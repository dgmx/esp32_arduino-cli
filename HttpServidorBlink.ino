/**
   HttpServidorBlink.ino
   Author: UPM
   Date: 2021
   Este sketch utiliza la placa de desarrollo como Servidor HTTP recibiendo peticiones para 
   encender y apagar el led interno de la placa
*/

#include <WiFi.h>
#include <WebServer.h>


// Definición de constantes
// Se configura como constantes los datos de identificación de la red WiFi
const char* ssid     = "WIFI"; // Establecer SSID red WiFi de tu casa 
const char* password = "Password-WIFI"; // Establecer contraseña red WiFi de tu casa

// Constante para configurar el led interno de la placa
const int led =  LED_BUILTIN;   

// Constantes para entender mejor que es apagado/encendido del led interno
#define APAGAR    HIGH
#define ENCENDER LOW

// Definición de variables globales
// Asignación de una IP fija en vez de usar el protocolo DHCP
IPAddress wifiIP(192, 168, 1, 235);  // IP que se asigna al microcontrolador
IPAddress wifiNET (255, 255, 255, 0); // Máscara de Red de la red WiFi
IPAddress wifiON (192, 168, 1, 1); // IP del Router de la red WiFi

// Instanciar objeto servidor web 
WebServer servidorWeb(80);  

void setup() {
  // Se inicializa el pin digital LED_BUILTIN como una salida
  pinMode(led, OUTPUT);
 
  // Se configura la velocidad a la que se transmite la información desde la placa hasta la consola.
  Serial.begin(115200);  
  Serial.println("");
  Serial.println("Arrancando");

   for (uint8_t t = 4; t > 0; t--) {
    // Se enciende y apaga el led interno varias veces para así indicar que se está arrancando el programa
    digitalWrite(led, ENCENDER);
    delay(100);    
    digitalWrite(led, APAGAR);    
    delay(100);
  }
  // Se comienza con el led interno apagado
  digitalWrite(led, APAGAR);
  
  // Se implementa la configuración de la WiFi en una función
  // Esto limita el número de líneas de la función setup
  conexionWifi();
  
  // Se configuran las páginas del servidor web
  configurarServidorWebPlaca();
}

void loop()
{
  // El método handleClient() comprueba si se ha solicitado una página al servidor, 
  // y en ese caso ejecuta el manejador correspondiente
  servidorWeb.handleClient(); 
}

/* Función conexionWifi() presentado en el Módulo 2 del curso
   Se conecta a la wifi hasta conseguirlo, sin usar el protocolo DHCP
   Cuando termina, muestra la IP obtenida
*/
void conexionWifi(){
  Serial.println();
  Serial.println();
  //Serial.print("Conectando con ");
  //Serial.println(ssid);
  
  // Conexión a la red WiFi
  // Se establece el microcontrolador como un cliente WiFi
  WiFi.mode(WIFI_STA);

  // Se establecen los parámetros de red sin usar DHCP
  WiFi.config(wifiIP, wifiON, wifiNET); 
  
  WiFi.begin(ssid, password);
  // Intentar la conexión cada medio segundo hasta conseguirlo, mostrando un punto en cada intento
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectada");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

/* Función configurarServidorWebPlaca() 
   En esta función se realizan las acciones necesarias para configurar el servidor web que se ejecuta en la placa
*/
void configurarServidorWebPlaca(){
  // Se asocia un manejador a cada una de las rutas en las que responde el servidor web
  servidorWeb.on("/", handleRoot);
  servidorWeb.on("/encender", manejadorEncendido);
  servidorWeb.on("/apagar", manejadorApagado);
  
  // Asociar el manejador handleNotFound a cualquier ruta a la que no se le haya asociado un manejador
  servidorWeb.onNotFound(handleNotFound);  
  // Se inicia el servidor web
  servidorWeb.begin();
  Serial.println("Servidor HTTP iniciado");
     
  Serial.println("Listo. Conectarse a un navegador y usar estas URLs:");
  Serial.print("Para encender el led interno: http://");Serial.print (WiFi.localIP());Serial.println("/encender");
  Serial.print("Para apagar el led interno: http://");Serial.print (WiFi.localIP());Serial.println("/apagar");
}

/* Función manejadorEncendido() 
   Manejador que se va a utilizar para ejecutar el código necesario 
   con el fin de encencer el led interno
*/
void manejadorEncendido() {
  // Manejador asociado a la ruta /encender
  digitalWrite(led, ENCENDER);
  servidorWeb.send(200, "text/plain", "ENCENDIDO!");
}

/* Función manejadorApagado() 
   Manejador que se va a utilizar para ejecutar el código necesario 
   con el fin de apagar el led interno
*/
void manejadorApagado() {
  // Manejador asociado a la ruta /apagar
  digitalWrite(led, APAGAR);
  servidorWeb.send(200, "text/plain", "APAGADO!");
}

/* Función handleRoot() 
    Manejador por defecto cuando no se pone una ruta y que envía una página html que sirve para conocer 
    las rutas disponibles en este dispositivo que permiten el encendido y apagado del led interno
*/
void handleRoot() {
 String mensaje;
  mensaje = "<!DOCTYPE HTML>\r\n<html>\r\n";
  mensaje += "<head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">";
  mensaje += "<title>UTILIZACIÓN DE PLACA DE DESARROLLO COMO SERVIDOR HTTP</title></head>\r\n";
  mensaje += "<body>";
  mensaje += "<br><br>Gestión del Led Interno de la placa con las siguients páginas<br><br><br>";
  mensaje += "* <a href=""/encender"">Encender led interno</a><br>";
  mensaje += "* <a href=""/apagar"">Apagar led interno</a><br>";
  mensaje += "* <p><i>ESP32 Systems</i></p>";
  mensaje += "</body>";
  mensaje += "</html>\n";
  // Se envia el texto en formato html que hay en la variable mensaje al cliente que ha hecho la petición
  servidorWeb.send(200, "text/html; charset=UTF-8", mensaje); 
}

/* Función handleNotFound() 
   Manejador que se ejecuta si se invoca a una página que no existe en el servidor web
*/
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += servidorWeb.uri();
  message += "\nMethod: ";
  message += (servidorWeb.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += servidorWeb.args();
  message += "\n";
  for (uint8_t i = 0; i < servidorWeb.args(); i++) {
    message += " " + servidorWeb.argName(i) + ": " + servidorWeb.arg(i) + "\n";
  }
  servidorWeb.send(404, "text/plain", message);
}
