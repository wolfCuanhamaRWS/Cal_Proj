
#ifndef CAL_PROJ_LOCAL_H
#define CAL_PROJ_LOCAL_H
#include <iostream>
#include <string>
using namespace std;


class Local {
private:

    long double latitude, longitude;
public:
    Local();

    Local(long double latitude,long double longuitude);

    double get_latitude() const;

    void set_latitude(double latitude);

    double get_longitude() const;

    void set_longitude(double longitude);

};

#endif //CAL_PROJ_LOCAL_H
