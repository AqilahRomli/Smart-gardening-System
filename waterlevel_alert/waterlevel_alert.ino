#define BLYNK_TEMPLATE_ID "TMPLGjXd4G4Y"
#define BLYNK_DEVICE_NAME "LCD LEVEL"
#define BLYNK_AUTH_TOKEN "d2j0DNSbQYamqvOPIj4T2ny97sssd1EW"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define pingPin D5   // Trig pin
#define echoPin D6 
int sensorpin=A0;
int sensorvalue=0;
int outputvalue=0;
int relaypin = D4;

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "zahnor1974 2.4G@unifi";
char pass[] = "zahahmed";
int depth =9;
long duration,cm, level;

WidgetLCD LCD(V1);
BlynkTimer timer;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Starting Serial Terminal
  pinMode(relaypin,OUTPUT);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  timer.setInterval(10L, sensor);

}

void loop() {
   Blynk.run();
   // You can inject your own code or combine it with other sketches.
   // Check other examples on how to communicate with Blynk. Remember
   // to avoid delay() function!
   timer.run();
}

void sensor(){
    // put your main code here, to run repeatedly:
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   cm = microsecondsToCentimeters(duration);
   level= depth-cm;
   Serial.print(cm);
   Serial.print("cm");
   Serial.println();
   level = map(level,0,depth-3,0,100);
   Blynk.virtualWrite(V0, level);

   sensorvalue=analogRead(sensorpin);
   outputvalue=map(sensorvalue,0,1023,0,100); //100,0 pottupaaru
   Blynk.virtualWrite(V2,outputvalue);

   if((level < 30) && (outputvalue>70)){
   LCD.clear();
   LCD.print(3,0, "Tank is Low");
   LCD.print(5,1, "soil dry");
   delay(5000);
   digitalWrite(relaypin, LOW);   // turn the LED on (HIGH is the voltage level)
   delay(4000);
   digitalWrite(relaypin, HIGH);
   LCD.clear();
   LCD.print(3,0, "refill tank");
   LCD.print(2,1, "watering plant");
   delay(5000);
  }
  else if((level < 30) && (outputvalue<70)){
   LCD.clear();
   LCD.print(3,0, "Tank is Low");
   LCD.print(3,1, "refill tank");
   delay(5000);
  }
  else if((level > 30) && (outputvalue>70)){
   LCD.clear();
   LCD.print(4,0, "soil dry");
   digitalWrite(relaypin, LOW);   // turn the LED on (HIGH is the voltage level)
   delay(4000);
   digitalWrite(relaypin, HIGH);
   LCD.print(1,1, "watering plant");
   delay(5000);
  }
  else{
   LCD.clear();
   LCD.print(3,0, "All is good");
   delay(5000);
  }
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
