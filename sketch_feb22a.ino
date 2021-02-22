
int trigger = 10;
int echo[2] = {9,7};

unsigned long startTime;
unsigned long stopTime;

float speedOfSound = 0.034;

long elapsedMicroseconds[2];

float initialDuration[2];
float initialDistance[2];

float duration[2];
float distance[2];

void setup() {
  
  Serial.begin(9600);
  
  pinMode(trigger,OUTPUT);
  
  for(int i = 0; i < 2; i++) {  
    pinMode(echo[i],INPUT);
  }
    

  Serial.print("starting init \n");

  for (int i = 0; i < 2; i++) {
    digitalWrite(trigger,LOW);
    delayMicroseconds(2);
    digitalWrite(trigger,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger,LOW);
    delayMicroseconds(2);
  
    initialDuration[i] = pulseIn(echo[i],HIGH);
  }
      
  for (int i = 0; i < 2; i++)
    initialDistance[i] = initialDuration[i]/2 * speedOfSound;
    

  Serial.print("System has been initialized\n\n");  
  for (int i = 0; i < 2; i++){
    if (i == 0)
      Serial.print("initial distnace[0] = ");
    else 
      Serial.print("initial distnace[1] = ");  
   Serial.print(initialDistance[i]); Serial.print(" cm\n");  
  }  

}

void loop() {
  
  for (int i = 0; i < 2; i++){
    
    digitalWrite(trigger,LOW);
    delayMicroseconds(2);
    digitalWrite(trigger,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger,LOW);
    delayMicroseconds(2);

    startTime = micros();
    duration[i] = pulseIn(echo[i],HIGH);
    stopTime = micros();
    elapsedMicroseconds[i] = stopTime - startTime;
  }
    
  for (int i = 0; i < 2; i++)
     distance[i] = duration[i]/2 * speedOfSound;

  if (distance[0] < (0.97*initialDistance[0]) || distance[1] < (0.97*initialDistance[1])) {
    Serial.print("obstacle detected\n");
        if (elapsedMicroseconds[0] < elapsedMicroseconds[1])
          Serial.print("in\n");
        else if (elapsedMicroseconds[0] > elapsedMicroseconds[1])
          Serial.print("out\n");  
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
   
  delay(2500);
}
