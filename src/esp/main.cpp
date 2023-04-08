#include <Arduino.h>
#include <ESP8266WiFi.h>

#define LED1  4 // D2
#define LED2  5 // D1
#define LED3  14 // D5



const char* ssid = "smartHome";
const char* password = "12345678";
const uint16_t socketNo = 5045;
WiFiServer wifiServer(socketNo);



int LED_TCP = 2; // GPIO2 of ESP8266

void setup() {

  pinMode(LED1, OUTPUT); // Initialize the LED pin as an output
  pinMode(LED2, OUTPUT); // Initialize the LED pin as an output
  pinMode(LED3, OUTPUT); // Initialize the LED pin as an output
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  // Set your Static IP address
  IPAddress local_IP(192, 168, 1, 50);
  // Set your Gateway IP address
  IPAddress gateway(192, 168, 1, 1);

  IPAddress subnet(255, 255, 255, 0);
  IPAddress primaryDNS(8, 8, 8, 8);   //optional
  IPAddress secondaryDNS(8, 8, 4, 4); //optional

  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
      Serial.println("STA Failed to configure");
  }

  Serial.begin(9600);
  delay(1000);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting..");
  }
  Serial.print("Connected to WiFi. IP:");
  Serial.println(WiFi.localIP());
  digitalWrite(LED_BUILTIN, LOW);
  wifiServer.begin();
}

void loop() {
  WiFiClient client = wifiServer.available();
  bool sendFeedBack = false;
  char msg[10] = {};
  if (client) {
    while (client.connected()) {
      int i = 0;
      while (client.available() > 0) {
        char c = client.read();
        msg[i] = c;
        Serial.write(c);
        delay(50);
        sendFeedBack = true;
        i++;
      }
      if(sendFeedBack)
      {
        if(msg[0] >= '1' && msg[0] <= '3' && msg[1] == '#' && msg[2] >= '0' && msg[2] <= '1')
        {
          bool ledState = LOW;
          if(msg[2] == '1')
            ledState = HIGH;
          
          switch(msg[0])
          {
            case '1':
              digitalWrite(LED1, ledState);
              break;
            case '2':
              digitalWrite(LED2, ledState);
              break;
            case '3':
              digitalWrite(LED3, ledState);
              break;
          }
          
        }
        
        client.println("thanks");
      
      }
      sendFeedBack = false;
    }
  }
  client.stop();
}


// void setup() {
//   // put your setup code here, to run once:
//   pinMode(LED1, OUTPUT); // Initialize the LED pin as an output
//   pinMode(LED2, OUTPUT); // Initialize the LED pin as an output
//   pinMode(LED3, OUTPUT); // Initialize the LED pin as an output
// }

// void loop() {
//   digitalWrite(LED1, LOW); // Turn the LED on (Note that LOW is the voltage level)
//   digitalWrite(LED2, LOW); // Turn the LED on (Note that LOW is the voltage level)
//   digitalWrite(LED3, LOW); // Turn the LED on (Note that LOW is the voltage level)
//   delay(1000); // Wait for a second
//   digitalWrite(LED1, HIGH); // Turn the LED off by making the voltage HIGH
//   digitalWrite(LED2, HIGH); // Turn the LED off by making the voltage HIGH
//   digitalWrite(LED3, HIGH); // Turn the LED off by making the voltage HIGH
//   delay(1000); // Wait for two seconds
// }