
// Libs
#include <bits/stdc++.h>
#include <GL/freeglut.h>
#include "include/algebra.h"
#include "include/callback.h"
#include "include/parser.h"

// Classes
#include "include/classes/Entidade.h"
#include "include/classes/Player.h"
#include "include/classes/Shot.h"

// TODO: Classes inacabadas
 #include "include/classes/World.h"
// #include "include/classes/Enemy.h"
// #include "include/classes/Colider.h"
 #include "include/classes/Texturazer.h"

// VAMOS MEU CAMISA 09 >_< (Updated by Mateus on 16/08, 11:00:01)
Player *joga;
std::vector<Shot> entities;
World *mundo;

void drawUpdate()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    if (joga->getOnScreen())
    {
        glEnable(GL_TEXTURE_2D);
        joga->draw();
        glDisable(GL_TEXTURE_2D);
    }
    else
    {
        printf("Ta dentro AI \n");
    }
    for (int i = 0; i < entities.size(); i++)
    {
        if (entities[i].getOnScreen())
            entities[i].draw();
    }

    glutSwapBuffers();
}

float timer_count = 0;
float world_time = 0;

void onTimeUpdate(int time)
{
    // Updates the movements
    int shot = joga->updateOnKeyboard(keyboard);
    joga->move();

    if (shot && timer_count > 1)
    {
        timer_count = 0;
        entities.push_back(joga->playerFire());
    }

    for (int i = 0; i < entities.size(); i++)
    {
        entities[i].move();
        entities[i].updateModel();
    }

    // Updates the collisions boxes
    joga->updateModel();

    // Treats the collisions

    // Draws everything <3
    glutPostRedisplay();

    //tempo globais para auxiliar a classe World
    timer_count += (float)time / 1000;
    world_time += (float)time / 1000;
    mundo->start_mission(&world_time);
    // Restarts the timerFunc
    glutTimerFunc(time, onTimeUpdate, time);
}

void configGlut()
{
    // Configura a janela da GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Game");

    // Configura os callbacks da GLUT
    glutDisplayFunc(drawUpdate);
    glutReshapeFunc(reshapeFct);
    glutKeyboardFunc(keyboardFct);
    glutKeyboardUpFunc(keyboardFct);
    glutSpecialFunc(keyboardSpecial);
    glutSpecialUpFunc(keyboardSpecial);

    glutTimerFunc(16, onTimeUpdate, 16);

    glLineWidth(8);
    glClearColor(1, 1, 1, 1);

    // Ignora repetições de teclas e verifica apenas o pressionamento e qnd soltar
    glutIgnoreKeyRepeat(1);
}

void initPlayer()
{
    std::vector<vec3f_t> vector;
    std::vector<GLuint> texture_vec;
    std::vector<std::pair<GLfloat,GLfloat>> texture_coord;
    if (!parse_model(&vector, "model"))
    {
        printf("DEU BOM NO FILE \n");
    }
    /*if(!parse_texture(%texture_vec,"texture.txt"))
        printf(" DEU BOM NO PARSER DA TEXTURA\n");
    */
    vec3f_t origin = {
        .x = 0,
        .y = 0,
        .z = 0};

    joga = new Player(origin, 0, 0.0f, 1.0f, vector, vector,texture_vec,texture_coord);
    mundo = new World();
    //mundo->initialize_script_mission();
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);

    initPlayer();

    configGlut();

    glutMainLoop();

    return 0;
}

/*
        Updated By : Camisa 09

        if you hear a voice within you say 'you cannot paint',
         then by all means paint, and that voice will be silenced.
        , Vincent Van Gogh

        -> https://www.youtube.com/watch?v=dQw4w9WgXcQ
*/