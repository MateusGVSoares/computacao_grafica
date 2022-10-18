#include "Entidade.h"
#include "Shot.h"
#include "Texturazer.h"
#include <bits/stdc++.h>
#include "../parser.h"

class Player : public Entidade , public Texturazer 
{
public:
    Player(vec3f_t origin, int layer, float angle, float velocidade, std::vector<vec3f_t> hit_box, std::vector<vec3f_t> model,std::vector<GLuint> tex_vec,std::vector<std::pair<GLfloat,GLfloat>> texture_cord);
    using Entidade::Entidade;
    using Texturazer::Texturazer;
    Shot playerFire();
    int updateOnKeyboard(keyboard_t keys);
    void move() override;
    void draw() override;
    void treatColide(int col_type) override;
};