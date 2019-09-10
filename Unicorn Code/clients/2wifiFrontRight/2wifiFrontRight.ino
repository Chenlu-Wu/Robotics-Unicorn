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
const int tcpPort = 4029;
void setup()
{
 Serial.begin(115200);
  
servo1.attach(14); //back left leg 1st
servo2.attach(12); //back left leg 2nd 
servo3.attach(13);//back left leg 3rd
servo4.attach(15);//back left leg shoulder

servo1.write(128);
servo2.write(121);
servo3.write(90);
servo4.write(75);       
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
    //client.write(1);
      //moving to ready to walk position
      //from 124,121,90,85 to 124,150,139,85
      if(val==1){
        client.write(1);
        for(i=121;i<=150;i++){
        servo1.write(128);
        servo2.write(i);
        servo3.write(2*i-152);
        servo4.write(75);
        delay(10);
            } 
        //
         for(i=148;i>=139;i--){
        servo1.write(128);
        servo2.write(150);
        servo3.write(i);
        servo4.write(75);
        delay(10);
    }
        }

// stand up position
if (val==2){
  client.write(2);
  for (i=139;i<=148;i++){
        servo1.write(128);
        servo2.write(150);
        servo3.write(i);
        servo4.write(75);
        delay(10);
    }

    for (i=150;i>=121;i--){
        servo1.write(128);
        servo2.write(i);
        servo3.write(2*i-152);
        servo4.write(75);
        delay(10);
      }
  }

//Step1:friction, move back from middile
//from 128,150,139,75 to 128,136,137,75
  //16*20
if (val==3){
  client.write(3);
  for (i=150;i>=138;i--){
        servo1.write(128);
        servo2.write(i);
        servo3.write(139);
        servo4.write(75);
        delay(20);
    }
      for (i=138;i>=136;i--){
        servo1.write(128);
        servo2.write(i);
        servo3.write(i+1);
        servo4.write(75);
        delay(20);
    }
  }


//Step2: rise leg, move from back to front
//from 128,136,137,75 to 128,152,120,75
//54+255+230=539ms
if (val==4){
  client.write(4);
  for (i=137;i<=142;i++){
        servo1.write(128);
        servo2.write(139);
        servo3.write(i);
        servo4.write(75);
        delay(9);
    }
  for (i=136;i<=152;i++){
        servo1.write(128);
        servo2.write(i);
        servo3.write(142);
        servo4.write(75);
        delay(15);
  }
    for (i=142;i>=120;i--){
        servo1.write(128);
        servo2.write(152);
        servo3.write(i);
        servo4.write(75);
        delay(10);
    }    

//Step3: friction, move from front to back
//from 128,152,120,75 to 128,136,137,75
//18*30=540ms
    for (i=152;i>=136;i--){
        servo1.write(128);
        servo2.write(i);
        servo3.write(272-i);
        servo4.write(75);
        delay(30);
      }
        servo1.write(128);
        servo2.write(139);
        servo3.write(137);
        servo4.write(75);
        delay(30);

  }
        

         } 
        //client.write(2);    
        }
        else{
        digitalWrite(LED_BUILTIN, HIGH);  
          }
        //client.println("tested");
        delay(10);
}
