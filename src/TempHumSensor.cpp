#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

class TempHumSensor {
private:
	DHT_Unified dht;

public:
	TempHumSensor(uint8_t pin)
		: dht(pin, DHT11) {
	}

	void begin() {
		dht.begin();
	}

	float readTemperature() {
		sensors_event_t event;
		dht.temperature().getEvent(&event);
		return event.temperature;
	}

	float readHumidity() {
		sensors_event_t event;
		dht.humidity().getEvent(&event);
		return event.relative_humidity;
	}

	void printTempHumInfo() {
		float temp = readTemperature();
		float hum = readHumidity();

		Serial.print("Temperature: ");
		Serial.print(temp);
		Serial.print("°C\nHumidity: ");
		Serial.print(hum);
		Serial.println("%");
	}
};