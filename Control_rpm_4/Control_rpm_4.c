#include <16f877A.h>
#use delay(crystal=20000000)
#FUSES NOWDT, NOBROWNOUT, NOLVP, NOPROTECT, HS, NOPUT

#use STANDARD_IO(B)

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

#define MOTOR PIN_B3

FLOAT T0_CARGA = 60.6875;
int16 objetivo = 0;
int32 Alta,Baja,porcentaje,porcentaje1;
short isAlto=0;

int16 pulsos =0; 
signed int16  error = 0;
float RPM=0;
const float dientes = 12, tiempo_muestreo = 1;
const int16 RPMAX = 800;
int16 ms_timer=0;
int1 estado=0;

#INT_EXT
void pulso()      //INTERRUPCION SENSOR RPM
{
   pulsos++;
}

#INT_TIMER0
void timer0(){
   set_timer0(T0_CARGA);
   ms_timer++;
   if(ms_timer >= 1000 ){      //HASTA 100ms SE REINCIA
      ms_timer=0;             //CICLO DE TRABAJO
      estado=1;
   }
}

#INT_TIMER1
void timer1_isr(){            
   if(isAlto){
      set_timer1(Baja);
      output_low(MOTOR);
      isAlto = 0;
   }else{
      set_timer1(Alta);
      output_high(MOTOR);
      isAlto = 1;
   }
}
void main(){
   lcd_init();
   kbd_init();
   
   output_low(MOTOR);
   
   // Timer interno con prescaler
      setup_timer_1(T1_INTERNAL | T1_DIV_BY_8); 
      setup_timer_0(RTCC_INTERNAL | RTCC_DIV_256);
      

      printf(lcd_putc,"\fRPM DE 0 A 5000:");
      objetivo =  get_num_lcd(1,8);
       
      while (objetivo > 5000 || objetivo <= 0)
         {
           printf(lcd_putc,"\fingresa otro:  ");
           objetivo = get_num_lcd(1,2);
         }
      
         porcentaje = (objetivo * 100)/RPMAX;
         
         enable_interrupts(INT_TIMER1);  
         enable_interrupts(INT_TIMER0);
         enable_interrupts(GLOBAL);
         enable_interrupts(INT_EXT);
         ext_int_edge(L_TO_H);
         set_timer0(T0_CARGA);
        
         Alta = 65535 * (100.0 - (float)porcentaje) / 100.0;      //OPERACIONES TIMER 1
         Baja = 65535 - Alta;
         
         isAlto = 0;
         set_timer1(Baja);
          
  
   while(true){
   
       if (estado == 1)
        {
           error = objetivo - RPM;                                //OPERACIONES RPM SENSOR
           int16 pulsos_tem = pulsos;
           RPM = pulsos_tem / (tiempo_muestreo * dientes)*60;
           porcentaje1 = (objetivo * 100)/RPM;
           
            printf(lcd_putc,"\fRPM: %f", RPM);
            printf(lcd_putc,"\nOBJ:%lu  ", objetivo);
            printf(lcd_putc,"Porc:%lu", porcentaje1);
            pulsos = 0;
            estado=0;
      }
   }
}
