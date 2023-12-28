int32_t getWiFiChannel(const char *ssid)
{
    Serial.println("STARTING NETWORK SCAN ");
    if (int32_t n = WiFi.scanNetworks())
    {
        for (uint8_t i = 0; i < n; i++)
        {

            if (!strcmp(ssid, WiFi.SSID(i).c_str()))
            {

                return WiFi.channel(i);
            }
        }
        Serial.print("DESIRED NETWORK NOT FOUND");
    }
    return 0;
}
void initWiFi()
{
    delay(500);
    WiFi.mode(WIFI_STA);
    int32_t channel = getWiFiChannel(WIFI_SSID);
    Serial.print("DESIRED NETWORK FOUND ON CHANNEL: ");
    Serial.println(channel);
    // WiFi.printDiag(Serial);
    // esp_wifi_set_promiscuous(true);
    // esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
    // esp_wifi_set_promiscuous(false);
    // WiFi.printDiag(Serial);
    Serial.println("WIFI INIT DONE");
}
// ----------------------------------------------------------------------------
// ESP-NOW handling
// ----------------------------------------------------------------------------
void initEspNow()
{
    delay(500);

    if (esp_now_init() != ESP_OK)
    {
        Serial.println("ESP NOW INIT FAIL");
        while (1)
            ;
    }
    else
    {
        Serial.println("ESP NOW INIT DONE");
    }
    memcpy(peerInterface.peer_addr, ESP_NOW_RECEIVER, 6);
    // peerInfo.ifidx = ESP_IF_WIFI_STA;
    // peerInterface.channel = 0; // uncomment if channel aquisition goes wrong
    peerInterface.encrypt = false;

    if (esp_now_add_peer(&peerInterface) != ESP_OK)
    {
        Serial.println("ESP NOW pairing failure");
        while (1)
            ;
    }
    else
    {
        Serial.println("ESP NOW PAIRING DONE");
    }
}
void ledInit()
{
    // PWM LED INIT
    ledcSetup(PWMledChannel, PWMfreq, PWMresolution); // configure LED PWM functionalitites
    ledcAttachPin(LED_BUILTIN, PWMledChannel);        // attach the channel to the GPIO to be
                                                      // pinMode(LED_BUILTIN, OUTPUT); // pin 2 on ESP32/ESP32-WROOM
}
void MPUinit()
{

    // MPU6050 INIT
    Serial.println("INTIALIZING MPU6050");
    byte mpuStatus = mpu.begin();
    Serial.print("MPU6050 STATUS: ");
    Serial.println(mpuStatus);
    while (mpuStatus != 0)
    {
        Serial.println("MPU6050 INIT FAILED. BAD STATUS. CHECK GPIO NUMBERS OF THE  I2C CONNECTION ");
    } // stop everything if could not connect to MPU6050
}
void buttonInit()
{
    // ACTIVATE PULLUPS AT YET UNUSED BUTTONS OF RAZOM PROJECTBOARDSFOR SAFETY PURPOSES
    // pinMode(USR0_BTN, INPUT_PULLUP);
    // pinMode(USR1_BTN, INPUT_PULLUP);
    pinMode(USR0_BTN, INPUT_PULLDOWN);
    pinMode(USR1_BTN, INPUT_PULLDOWN);
}