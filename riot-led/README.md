examples/light-read-write
================
This application reads RGB value from light/color sensor and outputs it
to RGB LED.

Each elements of RGB (red, green, blue) will be measured, if lower than given
threshold the respective colour will be turn off. If higher than threshold
it will be turned on again.

Usage
=====
1. Check RGB LED and light sensor is detected using `sensor-check` on the shell
2. Set threshold using `set-threshold` on the shell. Default is 1500 (TODO: change this!)
