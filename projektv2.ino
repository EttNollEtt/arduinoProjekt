const int trigOne = 7;
const int echoOne = 8;
const int trigTwo = 3;
const int echoTwo = 4;
const int irOne = 13;
const int irTwo = 12;
int distanceOne = "";
int distanceTwo = "";
int sensor = "";

// irOne tillhör pins 5, 6
// irTwo tillhör 10, 11
// ultraljud två tillhör pins 5, 6
// ultra ett tillhör 10, 11

void setup() {
  Serial.begin(9600);
  pinMode(trigOne, OUTPUT);
  pinMode(trigTwo, OUTPUT);
  pinMode(echoOne, INPUT);
  pinMode(echoTwo, INPUT);
  pinMode(irOne, INPUT);
  pinMode(irTwo, INPUT);
}

void loop() {
  //Serial.print(digitalRead(irOne));
  delay(50);
  sensor = sensorRead(irOne, irTwo);
  if (sensor == 0) {
    distanceOne = distanceRead(trigOne, echoOne);
    distanceTwo = distanceRead(trigTwo, echoTwo);
    deltaDistance(distanceOne, distanceTwo);     
  }
  else if (sensor == 1) {
    motorControl(1);
  }
  else {
    motorControl(-1);
  }
}

int distanceRead(int x, int y) {
  // tar in en trigpin och en echopin
  // och räknar ut avståndet från sensorn i cm
  int var = "";
  int distance = "";
  digitalWrite(x, LOW);
  delayMicroseconds(2);
  digitalWrite(x, HIGH);
  delayMicroseconds(8);  
  digitalWrite(x, LOW);
  var = pulseIn(y, HIGH);
  distance = (var*0.034/2);
  return distance;
}

int sensorRead(int x, int y) {
  // tar in två IRsensorer och returnerar
  // värden beroende på vad dem läser av
  if ((digitalRead(x) == 0) && (digitalRead(y) == 0)) {
    return 0;
  }
  else if (digitalRead(x) != 0){
    return 1;
  }
  else {
    return -1;
  }
}

int deltaDistance(int x, int y) {
  // tar in två avstånd och räknar ut kvadraten
  // testar om x eller y är störst och om absolutvärdet
  // är större än ett visst värde så tillkallar den 
  // motorfunktionen för att svänga, annars rakt fram
  int variab = "";
  variab = ((x-y)*(x-y));
  if (((x - y) < 0) && (sqrt(variab) > 10)) {
    motorControl(1);
  }
  else if (((x - y) > 0) && (sqrt(variab) > 10)) {
    motorControl(-1);
  }
  else {
    motorControl(0);
  }
}

void motorControl(int x) {
  // slutfunktionen som tar in 1, -1 eller 0
  // som hör ihop med sväng höger, vänster eller rakt fram
  Serial.print(x);
  // om irTwo ej upptäcker körs denna om allt annat stämmer
  if (x == 1) {
    analogWrite(5, 0);
    analogWrite(10, 255);
    analogWrite(11, 0);
  }
  // om irOne ej upptäcker körs denna om allt annat stämmer
  else if (x == -1) {
    analogWrite(10, 0);
    analogWrite(5, 255);
    analogWrite(6, 0);
  }
  // om båda IR upptäcker mark körs denna om allt annat stämmer
  else {
    analogWrite(10, 255);
    analogWrite(11, 0);
    analogWrite(5, 255);
    analogWrite(6, 0);
  }
}
