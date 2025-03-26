#include <thread>
#include <stdio.h>
#include <Arduino.h>

class Button {
private:
	uint8_t pin;

public:
	Button(uint8_t pin)
		: pin(pin)
	{ }

	void begin() {
	  pinMode(pin, INPUT);
	}

	bool isPressed() {
	  return digitalRead(pin) == 0;
	}
};