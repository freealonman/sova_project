#include "main.h"


void CSattelite::AddEathObject(CEarthObject& EarthObject) {
	EarthObject.SetSattelite(this);
	EarthObjects.push_back(EarthObject);
    SatteliteFileDesc.ObjectCount++;
}

SECICoordinate CSattelite::GetPositionECI(time_t t) {
	CallculatePosition(t);
	return ECIPosition;

}


SECRCoordinate CSattelite::GetPositionECR(time_t t)
{
	CallculatePosition(t);
	return ECRPosition;
}


SLLACoordinate CSattelite::GetPositionLLA(time_t t) {
	CallculatePosition(t);
	return LLAPosition;

}

CEarthObject CSattelite::GetEarthObject(string ObjectName) {
	for (int i=0; i < EarthObjects.size();i++)
	{
		if (EarthObjects[i].GetName() == ObjectName)
		{
			return EarthObjects[i];
		}
	}
	CEarthObject ceo = CEarthObject("NULLOBJECT", SECICoordinate(0,0,0));
	return ceo;

}

int CSattelite::GetEarthObject(CEarthObject& earth_object, time_t t)
{
    if (EarthObjects.size() == 0) return -1;
   for (int i=0; i < EarthObjects.size(); i++)
   {
       if (EarthObjects[i].GetAngleX(t) > -30.0 && EarthObjects[i].GetAngleX(t) < 30.0)
       {
           earth_object = EarthObjects[i];
           return 1;
       }

   }
    return 0;
}

void CSattelite::LoadTLE(string FileName) {
	ifstream f;
	f.open(FileName.c_str());
	getline(f, TLESTR1);
	getline(f, TLESTR2);
	getline(f, TLESTR3);
	
	TLE   = new cTle(TLESTR1, TLESTR2, TLESTR3);
	Orbit = new cOrbit(*TLE);

	SatteliteFileDesc.Name = TLE->GetField(cTle::FLD_FIRST, cTle::U_FIRST, NULL, true);

}

void CSattelite::Load(string FileName) {
	SatteliteFile = fopen(StringToChar(FileName), "r+");

	fread(&SatteliteFileDesc, sizeof(SSatelliteFileDesc), 1, SatteliteFile);

	if (SatteliteFileDesc.FileType == "SOVA")
	{
		for (int i=0; i < SatteliteFileDesc.ObjectCount; i++)
		{
			CEarthObject EarthObject = CEarthObject();
			EarthObject.Load(SatteliteFile);
			//EarthObjects.push_back(EarthObject);
			AddEathObject(EarthObject);
		}
	}
	fclose(SatteliteFile);


}

void CSattelite::Save(string FileName) {
	SatteliteFile = fopen(StringToChar(FileName), "w+");
	fwrite(&SatteliteFileDesc, sizeof(SSatelliteFileDesc),1 , SatteliteFile);
	for (int i=0;i < SatteliteFileDesc.ObjectCount; i++)
	{
		EarthObjects[i].Save(SatteliteFile);
	}
    //const GLuebyte*
    //glEnable(GL_MULTISAMPLE);
	fclose(SatteliteFile);
}

void CSattelite::CallculatePosition(time_t t)
{
	cJulian CurrentTime(t);
	double tleYear  = TLE->GetField(cTle::FLD_EPOCHYEAR) + 2000.0;
	double tleDay   = TLE->GetField(cTle::FLD_EPOCHDAY);
    //TLE->GetField(cTle::FLD_MMOTION)
	cJulian SatTime(tleYear, tleDay);
	time_t t1 = timeDiff(CurrentTime, SatTime);
	cEciTime EciTime = Orbit->GetPosition(t1/60.0f);
	cGeoTime GeoTime = cGeoTime(EciTime);
	
	ECIPosition.X = EciTime.Position().m_x;
	ECIPosition.Y = EciTime.Position().m_y;
	ECIPosition.Z = EciTime.Position().m_z;

	LLAPosition.Altitude  = GeoTime.AltitudeKm();
	LLAPosition.Latitude  = GeoTime.LatitudeDeg();
	if (GeoTime.LongitudeDeg() > 180)
	{
		LLAPosition.Longitude = GeoTime.LongitudeDeg() - 360.0;
	} else
	{
		LLAPosition.Longitude = GeoTime.LongitudeDeg();
	}
	
}

CSattelite::CSattelite()
{
	SatteliteFileDesc.FileType    = "SOVA";
	SatteliteFileDesc.ObjectCount = 0;
	SatteliteFileDesc.Name        = "NONAME";
}

CEarthObject* CSattelite::GetEarthObjects()
{
	return &EarthObjects[0];
}

int CSattelite::GetObjectsCount()
{
	return SatteliteFileDesc.ObjectCount;
}

void CSattelite::AddObject(const string & ObjectName, double Latitude, double Longitude)
{
	CEarthObject EarthObject = CEarthObject(ObjectName, SLLACoordinate(Latitude, Longitude, 0.0));
	EarthObject.SetSattelite(this);
	EarthObjects.push_back(EarthObject);
	SatteliteFileDesc.ObjectCount++;
}

SLLACoordinate* CSattelite::GetTrace(time_t _current_time, const int&point_count)
{
    double StartTime = _current_time;
    double EndTime   = _current_time + (3600 * 24) /TLE->GetField(cTle::FLD_MMOTION);
    double ShiftTime = (EndTime - _current_time) / point_count;
    SLLACoordinate* Positions = (SLLACoordinate*)malloc(sizeof(SLLACoordinate)*(point_count));
    for (int i = 0; i < point_count; i++)
	{
        Positions[i] = GetPositionLLA((i * round(ShiftTime)) + StartTime);
	}
	return Positions;
}
