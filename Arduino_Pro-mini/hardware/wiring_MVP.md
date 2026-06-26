# 📋 MONTAGE ÉTAPE 1 - Arduino Pro Mini + MH-M18 + PAM8403 + 1 HP

## LÉGENDE COULEURS
- **Noir** : GND (masse)
- **Rouge** : 5V
- **Orange** : 3,6V (sortie abaisseur pour MH-M18)
- **Vert** : Signaux numériques (UART)
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
├─ (noir) ──→ GND MH-M18 (pin GND)
└─ (noir) ──→ GND commun (référence unique)
```

### Abaisseur 5V → 3,6V (MH-M18, avec 2 × 1N4007)
```
+5V (rouge)
│
└─[1N4007 n°1]─ (Anode vers 5V, Cathode vers suivant)
    │
    └─[1N4007 n°2]─ (Anode vers précédent, Cathode vers 3,6V)
        │
        ├─ (orange) ──→ VCC MH-M18
        │
        └─[Condensateur 100µF 50V]
            │
           GND (noir)
```

---

## 2️⃣ ARDUINO PRO MINI (5V, 16MHz)

### Broches utilisées
| Broche | Type    | Destination      | Couleur |
|--------|---------|------------------|---------|
| VCC    | Alim    | +5V              | Rouge   |
| GND    | Alim    | GND commun       | Noir    |
| D2     | UART RX | TX du MH-M18     | Vert    |
| D3     | UART TX | RX du MH-M18     | Vert    |

Toutes les autres broches restent **libres** à cette étape (A0/A1, A4/A5, D5, etc.).

---

## 3️⃣ MH-M18 (Module Bluetooth UART)

### Alimentation
- VCC ────(orange)──→ Ligne 3,6V (après les 2 × 1N4007)
- GND ────(noir)────→ GND commun

### Communication UART (SoftwareSerial)
- TX ─────(vert)────→ Arduino D2 (RX logiciel)
- RX ─────(vert)────→ Arduino D3 (TX logiciel)

(Pins supplémentaires type KEY/EN si présentes sur ton module : **non connectées** pour ce test simple.)

### Audio (vers PAM8403, mixage L+R simple)

On mélange les canaux L et R du MH-M18 vers un seul canal du PAM8403 via **2 résistances 10kΩ** :

- L_OUT ──(bleu)──[10kΩ]──┐
                       ├─→ L_IN+ PAM8403
- R_OUT ──(bleu)──[10kΩ]──┘

---

## 4️⃣ PAM8403 (Ampli Audio Stéréo 3W)

### Alimentation
- VCC ────(rouge)───→ +5V
- GND ────(noir)────→ GND commun

### Entrées audio (mono sur canal L uniquement)
- L_IN+ ──(bleu)────← Point de mixage MH-M18 (L_OUT + R_OUT via 2 × 10kΩ)
- L_IN- ──(noir)────→ GND commun
- R_IN+ ──(noir)────→ GND commun (canal R inutilisé, entrée forcée au repos)
- R_IN- ──(noir)────→ GND commun

### Sorties audio (vers 1 seul HP)
- L_OUT+ ──(bleu)───→ + du Haut-Parleur 8Ω
- L_OUT- ──(noir)───→ – du Haut-Parleur 8Ω
- R_OUT+ ───────────→ Non utilisé (laissez libre)
- R_OUT- ───────────→ Non utilisé (laissez libre)

---

## ✅ CHECKLIST AVANT ALIMENTATION (ÉTAPE 1)

- [ ] GND commun relie : alimentation 5V, Arduino, MH-M18, PAM8403
- [ ] Arduino Pro Mini alimenté en 5V
- [ ] PAM8403 alimenté en 5V
- [ ] MH-M18 alimenté en ~3,6V (via 2 × 1N4007 + condo 100µF 50V)
- [ ] TX/RX MH-M18 correctement croisés avec D2/D3 de l’Arduino
- [ ] L_OUT et R_OUT du MH-M18 passent bien par 2 résistances 10kΩ vers L_IN+ du PAM
- [ ] L_IN- du PAM à GND, R_IN+/R_IN- à GND
- [ ] Haut-parleur 8Ω sur L_OUT+/L_OUT- du PAM
- [ ] Pas de court-circuit visible entre 5V, 3,6V et GND

---

## 🔧 CODE DE TEST (ÉTAPE 1 : UART + Bluetooth)

Objectif :  
- Vérifier la liaison série Arduino ↔ MH-M18 (via SoftwareSerial).  
- Voir ce qui arrive du Bluetooth sur le moniteur série.  
- Tester l’audio Bluetooth directement (tu connectes ton téléphone au MH-M18 et tu écoutes sur le HP).

```cpp
#include <SoftwareSerial.h>

// SoftwareSerial pour le MH-M18 (RX=D2, TX=D3)
SoftwareSerial bt(2, 3); // RX, TX

void setup() {
  Serial.begin(9600);   // Moniteur série PC
  bt.begin(9600);       // MH-M18 à 9600 bauds (par défaut)

  Serial.println("Test ETAPE 1 : Arduino + MH-M18 + PAM8403");
  Serial.println("------------------------------------------------");
  Serial.println("1) Appaire le Bluetooth (MH-M18) avec ton téléphone.");
  Serial.println("2) Lance de la musique pour tester l'audio.");
  Serial.println("3) Tape dans le moniteur serie pour envoyer vers le MH-M18 (si mode AT).");
}

void loop() {
  // Ce qui vient du MH-M18 → PC
  if (bt.available()) {
char c = bt.read();
Serial.write(c);
  }

  // Ce qui vient du PC → MH-M18
  if (Serial.available()) {
char c = Serial.read();
bt.write(c);
  }
}
```

---

## 📌 OBJECTIF DE CETTE ÉTAPE

- Valider :
  - l’alimentation 5V,
  - l’abaisseur 5V → 3,6V pour le MH-M18,
  - la liaison UART (D2/D3 ↔ MH-M18),
  - la chaîne audio complète : MH-M18 → résistances 10kΩ → PAM8403 → HP.

Quand tout ça fonctionne proprement (Bluetooth OK, son clair dans le HP), tu pourras passer au montage complet avec le RDA5807M et les potentiomètres.
