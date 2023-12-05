//Maestro
#include <16F877a.h>
#device ADC = 10
#use delay(crystal = 20000000)
#FUSES NOWDT, NOBROWNOUT, NOLVP, HS

#include <lcd_d.c>
#include <kbd4x4_b.c>
#include <getNum16.c>

#use rs232(BAUD=9600, XMIT = PIN_C6, RCV=PIN_C7)

void main()
{
   // Inicializar pines
   lcd_init();
   kbd_init();
   port_b_pullups(TRUE);
   
   setup_uart(9600); //Configurar baudios

   char opcion;
   int8 tiempo;
   
   while (TRUE){
      printf(lcd_putc,"\fC - Inicia\n= - Paro");
      opcion = read_key();
      
      if(opcion != 'C' && opcion != '='){
         printf(lcd_putc,"\f**ERROR**");
         delay_ms(1000);
      }else if(opcion == 'C'){
         printf(lcd_putc,"\f1-Izq\n3-Der");
         opcion = read_key();
         if(opcion != '1' && opcion != '3'){
            printf(lcd_putc,"\f**ERROR**");
            delay_ms(1000);
         }else{
            printf(lcd_putc,"\fSegundos(0-9):");
            tiempo = get_num_lcd(1,2);
            if(tiempo>9){
               printf(lcd_putc,"\f**ERROR**");
               delay_ms(1000);
            }else{
               putc(opcion);
               putc(tiempo);
            }
         }
      }else if(opcion == '='){
         putc(opcion);
         printf(lcd_putc,"\fMOTOR DETENIDO");
         delay_ms(2000);
      }
   }
}
