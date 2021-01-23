#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#define X_MIN_PIN           3
#define X_MAX_PIN           2

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19

#define E_STEP_PIN         26
#define E_DIR_PIN          28
#define E_ENABLE_PIN       24

#define Q_STEP_PIN         36
#define Q_DIR_PIN          34
#define Q_ENABLE_PIN       30

#define SDPOWER            -1
#define SDSS               53
#define LED_PIN            13

#define FAN_PIN            9

#define PS_ON_PIN          12
#define KILL_PIN           -1

#define HEATER_0_PIN       10
#define HEATER_1_PIN       8
#define TEMP_0_PIN          13   // ANALOG NUMBERING
#define TEMP_1_PIN          14   // ANALOG NUMBERING

int isHomeKnown = 0;
int xmaxx = 0;
int ymaxx = 0;
int isChasing =0;
void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN  , OUTPUT);

  pinMode(X_STEP_PIN  , OUTPUT);
  pinMode(X_DIR_PIN    , OUTPUT);
  pinMode(X_ENABLE_PIN    , OUTPUT);

  pinMode(Y_STEP_PIN  , OUTPUT);
  pinMode(Y_DIR_PIN    , OUTPUT);
  pinMode(Y_ENABLE_PIN    , OUTPUT);

  pinMode(Z_STEP_PIN  , OUTPUT);
  pinMode(Z_DIR_PIN    , OUTPUT);
  pinMode(Z_ENABLE_PIN    , OUTPUT);

  digitalWrite(X_ENABLE_PIN    , LOW);
  digitalWrite(Y_ENABLE_PIN    , LOW);
  digitalWrite(Z_ENABLE_PIN    , LOW);
  isHomeKnown = 0;
}





void loop () {


  if (isHomeKnown == 0)
  {
    digitalWrite(Y_DIR_PIN    , LOW);
    digitalWrite(Z_DIR_PIN    , HIGH);
    int val1, val2;
    for (int i = 0; i < 250; i++)
    {
      val1 = digitalRead(Z_MIN_PIN);
      if (val1 != 0) {
        digitalWrite(Y_STEP_PIN    , HIGH);
        digitalWrite(Z_STEP_PIN    , HIGH);

        digitalWrite(Y_STEP_PIN    , LOW);
        digitalWrite(Z_STEP_PIN    , LOW);
        delay(2);
      }
    }

    digitalWrite(X_DIR_PIN    , HIGH);
    for (int i = 0; i < 250; i++) {
      val2 = digitalRead(X_MIN_PIN);
      if (val2 != 0) {
        digitalWrite(X_STEP_PIN    , HIGH);
        digitalWrite(X_STEP_PIN    , LOW);
        delay(2);
      }
    }
    Serial.println(isHomeKnown);

    if ((val1 == 0) && (val2 == 0)) {
      isHomeKnown = 1;
      Serial.println("here");

    }
  }
  if (Serial.available() > 0) {

    char command = Serial.read();
    Serial.println(command);
    if (command == '1') {
      digitalWrite(X_DIR_PIN    , HIGH);
      for (int i = 0; i < 250; i++) {
        int val = digitalRead(X_MIN_PIN);
        if (val != 0) {
          digitalWrite(X_STEP_PIN    , HIGH);
          digitalWrite(X_STEP_PIN    , LOW);
          xmaxx--;

          delay(2);
        }
      }
    }
    else if (command == '2')
    {
      digitalWrite(X_DIR_PIN    , LOW);
      for (int i = 0; i < 250 && xmaxx < 2900; i++)
      {
        digitalWrite(X_STEP_PIN    , HIGH);
        digitalWrite(X_STEP_PIN    , LOW);
        xmaxx++;
        delay(2);
      }
    }
    else if (command == '3')
    {
      digitalWrite(Y_DIR_PIN    , LOW);
      digitalWrite(Z_DIR_PIN    , HIGH);

      for (int i = 0; i < 250; i++)
      {
        int val = digitalRead(Z_MIN_PIN);
        if (val != 0) {
          digitalWrite(Y_STEP_PIN    , HIGH);
          digitalWrite(Z_STEP_PIN    , HIGH);

          digitalWrite(Y_STEP_PIN    , LOW);
          digitalWrite(Z_STEP_PIN    , LOW);
          ymaxx--;
          delay(2);
        }
      }
    }
    else if (command == '4')
    {
      digitalWrite(Y_DIR_PIN    , HIGH);
      digitalWrite(Z_DIR_PIN    , LOW);

      for (int i = 0; i < 250 && ymaxx < 2400; i++)
      {

        digitalWrite(Y_STEP_PIN    , HIGH);
        digitalWrite(Z_STEP_PIN    , HIGH);

        digitalWrite(Y_STEP_PIN    , LOW);
        digitalWrite(Z_STEP_PIN    , LOW);
        ymaxx++;
        delay(2);
      }
    }
    else if(command == 'g')
    {
      isChasing =1;
    }
  }
  //  if (millis() %1000 <500)
  //    {digitalWrite(LED_PIN, HIGH);
  //  }else{
  //   digitalWrite(LED_PIN, LOW);
  //
  //  digitalWrite(FAN_PIN, LOW);
  // }
  //
  //
  //  if (millis() %4000 <2000) {
  //    digitalWrite(X_DIR_PIN    ,HIGH);
  //    digitalWrite(Y_DIR_PIN    , HIGH);
  //    digitalWrite(Z_DIR_PIN    , HIGH);
  //
  //
  //  }
  //  else {
  //
  //    digitalWrite(X_DIR_PIN    , LOW);
  //    digitalWrite(Y_DIR_PIN    , LOW);
  //    digitalWrite(Z_DIR_PIN    , LOW);
  //    }
  //
  //
  //    digitalWrite(X_STEP_PIN    , HIGH);
  //    digitalWrite(Y_STEP_PIN    , HIGH);
  //    digitalWrite(Z_STEP_PIN    , HIGH);
  //    delay(1);
  //
  //    digitalWrite(X_STEP_PIN    , LOW);
  //    digitalWrite(Y_STEP_PIN    , LOW);
  //    digitalWrite(Z_STEP_PIN    , LOW);
}
