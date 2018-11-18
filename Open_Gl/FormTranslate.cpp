#include "FormTranslate.h"

FormTranslateNew::FormTranslateNew()
{
	initializer();
}

FormTranslateNew::~FormTranslateNew()
{
}

void FormTranslateNew::ReshapeFunc_g(int aw, int ah)
{
	update();
}

void FormTranslateNew::Proc(UIGL::uiglEvents ev, std::string name)
{
	std::cout << "FormTranslate  " << ev << "  " << name << std::endl;
	if (ev == UIGL::uiglEvents::uiglEnter && name == "inp2")
	{
		translate();
		return;
	}
	if ((ev == UIGL::uiglEvents::uiglMouseLeftDown || ev == UIGL::uiglEvents::uiglEnter) && name == "swap1")
	{
		Translate_to = !Translate_to;
		inp2.Text = "";
		out2.Text = "";
		update();
		return;
	}
	if ((ev == UIGL::uiglEvents::uiglMouseLeftDown || ev == UIGL::uiglEvents::uiglEnter) && name == "favor")
	{
		favourite();
	}
	if ((ev == UIGL::uiglEvents::uiglMouseLeftDown || ev == UIGL::uiglEvents::uiglEnter) && name == "cutword")
	{
		this->Focus_push_back(&messageBox);
		messageBox.Show(MsgString[(int)UIGL::Jora::Language][4], MsgString[(int)UIGL::Jora::Language][0], UIGL::uiglButtonOKNO);
		messageBox.Name = "del";
	}
	if (ev == UIGL::uiglEvents::uiglMsgYes && name == "del")
	{
		for (int i = 0; i < My_data.size(); i++)
		{
			if (list_l.Get_Selected_text() == My_data[i].Text)
			{
				My_data.erase(My_data.begin() + i);
			}
		}
		list_updat();
		saveFavouriteWords("selfnew.txt", My_data);
	}
}

void FormTranslateNew::initializer()
{
	openFavouriteWords(dataFilename, My_data);
	list_updat();
	list_l.Name = "list_l";
	butt2.Name = "setting";
	inp.Name = "textbox";
	inp2.Name = "inp2";
	favor.Name = "favor";
	cutword.Name = "cutword";
	swap1.Name = "swap1";
	butt.Name = "enter";

	Stec_push_back(&list_l);
	Stec_push_back(&cutword);
	Stec_push_back(&butt2);
	Stec_push_back(&inp2);
	Stec_push_back(&out2);
	Stec_push_back(&swap1);
	Stec_push_back(&favor);

	swap1.Open("swap.ggp");

	update();
}

void FormTranslateNew::update()
{
	Background_color = Parameters.BackgroundColor;
	//list_l
	list_l.Size.setSize(UIGL::Jora::WndW, UIGL::Jora::WndH*0.8);
	list_l.Position.setPosition(0, 0);
	list_l.Set_text_size(25);

	list_l.Color = Parameters.ButtonsColor;
	list_l.Outline_color = Parameters.LinesColor;
	list_l.Select_color = Parameters.SelectedColor;
	list_l.Text_color = Parameters.TextsColor;

	//butt2
	butt2.Size.setSize(150, 30);
	butt2.Position.setPosition(UIGL::Jora::WndW - 160, UIGL::Jora::WndH - 40);
	butt2.Set_text_size(butt.Size.getSizeH() - 5);
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

	//butt
	butt.Size.setSize(150, 30);
	butt.Position.setPosition(10, UIGL::Jora::WndH - butt.Size.getSizeH() - 10);
	butt.Set_text_size(butt.Size.getSizeH() - 5);
	butt.Text = Text_en_ru[(int)UIGL::Jora::Language][0];
	butt.Color = Parameters.ButtonsColor;
	butt.Outline_color = Parameters.LinesColor;
	butt.Text_color = Parameters.TextsColor;

	//inp2
	inp2.Size.setSize(UIGL::Jora::WndW*0.5 - 35, 30);
	inp2.Set_text_size(inp.Size.getSizeH() - 6);
	inp2.Position.setPosition(10, UIGL::Jora::WndH - 80);
	inp2.Color = Parameters.ButtonsColor;
	inp2.Outline_color = Parameters.LinesColor;
	inp2.Text_color = Parameters.TextsColor;
	inp2.Text_align = UIGL::uiglBottomCenter;

	//favor
	favor.Size.setSize(300, 30);
	favor.Position.setPosition(10, UIGL::Jora::WndH - butt.Size.getSizeH() - 10);
	favor.Set_text_size(butt.Size.getSizeH() - 5);
	favor.Text = Head_en_ru[(int)UIGL::Jora::Language][6];
	favor.Color = Parameters.ButtonsColor;
	favor.Outline_color = Parameters.LinesColor;
	favor.Text_color = Parameters.TextsColor;

	//cutword
	cutword.Size.setSize(150, 30);
	cutword.Position.setPosition(UIGL::Jora::WndW - 160, UIGL::Jora::WndH*0.8 + 10);
	cutword.Set_text_size(butt.Size.getSizeH() - 5);
	cutword.Text = Head_en_ru[(int)UIGL::Jora::Language][7];
	cutword.Color = Parameters.ButtonsColor;
	cutword.Outline_color = Parameters.LinesColor;
	cutword.Text_color = Parameters.TextsColor;

	//out2
	out2.Size.setSize(UIGL::Jora::WndW*0.5f - 35, 30);
	out2.Position.setPosition(UIGL::Jora::WndW*0.5f + 25, UIGL::Jora::WndH - 80);
	out2.Name = "out2";
	out2.Set_text_size(butt.Size.getSizeH() - 5);
	out2.Color = Parameters.ButtonsColor;
	out2.Outline_color = Parameters.LinesColor;
	out2.Text_color = Parameters.TextsColor;
	out2.Text_align = UIGL::uiglBottomCenter;

	//swap1
	swap1.Size.setSize(40, 40);
	swap1.Position.setPosition(UIGL::Jora::WndW*0.5f - 20, UIGL::Jora::WndH - 85);
	//		swap1.Position.setPosition(Jora::WndW, Jora::WndH);		
	swap1.Color = Parameters.ButtonsColor;
	swap1.Outline_color = Parameters.LinesColor;

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

void FormTranslateNew::list_updat()
{
	list_l.Items.clear();
	list_l.Items1.clear();

	for (int i = 0; i < My_data.size(); i++)
	{
		list_l.Items.push_back(My_data[i].Text);
		list_l.Items1.push_back(My_data[i].Text1);
	}
	list_l.Selected = 0;
}

void FormTranslateNew::translate()
{

	if (inp2.Text != "")
	{
		if (Translate_to)
		{//ru to en
			if (!TranslateFromFile("ru.txt", inp2.Text, out2.Text))
			{
				UIGL::Jora::MsgBox.Show(MsgString[(int)UIGL::Jora::Language][3], MsgString[(int)UIGL::Jora::Language][0]);
				UIGL::Jora::MsgBox.Name = "msgbax";
			}
		}
		else
		{
			if (!TranslateFromFile("en.txt", inp2.Text, out2.Text))
			{
				UIGL::Jora::MsgBox.Show(MsgString[(int)UIGL::Jora::Language][3], MsgString[(int)UIGL::Jora::Language][0]);
				UIGL::Jora::MsgBox.Name = "msgbax";
			}
		}
	}

}

void FormTranslateNew::favourite()
{
	if (inp2.Text != "" && out2.Text != "")
	{
		if (!Add_word())
		{
			UIGL::Jora::MsgBox.Show(MsgString[(int)UIGL::Jora::Language][1], MsgString[(int)UIGL::Jora::Language][0]);
			UIGL::Jora::MsgBox.Name = "msgbax";
		}
	}
	else {
		UIGL::Jora::MsgBox.Show(MsgString[(int)UIGL::Jora::Language][2], MsgString[(int)UIGL::Jora::Language][0]);
		UIGL::Jora::MsgBox.Name = "msgbax";
	}
}

bool FormTranslateNew::Add_word()
{
	UIGL::string_int _temp;

	if (Translate_to)
	{
		if (std::find(list_l.Items1.begin(), list_l.Items1.end(), inp2.Text) == list_l.Items1.end())
		{
			_temp.Text1 = inp2.Text;
			_temp.Text = out2.Text;
		}
		else	return 0;
	}
	else {///en to ru
		if (std::find(list_l.Items.begin(), list_l.Items.end(), inp2.Text) == list_l.Items.end())
		{
			_temp.Text = inp2.Text;
			_temp.Text1 = out2.Text;
		}
		else return 0;
	}

	_temp.Count = 1000;
	My_data.push_back(_temp);
	inp2.Text = "";
	out2.Text = "";
	list_updat();
	saveFavouriteWords("selfnew.txt", My_data);

	return 1;
}