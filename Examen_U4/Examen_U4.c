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
   int16 POT1, POT2, POT3;
   int8 byte1, byte2, byte3;
   
   while(TRUE)
   {
      set_adc_channel(0);
      POT1 = read_adc();
      byte1 = POT1 & 255;
      byte2 = (POT1 >> 8) & 255;
      byte3 = 1;
      delay_us(40);
      set_adc_channel(1);
      POT2 = read_adc();
      byte1 = POT2 & 255;
      byte2 = (POT2 >> 8) & 255;
      byte3 = 1;
      delay_us(40);
      set_adc_channel(3);
      POT3 = read_adc();
      byte1 = POT3 & 255;
      byte2 = (POT3 >> 8) & 255;
      byte3 = 1;
      delay_us(40);
      printf(lcd_putc,"\fA1  A2  A3\n%Lu, %Lu, %Lu",POT1,POT2,POT3);
      putc(byte3);
      putc(byte2); 
      putc(byte1); 
      delay_ms(100);
   }
}
