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
const int tcpPort = 1042;

void setup()
{
  Serial.begin(115200);  
servo1.attach(14); //front left leg 1st
servo2.attach(12); //front left leg 2nd 
servo3.attach(13);//front left leg 3rd
servo4.attach(15);//front left leg shoulder

servo1.write(67);
servo2.write(59);
servo3.write(90);
servo4.write(100);
  
      
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

}
 
 
void loop()
{ 
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
  if (val){         
      //moving to ready to walk position
      //from 67,59,90,95 to 67,30,41,95
      //client.write(1);         
      if(val==1){
        client.write(1);
        for(i=59;i>=30;i--){
        servo1.write(67);
        servo2.write(i);
        servo3.write(2*i-28);
        servo4.write(100);
        delay(10);
            } 
         for(i=32;i<=41;i++){
        servo1.write(67);
        servo2.write(30);
        servo3.write(i);
        servo4.write(100);
        delay(10);
    }
        }

//move back from ready to go position to stand up position
if (val==2){
  client.write(2);
  for (i=41;i>=32;i--){
        servo1.write(67);
        servo2.write(30);
        servo3.write(i);
        servo4.write(100);
        delay(10);
    }

    for (i=30;i<=59;i++){
        servo1.write(67);
        servo2.write(i);
        servo3.write(2*i-28);
        servo4.write(100);
        delay(10);
      }
  }
  
  //Srep1: move forward
  //from 67,30,41,100 to 67,28,60,100
  //11*10
if (val==3){
  client.write(3);
  for (i=30;i>=24;i--){
        servo1.write(67);
        servo2.write(i);
        servo3.write(41);
        servo4.write(100);
        delay(10);
  }
   for (i=41;i<=56;i++){
        servo1.write(67);
        servo2.write(24);
        servo3.write(i);
        servo4.write(100);
        delay(10);
  }
     for (i=56;i<=60;i++){
        servo1.write(67);
        servo2.write(i-32);
        servo3.write(i);
        servo4.write(100);
        delay(10);
  }
  }

//Step2: move from front to back 
//from 67,28,60,100 to 67,44,43,100
//565ms
if (val==4){
  client.write(4);
  for (i=28;i<=44;i++){
        servo1.write(67);
        servo2.write(i);
        servo3.write(88-i);
        servo4.write(100);
        delay(30);
    }
        servo1.write(67);
        servo2.write(44);
        servo3.write(43);
        servo4.write(100);
        delay(30);

//Step3: rise leg, move from back to front
//from 67,44,43,100 to 67,28,60,100
//539
    for (i=43;i>=38;i--){
        servo1.write(67);
        servo2.write(44);
        servo3.write(i);
        servo4.write(100);
        delay(9);
      }
    for(i=44; i>=28; i--){
        servo1.write(67);
        servo2.write(i);
        servo3.write(38);
        servo4.write(100);
        delay(15);
      }       
    for(i=38; i<=60; i++){
        servo1.write(67);
        servo2.write(28);
        servo3.write(i);
        servo4.write(100);
        delay(10);
      }       

  }      

  }
         
          } 
      
        else{
        digitalWrite(LED_BUILTIN, HIGH);  
          }
        //client.println("tested");
        delay(10);
}
