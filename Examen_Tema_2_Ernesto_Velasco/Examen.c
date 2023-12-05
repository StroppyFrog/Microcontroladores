//-. Motor unipolar .-

#include <16F877a.h>
#device ADC = 10
#use delay(crystal = 20000000)
#FUSES NOWDT, NOBROWNOUT, NOLVP, HS

#include <lcd_c.c>
#include <kbd4x4_b.c>
//#include <kbd4x4_b_fisico.c> para utilizarla en fisico
#include <getNum16.c>
//#use STANDARD_IO(B)
#use STANDARD_IO(D)

#define MA1 PIN_D0
#define MA2 PIN_D1
#define MA3 PIN_D2
#define MA4 PIN_D3

const int8 pasos[10] = 
{

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
   output_d(pasos[step_index]);
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
   int16 tiempo;
   int16 grados;
   Char opci;
   float pos_actual = 0;
   float micro_paso = 0.9;
   while (TRUE){
      printf(lcd_putc,"\fPosiciones\n(2 a 10):");
      numero = get_num_lcd(10,2);
      float posi = (float)numero;
      printf(lcd_putc,"\fTiempo de espera: ");
      tiempo = get_num_lcd(1,2);
      float time = (float)tiempo;
      printf(lcd_putc,"\fAngulos: ");
      grados = get_num_lcd(1,2);
      float angulos = (float)grados;
      if(numero <= 1 || numero > 10)
      {
         printf(lcd_putc,"\f**ERROR** \nNumero no valido");
         delay_ms(1000);
         //numero = pos_actual;
      }
      if(tiempo < 0 || tiempo > 200)
      {
         printf(lcd_putc,"\f**ERROR** \nNumero no valido");
         delay_ms(1000);
         //numero = pos_actual;
      }
      if( grados < 0 || grados > 360)
      {
         printf(lcd_putc,"\f**ERROR** \nNumero no valido");
         delay_ms(1000);
         angulos = pos_actual;
      }
      {
         float pasos_totales = ((angulos*512.0)/360.0);
         float pasos_moverse = pasos_totales -= pos_actual;
         float pasos_diferencia = abs(pasos_moverse);
         //printf(lcd_putc,"\fPasos total:%f\nPaso actual:%f",pasos_moverse,pos_actual);
         
         if(pos_actual < grados)
         {
            for(int16 i=0; i < pasos_diferencia; i++)
            {
               step_up();
               pos_actual += micro_paso;
               printf(lcd_putc,"\fPasos total:%f\nPaso actual:%f",pasos_moverse,pos_actual);
               delay_ms(1000);
            }
         }
         else if(pos_actual > grados)
         {
            for(int16 i=0; i < pasos_diferencia; i++)
            {
               step_back();
               pos_actual -= micro_paso;
               printf(lcd_putc,"\fPasos total:%f\nPaso actual:%f",pasos_moverse,pos_actual);
               delay_ms(1000);
            }
         }
      }
   }
}
