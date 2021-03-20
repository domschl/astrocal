#include "astrocal.h"

struct timespec ASTC_currentTimeUTC() {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return ts;
}

void ASTC_printTime(const struct timespec ts) {
    char buf[100];
    strftime(buf, sizeof(buf), "%Y-%m-%d %T", gmtime(&ts.tv_sec));
    printf("Current time: %s.%09ld UTC\n", buf, ts.tv_nsec);
}

void ASTC_printLocalTime(const struct timespec ts) {
    char buf[100];
    strftime(buf, sizeof(buf), "%Y-%m-%d %T", localtime(&ts.tv_sec));
    printf("Current time: %s.%09ld\n", buf, ts.tv_nsec);
}

double ASTC_timespecToDouble(const struct timespec ts) {
    double dts=(double)ts.tv_sec+(double)ts.tv_nsec/1000000000.0;
    return dts;
}

struct timespec ASTC_doubleToTimespec(double dts) {
    struct timespec ts;
    ts.tv_sec=(long)dts;
    ts.tv_nsec=(long)((dts-(double)ts.tv_sec)*1000000000.0);
    return ts;
}

double ASTC_timespecToJD(const struct timespec ts) {
    // Unix time = (JD − 2440587.5) × 86400 
    double dts=ASTC_timespecToDouble(ts);
    return dts/86400.0+2440587.5;
}

struct timespec ASTC_JDToTimespec(double jd) {
    double dts=(jd-2440587.5)*86400.0;
    return ASTC_doubleToTimespec(dts);
}