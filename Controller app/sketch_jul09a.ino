int RedLight=11;
int BlueLight=10;
int GreenLight=9;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(2400);
  pinMode(RedLight, OUTPUT);
  pinMode(BlueLight, OUTPUT);
  pinMode(GreenLight, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    
  setColor(0, 255, 255);
  delay(350);
  setColor(255, 0, 255);
  delay(350);
  setColor(255, 255, 0);
  delay(350);
}

void setColor (unsigned char red, unsigned char green, unsigned char blue) 
{        
    analogWrite(RedLight, red);
    analogWrite(GreenLight, green);
    analogWrite(BlueLight, blue);
} 
