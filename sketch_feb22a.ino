
int trigger[2] = {10,8};
int echo[2] = {11,9};

unsigned long startTime;
unsigned long stopTime;

int visitorCount;

float speedOfSound = 0.034;

long elapsedMicroseconds[2];

float initialDuration[2];
float initialDistance[2];

float duration[2];
float distance[2];

void setup() {

  Serial.begin(9600);

  for(int i = 0; i < 2; i++) {
    pinMode(trigger[i],OUTPUT);
    pinMode(echo[i],INPUT);
  }

  visitorCount = 0;

  for (int i = 0; i < 2; i++) {
    digitalWrite(trigger[i],LOW);
    delayMicroseconds(2);
    digitalWrite(trigger[i],HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger[i],LOW);
    delayMicroseconds(2);

    initialDuration[i] = pulseIn(echo[i],HIGH);
    delay(1000);
  }

  for (int i = 0; i < 2; i++) {
    initialDistance[i] = initialDuration[i]/2 * speedOfSound;
//    delay(1000);
    }


  Serial.print("System has been initialized\n\n");
  for (int i = 0; i < 2; i++){
    if (i == 0)
      Serial.print("initial distnace[0] = ");
    else
      Serial.print("initial distnace[1] = ");
   Serial.print(initialDistance[i]); Serial.print(" cm\n");
  }
   delay(5*1000);

}

void loop() {

  for (int i = 0; i < 2; i++){

    digitalWrite(trigger[i],LOW);
    delayMicroseconds(2);
    digitalWrite(trigger[i],HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger[i],LOW);
    delayMicroseconds(2);

    startTime = micros();
    duration[i] = pulseIn(echo[i],HIGH);
    stopTime = micros();
    elapsedMicroseconds[i] = stopTime - startTime;
  }

  for (int i = 0; i < 2; i++) {
     distance[i] = duration[i]/2 * speedOfSound;
  }
    

  if (distance[0] < (0.97*initialDistance[0]) && distance[1] < (0.97*initialDistance[1])) {
    Serial.print("obstacle detected\n");

        for (int i = 0; i < 2; i++){
        if (i == 0)
          Serial.print("elapsedMicroseconds[0] = ");
        else
          Serial.print("elapsedMicroseoncds[1] = ");
        Serial.print(elapsedMicroseconds[i]); Serial.print("\n\n\n");
        }

        if (elapsedMicroseconds[0] < elapsedMicroseconds[1])
          visitorCount++;
        else if (elapsedMicroseconds[0] > elapsedMicroseconds[1])
          visitorCount--;
  }
  else {
    Serial.print(" no obstacle \n");
      for (int i = 0; i < 2; i++){
        if (i == 0)
          Serial.print("distnace[0] = ");
        else
          Serial.print("distnace[1] = ");
        Serial.print(distance[i]); Serial.print(" cm\n");

      }

  }

  Serial.print("No of people inside = "); Serial.print(visitorCount); Serial.print("\n\n");
  delay(1500);

}
