#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include "DHT.h"

#define DHTTYPE DHT11   // Kullandığımız sensörün tipi DHT 11
#define DHTPIN D4
#define BLYNK_PRINT Serial 

// Insert your network credentials
#define WIFI_SSID "Ahmet"
#define WIFI_PASSWORD "Aydeniz123."

// Insert Firebase project API Key
#define API_KEY "AIzaSyDTnYOFqZPB-gzTlxm-t6M5ifrZci2meZw"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://deneme-efeb4-default-rtdb.firebaseio.com/" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;
DHT dht(DHTPIN, DHTTYPE);

unsigned long sendDataPrevMillis = 0;
int count = 0;

void setup(){
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop(){
  if (Firebase.ready()){
    sendDataPrevMillis = millis();
    float hum = dht.readHumidity();
    char temp = dht.readTemperature();
     Serial.print(F("Humidity: "));
     Serial.print(hum);
     Serial.print(F("%  Temperature: "));
     Serial.print(temp);
    // Write an Float number on the database path test/float
   Firebase.RTDB.setFloat(&fbdo, "DHT/Nem", hum);
   Firebase.RTDB.setFloat(&fbdo, "DHT/Sicaklik", temp);

      
  }
  
  
}