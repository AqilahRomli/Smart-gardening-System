int relaypin = D4;
void setup()
{     
  Serial.begin(115200);   
  pinMode(relaypin,OUTPUT);
 
}

void loop()
{
  digitalWrite(relaypin, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(6000);                     // wait for a second
  digitalWrite(relaypin, HIGH);    // turn the LED off by making the voltage LOW  
  delay(20000);

 }
