/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.c to edit this template
 */

#include "./multiusos.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdlib.h>

void inicializar_multiusos(void) {
    glClearColor(0.6, 0.6, 0.6, 1.0); // gray color
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 700, 0, 700); // 700x700
}

// Estructura para almacenar puntos
typedef struct {
    int x, y;
} Point;

// Número de vértices del polígono
int numVertices = 4;

// Vértices del polígono
                     //h           //i        //f           //g
Point vertices[] = {{450, 231}, {450, 394}, {630, 394}, {630, 231}};

// Función para dibujar un píxel
void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

// Función para dibujar el polígono
void drawPolygon(Point *vertices, int numVertices) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numVertices; i++) {
        glVertex2i(vertices[i].x, vertices[i].y);
    }
    glEnd();
    glFlush();
}
// Función para rellenar el polígono utilizando Scan-Line Fill
void scanLineFill(Point *vertices, int numVertices) {
    int i, j, k;
    int x, y, temp;
    int minY = vertices[0].y, maxY = vertices[0].y;

    // Encontrar las coordenadas y mínima y máxima
    for (i = 1; i < numVertices; i++) {
        if (vertices[i].y < minY)
            minY = vertices[i].y;
        if (vertices[i].y > maxY)
            maxY = vertices[i].y;
    }

    // Scan-Line Fill
    for (y = minY; y <= maxY; y++) {
        int intersections[numVertices];
        int numIntersections = 0;

        // Encontrar las intersecciones con las aristas del polígono
        for (i = 0; i < numVertices; i++) {
            int next = (i + 1) % numVertices;
            if ((vertices[i].y <= y && vertices[next].y > y) ||
                (vertices[i].y > y && vertices[next].y <= y)) {
                int intersectX = vertices[i].x + (y - vertices[i].y) * (vertices[next].x - vertices[i].x) / (vertices[next].y - vertices[i].y);
                intersections[numIntersections++] = intersectX;
            }
        }

        // Ordenar las intersecciones
        for (j = 0; j < numIntersections - 1; j++) {
            for (k = j + 1; k < numIntersections; k++) {
                if (intersections[j] > intersections[k]) {
                    temp = intersections[j];
                    intersections[j] = intersections[k];
                    intersections[k] = temp;
                }
            }
        }

        // Dibujar píxeles entre pares de intersecciones
        for (i = 0; i < numIntersections; i += 2) {
            for (x = intersections[i]; x <= intersections[i + 1]; x++) {
                setPixel(x, y);
            }
        }
    }
}
void EcuacionG(int size, float x1, float y1, float x2, float y2) {

    if (x1 == x2) {
        int startY = (y1 < y2) ? y1 : y2;
        int endY = (y1 > y2) ? y1 : y2;
        for (int j = startY; j <= endY; j++) {
            glPointSize(size);
            glBegin(GL_POINTS);
            glVertex2f(x1, j);
            glEnd();
        }
    }

    float m = (y2 - y1) / (x2 - x1);
    float b = y1 - (m * x1);

    float dx = x2 - x1;
    float dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xIncrement = dx / steps;
    float yIncrement = dy / steps;

    glPointSize(size);
    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        float x = x1 + i * xIncrement;
        float y = m * x + b;
        glVertex2f(x, y);
    }
    glEnd();
}


void dibujar_multiusos(){
   glClear(GL_COLOR_BUFFER_BIT);
   
     //borde del edificio
    //{{450, 231}, {450, 394}, {630, 394}, {630, 231}
    glColor3f( 0, 0, 1);
    EcuacionG(5,450, 396,632, 396);
    EcuacionG(5,634, 396,634, 228);
    EcuacionG(5,634, 228,450, 228);
    
    //relleno del edificio
    glColor3f( 0.55, 0.89, 0.96); // Azul para el relleno del polígono
    scanLineFill(vertices, numVertices);
    
    Point vertices1[] = {{536, 369}, {576, 369}, {576, 342}, {536, 342}};
    glColor3f( 0.0, 0.0, 0.0); // Azul para el relleno del polígono
    scanLineFill(vertices1, numVertices);
    
    Point vertices2[] = {{534, 316}, {574, 316}, {574, 290}, {534, 290}};
    glColor3f( 0.0, 0.0, 0.0); // Azul para el relleno del polígono
    scanLineFill(vertices2, numVertices);
    
    Point vertices3[] = {{534, 265}, {574, 265}, {574, 238}, {534, 238}};
    glColor3f( 0.0, 0.0, 0.0); // Azul para el relleno del polígono
    scanLineFill(vertices3, numVertices);
    
    
    // Ventanas de Marroquin
    //                      r1           s1         t1          u1
     Point vertices4[] = {{450,369 }, {528,369 }, {528,342 }, {450,342 }};
     glColor3f( 0.0, 0.0, 0.0); // Azul para el relleno del polígono
     scanLineFill(vertices4, numVertices);
     
     //                      v1           w1         z1          a2
     Point vertices5[] = {{450,316}, {528,316 }, {528,290 }, {450,290 }};
     glColor3f( 0.0, 0.0, 0.0); // Azul para el relleno del polígono
     scanLineFill(vertices5, numVertices);
     
     //                      b2           c2         d2          e2
     Point vertices6[] = {{450,265 }, {528,265 }, {528,238 }, {450,238 }};
     glColor3f( 0.0, 0.0, 0.0); // Azul para el relleno del polígono
     scanLineFill(vertices6, numVertices);
     
    
    
    //los pilares derechos
    glColor3f( 1, 0, 0);
    EcuacionG(10,530,365,530,233);
    glColor3f( 1, 0, 0);
    EcuacionG(10,453,320,574,320);
    glColor3f( 1, 0, 0);
    EcuacionG(10,574,267,453,267);
    
    
    //edificio en medio
    glColor3f(1,0,0);
    EcuacionG(5,450,228,450,408);
    glColor3f(1,0,0);
    EcuacionG(5,450,408,380,408);
    glColor3f(3,0,0);
    EcuacionG(5,380,408,380,228);
    glColor3f(1,0,0);
    EcuacionG(5,380,228,450,228);
/*
    Point vertices[] = {{25, 25}, {150, 25}, {150, 150}, {25, 150}};
    glColor3f(0.0, 0.0, 0.0); // Rojo para el relleno del polígono
    scanLineFill(vertices, numVertices);
*/
    glFlush();
       
}



const char* get_carnet(void){
    return "CC19089 and MA19074";
}