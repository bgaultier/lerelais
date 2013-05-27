lerelais
========

This is a connected Arduino mounted by a relay shield which can swith on or off appliances remotely.
This project is powered by an [Arduino Ethernet](http://arduino.cc/en/Main/ArduinoBoardEthernet) and a [Relay shield](http://www.seeedstudio.com/depot/relay-shield-p-693.html).

![lerelais](https://raw.github.com/bgaultier/lerelais/master/lerelais.png)

Installation
------------

* Fork this project
* Move it to your Arduino sketchbook
* Open your favorite Arduino IDE
* Modify `myapikey` line 29 in `lerelais.ino`, choose a random alphanumeric string. For instance:


```ruby
String myapikey = "xqwr2hrp5r";
```

* Upload the sketch to your Arduino
* Connect your Arduino mounted with the relay shield to your local network
* Open your browser and enter the URL : http://<arduino-ipaddress>/?action=on&apikey=xqwr2hrp5r
* If you are using an iOS device, you can also add a direct icon by touching _Add to Home Screen_.

![iOS home screen](https://raw.github.com/bgaultier/lerelais/master/homescreen.png)

* Enjoy a freshly-brewed coffee 

License
-------

The code is fucking public domain.
http://creativecommons.org/publicdomain/zero/1.0/
