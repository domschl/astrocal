#include <stdio.h>
#include "astrocal.h"

int main(int argc, char *argv[]) {
    struct timespec ts;
    ts=ASTC_currentTimeUTC();
    ASTC_printTime(ts);
    ASTC_printLocalTime(ts);
}