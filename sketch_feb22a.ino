/* Pins to microcontroller */

int trigger[2] = {10,8};
int echo[2] = {11,9};

/* init 1 */

float temperature = (17) + 273.15; // Celcius + 273.15

float speedOfSound;

float initialDistance[2];
float distance[2][2];

unsigned visitorCount;

int i; // gloabal loop variable

void setup() {

  Serial.begin(9600);
  delay(200);

  speedOfSound = 20.05 * sqrt(temperature) / 10000; // centimeters per microseconds

  for (i = 0 ; i < 2; i++) {
    pinMode(trigger[i],OUTPUT);
    pinMode(echo[i],INPUT);
    initialDistance[i] = measureDistance(i);
  }
  
  visitorCount = 0; 
  
  Serial.print("System init complete\n");
}

void loop() {

  if (obstacleDetected()) {
    if (isEntering())
      visitorCount++;
    else if (isExiting())   
      visitorCount--;      
  }
      
  Serial.print("visitors = "); Serial.print(visitorCount); Serial.print("\n");    
}

float measureDistance(int i) {
  
    digitalWrite(trigger[i],LOW);
    delayMicroseconds(2);
    digitalWrite(trigger[i],HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger[i],LOW);

  return (pulseIn(echo[i],HIGH)/2*speedOfSound);
}

bool obstacleDetected() {
  for (i = 0 ; i < 2; i++) {
    distance[0][i] = measureDistance(i);
    delay(200);
    distance[1][i] = measureDistance(i);
  }
  return (distance[0][0]< 0.77*initialDistance[0] || distance[0][1] < 0.77*initialDistance[1]);
}


bool isEntering(){
  return  (distance[0][0] > distance[1][0]);
}

bool isExiting(){
  return  (distance[0][1] > distance[1][1]);
}
  
