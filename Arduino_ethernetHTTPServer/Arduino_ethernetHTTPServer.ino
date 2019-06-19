#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 177);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup() {
  // You can use Ethernet.init(pin) to configure the CS pin
  //Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Ethernet WebServer Example");

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  // start the server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

int pinNumber(char *pin)
{
  if(strncmp(pin, "D1", 3) == 0){
    return (1);
  }else if(strncasecmp(pin, "D2", 3) == 0){
    return (2);
  }else if(strncasecmp(pin, "D3", 3) == 0){
    return (3);
  }else if(strncasecmp(pin, "D4", 3) == 0){
    return (4);
  }else if(strncasecmp(pin, "D5", 3) == 0){
    return (5);    
  }else if(strncasecmp(pin, "D6", 3) == 0){
    return (6);
  }else if(strncasecmp(pin, "D7", 3) == 0){
    return (7);
  }else if(strncasecmp(pin, "D8", 3) == 0){
    return (8);
  }else if(strncasecmp(pin, "D9", 3) == 0){
    return (9);
  }else if(strncasecmp(pin, "D10", 3) == 0){
    return (10);
  }else if(strncasecmp(pin, "D11", 3) == 0){
    return (11);
  }else if(strncasecmp(pin, "D12", 3) == 0){
    return (12);
  }else if(strncasecmp(pin, "D13", 3) == 0){
    return (13);
  }else if(strncasecmp(pin, "A0", 3) == 0){
    return (A0);
  }else if(strncasecmp(pin, "A1", 3) == 0){
    return (A1);
  }else if(strncasecmp(pin, "A2", 3) == 0){
    return (A2);
  }else if(strncasecmp(pin, "A3", 3) == 0){
    return (A3);
  }else if(strncasecmp(pin, "A4", 3) == 0){
    return (A4);
  }else if(strncasecmp(pin, "A5", 3) == 0){
    return (A5);
  }else if(strncasecmp(pin, "A6", 3) == 0){
    return(A6);
  }

  return(-1);
}
void loop() {
    #define REQBUFF_SZ (100)
  char reqBuff[REQBUFF_SZ] = {'\0'};
  char c = 0;
  
  // listen for incoming clients
  EthernetClient client = server.available();

  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    bool currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        #define RESBUFF_SZ (200)
        char response[RESBUFF_SZ] = {'\0'};
        c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          if(strncmp(reqBuff, "STATUS", 6) == 0){
          }else if(strncmp(reqBuff, "SET", 3) == 0){
            char gpio[4] = {'\0'}, *endch = NULL;
            /* 0123456 */
            /* SET/D1=0 */
            endch = strchr(&reqBuff[4], '=');
            if(endch == NULL){
              /* TODO: erro */
            }
            
            if(reqBuff[4] == 'D' || reqBuff[4] == 'd'){
              strncpy(gpio, &reqBuff[5], &reqBuff[5]-endch);
            }else{
              strncpy(gpio, &reqBuff[4], &reqBuff[5]-endch); /* GPIOs A[0-6] */
            }
            
          /*digitalWrite();*/
          }else if(strncmp(reqBuff, "GET", 3) == 0){
            /* 0123456 */
            /* GET/D1 */

          }
          
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          /* client.println("Refresh: 5"); */  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of each analog input pin
          #if 0
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");
          }
          #endif

          client.println("</html>");
          break;
        }

        if(c == '$'){
          int i = 0;
          /* getting the request parameter */
          for(i = 0; i < REQBUFF_SZ || c == '\n'; i++){
            char c = client.read();
            reqBuff[i] = c;
            Serial.write(c);
          }
          reqBuff[i-1] = '\0'; /* writes \0 over \r */
        }
        
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}
