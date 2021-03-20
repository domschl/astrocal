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
