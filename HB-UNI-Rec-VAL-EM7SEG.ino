//- -----------------------------------------------------------------------------------------------------------------------
// AskSin++
// 2016-10-31 papa Creative Commons - http://creativecommons.org/licenses/by-nc-sa/3.0/de/
// 2020-04-16 jp112sdl Creative Commons - http://creativecommons.org/licenses/by-nc-sa/3.0/de/
//- -----------------------------------------------------------------------------------------------------------------------

#include <SPI.h>
#define EI_NOTEXTERNAL
#include <EnableInterrupt.h>
#include <AskSinPP.h>
#include <Device.h>
#include <Register.h>
#include "Em7seg_ctrl.h"

#define UNREACH_INTERVAL_SEC  600
uint8_t LISTEN_FOR_ADDRESS[3] = { 0xf9, 0xd2, 0x01 };
uint8_t LISTEN_FOR_TYPE       = 0x53;
#define PAYLOAD_START_IDX     2
#define PAYLOAD_LENGTH        4

EM7ModuleArray em7seg;

// all library classes are placed in the namespace 'as'
using namespace as;

// define all device properties
const struct DeviceInfo PROGMEM devinfo = {
  {0xFF, 0xFF, 0xFF},     // Device ID
  "..........",           // Device Serial
  {0x00, 0x00},           // Device Model
  0x10,                   // Firmware Version
  as::DeviceType::Remote, // Device Type
  {0x00, 0x00}            // Info Bytes
};

typedef AskSin<StatusLed<4>, NoBattery, Radio<LibSPI<10>, 2>> HalType;

class RcvDev : public Device<HalType, DefList0>, Alarm {
    DefList0 l0;
public:
    typedef Device<HalType, DefList0> BaseDevice;
    RcvDev (const DeviceInfo& i, uint16_t addr) : BaseDevice(i, addr, l0, 0), Alarm(0), l0(addr) {}
    virtual ~RcvDev () {}


    void setUnreach() {
      em7seg.displayWord("----");
    }

    virtual void trigger (__attribute__ ((unused)) AlarmClock& clock) {
      set(seconds2ticks(UNREACH_INTERVAL_SEC));
      clock.add(*this);
      setUnreach();
    }

    virtual bool process(Message& msg) {
      //DHEX(msg.flags());
      HMID ListenID = HMID(LISTEN_FOR_ADDRESS);
      uint8_t MessageType = msg.type();

      if (msg.from() == ListenID && MessageType == LISTEN_FOR_TYPE) {
        DPRINTLN("Received Message");
        sysclock.cancel(*this);
        sysclock.add(*this);
        this->led().ledOn(millis2ticks(500));

        if ( (msg.length() - 9) < (PAYLOAD_LENGTH + PAYLOAD_START_IDX)  ) {
          DPRINT(F("Payload too short: Payload length ="));DDEC(msg.length() - 9);DPRINT(", PAYLOAD_START_IDX = ");DDEC(PAYLOAD_START_IDX);DPRINT(", PAYLOAD_LENGTH = ");DDECLN(PAYLOAD_LENGTH);
          return true;
        }

        for (uint8_t l = 0; l < msg.length() - 9; l++) {
          DHEX(msg.buffer()[l + 9]);
          DPRINT(" ");
        }
        DPRINTLN("");


        uint32_t liter = 0;
        for (uint8_t l = 0; l < PAYLOAD_LENGTH; l++) {
          liter += (uint32_t)msg.buffer()[l + 9 + PAYLOAD_START_IDX] << (((PAYLOAD_LENGTH-1) * 8) - (l * 8)) ;
        }

        DPRINT("Liter = ");DDECLN(liter);

        em7seg.displayNumber(liter, false, true);
      }

      return true;
    }

    bool init (HalType& hal) {
      HMID id;
      this->setHal(hal);
      this->getDeviceID(id);
      hal.init(id);
      hal.config(this->getConfigArea());
      sysclock.add(*this);
      return false;
    }
};

HalType hal;
RcvDev sdev(devinfo, 0x20);

void setup () {
  DINIT(57600, ASKSIN_PLUS_PLUS_IDENTIFIER);
  em7seg.init();
  delay(200);
  sdev.init(hal);
}

void loop() {
  bool rdy = hal.runready();
  bool poll = sdev.pollRadio();
  if (!rdy && !poll)
    hal.activity.savePower<Idle<>>(hal);
}
