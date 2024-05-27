/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   usos_multiples.h
 * Author: gera
 *
 * Created on 27 de mayo de 2024, 10:16
 */

#ifndef USOS_MULTIPLES_H
#define USOS_MULTIPLES_H

#ifdef __cplusplus
extern "C" {
#endif
/**
* Se encarga de inicializar (si es necesario) su invocacion
* esta llamada se realizara una sola vez al inicio de la ejecucion
*/
void inicializar_usos_multiples(void);
/**
* Dibuja su entrega mediante la invocacion del callback
de glut tal y como se mostro en clase.
*/
void dibujar_usos_multiples();

#ifdef __cplusplus
}
#endif

#endif /* USOS_MULTIPLES_H */

