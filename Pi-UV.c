#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lowlevel.h"
#include "darlington.h"

int main(int argc, const char *argv[])
{
    if (argc == 1) {
        fprintf(stderr,
                "Usage: Pi-UV UP_SECOND DOWN_SECOND\n" );
        exit(-1);
    }
    int up = atoi(argv[1]);
    int down = atoi(argv[2]);
    printf("up: %d, down: %d\n", up, down);
    exp_open();
    int r = 0;
    while(1) {
        r += darlington_off(1);
        r += darlington_on(1);
        printf("up\n");
        sleep(up);
        r += darlington_off(1);
        printf("down\n");
        sleep(down);
    }
    exp_close();
    printf("Done!\n");
    return r;
}
