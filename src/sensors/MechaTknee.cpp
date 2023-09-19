#include "MechaTknee.h"
#include "network/network.h"
#include "utils.h"
#include "GlobalVars.h"

void MechaTknee::motionSetup(){
    m_Logger.info("Connected to MechaTB");
    working = true;
    configured = true;
}

void MechaTknee::motionLoop()
{
hadData = true;

    Quat quat = imuB.getQuat(2);
    quaternion.set(quat.x,quat.y,quat.z,quat.w);
    quaternion *= sensorOffset;

            if (!OPTIMIZE_UPDATES || !lastQuatSent.equalsWithEpsilon(quaternion))
            {
                newData = true;
                lastQuatSent = quaternion;
            }
}

void MechaTknee::sendData()
{
    if (newData)
    {
        newData = false;
        Network::sendRotationData(&quaternion, DATA_TYPE_NORMAL, calibrationAccuracy, sensorId);
    }
}
void MechaTknee::startCalibration(int calibrationType){

}