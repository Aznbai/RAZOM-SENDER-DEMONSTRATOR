
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
    // INCOMING DATA UNNOMALISED

    // int currTemp = round(mpu.getTemp());
    // dataObj.anX = round(mpu.getAngleX());         // angle x
    // dataObj.anY = round(mpu.getAngleY());         // angle y
    // dataObj.anZ = round(mpu.getAngleZ());         // angle z
    // dataObj.acX = round(mpu.getAccX() * 100);     // acceleration x
    // dataObj.acY = round(mpu.getAccY() * 100);     // acceleration y
    // dataObj.acZ = round(mpu.getAccZ() * 100);     // acceleration z
    // dataObj.gyX = round(mpu.getGyroX() * 10);     // gyro x
    // dataObj.gyY = round(mpu.getGyroY() * 10);     // gyro y
    // dataObj.gyZ = round(mpu.getGyroZ() * 10);     // gyro z
    // dataObj.aaX = round(mpu.getAccAngleX() * 10); // acc angle x
    // dataObj.aaY = round(mpu.getAccAngleY() * 10); // acc angle y

    // INCOMING DATA NOMALISED TO  BASE 1000

    dataObj.anX = constrain(round(mpu.getAngleX() * 12), -2000, 2000);      // angle x;
    dataObj.anY = constrain(round(mpu.getAngleY() * 12), -2000, 2000);      // angle y;
    dataObj.anZ = round(mpu.getAngleZ());                                   // angle z
    dataObj.acX = constrain((mpu.getAccX() * 250), -1000, 1000);            // acceleration x
    dataObj.acY = constrain((mpu.getAccY() * 250), -1000, 1000);            // acceleration y
    dataObj.acZ = constrain((mpu.getAccZ() * 250), -1000, 1000);            // acceleration z
    dataObj.gyX = constrain(round(mpu.getGyroX() * 3.74), -1000, 1000);     // gyro x
    dataObj.gyY = constrain(round(mpu.getGyroY() * 3.74), -1000, 1000);     // gyro y
    dataObj.gyZ = constrain(round(mpu.getGyroZ() * 3.74), -1000, 1000);     // gyro z
    dataObj.aaX = constrain(round(mpu.getAccAngleX() * 5.5), -1000, 1000);  // acc angle x aka ROLL
    dataObj.aaY = constrain(round(mpu.getAccAngleY() * 11.4), -1000, 1000); // acc angle y aka PITCH

    Serial.print(">AngleX: ");
    Serial.print(dataObj.anX);
    Serial.println();
    Serial.print(">AngleY: ");
    Serial.print(dataObj.anY);
    Serial.println();
    Serial.print(">AngleZ: ");
    Serial.println(dataObj.anZ);
    Serial.println();

    Serial.print(">AccX: ");
    Serial.print(dataObj.acX);
    Serial.println();
    Serial.print(">AccY: ");
    Serial.print(dataObj.acY);
    Serial.println();
    Serial.print(">AccZ: ");
    Serial.println(dataObj.acZ);
    Serial.println();

    Serial.print(">GyroX: ");
    Serial.print(dataObj.gyX);
    Serial.println();
    Serial.print(">GyroY: ");
    Serial.print(dataObj.gyY);
    Serial.println();
    Serial.print(">GyroZ: ");
    Serial.println(dataObj.gyZ);
    Serial.println();

    Serial.print(">Roll: ");
    Serial.print(dataObj.aaX);
    Serial.println();
    Serial.print(">Pitch: ");
    Serial.print(dataObj.aaY);
    Serial.println();
}