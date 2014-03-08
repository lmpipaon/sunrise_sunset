// A simple C++ program calculating the sunrise and sunset for

// the current date and a set location (latitude,longitude)

// Jarmo Lammi © 1999 - 2000

// jjlammi@netti.fi


#include <math.h>
#include <orto_ocaso.h>


float L, g;
float SunDia = 0.53;  // Sunradius degrees
float AirRefr = 34.0/60.0; // athmospheric refraction degrees //

float _PI_180=M_PI/180.0;
float _2PI=2*M_PI;
float _180PI=180.0/M_PI;
float _PI_2=M_PI/2.0;
float _PI=M_PI;

// Get the days to J2000

// h is UT in decimal hours

// FNday only works between 1901 to 2099 - see Meeus chapter 7


float FNday (unsigned int y, unsigned char m, unsigned char d, float h) {

float luku = double((unsigned long)y*367 - 7 * (y + (m + 9)/12)/4 + 275*m/9) + d;

return (float)(luku - 730531.5 + h/24.0);
// FNday+2451545.0 = julian
};



// the function below returns an angle in the range

// 0 to 2*M_PI



float FNrange (float x) {

    float b = x / _2PI;

    float a = _2PI * (b - floor(b));

    if (a < 0) a = _2PI + a;

    return a;

};



// Calculating the hourangle

float f0(float lat, float declin) {

float fo,dfo;

// Correction: different sign at S HS

dfo = _PI_180*(0.5*SunDia + AirRefr); if (lat < 0.0) dfo = -dfo;

fo = tan(declin + dfo) * tan(lat*_PI_180);

if (fo > 0.99999) fo=1.0; // to avoid overflow //

fo = asin(fo) + _PI_2;

return fo;

};



// Calculating the hourangle for twilight times

//

float f1(float lat, float declin) {

float fi,df1;

// Correction: different sign at S HS

df1 = _PI_180 * 6.0; if (lat < 0.0) df1 = -df1;

fi = tan(declin + df1) * tan(lat*_PI_180);


if (fi > 0.99999) fi=1.0; // to avoid overflow //

fi = asin(fi) + _PI_2;

return fi;

};



// Find the ecliptic longitude of the Sun

float FNsun (float d) {

// mean longitude of the Sun

L = FNrange(280.461 * _PI_180 + .9856474 * _PI_180 * d);

// mean anomaly of the Sun

g = FNrange(357.528 * _PI_180 + .9856003 * _PI_180 * d);



// Ecliptic longitude of the Sun

return FNrange(L + 1.915 * _PI_180 * sin(g) + .02 * _PI_180 * sin(2 * g));

};







void orto_ocaso(float latit, float longit, float tzone,
                float d, float* delta, float* daylen, float* twam,
                float* riset, float* noont, float* altmax, float* settm,
                float* twpm){



 
// Use FNsun to find the ecliptic longitude of the

// Sun

float lambda = FNsun(d);

// Obliquity of the ecliptic
float obliq = 23.439 * _PI_180 - .0000004 * _PI_180 * d;



// Find the RA and DEC of the Sun


float temp_float=sin(lambda);

float alpha = atan2(cos(obliq) * temp_float, cos(lambda));

*delta = asin(sin(obliq) * temp_float);


// Find the Equation of Time in minutes

// Correction suggested by David Smith

float LL = L - alpha;

if (L < _PI) LL += _2PI;

float equation = 1440.0 * (1.0 - LL / _2PI);



float ha = f0(latit,*delta);

float hb = f1(latit,*delta);

float twx = hb - ha;   // length of twilight in radians

twx = 12.0*twx/_PI;      // length of twilight in degrees

// Conversion of angle to hours and minutes //

*daylen = _180PI * ha / 7.5;

if (*daylen<0.0001) {*daylen = 0.0;}

// arctic winter   //


temp_float=ha/_PI;

*riset = 12.0 - 12.0 * temp_float + tzone - longit/15.0 + equation/60.0;

*settm = 12.0 + 12.0 * temp_float + tzone - longit/15.0 + equation/60.0;

*noont = *riset + 12.0 * temp_float;

*altmax = 90.0 + *delta * _180PI - latit;

// Correction suggested by David Smith
// to express as degrees from the N horizon

if ( (*delta * _180PI) > latit ) *altmax = 90.0 + latit - ( *delta * _180PI );


*twam = *riset - twx;      // morning twilight begin

*twpm = *settm + twx;      // evening twilight end


if (*riset > 24.0) *riset-= 24.0;

if (*settm > 24.0) *settm-= 24.0;


}

