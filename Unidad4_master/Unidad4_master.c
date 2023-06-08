#include <16F877a.h>
#device ADC=10
#use delay(crystal=20Mhz)
#FUSES NOWDT, NOBROWNOUT, NOLVP

//Directiva para utilizar puerto USART
#use rs232(BAUD=9600, XMIT = PIN_C6, RCV=PIN_C7)

#include <lcd_d.c> //Incluir librería LCD
#include <kbd4x4_b.c> //Librería teclado 4x4 puerto B
#include <getNum16.c> //Librería para leer numeros enteros de 16 bits


void main(){

   lcd_init(); 
   kbd_init(); 
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(AN0); 
   
   setup_uart(9600); 
   
   int16 sensor1, sensor2, sensor3;
   int8 byte1, byte2,byte3; 
   while(TRUE){
   
   set_adc_channel(0);
   sensor1 = read_adc();
   
      byte1 = sensor1 & 255; 
      byte2 = (sensor1 >> 8) & 255; 
      byte3 = 1;
      putc(byte3);
      putc(byte2); 
      putc(byte1); 
         lcd_gotoxy(1,1); 
         printf(lcd_putc,"A1"); // Imprimir número
         lcd_gotoxy(1,2);
         printf(lcd_putc,"%lu",sensor1);
      
      set_adc_channel(1);
      sensor2 = read_adc();
      
      byte1 = sensor2 & 255; 
      byte2 = (sensor2 >> 8) & 255; 
      byte3 = 2;
      putc(byte3);
      putc(byte2); 
      putc(byte1); 
         lcd_gotoxy(4,1); 
         printf(lcd_putc,"A2"); // Imprimir número
         lcd_gotoxy(4,2); 
         printf(lcd_putc,"%lu",sensor2);
      
      set_adc_channel(2);
     sensor3 = read_adc();
     
      byte1 = sensor3 & 255; 
      byte2 = (sensor3 >> 8) & 255; 
      byte3 = 3;
      putc(byte3);
      putc(byte2); 
      putc(byte1); 
         lcd_gotoxy(8,1); 
         printf(lcd_putc,"A3"); // Imprimir número
         lcd_gotoxy(8,2);
         printf(lcd_putc,"%lu",sensor3);
      }
   }
