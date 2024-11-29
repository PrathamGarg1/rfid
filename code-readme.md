# RFID Automatic Toll Tax Collection 

## Project Overview
This is an Arduino-based RFID-enabled vehicle gate access control system that manages vehicle entry through an automated gate mechanism with balance-based access control.

## Components
- Arduino Uno
- MFRC522 RFID Reader
- 16x2 I2C LCD Display
- Servo Motor
- Green and Red LEDs
- Push Button

## Features
- RFID-based vehicle authentication
- Balance-based access control
- Vehicle registration mode
- Real-time balance tracking
- Visual feedback through LCD and LEDs

## Prerequisites
### Hardware Requirements
- Arduino Uno
- MFRC522 RFID Module
- I2C 16x2 LCD Display
- Servo Motor
- Breadboard and jumper wires
- Two LEDs (Green and Red)
- Push button

### Software Requirements
- Arduino IDE (version 1.8.10 or newer)
- Libraries:
  - MFRC522 Library
  - LiquidCrystal_I2C Library
  - Wire Library
  - Servo Library

## Installation Steps
1. Install Arduino IDE
2. Install required libraries via Arduino Library Manager
3. Connect hardware components as per circuit diagram
4. Upload the provided Arduino sketch
5. Power the system and test functionality

## Wiring Configuration
- RFID Module:
  - SS Pin: Digital Pin 10
  - RST Pin: Digital Pin 9
- LEDs:
  - Green LED: Digital Pin 7
  - Red LED: Digital Pin 6
- Servo Motor: Digital Pin 5
- Push Button: Digital Pin 8
- I2C LCD: Connected via I2C interface

## System Workflow
1. Initial Setup
   - System initializes components
   - Displays welcome message
   - Waits for RFID card scanning

2. Registration Mode
   - Press button to enter registration mode
   - Scan new RFID card to register
   - Assigns default balance of Rs. 1000
   - Maximum 10 vehicle registrations

3. Access Control
   - Scan registered RFID card
   - Check balance and blacklist status
   - Deduct Rs. 100 per access
   - Open/close gate with servo motor
   - Provide visual and LCD feedback

## Customization
- Modify `DEDUCTION_AMOUNT` to change access fee
- Adjust `servoOpenPosition` and `servoClosedPosition` for gate mechanism
- Update vehicle data in `vehicles` array

## Troubleshooting
- Ensure all libraries are installed
- Check wiring connections
- Verify RFID module and LCD address
- Monitor Serial Monitor for debug information

## License
[Specify your license here, e.g., MIT, GPL]

## Contributors
[List contributors or your name]
