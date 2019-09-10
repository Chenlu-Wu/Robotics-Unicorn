#include "ESP8266WiFi.h" 
#include <WiFiClient.h>
#include <Servo.h>

Servo servo1;      //initialize a servo object for the connected servo                
Servo servo2;
Servo servo3;
Servo servo4;

int i=0;  
const char* ssid = "Chenlu";
const char* password =  "110919yw";
const char *host = "172.20.10.10";
WiFiClient client;
const int tcpPort = 1109;

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200); 
servo1.attach(14); //back right leg 1st
servo2.attach(12); //back right leg 2nd 
servo3.attach(13);//back right leg 3rd
servo4.attach(15);//back right leg shoulder

servo1.write(113);
servo2.write(143);
servo3.write(108);
servo4.write(95);

    pinMode(LED_BUILTIN, OUTPUT);
    delay(10);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid); 
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

//delay(5000);
}

void loop() {
 while (!client.connected())
    {
        if (!client.connect(host, tcpPort))
        {
            Serial.println("No Server Found");
            digitalWrite(LED_BUILTIN, HIGH);
        }
    }   
        //Serial.println("online");     
        //String val = client.readStringUntil('\n');
        if(client.available() ){
        digitalWrite(LED_BUILTIN, LOW);
        int val = client.read();
        Serial.println(val);
    if (val) {
      //moving to ready to walk position
      //from 113,143,108,100 to 119,154,113,100
      if(val==1){
        client.write(1);
        for(i=108;i<=113;i++){
        servo1.write(5+i);
        servo2.write(2*i-73);
        servo3.write(i);
        servo4.write(95);
        delay(20);
            } 
        //
        servo1.write(119);
        servo2.write(154);
        servo3.write(113);
        servo4.write(95);
        delay(20);
        }

// stand up position
if (val==2){
        client.write(2);
        servo1.write(118);
        servo2.write(153);
        servo3.write(113);
        servo4.write(95);
        delay(20);

        for(i=113;i>=108;i--){
        servo1.write(5+i);
        servo2.write(2*i-73);
        servo3.write(i);
        servo4.write(95);
        delay(20);
            } 
  }

//Step1: friction, move  back left leg back
//from 119,154,113,100 to 109,148,110,100 
//25*4+30*7=309
if (val==3){
  client.write(3);
delay(320);
  for(i=113;i>=110;i--){
    servo1.write(6+i);
    servo2.write(i+41);
    servo3.write(i);
    servo4.write(100);
    delay(24);
    }
      for(i=151;i>=148;i--){
    servo1.write(i-35);
    servo2.write(i);
    servo3.write(110);
    servo4.write(100);
    delay(24);
    }
      for(i=113;i>=109;i--){
    servo1.write(i);
    servo2.write(148);
    servo3.write(110);
    servo4.write(100);
    delay(24);
    }
  }

  
//Step2: rise leg, move from back to front
//from 109,148,110,100  to 127,154,115,100
if (val==4){
  client.write(4);
  delay(270);
  for (i=109;i<=120;i++){
        servo1.write(i);
        servo2.write(i+40);
        servo3.write(i+1);
        servo4.write(100);
        delay(27);
    }

    for (i=121;i<=126;i++){
        servo1.write(i);
        servo2.write(281-i);
        servo3.write(242-i);
        servo4.write(100);
        delay(27);
      }
        servo1.write(127);
        servo2.write(154);
        servo3.write(115);
        servo4.write(100);


//Step3: friction, move from front to back
//from 127,154,115,100 to 109,148,110,100
  for (i=127;i>=122;i--){
        servo1.write(i);
        servo2.write(i+27);
        servo3.write(i-12);
        servo4.write(100);
        delay(27);
    }

    for (i=122;i>=109;i--){
        servo1.write(i);
        servo2.write(148);
        servo3.write(110);
        servo4.write(100);
        delay(27);
      }
  }

    // a=0;
  }
    }
  else{
        digitalWrite(LED_BUILTIN, HIGH);  
          }
        //client.println("tested");
        delay(10);

}

    
    
