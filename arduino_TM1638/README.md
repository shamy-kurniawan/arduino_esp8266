## Menggunakan Arduino dan modul TM1638 8x7segment, 8xLED dan 8xPush button dengan TM1638.h sebagai acuan library-nya. 

- Menggunakan library

  {
  #include <TM1638.h>
   }
   
- Menentukan pin DIO,CLK,STD
 

Connections to MCU: 

	* GPIO = STB = Strobe
	* GPIO  = CLK  = Clock
	* GPIO = DIO = Data input / output
	* GND
	* VCC 

    TM1638 module(8, 9, 10);

- Menulis karakter pada 7segment contoh :
  
  module.setDisplayToString("READY");
  
- Button  
  
  module.getButtons();
  
  set button dengan kelipatan.1,2,4,8,16,32,64,128. 
  
  1 untuk push 1
  
  2 untuk push 2
  
  4 untuk push 3
  
  8 untuk push 4
  
  16 untuk push 5 dst.... 
  
- Led  
  
  module.setLED(1,0); --- menyalakan led 1
  
  module.setLED(1,1); --- menyalakan led 2
  
  module.setLED(1,2); --- menyalakan led 3
  
  module.setLED(1,3); --- menyalakan led 4
  

![Blynk Banner](https://github.com/shamy-kurniawan/arduino_esp8266/arduino_TM1638/blob/main/TM1638.jpg)


