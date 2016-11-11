#include <SPI.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//#include "TBOHAhome.h"
#include "TBOHAaccespoint.h"

WiFiClient espClient;
PubSubClient client(espClient);

String chipid;
unsigned long previousMillis = 0;
//IPAddress ip(192, 168, 10, 21);
//IPAddress gateway(192, 168, 10, 1);
//IPAddress subnet(255, 255, 255, 0);
//IPAddress dns1(192, 168, 10, 1);
//IPAddress dns2(8, 8, 8, 8);

String moveTopic = "";

void setup() {
  if (S_DEBUG) {
    Serial.begin(9600);
  }
  pinMode(BUILTIN_LED, OUTPUT);  // initialize onboard LED as output
  pinMode(PIRPIN, INPUT);
  if (S_DEBUG) {
    Serial.print("calibrating sensor ");
  }
  sendLeds(LOW);
  for (int i = 0; i < calibrationTime; i++) {
    if (S_DEBUG) {
      Serial.print(".");
    }
    delay(1000);
  }
  if (S_DEBUG) {
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
  }

  sendLeds(HIGH);
  delay(500);
  sendLeds(LOW);

  setup_wifi(); 
  
  chipid = String( ESP.getChipId() );

  moveTopic = MQTTTopicPrefix + chipid + "/movement";
  printStatus();

  client.setServer(server, port);


  sendLeds(HIGH);

  previousMillis = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!client.loop()) {
    reconnect();
  }

  if (millis() - previousMillis > publishInterval) {
    sendLeds(LOW);
    sendMovementInformation();
    previousMillis = millis();
    sendLeds(HIGH);
  }
}

//Setting up the Wifi environment:
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  if (S_DEBUG) {
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
  }
  
 // WiFi.config(ip,gateway,subnet,dns1,dns2);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (S_DEBUG) {
      Serial.print(".");
    }
  }
  if (S_DEBUG) {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
}

void printStatus() {
  // print the SSID of the network you're attached to:
  if (S_DEBUG) {
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print your WiFi shield's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
    Serial.print("CHIP_ID:");
    Serial.println(chipid);
    Serial.print("The Pub Topic: ");
    Serial.println(moveTopic);
  }
}

void sendLeds(unsigned int val) {
  digitalWrite(BUILTIN_LED, val);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    if (S_DEBUG) {
      Serial.print("Attempting MQTT connection...");
      Serial.print(server);
      Serial.print(" ... ");
      Serial.print(port);
      
    }
    // Attempt to connect
    if (client.connect(chipid.c_str(), mqtt_user, mqtt_password)) {
      if (S_DEBUG) {
        Serial.println("CONNECTED .......");
      }
    } else {
      if (S_DEBUG) {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
      }
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
  if (S_DEBUG) {
    Serial.println("Connection OK .....");
  }
}

void sendMovementInformation() {
  if (digitalRead(PIRPIN) == HIGH) {
    client.publish(moveTopic.c_str(), "1");
    if (S_DEBUG) {
      Serial.println("Sending Information HIGH");
    }
  }
  else {
    client.publish(moveTopic.c_str(), "0");
    if (S_DEBUG) {
      Serial.println("Sending Information LOW");
    }
  }

}

