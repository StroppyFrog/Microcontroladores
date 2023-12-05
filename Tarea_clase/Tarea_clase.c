#include <16F877a.h>
#device ADC=10
#use delay(crystal=20Mhz)
#FUSES NOWDT, NOBROWNOUT, NOLVP

#include <lcd_d.c> //Incluir librer�a LCD
#include <kbd4x4_b.c>
#include <getNum16.c>

#USE STANDARD_IO(A)
#define LED PIN_A1

#INT_TIMER1
void desborde_timer_1()
{
   printf(lcd_putc,"\fQue siempre si\nuwu");
}


void main(){
   lcd_init(); //Inicializar pantalla
   kbd_init();
   
   output_low(LED);
   
   setup_timer_1(T1_EXTERNAL | T1_DIV_BY_1);
   enable_interrupts(INT_TIMER1);
   enable_interrupts(GLOBAL);
 
   set_timer1(65532); // 65536 + 1


   printf(lcd_putc,"\fSin nada \nque hacer");
   while(1){

   } // while
}
