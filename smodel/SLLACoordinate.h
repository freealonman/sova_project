#ifndef _SLLACOORDINATE_H_
#define _SLLACOORDINATE_H_

class SLLACoordinate {

public:
	double Latitude;
	double Longitude;
	double Altitude;
	SLLACoordinate():Latitude(0),Longitude(0),Altitude(0){};
	SLLACoordinate(double Lat, double Long, double Alt):Latitude(Lat),Longitude(Long),Altitude(Alt){};
};
#endif
