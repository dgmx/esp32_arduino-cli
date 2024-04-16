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

Para añadir una carpeta al PATH de Linux se usa el comando export:
```
export PATH=$PATH:/home/usuario/ruta_a_la_carpeta_que_quiero_añadir
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
