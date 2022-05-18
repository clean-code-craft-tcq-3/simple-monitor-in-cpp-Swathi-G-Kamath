#include <assert.h>
#include <iostream>
#include "string.h"

int const mintemp = 0, maxtemp = 45, minsoc = 20, maxsoc = 80;
char* lang;

using namespace std;

class Battery {
public:
    float temperature, soc, chargeRate;

    bool checkTempIsInRange(float temp, int max, int min);
    bool checkTempIsInWarningRange(float temp, int minwarn, int maxwarn);

    bool checkSocIsInRange(float soc, int max, int min);
    bool checkSocIsInWarningRange(float soc, int minwarn, int maxwarn);

    bool checkChargeRateIsInRange(float chargeRate);
    bool checkChargeRateIsInWarningRange(float chargeRate, int minwarn, int maxwarn);


    bool valueIsInRange(float value, int min, int max);
    bool valuesIsInWarningRange(float value, int min, int max);

    bool checkBatteryIsOk(float temp, float soc, float chargeRate);

    void LogHighTempWarning(char* msg);
    void LogLowTempWarning(char* msg);

    void LogHighSocWarning(char* msg);
    void LogLowSocWarning(char* msg);

};

class NewBattery :public Battery
{
public:
    char* msg;

    enum warninglevel
    {
        discharge,
        peak
    };

    enum warningsoclevel
    {
        LOW_LIMIT_BREACH = 0,
        LOW_LIMIT_WARNING = 1,
        NORMAL = 3,
        HIGH_LIMIT_WARNING = 2,
        HIGH_LIMIT_BREACH = 4
    };

    float lowlimtempwarn = mintemp + (0.05 * maxtemp);
    float highlimtempwarn = maxtemp - (0.05 * maxtemp);
    float lowlimsocwarn = minsoc + (0.05 * maxsoc);
    float highlimsocwarn = maxsoc - (0.05 * maxsoc);
    float chargeratewarn = 0.8 - (0.8 * 0.05);


    bool checkTempIsInRange(float temperature, int mintemp, int maxtemp)
    {
        if (valueIsInRange(temperature, mintemp, maxtemp))
            return NORMAL;
        else
            return false;
    }

    bool checkSocIsInRange(float soc, int minsoc, int maxsoc)
    {
        if (valueIsInRange(soc, minsoc, maxsoc))
            return NORMAL;
        else
            return false;
    }

    bool checkChargeRateIsInRange(float chargeRate)
    {
        if (chargeRate >= 0.8)
            return false;
        else
            return NORMAL;
    }

    bool valueIsInRange(float value, int min, int max)
    {
        if (value < min || value > max)
            return false;
        else
            return true;
    }

    bool checkBatteryIsOk(float temp, float soc, float chargerate)
    {
        return(checkTempIsInRange(temp, mintemp, maxtemp) && checkSocIsInRange(soc, minsoc, maxsoc) && checkChargeRateIsInRange(chargerate));
    }

    bool checkTempIsInWarningRange(float temp, char* lang)
    {
        int warninglevel = valuesIsInWarningRange(temp, mintemp, maxtemp, lowlimtempwarn, highlimtempwarn);
        switch (warninglevel)
        {
        case 1:
            LogLowTempWarning(lang);
            return true;
        case 2:
            LogHighTempWarning(lang);
            return true;
        }
        return false;
    }

    bool checkSocIsInWarningRange(float soc, char* lang)
    {
        int warninglevel = valuesIsInWarningRange(soc, minsoc, maxsoc, lowlimsocwarn, highlimsocwarn);
        switch (warninglevel)
        {
        case 1:
            LogLowSocWarning(lang);
            return true;
        case 2:
            LogHighSocWarning(lang);
            return true;
        }
        return false;
    }

    bool checkChargeRateIsInWarningRange(float chargerate, char* lang)
    {
        if (0.8 > chargerate > chargeratewarn)
        {
            LogChargeRateWarning(lang);
            return true;
        }
        return false;
    }

    void LogHighTempWarning(char* lang)
    {
        if (!strcmp(lang, "English"))
        {
            cout << "Warning: Approaching High Temperature Range\n";
        }
        if (!strcmp(lang, "German"))
        {
            cout << "Warnung: Annäherung an den hohen Temperaturbereich\n";
        }
    }

    void LogLowTempWarning(char* lang)
    {
        if (!strcmp(lang, "English"))
        {
            cout << "Warning: Approaching Low Temperature Range\n";
        }
        if (!strcmp(lang, "German"))
        {
            cout << "Warnung: Annäherung an den niedrigen Temperaturbereich\n";
        }
    }

    void LogHighSocWarning(char* lang)
    {
        if (!strcmp(lang, "English"))
        {
            cout << "Warning: Approaching charge-peak\n";
        }
        if (!strcmp(lang, "German"))
        {
            cout << "Warnung: Ladespitze nähert sich\n";
        }
    }

    void LogLowSocWarning(char* lang)
    {
        if (!strcmp(lang, "English"))
        {
            cout << "Warning: Approaching discharge\n";
        }
        if (!strcmp(lang, "German"))
        {
            cout << "Warnung:  Naht Entladung\n";
        }
    }

    void LogChargeRateWarning(char* lang)
    {
        if (!strcmp(lang, "English"))
        {
            cout << "Warning: ChargeRate is high\n ";
        }
        if (!strcmp(lang, "German"))
        {
            cout << "Warnung:  Naht Entladung\n";
        }
    }

    int valuesIsInWarningRange(float value, float min, float max, float minwarn, float maxwarn)
    {
       int a=min <value;
       int b=value<=minwarn;
       int lowlimit=a&&b;
       //int c=maxwarn <=value,d=value<max,highlimit=c&&d;
        if (lowlimit)
        {
            return LOW_LIMIT_WARNING;
        }
     /*   if (highlimit)
        {
            
            return HIGH_LIMIT_WARNING;
        }*/
    }
};

void checkBattery()
{
    NewBattery n;

    //Check if battery is ok
    assert(n.checkBatteryIsOk(0, 19, 1) == false);
    assert(n.checkBatteryIsOk(1, 21, 1) == false);
    assert(n.checkBatteryIsOk(1, 81, 0.7) == false);
    assert(n.checkBatteryIsOk(-1, 79, 0.7) == false);
    assert(n.checkBatteryIsOk(1, 21, 0.7) == true);
    assert(n.checkBatteryIsOk(44, 79, 0.7) == true);

    //Check if temperature in range
    assert(n.checkTempIsInRange(0, mintemp, maxtemp) == true);
    assert(n.checkTempIsInRange(45, mintemp, maxtemp) == true);
    assert(n.checkTempIsInRange(-1, mintemp, maxtemp) == false);
    assert(n.checkTempIsInRange(46, mintemp, maxtemp) == false);
    assert(n.checkTempIsInRange(40, mintemp, maxtemp) == true);

    //Check if soc in range
    assert(n.checkSocIsInRange(20, minsoc, maxsoc) == true);
    assert(n.checkSocIsInRange(80, minsoc, maxsoc) == true);
    assert(n.checkSocIsInRange(19, minsoc, maxsoc) == false);
    assert(n.checkSocIsInRange(81, minsoc, maxsoc) == false);
    assert(n.checkSocIsInRange(21, minsoc, maxsoc) == true);

    //Check if chargerate in range
    assert(n.checkChargeRateIsInRange(0.8) == false);
    assert(n.checkChargeRateIsInRange(0.9) == false);
    assert(n.checkChargeRateIsInRange(0.7) == true);
    assert(n.checkChargeRateIsInRange(0) == true);

    //check temp warning levels
    assert(n.checkTempIsInWarningRange(1, "English") == true);
    assert(n.checkTempIsInWarningRange(2, "English") == true);
    assert(n.checkTempIsInWarningRange(1, "German") == true);
    assert(n.checkTempIsInWarningRange(2, "German") == true);
    //assert(n.checkTempIsInWarningRange(43, "English") == true);
    //assert(n.checkTempIsInWarningRange(44, "English") == true);

    //Check soc warning levels
    assert(n.checkSocIsInWarningRange(21, "English") == true);
    assert(n.checkSocIsInWarningRange(22, "English") == true);
    assert(n.checkSocIsInWarningRange(23, "English") == true);
    assert(n.checkSocIsInWarningRange(24, "English") == true);
    //assert(n.checkSocIsInWarningRange(77, "English") == true);
    //assert(n.checkSocIsInWarningRange(78, "English") == true);
    //assert(n.checkSocIsInWarningRange(79, "English") == true);
    //assert(n.checkSocIsInWarningRange(78, "German") == true);
    //assert(n.checkSocIsInWarningRange(79, "German") == true);

    //Check charge rate warnings
    assert(n.checkChargeRateIsInWarningRange(0.79, "English") == true);
    assert(n.checkChargeRateIsInWarningRange(0.77, "English") == true);
    assert(n.checkChargeRateIsInWarningRange(0.78, "English") == true);
    assert(n.checkChargeRateIsInWarningRange(0.78, "German") == true);
}

int main()
{
    checkBattery();
}
