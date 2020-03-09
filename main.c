/**
 *  \file main.c
 *  \brief Implementa projeto de SCCS
 */
 

#include "Config.h"
#include "displayLCD.h"
#include "eeprom.h"
#include "adc.h"

void InicializaHardware ( void ) ;
void InicializaInterrupts( void );
void OdometroParcial(void);
void OdometroTotal(void);

unsigned char AtualizaOdoParcial;
unsigned char AtualizaOdoTotal;
unsigned int TimerBreathingLight = 0;

/**
 *  \brief void InicializaHardware ( void )
 *  
 *  \return Nenhum
 *  
 *  \details Inicializa perifericos e postas do microcontrolador
 */ 
void InicializaHardware ( void )  
{
    
    TRISA = 0xFF;
    TRISB = 0x00;
    TRISC = 0xFF;
    TRISD = 0x00;
    TRISE = 0xFF;
       
    LATA = 0x00;
    LATB = 0xFF;
    LATC = 0x00;
    LATD = 0x00;
    LATE = 0x00;
    
    ADCON0bits.ADON = 1;// habilita conversor
    ADCON1 = 0x0D;
    ADCON2bits.ADFM = 1;
    ADCON2bits.ADCS0 = 0;
    ADCON2bits.ADCS1 = 1;
    ADCON2bits.ADCS2 = 1;
    ADCON2bits.ACQT0 = 0;
    ADCON2bits.ACQT1 = 1;
    ADCON2bits.ACQT2 = 1;
}

/**
 *  \brief void InicializaInterrupts( void )
 *  
 *  \return Nenhum
 *  
 *  \details Inicializa interrupções do microcontrolador
 */
void InicializaInterrupts( void )
{
    INTCON = 0b11100000;
    INTCON2 = 0b10000000;
    INTCON3 = 0b00000000; 
    PIR1 = 0b00000000;
    PIR2 = 0b00000000;
    PIE1 = 0b00000100;
    PIE2 = 0b00000000;
    IPR1 = 0b00000000;
    IPR2 = 0b00000000;
    RCON = 0b00000000;
    CCP1CON = 0b00000101;
}

/**
 *  \brief void interrupt isr (void)
 *  
 *  \return Nenhum
 *  
 *  \details Implementa o processamento das interrupções de CCP e Timer0
 */
void interrupt isr (void)
{
    if(CCP1IF && CCP1IE)
    {
        CCP1IF = 0;
    }
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
 *  \brief void OdometroParcial(void)
 *  
 *  \return Nenhum
 *  
 *  \details Implementa a lógica para o Odometro Parcial
 */
void OdometroParcial(void)
{ 
    if(AtualizaOdoParcial==1 )
    {
        AtualizaOdoParcial = 0;
        
    }
     
}


/**
 *  \brief void OdometroTotal(void)
 *  
 *  \return Nenhum
 *  
 *  \details Implementa a lógica para o Odometro Total
 */
void OdometroTotal(void)
{ 

    if(AtualizaOdoTotal==1 )
    {
        AtualizaOdoTotal = 0;
    }
    
}           

/**
 *  \brief void main(void)
 *  
 *  \return Nenhum
 *  
 *  \details Função principal
 */
void main(void)
{
	InicializaHardware();
	InicializaInterrupts();
	Init_EEPROM();
	ConfiguraLCD();


	while (1)
	{ 

	}
}


