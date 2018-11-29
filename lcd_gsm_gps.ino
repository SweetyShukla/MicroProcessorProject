#include<LiquidCrystal.h>
#include<SoftwareSerial.h>
#include<TinyGPS.h>
//gps- mt3299, gsm- sim900a

const int AOUTpin=0;
const int DOUTpin=7;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
SoftwareSerial sim(9,10);
TinyGPS gps;

int value; 
int c=1;
float x,y;

void setup() {
  // code to run once:
  Serial.begin(19200);
  sim.begin(19200);
  pinMode(AOUTpin,INPUT);
  pinMode(DOUTpin,INPUT);
  lcd.begin(16,2);
  lcd.print("Speed");
  delay(100);
  
}

void sendMessage()
  {
    float flat,flon;
    unsigned long age;
    gps.f_get_position(&flat,&flon,&age);
    Serial.println("sending");
    sim.println("AT+CMGF=1");
    delay(1000);
    sim.println("AT+CMGS=\"+918280079489\"\r");
    delay(1000);
    sim.print("Name: Ajay, Veh No- OD56LX at ");
    sim.print("http://maps.google.com/maps?q=loc:");
    sim.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print(",");
    sim.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    delay(1000);
    sim.println((char)26);
    delay(1000);
}




void detected()
{
  Serial.println("Above the value");
  lcd.print(" Drunk");
  
}

void loop() {
  // code to run repeatedly:
  value=analogRead(AOUTpin);
  x=((value*0.21)/1023);
  y=gps.f_speed_kmph();
  lcd.setCursor(5,0);
  lcd.print(y);
  Serial.println("Alcohol Level");
  Serial.println(value);
  Serial.println(x);
  lcd.setCursor(0,1);
  lcd.print(x);
  lcd.print("mg/L");
  delay(5000);
  if(c!=0)
  {
  if(x>0.09)
  {
    c=0;
    sendMessage();
    Serial.println("Above the value");
    lcd.print(" Drunk");
    delay(5000);
  }
  else
  {
    Serial.println("Sober");
    lcd.print(" Sober");
  }
  }
}
