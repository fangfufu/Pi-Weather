#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lowlevel.h"
#include "darlington.h"

/**
 * @return 0 on success
 */
int main(int argc, const char *argv[])
{
    if (argc == 1) {
        fprintf(stderr,
                "Usage: Pi-Water CUP\n1 CUP = running the pump for 14 seconds\n" );
        exit(-1);
    }
    double cup = atof(argv[1]);
    int sec = cup * 14;
    if (sec == 0) {
        fprintf(stderr,
                "Please supply a valid number.\n" );
        exit(-2);
    }
    printf("Turing on the pump for %d seconds...", sec);
    exp_open();
    int r = 0;
    r += darlington_on(1);
    r += darlington_on(2);
    r += darlington_on(3);
    r += darlington_on(4);
    sleep(sec);
    r += darlington_off(1);
    r += darlington_off(2);
    r += darlington_off(3);
    r += darlington_off(4);
    exp_close();
    printf("Done!\n");
    return r;
}
