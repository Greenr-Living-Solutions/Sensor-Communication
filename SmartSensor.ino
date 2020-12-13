
#include <WiFi.h>
#include <WiFiNINA.h>

HTTPClient http;

//SSID of your network
char ssid[] = "Araquis";
//password of your WPA Network
char pass[] = "fatkitty";

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
}

String url = "https://greenr-energy-solutions.firebaseio.com/test.json";  http.setTimeout(1000);
http.begin(url);
// Issue the HTTP GET request.
int status = http.GET();
if (status <= 0) {
  Serial.printf("HTTP error: %s\n", 
      http.errorToString(status).c_str());
  return;
}
// Read the response.
String payload = http.getString();
Serial.println("Got HTTP response:");
Serial.println(payload);
