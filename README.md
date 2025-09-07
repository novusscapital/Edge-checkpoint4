Henrique Keigo Nakashima Minowa - RM:564091
Eduardo Delorenzo Moraes - RM:561749
Matheus Bispo Faria Barbosa - RM:562140

# 🌐 FIWARE Smart Lamp – PoC com ESP32
Projeto de Prova de Conceito (PoC) utilizando ESP32 DEVKIT 1, FIWARE Descomplicado e Postman para monitoramento e controle de uma lâmpada inteligente.
Este protótipo é parte do estudo de monitoramento global de vinherias, utilizando sensor LDR para leitura de luminosidade.

## 📋 Requisitos
🔧 Hardware
- ESP32 DEVKIT 1
- Sensor LDR (fotoresistor)
- Resistores (para divisor de tensão do LDR)
- Fios jumper fêmea-fêmea
- Protoboard

💻 Software
- Postman
- Cloud Service Provider, para criar as VM's (exemplo: Microsoft Azure)
- FIWARE Descomplicado -> instalado na VM
- Arduino IDE ou PlatformIO
- Simulador Wokwi (para testes online)

## 🚀 Passo 1 – Instalação e Configuração
- Crie uma máquina virtual (VM) em um Cloud Service Provider de sua escolha.
- A FIAP disponibiliza créditos para uso do Microsoft Azure.
- Instale o FIWARE Descomplicado na VM criada.
- Repositório oficial: FIWARE Descomplicado no GitHub
- Realize a configuração inicial:
- Configure medidas de segurança (usuário, senha, firewall, regras de rede).
- Execute os procedimentos de Health Check descritos no repositório para validar a instalação.

## 🔧 Passo 2 – Criação da Entidade Lógica (PoC Smart Lamp)
No FIWARE, crie uma entidade representando a lâmpada inteligente.
### Use um ID que corresponda ao protótipo:
```
{
  "id": "SmartLamp:001",
  "type": "Lamp",
  "status": "off",
  "luminosity": 0
}
```


### Configure a comunicação do ESP32:
O ESP32 DEVKIT 1 com sensor LDR será responsável por enviar dados de luminosidade para a entidade.
O envio é feito via requisições HTTP para a API do FIWARE Descomplicado.

## 🎥 Passo 3 – Apresentação de Evidências

📺 [Vídeo da simulação funcionando](https://youtu.be/d2TaLoZvgjg?si=l5Gs-5NLf_5yGnTT)
