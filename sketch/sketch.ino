#include <thread>
#include <stdio.h>

#include "TempHumSensor.cpp"
#include "SteamSensor.cpp"

#include "LED.cpp"
#include "RGB.cpp"
#include "LCD.cpp"

#include "Window.cpp"


TempHumSensor tempHum;
SteamSensor steam;

LED led;
RGB rgb;
LCD lcd;

Window window;

// String displayText = "Hello World!";


void rgbTask() {
	while (true) {
		rgb.colorWipe(rgb.color(255, 0, 0), 50);
		rgb.colorWipe(rgb.color(0, 255, 0), 50);
		rgb.colorWipe(rgb.color(0, 0, 255), 50);

		rgb.theaterChase(rgb.color(127, 127, 127), 50);
		rgb.theaterChase(rgb.color(127, 0, 0), 50);
		rgb.theaterChase(rgb.color(0, 0, 127), 50);

		rgb.rainbow(10);             // Cycle d'arc-en-ciel sur toute la bande
		rgb.theaterChaseRainbow(50); // Variante de l'effet theaterChase avec arc-en-ciel
	}
}

void lcdTask() {
	while (true) {
		lcd.writeText("Hello World!", 1);
		lcd.writeTextScrolling("un message bien long pour test", 0, 400);
		lcd.clearScreen();
	}
}

void tempHumTask() {
	while (true) {
		// tempHum.printTempHumInfo();
		steam.printSteamLevel();

		delay(10000);
	}
}

void setup() {
	Serial.begin(115200);

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
	clock_prescale_set(clock_div_1);
#endif


	tempHum.begin ();

	led.begin ();
	rgb.begin ();
	lcd.begin ();

	window.begin ();


	std::thread tempHumThread(tempHumTask);

	std::thread rgbThread(rgbTask);
	std::thread lcdThread(lcdTask);


	tempHumThread.detach();

	rgbThread.detach();
	lcdThread.detach();
}

void loop() {
	led.blink(100);
}