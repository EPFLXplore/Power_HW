<p align="center" width="100%">
  <picture>
    <source media="(prefers-color-scheme: dark)" srcset="./Logos/ElonMuxLight.png">
    <source media="(prefers-color-scheme: light)" srcset="./Logos/ElonMuxDark.png">
    <img alt="ElonMux logo" width="33%" src="./Logos/ElonMuxDark.png">
  </picture>
</p>

<h1 align="center">ElonMux</h1>

ElonMux was designed by Théo Heng for EPFL [Xplore's](https://github.com/EPFLXplore) rover in the context of the European Rover Challenge. This board is capable to power the rover while simultaneously charging it's battery. The user have to be able to plug and unplug the power supply from the rover without shuting down/rebooting the load, requiring fast switching times. 
The system will always try to use the external power supply as the primary power source for the rover, but will default to the battery if it is not availaible.

<p align="center" width="100%">
    <img src="./Images/ElonMux_r1.png">
</p>

***

## SPECIFICATIONS

| Parameter | ElonMux V1.0 | 
| --- | --- |
| Voltage Input | 10-33V |
| Continuous Supply Current | 30A |
| Continuous Discharge Current | 30A |
| Max. Continuous Charge Current | 10A |
| Mass | TBD |
| Communication | USB 2.0 / JTAG / UART / I2C |
| MCU | ESP32-S3FN8 |
| Dimensions | 100x70x13mm |
| Designer   | Théo Heng        |
| Date       | Oct. 2024 - Feb. 2024 |
| Project    | ERC            |

***

## DIRECTORY STRUCTURE

```
ElonMux
├── Blender             # .pcb3d file and Blender files
├── Computations        # Computation sheets an simulation performed
├── Datasheets          # Datasheet of major components
├── Images              # Various images, pictures and screenshot used in the project 
    └── Photos          # High res. pictures of the assembled PCB
├── lib
    |── 3d_models       # Component 3D models
    |── lib_fp          # Footprint libraries
    └── lib_sym         # Symbol libraries
├── Logos               # Xplore and ElonMux logos
├── Manufacturing & BOMs
│   |── Assembly        # Position files, BOM, assembly document
|   |   └── ibom        # HTML BOM
|   └── Fabrication     # Fabrication document and testpoints positions
|       └── Gerbers     # Gerbers
├── Schematic           # PDF of schematic
├── STEP                # Step file of the board
└── Templates           # Title block templates

```

***

## FIRMWARE

The firware for ElonMux was written in the Arduino Framwork on Platform.io in VScode and flashed over USB. This is the recommended way of flashing the firmware. The firmware can be found 

***

## CREDITS

Schematic template & project structure is hugely inspired by the work of Vincent Nguyen on its [Λ M U L E T](https://github.com/EPFLXplore/XRE_LeggedRobot_HW/tree/master/amulet_controller) controler.

***

## PHOTOS

<p align="center" width="100%">
    <img src="./Images/ElonMuxFront3.png">
</p>

<p align="center" width="100%">
    <img src="./Images/ElonMuxBack3.png">
</p>
