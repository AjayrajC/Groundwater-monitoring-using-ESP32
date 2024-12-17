// Blynk Template Definitions
#define BLYNK_TEMPLATE_ID "TMPL3KHiLGLzt" // Your Blynk Template ID
#define BLYNK_TEMPLATE_NAME "GroundWater Monitoring" // Your Blynk Template Name
#define BLYNK_AUTH_TOKEN "2l-tyDUuUCLrFHlaNPuu7g9pTShdL-uh" // Your Blynk Auth Token

#define BLYNK_FIRMWARE_VERSION "0.0.1"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <BlynkSimpleEsp32.h>

// WiFi Credentials
char ssid[] = "LNS PG 2ND FLOOR";
char pass[] = "lnspg@012";

// Google Sheets script URL
String googleScriptUrl = "https://script.google.com/macros/s/AKfycbxXBMQBVY_HY98Wles8g6WCJyUAWNRmN0XgTdg12iU6tKq4xEgF0T338es8ynNRYYY_/exec"; 

// Water Monitoring Setup
#define ECHO_PIN 32  // GPIO32 for Echo pin
#define TRIG_PIN 33  // GPIO33 for Trig pin

float waterUsage = 0;
float initialWaterLevel = 100; // Assuming a 100 cm deep borewell
float currentWaterLevel;
float waterYield;

long duration;

// Function to measure water level using the ultrasonic sensor
void ultrasonic() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    duration = pulseIn(ECHO_PIN, HIGH);
    float distance = duration * 0.034 / 2; // Convert duration to distance in cm

    // Calculate the current water level
    currentWaterLevel = initialWaterLevel - distance;

    // Calculate water usage and yield
    waterUsage += calculateUsage(currentWaterLevel);
    waterYield = initialWaterLevel - waterUsage;

    // Display data on Blynk
    Blynk.virtualWrite(V1, waterUsage);
    Blynk.virtualWrite(V2, waterYield);

    // Display water usage and yield on Serial Monitor
    Serial.print("Water Usage: ");
    Serial.print(waterUsage);
    Serial.println(" cm");

    Serial.print("Water Yield: ");
    Serial.print(waterYield);
    Serial.println(" cm");

    // Send data to Google Sheets
    sendDataToGoogleSheets(waterUsage, waterYield);

    delay(500); // Short delay between readings
}

// Function to calculate water usage
float calculateUsage(float currentWaterLevel) {
    static float previousWaterLevel = 100; // Initial water level
    float usage = previousWaterLevel - currentWaterLevel;
    previousWaterLevel = currentWaterLevel;
    return usage > 0 ? usage : 0; // Only return positive usage values
}

// Function to send data to Google Sheets
void sendDataToGoogleSheets(float waterUsage, float waterYield) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(googleScriptUrl);

        // Prepare data in JSON format
        String jsonData = "{\"waterUsage\":\"" + String(waterUsage) + "\",\"waterYield\":\"" + String(waterYield) + "\"}";

        http.addHeader("Content-Type", "application/json");

        // Send the request
        int httpResponseCode = http.POST(jsonData);

        // Only print to Serial if the response is not a 302 redirect
        if (httpResponseCode != 302) {
            if (httpResponseCode > 0) {
                String response = http.getString();
                Serial.println(httpResponseCode); 
                Serial.println(response);
            } else {
                Serial.print("Error on sending POST: ");
                Serial.println(httpResponseCode);
            }
        }

        http.end(); // Free resources
    } else {
        Serial.println("Error in WiFi connection");
    }
}

void setup() {
    Serial.begin(9600);
    pinMode(TRIG_PIN, OUTPUT); 
    pinMode(ECHO_PIN, INPUT); 

    // WiFi and Blynk Initialization
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected to WiFi");

    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
    delay(2000); 
}

void loop() {
    Blynk.run();
    ultrasonic();
}
