#include <16F877a.h>
#device ADC = 10
#use delay(crystal = 20000000)
#FUSES NOWDT, NOBROWNOUT, NOLVP, HS

#define S1 PIN_C0
#define S2 PIN_C1
#define S3 PIN_C2
#define BOT PIN_C3

#include <lcd_d.c>
#include <kbd4x4_b.c>
#include <getNum16.c>

//Directiva para utilizar puerto USART
//#use rs232(BAUD=9600, XMIT = PIN_C6, RCV=PIN_C7)

void main()
{
   // setup_uart(9600); //Configurar baudios
   // Inicializar pines
   lcd_init();
   kbd_init();
   int16 option;
   int16 time;
   int1 condicion;
   while (TRUE)
    {
      do
      {
         printf(lcd_putc,"\fIngresar opcion: ");
         option = get_num_lcd(1,2);
         
         switch(option)
         {
            case 1:
               printf(lcd_putc,"\fIngresar tiempo: ");
               time = get_num_lcd(1,2);
               if(time > 0 && time <=120)
               {
                  output_high(S1);
                  delay_ms(1000*time);
                  output_low(S1);
               }
               else if(time > 120)
               {
                  printf(lcd_putc,"\fFuera de rango ");
                  delay_ms(3000);
               }
               condicion = (condicion != 1) && (condicion != 3);             
            break;
            case 2:
               printf(lcd_putc,"\fingresar tiempo");
               time = get_num_lcd(1,2);
               if(time >0 && time <= 120)
               {
                     output_high(S2);
                     delay_ms(250*time);
                     output_low(S2);
                     delay_ms(250*time);
                     output_high(S2);
                     delay_ms(250*time);
                     output_low(S2);
                     delay_ms(250*time);  
               }
               else if(time > 120)
               {
                  printf(lcd_putc,"\fFuera de rango");
                  delay_ms(30000);
               }
               condicion = (condicion != 1) && (condicion != 3);
            break;
            case 3:
               printf(lcd_putc,"\fingresar tiempo");
               time = get_num_lcd(1,2);
               if(time >0 && time <= 120)
               {
                  for(int16 i = 2; i < time; i++)
                  {
                     output_high(S3);
                     delay_ms(1000);
                     output_low(S3);
                     delay_ms(1000);
                  }   
               }
               else if(time > 120)
               {
                  printf(lcd_putc,"\fFuera de rango");
                  delay_ms(30000);
               }
               condicion = (condicion != 1) && (condicion != 3);               
            break;
            default:
               printf(lcd_putc,"\fFuera de rango");
               condicion = (condicion != 1) && (condicion != 3);
               delay_ms(3000);
         }   
         
      }while(condicion == 1);
    }
}
