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

int epsEqual(double a, double b, double ϵ) {
    if (fabs(a-b)<ϵ) return 1;
    else return 0;
}

int testCR(double x, double y, double z) {
    double r, ϑ, φ, x1,y1,z1;
    double xv[3], rv[3], xv1[3],rv1[3];
    int err=0;
    double ϵ=0.000000000001;
    
    ASTC_cartesianToSpherical(x,y,z,&r,&ϑ, &φ);
    printf("x=%f,y=%f,z=%f -> r=%f,ϑ=%f,φ=%f\n",x,y,z,r,ϑ,φ);
    ASTC_sphericalToCartesian(r, ϑ, φ, &x1, &y1, &z1);
    if (!epsEqual(x,x1,ϵ)) {
        ++err;
        printf("error on x-coord transform: %f!=%f,δ=%f\n",x,x1,x-x1);
    }
    if (!epsEqual(y,y1,ϵ)) {
        ++err;
        printf("error on y-coord transform: %f!=%f,δ=%f\n",y,y1,y-y1);
    }
    if (!epsEqual(z,z1,ϵ)) {
        ++err;
        printf("error on x-coord transform: %f!=%f,δ=%f\n",z,z1,z-z1);
    }
    xv[0]=x; xv[1]=y; xv[2]=z;
    ASTC_C2P(xv,rv);
    ASTC_P2C(rv,xv1);
    
    for (int i=0; i<3; i++) {
        rv1[i]=rv[i];
        if (!epsEqual(xv[i], xv1[i], ϵ)) {
            ++err;
            printf("error on x[%d]-coord transform: %f!=%f, δ=%f\n", i, xv[i], xv1[i],
                   xv[i] - xv1[i]);
        }
    }
    ASTC_P2D(rv);
    ASTC_D2P(rv);
    for (int i=0; i<3; i++) {
        if (!epsEqual(rv[i], rv1[i],ϵ)) {
            ++err;
            printf("radian <-> degree conversion failed for dim %d, %f!=%f, ̣δ=%f\n", i, rv[i],
                   rv1[i], rv[i] - rv1[i]);
        }
    }
    return err;
}

int testCartRad() {
    int err = 0;
    printf("--- Cartesian <-> radian tests ---------------\n");
    err+=testCR(0,0,0);
    err+=testCR(1,0,0);
    err+=testCR(0,1,0);
    err+=testCR(0,0,1);
    err+=testCR(1,1,0);
    err+=testCR(0,1,1);
    err+=testCR(1,0,1);
    err+=testCR(1,1,1);
    err+=testCR(3.14,77.0,100.0);
    err+=testCR(-10,-20,-30);
    return err;
}

int main(int argc, char *argv[]) {
    int err=0;
    err += testTime();
    err += testDegreeDec();
    err += testCartRad();
    printf("--- Result  ----------------------------------\n");
    printf("%d Errors\n",err);
    return err;
}
