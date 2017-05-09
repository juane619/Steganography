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
#include "imagenES.h"
using namespace std;

const int MAXBUFFER= 1000000;
const int MAXNOMBRE= 100;
const int MAXMENSAJE= 125000;

int main(){
    int filas, columnas;
    bool error_lectura = 0, error_formato = 0, err_long_mens = 0;
    int long_mensaje;

    char nom_img_in[MAXNOMBRE], nom_img_out[MAXNOMBRE];
    unsigned char buffer[MAXBUFFER];
    char mensaje[MAXMENSAJE] = "";

    cout << "Introduzca la imagen de entrada: ";
    cin >> nom_img_in;

    cout << "Introduzca la imagen de salida: ";
    cin >> nom_img_out;

    cout << "Introduzca el mensaje: ";
    cin.get();
    cin.getline(mensaje, MAXMENSAJE);

    long_mensaje = strlen(mensaje);

    if(LeerTipoImagen(nom_img_in, filas, columnas) == IMG_PGM){
        if(LeerImagenPGM(nom_img_in, filas, columnas, buffer)){
            err_long_mens = long_mensaje+1 > (filas*columnas/8);
            if(!err_long_mens)
                if(Ocultar(buffer, mensaje)){
                    strcat(nom_img_out, ".pgm");
                    if(EscribirImagenPGM(nom_img_out, buffer, filas, columnas))
                        cout << "Ocultando.." << endl;
                }
        }
        else
            error_lectura = 1;
    }
    else if(LeerTipoImagen(nom_img_in, filas, columnas) == IMG_PPM){
        if(LeerImagenPPM(nom_img_in, filas, columnas, buffer)){
            err_long_mens = long_mensaje+1 > (filas*columnas*3/8);
            if(!err_long_mens)
                if(Ocultar(buffer, mensaje)){
                    strcat(nom_img_out, ".ppm");
                    if(EscribirImagenPPM(nom_img_out, buffer, filas, columnas))
                        cout << "Ocultando.." << endl;
                }
        }
        else
            error_lectura = 1;
    }
    else
        error_formato = 1;

    if(error_formato)
        cerr << "El formato de la imagen es desconocido." << endl;

    if(error_lectura)
        cerr << "Error: la imagen no existe." << endl;

    if(err_long_mens)
        cerr << "Error: el tamanio del mensaje es demasiado grande." << endl;

}


