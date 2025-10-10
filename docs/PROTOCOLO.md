# PROTOCOLO

Este documento define o protocolo para envio de eventos do sistema **Asseguro**, utilizando comunicação MODBUS para comandos de abertura de portas.

---

## Tipos de Eventos

O sistema trabalha com dois tipos de eventos:

1. **Criação de Usuário**
   Evento que informa ao sistema que um novo usuário foi criado.
   - Campos principais:
     - `id_usuario`: Identificador único do usuário
     - `nome`: Nome do usuário
     - `nivel_acesso`: Nível de permissão do usuário

2. **Abertura de Porta**
   Evento que indica a ação de abrir ou fechar uma porta.
   Pode haver **Porta 1** ou **Porta 2**.

---

## Evento de Porta (MODBUS)

O evento de porta segue o protocolo MODBUS padrão, com endereço, função de escrita, dados e CRC16.

### Estrutura Geral

| Campo          | Descrição                                               |
|----------------|---------------------------------------------------------|
| Address        | Endereço do dispositivo MODBUS (ex: 0x01)               |
| Função         | Função de escrita MODBUS (0x06 – Write Single Register) |
| Endereço       | Endereço do registrador a ser escrito                   |
| Valor          | Valor do registrador                                    |
| CRC16          | CRC16 para verificação de integridade                   |

### Mapa MODBUS

| Ação             | Endereço | Valor                          |
|------------------|----------|--------------------------------|
| Abrir Porta 1    | 0x34     | 0xFF (aberto) / 0x00 (fechado) |
| Abrir Porta 2    | 0x35     | 0xFF (aberto) / 0x00 (fechado) |

---

### Exemplo de Comandos

| Ação           | Address | Função | Endereço High | Endereço Low | Valor High | Valor Low | CRC Low | CRC High |
|----------------|---------|--------|---------------|--------------|------------|-----------|---------|----------|
| Abrir Porta 1  | 0x01    | 0x06   | 0x00          | 0x34         | 0x00       | 0xFF      | CRC_L   | CRC_H    |
| Fechar Porta 2 | 0x01    | 0x06   | 0x00          | 0x35         | 0x00       | 0x00      | CRC_L   | CRC_H    |


> O `CRC16` deve ser calculado conforme padrão **MODBUS RTU**, considerando os 6 bytes anteriores (Address, Função, Endereço, Valor).

---

### Observações

- Todos os comandos MODBUS devem ser enviados como string **hexadecimal**.
- É obrigatório enviar o **CRC16** para validação de integridade do pacote.
- A comunicação é unidirecional do controlador para o equipamento, seguindo o modelo de escrita (`Write Single Register`).

# API de Eventos - Asseguro

O sistema **Asseguro** disponibiliza um endpoint para envio de eventos, permitindo registrar ações de criação de usuários e abertura de portas.

---

## Endpoint

**POST** `/api/eventos`
**Content-Type:** `application/json`

Este endpoint recebe eventos do sistema e registra as ações correspondentes no backend.

---

## Tipos de Eventos

O endpoint suporta dois tipos de eventos:

### 1. Criação de Usuário

Evento que informa ao sistema que um novo usuário foi criado.

**Exemplo de JSON:**

```json
{
  "tipo_evento": "criar_usuario",
  "usuario": {
    "nome": "João Silva",
    "tipo": "admin"
  },
  "timestamp": "2025-10-08T09:30:00Z"
}
```


| Campo                | Tipo   | Descrição                       |
| -------------------- | ------ | ------------------------------- |
| tipo_evento          | string | `"criar_usuario"`               |
| usuario.nome         | string | Nome do usuário                 |
| usuario.tipo 	       | string | Nível de permissão do usuário   |
| timestamp            | string | Data e hora no formato ISO 8601 |

### 2. Movimentação de Porta

Evento que indica a ação de abrir ou fechar uma porta. Suporta Porta 1 e Porta 2.

**Exemplo de JSON:**
```json
{
  "tipo_evento": "movimentacao_porta",
  "porta": 1,
  "acao": "abrir",
  "modbus": "0106003400FFCDAB",
  "timestamp": "2025-10-08T09:32:00Z"
}
```

| Campo       | Tipo   | Descrição                                         |
| ----------- | ------ | ------------------------------------------------- |
| tipo_evento | string | `"abrir_porta"`                                   |
| usuario     | string | Nome do usuário                                   |
| porta       | int    | Número da porta (1 ou 2)                          |
| acao        | string | `"abrir"` ou `"fechar"`                           |
| modbus      | string | Pacote MODBUS completo em hexadecimal (com CRC16) |
| timestamp   | string | Data e hora no formato ISO 8601                   |

O campo modbus contém o pacote completo a ser enviado ao servidor, já incluindo o CRC16.

A API apenas registra o evento; o envio físico ao equipamento é feito pelo firmware conforme integração.
