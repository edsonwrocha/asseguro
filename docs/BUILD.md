# BUILD — Compilação do Projeto Asseguro

Este guia descreve como **compilar e executar o sistema Asseguro** em um Raspberry Pi com **Raspberry Pi OS (Trixie)**.

---

## Pré-requisitos

Antes de começar, verifique se o sistema possui as seguintes dependências:

- **g++** — compilador C++20  
- **cmake** — ferramenta de construção de projetos  
- **libcurl** — para comunicação HTTP (`libcurl4-openssl-dev`)  
- **libgpiod** — para controle de GPIOs (`libgpiod-dev`)  
- **git** — para clonar o repositório  

Certifique-se de estar usando um **Raspberry Pi com Linux embarcado**, pois algumas bibliotecas podem não estar disponíveis em outras distribuições.

---

## Passo 1 — Atualizar pacotes do sistema

```bash
sudo apt update
sudo apt upgrade -y
```

## Passo 2 - Instalar dependências

```bash
sudo apt install -y g++ cmake libcurl4-openssl-dev libgpiod-dev git
```

## Passo 3 - Ativar UART no Raspberry Pi

```bash
sudo raspi-config
```

Navegue até: Interface Options → Serial Port

Quando perguntado sobre login shell, selecione Não

Habilite a interface serial

Reinicie o Raspberry Pi:

```bash
sudo reboot
```

## Passo 4 - Clonar o repositório

```bash
git clone https://github.com/edsonwrocha/asseguro.git
cd asseguro
```

## Passo 5 - Criar diretório de build

```bash
mkdir build
cd build
```

## Passo 6 - Configurar o projeto com CMake

```bash
cmake ..
```

## Passo 7 - Compilar o projeto

```bash
make
```
## Passo 8 - Executar o projeto

```bash
./asseguro
```
