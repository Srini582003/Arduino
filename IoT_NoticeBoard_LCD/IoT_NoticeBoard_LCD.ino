
#include <ESP8266HTTPClient.h>
#include<ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
int wifi = D0; // WiFi Onboard LED
const char* ssid = "Vignesh";
const char* password = "20032003";
String api = "cd8635f548c86e82888063a04cfea107bc4d9fe7"; // Visit https://iot.webumblebees.com for API Key
String value;
void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(wifi, OUTPUT);
  digitalWrite(wifi, HIGH); // OFF
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    lcd.setCursor(0, 0);
    lcd.print("Connecting To");
    lcd.setCursor(0, 1);
    lcd.print(ssid);
    Serial.println("Connecting to WiFi");
    digitalWrite(wifi, LOW); // ON
    delay(500);
    lcd.clear();
    digitalWrite(wifi, HIGH); // OFF
    delay(500);
  }
  digitalWrite(wifi, LOW); // Permanent WiFi LED ON
  lcd.setCursor(0, 0);
  lcd.print("Connected To");
  lcd.setCursor(0, 1);
  lcd.print(ssid);
  delay(2000);
}
void loop()
{
  HTTPClient http;
  http.begin("https://iot.webumblebees.com/script.php?api=" + api); // Read Status from Cloud
  int httpCode = http.GET();
  if (httpCode > 0)
  {
    value = http.getString();
    Serial.println(value);
    techVegan(value);
    delay(1000); // Delay should not be less than 1000
  }
  else
  {
    techVegan("NO INTERNET");
    delay(1000); // Delay should not be less than 1000
  }
}
void techVegan(String message)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("IoT NOTICE BOARD");
  lcd.setCursor(0, 1);
  lcd.print(message);
  delay(2000);
}
