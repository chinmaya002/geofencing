
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
//----------------------------------------
//----------------------------------------Include the DHT Library
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
SoftwareSerial neogps(D7,D8);
TinyGPSPlus gps;
//----------------------------------------
//----------------------------------------
const float maxDistance = 20;
const float maxDistance1 = 20;

float initialLatitude = 12.923282;
float initialLongitude = 77.497849;

float finalLatitude =12.923979;
float finalLongitude=77.498627;
//----------------------------------------
//----------------------------------------
float latitude, longitude;
void getGps(float& latitude, float& longitude);
//----------------------------------------
//----------------------------------------
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

String st;

#define ON_Board_LED 2  //--> Defining an On Board LED, used for indicators when the process of connecting to a wifi router

//----------------------------------------SSID and Password of your WiFi router.
const char* ssid = "AmoghPhone"; //--> Your wifi name or SSID.
const char* password = "amoghsimha"; //--> Your wifi password.
//----------------------------------------

//----------------------------------------Host & httpsPort
const char* host = "script.google.com";
const int httpsPort = 443;
//----------------------------------------

WiFiClientSecure client; //--> Create a WiFiClientSecure object.

String GAS_ID = "AKfycbyJ96Nl3sG8E51LSHHpgEgq5WcIN3-7vddU0F5EdJCWtaFGMd4lS6mBieXZ8cF5IxFI"; //--> spreadsheet script ID

//============================================================================== void setup
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  neogps.begin(9600);
  //........................................
    Wire.begin(D2, D1);   //Use predefined PINS consts
    lcd.backlight();      // Turn on the backlight.
    lcd.home();
    lcd.begin(20,4); 
    lcd.setCursor(0,1);
    lcd.print("smart transportation");
    lcd.setCursor(0,2);
    lcd.print("system for bmtc bus!");
    delay(5000);
    lcd.clear();
   //........................................ 
  
  WiFi.begin(ssid, password); //--> Connect to your WiFi router
  Serial.println("");
    
  pinMode(ON_Board_LED,OUTPUT); //--> On Board LED port Direction output
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off Led On Board

  //----------------------------------------Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    //----------------------------------------Make the On Board Flashing LED on the process of connecting to the wifi router.
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
    //----------------------------------------
  }
  //----------------------------------------
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off the On Board LED when it is connected to the wifi router.
  //----------------------------------------If successfully connected to the wifi router, the IP Address that will be visited is displayed in the serial monitor
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  //----------------------------------------

  client.setInsecure();
  randomSeed(analogRead(0));
}
//==============================================================================
//============================================================================== void loop
void loop() {
  //..................................................................................
  getGps(latitude, longitude);
  float distance = getDistance(latitude, longitude, initialLatitude, initialLongitude);
  float distance1 = getDistance(latitude, longitude, finalLatitude, finalLongitude);
 lcd.setCursor(0,0);
 lcd.print("current_lat_lon:");
 lcd.setCursor(0,1);
 lcd.print(latitude,6);
 lcd.print("'");
 lcd.print(longitude,6);
 lcd.setCursor(0,2);
 lcd.print("initial_lat_lon:");
 lcd.setCursor(0,3);
 lcd.print(initialLatitude,6);
 lcd.print("'");
 lcd.print(initialLongitude,6);
 delay(3000);
 //.....................................................................................
  float h = longitude ;;
  float t = latitude ;;
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor !");
    delay(500);
    return;
  }
 

  //............................................................................
  

  if(distance > maxDistance && distance1 > maxDistance1)
   {
    lcd.clear();
    st="left_DTL_huddle";
    lcd.setCursor(0,1);
    lcd.print("     Left DTL      ");
    lcd.setCursor(0,2);
    lcd.print("      Huddle       ");
    delay(3000);
    
   }
   else if(distance <= maxDistance && distance1 > maxDistance1){
     Serial.println("inside bus stand1");
    lcd.clear();
    st="Reached_DTL_huddle";
    lcd.setCursor(0,1);
    lcd.print("   inside the DTL  ");
    lcd.setCursor(0,2);
    lcd.print("      Huddle       ");
    delay(3000);
   }
   else if(distance > maxDistance && distance1 <= maxDistance1)
   {
    Serial.println("inside bus stand1");
    lcd.clear();
    st="Reached_Gate";
    lcd.setCursor(0,1);
    lcd.print("    Reached gate   ");
    //lcd.setCursor(0,2);
    //lcd.print("      Huddle       ");
    delay(3000);
   }
   else
   {
    Serial.println("inside bus stand1");
    lcd.clear();
    st="error";
    lcd.setCursor(0,1);
    lcd.print("       Error       ");
    lcd.setCursor(0,2);
    lcd.print("       Error       ");
    delay(3000);
   }


   //...............................................................................
  
  sendData(t, h, st); //--> Calls the sendData Subroutine
}
//==============================================================================
//============================================================================== void sendData
// Subroutine for sending data to Google Sheets
void sendData(float tem, float hum, String sta ) {
  Serial.println("==========");
  Serial.print("connecting to ");
  Serial.println(host);
  
  //----------------------------------------Connect to Google host
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }
  //----------------------------------------

  //----------------------------------------Processing data and sending data
  String lat =  String(tem,DEC);
  
  String lon =  String(hum, DEC); 
  String string_status=sta;
  String url = "/macros/s/" + GAS_ID + "/exec?temperature=" + lat + "&humidity=" + lon + "&status=" + string_status;
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
         "User-Agent: BuildFailureDetectorESP8266\r\n" +
         "Connection: close\r\n\r\n");

  Serial.println("request sent");
  //----------------------------------------

  //----------------------------------------Checking whether the data was sent successfully or not
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI successfull!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.print("reply was : ");
  Serial.println(line);
  Serial.println("closing connection");
  Serial.println("==========");
  Serial.println();
  //----------------------------------------
} 

float getDistance(float flat1, float flon1, float flat2, float flon2) {

  // Variables
  float dist_calc=0;
  float dist_calc2=0;
  float diflat=0;
  float diflon=0;

  // Calculations
  diflat  = radians(flat2-flat1);
  flat1 = radians(flat1);
  flat2 = radians(flat2);
  diflon = radians((flon2)-(flon1));

  dist_calc = (sin(diflat/2.0)*sin(diflat/2.0));
  dist_calc2 = cos(flat1);
  dist_calc2*=cos(flat2);
  dist_calc2*=sin(diflon/2.0);
  dist_calc2*=sin(diflon/2.0);
  dist_calc +=dist_calc2;

  dist_calc=(2*atan2(sqrt(dist_calc),sqrt(1.0-dist_calc)));
  
  dist_calc*=6371000.0; //Converting to meters

  return dist_calc;
}


/*****************************************************************************************
 * getGps() Function
*****************************************************************************************/
void getGps(float& latitude, float& longitude)
{
  // Can take up to 60 seconds
  boolean newData = false;
  for (unsigned long start = millis(); millis() - start < 2000;){
    while (neogps.available()){
      if (gps.encode(neogps.read())){
        newData = true;
        break;
      }
    }
  }
  
  if (newData) //If newData is true
  {
    latitude = gps.location.lat();
    longitude = gps.location.lng();
    newData = false;
  }
  else {
    Serial.println("No GPS data is available");
    latitude = 0;
    longitude = 0;
  }
}
//==============================================================================
