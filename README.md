# rde2013ctl

**rde2013ctl** is a CLI tool for controlling the features of Razer DeathAdder 2013 mice on GNU/Linux systems.

## Built With
* [libusb](http://libusb.info/) — Cross-platform C library that provides access to USB devices.
* [Wireshark](https://www.wireshark.org/) — For USB packet sniffing.

## Dependencies
* libusb 1.0

## Install & Uninstall
* `make && sudo make install` — Installs *rde2013ctl* under /usr/bin (You can change installiation directory in MAKEFILE)
* `sudo make uninstall` — Uninstalls *rde2013ctl* from /usr/bin

## Usage
* rde2013ctl set wheel-light *on* | *off* — Turns LED illumination of the mouse wheel on or off.
* rde2013ctl set logo-light *on* | *off* — Turns LED illumination of the logo on or off.

## License

This project is licensed under the GPLv3 License - see the LICENSE.md file for details.

## Scope of the Project
Scope of this project is limited to Razer DeathAdder 2013 mice. This is the only Razer product that I have and I wanted to create a simple tool to control its features. If you are looking support for other Razer devices, you could take a look at [razercfg](https://github.com/mbuesch/razer) project.
