/**
 * @file header.h
 * @author TR AJEESH
 * @brief This the project on automation movement of vacuum cleaner shortly 
 * tittled as "SMART VACUUM CLEANER" 
 * @version 0.1
 * @date 2022-03-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "BLEHM10.h"
#include "ESP8266.h"
#include "NewPing.h"
#include "LiquidCrystal.h"
#include "Relay.h"
#include "StepperMotor.h"
#include "Button.h"


// Pin Definitions
#define BLEHM10_PIN_TXD	11
#define BLEHM10_PIN_RXD	10
#define WIFI_PIN_TX	3
#define WIFI_PIN_RX	2
#define HCSR04_PIN_TRIG	5
#define HCSR04_PIN_ECHO	4
#define LCD_PIN_RS	13
#define LCD_PIN_E	12
#define LCD_PIN_DB4	6
#define LCD_PIN_DB5	7
#define LCD_PIN_DB6	8
#define LCD_PIN_DB7	9
#define RELAYMODULE_PIN_SIGNAL	A3
#define STEPPER_PIN_STEP	A1
#define STEPPER_PIN_DIR	A4
#define REFLECTIVEIR_PIN_COLL	A5



// Global variables and defines
String blehm10Str = "";
// ====================================================================
// vvvvvvvvvvvvvvvvvvvv ENTER YOUR WI-FI SETTINGS  vvvvvvvvvvvvvvvvvvvv
//
const char *SSID     = "WIFI-SSID"; // Enter your Wi-Fi name 
const char *PASSWORD = "PASSWORD" ; // Enter your Wi-Fi password
//
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// ====================================================================
char* const host = "www.google.com";
int hostPort = 80;
#define stepperDelayTime  1000
// object initialization
/**
 * @brief  BLE(Bluetooth) module for an embedded system
 * 
 * @return BLEHM10 
 */
BLEHM10 blehm10(BLEHM10_PIN_RXD,BLEHM10_PIN_TXD);
/**
 * @brief ESP8266 WiFi Module is a self contained SOC
 * 
 * @return ESP8266 
 */
ESP8266 wifi(WIFI_PIN_RX,WIFI_PIN_TX);
/**
 * @brief HC-SR04 with Arduino and NewPing library
 * 
 * @return NewPing 
 */
NewPing hcsr04(HCSR04_PIN_TRIG,HCSR04_PIN_ECHO);
/**
 * @brief Displays operation that takes place
 * 
 * @return LiquidCrystal 
 */
LiquidCrystal lcd(LCD_PIN_RS,LCD_PIN_E,LCD_PIN_DB4,LCD_PIN_DB5,LCD_PIN_DB6,LCD_PIN_DB7);
/**
 * @brief to convert small electrical stimuli into larger currents
 * 
 * @return Relay 
 */
Relay relayModule(RELAYMODULE_PIN_SIGNAL);
/**
 * @brief used for precise positioning with a motor
 * 
 * @return StepperMotor 
 */
StepperMotor stepper(STEPPER_PIN_STEP,STEPPER_PIN_DIR);
/**
 * @brief for line tracking purposes
 * 
 * @return Button 
 */
Button ReflectiveIR(REFLECTIVEIR_PIN_COLL);
