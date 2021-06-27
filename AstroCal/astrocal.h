/*! \brief the h file for AstroCal */
#include <time.h>
#include <math.h>
#include <stdio.h>

struct timespec ASTC_currentTimeUTC();
void ASTC_printTime(const struct timespec ts);
void ASTC_printLocalTime(const struct timespec ts);
double ASTC_timespecToDouble(const struct timespec ts);
struct timespec ASTC_doubleToTimespec(double dts);
double ASTC_timespecToJD(const struct timespec ts);
struct timespec ASTC_JDToTimespec(double jd);

double ASTC_JDToMSDprec(double jd, double k);
double ASTC_MSDToJDprec(double msd, double k);
double ASTC_JDToMSD(double jd);
double ASTC_MSDToJD(double msd);

double ASTC_degreeToDecimal(int d, int m, double s);
void ASTC_decimalToDegree(double de, int *d, int *m, double *s);
