
#include "../resources//Local.h"


Local::Local() {
    this->latitude = 0;
    this->longitude = 0;

}

Local::Local(long double latitude,long double longitude) {
    this->latitude = latitude;
    this-> longitude = longitude;

}


double Local:: get_xMap() const{return this->xMap;}

void Local:: set_xMap(double xMap){
    this->xMap =xMap;
}


double Local:: get_yMap() const{return this->yMap;}

void Local:: set_yMap(double yMap){
    this->yMap = yMap;
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




