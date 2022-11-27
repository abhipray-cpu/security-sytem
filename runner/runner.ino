#include<Servo.h>
#include<ESP8266WiFi.h>
#include<FirebaseESP8266.h>

#define WIFI_SSID "Amber-Prajjwal"
#define WIFI_PASSWORD "chalajaabsdk"
#define FIREBASE_AUTH "J7zZWSjFYt1VW2h3Y6SgGz8JW7okCe1qrYYEnEe0"
#define FIREBASE_HOST "channel-relay-control-3a865-default-rtdb.asia-southeast1.firebasedatabase.app/"

const int play = 2;
const int record = 0;
FirebaseData firebaseData;
FirebaseJson json;
FirebaseData fbdo;

Servo myServo1;
Servo myServo2;

void setup() {
  // put your setup code here, to run once:

Serial.begin(115200);
pinMode(play,OUTPUT);
pinMode(record,OUTPUT);
digitalWrite(play,LOW);
digitalWrite(record,LOW);
Serial.println("Starting the securtiy system!");
myServo1.attach(13); //this is the axis1
myServo2.attach(15); //this is the axis2
myServo1.write(0);
myServo2.write(0); 
 WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
   Serial.println();
   Serial.print("Connected with IP: ");
   Serial.println(WiFi.localIP());
   Serial.println(); 
   Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  // put your main code here, to run repeatedly:
moveAxis1();
moveAxis2();
recordFn();
playFn();
repeatFn();
}

// these functions are used for reading data from real time database and then moving the servos as per the value
void moveAxis1()
{
    if (Firebase.getInt(firebaseData, "/security/axis1")){
    Serial.println(firebaseData.intData());
    myServo1.write(firebaseData.intData());
     } 
  }

void moveAxis2()
{
  if (Firebase.getInt(firebaseData, "/security/axis2")){
    Serial.println(firebaseData.intData());
    myServo2.write(firebaseData.intData());
     }
  }  
// these functions will control the sound module

void recordFn()
{
  if(Firebase.getInt(firebaseData,"/security/record") == 1)
  {
    digitalWrite(record,HIGH);
    delay(60);
    digitalWrite(record,LOW);
    Firebase.setInt(fbdo, F("/security/record"),0);
    }
  }

void playFn()
{
  if(Firebase.getInt(firebaseData,"/security/play") == 1)
  {
    digitalWrite(play,HIGH);
    delay(60);
    digitalWrite(play,LOW);
    Firebase.setInt(fbdo, F("/security/play"),0);
    }
  }
 void repeatFn()
 {
  if(Firebase.getInt(firebaseData, "/security/repeat") == 1)
  {
    for(int i=0;i<10;i++)
    {
      digitalWrite(play,HIGH);
      delay(60);
      digitalWrite(play,LOW);
      }
      Firebase.setInt(fbdo, F("/security/repeat"),0);
    }
  }
