#include <16F877a.h>
#device ADC=10
#use delay(crystal=20Mhz)
#FUSES NOWDT, NOBROWNOUT, NOLVP

#use rs232(BAUD=9600, XMIT = PIN_C6, RCV=PIN_C7)

#include <lcd_d.c> //Incluir librería LCD
#include <kbd4x4_b.c>
#include <getNum16.c>

#INT_RDA
void interrupcion_rda(){
   char caracter = getc();
   putc(caracter);
   putc(caracter+1);
}

void main(){
   lcd_init(); //Inicializar pantalla
   kbd_init();
   
   setup_uart(9600);
   
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   
   while(1){
      putc(':');
      putc(')');
      putc('\n');
      delay_ms(1000);
   } // while
}
