int LDRInput=A0; //Set Analog Input A0 for LDR.
int LED=2;
void setup() {
Serial.begin(9600);
pinMode(LDRInput,INPUT);
pinMode(LED,OUTPUT);
}

void loop() {
int value=analogRead(LDRInput);//Reads the Value of LDR(light).
Serial.println("LDR value is :");//Prints the value of LDR to Serial Monitor.
Serial.println(value);
if(value<300)
  {
    digitalWrite(LED,HIGH);//The LED turns ON in Dark.
  }
  else
  {
    digitalWrite(LED,LOW);//The LED turns OFF in Light.
  }
}