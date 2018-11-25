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
	FormSettingsNew();
	~FormSettingsNew();

	void ReshapeFunc_g(int aw, int ah);
	void Proc(UIGL::uiglEvents ev, std::string name);

	UIGL::UiglRectangle butt2;
	numbox inp;
	const int sett_col_size = 7;
	UIGL::UiglRectangle sett_col[7];

private:

	void initializer();
	void update();

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
