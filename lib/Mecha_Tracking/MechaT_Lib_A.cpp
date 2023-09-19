#include "MechaT_Lib_A.h"

//htm

void HVecA::HipVec(double L1,double L2,double A,double B, double L, double M, double K, double* vx, double* vy, double* vz){
    //LMK is origin values, L1 length of rod 1, L2 length of rod 2, A,B is angles of pot a,b, vx vy and vz are output vector
    double x1 = 0;
    double y1 = 0;
    double z1 = 0;
    double x1r = 0;
    double x3 = 0;
    double y3 = 0;
    double z3 = 0;
    double x2 = 0;
    double y2 = 0;
    double Jh = 0;
    double Ih = 0;

    //endpodouble one:
    x1r = (L1* cos(Rad(A)));
    x1 = ((ceil((L1* cos(Rad(A))) * 100) / 100)+L);
    y1 = M;
    z1 = ((ceil((L1* sin(Rad(A))) * 100) / 100)+K);
    // endpodouble 2 on plane 2:
    x2 = ceil((L2* sin(Rad(B)) + L1) * 100) / 100;
    y2 = ceil((L2* cos(Rad(B))) * 100) / 100;
    //conversion from planes:
    Ih = (x1 / L2);
    Jh = (1);
    // Z3
    z3 = ceil((x2* sin(Rad(A))) * 100) / 100;
    // prdoubleing
    x3 = (((Ih * x2)  * 100) / 100);
    y3 = (((Jh * y2)  * 100) / 100);
    *vx = x3;
    *vy = y3;
    *vz = z3;
}

float HVecA::floatmap(float x, float in_min, float in_max, float out_min, float out_max){
      return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void HVecA::PTMRead(double P1,double* A1,double map){
    float angle1 = 0;
    // read the input on analog pins:
    double analogValue1 = analogRead(P1);
    // Rescale to potentiometer's voltage (from 0V to 3.3V):
    angle1 = floatmap(analogValue1, 0, 4095, 0, map);
    *A1 = angle1;
}

//nerot

double NerotA::ABV(double x, double y, double z, double w) {
    double B = ((acos(((x*y)+(z*w))/((sqrt((x*x)+(y*y)))*(sqrt((z*z)+(w*w)))))));
    // std::cout << B;
    return B;
}

double NerotA::QuadXY(double x, double y)
{
    double B = 0;

    if(x>0 and y>0 and y > x){
        B = 7;
    }
    else if (x>0 and y>0 and x > y){
        B = 8;
    }
    else if (x>0 and y<0 and x > abs(y)){ 
        B = 1;
    }
    else if (x>0 and y<0 and x < abs(y)){
        B = 2;
    }
    else if (x<0 and y<0 and abs(x) < abs(y)){
        B = 3;
    }
    else if (x<0 and y<0 and abs(x) > abs(y)){
        B = 4;
    }
    else if (x<0 and y>0 and abs(x) > y){
        B = 5;
    }
    else if (x<0 and y>0 and abs(x) < y){
        B = 6;
    }
    else if (x == 0){
        if(y>0){
            B = 10;
        }
        else if(y<0){
            B = 30;
        }
        else{
            B = 0;
        }
    }
    else if (y == 0){
        if(x>0){
            B = 20;
        }
        else if(x<0){
            B = 40;
        }
        else{
            B = 0;
        }
    }
    else if (abs(y) == abs(x)){
        if(x>0 and y>0){
            B = 15;
        }
        else if(x<0 and y<0){
            B = 35;
        }
        else if(x>0 and y<0){
            B = 25;
        }
        else if (x<0 and y>0){
            B = 45;
        }
        else{
            B = 0;
        }
    }
    return B;
    //std::cout << B;
}

//float buttonmap(float x){
//float B = 0;
//if (x>0){
//B = 1;
//} else{
//B = 0;
//}
//return B; 
//}
double JoyTestA::joyread( int maxmin, int pin, int angle){
    HVecA o;
    double x = analogRead(pin);
    double max = 1800+maxmin;
    double min = 1800-maxmin;
    double B = 0;
    if ((x > min) && (x < max)) {

        B = 0;
    }
    else{

        B = o.floatmap(analogRead(pin),0,4095,(-angle),angle);
    }  
    return B;
}


//int xValue = joymap(100,36,45);
//int yValue = joymap(100,39,45);
//int button = buttonmap(analogRead(34));
//int xValue2 = joymap(100,27,45);
//int yValue2 = joymap(100,14,45);
//int button2 = buttonmap(analogRead(12));


double NerotA::ABVS(double x,double y,double z,double w){
    double B = 0;
    double Q1 = QuadXY(x,y);
    double Q2 = QuadXY(z,w);
    if (x!=0 and z!=0 and y!=0 and w!=0){
        double m1 = (y-0)/(x-0);
        double m2 = (w-0)/(z-0);
        B = (180/M_PI)*(atan((abs(((m1-m2)/(1+(m1*m2)))))));
    } 
    else{
        B= 0;
    }
    return B;
}

double NerotA::AngleXY(double x, double y){
    NerotA O;
    double BX = O.QuadXY(x,y);
    double B = 0;

    if (BX == 1){
        B = abs(45-(O.ABVS(x,y,1,-1)));
    }  
    else if(BX == 2){
        B = (O.ABVS(x,y,1,-1))+45;
    }
    else if(BX == 3){
        B = abs(45-(O.ABVS(x,y,-1,-1)))+90;
    }
    else if(BX == 4){
        B = (O.ABVS(x,y,1,-1))+135;
    }
    else if(BX == 5){
        B = abs(45-(O.ABVS(x,y,-1,1)))+180;
    }
    else if (BX == 6){
        B = (O.ABVS(x,y,-1,1))+225;
    }
    else if (BX == 7){
        B = abs(45-(O.ABVS(x,y,1,1)))+270;
    }
    else if (BX == 8){
        B = O.ABVS(x,y,1,1)+315;
    }
    else if (BX == 10){
        B = 270;
    }
    else if (BX == 20){
        B = 0;
    }
    else if (BX == 30){
        B = 90;
    }
    else if (BX == 40){
        B = 180;
    }
    else if (BX == 15){
        B = 315;
    }
    else if (BX == 25){
        B = 45;
    }
    else if (BX == 35){
        B = 135;
    }
    else if (BX == 45){
        B = 225;
    }
    else{
        B = 0;
    }
    return B;
}

//quat + imu

void EtoQA(double ze,double ye,double xe, double* x, double* y, double* z, double* w){

    //double c1 = 0;
    //double c2 = 0;
    //double c3 = 0;
    //double s1 = 0;
    //double s2 = 0;        
    //double s3 = 0;        
    //c1 = cos( xe / 2 );
    //c2 = cos( ye / 2 );
    //c3 = cos( ze / 2 );

    //s1 = sin( xe / 2 );
    //s2 = sin( ye / 2 );
    //s3 = sin( ze / 2 );

    //double c1c2 = c1*c2;
    //double s1s2 = s1*s2;
    //*w =c1c2*c3 - s1s2*s3;
  	//*x =c1c2*s3 + s1s2*c3;
	//*y =s1*c2*c3 + c1*s2*s3;
	//*z =c1*s2*c3 - s1*c2*s3;

    double cr = cos(xe * 0.5);
    double sr = sin(xe * 0.5);
    double cp = cos(ye * 0.5);
    double sp = sin(ye * 0.5);
    double cy = cos(ze * 0.5);
    double sy = sin(ze * 0.5);

    
    *w = cr * cp * cy + sr * sp * sy;
    *x = sr * cp * cy - cr * sp * sy;
    *y = cr * sp * cy + sr * cp * sy;
    *z = cr * cp * sy - sr * sp * cy;

}

void MechaLibA::EtoQ(double X1,double Y1,double Z1, double* X, double* Y, double* Z, double* W){
    double x1,y1,z1,cX,cY,cZ,sX,sY,sZ;

    x1 = Rad(X1);
    y1 = Rad(Y1);
    z1 = Rad(Z1);

    cX = cos(x1 / 2);
    cY = cos(y1 / 2);
    cZ = cos(z1 / 2);
    sX = sin(x1 / 2);
    sY = sin(y1 / 2);
    sZ = sin(z1 / 2);

    *W = cX * cY * cZ - sX * sY * sZ;
    *Y = cY * cZ * sX + cX * sY * sZ;
    *Z = cX * cZ * sY + cY * sX * sZ;
    *X = cX* cY * sZ - cZ * sX * sY;

}

Quat MechaLibA::getQuat(int16_t k){
    MechaLibA mlb;
    NerotA rot;
    HVecA vec;
    Quat Q;
    JoyTestA J;
    int16_t rX1, rY1, rZ1;
    double x1, y1, z1, w1;
    x1 = y1 = z1 = w1 = 0;
    double P1,P2,P3,P4;
    double vx1,vy1,vz1,vy2,vx2,vz2;
    double XE,YE,ZE;
    double x, y, z, w;
    x = y = z = w = 0;

    double rX, rY, rZ;

    if (k == 0){
        //imu.getRotation(&rX,&rY,&rZ);

        vec.PTMRead(36,&P1,180);
        vec.PTMRead(39,&P2,180);

        vec.HipVec(5,5,P1,P2,0,0,0,&vx1,&vy1,&vz1);

        double vx2 = sqrt(((vx1*vx1)+(vy1*vy1)));
        double vy2 = vz1;

        double rZE = rot.AngleXY(vx1,vy1);
        double rXE = rot.AngleXY(vx2,vy2);

        XE = Rad(rXE-360);
        YE = Rad(0);
        ZE = Rad(rZE);


        mlb.EtoQ(XE,YE,ZE,&x1,&y1,&z1,&w1);

    }
    else if(k == 1){

        vec.PTMRead(33,&P4,170);
        P1 = J.joyread(150,36,70);
        P2 = J.joyread(150,39,70);
        vec.PTMRead(35,&P3,360);
        double XE = P1+rY1;
        double YE = P3+rZ1;
        double ZE = -P2-P4+rX1;
        
        mlb.EtoQ(XE,YE,ZE,&x1,&y1,&z1,&w1);
    }
    else if(k == 2){
        P1 = J.joyread(150,36,70);
        P2 = J.joyread(150,39,70);
        vec.PTMRead(35,&P3,360);
        double XE = P1+rY1;
        double YE = P3+rZ1;
        double ZE = -P2+rX1;
        
        mlb.EtoQ(XE,YE,ZE,&x1,&y1,&z1,&w1);
    }

    x = x1;
    y = y1;
    z = z1;
    w = w1;
    

  return Quat(x,y,z,w);

//scale * x, scale * y, scale * z, scale * w

}