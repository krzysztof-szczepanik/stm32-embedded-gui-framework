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

<br>

---

## 🚀 Getting Started

### Requirements
- STM32CubeIDE
- STM32F429I-DISC1 board (or compatible hardware)

<br>

### Setup
1. Get the project:
   - **Option 1: Download ZIP** - click the Code → Download ZIP button on GitHub, then extract it to a folder.

   - **Option 2: Clone the repository (requires Git)**
     \code{.bash}
     git clone https://github.com/krzysztof-szczepanik/stm32-embedded-gui-framework.git
     \endcode
     
3. Open STM32CubeIDE.

4. Import the project:
   - Go to **File → Open Projects from File System**
   - Select the cloned repository folder
   - Click **Finish**

5. Build the project.

6. Flash it to the board.

<br>

### Notes
- The project already contains a working built-in example (**washing machine controller**).
- It is designed as a complete framework, not a standalone library.
- Porting to other hardware may require changes in the **HW layer**.

<br>

---

## 🎬 Demo

Demonstration of the framework running on the **STM32F429I-DISC1** board, using the built-in example (**washing machine controller**).

<br>

<div align="center">

\htmlonly
<video controls style="max-width: 100%; height: auto;">
  <source src="demo.mp4" type="video/mp4">
</video>
\endhtmlonly

</div>

<br>

---

## 🖥️ UI Screens

Example screens available in the project:

<br>

<div align="center">
    <table>
        <tr>
            <td align="center"><strong>Modes Screen</strong></td>
            <td align="center"><strong>Main Screen</strong></td>
            <td align="center"><strong>Settings Screen</strong></td>
        </tr>
        <tr>
            <td><img src="modes_screen.jpg" alt="Modes Screen" style="max-height: 420px; height: auto; width: auto;" /></td>
            <td><img src="main_screen.jpg" alt="Main Screen" style="max-height: 420px; height: auto; width: auto;" /></td>
            <td><img src="settings_screen.jpg" alt="Settings Screen" style="max-height: 420px; height: auto; width: auto;" /></td>
        </tr>
    </table>
</div>

<br>

---

## ⚙️ Hardware Setup

This project uses a **Thumb Joystick with button v2** (Iduino ST1079) as the primary input device for navigating the UI.

<br>

<div align="center">
    <table>
        <tr>
            <td align="center"><strong>Connection Overview</strong></td>
            <td align="center"><strong>Joystick Overview</strong></td>
        </tr>
        <tr>
            <td><img src="hardware.jpg" alt="Hardware" style="max-height: 460px; height: auto; width: auto;" /></td>
            <td><img src="joystick.jpg" alt="Joystick" style="max-height: 460px; height: auto; width: auto;" /></td>
        </tr>
    </table>
</div>

<br>

The joystick connects to the **STM32F429I-DISC1** board via a breadboard, which allows for easy prototyping. This setup allows analog reading for X/Y axes and digital read for the button press.

<br>

<div align="center">

**Joystick Pin Mapping**

<table>
    <tr align="center">
        <th>
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
            Joystick Pin
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
        </th>
        <th>
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
            STM32 Pin
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
        </th>
        <th>
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
            Notes
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
        </th>
    </tr>
    <tr align="center">
        <td>GND</td>
        <td>GND</td>
        <td>Ground</td>
    </tr>
    <tr align="center">
        <td>+5V</td>
        <td>+3V</td>
        <td>Joystick power supply</td>
    </tr>
    <tr align="center">
        <td>VRx</td>
        <td>PC1 (ADC1_IN11)</td>
        <td>X-axis (analog read)</td>
    </tr>
    <tr align="center">
        <td>VRy</td>
        <td>PC2 (ADC1_IN12)</td>
        <td>Y-axis (analog read)</td>
    </tr>
    <tr align="center">
        <td>SW</td>
        <td>PC3</td>
        <td>Button press</td>
    </tr>
</table>

</div>

<br>

### Notes
- Make sure to provide power to the joystick (+3V on the board, not +5V).  
- This setup corresponds to the **washing machine controller example** included in the project, which can be run directly on the **STM32F429I-DISC1** board.

<br>

---

## 🤝 Contributing
This project is not actively maintained, but you are welcome to fork it for personal use or experimentation.

<br>

---

## 📄 License
This project is released under the **MIT License**. See the [LICENSE](https://github.com/krzysztof-szczepanik/stm32-embedded-gui-framework/blob/main/LICENSE) file for full details.

<br>

You are free to:
- Use, copy, and modify the code for personal or commercial projects.
- Distribute and sublicense your modifications.

<br>

You must:  
- Include the original license and copyright notice in your distributed code.

<br>

> Including a license in your project is important because it tells others exactly what they **can and cannot do** with your code, protecting both you and anyone who wants to use it.
