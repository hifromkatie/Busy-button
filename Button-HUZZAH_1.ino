#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_NeoPixel.h>
#include <LittleFS.h>

#define RED indicate.Color(255,0,0)
#define BLACK indicate.Color(0,0,0)
#define GREEN indicate.Color(0,255,0)

const char* ssid = "****";
const char* password = "****";
const char* mqtt_server = "192.168.0.143";

const int buttonPin = 12;
const int ledPin = 14;

boolean indicate_status = false;
int buttonState, lastButtonState = 0;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;


Adafruit_NeoPixel indicate(1,ledPin, NEO_RGB + NEO_KHZ800);

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

//using example code for setting up wifi
void setup_wifi() {

  delay(10);
  indicate.setPixelColor(0, GREEN);
  indicate.show();
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  indicate.setPixelColor(0, BLACK);
  indicate.show();
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if (memcmp(payload,"busy",length)==0){
    indicate.setPixelColor(0,RED);
    indicate.show();
    indicate_status = true;
  }else if(memcmp(payload,"notBusy",length)==0){
    indicate.setPixelColor(0,BLACK);
    indicate.show();
    indicate_status = false;
  }

}

//use example code for reconnecting
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin,INPUT);
  pinMode(ledPin,OUTPUT);
  indicate.begin();
  indicate.setBrightness(50);  
  indicate.setPixelColor(0, BLACK);
  indicate.show();
  indicate.show(); //https://github.com/adafruit/Adafruit_NeoPixel/issues/159 
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

}

void loop() {
    if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int readButtonState = digitalRead(buttonPin);

  if (readButtonState !=lastButtonState){
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay){
    if (readButtonState != buttonState){
      buttonState = readButtonState;

      if (buttonState ==HIGH){
        if (indicate_status==false){
          client.publish("button1","busy");
          indicate_status = true;
        }else if (indicate_status==true){
          client.publish("button1","notBusy");
          indicate_status = false;          
        }
      }
    }
      
  }
  lastButtonState = readButtonState;

}
