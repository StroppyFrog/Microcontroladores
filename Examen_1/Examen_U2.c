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

<<<<<<< Updated upstream
=======
int1 delay_paro(int16 segundos); // Declaramos funci�n pero no la definimos
int16 Cantidad;

/*void girar_Fresa()
{
   output_high(M_Fresa);
   output_low(M_Light);
}*/

/*void girar_Light()
{
   output_high(M_Light);
   output_low(M_fresa);
}*/

>>>>>>> Stashed changes
void paro()
{
   output_low(M_Fresa);
   output_low(M_Light);
}

void Cantidad_F()
{
   printf(lcd_putc,"\fCajas: %5Lu", Cantidad);
   int8 i = 0;
   while(i < Cantidad)
   {
      output_high(M_Fresa);
      output_low(M_Light);
      if(S_Fresa == TRUE)
      {
         i++;
         return;
      }
   }
}

void Cantidad_L()
{
   printf(lcd_putc,"\fCajas: %5Lu", Cantidad);
   int8 i = 0;
   while(i < Cantidad)
   {
      output_high(M_Light);
      output_low(M_Fresa);
   }
}

void paro_emergencia()
{
   paro(); // Detener motores
   printf(lcd_putc,"\fPARO DE EMERGEN");
   while(input(boton_paro) == 1){}
   printf(lcd_putc,"\fPRESS ANY KEY");
   char tecla = read_key();
}

int1 delay_paro(int16 segundos){
   for(int16 i = 0; i < segundos * 100; i++){
      delay_ms(10);
      if(input(boton_paro)){
         paro_emergencia();
         return 1;
      }
  }
   return 0;
}

void main()
{
   //port_b_pullups(TRUE);
   lcd_init();
   kbd_init();
   paro();
   input(boton_paro);
   int16 menu;
   
<<<<<<< Updated upstream

   printf(lcd_putc,"Fresa/Light: %3Lu", menu);
   menu = get_num_lcd(9,2);
   
   switch(menu)
   {
      case 1:
         
=======
   while (TRUE)
   {
      printf(lcd_putc,"\fFresa/light\n 1/3: ");
      menu = get_num_lcd(9,2);
      
      if(menu == 1)
      {
       Cantidad_F();
      }
      else if (menu == 2)
      {
       Cantidad_L();         
      }
      else if(Cantidad <= 0 || cantidad > 2)
      {
        printf(lcd_putc,"\f**ERROR** \nNumero no valido");
        delay_paro(2);
      }
>>>>>>> Stashed changes
   }
}