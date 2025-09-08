- Henrique Keigo Nakashima Minowa - RM:564091
- Eduardo Delorenzo Moraes - RM:561749
- Matheus Bispo Faria Barbosa - RM:562140

# 🌐 FIWARE Smart Lamp – PoC com ESP32
- Projeto de Prova de Conceito (PoC) utilizando ESP32 DEVKIT 1, FIWARE Descomplicado e Postman para monitoramento e controle de uma lâmpada inteligente.
- Este protótipo é parte do estudo de monitoramento global de vinherias, utilizando um sensor LDR para leitura de luminosidade.

## 📋 Requisitos
### 🔧 Hardware
```*(pode fazer ligação direta, sem a necessidade desses materiais)```
- ESP32 DEVKIT 1

- Sensor LDR (fotoresistor)

- *Resistores (para divisor de tensão do LDR)

- Fios jumper fêmea-fêmea

- *Protoboard

### 💻 Software

- Postman → Ferramenta utilizada para realizar requisições HTTP, permitindo testar e validar os endpoints expostos pelo FIWARE. Foi usada aqui para simular o envio e recebimento de dados das lâmpadas inteligentes.

- Cloud Service Provider (exemplo: Microsoft Azure) → Responsável pela criação e hospedagem da máquina virtual (VM) onde o FIWARE Descomplicado foi instalado e configurado. O Azure fornece recursos em nuvem para manter o sistema acessível remotamente.

- FIWARE Descomplicado → Instalado na VM, possibilita a gestão de entidades inteligentes e a integração entre o ESP32 e o Postman.

- Arduino IDE ou PlatformIO (para compilação e envio do código ao ESP32)

- Simulador Wokwi (para testes online)

### 📺 Vídeos de Demonstração

Vídeo que mostra a SmartLamp funcionando: 📺 [Vídeo da simulação funcionando](https://youtu.be/d2TaLoZvgjg?si=l5Gs-5NLf_5yGnTT)

Vídeo que ensina a construir a VM e ligar ao postman: 📺 [Vídeo da simulação no Wokwi](https://www.linkedin.com/posts/diogopelinsonmoraes_fiware-iot-azure-activity-7362259978176397312-avBS?utm_source=social_share_send&utm_medium=member_desktop_web&rcm=ACoAAA4IttQBKDdr5cvPzUTzpVSkZFkQM-qKngk)

