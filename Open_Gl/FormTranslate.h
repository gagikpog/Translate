#ifndef FORMTRANSLATE_H
#define FORMTRANSLATE_H

#include <iostream>

#include "lib/freeuigl.h"
#include "src/doubleListbox.h"
#include "src/textbox.h"
#include "src/numbox.h"


class FormTranslateNew:public UIGL::UiglForms
{
public:
	FormTranslateNew() {
		Wnd_proc = Proc;
		initializer();
	}
	~FormTranslateNew(){}

	doubleListbox list_l;
	textbox inp2;
	textbox out2;
	UIGL::UiglRectangle cutword;
	UIGL::UiglRectangle butt2;
	UIGL::UiglRectangle butt;
	UIGL::UiglRectangle favor;
	UIGL::UiglPicture swap1;
	numbox inp;

	void ReshapeFunc_g(int aw, int ah)
	{
		update();
	}

	static void Proc(UIGL::uiglEvents ev,std::string name)
	{
		std::cout << "FormTranslate  " << ev << "  " << name << std::endl;
	}

	bool Translate_to = false;
private:
	void initializer()
	{
		Stec_push_back(&list_l);
		list_l.Name = "list_l";

		Stec_push_back(&cutword);
		Stec_push_back(&butt2);
		Stec_push_back(&inp2);

		Stec_push_back(&out2);
		Stec_push_back(&swap1);
		Stec_push_back(&favor);
		swap1.Open("swap.ggp");

		update();
	}
	void update()
	{
		//list_l
		{
			list_l.Size.setSize(UIGL::Jora::WndW, UIGL::Jora::WndH*0.8);
			list_l.Position.setPosition(0, 0);
			list_l.Set_text_size(25);
			//list_l.Color = button_col;
			//list_l.Outline_color = line_col;
			//list_l.Select_color = select_col;
			//list_l.Text_color = text_col;
		}
		//butt2
		{
			butt2.Size.setSize(150, 30);
			butt2.Position.setPosition(UIGL::Jora::WndW - 160, UIGL::Jora::WndH - 40);
			butt2.Name = "setting";
			butt2.Set_text_size(butt.Size.getSizeH() - 5);
			butt2.Text = Text_en_ru[(int)UIGL::Jora::Language][2];
			//butt2.Color = button_col;
			//butt2.Outline_color = line_col;
			//butt2.Text_color = text_col;
		}
		//inp
		{
			inp.NumbersOnly = 1;
			inp.Size.setSize(70, 30);
			inp.Set_text_size(inp.Size.getSizeH() - 6);
			inp.Name = "textbox";
			inp.Position.setPosition(10, UIGL::Jora::WndH - inp.Size.getSizeH() - 10);
			inp.Title = Text_en_ru[(int)UIGL::Jora::Language][3];
			inp.SetMin(5);
			inp.SetMax(99);
			inp.Text_max_length = 2;
			//inp.Color = button_col;
			//inp.Outline_color = line_col;
			//inp.Text_color = text_col;
		}
		//butt
		{
			butt.Size.setSize(150, 30);
			butt.Position.setPosition(10, UIGL::Jora::WndH - butt.Size.getSizeH() - 10);
			butt.Name = "enter";
			butt.Set_text_size(butt.Size.getSizeH() - 5);
			butt.Text = Text_en_ru[(int)UIGL::Jora::Language][0];
			//butt.Color = button_col;
			//butt.Outline_color = line_col;
			//butt.Text_color = text_col;
		}
		//inp2
		{
			inp2.Size.setSize(UIGL::Jora::WndW*0.5 - 35, 30);
			inp2.Set_text_size(inp.Size.getSizeH() - 6);
			inp2.Name = "inp2";
			inp2.Position.setPosition(10, UIGL::Jora::WndH - 80);
			//inp2.Color = button_col;
			//inp2.Outline_color = line_col;
			//inp2.Text_color = text_col;
			inp2.Text_align = UIGL::uiglBottomCenter;
		}
		//favor
		{
			favor.Size.setSize(300, 30);
			favor.Position.setPosition(10, UIGL::Jora::WndH - butt.Size.getSizeH() - 10);
			favor.Name = "favor";
			favor.Set_text_size(butt.Size.getSizeH() - 5);
			favor.Text = Head_en_ru[(int)UIGL::Jora::Language][6];
			//favor.Color = button_col;
			//favor.Outline_color = line_col;
			//favor.Text_color = text_col;
		}
		//cutword
		{
			cutword.Size.setSize(150, 30);
			cutword.Position.setPosition(UIGL::Jora::WndW - 160, UIGL::Jora::WndH*0.8 + 10);
			cutword.Name = "cutword";
			cutword.Set_text_size(butt.Size.getSizeH() - 5);
			cutword.Text = Head_en_ru[(int)UIGL::Jora::Language][7];
			//cutword.Color = button_col;
			//cutword.Outline_color = line_col;
			//cutword.Text_color = text_col;
		}
		//out2
		{
			out2.Size.setSize(UIGL::Jora::WndW*0.5f - 35, 30);
			out2.Position.setPosition(UIGL::Jora::WndW*0.5f + 25, UIGL::Jora::WndH - 80);
			out2.Name = "out2";
			out2.Set_text_size(butt.Size.getSizeH() - 5);
			//out2.Color = button_col;
			//out2.Outline_color = line_col;
			//out2.Text_color = text_col;
			out2.Text_align = UIGL::uiglBottomCenter;
		}
		//swap1
		{
			swap1.Size.setSize(40, 40);
			swap1.Position.setPosition(UIGL::Jora::WndW*0.5f - 20, UIGL::Jora::WndH - 85);
			//		swap1.Position.setPosition(Jora::WndW, Jora::WndH);		
			swap1.Name = "swap1";
			//swap1.Color = button_col;
			//swap1.Outline_color = line_col;
		}
		if (!Translate_to)
		{
			inp2.Title = Head_en_ru[(int)UIGL::Jora::Language][4];
			out2.Title = Head_en_ru[(int)UIGL::Jora::Language][5];
		}
		else {
			inp2.Title = Head_en_ru[(int)UIGL::Jora::Language][5];
			out2.Title = Head_en_ru[(int)UIGL::Jora::Language][4];
		}
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
	const std::string Head_en_ru[2][8]{ "     Настрoйки",	"   Переводчик",	"    Тренировка",	"    В разработке" ,	"Английский",	"Русский","Добавить в избранные"," Удалить",
		"        Settings",	"       Translate",	"       Training",	"   In developing",	"English",		"Russian","Add to favorites"," Remove" };

};

#endif // !FORMTRANSLATE_H