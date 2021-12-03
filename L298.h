/**********************************************************************
  ) 2021 Carlos P

  ; * FileName:        L298.h
  ; * Dependencies:    
  ; * Processor:       ATMEGA328p
  ; * Compiler:        Arduino IDE
  ; *
   REVISION HISTORY:
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   Author           Date      Comments on this revision
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   Carlos Piccolini         22/11/21        Creation
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   Code Description:
   El objetivo de esta librería es la de poder ser de utilidad para la 
   configuración y manjeo del driver L298 para control de dos motores
   en Arduino
 *************************************************************************/

#ifndef L298_H_
#define L298_H_

/******************** Includes ********************/
#include <Arduino.h>        // Librería conmuchas funciones de Arduino

/******************** Class ********************/

class L298 {
private:
  byte ena_left;    // Mediante PWM controla la velocidad del motor izquierdo
  byte forw_left;   // Motor izquierdo para adelante
  byte back_left;   // Motor izquierdo para atras
  byte ena_right;
  byte forw_right;
  byte back_right;
public:
  L298(byte en_l=3, byte for_l=4, byte bac_l=5, byte en_r=6, byte for_r=7, byte bac_r=8);  

  void begin();

  void goForward(byte speed=255);
  void goForwardLeft(byte speed=255);
  void goForwardRight(byte speed=255);
  void goBackward(byte speed=255);
  void turnLeftF(byte speed=255);
  void turnRightF(byte speed=255);
  void stop();

  void leftMotor(byte speed, bool forward=true);
  void rightMotor(byte speed, bool forward=true);

  
  virtual ~L298();
};


#endif /* L298_H_ */
