#include "RGB.cpp"
#include "LCD.cpp"

RGB rgb;
LCD lcd;

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
	clock_prescale_set(clock_div_1);
#endif

	rgb.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)

	lcd.begin ();

	// SetTheServo();
}

void loop() {
	// Fill along the length of the strip in various colors...
	rgb.colorWipe(rgb.color(255,   0,   0), 50); // Red
	rgb.colorWipe(rgb.color(  0, 255,   0), 50); // Green
	rgb.colorWipe(rgb.color(  0,   0, 255), 50); // Blue

	// Do a theater marquee effect in various colors...
	rgb.theaterChase(rgb.color(127, 127, 127), 50); // White, half brightness
	rgb.theaterChase(rgb.color(127,   0,   0), 50); // Red, half brightness
	rgb.theaterChase(rgb.color(  0,   0, 127), 50); // Blue, half brightness

	rgb.rainbow(10);             // Flowing rainbow cycle along the whole strip
	rgb.theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant
	//OpenTheGate();


	lcd.scrollText ("un message bien long pour test si axel est un chad", 0, 200);
}