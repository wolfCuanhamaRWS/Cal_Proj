
#include "../Header/Local.h"


Local::Local() {
    this->latitude = 0;
    this->longitude = 0;
}

Local::Local(long double latitude,long double longuitude) {
    this->latitude = latitude;
    this-> longitude = longuitude;

}

double Local::get_latitude() const {
    return this->latitude;
}

void Local::set_latitude(double latitude) {
    this->latitude = latitude;
}



double Local::get_longitude() const {
    return this->longitude;
}



void Local::set_longitude(double longitude) {
    this->longitude = longitude;
}
