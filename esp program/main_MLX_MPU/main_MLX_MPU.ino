#include <ESP8266WiFi.h>
#include <Adafruit_MLX90614.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>



Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Adafruit_MPU6050 mpu;

const unsigned long WIFI_CONNECT_TIMEOUT = 5000; // Wi-Fi connection timeout in milliseconds

float maxRotX=0, maxRotY=0, maxRotZ=0;


/*----------------------------wifi param--------------------------------*/
// Insert your network credentials
char ssid[50] = "PHONG TRO 36/4 -1";
char pass[50] = "0934085190";
char userID[5] = "46";

char* host = "192.168.1.214";
WiFiClient wifiClient;
/*----------------------------wifi param--------------------------------*/





void connect_wifi(){
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




void MPU_Setup(){
  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
//    while (1) {
//      delay(10);
//    }
    
  }

  else{
      Serial.println("MPU6050 Found!");
    
      mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
      Serial.print("Accelerometer range set to: ");
      switch (mpu.getAccelerometerRange()) {
      case MPU6050_RANGE_2_G:
        Serial.println("+-2G");
        break;
      case MPU6050_RANGE_4_G:
        Serial.println("+-4G");
        break;
      case MPU6050_RANGE_8_G:
        Serial.println("+-8G");
        break;
      case MPU6050_RANGE_16_G:
        Serial.println("+-16G");
        break;
      }
      mpu.setGyroRange(MPU6050_RANGE_500_DEG);
      Serial.print("Gyro range set to: ");
      switch (mpu.getGyroRange()) {
      case MPU6050_RANGE_250_DEG:
        Serial.println("+- 250 deg/s");
        break;
      case MPU6050_RANGE_500_DEG:
        Serial.println("+- 500 deg/s");
        break;
      case MPU6050_RANGE_1000_DEG:
        Serial.println("+- 1000 deg/s");
        break;
      case MPU6050_RANGE_2000_DEG:
        Serial.println("+- 2000 deg/s");
        break;
      }
    
      mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
      Serial.print("Filter bandwidth set to: ");
      switch (mpu.getFilterBandwidth()) {
      case MPU6050_BAND_260_HZ:
        Serial.println("260 Hz");
        break;
      case MPU6050_BAND_184_HZ:
        Serial.println("184 Hz");
        break;
      case MPU6050_BAND_94_HZ:
        Serial.println("94 Hz");
        break;
      case MPU6050_BAND_44_HZ:
        Serial.println("44 Hz");
        break;
      case MPU6050_BAND_21_HZ:
        Serial.println("21 Hz");
        break;
      case MPU6050_BAND_10_HZ:
        Serial.println("10 Hz");
        break;
      case MPU6050_BAND_5_HZ:
        Serial.println("5 Hz");
        break;
  }     
  }
 
}




void MLX_Setup(){
  Serial.println("Adafruit MLX90614 test");

  if (!mlx.begin()) {
    Serial.println("Error connecting to MLX sensor. Check wiring.");
    while (1);
  };

  Serial.print("Emissivity = "); Serial.println(mlx.readEmissivity());
  Serial.println("================================================");  
}



void MPU_Print_Data(){
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  
  Serial.print("Rotation X: ");
  Serial.print(maxRotX);
  Serial.print(", Y: ");
  Serial.print(maxRotY);
  Serial.print(", Z: ");
  Serial.print(maxRotZ);
  Serial.println(" rad/s");

  if(g.gyro.x > maxRotX) maxRotX = g.gyro.x;
  if(g.gyro.y > maxRotY) maxRotY = g.gyro.y;
  if(g.gyro.z > maxRotZ) maxRotZ = g.gyro.z;

}



void sendDataToDB(float bodyTemp){
        const int httpPort = 80;
        if (!wifiClient.connect(host, httpPort)) {
            Serial.println("connection failed");
            return;
        }

        Serial.println("Sent body temp: ");
        Serial.println(bodyTemp);
    
        Serial.print("connecting to ");
        Serial.println(host);
    
    
        
        // This will send the request to the server
        wifiClient.print(String("GET http://192.168.2.214/receiveArmBand.php?") + 
                              ("&bodyTemp=") + bodyTemp + 
                              ("&rotX=") + maxRotX + 
                              ("&rotY=") + maxRotY + 
                              ("&rotZ=") + maxRotZ + 
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
}




void getWifiInfor(){
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



void verifyWifiConnection(){
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
  Serial.begin(9600);
  while (!Serial);
  delay(1000);

  //  verifyWifiConnection();
  //  getUserID();
  connect_wifi();

  
  MPU_Setup();
  MLX_Setup();
  

}

void loop() {
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC());
  
  float bodyTemp = mlx.readObjectTempC() + 2.8;
  Serial.print("  Object = "); Serial.print(bodyTemp); Serial.println("*C");

  MPU_Print_Data();

  sendDataToDB(bodyTemp);

  Serial.println();
  delay(500);
}
