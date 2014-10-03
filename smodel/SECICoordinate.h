#ifndef _SECICOORDINATE_H_
#define _SECICOORDINATE_H_


class SECICoordinate {

public:
	double X;
	double Y;
	double Z;
	SECICoordinate():X(0),Y(0),Z(0){};
	SECICoordinate(double x, double y, double z):X(x),Y(y),Z(z){};
};

class SECRCoordinate:public SECICoordinate
{

};
#endif