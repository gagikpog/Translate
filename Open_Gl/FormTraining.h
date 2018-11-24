#ifndef FORMTRAINING_H
#define FORMTRAINING_H

#include <iostream>

#include "lib/freeuigl.h"
#include "src/readFromFile.h"
#include "SerringsStruct.h"

class FormTrainingNew:public UIGL::UiglForms
{
public:
	FormTrainingNew()
	{
		initializer();
	}
	~FormTrainingNew(){}
	
	void ReshapeFunc_g(int aw, int ah)
	{
		update();
	}
	void Proc(UIGL::uiglEvents ev, std::string name) 
	{
		std::cout << "Training Form new  " << ev << "  " << name << std::endl;
	}

	UIGL::UiglRectangle butt3;
	UIGL::UiglRectangle butt2;
	UIGL::UiglRectangle butt1;
	UIGL::UiglRectangle butt;
	UIGL::UiglListbox list1;
	UIGL::UiglListbox list2;

private:
	int ans_correct = 0;
	int ans_wrong = 0;
	int word_count = 0;
	void update()
	{
		Background_color = Parameters.BackgroundColor;

		//butt2
		butt2.Size.setSize(150, 30);
		butt2.Position.setPosition(UIGL::Jora::WndW - 160, UIGL::Jora::WndH - 40);
		butt2.Set_text_size(butt2.Size.getSizeH() - 5);
		butt2.Text = Text_en_ru[(int)UIGL::Jora::Language][2];
		butt2.Color = Parameters.ButtonsColor;
		butt2.Outline_color = Parameters.LinesColor;
		butt2.Text_color = Parameters.TextsColor;
		
		//butt
		butt.Size.setSize(150, 30);
		butt.Position.setPosition(10, UIGL::Jora::WndH - butt.Size.getSizeH() - 10);
		butt.Set_text_size(butt.Size.getSizeH() - 5);
		butt.Text = Text_en_ru[(int)UIGL::Jora::Language][0];
		butt.Color = Parameters.ButtonsColor;
		butt.Outline_color = Parameters.LinesColor;
		butt.Text_color = Parameters.TextsColor;

		//butt1
		butt1.Size.setSize(150, 30);
		butt1.Position.setPosition(10, UIGL::Jora::WndH - butt.Size.getSizeH() - 50);
		butt1.Set_text_size(butt.Size.getSizeH() - 5);
		butt1.Text = Text_en_ru[(int)UIGL::Jora::Language][1];
		butt1.Color = Parameters.ButtonsColor;
		butt1.Outline_color = Parameters.LinesColor;
		butt1.Text_color = Parameters.TextsColor;

		//butt3
		butt3.Size.setSize(UIGL::Jora::WndW, 30);
		butt3.Position.setPosition(0, UIGL::Jora::WndH*0.8);
		butt3.IsHover = false;
		butt3.Set_text_size(butt.Size.getSizeH() - 5);
		butt3.Text = std::to_string(word_count) + "/ " + Text_en_ru[(int)UIGL::Jora::Language][11] + ":" + std::to_string(ans_correct) + " " +
			Text_en_ru[(int)UIGL::Jora::Language][12] + ":" + std::to_string(ans_wrong);
		butt3.Color = Parameters.ButtonsColor;
		butt3.Outline_color = Parameters.LinesColor;
		butt3.Text_color = Parameters.TextsColor;
		
		//list1
		list1.Size.setSize(UIGL::Jora::WndW / 2, UIGL::Jora::WndH*0.8);
		list1.Position.setPosition(0, 0);
		list1.Set_text_size(25);
		list1.Color = Parameters.ButtonsColor;
		list1.Outline_color = Parameters.LinesColor;
		list1.Select_color = Parameters.SelectedColor;
		list1.Text_color = Parameters.TextsColor;

		//list2
		list2.Size.setSize(UIGL::Jora::WndW / 2, UIGL::Jora::WndH*0.8);
		list2.Position.setPosition(UIGL::Jora::WndW / 2, 0);
		list2.Set_text_size(25);
		list2.Color = Parameters.ButtonsColor;
		list2.Outline_color = Parameters.LinesColor;
		list2.Select_color = Parameters.SelectedColor;
		list2.Text_color = Parameters.TextsColor;
	}

	void initializer() 
	{
		butt.Name = "enter";
		butt2.Name = "setting";
		butt1.Name = "next";
		butt3.Name = "inf";
		list1.Name = "list1";
		list2.Name = "list2";

		Stec_push_back(&butt3);
		Stec_push_back(&butt2);
		Stec_push_back(&butt1);
		Stec_push_back(&butt);
		Stec_push_back(&list1);
		Stec_push_back(&list2);
		update();
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

#endif // !FORMTRAINING_H
