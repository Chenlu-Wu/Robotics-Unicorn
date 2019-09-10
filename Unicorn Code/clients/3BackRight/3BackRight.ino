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
const int tcpPort = 8888;

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);  
servo1.attach(14); //back right leg 1st
servo2.attach(12); //back right leg 2nd 
servo3.attach(13);//back right leg 3rd
servo4.attach(15);//back right leg shoulder

servo1.write(66);
servo2.write(22);
servo3.write(64);
servo4.write(70);

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
      //from 66,22,64,75 to 60,11,59,75
      if(val==1){
        client.write(1);
        for(i=64;i>=59;i--){
        servo1.write(2+i);
        servo2.write(2*i-106);
        servo3.write(i);
        servo4.write(70);
        delay(20);
            } 
        //
        servo1.write(60);
        servo2.write(11);
        servo3.write(59);
        servo4.write(70);
        delay(20);
        }

// stand up position
if (val==2){
        client.write(2);
        servo1.write(61);
        servo2.write(12);
        servo3.write(59);
        servo4.write(70);
        delay(20);

    for (i=59;i<=64;i++){
        servo1.write(2+i);
        servo2.write(2*i-106);
        servo3.write(i);
        servo4.write(70);
        delay(20);
      }
  }


//Step1: move forward
//from 60,11,59,75 to 52,11,57,75
//9*30+3*20+15 
if (val==3){
  client.write(3);
  delay(320);
  for (i=60;i>=52;i--){
        servo1.write(i);
        servo2.write(11);
        servo3.write(59);
        servo4.write(75);
        delay(30);     
      }  
  for (i=59;i>=57;i--){
        servo1.write(52);
        servo2.write(11);
        servo3.write(i);
        servo4.write(75);
        delay(20);
    }
        servo1.write(52);
        servo2.write(11);
        servo3.write(57);
        servo4.write(75);
        delay(15);
  }
//Step2: friction, move from front to back
//from  52,11,57,75 to 70,17,62,75 
if (val==4){
  client.write(4);
  delay(270);
  for (i=52;i<=57;i++){
        servo1.write(i);
        servo2.write(i-41);
        servo3.write(i+5);
        servo4.write(75);
        delay(27);
    }

    for (i=57;i<=70;i++){
        servo1.write(i);
        servo2.write(17);
        servo3.write(62);
        servo4.write(75);
        delay(27);
      }

//Step3: rise leg, move from back to front
//from 70,17,62,75 to 52,11,57,75
  for (i=70;i>=59;i--){
        servo1.write(i);
        servo2.write(i-54);
        servo3.write(i-8);
        servo4.write(75);
        delay(27);
    }

    for (i=58;i>=53;i--){
        servo1.write(i);
        servo2.write(65-i);
        servo3.write(110-i);
        servo4.write(75);
        delay(27);
      }
        servo1.write(52);
        servo2.write(11);
        servo3.write(57);
        servo4.write(75);
  }
    }
    // a=0;
  }
      else{
        digitalWrite(LED_BUILTIN, HIGH);  
          }
        //client.println("tested");
        delay(10);
  
  }

    
    
