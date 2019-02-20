
#include <Adafruit_MQTT_Client.h> // les deux libraire mqtt
#include <Adafruit_MQTT.h>
#include <WiFi.h> // librairie wifi
#include <uTimerLib.h>
WiFiClient wiFiClient;
Adafruit_MQTT_Client mqttClient(&wiFiClient, "192.168.0.109", 1883); // creation de l'objet wifi de connection
Adafruit_MQTT_Publish comPublisher(&mqttClient, "/commande");
int commande = 0;


void boutondash() {
  
int button1 = digitalRead(26);
int button2 = digitalRead(27);

comPublisher.publish(commande);

if (button1 == HIGH) {
   commande++;
}
if (button2 == HIGH) {
   commande--;
}
  
}

void setup() {

pinMode(26, INPUT);
pinMode(27, INPUT);
Serial.begin(115200);
WiFi.begin("createch2019", "createch2019");
delay(5000);
TimerLib.setInterval_s(boutondash, 2);

}


void loop() {


  // put your main code here, to run repeatedly:
if (mqttClient.connected()) { // cette condition permet a l' arduino de verifier sa connection wifi
    mqttClient.processPackets(10000);
    mqttClient.ping();
  } else {
    mqttClient.disconnect();
    mqttClient.connect();
  }
  Serial.println(commande);
 
}
