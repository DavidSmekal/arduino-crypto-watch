/*

  Created by David Smekal
  May 10, 2018

*/

#include <CoinMarketCapApi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>


#define LED D0
#define redPin D7
#define greenPin D6
#define bluePin D5
#define buzzer D8

// set the LCD address to 0x3F for a 20 chars and 4 line display
LiquidCrystal_I2C lcd(0x3F, 20, 4);

// enter your own details here
const char * ssid     = "***************";
const char * password = "****************";

// change string to your choice of cryptocoin
const char * cryptoCoin = "Bitcoin";


int timerStart = 9;
double difference = 0.00;
double previousValue = 0.00;


WiFiClientSecure client;
CoinMarketCapApi api(client);


void setup() {

  // clear everything on the screen
  lcd.clear();

  //initializing pins
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(buzzer, OUTPUT);


  lcd.init();
  lcd.backlight();

  // if delay isn't before serial.begin, it doesn't work for some reason
  delay(1000);
  Serial.begin(115200);

  digitalWrite(LED, HIGH);


  Serial.println();
  Serial.println();
  lcd.setCursor(0, 1);
  lcd.print("Connecting to: ");

  lcd.setCursor(0, 2);
  lcd.print(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  int loop = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    // This section shows ellipses while it tries to connect
    lcd.setCursor(loop, 5);
    lcd.print(".");
    if (loop == 5) {
      loop = -1;
      lcd.setCursor(0, 5);
      lcd.print("      ");
    }
    loop++;

  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // changes LED to blue to show device is connected to wifi
  digitalWrite(bluePin, HIGH);
  digitalWrite(redPin, LOW);
  digitalWrite(LED, LOW);

  lcd.setCursor(1, 0);
  lcd.print("Connected to: ");
  lcd.setCursor(0, 1);
  lcd.print(ssid);

  lcd.clear();


  CMCTickerResponse response = api.GetTickerInfo(cryptoCoin, "USD");
  // need to set previous value early
  previousValue = response.price_usd;

  // show price on LCD board
  updatePrice();



}

// Even though we are refreshing every 10 seconds, the API updates every 5 minutes
void loop() {


  lcd.setCursor(19, 0);
  lcd.print(timerStart);
  delay(1000);
  timerStart--;

  if (timerStart == -1) {
    timerStart = 9;
    updatePrice();

  }


}

void updatePrice() {

  CMCTickerResponse response = api.GetTickerInfo(cryptoCoin, "USD");

  // plays a buzz sound everytime the value is updated.
  // Also, changes the LED color to red if price
  // has decreased, and changes the LED color to
  // green if price has increased.
  if (previousValue > response.price_usd) {
    difference = response.price_usd - previousValue;
    digitalWrite(redPin, HIGH);
    digitalWrite(bluePin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(buzzer, HIGH);

    lcd.setCursor(0, 3);
    lcd.print("Difference: " + String(difference));
    delay(1000);
    digitalWrite(buzzer, LOW);

  }
  else if (previousValue < response.price_usd) {
    difference = response.price_usd - previousValue;
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
    digitalWrite(redPin, LOW);
    digitalWrite(buzzer, HIGH);

    lcd.setCursor(0, 3);
    lcd.print("Difference: " + String(difference));
    delay(1000);
    digitalWrite(buzzer, LOW);
  }


  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(response.name);
  lcd.setCursor(0, 2);
  lcd.print("Price: " + String(response.price_usd));

  lcd.setCursor(0, 3);
  lcd.print("Difference: " + String(difference));

  previousValue = response.price_usd;

}

