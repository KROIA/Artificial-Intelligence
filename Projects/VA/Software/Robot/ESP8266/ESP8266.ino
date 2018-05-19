//ItKindaWorks - Creative Commons 2016
//github.com/ItKindaWorks
//
//Requires PubSubClient found here: https://github.com/knolleary/pubsubclient
//
//ESP8266 Simple MQTT light controller
//https://www.youtube.com/watch?v=PgsH43Tpqjc
//Setup the ESP8266: http://www.instructables.com/id/Getting-Started-With-the-ESP8266-ESP-01/

#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include "Timer.h"
//#define SERIAL_RX_BUFFER_SIZE 128
//#define SERIAL_TX_BUFFER_SIZE 128

Timer blinkTimer;
Timer wiFiTimer;
Timer recivedTimer;
Timer recivedSerialTimer;
Timer timeoutSerialIn;
boolean blinkSwitch = false;
Timer timer500ms;
//EDIT THESE LINES TO MATCH YOUR SETUP
#define MQTT_SERVER "192.168.0.100"
const char* ssid = "dlink-9FE0";
const char* password = "yuedp80831";

//LED on ESP8266 GPIO2
const int redLed = 2;
const int greenLed = 0;

//char* lightTopic = "/test/light1";

/*char* sens1Topic = "robot/sens1";
char* sens2Topic = "robot/sens2";
char* sens3Topic = "robot/sens3";
char* sens4Topic = "robot/sens4";
char* sens5Topic = "robot/sens5";
char* sens6Topic = "robot/sens6";*/
char* motLTopic  = "robot/motL";
char* motRTopic  = "robot/motR";
char* masterTopic= "robot/master";


WiFiClient wifiClient;
PubSubClient client(MQTT_SERVER, 1883, callback, wifiClient);

void setup() {
  Serial.begin(19200);
   Serial.println("SETUP");
	//initialize the light as an output and set to LOW (off)
	pinMode(redLed, OUTPUT);
        pinMode(greenLed, OUTPUT);
	digitalWrite(redLed, LOW);
	digitalWrite(greenLed, LOW);

	//start the serial line for debugging
	
	delay(100);


	//start wifi subsystem
	WiFi.begin(ssid, password);
	//attempt to connect to the WIFI network and then connect to the MQTT server
	reconnect();

	//wait a bit before starting the main loop
    	//delay(2000);
    //Serial.println("LOOP");
    /*while(true)
    {
      blinkRed(100);
      }*/
}

char incomingByte;
//String _buffer = "";
void loop(){

	//reconnect if connection is lost
        if(wiFiTimer.start(10))
        {
            if (!client.connected() && WiFi.status() == 3) {Serial.println("RECONNECT");reconnect();}
        }
//delay(10);
       /* if(WiFi.status()!=WL_CONNECTED)
        {
          blinkRed(50);
        }*/
	//maintain MQTT connection
	client.loop();

	//MUST delay to allow ESP8266 WIFI functions to run
          String _buffer = "";
          boolean ret = false;
        if(Serial.available() > 0)
        {
          
          String _buffer = Serial.readStringUntil('\n');
          //Serial.flush();
          
         /*while(!ret)
          {
             incomingByte = (char)Serial.read();
                if(incomingByte == '\n')
                {
                  ret = true;
                  //break;
                }
                if(timeoutSerialIn.start(100))
                {
                  ret = true;
                  Serial.println("TIMEOUT");
                }
                if(incomingByte != -1 && incomingByte != 255 && incomingByte != '\n')
                {
                  _buffer+=incomingByte;
                  //Serial.print(incomingByte);
                 // Serial.print("->");
                 // Serial.print(incomingByte,DEC);
                }
            
           
          }*/
          //Serial.flush();
          //timeoutSerialIn.stop();
          /* Serial.println("-------");
          Serial.println(_buffer);
           Serial.println("---END----");*/
          //client.publish("robot/master1", _buffer.c_str()); 
         if(_buffer.indexOf("||") != -1)
          {
            digitalWrite(redLed, LOW);
            recivedSerialTimer.stop();
            recivedSerialTimer.start(5);
            digitalWrite(redLed, HIGH);
            client.publish(_buffer.substring(0,_buffer.indexOf("||")).c_str(), _buffer.substring(_buffer.indexOf("||")+2).c_str()); 
          }
        }
	//delay(10); 
        if(recivedTimer.update() == true)
        {
          digitalWrite(greenLed, HIGH);
        }
        if(recivedSerialTimer.update()==true)
        {
          digitalWrite(redLed, LOW);
        }
}


void callback(char* topic, byte* payload, unsigned int length) {

	//convert topic to string to make it easier to work with
	String topicStr = topic; 

	//Print out some debugging info
	/*Serial.println("Callback update.");
	Serial.print("Topic: ");
	Serial.println(topicStr);
        Serial.print("Message: ");
        Serial.println((char*)payload);
        Serial.println(length);
        

        Serial.print("Message: ");
        Serial.println(message);
        */
        String message = (char*)payload;
        message = message.substring(0,length);
        message = (String)topic + "||" + message + '\n';
        Serial.print(message);
        digitalWrite(greenLed, HIGH);
        recivedTimer.stop();
        recivedTimer.start(5);
        digitalWrite(greenLed, LOW);
        
	//turn the light on if the payload is '1' and publish to the MQTT server a confirmation message
	/*if( message == "11"){
		digitalWrite(lightPin, HIGH);
		client.publish("/test/confirm", "Light On");

	}

	//turn the light off if the payload is '0' and publish to the MQTT server a confirmation message
	else if ( message == "00"){
		digitalWrite(lightPin, LOW);
		client.publish("/test/confirm", "Light Off");
	}
*/
}




void reconnect() {

	//attempt to connect to the wifi if connection is lost
	if(WiFi.status() != WL_CONNECTED){
		//debug printing
		Serial.print("Connecting to ");
		Serial.println(ssid);

		//loop while we wait for connection
		while (WiFi.status() != WL_CONNECTED) {
			delay(100);

			Serial.print(".");
                       // while(!timer500ms.start(100))
                        {
                          blinkRed(100);
                          //delay(10);
                        }
                        //Serial.println("----------------------");
		}

		//print out some more debug once connected
		Serial.println("");
		Serial.println("WiFi connected");  
		Serial.println("IP address: ");
		Serial.println(WiFi.localIP());
	}

	//make sure we are connected to WIFI before attemping to reconnect to MQTT
	if(WiFi.status() == WL_CONNECTED){
	// Loop until we're reconnected to the MQTT server
		while (!client.connected()) {
  
  
                        blinkRed(500);
                    
                          
                        
			Serial.print("Attempting MQTT connection...");

			// Generate client name based on MAC address and last 8 bits of microsecond counter
			String clientName;
			clientName += "esp8266-";
			uint8_t mac[6];
			WiFi.macAddress(mac);
			clientName += macToStr(mac);

			//if connected, subscribe to the topic(s) we want to be notified about
			if (client.connect((char*) clientName.c_str())) {
				Serial.print("\tMTQQ Connected");
				//client.subscribe(lightTopic);

                          
                                client.subscribe(motLTopic);
                                client.loop();
                                client.subscribe(motRTopic);
                                client.loop();
                                client.subscribe(masterTopic);
                                client.loop();
			}

			//otherwise print failed for debugging
			else{Serial.println("\tFailed."); abort();}
		}
                digitalWrite(greenLed, HIGH);
                digitalWrite(redLed, LOW);
	}
}
//generate unique name from MAC addr
String macToStr(const uint8_t* mac){

  String result;

  for (int i = 0; i < 6; ++i) {
    result += String(mac[i], 16);

    if (i < 5){
      result += ':';
    }
  }

  return result;
}
void blinkRed(int time)
{
  if(blinkTimer.start(time))
   {
       
       if(blinkSwitch)
       {
         digitalWrite(redLed, LOW);
         blinkSwitch = false;
        // Serial.println("LOW");
       }
       else
       {
         digitalWrite(redLed, HIGH);
         //digitalWrite(greenLed,LOW);
         blinkSwitch = true;
       //  Serial.println("HIGH");
       }  
       
   }
}




