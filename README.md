# Car Parking System using PIR Sensor and I2C Protocol with LPC2148 ARM microcontroller

## **Team Members**: <br> Amit Kumar<br> Nidhi Neje<br> Sakshi Kulkarni<br> Sejal Ankush

## Problem Statement
The goal was to build an application using the I2C protocol and PIR sensor to monitor car entry in a parking lot, displaying the status on an LCD and UART with LPC2148 ARM microcontroller.

## Introduction
The project aims to develop a car parking system that detects cars entering a parking lot using a PIR sensor. The system displays the status on an LCD and allows a maximum of 10 cars per floor. When the parking lot is full, it indicates this status using LED lights and displays the message on UART.

## Features Selected
  - Detects car entry using a PIR sensor.
  - Displays the parking status on an LCD.
  - Communicates the status via UART.
  - Indicates a full parking lot with LEDs.

## System Components
  - LPC2148: Main microcontroller.
  - PIR Sensor: Detects the presence of a car.
  - UART: Used for communication.
  - LED: Indicates the status of the parking lot.
  - LCD: Displays messages related to parking status.

## Learning from the Project:
- I2C Protocol: Learned and implemented I2C communication for interfacing peripherals like LCD and PIR sensor with the LPC2148 microcontroller.
- PIR Sensor Integration: Successfully interfaced a PIR sensor to detect car entry and trigger status updates.
- UART Communication: Configured UART for real-time parking status communication to external systems.
- LCD Interfacing: Programmed the LCD to display dynamic parking status, including available slots and "Full" alerts.
- LED Indicators: Used LEDs to visually indicate parking lot status (e.g., green for available, red for full).
- ARM Programming: Gained hands-on experience in programming the LPC2148 microcontroller using embedded C.
- System Integration: Integrated all components (PIR, LCD, UART, LEDs) and debugged for seamless operation.
- Team Collaboration: Improved project management and teamwork skills through task allocation and collaborative problem-solving.

## Conclusion
The project successfully implemented a car parking system using a PIR sensor and I2C protocol. The system can be expanded for larger parking lots, ensuring scalability.

Additional Resources:

- Code File: The implementation code is available in the ARM.c file.
- Presentation: A PowerPoint presentation is available, providing a detailed overview of the project, including the functional block diagrams, and interfacing details.
