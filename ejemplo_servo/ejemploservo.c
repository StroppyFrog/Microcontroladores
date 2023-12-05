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
#include <lcd.c> //Incluir librer�a LCD
#include <kbd4x4_b.c>
#include <getNum16.c>

#use STANDARD_IO(C)

#define PIN_SERVO PIN_C0


void move_servo(int16 ancho)
{
   //float milis = (180.0 + (float)grados) / 180.0;
   //int16 tiempo_alto = (int16)(milis * 1000.0);
   int16 tiempo_alto = ancho;
   int16 tiempo_bajo = 20000 - tiempo_alto;
   for(int8 i = 0; i < 15; i++){
      output_high(PIN_SERVO);
      delay_us(tiempo_alto);
      output_low(PIN_SERVO);
      delay_us(tiempo_bajo);
   }
}

void main(){
   lcd_init(); //Inicializar pantalla
   kbd_init();

   output_low(PIN_SERVO);
   printf(lcd_putc,"\fHolis :)");
   
   int16 grados_deseados;
   while(1){
      printf(lcd_putc,"\fIngrese ancho:");
      grados_deseados = get_num_lcd(1,2);
      move_servo(grados_deseados);
   } // while
}
