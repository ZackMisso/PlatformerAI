#pragma once

#include <pai/entity.h>

class Player : public Entity
{
public:
    Player();

    virtual void update();
    virtual void draw(NVGcontext* ctx);
};
