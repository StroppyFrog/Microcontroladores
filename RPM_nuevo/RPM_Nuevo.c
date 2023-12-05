#include <16F877A.h>
#FUSES NOWDT, NOBROWNOUT, NOLVP, NOPROTECT, HS, NOPUT
#use delay(clock= 20 MHz)        

#include <lcd_c.c>
#INCLUDE <kbd4x4_d.c>
#include <getNum16.c>

long  RPM = 0, ancho = 0, RPMA = 0, t = 0;
int x = 0; 
short a = 0, c = 0;
int32 pulsos = 0,  PPRPM = 0;
int16 porcentaje;

#Int_Timer0
void Interrupcion_Timer0()
{
    t++;
    if(t == 500)
    {
       
       if( RPM> 0 && c == 0)
       {
         
          RPMA = (PULSOS*240)/24;
          porcentaje = (RPM * 100)/RPMA;
          lcd_gotoxy(1,2);
          printf(lcd_putc,"\RPMA %05Lu P:%lu",RPMA,porcentaje);
       }

      
      if(RPM < RPMA)
         ancho -= x;
      if(RPM > RPMA)
         ancho += x;
         
      PULSOS = 0;
      t = 0;
    }
    
    if(RPM > 0 )/*&& RPM >= 2500 && RPM <= 6200*/
       {
            output_high(pin_b3);
            output_low(pin_b1);
            delay_us(ancho);
            output_low(pin_b3);
       }
   set_timer0(26);
 
}
#Int_Ext
void Interrupcion()
{
      pulsos++;
}

void main()
{
   lcd_init();
   kbd_init();
   port_b_pullups(true);
   enable_interrupts(int_ext);
   ext_int_edge(H_TO_L);
   
   setup_timer_0(RTCC_INTERNAL | RTCC_DIV_2);
   enable_interrupts(INT_TIMER0);
   set_timer0(6);
   
    enable_interrupts(global); 
    
    output_low(pin_b3);
    output_low(pin_b1);
    do
    {
       c = 1;
       lcd_gotoxy(1,1);
       printf(lcd_putc,"Ingresa RPM:");
       lcd_gotoxy(1,2);
       //printf(lcd_putc,"500 a 3600 ");
       RPM = get_num_lcd(1,3);
       if(RPM < 500 || RPM > 3600 )
       {
         
            printf(lcd_putc,"\fValor Invalido");
            delay_ms(500);         
       }
       
    }while(RPM < 1 || RPM > 3600);
    c = 0;
    ancho = 450;
    a = 1;

   while(true)
   {
    
       if(input(pin_b3) == 0 && a == 0)
       {
         a = 1;
         c = 1;
         do
            {
             lcd_gotoxy(1,1);
             printf(lcd_putc,"Ingresa RPM     ");
             lcd_gotoxy(1,2);
             //printf(lcd_putc,"500 a 3600 ");
             RPM = get_num_lcd(1,3);
             if(RPM < 500 || RPM > 3600 )
             {
               
                  printf(lcd_putc,"\fValor Invalido");
                  delay_ms(500);         
             }
          }while(RPM < 500 || RPM > 3600);
          PPRPM = (RPM*24)/60;
          c = 0;
       }
       
       if(RPM>0 && a == 1)
       {

          lcd_gotoxy(1,1);
          printf(lcd_putc,"RPM %Lu  A%Lu      ",RPM, ancho);
       }
      
     if((RPM - RPMA) >500)
         x = 50;
      if((RPM - RPMA) >= 250 && (RPM - RPMA) < 500)
         x = 20;
      if((RPM - RPMA) > 100 && (RPM - RPMA) < 250)
         x = 15;
      if((RPM - RPMA) <= 100 && (RPM - RPMA) < 50)
      {
         x = 1;
         a = 0;
      }
      if((RPM - RPMA) <= 50)
         x = 0;
   }
}
