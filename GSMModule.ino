#include <SoftwareSerial.h>
void sendMessage();

SoftwareSerial sim(9,10);
void setup() {
  sim.begin(19200);
  Serial.begin(9600);
  delay(100);
  // put your setup code here, to run once:

}

void loop() {
  if(Serial.available()>0)
  {
    switch(Serial.read())
    {
      case 's':
        sendMessage();
        Serial.println("Sending message");
        break;
      case 'r':
        receiveMessage();
        break;;
    }
    while(sim.available()>0)
    {
      Serial.write(sim.read());
    }
  }
  
  // put your main code here, to run repeatedly:

}
void sendMessage()
  {
    Serial.println("sending");
    sim.println("AT+CMGF=1");
    delay(1000);
    sim.println("AT+CMGS=\"+918280079489\"\r");
    delay(1000);
    sim.println("Hi I am Sweety");
    delay(1000);
    sim.println((char)26);
    delay(1000);
  }
  
  
