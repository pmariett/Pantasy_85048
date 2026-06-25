# Radio Vintage Légo
Un projet de radio FM/Bluetooth intégrée dans un boîtier Légo (inspiré du set Pantasy 85048), avec deux versions :
- **Arduino Pro Mini** (5V)
- **ESP32-C3** (3.3V natif)

---

## Structure du projet
| Dossier          | Description                                                                 |
|------------------|-----------------------------------------------------------------------------|
| `Arduino_Pro-mini/` | Code et ressources pour la version Arduino Pro Mini (5V).                  |
| `ESP32-C3/`         | Code et ressources pour la version ESP32-C3 (3.3V).                        |
| `docs/`             | Documentation générale (liste des composants, guide d'assemblage).        |

---

## Prérequis
### Matériel
- **Pour Arduino Pro Mini** :
  - Arduino Pro Mini (5V, 16MHz)
  - Module RDA5807M (FM)
  - Module Bluetooth MH-M18
  - Ampli PAM8403
  - Potentiomètres 10kΩ (x2)
  - Régulateur 3.3V (AMS1117-3.3)
  - Haut-parleur 8Ω

- **Pour ESP32-C3** :
  - ESP32-C3
  - Module RDA5807M (FM)
  - Module Bluetooth MH-M18
  - Ampli PAM8403
  - Potentiomètres 10kΩ (x2)
  - Haut-parleur 8Ω

### Logiciel
- [Arduino IDE](https://www.arduino.cc/en/software)
- [ESP32 Core pour Arduino](https://github.com/espressif/arduino-esp32) (pour l'ESP32-C3)

---

## Installation
1. Clonez le dépôt :
   ```bash
   git clone https://github.com/votre-utilisateur/radio_vintage_lego.git
