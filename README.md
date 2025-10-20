# DIY Flight Simulator Controller PCB

This repository contains the arduino .ino code base and the Gerber files for the custom PCB designed for the "Build Your Own Low-Cost, Extensible Flight Sim Controller" project.

**Find the complete build guide, 3D-printable files, and software setup instructions on Instructables:**
**[https://www.instructables.com/Build-Your-Own-Low-Cost-Extensible-Flight-Sim-Cont/](https://www.instructables.com/Build-Your-Own-Low-Cost-Extensible-Flight-Sim-Cont/)**

## About This Project

This project, is about a fully DIY flight simulator yoke and rudder system. It is designed to be low-cost, 3D-printable, and extensible. The system uses an Arduino Nano and potentiometers to read control inputs.

### Key Features
* **Low-Cost:** Built with common components and 3D-printed parts.
* **Extensible:** The design allows for adding more controls like levers for throttle, flaps, and more.
* **Flexible Software:** Can be used with:
    * **native HID of Arduino Pro Micro
    * **MobiFlight:** For a direct interface with MSFS 2020.
    * **vJoy & vJoySerialFeeder:** To act as a standard virtual joystick for any game.
* **Custom PCB:** This simple PCB makes wiring the components clean and reliable.

## About This Repository

This repository holds the arduino .ino code base and the PCB design files (**Gerber files**) for the controller's main connection board. This board is not the microcontroller itself, but rather a "shield" or breakout board for an **Arduino Micro Pro**.

### PCB Purpose
The PCB is designed to simplify the wiring process. It provides a clean way to connect:
* An **Arduino Micro Pro** (or compatible clone).
* **5 Analog Inputs:** For potentiometers (e.g., yoke pitch, yoke roll, throttle, flaps, rudder).
* **5 Digital Inputs:** For pushbuttons (with built-in pulldown resistors).

### Files
* `Pro_Micro_Rudder_v1_0_4` / `flight_yoke_micro_pro`: the arduino Pro Micro .ino code base.
* `*.zip`: These zip archives (e.g., `Flight Yoke v3-.zip`) contain the ready-to-use Gerber files for ordering.

## How to Use

1.  **Download the Gerber Files:** Grab the latest `.zip` file from this repository.
2.  **Order the PCB:** Upload the zip file to a PCB manufacturer (like [JLCPCB](https://jlcpcb.com), [PCBWay](https://www.pcbway.com), etc.) to order your boards. They are typically very inexpensive.
3.  **Get Build Instructions:** Go to the [Instructables project page](https://www.instructables.com/Build-Your-Own-Low-Cost-Extensible-Flight-Sim-Cont/) for the full list of components (potentiometers, 3D printer filament, Arduino Nano, etc.), 3D models (`.stl` files), and detailed assembly and software setup guides.

## Disclaimer

These files are provided as-is. Use them at your own risk.
