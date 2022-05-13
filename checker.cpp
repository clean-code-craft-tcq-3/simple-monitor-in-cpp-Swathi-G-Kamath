#include <assert.h>
#include <iostream>


int const mintemp= 0,maxtemp=45,minsoc=20,maxsoc=80;

using namespace std;

class Battery{
    public:
        float temperature,soc,chargeRate;
        bool checkTempIsInRange(float temp,int max,int min);
        bool checkSocIsInRange(float soc,int max, int min);
        bool checkChargeRateIsInRange(float chargeRate);
        bool valueIsInRange(float value, int min, int max); 
        bool checkBatteryIsOk(float temp ,float soc ,float chargeRate);
};

class NewBattery:public Battery
{  
    public:
    bool checkTempIsInRange(float temperature,int mintemp,int maxtemp)
    {
        if(valueIsInRange(temp,mintemp,maxtemp))
            return true;
        else 
            return false;
    }
    bool checkSocIsInRange(float soc,int minsoc,int maxsoc)
    {
        if(valueIsInRange(soc,minsoc,maxsoc))
            return true;
        else
            return false;        
    }
    bool checkChargeRateIsInRange(float chargeRate)
    {
        if(chargeRate>=0.8)
            return false;
        else 
            return true;
    }
    bool valueIsInRange(float value, int min, int max)
    {
       if(value < min || value > max)
         return false;
       else
         return true;
    }
       
    bool checkBatteryIsOk(float temp,float soc ,float chargerate)
    {
        return(checkTempIsInRange(temp,mintemp,maxtemp)&&checkSocIsInRange(soc,minsoc,maxsoc)&&checkChargeRateIsInRange(chargerate));
    }
};

void checkBattery()
{
    NewBattery n;
    
    //Check if battery is ok
    assert(n.checkBatteryIsOk(0,19,1)==false);
    assert(n.checkBatteryIsOk(1,21,1)==false);
    assert(n.checkBatteryIsOk(1,81,0.7)==false); 
    assert(n.checkBatteryIsOk(-1,79,0.7)==false);
    assert(n.checkBatteryIsOk(1,21,0.7)==true);
    assert(n.checkBatteryIsOk(44,79,0.7)==true);
    
    //Check if temperature in range
    assert(n.checkTempIsInRange(0)==true);
    assert(n.checkTempIsInRange(45)==true);
    assert(n.checkTempIsInRange(-1)==false);
    assert(n.checkTempIsInRange(46)==false);
    assert(n.checkTempIsInRange(40)==true);   
    
    
    //Check if soc in range
    assert(n.checkSocIsInRange(20)==true);
    assert(n.checkSocIsInRange(80)==true);
    assert(n.checkSocIsInRange(19)==false);
    assert(n.checkSocIsInRange(81)==false);
    assert(n.checkSocIsInRange(21)==true);
        
    //Check if chargerate in range
    assert(n.checkChargeRateIsInRange(0.8)==false);
    assert(n.checkChargeRateIsInRange(0.9)==false);
    assert(n.checkChargeRateIsInRange(0.7)==true);
    assert(n.checkChargeRateIsInRange(0)==true);
         
}

int main() 
{
   checkBattery();
}
