/**********************************************************************
  ) 2021 Carlos P

  ; * FileName:        L298.cpp
  ; * Dependencies:    Header
  ; * Processor:       ATMEGA328p
  ; * Compiler:        Arduino IDE
  ; *
   REVISION HISTORY:
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   Author           Date      Comments on this revision
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   Carlos Piccolini           22/11/21      Creation
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   Code Description:
   El objetivo de esta librería es la de poder ser de utilidad para la 
   configuración y manjeo del driver L298 para control de dos motores
   en Arduino
 *************************************************************************/

/******************** Includes ********************/
#include "L298.h"

/******************** Methods ********************/

/*!
 * Object constructor
 * @param : pines que manejan al driver
 * @return :-
 */
L298::L298(byte en_l, byte for_l, byte bac_l, byte en_r, byte for_r, byte bac_r) 
:ena_left(en_l), forw_left(for_l), back_left(bac_l), ena_right(en_r), forw_right(for_r), back_right(bac_r)
{
}

/*!
 * Inicializa el driver con sus pines
 * @param : 
 * @return :-
 */
void L298::begin() {
  pinMode(ena_left, OUTPUT);
  pinMode(forw_left, OUTPUT);
  pinMode(back_left, OUTPUT);
  pinMode(ena_right, OUTPUT);
  pinMode(forw_right, OUTPUT);
  pinMode(back_right, OUTPUT);
  stop();
}

/*!
 * Ambos motores avanzan hacia adelante
 * @param : velocidad de avance
 * @return :-
 */
void L298::goForward(byte speed) {
  leftMotor(speed, true);
  rightMotor(speed, true);
}

/*!
 * Ambos motores avanzan hacia adelante pero el motor derecha lo hace más rápido
 * @param : velocidad de avance
 * @return :-
 */
void L298::goForwardLeft(byte speed) {
  rightMotor(speed, true);
  leftMotor(speed / 2, true);
}

/*!
 * Ambos motores avanzan hacia adelante pero el motor izquierda lo hace más rápido
 * @param : velocidad de avance
 * @return :-
 */
void L298::goForwardRight(byte speed) {
  leftMotor(speed, true);
  rightMotor(speed / 2, true);
}

/*!
 * Ambos motores avanzan hacia atras
 * @param : velocidad de retoceso
 * @return :-
 */
void L298::goBackward(byte speed) {
  leftMotor(speed, false);
  rightMotor(speed, false);
}

/*!
 * Solo avanza el motor de la derecha
 * @param : velocidad de retoceso
 * @return :-
 */
void L298::turnLeftF(byte speed) {
  leftMotor(0);
  rightMotor(speed, true);
}

/*!
 * Solo avanza el motor de la izquierda
 * @param : velocidad de retoceso
 * @return :-
 */
void L298::turnRightF(byte speed) {
  leftMotor(speed, true);
  rightMotor(0);
}

/*!
 * Para ambos motores, poniendo los pins PWM en 0
 * y en bajo los pin de control de los motores
 * @param : 
 * @return :-
 */
void L298::stop() {
  leftMotor(0);
  rightMotor(0);
}

/*!
 * Maneja el sentido y velocidad del motor izquierdo
 * @param : velocidad del motor y sentido
 * @return :-
 */
void L298::leftMotor(byte speed, bool forward) {
  if(speed == 0) {
    analogWrite(ena_left, 0);
    digitalWrite(forw_left, LOW);
    digitalWrite(back_left, LOW);
  } else if(forward) {
    analogWrite(ena_left, speed);
    digitalWrite(back_left, LOW);
    digitalWrite(forw_left, HIGH);
  } else {
    analogWrite(ena_left, speed);
    digitalWrite(forw_left, LOW);
    digitalWrite(back_left, HIGH);
  }
}

/*!
 * Maneja el sentido y velocidad del motor derecho
 * @param : velocidad del motor y sentido
 * @return :-
 */
void L298::rightMotor(byte speed, bool forward) {
  if(speed == 0) {
    analogWrite(ena_right, 0);
    digitalWrite(forw_right, LOW);
    digitalWrite(back_right, LOW);
  } else if(forward) {
    analogWrite(ena_right, speed);
    digitalWrite(back_right, LOW);
    digitalWrite(forw_right, HIGH);
  } else {
    analogWrite(ena_right, speed);
    digitalWrite(forw_right, LOW);
    digitalWrite(back_right, HIGH);
  }
}

/*!
 * Object destructor
 * @param :-
 * @return :-
 */
L298::~L298() {
  // TODO Auto-generated destructor stub
}
