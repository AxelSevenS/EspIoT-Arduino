#include <Arduino.h>

#define SERVO_PIN 26

class Window {

private:
	int servoPin;
public:
	Window()
		: Window(SERVO_PIN)
	{ }

	Window(int servoPin)
		: servoPin(servoPin)
	{ }

	void begin() {
		pinMode(servoPin, OUTPUT);
	}

	void SetTheServo(int angleDegrees) {
		auto pulseWidth = angleDegrees * 11 + 500; // convert angle to 500-2480 pulse width
		digitalWrite(servoPin, HIGH);
		delayMicroseconds(pulseWidth); // delay microsecond of pulse width
		digitalWrite(servoPin, LOW);
		delay(20 - pulseWidth / 1000);
	}

	void LaunchTheServo(uint32_t degrees) {
		// Serial.print("moving servo to ");
		// Serial.print(val, DEC);
		// Serial.println();
		for(int i = 0; i <= 50; i++)
		{
			SetTheServo(degrees);
		};
	}
};



