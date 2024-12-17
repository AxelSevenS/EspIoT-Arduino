#include "LCD.cpp"
LCD lcd(0x27, 16, 2);

void setup() {
	lcd.begin ();
	lcd.writeText (0, 0, "ricardo");
	lcd.writeText (2, 1, "GIGACHAD");
}

void loop() {

}