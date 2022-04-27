#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define OLED_RESET     4 
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };



AsyncWebServer server(80);

const char* ssid = "Redmi8";  //wifi ssid
const char* password = "19701970";   //wifi password

const char* PARAM_INPUT_1 = "input1";


const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>Smart Notice Board</title>
  <meta name="viewport" content="width=device-width, initial-scale=5">
<p>
<font size="9" face="sans-serif"> <marquee> Smart Notice Board </marquee> </font> </p>
</head><body><center>
  <form action="/get">
    Enter Text to Display: <input type="text" name="input1">
    <input type="submit" value="Send">
  </form>
<br>
 
</center>
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  Serial.begin(9600);
  
if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }


  display.display();
  delay(2000);
  
  display.clearDisplay();

  display.drawPixel(10, 10, SSD1306_WHITE);

  display.display();
  delay(2000);
  
   display.clearDisplay();

  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,1);             // Start at top-left corner
  display.println(F("Vivek!"));
   
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!");
    return;
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String message;
    String inputParam;
    if (request->hasParam(PARAM_INPUT_1)) {
      message = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
       
      
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,1);             // Start at top-left corner
  display.println(F(message));

    }
    else {
      message = "No message sent";
      inputParam = "none";
    }
    display.println(F(message));
   
  request->send(200, "text/html", index_html);
  });
  server.onNotFound(notFound);
  server.begin();
}

void loop() {

}