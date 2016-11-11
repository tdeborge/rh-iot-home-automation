#include <SPI.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//#include "TBOHAhome.h"
#include "TBOHAaccespoint.h"

WiFiClient espClient;
PubSubClient client(espClient);

String chipid;
unsigned long previousMillis = 0;

String moveTopic = "";
String lightTopic = "";
int ledState = LOW;

int movement = 0;

boolean lockLow = true;
boolean takeLowTime;
unsigned long lowIn;

//IPAddress ip(192, 168, 10, 20);
//IPAddress gateway(192, 168, 10, 1);
//IPAddress subnet(255, 255, 255, 0);
//IPAddress dns1(192, 168, 10, 1);
//IPAddress dns2(8, 8, 8, 8);

void setup() {
  if (S_DEBUG) {
    Serial.begin(9600);
  }
  pinMode(BUILTIN_LED, OUTPUT);  // initialize onboard LED as output
  pinMode(BLUEPIN, OUTPUT);
  pinMode(YELLOWPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);

  sendLeds(LOW);

  setup_wifi();
  printStatus();

  chipid = String( ESP.getChipId() );

  moveTopic = MQTTTopicPrefix + "+" + "/movement";
  lightTopic = MQTTSmartTopicPrefix + chipid + "/light";
  printStatus();

  client.setServer(server, port);
  client.setCallback(callback);


  sendLeds(HIGH);

  previousMillis = millis();

}

void loop() {
  unsigned long currentMillis = millis();
  if (!client.loop()) {
    reconnect();
  }
  if (movement == 1) {
    setLeds(SENSOR_MOTION_DETECTED);
    if (lockLow) {
      //makes sure we wait for a transition to LOW before any further output is made:
      lockLow = false;
      //send message light on
      client.publish(lightTopic.c_str(), "1");
      if (S_DEBUG) {
        Serial.println("---");
        Serial.print("motion detected at ");
        Serial.print(millis() / 1000);
        Serial.println(" sec");
      }
    }
    takeLowTime = true;
  }

  if (movement == LOW) {
    //digitalWrite(ledPin, LOW);  //the led visualizes the sensors output pin state

    if (takeLowTime) {
      lowIn = millis();          //save the time of the transition from high to LOW
      takeLowTime = false;       //make sure this is only done at the start of a LOW phase
    }
    //if the sensor is low for more than the given pause,
    //we assume that no more motion is going to happen
    if (!lockLow && millis() - lowIn > pause) {
      lockLow = true;
      //Send message light off
      client.publish(lightTopic.c_str(), "0");
      if (S_DEBUG) {
        Serial.print("motion ended at ");      //output
        Serial.print((millis() - pause) / 1000);
        Serial.println(" sec");
        // delay(50);
      }
    }
    if (lockLow) {
      setLeds(SENSOR_ACTIVE);
    }
    else {
      setLeds(SENSOR_MOTION_LATENT);
    }
  }
  // if enough millis have elapsed
  //  if (currentMillis - previousMillis >= publishInterval) {
  //    previousMillis = currentMillis;
  //
  //    // toggle the LED
  //    ledState = !ledState;
  //    digitalWrite(BUILTIN_LED, ledState);
  //    digitalWrite(BLUEPIN, ledState);
  //    digitalWrite(YELLOWPIN, ledState);
  //    digitalWrite(GREENPIN, ledState);
  //  }
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
      client.subscribe(moveTopic.c_str());
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

void sendLeds(unsigned int val) {
  digitalWrite(BUILTIN_LED, val);
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
//  WiFi.config(ip,gateway,subnet,dns1,dns2);
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
    Serial.print("The Sub Topic: ");
    Serial.println(moveTopic);
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  sendLeds(LOW);
  char text[length];
  if (S_DEBUG) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    char text[length];
  }

  for (int i = 0; i < length; i++) {
    if (S_DEBUG) {
      Serial.print((char)payload[i]);
    }
    text[i] = (char)payload[i];
  }
  if (S_DEBUG) {
    Serial.println("");
    Serial.print("the value received is: ");
    Serial.print(atoi(text));
    movement = atoi(text);
    Serial.println("");
  }
  movement = atoi(text);
  sendLeds(HIGH);   // turn off LED with voltage LOW
}

void setLeds(unsigned int val) {
  if (val & GREEN) {
    digitalWrite(GREENPIN, LOW);
  }
  else {
    digitalWrite(GREENPIN, HIGH);
  }

  if (val & YELLOW) {
    digitalWrite(YELLOWPIN, LOW);
  }
  else {
    digitalWrite(YELLOWPIN, HIGH);
  }

  if (val & BLUE) {
    digitalWrite(BLUEPIN, LOW);
  }
  else {
    digitalWrite(BLUEPIN, HIGH);
  }
}
