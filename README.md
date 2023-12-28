# RAZOM-SENDER-DEMONSTRATOR
The MVP sender node implementing ESP-NOW communication with the WiFi/MIDI  gateway

THANKS RO M1CR0LAB FOR CORRECT GATEWAY IMPEMENTATION
more here https://github.com/m1cr0lab-esp32/esp-now-network-and-wifi-gateway

this ESP-NOW sender sketch allows for reliable packet delivery to receiver, which itself is connected to a wifi network.
when working with barebone ESP32-WROOM module: avoid using default I2C pins on  ESP32: baseboard pcbs unlike bigger dev board only work with external resistors an capacitors if default i2c pins are used during boot up

in order for this firmware to work on a barebone module make sure that SCL // SDA pins are connected as follows:
SDA - pin "IO18"
SCL - pin "IO19"

tested with ESP32-WROOM-DEVKIT-V1 as well as Razom sender node board
dont forget to press and hold BOOT button before upload

this sketchfirmware coresponds with other one named TEST-ESP-NOW-WIFI-RECEIVER
serial output is compatible with "teleplot" plotter
green led is connected via 150R resistor to GPIO2
notice that brownout detector is supressed in order to increase compatibility with various ESP32 ESP-WROOM-32 modules