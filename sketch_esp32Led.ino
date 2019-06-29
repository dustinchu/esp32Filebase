#include <WiFi.h>                                                // esp32 library

#include <IOXhop_FirebaseESP32.h>                                             // firebase library

#define FIREBASE_HOST "XXXX.firebaseio.com"   
#define FIREBASE_AUTH "TOKEN"   
#define WIFI_SSID "name"               
#define WIFI_PASSWORD "pwd"

String fireStatus = "";                                                     // led status received from firebase

int led = 2;                                                               

void setup() {

  Serial.begin(115200);

  delay(1000);

  pinMode(21, OUTPUT);                

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                      //try to connect with wifi

  Serial.print("Connecting to ");

  Serial.print(WIFI_SSID);

  while (WiFi.status() != WL_CONNECTED) {

    Serial.print(".");

    delay(500);

  }

  Serial.println();

  Serial.print("Connected to ");

  Serial.println(WIFI_SSID);

  Serial.print("IP Address is : ");

  Serial.println(WiFi.localIP());                                                      //print local IP address

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                                       // connect to firebase

  Firebase.setString("LED_STATUS", "OFF");                                          //send initial string of led status

}

void loop() {

  fireStatus = Firebase.getString("LED_STATUS");                     // get led status input from firebase

  if (fireStatus == "ON") {                         // compare the input of led status received from firebase

    Serial.println("Led Turned ON");                 

    digitalWrite(21, HIGH);                                                         // make output led ON

  }

  else if (fireStatus == "OFF") {              // compare the input of led status received from firebase

    Serial.println("Led Turned OFF");

    digitalWrite(21, LOW);                                                         // make output led OFF

  }

  else {

    Serial.println("Wrong Credential! Please send ON/OFF");

  }

}
