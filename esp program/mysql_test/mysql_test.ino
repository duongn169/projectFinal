#include <ESP8266WiFi.h> 
#include "DHT.h"

#include <Wire.h>
#include "MAX30105.h"
#include "spo2_algorithm.h"
#include "heartRate.h"



/*--------------------------------------DHT11 Param---------------------*/
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
/*--------------------------------------DHT11 Param---------------------*/




/*------------------------------------MAX30100 Param--------------------*/
MAX30105 particleSensor;

#define MAX_BRIGHTNESS 255

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
//Arduino Uno doesn't have enough SRAM to store 100 samples of IR led data and red led data in 32-bit format
//To solve this problem, 16-bit MSB of the sampled data will be truncated. Samples become 16-bit data.
uint16_t irBuffer[100]; //infrared LED sensor data
uint16_t redBuffer[100];  //red LED sensor data
#else
uint32_t irBuffer[100]; //infrared LED sensor data
uint32_t redBuffer[100];  //red LED sensor data
#endif

int32_t bufferLength; //data length
int32_t spo2; //SPO2 value
int8_t validSPO2; //indicator to show if the SPO2 calculation is valid
int32_t heartRate; //heart rate value
int8_t validHeartRate; //indicator to show if the heart rate calculation is valid
int32_t updatedSPO2=0, updatedBPM=0;

byte pulseLED = 12; //Must be on PWM pin
byte readLED = 13; //Blinks with each data read
/*------------------------------------MAX30100 Param--------------------*/




/*----------------------------wifi param--------------------------------*/
// Insert your network credentials
#define WIFI_SSID "PHONG TRO 36/4 -1"                                  
#define WIFI_PASSWORD "0934085190" 
char* host = "192.168.1.214";
/*----------------------------wifi param--------------------------------*/






void setup()
{
  
    Serial.begin(115200);

    /*---------------------------Connect to wifi--------------------------*/
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);
  
    // Connect to the WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                  
    Serial.print("Connecting to ");
    Serial.print(WIFI_SSID);
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(300);
    }
  
    // Debugging – Output the IP Address of the ESP8266
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    /*---------------------------Connect to wifi--------------------------*/





    

    /*-------------------------------DHT11 begin------------------------------*/
    Serial.println("DHT11 Output!");
    dht.begin();
    /*---------------------------DHT11 end begin------------------------------*/






    /*---------------------------MAX30100 begin------------------------------*/
    pinMode(pulseLED, OUTPUT);
    pinMode(readLED, OUTPUT);
    
    // Initialize sensor
    if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
    {
      Serial.println(F("MAX30105 was not found. Please check wiring/power."));
      yield();
      //while (1);
    }
    Serial.println("Connection OK");
    
    //Serial.println(F("Attach sensor to finger with rubber band. Press any key to start conversion"));
    //while (Serial.available() == 0) ; //wait until user presses a key
    //Serial.read();
  
    byte ledBrightness = 60; //Options: 0=Off to 255=50mA
    byte sampleAverage = 4; //Options: 1, 2, 4, 8, 16, 32
    byte ledMode = 2; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
    byte sampleRate = 100; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
    int pulseWidth = 215; //Options: 69, 118, 215, 411
    int adcRange = 4096; //Options: 2048, 4096, 8192, 16384

    particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings
  

    /*---------------------------MAX30100 begin------------------------------*/

}





void loop()
{

   /*--------------------------------------Read max30102 DAta--------------------------------*/
  bufferLength = 100; //buffer length of 100 stores 4 seconds of samples running at 25sps

  //read the first 100 samples, and determine the signal range
  for (byte i = 0 ; i < bufferLength ; i++)
  {
    while (particleSensor.available() == false) //do we have new data?
      particleSensor.check(); //Check the sensor for new data

    redBuffer[i] = particleSensor.getRed();
    irBuffer[i] = particleSensor.getIR();
    particleSensor.nextSample(); //We're finished with this sample so move to next sample

    Serial.print(F("red="));
    Serial.print(redBuffer[i], DEC);
    Serial.print(F(", ir="));
    Serial.println(irBuffer[i], DEC);
  }

  //calculate heart rate and SpO2 after first 100 samples (first 4 seconds of samples)
  maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);

  //Continuously taking samples from MAX30102.  Heart rate and SpO2 are calculated every 1 second
  while (1)
  {
        //dumping the first 25 sets of samples in the memory and shift the last 75 sets of samples to the top
        for (byte i = 25; i < 100; i++)
        {
          redBuffer[i - 25] = redBuffer[i];
          irBuffer[i - 25] = irBuffer[i];
        }
    
        //take 25 sets of samples before calculating the heart rate.
        for (byte i = 75; i < 100; i++)
        {
          while (particleSensor.available() == false) //do we have new data?
          particleSensor.check(); //Check the sensor for new data
    
          digitalWrite(readLED, !digitalRead(readLED)); //Blink onboard LED with every data read
    
          redBuffer[i] = particleSensor.getRed();
          irBuffer[i] = particleSensor.getIR();
          particleSensor.nextSample(); //We're finished with this sample so move to next sample
    
          //send samples and calculation result to terminal program through UART
          Serial.print(F("red="));
          Serial.print(redBuffer[i], DEC);
          Serial.print(F(", ir="));
          Serial.print(irBuffer[i], DEC);
    
          Serial.print(F(", HR="));
          Serial.print(heartRate, DEC);
    
          Serial.print(F(", HRvalid="));
          Serial.print(validHeartRate, DEC);
    
          Serial.print(F(", SPO2="));
          Serial.print(spo2, DEC);
    
          Serial.print(F(", SPO2Valid="));
          Serial.println(validSPO2, DEC);
    
          if(validHeartRate) updatedBPM = heartRate;
          if(validSPO2) updatedSPO2 = spo2;
        }
    
          //After gathering 25 new samples recalculate HR and SP02
          maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);

        
        /*-----------------------------------------------------Read max30102 Data------------------------------------*/
       
    
    
    
    
        /*----------------------------------------------------Read DHT11 Data------------------------------*/
        float temperature = dht.readTemperature();
        float humidity = dht.readHumidity(); 
         
        if(isnan(temperature) || isnan(humidity)){
          Serial.println("Failed to read DHT11");
        }else{
          Serial.print("Humidity: ");
          Serial.print(humidity);
          Serial.print(" %\t");
          Serial.print("Temperature: ");
          Serial.print(temperature);
          Serial.println(" *C");
          delay(300);
        }
        /*-----------------------------------------------Read DHT11 Data-------------------------------*/
    
    
    
    
        //--------------------------------- Use WiFiClient class to create TCP connections-----------------------------------
        WiFiClient client;
        const int httpPort = 80;
        if (!client.connect(host, httpPort)) {
            Serial.println("connection failed");
            return;
        }
        
    
        Serial.print("connecting to ");
        Serial.println(host);
    
    
        
        // This will send the request to the server
        client.print(String("GET http://192.168.1.214/index1.php?") + 
                              ("&temperature=") + temperature +
                              ("&humidity=") + humidity +
                              ("&bpm=") + updatedBPM + 
                              ("&spo2=") + updatedSPO2 + 
                              " HTTP/1.1\r\n" +
                     "Host: " + host + "\r\n" +
                     "Connection: close\r\n\r\n");
        unsigned long timeout = millis();
        while (client.available() == 0) {
            if (millis() - timeout > 1000) {
                Serial.println(">>> Client Timeout !");
                client.stop();
                return;
            }
        }
    
        
        // Read all the lines of the reply from server and print them to Serial
        /*
        while(client.available()) {
            String line = client.readStringUntil('\r');
            Serial.print(line);
            
        }
        */
        Serial.println();
        Serial.println("closing connection");
      }

      //small comment here
      //now add another comment
}
