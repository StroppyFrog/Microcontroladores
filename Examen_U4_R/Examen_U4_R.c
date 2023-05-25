// Receptor
#include <16F877a.h>
#device ADC=10
#use delay(crystal=20Mhz)
#FUSES NOWDT, NOBROWNOUT, NOLVP
// Directiva para usar el puerto USART
#use rs232(BAUD=9600, XMIT = PIN_C6, RCV=PIN_C7)
#include <lcd_d.c> //Incluir librería LCD

int16 NEWPOT1 = 0, OLDPOT1 = 0;
//int16 POT2;
//short Ent = 0;

// Interrupción al recibir una trama
#INT_RDA 
void rda_int()
{
   OLDPOT1 = getc();
   //POT2 = getc();
}

void main()
{
   lcd_init(); //Inicializar pantalla  
   setup_uart(9600); //Configurar baudios
   // Habilitar interrupciones
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   printf(lcd_putc,"\fINICIANDO...");
   while(TRUE)
   {
      if(OLDPOT1 != NEWPOT1)
      {
         OLDPOT1 = NEWPOT1;
         printf(lcd_putc,"\fADC1: %lu\nADC2:",NEWPOT1);
      }
   }
}
