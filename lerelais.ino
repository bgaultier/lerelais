/*
  lerelais
 
 A simple web server that switchs on or off relays.
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Relay Shield attached to port 4, 5, 6, 7, 8
 
 created 18 Dec 2009
 by David A. Mellis
 modified 2 Aug 2013
 by Baptiste Gaultier
 
 */

#include <SPI.h>
#include <Ethernet.h>
#include <avr/wdt.h>

int currentState6 = LOW;        // state used to toggle the relay 6
int currentState7 = LOW;        // state used to toggle the relay 6


String currentLine = "";        // string to hold the text from client
String query = "";              // string to hold the URL
String action = "";             // string to hold the action (on or off)
boolean readingQuery = false;   // if you're currently reading the query

String myapikey = "h3xk518i";

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x6F, 0x24 };
IPAddress ip(192,168,1, 177);

// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup() {
  // reserve space for the strings:
  currentLine.reserve(64);
  query.reserve(32);
  
  // initialize the digital pins as outputs:
  pinMode(4, OUTPUT);  
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  
  // open serial communications and wait for port to open:
  Serial.begin(9600);
  
  // attempt a DHCP connection:
  Serial.println("Attempting to get an IP address using DHCP:");
  if (!Ethernet.begin(mac)) {
    // if DHCP fails, start with a hard-coded address:
    Serial.println("failed to get an IP address using DHCP, trying manually");
    Ethernet.begin(mac, ip);
  }
  server.begin();
  Serial.print("lerelais v0.2 starting at ");
  Serial.print(Ethernet.localIP());
  Serial.println("...");
  
  // enable the watchdog timer, configuring it for expiry after 8 seconds:
  wdt_enable (WDTO_8S);
}


void loop() {
  // reset the watchdog timer:
  wdt_reset ();
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("New client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        //Serial.write(c);
        
        // add incoming byte to end of line:
        currentLine += c;
        
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println(F("HTTP/1.1 200 OK"));
          client.println(F("Content-Type: text/html"));
          client.println(F("Connection: close"));
          client.println();
          client.println(F("<!DOCTYPE html>"));
          client.println(F("<html>"));
          client.println(F("  <head>"));
          if(action.equals("on")) {
            client.println(F("    <link rel=\"apple-touch-icon-precomposed\" href=\"http://api.baptistegaultier.fr/on57.png\" />"));
            client.println(F("    <link rel=\"apple-touch-icon-precomposed\" sizes=\"72x72\" href=\"http://api.baptistegaultier.fr/on72.png\" />"));
            client.println(F("    <link rel=\"apple-touch-icon-precomposed\" sizes=\"114x114\" href=\"http://api.baptistegaultier.fr/on114.png\" />"));
            client.println(F("    <link rel=\"apple-touch-icon-precomposed\" sizes=\"144x144\" href=\"http://api.baptistegaultier.fr/on144.png\" />"));
          }
          else if(action.equals("off")) {
            client.println(F("    <link rel=\"apple-touch-icon-precomposed\" href=\"http://api.baptistegaultier.fr/off57.png\" />"));
            client.println(F("    <link rel=\"apple-touch-icon-precomposed\" sizes=\"72x72\" href=\"http://api.baptistegaultier.fr/off72.png\" />"));
            client.println(F("    <link rel=\"apple-touch-icon-precomposed\" sizes=\"114x114\" href=\"http://api.baptistegaultier.fr/off114.png\" />"));
            client.println(F("    <link rel=\"apple-touch-icon-precomposed\" sizes=\"144x144\" href=\"http://api.baptistegaultier.fr/off144.png\" />"));
          }
          else {
            client.println(F("    <link rel=\"apple-touch-icon-precomposed\" href=\"http://api.baptistegaultier.fr/toggle57.png\" />"));
            client.println(F("    <link rel=\"apple-touch-icon-precomposed\" sizes=\"72x72\" href=\"http://api.baptistegaultier.fr/toggle72.png\" />"));
            client.println(F("    <link rel=\"apple-touch-icon-precomposed\" sizes=\"114x114\" href=\"http://api.baptistegaultier.fr/toggle114.png\" />"));
            client.println(F("    <link rel=\"apple-touch-icon-precomposed\" sizes=\"144x144\" href=\"http://api.baptistegaultier.fr/toggle144.png\" />"));
          }
          client.println(F("    <link rel=\"apple-touch-startup-image\" href=\"http://api.baptistegaultier.fr/lerelais.png\" />"));
          client.println(F("    <meta name =\"viewport\" content =\"user-scalable=no, width=device-width\">"));
          client.println(F("    <title>lerelais</title>"));
          client.println(F("  </head>"));
          client.println(F("  <body>"));
          client.println(F("    <img src=\"http://api.baptistegaultier.fr/lerelais.png\" alt=\"lerelais v0.2\" />"));
          client.println(F("  </body>"));
          client.println(F("</html>"));
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
          currentLine = ""; 
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
        // if the current line ends with <text>, it will
        // be followed by the query:
        if ( currentLine.endsWith("?action=")) {
          // Query is beginning. Clear the query string:
          readingQuery = true; 
          query = "";
        }
        // if you're currently reading the bytes of a query,
        // add them to the query String:
        if (readingQuery) {
          if (c != 'H') {
             if (c != '=')
               query += c;
          }
          else {
            // if you got a "H" character (beginning of "HTTP/1.1"),
            // you've reached the end of the query:
            readingQuery = false;
            byte firstAmpersand = query.indexOf('&');
            action = query.substring(0, firstAmpersand);
            String apikey = query.substring(firstAmpersand+7, query.length() - 1);
            if(action.equals("on") && apikey.equals(myapikey))
              turnOn();
            if(action.equals("off") && apikey.equals(myapikey))
              turnOff();
            if(action.equals("toggle1") && apikey.equals(myapikey))
              toggleRelay6();
            if(action.equals("toggle2") && apikey.equals(myapikey))
              toggleRelay7();
          }
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("Client disconnected");
  }
}

void turnOn() {
  digitalWrite(5, HIGH);   // send an on order
  delay(1000);                     // during a second
  digitalWrite(5, LOW);
}

void turnOff() {
  digitalWrite(4, HIGH);   // send an off order
  delay(1000);                     // during a second
  digitalWrite(4, LOW);
}

void toggleRelay6() {
  if(currentState6 == HIGH) {
    currentState6 = LOW;
    digitalWrite(6, currentState6);
  }
  else {
    currentState6 = HIGH;
    digitalWrite(6, currentState6);
  }
}

void toggleRelay7() {
  if(currentState7 == HIGH) {
    currentState7 = LOW;
    digitalWrite(7, currentState7);
  }
  else {
    currentState7 = HIGH;
    digitalWrite(7, currentState7);
  }
}


