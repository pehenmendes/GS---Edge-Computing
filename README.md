# GS - Edge Computing

## Integrantes 👋
<ul>
    <li>Pedro Henrique Mendes dos Santos (RM555332)</li>
    <li>Gabriel Barros Cisoto (RM556309)</li>  
    <li>Pedro Henrique Bizzo de Santana (RM557263)</li>
</ul>
 
<img src="./ESP32.png" alt="print do circuito Arduino/printscreen Arduino circuit"/>

Link da simulação no <a href="https://wokwi.com/projects/414726253290118145">Wokwi</a>

## Explicação do Projeto 📖
Este projeto implementa um sistema de monitoramento de luminosidade e temperatura usando um microcontrolador com Wi-Fi integrado, um sensor DHT, e comunicação com um broker MQTT.

## Instruções
<ul>
    <li>Faça o upload do código no seu microcontrolador, após configurar os parâmetros de rede Wi-Fi e MQTT.</li>
    <li>Monitore o status da conexão e os dados do sensor via o broker MQTT.</li>
</ul>

## Componentes 🛠️
<ul>
    <li>ESP32</li>
    <li>DHT11/22</li>
    <li>LDR</li>
</ul>
 
<br>

## Explicando o <a href="https://github.com/pehenmendes/GS---Edge-Computing/blob/main/fiware_IOT.cc">Código</a> 🧑‍💻

### Dependências 📦
<ul>
    <li>WiFi.h</li>
    <li>PubSubClient.h</li>
    <li>DHT.h</li>
</ul>
 
<br>
 
Este código é responsável por conectar o dispositivo IoT à rede Wi-Fi e ao Broker MQTT para enviar e receber dados dos sensores e controlar o estado de saída do dispositivo.

**Principais Funcionalidades**:
<ul>
    <li>Wi-Fi: Conexão com a rede Wi-Fi utilizando o nome e senha configurados.</li>
    <li>MQTT: Publicação e assinatura em tópicos MQTT para enviar dados de sensores e receber comandos do broker.</li>
    <li>Tópicos utilizados:</li>
        <ul>
            <li>/TEF/device010/attrs: Publica o estado do dispositivo.</li>
            <li>/TEF/device010/attrs/luminosity: Publica o valor da luminosidade.</li>
            <li>/TEF/device010/attrs/dht: Publica dados do sensor DHT (temperatura.</li>
        </ul>
    <li>DHT22: Leitura de temperatura e umidade usando o sensor DHT22.</li>
    <li>Luminosidade: Lê valores de luminosidade simulados e os publica no Broker MQTT.</li>
    <li>Gerenciamento de Conexões: Reconecta automaticamente ao Wi-Fi e ao Broker MQTT em caso de desconexão.</li>
</ul>

<br>

## Estrutura de Tópicos MQTT

| Tópico                        | Descrição                                     |
|-------------------------------|-----------------------------------------------|
| `/TEF/device010/attrs`         | Publicação do estado do LED (ligado/desligado)|
| `/TEF/device010/attrs/luminosity`       | Publicação do valor da luminosidade          |
| `/TEF/device010/attrs/dht`     | Publicação de temperatura           |

<br>
