void buttonRoutine()
{
    // // if (digitalRead(USR0_BTN) == LOW)
    // if (digitalRead(USR0_BTN) == HIGH)
    // {
    //     Serial.println("BUTTON USER_0 PUSHED");

    //     MPUcalibrate();
    // }
    // if (digitalRead(USR1_BTN) == LOW)
    if (digitalRead(USR1_BTN) == HIGH)
    {
        Serial.println("BUTTON USER_1 PUSHED");

        MPUcalibrate();
    }
}