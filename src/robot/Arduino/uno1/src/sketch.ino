#define S0 0

void s0f(){
  Serial.println("a");
}

void setup()
{
  pinMode(INPUT,3);
  pinMode(OUTPUT,4);
  pinMode(OUTPUT,5);
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  Serial.begin(9600);
}

void loop()
{
  Serial.println(digitalRead(2));
}
