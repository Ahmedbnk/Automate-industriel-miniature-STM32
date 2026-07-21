# Mini-PLC STM32 Configurable sans Reprogrammation

<p align="center">

**Automate Programmable Industriel Open Hardware basé sur STM32F411CEU6**

*Développé durant un stage de fin d'études chez **Tera Maroc Technologie***

</p>

<p align="center">

![Platform](https://img.shields.io/badge/Platform-STM32F411-blue?style=for-the-badge)
![Language](https://img.shields.io/badge/Language-C-success?style=for-the-badge)
![HAL](https://img.shields.io/badge/Framework-STM32_HAL-green?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen?style=for-the-badge)
![License](https://img.shields.io/badge/License-Academic-lightgrey?style=for-the-badge)

</p>

---

# Aperçu

> Un Mini-PLC configurable conçu pour rendre l'automatisation industrielle plus accessible aux PME marocaines.

Contrairement aux automates industriels classiques, cette solution permet de **modifier les seuils de fonctionnement directement par des potentiomètres**, sans logiciel propriétaire, sans ordinateur et sans reprogrammation.

L'objectif est de fournir une plateforme simple, économique et facilement déployable pour des applications industrielles légères.

---

# Sommaire

* Présentation
* Fonctionnalités
* Architecture
* Matériel
* Logiciel
* Fonctionnement
* Démonstration
* Performances
* Structure du projet
* Perspectives
* Auteur

---

# Présentation

Les automates programmables industriels offrent une excellente fiabilité mais présentent plusieurs contraintes :

* coût élevé
* logiciels propriétaires
* maintenance complexe
* nécessité d'une reprogrammation pour chaque modification

Ce projet propose une alternative basée sur un **STM32F411CEU6** permettant à l'opérateur de modifier les paramètres directement depuis la face avant de l'automate.

---

# Fonctionnalités

✔ Configuration sans reprogrammation

✔ STM32F411CEU6 Black Pill

✔ ADC 12 bits

✔ Lecture de 4 entrées analogiques

✔ Réglage par 4 potentiomètres

✔ Affichage LCD 16×2

✔ Bus I²C

✔ Commande de 4 relais

✔ Cycle déterministe de 100 ms

✔ Développement entièrement en C embarqué

---

# Architecture générale

```text
                Potentiomètres
                P0  P1  P2  P3
                     │
                     ▼
             ADC STM32F411CEU6
                     │
                     ▼
         Traitement & Comparaison
                     │
          ┌──────────┴──────────┐
          ▼                     ▼
     LCD 16×2 I²C          Module Relais
          │                     │
          ▼                     ▼
   Interface opérateur      Actionneurs
```

---

# Caractéristiques matérielles

| Élément             | Description   |
| ------------------- | ------------- |
| Microcontrôleur     | STM32F411CEU6 |
| Architecture        | ARM Cortex-M4 |
| Fréquence           | 100 MHz       |
| Flash               | 512 KB        |
| SRAM                | 128 KB        |
| ADC                 | 12 bits       |
| Entrées analogiques | 4             |
| Potentiomètres      | 4             |
| Relais              | 4 sorties     |
| Affichage           | LCD 16×2 I²C  |

---

# Outils de développement

* STM32CubeMX
* STM32CubeIDE
* STM32CubeProgrammer
* STM32 HAL
* Langage C

---

# Cycle de fonctionnement

Le système fonctionne selon un cycle fixe de **100 ms** :

```text
Lecture ADC
      │
      ▼
Conversion en %
      │
      ▼
Comparaison
      │
      ▼
Commande des relais
      │
      ▼
Mise à jour LCD
      │
      ▼
Attente 100 ms
```

---

# Démonstration

Le prototype a été validé sur une application de **gestion multi-réservoirs**.

Chaque voie comprend :

* un capteur analogique
* un seuil configurable
* une sortie relais

L'utilisateur ajuste les seuils directement grâce aux potentiomètres.

Aucune reprogrammation n'est nécessaire.

---

# Performances

| Paramètre             | Valeur      |
| --------------------- | ----------- |
| Temps de cycle        | 100 ms      |
| Rafraîchissement LCD  | Temps réel  |
| Nombre d'entrées      | 4           |
| Nombre de sorties     | 4           |
| Configuration         | Instantanée |
| Logiciel propriétaire | Aucun       |

---

# Structure du projet

```text
Mini-PLC
│
├── Core
│   ├── Inc
│   └── Src
│
├── Drivers
│
├── STM32CubeMX
│
├── Documentation
│
├── Images
│
├── Presentation
│
├── README.md
│
└── LICENSE
```

---

# Perspectives

* PCB professionnel
* Boîtier industriel
* Alimentation 24 V
* Communication Wi-Fi
* Dashboard Web
* Modbus RTU
* Modbus TCP
* SCADA
* Version industrielle

---


<p align="center">

⭐ N'hésitez pas à laisser une étoile si ce projet vous intéresse.

</p>
