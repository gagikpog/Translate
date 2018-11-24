#ifndef FORMTRAINING_H
#define FORMTRAINING_H

#include <iostream>

#include "lib/freeuigl.h"
#include "src/readFromFile.h"
#include "SettingsStruct.h"

class FormTrainingNew: public UIGL::UiglForms
{
public:
	FormTrainingNew();
	~FormTrainingNew();
	
	void ReshapeFunc_g(int aw, int ah);
	void Proc(UIGL::uiglEvents ev, std::string name);

	UIGL::UiglRectangle butt3;
	UIGL::UiglRectangle butt2;
	UIGL::UiglRectangle butt1;
	UIGL::UiglRectangle butt;
	UIGL::UiglListbox list1;
	UIGL::UiglListbox list2;

private:
	int ans_correct = 0;
	int ans_wrong = 0;
	int word_count = 10;

	std::vector<UIGL::string_int> My_data;
	std::vector<UIGL::string_int*> My_sub_data;

	void update();
	void initializer();

	bool cut_data(std::vector<UIGL::string_int*>& sub_mas, std::vector<UIGL::string_int>& mas, int sub_mas_size);
	void resetlist();
	std::string translate(std::string text_en);

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

#endif // !FORMTRAINING_H
