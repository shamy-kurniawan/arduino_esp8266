#include <TM1638.h>
TM1638 module(8, 9, 10);

void setup() {
  module.setDisplayToString("READY");
}

byte buttons, oldbuttons, page;
boolean changed;
unsigned long milstart;

void loop() {
buttons = module.getButtons();
  if (buttons != 0) {
    if (buttons != oldbuttons) {
      oldbuttons = buttons;
      page = buttons;
    switch (page) {
        case 1:
          module.setDisplayToString("satu    ", 0, 0);
          break;
        case 2:
          module.setDisplayToString("dua     ", 0, 0);
          break;
        case 4:
          module.setDisplayToString("tiga    ", 0, 0);
          break;    
        case 8:
          module.setDisplayToString("Gear spd", 0, 0);
          break;
        case 16:
          module.setDisplayToString("Engine  ", 0, 0);
          break;
        case 32:
          module.setDisplayToString("Fuel pct", 0, 0);
          break;
      }

      changed = true;
      milstart = millis();
    }
  }
}
