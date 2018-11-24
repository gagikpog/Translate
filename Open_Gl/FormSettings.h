#ifndef FORMSETTINGS_H
#define FORMSETTINGS_H

#include <iostream>

#include "lib/freeuigl.h"
#include "src/doubleListbox.h"
#include "src/textbox.h"
#include "src/numbox.h"
#include "src/readFromFile.h"
#include "SettingsStruct.h"

class FormSettingsNew :public UIGL::UiglForms
{
public:
	FormSettingsNew()
	{
		initializer();
	}
	~FormSettingsNew(){}

	void ReshapeFunc_g(int aw, int ah)
	{
		update();
	}

	void Proc(UIGL::uiglEvents ev, std::string name)
	{

	}

	UIGL::UiglRectangle butt2;

private:

	void initializer()
	{
		butt2.Name = "setting";

		Stec_push_back(&butt2);

	}
	void update()
	{
		//butt2
		butt2.Size.setSize(150, 30);
		butt2.Position.setPosition(UIGL::Jora::WndW - 160, UIGL::Jora::WndH - 40);
		butt2.Set_text_size(butt2.Size.getSizeH() - 5);
		butt2.Text = Text_en_ru[(int)UIGL::Jora::Language][2];
		butt2.Color = Parameters.ButtonsColor;
		butt2.Outline_color = Parameters.LinesColor;
		butt2.Text_color = Parameters.TextsColor;

	}
	const std::string Text_en_ru[2][13]{
		"Проверка","Далее","    Меню",
		"Число отображаемых слов",
		"     Фон",
		"     Текст",
		"     Линия",
		"     Кнопки",
		"     Выбранный",
		"EN",
		"--",
		"Ответы",
		"Ошибки",

		"Checkup","Next","    Menu",
		"The number of displayed words",
		"     Background",
		"     Text",
		"     Line",
		"     Buttons",
		"     Selected",
		"РУ",
		"--",
		"Correct",
		"Wrong"
	};
};


#endif // !FORMSETTINGS_H
