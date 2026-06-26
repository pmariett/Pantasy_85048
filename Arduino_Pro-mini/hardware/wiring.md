# 📋 MONTAGE INTÉGRAL - Arduino Pro Mini + RDA5807M + MH-M18 + PAM8403 + 1 HP

## LÉGENDE COULEURS
- **Noir** : GND (masse)
- **Rouge** : 5V
- **Orange** : 3,6V (sortie abaisseur)
- **Vert** : Signaux numériques
- **Bleu** : Audio

---

## 1️⃣ ALIMENTATION PRINCIPALE

### Source 5V
```
+5V (USB/Step-Down)
├─ (rouge) ──→ VCC Arduino Pro Mini (pin VCC)
├─ (rouge) ──→ VCC PAM8403 (pin VCC)
└─ (rouge) ──→ Anode 1N4007 n°1

GND (USB/Step-Down)
├─ (noir) ──→ GND Arduino Pro Mini (pin GND × 2)
├─ (noir) ──→ GND PAM8403 (pin GND)
├─ (noir) ──→ GND RDA5807M (pin GND)
├─ (noir) ──→ GND MH-M18 (pin GND)
└─ (noir) ──→ GND potentiomètres (extrémité)
```

### Abaisseur 5V → 3,6V (avec 1N4007)
```
+5V (rouge)
│
└─[1N4007 n°1]─ (Anode vers 5V, Cathode vers suivant)
    │
    └─[1N4007 n°2]─ (Anode vers précédent, Cathode vers 3,6V)
        │
        ├─ (orange) ──→ VCC RDA5807M
        ├─ (orange) ──→ VCC MH-M18
        │
        └─[Condensateur 100µF 50V]
            │
           GND (noir)
```

---

## 2️⃣ ARDUINO PRO MINI (5V, 16MHz)

### Broches utilisées
| Broche | Type    | Destination             | Couleur |
|--------|---------|-------------------------|---------|
| VCC    | Alim    | +5V                     | Rouge   |
| GND    | Alim    | GND commun              | Noir    |
| A4     | I2C     | SDA (RDA5807M)          | Vert    |
| A5     | I2C     | SCL (RDA5807M)          | Vert    |
| D2     | UART RX | TX du MH-M18            | Vert    |
| D3     | UART TX | RX du MH-M18            | Vert    |
| A0     | Analog  | Potentiomètre Mode      | Vert    |
| A1     | Analog  | Potentiomètre Fréquence | Vert    |

---

## 3️⃣ RDA5807M (Module FM I2C)

### Alimentation
- VCC ────(orange)──→ Ligne 3,6V
- GND ────(noir)────→ GND commun

### Communication I2C
- SDA ────(vert)────→ Arduino A4
- SCL ────(vert)────→ Arduino A5

### Audio (vers PAM8403 via résistance 10kΩ)
- L_OUT ──(bleu)──[10kΩ]──→ L_IN+ PAM8403 (point mixage)
- R_OUT ──(bleu)──[10kΩ]──→ L_IN+ PAM8403 (idem, pour mixage mono)

---

## 4️⃣ MH-M18 (Module Bluetooth UART)

### Alimentation
- VCC ────(orange)──→ Ligne 3,6V
- GND ────(noir)────→ GND commun

### Communication UART (SoftwareSerial)
- TX ─────(vert)────→ Arduino D2 (RX logiciel)
- RX ─────(vert)────→ Arduino D3 (TX logiciel)

### Audio (vers PAM8403 via résistance 10kΩ)
- L_OUT ──(bleu)──[10kΩ]──→ L_IN+ PAM8403 (point mixage)
- R_OUT ──(bleu)──[10kΩ]──→ L_IN+ PAM8403 (idem, pour mixage mono)

---

## 5️⃣ PAM8403 (Ampli Audio Stéréo 3W)

### Alimentation
- VCC ────(rouge)───→ +5V
- GND ────(noir)────→ GND commun

### Entrées audio (MONO sur canal L)
- L_IN+ ──(bleu)────← Point de mixage (depuis RDA + MH via résistances 10kΩ)
- L_IN- ──(noir)────→ GND commun
- R_IN+ ──(noir)────→ GND commun (non utilisé, maintient canal R au repos)
- R_IN- ──(noir)────→ GND commun

### Sorties audio (vers 1 seul HP)
- L_OUT+ ──(bleu)───→ + du Haut-Parleur 8Ω
- L_OUT- ──(noir)───→ – du Haut-Parleur 8Ω
- R_OUT+ ───────────→ Non utilisé (laissez libre)
- R_OUT- ───────────→ Non utilisé (laissez libre)

---

## 6️⃣ POTENTIOMÈTRES (RK11 B103, 4 broches, 10kΩ)

Chaque RK11 B103 a :
- **2 broches extrémités** (résistance totale 10kΩ),
- **1 broche curseur** (wiper),
- **1 broche midpoint** (à **ne pas connecter**).

### Potentiomètre Mode (A0)
```
+3,6V (orange)
│
[RK11 B103 Mode]
│
├─ Extrémité 1 ────→ GND (noir)
├─ Extrémité 2 ────→ +3,6V (orange)
└─ Curseur ───────→ A0 Arduino (vert)
│
└─ Midpoint ───────→ **Non connecté**
```

### Potentiomètre Fréquence (A1)
```
+3,6V (orange)
│
[RK11 B103 Fréquence]
│
├─ Extrémité 1 ────→ GND (noir)
├─ Extrémité 2 ────→ +3,6V (orange)
└─ Curseur ───────→ A1 Arduino (vert)
│
└─ Midpoint ───────→ **Non connecté**
```

---

## 7️⃣ RÉSUMÉ DES POINTS DE MIXAGE AUDIO

**Point de mixage L (entrée L_IN+ du PAM8403)** :
```
RDA5807M L_OUT ──[10kΩ]──┐
                      ├─→ L_IN+ PAM8403
MH-M18 L_OUT ───[10kΩ]──┘
```

**L_IN- du PAM** : branché à GND
**R_IN+/R_IN- du PAM** : branchés à GND (canal inutilisé en mono)

---

## ✅ CHECKLIST AVANT ALIMENTATION

- [ ] GND commun relie tous les modules
- [ ] RDA5807M et MH-M18 alimentés en 3,6V (via abaisseur 2 × 1N4007)
- [ ] Arduino Pro Mini alimenté en 5V
- [ ] PAM8403 alimenté en 5V
- [ ] I2C : A4 (SDA) et A5 (SCL) du RDA5807M connectés à l'Arduino
- [ ] UART : D2/D3 de l'Arduino connectés à TX/RX du MH-M18
- [ ] Potentiomètres RK11 B103 connectés à A0/A1 (midpoint non connecté)
- [ ] Résistances 10kΩ de mixage audio en place (RDA + MH → L_IN+ PAM)
- [ ] Condensateur 100µF 50V entre ligne 3,6V et GND
- [ ] Haut-parleur 8Ω connecté sur L_OUT+/L_OUT- du PAM
- [ ] Pas de court-circuit visible

---

## 🔧 CODE DE TEST (SoftwareSerial + I2C)

```cpp
#include <Wire.h>
#include <SoftwareSerial.h>

// SoftwareSerial pour le MH-M18 (RX=D2, TX=D3)
SoftwareSerial bt(2, 3); // RX, TX

void setup() {
  Serial.begin(9600);     // Moniteur série
  bt.begin(9600);         // MH-M18 à 9600 baud
  Wire.begin();           // I2C pour RDA5807M

  Serial.println("Radio Vintage démarrée !");
}

void loop() {
  // Lecture des potentiomètres
  int modeValue = analogRead(A0);     // Mode (0-1023)
  int freqValue = analogRead(A1);     // Fréquence (0-1023)

  // Affichage
  Serial.print("Mode: ");
  Serial.print(modeValue);
  Serial.print(" | Freq: ");
  Serial.println(freqValue);

  // Relais Bluetooth (exemple basique)
  if (bt.available()) {
char c = bt.read();
Serial.write(c);
  }
  if (Serial.available()) {
char c = Serial.read();
bt.write(c);
  }

  delay(100);
}
```

---

## 📞 RÉFÉRENCES UTILES

- **RDA5807M Datasheet** : I2C, adresse 0x10 ou 0x11
- **MH-M18 Datasheet** : UART 9600 baud, commandes AT
- **PAM8403 Datasheet** : Entrées analogiques single-ended
- **Arduino Pro Mini** : [https://www.arduino.cc/en/Main/ArduinoBoardProMini](https://www.arduino.cc/en/Main/ArduinoBoardProMini)
- **RK11 B103** : Potentiomètre 10kΩ linéaire, 4 broches (midpoint non utilisé)
