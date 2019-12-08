
#define BLYNK_PRINT DebugSerial
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3); // RX, TX
#include <dht.h>
dht DHT;
#define DHT11_PIN 5
#include <BlynkSimpleStream.h>
#include <Servo.h>
Servo myservo;

char auth[] = "yaBid1MGEenT7aiOQpJQ-J-j6lOQ1mbx";
String input;
WidgetTerminal terminal(V3);
BLYNK_WRITE(V2){
float lati = param[0].asFloat();
float lot = param[1].asFloat();
terminal.print("Latitude is:");
terminal.println(lati);
float latidis;
latidis = lati-39.964862;
float dist;
float lotdis;
lotdis = lot-116.481625;

if(latidis<0)
{
  latidis = 0-latidis;
}
if(lotdis<0)
{
  lotdis = 0-lotdis;
}
dist = latidis + lotdis;
if(dist<0.02 && dist>0.0002){
  myservo.write(90);
  Blynk.virtualWrite(V10,"kindaclose");
}
else if(dist<0.0002){
  myservo.write(180);
  Blynk.virtualWrite(V10,"veryclose");
}

terminal.print("Longtitude is:");
terminal.println(lot);

}

void setup(){
pinMode(13,OUTPUT);
  DebugSerial.begin(9600);

  Serial.begin(9600);
  Blynk.begin(Serial, auth);

  myservo.attach(9);
}
 BLYNK_WRITE(V9)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
   if(pinValue==1){
    myservo.write(160);
    delay(500);
   }
    else {
     myservo.write(60);
    delay(500); 

   }

}
void loop()
{
  int chk = DHT.read11(DHT11_PIN);
  
  Blynk.run();
  
  Blynk.virtualWrite(V5, DHT.humidity);
  Blynk.virtualWrite(V6, DHT.temperature);
}
