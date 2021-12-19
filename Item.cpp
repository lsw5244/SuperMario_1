#include "Item.h"
#include "Image.h"
#include "MacroCollection.h"

void Item::Spawn(POINTFLOAT pos)
{
    this->pos = pos;
    isSpawning = true;
}

void Item::SpawnAnimation()
{
    pos.y -= spawnSpeed * DELETA_TIME;
    UpdateCollider();
    spawnMoveDistance += spawnSpeed * DELETA_TIME;
    if (spawnMoveDistance > TILE_SIZE)
    {
        isDead = false;
        isSpawning = false;
        spawnMoveDistance = 0.0f;
    }
}

void Item::UpdateCollider()
{
    SetRect(&collider, pos.x - (float)img->GetFrameWidth() / 2,
        pos.y - img->GetFrameWidth() / 2,
        pos.x + img->GetFrameWidth() / 2,
        pos.y + img->GetFrameHeight() / 2);
}

bool Item::OnCollisionEnter(RECT plyaerRect, RECT tileRect)
{
	return false;
}

void Item::Destroy()
{
    if (pos.x > WIN_SIZE_X || pos.x < 0)
    {
        isDead = true;
        isSpawning = false;
        pos = { 0, 0 };
        UpdateCollider();
    }
}
