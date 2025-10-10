# Instalação do Sistema Asseguro
Este documento explica como instalar e configurar o Sistema Asseguro em seu dispositivo.

## Pré-requisitos

- Sistema operacional Linux (testado no Raspberry Pi OS)
- Acesso de superusuário (sudo)
- Compilador C++ e ferramentas de build
- CMake instalado
- libcurl instalado
- libgpiod instalado
- Systemd como sistema de init

## Passos de Instalação
### 1. Preparar o Ambiente
Certifique-se de que as dependências necessárias estão instaladas:

```bash
sudo apt update
sudo apt install build-essential cmake
```

### 2. Executar o Script de Instalação
Tornar o script executável:
```bash
chmod +x install.sh
```
Executar a instalação:
```bash
./install.sh
```

O que o Script Faz
O script de instalação automatiza os seguintes passos:

1. Compilação do Projeto
Cria um diretório de build

Executa CMake para configurar o projeto

Compila o código fonte usando Make

2. Estrutura de Diretórios
Cria a seguinte estrutura no sistema:

```text
/opt/asseguro/
├── bin/           # Binário executável
├── asseguro.conf  # Arquivo de configuração (se aplicável)
└── dados/         # Diretório de dados (se aplicável)
```

3. Configuração do Serviço Systemd
Cria e configura um serviço systemd com as seguintes características:

Nome do serviço: asseguro.service

Tipo: Serviço simples

Reinício automático: Sempre que falhar

Usuário: pi

Dependências: Rede e dispositivo serial

4. Inicialização do Serviço
Recarrega o systemd

Habilita inicialização automática na boot

Inicia o serviço imediatamente

Verificação da Instalação
Verificar status do serviço:
bash
sudo systemctl status asseguro
Ver logs do serviço:
bash
journalctl -u asseguro -f
Parar o serviço:
bash
sudo systemctl stop asseguro
Reiniciar o serviço:
bash
sudo systemctl restart asseguro
Desabilitar inicialização automática:
bash
sudo systemctl disable asseguro
Estrutura de Arquivos Instalada
Binário: /opt/asseguro/bin/asseguro

Configuração: /opt/asseguro/ (diretório de configuração)

Dados: /opt/asseguro/ (diretório de dados)

Serviço: /etc/systemd/system/asseguro.service

## Permissões
O serviço é executado com o usuário pi e grupo pi. Certifique-se de que este usuário tenha as permissões necessárias para acessar dispositivos seriais ou outros recursos do sistema.

## Solução de Problemas
Serviço não inicia
Verifique as permissões: ls -la /opt/asseguro/bin/

Confirme que o binário é executável

Verifique os logs: journalctl -u asseguro -n 50

Erros de compilação
Certifique-se de que todas as dependências de desenvolvimento estão instaladas

Verifique se há espaço suficiente em disco

Problemas de dispositivo serial
Verifique se o usuário pi pertence ao grupo dialout:

```bash
sudo usermod -a -G dialout pi
```

## Desinstalação
Para remover completamente o sistema:

```bash
sudo systemctl stop asseguro
sudo systemctl disable asseguro
sudo rm /etc/systemd/system/asseguro.service
sudo systemctl daemon-reload
sudo rm -rf /opt/asseguro
```
Nota: Este script assume que está sendo executado a partir do diretório do projeto fonte, onde o código CMakeLists.txt está localizado.
