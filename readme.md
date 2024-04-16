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
Es muy probable que tengamos que instalar la libreria PySerial en nuestro sistema:
```
python3 -m pip install PySerial
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
```
El siguiente paso será crear el sketch de Arduino, para ello usaremos el siguiente comando:
```
arduino-cli sketch new Sketch01
Sketch created in: /home/diego/Arduino/Sketch01

```
Accedemos a la carpeta y comprobamos que el archivo Sketch01.ino ha sido generado:
```
cd Sketch01
ls -l 

-rw-r--r-- 1 diego diego 35 abr 16 10:11 Sketch01.ino
```
Editamos el archivo para configurar el sketch que queremos instalar en nuestra placa, en este ejemplo vamos a usar el codigo de ejemplo de HttpServidorBlink
```   
   HttpServidorBlink.ino
   Author: UPM
   Date: 2021
   Este sketch utiliza la placa de desarrollo como Servidor HTTP recibiendo peticiones para
   encender y apagar el led interno de la placa
```
Copiamos el archivo a la carpeta del sketch y eliminamos el anterior
```
rm Sketch01.inp
```
Renombramos el archivo copiado al nombre del sketch:
```
mv HttpServidorBlink.ino Sket01.ino
```


