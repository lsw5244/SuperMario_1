#include "Item.h"
#include "Image.h"

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
