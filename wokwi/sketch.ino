#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "DHTesp.h"

const char* WIFI_SSID = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";

const char* MQTT_SERVER = "f7add22f5aca4e419d7f16f464a29f35.s1.eu.hivemq.cloud";
const int MQTT_PORT = 8883;
const char* MQTT_USER = "carlos";
const char* MQTT_PASSWORD = "Kaka1212$";

const char* TOPIC_JSON = "fiap/maquina1/dados";

WiFiClientSecure espClient;
PubSubClient client(espClient);
DHTesp dhtSensor;

const int DHT_PIN = 15;
const int LDR_PIN = 34;

void conectaWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectando no WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");
}

void conectaMQTT() {
  while (!client.connected()) {
    String clientId = "esp32-wokwi-";
    clientId += String(random(1000, 9999));

    Serial.print("Conectando ao MQTT...");
    if (client.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD)) {
      Serial.println(" conectado!");
    } else {
      Serial.print(" falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 2s");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  conectaWiFi();

  espClient.setInsecure(); 
  client.setServer(MQTT_SERVER, MQTT_PORT);
}

void loop() {
  if (!client.connected()) {
    conectaMQTT();
  }
  client.loop();

  TempAndHumidity data = dhtSensor.getTempAndHumidity();
  float temperatura = data.temperature;
  int luminosidade = analogRead(LDR_PIN);

  String payloadJson = "{";
  payloadJson += "\"temperatura\":";
  payloadJson += String(temperatura, 2);
  payloadJson += ",";
  payloadJson += "\"luminosidade\":";
  payloadJson += String(luminosidade);
  payloadJson += "}";

  client.publish(TOPIC_JSON, payloadJson.c_str());

  Serial.println(payloadJson);
  delay(5000);
}
