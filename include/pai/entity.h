#pragma once

#include <nanogui/glutil.h>

class Entity
{
public:
    Entity();

    virtual void update() = 0;
    virtual void draw(NVGcontext* ctx) = 0;

    void setPos(float x, float y);

protected:
    float xpos;
    float ypos;
};
