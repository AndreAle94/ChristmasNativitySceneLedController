# ChristmasNativitySceneLedController
This repository contains the electrical diagram and the source code used to control the lights.

# Table of Contents
1. [Description](#description)
2. [Diagram](#diagram)
3. [Components](#components)
4. [License](#license)

## Description
The goal is to create a microcontroller capable of controlling the LED lights of a Christmas crib simulating the four main phases of the day:
- The sunrise and the day (the sun is up)
- The nightfall (the sun goes down and the lights of the houses come on)
- The evening (the sun is out, the stars light up while the houses remain illuminated)
- The night (the lights of the houses are turned off while only the stars remain on)
At the end, the cycle is repeated. Inside the code, all the timing of the transitions can be personalized.
The lights of the stars are not fixed but buttons to simulate the optical effect that is felt when observing the sky during the night.

## Diagram
![diagram](https://github.com/AndreAle94/ChristmasNativitySceneLedController/raw/master/diagrams/board.png)
The prototype was made using Arduino Uno and a breadboard. After completing the electrical diagram, I chose to move the project on a matrix board, replacing the entire development board with an ATmega328p. This device is powered at 12 volts - 1A.

## Components
- C1 = 100µF (electrolytic)
- C2 = 100nF (ceramic)
- C3 = 10µF (electrolytic)
- C4 = 22pF (ceramic)
- Q1 = 16MHz crystal
- D1 = 1N4007
- D2 = high brightness white LED
- IC1 = LM7805
- IC2 = ATmega328p
- R1 = 10KΩ
- R2 = 330Ω (can change!)
- T1 = 2N2222

## License
    Copyright (c) 2019.
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
