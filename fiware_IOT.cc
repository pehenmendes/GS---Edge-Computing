#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// Configurações - variáveis editáveis
const char* default_SSID = "Wokwi-GUEST"; // Nome da rede Wi-Fi
const char* default_PASSWORD = ""; // Senha da rede Wi-Fi
const char* default_BROKER_MQTT = "34.171.152.225"; // IP do Broker MQTT
const int default_BROKER_PORT = 1883; // Porta do Broker MQTT
const char* default_TOPICO_SUBSCRIBE = "/TEF/device010/cmd"; // Tópico MQTT de escuta
const char* default_TOPICO_PUBLISH_1 = "/TEF/device010/attrs"; // Tópico MQTT de envio de informações para Broker
const char* default_TOPICO_PUBLISH_2 = "/TEF/device010/attrs/luminosity"; // Tópico MQTT para luminosidade
const char* default_TOPICO_PUBLISH_DHT = "/TEF/device010/attrs/dht"; // Tópico MQTT para DHT
const char* default_ID_MQTT = "fiware_010"; // ID MQTT

// Configurações do sensor DHT
#define DHTPIN 15        // Pino do sensor DHT
#define DHTTYPE DHT22    // Tipo do sensor (DHT11, DHT22, etc.)
DHT dht(DHTPIN, DHTTYPE);

// Configurações do LDR
#define LDR_PIN 34       // Pino do sensor LDR

WiFiClient espClient;
PubSubClient MQTT(espClient);

void initSerial() {
    Serial.begin(115200);
}

void initWiFi() {
    delay(10);
    Serial.println("------Conexao WI-FI------");
    Serial.print("Conectando-se na rede: ");
    Serial.println(default_SSID);
    Serial.println("Aguarde");
    reconectWiFi();
}

void initMQTT() {
    MQTT.setServer(default_BROKER_MQTT, default_BROKER_PORT);
}

void setup() {
    initSerial();
    initWiFi();
    initMQTT();
    dht.begin(); // Inicializa o sensor DHT
    pinMode(LDR_PIN, INPUT); // Configura o pino do LDR como entrada
    delay(5000);
}

void loop() {
    VerificaConexoesWiFIEMQTT();
    handleLuminosity(); // Lida com a leitura do LDR
    handleDHT();        // Lida com as leituras do DHT
    MQTT.loop();
    delay(1000);
}

void reconectWiFi() {
    if (WiFi.status() == WL_CONNECTED)
        return;
    WiFi.begin(default_SSID, default_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("Conectado com sucesso na rede ");
    Serial.print(default_SSID);
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP());
}

void VerificaConexoesWiFIEMQTT() {
    if (!MQTT.connected())
        reconnectMQTT();
    reconectWiFi();
}

void reconnectMQTT() {
    while (!MQTT.connected()) {
        Serial.print("* Tentando se conectar ao Broker MQTT: ");
        Serial.println(default_BROKER_MQTT);
        if (MQTT.connect(default_ID_MQTT)) {
            Serial.println("Conectado com sucesso ao broker MQTT!");
            MQTT.subscribe(default_TOPICO_SUBSCRIBE);
        } else {
            Serial.println("Falha ao reconectar no broker. Tentando novamente em 2 segundos...");
            delay(2000);
        }
    }
}

void handleLuminosity() {
    int ldrValue = analogRead(LDR_PIN); // Lê o valor do sensor LDR
    int luminosity = map(ldrValue, 0, 4095, 0, 100); // Converte para um percentual
    String mensagem = String(luminosity);
    Serial.print("\nLuminosidade: ");
    Serial.println(mensagem.c_str());
    MQTT.publish(default_TOPICO_PUBLISH_2, mensagem.c_str()); // Publica o valor de luminosidade
}

void handleDHT() {
    float temperature = dht.readTemperature();

    if (isnan(temperature)) {
        Serial.println("Falha na leitura do sensor DHT!");
        return;
    }

    String mensagem = "t:" + String(temperature);
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.print(" °C");

    MQTT.publish(default_TOPICO_PUBLISH_DHT, mensagem.c_str()); // Publica temperatura
}