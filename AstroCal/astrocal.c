#include "astrocal.h"

struct timespec ASTC_currentTimeUTC() {
    /*! Provide current time in UTC as \ref struct timespec 

      The timespec ts contains a long value for seconds ts.tv_sec and 
      a long value for nanoseconds ts.tv_nsec.

     @return \ref timespec */
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
    printf("Current time: %s.%09ld (local)\n", buf, ts.tv_nsec);
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

double ASTC_degreeToDecimal(int d, int m, double s) {
    double sgn=1.0;
    if (d<0 || m<0 || s<0.0) sgn=-1.0;
    if (d<0) d= -d;
    if (m<0) m= -m;
    if (s<0) s=fabs(s);
    if (m>=60) {
        printf("Internal error in ASTC_degreeToDecimal: m>=60 -> %d!\n", m);
    }
    if (s>=60.0) {
        printf("Internal error in ASTC_degreeToDecimal: s>=60.0 -> %f!\n", s);
    }
    return sgn*(fabs((double)d)+fabs((double)m/60.0)+fabs(s)/3600.0);
}

void ASTC_decimalToDegree(double de, int *d, int *m, double *s) {
    double ade=fabs(de);
    if (d) *d=(int)ade;
    ade -= (int)ade;
    ade *= 60.0;
    if (m) *m=(int)(ade);
    ade -= (int)ade;
    ade *= 60.0;
    if (s) *s=ade;
    if (de<0.0) {
        if (d) {
            if (*d != 0) {
                *d = -*d;
                return;
            }
            if (m) {
                if (*m != 0) {
                    *m = -*m;
                    return;
                }
            }
            if (s) {
                if (*s != 0.0) {
                    *s = -*s;
                }
            }
        }
    }           
}
