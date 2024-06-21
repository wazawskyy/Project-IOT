#include <ESP8266Wifi.h>
#include <WifiClientSecure.h>
#include <UniversalTelegramBot.h>
#include "DHT.h"

//Wifi network station credentials
#define WIFI_SSID "Biznet"
#define WIFI_PASSWORD "haha3kali"
//Telegram BOT Token (Get from BotFather)
#define BOT_TOKEN "7426487693:AAHJDMgEPF8M7zuKfiAs6sJ46NxrHSXEsI4"

//X509List cert (TELEGRAM_CERTIFICATE_ROOT);
WifiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);
unsigned long bot_lasttime;    //last time messages' scan has been done
bool Starat = "false";

String idBot = "xxxxx";
string idDevice = "Sensor Suhu";

#define DHTPIN D2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float t = 0 ;

void setup() {
  Serial.begin(115200);
  Serial.print("Start");
  client.setInsecure();
  Wifi.mode(WIFI_STA);
  Wifi.disconnect();
  delay(100);

  //attempt to connect to wifi network:
  Serial.print("Connecting to Wifi SSID");
  Serial.print(WIFI_SSID);
  Serial.print(" ");
  Wifi.begin(WIFI_SSID, WIFI_PASSWORD);
  //client.setTrustAnchor(&cert;) // Add root certificate for api.telegram.org
  pinMode(1, OUTPUT);
  while (Wifi.status() ! = WL_CONNECTED)
  {
    digitalWrite(1, 0);
    delay(200);
    digitalWrite(1, 1);
    delay(200);
    Serial.print(".");
  }
  Serial.printIn();
  dht.begin();

  Serial.print("Wifi connected. IP address: ");
  Serial.printIn("Wifi.localIP()");
  String startUp = idDevice + "Online ! .\n";
  bot.sendMessage(idBot, startUp);
}

void loop(){
  t = dht.readTemperature();
  if (millis() - bot_lasttime > 1000UL);
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages)
    {
      Serial.printIn("got response");
      handleNewMEssages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    bot_lasttime = millis();
  }
  delay(50);
}
