#include <16F877a.h>
#device ADC = 10
#use delay(crystal = 20000000)
#FUSES NOWDT, NOBROWNOUT, NOLVP, NOPROTECT, HS, NOPUT

#define LCD_ENABLE_PIN  PIN_A3                                    ////
#define LCD_RS_PIN      PIN_A5                                    ////
#define LCD_RW_PIN      PIN_A4                                    ////
#define LCD_DATA4       PIN_D4                                    ////
#define LCD_DATA5       PIN_D5                                    ////
#define LCD_DATA6       PIN_D6                                    ////
#define LCD_DATA7       PIN_D7 
#include <lcd.c>
#use STANDARD_IO(B)

#define LED PIN_A0

int16 contador;

#INT_TIMER1
void t1_isr(){
   contador++;
   set_timer1(0); 
}

void main()
{
   lcd_init();
   
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8); 
   enable_interrupts(INT_TIMER1);
   float tiempo_ms;
   int16 pulsos;
   
   while (TRUE)
   {
      while(input(PIN_B0)==1){delay_us(100);}
      printf(lcd_putc,"\fContando");
      contador=0;
      set_timer1(0);
     
      enable_interrupts(GLOBAL);
      while(input(PIN_B0)==0){delay_us(1000);}
      disable_interrupts(GLOBAL);
      pulsos = get_timer1(); 
      tiempo_ms = (float)pulsos * 0.0016 + (float) contador * 104.2;
      printf(lcd_putc,"\f%f ms",tiempo_ms);
      printf(lcd_putc,"\n%lu %lu", pulsos, contador);
      delay_ms(1000);

      output_high(LED);
      delay_ms((int16) tiempo_ms);
      output_low(LED);
   }
}
