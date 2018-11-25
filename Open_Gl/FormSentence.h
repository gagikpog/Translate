#ifndef FORMSANTENCE_H
#define FORMSANTENCE_H

#include <iostream>

#include "lib/freeuigl.h"
#include "src/doubleListbox.h"
#include "src/textbox.h"
#include "src/numbox.h"
#include "src/readFromFile.h"
#include "src/Panel.h"
#include "src/WordObj.h"
#include "SettingsStruct.h"

class FormSentenceNew :public UIGL::UiglForms
{
public:
	FormSentenceNew();
	~FormSentenceNew();

	void ReshapeFunc_g(int aw, int ah) 
	{
		update();
	}

	void Proc(UIGL::uiglEvents ev, std::string name) 
	{
		std::cout << "Settings Form new  " << ev << "  " << name << std::endl;
	}
	UIGL::UiglRectangle butt;
	UIGL::UiglRectangle butt1;
	UIGL::UiglRectangle butt2;
	UIGL::UiglRectangle butt3;
	UIGL::UiglRectangle AddLineTranslation;
	Panel panel1;
	std::vector<WordObj> words;
private:

	void initializer() 
	{
		words.insert(words.begin(),30, WordObj());

		for (int i = 0; i < words.size(); i++)
		{
			Stec_push_back(&words[i]);
			words[i].Name = "word" + std::to_string(i);
		}
		Stec_push_back(&butt2);
		Stec_push_back(&panel1);
		Stec_push_back(&AddLineTranslation);
		//	Form5.Stec_push_back(&TestTranslation);
		Stec_push_back(&butt3);
		Stec_push_back(&butt);
		Stec_push_back(&butt1);

		update();
	}

	void update() 
	{
		Background_color = Parameters.BackgroundColor;
		//butt
		butt.Size.setSize(150, 30);
		butt.Position.setPosition(10, UIGL::Jora::WndH - butt.Size.getSizeH() - 10);
		butt.Name = "enter";
		butt.Set_text_size(butt.Size.getSizeH() - 5);
		butt.Text = Text_en_ru[(int)UIGL::Jora::Language][0];
		butt.Color = Parameters.ButtonsColor;
		butt.Outline_color = Parameters.LinesColor;
		butt.Text_color = Parameters.TextsColor;

		//butt1
		butt1.Size.setSize(150, 30);
		butt1.Position.setPosition(10, UIGL::Jora::WndH - butt.Size.getSizeH() - 50);
		butt1.Name = "next";
		butt1.Set_text_size(butt.Size.getSizeH() - 5);
		butt1.Text = Text_en_ru[(int)UIGL::Jora::Language][1];
		butt1.Color = Parameters.ButtonsColor;
		butt1.Outline_color = Parameters.LinesColor;
		butt1.Text_color = Parameters.TextsColor;

		//butt2
		butt2.Size.setSize(150, 30);
		butt2.Position.setPosition(UIGL::Jora::WndW - 160, UIGL::Jora::WndH - 40);
		butt2.Name = "setting";
		butt2.Set_text_size(butt.Size.getSizeH() - 5);
		butt2.Text = Text_en_ru[(int)UIGL::Jora::Language][2];
		butt2.Color = Parameters.ButtonsColor;
		butt2.Outline_color = Parameters.LinesColor;
		butt2.Text_color = Parameters.TextsColor;

		//butt3
		butt3.Size.setSize(UIGL::Jora::WndW, 30);
		butt3.Position.setPosition(0, UIGL::Jora::WndH*0.8);
		butt3.Name = "inf";
		butt3.IsHover = 0;
		butt3.Set_text_size(butt.Size.getSizeH() - 5);
		butt3.Text = "NONE";
		butt3.Color = Parameters.ButtonsColor;
		butt3.Outline_color = Parameters.LinesColor;
		butt3.Text_color = Parameters.TextsColor;
		
		//panel1
		for (int i = 0; i < words.size(); i++)
		{
			words[i].Color = Parameters.ButtonsColor;
			words[i].Outline_color = Parameters.LinesColor;
			words[i].Text_color = Parameters.TextsColor;
		}
		panel1.Position.setPosition(UIGL::Jora::WndMinX, UIGL::Jora::WndMinY);
		panel1.Size.setSize(UIGL::Jora::WndW, UIGL::Jora::WndH*0.8f);
		panel1.Color = Parameters.SelectedColor;
		panel1.Outline_color = Parameters.LinesColor;

		///AddLineTranslation
		AddLineTranslation.Size.setSize(210, 30);
		AddLineTranslation.Position.setPosition(10, UIGL::Jora::WndH*0.8 + 10 + butt3.Size.getSizeH());
		AddLineTranslation.Set_text_size(butt.Size.getSizeH() - 5);
		AddLineTranslation.Text = Text_Form5[(int)UIGL::Jora::Language][0];
		AddLineTranslation.Color = Parameters.ButtonsColor;
		AddLineTranslation.Outline_color = Parameters.LinesColor;
		AddLineTranslation.Text_color = Parameters.TextsColor;
		AddLineTranslation.Name = "Translation";
	}
	const std::string Text_Form5[2][2]{ "Перевод строки",""
		,"Line translation","" };
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

#endif // !FORMSANTENCE_H