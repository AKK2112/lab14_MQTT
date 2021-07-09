#include <MQTT.h>
#include "oled-wing-adafruit.h"
#include "blynk.h"


SYSTEM_THREAD(ENABLED);

OledWingAdafruit display;

void callback(char* topic, byte* payload, unsigned int length);

MQTT client("lab.thewcl.com", 1883, callback);

WidgetTerminal terminal(V1);
BLYNK_WRITE(V1) {
  String inputText = param.asStr();
  client.publish("vkak", inputText);
}
// recieve message
void callback(char* topic, byte* payload, unsigned int length) 
{
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  Serial.printlnf("%s",p);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println(p);
    display.display();
    delay(1000);
    
    if (p[0] == '1')
    {
      digitalWrite(D7, HIGH);
      Serial.println("LED on!");
    }
    if (p[0] == '0')
    {
      digitalWrite(D7, LOW);
      Serial.println("LED off!");
    }
}
void setup() {
  Serial.begin(9600);
  display.setup();
	display.clearDisplay();
	display.display();
  pinMode(D7, OUTPUT); // blue light
  Blynk.begin("DISy_9aRsQHnyt8mtvZXh09rT-tdy72R", IPAddress(167, 172, 234, 162), 9090);
  
}

void loop() {
  Blynk.run();
  

  
  display.loop();
    if (display.pressedA()) {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println("1");
      client.publish("vkak","Button 1 was pushed on the OLED!");
      display.display();
      delay(2000);
      display.clearDisplay();
      display.display();
    }
    if (display.pressedB()) {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println("2");
      client.publish("vkak","Button 2 was pushed on the OLED!");
      display.display();
      delay(2000);
      display.clearDisplay();
      display.display();
    }
    if (display.pressedC()) {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println("3");
      client.publish("vkak","Button 3 was pushed on the OLED!");
      display.display();
      delay(1000);
      display.clearDisplay();
      display.display();
    }

    if (client.isConnected()) {
      
      client.subscribe("vkak");
      client.loop();
    } else {
      client.connect(System.deviceID());
    }
delay(100);


}