#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "ngoga";
const char* password = "keza1123";
const char* servername = "http://192.168.0.125/final/insert.php";

#define triggerPin 7
#define echoPin 6
#define ledred 8
#define ledgreen 5

void setup() {

  Serial.begin(115200);

  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(ledred, OUTPUT);
  pinMode(ledgreen, OUTPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {

  if (WiFi.status() == WL_CONNECTED) {

    long duration;
    long distance;

    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);

    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(triggerPin, LOW);

    duration = pulseIn(echoPin, HIGH);

    distance = (duration * 0.034) / 2;

    HTTPClient http;
    http.begin(servername);
    http.addHeader("Content-Type", "application/json");

    StaticJsonDocument<200> doc;

    doc["distance"] = distance;

    if(distance < 10){

      doc["status"] = "Danger";

      digitalWrite(ledred, HIGH);
      digitalWrite(ledgreen, LOW);

    } else {

      doc["status"] = "Safe";

      digitalWrite(ledred, LOW);
      digitalWrite(ledgreen, HIGH);
    }

    String postData;
    serializeJson(doc, postData);

    Serial.println(postData);

    int httpResponseCode = http.POST(postData);

    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    if(httpResponseCode > 0){
      String response = http.getString();
      Serial.println(response);
    }

    http.end();
  }

  delay(1000);
}