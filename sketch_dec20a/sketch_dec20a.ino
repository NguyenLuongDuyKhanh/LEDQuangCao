const int A_pin = 11;
const int B_pin = 10;
const int C_pin =9;
int pinMatrix [8][3] = {
  {0,0,0},
  {1,0,0},
  {0,1,0},
  {1,1,0},
  {0,0,1},
  {1,0,1},
  {0,1,1},
  {1,1,1}
};
void setup() {
  // put your setup code here, to run once:
  pinMode(A_pin, OUTPUT);
  pinMode(B_pin, OUTPUT);
  pinMode(C_pin, OUTPUT);

  digitalWrite(A_pin, HIGH);
  digitalWrite(B_pin, HIGH);
  digitalWrite(C_pin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0; i<8;i++)
  {
    digitalWrite(A_pin, pinMatrix[i][0]);
    digitalWrite(B_pin, pinMatrix[i][1]);
    digitalWrite(C_pin, pinMatrix[i][2]);
    delay(1000);
  }
}
