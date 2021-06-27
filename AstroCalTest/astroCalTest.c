#include <stdio.h>
#include "astrocal.h"

int testTime() {
    int err=0;
    printf("--- Time tests -------------------------------\n");
    struct timespec ts;
    ts=ASTC_currentTimeUTC(); // test
    ASTC_printTime(ts);
    ASTC_printLocalTime(ts);
    double dts=ASTC_timespecToDouble(ts);
    printf("DTS=%f\n",dts);
    struct timespec ts1;
    ts1=ASTC_doubleToTimespec(dts);
    double dt2=ASTC_timespecToDouble(ts1);
    if (dts != dt2) {
        ++err;
        printf("Timespec / double conversion failure\n");
    }
    ASTC_printLocalTime(ts1);
    double jd=ASTC_timespecToJD(ts);
    struct timespec ts2=ASTC_JDToTimespec(jd);
    printf("Julian date: %f\n",jd);
    ASTC_printLocalTime(ts2);

    double msd=ASTC_JDToMSD(jd);
    printf("Mars Sol Date: %f\n", msd);
    double jd2=ASTC_MSDToJD(msd);
    printf("Back to JD: %f\n", jd2);
    if (jd2 != jd) {
        ++err;
        printf("back-conversion failed!\n");
    }
    return err;
}

int testDegree(double dd) {
    int d,m;
    double s,dd2;
    ASTC_decimalToDegree(dd, &d, &m, &s);
    dd2=ASTC_degreeToDecimal(d,m,s);
    printf("%f -> %d:%d:%f -> %f\n",dd,d,m,s,dd2);
    if (fabs(dd-dd2)>0.0001) {
        printf("Error converting %f degree/decimal!\n",dd);
        return 1;
    }
    return 0;
}

int testDegreeDec() {
    int err = 0;
    printf("--- Degree <-> decimal tests -----------------\n");
    err+=testDegree(15.5);
    err+=testDegree(-8.15278);
    err+=testDegree(0.01667);
    err+=testDegree(-0.08334);
    return err;
}

int main(int argc, char *argv[]) {
    int err=0;
    err += testTime();
    err += testDegreeDec();
    printf("--- Result  ----------------------------------\n");
    printf("%d Errors\n",err);
    return err;
}
