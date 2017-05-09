/**
  * @file imagenES.cpp
  * @brief Fichero con definiciones para la E/S de imágenes
  *
  * Permite la E/S de archivos de tipo PGM,PPM
  *
  */
#include <iostream>
#include <cstring>
#include "codificar.h"
using namespace std;
const int MAXMENSAJE= 125000;
const unsigned short int COMP_BIT_IMG = 0x01;

bool Ocultar(unsigned char imagen[], const char mensaje[]){
    unsigned short int comp_bit_men;
    int i= 0, k= 0;  //i: indice que recorre el vector mensaje, k: indice que recorre el vector imagen
    char octeto_res;
    bool bit_imagen, bit_mensaje;

    while(mensaje[i] != '\0'){
        comp_bit_men= 0x80; //para comprobar el bit mas a la izquierda

         /*bucle para recorrer cada uno de los bits del byte i del mensaje y tambien aumenta en cada vuelta el indice k(indice de la imagen)*/
        for(int j=0; j<8; j++, k++){
            bit_mensaje = mensaje[i] & comp_bit_men;    //guarda el bit de la posicion que indica comp_bit_men del byte i del mensaje
            bit_imagen = imagen[k] & COMP_BIT_IMG;  //guarda el bit menos significativo del byte k de la imagen

            if(bit_imagen != bit_mensaje){  // cambiamos el bit del byte k de la imagen en caso de que no sean iguales
                if(!bit_imagen)
                    octeto_res = imagen[k] | COMP_BIT_IMG;
                else
                    octeto_res = imagen[k] & !COMP_BIT_IMG;

                imagen[k] = octeto_res;
            }
            comp_bit_men = comp_bit_men >> 1;   //movemos una posicion todos los bits para en la siguiente vuelta, comprobar el siguiente bit
        }

        i++;
    }

   /*bucle para poner a cero el bit menos significativo de los 8 bytes despues
    del mensaje completo en caso de que dicho bit no este ya a cero.

    En este caso, utilizamos octeto_res de manera que se queda con el valor de cada uno
    de los bits del byte k de la imagen excepto el de la posicion menos significativa en
    caso de que tenga que cambiarse.*/
    for(int j=0; j<8; j++, k++){
        bit_imagen = imagen[k] & COMP_BIT_IMG;

        if(bit_imagen){
            octeto_res = imagen[k] & !COMP_BIT_IMG;
            imagen[k] = octeto_res;
        }
    }

    return 1;
}


bool Revelar(const unsigned char imagen[], char mensaje[]){
    unsigned short int comp_bit_men = 0x80;
    int i= 0, j= 0, k= 0;  //k: indice que recorre el vector imagen, j: indice que cuenta los ceros seguidos, k: indice que recorre el vector mensaje.
    char octeto_imagen, octeto_res = '\0';
    bool bit_imagen, byte_cero=false;

    while(!byte_cero && i<MAXMENSAJE){
        octeto_imagen= imagen[i];
        bit_imagen = octeto_imagen & COMP_BIT_IMG;

        /*aumenta una unidad el contador j en caso de que el bit_imagen comprobado sea cero, en caso contrario, lo resetea
        a cero. Esto sirve para comprobar mas adelante si se llega a contar 8 ceros seguidos y acabar de
        revelar el mensaje.
        */
        if(!bit_imagen)
            j++;
        else
            j= 0;

        /*Cada 8 vueltas se introduce el char formado al mensaje, se aumenta k(indice del vector imagen) y el octeto a construir se hace cero.*/
        if(i%8 == 0 && i!=0){
            mensaje[k] = octeto_res;
            k++;
            octeto_res = '\0';
            comp_bit_men = 0x80;
        }

        /*Solo si el bit comprobado de la imagen es 1, se introduce al octeto en construccion,
        en la posicion indicada por comp_bit_men ya que si fuera 0, este ya estaria incluido*/
        if(bit_imagen)
            octeto_res = octeto_res | comp_bit_men;

        /*En cada vuelta del while comprobamos si llevamos 8 ceros seguidos, aumentamos
        el byte a leer de la imagen y movemos los bits de comp_bit_men para comprobar el bit siguiente*/
        comp_bit_men = comp_bit_men >> 1;
        byte_cero = j >= 8;
        i++;
    }

    return byte_cero;
}

