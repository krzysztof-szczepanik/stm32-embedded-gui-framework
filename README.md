# STM32 Embedded GUI Framework

<br>

## 📖 Description
STM32 Embedded GUI Framework is a lightweight and modular GUI framework designed for embedded systems based on STM32 microcontrollers.

The project focuses on simplicity, performance, and clean architecture, making it suitable for low-level embedded development without relying on heavy external libraries.

It provides a structured way to build graphical user interfaces, handle rendering, and separate hardware-specific code from higher-level UI logic.

<br>

---

## ✨ Features
- Layered architecture: **UI / Render / Hardware**
- Clear separation between logic and hardware
- Easy to extend and customize
- Basic input support: joystick handling

<br>

---

## 🏗️ Project Structure
```
Core/
├─ Inc/
│  ├─ HW/        # Hardware abstraction layer
│  ├─ Render/    # Rendering interfaces
│  └─ UI/        # UI components and interfaces
│
└─ Src/
   ├─ HW/        # Hardware-specific code
   ├─ Render/    # Rendering implementation
   └─ UI/        # UI implementation
```

<br>

The project is divided into logical layers:
- **HW** - low-level hardware interaction  
- **Render** - drawing and graphics handling  
- **UI** - high-level user interface elements
