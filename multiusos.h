/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   multiusos.h
 * Author: gera
 *
 * Created on 24 de mayo de 2024, 09:00
 */

#ifndef MULTIUSOS_H
#define MULTIUSOS_H

#ifdef __cplusplus
extern "C" {
#endif
/**
* Se encarga de inicializar (si es necesario) su invocacion
* esta llamada se realizara una sola vez al inicio de la ejecucion
*/
void inicializar_multiusos(void);
/**
* Dibuja su entrega de multiusos
*/
void dibujar_multiusos();

/**
* retorne su numero de carnet en la invocacion, en base a esto se asignara su nota de forma automatica
*/
const char* get_carnet(void);



#ifdef __cplusplus
}
#endif

#endif /* MULTIUSOS_H */

