/*
 * Electronisation de lla radio vintage Pantasy 85048
 * https://pantasy.com/products/pantasy-radio-85048
 *
 *
 * ==============================================================================
 * MONTAGE RADIO VINTAGE LÉGO - ESP32-C3 + RDA5807M + MH-M18 + PAM8403
 *
 * Conventions de couleurs :
 * - Noir   : GND (masse)
 * - Rouge  : 5V (alimentation principale)
 * - Orange : 3.3V (alimentation modules sensibles)
 * - Vert   : Signaux numériques/analogiques (I2C, potentiomètres, PWM)
 * - Bleu   : Signaux audio (vers ampli/haut-parleur)
 *
 * ==============================================================================
 * ALIMENTATION
 * - 5V (rouge) : Alimente l'ESP32-C3 (broche VIN ou 5V) et le PAM8403 (VCC).
 * - 3.3V (orange) : Sortie de l'ESP32-C3 (broche 3.3V) pour alimenter :
 *     - RDA5807M (VCC)
 *     - MH-M18 (VCC)
 *
 * ==============================================================================
 * MODULE RDA5807M (FM)
 * - VCC    : 3.3V (orange) depuis ESP32-C3.
 * - GND    : Noir (masse commune).
 * - SDA    : Vert → GPIO 8 (ESP32-C3).
 * - SCL    : Vert → GPIO 9 (ESP32-C3).
 * - AUDIO OUT : Bleu → GPIO 0 (A0, entrée audio FM pour PAM8403).
 *
 * ==============================================================================
 * MODULE BLUETOOTH MH-M18
 * - VCC    : 3.3V (orange) depuis ESP32-C3.
 * - GND    : Noir (masse commune).
 * - TX     : Vert → GPIO 11 (RX, ESP32-C3).
 * - RX     : Vert → GPIO 10 (TX, ESP32-C3).
 * - AUDIO OUT : Bleu → GPIO 1 (A1, entrée audio Bluetooth pour PAM8403).
 *
 * ==============================================================================
 * AMPLIFICATEUR PAM8403
 * - VCC    : 5V (rouge) depuis alimentation.
 * - GND    : Noir (masse commune).
 * - LAUD+  : Bleu ← GPIO 0 (A0, signal FM depuis RDA5807M).
 * - RAUD+  : Bleu ← GPIO 1 (A1, signal Bluetooth depuis MH-M18).
 * - LAUD-  : Noir (GND).
 * - RAUD-  : Noir (GND).
 * - OUT+   : Bleu → Haut-parleur (+).
 * - OUT-   : Bleu → Haut-parleur (-).
 *
 * ==============================================================================
 * POTENTIOMÈTRES (10kΩ)
 * - Mode (4 positions) :
 *     - Une patte : 3.3V (orange) depuis ESP32-C3.
 *     - Patte centrale : Vert → GPIO 2 (A2, ESP32-C3).
 *     - Autre patte : Noir (GND).
 * - Fréquence (réglage FM) :
 *     - Une patte : 3.3V (orange) depuis ESP32-C3.
 *     - Patte centrale : Vert → GPIO 3 (A3, ESP32-C3).
 *     - Autre patte : Noir (GND).
 *
 * ==============================================================================
 * LEDS (ÉCRAN RÉTROÉCLAIRÉ)
 * - Anode : Vert → GPIO 4 (PWM, ESP32-C3) via résistance 220Ω.
 * - Cathode : Noir (GND).
 *
 * ==============================================================================
 * NOTES
 * - L'ESP32-C3 fonctionne en 3.3V natif : pas besoin de régulateur pour le RDA5807M.
 * - Le MH-M18 gère l'appairage Bluetooth avec le smartphone.
 * - Le PAM8403 amplifie les signaux audio (FM ou Bluetooth) vers le haut-parleur.
 * - Les potentiomètres utilisent des entrées analogiques 12 bits (0-4095) de l'ESP32-C3.
 */

***/

#include <Wire.h>

// PINS ESP32-C3
#define MODE_POT 2    // GPIO 2 (A2)
#define FREQ_POT 3    // GPIO 3 (A3)
#define LED_PIN 4     // GPIO 4 (PWM)
#define FM_AUDIO 0    // GPIO 0 (A0)
#define BT_AUDIO 1    // GPIO 1 (A1)

// MODES
#define MODE_OFF 0
#define MODE_FM 1
#define MODE_BT 2

// RDA5807M
#define RDA_ADDR 0x10
#define REG_CTRL 0x02
#define REG_CHAN 0x03

// Variables
int currentMode = MODE_OFF;
int currentFreq = 88; // MHz
int lastModeValue = 0;
int lastFreqValue = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(8, 9); // SDA=GPIO 8, SCL=GPIO 9

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  initRDA5807M();
}

void loop() {
  // Lecture potentiomètres
  int modeValue = analogRead(MODE_POT) / 1365; // 0-3 (4 positions)
  int freqValue = analogRead(FREQ_POT); // 0-4095 (ESP32-C3 : 12 bits)

  // Gestion du mode (avec hystérésis)
  if (abs(modeValue - lastModeValue) > 0) {
    setMode(modeValue);
    lastModeValue = modeValue;
  }

  // Gestion fréquence FM (76-108 MHz)
  if (currentMode == MODE_FM && abs(freqValue - lastFreqValue) > 20) {
    int newFreq = 76 + (freqValue * 32) / 4095;
    if (newFreq != currentFreq) {
      setFMFrequency(newFreq);
      currentFreq = newFreq;
    }
    lastFreqValue = freqValue;
  }

  delay(100);
}

void setMode(int mode) {
  currentMode = mode;

  switch(mode) {
    case MODE_OFF:
      digitalWrite(LED_PIN, LOW);
      Serial.println("Mode: OFF");
      break;

    case MODE_FM:
      digitalWrite(LED_PIN, HIGH);
      initRDA5807M();
      setFMFrequency(currentFreq);
      Serial.println("Mode: FM");
      break;

    case MODE_BT:
      digitalWrite(LED_PIN, HIGH);
      Serial.println("Mode: Bluetooth");
      break;
  }
}

void initRDA5807M() {
  Wire.beginTransmission(RDA_ADDR);
  Wire.write(0x02); // Registre de contrôle
  Wire.write(0xC1); // Activation, FCC band
  Wire.write(0x08);
  Wire.endTransmission();
  delay(100);
}

void setFMFrequency(int freqMHz) {
  int channel = (freqMHz - 76) * 10 / 10;

  Wire.beginTransmission(RDA_ADDR);
  Wire.write(0x03); // Registre fréquence
  Wire.write((channel >> 8) & 0xFF);
  Wire.write(channel & 0xFF);
  Wire.endTransmission();

  Serial.print("Fréquence: ");
  Serial.print(freqMHz);
  Serial.println(" MHz");
  delay(200);
}