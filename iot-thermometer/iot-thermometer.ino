// Tento program je určený pro desku NodeMCU 12E
// měl by běžet na jakékoliv desce využívající ESP8266

#include <DHT.h>
#include <ESP8266WiFi.h>

// Network information.
#define WIFI_NAME           "wifiname"
#define WIFI_PASSWORD       "wifipass"
#define TIMEOUT             5000
#define DELAY_TIME          300e3   // measures and sends data every 5 minutes  
#define CONNECTION_RETRIES  3
#define THING_SPEAK_ADDRESS "api.thingspeak.com"
#define API_KEY             "API_KEY"    
#define NUM_FIELDS          3 

const byte PIN_LED = LED_BUILTIN;
const byte PIN_DHT = D4;     // Digital pin connected to the DHT sensor
const byte PIN_MOISTURE = A0; 

DHT dht(PIN_DHT, DHT11); 
WiFiClient client;

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  pinMode(PIN_LED, OUTPUT);
  // turn the LED off
  digitalWrite(PIN_LED, HIGH);
}

void loop() {
  float temperature = dht.readTemperature();
  Serial.print("temperature: ");
  Serial.print(temperature);

  float humidity = dht.readHumidity();
  Serial.print(", humidity: ");
  Serial.print(humidity);

  float moistureReading = analogRead(PIN_MOISTURE);
  float moisture = map(moistureReading, 0, 1023, 100, 0);
  Serial.print(", moisture: ");
  Serial.print(moisture);

  Serial.println();

  // Write to successive fields in your channel by filling fieldData with up to 8 values.
  String data[NUM_FIELDS+1];  
  
  data[1] = String(temperature); 
  data[2] = String(humidity); 
  data[3] = String(moisture); 
  
  sendData(NUM_FIELDS, data, API_KEY);

  // delay after each reading
  delay(DELAY_TIME);
}

void connectWifi(String networkName, String password)
{
    for (int i = 0; i < CONNECTION_RETRIES; i++) {
        WiFi.begin(networkName, password);
        Serial.print("Connecting to WiFi: ");
        Serial.println(networkName);

        if (wifiConnected()) {
          break;
        }
        delay(TIMEOUT);
    }

    if (wifiConnected()) {
      Serial.println("Connected!");
    } else {
      Serial.println("Wifi connection failed!");
    }
}

bool wifiConnected() {
  return WiFi.status() == WL_CONNECTED;
}

int sendData(int numFields, String fieldData[], String apiKey){
  if (!wifiConnected()) {
    connectWifi(WIFI_NAME, WIFI_PASSWORD);
  }
  
  if (client.connect(THING_SPEAK_ADDRESS, 80)) {
     // Build the postData string.  
     // If you have multiple fields, make sure the sting does not exceed 1440 characters.
     String postData= "api_key=" + apiKey ;
     for ( int fieldNumber = 1; fieldNumber < numFields+1; fieldNumber++ ){
          String fieldName = "field" + String( fieldNumber );
          postData += "&" + fieldName + "=" + fieldData[fieldNumber];     
     }

    // POST data via HTTP.
  //  Serial.println(postData);
    
    client.println("POST /update HTTP/1.1" );
    client.println("Host: api.thingspeak.com" );
    client.println("Connection: close" );
    client.println("Content-Type: application/x-www-form-urlencoded" );
    client.println("Content-Length: " + String(postData.length()));
    client.println();
    client.println(postData);

    Serial.println("Data sent to the ThingSpeak server.");
    
    digitalWrite(PIN_LED, LOW);
    delay(1000);
    digitalWrite(PIN_LED, HIGH);
  }
  else
  {
    Serial.println("Sending data to the server failed!");
  }
}