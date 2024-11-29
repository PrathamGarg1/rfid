#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Pin definitions for Arduino Uno
#define SS_PIN 10       // Slave Select pin for RFID module
#define RST_PIN 9       // Reset pin for RFID module
#define LED_GREEN 7     // Green LED for access granted
#define LED_RED 6       // Red LED for access denied
#define SERVO_PIN 5     // Servo motor pin
#define BUTTON_PIN 8    // Button for enabling registration mode

// LCD pin configurations for I2C (16x2 display)
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27 for the LCD

// Initialize RFID reader
MFRC522 rfid(SS_PIN, RST_PIN);

// Initialize servo motor
Servo gateServo;
const int servoOpenPosition = 90;  // Servo angle for open gate
const int servoClosedPosition = 0; // Servo angle for closed gate

// Constants
const float DEDUCTION_AMOUNT = 100.0; // Amount deducted per access

// Structure for vehicle data
struct VehicleData {
  byte tagID[4];         // RFID tag ID (4 bytes)
  float balance;         // Balance associated with the vehicle
  bool isBlacklisted;    // Blacklist status (true if blacklisted)
};

// Array of authorized vehicles with their initial data
VehicleData vehicles[10] = {
  {{0x12, 0x34, 0x56, 0x78}, 500.0, false}, // Vehicle 1
  {{0x98, 0x76, 0x54, 0x32}, 500.0, false}, // Vehicle 2
  {{0xDE, 0xAD, 0xBE, 0xEF}, 500.0, true}  // Vehicle 3 (blacklisted)
};

// Global variables
bool registerMode = false; // Flag to track registration mode

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  Serial.println("Initializing...");

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();

  // Initialize RFID reader
  SPI.begin();
  rfid.PCD_Init();
  
  // Configure pin modes
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Button with pull-up resistor

  // Attach servo motor and set to closed position
  gateServo.attach(SERVO_PIN);
  gateServo.write(servoClosedPosition);

  // Display the initial welcome message on the LCD
  displayWelcomeMessage();
}

void loop() {
  // Check if the button is pressed to activate registration mode
  if (digitalRead(BUTTON_PIN) == LOW) { // LOW because of pull-up configuration
    registerMode = true;
    lcd.clear();
    lcd.print("Register Mode On");
    Serial.println("Register mode activated");
    delay(2000);
  }

  // Check if a new RFID card is detected
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    if (registerMode) {
      // Register new tag if in registration mode
      Serial.println("Registering new tag...");
      registerNewTag();
      registerMode = false; // Exit registration mode after registering
    } else {
      // Handle RFID detection for regular access
      Serial.println("Handling RFID detection...");
      handleRFIDDetection();
    }
  }
}

// Function to register a new RFID tag
void registerNewTag() {
  byte tagID[4];
  for (byte i = 0; i < 4; i++) {
    tagID[i] = rfid.uid.uidByte[i]; // Read tag ID
  }

  int newVehicleIndex = findAvailableVehicleSlot();
  if (newVehicleIndex == -1) {
    // No space available for new vehicle
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No Space for New");
    lcd.setCursor(0, 1);
    lcd.print("Vehicle");
    Serial.println("No space for new vehicle");
    delay(3000);
    return;
  }

  // Register new vehicle with default balance
  vehicles[newVehicleIndex] = { {tagID[0], tagID[1], tagID[2], tagID[3]}, 1000.0, false };

  // Display success message on LCD
  lcd.clear();
  lcd.print("Tag Registered");
  lcd.setCursor(0, 1);
  lcd.print("Balance: Rs.1000");
  Serial.println("New tag registered with balance Rs.1000");
  delay(3000);
  displayWelcomeMessage();
}

// Function to find an empty slot in the vehicle array
int findAvailableVehicleSlot() {
  for (int i = 0; i < 10; i++) {
    if (vehicles[i].tagID[0] == 0x00 && vehicles[i].tagID[1] == 0x00 &&
        vehicles[i].tagID[2] == 0x00 && vehicles[i].tagID[3] == 0x00) {
      return i; // Return index of available slot
    }
  }
  return -1; // No available slot found
}

// Function to handle RFID detection for regular access
void handleRFIDDetection() {
  byte tagID[4];
  for (byte i = 0; i < 4; i++) {
    tagID[i] = rfid.uid.uidByte[i]; // Read tag ID
  }

  int vehicleIndex = findVehicleIndex(tagID);
  if (vehicleIndex == -1) {
    // Unknown vehicle detected
    Serial.println("Unknown vehicle detected");
    accessDenied("Unknown Vehicle");
    return;
  }

  if (vehicles[vehicleIndex].balance < DEDUCTION_AMOUNT) {
    // Insufficient balance
    Serial.println("Insufficient balance");
    accessDenied("Insufficient Bal.");
    return;
  }

  // Deduct amount and grant access
  vehicles[vehicleIndex].balance -= DEDUCTION_AMOUNT;
  Serial.print("Access granted. Remaining balance: Rs.");
  Serial.println(vehicles[vehicleIndex].balance);
  accessGranted(vehicles[vehicleIndex].balance);
  
  // Halt RFID communication
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

// Function to grant access and open the gate
void accessGranted(float remainingBalance) {
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, HIGH);
  
  lcd.clear();
  lcd.print("Access Granted");
  lcd.setCursor(0, 1);
  lcd.print("Bal: Rs.");
  lcd.print(remainingBalance);
  
  Serial.println("Gate opened");
  gateServo.write(servoOpenPosition); // Open gate
  delay(5000); // Keep gate open for 5 seconds
  gateServo.write(servoClosedPosition); // Close gate
  Serial.println("Gate closed");
  
  digitalWrite(LED_GREEN, LOW);
  displayWelcomeMessage();
}

// Function to deny access and display the reason
void accessDenied(String reason) {
  digitalWrite(LED_RED, HIGH);

  lcd.clear();
  lcd.print("Access Denied");
  lcd.setCursor(0, 1);
  lcd.print(reason);
  Serial.print("Access denied: ");
  Serial.println(reason);
  
  delay(3000);
  digitalWrite(LED_RED, LOW);
  displayWelcomeMessage();
}

// Function to display the welcome message on LCD
void displayWelcomeMessage() {
  lcd.clear();
  lcd.print("Vehicle Gate");
  lcd.setCursor(0, 1);
  lcd.print("Scan RFID Card");
  Serial.println("Welcome message displayed");
}

// Function to find the index of a vehicle based on tag ID
int findVehicleIndex(byte tagID[]) {
  for (int i = 0; i < 10; i++) {
    if (memcmp(tagID, vehicles[i].tagID, 4) == 0) {
      return i; // Return index of matching vehicle
    }
  }
  return -1; // No matching vehicle found
}