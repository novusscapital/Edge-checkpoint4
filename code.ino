/*
 Projeto: Smart Lamp - PoC FIWARE com ESP32
 Autores: Matheus Bispo, Eduardo Delorenzo, Henrique Keigo
 Data: 07/09/2025
*/

#include <WiFi.h>           // Biblioteca para conexão Wi-Fi
#include <PubSubClient.h>   // Biblioteca para comunicação MQTT

// ========================= CONFIGURAÇÕES INICIAIS ==========================

// Configurações editáveis de Wi-Fi e Broker
const char* default_SSID = "REDE1";        // Nome da rede Wi-Fi
const char* default_PASSWORD = "SENHA2";  // Senha da rede Wi-Fi
const char* default_BROKER_MQTT = "20.163.23.245"; // IP do Broker MQTT
const int default_BROKER_PORT = 1883;         // Porta padrão MQTT

// Definição dos tópicos MQTT
const char* default_TOPICO_SUBSCRIBE = "/TEF/lamp001/cmd";   // Recebe comandos do Broker
const char* default_TOPICO_PUBLISH_1 = "/TEF/lamp001/attrs"; // Publica estado da lâmpada
const char* default_TOPICO_PUBLISH_2 = "/TEF/lamp001/attrs/l"; // Publica valor de luminosidade

// Identificação do cliente MQTT
const char* default_ID_MQTT = "fiware_001";  

// Pino do LED onboard do ESP32
const int default_D4 = 2;

// Prefixo usado para construir as mensagens de comando
const char* topicPrefix = "lamp001";

// ========================= VARIÁVEIS GLOBAIS ==========================

// Ponteiros para manter valores de configuração
char* SSID = const_cast<char*>(default_SSID);
char* PASSWORD = const_cast<char*>(default_PASSWORD);
char* BROKER_MQTT = const_cast<char*>(default_BROKER_MQTT);
int BROKER_PORT = default_BROKER_PORT;
char* TOPICO_SUBSCRIBE = const_cast<char*>(default_TOPICO_SUBSCRIBE);
char* TOPICO_PUBLISH_1 = const_cast<char*>(default_TOPICO_PUBLISH_1);
char* TOPICO_PUBLISH_2 = const_cast<char*>(default_TOPICO_PUBLISH_2);
char* ID_MQTT = const_cast<char*>(default_ID_MQTT);
int D4 = default_D4;

// Objetos de rede
WiFiClient espClient;           // Cliente Wi-Fi
PubSubClient MQTT(espClient);   // Cliente MQTT (roda sobre TCP/IP)

// Estado atual do LED (0 = desligado, 1 = ligado)
char EstadoSaida = '0';

// ========================= FUNÇÕES AUXILIARES ==========================

// Inicializa o monitor serial
void initSerial() {
    Serial.begin(115200);
}

// Conecta o ESP32 ao Wi-Fi
void initWiFi() {
    delay(10);
    Serial.println("------Conexao WI-FI------");
    Serial.print("Conectando-se na rede: ");
    Serial.println(SSID);
    Serial.println("Aguarde");
    reconectWiFi(); // Tenta se conectar
}

// Configura conexão MQTT
void initMQTT() {
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);   // Define o broker e porta
    MQTT.setCallback(mqtt_callback);            // Função que será chamada quando chegar mensagem
}

// Função principal de setup
void setup() {
    InitOutput();   // Pisca o LED para indicar inicialização
    initSerial();   // Inicia monitor serial
    initWiFi();     // Conecta ao Wi-Fi
    initMQTT();     // Configura MQTT
    delay(5000);

    // Publica estado inicial da lâmpada (ligada)
    MQTT.publish(TOPICO_PUBLISH_1, "s|on");
}

// Loop principal do programa
void loop() {
    VerificaConexoesWiFIEMQTT(); // Garante que Wi-Fi e MQTT estão ativos
    EnviaEstadoOutputMQTT();     // Envia estado atual da lâmpada ao broker
    handleLuminosity();          // Lê sensor LDR e envia luminosidade
    MQTT.loop();                 // Mantém a conexão MQTT viva
}

// ========================= CONEXÃO WI-FI ==========================

// Tenta reconectar ao Wi-Fi caso caia
void reconectWiFi() {
    if (WiFi.status() == WL_CONNECTED)
        return;
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("Conectado com sucesso na rede ");
    Serial.print(SSID);
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP());

    // Garante que o LED inicie desligado
    digitalWrite(D4, LOW);
}

// ========================= CALLBACK MQTT ==========================

// Função chamada quando chega mensagem MQTT
void mqtt_callback(char* topic, byte* payload, unsigned int length) {
    String msg;
    for (int i = 0; i < length; i++) {
        char c = (char)payload[i];
        msg += c;
    }
    Serial.print("- Mensagem recebida: ");
    Serial.println(msg);

    // Cria os comandos esperados
    String onTopic = String(topicPrefix) + "@on|";   // Exemplo: lamp001@on|
    String offTopic = String(topicPrefix) + "@off|"; // Exemplo: lamp001@off|

    // Se a mensagem for ligar
    if (msg.equals(onTopic)) {
        digitalWrite(D4, HIGH);
        EstadoSaida = '1';
    }

    // Se a mensagem for desligar
    if (msg.equals(offTopic)) {
        digitalWrite(D4, LOW);
        EstadoSaida = '0';
    }
}

// ========================= GERENCIAMENTO DE CONEXÕES ==========================

// Verifica se Wi-Fi e MQTT estão ativos
void VerificaConexoesWiFIEMQTT() {
    if (!MQTT.connected())
        reconnectMQTT();
    reconectWiFi();
}

// Envia ao broker o estado atual do LED
void EnviaEstadoOutputMQTT() {
    if (EstadoSaida == '1') {
        MQTT.publish(TOPICO_PUBLISH_1, "s|on");
        Serial.println("- Led Ligado");
    }

    if (EstadoSaida == '0') {
        MQTT.publish(TOPICO_PUBLISH_1, "s|off");
        Serial.println("- Led Desligado");
    }
    Serial.println("- Estado do LED onboard enviado ao broker!");
    delay(1000);
}

// Inicializa o LED onboard piscando (efeito de boot)
void InitOutput() {
    pinMode(D4, OUTPUT);
    digitalWrite(D4, HIGH);
    boolean toggle = false;

    for (int i = 0; i <= 10; i++) {
        toggle = !toggle;
        digitalWrite(D4, toggle);
        delay(200);
    }
}

// Tenta reconectar ao Broker MQTT
void reconnectMQTT() {
    while (!MQTT.connected()) {
        Serial.print("* Tentando se conectar ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT)) {
            Serial.println("Conectado com sucesso ao broker MQTT!");
            MQTT.subscribe(TOPICO_SUBSCRIBE); // Reassina o tópico
        } else {
            Serial.println("Falha ao reconectar no broker.");
            Serial.println("Haverá nova tentativa de conexão em 2s");
            delay(2000);
        }
    }
}

// ========================= SENSOR DE LUMINOSIDADE ==========================

// Lê o valor do LDR e envia ao Broker
void handleLuminosity() {
    const int potPin = 34; // Entrada analógica do ESP32
    int sensorValue = analogRead(potPin); // Valor entre 0 e 4095
    int luminosity = map(sensorValue, 0, 4095, 0, 100); // Converte para escala %
    String mensagem = String(luminosity);

    Serial.print("Valor da luminosidade: ");
    Serial.println(mensagem.c_str());

    // Publica no tópico do Broker
    MQTT.publish(TOPICO_PUBLISH_2, mensagem.c_str());
}
