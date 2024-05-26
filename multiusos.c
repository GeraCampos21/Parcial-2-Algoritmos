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
    gluOrtho2D(-500, 700, 0, 700);; // 700x700
}

// Estructura para almacenar puntos
typedef struct {
    int x, y;
} Point;

// Número de vértices del polígono
int numVertices = 4;

// Vértices del polígono
                     //h           //i        //f           //g
// Función para dibujar un píxel
void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glVertex2i(-x, y);
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

void setPixe2(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glVertex2i(-x, y);
    glEnd();
    glFlush();
}


void EcuacionG(int size, float x1, float y1, float x2, float y2) {

    if (x1 == x2) {
        int startY = (y1 < y2) ? y1 : y2;
        int endY = (y1 > y2) ? y1 : y2;
        for (int j = startY; j <= endY; j++) {
            glPointSize(size);
            glBegin(GL_POINTS);
/*
            glVertex2f(x1, j);
*/
            setPixe2(x1, j);
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
/*
        glVertex2f(x, y);
*/
        setPixe2(x, y);
    }
    glEnd();
}


void dibujar_multiusos(){
   glClear(GL_COLOR_BUFFER_BIT);
    
   //PRIMERA PARTE DEL DIBUJO ESTO RELLENA Y HACE LAS LINEAS EN ROJO QUE ESTAN ARRIBA DEL RELLENO
   //relleno del edificio
    glColor3f( 0.55, 0.89, 0.96); // Azul para el relleno del polígono
    Point vertices[] = {{135, 545}, {135, 340}, {390, 340}, {390, 545}};
    scanLineFill(vertices, numVertices);
    
    //lineas sobre el relleno del edifico
    glColor3f(0.2,0.5,0.9);
    EcuacionG(10,135,546,391,546);
    EcuacionG(10,391,546,391,340);
    EcuacionG(10,391,340,137,340);
    
    //lineas primera ventana
    glColor3f(1,0,0);
    EcuacionG(15,240,505,240,353);
    EcuacionG(10,145,455,310,455);
    EcuacionG(10,145,390,310,390);
   
   //SEGUNDA PARTE  LO E ENMEDIO
    glColor3f(1,0,0); // Azul para el relleno del polígono
    Point vertices1[] = {{50, 560}, {50, 340}, {132, 340}, {132, 560}};
    scanLineFill(vertices1, numVertices);
    
    //SEGUNDA PARTE  LO E ENMEDIO LA PARTE SUPERIOR QUE ESTA EN ROJO
    glColor3f(1,0,0); // Azul para el relleno del polígono
    Point vertices2[] = {{0, 560}, {0, 528}, {50, 528}, {50, 560}};
    scanLineFill(vertices2, numVertices);
    
    
    
    
    
    
    
    
    
    
    
    glFlush();
       
}

const char* get_carnet(void){
    return "CC19089 and MA19074";
}