# Configuração do Sistema Asseguro

## Localização
O arquivo de configuração está localizado em:

```bash
/opt/asseguro/asseguro.conf
```

⚡ Ao instalar o sistema, um arquivo de configuração padrão é automaticamente criado com as seguintes configurações iniciais:

```ini
[UART]
device=/dev/serial0
baud=115200

[HTTP]
server_url=192.168.1.8:8080

[Files]
evento_file=eventos.txt
usuario_file=usuarios.txt

[Portas]
P1=17
P2=27
```

## Estrutura do Arquivo
O arquivo asseguro.conf utiliza o formato INI e está dividido em seções:

### Seção [UART]
Configurações da comunicação serial:

device = /dev/serial0

Dispositivo serial utilizado para comunicação

baud = 115200

Velocidade de transmissão em bauds

### Seção [HTTP]
Configurações do servidor remoto:

server_url = 192.168.1.8:8080

URL do servidor onde as requisições HTTP POST são enviadas

Formato: IP:PORTA

### Seção [Files]
Configurações dos arquivos locais:

evento_file = eventos.txt

Arquivo local onde os eventos são salvos em texto

usuario_file = usuarios.txt

Arquivo local onde os usuários são salvos em texto

### Seção [Portas]
Configurações das portas GPIO:

P1 = 17

Número da GPIO para a Porta 1

P2 = 27

Número da GPIO para a Porta 2

## Estrutura do Diretório
```bash
/opt/asseguro/
```

```text
├── asseguro.conf      # Arquivo de configuração
├── bin/               # Executáveis do sistema
├── eventos.txt        # Arquivo de eventos (local)
└── usuarios.txt       # Arquivo de usuários (local)
```

## Funcionalidades
### Armazenamento Local
Eventos: Salvos localmente em eventos.txt

Usuários: Salvos localmente em usuarios.txt

### Comunicação Remota
HTTP POST: As requisições são enviadas para o servidor especificado em server_url

### Notas
Os arquivos de texto locais (eventos.txt e usuarios.txt) servem como backup e cache local
As configurações de porta GPIO seguem a numeração BCM do Raspberry Pi

A comunicação UART utiliza a interface serial padrão do Raspberry Pi
