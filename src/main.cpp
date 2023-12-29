// ----------------------------------------------------------------------------
// RAZOM ESP-NOW  MVP SENDER
// ----------------------------------------------------------------------------
// This ESP-NOW sender sketch allows for reliable packet delivery to the Razom receiver, which acts as a gateway, and is itself connected to a wifi network and produces MIDI output.
//
// When working with barebone ESP32-WROOM modules like : avoid using default I2C pins on  ESP32:
// baseboard pcbs unlike bigger dev board only work with external resistors an capacitors if default i2c pins are used during boot up
//
// in order for this sketch to work on a barebone module  make sure that SCL // SDA pins are connected as follows SDA on pin "IO18", SCL on pin "IO19"
// tested with ESP32-WROOM-DEVKIT-V1 as well as motion capture node prototype
// dont forget to press and hold BOOT button before upload
// this sketch coresponds with other one named TEST-ESP-NOW-WIFI-RECEIVER
// serial output is compatible with "teleplot" plotter
// green led is connected via 150R resistor to GPIO2
//
// notice that brownout detector is supressed in order to increase compatibility with various ESP32 ESP-WROOM-32 modules
// ----------------------------------------------------------------------------
// THANKS RO M1CR0LAB FOR CORRECT GATEWAY SETUP IMPEMENTATION
// more here https://github.com/m1cr0lab-esp32/esp-now-network-and-wifi-gateway
// ----------------------------------------------------------------------------
//
#include "soc/soc.h"          //for supression of brownout detector
#include "soc/rtc_cntl_reg.h" //for supression of brownout detector

#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
// #include <esp_wifi.h>
// #include <HardwareSerial.h>
#include "Wire.h"
#include <MPU6050_light.h>

// ADAPT FOLLOWING PARAMETERS
//
#define NODE_ID 0
#define LED_BUILTIN 2
// #define USR0_BTN 4  // USER_0 button pin of razom shield
// #define USR1_BTN 19 // USER_1 button pin of razom shield
#define USR0_BTN 35 // USER_0 button pin of razom sender node
#define USR1_BTN 32 // USER_1 button pin of razom sender node
//
constexpr char WIFI_SSID[] = "ESP-HUB";
constexpr uint8_t ESP_NOW_RECEIVER[] = {0x24, 0x62, 0xab, 0xf1, 0xea, 0xb4};
//
// PWM LED
const int PWMfreq = 5000;
const int PWMledChannel = 0;
const int PWMresolution = 8;
// UTILITY VARS
unsigned long timer = 0;
int sendDelay = 100;
// OBJ CONTAINING CURRENT MSG
typedef struct struct_message // Structure example to send data. Must match the receiver structure
{
  byte id = 0; // unique for each sender node
  int anX = 0; // angle x
  int anY = 0; // angle y
  int anZ = 0; // angle z
  int acX = 0; // acceleration x
  int acY = 0; // acceleration y
  int acZ = 0; // acceleration z
  int gyX = 0; // gyro x
  int gyY = 0; // gyro y
  int gyZ = 0; // gyro z
  int aaX = 0; // acc angle x
  int aaY = 0; // acc angle y
} struct_message;
struct_message dataObj; // Create an instance of struct_message to hold current msg data
//
MPU6050 mpu(Wire);
//
esp_now_peer_info_t peerInterface;
//
#include "initFunctions.h"
#include "MPUfuctions.h"
#include "buttonFuctions.h"
#include "espnowFunctions.h"
//
void setup()
{
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //    supression of brownout detector
  dataObj.id = NODE_ID;
  // Wire.begin(); // SDA SCL DEFAULT SETUP
  Wire.begin(18, 19); // SDA on pin "IO18", SCL on pin "IO19"
                      //^,
  Serial.begin(115200);
  // delay(2000);
  ledInit();
  buttonInit();
  MPUinit();
  MPUcalibrate();
  delay(250);
  mpu.update();
  delay(250);
  MPUcalibrate();
  initWiFi();
  initEspNow();
  Serial.println("DEMO NODE SETUP DONE!");
}

void loop()
{
  mpu.update(); // experimental mode: increase update rate. Extracted from the MPUgetData function.
  if (millis() - timer > sendDelay)
  {
    timer = millis();
    MPUgetData();
    espNowSendData();
  }
  buttonRoutine();
}