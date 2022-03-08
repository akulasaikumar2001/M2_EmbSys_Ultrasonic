// Include Libraries
#include "Arduino.h"
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
BLEHM10 blehm10(BLEHM10_PIN_RXD,BLEHM10_PIN_TXD);
ESP8266 wifi(WIFI_PIN_RX,WIFI_PIN_TX);
NewPing hcsr04(HCSR04_PIN_TRIG,HCSR04_PIN_ECHO);
LiquidCrystal lcd(LCD_PIN_RS,LCD_PIN_E,LCD_PIN_DB4,LCD_PIN_DB5,LCD_PIN_DB6,LCD_PIN_DB7);
Relay relayModule(RELAYMODULE_PIN_SIGNAL);
StepperMotor stepper(STEPPER_PIN_STEP,STEPPER_PIN_DIR);
Button ReflectiveIR(REFLECTIVEIR_PIN_COLL);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    blehm10.begin(9600);
    //This example uses HM-10 BLE to communicate with an Android or iOS device.
    //For Android download Hm BLE Terminal from google play store, or any other BLE app.
    //For iOS download LightBlue from App Store, or any other BLE app.
    //On both apps, pair and connect to your HM-10
    //You should see this message your Smartphone 
    blehm10.println("BLE On....");
    wifi.init(SSID, PASSWORD);
    // set up the LCD's number of columns and rows
    lcd.begin(16, 2);
    // enable the stepper motor, use .disable() to disable the motor
    stepper.enable();
    // set stepper motor speed by changing the delay value, the higher the delay the slower the motor will turn
    stepper.setStepDelay(stepperDelayTime);
    ReflectiveIR.init();
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // HM-10 BLE Bluetooth 4.0 - Test Code
    //Receive String from bluetooth device
    if (blehm10.available())
    {
    //Read a complete line from bluetooth terminal
    blehm10Str = blehm10.readStringUntil('\n');
    // Print raw data to serial monitor
    Serial.print("BT Raw Data: ");
    Serial.println(blehm10Str);
    }
    //Send sensor data to Bluetooth device  
    blehm10.println("PUT YOUR SENSOR DATA HERE");

    }
    else if(menuOption == '2') {
    // ESP8266-01 - Wifi Module - Test Code
    //Send request for www.google.com at port 80
    wifi.httpGet(host, hostPort);
    // get response buffer. Note that it is set to 250 bytes due to the Arduino low memory
    char* wifiBuf = wifi.getBuffer();
    //Comment out to print the buffer to Serial Monitor
    //for(int i=0; i< MAX_BUFFER_SIZE ; i++)
    //  Serial.print(wifiBuf[i]);
    //search buffer for the date and time and print it to the serial monitor. This is GMT time!
    char *wifiDateIdx = strstr (wifiBuf, "Date");
    for (int i = 0; wifiDateIdx[i] != '\n' ; i++)
    Serial.print(wifiDateIdx[i]);

    }
    else if(menuOption == '3') {
    // Ultrasonic Sensor - HC-SR04 - Test Code
    // Read distance measurment from UltraSonic sensor           
    int hcsr04Dist = hcsr04.ping_cm();
    delay(10);
    Serial.print(F("Distance: ")); Serial.print(hcsr04Dist); Serial.println(F("[cm]"));

    }
    else if(menuOption == '4') {
    // LCD 16x2 - Test Code
    // Print a message to the LCD.
    lcd.setCursor(0, 0);
    lcd.print("Circuito Rocks !");
    // Turn off the display:
    lcd.noDisplay();
    delay(500);
    // Turn on the display:
    lcd.display();
    delay(500);
    }
    else if(menuOption == '5') {
    // Relay Module - Test Code
    // The relay will turn on and off for 500ms (0.5 sec)
    relayModule.on();       // 1. turns on
    delay(500);             // 2. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    relayModule.off();      // 3. turns off.
    delay(500);             // 4. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    }
    else if(menuOption == '6') {
    // Stepper Motor with EasyDriver - Test Code
    // the higher the time value the slower the motor will run
    stepper.step(1, 1000);  // move motor 1000 steps in one direction
    delay(1000);            // short stop
    stepper.step(0, 1000);  // move motor 1000 steps in the other dirction
    delay(1000);            //short stop
    }
    else if(menuOption == '7') {
    // Reflective IR Sensor TCRT5000L - Test Code
    //read Reflective IR Sensor. 
    //if the sensor detects an echo function will return LOW (0). 
    //if it is not detect an echo function will return HIGH (1).
    bool ReflectiveIR_Val = ReflectiveIR.read();
    Serial.print(F("Val: ")); Serial.println(ReflectiveIR_Val);
    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) HM-10 BLE Bluetooth 4.0"));
    Serial.println(F("(2) ESP8266-01 - Wifi Module"));
    Serial.println(F("(3) Ultrasonic Sensor - HC-SR04"));
    Serial.println(F("(4) LCD 16x2"));
    Serial.println(F("(5) Relay Module"));
    Serial.println(F("(6) Stepper Motor with EasyDriver"));
    Serial.println(F("(7) Reflective IR Sensor TCRT5000L"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing HM-10 BLE Bluetooth 4.0"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing ESP8266-01 - Wifi Module"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing Ultrasonic Sensor - HC-SR04"));
    		else if(c == '4') 
    			Serial.println(F("Now Testing LCD 16x2"));
    		else if(c == '5') 
    			Serial.println(F("Now Testing Relay Module"));
    		else if(c == '6') 
    			Serial.println(F("Now Testing Stepper Motor with EasyDriver"));
    		else if(c == '7') 
    			Serial.println(F("Now Testing Reflective IR Sensor TCRT5000L"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}
