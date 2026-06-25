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
1. Clonez le dépôt :  git clone https://github.com/pmariett/Pantasy_85048.git
2. Ouvrez le dossier de la version choisie (Arduino_Pro-mini ou ESP32-C3).
3. Ouvrez le fichier .ino dans l'Arduino IDE.
4. Compilez et téléversez le code.

---

### 📂 Documentation
- [Liste des composants](docs/bill_of_materials.md)
- [Guide d'assemblage](docs/assembly_guide.md)
- [Câblage Arduino Pro Mini](Arduino_Pro-mini/hardware/wiring.md)
- [Câblage ESP32-C3](ESP32-C3/hardware/wiring.md)

---

### Licence

Ce projet est sous licence MIT. Voir le fichier [LICENSE](LICENSE.md)
