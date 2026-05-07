## Descrição do projeto

Este projeto apresenta uma solução de monitoramento inteligente com IoT utilizando **ESP32, MQTT, Node-RED e MySQL**. A proposta é simular o monitoramento de um ambiente ou processo por meio da coleta de dados de sensores, envio das informações em tempo real para um broker MQTT, processamento no Node-RED, armazenamento em banco de dados e exibição em dashboard. [file:1]

A solução foi desenvolvida com foco em integração entre sistemas, transmissão de dados em tempo real e visualização das informações de forma simples e organizada. O projeto utiliza dois sensores conectados ao ESP32 para capturar dados do ambiente, que depois são tratados no Node-RED para geração de indicadores, gráficos e alertas. [file:1]

Além dos dados dos sensores, o sistema também integra informações de uma API externa, exibindo esses dados no dashboard junto com as leituras recebidas pelo MQTT. Isso atende ao requisito de combinar dados internos do dispositivo com dados externos em uma mesma interface. [file:1]

## Arquitetura da solução

A arquitetura do projeto segue o fluxo abaixo:

**ESP32 → MQTT Broker → Node-RED → Dashboard / MySQL / API Externa** 

### Fluxo da solução

1. O **ESP32** realiza a leitura periódica dos sensores conectados
2. Os dados coletados são enviados em formato JSON para um **broker MQTT**, utilizando tópicos organizados
3. O **Node-RED** recebe essas mensagens MQTT, converte os dados e realiza o processamento necessário, como separação dos valores e geração de alertas
4. As informações são exibidas em um **dashboard em tempo real**, com gauges, gráficos e indicadores
5. O Node-RED também grava os dados em um **banco MySQL**, permitindo persistência das leituras
6. Uma **API externa** é consumida para complementar o dashboard com informações adicionais, como cotação ou clima

## Tecnologias utilizadas

- **ESP32** — microcontrolador principal responsável pela leitura dos sensores
- **Wokwi** — ambiente de simulação do circuito com ESP32 e sensores
- **MQTT** — protocolo utilizado para envio das leituras dos sensores
- **HiveMQ** — broker MQTT utilizado para publicação e recebimento das mensagens
- **Node-RED** — plataforma utilizada para integração, processamento, dashboard e comunicação com o banco
- **Node-RED Dashboard** — interface gráfica para visualização dos dados em tempo real
- **MySQL** — banco de dados utilizado para armazenar as leituras dos sensores
- **API externa** — serviço consumido no Node-RED para complementar as informações exibidas no dashboard
- **GitHub** — repositório para armazenamento do código, fluxo e documentação do projeto

## Instruções de execução

### 1. Configurar o ESP32 no Wokwi
- Montar o circuito com o ESP32 e os sensores utilizados no projeto.
- Inserir o código do ESP32 para leitura dos sensores.
- Configurar a conexão Wi-Fi e o broker MQTT.
- Publicar os dados em um tópico, por exemplo: `maquina1/sensores`.

### 2. Configurar o broker MQTT
- Utilizar um broker MQTT, como o HiveMQ.
- Garantir que o ESP32 publique os dados no tópico correto.
- Testar o envio das mensagens no formato JSON.

Exemplo de payload:
```json
{
  "temperatura": 24,
  "luminosidade": 1001
}
```

### 3. Configurar o Node-RED
- Importar o fluxo JSON do projeto no Node-RED
- Configurar o nó MQTT para assinar o tópico utilizado pelo ESP32.
- Configurar os nós de processamento para separar temperatura, luminosidade e alerta.
- Configurar o dashboard para exibir os gauges, gráficos e indicadores em tempo real

### 4. Configurar o MySQL
- Criar o banco de dados:
```sql
CREATE DATABASE iot_monitoramento;
USE iot_monitoramento;
```

- Criar a tabela de leituras:
```sql
CREATE TABLE leituras (
  id INT AUTO_INCREMENT PRIMARY KEY,
  temperatura DECIMAL(5,2),
  luminosidade INT,
  alerta VARCHAR(50),
  data_hora TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
```

- Configurar o nó MySQL no Node-RED com host, porta, usuário, senha e nome do banco.

### 5. Configurar a API externa
- Escolher uma API pública, como clima ou cotação
- Configurar a requisição no Node-RED.
- Exibir as informações recebidas no dashboard junto com os dados dos sensores

### 6. Executar o projeto
- Iniciar a simulação no Wokwi.
- Verificar se o ESP32 está publicando as mensagens MQTT.
- Confirmar no Node-RED o recebimento e processamento das leituras.
- Acessar o dashboard para acompanhar os dados em tempo real.
- Consultar o MySQL para validar o armazenamento das informações.

## Vídeo demonstrativo

Link do vídeo no YouTube: **[https://youtu.be/zxaa4ZdxiKI]**
