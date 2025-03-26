#include <thread>
#include <stdio.h>


#include "BLE.cpp"

#include "TempHumSensor.cpp"
#include "SteamSensor.cpp"

#include "Button.cpp"

#include "LED.cpp"
#include "RGB.cpp"
// #include "LCD.cpp"
#include "Window.cpp"


BLE ble;

TempHumSensor tempHum(17);
SteamSensor steam(34);

Button button1(27);
Button button2(16);

LED led(12);
RGB rgb(4, 32);
// LCD lcd(0x27, 16, 2);
Window window(5);



void sensorTask() {
	while (true) {
		// tempHum.printTempHumInfo();
		delay(10);
	}
}

void ledTask() {
	while (true) {
		led.blink(100);
		delay(1000);
	}
}

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

// void lcdTask() {
// 	while (true) {
// 		lcd.writeText("Hello World!", 1);
// 		lcd.writeTextScrolling("un message bien long pour test", 0, 400);
// 		lcd.clearScreen();
// 	}
// }

void setup() {
	Serial.begin(115200);

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
	clock_prescale_set(clock_div_1);
#endif

	ble.begin();

	tempHum.begin();

	button1.begin();
	button2.begin();

	led.begin();
	// rgb.begin();
	window.begin();


	std::thread sensorThread(sensorTask);

	std::thread ledThread(ledTask);
	// std::thread rgbThread(rgbTask);


	sensorThread.detach();

	ledThread.detach();
	// rgbThread.detach();

}

void loop() {
	ble.setTemperature(tempHum.readTemperature());
	ble.loop();

	// bool button1Pressed = button1.isPressed();
	// bool button2Pressed = button2.isPressed();

	// Serial.print("Button 1: ");
	// Serial.println(button1Pressed);

	// Serial.print("Button 2: ");
	// Serial.println(button2Pressed);
}

