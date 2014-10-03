#ifndef _CEARTHOBJECT_H_
#define _CEARTHOBJECT_H_

class CSattelite;

#include "main.h"


class CEarthObject {

private:
	CSattelite* Satellite;
	SEarthObject EarthObject;
	time_t PredictableTime;
	vector<SVSSData> VSSData;
	double angleX;
	double angleY; 

private:
	void			CallculatePredictableTime();
	void			CallculateShootingData();
	void			CallculateVssData();
	void			CallculatePhotoData();
    
public:
	CEarthObject();
	CEarthObject(string ObjectName, SECICoordinate ECI);
	CEarthObject(string ObjectName, SLLACoordinate LLA);

public:
	string			GetName();
	time_t			GetPredictableTime();
	SECICoordinate  GetPositionECI();
	SLLACoordinate  GetPositionLLA();
	double			GetAngleX(time_t t);
	double			GetAngleY(time_t t);

public:
	void			Load(FILE* file);
	void			Save(FILE* file);
	void			SetSattelite(CSattelite* Sat);
};

#endif
