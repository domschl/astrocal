#include <stdio.h>
#include "astrocal.h"

int testDegree(double dd) {
    int d,m;
    double s,dd2;
    ASTC_decimalToDegree(dd, &d, &m, &s);
    dd2=ASTC_degreeToDecimal(d,m,s);
    printf("%f -> %d:%d:%f -> %f\n",dd,d,m,s,dd2);
    if (fabs(dd-dd2)>0.0001) {
        printf("Error converting %f degree/decimal!\n",dd);
        return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    struct timespec ts;
    ts=ASTC_currentTimeUTC(); // test
    ASTC_printTime(ts);
    ASTC_printLocalTime(ts);
    double dts=ASTC_timespecToDouble(ts);
    printf("DTS=%f\n",dts);
    struct timespec ts1;
    ts1=ASTC_doubleToTimespec(dts);
    ASTC_printLocalTime(ts1);
    double jd=ASTC_timespecToJD(ts);
    struct timespec ts2=ASTC_JDToTimespec(jd);
    printf("Julian date: %f\n",jd);
    ASTC_printLocalTime(ts2);

    double msd=ASTC_JDToMSD(jd);
    printf("Mars Sol Date: %f\n", msd);
    double jd2=ASTC_MSDToJD(msd);
    printf("Back to JD: %f\n", jd2);
    
    testDegree(15.5);
    testDegree(-8.15278);
    testDegree(0.01667);
    testDegree(-0.08334);

    
    
}
