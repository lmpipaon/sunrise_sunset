// A simple C++ program calculating the sunrise and sunset for

// the current date and a set location (latitude,longitude)

// Jarmo Lammi © 1999 - 2000

// jjlammi@netti.fi


// Get the days to J2000

// h is UT in decimal hours

// FNday only works between 1901 to 2099 - see Meeus chapter 7


float FNday (unsigned int y, unsigned char m, unsigned char d, float h);



// the function below returns an angle in the range

// 0 to 2*pi



float FNrange (float x);



// Calculating the hourangle

float f0(float lat, float declin);



// Calculating the hourangle for twilight times

//

float f1(float lat, float declin);



// Find the ecliptic longitude of the Sun

float FNsun (float d);






void orto_ocaso(float latit, float longit, float tzone,
                float d, float* delta, float* daylen, float* twam,
                float* riset, float* noont, float* altmax, float* settm,
                float* twpm);




