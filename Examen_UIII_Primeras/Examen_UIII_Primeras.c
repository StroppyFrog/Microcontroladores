#include <16F877a.h>
#device ADC = 10
#use delay(crystal = 20000000)
#FUSES NOWDT, NOBROWNOUT, NOLVP, HS

#include <lcd_d.c>
#include <kbd4x4_b.c>
#include <getNum16.c>

#define senal PIN_A0
#use standard_io(A)
double carga;
int16 frecuencia;

#INT_TIMER1
void timer1_isr()
{
   output_toggle(senal);
   set_timer1(carga);
}

void main()
{
   // Inicializar pines
   lcd_init();
   kbd_init();
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);
   enable_interrupts(INT_TIMER1);
   enable_interrupts(GLOBAL);
   set_timer1(carga);
   port_b_pullups(TRUE);
   //set_timer1(carga);
   //output_low(señal);
   
   while (TRUE)
   {
      printf(lcd_putc,"\f Ingresa freq:"); // Leer velocidad deseada desde el teclado
      frecuencia = get_num_lcd(1,2);
      if(frecuencia >= 5 && frecuencia <= 300)
      {
      }
      else
      {
         printf(lcd_putc,"\fsolo 5 a 300 >:c ");
         delay_ms(3000);
      }
   }
}

