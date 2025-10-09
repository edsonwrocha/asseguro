#!/bin/bash
set -e

# ------------------------
# CONFIGURAÇÃO DE DIRETÓRIOS
# ------------------------
BASE_DIR="/opt/asseguro"
BIN_DIR="$BASE_DIR/bin"
CONFIG_DIR="$BASE_DIR"
DATA_DIR="$BASE_DIR"
BUILD_DIR="$(pwd)/build"
SERVICE_FILE="/etc/systemd/system/asseguro.service"
USER="pi"
GROUP="pi"

echo "=== Instalando Asseguro ==="

# ------------------------
# COMPILAR O PROJETO
# ------------------------
echo "Compilando projeto..."
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"
cmake ..
make

# ------------------------
# CRIAR PASTAS
# ------------------------
echo "Criando diretórios..."
sudo mkdir -p "$BIN_DIR" "$CONFIG_DIR" "$DATA_DIR"

# ------------------------
# COPIAR BINÁRIO
# ------------------------
echo "Copiando binário..."
sudo cp "$BUILD_DIR/asseguro" "$BIN_DIR/"

# ------------------------
# PERMISSÕES
# ------------------------
echo "Definindo permissões..."
sudo chown -R $USER:$GROUP "$BASE_DIR"
sudo chmod 755 "$BIN_DIR/asseguro"

# ------------------------
# CRIAR SERVIÇO SYSTEMD
# ------------------------
echo "Criando serviço systemd..."
sudo bash -c "cat > $SERVICE_FILE" <<EOL
[Unit]
Description=Asseguro - Sistema de Controle de Portas
After=network.target dev-serial0.device
Requires=dev-serial0.device

[Service]
Type=simple
ExecStart=$BIN_DIR/asseguro
WorkingDirectory=$BASE_DIR
Restart=always
User=$USER
Group=$GROUP
Environment=CONFIG_DIR=$CONFIG_DIR
Environment=DATA_DIR=$DATA_DIR

[Install]
WantedBy=multi-user.target
EOL

# ------------------------
# ATIVAR E INICIAR SERVIÇO
# ------------------------
echo "Ativando e iniciando serviço..."
sudo systemctl daemon-reload
sudo systemctl enable asseguro
sudo systemctl start asseguro

echo "=== Instalação concluída! ==="
echo "Serviço Asseguro ativo. Logs: journalctl -u asseguro -f"
