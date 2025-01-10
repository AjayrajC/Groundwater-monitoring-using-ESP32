# Groundwater-monitoring-using-ESP32
This project provides a complete solution for real-time groundwater monitoring using an ESP32 microcontroller, Blynk for remote data monitoring and Google Sheets for logging data. The system measures water levels using an ultrasonic sensor and calculates water usage and remaining water yield. The data is visualized in the Blynk app and logged into Google Sheets for further analysis.

## Hardware Components
- ESP32 Microcontroller (ESP32-WROOM-32)
- HC-SR04 Ultrasonic Sensor
- Breadboard, Jumper Wires
- Power Supply (if not using USB for power)

## Software Requirements
- Arduino IDE with the ESP32 board manager installed
- Blynk Library installed via Arduino Library Manager
- Google Sheets for data logging
- Google Apps Script for handling HTTP requests from ESP32


### Arduino IDE Setup

#### Install the ESP32 Board in Arduino IDE:
- Go to File > Preferences.
- In the "Additional Board Manager URLs" field add the following URL:
https://dl.espressif.com/dl/package_esp32_index.json
- Go to Tools > Board > Boards Manager, search for ESP32 and install the package.
### Install Required Libraries:
Go to Sketch > Include Library > Manage Libraries.
#### Install the following libraries:
- Blynk (Blynk by Volodymyr Shymanskyy)
- WiFi (built-in for ESP32)
### Configure Your Arduino Sketch:
- Clone or download the repository.
- Open the .ino file in the Arduino IDE.
- Replace the WiFi credentials, Blynk template ID and Google Script URL with your own values.
### Google Sheets Setup

1. Create a Google Sheet:
Create a new Google Sheet for logging water usage and yield.
2. Rename the columns to Number, DateTime, Water Usage (cm) and Water Yield (cm) respectively.
3. Google Apps Script Setup:
 Go to Extensions > Apps Script in your Google Sheets.
4. Copy and paste the Google Apps Script code provided in the repository.
5. Save and deploy the script as a Web App:
 Go to Deploy > New deployment.
6. Set the type to Web App.
7. Configure the access to "Anyone" with the link.
8. Copy the Web App URL and update your Arduino sketch with it.
### Google Apps Script Setup

#### Google Apps Script Code:
- Use the provided code.gs file in the repository.
- Ensure the doGet(e) function is correctly handling the incoming data and appending it to the Google Sheet.

#####  Google Sheets Logging: Sends the data to a Google Sheets document for persistent storage.
- Uploading Code to ESP32
- Connect the ESP32 to your computer via USB.
#####  Select the Correct Board and Port:
- Go to Tools > Board, select ESP32 Dev Module.
- Go to Tools > Port and select the appropriate port for your ESP32.
#####  Upload the Sketch:
- Click the Upload button in the Arduino IDE.
#####  Testing and Monitoring
- Serial Monitor: Open the Serial Monitor in Arduino IDE to see real-time water usage and yield data.
- Blynk App: Monitor your water usage and yield via the Blynk app on your mobile device.
- Google Sheets: Check the Google Sheets to ensure data is being logged correctly.

