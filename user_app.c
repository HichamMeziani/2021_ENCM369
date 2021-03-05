/*!*********************************************************************************************************************
@file user_app.c                                                                
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void UserApp1Initialize(void)
- void UserApp1Run(void)


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u8 G_u8UserAppFlags;                             /*!< @brief Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp_<type>" and be declared as static.
***********************************************************************************************************************/


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserAppInitialize(void)

@brief
Initializes the application's variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE

*/
void UserAppInitialize(void)
{
/* LED Initialization */
    
    LATA = 0x80;
    
    /*Timer0 Control Register initialization to turn timer on ---  Asynch mode , (16-bit*Fosc)/4 , 1:16 prescaler 
     , 1:1 postscalar  */
    
    T0CON0 = 0X90;
    T0CON1 = 0X54;        

} /* end UserAppInitialize() */

  
/*!----------------------------------------------------------------------------------------------------------------------
@fn void UserAppRun(void)

@brief Application code that runs once per system loop

Requires:
- 

Promises:
- 

*/
void UserAppRun(void)
{
    int i = 0;
    u8 au8Pattern[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20};
    static u16 u16Counter = 0x00;
    

if(u16Counter == 0x3E8)
{
    if (i < 6)
    {
        LATA = au8Pattern[i];
        i++;       
    }
    if (i == 6)
    {
        i = 0;
    }
    
    u16Counter++;
}
    
}
    

 /* end UserAppRun */



/*--------------------------------------------------------------------
void TimeXus(INPUT_PARAMETER_)
Sets Timer0 to count u16Microseconds_
Requires:
- Timer0 configured such that each timer tick is 1 microsecond
- INPUT_PARAMETER_ is the value in microseconds to time from 1 to 65535
Promises:
- Pre-loads TMR0H:L to clock out desired period
- TMR0IF cleared
- Timer0 enabled
*/
void TimeXus(u16 u16Microseconds)
{
/* OPTIONAL: range check and handle edge cases */
    
  T0CON0 &= 0x7F;  // Disabling the timer during config 
  u16 u16timer = 0x00FF - u16Microseconds;
  
  
  /* Preloading TMR0H and TMR0L based on u16TimeXus */        
  TMR0L = (u8) ((u16timer >> 8) & 0x00FF);   
  TMR0H = (u8) (u16timer & 0x00FF);  
             
  /* Clearing TMR0IF and enable Timer 0 */
  PIR3 = 0x7F;
  T0CON0 |= 0x80; 
  
  
} /* end TimeXus () */


/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/





/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
