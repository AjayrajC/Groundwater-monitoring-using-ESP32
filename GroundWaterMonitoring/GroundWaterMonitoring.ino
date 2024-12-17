// Blynk Template
#define BLYNK_TEMPLATE_ID "TMPL3KHiLGLzt"
#define BLYNK_TEMPLATE_NAME "GroundWater Monitoring"
#define BLYNK_AUTH_TOKEN "2l-tyDUuUCLrFHlaNPuu7g9pTShdL-uh"

#define BLYNK_FIRMWARE_VERSION "0.0.1"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "2l-tyDUuUCLrFHlaNPuu7g9pTShdL-uh";
//Enter your WIFI SSID and password
char ssid[] = "LNS PG 2ND FLOOR";
char pass[] =  "lnspg@012";

// Water Monitoring
#define ECHO_PIN 32    // GPIO32 for Echo pin
#define TRIG_PIN 33    // GPIO33 for Trig pin

// Variables to track water usage and yield
float waterUsage = 0;     // Water usage by the owner
float initialWaterLevel = 100;  // Initial water level in the borewell (in cm)
float currentWaterLevel;
float waterYield;  

long duration;

void ultrasonic() {
    // Measure the distance using the ultrasonic sensor
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    duration = pulseIn(ECHO_PIN, HIGH);
    float distance = duration * 0.034 / 2; // Convert duration to distance in cm

    // Calculate the current water level in the borewell
    currentWaterLevel = initialWaterLevel - distance;

    // Calculate water usage by the owner
    waterUsage += calculateUsage(currentWaterLevel);

    // Calculate yield (water remaining after owner's usage)
    waterYield = initialWaterLevel - waterUsage;

    // Output water usage and yield data to Serial Monitor
    Serial.print("Water Usage: ");
    Serial.print(waterUsage);
    Serial.println(" cm");

    Serial.print("Water Yield: ");
    Serial.print(waterYield);
    Serial.println(" cm");

    // Send water usage and yield data to Blynk app
    Blynk.virtualWrite(V1, waterUsage);  // Send water usage data to Blynk
    Blynk.virtualWrite(V2, waterYield);  // Send water yield data to Blynk

    delay(500);
}

// Function to calculate water usage based on the change in water level
float calculateUsage(float currentWaterLevel) {
    static float previousWaterLevel = 100;  // Start with the initial water level
    float usage = previousWaterLevel - currentWaterLevel;
    previousWaterLevel = currentWaterLevel;
    return usage > 0 ? usage : 0;  // Only return positive usage values
}

void setup() {
    Serial.begin(9600);
    pinMode(TRIG_PIN, OUTPUT); 
    pinMode(ECHO_PIN, INPUT); 
    
    // Blynk Initialization
    Blynk.begin(BLYNK_AUTH_TOKEN, "LNS PG 2ND FLOOR", "lnspg@012");
    delay(2000); 
}

void loop() {
    Blynk.run();        // Keep Blynk connection alive
    ultrasonic();       // Measure water usage and update Blynk and Serial Monitor
}