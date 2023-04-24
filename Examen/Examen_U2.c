//-. Motor DC .-

#include <16F877a.h>
#device ADC = 10
#use delay(crystal = 20000000)
#FUSES NOWDT, NOBROWNOUT, NOLVP, HS

#include <lcd_c.c>
#include <kbd4x4_d.c>
#include <getNum16.c>

#use STANDARD_IO(C)
#use STANDARD_IO(B)
#use STANDARD_IO(D)

#define M_Fresa PIN_B0
#define M_Light PIN_B1
#define S_Fresa PIN_B4
#define S_Light PIN_B5
#define boton_paro PIN_B7

void paro()
{
   output_low(M_Fresa);
   output_low(M_Light);
}

void paro_emergencia()
{
   paro(); // Detener motores
   printf(lcd_putc,"\fPARO DE EMERGEN");
   while(input(boton_paro) == 1){}
   printf(lcd_putc,"\fPRESS ANY KEY");
   char tecla = read_key();
}


void main()
{
   lcd_init();
   kbd_init();
   paro();
   input(boton_paro);
   int16 menu;
   

   printf(lcd_putc,"Fresa/Light: %3Lu", menu);
   menu = get_num_lcd(9,2);
   
   switch(menu)
   {
      case 1:
         
   }
}
