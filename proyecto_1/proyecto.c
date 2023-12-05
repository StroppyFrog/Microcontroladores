//-. Motor bipolar .-

#include <16F877a.h>
#device ADC = 10
#use delay(crystal = 20000000)
#FUSES NOWDT, NOBROWNOUT, NOLVP, HS
#define LCD_ENABLE_PIN  PIN_A3                                    ////
#define LCD_RS_PIN      PIN_A5                                    ////
#define LCD_RW_PIN      PIN_A4                                    ////
#define LCD_DATA4       PIN_D4                                    ////
#define LCD_DATA5       PIN_D5                                    ////
#define LCD_DATA6       PIN_D6                                    ////
#define LCD_DATA7       PIN_D7 
#include <lcd.c>
//#include <lcd_d.c>
//#include <kbd4x4_b.c>
#include <kbd4x4_b_fisico.c> //para utilizarla en fisico
#include <getNum16.c>

#use STANDARD_IO(A)
#use STANDARD_IO(B)
#use STANDARD_IO(D)
#use STANDARD_IO(C)

const int8 pasos[8] = {

   0b1000,
   0b1010,
   0b0010,
   0b0110,
   0b0100,
   0b0101,
   0b0001,
   0b1001

};

int8 step_index = 0;

void update_stepper(){
   output_a(pasos[step_index]);
}

void step_up(){
   if(step_index == 0){
      step_index = 7;
   }else{
      step_index--;
   }
   update_stepper();
}

void step_back(){
   step_index++;
   if(step_index > 7){
      step_index = 0;
   }
   update_stepper();
}

void main(){
   // setup_uart(9600); //Configurar baudios
   // Inicializar pines
   update_stepper();
   lcd_init();
   kbd_init();
   port_b_pullups(TRUE);
   int16 numero;
   float pos_actual = 0;
   float micro_paso = 0.9;
   while (TRUE){
      printf(lcd_putc,"\fGrado (0 a 360):");
      numero = get_num_lcd(1,2);
      float grados = (float)numero;
      if(numero > 360.0 || numero < 0.0){
         printf(lcd_putc,"\f*ERROR* \nNumero no valido");
         delay_ms(1000);
         numero = pos_actual;
      }
      else{
         float pasos_totales = ((grados-pos_actual)*400.0)/(360.0);
         float pasos_diferencia = abs(pasos_totales);
         printf(lcd_putc,"\fPasos total:%f\nPaso actual:%f",pasos_totales,pos_actual);
         if(pos_actual < grados){
            for(int16 i=0; i < pasos_diferencia; i++){
               step_up();
               pos_actual += micro_paso;
               printf(lcd_putc,"\fPasos total:%f\nPaso actual:%f",pasos_totales,pos_actual);
               delay_ms(100);
            }
         }
         else if(pos_actual > grados){
            for(int16 i=0; i < pasos_diferencia; i++){
               step_back();
               pos_actual -= micro_paso;
               printf(lcd_putc,"\fPasos total:%f\nPaso actual:%f",pasos_totales,pos_actual);
               delay_ms(100);
            }
         }
      }
   }
}
