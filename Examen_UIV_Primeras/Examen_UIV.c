#include <16F877a.h>
#device ADC=10
#use delay(crystal=20Mhz)
#FUSES NOWDT, NOBROWNOUT, NOLVP
#use rs232(BAUD=9600, XMIT = PIN_C6, RCV=PIN_C7)
#include <lcd_d.c> //Incluir librer�a LCD
#include <kbd4x4_b.c>
#include <getNum16.c>

void interrupcion_rda()
{
   char caracter = getc();
   putc(caracter);
   putc(caracter+1);
}

void main(){
   lcd_init(); //Inicializar pantalla
   kbd_init();
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(AN0_AN1_AN2_AN3_AN4);

   int16 lectura_adc_0,lectura_adc_1,lectura_adc_3;
   
   while(1)
   {
   
      set_adc_channel(0);
      delay_us(8000);
      lectura_adc_0 = read_adc();

      set_adc_channel(1);
      delay_us(8000);
      lectura_adc_1 = read_adc();
     
      set_adc_channel(3);
      delay_us(8000);
      lectura_adc_3 = read_adc();
      printf("A0:%4lu, A1:%4lu\nA3:%4lu",lectura_adc_0,lectura_adc_1,lectura_adc_3);
     

   } // while
}
