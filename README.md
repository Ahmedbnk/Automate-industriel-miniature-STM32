#  Automate Programmable STM32 — Configurable par Potentiomètres

> **Automate programmable STM32 configurable par potentiomètres sans reprogrammation**  
> Micro-PLC industriel basé sur STM32F411 avec entrées analogiques configurables et sorties relais.

---

## 📋 Table des matières

- [Description](#-description)
- [Objectif du projet](#-objectif-du-projet)
- [Caractéristiques](#-caractéristiques)
- [Architecture matérielle](#-architecture-matérielle)
- [Matériel utilisé](#-matériel-utilisé)
- [Logiciels & Outils](#-logiciels--outils)
- [Structure du code](#-structure-du-code)
- [Installation & Configuration](#-installation--configuration)
- [Cycle d'exécution](#-cycle-dexécution)
- [Entrées / Sorties](#-entrées--sorties)
- [Fonctionnement](#-fonctionnement)
- [Roadmap](#-roadmap)
- [Auteur](#-auteur)

---

##  Description

Ce projet de **stage de fin d'études** consiste à concevoir et implémenter un **mini automate programmable (PLC)** basé sur un microcontrôleur **STM32F411** capable de :

✅ Lire **4 entrées analogiques de configuration** (potentiomètres)  
✅ Lire **3 entrées analogiques externes** à comparer contre les seuils  
✅ Exécuter une **logique de comparaison** en temps réel  
✅ Piloter **5 sorties relais** (24V / 1A)  
✅ Afficher les valeurs sur **LCD 16x2** via I2C  
✅ Cycle de **100 ms** (configurable)  

**Avantage principal** : Configuration des seuils sans reprogrammation du microcontrôleur. Les utilisateurs ajustent les potentiomètres pour modifier le comportement.

---

##  Objectif du projet

Concevoir une solution **industrielle légère** pour :

- Automatisation simple d'équipements (pompes, ventilateurs, chauffage)
- Configuration facile par l'opérateur (pas de code requis)
- Supervision locale via afficheur LCD
- Architecture modulaire et extensible (possibilité ajout Modbus RTU, SCADA)

---

##  Caractéristiques

| Feature | Détail |
|---|---|
| **Microcontrôleur** | STM32F411CEU6 (Black Pill) |
| **Horloge** | 100 MHz (HSI) |
| **ADC** | 12-bit, 7 canaux, mode DMA continu |
| **Entrées analogiques** | 7 canaux (PA0–PA3 pots + PA5–PA7 inputs) |
| **Sorties numériques** | 5 relais (PB5, PB4, PB3, PA15, PA12) |
| **Communication** | I2C (LCD 16x2 @ 400 kHz) |
| **Cycle PLC** | 100 ms (configurable) |
| **Résolution ADC** | 12-bit → 0–4095 |
| **Tension d'entrée** | 0–3.3V (analogiques) |
| **Tension relais** | 5V (contrôlé par transistor/relais) |

---

##  Architecture matérielle

```
┌──────────────────────────────────────────────────────────┐
│                    STM32F411CEU6                         │
│                     (Black Pill)                         │
│                                                          │
│   ┌────────────────┐     ┌──────────────┐               │
│   │  ADC1 (DMA)    │────▶│  Comparator  │               │
│   │  7 canaux      │     │   Logique    │               │
│   └────────────────┘     └──────────────┘               │
│        ▲                         │                       │
│        │                         ▼                       │
│        │                  ┌──────────────┐               │
│   ┌─────────┐            │  GPIO Output │               │
│   │ PA0–PA3 │◀──Pot──┐   └──────────────┘               │
│   │ PA5–PA7 │◀─Input─┤         │                        │
│   └─────────┘        │         ▼                        │
│                      │   ┌──────────────┐               │
│   ┌──────────┐       │   │ Relais (x5)  │               │
│   │ I2C (400│───LCD──┤   └──────────────┘               │
│   │  kHz)   │       │    PB5, PB4, PB3,                │
│   └──────────┘       └─→ PA15, PA12                     │
│                                                          │
└──────────────────────────────────────────────────────────┘
         │                    │
    Potentiomètres      Relais/Actionneurs
    (Seuils)           (Charge 24V / 1A)
```

---

##  Matériel utilisé

| Composant | Référence | Rôle | Quantité |
|---|---|---|---|
| Microcontrôleur | STM32F411CEU6 | CPU principal | 1 |
| Programmateur | STLINK-V2/V3 | Flash & Debug | 1 |
| Potentiomètre | 10kΩ pot lin. | Entrées config | 4 |
| Capteur analogique | 4–20mA / 0–10V | Entrées mesure | 3 |
| Relais module | SRD-05VDC-SL-C | Sorties | 5 |
| Afficheur | LCD 16x2 + PCF8574 | HMI local | 1 |
| Résistances | 10kΩ pull-up | I2C / GPIO | 8 |
| Condensateurs | 100nF (découp.) | Alimentation | 5 |
| Convertisseur | AMS1117-3.3V | Régul. 3.3V | 1 |

---

##  Logiciels & Outils

- **STM32CubeIDE** — IDE de développement (C)
- **STM32CubeMX** — Configurateur périphériques (GPIO, ADC, DMA, I2C)
- **OpenOCD / GDB** — Débogage & monitoring
- **UART Terminal** — Supervision série (optionnel)
- **Git** — Versioning

---

## 📁 Structure du code

```
STM32_Automate/
│
├── Core/
│   ├── Inc/
│   │   ├── main.h
│   │   ├── stm32f4xx_it.h       # Interruptions
│   │   └── [...autres headers]
│   │
│   └── Src/
│       ├── main.c               # Boucle principale + logique relais
│       ├── stm32f4xx_it.c       # Interruptions
│       └── stm32f4xx_hal_msp.c  # Initialisation MSP
│
├── Drivers/
│   └── STM32F4xx_HAL_Driver/    # HAL généré par CubeMX
│
├── Middlewares/
│   └── liquidcrystal_i2c/       # Pilote LCD I2C
│
├── .ioc                         # Config CubeMX
├── .project
├── STM32F411CCUx_FLASH.ld       # Linker script
│
└── README.md
```

---

## ⚙️ Installation & Configuration

### 1. Prérequis

- **STM32CubeIDE** (dernière version)
- **STM32CubeMX** (pour régénérer config si besoin)
- Carte **STM32F411 Black Pill**
- Programmateur **STLINK-V2/V3**

### 2. Cloner / Importer le projet

```bash
# Cloner (si sur Git)
git clone <repo-url> STM32_Automate
cd STM32_Automate
```

Ou importer directement dans **STM32CubeIDE** :
```
File → Import → Existing Projects into Workspace
→ Sélectionner dossier du projet
```

### 3. Configuration CubeMX (si modification requise)

Ouvrir `projet.ioc` avec STM32CubeMX :

**ADC1 Configuration :**
- Mode Scan + Continuous
- DMA Mode : Circular
- 7 canaux : CH0–3 (pots), CH5–7 (inputs)
- Résolution : 12-bit
- Data Alignment : **RIGHT**

**GPIO Configuration :**
- PA0–PA3, PA5–PA7 : Analogic Input
- PB5, PB4, PB3, PA15, PA12 : GPIO Output
- PB6, PB7 : I2C1 (SCL, SDA)

**I2C1 Configuration :**
- Speed Mode : Fast (400 kHz)

Puis : **Generate Code** (Ctrl+Shift+G)

### 4. Compiler & Flasher

```bash
# Build
Project → Build All (Ctrl+B)

# Flash
Run → Debug (F11)
# ou
Run → Run as STM32 Cortex-M Application
```

---

## 🔄 Cycle d'exécution

```
┌─────────────────────────────────────┐
│  Boucle principale (100 ms)         │
├─────────────────────────────────────┤
│ 1. Lire ADC (DMA continu)           │
│    adc_values[0–3] = seuils         │
│    adc_values[4–6] = entrées        │
│                                     │
│ 2. Comparer & Décider               │
│    if (input > seuil) → relay ON    │
│                                     │
│ 3. Écrire sorties GPIO              │
│    HAL_GPIO_WritePin()              │
│                                     │
│ 4. Afficher LCD                     │
│    itoa(adc_values[0])              │
│                                     │
│ 5. HAL_Delay(100 ms)                │
└─────────────────────────────────────┘
```

**Code simplifié :**

```c
while (1) {
    /* ADC reading via DMA (automatic) */
    
    /* Relay logic */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 
        (adc_values[4] > adc_values[0]) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    
    /* LCD Display */
    char buffer[20];
    itoa(adc_values[0], buffer, 10);
    HD44780_SetCursor(0, 0);
    HD44780_PrintStr(buffer);
    
    HAL_Delay(100);
}
```

---

##  Entrées / Sorties

### Mapping GPIO

| Broche | Type | Rôle | Description |
|---|---|---|---|
| **PA0** | ADC_CH0 | Potentiomètre 1 | Seuil Entrée 1 |
| **PA1** | ADC_CH1 | Potentiomètre 2 | Seuil Entrée 2 |
| **PA2** | ADC_CH2 | Potentiomètre 3 | Seuil Entrée 3 |
| **PA3** | ADC_CH3 | Potentiomètre 4 | Seuil Relais 4 |
| **PA5** | ADC_CH5 | Entrée analogique 1 | Capteur / Signal |
| **PA6** | ADC_CH6 | Entrée analogique 2 | Capteur / Signal |
| **PA7** | ADC_CH7 | Entrée analogique 3 | Capteur / Signal |
| **PB5** | GPIO_Out | Relais 1 | Sortie 1 (24V) |
| **PB4** | GPIO_Out | Relais 2 | Sortie 2 (24V) |
| **PB3** | GPIO_Out | Relais 3 | Sortie 3 (24V) |
| **PA15** | GPIO_Out | Relais 4 | Sortie 4 (24V) |
| **PA12** | GPIO_Out | Relais 5 | Sortie 5 (24V) |
| **PB6** | I2C1_SCL | LCD I2C | Afficheur 16x2 |
| **PB7** | I2C1_SDA | LCD I2C | Afficheur 16x2 |

### Valeurs ADC

| Niveau | Tension | Valeur 12-bit |
|---|---|---|
| Bas (LOW) | 0V | 0 |
| Moyen (MID) | 1.65V | ~2048 |
| Haut (HIGH) | 3.3V | 4095 |

### Logique de contrôle

```
Relay 1 (PB5) :  if (Input_A5 > Threshold_A0) then ON else OFF
Relay 2 (PB4) :  if (Input_A6 > Threshold_A1) then ON else OFF
Relay 3 (PB3) :  if (Input_A7 > Threshold_A2) then ON else OFF
Relay 4 (PA15) : if (Threshold_A3 > 2048)     then ON else OFF
Relay 5 (PA12) : (Non utilisé / Réservé)
```

---

##  Fonctionnement

### Phase de démarrage

1. **Initialisation STM32** → RCC, GPIO, ADC, DMA, I2C
2. **Démarrage ADC+DMA** → Lecture continue des 7 canaux
3. **Init LCD** → Effacement, affichage message démarrage
4. **Boucle principale** → Cycle 100 ms

### Ajustement des seuils

1. **Tourner potentiomètre** → Valeur seuil change (PA0–PA3)
2. **ADC lit en temps réel** → Mise à jour dans `adc_values[]`
3. **Logique compare** → Relais commute automatiquement
4. **LCD affiche** → Valeur actuelle visible

**Exemple :**
- Pot A0 = 2500 (50% de 5000)
- Entrée A5 = 3000 (60% de 5000)
- Résultat : 3000 > 2500 → **Relay 1 = ON** ✅

---

## 🗺️ Roadmap

### Phase 1 ✅ (En cours)
- [x] Configuration CubeMX (GPIO, ADC, DMA, I2C)
- [x] Lecture ADC 7 canaux
- [x] Logique comparaison & relais
- [x] Affichage LCD
- [x] Cycle 100 ms

### Phase 2 (Optionnel)
- [ ] UART Debug (monitoring en temps réel)
- [ ] Modbus RTU RS485 (supervision PC)
- [ ] Sauvegarde configurations en EEPROM
- [ ] Menu LCD (ajustement via boutons)

### Phase 3 (Futur)
- [ ] Blocs IEC 61131-3 (TON, CTU, SR...)
- [ ] Interpréteur Ladder
- [ ] Dashboard SCADA web
- [ ] Historique données (SD card)

---

##  Tests & Validation

### Test 1 : Vérifier ADC

```
Connecter potentiomètre PA0 à 0V → adc_values[0] = 0
Connecter potentiomètre PA0 à 3.3V → adc_values[0] = 4095
```

### Test 2 : Vérifier comparaison

```
Pot A0 = 2000, Entrée A5 = 1500 → Relay OFF
Pot A0 = 2000, Entrée A5 = 3000 → Relay ON
```

### Test 3 : Affichage LCD

```
LCD doit afficher valeur ADC_CH0 en temps réel
Test rotation potentiomètre → chiffres changent
```

---

## 👤 Auteur

**BENKRARA AHMED**  
Stagiaire — Systèmes Embarqués & Électronique Industrielle  

**Superviseurs** :  
- [ILCHHAB OUSSAMA] — Tera Maroc Technologie

**Établissements** :  
- Tera Maroc Technologie — Chichaoua, Maroc
- EST Salé — Superviseur académique

**Année académique** : 2025–2026

---

##  Remerciements

Merci à :
- **Tera Maroc Technologie** pour l'accueil et les ressources
- **EST Salé** pour l'supervision académique
- Tous les contributeurs et testeurs

---

## 📄 Licence

Ce projet est développé dans le cadre d'un stage académique.  
© 2026 — Tous droits réservés.

---

**Notes techniques** :
- Plateforme cible : STM32F411CEU6 (Black Pill)
- Langage : C (STM32 HAL)
- IDE : STM32CubeIDE 1.13+
