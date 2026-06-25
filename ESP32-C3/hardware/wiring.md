# Câblage - ESP32-C3 (3.3V)

## 📌 Légende des couleurs
| Couleur | Description                     |
|---------|---------------------------------|
| Noir    | GND (masse)                     |
| Rouge   | 5V (alimentation)               |
| Orange  | 3.3V (alimentation modules)     |
| Vert    | Signaux numériques/analogiques  |
| Bleu    | Signaux audio                   |

---

## 🔌 Schéma de câblage

### Alimentation
- **5V** : Alimente l'ESP32-C3 (VIN) et le PAM8403 (VCC).
- **3.3V** : Sortie de l'ESP32-C3 pour alimenter le RDA5807M et le MH-M18.

### Modules
| Module          | Broche ESP32-C3      | Broche Module         | Couleur |
|-----------------|----------------------|-----------------------|---------|
| RDA5807M (FM)   | 3.3V                 | VCC                   | Orange  |
| RDA5807M (FM)   | GND                  | GND                   | Noir    |
| RDA5807M (FM)   | GPIO 8 (SDA)         | SDA                   | Vert    |
| RDA5807M (FM)   | GPIO 9 (SCL)         | SCL                   | Vert    |
| MH-M18 (BT)     | 3.3V                 | VCC                   | Orange  |
| MH-M18 (BT)     | GND                  | GND                   | Noir    |
| MH-M18 (BT)     | GPIO 10 (TX)         | RX                    | Vert    |
| MH-M18 (BT)     | GPIO 11 (RX)         | TX                    | Vert    |
| PAM8403 (Ampli) | 5V                   | VCC                   | Rouge   |
| PAM8403 (Ampli) | GND                  | GND                   | Noir    |
| PAM8403 (Ampli) | GPIO 0 (A0)          | LAUD+ (FM)            | Bleu    |
| PAM8403 (Ampli) | GPIO 1 (A1)          | RAUD+ (BT)            | Bleu    |
| Potentiomètre (Mode) | GPIO 2 (A2)     | Signal                | Vert    |
| Potentiomètre (Fréquence) | GPIO 3 (A3) | Signal                | Vert    |
| LEDs            | GPIO 4 (PWM)         | Anode                 | Vert    |

---

## ⚠️ Notes importantes
- L'ESP32-C3 fonctionne en **3.3V natif** : pas besoin de régulateur pour le RDA5807M.
- Les broches **GPIO 8/9** sont utilisées pour l'I2C (SDA/SCL).
- Les potentiomètres doivent être connectés à des entrées analogiques (GPIO 2/3).
