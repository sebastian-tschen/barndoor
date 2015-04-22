/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)



{
    
    
    //set some ports to be outputs
//    TRISC2=false; 
    TRISC3=false; 
    TRISC4=false; 
    TRISD0=false; 
    TRISD1=false; 
    TRISD2=false; 
//    TRISD3=false; 
    TRISD4=false; 
    TRISD5=false; 
    
    
    
    
//    make RB0, RB1 and RB2 inputs (switches)
    TRISB1=1;
    TRISB2=1;
    TRISB0=1;
    TRISB4=1;
    TRISB5=1;
    
//    enable weak pull-ups
    OPTION_REG=0x7F;
//    WPUB0=1;
    WPUB1=1;
    WPUB2=1;
    WPUB4=1;
    WPUB5=1;
    
    //TIMER2 setup
    
    //set 1010 = 1:11 Postscaler
    //0100 = 1:5 Postscaler
    TOUTPS0=0;
    TOUTPS1=0;
    TOUTPS2=0;
    TOUTPS3=0;
    
    //set prescaler
    T2CKPS1=0;
    T2CKPS0=1;
    
    //enable timer2 interrupt
    TMR2IE=1;
    
    //Turn off Timer2
    TMR2ON=0;
            
    
    
    
    
    //set RC4 (direction)
    RC4=1;
    
    
    //enable interrupt for compare event;
    GIE=true;
    PEIE=true;
    CCP1IE=true;

    //set compare mode to special event trigger
    CCP1M3=true;
    CCP1M2=false;
    CCP1M1=true;
    CCP1M0=true;
    
    //set timer1 clock source externally
    TMR1CS=1;
    
    //enable external LP oscillator for timer1 clock source
    T1OSCEN=1;
    
    //sync external LP oscillator;
    T1SYNC=0;
    
    
    //make RA0 analog input
    TRISA0=1;
    ANS0=1;
    
//    make RB0, RB1 and RB2 digital inputs
    ANS10=0;
    ANS8=0;
    ANS12=0;
    ANS11=0;
    ANS13=0;
    //adc reference voltages VDD and VSS
    VCFG1=0;
    VCFG0=0;
    
    
//    ADFM: A/D Conversion Result Format Select bit 
//    1 = Right justified
//      0 = Left justified
    ADFM=1;
//  set adc speed to Fosc/32
    ADCS1=1;
    ADCS0=0;
    //adc channel select RA0
    CHS3=0;
    CHS2=0;
    CHS1=0;
    CHS0=0;
    //enable adc
    ADON=1;
    
    CCPR1H=0;
    CCPR1L=55;
    
    
    
    /* TODO Initialize User Ports/Peripherals/Project here */

    /* Setup analog functionality and port direction */

    /* Initialize peripherals */

    /* Enable interrupts */
}

