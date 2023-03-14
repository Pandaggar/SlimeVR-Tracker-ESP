#include "MechaTsensor.h"
#include "network/network.h"
#include "utils.h"
#include "GlobalVars.h"

void MechaTsensor::motionSetup(){
#ifdef DEBUG_SENSOR

#endif
    m_Logger.info("Connected to MechaT");
    working = true;
    configured = true;
}

void MechaTsensor::motionLoop()
{
hadData = true;

    Quat quat = imu.getQuat();
    quaternion.set(quat.x, quat.y, quat.z, quat.w);
    quaternion *= sensorOffset;

            if (!OPTIMIZE_UPDATES || !lastQuatSent.equalsWithEpsilon(quaternion))
            {
                newData = true;
                lastQuatSent = quaternion;
            }
}


 void MechaTsensor::startCalibration(int calibrationType){

}