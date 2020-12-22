int DS_pin = 8;
int STCP = 9;
int SHCP = 10;

void setup()
{
  pinMode(DS_pin,OUTPUT);
  pinMode(STCP,OUTPUT);
  pinMode(SHCP,OUTPUT);
  writereg();
}
boolean registers[8]={HIGH,LOW,HIGH,LOW,HIGH,LOW,HIGH,LOW};

void writereg()
{
  digitalWrite(SHCP,LOW);
  for (int i = 7; i>=0;i--)
  {
    digitalWrite(STCP,LOW);
    digitalWrite(DS_pin,registers[i]);
    digitalWrite(STCP,HIGH);
  }
  digitalWrite(SHCP,HIGH);
}
void loop()
{
  for(int i =0; i<9;i++)
  {
    //registers[i]=HIGH;
    delay(100);
    writereg();
  }
  delay(5000);
  for(int i = 8; i>0;i++)
  {
    //registers[i]=LOW;
    delay(100);
    writereg();
  }
}
