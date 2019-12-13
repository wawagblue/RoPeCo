#include <Arduino.h>
#include "buttons.h"

int LONG_CLICK_DELAY = 500;
int DEBOUNCING_DELAY = 300;
int lastButtonId = -1;
unsigned long lastClick = 0;
unsigned long lastRawPressed = 0;


void setupButtons()
{
      pinMode(KEYS_PIN, INPUT);
}




int getPressedButton() {
 
  int raw = analogRead(KEYS_PIN);
  int b = -1;
  if (raw >= 350) {
    lastRawPressed = millis();
    if (raw >= 981) {
      b = 1;
    } else if (raw >= 940  && raw <= 955 ) {
      b = 2;//configurar
    } else if (raw >= 684 && raw < 704) {
      b = 3;//apagar
    } else if (raw >= 545 && raw <= 570) {
      b = 10;//caneta subir
    } else if (raw >= 750  && raw <= 770 ) {
      b = 5;//direita
    } else if (raw >= -3 && raw <= -3 ) {
      b = 6;//caneta
    } else if (raw >= 645  && raw <= 668 ) {
      b = 7;//cima/frente
    } else if (raw >= 920  && raw <= 935  ) {
      b = 8;//parar 
    } else if (raw >= 499  && raw <= 519 ) {
      b = 9;//baixo   
    } else if (raw >= 590  && raw <= 620 ) {
      b = -1;//caneta descer
    } else if (raw >= 820  && raw <= 850 ) {
      b = 0;//esquerda
    } else if (raw >= 720 && raw <= 740) {
      b = 1;//play
    }
    unsigned long currentClick = millis();
    if (lastButtonId != b) {
      if (currentClick > lastClick + DEBOUNCING_DELAY) {
        lastClick = currentClick;
        lastButtonId = b;
      } else {
        b = -1;
      }
    } else {
      if (currentClick > lastClick + LONG_CLICK_DELAY) {
        lastButtonId = b;
        b = b + 12;
        lastClick = currentClick;
      } else {
        b = -1;
      }
    }
  } else {
    if (millis() - lastRawPressed > 100) {
      lastButtonId = -1;
    }
  }
  return b;
}
