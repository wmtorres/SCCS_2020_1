#include "adc.h"
#include "Config.h"

/*Recebe o canal ao qual deve ser feita a conversão adc e retorna o valor convertido*/
unsigned int converte_adc (unsigned char Canal)
{

    unsigned int Resultado;

    ADCON0bits.CHS2 = (Canal >> 2) & 0x01;
    ADCON0bits.CHS1 = (Canal >> 1) & 0x01;
    ADCON0bits.CHS0 = (Canal) & 0x01;
    ADCON0bits.GO = 1;
    
    while(ADCON0bits.GO == 1);
    Resultado = (ADRESH << 8) | ADRESL;
    return (Resultado);

}
