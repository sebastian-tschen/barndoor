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

int FastForwardSpeed = 55;
int debounceCounter = 21;

void setNewTimerCompareValue(int pNewLow, int pNewHigh) {

    //wait for new value to be set by interrupt
    while (newTimerCompareValue) {

    }
    newIntermediateHighValue = pNewHigh;
    newIntermediateLowValue = pNewLow;

    newTimerCompareValue = true;


}

void stopMotor(void) {

    if (motorRunning) {
        newTimerCompareValue = false;
        TMR1ON = false;
        RD3 = false;
        motorRunning = false;
    }
}

void startMotor(void) {

    if (!motorRunning) {
        TMR1H = 0;
        TMR1L = 0;
        CCPR1H = newIntermediateHighValue;
        CCPR1L = newIntermediateLowValue;
        newTimerCompareValue = false;
        TMR1ON = true;
        RD3 = true;
        motorRunning = true;
    }
}

bool debounceRB5(void) {

    int lastValue = RB5;
    int counter = 0;

    while (lastValue != RB5 || counter < debounceCounter) {
        if (lastValue == RB5) {
            counter++;
        } else {
            lastValue = RB5;
            counter = 0;
        }
        __delay_ms(1);
    }

    return lastValue;

}

bool debounceRB1(void) {

    int lastValue = RB1;
    int counter = 0;

    while (lastValue != RB1 || counter < debounceCounter) {
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

bool debounceRB2(void) {

    int lastValue = RB2;
    int counter = 0;

    while (lastValue != RB2 || counter < debounceCounter) {
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

bool debounceRB4(void) {

    int lastValue = RB4;
    int counter = 0;

    while (lastValue != RB4 || counter < debounceCounter) {
        if (lastValue == RB4) {
            counter++;
        } else {
            lastValue = RB4;
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


        //wait for button to be pressed
        while (RB1 == true && RB2 == true && RB4 == true && RB5 == true) {
            RD1 = RB1;
            RD2 = RB3;
            RD4 = RB4;
            RD5 = RB5;

        }

        //        check which button was pressed
        if (!RB5) {

            debounceRB5();
            if (motorRunning) {
                stopMotor();
            } else {
                RC4 = false;
                setNewTimerCompareValue(0x63, 1);
                startMotor();
            }
            while (RB5 == false) {
            }
            debounceRB5();

            //        }

        } else if (!RB1) {

            if (!motorRunning) {
                //fast forward
                debounceRB1();
                RC4 = false;
                setNewTimerCompareValue(FastForwardSpeed, 0);
                startMotor();
                while (RB1 == false) {

                }
                stopMotor();
            }


        } else if (!RB2) {


            if (!motorRunning) {
                debounceRB2();

                RC4 = true;
                setNewTimerCompareValue(FastForwardSpeed, 0);
                startMotor();
                while (RB2 == false) {

                }
                stopMotor();
            }


        }

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

