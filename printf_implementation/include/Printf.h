/*
	Hallo Herr Fertig,

	ich habe mir einige Gedanken zur Formatierung des dec2bin strings gemacht.
	Dabei bin ich auf zwei plausible Implementierungen gekommen:

	Option 1:
	
	Die auskommentierte Lösung verwendet als 3. Element des Buffers ein Bit das 0 oder 1 sein kann, für positiv und negativ.
	Danach kommt die Zahl im Zweierkomplement oder eben im positiven Bereich. Die Darstellung entspricht also einer normalen signed Integer Zahl. (Zahlenkreis => Alle positiven zahlen fangen mit 0 an)
	Da hier jedoch führende Nullen bei positiven Zahlen vorkommen habe ich diese Lösung nicht verwendet.

	Option 2:

	Hier habe ich keine führenden Nullen, jedoch führende Einsen für das 2er Komplement.
	Man erkennt das Komplement daran, dass die Zahl 32 Bit hat, sonst nicht!
	
	Da mir die Implementierung für Option 2 deutlich galanter gelungen ist und führende Nullen ausgeschlossen wurden habe ich diese Lösung gewählt.
	Aufgrund der unklarheit lasse ich die Funktionen jedoch im Code auskommentiert. 
	Abgabe soll Option 2 sein. Falls diese fatal falsch ist können Sie noch Option 1 auskommentieren. :)

	Liebe Grüße

*/



//void  intToBin(char* chararr_out, const int sint_in);
//void  buildTwoComp(char* binaryValue, const long long int binSize);

void  intToHex(char* hexValue, const int toHex);
void  int2bin(char* chararr_out, int sint_in);
void  getHexCharForPos(char* hexValueAtPosition, const int toHexChar);
char* Printf(char* dst, const void* end, const char* fmt, ...);

