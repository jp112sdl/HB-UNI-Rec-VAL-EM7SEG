# HB-UNI-Rec-VAL-EM7SEG
#### abgesetzte 7-Segment Anzeige für die Regenwasserzisterne

Derzeit erfolgt die Messwert-Ermittlung und -Übertragung des Wasserstands mittels [HB-UNI-Sen-LEV-US](https://github.com/jp112sdl/HB-UNI-Sen-LEV-US) an die HomeMatic CCU. 
Die Anzeige des Inhalts erfolgt im Haus auf 2 ePaper Displays, sowie auf einer mobilen Visualisierung auf dem iPhone.
<br/>
Was fehlte, war eine direkte Anzeige im Garten - dort wo ich das Wasser benötige.<br/>
<br/> 
Ich hatte noch aus einem meiner anderen Projekte ([EM7SEG](https://github.com/jp112sdl/EM7SEG)-Uhr) ein paar mechanische 7-Segmentanzeigen (_bekannt aus früheren Tank-Zapfsäulen_) übrig.
<br/>
Ab und zu bekommt man noch welche bei eBay: https://www.ebay.de/itm/174249670792
<br/><br/>
Der [HB-UNI-Sen-LEV-US](https://github.com/jp112sdl/HB-UNI-Sen-LEV-US) sendet nun alle paar Minuten den aktuellen Füllstand an die CCU.
Diese Funktelegramme werden vom HB-UNI-Rec-VAL-EM7SEG direkt empfangen und angezeigt.<br/>
**Vorteile:**
- Der anzuzeigende Wert muss nicht extra wieder an die Anzeige gesendet werden.
- Das HB-UNI-Rec-VAL-EM7SEG taucht in keiner Konfiguration auf, sondern läuft nur als "Mithörer" nebenher. Es müssen somit keine Vorkehrungen getroffen werden, falls es mal nicht erreichbar ist (im Winter z.B.) 



<img src="Images/Front_Unreach.jpeg" width=600 /><br/>
_Unreach-Timeout überschritten; Kein Telegramm innerhalb der vorgegebenen Zeit empfangen_

<img src="Images/Front_Wert.jpeg" width=600 /><br/>
_Wert empfangen (21 Liter ^^)_

<img src="Images/Back.jpeg" width=600 /><br/>
_Innenleben_


