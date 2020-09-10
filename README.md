# Arduino-(K)-Switch

This is a fully functional keyboard switch (KVM but while only the keyboard),
based on the combination of Arduino UNO + Arduino LEONARDO pro Micro.
Arduino UNO sends data from a connected USB keyboard via SoftwareSerial to 2 Arduino LEONARDOs that emulate the keyboard.

## This project is closed and is repleaced by newer https://github.com/nathalis/Arduino-USB-KM-Switch-2.0

Keyboard is toggled with ScrollLock Key.
I recommend USB cable keyboard.
All SoftwareSerials has baud rate: 38400 (increased to 115200)

Connection Schematics:

![Image description](https://github.com/nathalis/Arduino-KVM-Switch/blob/master/KVM_SCHEMATICS-updated.png?raw=true)

Prototype photo:

![Image description](https://raw.githubusercontent.com/nathalis/Arduino-KVM-Switch/master/Keyboard-prototype.jpg)

> to do mouse/joypad/video switch support... 

USB version has been released: https://github.com/nathalis/Arduino-USB-KM-Swtich

by Nathalis.

MIT. License
(c)2020
