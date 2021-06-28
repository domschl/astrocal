/*! AstroCal routines
  \file astrocal.c a lib
  \brief That is the AstroCal library
 */
#include "astrocal.h"

// ------- Time & date ------------------------------------------

/*! Provide current time in UTC as struct timespec 

  The timespec ts contains a long value for seconds ts.tv_sec and 
  a long value for nanoseconds ts.tv_nsec.

 @return \ref timespec
*/
struct timespec ASTC_currentTimeUTC() {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return ts;
}

/*! Print a timespec to console as UTC time
  @param ts \ref timespec
*/
void ASTC_printTime(const struct timespec ts) {
    char buf[100];
    strftime(buf, sizeof(buf), "%Y-%m-%d %T", gmtime(&ts.tv_sec));
    printf("Current time: %s.%09ld UTC\n", buf, ts.tv_nsec);
}

/*! Print a timespec to console as local time
    @param ts \ref timespec
*/
void ASTC_printLocalTime(const struct timespec ts) {
    char buf[100];
    strftime(buf, sizeof(buf), "%Y-%m-%d %T", localtime(&ts.tv_sec));
    printf("Current time: %s.%09ld (local)\n", buf, ts.tv_nsec);
}

/*! Convert a struct timespec into a double float
  See also \ref ASTC_doubleToTimespec
  @param ts \ref timespec
  @return double float value in seconds
 */
double ASTC_timespecToDouble(const struct timespec ts) {
    double dts=(double)ts.tv_sec+(double)ts.tv_nsec/1000000000.0;
    return dts;
}

/*! Convert double time (sec) to timespec
  See also \ref ASTC_timespecToDouble
  @param dt Unix time in seconds (double)
  @return struct \ref timespec
*/
struct timespec ASTC_doubleToTimespec(double dt) {
    struct timespec ts;
    ts.tv_sec=(long)dt;
    ts.tv_nsec=(long)((dt-(double)ts.tv_sec)*1000000000.0);
    return ts;
}

/*! Convert a timespec to Julian date
  Unix time = (JD − 2440587.5) × 86400
  @param ts \ref timespec
  @return julian date as double.
*/
double ASTC_timespecToJD(const struct timespec ts) {
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

/*! Convert a Julian date to Mars Sol Date (MSD)
  See: https://en.wikipedia.org/wiki/Timekeeping_on_Mars
  See also \ref ASTC_JDToMSD() for a version with default value for k.
  @param jd julian date
  @param k correction factor in MSDs of location of reference crater Airy-0, currently 0.00014d
  (12sec).
  @return MSD, Mars Sol Date
*/
double ASTC_JDToMSDprec(double jd, double k) {
    double msd=(jd - 2451549.5 + k)/1.02749125 + 44796.0;
    return msd;
}

/*! Convert a Mars Sol Date (MSD) to Julian date
  See: https://en.wikipedia.org/wiki/Timekeeping_on_Mars
  See also \ref ASTC_MSDToJD() for a version with default value for k.
  @param msd Mars Sol Date (MSD)
  @param k correction factor in MSDs of location of reference crater Airy-0, currently 0.00014d
  (12sec).
  @return JD, Julian date.
*/
double ASTC_MSDToJDprec(double msd, double k) {
    double jd=(msd-44796.0)*1.02749125-k+2451549.5;
    return jd;
}

/*! Convert a Julian date to Mars Sol Date (MSD)
  See: https://en.wikipedia.org/wiki/Timekeeping_on_Mars
  See also \ref ASTC_JDToMSDprec().
  @param jd julian date
  @return MSD, Mars Sol Date
*/
double ASTC_JDToMSD(double jd) {
    return ASTC_JDToMSDprec(jd, 0.00014);
}

/*! Convert a Mars Sol Date (MSD) to Julian date
  See: https://en.wikipedia.org/wiki/Timekeeping_on_Mars
  See also \ref ASTC_MSDToJDprec().
  @param msd MSD, Mars Sol Date
  @return julian date
*/
double ASTC_MSDToJD(double msd) {
    return ASTC_MSDToJDprec(msd, 0.00014);
}

// ------- Degrees & decimals (angles, time hms)  ---------------
/*! Convert degree, minutes, seconds into decimal value
  See also \ref ASTC_decimalToDegree
  @param d degrees (int)
  @param m minutes (int)
  @param s seconds (real)
  @return decimal equivalent D.dddd
*/
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


/*! Convert decimal degree value to degree, minutes, seconds
  See also \ref ASTC_degreeToDecimal
  @param de decimal degree D.dddd
  @param d degrees (int*)
  @param m minutes (int*)
  @param s seconds (double*)
*/
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

// ------- Coordinate systems (cartesian, spherical) ------------

const double π = 3.14159265358979323846;

/*           z
             |
             |      o P
             |  r / |
             |   /  |
             | / ϑ  |
             +——————————————————y
            / \     |      .
          /.φ...\   |    .
        /        \  |  . 
      /............\|.
     x
     Azimuth   φ is angle from x towards y (counter-clockwise) in x-y plane, 
     Elevation ϑ is angle from x-y plane towards z-axis
     Radius    r is distance from P to origin.
 */

/*! Convert cartesian into spherical coordinates
  See also \ref ASTC_sphericalToCartesian (inverse)
  and \ref ASTC_C2P (vector version)
  @param x x-coordinate
  @param y y-coordinate
  @param z z-coordinate
  @param r pointer to radius, calculated
  @param ϑ pointer to elevation, angle on x-y plane towards z-axis
  @param φ pointer to azimuth, angle from x towards y (counter-clockwise in x-y plane
 */
void ASTC_cartesianToSpherical(double x, double y, double z, double *r, double *ϑ, double *φ) {
    if (r) *r=sqrt(x*x+y*y+z*z);
    if (ϑ) *ϑ=atan2(z,sqrt(x*x+y*y));
    if (φ) *φ=atan2(y,x);
}

/*! Convert sperical into cartesian coordinates
  See also \ref ASTC_cartesianToSpherical (inverse)
  and \ref AST_P2C (vector version)
  @param r radius
  @param ϑ elevation, angle on x-y plane towards z-axis
  @param φ azimuth, angle from x towards y (counter-clockwise in x-y plane)
  @param x pointer to x-coordinate, calculated
  @param y pointer to y-coordinate
  @param z pointer to z-coordinate
 */
void ASTC_sphericalToCartesian(double r, double ϑ, double φ, double *x, double *y, double *z) {
    if (x) *x=r*cos(ϑ)*cos(φ);
    if (y) *y=r*cos(ϑ)*sin(φ);
    if (z) *z=r*sin(ϑ);
}

/*! Convert cartesian vector [x,y,z] into spherical coordinates vector [r,ϑ,φ]
  See also \ref ASTC_cartesianToSpherical (scalar version)
  and \ref ASTC_P2C (inverse)
  Both r and x must be double[3] arrays with 3 elements.
  @param x IN x[0]: x, x[1]: y, x[2]: z-coordinate
  @param r OUT r[0]: radius, r[1]: ϑ elevation, angle on x-y plane towards z-axis, r[2]: φ azimuth, angle from x towards y (counter-clockwise in x-y plane)
 */
void ASTC_C2P(const double x[], double r[]) {
    ASTC_cartesianToSpherical(x[0],x[1],x[2],&(r[0]),&(r[1]),&(r[2]));
}

/*! Convert sperical vector [r,ϑ,φ] into cartesian coordinates vector [x,y,z]
  See also \ref ASTC_sphericalToCartesian (scalar version)
  and \ref ASTC_C2P (inverse)
  Both r and x must be double[3] arrays with 3 elements.
  @param r IN r[0]: radius, r[1]: ϑ elevation, angle on x-y plane towards z-axis, r[2]: φ azimuth, angle from x towards y (counter-clockwise in x-y plane)
  @param x OUT x[0]: x, x[1]: y, x[2]: z-coordinate
 */
void ASTC_P2C(const double r[], double x[]) {
    ASTC_sphericalToCartesian(r[0], r[1], r[2], &(x[0]), &(x[1]), &(x[2]));
}

/*! Convert elements of vector d with len elements from degrees (360deg) to radian (2π)
  See also \ref ASTC_R2D (inverse) and
  \ref ASTC_P2D (act on sperical coordinates ϑ,φ of vector [r,ϑ,φ]
  @param d double vector of lenght len
  @param len number of elements in vector d
*/
void ASTC_D2R(double d[], int len) {
    for (int i=0; i<len; i++) {
        d[i]=d[i]*π/180.0;
    }
}

/*! Convert elements of vector d with len elements from radian (2π) to degrees (360deg)
  See also \ref ASTC_D2R (inverse) and
  \ref ASTC_D2P (act on sperical coordinates ϑ,φ of vector [r,ϑ,φ]
  @param d double vector of lenght len
  @param len number of elements in vector d
 */
void ASTC_R2D(double r[], int len) {
    for (int i=0; i<len; i++) {
        r[i]=r[i]*180.0/π;
    }
}

/*! Convert elements ϑ,φ of spherical coordinates vector d with
  elements [r,ϑ,φ] from degrees (360deg) to radian (2π)
  r (element at 0) remains unchanged.
  See also \ref ASTC_P2D (inverse) and
  \ref ASTC_D2R (general degree to radian conversions)
  @param d double vector of lenght 3 containing [r,ϑ,φ]
*/
void ASTC_D2P(double d[]) {
    for (int i=1; i<3; i++) {
        d[i]=d[i]/180.0*π;
    }
}

/*! Convert elements ϑ,φ of spherical coordinates vector d with
  elements [r,ϑ,φ] from radian to degrees
  r (element at 0) remains unchanged.
  See also \ref ASTC_D2P (inverse) and
  \ref ASTC_R2D (general radian to degree conversions)
  @param d double vector of lenght 3 containing [r,ϑ,φ]
*/
void ASTC_P2D(double p[]) {
    for (int i=1; i<3; i++) {
        p[i]=p[i]*180.0/π;
    }
}
