#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 1, 177);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup()
{
	// You can use Ethernet.init(pin) to configure the CS pin
	//Ethernet.init(10);  // Most Arduino shields
	//Ethernet.init(5);   // MKR ETH shield
	//Ethernet.init(0);   // Teensy 2.0
	//Ethernet.init(20);  // Teensy++ 2.0
	//Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
	//Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

	// Open serial communications and wait for port to open:
	Serial.begin(9600);
	while(!Serial) delay(5);

	Serial.println("Ethernet WebServer Example");

	// start the Ethernet connection and the server:
	Ethernet.begin(mac, ip);

	// Check for Ethernet hardware present
	if(Ethernet.hardwareStatus() == EthernetNoHardware){
		Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
		while(true) delay(5); // do nothing, no point running without Ethernet hardware
	}
	if(Ethernet.linkStatus() == LinkOFF)
		Serial.println("Ethernet cable is not connected.");

	// Arduino UNO
	// pinMode(0, OUTPUT);
	// pinMode(1, OUTPUT);
	pinMode(2, OUTPUT);
	pinMode(3, OUTPUT);
	// pinMode(4, OUTPUT); // SD Card
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
	pinMode(8, OUTPUT);
	pinMode(9, OUTPUT);
	// pinMode(10, OUTPUT);
	// pinMode(11, OUTPUT);
	// pinMode(12, OUTPUT);
	// pinMode(13, OUTPUT);
	pinMode(A0, OUTPUT);
	pinMode(A1, OUTPUT);
	pinMode(A2, OUTPUT);
	pinMode(A3, OUTPUT);
	pinMode(A4, OUTPUT);
	pinMode(A5, OUTPUT);
 
	// start the server
	server.begin();
	Serial.print("server is at ");
	Serial.println(Ethernet.localIP());
}

int pinNumber(char *pin)
{
	if     (strncasecmp(pin, "D0",  2) == 0) return(0);
	else if(strncasecmp(pin, "D1",  2) == 0) return(1);
	else if(strncasecmp(pin, "D2",  2) == 0) return(2);
	else if(strncasecmp(pin, "D3",  2) == 0) return(3);
	else if(strncasecmp(pin, "D4",  2) == 0) return(4);
	else if(strncasecmp(pin, "D5",  2) == 0) return(5);    
	else if(strncasecmp(pin, "D6",  2) == 0) return(6);
	else if(strncasecmp(pin, "D7",  2) == 0) return(7);
	else if(strncasecmp(pin, "D8",  2) == 0) return(8);
	else if(strncasecmp(pin, "D9",  2) == 0) return(9);
	else if(strncasecmp(pin, "D10", 3) == 0) return(10);
	else if(strncasecmp(pin, "D11", 3) == 0) return(11);
	else if(strncasecmp(pin, "D12", 3) == 0) return(12);
	else if(strncasecmp(pin, "D13", 3) == 0) return(13);
	else if(strncasecmp(pin, "A0",  2) == 0) return(A0);
	else if(strncasecmp(pin, "A1",  2) == 0) return(A1);
	else if(strncasecmp(pin, "A2",  2) == 0) return(A2);
	else if(strncasecmp(pin, "A3",  2) == 0) return(A3);
	else if(strncasecmp(pin, "A4",  2) == 0) return(A4);
	else if(strncasecmp(pin, "A5",  2) == 0) return(A5);

	return(-1);
}

void loop()
{
#define URL_DELIMITER_CHAR ('?')
#define REQBUFF_SZ (12)
	char reqBuff[REQBUFF_SZ] = {'\0'};
	char c = 0;

	// listen for incoming clients
	EthernetClient client = server.available();

	if(client){
		// an http request ends with a blank line
		bool currentLineIsBlank = true;

		Serial.println("new client");

		while(client.connected()){

			if(client.available()){
#define RESBUFF_SZ (200)
				char response[RESBUFF_SZ] = {'\0'};
				
				c = client.read();
				Serial.write(c);
				// if you've gotten to the end of the line (received a newline
				// character) and the line is blank, the http request has ended,
				// so you can send a reply
				if(c == '\n' && currentLineIsBlank){

					if(strncmp(reqBuff, "STATUS", 6) == 0){
						snprintf(response, RESBUFF_SZ,
						         "D0=%c<br>D1=%c<br>D2=%c<br>D3=%c<br>D4=%c<br>D5=%c<br>D6=%c<br>D7=%c<br>D8=%c<br>D9=%c<br>"
						         "D10=%c<br>D11=%c<br>D12=%c<br>D13=%c<br>A0=%c<br>A1=%c<br>A2=%c<br>A3=%c<br>A4=%c<br>A5=%c", 
						         (digitalRead(0)  == LOW ? '0' : '1'), (digitalRead(1)  == LOW ? '0' : '1'),
						         (digitalRead(2)  == LOW ? '0' : '1'), (digitalRead(3)  == LOW ? '0' : '1'),
						         (digitalRead(4)  == LOW ? '0' : '1'), (digitalRead(5)  == LOW ? '0' : '1'),
						         (digitalRead(6)  == LOW ? '0' : '1'), (digitalRead(7)  == LOW ? '0' : '1'),
						         (digitalRead(8)  == LOW ? '0' : '1'), (digitalRead(9)  == LOW ? '0' : '1'),
						         (digitalRead(10) == LOW ? '0' : '1'), (digitalRead(11) == LOW ? '0' : '1'),
						         (digitalRead(12) == LOW ? '0' : '1'), (digitalRead(13) == LOW ? '0' : '1'),
						         (digitalRead(A0) == LOW ? '0' : '1'), (digitalRead(A1) == LOW ? '0' : '1'),
						         (digitalRead(A2) == LOW ? '0' : '1'), (digitalRead(A3) == LOW ? '0' : '1'),
						         (digitalRead(A4) == LOW ? '0' : '1'), (digitalRead(A5) == LOW ? '0' : '1'));

					}else if(strncmp(reqBuff, "SET", 3) == 0){
						int pinReq = 0;
						// 01234567
						// SET/D1=0

						pinReq = pinNumber(&reqBuff[4]);
						if(pinReq == -1){
							// TODO: ERRO
						}

						if(reqBuff[strlen(reqBuff)-1] == '0') digitalWrite(pinReq, LOW );
						else                                  digitalWrite(pinReq, HIGH);

/*
Serial.println("*****************");
Serial.println(strlen(reqBuff));
Serial.println(reqBuff[strlen(reqBuff)-1]);
Serial.println(pinReq);
Serial.println("*****************");
*/
						snprintf(response, RESBUFF_SZ, "GPIO [%d] set to [%c]", pinReq, (digitalRead(pinReq) == LOW ? '0' : '1'));

					}else if(strncmp(reqBuff, "GET", 3) == 0){
						int pinReq = 0;
						// 012345
						// GET/D1
						
						pinReq = pinNumber(&reqBuff[4]);
						if(pinReq == -1){
							// TODO: ERRO
						}

						snprintf(response, RESBUFF_SZ, "%c", (digitalRead(pinReq) == LOW ? '0' : '1'));
					}

					// send a standard http response header
					client.println("HTTP/1.1 200 OK");
					client.println("Content-Type: text/html");
					client.println("Connection: close");  // the connection will be closed after completion of the response
					// client.println("Refresh: 5");         refresh the page automatically every 5 sec
					client.println();
					client.println("<!DOCTYPE HTML>");
					client.println("<html>");
					client.println(response);
					client.println("</html>");
/*
Serial.println(">>>>> ENVIANDO:");
Serial.println(response);
*/
					break;
				}

				if(c == URL_DELIMITER_CHAR){
					int i = 0;

					memset(reqBuff, 0, REQBUFF_SZ);

					// getting the request parameter
					for(i = 0; i < REQBUFF_SZ && c != '\n'; i++){
						c = client.read();
						reqBuff[i] = c;
						Serial.write(c);
					}
					reqBuff[i-2] = '\0'; // writes \0 over \r
/*
Serial.println(">>>>> RECEBIDO:");
Serial.println(reqBuff);
Serial.println(">>>>> RECEBIDO BYTES:");
Serial.println(i);
Serial.println(">>>>> RECEBIDO STRLEN():");
Serial.println(strlen(reqBuff));
*/
				}

				if(c == '\n'){
					// you're starting a new line
					currentLineIsBlank = true;
				}else if (c != '\r'){
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
