#include "Vec.h"
Unit::Unit() {
	px = 0;
	sw = 0;
	sh = 0;
	pw = 0;
	ph = 0;
};
Unit::Unit(UnitType unitType, float size)
{
	px = 0;
	sw = 0;
	sh = 0;
	pw = 0;
	ph = 0;
	switch (unitType)
	{
	case UnitType::px:
		px = size;
		break;
	case UnitType::sw:
		sw = size;
		break;
	case UnitType::sh:
		sh = size;
		break;
	case UnitType::pw:
		pw = size;
		break;
	case UnitType::ph:
		ph = size;
		break;
	default:
		Log("UnitType not included yet");
	}

}


Color4::Color4() {};
Color4::Color4(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}
Color4::Color4(Vec4f vecA)
{
	this->r = vecA.x;
	this->g = vecA.y;
	this->b = vecA.z;
	this->a = vecA.u;
}
