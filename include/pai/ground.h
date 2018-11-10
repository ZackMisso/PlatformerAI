#pragma once

#include <pai/entity.h>

class Ground : public Entity
{
public:
    // Ground();

    virtual void update();
    virtual void draw(NVGcontext* ctx);
};
