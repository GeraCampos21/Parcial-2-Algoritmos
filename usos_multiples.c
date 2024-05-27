/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.c to edit this template
 */

#include "./usos_multiples.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdlib.h>

void inicializar_usos_multiples(void) {
    glClearColor(0.5, 0.75, 1.0, 1.0); // gray color
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-700, 700, -700, 700);; // 700x700
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


// Función para rellenar el polígono utilizando Scan-Line Fill
void relleno(Point *vertices, int numVertices) {
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


void lineas(int size, float x1, float y1, float x2, float y2) {

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

void jardin(float radioX, float radioY, float centerX, float centerY, float LimiteAng) {
    if (radioX > 0 && radioY > 0) {
        if (LimiteAng > 360) {
            exit(EXIT_FAILURE);
        }

        glBegin(GL_TRIANGLE_FAN);
        glColor3f(0, 1, 0); // color verde para rellenar la elipse
        glVertex2f(centerX, centerY); // centro de la elipse

        for (float angle = 0; angle <= LimiteAng; angle++) {
            float radian = angle * (M_PI / 180); // para pasar a radianes

            float x = centerX + radioX * cos(radian); // coordenada x
            float y = centerY + radioY * sin(radian); // coordenada y

            glVertex2f(x, y);
        }
        glVertex2f(centerX + radioX * cos(0), centerY + radioY * sin(0)); // cierra la elipse
        glEnd();
    } else {
        exit(EXIT_FAILURE);
    }
}

void lamparas(float radio, float centerX, float centerY, float LimiteAng)
{
    if (radio > 0)
    {
        if (LimiteAng > 360)
        {
           
            exit(EXIT_FAILURE);
        }

        glBegin(GL_TRIANGLE_FAN);
        glColor3f(1, 1, 1);           // color blanco para rellenar el círculo
        glVertex2f(centerX, centerY); // centro del círculo

        for (float angle = 0; angle <= LimiteAng; angle++)
        {
            float radian = angle * (M_PI / 180); // para pasar a radianes

            float x = centerX + radio * cos(radian); // coordenada x
            float y = centerY + radio * sin(radian); // coordenada y

           glVertex2i(x,y);
            
        }

        glVertex2f(centerX + radio * cos(0), centerY + radio * sin(0)); // cierra el círculo
        glEnd();
    }
    else
    {
        
        exit(EXIT_FAILURE);
    }
}



void dibujar_usos_multiples(){
   glClear(GL_COLOR_BUFFER_BIT);
    
   //PRIMERA PARTE DEL DIBUJO ESTO RELLENA Y HACE LAS LINEAS EN ROJO QUE ESTAN ARRIBA DEL RELLENO
   //relleno del edificio
    glColor3f( 0.55, 0.89, 0.96); // Azul para el relleno del polígono
    //                     c            d           e           f
    Point vertices[] = {{572,564}, {572, 237}, {217,237}, {217, 564}};
    relleno(vertices, numVertices);
    
    //lineas sobre el relleno del edifico
    glColor3f(0.2,0.5,0.9);
    lineas(4,572,564,572, 237); // c a d
    lineas(4,572, 237,217,237);// d a e
    lineas(2,217,237,217, 564);// e a f
    lineas(4,217, 564,572,564);//f a c ( cierro el cuadrado)
    
    
   
   //SEGUNDA PARTE  LO E ENMEDIO
    glColor3f(1,0,0); // Azul para el relleno del polígono
    Point vertices1[] = {{210, 227}, {210, 590}, {70, 590}, {70, 227}};
    relleno(vertices1, numVertices);
    
    //SEGUNDA PARTE  LO E ENMEDIO LA PARTE SUPERIOR QUE ESTA EN ROJO
    glColor3f(1,0,0); // Azul para el relleno del polígono
    Point vertices2[] = {{70, 590}, {70, 530}, {0, 530}, {0, 590}};
    relleno(vertices2, numVertices);
    
    //Ventanas 
    
    //Ventanas de lo mas derecho ( mas cortas)
    
    //Arriba
    glColor3f(0.62745,0.2509,0);
    Point vertices3[] = {{390,520}, {460,520 }, {460,463 }, {390,463}};
    relleno(vertices3, numVertices);
    glColor3f(0,0,0);
    lineas(4,410,520,410,463);
    lineas(4,440,520,440,463);
    
    //Medio
    glColor3f(0.62745,0.2509,0);
    Point vertices4[] = {{390,411}, {460,411 }, {460,360 }, {390,360}};
    relleno(vertices4, numVertices);
    glColor3f(0,0,0);
    lineas(4,410,406,410,360);
    lineas(4,440,406,440,360);
    
    //Abajo
    glColor3f(0.62745,0.2509,0);
    Point vertices5[] = {{390,310}, {460,310 }, {460,255 }, {390,255}};
    relleno(vertices5, numVertices);
    glColor3f(0,0,0);
    lineas(4,410,310,410,255);
    lineas(4,440,310,440,255);
    
    
    //Ventanas pegadas al pilar rojo ( las mas anchas y largas)
    //Arriba
    glColor3f(0.62745,0.2509,0);
    Point vertices6[] = {{366,520}, {226,520 }, {226,463 }, {366,463}};
    relleno(vertices6, numVertices);
    glColor3f(0,0,0);
    lineas(4,261,520,261,463);
    lineas(4,296,520,296,463);
    lineas(4,331,520,331,463);
    
    //Medio
    glColor3f(0.62745,0.2509,0);
    Point vertices7[] = {{226,411}, {366,411 }, {366,360 }, {226,360}};
    relleno(vertices7, numVertices);
    glColor3f(0,0,0);
    lineas(4,261,406,261,360);
    lineas(4,296,406,296,360);
    lineas(4,331,406,331,360);
    
    //Abajo
    glColor3f(0.62745,0.2509,0);
    Point vertices8[] = {{226,310}, {366,310 }, {366,255 }, {226,255}};
    relleno(vertices8, numVertices);
    glColor3f(0,0,0);
    lineas(4,261,310,261,255);
    lineas(4,296,310,296,255);
    lineas(4,331,310,331,255);
    
   
    
    //lineas primera ventana
    glColor3f(1,0,0);
    lineas(13,380,520,380,251);// g a h
    lineas(10,217,422,470,422);// i a j
    lineas(10,217,317,470,317);// k a l
    
    
    
    //Ventanas de enmedio
    glColor3f(0.62745,0.2509,0);
    Point vertices9[] = {{180,528}, {190,528 }, {190,454 }, {180,454}};
    relleno(vertices9, numVertices);
    
    glColor3f(0.62745,0.2509,0);
    Point vertices10[] = {{135,528}, {145,528 }, {145,454 }, {135,454}};
    relleno(vertices10, numVertices);
    
    glColor3f(0.62745,0.2509,0);
    Point vertices11[] = {{90,528}, {100,528 }, {100,454 }, {90,454}};
    relleno(vertices11, numVertices);
    
    
    
    glColor3f(0.62745,0.2509,0);
    Point vertices12[] = {{180,420}, {190,420 }, {190,346 }, {180,346}};
    relleno(vertices12, numVertices);
    
    glColor3f(0.62745,0.2509,0);
    Point vertices13[] = {{135,420}, {145,420 }, {145,346 }, {135,346}};
    relleno(vertices13, numVertices);
    
    glColor3f(0.62745,0.2509,0);
    Point vertices14[] = {{90,420}, {100,420 }, {100,346 }, {90,346}};
    relleno(vertices14, numVertices);
    
    
    
    glColor3f(0.62745,0.2509,0);
    Point vertices15[] = {{180,314}, {190,314 }, {190,265 }, {180,265}};
    relleno(vertices15, numVertices);
    
    glColor3f(0.62745,0.2509,0);
    Point vertices16[] = {{135,314}, {145,314 }, {145,265 }, {135,265}};
    relleno(vertices16, numVertices);
    
    glColor3f(0.62745,0.2509,0);
    Point vertices17[] = {{90,314}, {100,314 }, {100,265 }, {90,265}};
    relleno(vertices17, numVertices);
    
    
    //dibujar las lamparas
    glColor3f(1, 1, 0);
    lamparas(10,380,420,360);
    lamparas(10,-380,420,360);
    
    //Parte de enmedio
    //Relleno de la pintura blanca
    glColor3f(1,1,1);
    Point vertices21[] = {{0,515}, {55,515 }, {55,232 }, {0,232}};
    relleno(vertices21, numVertices);
    
    
    //Ventana superior
    glColor3f(0.62745,0.2509,0);
    Point vertices18[] = {{0,500}, {40,500 }, {40,450 }, {0,450}};
    relleno(vertices18, numVertices);
    glColor3f(0,0,0);
    lineas(2,0,505,0,443);
    lineas(2,20,505,20,443);
    lineas(2,0,474,47,474);
    
    
    //Ventana medio
    glColor3f(0.62745,0.2509,0);
    Point vertices19[] = {{0,410}, {40,410 }, {40,340 }, {0,340}};
    relleno(vertices19, numVertices);
    glColor3f(0,0,0);
    lineas(2,0,410,0,340);
    lineas(2,20,410,20,340);
    lineas(2,0,375,40,375);
    
    //Puerta
    glColor3f(0.62745,0.2509,0);
    Point vertices20[] = {{0,300}, {40,300 }, {40,237 }, {0,237}};
    relleno(vertices20, numVertices);
    glColor3f(0,0,0);
    lineas(2,0,300,0,237); //linea divisoria
    lineas(2,0,280,40,280);
    
    //para hacer lo que es el jardin en verde
    jardin(350.0,45.0,0,180.0,360.0);
    
    
    
    glFlush();
       
}