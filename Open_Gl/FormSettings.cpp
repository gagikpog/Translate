#include "FormSettings.h"

FormSettingsNew::FormSettingsNew()
{
	initializer();
}

FormSettingsNew::~FormSettingsNew()
{
}

void FormSettingsNew::ReshapeFunc_g(int aw, int ah)
{
	update();
}

void FormSettingsNew::Proc(UIGL::uiglEvents ev, std::string name)
{
	std::cout << "Settings Form new  " << ev << "  " << name << std::endl;

	if (ev == UIGL::uiglEvents::uiglChanged && name == "textbox")
	{
		Parameters.TestWordsCount = std::stoi(inp.Text);
	}

	if ((ev == UIGL::uiglEvents::uiglMouseLeftDown || ev == UIGL::uiglEvents::uiglEnter) && name.substr(0, 6) == "setcol")
	{
		switch (name[6])
		{
		case '0':
			Focus_push_back(&UIGL::Jora::ColDial);
			UIGL::Jora::ColDial.Diolog(&Parameters.BackgroundColor, Text_en_ru[(int)UIGL::Jora::Language][4]);
			break;
		case '1':
			Focus_push_back(&UIGL::Jora::ColDial);
			UIGL::Jora::ColDial.Diolog(&Parameters.TextsColor, Text_en_ru[(int)UIGL::Jora::Language][5]);
			break;
		case '2':
			Focus_push_back(&UIGL::Jora::ColDial);
			UIGL::Jora::ColDial.Diolog(&Parameters.LinesColor, Text_en_ru[(int)UIGL::Jora::Language][6]);
			break;
		case '3':
			Focus_push_back(&UIGL::Jora::ColDial);
			UIGL::Jora::ColDial.Diolog(&Parameters.ButtonsColor, Text_en_ru[(int)UIGL::Jora::Language][7]);
			break;
		case '4':
			Focus_push_back(&UIGL::Jora::ColDial);
			UIGL::Jora::ColDial.Diolog(&Parameters.SelectedColor, Text_en_ru[(int)UIGL::Jora::Language][8]);
			break;
		case '5':
			if (UIGL::Jora::Language == UIGL::uiglLanguageRU)
				UIGL::Jora::Language = UIGL::uiglLanguageEN;
			else UIGL::Jora::Language = UIGL::uiglLanguageRU;
			//				conf.Set_count("en", (int)UIGL::Jora::Language);
			//				Bild_Window();
			break;
		default:
			break;
		}
		return;
	}
	if (ev == UIGL::uiglEvents::uiglEraseMsg && name == "dialog")
		update();

}

void FormSettingsNew::initializer()
{
	butt2.Name = "setting";
	inp.Name = "textbox";

	Stec_push_back(&butt2);
	Stec_push_back(&inp);
	for (int i = 0; i < sett_col_size; i++)
	{
		Stec_push_back(&sett_col[i]);
	}
	inp.Text = std::to_string(Parameters.TestWordsCount);
}

void FormSettingsNew::update()
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

	//inp
	inp.NumbersOnly = 1;
	inp.Size.setSize(70, 30);
	inp.Set_text_size(inp.Size.getSizeH() - 6);
	inp.Position.setPosition(10, UIGL::Jora::WndH - inp.Size.getSizeH() - 10);
	inp.Title = Text_en_ru[(int)UIGL::Jora::Language][3];
	inp.SetMin(5);
	inp.SetMax(99);
	inp.Text_max_length = 2;
	inp.Color = Parameters.ButtonsColor;
	inp.Outline_color = Parameters.LinesColor;
	inp.Text_color = Parameters.TextsColor;

	//sett_col
	sett_col[0].Color = Parameters.BackgroundColor;
	sett_col[1].Color = Parameters.TextsColor;
	sett_col[2].Color = Parameters.LinesColor;
	sett_col[3].Color = Parameters.ButtonsColor;
	sett_col[4].Color = Parameters.SelectedColor;
	sett_col[5].Color = Parameters.ButtonsColor;
	sett_col[6].Color = Parameters.ButtonsColor;

	for (int i = 0; i < sett_col_size; i++)
	{
		sett_col[i].Size.setSize(30, 30);
		sett_col[i].Position.setPosition(UIGL::Vector2f(10, UIGL::Jora::WndH - 40 * (i + 2)));
		sett_col[i].Set_text_size(24);
		sett_col[i].Name = "setcol" + std::to_string(i);
		sett_col[i].Text_color = Parameters.TextsColor;
		sett_col[i].Text = Text_en_ru[(int)UIGL::Jora::Language][i + 4];
		sett_col[i].Outline_color = Parameters.LinesColor;
		sett_col[i].IsHover = false;
	}
	sett_col[5].IsHover = true;
	sett_col[5].Size.setSize(50, 30);

}
