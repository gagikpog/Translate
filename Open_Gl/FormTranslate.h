#ifndef FORMTRANSLATE_H
#define FORMTRANSLATE_H

#include <iostream>

#include "lib/freeuigl.h"
#include "src/doubleListbox.h"
#include "src/textbox.h"
#include "src/numbox.h"
#include "src/readFromFile.h"
#include "SettingsStruct.h"


class FormTranslateNew:public UIGL::UiglForms
{
public:
	FormTranslateNew();
	~FormTranslateNew();

	void ReshapeFunc_g(int aw, int ah);
	void Proc(UIGL::uiglEvents ev, std::string name);

	doubleListbox list_l;
	textbox inp2;
	textbox out2;
	UIGL::UiglRectangle cutword;
	UIGL::UiglRectangle butt2;
	UIGL::UiglRectangle butt;
	UIGL::UiglRectangle favor;
	UIGL::UiglPicture swap1;
	numbox inp;
	bool Translate_to = false;

private:
	UIGL::UiglMessageBox messageBox;
	std::vector<UIGL::string_int> My_data;	
	std::string dataFilename = "selfnew.txt";

	void initializer();
	void update();
	void list_updat();	
	void translate();
	void favourite();
	bool Add_word();

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
	const std::string Head_en_ru[2][8]{ "     Настрoйки",	"   Переводчик",	"    Тренировка",	"    В разработке" ,	"Английский",	"Русский","Добавить в избранные"," Удалить",
		"        Settings",	"       Translate",	"       Training",	"   In developing",	"English",		"Russian","Add to favorites"," Remove" };
	const std::string MsgString[2][8]{ "Справка",	"Это слово уже существует",	"Заполните поля"	,"Слово не найдено"	,"Вы действительно хотите удалить это слово?",	"","","",
		"Reference","This word already exists",	"Fill in the fields","Word not found"	,"Are you sure you want to delete this word?",	"","","" };
};

#endif // !FORMTRANSLATE_H