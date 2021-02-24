/* Pins to microcontroller */

int trigger[2] = {10,8};
int echo[2] = {11,9};

/* Sensor Data */

float initialDuration[2];
float duration[2];

/* For data manupulation */

float speedOfSound = 0.034; 

float initialDistance[2];
float distance[2];

String sequence = "";
int timeOutCounter = 0;
unsigned visitorCount = 0;

int i; // gloabal loop variable

void setup() {

  Serial.begin(9600);
  delay(200);
  for(i = 0; i < 2; i++) {
    pinMode(trigger[i],OUTPUT);
    pinMode(echo[i],INPUT);
    initialDistance[i] = measureDistance(i);
  }

  /* Displaying init information */

  i = 0;
  
  switch (i) { 
    case 0: {
      Serial.print("initial distance[0] = ");
      Serial.print(initialDistance[0]); Serial.print(" cm\n");
    }
 
    case 1: {
      Serial.print("initial distance[1] = ");
      Serial.print(initialDistance[1]); Serial.print(" cm\n");
    }      
  }

  Serial.print("System has been initialized\n");
}

void loop() {

  for(i = 0; i < 2; i++) {
    distance[i] = measureDistance(i);
  }  

  if (distance[0] < (0.95 * initialDistance[0]) && distance[1] < (0.97 * initialDistance[1])) {
    Serial.print("obstacle detected\n");

        for (i = 0; i < 2; i++){
        if (i == 0)
          Serial.print("distance[0] = ");
        else
          Serial.print("distance[1] = ");
        Serial.print(distance[i]); Serial.print(" cm \n");
        }
  }
  else {
    Serial.print(" no obstacle \n");
      for (i = 0; i < 2; i++){
        if (i == 0)
          Serial.print("distnace[0] = ");
        else
          Serial.print("distnace[1] = ");
        Serial.print(distance[i]); Serial.print(" cm\n");
      }

  }

  delay(800);

}

float measureDistance(int i) {
  
    digitalWrite(trigger[i],LOW);
    delayMicroseconds(2);
    digitalWrite(trigger[i],HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger[i],LOW);
    delayMicroseconds(2);

  return (pulseIn(echo[i],HIGH)/2*speedOfSound);
}
