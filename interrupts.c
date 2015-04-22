/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
#include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "interrupts.h"

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* Baseline devices don't have interrupts. Note that some PIC16's 
 * are baseline devices.  Unfortunately the baseline detection macro is 
 * _PIC12 */
#ifndef _PIC12


bool newToggleValue = true;

extern bool newTimerCompareValue;
extern unsigned short newIntermediateCompareValue;
extern unsigned long newIntermediateAdditionalStepBase;
extern unsigned long newIntermediateAdditionalStepFraction;

unsigned long additionalStepFraction;
unsigned long additionalStepBase;

unsigned short origClocks;
unsigned short longClocks;

unsigned long additionalStepCurrentValue;

bool checkEndSwitch() {
    return !(RC4 == REVERSE && !RB4);
}

void interrupt isr(void) {
    /* This code stub shows general interrupt handling.  Note that these
    conditional statements are not handled within 3 seperate if blocks.
    Do not use a seperate if block for each interrupt flag to avoid run
    time errors. */


    /* TODO Add interrupt routine code here. */

    /* Determine which flag generated the interrupt */
    if (CCP1IF) {
        CCP1IF = 0; /* Clear Interrupt Flag 1 */
        //make step
        if (checkEndSwitch()) {
            RC3 = true;
            //        calculate if additional fractional steps
            //set new speed if there is one
            if (newTimerCompareValue) {
                origClocks=newIntermediateCompareValue;
                longClocks=newIntermediateCompareValue+1;
                CCPR1 = origClocks;
                
                additionalStepBase = newIntermediateAdditionalStepBase;
                additionalStepFraction = newIntermediateAdditionalStepFraction;
                additionalStepCurrentValue = 0;
                newTimerCompareValue = false;
            }

            if (additionalStepBase != 0) {
                additionalStepCurrentValue += additionalStepFraction;
                if (additionalStepCurrentValue > additionalStepBase) {
                    CCPR1 = longClocks;
                    additionalStepCurrentValue -= additionalStepBase;
                }else{
                    CCPR1 = origClocks;
                }
            }
            //activate Timer2 to lower flank
            TMR2ON = 1;

            //

        }
    }

    if (TMR2IF) {
        TMR2IF = 0;
        RC3 = false;
        TMR2ON = 0;
        TMR2 = 0;
    }


}
#endif


