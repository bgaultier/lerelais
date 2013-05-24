lerelais
========

This is a connected Arduino mounted by a relay shield which can swith on or off the appliances remotely.
This project is powered by an [Arduino Ethernet](http://arduino.cc/en/Main/ArduinoBoardEthernet) and a [Relay shield](http://www.seeedstudio.com/depot/relay-shield-p-693.html).

![lerelais](https://raw.github.com/bgaultier/lerelais/master/lerelais.png)

Installation
------------

1. Fork this project
2. Move it to your Arduino sketchbook
3. Open your favorite Arduino IDE
4. Modify `myapikey` line 29 in `lerelais.ino`, choose a random alphanumeric string. For instance:


```ruby
String myapikey = "xqwr2hrp5r";
```

5. Upload the sketch to your Arduino
6. Connect your Arduino mounted with the relay shield to your local network
7. Open your browser and enter the URL : http://<arduino-ipaddress>/?action=on&apikey=xqwr2hrp5r
8. If you are using an iOS device, you can also add a direct icon by touching _Add to Home Screen_.

![iOS home screen](https://raw.github.com/bgaultier/lerelais/master/homescreen.png)

9. Enjoy a freshly-brewed coffee 

License
-------

The code is fucking public domain.
http://creativecommons.org/publicdomain/zero/1.0/
