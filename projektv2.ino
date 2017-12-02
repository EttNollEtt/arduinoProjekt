const int trigOne = 7;
const int echoOne = 8;
const int trigTwo = 3;
const int echoTwo = 4;
const int irOne = 13;
const int irTwo = 12;
const int in1 = 6;
const int in2 = 5;
const int in3 = 10;
const int in4 = 11;

// abandon all hope, ye who enter

void systemFail()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(2000);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

int distanceRead(int x, int y)
{
  // tar in en trigpin och en echopin
  // och räknar ut avståndet från sensorn i mm
  int var;
  int distance;
  digitalWrite(x, LOW);
  delayMicroseconds(2);
  digitalWrite(x, HIGH);
  delayMicroseconds(8);
  digitalWrite(x, LOW);
  var = pulseIn(y, HIGH);
  distance = (var * 0.034 / 2);
  if (distance > 15)
  {
    motorControl(0);
  }
  return distance;
}

int sensorRead(int x, int y)
{
  // tar in två IRsensorer och returnerar
  // värden beroende på vad dem läser av
  if ((digitalRead(x) == 0) && (digitalRead(y) == 0))
  {
    return 0;
  }
  else if ((digitalRead(x) != 0) && (digitalRead(y) == 0))
  {
    return 1;
  }
  else if ((digitalRead(x) == 0) && (digitalRead(y) != 0))
  {
    return -1;
  }
  else if ((digitalRead(x) != 0) && (digitalRead(y) != 0))
  {
    systemFail();
  }
}

void motorControl(int x)
{
  // slutfunktionen som tar in 1, -1 eller 0
  // som hör ihop med sväng höger, vänster eller rakt fram
  //Serial.print(x);
  // om irTwo ej upptäcker körs denna om allt annat stämmer
  //Serial.print(x);
  if (x == 1)
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  // om irOne ej upptäcker körs denna om allt annat stämmer
  else if (x == -1)
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  // om båda IR upptäcker mark körs denna om allt annat stämmer
  else if (x == 0)
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
}

int deltaDistance(int x, int y)
{
  // kollar om avståndet till den ena sensorn är större än det andra avståndet
  // isåfall och skillnaden är större än 15cm så svänger den
  Serial.print(x);
  if (((x > y)) && ((x - y) > 5))
  {
    motorControl(1);
  }
  else if (((x < y)) && ((y - x) > 5))
  {
    motorControl(-1);
  }
  else
  {
    motorControl(0);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(trigOne, OUTPUT);
  pinMode(trigTwo, OUTPUT);
  pinMode(echoOne, INPUT);
  pinMode(echoTwo, INPUT);
  pinMode(irOne, INPUT);
  pinMode(irTwo, INPUT);
}

void loop() {
  delay(10);
  int distanceOne;
  int distanceTwo;
  int sensor;
  sensor = sensorRead(irOne, irTwo);
  if (sensor == 0)
  {
    distanceOne = distanceRead(trigOne, echoOne);
    distanceTwo = distanceRead(trigTwo, echoTwo);
    deltaDistance(distanceOne, distanceTwo);
  }
  else if (sensor == 1)
  {
    motorControl(1);
  }
  else
  {
    motorControl(-1);
  }
}

