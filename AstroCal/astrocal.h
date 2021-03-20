#include <time.h>
#include <stdio.h>

struct timespec ASTC_currentTimeUTC();
void ASTC_printTime(const struct timespec ts);
void ASTC_printLocalTime(const struct timespec ts);
double ASTC_timespecToDouble(const struct timespec ts);
struct timespec ASTC_doubleToTimespec(double dts);
double ASTC_timespecToJulianDate(const struct timespec ts);
struct timespec ASTC_julianDateToTimespec(double jd);
