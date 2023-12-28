
void MPUcalibrate()
{
    // MPU6050 CALIBRATION
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println("DONT MOVE! RECALIBRATION IN 1 SECOND");
    for (byte i = 0; i < 20; i++)
    {
        ledcWrite(PWMledChannel, 255);
        delay(5);
        ledcWrite(PWMledChannel, 0);
        delay(5);
    }
    mpu.calcOffsets(true, true); //  mpu.calcOffsets(); // gyro and acc
    Serial.println("CALIBRATION DONE");
}
void MPUgetData()
{
    mpu.update();
    // int currTemp = round(mpu.getTemp());
    dataObj.anX = round(mpu.getAngleX());         // angle x
    dataObj.anY = round(mpu.getAngleY());         // angle y
    dataObj.anZ = round(mpu.getAngleZ());         // angle z
    dataObj.acX = round(mpu.getAccX() * 100);     // acceleration x
    dataObj.acY = round(mpu.getAccY() * 100);     // acceleration y
    dataObj.acZ = round(mpu.getAccZ() * 100);     // acceleration z
    dataObj.gyX = round(mpu.getGyroX() * 10);     // gyro x
    dataObj.gyY = round(mpu.getGyroY() * 10);     // gyro y
    dataObj.gyZ = round(mpu.getGyroZ() * 10);     // gyro z
    dataObj.aaX = round(mpu.getAccAngleX() * 10); // acc angle x
    dataObj.aaY = round(mpu.getAccAngleY() * 10); // acc angle y
}