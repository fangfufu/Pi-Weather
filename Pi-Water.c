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
                "Usage: Pi-Water TIME\nThe unit for TIME is in seconds.\n" );
        exit(1);
    }
    int sec = atoi(argv[1]);
    if (sec == 0) {
        fprintf(stderr, 
                "Please supply a valid number.\n" );
        exit(2);
    }
    printf("Turing on the pump for %d seconds...", sec);
    exp_open();
            darlington_on(1);
            darlington_on(2);
            darlington_on(3);
            darlington_on(4);
    sleep(sec);
            darlington_off(1);
            darlington_off(2);
            darlington_off(3);
            darlington_off(4);
    exp_close();
    printf("Done!\n");
    return 0;
}
