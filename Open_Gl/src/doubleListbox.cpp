#include "doubleListbox.h"

void doubleListbox::Init()
{
	int _count = ((H - 10.0f) / Text_size);
	UiglListbox::Init();
	for (int i = 0; i < Items1.size() - item_up_num && i < _count; i++)
	{
		textprint.glText(X + W / 2 + 5, Y + H - 2 - (i + 1)*Text_size, Items1[i + item_up_num], Text_color);
	}
	Outline_color.Init();
	glBegin(GL_LINES);
	glVertex2f(Position.getPositionX() + Size.getSizeW() / 2.0f, Position.getPositionY());
	glVertex2f(Position.getPositionX() + Size.getSizeW() / 2.0f, Position.getPositionY() + Size.getSizeH());
	glEnd();
}