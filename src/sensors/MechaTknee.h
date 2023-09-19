#ifndef SENSORS_MECHATSENSOR_H1
#define SENSORS_MECHATSENSOR_H1

#include "sensor.h"
#include "MechaT_Lib_B.h"
#include "BMI160.h"

class MechaTknee : public Sensor
{
public:
    MechaTknee(uint8_t id, uint8_t address, float rotation) : Sensor("MechaTknee", IMU_MechaTknee, id, address, rotation){};
    ~MechaTknee()override = default;
    void motionSetup() override final;
    void motionLoop() override final;
    void sendData() override final;
    void startCalibration(int calibrationType) override final;
private:
    MechaLibB imuB{};
    BMI160 BMI1{};

};

#endif