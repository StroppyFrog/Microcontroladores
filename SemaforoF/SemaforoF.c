#include <16f877a.h>
#fuses XT, NOWDT
#use delay(clock = 4000000)
#use standard_io(B)
#use standard_io(C)

// LIGHTS
void green()
{ //LUZ VERDE
     for(int i=0; i<=100; i++)
     {
          output_high(PIN_B2);//PRENDO LUZ VERDE
          delay_ms(50); //5 SEGUNDOS
          output_low(PIN_B2);//APAGO LUZ VERDE
         if(input(PIN_C0)==1)//SI PRESIONO EL BOTON
         {
           output_low(PIN_B2);//APAGO LUZ VERDE
           break;//ROMPO EL CICLO
         }
     }
}

void yellow()
{//LUZ AMARILLA
 int y=0;

  for (y=0; y < 4 ; y++)
  {//REPITO 4 VECES POR 3 SEGUNDOS
    output_high(PIN_B1);//PRENDO LUZ AMARILLA
    delay_ms(375);//DELAY
    output_low(PIN_B1);//APAGO LUZ AMARILLA
    delay_ms(375);//DELAY
  } 
}

void red()
{ //LUZ ROJA
     for(int i=0; i<=100; i++)
     {
         output_high(PIN_B0);//PRENDO LUZ ROJA
         delay_ms(80);//8 SEGUNDOS
         output_low(PIN_B0);//APAGO LUZ ROJA
          
         if(input(PIN_C0)==1)
         {//SI PRESIONO EL BOTON
            i=0;//RESETEO CONTADOR Y REINICIA EL CICLO DE 8 SEGUNDOS
         }
      }
}

void main(){
    port_b_pullups (TRUE);
    output_low(PIN_B0);//APAGO LUZ ROJA
    output_low(PIN_B1);//APAGO LUZ AMARILLA
    output_low(PIN_B2);//APAGO LUZ VERDE
    
    while (1)//CICLO INFINITO
    {
        green();
        yellow();
        red();
    }
}
