# Mini-PLC STM32 Configurable

> A low-cost configurable Programmable Logic Controller (PLC) based on the STM32F411CEU6, designed for industrial automation without firmware reprogramming.

![Mini-PLC](docs/images/cover.png)

---

## 📖 Overview

This project was developed during my **Bachelor's End-of-Studies Internship** at **Tera Maroc Technologie**.

The objective was to design and implement a **configurable Mini-PLC** capable of replacing expensive industrial PLCs for small automation applications.

Unlike conventional PLCs, this system allows the operator to modify control thresholds **directly using physical potentiometers**, eliminating the need for proprietary software, programming cables, or firmware updates.

The solution is mainly intended for **Moroccan SMEs, agricultural automation, and light industrial applications**.

---

# ✨ Features

- ⚙️ STM32F411CEU6 (Black Pill)
- 🎛 4 configurable potentiometers (P0–P3)
- 📥 4 analog inputs (I0–I3)
- 📤 4 relay outputs
- 📺 LCD 16×2 (I2C)
- ⏱ 100 ms deterministic control cycle
- 🔄 Configuration without firmware reprogramming
- 💰 Low hardware cost
- 🆓 No proprietary software licenses

---

# 🛠 Hardware

| Component | Quantity |
|------------|----------|
| STM32F411CEU6 Black Pill | 1 |
| LCD 16×2 I2C | 1 |
| Potentiometers | 4 |
| Analog Inputs | 4 |
| HW-482 Relay Module | 4 |
| Breadboard | 1 |
| Power Supply | 5V |

---

# 🏗 System Architecture

```text
        Potentiometers (P0-P3)
                 │
                 ▼
          STM32 ADC (12-bit)
                 │
                 ▼
        Processing & Decision
                 │
        ┌────────┴────────┐
        ▼                 ▼
   LCD Display       Relay Outputs
                         │
                         ▼
                  External Loads
```

---

# 📺 LCD Interface

The LCD continuously displays the configured thresholds and the measured input values.

```text
Automate STM32

P0:96%   I0:74%
P1:80%   I1:61%
```

Where:

- **P** → Potentiometer value
- **I** → Analog input value

---

# ⚙️ Operating Principle

Every **100 milliseconds**, the firmware executes the following sequence:

1. Read the 4 potentiometers.
2. Read the 4 analog inputs.
3. Convert ADC values into percentages.
4. Compare sensor values with configured thresholds.
5. Switch the corresponding relay ON or OFF.
6. Refresh the LCD display.

This deterministic execution guarantees stable real-time operation.

---

# 💡 Innovation

Traditional industrial PLCs require:

- Proprietary software
- Programming cable
- Laptop
- Firmware modification
- System downtime

With this Mini-PLC:

✔ The operator simply turns a potentiometer.

The new threshold is immediately applied without stopping the system.

---

# 💰 Cost Comparison

| Mini-PLC | Industrial PLC |
|-----------|----------------|
| < 250 MAD | €5000 – €10000 |
| Free software | €800 – €1600 licenses |
| Instant configuration | Firmware reprogramming |
| No maintenance software | Proprietary ecosystem |

---

# 🧪 Demonstration Application

The prototype has been validated using a **multi-water-reservoir management system**.

Each channel consists of:

- One analog sensor
- One configurable threshold
- One relay output

The operator can adjust each threshold directly from the front panel while the system continues running.

---

# 🚀 Future Improvements

- Custom PCB
- DIN-Rail enclosure
- Wi-Fi connectivity
- Web Dashboard
- Cloud Monitoring
- Modbus RTU / TCP
- SCADA integration
- Industrial enclosure

---

# 🧰 Development Tools

- STM32CubeMX
- STM32CubeIDE
- STM32CubeProgrammer
- HAL Drivers
- Embedded C

---

# 👨‍💻 Author

**Ahmed BENKRARA**

Bachelor's End-of-Studies Internship

**Tera Maroc Technologie**

École Supérieure de Technologie de Salé

Université Mohammed V de Rabat

Academic Year **2025–2026**

---

# 📄 License

This project was developed for academic and educational purposes as part of a Bachelor's end-of-studies internship.
