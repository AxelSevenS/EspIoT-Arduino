#include <thread>

#include "TempHumSensor.cpp"

#include "LED.cpp"
#include "RGB.cpp"
#include "LCD.cpp"

#include "Window.cpp"

TempHumSensor tempHum;

LED led;
RGB rgb;
LCD lcd;

Window window;


void rgbTask() {
    while (true) {
        rgb.colorWipe(rgb.color(255, 0, 0), 50); // Rouge
        rgb.colorWipe(rgb.color(0, 255, 0), 50); // Vert
        rgb.colorWipe(rgb.color(0, 0, 255), 50); // Bleu

        rgb.theaterChase(rgb.color(127, 127, 127), 50); // Blanc, demi-luminosité
        rgb.theaterChase(rgb.color(127, 0, 0), 50);     // Rouge, demi-luminosité
        rgb.theaterChase(rgb.color(0, 0, 127), 50);     // Bleu, demi-luminosité

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
		Serial.println("TempHumSensor");
		tempHum.tempHumInfo();
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