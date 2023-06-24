#include <ESP8266WiFi.h>
#include <IRCClient.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#define IRC_BUFSIZE  32  
#define ssid         "You_SSID"                 //Disamakan dengan pengaturan Hotspot di Android atau AP kalian
#define password     "You_Pass_SSID"                 //Disamakan dengan pengaturan Hotspot di Android atau AP kalian

#define IRC_SERVER   "You_IRC_Server"             //Alamat Server irc atau server ZNC
#define IRC_PORT     2323                       //Port IRC atau port ZNC
#define IRC_NICKNAME randNumber
#define IRC_USER     "mobile"                     //Username ZNC
#define REPLY_TO     "shamy"                      //Nick pada IRC yg dapat memberi perintah
#define IRC_PASS     "passIRCServer"                    //Passwd IRC server atau ZNC server
const String Channel = "pekalongan";                   //Alamat channel IRC
String ircChannel = "";
long randNumber;
char randNick[50];

WiFiClient wiFiClient;
IRCClient client(IRC_SERVER, IRC_PORT, wiFiClient);

void setup() {
  Serial.begin(115200);
  lcd.init();  
  lcd.init();
  lcd.backlight();
  
  delay(100);
  Serial.println("");
  Serial.print("Menghubungi Wifi ");
  Serial.println(ssid);
 
  WiFi.mode(WIFI_STA);
  WiFi.hostname("Mobile");
  WiFi.begin(ssid, password);
  IPAddress ip(192, 168, 10, 77);                     //ini alamat IP local, biar dapat diakses lewat Aplikasi Android atau PC
  IPAddress dns(192, 168, 10, 1);
  IPAddress gateway(192, 168, 10, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.config(ip, dns, gateway, subnet);
     
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi terhubung");
  Serial.println("Alamat IP: ");
  Serial.println(WiFi.localIP());
  WiFi.printDiag(Serial);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("WiFi");
  lcd.setCursor(0,1);
  lcd.print("Connected");
  
  ircChannel = "#" + Channel;

  client.setCallback(callback);
  client.setSentCallback(debugSentCallback);
}

void loop() {
     random_nick();
     cek_koneksi();
     client.loop();
}

void random_nick(){
     unsigned long randNumber = random(1000);
     sprintf(randNick, "ESP%lu", randNumber);
    }

void cek_koneksi(){
    if (!client.connected()) {
    Serial.println("Menghubungi IRC server");

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Connecting");
    lcd.setCursor(0,1);
    lcd.print("to IRC Server");
  
    if (client.connect(randNick, IRC_USER, IRC_PASS)) {
      Serial.println("terhubung");

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Status");
      lcd.setCursor(0,1);
      lcd.print("Online Server");
      
      delay(5000);
      join_channel();
      } else {
      Serial.println("Konkesi gagal, mengulang dalam 5 detik");      //mencoba kembali dalam 5 detik

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Koneksi gagal");
      lcd.setCursor(0,1);
      lcd.print("Ulang pd 5 detik");
  
      delay(5000);
      }
    return;
  }
}

void join_channel(){
       if (client.connected()) {
       Serial.println("Join Channel");
       client.sendRaw("JOIN " + ircChannel);

       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Join Server");
       lcd.setCursor(0,1);
       lcd.print("JOIN " + ircChannel);
       }
     }


void callback(IRCMessage ircMessage) {
    // PRIVMSG ignoring CTCP messages
  if (ircMessage.command == "PRIVMSG" && ircMessage.text[0] != '\001') {
    String message("<" + ircMessage.nick + "> " + ircMessage.text);
    Serial.println(message);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Pesan");
    lcd.setCursor(0,1);
    lcd.print(message);

    if (ircMessage.nick == REPLY_TO) {
        if(ircMessage.text == "!HELP"){

           lcd.clear();
           lcd.setCursor(0,0);
           lcd.print("Pesan");
           lcd.setCursor(0,1);
           lcd.print(ircMessage.text);
           
           client.sendMessage(ircMessage.nick, "Hi " + ircMessage.nick + "! Perintahnya adalah :");
           client.sendMessage(ircMessage.nick, "UNLOCK");
           client.sendMessage(ircMessage.nick, "LOCK");
           client.sendMessage(ircMessage.nick, "ACC");
           client.sendMessage(ircMessage.nick, "KONTAK");
           client.sendMessage(ircMessage.nick, "STATER");
           client.sendMessage(ircMessage.nick, "KONTAK OFF");
           client.sendMessage(ircMessage.nick, "ECU ON");
           client.sendMessage(ircMessage.nick, "ECU OFF");
           client.sendMessage(ircMessage.nick, "AC ON");
           client.sendMessage(ircMessage.nick, "AC OFF");
           client.sendMessage(ircMessage.nick, "DOME ON");
           client.sendMessage(ircMessage.nick, "DOME OFF");
        }else{
         if(ircMessage.text == "UNLOCK"){
           client.sendMessage(ircMessage.nick, "Hi " + ircMessage.nick + "! Pintu sekarang tidak terkunci");
         }else{
         if(ircMessage.text == "LOCK"){
           client.sendMessage(ircMessage.nick, "Hi " + ircMessage.nick + "! Pintu sekarang terkunci");
         
        }else{
         if(ircMessage.text == "ACC"){
           client.sendMessage(ircMessage.nick, "Hi " + ircMessage.nick + "! Kontak ACC Aktif");
         
        }else{
         if(ircMessage.text == "KONTAK"){
           client.sendMessage(ircMessage.nick, "Hi " + ircMessage.nick + "! Kontak Ready, mesin siap menyala");
         
        }else{
         if(ircMessage.text == "STATER"){
           client.sendMessage(ircMessage.nick, "Hi " + ircMessage.nick + "! Mesin menyala");
         
        }else{
         if(ircMessage.text == "KONTAK OFF"){
           client.sendMessage(ircMessage.nick, "Hi " + ircMessage.nick + "! Mesin OFF, Kelistrikan OFF");
         
        }else{
         if(ircMessage.text == "ECU ON"){
           client.sendMessage(ircMessage.nick, "Hi " + ircMessage.nick + "! Electronic Control Unit ON");
         
        }else{
         if(ircMessage.text == "ECU OFF"){
           client.sendMessage(ircMessage.nick, "Hi " + ircMessage.nick + "! Electronic Control Unit OFF");
         
         }else{
         if(ircMessage.text == "DOME ON"){
           client.sendMessage(ircMessage.nick, "Hi " + ircMessage.nick + "! Lampu dalam menyala");
         
         }else{
         if(ircMessage.text == "DOME OFF"){
           client.sendMessage(ircMessage.nick, "Hi " + ircMessage.nick + "! Lampu dalam padam");
         
         }else{
         if(ircMessage.text == "AC ON"){
           client.sendMessage(ircMessage.nick, "Hi " + ircMessage.nick + "! Pendingin Ruangan Menyala");
         
         }else{
         if(ircMessage.text == "AC OFF"){
           client.sendMessage(ircMessage.nick, "Hi " + ircMessage.nick + "! Pendingin Ruangan padam");
         
         }else{
         if(ircMessage.text == "DUSK ON"){
           client.sendMessage(ircMessage.nick, "Hi " + ircMessage.nick + "! Lampu senja menyala");
         
         }else{
         if(ircMessage.text == "DUSK OFF"){
           client.sendMessage(ircMessage.nick, "Hi " + ircMessage.nick + "! Lampu senja padam");
         
        }}}}}}}}}}}}}}}}
                 return;
    }
  Serial.println(ircMessage.original);
}

void debugSentCallback(String data) {
  Serial.println(data);
  }
