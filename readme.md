## Programación de Placas ESP32 con Arduino-Cli

Introducción a la programación de placas ESP32 con Arduino Cli.
Empezamos con la instalación de Arduino-Cli:

```
# instalamos desde github
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
# comprobamos la instalación
arduino-cli version
```
Es probable que debamos añadir la carpeta de instalación del CLI al path.

Para añadir una carpeta al PATH de Linux se usa el comando export.
Editamos el archivo de configuración de bash (.bashrc) o zsh (.zshrc) y añadimos la siguiente linea al final:
```
export PATH=$PATH:/home/usuario/bin/arduino-cli
```
El siguiente paso será crear el archivo de configuración de Arduino-Cli
```
# setup configuration file
arduino-cli config init

# Config file written: /home/username/.arduino15/arduino-cli.yaml
# Documentation for file: https://arduino.github.io/arduino-cli/0.19/configuration/

```
Una vez creado el archivo de configuración, añadimos al archivo yaml las placas ESP32:
```
board_manager:
  additional_urls:
    - https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

```
Actualizamos el indice de placas e instalamos las ESP32

```
arduino-cli core update-index
arduino-cli board listall
arduino-cli core install esp32:esp32
# Platform esp32:esp32@2.0.2 already installed
```
Comprobamos que la placa está instalada:
```
arduino-cli core list

ID          Instalado Última Nombre
esp32:esp32 2.0.11    2.0.11 esp32
```
Podemos comprobar los puertos serial en uso con el comando:
```
arduino-cli board list

Puerto       Protocolo Tipo              Nombre de la placa FQBN Núcleo
/dev/ttyS0   serial    Serial Port       Unknown
/dev/ttyUSB0 serial    Serial Port (USB) Unknown
