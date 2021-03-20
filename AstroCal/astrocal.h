#include <time.h>
#include <stdio.h>

struct timespec ASTC_currentTimeUTC();
void ASTC_printTime(const struct timespec ts);
void ASTC_printLocalTime(const struct timespec ts);
