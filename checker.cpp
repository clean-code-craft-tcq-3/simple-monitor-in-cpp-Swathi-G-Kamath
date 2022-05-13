#include <assert.h>
#include <iostream>
using namespace std;

class Battery{
    public:
        float temperature,soc,chargeRate;
        bool checkTempIsInRange(float temp);
        bool checkSocIsInRange(float soc);
        bool checkChargeRateIsInRange(float chargeRate);
        bool checkBatteryIsOk(float temp ,float soc ,float chargeRate);
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
    bool checkBatteryIsOk(float temp,float soc ,float chargerate)
    {
        return(checkTempIsInRange(temp)&&checkSocIsInRange(soc)&&checkChargeRateIsInRange(chargerate));
    }
};

void checkBattery()
{
    NewBattery n;
    
    //Check if temp is in range
    assert(n.checkBatteryIsOk(0,19,1)==false);
    assert(n.checkBatteryIsOk(1,21,1)==false);
    assert(n.checkBatteryIsOk(1,81,0.7)==false); 
    assert(n.checkBatteryIsOk(-1,79,0.7)==false);
    assert(n.checkBatteryIsOk(1,21,0.7)==true);
    assert(n.checkBatteryIsOk(44,79,0.7)==true);
    
    //Check if soc in range
    assert(n.checkSocIsInRange(20)==true)
    assert(n.checkSocIsInRange(80)==true)
    assert(n.checkSocIsInRange(19)==false)
    assert(n.checkSocIsInRange(81)==false)
    assert(n.checkSocIsInRange(21)==true)
        
    //Check if chargerate in range
    assert(n.checkChargeRateIsInRange(0.8)==true)
    assert(n.checkChargeRateIsInRange(0.9)==false)
    assert(n.checkChargeRateIsInRange(0.7)==true)
    assert(n.checkChargeRateIsInRange(0)==true)
         
}

int main() 
{
   checkBattery();
}
