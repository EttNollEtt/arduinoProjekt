#define trigOne 7
#define echoOne 8
#define trigTwo 3
#define echoTwo 4
#define irOne 13
#define irTwo 12
#define in1 6
#define in2 5
#define in3 10
#define in4 11

// abandon all hope, ye who enter

void systemFail()
// ifall båda ir-sensorerna upptäcker färg
// backar den i 1(en) sekund och stannar sedan
// sedan börjar loopen om
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(1000);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

long distanceRead(int x, int y)
// tar in en trigpin och en echopin
// och räknar ut avståndet från sensorn i cm
{
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

int colorRead(int x)
// tar in värden från en ir-sensor och
// jämför det med värdet efter en kort delay
// den kommer att reagera om skillnaden är för stor 
{
  int val;
  int ny;
  val = analogRead(x);
  delay(5);
  ny = analogRead(x);
  if ((val - ny) > 50) // DEN SJUNDE DAGEN VILADE HAN: DEN SJÄTTE DAGEN SADE HAN; VAR E LJUSET FÖR FAN? OCH LJUSET KOM I SPRUTLUDRET
  {
    return true;
  }
  else
  {
    return false;
  }
}

void motorControl(int x)
// slutfunktionen som tar in 1, -1 eller 0
// som hör ihop med sväng höger, vänster eller rakt fram
// om irTwo ej upptäcker körs denna om allt annat stämmer
{
  if (x == 1)
  {
    analogWrite(in1, 255);
    analogWrite(in2, 0);
    analogWrite(in3, 0);
    analogWrite(in4, 255);
  }
  // om irOne ej upptäcker körs denna om allt annat stämmer
  else if (x == -1)
  {
    analogWrite(in1, 0);
    analogWrite(in2, 255);
    analogWrite(in3, 255);
    analogWrite(in4, 0);
  }
  // om båda IR upptäcker mark körs denna om allt annat stämmer
  else if (x == 0)
  {
    analogWrite(in1, 255);
    analogWrite(in2, 0);
    analogWrite(in3, 255);
    analogWrite(in4, 0);
  }
}

int deltaDistance(int x, int y)
// kollar om avståndet till den ena sensorn är större än det andra avståndet
// isåfall och skillnaden är större än 15cm så svänger den
{
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

void setup()
{
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

void loop()
// kollar med ir-sensorerna först av allt
// beroende på vad de känner av så kommer
// en viss funktion med motorerna utföras
{
  delay(10);
  int distanceOne;
  int distanceTwo;
  if (colorRead(irOne) == true && colorRead(irTwo) == true)
  {
    systemFail();
  }
  else if ((colorRead(irOne) &&! colorRead(irTwo) == true))
  {
    motorControl(1);
  }
  else if ((colorRead(irTwo) &&! colorRead(irOne) == true))
  {
    motorControl(-1);
  }
  else
  {
    distanceOne = distanceRead(trigOne, echoOne);
    distanceTwo = distanceRead(trigTwo, echoTwo);
    deltaDistance(distanceOne, distanceTwo);
  }
}
