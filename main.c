/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
#include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

#define _XTAL_FREQ 8000000


/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/


int newLow;
int newHigh;
int newRD1Value = 0;
int motorRunning = false;

bool newTimerCompareValue = false;
int newIntermediateHighValue = 0;
int newIntermediateLowValue = 0;

void setNewTimerCompareValue(int pNewLow, int pNewHigh) {

    //wait for new value to be set by interrupt
    while (newTimerCompareValue) {

    }

    newIntermediateHighValue = pNewHigh;
    newIntermediateLowValue = pNewLow;

    newTimerCompareValue = true;


}

void stopMotor(void) {

    TMR1ON = false;
    RD3 = false;
    motorRunning = false;
}

void startMotor(void) {

    TMR1ON = true;
    RD3 = true;
    motorRunning = true;
}

bool debounceRB2(void) {

    int lastValue = RB2;
    int counter = 0;

    while (lastValue != RB2 || counter < 5) {
        if (lastValue == RB2) {
            counter++;
        } else {
            lastValue = RB2;
            counter = 0;
        }
        __delay_ms(1);
    }

    return lastValue;

}

bool debounceRB1(void) {

    int lastValue = RB1;
    int counter = 0;

    while (lastValue != RB1 || counter < 5) {
        if (lastValue == RB1) {
            counter++;
        } else {
            lastValue = RB1;
            counter = 0;
        }
        __delay_ms(1);
    }

    return lastValue;

}

bool debounceRB0(void) {

    int lastValue = RB0;
    int counter = 0;

    while (lastValue != RB0 || counter < 5) {
        if (lastValue == RB0) {
            counter++;
        } else {
            lastValue = RB0;
            counter = 0;
        }
        __delay_ms(1);
    }

    return lastValue;

}

void main(void) {
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    stopMotor();
    //wait for oscillator to settle
    _delay(1000000);
    while (1) {


        //        if (RB0==false){
        //            RD0=true;
        //        }else{
        //            RD0=false;
        //        }

        while (RB0 == true) {//F && RB1 == true && RB2 == true) {
            RD0 = RB0;
            RD1 = RB1;
            RD2 = RB2;
            RD4 = RB4;
            RD5 = RB5;
        }

        //                RD3=false;

        //        if (RB1 == false) {
        //
        //            debounceRB1();
        //            if (motorRunning == false) {
        //                setNewTimerCompareValue(55, 0);
        //                RC4 = true;
        //                startMotor();
        //            }
        //            while (RB1 == false) {
        //            }
        //            stopMotor();
        //        }else
//        if (RB0 == false) {

            debounceRB0();

            while (RB0 == false) {

            }
            debounceRB0();

            if (motorRunning) {
                stopMotor();
            } else {
                
                setNewTimerCompareValue(0x63, 1);
                RC4 = false;
                startMotor();
            }
//        }


    }
}

//   
//        _delay(10000);
//        GO_DONE = 1;
//        _delay(10000);
//        while (GO_DONE == 1);
//
//
//        RD1 = newRD1Value;
//        if (newRD1Value == 0) {
//            newRD1Value = 1;
//        } else {
//            newRD1Value = 0;
//        }
//
//
//
//        newLow = ADRESL;
//        newHigh = ADRESH;
//
//        if (newHigh == 0 && newLow < 55) {
//            newLow = 55;
//        }
//        setNewTimerCompareValue(newLow, newHigh);

