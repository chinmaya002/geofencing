# geofencing

Geofencing is creating a virtual boundary around any particular location and finding out whether your system has entered the virtual fence. This model was built using ESP8266 and SIM28 GPS module.The ESP8266 is a low-cost, Wi-Fi-enabled microcontroller chip.SIM28 is primarily focused on GPS (Global Positioning System) functionality. It integrates a GPS receiver that can receive signals from multiple satellites to determine the device's precise location coordinates (latitude and longitude), altitude, speed, and time information.  The data whether the system has entered the fence can be displayed on 2004A LCD display.
The ESP8266WiFi.h labrary gives us access to the GPIO pins of the board and the access to WiFi Capability .
WifiClientSecure.h library gives us access to the client on the internet network .
SoftwareSerial library is used to give us access to serial communication between the MCU and other componenets using the digital pins.
TinyGPS++.h is a library that is used to use the SIM28 GPS module 
LiquidCrystal_I2C.h is used to work with the LCD Monitor which works with the MCU with I2C communication.
The WiFi module works in the station mode ,in this mode the module connects to the internet by connecting to an existing WiFi Network.
In this code we have tried to connect to a google sheets client.
The MCU updates the current location in the spreadsheet at regular intervals . The spreadsheet is recognised by a scriptid over the internet .



![WhatsApp Image 2023-06-16 at 7 43 20 AM](https://github.com/chinmaya002/geofencing/assets/102479420/6f0d0bf6-4cc7-455f-9d8e-eab4c437d2e2)
