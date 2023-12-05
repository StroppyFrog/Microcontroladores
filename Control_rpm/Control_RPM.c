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
#define KBD_A PIN_C0
#define KBD_B PIN_C1
#define KBD_C PIN_C2
#define KBD_D PIN_C3
#define KBD_1 PIN_C4
#define KBD_2 PIN_C5
#define KBD_3 PIN_C6
#define KBD_4 PIN_C7
#include <kbd_4x4_custom.c> //Librer�a teclado 4x4 puerto B
#include <getNum16.c>

#use STANDARD_IO(B)
#use STANDARD_IO(E)
#use STANDARD_IO(D)

#define PWM_PIN PIN_B1
#define Motor PIN_B2
#define carga 61

int16 pulsos = 0,velocidad_deseada = 0,velocidad_actual = 0;
int1 esAltoPWM = 0;
int16 carga_bajo,carga_alto;

#INT_TIMER1
void timer1_isr(){
   if(esAltoPWM == 1){
      set_timer1(carga_bajo);
      output_low(PWM_PIN);
      esAltoPWM = 0;
   }else{
      set_timer1(carga_alto);
      output_high(PWM_PIN);
      esAltoPWM = 1;
   }
   if(velocidad_deseada == 6600){
      output_high(PWM_PIN);
   }else if(velocidad_deseada == 0){
      output_low(PWM_PIN);
   }
}

#INT_EXT
void ext_isr()
{
   pulsos++;
}

void main(){
   // Inicializar pines
   lcd_init();
   kbd_init();

   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);
   enable_interrupts(INT_TIMER1);
   enable_interrupts(INT_EXT);
   enable_interrupts(GLOBAL);
   
   set_timer1(carga);


   int16 porcentaje;
   output_low(PWM_PIN);
   output_low(Motor);
   
   while (TRUE){
      printf(lcd_putc,"\fVelocidad:"); // Leer velocidad deseada desde el teclado
      velocidad_deseada = get_num_lcd(1,2);
      porcentaje = ((float)velocidad_deseada * 100.0)/6600.0;
      
      if(velocidad_deseada<=6600 && velocidad_deseada>=0){
         while(TRUE){
            carga_bajo = (int16)((65536.0 * porcentaje / 100.0)); // Calcular el tiempo en bajo
            carga_alto = 65536 - carga_bajo; // Calcular el timepo en alto
            
            pulsos = 0; // Reiniciar el contador
            delay_ms(5000); // Esperar 5 segundos para medir la velocidad actual
            velocidad_actual = 60 * pulsos / 12; // Velocidad en RPM (12 dientes por vuelta)
            

            lcd_gotoxy(1,1);
            printf(lcd_putc, "\fRPM OBJ ERR \n%4lu %4lu %4lu", velocidad_actual,velocidad_deseada,porcentaje);
            if(velocidad_actual<velocidad_deseada){
               porcentaje++;
            }
            else if(velocidad_actual>velocidad_deseada){
               porcentaje--;
            }
         }
      }
      else if(velocidad_deseada>6600){
         printf(lcd_putc,"\fSolo llego a\n6600 rpm :(");
         velocidad_deseada = 0;
         delay_ms(2000);
      }
   }
}
