# Power Wago + INA

## Description

Based on the "power_hat_wago" design, this design adds current and voltage monitoring. The INA238 paired with a shunt resistor is able to read the current by measuring the voltage drop across the resistor. The value can then be recovered via I2C.

## Design choices/constraints

The wago is sized to withstand a max current of 40A at 5, 15, 24V and Vbatt (depending on what voltage bus it's connected on). 

This version also adds some very basic protections but this board is not meant to protect the system. This is something that we plan either to implement on a dedicated board or on the buck converters.
 
### Layer stackup

This board has 4 layers. two GND layers in the middle, one power layer on the underside (with shunt resistor, TVS diode and fuse) and one top layer with all the connectors and remaining components

### I/O ports

This board is meant to be connected to the main avionics NOVA board. It has a 5x1 clickmate connector with 2 power lines and 2 data lines for I2C. The remaining pin is currently not used. 

## Questions

For TVS diodes, there is a gap between reverse standoff voltage, breakdown and clamping voltage. Let's say i want to power a raspberry pi at 5V (between 4.75V and 5.25V). Which of the three values should i match ? Because of course the max voltage is the clamping voltage so i could choose a diode with a clamping voltage at 5.25V but i don't want my diode to be conducting under normal conditions. Here's the datasheet of the diode i used in this schematic, would the SMAJ5.0A be suitable for the 5V bus ? 
https://www.littelfuse.com/assetdocs/tvs-diodes-smaj-datasheet?assetguid=13c2a823-03b8-4d1f-9ddc-9b44670aed9d

The INA238 is currently out of stock and is expected to be restocked on march. Should i just wait for it or go look for a replacement ? Also, how do i know which ADC i should choose ? There a ton of choices and i don't even know where to start my selection. (What i usually do is just copy the component used in another schematic lol)

Digikey's trace width calulator tells me i should have 15mm wide traces, but then all the current flows in a little fuse, is this ok ?


