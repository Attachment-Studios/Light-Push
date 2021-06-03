// Light Push

int start_btn = 13;

int ot1 = 9;
int ot2 = 8;
int ot3 = 7;
int ot4 = 6;

int bt1 = 2;
int bt2 = 3;
int bt3 = 4;
int bt4 = 5;

int c1 = 0;
int c2 = 0;
int c3 = 0;
int c4 = 0;

int minTick = 562;
int maxTick = 2343;

bool active = false;

void setup(){
  pinMode(start_btn, INPUT_PULLUP);
  
  pinMode(bt1, INPUT_PULLUP);
  pinMode(bt2, INPUT_PULLUP);
  pinMode(bt3, INPUT_PULLUP);
  pinMode(bt4, INPUT_PULLUP);
  
  pinMode(ot1, OUTPUT);
  pinMode(ot2, OUTPUT);
  pinMode(ot3, OUTPUT);
  pinMode(ot4, OUTPUT);
  
  Serial.begin(9600);
}

bool hasStarted = false;
int startCount = 0;

bool isBeingPressed = false;

int color = 9;
int tick = 0;

int nextRandomTick = random(minTick, maxTick);

int score = 0;
bool updateScore = false;

String playMode = "PLAY";

void loop(){
  if ( startCount == 0 ){
    c1 = 1;
    c2 = 1;
    c3 = 1;
    c4 = 1;
    analogWrite(ot1, 255 * c1);
    analogWrite(ot2, 255 * c2);
    analogWrite(ot3, 255 * c3);
    analogWrite(ot4, 255 * c4);
    Serial.println("Light Push!!!");
    delay(1000);
  } else {
    c1 = 0;
    c2 = 0;
    c3 = 0;
    c4 = 0;
  }
  if ( hasStarted == false ){
    startCount += 1;
    delay(100);
    if ( startCount > 1 ) {
      color += 1;
      if ( color > 4 ){
        color -= 4;
      }
      if ( color == 1 ){
        c1 = 1;
      }
      else if ( color == 2 ){
        c2 = 1;
      } else if ( color == 3 ){
        c3 = 1;
      } else{
        c4 = 1;
      }
    }
    if ( startCount > 21 ){
      hasStarted = true;
      c1 = 0;
      c2 = 0;
      c3 = 0;
      c4 = 0;
      color = 9;
      tick = 0;
      nextRandomTick = random(minTick, maxTick);
      score = 0;
      updateScore = true;
      score = -1;
      playMode = "PLAY";
    }
  }
  if ( hasStarted == true ){
    if ( digitalRead(start_btn) == LOW ){
      c1 = 1;
      c2 = 1;
      c3 = 1;
      c4 = 1;
      if ( isBeingPressed == false ){
        isBeingPressed = true;
        active = not(active);
        hasStarted = false;
        startCount = 0;
        color = 0;
      }
    }
    if ( digitalRead(start_btn) == HIGH ){
      c1 = 0;
      c2 = 0;
      c3 = 0;
      c4 = 0;
      if ( isBeingPressed == true ){
        isBeingPressed = false;
      }
    }
    if ( playMode == "PLAY" ){
      tick += 1;
      Serial.print(tick);
      if ( tick > nextRandomTick ){
        color = random(1, 5);
        tick = 0;
        nextRandomTick = random(minTick, maxTick);
        Serial.println();
        maxTick -= 2;
        if ( maxTick < minTick ){
          maxTick = minTick;
        }
        if ( updateScore == true ){
          score += 1;
        } else {
          playMode = "LOST";
        }
        updateScore = false;
      }
      int b1r = not(digitalRead(bt1));
      int b2r = not(digitalRead(bt2));
      int b3r = not(digitalRead(bt3));
      int b4r = not(digitalRead(bt4));
      if ( b1r == HIGH or color == 1 ){
        c1 = 1;
      }
      if ( b2r == HIGH or color == 2 ){
        c2 = 1;
      }
      if ( b3r == HIGH or color == 3 ){
        c3 = 1;
      }
      if ( b4r == HIGH or color == 4 ){
        c4 = 1;
      }
      if ( color == 1 ) {
        if ( b2r == LOW and b3r == LOW and b4r == LOW ){
          if ( b1r == HIGH ){
            updateScore = true;
          }
        } else {
          updateScore = false;
          playMode = "LOST";
        }
      }
      if ( color == 2 ) {
        if ( b1r == LOW and b3r == LOW and b4r == LOW ){
          if ( b2r == HIGH ){
            updateScore = true;
          }
        } else {
          updateScore = false;
          playMode = "LOST";
        }
      }
      if ( color == 3 ) {
        if ( b2r == LOW and b1r == LOW and b4r == LOW ){
          if ( b3r == HIGH ){
            updateScore = true;
          }
        } else {
          updateScore = false;
          playMode = "LOST";
        }
      }
      if ( color == 4 ) {
        if ( b2r == LOW and b3r == LOW and b1r == LOW ){
          if ( b4r == HIGH ){
            updateScore = true;
          }
        } else {
          updateScore = false;
          playMode = "LOST";
        }
      }
      if ( color > 4 ){
        updateScore = true;
        score = -1;
      }
    } else {
      c1 = 1;
      c2 = 1;
      c3 = 1;
      c4 = 1;
    }
  }
  if ( updateScore == true ){
    tick = nextRandomTick;
    c1 = 0;
    c2 = 0;
    c3 = 0;
    c4 = 0;
  }
  analogWrite(ot1, 255 * c1);
  analogWrite(ot2, 255 * c2);
  analogWrite(ot3, 255 * c3);
  analogWrite(ot4, 255 * c4);
  if ( startCount < 2 or updateScore == true ){
    delay(1000);
  }
}
