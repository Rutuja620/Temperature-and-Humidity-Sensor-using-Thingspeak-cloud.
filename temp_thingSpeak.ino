#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ThingSpeak.h>

#define DHTPIN D1
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "realme 9i";
const char* password = "12344321";

unsigned long channelID = 3385479;
const char* writeAPIKey = "K1DPGSA55KJXKM7L";

WiFiClient client;

void setup() {
  Serial.begin(115200);

  dht.begin();

  WiFi.begin(ssid, password);

  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");

  ThingSpeak.begin(client);
}

void loop() {

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);

  ThingSpeak.writeFields(channelID, writeAPIKey);

  Serial.println("Data Sent to ThingSpeak");
  Serial.println("----------------------");

  delay(20000); // wait 20 seconds
}
