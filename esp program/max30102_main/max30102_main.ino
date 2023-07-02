

#include <ESP8266WiFi.h>
#include <Wire.h>
#include "MAX30105.h"
#include "spo2_algorithm.h"
#include "heartRate.h"



int myBPM = 0, mySPO2 = 0;

const unsigned long WIFI_CONNECT_TIMEOUT = 5000; // Wi-Fi connection timeout in milliseconds


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
int32_t updatedSPO2 = 0, updatedBPM = 0;

byte pulseLED = 12; //Must be on PWM pin
byte readLED = 13; //Blinks with each data read
///*------------------------------------MAX30100 Param--------------------*/







/*----------------------------wifi param--------------------------------*/
// Insert your network credentials
char ssid[50] = "PHONG TRO 36/4 -1";
char pass[50] = "0934085190";
char userID[5] = "46";
char phone[12] = "12345";

char* host = "192.168.1.214";
WiFiClient wifiClient;
/*----------------------------wifi param--------------------------------*/



void connect_wifi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Connect to the WiFi
  WiFi.begin(ssid, pass);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // Debugging – Output the IP Address of the ESP8266
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}


void getWifiInfor() {
  Serial.println("Enter Wi-Fi SSID:");
  while (Serial.available() == 0) {
    // Wait for user input
  }
  Serial.readBytesUntil('\n', ssid, sizeof(ssid) - 1); // Read the user input until newline character
  ssid[sizeof(ssid) - 1] = '\0'; // Add null termination to make it a valid string

  delay(1000);
  Serial.println("Enter Wi-Fi password:");
  while (Serial.available() == 0) {
    // Wait for user input
  }
  Serial.readBytesUntil('\n', pass, sizeof(pass) - 1); // Read the user input until newline character
  pass[sizeof(pass) - 1] = '\0'; // Add null termination to make it a valid string

  Serial.println("Wi-Fi credentials received! Please wait...");
  connect_wifi();
}



void verifyWifiConnection() {
  bool connected = false;

  while (!connected) {
    // Call the function to get Wi-Fi credentials
    getWifiInfor();

    // Attempt to connect to Wi-Fi
    unsigned long startTime = millis(); // Get the current time
    while (millis() - startTime < WIFI_CONNECT_TIMEOUT) {
      // Check if Wi-Fi connection is successful
      if (WiFi.status() == WL_CONNECTED) {
        connected = true;
        break;
      }
      // Wait a short delay before retrying
      delay(500);
    }

    if (connected) {
      Serial.println("Connected to Wi-Fi!");
      // Continue with your code logic
      // ...
    } else {
      Serial.println("Failed to connect to Wi-Fi. Please try again.");
    }
  }
}


void sendDataToDB() {
  //--------------------------------- Use WiFiClient class to create TCP connections-----------------------------------

  const int httpPort = 80;
  if (!wifiClient.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }


  Serial.print("connecting to ");
  Serial.println(host);



  // This will send the request to the server
  wifiClient.print(String("GET http://192.168.1.214/index1.php?") +
                   ("&bpm=") + updatedBPM +
                   ("&spo2=") + updatedSPO2 +
                   ("&phone=") + phone +
                   ("&userId=") + userID +
                   " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (wifiClient.available() == 0) {
    if (millis() - timeout > 1000) {
      Serial.println(">>> Client Timeout !");
      wifiClient.stop();
      return;
    }
  }
  //--------------------------------- Use WiFiClient class to create TCP connections-----------------------------------
}



void getUserID() {
  Serial.println("Enter User ID:");
  while (Serial.available() == 0) {
    // Wait for user input
  }
  Serial.readBytesUntil('\n', userID, sizeof(userID) - 1); // Read the user input until newline character
  userID[sizeof(userID) - 1] = '\0'; // Add null termination to make it a valid string

  delay(200);
}






void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

//  verifyWifiConnection();
//  getUserID();
  connect_wifi();


  /*---------------------------MAX30100 begin------------------------------*/
  pinMode(pulseLED, OUTPUT);
  pinMode(readLED, OUTPUT);

  // Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println(F("MAX30105 was not found. Please check wiring/power."));
    yield();
    while (1);
  }
  Serial.println("Connection OK");


  byte ledBrightness = 50; //Options: 0=Off to 255=50mA
  byte sampleAverage = 4; //Options: 1, 2, 4, 8, 16, 32
  byte ledMode = 2; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
  byte sampleRate = 200; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
  int pulseWidth = 69; //Options: 69, 118, 215, 411
  int adcRange = 16384; //Options: 2048, 4096, 8192, 16384

  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings
  /*---------------------------MAX30100 begin------------------------------*/
}

void loop() {


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



      //trash calculate
      myBPM = redBuffer[i] / 430;
      mySPO2 = irBuffer[i] / 460;

      //send samples and calculation result to terminal program through UART
      Serial.print(F("red="));
      Serial.print(redBuffer[i], DEC);
      Serial.print(F(", ir="));
      Serial.print(irBuffer[i], DEC);

      Serial.print(F(", HR="));
      Serial.print(myBPM, DEC);

      Serial.print(F(", HRvalid="));
      Serial.print(validHeartRate, DEC);

      Serial.print(F(", SPO2="));
      Serial.print(mySPO2, DEC);

      Serial.print(F(", SPO2Valid="));
      Serial.println(validSPO2, DEC);

      if (validHeartRate) updatedBPM = myBPM;
      if (validSPO2) updatedSPO2 = mySPO2;
    }


    sendDataToDB();

    //After gathering 25 new samples recalculate HR and SP02
    maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);

  }



}
