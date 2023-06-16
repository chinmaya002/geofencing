# geofencing

Geofencing is creating a virtual boundary around any particular location and findinf out whether your system has entered the virtual geofence. This model was built using ESP8266 and SIM28 GPS module.The ESP8266 is a low-cost, Wi-Fi-enabled microcontroller chip that gained significant popularity in the world of Internet of Things (IoT) and embedded systems.SIM28 is primarily focused on GPS (Global Positioning System) functionality. It integrates a GPS receiver that can receive signals from multiple satellites to determine the device's precise location coordinates (latitude and longitude), altitude, speed, and time information. ESP8266 and sim28 follow I2C communication. The data whether the system has entered the fence can be displayed on 2004A LCD display.
The ESP8266WiFi.h labrary gives us access to the GPIO pins of the board and the access to WiFi Capability .
WifiClientSecure.h library gives us access to the client on the internet network .
SoftwareSerial library is used to give us access to serial communication between the MCU and other componenets using the digital pins.
TinyGPS++.h is a library that is used to use the SIM28 GPS module 
LiquidCrystal_I2C.h is used to work with the LCD Monitor which works with the MCU with I2C communication.
The WiFi module works in the station mode ,in this mode the module connects to the internet by connecting to an existing WiFi Network .

