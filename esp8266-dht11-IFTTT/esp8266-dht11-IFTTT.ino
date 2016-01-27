#include "DHT.h"
#include <ESP8266WiFi.h>

#define DHTPIN 2 
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

const char* ssid     = "TP-LINK_BUC_2.4";
const char* password = "02414706";
const char* host = "maker.ifttt.com";
const int httpPort = 80;

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == 6) {
    ESP.restart();
  }
  
  WiFiClient client;
  
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }else{
    client.print(String("GET ") + "/trigger/esp8266/with/key/o95QzDMozY-8qRRCsZsFO?value1=" + t + "&value2="+ h + " HTTP/1.1\r\n" +
             "Host: " + host + "\r\n" + 
             "Connection: close\r\n\r\n");
    //  delay(100);
    //  while(client.available()){
    //    String line = client.readStringUntil('\r');
    //    Serial.print(line);
    //  }
      
    Serial.print("Humidity: ");
    Serial.println(h);
    //  Serial.print(" %\t");
    //  Serial.print("Temperature: ");
    //  Serial.print(t);
    //  Serial.println(" *C ");
    delay(900000);//15 min
  }
}
