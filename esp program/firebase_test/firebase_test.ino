#include  <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include "DHT.h"
 
#define FIREBASE_HOST "sensor-data-8ed1c-default-rtdb.firebaseio.com" 
#define WIFI_SSID "MINH QUAN" // Change the name of your WIFI
#define WIFI_PASSWORD "0978249969" // Change the password of your WIFI
 
#define DHTPIN D2   
 
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
 
void setup() 
{
  Serial.begin(115200);
  dht.begin();                                                  //reads dht sensor data 
               
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                  
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
 
  Serial.println();
  Serial.print("Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); 
  Firebase.begin(FIREBASE_HOST);
  
}
 
void loop() 
{
 
  float h = dht.readHumidity();
  float t = dht.readTemperature();  // Reading temperature as Celsius (the default)
 
  Serial.print("Humidity: ");  
  Serial.print(h);
  
  Serial.print("%  Temperature: ");  
  Serial.print(t);  
  Serial.println("°C ");
   
  Firebase.setFloat ("Temp",t);
  Firebase.setFloat ("Humidity",h);
  delay(3000);
}
