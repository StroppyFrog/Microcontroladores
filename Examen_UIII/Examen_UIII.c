#include <16F877a.h>
#device ADC = 10
#use delay(crystal = 20000000)
#FUSES NOWDT, NOBROWNOUT, NOLVP, HS

#include <lcd_d.c>

#use STANDARD_IO(B)
#use STANDARD_IO(C)
#use STANDARD_IO(D)

int16 contador1=0;
int16 contador2=0;
int16 contador3=0;
int16 contador4=0;
int1 huboCambio = 0;

int1 b4_previo = 0;
int1 b5_previo = 0;
int1 b6_previo = 0;
int1 b7_previo = 0;

#INT_RB
void rb_isr()
{
   if(input(PIN_B4)==1 && b4_previo == 0)contador1+=1;
   if(input(PIN_B5)==1 && b5_previo == 0)contador2+=1;
   if(input(PIN_B6)==1 && b6_previo == 0)contador3+=1;
   if(input(PIN_B7)==1 && b7_previo == 0)contador4+=1;
   
   b4_previo = input(PIN_B4);
   b5_previo = input(PIN_B5);
   b6_previo = input(PIN_B6);
   b7_previo = input(PIN_B7);
   huboCambio = 1;
}

#INT_EXT
void ext_isr()
{
   contador1 = 0;
   contador2 = 0;
   contador3 = 0;
   contador4 = 0;
   huboCambio = 1;
}

void main()
{
   // Inicializar pines
   lcd_init();

   enable_interrupts(GLOBAL);
   enable_interrupts(INT_RB);
   enable_interrupts(INT_EXT);
   while (TRUE)
   {
      if(huboCambio)
      {
         printf(lcd_putc,"\fB4:%lu, B5:%lu,\nB6:%lu, B7:%lu",contador1,contador2,contador3,contador4);
         huboCambio=0;
      }
   }
}
