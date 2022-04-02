#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid ="MySpectrumWiFi68-2G";
const char* password = "orangewhale940";

// Create an AsyncWebServer object on port 80
AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>ESP Web Server</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:,">
    <style>
        html {
            font-family: Arial;
            text-align: center;
        }
        body {
            max-width: 400px;
            margin:0px auto;
        }
    </style>
</head>
<body>
    <h1>Hello, world!</h1>
    <p>Congratulations!<br>This is your first Web Server with the ESP.</p>
</body>
</html>
)rawliteral";

void initWiFi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(1000);
    }
    Serial.println(WiFi.localIP());
}

void setup() {
    // Serial port for debugging purposes
    Serial.begin(115200);
    initWiFi();

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/html", index_html);
    });
    // Start server
    server.begin();
}

void loop() {}