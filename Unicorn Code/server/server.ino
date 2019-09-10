/*
 * Copyright (c) 2018, circuits4you.com
 * All rights reserved.
 * Create a TCP Server on ESP8266 NodeMCU. 
 * TCP Socket Server Send Receive Demo
*/
#include <ESP8266WiFi.h>
//#define SendKey 0  //Button to send data Flash BTN on NodeMCU
int port1 = 1042;  //Port number
int port2 = 4029;  //Port number
int port3 = 8888;
int port4 = 1109;

WiFiServer server0(8088);
WiFiServer server1(port1);
WiFiServer server2(port2);
WiFiServer server3(port3);
WiFiServer server4(port4);

//Server connect to WiFi Network
const char *ssid = "Chenlu";  //Enter your wifi SSID
const char *password = "110919yw";  //Enter your wifi Password

int count=0;
int clienti=1;
int re=0;
void setup() 
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  //pinMode(SendKey,INPUT_PULLUP);  //Btn to send data
 // Serial.println();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); //Connect to wifi
 
  // Wait for connection  
  Serial.println("Connecting to Wifi");
  while (WiFi.status() != WL_CONNECTED) {   
    delay(500);
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server1.begin();  
  server2.begin();
  server3.begin();  
  server4.begin();
}

void sendtoclient(int num,int cln){
  WiFiClient client = server0.available();
  if (cln==1){
    client = server1.available(); 
  }
  else if(cln==2  ){
    client = server2.available(); 
  }
  else if(cln==3  ){
  client = server3.available(); 
}
  else if(cln==4  ){
  client = server4.available(); 
}
      
    if(client.connected())
    {
      Serial.print("Client");
      Serial.println(cln);
    } 
    client.write(num);
    while(client.connected()){      
      while(client.available()>0){

        // read data from the connected client
       //Serial.write(client.read());
       re= client.read();
       Serial.print("re=");
        Serial.println(re);
      }
      
      //Send Data to connected client
     // while(Serial.available()>0)
    // {
        //client.write(5);
    // }
    if (re==num){
      re=0;
      break;}
    }   
    client.stop();  
  }

void loop() 
{
  digitalWrite(LED_BUILTIN, LOW);


 if (Serial.available()>0){
  count=Serial.parseInt();
  if(count != 0){
    Serial.println(count);
    if (clienti==1){
    sendtoclient(count,1);
    delay(20);  
    sendtoclient(count,2);
    delay(15);
    sendtoclient(count,3);  
    delay(10);
    sendtoclient(count,4); 
    delay(10); 
    count=0;
    
    }
    delay(10); 

  
  }    
}
}
