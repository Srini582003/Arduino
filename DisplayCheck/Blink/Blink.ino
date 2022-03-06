 #include <LiquidCrystal_I2C.h>

int totalColumns = 16;
int totalRows = 2;

LiquidCrystal_I2C lcd(0x27, totalColumns, totalRows);

void setup(){
lcd.init(); 
lcd.backlight(); // use to turn on and turn off LCD back light
}

void loop()
{
lcd.setCursor(0, 0);
lcd.print("Microcontrollerslab");
lcd.setCursor(0,1);
lcd.print("I2C LCD tutorial");
delay(1000);
lcd.clear(); 
lcd.setCursor(0, 0);
lcd.print("Static text");
delay(1000);
lcd.setCursor(0,1);
lcd.print("I2C LCD tutorial");
delay(1000);
lcd.clear(); 
}
