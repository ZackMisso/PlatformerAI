#include <pai/ground.h>

// Ground::Ground()
// {
//     // does nothing now
// }

// the ground does nothing
void Ground::update() { }

void Ground::draw(NVGcontext* ctx)
{
    nvgBeginPath(ctx);
    nvgRect(ctx, int(xpos), int(ypos), 32, 32);
    nvgFillColor(ctx, nvgRGBA(90, 180, 60, 255));
    nvgFill(ctx);
}
