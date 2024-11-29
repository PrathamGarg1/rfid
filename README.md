# RFID Automatic Toll Tax Collection 
## Github Repository
https://github.com/PrathamGarg1/rfid/new/main


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
MIT Open source Licence 

# RFID Automatic Toll Tax Collection : Technical Explanation

## Conceptual Overview

The Vehicle Gate Access Control System is an intelligent, embedded system designed to manage vehicle entry through an automated gate mechanism. It combines hardware components and software logic to create a sophisticated access control solution that goes beyond simple entry management.

### Core Objectives
- Secure and controlled vehicle access
- Automated gate operation
- Real-time balance-based access management
- Flexible vehicle registration
- Robust error handling and user feedback

## System Architecture

### Hardware Components
1. **Microcontroller**: Arduino Uno
   - Central processing unit
   - Coordinates all system interactions
   - Manages communication between different modules

2. **RFID Module (MFRC522)**
   - Wireless identification technology
   - Reads unique tag identifiers
   - Enables contactless vehicle authentication

3. **LCD Display (16x2 I2C)**
   - Provides real-time system status
   - Displays messages and feedback
   - Helps users understand system state

4. **Servo Motor**
   - Physical gate mechanism
   - Controlled rotation for opening/closing
   - Precise angle-based positioning

5. **Indicator LEDs**
   - Green LED: Access granted signal
   - Red LED: Access denied signal
   - Provides immediate visual feedback

6. **Push Button**
   - Enables registration mode
   - Manual system mode switching

## Code Structure and Design Patterns

### Data Representation: VehicleData Structure
```cpp
struct VehicleData {
  byte tagID[4];         // Unique 4-byte RFID tag identifier
  float balance;         // Monetary balance associated with vehicle
  bool isBlacklisted;    // Administrative access control flag
};
```

#### Design Rationale
- Fixed-size array for predictable memory allocation
- Compact representation of vehicle metadata
- Supports future extensibility

### Memory Management Strategy
- Static array of 10 vehicles (`vehicles[10]`)
- Predefined maximum vehicle registration limit
- Prevents dynamic memory allocation complications

### Key Functions and Their Responsibilities

#### 1. setup() Function
- System initialization
- Configure pin modes
- Initialize communication protocols
- Set initial system state

#### 2. loop() Function
- Continuous execution cycle
- Checks for user interactions
- Handles RFID card detection
- Manages registration and access control modes

#### 3. Registration Workflow
```cpp
void registerNewTag() {
  // Capture new RFID tag
  // Find available vehicle slot
  // Assign default balance
  // Store vehicle information
}
```

#### 4. Access Control Logic
```cpp
void handleRFIDDetection() {
  // Validate RFID tag
  // Check vehicle status
  // Verify balance
  // Grant/Deny access
  // Update balance
}
```

## Advanced System Features

### 1. Balance-Based Access Control
- Fixed deduction amount per access (Rs. 100)
- Prevents access with insufficient funds
- Real-time balance tracking

### 2. Blacklist Mechanism
- Administrative control feature
- Prevent specific vehicles from accessing
- Integrated into access control logic

### 3. State Management
- Clear mode transitions
- Registration and normal operation modes
- Explicit state change indicators

## Error Handling and Feedback Mechanisms

### Visual Feedback
- LCD Display: Detailed status messages
- LED Indicators: Immediate access status
- Serial Monitor: Debugging and detailed logs

### Common Scenarios Handled
- Unknown vehicle detection
- Insufficient balance
- Registration mode limitations
- Maximum vehicle registration

## Performance Considerations

### Memory Usage
- Minimal dynamic memory allocation
- Efficient use of Arduino's limited resources

### Time Complexity
- O(1) tag lookup in vehicle array
- Constant-time operations for most functions

### Power Efficiency
- Low-power components
- Minimal computational overhead

## Potential Future Enhancements
1. Wireless connectivity (GSM/WiFi)
2. Cloud-based balance management
3. Advanced authentication methods
4. Comprehensive logging system
5. Mobile app integration

