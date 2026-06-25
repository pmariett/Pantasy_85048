# Câblage - Arduino Pro Mini (5V)

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
- **5V** : Alimente l'Arduino Pro Mini (VCC) et le PAM8403 (VCC).
- **3.3V** : Sortie du régulateur AMS1117-3.3 pour alimenter le RDA5807M et le MH-M18.

### Modules
| Module          | Broche Arduino       | Broche Module         | Couleur |
|-----------------|----------------------|-----------------------|---------|
| RDA5807M (FM)   | 3.3V                 | VCC                   | Orange  |
| RDA5807M (FM)   | GND                  | GND                   | Noir    |
| RDA5807M (FM)   | A4 (SDA)             | SDA                   | Vert    |
| RDA5807M (FM)   | A5 (SCL)             | SCL                   | Vert    |
| MH-M18 (BT)     | 3.3V                 | VCC                   | Orange  |
| MH-M18 (BT)     | GND                  | GND                   | Noir    |
| MH-M18 (BT)     | RX (Pin 0)           | TX                    | Vert    |
| MH-M18 (BT)     | TX (Pin 1)           | RX                    | Vert    |
| PAM8403 (Ampli) | 5V                   | VCC                   | Rouge   |
| PAM8403 (Ampli) | GND                  | GND                   | Noir    |
| PAM8403 (Ampli) | A0                   | LAUD+ (FM)            | Bleu    |
| PAM8403 (Ampli) | A1                   | RAUD+ (BT)            | Bleu    |
| Potentiomètre (Mode) | A2              | Signal                | Vert    |
| Potentiomètre (Fréquence) | A3          | Signal                | Vert    |
| LEDs            | D5 (PWM)             | Anode                 | Vert    |

---

## ⚠️ Notes importantes
- Utilisez un **régulateur 3.3V (AMS1117-3.3)** pour alimenter le RDA5807M et le MH-M18.
- Les broches **A4/A5** sont utilisées pour l'I2C (SDA/SCL).
- Les potentiomètres doivent être connectés à des entrées analogiques (A2/A3).
