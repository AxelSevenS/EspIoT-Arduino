#include <thread>
#include <stdio.h>
#include <ModbusSerial.h>

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

#define mbSerial Serial1
ModbusSerial mb(mbSerial, 1);

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

void sensorTask() {
	while (true) {
		mb.Hreg(0, steam.readSteamLevel());

		mb.task();
		delay(10);
	}
}

void setup() {
	Serial.begin(115200);

	mbSerial.begin(9600, SERIAL_8N1, 4, 5);
	mb.addHreg(0, 0);


#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
	clock_prescale_set(clock_div_1);
#endif


	tempHum.begin ();

	led.begin ();
	rgb.begin ();
	lcd.begin ();

	window.begin ();


	std::thread sensorThread(sensorTask);

	std::thread rgbThread(rgbTask);
	std::thread lcdThread(lcdTask);


	sensorThread.detach();

	rgbThread.detach();
	lcdThread.detach();
}

void loop() {
	delay(1000);
	led.blink(100);
}