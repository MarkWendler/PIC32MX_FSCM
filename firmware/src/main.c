/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include "config/default/bsp/bsp.h"
#include "config/default/peripheral/tmr1/plib_tmr1.h"

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************
void myTmrIntHandler (uint32_t status, uintptr_t context){
    
    LED1_Toggle();
}


int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );

    //FSCMIE is not enabled by harmony. Harmony set only priority.
    IEC0bits.FSCMIE = 1; 
    
    //Overrite default timer int handler, timer runs at 500ms
    TMR1_CallbackRegister(myTmrIntHandler, (uintptr_t)NULL);
    TMR1_Start();
    
    
    while ( true )
    {
        if(OSCCONbits.COSC == 0b011){ 
            LED2_Off(); //oscillator is primary with pll
        }
        else if (OSCCONbits.COSC == 0){
            LED2_On(); //oscillator fall back to FRC
        }
        else{
            LED1_On(); // something is not expected
        }
        
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}

void __ISR(_FAIL_SAFE_MONITOR_VECTOR, ipl1SOFT) FAIL_SAFE_MONITOR_Handler (void)
{
    IFS0CLR = _IFS0_FSCMIF_MASK;
    LED3_On(); //FSCM detected
}


/*******************************************************************************
 End of File
*/

