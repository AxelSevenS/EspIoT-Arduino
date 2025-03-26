#include <Arduino.h>

#define STEAM_THRESHOLD 500

class SteamSensor {
private:
int sensorPin;
int threshold;

public:
	SteamSensor(int pin) : SteamSensor(pin, STEAM_THRESHOLD) { }
	SteamSensor(int pin, int thresh) : sensorPin(pin), threshold(thresh) {
		pinMode(sensorPin, INPUT);
	}

	int readSteamLevel() {
		return analogRead(sensorPin);
	}

	bool isSteamDetected() {
		return readSteamLevel() >= threshold;
	}

	void printSteamLevel() {
		Serial.print("Steam Level (%): ");
		Serial.println(readSteamLevel());
	}
};
