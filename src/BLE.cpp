#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>


#define SERVICE_UUID              "4efbac2b-26d0-4341-9e18-48db2a98ce1f"
#define TEMP_CHARACTERISTIC_UUID  "2579c8dd-bc99-4001-b5c9-81cf30385403"
#define LED_CHARACTERISTIC_UUID   "35569cd2-0c9b-4b3a-9a2c-580581b6448e"
#define BTN_CHARACTERISTIC_UUID   "ff176132-91ca-48d1-9f25-a26332a53d77"

class BLE {
private:
	BLEServer *pServer = NULL;
	BLECharacteristic *tempCharacteristic = NULL;
	BLECharacteristic *ledCharacteristic = NULL;
	BLECharacteristic *buttonCharacteristic = NULL;

	uint32_t lastNotifiedTemperatureValue = 0;
	uint32_t temperatureValue = 0;

	bool deviceConnected = false;
	bool oldDeviceConnected = false;

	class MyServerCallbacks : public BLEServerCallbacks {
	private:
		BLE &parent;
	public:
		MyServerCallbacks(BLE &parentInstance) : parent(parentInstance) {}

		void onConnect(BLEServer *pServer) override {
			parent.deviceConnected = true;
		}

		void onDisconnect(BLEServer *pServer) override {
			parent.deviceConnected = false;
		}
	};

public:
	BLE() {}

	void setTemperature(uint32_t temp) {
		temperatureValue = temp;
	}

	void begin() {
		// Create the BLE Device
		BLEDevice::init("GROSSE PUTE");

		// Create the BLE Server
		pServer = BLEDevice::createServer();
		pServer->setCallbacks(new MyServerCallbacks(*this));

		// Create the BLE Service
		BLEService *pService = pServer->createService(SERVICE_UUID);

		// Create a BLE Characteristic
		tempCharacteristic = pService->createCharacteristic(
			TEMP_CHARACTERISTIC_UUID,
			BLECharacteristic::PROPERTY_READ
		);
		ledCharacteristic = pService->createCharacteristic(
			LED_CHARACTERISTIC_UUID,
			BLECharacteristic::PROPERTY_WRITE
		);
		buttonCharacteristic = pService->createCharacteristic(
			BTN_CHARACTERISTIC_UUID,
			BLECharacteristic::PROPERTY_NOTIFY
		);

		// Creates BLE Descriptor 0x2902: Client Characteristic Configuration Descriptor (CCCD)
		tempCharacteristic->addDescriptor(new BLE2902());

		// Start the service
		pService->start();

		// Start advertising
		BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
		pAdvertising->addServiceUUID(SERVICE_UUID);
		pAdvertising->setScanResponse(false);
		//   pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter


		BLEDevice::startAdvertising();
		Serial.println("Waiting a client connection to notify...");
	}

	void loop() {
		Serial.println("loop");
		// notify changed value
		if (deviceConnected) {
			tempCharacteristic->setValue((uint8_t*)&temperatureValue, 4);
			tempCharacteristic->notify();
			Serial.print("Notify Temperature value: ");
			Serial.println(temperatureValue);
			lastNotifiedTemperatureValue = temperatureValue;
		}

		// disconnecting
		if (!deviceConnected && oldDeviceConnected) {
			delay(500);                   // give the bluetooth stack the chance to get things ready
			pServer->startAdvertising();  // restart advertising
			Serial.println("start advertising");
			oldDeviceConnected = deviceConnected;
		}
		// connecting
		if (deviceConnected && !oldDeviceConnected) {
			// do stuff here on connecting
			oldDeviceConnected = deviceConnected;
		}

		delay(500);
	}
};
