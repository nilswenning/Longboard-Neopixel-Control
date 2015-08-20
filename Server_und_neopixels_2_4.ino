
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SimpleTimer.h>
#include <EEPROM.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, 2, NEO_GRB + NEO_KHZ800);
int Type = 0;
const char* ssid = "Hallo";
const char* password = "........";
MDNSResponder mdns;

ESP8266WebServer server(80);

String indix = "<!DOCTYPE html><html><head><title>Longboard Steuerung</title><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><style>body{background: linear-gradient(0deg, yellow 5%, orange 70%);}.op{opacity: 0.8;}h1{color:#564536;font-family: Courier;font-size: 50px;}</style></head><body><div align='center' class='op'><h1>Longboard Steuerung</h1><br><br><br><form action='a'><input type='submit' value='OFF'></form><br><br><form action='b'><input type='submit' value='Rot'></form><br><br><form action='c'><input type='submit' value='Gruen'></form><br><br><form action='d'><input type='submit' value='Blau'></form><br><br><form action='e'><input type='submit' value='Blinken Weiss'></form><br><br><form action='f'><input type='submit' value='Blinken Rot'></form><br><br><form action='g'><input type='submit' value='Blinken Blau'></form><br><br><form action='h'><input type='submit' value='Regenbogen'></form><br><br><form action='i'><input type='submit' value='Regenbogen Kreis'></form><br><br><form action='j'><input type='submit' value='Blinken Regenbogen'></form><br><br><form action='restart'><input type='submit' value='Restart'></form><br><br></div></body></html>";
byte epval;

SimpleTimer timer;
// a function to be executed periodically
void repeatMe() {
      server.handleClient();
  
  
}

void setup() {
    Serial.begin(115200);
    Serial.println("Start");
    delay(500);
    timer.setInterval(1, repeatMe);
  strip.begin(); // This initializes the NeoPixel library.
  Serial.begin(115200);
  WiFi.softAP(ssid);
  Serial.println("");
  Type = 7;
  Serial.println(Type);
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  EEPROM.begin(512);
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
  
  server.on("/", handleRoot);
  
  server.on("/a", [](){
    server.send(200, "text/html", "<meta http-equiv='refresh' content='5; URL=http://192.168.4.1'><p>ok</p>");
    save(0);
    Type = 0;
    
  });
  server.on("/b", [](){
    server.send(200, "text/html", "<meta http-equiv='refresh' content='5; URL=http://192.168.4.1'><p>ok</p>");
    save(1);
    Type = 1;
    
  });
  server.on("/c", [](){
    server.send(200, "text/html", "<meta http-equiv='refresh' content='5; URL=http://192.168.4.1'><p>ok</p>");
    save(2);
    Type = 2;
    
  });
  server.on("/d", [](){
    server.send(200, "text/html", "<meta http-equiv='refresh' content='5; URL=http://192.168.4.1'><p>ok</p>");
    save(3);
    Type = 3;
    
  });
  server.on("/e", [](){
    server.send(200, "text/html", "<meta http-equiv='refresh' content='5; URL=http://192.168.4.1'><p>ok</p>");
    save(4);
    Type = 4;
    
  });
  server.on("/f", [](){
    server.send(200, "text/html", "<meta http-equiv='refresh' content='5; URL=http://192.168.4.1'><p>ok</p>");
    save(5);
    Type = 5;
    
  });
  server.on("/g", [](){
    server.send(200, "text/html", "<meta http-equiv='refresh' content='5; URL=http://192.168.4.1'><p>ok</p>");
    save(6);
    Type = 6;
    
  });
  server.on("/h", [](){
    server.send(200, "text/html", "<meta http-equiv='refresh' content='5; URL=http://192.168.4.1'><p>ok</p>");
    save(7);
    Type = 7;
    
  });
  server.on("/i", [](){
    server.send(200, "text/html", "<meta http-equiv='refresh' content='5; URL=http://192.168.4.1'><p>ok</p>");
    save(8);
    Type = 8;
  });
  server.on("/j", [](){
    server.send(200, "text/html", "<meta http-equiv='refresh' content='5; URL=http://192.168.4.1'><p>ok</p>");
    save(9);
    Type = 9;
  });
  server.on("/restart", [](){
    server.send(200, "text/html", "<p>OK RESTART");
    ESP.restart();
  });



  server.onNotFound(handleNotFound);
  
  server.begin();
  Serial.println("HTTP server started");


  epval = EEPROM.read(0);
  Serial.print("EEPROM :");
  Serial.print("\t");
  Serial.println(epval, DEC);
  Type = epval;
  Serial.print("Danach :");
  Serial.print("\t");
  Serial.println(Type);
}






void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}





void handleRoot() {
  server.send(400, "text/html", indix);
  }






void loop() {
    timer.run();
    startShow();
}







void save(int val){
  EEPROM.write(0, val);
  EEPROM.commit();
  delay(100);
}



void startShow() {
  switch(Type){
    case 0: colorWipe(strip.Color(0, 0, 0), 50);    // Black/off
            break;
    case 1: colorWipe(strip.Color(255, 0, 0), 50);  // Red
            break;
    case 2: colorWipe(strip.Color(0, 255, 0), 50);  // Green
            break;
    case 3: colorWipe(strip.Color(0, 0, 255), 50);  // Blue
            break;
    case 4: theaterChase(strip.Color(127, 127, 127), 50); // White
            break;
    case 5: theaterChase(strip.Color(127,   0,   0), 50); // Red
            break;
    case 6: theaterChase(strip.Color(  0,   0, 127), 50); // Blue
            break;
    case 7: rainbow(20);
            break;
    case 8: rainbowCycle(20);
            break;
    case 9: theaterChaseRainbow(50);
            break;
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}


