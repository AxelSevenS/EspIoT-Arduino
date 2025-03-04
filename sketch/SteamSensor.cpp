#include <Arduino.h>

#define STEAM_SENSOR_PIN 33
#define STEAM_THRESHOLD 500

class SteamSensor {
private:
int sensorPin;
int threshold;

public:
	SteamSensor() : SteamSensor(STEAM_SENSOR_PIN, STEAM_THRESHOLD) { }
	SteamSensor(int pin, int thresh) : sensorPin(pin), threshold(thresh) {
		pinMode(sensorPin, INPUT);
	}

	// Méthode pour lire la valeur du capteur en mode analogique
	int readSteamLevel() {
		return analogRead(sensorPin);
	}

	// Méthode pour détecter la vapeur en fonction d'un seuil
	bool isSteamDetected() {
		return readSteamLevel() >= threshold;
	}

	void printSteamLevel() {
		Serial.print("Steam Level (%): ");
		Serial.println(readSteamLevel());
	}
};
