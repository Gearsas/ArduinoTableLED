//-----------------------
int numColors=255;
int RedLight=11;
int BlueLight=10;
int GreenLight=9;
int animationDelay= 70;
int counter=0;
int trigPin=7;
int echoPin=6;
int pingTravelTime=0;
int OutofRangeTimer=0;
String data = "";
bool lights = true;
//-----------------------

void setup() {
  Serial.begin(4800);
  pinMode(RedLight, OUTPUT);
  pinMode(BlueLight, OUTPUT);
  pinMode(GreenLight, OUTPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
}

void loop() {
  digitalWrite(trigPin,HIGH);
  delay(animationDelay);
  digitalWrite(trigPin,LOW);
  pingTravelTime=pulseIn(echoPin,HIGH)/29;


 /*if person is away for too long turn off led
 /* if(OutofRangeTimer < 150)
  {
    lights= true;
  }
  else
  {
    lights= false;
  }*/
  if(lights == true)
  {
    float colorNumber = counter > numColors ? counter - numColors: counter;

    float saturation = .9; // Between 0 and 1 (0 = gray, 1 = full color)
    float brightness = .2; // Between 0 and 1 (0 = dark, 1 is full brightness)
    float hue = (colorNumber / float(numColors)) * 360; // Number between 0 and 360
    long color = HSBtoRGB(hue, saturation, brightness); 
  
    int red = color >> 16 & 255;
    int green = color >> 8 & 255;
    int blue = color & 255;

  setColor(red, green, blue);
  
  counter = (counter + 1) % (numColors * 2);
  }
  if(pingTravelTime/2 < 1100)
  {
    OutofRangeTimer=0;
  }
  else if (pingTravelTime/2 >1100)
          OutofRangeTimer++;
          
  if(lights == false)
          setColor(0, 0, 0);
  //Serial.println(OutofRangeTimer);
 // Serial.println(timer);

  if(Serial.available()!=0){
    data="";
    data = Serial.readString();
    Serialinput(data,millis());
  }
}


//--------------input from pc-------------------
void Serialinput(String data, double uptime){

  if(data == "Status"){
     Serial.print("Arduino uptime: ");
     Serial.println(uptime);
  }
  else{
    Serial.println("Unrecognised command");
  }
}





//-------------Color thingys----------------------


void setColor (unsigned char red, unsigned char green, unsigned char blue) 
{        
    analogWrite(RedLight, red);
    analogWrite(GreenLight, green);
    analogWrite(BlueLight, blue);
} 

long HSBtoRGB(float _hue, float _sat, float _brightness) {
    float red = 0.0;
    float green = 0.0;
    float blue = 0.0;
    
    if (_sat == 0.0) {
        red = _brightness;
        green = _brightness;
        blue = _brightness;
    } else {
        if (_hue == 360.0)
            _hue = 0;

        int slice = _hue / 60.0;
        float hue_frac = (_hue / 60.0) - slice;

        float aa = _brightness * (1.0 - _sat);
        float bb = _brightness * (1.0 - _sat * hue_frac);
        float cc = _brightness * (1.0 - _sat * (1.0 - hue_frac));
        
        switch(slice) {
            case 0:
                red = _brightness;
                green = cc;
                blue = aa;
                break;
            case 1:
                red = bb;
                green = _brightness;
                blue = aa;
                break;
            case 2:
                red = aa;
                green = _brightness;
                blue = cc;
                break;
            case 3:
                red = aa;
                green = bb;
                blue = _brightness;
                break;
            case 4:
                red = cc;
                green = aa;
                blue = _brightness;
                break;
            case 5:
                red = _brightness;
                green = aa;
                blue = bb;
                break;
            default:
                red = 0.0;
                green = 0.0;
                blue = 0.0;
                break;
        }
    }

    long ired = red * 255.0;
    long igreen = green * 255.0;
    long iblue = blue * 255.0;
    
    return long((ired << 16) | (igreen << 8) | (iblue));
}
