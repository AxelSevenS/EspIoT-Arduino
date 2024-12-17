#include <DHT11.h>

#define DHT11_PIN 4

class TempHumSensor {
private:
	DHT11 dht;

public:
	TempHumSensor()
		: TempHumSensor(DHT11_PIN) {
	}

	TempHumSensor(int pin)
		: dht(pin) {
	}

	void begin() { }

	void tempHumInfo() {
		int temp = dht.readTemperature();
		int hum = dht.readHumidity();


		switch (temp) {
		case 253:
			Serial.println("Error: DHT11_ERROR_TIMEOUT");
			break;
		case 254:
			Serial.println("Error: DHT11_ERROR_CHECKSUM");
			break;
		default:
			Serial.print("Temperature (C): ");
			Serial.println(temp);
			break;
		}

		switch (hum) {
		case 253:
			Serial.println("Error: DHT11_ERROR_TIMEOUT");
			break;
		case 254:
			Serial.println("Error: DHT11_ERROR_CHECKSUM");
			break;
		default:
			Serial.print("Humidity (%): ");
			Serial.println(hum);
			break;
		}
	}
};