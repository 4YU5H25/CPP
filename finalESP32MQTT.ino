// INCLUDING LIBRARIES
#include <WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <DHT.h>

//  WIFI ID AND PASSWORD DECLARED
#define WLAN_SSID       "Rg"
#define WLAN_PASS       "ayush@25"

// ADAFRUIT SERVER DETAILS 
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   
#define AIO_USERNAME    "4YU5H"
#define AIO_KEY         "aio_GFfA01AUcyBQCc3nWVrTD0d6AfVv"


// LED AND SENSOR PIN DECLARATION
#define LED 2
#define DHTPIN 5                    
#define DHTTYPE DHT11        
         
// DHT OBJECT CREATED
DHT dht(DHTPIN, DHTTYPE);

// WIFI CLIENT CLASS INSTANCE CREATED
WiFiClient client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// SETTING UP ESSENTIAL FEEDS 
Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Temperature");
Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Humidity");
Adafruit_MQTT_Subscribe led = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/led");

// SETUP PART
void setup() {

  // ESP32 - COMPUTER COMMUNICATION BAUD RATE -- 115200 
  Serial.begin(115200);
  delay(10);

  // DHT SENSOR STARTS CAPTURING TEMPERATURE AND HUMIDITY DATA
  dht.begin();
  
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);
  
  WiFi.begin(WLAN_SSID, WLAN_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); // FUNCTION TO RETURN IP ADDRESS OF THE CONNECTED WIFI
  mqtt.subscribe(&led);
}

void loop() {

//  DECLARING VARIABLES
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  MQTT_connect();
  
 
   Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000)))
  {
    if (subscription == &led)
    {
      // Storing the data
      char* Data = (char*) led.lastread;
      Serial.print("Got: ");
      Serial.println(Data);

      // comparing the data
      // IF TOGGLE SWITCH IS PRESSED ONLY THEN THE DATA WILL BE SHARED AND SIMULTANEOUSLY LED WILL TURN ON
      if (strstr(Data, "1"))
      {
        digitalWrite(LED, HIGH);
        temperature.publish(t);
        humidity.publish(h);
        Serial.print("Humidity: ");
        Serial.print(h);
        Serial.print(" %\t");
        Serial.print("Temperature: ");
        Serial.print(t);
        Serial.println(" *C ");
      }
      if (strstr(Data, "0"))
      {
        digitalWrite(LED, LOW);
      }
    }
  }  
}

// MQTT CONNECT FUNCTION PRESENT IN EXAMPLES
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
