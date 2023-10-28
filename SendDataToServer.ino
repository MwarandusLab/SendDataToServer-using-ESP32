#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "your_wifi_ssid";
const char* password = "your_wifi_password";

const char* serverName = "http://yourdomain.com/your_endpoint"; // Replace with your domain and endpoint

const int BUFFER_SIZE = 14;
const int DATA_TAG_SIZE = 8;

SoftwareSerial ssrfid = SoftwareSerial(12, 8);

uint8_t buffer[BUFFER_SIZE];
int buffer_index = 0;
boolean tagRead = false;
boolean tagRemoved = true;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  
  ssrfid.begin(9600);
  ssrfid.listen();

  Serial.println("INIT DONE");
}

void loop() {
  // RFID reading logic remains the same as before

  // Sending the tag to the server if it's read
  if (tagRead) {
    sendTagToServer();
    tagRead = false; // Reset tagRead after sending the tag
  }
}

void sendTagToServer() {
  String tag = extract_tag_string(); // Convert the tag to a String
  String url = serverName + "?tag=" + tag;

  HTTPClient http;
  http.begin(url);

  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
  } else {
    Serial.println("Error in HTTP request");
  }

  http.end();
}

String extract_tag_string() {
  // Extract the tag and convert it to a String
  // ... (rest of the extract_tag function)
}
