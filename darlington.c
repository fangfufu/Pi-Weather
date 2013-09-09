#include <stdio.h>
#include <unistd.h>

#include "lowlevel.h"
#include "darlington.h"

#define DARLINGTON_ON   0x25
#define DARLINGTON_OFF  0x26

int darlington_on(int p) {
    if ( (p < 1) || (p > 4) ) {
        fprintf(stderr, "darlington_on error: invalid pin.\n");
        return 1;
    }
    uint8_t buf[2];
    buf[0] = DARLINGTON_ON;
    buf[1] = p;
    if (exp_write(buf, sizeof(buf)) == 2) {
        return 0;
    }
    return 2;
}

int darlington_off(int p) {
    if ( (p < 1) || (p > 4) ) {
        fprintf(stderr, "darlington_off error: invalid pin.\n");
        return 1;
    }
    uint8_t buf[2];
    buf[0] = DARLINGTON_OFF;
    buf[1] = p;
    if (exp_write(buf, sizeof(buf)) == 2){
        return 0;
    }
    return 2;
}