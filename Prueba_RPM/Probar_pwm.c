#include <16F877a.h>
#device ADC=10
#use delay(crystal=20Mhz)
#FUSES NOWDT, NOBROWNOUT, NOLVP

#define LCD_ENABLE_PIN  PIN_A3                                    ////
#define LCD_RS_PIN      PIN_A5                                    ////
#define LCD_RW_PIN      PIN_A4                                    ////
#define LCD_DATA4       PIN_D4                                    ////
#define LCD_DATA5       PIN_D5                                    ////
#define LCD_DATA6       PIN_D6                                    ////
#define LCD_DATA7       PIN_D7 
#include <lcd.c>
#define KBD_A PIN_C0
#define KBD_B PIN_C1
#define KBD_C PIN_C2
#define KBD_D PIN_C3
#define KBD_1 PIN_C4
#define KBD_2 PIN_C5
#define KBD_3 PIN_C6
#define KBD_4 PIN_C7
#include <kbd_4x4_custom.c> //Librería teclado 4x4 puerto B
#include <getNum16.c>

#USE STANDARD_IO(A)
#define LED PIN_A1

int16 carga_alto, carga_bajo;

#INT_TIMER0
void desborde_timer_0()
{
   static short es_alto = 0;
   if(es_alto){
      set_timer0(carga_alto);
      output_high(LED);
   }else{
      set_timer0(carga_bajo);
      output_low(LED);
   }
   es_alto = !es_alto;
}

void actualizar_pwm(float porcentaje){
   carga_bajo = (int) (256.0 * porcentaje / 100.0);
   carga_alto = 256 - carga_bajo;
}

void pedir_porcentaje(){
   printf(lcd_putc,"\fIngrese porcentaje");
   int16 porcentaje = get_num_lcd(1,2);
   
   actualizar_pwm((float)porcentaje);
   printf(lcd_putc,"\fCA:%lu\nCB:%lu",carga_alto,carga_bajo);
}

void main(){
   lcd_init(); //Inicializar pantalla
   kbd_init();
   
   setup_timer_0(RTCC_INTERNAL | RTCC_DIV_256);
   
   
   pedir_porcentaje();
 
   output_low(LED);  
   set_timer0(carga_bajo);
   
   
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
 
   while(1){
      pedir_porcentaje();
      delay_ms(2000);
   } // while
}
