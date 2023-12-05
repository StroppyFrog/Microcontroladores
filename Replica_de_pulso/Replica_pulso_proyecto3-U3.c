#include <16F877a.h>
#device ADC = 10
#use delay(crystal = 20000000)
#FUSES NOWDT, NOBROWNOUT, NOLVP, HS

#include <lcd_d.c>
#include <kbd4x4_d.c>
#include <getNum16.c>

#use STANDARD_IO(A)
#use STANDARD_IO(B)
#use STANDARD_IO(C)

#define LED PIN_A0

int16 contador;

#INT_TIMER1
void t1_isr(){
   contador++;
   set_timer1(0); // Volver a comenzar conteo de timer
}

void main()
{
   // Inicializar pines
   lcd_init();
   kbd_init();
   //port_b_pullups(TRUE);
   
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8); // Configuración del t1
   enable_interrupts(GLOBAL);
   float tiempo_ms;
   int16 pulsos;
   
   while (TRUE)
   {
   printf(lcd_putc,"\fsi jala XD");
      while(input(PIN_B0)==0){}
      contador=0;
      enable_interrupts(INT_TIMER1);
      set_timer1(0); // Inicio del conteo
      while(input(PIN_B0)){}
      disable_interrupts(INT_TIMER1);
       pulsos = get_timer1(); // Obtener registros
      tiempo_ms = (float)pulsos * 0.0016 + (float) contador * 104.2; // Pendiente: agregar lógica del contador
      printf(lcd_putc,"\f%f ms",tiempo_ms); // Mostrar tiempo en ms
      delay_ms(2000);
      
     

      output_high(LED);
      delay_ms((int16) tiempo_ms);
      output_low(LED);
   }
}
