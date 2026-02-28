#include <MatrizLed.h>
MatrizLed led;

int heal = 3;
int x = 4;
int hard = 45;
int pad = 200;
int ability = 0;
int lok = -1;
int wipe = 0;
int pocet = 0;
bool reset = false;
bool gameover = false;
int score1 = 0;


unsigned long celek;
unsigned long score;
unsigned long lastFallTime = 0;
unsigned long fallInterval = pad; //delka pad

char scoreText[10];

void setup() {
  led.begin(12,10,11,1); // 12 din 10 clk 11 cs
  Serial.begin(9600);
  led.borrar();

  pinMode(3, INPUT_PULLUP); // button leva
  pinMode(4, INPUT_PULLUP); // button prava
  pinMode(5, INPUT_PULLUP); // ability
  pinMode(2, OUTPUT); //ability slow
  pinMode(13, OUTPUT); //ability wipe
  pinMode(7, OUTPUT); // led last zivot
  pinMode(8, OUTPUT); // led zivot 2
  pinMode(9, OUTPUT); // led zivot 3

  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);

  led.escribirFraseScroll("GAME START", 100);
  delay(1000);

  led.setLed(0,x - 1,0,true);
  led.setLed(0,x,0,true);
  led.setLed(0,x + 1,0,true);
  led.setLed(0,x,1,true);

  randomSeed(analogRead(A0));
  celek = millis();
}
void loop() {
  static bool lastState = HIGH;
  bool state = digitalRead(3);

  static bool lastState1 = HIGH;
  bool state1 = digitalRead(4);

  static bool lastState2 = HIGH;
  bool state2 = digitalRead(5);

  if (lastState == HIGH && state == LOW && x >= 2) {
    x--;
  }
  if (lastState1 == HIGH && state1 == LOW && x <= 5) {
    x++;
  }
  if (lastState2 == HIGH && state2 == LOW) {
    // schopnost

    if (ability == 1){
      wipe = 2;

      ability = 0;
      digitalWrite(13, LOW);
    }
    if (ability == 2) {
      pocet = 50;
      ability = 0;
      digitalWrite(2, LOW);
    }
  }

  lastState = state;
  lastState1 = state1;
  lastState2 = state2;
  if (pocet == 50) {
    pad = 10000;
    fallInterval = pad;
  }
  if (pocet <= 50 && pocet > 1) {
    pocet--;
    reset = true;
    fr();
    nd();
    rd();
    fo();
    fif();
    ses();
    sed();
    os();
  }
  if (pocet == 1) {
    reset = false;
    pad = 200;
    fallInterval = pad;
    pocet--;
  }
  if (heal > 0) {
    hra();

  }
  else {
  led.borrar();
  digitalWrite(13, LOW);
  digitalWrite(2, LOW);
  led.escribirFraseScroll("GAME OVER", 100);

  }


}


void fr() {
  
  static int y = -1;
  if (reset == false) {
    if (y == -1) {
      int a = random(1, hard);
      if (a == 2) {
        y = 8;
      }
    }
    if (wipe >= 1) {
      y = -1;

    }
    // padání bloku
    if (y > -1) {
      y--;
      led.setLed(0, 0, y, true);
      if (y < 7) {
        led.setLed(0, 0, y + 1, true);
      }
    }
    if (y == 0) {
      if (x - 1 == 0) {
        heal--;

      }
    }
  }
  else {
    led.setLed(0, 0, y, true);
    if (y < 7 && y > -1) {
      led.setLed(0, 0, y + 1, true);
    }
  }
}
void nd() {
  static int y = -1;
  static int ag = 0;
  if (reset == false) {
    if (y == -1) {
      int a = random(1, hard);
    
      if (a == 2) {
        y = 8;
      }
    }
    if (wipe >= 1) {
      y = -1;
    }
  // padání bloku
    if (y > -1) {
      y--;
      led.setLed(0, 1, y, true);
      if (y < 7) {
        led.setLed(0, 1, y + 1, true);
      }
    }
    if (y == 0 || y == 1) {
      if (x == 1 && ag == 0){
        heal--;
        ag++;

        delay(50);
      }
      if (y == 0) {
        if (x - 1 == 1 && ag == 0){
          heal--;

        }
      }
      if (y == -1){
        ag = 0;
      }
    }
  }
  else {
    led.setLed(0, 1, y, true);
    if (y < 7 && y > -1) {
      led.setLed(0, 1, y + 1, true);
    }
  }
}
void rd() {
  static int ag = 0;
  static int y = -1;
  if (reset == false) {
    if (y == -1) {
      int a = random(1, hard);
      if (a == 2) {
        y = 8;
      }
    }
    if (wipe >= 1) {
      y = -1;
    }
  // padání bloku
    if (y > -1) {
      y--;
      led.setLed(0, 2, y, true);
      if (y < 7) {
        led.setLed(0, 2, y + 1, true);
      }
    }
    if (y == 0 || y == 1) {
      if (x == 2 && ag == 0){
        heal--;
        ag++;

        delay(50);
      }
      if (y == 0) {
        if (x - 1 == 2 && ag == 0 || x + 1 == 2 && ag == 0){
          heal--;

        }
      }
      if (y == -1){
        ag = 0;
      }
    }
  }
  else {
    led.setLed(0, 2, y, true);
    if (y < 7 && y > -1) {
      led.setLed(0, 2, y + 1, true);
    }
  }
}
void fo() {
  static int y = -1;
  static int ag = 0;
  if (reset == false) {
    if (y == -1) {
      int a = random(1, hard);
      if  (a == 2) {
        y = 8;
      }
    }
    if (wipe >= 1) {
      y = -1;
    }
  // padání bloku
    if (y > -1) {
      y--;
      led.setLed(0, 3, y, true);
      if (y < 7) {
        led.setLed(0, 3, y + 1, true);
      }
    }
    if (y == 0 || y == 1) {
      if (x == 3 && ag == 0){
        heal--;
        ag++;

        delay(50);
      }
      if (y == 0) {
        if (x - 1 == 3 && ag == 0 || x + 1 == 3 && ag == 0){
          heal--;

        }
      }
      if (y == -1){
        ag = 0;
      }
    }
  }
  else {
    led.setLed(0, 3, y, true);
    if (y < 7 && y > -1) {
      led.setLed(0, 3, y + 1, true);
    }
  }
}
void fif() {
  static int y = -1;
  static int ag = 0;
  if (reset == false) {
    if (y == -1) {
      int a = random(1, hard);
      if (a == 2) {
        y = 8;
      }
    } 
    if (wipe >= 1) {
      y = -1;
  }
  // padání bloku
    if (y > -1) {
      y--;
      led.setLed(0,4, y, true);
      if (y < 7) {
        led.setLed(0,4, y + 1, true);
      }
    }
    if (y == 0 || y == 1) {
      if (x == 4 && ag == 0){
        heal--;
        ag++;

        delay(50);
      }
      if (y == 0) {
        if (x - 1 == 4 && ag == 0 || x + 1 == 4 && ag == 0){
          heal--;

        }
      }
      if (y == -1){
        ag = 0;
      }
    }
  }
  else {
    led.setLed(0, 4, y, true);
    if (y < 7 && y > -1) {
      led.setLed(0, 4, y + 1, true);
    }
  }
}
void ses() {
  static int y = -1;
  static int ag = 0;
  if (reset == false) {
    if (y == -1) {
      int a = random(1, hard);
      if (a == 2) {
        y = 8;
      }
    }
    if (wipe >= 1) {
      y = -1;
    }
  // padání bloku
    if (y > -1) {
      y--;
      led.setLed(0,5, y, true);
      if (y < 7) {
        led.setLed(0,5, y + 1, true);
      }
    }
    if (y == 0 || y == 1) {
      if (x == 5 && ag == 0){
        heal--;
        ag++;

        delay(50);
      }
      if (y == 0) {
        if (x - 1 == 5 && ag == 0 || x + 1 == 5 && ag == 0){
          heal--;

        }
      }
      if (y == -1){
        ag = 0;
      }
    }
  }
  else {
    led.setLed(0, 5, y, true);
    if (y < 7 && y > -1) {
      led.setLed(0, 5, y + 1, true);
    }
  }
}
void sed() {
  static int y = -1;
  static int ag = 0;
  if (reset == false) {
    if (y == -1) {
      int a = random(1, hard);
      if (a == 2) {
        y = 8;
      }
    }
    if (wipe >= 1) {
      y = -1;
    }
  // padání bloku
    if (y > -1) {
      y--;
      led.setLed(0,6, y, true);
      if (y < 7) {
        led.setLed(0,6, y + 1, true);
      }
    }
    if (y == 0 || y == 1) {
      if (x == 6 && ag == 0){
        heal--;
        ag++;

        delay(50);
      }
      if (y == 0) {
        if (x - 1 == 6 && ag == 0 || x + 1 == 6 && ag == 0){
          heal--;

        }
      }
      if (y == -1){
        ag = 0;
      }
    }
  }
  else {
    led.setLed(0, 6, y, true);
    if (y < 7 && y > -1) {
      led.setLed(0, 6, y + 1, true);
    }
  }
}
void os() {
  static int y = -1;
  static int ag = 0;
  if (reset == false) {
    if (y == -1) {
      int a = random(1, hard);
      if (a == 2) {
        y = 8;
      }
    }
    if (wipe >= 1) {
      y = -1;
    }
  // padání bloku
    if (y > -1) {
      y--;
      led.setLed(0,7, y, true);
      if (y < 7) {
        led.setLed(0,7, y + 1, true);
      }
    }
    if (y == 0) {
      if (x + 1 == 7) {
        heal--;

      }
    }
  }
  else {
    led.setLed(0, 7, y, true);
    if (y < 7 && y > -1) {
      led.setLed(0, 7, y + 1, true);
    }
  }
}
void hra() {
  delay(100);
  led.borrar();

  unsigned long currentTime = millis();
  if (currentTime - lastFallTime >= fallInterval) {
    fr();
    nd();
    rd();
    fo();
    fif();
    ses();
    sed();
    os();
    abilit();
    lastFallTime = currentTime;
  }
  led.setLed(0,x - 1,0,true);
  led.setLed(0,x,0,true);
  led.setLed(0,x + 1,0,true);
  led.setLed(0,x,1,true);

  digitalWrite(9, heal >= 3 ? HIGH : LOW);
  digitalWrite(8, heal >= 2 ? HIGH : LOW);
  digitalWrite(7, heal >= 1 ? HIGH : LOW);
  if (wipe > 0) {
    wipe--;

  }


}
void abilit() {
 if (ability == 0) {
  int a = random(1, 10);
  if (a == 5) {
    int b = random(1, 3);
    if ( b == 1) {
      ability = 1;
      digitalWrite(13, HIGH);
    }
    if (b == 2) {
      ability = 2;
      digitalWrite(2, HIGH);
    }

  }
 }
}
