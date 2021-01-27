#include <SPI.h>
#include <WiFiNINA.h>
#include "DHT.h"
#include <ArduinoHttpClient.h>

char ssid[] = "ATTAB6jbtA";
char pass[] = "fv3fw6t=k3r6";

char serverAddress[] = "192.168.1.68";  // server address
int port = 8080;

WiFiClient wifi;
WebSocketClient client = WebSocketClient(wifi, serverAddress, port);
int status = WL_IDLE_STATUS;

DHT sensor(7, DHT11);

void setup() {

  sensor.begin(9600);
  Serial.begin(9600);

  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
  }

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

}

void loop() {

  client.begin();

  while (client.connected()) {

  int sound = digitalRead(2);

  int temperature = sensor.readTemperature();
  int humidity = sensor.readHumidity();

  if (sound == 1) {
    
    client.beginMessage(TYPE_TEXT);
    client.print(millis());
    client.print(" ");
    client.print(sound);
    client.print(" ");
    client.print(temperature);
    client.print(" ");
    client.print(humidity);
    client.endMessage();

    delay(500);
  }

  if (millis() % 1000 == 0) {

    client.beginMessage(TYPE_TEXT);
    client.print(millis());
    client.print(" ");
    client.print(sound);
    client.print(" ");
    client.print(temperature);
    client.print(" ");
    client.print(humidity);
    client.endMessage();

    delay(200);

  }

  }

  Serial.println("Disconnected from server. Reconnecting...");

  client.isFinal();

}
