
/*
volcado.c
*/


#include<stdio.h>
void Imprimir_Buffer ( unsigned char *Mi_Buffer , int Tama_Volcado)
{

char Codigo_ascii[17];
int i;
 
for (i = 0; i < Tama_Volcado; ++i) {
        printf("%02X ", ((unsigned char*)&Mi_Buffer)[i]);
        if (((unsigned char*)&Mi_Buffer)[i] >= ' ' && ((unsigned char*)&Mi_Buffer)[i] <= '~')
         {
            Codigo_ascii[i % 16] = ((unsigned char*)&Mi_Buffer)[i];
        } else {
            Codigo_ascii[i % 16] = '.';
        }
        if ((i+1) % 8 == 0 || i+1==Tama_Volcado) {
            printf(" ");
            if ((i+1) % 16 == 0) {
                printf(" |  %s \n", Codigo_ascii);
 
}}}
}