/**********************************************************************
  ) 2021 Carlos P

  ; * FileName:        Auto_Wifi.ino
  ; * Dependencies:    ESP01.h y L298.h
  ; * Processor:       ATMEGA328p
  ; * Compiler:        Arduino IDE
  ; *
   REVISION HISTORY:
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   Author                   Date            Comments on this revision
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   Carlos Piccolini         22/11/21        Creation
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   Code Description:
   Este código realiza el control de un auto a control remoto inalámbrico 
   (WiFi)
 *************************************************************************/

/******************** Includes ********************/
#include "ESP01.h"
#include "L298.h"

/******************** Defines ********************/
#define SSID_NAME   "ESP01_wifi3"    // Id de Red WiFi
#define PASS        "matraca96"     // Pass de Red WiFi
#define WIFI_RX 10                  // Pin receptor de datos provenientes del ESP01
#define WIFI_TX 11                  // Pinque envía datos al ESP01
#define LEFT_ENA 3                  // Left motor PWM speed control
#define LEFT_FORW 4                 // Left motor Forward Direction
#define LEFT_BACK 5                 // Left motor Backward Direction
#define RIGHT_BACK 7                // Right motor Backward Direction
#define RIGHT_FORW 8                // Right motor Forward Direction
#define RIGHT_ENA 9                 // Right motor PWM speed control

/******************** Objects ********************/
ESP01 wifi(WIFI_TX, WIFI_RX);  // Inicializo el módulo ESP01
L298 motors(LEFT_ENA, LEFT_FORW, LEFT_BACK, RIGHT_ENA, RIGHT_FORW, RIGHT_BACK);  // Inicializo el driver L298

/******************** Main Setup ********************/ 
void setup() {
  // Inicializo los pines del driver L298
  motors.begin(); 
  
  // Inicializo la comunciación Serie con el módulo WiFi
  wifi.begin(19200); 
  
  // Configuro el módulo ESP01 como un Servidor AP
  wifi.setupAsAP(SSID_NAME, PASS);
  wifi.setupServer();
}

void loop() {
  char data_received [70] = "";

  // Espero que ingrese data por el ESP01
  while(!wifi.dataAvailable()) {}

  // Leo la data recibida por el ESP01
  wifi.readESP(data_received);

  // Logica a partir dela información recibida
  if(strstr(data_received, "/D?=1&")) {
    motors.goForward(200);
    delay(10);
    motors.goForward(255);
  }
  else if(strstr(data_received, "/D?=2")) {
    motors.stop();
  }
  else if(strstr(data_received, "/D?=3")) {
    motors.turnLeftF(200);
  }
  else if(strstr(data_received, "/D?=4")) {
    motors.turnRightF(200);
  }


}
