#include <Wire.h>
#include <LiquidCrystal_I2C.h>


class LCD {

private:
	LiquidCrystal_I2C lcd;
	uint8_t cols;
	uint8_t rows;

public:
	LCD(uint8_t address, uint8_t cols, uint8_t rows)
		: lcd(address, cols, rows), cols(cols), rows(rows) {
	}

	void begin() {
		lcd.init();
		lcd.backlight();
		lcd.clear();
	}

	// Méthode pour écrire un texte à une position donnée
	void writeText(const char* text, int row, int col = 0) {
		if (col >= 0 && col < cols && row >= 0 && row < rows) {
			lcd.setCursor(col, row);
			lcd.print(text);
		} else {
			// Serial.println("Erreur : position hors limites de l'écran");
		}
	}

	// Méthode pour effacer l'écran
	void clearScreen() {
		lcd.clear();
	}

	// Méthode pour défiler le texte sur l'écran
	void writeTextScrolling(const char* text, int row, int delayTime) {
		int len = strlen(text);
		for (int i = 0; i <= len; i++) {
			lcd.setCursor(0, row);
			lcd.print(text + i);
			delay(delayTime);
			lcd.clear();
		}
	}
};