// Receptor
#include <16F877a.h>
#device ADC=10
#use delay(crystal=20Mhz)
#FUSES NOWDT, NOBROWNOUT, NOLVP

// Directiva para usar el puerto USART
//#use rs232(BAUD=9600, XMIT = PIN_C6, RCV=PIN_C7)

#define led PIN_A0

#use standard_io(A)

#define carga 93

#INT_TIMER0
void timer0_interruption()
{
   output_toggle(led);
   set_timer0(carga);
}
   
void main(){
   //setup_uart(9600); //Configurar baudios

   setup_timer_0(RTCC_INTERNAL | RTCC_DIV_256);
   // Habilitar interrupciones
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   set_timer0(carga);
   while(TRUE)
   {
   }

}
