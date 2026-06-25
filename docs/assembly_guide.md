# Guide d'assemblage

## 📌 Prérequis
- Tous les composants listés dans [bill_of_materials.md](bill_of_materials.md).
- Un fer à souder et de l'étain (optionnel, pour des connexions plus solides).
- Un multimètre pour vérifier les tensions.
- Un boîtier Légo pour intégrer le montage.

---

## 🛠 Étapes d'assemblage

### 1. Préparer les composants
- Vérifiez que tous les composants sont fonctionnels (testez les modules séparément si possible).
- Préparez les fils de connexion en les découpant à la bonne longueur.

### 2. Câbler l'alimentation
#### Pour l'Arduino Pro Mini :
- Connectez le **régulateur AMS1117-3.3** à l'alimentation 5V.
- Ajoutez les condensateurs **10µF** et **100nF** pour stabiliser la tension.
- Alimentez l'Arduino Pro Mini en **5V** (VCC) et le RDA5807M/MH-M18 en **3.3V**.

#### Pour l'ESP32-C3 :
- Alimentez l'ESP32-C3 en **5V** (VIN) et utilisez sa sortie **3.3V** pour alimenter le RDA5807M et le MH-M18.

### 3. Connecter les modules
- Suivez les schémas de câblage dans :
  - [Arduino_Pro-mini/hardware/wiring.md](Arduino_Pro-mini/hardware/wiring.md)
  - [ESP32-C3/hardware/wiring.md](ESP32-C3/hardware/wiring.md)
- Connectez les modules **RDA5807M**, **MH-M18** et **PAM8403** selon les tableaux.

### 4. Fixer les potentiomètres aux axes Légo
- Utilisez un **collier de serrage** ou du **ruban adhésif résistant** pour fixer les axes Légo aux potentiomètres.
- Voir la [documentation dédiée](Arduino_Pro-mini/hardware/wiring.md#fixer-les-potentiomètres) pour plus de détails.

### 5. Assembler le boîtier Légo
- Créez un support pour les composants dans le boîtier Légo.
- Percez des trous pour les potentiomètres, le haut-parleur et les LEDs.
- Fixez les composants avec de la **colle chaude** ou des **briques Légo Technic**.

### 6. Tester le montage
- Téléversez le code sur votre carte.
- Vérifiez que les potentiomètres fonctionnent correctement (utilisez le moniteur série).
- Testez la réception FM et le Bluetooth.

---

## ⚠️ Problèmes courants
- **Pas de son** : Vérifiez les connexions audio (PAM8403) et les tensions d'alimentation.
- **Potentiomètres qui ne répondent pas** : Vérifiez les connexions aux entrées analogiques.
- **Module FM qui ne fonctionne pas** : Vérifiez les connexions I2C (SDA/SCL) et l'alimentation 3.3V.
