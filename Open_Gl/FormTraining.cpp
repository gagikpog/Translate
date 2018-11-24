#include "FormTraining.h"

FormTrainingNew::FormTrainingNew()
{
	initializer();
}

FormTrainingNew::~FormTrainingNew()
{
}

void FormTrainingNew::ReshapeFunc_g(int aw, int ah)
{
	update();
}

void FormTrainingNew::Proc(UIGL::uiglEvents ev, std::string name)
{
	std::cout << "Training Form new  " << ev << "  " << name << std::endl;

	if (name == "next" && ev == UIGL::uiglEvents::uiglMouseLeftUp)
	{
		cut_data(My_sub_data, My_data, word_count);
		ans_wrong = ans_correct = 0;
		resetlist();
		return;
	}
	if (name == "enter" && ev == UIGL::uiglEvents::uiglMouseLeftUp || ((name == "list1" || name == "list2") && (ev == UIGL::uiglEvents::uiglDoubleClick || ev == UIGL::uiglEvents::uiglEnter)))
	{
		if (list1.Selected >= 0 && list1.Selected < My_sub_data.size())
		{
			if (translate(list1.Get_Selected_text()) == list2.Get_Selected_text())
			{
				My_sub_data[list1.Selected]->Count++;
				My_sub_data.erase(My_sub_data.begin() + list1.Selected);
				list1.Items.clear();
				list2.Items.clear();
				list1.Selected = 0;
				list2.Selected = 0;
				ans_correct++;
				for (int i = 0; i < My_sub_data.size(); i++)
				{
					list1.Items.push_back(My_sub_data[i]->Text);
					list2.Items.push_back(My_sub_data[i]->Text1);
				}
				std::sort(list2.Items.begin(), list2.Items.end());
			}
			else {
				ans_wrong++;
				My_sub_data[list1.Selected]->Count--;
			}
			butt3.Text = std::to_string(word_count) + "/ " + Text_en_ru[(int)UIGL::Jora::Language][11] + ":" + std::to_string(ans_correct) + " " +
				Text_en_ru[(int)UIGL::Jora::Language][12] + ":" + std::to_string(ans_wrong);
			saveFavouriteWords("selfnew.txt", My_data);
			//conf.Save("settings.conf");
		}
		return;
	}
}

void FormTrainingNew::update()

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

void FormTrainingNew::initializer()
{
	openFavouriteWords("selfnew.txt", My_data);
	cut_data(My_sub_data, My_data, word_count);
	resetlist();

	word_count = Parameters.TestWordsCount;

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

bool FormTrainingNew::cut_data(std::vector<UIGL::string_int*>& sub_mas, std::vector<UIGL::string_int>& mas, int sub_mas_size)
{
	sub_mas.clear();
	std::sort(mas.begin(), mas.end(), [](UIGL::string_int a, UIGL::string_int b) {return a.Count < b.Count; });
	int i(0), j(0);

	while (j < sub_mas_size && i < mas.size())
	{
		if (mas[i].Num == 0)
		{
			mas[i].Num = 1;
			sub_mas.push_back(&mas[i]);
			j++;
		}
		i++;
	}

	if (i >= mas.size() - 1)
		for (int k = 0; k < mas.size(); k++)
			mas[k].Num = 0;

	std::sort(list2.Items.begin(), list2.Items.end());
	return 1;
}

void FormTrainingNew::resetlist()
{
	list1.Items.clear();
	list2.Items.clear();
	list1.Selected = 0;
	list2.Selected = 0;
	for (int i = 0; i < My_sub_data.size(); i++)
	{
		list1.Items.push_back(My_sub_data[i]->Text);
		list2.Items.push_back(My_sub_data[i]->Text1);
	}
	std::sort(list2.Items.begin(), list2.Items.end());
}

std::string FormTrainingNew::translate(std::string text_en)
{
	for (int i = 0; i < My_sub_data.size(); i++)
	{
		if (My_sub_data[i]->Text == text_en)
			return My_sub_data[i]->Text1;
	}
	return "";
}
