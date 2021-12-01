#pragma once
enum class UnitType
{
	px,//pixels
	sw,//screen Widt
	sh,//screen Height
	pw,//parent Width
	ph,//parent Height
};

/**
 * @brief
*/
struct Unit
{
public:
	float px;
	float sw;
	float sh;
	float pw;
	float ph;
	Unit();
	Unit(UnitType unitType, float size);
	Unit operator + (const Unit& s) const
	{
		Unit un;
		un.px = this->px + s.px;
		un.pw = this->pw + s.pw;
		un.ph = this->ph + s.ph;
		un.sw = this->sw + s.sw;
		un.sh = this->sh + s.sh;
		return un;
	}
	Unit operator - (const Unit& s) const
	{
		Unit un;
		un.px = this->px - s.px;
		un.pw = this->pw - s.pw;
		un.ph = this->ph - s.ph;
		un.sw = this->sw - s.sw;
		un.sh = this->sh - s.sh;
		return un;
	}
	Unit operator * (const float& s) const
	{
		Unit un;
		un.px = this->px * s;
		un.pw = this->pw * s;
		un.ph = this->ph * s;
		un.sw = this->sw * s;
		un.sh = this->sh * s;
		return un;
	}
};