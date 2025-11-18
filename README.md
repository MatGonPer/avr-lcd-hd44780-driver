# AVR HD44780 LCD Driver (4-Bit Mode)

A lightweight, bare-metal C driver for 16x2 LCD displays based on the Hitachi HD44780 controller. Optimized for **AVR microcontrollers** (specifically the ATmega328P used on the Arduino Uno).

This library is written in **Pure C** (AVR-GCC) without dependencies on the Arduino framework (`wiring`, `LiquidCrystal`, etc.). It operates the LCD in **4-bit mode** to save GPIO pins and implements the specific initialization timing sequence required by the datasheet.

## Features

* **Zero Dependencies:** Pure C implementation using `avr-libc`.
* **Pin Efficient:** Uses 4-bit mode (requires only 6 GPIO pins total).
* **Lightweight:** Direct port manipulation for minimal Flash/RAM usage.
* **Structured:** Clean separation between API (`.h`) and Implementation (`.c`).

---

## 🔌 Hardware Setup (Wiring)

This driver uses a specific pin mapping optimized for the ATmega328P port registers. Please follow the wiring below carefully.

### Pin Mapping Table

| LCD Pin | Name | Function | Connect to Arduino Pin | AVR Pin |
| :--- | :--- | :--- | :--- | :--- |
| 1 | **VSS** | Ground | **GND** | - |
| 2 | **VDD** | Power (5V) | **5V** | - |
| 3 | **V0** | Contrast | **Potentiometer Center** | - |
| 4 | **RS** | Register Select | **Digital 8** | `PB0` |
| 5 | **RW** | Read/Write | **GND** | - |
| 6 | **E** | Enable | **Digital 9** | `PB1` |
| 11 | **D4** | Data 4 | **Digital 4** | `PD4` |
| 12 | **D5** | Data 5 | **Digital 5** | `PD5` |
| 13 | **D6** | Data 6 | **Digital 6** | `PD6` |
| 14 | **D7** | Data 7 | **Digital 7** | `PD7` |
| 15 | **A** | Backlight (+) | **5V** | - |
| 16 | **K** | Backlight (-) | **GND** | - |

**Note on Contrast (V0):** You *must* use a 10kΩ potentiometer connected between 5V and GND, with the wiper (center pin) connected to V0. If you see a blank screen or black boxes, adjust the potentiometer.



---

## 🛠️ Prerequisites & Installation

You need the AVR toolchain installed on your system to compile this project.

### 🐧 Linux (Arch/Manjaro)
```bash
# 1. Install Toolchain
sudo pacman -S avr-gcc avr-libc avrdude make

# 2. Serial Monitor (Optional)
sudo pacman -S picocom

# 3. Permissions (If you haven't already)
sudo usermod -aG uucp $USER
# Note: Log out and log back in for permissions to take effect.
```
### 🐧 Linux (Debian/Ubuntu)
```bash
sudo apt-get install gcc-avr binutils-avr avr-libc avrdude make
sudo usermod -aG dialout $USER
```
### 🪟 Windows
Install Make & AVRDude: The easiest way is using Chocolatey
```PowerShell
choco install make avrdude
```
Install Toolchain: Download the AVR 8-bit Toolchain for Windows from Microchip and add it to your PATH.

### 🚀 How to Build and Run
This repository includes a "Hello World" example to test the driver.
1. Clone the Repository
```Bash
git clone https://github.com/MatGonPer/avr-lcd-hd44780-driver.git
cd avr-lcd-hd44780-driver
```
2. Build the Example
Navigate to the example folder and run make. The Makefile will automatically locate the driver source code in ../../src.
```bash
cd examples/HelloWorld
make
```
3. Upload to Arduino
Connect your Arduino Uno via USB.
On Linux (Auto-Detect): The Makefile attempts to automatically detect the port (/dev/ttyACM* or /dev/ttyUSB*).
```bash
make upload
```
On Windows (Manual Port): Check Device Manager to find your COM port (e.g., COM3) and override the variable.
```bash
make upload PORT=COM3
```

### 📖 API Reference

To use this driver in your own project, copy the src folder or add it to your include path.

### `void lcd_init(void);`

    Initializes the display. Performs the hardware reset sequence and sets the interface to 4-bit mode, 2 lines, 5x8 font.
    Usage: Call this once inside your main setup.

### `void lcd_print(char *str);`

    Prints a null-terminated string to the current cursor position.

### `lcd_print("Hello World!");`
    Prints a string into the display

### `void lcd_set_cursor(uint8_t line, uint8_t col);`

    Moves the cursor to a specific position.
    line: 0 for the top row, 1 for the bottom row.
    col: 0 to 15.
    
    Example: lcd_set_cursor(1, 2); // Move to bottom row, 3rd character

### `void lcd_command(uint8_t cmd);`
    Sends a low-level command byte directly to the LCD controller.
    
    Example: lcd_command(0x01); // Clear Display
