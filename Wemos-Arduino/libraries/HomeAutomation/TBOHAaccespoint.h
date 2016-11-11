//
//  TBOHAhome.h
//
//
//  Created by Tim De Borger on 14/07/16.
//
//
#ifndef tbohome_h
#define tbohome_h
//**********************************************************
//General Parameters
//**********************************************************
//When not looking at a serial monitor, it is better to disabel debugging
const boolean S_DEBUG = true;

//WIFI
const char* ssid = "RHIoT";
const char* password = "rhiot123";

//MQTT
const int port = 1883;
char mqtt[] = "192.168.10.3";
IPAddress server(192, 168, 10, 3);

const char* mqtt_user = "admin";
const char* mqtt_password = "admin";

String MQTTTopicPrefix = "Wemos/Home/";
String MQTTSmartTopicPrefix = "Wemos/SmartHome/";

//NNTP Server Address
IPAddress timeServerIP(129, 6, 15, 28);

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//This controls if you subscribe to your own messages or not
const boolean loopBack = true;

//This is the timeout in ms for sending measuring information
unsigned long measureloop = 30000;

//Rate in ms for blinking in case the clock was not settable
unsigned long fatalNNTPblinkrate = 100;

//**********************************************************



//**********************************************************
//Smart Sensor Parameters
//**********************************************************
const int PIRPIN = 14;
//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
const int calibrationTime = 2;
const int publishInterval = 500;
//**********************************************************




//**********************************************************
//Smart Light Parameters
//**********************************************************
const int BLUEPIN = 14;
const int YELLOWPIN = 12;
const int GREENPIN = 13;

const unsigned int GREEN = 1;
const unsigned int YELLOW = 2;
const unsigned int BLUE = 4;

const unsigned int SENSOR_ACTIVE = 2;
const unsigned int SENSOR_MOTION_DETECTED = 7;
const unsigned int SENSOR_MOTION_LATENT = 3;
const unsigned int SENSOR_OFF = 0;
const unsigned int SENSOR_BOOTING = 1;

const unsigned int pause = 5000;
//**********************************************************










#endif /* TBOHAhome.h */
