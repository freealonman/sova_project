#include "main.h"

CEarthObject::CEarthObject() {


}

CEarthObject::CEarthObject(string ObjectName, SECICoordinate ECI) {
	EarthObject.ECIPosition = ECI;

	EarthObject.Name = ObjectName;
}

CEarthObject::CEarthObject(string ObjectName, SLLACoordinate LLA) {
	EarthObject.LLAPosition = LLA;
	cGeo cg1 = cGeo(LLA.Latitude, LLA.Longitude, LLA.Altitude);
	cEci ce1(cg1, cJulian(0));
	EarthObject.ECIPosition.X = ce1.Position().m_x;
	EarthObject.ECIPosition.Y = ce1.Position().m_y;
	EarthObject.ECIPosition.Z = ce1.Position().m_z;
	EarthObject.Name = ObjectName;

}


time_t CEarthObject::GetPredictableTime() {
	return PredictableTime;

}

void CEarthObject::SetSattelite(CSattelite* Sat) {
	Satellite = Sat;
	CallculatePredictableTime();
}

void CEarthObject::Save(FILE* file) {
	fwrite(&EarthObject, sizeof(SEarthObject), 1, file);
}

SECICoordinate CEarthObject::GetPositionECI()
{
	return EarthObject.ECIPosition;

}

SLLACoordinate CEarthObject::GetPositionLLA()
{
	return EarthObject.LLAPosition;

}

double CEarthObject::GetAngleX(time_t t)
{
	SLLACoordinate LLaStation = Satellite->GetPositionLLA(t);
	double a = sqrt(sqr(EarthObject.LLAPosition.Latitude - LLaStation.Latitude) + sqr(EarthObject.LLAPosition.Longitude-LLaStation.Longitude));
	double b = sqrt(sqr(LLaStation.Latitude) + sqr(LLaStation.Longitude) + sqr(LLaStation.Altitude));
	double alpha = atan((a*2.0*PI*EARTH_RADIUS)/(b*360.0));
	//double alpha = atan(((EarthObject.LLAPosition.Latitude-LLaStation.Latitude)*2.0*PI*6400.0)/(LLaStation.Altitude*360.0));
	alpha = (alpha*180.0)/PI;
	return alpha;
}

double CEarthObject::GetAngleY(time_t t)
{
    return 0;
}


void CEarthObject::CallculatePredictableTime()
{
	int i = time(NULL);
	double alpha = 360;
	/*do 
	{
		
		//double a = sqrt(sqr(EarthObject.LLAPosition.Latitude - LLaStation.Latitude) + sqr(EarthObject.LLAPosition.Longitude-LLaStation.Longitude));
		//double b = sqrt(sqr(LLaStation.Latitude) + sqr(LLaStation.Longitude) + sqr(LLaStation.Altitude));
		//alpha = atan((a*2.0*PI*EARTH_RADIUS)/(b*360.0));

	} while (alpha < 30.0f && alpha > -30.0f);*/
	while (alpha > 30.0f || alpha < -30.0f)
	{
		SLLACoordinate LLaStation = Satellite->GetPositionLLA(i);
		//alpha = atan(((EarthObject.LLAPosition.Latitude-LLaStation.Latitude)*2.0*PI*6400.0)/(LLaStation.Altitude*360.0));
		double a = sqrt(sqr(EarthObject.LLAPosition.Latitude - LLaStation.Latitude) + sqr(EarthObject.LLAPosition.Longitude-LLaStation.Longitude));
		double b = sqrt(sqr(LLaStation.Latitude) + sqr(LLaStation.Longitude) + sqr(LLaStation.Altitude));
		alpha = atan((a*2.0*PI*EARTH_RADIUS)/(b*360.0));
		alpha = (alpha*180.0)/PI;
		i++;
	}
	PredictableTime = i;
	//Satellite = NULL;
}

std::string CEarthObject::GetName()
{
	return EarthObject.Name;

}

void CEarthObject::Load(FILE* file)
{
	fread(&EarthObject, sizeof(SEarthObject), 1, file);
}

void CEarthObject::CallculateVssData()
{
	double angleX = 0;
	double angleY = 0;
	time_t t = PredictableTime;

	while (angleX > -30.0 && angleX < 30.0 && angleY > -30.0 && angleY < 30.0)
	{
		SVSSData data;
		data.angleX		= GetAngleX(t);
		data.angleY		= GetAngleY(t);
		data.objectName = EarthObject.Name;
		data.LLAObject  = EarthObject.LLAPosition;
		data.LLAStation = Satellite->GetPositionLLA(t);
		data.shootTime = t;

		VSSData.push_back(data);
		t++;

	}
}

