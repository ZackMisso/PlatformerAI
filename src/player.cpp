#include <pai/player.h>

Player::Player()
{
    // TODO
}

void Player::update()
{
    // TODO
}

void Player::draw(NVGcontext* ctx)
{
    nvgBeginPath(ctx);
    nvgRect(ctx, int(xpos), int(ypos), 32, 32);
    nvgFillColor(ctx, nvgRGBA(40, 60, 180, 255));
    nvgFill(ctx);
}
