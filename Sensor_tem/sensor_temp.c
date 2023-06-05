#include <16F877a.h>
#device ADC=10
#use delay(crystal=20000000)
#FUSES NOWDT, NOBROWNOUT, NOLVP
#use rs232(BAUD=9600, XMIT = PIN_C6, RCV=PIN_C7)
#include <lcd_d.c> //Incluir librer�a LCD

int16 valor;
float temp;
char rcv = 'D';

#INT_RDA
void rda_int()
{
   char k = getc();
   if(k != 10)
   if(k != 13)
   if(k != 07)
   rcv = k;
}
void main()
{
   lcd_init();
   setup_uart(9600);
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(AN0_AN1_AN3);
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL); 
   while(TRUE)
   {
      if(rcv == 'A')
      {
         set_adc_channel(0);
         delay_us(1);
         valor = read_adc();
         temp = 500 * (float)valor/1023.0;
         printf("%fC", temp);
         lcd_gotoxy(1,1);
         printf(lcd_putc,"temp=%f", temp);
         delay_ms(500);
      }
      if(rcv == 'B')
      {
      }
      delay_ms(500);
   }
}
