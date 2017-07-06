#include <IRremoteESP8266.h>
#include <IRsend.h> 
#include <ESP8266mDNS.h>

const char* ssid = "ssid";
const char* password = "pass";
MDNSResponder mdns;

IRsend irsend(4);  // An IR LED is controlled by GPIO pin 4 (D2)

// Lasko IR commands
uint16_t FAN_POWER[] = {1300, 350, 1300, 400, 400, 1250, 1250, 400, 1250, 400, 450, 1250, 400, 1250, 450, 1200, 450, 1250, 400, 1250, 450, 1200, 1250};
uint16_t FAN_TIMER[] = {1250, 400, 1250, 400, 450, 1200, 1250, 400, 1250, 450, 400, 1250, 450, 1200, 450, 1250, 1250, 400, 450, 1200, 450, 1250, 400};
uint16_t FAN_ROTATE[] = {1250, 400, 1250, 400, 450, 1200, 1300, 350, 1250, 450, 400, 1250, 450, 1200, 1300, 400, 400, 1250, 450, 1250, 400, 1250, 450};
uint16_t FAN_SPEED[] = {1250, 400, 1250, 400, 400, 1250, 1250, 400, 1250, 400, 450, 1250, 450, 1200, 450, 1250, 400, 1250, 450, 1200, 1250, 450, 400};

int kHz = 38;

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  irsend.begin();
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");

  // Start the server
  server.begin();
  Serial.println("HTTP Server Started");

  // Print the IP address
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  if (mdns.begin("IRBlasterLR", WiFi.localIP())) {
    Serial.println("MDNS Responder Started");
  }

  Serial.println();
  Serial.println();
}

void loop() {

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  if (req.indexOf("/power") != -1){
    Serial.println("Power On");
    irsend.sendRaw(FAN_POWER, sizeof(FAN_POWER) / sizeof(FAN_POWER[0]), kHz);
    Serial.println("IRreq Power sent");
  } else if (req.indexOf("/timer") != -1){
      irsend.sendRaw(FAN_TIMER, sizeof(FAN_TIMER) / sizeof(FAN_TIMER[0]), kHz);   
      Serial.println("IRreq Timer sent");
  } else if (req.indexOf("/rotate") != -1){
      irsend.sendRaw(FAN_ROTATE, sizeof(FAN_ROTATE) / sizeof(FAN_ROTATE[0]), kHz);   
      Serial.println("IRreq Timer sent");
  } else if (req.indexOf("/speed") != -1){
      irsend.sendRaw(FAN_SPEED, sizeof(FAN_SPEED) / sizeof(FAN_SPEED[0]), kHz);   
      Serial.println("IRreq Speed sent");
  } else {
    Serial.println("invalid request");
    client.stop();
    return;
  }
  
  client.flush();
  // Send the response to the client
  //client.print(s);
  client.print("HTTP/1.1 200 OK\r\n");
  delay(1);
  Serial.println("Client Disconnected");
  Serial.println();
  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
 
}
