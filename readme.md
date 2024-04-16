## Programación de Placas ESP32 con Arduino-Cli

Introducción a la programación de placas ESP32 con Arduino Cli.
Empezamos con la instalación de Arduino-Cli:

```
# instalamos desde github
$ curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
# comprobamos la instalación
$ arduino-cli version
```
Es probable que debamos añadir la carpeta de instalación del CLI al path.

Para añadir una carpeta al PATH de Linux se usa el comando export.
Editamos el archivo de configuración de bash (.bashrc) o zsh (.zshrc) y añadimos la siguiente linea al final:
```
export PATH=$PATH:/home/usuario/bin/arduino-cli
```
Es muy probable que tengamos que instalar la libreria PySerial en nuestro sistema:
```
$ python3 -m pip install PySerial
```
El siguiente paso será crear el archivo de configuración de Arduino-Cli
```
$ arduino-cli config init

Config file written: /home/username/.arduino15/arduino-cli.yaml
```
Una vez creado el archivo de configuración, añadimos al archivo yaml las placas ESP32:
```
board_manager:
  additional_urls:
    - https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

```
Actualizamos el indice de placas e instalamos las ESP32

```
$ arduino-cli core update-index
$ arduino-cli board listall
$ arduino-cli core install esp32:esp32

# Platform esp32:esp32@2.0.2 already installed
```
Comprobamos que la placa está instalada:
```
$ arduino-cli core list

ID          Instalado Última Nombre
esp32:esp32 2.0.11    2.0.11 esp32
```
Podemos comprobar los puertos serial en uso con el comando:
```
$ arduino-cli board list

Puerto       Protocolo Tipo              Nombre de la placa FQBN Núcleo
/dev/ttyS0   serial    Serial Port       Unknown
/dev/ttyUSB0 serial    Serial Port (USB) Unknown
```
El siguiente paso será crear el sketch de Arduino, para ello usaremos el siguiente comando:
```
$arduino-cli sketch new Sketch01

Sketch created in: /home/diego/Arduino/Sketch01

```
Accedemos a la carpeta y comprobamos que el archivo Sketch01.ino ha sido generado:
```
$ cd Sketch01
$ ls -l 

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
Este sketch va a probar la capacidad de la ESP32 de conectarese a una wifi e iniciar un servidor Web donde podemos modificar los leds de la placa

Copiamos el archivo a la carpeta del sketch y eliminamos el anterior
```
$ rm Sketch01.inp
```
Renombramos el archivo copiado al nombre del sketch:
```
$ mv HttpServidorBlink.ino Sket01.ino
```
En el archivo solo debemos modificar el SSID de nuestra wifi y su contraseña, y la dirección IP que le queramos configurar a la placa.

Una vez realizado las modificaciones necesarias, vamos a compilar y a subir el archivo a la placa:
Para ello volvemos una carpeta hacia atras y ejecutamos:
```
$ arduino-cli compile --fqbn esp32:esp32:nodemcu-32s Sketch01

El Sketch usa 748909 bytes (57%) del espacio de almacenamiento de programa. El máximo es 1310720 bytes.
Las variables Globales usan 43968 bytes (13%) de la memoria dinámica, dejando 283712 bytes para las variables locales. El máximo es 327680 bytes.

Used library Version Path
WiFi         2.0.0   /home/diego/.arduino15/packages/esp32/hardware/esp32/2.0.11/libraries/WiFi
WebServer    2.0.0   /home/diego/.arduino15/packages/esp32/hardware/esp32/2.0.11/libraries/WebServer
FS           2.0.0   /home/diego/.arduino15/packages/esp32/hardware/esp32/2.0.11/libraries/FS

Used platform Version Path
esp32:esp32   2.0.11  /home/diego/.arduino15/packages/esp32/hardware/esp32/2.0.11
```
El paso final es subir el archivo compilado a la placa:
```
$ arduino-cli upload -p /dev/ttyUSB0 --fqbn esp32:esp32:nodemcu-32s Sketch01

esptool.py v4.5.1
Serial port /dev/ttyUSB0
Connecting.....
Chip is ESP32-D0WDQ6 (revision v1.0)
Features: WiFi, BT, Dual Core, 240MHz, VRef calibration in efuse, Coding Scheme None
WARNING: Detected crystal freq 41.01MHz is quite different to normalized freq 40MHz. Unsupported crystal in use?
Crystal is 40MHz
MAC: 08:3a:f2:7c:07:d8
Uploading stub...
Running stub...
Stub running...
Changing baud rate to 921600
Changed.
Configuring flash size...
Flash will be erased from 0x00001000 to 0x00005fff...
Flash will be erased from 0x00008000 to 0x00008fff...
Flash will be erased from 0x0000e000 to 0x0000ffff...
Flash will be erased from 0x00010000 to 0x000c8fff...
Compressed 17568 bytes to 12204...
Writing at 0x00001000... (100 %)
Wrote 17568 bytes (12204 compressed) at 0x00001000 in 0.5 seconds (effective 276.7 kbit/s)...
Hash of data verified.
Compressed 3072 bytes to 146...
Writing at 0x00008000... (100 %)
Wrote 3072 bytes (146 compressed) at 0x00008000 in 0.1 seconds (effective 336.4 kbit/s)...
Hash of data verified.
Compressed 8192 bytes to 47...
Writing at 0x0000e000... (100 %)
Wrote 8192 bytes (47 compressed) at 0x0000e000 in 0.1 seconds (effective 448.4 kbit/s)...
Hash of data verified.
Compressed 754656 bytes to 489305...
Writing at 0x00010000... (3 %)
Writing at 0x0001b71e... (6 %)
Writing at 0x000255c1... (10 %)
Writing at 0x00031ca6... (13 %)
Writing at 0x00037730... (16 %)
Writing at 0x0003cfe3... (20 %)
Writing at 0x00042330... (23 %)
Writing at 0x000479e0... (26 %)
Writing at 0x0004cba7... (30 %)
Writing at 0x00051d40... (33 %)
Writing at 0x000570f4... (36 %)
Writing at 0x0005c2f1... (40 %)
Writing at 0x000614eb... (43 %)
Writing at 0x000669e3... (46 %)
Writing at 0x0006bc91... (50 %)
Writing at 0x0007192b... (53 %)
Writing at 0x0007710c... (56 %)
Writing at 0x0007c24b... (60 %)
Writing at 0x0008170e... (63 %)
Writing at 0x00086b82... (66 %)
Writing at 0x0008c12e... (70 %)
Writing at 0x00091989... (73 %)
Writing at 0x0009766c... (76 %)
Writing at 0x0009d01d... (80 %)
Writing at 0x000a33e6... (83 %)
Writing at 0x000adaab... (86 %)
Writing at 0x000b2ec0... (90 %)
Writing at 0x000b854e... (93 %)
Writing at 0x000bdfaf... (96 %)
Writing at 0x000c33c0... (100 %)
Wrote 754656 bytes (489305 compressed) at 0x00010000 in 7.4 seconds (effective 815.4 kbit/s)...
Hash of data verified.

Leaving...
Hard resetting via RTS pin...
New upload port: /dev/ttyUSB0 (serial)

```
Si todo ha ido correctamente, deberías poder acceder a tu placa ESP32 desde una navegador unando la dirección IP establecida en el sketch.
Puedes comprobar tambien su funcionamiento desde el terminal con el siguiente comando:
```
$ cul 192.168.1.253
<!DOCTYPE HTML>
<html>
<head><meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>UTILIZACIÓN DE PLACA DE DESARROLLO COMO SERVIDOR HTTP</title>
</head>
<body><br><br>Gestión del Led Interno de la placa con las siguients páginas<br><br><br>
*<a href=/encender>Encender led interno</a><br>
* <a href=/apagar>Apagar led interno</a><br>*
<p>Diego J. Gonzaĺez. <i>DGMXio Systems</i></p>
</body>
</html>
