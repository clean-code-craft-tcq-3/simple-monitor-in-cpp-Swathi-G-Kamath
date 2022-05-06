#include <assert.h>
#include <iostream>
using namespace std;

class Battery{
    public:
        float temperature,soc,chargeRate;
    bool checkTempIsInRange(float t);
    bool checkSocIsInRange(float s);
    bool checkChargeRateIsInRange(float c);
    bool checkBatteryIsOk(float t,float s ,float c);
};

class NewBattery:public Battery
{  
    public:
    bool checkTempIsInRange(float temperature)
    {
        if(temperature < 0 || temperature > 45)
            return false;
        else 
        return true;
    }
    bool checkSocIsInRange(float soc)
    {
        if(soc < 20 || soc > 80)
            return false;
        else
            return true;        
    }
    bool checkChargeRateIsInRange(float chargeRate)
    {
        if(chargeRate>0.8)
            return false;
        else 
            return true;
    }
    bool checkBatteryIsOk(float t,float s ,float c)
    {
        return(checkTempIsInRange(t)&&checkSocIsInRange(s)&&checkChargeRateIsInRange(c));
    }
};

void checkBattery()
{
    NewBattery n;
    assert(n.checkBatteryIsOk(0,19,1)==false);
    assert(n.checkBatteryIsOk(1,21,1)==false);
    assert(n.checkBatteryIsOk(1,81,0.7)==false); 
    assert(n.checkBatteryIsOk(0,79,0.7)==false);
    assert(n.checkBatteryIsOk(1,21,0.7)==true);
    assert(n.checkBatteryIsOk(44,79,0.7)==true);
}

int main() 
{
   checkBattery();
}
