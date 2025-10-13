#include <Adafruit_ssd1306syp.h>
Adafruit_ssd1306syp A(A3,A2);
int h = 0, s = 0;
const double Pi = 3.14;
const unsigned char PROGMEM bmp[] =
{  
  B00000000,
  B00111100,
  B01111110,
  B01111110,
  B01111110,
  B01111110,
  B00111100,
  B00000000,
};

void setup() {
  Serial.begin(250000);
  for (int i = 8; i <= 11; i++) {
    pinMode (i, OUTPUT);
  }
  pinMode (13, INPUT);
  pinMode (12, INPUT);
  pinMode(7,INPUT);
  
  pinMode (5, OUTPUT);
  pinMode (6, INPUT);
  
  digitalWrite(10, LOW);   //LED燈
  digitalWrite(9, LOW);
  digitalWrite(8, LOW);
  digitalWrite(4, LOW);
  A.initialize();
}

int Adisplay(int ag, int bg, int axl, int ayu, int bxl, int byu, int ballx, int bally) {    //顯示畫面
  A.setCursor(0,8);    //顯示分數
  A.setTextSize(1);
  A.println("your score");
  A.setCursor(65,8);
  A.setTextSize(1);
  A.println(s);
  
  A.drawLine(0, 17, 127, 17,WHITE);    //顯示外框
  A.drawLine(0, 63, 127, 63,WHITE);
  for (int i = 17; i < 63; i += 2) {
    A.drawLine(63, i, 64, i,WHITE);
  }
  A.drawLine(0, 17, 0, ag,WHITE);
  A.drawLine(0, 63, 0, ag + 30,WHITE);
  A.drawLine(127, 17, 127, bg,WHITE);
  A.drawLine(127, 63, 127, bg + 30,WHITE);
      
  A.drawLine(axl, ayu, axl + 5, ayu,WHITE);   //顯示玩家球拍
  A.drawLine(axl, ayu + 16, axl + 5, ayu + 16,WHITE);
  A.drawLine(axl, ayu, axl, ayu + 16,WHITE);
  A.drawLine(axl + 5, ayu, axl + 5, ayu + 16,WHITE);

  A.drawLine(bxl, byu, bxl + 5, byu,WHITE);   //顯示對手球拍
  A.drawLine(bxl, byu + 16, bxl + 5, byu + 16,WHITE);
  A.drawLine(bxl, byu, bxl, byu + 16,WHITE);
  A.drawLine(bxl + 5, byu, bxl + 5, byu + 16,WHITE);
        
  A.drawBitmap(ballx, bally, bmp, 8, 8, 1);   //顯示球

  A.update();
}

void loop() {
  int flag = 1;
  if (h < s) {
    h = s;
  }
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(7, HIGH);
  while (digitalRead(12) && digitalRead(13) && digitalRead(7) && flag) {    //遊戲初始介面
    A.setCursor(0,8);    //固定的圖案
    A.setTextSize(1);
    A.println("* highest score");
    A.setCursor(95,8);
    A.setTextSize(1);
    A.println(h);
    A.setCursor(0,18);
    A.setTextSize(1);
    A.println("your score");
    A.setCursor(65,18);
    A.println(s);
    A.drawLine(6, 34, 112, 34,WHITE);
    A.drawLine(6, 57, 112, 57,WHITE);
    A.drawLine(6, 34, 6, 57,WHITE);
    A.drawLine(112, 34, 112, 57,WHITE);
    A.update();
    
    digitalWrite(4, LOW);
    A.setCursor(0,38);   //閃爍的圖案
    A.println("  press any button");
    A.println("     to start");
    for (int i = 0; i < 500;i++) {
      delay(1);
      if (!digitalRead(12) || !digitalRead(13) || !digitalRead(7)) {
        flag = 0;
        break;
      }
    }
    if (!flag) {
        break;
    }
    A.update();
    digitalWrite(4, HIGH);
    for (int i = 0; i < 500;i++) {
      delay(1);
      if (!digitalRead(12) || !digitalRead(13) || !digitalRead(7)) {
        flag = 0;
        break;
      }
    }
    if (!flag) {
        break;
    }
    A.clear();
  }
  digitalWrite(4, LOW);

  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  for (int i = 3; i > 0; i--) {    //倒數
    A.clear();
    A.setCursor(0,8);
    A.setTextSize(1);
    A.println("game start in :");
    A.setCursor(54,25);
    A.setTextSize(4);
    A.println(i);
    A.update();
    tone(11, 659, 250);
    delay(1000);
    digitalWrite(i + 7, LOW);
  }
  A.clear();
  A.setCursor(27,20);
  A.setTextSize(5);
  A.println("GO!");
  A.update();
  tone(11, 1318, 500);
  digitalWrite(4, HIGH);
  delay(1000);
  digitalWrite(4, LOW);
  
  //遊戲開始
  int life = 3, ag, bg, axl, ayu, bxl, byu, ballx, bally, ballspeed = 6, t, times = 0;
  s = 0;
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  while (life) {
    ag = 25, bg = 25, axl = 20, ayu = 32, bxl = 102, byu = 32, ballx = 60, bally = 36;
    bool rebounda = 1, reboundb = 0, speedup = 0;
    times++;
    
    digitalWrite(5, HIGH);    //速度 & 方向設定
    delayMicroseconds(10); 
    digitalWrite(5, LOW); 
    int time_echo = pulseIn(6, HIGH);
    Serial.print(time_echo);
    t = (time_echo + random(10000)) % 60 - 30;
    if ((random(2) + time_echo) % 2) {
      t = 180 - t;
    }
    ballspeed += ballspeed / 2.6 / times;
    
    A.clear();
    Adisplay(ag, bg, axl, ayu, bxl, byu, ballx, bally);
    delay(1000);
    while (1) {
      A.clear();
           
      if (!digitalRead(13) && ag > 17) {   //玩家操控球門
        ag -= 8;
      }
      if (!digitalRead(12) && ag < 33) {
        ag += 8;
      }
      
      if (analogRead(A4) < 550) {   //玩家操控球拍
        if (axl + pow((550 - analogRead(A4)) / 165, 1.2) < 58) {
          axl += pow((550 - analogRead(A4)) / 165, 1.2);
        } else {
          axl = 58;
        }
      }
      if (analogRead(A4) > 500) {
        if (axl - pow((analogRead(A4) - 500) / 150, 1.2) > 20) {
          axl -= pow((analogRead(A4) - 500) / 150, 1.2);
        } else {
          axl = 20;
       }
      }
      if (analogRead(A5) < 550) {
        if (ayu - pow((550 - analogRead(A5)) / 165, 1.2) > 17) {
          ayu -= pow((550 - analogRead(A5)) / 165, 1.2);
        } else {
           ayu = 17;
        }
      }
      if (analogRead(A5) > 500) {
        if (ayu + pow((analogRead(A5) - 500) / 150, 1.2) < 46) {
          ayu += pow((analogRead(A5) - 500) / 150, 1.2);
        } else {
          ayu = 46;
         }
      }

      if (ballx > 96) {   //電腦操控球門
        int k = (random(10) + time_echo) % 10;   
        if (k <= 4) {
          if (bg > 17 && bally > 40) {
            bg -= 8;
          } else if (bg < 33 && bally < 32) {
            bg += 8;
          }
        } else if (k == 5) {
          if (bg > 17 && bally < 32) {
            bg -= 8;
          } else if (bg < 33 && bally > 40) {
            bg += 8;
          }
        }
      }
      
      if (ballx > 40) {   //電腦操控球拍
        int k = (random(10) + time_echo) % 10;
        if (ballx < bxl && k > 3) {
          if (byu > 20 && bally < byu) {
            byu -= 3;
          } else if (byu < 43 && bally - 9 > byu) {
            byu += 3; 
          }  
          if (bxl < 99 && k > 7) {
            bxl += 3;
          } else if (bxl > 67 && k < 6) {
            bxl -= 3; 
          }
        } else if (k != 0) {
          if (byu > 20 && bally > 46 - (times % 2) * 20) {
            byu -= 3;
          } else if (byu < 43 && bally < 63) {
            byu += 3;
          } 
          if (bxl < 99) {
            bxl += 3;
          }
        }
      }
      
      if (bally < 20) {   //球反彈場地 & 進球
        t = abs(t);
        tone(11, 294, 100);
      }
      if (bally > 54) {
        t = -abs(t);
        tone(11, 294, 100);
      }
      if (ballx < 1) {
        rebounda = 0, reboundb = 0, speedup = 0;
        if (bally >= ag && bally <= ag + 22) {
          life--;
          A.clear();
          Adisplay(ag, bg, axl, ayu, bxl, byu, -100, -100);
          for (int i = 0; i < 3; i++) {   //電腦進球動畫
            digitalWrite(life + 8, LOW);
            tone(11, 466, 100);
            delay(100);
            digitalWrite(life + 8, HIGH);
            tone(11, 440, 100);
            delay(100);
          }
          digitalWrite(life + 8, LOW);
          break;
        }
        if (t > 0) {
          t = 180 - t;
        } else {
          t = -180 - t;
        }
        tone(11, 294, 100);
      }
      if (ballx > 118) {
        rebounda = 1, reboundb = 1, speedup = 0;
        A.clear();
        Adisplay(ag, bg, axl, ayu, bxl, byu, -100, -100);
        if (bally >= bg && bally <= bg + 22) {   //玩家進球動畫
          s += 100;
          digitalWrite(4, HIGH);
          delay(100);
          tone(11, 784, 100);
          digitalWrite(4, LOW);
          delay(100);
          tone(11, 1175, 100);
          digitalWrite(4, HIGH);
          delay(100);
          tone(11, 988, 100);
          digitalWrite(4, LOW);
          delay(100);
          tone(11, 1175, 100);
          digitalWrite(4, HIGH);
          delay(100);
          tone(11, 1046, 200);
          digitalWrite(4, LOW);
          delay(100);
          break;
        }
        if (t > 0) {
          t = 180 - t;
        } else {
          t = -180 - t;
        }
        tone(11, 294, 100);
      }
      
      if (ballx > axl - 8 && ballx < axl + 9 && bally > ayu - 8 && bally < ayu + 17) {    //球反彈玩家球拍
        if (rebounda) {
          if (t > 0) {
            t = random(15, 64);
          } else {
            t = -random(15, 64);
          }
          
        } else {
          if (t > 0) {
            t = random(165, 118);
          } else {
            t = -random(165, 118);
          }
        }
        reboundb = 0;
        tone(11, 784, 100);
        if (!digitalRead(7)) {
          speedup = 1;
          t *= 0.7;
        } else {
          speedup = 0;
        }
      }
      
      if (ballx > bxl - 8 && ballx < bxl + 9 && bally > byu - 8 && bally < byu + 17) {    //球反彈對手球拍
        if (reboundb) {
          if (t > 0) {
            t = random(15, 64);
          } else {
            t = -random(15, 64);
          }
          if (random(4) + time_echo) {
            speedup = 0;
          } else {
            speedup = 1;
            t *= 0.7;
          }
        } else {
          if (t > 0) {
            t = random(165, 118);
          } else {
            t = -random(165, 118);
          }
        }
        rebounda = 1;
        tone(11, 1568, 100);
      }

      if (speedup) {
        ballx += (ballspeed * 1.4) * cos(t * Pi / 180);   //球的座標
        bally += (ballspeed * 1.4) * sin(t * Pi / 180);
      } else {
        ballx += ballspeed * cos(t * Pi / 180);   //球的座標
        bally += ballspeed * sin(t * Pi / 180);
      }
      
      if (ballx > 119) {
        ballx = 119;
      } else if (ballx < 0) {
        ballx = 0;
      }
      if (bally > 55) {
        bally = 55;
      } else if (bally < 18) {
        bally = 18;
      }
      
      Adisplay(ag, bg, axl, ayu, bxl, byu, ballx, bally);
    }
  }
  A.clear();    //遊戲結束
  A.setCursor(0,8);
  A.setTextSize(1);
  A.println("your score");
  A.setCursor(65,8);
  A.setTextSize(1);
  A.println(s);
  A.setCursor(65,8);
  A.setTextSize(1);
  A.println(s);
  A.setCursor(10, 40);
  A.setTextSize(2);
  A.println("GAME OVER");
  A.update();
  int p = 120;
  delay(p);
  for (int i = 440; i > 138; i -= 25.5) {
    digitalWrite(i % 3 + 8, LOW);
    digitalWrite((i + 1) % 3 + 8, LOW);
    digitalWrite((i + 2) % 3 + 8, HIGH);
    tone(11, i);
    delay(p / 3);
  }
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  noTone(11);
  delay(p * 8);
  tone(11, 784);
  delay(p);
  tone(11, 1046);
  delay(p);
  tone(11, 1318);
  delay(p);
  tone(11, 1046);
  delay(p);
  tone(11, 1318);
  delay(p);
  tone(11, 1568);
  delay(p);
  tone(11, 1661);
  delay(p * 2);
  tone(11, 1568);
  delay(p);
  tone(11, 1397);
  delay(p);
  tone(11, 1568);
  delay(p * 4);
  noTone(11);
  delay(2500);
  A.clear();
}
