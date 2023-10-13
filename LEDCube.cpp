#include "mbed.h"
#include "LEDCube.h"
#include <chrono>

DigitalInOut green(PA_0);
DigitalInOut yellow(PA_1);
DigitalInOut red(PA_4);

DigitalOut slave(D10);//ds (pin 14)
SPI spi(D11, D12, D13);
//d11 -> st_cp (pin 12), d13 -> sh_cp (pin 11)


void initSPI(){
    green.output();
    yellow.output();
    red.output();
    green.mode(OpenDrain);
    yellow.mode(OpenDrain);
    red.mode(OpenDrain);
    red = 1;
    yellow = 1;
    green = 1;

    slave = 1;//deselect register
    spi.format(16, 3);//16bit data, hi clock
    spi.frequency(100000);//1MHz clock rate
    slave = 0;//select register
    spi.write(0b0000000000000000);//turn off all LEDs
    slave = 1;
    ThisThread::sleep_for(chrono::seconds(1));
}

void writeRaw(int data){

    slave = 0;//select register
    spi.write(data);
    slave = 1;//deselect register
}


void writeSeq(int seq[8]){
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
    int redIndex[9];
    int yellowIndex[9];
    int greenIndex[9];
    //parallel colors
    for (int i = 0; i < 9; i++){
        //printf("%c, ", seq[i]);
        if (i == 4){//skip middle led
            redIndex[i] = 0;
            yellowIndex[i] = 0;
            greenIndex[i] = 0;
        }
        else if (i < 4){
            switch(seq[i]) {
            case 'R':
                redIndex[i] = 1;
                yellowIndex[i] = 0;
                greenIndex[i] = 0;
                break;
            case 'Y':
                redIndex[i] = 0;
                yellowIndex[i] = 1;
                greenIndex[i] = 0;
                break;
            case 'G':
                redIndex[i] = 0;
                yellowIndex[i] = 0;
                greenIndex[i] = 1;
                break;
            default:
                redIndex[i] = 0;
                yellowIndex[i] = 0;
                greenIndex[i] = 0;
            }
        }
        else if (i > 4){
            switch(seq[i]) {
            case 'R':
                redIndex[i] = 1;
                yellowIndex[i] = 0;
                greenIndex[i] = 0;
                break;
            case 'Y':
                redIndex[i] = 0;
                yellowIndex[i] = 1;
                greenIndex[i] = 0;
                break;
            case 'G':
                redIndex[i] = 0;
                yellowIndex[i] = 0;
                greenIndex[i] = 1;
                break;
            default:
                redIndex[i] = 0;
                yellowIndex[i] = 0;
                greenIndex[i] = 0;
            }
        }
    }
    //printf("\n\n\r");
    //build binary write data for shift registers
    int redData = 0b0;
    int yellowData = 0b0;
    int greenData = 0b0;
    for (int i = 0; i < 9; i++){
        if(redIndex[i] == 1){
            //printf("r[%d]:%d\n\r", i, redIndex[i]);
            redData += (0b00000001 << (8 - i));// bitshift to get as leftmost as possible
        }
        if(yellowIndex[i] == 1){
            //printf("y[%d]:%d\n\r", i, yellowIndex[i]);
            yellowData += (0b00000001 << (8 - i));// bitshift to get as leftmost as possible
        }
        if(greenIndex[i] == 1){
            //printf("g[%d]:%d\n\r", i, greenIndex[i]);
            greenData += (0b00000001 << (8 - i));// bitshift to get as leftmost as possible
        }
        /*
        printf("%d\n\r", i);
        printf("r:%d\n\r", redData);
        printf("y:%d\n\r", yellowData);
        printf("g:%d\n\r", greenData);
        */
    }
    //printf("Write Data Done\n\r");
    /*
    Ticker tick;
    tick.attach(&lightLED, chrono::milliseconds(1));
    while(1){
        ThisThread::sleep_for(chrono::seconds(2));
    }
    */
    for(int i = 0; i < 1000; i++){
    green=0;
    writeRaw(greenData);
    writeRaw(0);
    ThisThread::sleep_for(chrono::milliseconds(1));
    green=5;

    yellow=0;
    writeRaw(yellowData);
    writeRaw(0);
    ThisThread::sleep_for(chrono::milliseconds(1));
    yellow=5;

    red=0;
    writeRaw(redData);
    writeRaw(0);
    ThisThread::sleep_for(chrono::milliseconds(1));
    red=5;





    }
}

