# Pico W Webserver to wake a computer remotely sending a short pulse on the motherboard power on button
<p align="center">
  <a href="https://skillicons.dev">
    <img src="https://skillicons.dev/icons?i=raspberrypi,c,vscode,cmake,html&perline=3" />
  </a>
</p>

## Screenshot of the webpage

![Website](https://i.imgur.com/n79rmdR.png)

## Build
Don't forget to add your WiFi credentials on the `main.c`
```
mkdir build
cmake -DPICO_BOARD=pico_w .. 
make
```