#  Mini Automate Programmable — STM32

> Implémentation d'un automate programmable industriel (PLC) basé sur un microcontrôleur STM32, conforme à la norme **IEC 61131-3**.

---

## Table des matières

- [Description](#-description)
- [Architecture](#-architecture)
- [Matériel requis](#-matériel-requis)
- [Logiciels & Outils](#-logiciels--outils)
- [Structure du projet](#-structure-du-projet)
- [Installation](#-installation)
- [Cycle automate](#-cycle-automate)
- [Entrées / Sorties](#-entrées--sorties)
- [Communication Modbus RTU](#-communication-modbus-rtu)
- [Langages PLC supportés](#-langages-plc-supportés)
- [Roadmap](#-roadmap)
- [Auteur](#-auteur)

---

##  Description

Ce projet est réalisé dans le cadre d'un **stage de fin d'études**. Il consiste à concevoir et implémenter un mini automate programmable industriel (PLC) à base de **STM32**, capable de :

- Lire des **entrées TOR et analogiques**
- Exécuter un **programme Ladder** (IEC 61131-3)
- Piloter des **sorties TOR** (relais, actionneurs)
- Communiquer via **Modbus RTU** (RS485)
- Offrir une supervision via **interface série PC**

---

##  Architecture

```
┌─────────────────────────────────────────────────┐
│                   STM32Fxxx                     │
│                                                 │
│  ┌──────────┐   ┌──────────┐   ┌────────────┐  │
│  │ Lecture  │──▶│  Moteur  │──▶│  Écriture  │  │
│  │ Entrées  │   │  Ladder  │   │  Sorties   │  │
│  └──────────┘   └──────────┘   └────────────┘  │
│       │              │               │          │
│  8x TOR IN      PIL / POL        8x TOR OUT     │
│  4x ANA IN      Blocs IEC         Relais/LEDs   │
│                                                 │
│  ┌──────────────────────────────────────────┐   │
│  │         Communication UART               │   │
│  │    Modbus RTU (RS485 / MAX485)           │   │
│  └──────────────────────────────────────────┘   │
└─────────────────────────────────────────────────┘
         │                         │
    PC Superviseur            ESP32 (optionnel)
    (SCADA / Terminal)        WiFi / Dashboard Web
```

---

##  Matériel requis

| Composant | Référence | Rôle |
|---|---|---|
| Microcontrôleur | STM32F401 / STM32G474 | CPU principal |
| Programmateur | STLINK-V2 / V3 | Flash + debug |
| Pilote RS485 | MAX485 / SP485 | Interface Modbus |
| Isolation optique | PC817 / TLP627 | Protection 24V |
| Driver sortie | ULN2003 / ULN2803 | Pilotage relais |
| Relais | SRD-05VDC | Sorties puissance |
| Convertisseur | AMS1117-3.3 | Alimentation 3.3V |
| Afficheur (opt.) | LCD 16x2 / OLED 128x64 | HMI local |

---

##  Logiciels & Outils

- **STM32CubeIDE** — IDE principal (C/C++)
- **STM32CubeMX** — Configuration des périphériques (GPIO, Timer, ADC, UART)
- **OpenOCD / STLINK GDB** — Débogage
- **KiCad / EasyEDA** — Schémas électroniques & PCB
- **Modbus Poll** — Test Modbus RTU côté PC
- **Unity** — Framework de tests unitaires C

---

## 📁 Structure du projet

```
mini-plc-stm32/
│
├── Core/
│   ├── Inc/
│   │   ├── plc_engine.h        # Moteur d'exécution PLC
│   │   ├── plc_io.h            # Gestion entrées/sorties
│   │   ├── plc_ladder.h        # Interpréteur Ladder
│   │   ├── plc_blocks.h        # Blocs IEC 61131-3 (TON, CTU...)
│   │   └── modbus_rtu.h        # Driver Modbus RTU
│   │
│   └── Src/
│       ├── main.c
│       ├── plc_engine.c
│       ├── plc_io.c
│       ├── plc_ladder.c
│       ├── plc_blocks.c
│       └── modbus_rtu.c
│
├── Drivers/                    # HAL STM32 (généré par CubeMX)
├── Tests/                      # Tests unitaires Unity
├── Docs/
│   ├── schéma_électronique.pdf
│   ├── architecture.md
│   └── rapport_stage.pdf
│
├── .ioc                        # Fichier config CubeMX
├── .gitignore
└── README.md
```

---

## ⚙️ Installation

### 1. Cloner le dépôt

```bash
git clone git@github.com:Ahmedbnk/Automate-industriel-miniature-bas-sur-microcontr-leur-STM32.git PLC
cd PLC
```

### 2. Ouvrir dans STM32CubeIDE

```
File → Import → Existing Projects into Workspace
→ Sélectionner le dossier mini-plc-stm32
```

### 3. Configurer les périphériques (si besoin)

Ouvrir `projet.ioc` avec **STM32CubeMX** pour régénérer le code HAL selon votre carte cible.

### 4. Compiler et flasher

```
Project → Build All (Ctrl+B)
Run → Debug / Run As → STM32 Cortex-M C/C++ Application
```

---

## 🔄 Cycle automate

Le cycle PLC s'exécute toutes les **10 ms** via une interruption Timer :

```c
// Cycle automate principal (appelé par TIM2 IRQ toutes les 10ms)
void PLC_CycleTask(void) {
    PLC_ReadInputs();      // 1. Lecture image entrées (PIL)
    PLC_ExecuteLadder();   // 2. Exécution programme Ladder
    PLC_WriteOutputs();    // 3. Écriture image sorties (POL)
    PLC_UpdateModbus();    // 4. Mise à jour registres Modbus
}
```

---

##  Entrées / Sorties

### Mapping GPIO

| Broche STM32 | Type | Description |
|---|---|---|
| PA0 – PA7 | Entrée TOR | 8 entrées numériques (optocouplées) |
| PB0 – PB7 | Sortie TOR | 8 sorties relais / transistor |
| PC0 – PC3 | Entrée ANA | 4 entrées analogiques ADC 12-bit |
| PA9 / PA10 | UART1 TX/RX | Debug + Modbus RS485 |
| PB6 / PB7 | UART1 (alt) | Interface série PC |

### Niveaux logiques

| Niveau | Tension | État |
|---|---|---|
| Entrée HIGH | 5V – 24V | 1 logique |
| Entrée LOW | 0V – 1V | 0 logique |
| Sortie active | VCC relais | Contact fermé |

---

##  Communication Modbus RTU

- **Interface physique** : RS485 half-duplex (MAX485)
- **Débit** : 9600 / 19200 / 115200 bauds (configurable)
- **Adresse esclave** : 0x01 (modifiable)

### Registres disponibles

| Type | Adresse | Description |
|---|---|---|
| Discrete Inputs (1x) | 0x0000 – 0x0007 | 8 entrées TOR |
| Coils (0x) | 0x0000 – 0x0007 | 8 sorties TOR |
| Input Registers (3x) | 0x0000 – 0x0003 | 4 entrées analogiques |
| Holding Registers (4x) | 0x0000 – 0x00FF | Variables internes PLC |

### Fonctions Modbus supportées

- `0x01` — Read Coils
- `0x02` — Read Discrete Inputs
- `0x03` — Read Holding Registers
- `0x04` — Read Input Registers
- `0x05` — Write Single Coil
- `0x06` — Write Single Register
- `0x10` — Write Multiple Registers

---

##  Langages PLC supportés

### Ladder Diagram (LD)

```
|----[ I0.0 ]----[/I0.1]----( Q0.0 )----|
|                                        |
|----[ I0.2 ]---+---( TON T1 100ms )----| 
|               |                        |
|         [T1.Q]+-----------( Q0.1 )----|
```

### Blocs IEC 61131-3 implémentés

| Bloc | Fonction |
|---|---|
| `TON` | Temporisation à l'enclenchement |
| `TOF` | Temporisation au déclenchement |
| `TP` | Impulsion temporisée |
| `CTU` | Compteur incrémental |
| `CTD` | Compteur décrémental |
| `SR` | Bascule Set/Reset |
| `RS` | Bascule Reset/Set |

---

## 🗺️ Roadmap

- [x] Phase 1 — Prise en main STM32 (GPIO, Timer, UART)
- [x] Phase 2 — Couche I/O (8 TOR IN + 8 TOR OUT + ADC)
- [ ] Phase 3 — Moteur d'exécution PLC + interpréteur Ladder
- [ ] Phase 4 — Modbus RTU RS485
- [ ] Phase 5 — Tests & validation
- [ ] Phase 6 — Documentation finale + soutenance

---

## 👤 Auteur

**[BENKRARA AHMED]**  
Stagiaire — Systèmes Embarqués  
Encadrant : [ILCHHAB OUSSAMA] · [TERAMAROC TECHNOLOGIE / EST Salé]  
Année : 2025–2026

---

## 📄 Licence

Ce projet est développé dans un cadre académique (stage).  
© 2026 — Tous droits réservés.
