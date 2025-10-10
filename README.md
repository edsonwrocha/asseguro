# Asseguro

**Asseguro** é um sistema embarcado desenvolvido em **C++** para **Linux embarcado (Raspberry Pi OS Trixie)**, projetado para o **gerenciamento de acesso a salas** de forma segura e integrada.

---

## Visão Geral

O sistema oferece funcionalidades completas para controle de acesso, incluindo:

- Cadastro e autenticação de usuários diretamente no dispositivo.  
- Liberação de portas mediante senha, com feedback local e registro de eventos.  
- Listagem de usuários via interface serial.  
- Envio de eventos a um servidor remoto via HTTP.  
- Integração com o protocolo Modbus RTU sobre HTTP.

**Observação:**  
Atualmente, **usuários e eventos são armazenados localmente em arquivos de texto**.  
Essa abordagem foi adotada para simplificar o desenvolvimento inicial e **não é ideal para produção** — o recomendado seria implementar um **banco de dados local (ex: SQLite)** para maior integridade e desempenho.  

Além disso, **nem todas as validações de entrada estão sendo realizadas** durante o cadastro de usuários, pois o projeto está sendo desenvolvido como **prova de conceito (PoC)**.

---

## Tecnologias Utilizadas

- **C++20**  
- **Linux embarcado**  
- **Raspberry Pi OS Trixie**  
- **libcurl** — comunicação HTTP  
- **libgpiod** — controle de GPIOs  
- **Modbus RTU / HTTP**  
- **UART** — interface de comunicação serial  

---

## Compilação e Instalação

Para instruções completas de compilação e instalação, consulte:

- [BUILD.md](./docs/BUILD.md) — Guia detalhado para gerar o binário e configurar dependências.  
- [INSTALL.md](./docs/INSTALL.md) — Passo a passo para instalar e executar o sistema no dispositivo embarcado.  
- [CONFIG.md](./docs/CONFIG.md) — Guia de configuração e personalização do sistema.  

---

## Comunicação

O sistema se comunica com o servidor remoto utilizando **HTTP**, enviando eventos registrados localmente.  
Também implementa o **protocolo Modbus RTU encapsulado sobre HTTP**, garantindo interoperabilidade com sistemas industriais.

---

## Funcionalidades Principais

| Funcionalidade | Descrição |
|----------------|------------|
| Cadastro de Usuários | Permite adicionar usuários e administradores. |
| Autenticação Local | Valida credenciais e libera portas. |
| Controle de Portas | Acionamento via GPIO de relé. |
| Gerenciamento de Eventos | Registra ações e envia logs ao servidor. |
| Comunicação Modbus | Suporte a Modbus RTU sobre HTTP. |

---

## Vídeo de Apresentação

Confira a demonstração completa do sistema no YouTube:

[Asseguro Apresentação](https://youtu.be/ZScxTI4xp3A)

© 2025 **Asseguro** — Sistema embarcado de controle de acesso.
