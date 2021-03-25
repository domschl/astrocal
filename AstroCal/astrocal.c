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
    /*! Print a timespec to console as UTC time
      @param ts \ref timespec
    */
    char buf[100];
    strftime(buf, sizeof(buf), "%Y-%m-%d %T", gmtime(&ts.tv_sec));
    printf("Current time: %s.%09ld UTC\n", buf, ts.tv_nsec);
}

void ASTC_printLocalTime(const struct timespec ts) {
    /*! Print a timespec to console as local time
      @param ts \ref timespec
    */
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
    /*! Convert a timespec to Julian date
      Unix time = (JD − 2440587.5) × 86400
      @param ts \ref timespec
      @return julian date as double.
    */
    double dts=ASTC_timespecToDouble(ts);
    return dts/86400.0+2440587.5;
}

struct timespec ASTC_JDToTimespec(double jd) {
    /*! Convert a Julian date to timespec
      Unix time = (JD − 2440587.5) × 86400
      @param jd julian date
      @return \ref timespec
    */
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

const double π = 3.14159265358979323846;

void ASTC_cartesianToPolar(double x, double y, double z, double *r, double *ϑ, double *φ) {
    if (r) *r=sqrt(x*x+y*y+z*z);
    if (ϑ) *ϑ=atan2(z,sqrt(x*x+y*y));
    if (φ) *ϑ=atan2(y,x);
}

void ASTC_polarToCartesian(double r, double ϑ, double φ, double *x, double *y, double *z) {
    if (x) *x=r*cos(ϑ)*cos(φ);
    if (y) *y=r*cos(ϑ)*sin(φ);
    if (z) *z=r*sin(ϑ);
    }

void ASTC_C2P(const double x[], double r[]) {
    ASTC_cartesianToPolar(x[0],x[1],x[2],&(r[0]),&(r[1]),&(r[2]));
}

void ASTC_P2C(const double r[], double x[]) {
    ASTC_cartesianToPolar(r[0], r[1], r[2], &(x[0]), &(x[1]), &(x[2]));
}

void ASTC_D2R(double d[], int len) {
    for (int i=0; i<len; i++) {
        d[i]=d[i]*π/180.0;
    }
}

void ASTC_R2D(double r[], int len) {
    for (int i=0; i<len; i++) {
        r[i]=r[i]*180.0/π;
    }
}

void ASTC_P2D(double p[]) {
    for (int i=1; i<3; i++) {
        p[i]=p[i]*180.0/π;
    }
}

void ASTC_D2P(double d[]) {
    for (int i=1; i<3; i++) {
        d[i]=d[i]/180.0*π;
    }
}
