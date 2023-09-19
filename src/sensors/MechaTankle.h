#ifndef SENSORS_MECHATSENSOR_H
#define SENSORS_MECHATSENSOR_H

#include "sensor.h"
#include "MechaT_Lib_A.h"
#include "BMI160.h"

class MechaTankle : public Sensor
{
public:
    MechaTankle(uint8_t id, uint8_t address, float rotation) : Sensor("MechaTankle", IMU_MechaTankle, id, address, rotation){};
    ~MechaTankle()override = default;
    void motionSetup() override final;
    void motionLoop() override final;
    void sendData() override final;
    void startCalibration(int calibrationType) override final;
private:
    MechaLibA imuA{};
};

#endif