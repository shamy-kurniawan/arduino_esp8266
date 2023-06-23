#include <WS2812FX.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,4);
#define SwitchPin1 3  //D7
#define SwitchPin2 13   //RX
#define LED_COUNT 144
#define LED_PIN D4

int toggleState_1 = 1;
int toggleState_2 = 1;

#define TIMER_MS 5000
WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);

unsigned long last_change = 0;
unsigned long now = 0;

void setup() {
  pinMode(SwitchPin1, INPUT_PULLUP);
  pinMode(SwitchPin2, INPUT_PULLUP);
  lcd.init();
  lcd.backlight();
  ws2812fx.init();
  ws2812fx.setBrightness(255);
  ws2812fx.setSpeed(1000);
  ws2812fx.setColor(0x007BFF);
  ws2812fx.setMode(FX_MODE_STATIC);
  ws2812fx.start();
}

void loop(){
    ws2812fx.service();
    saklar(); 
  }

void saklar(){
     if (digitalRead(SwitchPin1) == LOW){
        delay(200);
        ws2812fx.setMode((ws2812fx.getMode() + 1));
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Mode");
        lcd.setCursor(0,1);
        lcd.print(ws2812fx.getModeName(ws2812fx.getMode()));
        }
     else if (digitalRead(SwitchPin2) == LOW){
        delay(200);
        ws2812fx.setMode((ws2812fx.getMode() - 1));
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Mode");
        lcd.setCursor(0,1);
        lcd.print(ws2812fx.getModeName(ws2812fx.getMode()));
        }
      }   
     
