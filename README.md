# Project Description: **Digital Multimeter (DMM) with AVR Microcontroller**

This project implements a Digital Multimeter (DMM) using an AVR microcontroller. It measures voltage (AC/DC), current, and resistance, with results displayed on an LCD. User interaction is handled via a keypad for mode and range selection.

## Core Modules
- ADC Driver

1. Supports polling and interrupt modes.

2. Configurable reference voltage (AVCC, AREF, internal 2.56V) and prescaler.

3. Used for analog signal acquisition in voltmeter, ammeter, and ohmmeter circuits.

- GPIO Driver
1. Manages pin direction (input/output), read/write operations, and toggling.

2. Direct register access for PORT A/B/C/D.

- Keypad Driver
1. Supports 4x4 or 4x3 matrix keypad with pull-up/pull-down configurability.

2. Scans rows/columns to detect key presses and maps them to characters/numbers.

- LCD Driver
1. 4-bit mode for displaying measurements (voltage, current, resistance).

2. Functions for cursor control, string/number formatting, and screen clearing.

## Measurement Modes

- Voltmeter:

    1. AC/DC selection with two ranges:

        - Range 1: 0.3V–2V

        - Range 2: 2V–20V

    2. Relay-controlled circuit switching (e.g., PORTB_ID, PIN4_ID for AC/DC).

- Ammeter:

    1. Two ranges:

        - Range 1: 10mA–100mA

        - Range 2: 100mA–1A

    2. Uses ADC channel 5 (ADC5) for current sensing via shunt resistor.

- Ohmmeter:

    1. Three ranges:

        0–1.3kΩ, 1.3kΩ–10kΩ, 10kΩ–1MΩ

    2. Voltage divider circuit for resistance calculation.

## User Interface

- Keypad Navigation:

    - Menu-driven interface for selecting measurement type and range.

    - Reset functionality via external interrupt (INT0).

- LCD Display:

    - Shows real-time values (e.g., 12.34 mA, 5.67 V).

    - Uses LCD_floatToString for floating-point formatting.

## Hardware Integration
- ADC Circuitry:

    - Voltage scaling for different ranges (voltage dividers, shunt resistors).

    - Reference voltage set to AVCC (5V) in FinalFullProject.c.

- GPIO Connections:

    - LCD: Data on PORTD, control pins (RS, EN) on PORTD.

    - Keypad: Rows on PORTA, columns on PORTB.

    - Relays/Indicators:

        - PORTB, PIN7 for ammeter range switching.

        - PORTC, PIN6 for status LED.



