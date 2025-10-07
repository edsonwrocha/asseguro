# 🛡️ Projeto Asseguro

Sistema embarcado para **gerenciamento de acesso** à salas, desenvolvido em **C/C++ sobre Linux embarcado**.  
O projeto permite o **cadastro e autenticação de usuários**, **liberação de portas (salas)** mediante senha, e **envio de eventos para um servidor HTTP** utilizando o **protocolo Modbus RTU**.

---

## 📋 Objetivo

Gerenciar o acesso de membros a duas salas distintas, com controle via **interface serial (UART)** e comunicação com um **servidor remoto**.  
A abertura e fechamento das portas são representadas fisicamente por **relés/lâmpadas** conectados às saídas do dispositivo.
