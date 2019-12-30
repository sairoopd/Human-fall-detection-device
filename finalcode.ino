/*
 * CONNECT TO OUTGOING PORT HC-05 'DEV-B' TO VIEW DATA ON SERIAL MONITOR
 * USE THIS SKETCH ONLY FOR VIEWING SENSOR DATA ON SERIAL MONITOR.....NOT FOR FILE WRITING
 */
#include "MPU9250.h"
#include "time.h"
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#define buzzer D5
#define GPIO_PIN 13

const char* ssid ="Ashish";
const char* password = "Ashish05";
const char* host = "maker.ifttt.com";
const int httpsPort = 443;
int fls =0;
String url = "/trigger/Fall_Detected/with/key/2_s-AMGImqNscQrLs3Ksd";
WiFiClientSecure client;

MPU9250 IMU(Wire,0x68);
int status;
int switchstat;


void setup()
{
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(GPIO_PIN, INPUT_PULLUP); 
  
  //*****************WiFi setup*******************************//
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  //IMU setup*************************************************************//
  while(!Serial){}
  
  // start communication with IMU 
  status = IMU.begin();
  

  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }
  status = IMU.calibrateAccel();
   Serial.print("calib Status: ");
    Serial.println(status);
    
    attachInterrupt(GPIO_PIN, pin_ISR, CHANGE);
}

void loop()
{
  float acc = 0, acc1 = 0;
  float gyro = 0, gyro1 = 0;
  unsigned long x, y;
  int fall =0;
  fls = 0;
  Serial.flush();
  
  IMU.readSensor();
  // display the data
  // read the sensor

  acc = sqrt(sq(IMU.getAccelX_mss())+sq(IMU.getAccelY_mss())+sq(IMU.getAccelZ_mss()));
  gyro = sqrt(sq(IMU.getGyroX_rads())+sq(IMU.getGyroY_rads())+sq(IMU.getGyroZ_rads()));
  //Serial.print("aceel:");
  Serial.print(acc,3);
  Serial.print(" ");
  Serial.println(gyro,3);
  
  if(acc < 2.8){
x = millis();
      do{
        IMU.readSensor();
        //Serial.println("im here");
        acc1 = sqrt(sq(IMU.getAccelX_mss())+sq(IMU.getAccelY_mss())+sq(IMU.getAccelZ_mss()));
      gyro1 = sqrt(sq(IMU.getGyroX_rads())+sq(IMU.getGyroY_rads())+sq(IMU.getGyroZ_rads()));
     // Serial.print("acc1");
      Serial.print(acc1,3);
      Serial.print(" ");
     // Serial.print("gyro1");
      Serial.println(gyro1,3);
        if(acc1 > 23 && gyro1 >6){
        //Serial.println("fall detected");
        fall = 1;
        break;
        }
    }while((millis()-x)<500);
    }
  if (fall){
    digitalWrite(buzzer, HIGH);
    delay(9000);  
    //Serial.print("fls=");
    //Serial.println(fls); 
  if (!fls){
//      Serial.print("requesting URL: ");
//  Serial.println(url);
//  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
//               "Host: " + host + "\r\n" +
//               "User-Agent: BuildFailureDetectorESP8266\r\n" +
//               "Connection: close\r\n\r\n");
//  Serial.println("request sent");
//  while (client.connected()) {
//    String line = client.readStringUntil('\n');
//    if (line == "\r") {
//      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
//  Serial.println("reply was:");
//  Serial.println("==========");
//  Serial.println(line);
//  Serial.println("==========");
//  Serial.println("closing connection");
    }
    digitalWrite(buzzer, LOW);
  }
  delay(200);
}


void pin_ISR(){
//switchstat = digitalRead(sw);
  digitalWrite(buzzer, LOW);
  Serial.println(GPIO_PIN);
  Serial.println("false alarm");
  fls = 1;
}
