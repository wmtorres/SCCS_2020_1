
#include "config.h"
#include "EEPROM.h"

void Init_EEPROM(void)
{
    EECON1 = 0b00000100;
}

unsigned char EEPROM_ReadByte (unsigned char MemoryAddress)
{
    EEADR = MemoryAddress; /*recebe endereço na memória*/
    EECON1 = 0x01;          //seta o bit RD - leitura//
    return (EEDATA);        //Retorna o valor lido na EEPROM//
   
}

void EEPROM_WriteByte(unsigned char WriteMemoryAddress , unsigned char WriteData)
{
    EEADR  = WriteMemoryAddress;     //Recebe endereço na memória    
    EEDATA = WriteData;              //Daa a ser escrito
    EECON1bits.EEPGD = 0;            //Configura regidtrador EECON1 para escrita
    EECON1bits.CFGS = 0;             //Configura registrador EECON1 para escrita
    EECON1bits.WREN = 1;             //Configura registrador EECON1 para escrita
    INTCONbits.GIE = 0;              //Desabilita interruta
    EECON2 = 0x55;                   //Senha #1 para iniciar processo de escrita
    EECON2 = 0xAA;                   //Senha #2 para inciar processo de escrita
    EECON1bits.WR = 1;               //Configura regstrador EECON1 para escrita
    // VOCE ESQUECEDEU DESSA ULTIMA LINHA ACIMA
    
    while(EECON1bits.WR == 1);       //Aguarda o termino da escrita
    
    INTCONbits.GIE  = 1;              //Habilta iterrupções
    EECON1bits.WREN = 0;             //Desabilita premissão da escrita
}    