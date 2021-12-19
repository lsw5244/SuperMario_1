#include "Item.h"
#include "Image.h"
#include "MacroCollection.h"

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
    }
}
