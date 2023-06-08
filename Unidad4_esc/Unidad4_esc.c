#include <16F877a.h>
#device ADC=10

#use delay(crystal=20Mhz)

#FUSES NOWDT, NOBROWNOUT, NOLVP

// Directiva para usar el puerto USART

#use rs232(BAUD=9600, XMIT = PIN_C6, RCV=PIN_C7)

#include <lcd_d.c> //Incluir librería LCD

int8 byte1,byte2, entrada;
int16 ID;
float numero=0;

// Interrupción al recibir una trama

#INT_RDA 

void rda_int(){
   ID = getc();
   byte2 = getc();
   byte1 = getc();
   numero = ((int16) byte2 << 8) | byte1; // Unimos los bytes
   entrada=1;
}

void main(){
   lcd_init(); //Inicializar pantalla
   setup_uart(9600); //Configurar baudios
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   while(TRUE){

      if(ID==1 && entrada==1){
         lcd_gotoxy(1,1);
         printf(lcd_putc,"A1");
         lcd_gotoxy(1,2); 
         printf(lcd_putc,"%.0f ",(numero*(5.0 / 1023.0*100)));
         entrada=0;
      }else if(ID==2 && entrada==1){
         lcd_gotoxy(4,1); 
         printf(lcd_putc,"A2");
         lcd_gotoxy(4,2); 
         printf(lcd_putc,"%.0f",(numero*(5.0 / 1023.0*100)));
         entrada=0;
      }else if(ID==3 && entrada==1){
         lcd_gotoxy(8,1); 
         
         printf(lcd_putc,"A3");
         lcd_gotoxy(8,2);
         printf(lcd_putc,"%.0f",(numero*(5.0 / 1023.0*100)));
         entrada=0;
      }

   }

}
