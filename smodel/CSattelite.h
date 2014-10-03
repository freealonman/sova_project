#ifndef _CSATTELITE_H_
#define _CSATTELITE_H_

#include "main.h"
#include <QDebug>


class CSattelite {

private:
	std::vector<CEarthObject> EarthObjects;
	SECICoordinate ECIPosition;
	SLLACoordinate LLAPosition;
	SECRCoordinate ECRPosition;
	SSatelliteFileDesc SatteliteFileDesc;
	FILE  *SatteliteFile;
	string TLESTR1;
	string TLESTR2;
	string TLESTR3;
	cTle*   TLE;
	cOrbit* Orbit;

private:

    void CallculatePosition(time_t t);

public:
	CSattelite();

	void AddEathObject(CEarthObject& EarthObject);

	void AddObject(const string & ObjectName, double Latitude, double Longitude);

	SECICoordinate GetPositionECI(time_t t);

	SLLACoordinate GetPositionLLA(time_t t);

	SECRCoordinate GetPositionECR(time_t t);

	CEarthObject GetEarthObject(string ObjectName);
    int GetEarthObject(CEarthObject &earth_object, time_t t);
	
	CEarthObject* GetEarthObjects();

    SLLACoordinate* GetTrace(time_t _current_time, const int &point_count);



	int GetObjectsCount();

	void LoadTLE(string FileName);

	void Load(string FileName);

	void Save(string FileName);
};

#endif
