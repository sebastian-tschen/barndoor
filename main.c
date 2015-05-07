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
#include <math.h>

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include "interrupts.h"

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
bool motorRunning = false;
bool fastMode = false;

bool newTimerCompareValue = false;
unsigned short newIntermediateCompareValue = 0;
unsigned long newIntermediateAdditionalStepBase = 0;
unsigned long newIntermediateAdditionalStepFraction = 0;

int FastForwardSpeed = 45;

double SEDIRISCH = 709.929669310441;
double SOLAR = 711.873322419608;
//double LUNAR = 

int debounceCounter = 20;


void stopMotor(void) {

        newTimerCompareValue = false;
        TMR1ON = false;
        RD3 = false;
        motorRunning = false;
}


void startMotor(void) {

    if (!motorRunning && checkEndSwitch()) {
        TMR1H = 0;
        TMR1L = 0;
//        CCPR1 = newIntermediateCompareValue;
//        newTimerCompareValue = false;
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

void setMotorSpeed(unsigned short clocksPerStep, unsigned long additionalStepBase, unsigned long additionalStepFraction, bool direction){
  
    
    //wait for new value to be set by interrupt
    while (newTimerCompareValue) {

    }
    
    RC4=direction;
    newIntermediateCompareValue=clocksPerStep;
    newIntermediateAdditionalStepBase=additionalStepBase;
    newIntermediateAdditionalStepFraction=additionalStepFraction;
    
    newTimerCompareValue = true;
}

void setMotorSpeedSimple(double clocksPerStep, bool direction){
    
    double integerPart, fractionalPart;
    unsigned long base=100000000;
    fractionalPart=modf(clocksPerStep,&integerPart);
    unsigned long additionalStepFraction = (fractionalPart*base);
    unsigned short integerPartShort = integerPart;
    setMotorSpeed(integerPartShort,base,additionalStepFraction,direction);
    
}   

void setMotorSpeedDouble(short clocksPerStep, bool direction){
    setMotorSpeed(clocksPerStep,0,0,direction);
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
        }

        //stop motor if any button is pressed in fast mode;
        if (motorRunning && fastMode){
            stopMotor();
            if (!RB5){
                debounceRB5();
                while(!RB5){}
                debounceRB5();
            }
            if (!RB1){
                debounceRB1();
                while(!RB1){}
                debounceRB1();
            }
            if (!RB2){
                debounceRB2();
                while(!RB2){}
                debounceRB2();
            }
        } 
        //        check which button was pressed
        else if (!RB5) {
            debounceRB5();
            if (motorRunning) {
                stopMotor();
            } else {
                setMotorSpeedDouble(SEDIRISCH,FORWARD);
                fastMode=false;
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
                setMotorSpeedSimple(FastForwardSpeed,REVERSE);
                fastMode=true;
                startMotor();
                while (RB1 == false) {
                }
                debounceRB1;
            }
        } else if (!RB2) {
            if (!motorRunning) {
                debounceRB2();
                setMotorSpeedSimple(FastForwardSpeed,FORWARD);
                fastMode=true;
                startMotor();
                while (RB2 == false) {
                }
                debounceRB2();
            }
        } else if (!RB4) {
            if (!checkEndSwitch()){
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

