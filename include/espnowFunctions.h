void espNowSendData()
{
    // ESP-NOW SEND MSG
    esp_err_t result = esp_now_send(ESP_NOW_RECEIVER, (uint8_t *)&dataObj, sizeof(dataObj));
    if (result == ESP_OK)
    {
        Serial.print(millis());
        Serial.print(" DEMO NODE ID:");
        Serial.print(NODE_ID);
        Serial.print(" DONE SENDING ");
    }
    else
    {
        Serial.print("SEND ERR");
    }
    Serial.print(sizeof(dataObj));
    Serial.print(" BYTES ON WIFI CH: ");
    Serial.print(WiFi.channel());
    Serial.print(" TO MAC ADR: ");

    for (int i = 0; i < 6; i++)
    {
        Serial.print(ESP_NOW_RECEIVER[i], HEX);
        Serial.print(":");
    }
    Serial.println();
}