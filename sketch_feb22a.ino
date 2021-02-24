/* Pins to microcontroller */

int trigger[2] = {10,8};
int echo[2] = {11,9};

/* For data manupulation */

float temperature = (17) + 273.15; // Celcius + 273.15

float speedOfSound;

float initialDistance[2];
float distance[2];

String sequence = "";
int sequenceNumber;
unsigned visitorCount = 0;

int i; // gloabal loop variable

void setup() {

  Serial.begin(9600);
  delay(200);

  speedOfSound = 20.05 * sqrt(temperature) / 10000; // centimeters per microseconds
  
  for(i = 0; i < 2; i++) {
    pinMode(trigger[i],OUTPUT);
    pinMode(echo[i],INPUT);
    initialDistance[i] = measureDistance(i);
  }

  Serial.print("System has been initialized\n");
}

void loop() {

  for(i = 0; i < 2; i++) {
    distance[i] = measureDistance(i);
    Serial.print("distance[");Serial.print(i);Serial.print("] = ");Serial.print(distance[i]);Serial.print(" cm ");
  }  

  visitorCount = countPeople(visitorCount);

  Serial.print("\nvisitors = "); Serial.print(visitorCount); Serial.print("\n");
        
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

unsigned countPeople(unsigned visitorCount) {

  if (distance[0] < distance[1]) {
    if (distance[0] < (0.80 * initialDistance[0]) && sequence.charAt(0) != '1') 
      sequence += '1';
    if (distance[1] < (0.80 * initialDistance[1]) && sequence.charAt(0) != '2') 
      sequence += '2';
  }
    
  else if (distance[1] > distance[0]) {
    
    if (distance[1] < (0.80 * initialDistance[1]) && sequence.charAt(0) != '2') 
      sequence += '2';  
    if (distance[0] < (0.80 * initialDistance[0]) && sequence.charAt(0) != '1') 
      sequence += '1';
  }
    
  sequenceNumber = sequence.toInt();
  
  Serial.print(sequence); Serial.print("\n");

  switch (sequenceNumber){

    default: {
      sequence = ""; 
      break;
    } 
      
    case 12: {
      visitorCount++;
      sequence = "";
      break;
    }

    case 21:{
      visitorCount--;
      sequence = "";
      break;
    }
    
  }
  
  return visitorCount;
  
}
