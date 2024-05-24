/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/main.c to edit this template
 */

/* 
 * File:   main.c
 * Author: gera
 *
 * Created on 24 de mayo de 2024, 08:56
 */
#include "./multiusos.h"
#include <stdio.h>
#include <stdlib.h>
#include<GL/glut.h>
#include<GL/glu.h>
#include<GL/gl.h>
#include<GL/freeglut.h>
#include <math.h>



int main(int argc, char** argv) {
    printf("Examen parcial de %s \n",get_carnet());
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(700, 700);
    glutCreateWindow(get_carnet());
    glClearColor(0.8, 0, 0, 1);
    inicializar_multiusos();
    glutDisplayFunc(dibujar_multiusos);
    glutMainLoop();
    printf("=== fin ===");
    return (EXIT_SUCCESS);
}
