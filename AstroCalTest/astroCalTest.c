#include <stdio.h>
#include "astrocal.h"

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
}
