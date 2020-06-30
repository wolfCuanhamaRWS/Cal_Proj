
#ifndef CAL_PROJ_LOCAL_H
#define CAL_PROJ_LOCAL_H
#include <iostream>
#include <string>
#include <cmath>


#define PI 3.14159265358979323846

using namespace std;


class Local {
private:

    long double latitude, longitude;
    double xMap = 0;
    double yMap = 0;
public:
    Local();

    Local(long double latitude,long double longitude);
    Local( double xMap, double yMap,double latitude, double longitude){
        this->xMap = xMap;
        this->yMap = yMap;
        this->latitude = latitude;
        this-> longitude = longitude;
    }
    double get_latitude() const;

    void set_latitude(double latitude);

    double get_longitude() const;
    void set_longitude(double longitude);

    double get_xMap() const;
    void set_xMap(double xMap);

    double get_yMap() const;
    void set_yMap(double yMap);




};

#endif //CAL_PROJ_LOCAL_H
