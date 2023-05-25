// Transmisor 
#include <16F877a.h>
#device ADC=10
#use delay(crystal=20Mhz)
#FUSES NOWDT, NOBROWNOUT, NOLVP
//Directiva para utilizar puerto USART
#use rs232(BAUD=9600, XMIT = PIN_C6, RCV=PIN_C7)
#include <lcd_d.c> //Incluir librer�a LCD


void main()
{
   lcd_init(); //Inicializar pantalla
   //kbd_init(); //Inicializar teclado
   setup_uart(9600); //Configurar baudios
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(AN0_AN1_AN3);
   int16 POT1;
   int16 POT2;
   
   while(TRUE)
   {
      set_adc_channel(0);
      delay_us(40);
      POT1 = read_adc();
      set_adc_channel(1);
      delay_us(40);
      POT2 = read_adc();
      printf(lcd_putc,"\fADC1:%Lu\nADC2:%Lu",POT1,POT2);
      delay_ms(100);
   }
}
