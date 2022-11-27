// this sketch is for running the arudino sound record and play button
/*
A major feature of the ISD1820 Voice Recorder Module is that is can store the messages in its non-volatile memory and can be
configured to store messages of length between 8 Seconds to 20 Seconds.
The ISD1820 Voice Recorder Module used in this project is shown below.
As you can see, there are a lot of components on the board that help the ISD1820 IC in recording and playback.
*/

// we can control the board actions manually using buttons or we can use some microcontroller to control the module
#include<FirebaseESP8266.h>
#include<ESP8266WiFi.h>
#define WIFI_SSID "Amber-Prajjwal"
#define WIFI_PASSWORD "chalajaabsdk"
#define FIREBASE_AUTH "J7zZWSjFYt1VW2h3Y6SgGz8JW7okCe1qrYYEnEe0"
#define FIREBASE_HOST "channel-relay-control-3a865-default-rtdb.asia-southeast1.firebasedatabase.app/"
FirebaseData firebaseData;
FirebaseJson json;
int rec=14;
int play=12;

void setup() 
{
  Serial.begin(115200);
  Serial.println("Starting the system");
  digitalWrite(play,LOW);
  digitalWrite(rec,LOW);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
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

void loop() 
{
  if (Firebase.getInt(firebaseData, "/security/play") == 1)
  {
     play_();
    }
   if (Firebase.getInt(firebaseData, "/security/record") == 1)
  {
     record_();
   }
   if (Firebase.getInt(firebaseData, "/security/repeat") == 1)
  {
     repeat_(1);
    }
    if (Firebase.getInt(firebaseData, "/security/repeat") == 0)
  {
     repeat_(0);
    }
    
}

void play_()
{
  digitalWrite(play,HIGH);
  delay(10000);
  digitalWrite(play,LOW);
 }
void record_()
{
  digitalWrite(rec,HIGH);
  delay(10000);
  digitalWrite(rec,LOW);
}
void repeat_(int state)
{
  if(state==1)
  digitalWrite(play,HIGH);
  if (state==0)
  digitalWrite(play,LOW);
  }
