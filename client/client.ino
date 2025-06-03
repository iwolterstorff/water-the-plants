#include <WiFi.h>
#include <PubSubClient.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

#define MQTT_PORT 1883

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void setup() {
    LittleFS.begin();

    File file = LittleFS.open("/secrets.json", "r");
    if (file) {
        JsonDocument doc;
        deserializeJson(doc, file);
        const char* ssid = doc["ssid"];
        const char* psk = doc["psk"];
        const char* brokerIP = doc["mqtt_broker_ip"];
        Wifi.begin(ssid, psk);
        if (status != WL_CONNECTED) {
            // explode
            while(true);
        }
        mqttClient.setServer(brokerIP, MQTT_PORT);
    }
}

void loop() {

}
