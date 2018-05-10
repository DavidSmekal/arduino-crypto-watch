# arduino-crypto-watch

A simple Arduino project that retrieves the price of a Cryptocoin from Coinmarketcap.com, and shows the price of it on an LCD screen.
It updates every 10 seconds, however the Coinmarketcap API's endpoints update every 5 minutes. 
Whenever the endpoint is updated on the Arduino, it will alert the user with a buzz sound and the LED will turn green if the price
has increased, or will turn red if the price has decreased.

Blue LED confirms the Arduino is connected to the internet.

## Items:
1. NodeMCU esp8266
2. 20x4 LCD IC2
3. RGB LED
4. Active Buzzer
5. 3 220 Ω resistors
6. Breadboard
7. Wires


### Fritzing Sketch:

![image](https://user-images.githubusercontent.com/17584457/39897786-b9560fee-5468-11e8-959c-9c2014d9c608.png)

### Picture of Setup:

![image](https://user-images.githubusercontent.com/17584457/39897600-d225a1ac-5467-11e8-959e-0a5fb3858f98.jpg)
