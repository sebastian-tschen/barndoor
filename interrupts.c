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

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* Baseline devices don't have interrupts. Note that some PIC16's 
 * are baseline devices.  Unfortunately the baseline detection macro is 
 * _PIC12 */
#ifndef _PIC12

bool newToggleValue = true;


extern bool newTimerCompareValue;
extern int newIntermediateHighValue;
extern int newIntermediateLowValue;

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
        RC3 = true;;
        
        //activate Timer2 to lower flank in about 
        TMR2ON=1;
        
        if (newTimerCompareValue) {
            CCPR1H = newIntermediateHighValue;
            CCPR1L = newIntermediateLowValue;
            newTimerCompareValue = false;
        }
    }
    
    if (TMR2IF){
        
        TMR2IF=0;
        RC3=false;
        TMR2ON=0;
        TMR2=0;
        
    }


}
#endif


