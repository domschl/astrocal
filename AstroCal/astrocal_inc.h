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

void ASTC_cartesianToSpherical(double x, double y, double z, double *r, double *ϑ, double *φ);
void ASTC_sphericalToCartesian(double r, double ϑ, double φ, double *x, double *y, double *z);
void ASTC_C2P(const double x[], double r[]);
void ASTC_P2C(const double r[], double x[]);
void ASTC_D2R(double d[], int len);
void ASTC_R2D(double r[], int len);
void ASTC_P2D(double p[]);
void ASTC_D2P(double d[]);

double ASTC_latLonDistance(double lat1, double lon1, double lat2, double lon2, double r);
double ASTC_latLonDistanceEarth(double lat1, double lon1, double lat2, double lon2);
double ASTC_latLonDistanceEarthDeg(double lat1, double lon1, double lat2, double lon2);

