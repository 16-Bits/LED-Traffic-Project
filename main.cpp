/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "LEDCube.h"
#include <chrono>

int lightSeq[24][8] = {
    /*
    Four Way Intersection Light Layout:

        L1 L2
                L3
    L8          L4
    L7
          L6 L5

    Light Sequence Array:
    red = R, yellow = Y, green = G
    {L1, L2, L3, L8, L4, L7, L6, L5} // tick #
    */
    {'G', 'R', 'R', 'R', 'R', 'R', 'R', 'G'}, // 0
    {'G', 'R', 'R', 'R', 'R', 'R', 'R', 'Y'}, // 1
    {'G', 'G', 'R', 'R', 'R', 'R', 'R', 'R'}, // 2
    {'Y', 'G', 'R', 'R', 'R', 'R', 'R', 'R'}, // 3
    {'R', 'G', 'R', 'R', 'R', 'R', 'G', 'R'}, // 4
    {'R', 'Y', 'R', 'R', 'R', 'R', 'Y', 'R'}, // 5
    {'R', 'R', 'G', 'R', 'R', 'G', 'R', 'R'}, // 6
    {'R', 'R', 'G', 'R', 'R', 'Y', 'R', 'R'}, // 7
    {'R', 'R', 'G', 'R', 'G', 'R', 'R', 'R'}, // 8
    {'R', 'R', 'Y', 'R', 'G', 'R', 'R', 'R'}, // 9
    {'R', 'R', 'R', 'G', 'G', 'R', 'R', 'R'}, // 10
    {'R', 'R', 'R', 'Y', 'Y', 'R', 'R', 'R'}, // 11
    {'G', 'R', 'R', 'R', 'R', 'R', 'R', 'G'}, // 12
    {'Y', 'R', 'R', 'R', 'R', 'R', 'R', 'G'}, // 13
    {'R', 'R', 'R', 'R', 'R', 'R', 'G', 'G'}, // 14
    {'R', 'R', 'R', 'R', 'R', 'R', 'G', 'Y'}, // 15
    {'R', 'G', 'R', 'R', 'R', 'R', 'G', 'R'}, // 16
    {'R', 'Y', 'R', 'R', 'R', 'R', 'Y', 'R'}, // 17
    {'R', 'R', 'G', 'R', 'R', 'G', 'R', 'R'}, // 18
    {'R', 'R', 'Y', 'R', 'R', 'G', 'R', 'R'}, // 19
    {'R', 'R', 'R', 'G', 'R', 'G', 'R', 'R'}, // 20
    {'R', 'R', 'R', 'G', 'R', 'Y', 'R', 'R'}, // 21
    {'R', 'R', 'R', 'G', 'G', 'R', 'R', 'R'}, // 22
    {'R', 'R', 'R', 'Y', 'Y', 'R', 'R', 'R'}  // 23
};

Ticker ticker;
const chrono::seconds lightTimeSec(1);

int main() {
    initSPI();
    printf("Begin\n\r");
    while(1){
        printf("Loop Start\n\r");
        for(int i = 0; i < 24; i++){
            writeSeq(lightSeq[i]);
            //ThisThread::sleep_for(lightTimeSec);
        }
    }

}

