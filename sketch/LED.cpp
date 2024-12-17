#include <Arduino.h>

#define LED_PIN 13

class LED {
private:
	uint8_t led;
public:
	LED() : LED(LED_PIN) { }
	LED(uint8_t pin)
		: led(pin)
	{ }

	void begin()
	{
		pinMode(led, OUTPUT);
	}

	void blink(int delayTime)
	{
		digitalWrite(led, HIGH);
		delay(delayTime);
		digitalWrite(led, LOW);
		delay(delayTime);
	}

	void blink(int delayTime, int count)
	{
		for (int i = 0; i < count; i++)
		{
			blink(delayTime);
		}
	}

	void blink(int delayTime, int count, int pauseTime)
	{
		for (int i = 0; i < count; i++)
		{
			blink(delayTime);
			delay(pauseTime);
		}
	}

	void blink(int delayTime, int count, int pauseTime, int repeat)
	{
		for (int i = 0; i < repeat; i++)
		{
			blink(delayTime, count, pauseTime);
		}
	}

	void on()
	{
		digitalWrite(led, HIGH);
	}

	void off()
	{
		digitalWrite(led, LOW);
	}

	void toggle()
	{
		digitalWrite(led, !digitalRead(led));
	}
};