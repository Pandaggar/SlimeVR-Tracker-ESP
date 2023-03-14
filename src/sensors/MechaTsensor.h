#ifndef SENSORS_MECHATSENSOR_H
#define SENSORS_MECHATSENSOR_H

#include "sensor.h"
#include "MechaT_Lib.h"


class MechaTsensor : public Sensor
{
public:
    MechaTsensor(uint8_t id, uint8_t address, float rotation) : Sensor("MechaT", IMU_MechaT, id, address, rotation){};
    ~MechaTsensor(){};
    void motionSetup() override final;
    void motionLoop() override final;
    void startCalibration(int calibrationType) override final;

private:
    MechaLib imu{};
};

#endif