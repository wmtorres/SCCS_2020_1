/******************************************************************************
 * Nome do Arquivo:	main.c
 * Dependencias:	
 * Processador:		PIC18F4550
 * Opção de Clock:	HS 20MHz (externo) - CPU: 48MHz
 * Compilador:		XC8 
 *
 * Autor:			Weslley M. Torres
 *
 * Data:			v1 - 08/March/2020 - Initial revision 
 *
 * Descrição:       Funções main
 * 
 * Notas:
 *	
 *****************************************************************************/
 
 
 
/************************I N C L U D E S *************************************/

#include "Config.h"
#include "Hardware.h"
#include "displayLCD.h"

/*****************************************************************************/


/************************ Function Prototypes ********************************/
void TaskLED_RB0( void );

/*****************************************************************************/


/************************ Variaveis ******************************************/

uint16_t TimerBreathingLight = 0;
uint16_t TimerTaskLED_RB0 = 0;

/*****************************************************************************/


/**
 *  \brief ISR
 *  
 *  \return none
 *  
 *  \details Interrupt service routine (be careful snce PIC has only one interrupt vector, based on that, the way you check the 	interrupt flag will be the priority)
 */
void interrupt isr(void)
{
    	
    //check if Timer0 interupt was triggered
	if (TMR0IF && T0IF)   
    {
        T0IF = 0;                 //set trigger for Timer0 interrupt (so it can be generated again)
        INTCONbits.TMR0IF = 0;   
        TMR0 = TIMER0_INIT_VALUE; //Set initial value of TMR0 register (for counting 1ms, as we need)	

        if(TimerBreathingLight)     TimerBreathingLight--;
        if(TimerBreathingLight <= 0)
        {
             LATBbits.LATB4 = ~LATBbits.LATB4;
             TimerBreathingLight = 100;
        }
        
    }   
}


 /**
 *  \brief main
 *  
 *  \return none
 *  
 *  \details Main function of the system
 */
void main(void) 
{


	uint8_t MsgPrimLinha[17] = "  TAPM Exp. I ";
	uint8_t MsgSegLinha[17] =  "   09/03/20   ";
        
	InitHardware();
    
    ConfiguraLCD();         
 
    
	/* Write welcome screen on LCD line 1 */
	PosicaoCursorLCD(1,0);
	EscreveFraseRamLCD(MsgPrimLinha);
	
    /* Write welcome screen on LCD line 2 */
	PosicaoCursorLCD(2,0);
	EscreveFraseRamLCD(MsgSegLinha);

    
    while(True)                      
    {
        TaskLED_RB0();
    }
}


void TaskLED_RB0( void )
{

	if(TimerTaskLED_RB0 == 0)
	{
		TimerTaskLED_RB0 = TIMER_500ms;
		LED_RB0 = ~LED_RB0;
	}
}