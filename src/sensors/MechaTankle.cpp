#include "MechaTankle.h"
#include "network/network.h"
#include "utils.h"
#include "GlobalVars.h"

void MechaTankle::motionSetup(){
    m_Logger.info("Connected to MechaTA");
    working = true;
    configured = true;

}

void MechaTankle::motionLoop()
{
    hadData = true;
    
    Quat quat = imuA.getQuat(1);
    quaternion.set(quat.x,quat.y,quat.z,quat.w);
    quaternion *= sensorOffset;

            if (!OPTIMIZE_UPDATES || !lastQuatSent.equalsWithEpsilon(quaternion))
            {
                newData = true;
                lastQuatSent = quaternion;
            }
}


void MechaTankle::sendData()
{
    if (newData)
    {
        newData = false;
        Network::sendRotationData(&quaternion, DATA_TYPE_NORMAL, calibrationAccuracy, sensorId);
    }
}
void MechaTankle::startCalibration(int calibrationType){

}