#ifndef _UTILS_H_
#define  _UTILS_H_

#include "main.h"

#define EARTH_SPEED  0.0041666666666667
#define EARTH_RADIUS 6378.1

struct SVSSData
{
	double			angleX;
	double			angleY;
	time_t			shootTime;
	string          objectName;
	SLLACoordinate  LLAStation;
	SLLACoordinate  LLAObject;
};



static double VectorLength(SECICoordinate V1)
{
	return sqrt(pow(V1.X,2)+pow(V1.Y,2)+pow(V1.Z,2));
}

static double ScalarMultiply(const SECICoordinate V1, const SECICoordinate& V2)
{
	return (V1.X * V2.X) + (V1.Y * V2.Y) + (V1.Z * V2.Z);
}

static double Dot(SECICoordinate & V1, SECICoordinate & V2)
{	
	return ((acos((ScalarMultiply(V1, V2))/(VectorLength(V1)*VectorLength(V2))))*180.0)/PI;
};

static SLLACoordinate EciTOLla(const SECICoordinate& EciCoordinates)
{
	double Altitude = VectorLength(EciCoordinates);
	double Longitude = (180*acos(EciCoordinates.Z/Altitude))/PI;
	double Latitude = (180*atan2(EciCoordinates.Y,EciCoordinates.X));	
	return SLLACoordinate(Latitude,Longitude,Altitude);
}
static SECICoordinate LlaToEci(const SLLACoordinate& LlaCoordinates)
{
	double X = LlaCoordinates.Altitude*cos(LlaCoordinates.Latitude)*sin(LlaCoordinates.Longitude);
	double Y = LlaCoordinates.Altitude*sin(LlaCoordinates.Latitude)*sin(LlaCoordinates.Longitude);
	double Z = LlaCoordinates.Altitude*cos(LlaCoordinates.Longitude);
	return SECICoordinate(X,Y,Z);
}

static SECRCoordinate EciToEcr(const SECICoordinate& EciCoordinate, const time_t t)
{
	struct tm* t2;
	t2 = gmtime(&t);
	
	double  CurrentTime = t2->tm_hour*3600.0 + t2->tm_min*60.0 + t2->tm_sec;

	SECRCoordinate ECR = SECRCoordinate();
	ECR.X = EciCoordinate.X*cos(EARTH_SPEED*CurrentTime)  + EciCoordinate.Y*sin(EARTH_SPEED*CurrentTime);
	ECR.Y = -EciCoordinate.X*sin(EARTH_SPEED*CurrentTime) + EciCoordinate.Y*cos(EARTH_SPEED*CurrentTime);
	ECR.Z = EciCoordinate.Z;
	return ECR;
}

static SLLACoordinate EcrToLla(const SECRCoordinate& ECR)
{
	double Altitude = VectorLength(ECR);
	double Latitude = (acos(ECR.Z/Altitude)*180)/PI;
	double Longitude = (atan2(ECR.Y,ECR.X)*180)/PI;	
	return SLLACoordinate(Latitude,Longitude,Altitude);
}

static double TimeEpohShift(double dayTime)
{
	tm * epohTimeTm = new tm();

	dayTime = dayTime*3600*24;
	epohTimeTm->tm_year = 114;    //convert tle epoh to time_t type
	double epohTime = mktime(epohTimeTm) + dayTime;

	//double timeSinceEpoh=time(NULL) - epohTime;
	return epohTime;
}

static time_t timeDiff(cJulian tCurrent, cJulian tSat)
{
	return tCurrent.SpanSec(tSat);
}



static char* StringToChar(string String)
{
	char* c = new char[String.size()+1];
	copy(String.begin(), String.end(), c);
	c[String.size()] = '\0';
	return c;
}
static double DTR(const double& Angle)
{
	return (Angle*PI)/180.0;
}

static double to360(const double& Angle)
{
	if (Angle < 0)
	{
		return Angle+360;
	}else
		if (Angle >=360)
		{
			return Angle-360;
		} else
	{
		return Angle;

	}
}

static SLLACoordinate GetSunPosition(time_t t)
{
	struct tm * _t = gmtime(&t);
	double UT  = (_t->tm_hour) + _t->tm_min/60.0 + _t->tm_sec/3600.0;
    double MJD = 367.0*(_t->tm_year+1900) - ((7*(_t->tm_year + 1900 + ((_t->tm_mon + 9)/12.0)))/4.0)
                                   + ((275*_t->tm_mon)/9) + _t->tm_mday - 678987;
	double T = (MJD - 51544.5)/36525.0;
	double W = to360(357.528 + 35999.05*T + 0.04107*UT);
	double L = to360(280.46 + 36000.772*T + 0.04107*UT + (1.915 - 0.0048*T)*sin(DTR(W)) 
		                                                     + 0.02*sin(2*DTR(W)));

	double X = cos(DTR(L));
	double Y = sin(DTR(L));
	double Z = 0;

	double eps1 = (84381.488 - 46.815*T - 0.00059*pow(T,2) + 0.001813*pow(T, 3))/3600.0;
	
	double _x = X;
	double _y = Y*cos(DTR(eps1)) - Z*sin(DTR(eps1));
	double _z = Y*sin(DTR(eps1)) + Z*cos(DTR(eps1));

	double S0 = 24110.54841 + 8640184.812*T + 0.093104*pow(T,2) -0.0000062*pow(T, 3);
	double earth_sp = 1.002737909350795;
	double dT = (UT/24.0)*86400.0*earth_sp;
	double S1 = S0 + dT;
	double _S = to360(S1/240.0);

	double Xg = _x*cos(DTR(_S)) + _y*sin(DTR(_S));
	double Yg = -_x*sin(DTR(_S)) + _y*cos(DTR(_S));
	double Zg = _z;

	SLLACoordinate LLA = SLLACoordinate();
	LLA.Longitude  = (atan2(Yg, Xg)*180.0)/PI;
	LLA.Latitude = (atan2(Zg,sqr(pow(Xg,2)+pow(Yg,2)))*180.0)/PI;
	LLA.Altitude  = 0;

	return LLA;
    
}

static SLLACoordinate* GetTerminatorLine(time_t t, const int &vp_width)
{
    SLLACoordinate*  TerminatorLine = (SLLACoordinate*)malloc(sizeof(SLLACoordinate)*vp_width);
	SLLACoordinate*  SunCoord = &GetSunPosition(t);
    double shift_value = 360.0 / vp_width;
    for (int i=0; i < vp_width; i++ )
	{
        TerminatorLine[i].Latitude = -1*((180.0/PI)*atan(-cos(DTR(i*shift_value)-DTR(SunCoord->Longitude))/tan(DTR(SunCoord->Latitude))));
        TerminatorLine[i].Longitude = i*shift_value - 180;
	}

	return TerminatorLine;
}

/*SLLACoordinate GetSun2(time_t t)
{
	tm* _t = gmtime(t);
	double JD = (1461*(_t->tm_year+4800 + (_t->tm_mon-14)/12.0))/4.0 +
		        (367* _t->tm_mon - 2 -12*((_t->tm_mon-14)/12.0))/12.0 -
				(3*((_t->tm_year + 4900 + (_t->tm_mon-14)/12.0)/100))/4 +
				+ _t->tm_mday -32075 - 0.5 + _t->tm_hour/24.0;	

	double n   = JD - 2451545.0;
	double omg = 2.1429 - 0.0010394594 * n;
	double L   = 4.8950630 + 0.017202791698 * n;
	double g   = 6.2400600 + 0.0172019699 * n;

	double l   = L + 0.03341607*sin(g) + 0.00034894*sin(2*g) - 0.0001134 - 0.0000203*sin(omg);
	double ep  = 0.4090928 - 6.2140*pow(10, -9)*n +0.0000396*cos(omg);
	double ra  = atan2(cos(ep)*sin(l), cos(l));
}
*/

#endif
