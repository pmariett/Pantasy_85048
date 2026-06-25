/***
Electronisation de lla radio vintage Pantasy 85048
https://pantasy.com/products/pantasy-radio-85048

____________________________________________________________________

Composants et connexions

    Alimentation 5V
        Entrée : Fil rouge (+5V) et noir (GND).
        Ajouter une diode Schottky 1N5817 (cathode vers 5V) pour protection contre inversion.
        Condensateur 100nF entre 5V et GND (découplage).

    Régulateur 3.3V (AMS1117-3.3)
        IN : Fil rouge (5V) depuis l'alimentation.
        OUT : Fil orange (3.3V) vers le RDA5807M.
        GND : Fil noir (masse commune).
        Condensateurs :
            10µF entre IN et GND.
            10µF entre OUT et GND.
            100nF en parallèle sur OUT (stabilité).

    Arduino Pro Mini (5V)
        VCC : Fil rouge (5V).
        GND : Fil noir (masse).
        A4 (SDA) : Fil vert → SDA du RDA5807M.
        A5 (SCL) : Fil vert → SCL du RDA5807M.
        A2 : Fil vert → Potentiomètre "Mode" (10kΩ).
        A3 : Fil vert → Potentiomètre "Fréquence" (10kΩ).
        D5 (PWM) : Fil vert → Anode LED (cathode vers GND via résistance 220Ω).
        A0 : Fil bleu → Entrée audio FM (LAUD+ du PAM8403).
        A1 : Fil bleu → Entrée audio Bluetooth (RAUD+ du PAM8403).
        RX (Pin 0) : Fil vert → TX du module Bluetooth MH-M18.
        TX (Pin 1) : Fil vert → RX du module Bluetooth MH-M18.

    Module RDA5807M (FM)
        VCC : Fil orange (3.3V) depuis AMS1117.
        GND : Fil noir (masse).
        SDA : Fil vert → A4 (Arduino).
        SCL : Fil vert → A5 (Arduino).
        AUDIO OUT : Fil bleu → Entrée A0 (Arduino) → LAUD+ (PAM8403).

    Ampli PAM8403
        VCC : Fil rouge (5V).
        GND : Fil noir (masse).
        LAUD+ : Fil bleu depuis A0 (Arduino).
        RAUD+ : Fil bleu depuis A1 (Arduino).
        LAUD- et RAUD- : Fil noir (GND).
        OUT+ et OUT- : Fils bleus → Haut-parleur (8Ω).

    Module Bluetooth MH-M18
        VCC : Fil rouge (5V).
        GND : Fil noir (masse).
        TX : Fil vert → RX (Arduino Pin 0).
        RX : Fil vert → TX (Arduino Pin 1).
        AUDIO OUT : Fil bleu → Entrée A1 (Arduino) → RAUD+ (PAM8403).

    Haut-parleur (8Ω)
        Fil bleu depuis OUT+ et OUT- du PAM8403.

    Potentiomètres (10kΩ)
        Mode :
            Une patte → 5V (rouge).
            Patte centrale → A2 (vert).
            Autre patte → GND (noir).
        Fréquence :
            Une patte → 5V (rouge).
            Patte centrale → A3 (vert).
            Autre patte → GND (noir).

    LEDs (écran rétroéclairé)
        Anode → D5 (vert) via résistance 220Ω.
        Cathode → GND (noir).



***/

#include <Wire.h>
#include <SoftwareSerial.h>

// PINS
#define MODE_POT A2
#define FREQ_POT A3
#define LED_PIN 5
#define FM_AUDIO A0
#define BT_AUDIO A1

// MODES
#define MODE_OFF 0
#define MODE_FM 1
#define MODE_BT 2

// RDA5807M
#define RDA_ADDR 0x10
#define REG_CHIPID 0x00
#define REG_CTRL 0x02
#define REG_CHAN 0x03
#define REG_VOL 0x05

// Bluetooth Serial
SoftwareSerial btSerial(0, 1); // RX, TX

// Variables
int currentMode = MODE_OFF;
int currentFreq = 88; // MHz
int lastModeValue = 0;
int lastFreqValue = 0;

void setup() {
  Serial.begin(9600);
  btSerial.begin(9600);
  Wire.begin();
  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  initRDA5807M();
  Serial.println("Radio démarrée");
}

void loop() {
  // Lecture potentiomètres
  int modeValue = analogRead(MODE_POT) / 256; // 0-3 (4 positions)
  int freqValue = analogRead(FREQ_POT); // 0-1023
  
  // Gestion du mode (avec hystérésis)
  if (abs(modeValue - lastModeValue) > 0) {
    setMode(modeValue);
    lastModeValue = modeValue;
  }
  
  // Gestion fréquence FM (76-108 MHz)
  if (currentMode == MODE_FM && abs(freqValue - lastFreqValue) > 10) {
    int newFreq = 76 + (freqValue * 32) / 1023;
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
      // Le module MH-M18 fonctionne en mode passif
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
  // Calcul du channel (76-108 MHz)
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