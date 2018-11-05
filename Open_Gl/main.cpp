#include "lib/freeuigl.h"

#include "src/Sentence.h"
#include "src/textbox.h"
#include "src/numbox.h"
#include "src/doubleListbox.h"
#include "src/WordObj.h"
#include "src/Panel.h"

#include "src/readFromFile.h"
#include "FormTranslate.h"

#include "resource.h"

using namespace std;
using namespace UIGL;

///////////////////////////////////////////////////structures and classes
struct Mytext
{
	string en;
	string ru;
};
//////////////////////////////////////////////////

FormTranslateNew formT2;

int word_count(20), ans_wrong(0), ans_correct(0), sentence_selection = 0;
int state_wnd(2);
bool Translate_to(0);

std::string  MakeSentencr();
void WordsPosUpdate(int n);
void BildWords(std::string text);
void Bild_Window();
void Wnd_init();
bool cut_data(vector<string_int*>& sub_mas, vector<string_int>& mas, int sub_mas_size);
string translate(string text_en);
void resetlist();
void list_updat();
bool Add_word();

const string Text_en_ru[2][13]{ 
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
const string Head_en_ru[2][8]{	"     Настрoйки",	"   Переводчик",	"    Тренировка",	"    В разработке" ,	"Английский",	"Русский","Добавить в избранные"," Удалить",
								"        Settings",	"       Translate",	"       Training",	"   In developing",	"English",		"Russian","Add to favorites"," Remove"};
const string Text_Form5[2][2]{	 "Перевод строки",""
								,"Line translation","" };
const string MsgString[2][8]{	"Справка",	"Это слово уже существует",	"Заполните поля"	,"Слово не найдено"	,"Вы действительно хотите удалить это слово?",	"","","",
								"Reference","This word already exists",	"Fill in the fields","Word not found"	,"Are you sure you want to delete this word?",	"","","" };

//menu setings
UiglColor text_col = Black;
UiglColor backgr_col = Green;
UiglColor line_col = Black;
UiglColor button_col = White;
UiglColor select_col = White;
UiglColor Alpha_anim(0,255,0,0);
///menu setings

vector<Sentence>ArrSentence;
vector<string_int> My_data;
vector<string_int*> My_sub_data;
vector<WordObj> words(30);

UiglForms FormTraining, FormSetting, FormMain, FormTranslate, Form5;
doubleListbox list_l;
UiglListbox list1,list2;
textbox inp2,out2;
UiglConfig conf("settings.conf");
numbox inp;
UiglPicture swap1;
Panel panel1;

UiglRectangle butt,butt1,butt2,butt3,favor,cutword,AddLineTranslation, TestTranslation;
UiglRectangle sett_col[7];
UiglRectangle Head_menu[5];

void Display()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);
	glClear(GL_COLOR_BUFFER_BIT);
	Jora::Display();
	drawRectangle(Jora::WndMinX, Jora::WndMinY, Jora::WndW, Jora::WndH, Alpha_anim, Alpha_anim);
	glutSwapBuffers();
}

void Reshop(int aw, int ah)
{
	glViewport(0, 0, aw, ah);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, Jora::WndW, 0, Jora::WndH);
	Bild_Window();
	glMatrixMode(GL_MODELVIEW);
}

void Pos_Func(int ax, int ay)
{
	conf.Set_count("WndX", ax);
	conf.Set_count("WndY", ay);
}

void timer(int)
{
	glutPostRedisplay();//обновляет экран
	glutTimerFunc(50, timer, 0);
}

void Animation1(int p)
{
	if (p <= 240 && p%2 == 0)
		p += 10;
	if (p >= 240) {
		p++;
		Bild_Window();
	}
	if (p > 0 && p %2 == 1)
		p -= 10;
	if (p > 0 && p < 255) {
		Alpha_anim = backgr_col;
		Alpha_anim.setAlpha(p);
	}
	glutPostRedisplay();
	if(p>0)
		glutTimerFunc(10, Animation1, p);
}

void Wnd_proc(uiglEvents ev,string name)
{
	cout << "Wnd_proc1  " << ev << "  " << name << endl;
	
	if (ev == uiglEvents::uiglMsgYes&&name == "del")
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


	if (name == "enter" && ev == uiglMouseLeftUp||((name=="list1"||name=="list2") && (ev == uiglDoubleClick || ev == uiglEnter)))
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
				sort(list2.Items.begin(), list2.Items.end());
			}else 
			{
				ans_wrong++;
				My_sub_data[list1.Selected]->Count--;
			}
			butt3.Text = to_string(word_count) + "/ "+ Text_en_ru[(int)Jora::Language][11] +":"+ to_string(ans_correct)+" "+
				Text_en_ru[(int)Jora::Language][12]+":"+ to_string(ans_wrong);
			saveFavouriteWords("selfnew.txt", My_data);
			conf.Save("settings.conf");

		}
	}
	if (name == "next" && ev == uiglMouseLeftUp)
	{
		cut_data(My_sub_data, My_data, word_count);
		ans_wrong = ans_correct = 0;
		resetlist();
	}

	if(name == "dialog"&&ev == uiglEraseMsg)
	{
		Bild_Window();
	}
	
	if ((ev == uiglMouseLeftDown || ev == uiglEnter) && name.substr(0, 6) == "setcol")
	{
		switch (name[6])
		{
		case '0':
			FormSetting.Focus_push_back(&Jora::ColDial);
			Jora::ColDial.Diolog(&backgr_col, Text_en_ru[(int)Jora::Language][4]);
			break;
		case '1':
			FormSetting.Focus_push_back(&Jora::ColDial);
			Jora::ColDial.Diolog(&text_col, Text_en_ru[(int)Jora::Language][5]);
			break;
		case '2':
			FormSetting.Focus_push_back(&Jora::ColDial);
			Jora::ColDial.Diolog(&line_col, Text_en_ru[(int)Jora::Language][6]);
			break;
		case '3':
			FormSetting.Focus_push_back(&Jora::ColDial);
			Jora::ColDial.Diolog(&button_col, Text_en_ru[(int)Jora::Language][7]);
			break;
		case '4':
			FormSetting.Focus_push_back(&Jora::ColDial);
			Jora::ColDial.Diolog(& select_col, Text_en_ru[(int)Jora::Language][8]);
			break;
		case '5':
			if (Jora::Language == uiglLanguageRU)
				Jora::Language = uiglLanguageEN;
			else Jora::Language = uiglLanguageRU;
			conf.Set_count("en", (int)Jora::Language);
			Bild_Window();
			break;
		default:
			break;
		}
	}

	if ((ev == uiglMouseLeftDown||ev == uiglEnter) && name == "setting")
	{
		if(inp.Text != "")
			word_count = stoi(inp.Text);
		else inp.Text = to_string(word_count);

		state_wnd = 2;
		Animation1(0);		 
	}
}
void Wnd_proc1(uiglEvents ev, string name)
{
	cout << "Wnd_proc1  "<< ev << "  " << name << endl;

	if ((ev == uiglMouseLeftDown || ev == uiglEnter) && name.substr(0,4)=="head")
	{
		switch (name[4])
		{
		case '0': {
			state_wnd = 1;
			inp.Text = to_string(word_count);
			Animation1(0);

		}break;
		case '1':{
			state_wnd = 3;
			Animation1(0);
			inp2.Text = "";
			out2.Text = "";
		}break;
		case '2': {
			cut_data(My_sub_data, My_data, word_count);
			resetlist();
			state_wnd = 0;
			Animation1(0);
			ans_wrong = 0;
			ans_correct = 0;

		}break;	
		case '3': {
			resetlist();
			state_wnd = 4;
			Animation1(0);
			if (sentence_selection < ArrSentence.size())
			{
				BildWords(ArrSentence[sentence_selection].GetText());
				sentence_selection++;
				if(sentence_selection == ArrSentence.size())
					sentence_selection = 0;
			}
		}break;
		case '4':
			state_wnd = 5;
			Animation1(0);
			break;
		}
	}

	if ((ev == uiglMouseLeftDown || ev == uiglEnter)&& name == "setting")
	{
		if (inp.Text != "")
			word_count = stoi(inp.Text);
		else inp.Text = to_string(word_count);

		state_wnd = 2;
		Animation1(0);
	}
	
	if ((ev == uiglMouseLeftDown || ev == uiglEnter) && name == "swap1")
	{
		if (Translate_to)
			Translate_to = 0;
		else Translate_to = 1;
		inp2.Text = "";
		out2.Text = "";
		Bild_Window();
	}

	if ((ev == uiglMouseLeftDown || ev == uiglEnter)&& name == "favor")
	{
		if (inp2.Text != "" && out2.Text != "")
		{
			if (!Add_word())
			{
				Jora::MsgBox.Show(MsgString[(int)Jora::Language][1], MsgString[(int)Jora::Language][0]);
				Jora::MsgBox.Name = "msgbax";
			}
		}
		else
		{
			Jora::MsgBox.Show(MsgString[(int)Jora::Language][2], MsgString[(int)Jora::Language][0]);
			Jora::MsgBox.Name = "msgbax";
		}
	}
	
	if ((ev == uiglMouseLeftDown || ev == uiglEnter) && name == "cutword")
	{
		Jora::MsgBox.Show(MsgString[(int)Jora::Language][4], MsgString[(int)Jora::Language][0],uiglButtonOKNO);
		Jora::MsgBox.Name = "del";
	}

	if (ev == uiglEnter && name == "inp2")
	{
		if (inp2.Text != "") 
		{
			if (Translate_to)
			{//ru to en
				if (!TranslateFromFile("ru.txt", inp2.Text, out2.Text))
				{
					Jora::MsgBox.Show(MsgString[(int)Jora::Language][3], MsgString[(int)Jora::Language][0]);
					Jora::MsgBox.Name = "msgbax";
				}
			}
			else
			{
				if (!TranslateFromFile("en.txt", inp2.Text, out2.Text))
				{
					Jora::MsgBox.Show(MsgString[(int)Jora::Language][3], MsgString[(int)Jora::Language][0]);
					Jora::MsgBox.Name = "msgbax";
				}
			}
		}
	}

	if((ev == uiglMouseLeftDown || ev == uiglEnter) && name == "setting")
	{
		if (inp.Text != "")
			word_count = stoi(inp.Text);
		else inp.Text = to_string(word_count);

		state_wnd = 2;
	}
}

void Wnd_proc_Form5(uiglEvents ev, string name) 
{
	cout << "Wnd_proc_Form5  "<< ev << "  " << name << endl;

	if (((ev == uiglMouseLeftDown) || (ev == uiglEnter)) && name == "setting")
	{
		state_wnd = 2;
		Animation1(0);
	}

	if ((ev == uiglMouseLeftUp) && name.substr(0,4) == "word")
	{		
		WordsPosUpdate(std::stoi(name.substr(4)));
	}
	if ((ev == uiglMouseLeftDown || ev == uiglEnter) && name == "Translation")
	{

		for (int i = 0; i < words.size(); i++)
		{
			if (words[i].Visible == 0)
			{
				words[i].Visible = 1;
				words[i].LineTranslation = 1;
				words[i].Position.setPosition(Jora::WndW *0.5f, Jora::WndH*0.4f);
				words[i].Size.setSize(Jora::WndW *0.5f, Jora::WndH*0.2f);
				break;
			}
		}
	}

	if ((ev == uiglMouseLeftDown || ev == uiglEnter) && name == "enter")
	{		
		std::string txt = MakeSentencr();
		if (txt == "loop")
		{
			Jora::MsgBox.Show("loop", "");
			return;
		}
		if (txt == "gap")
		{
			Jora::MsgBox.Show("gap", "");
			return;
		}
		int num = sentence_selection;
		num--;
		if (num < 0)
			num = ArrSentence.size() - 1;
		if (ArrSentence[num].Test(txt))
		{
			Jora::MsgBox.Show("Done", "");
			Wnd_proc_Form5(ev, "next");
			return;
		}else {
			Jora::MsgBox.Show("Wrong", "");
			return;
		}

	}

	if ((ev == uiglMouseLeftDown || ev == uiglEnter) && name == "next")
	{
		if (sentence_selection < ArrSentence.size())
		{
			BildWords(ArrSentence[sentence_selection].GetText());
			sentence_selection++;
			if (sentence_selection == ArrSentence.size())
				sentence_selection = 0;
			return;
		}
	}
}

int main(int argc, char**argv)
{
	//config
	{
	conf.Get_count("WndH", Jora::WndH);
	conf.Get_count("WndW", Jora::WndW);
	conf.Get_color("textcol", text_col);
	conf.Get_color("backgrcol", backgr_col);
	conf.Get_color("linecol", line_col);
	conf.Get_color("buttrcol", button_col);
	conf.Get_color("selectcol", select_col);
	conf.Get_count("word_count", word_count);
	conf.Get_count("WndX", Jora::WndX);
	conf.Get_count("WndY", Jora::WndY);
	int a0;	conf.Get_count("en", a0);	Jora::Language = (uiglLanguages)a0;

	conf.Add_item("word_count", word_count);
	conf.Add_item("en", (int)Jora::Language);
	conf.Add_item("WndH", Jora::WndH);
	conf.Add_item("WndW", Jora::WndW);
	conf.Add_item("textcol", 100);
	conf.Add_item("backgrcol", 100);
	conf.Add_item("linecol", 100);
	conf.Add_item("buttrcol", 100);
	conf.Add_item("selectcol", 100);
	conf.Add_item("WndX", Jora::WndX);
	conf.Add_item("WndY", Jora::WndY);
	}
	///config

	Jora::WinProc_ptr = Wnd_proc;
	Jora::GluiInit(argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_MODELVIEW);
#ifndef NDEBUG
	HANDLE icon = LoadImage(GetModuleHandle((Jora::Name + ".exe").c_str()), MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, LR_COLOR);
	SendMessage(Jora::hWnd, (UINT)WM_SETICON, ICON_BIG, (LPARAM)icon);
#else// NDEBUG
	string s = (Jora::Name + ".exe");
	std::wstring stemp = std::wstring(s.begin(), s.end());
	LPCWSTR sw = stemp.c_str();
	HANDLE icon = LoadImage(GetModuleHandle(sw), MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, LR_COLOR);
	SendMessage(Jora::hWnd, (UINT)WM_SETICON, ICON_BIG, (LPARAM)icon);
#endif

	Jora::PositionFunc_ptr = Pos_Func;
	Jora::ReshapeFunc_ptr = Reshop;

	//string T = __DATE__ ;T += "  ";	T += __TIME__;
	//glutSetWindowTitle(T.c_str());
	/*Sentence ss;
	ss.SetText("The letters are on the desk."); ArrSentence.push_back(ss);
	ss.SetText("You'll find the sugar cubes in the cupboard."); ArrSentence.push_back(ss);
	ss.SetText("The coffee table is beside the sofa."); ArrSentence.push_back(ss);
	ss.SetText("The supermarket is in front of their block of flats."); ArrSentence.push_back(ss);
	ss.SetText("The girl is sitting next to her mum."); ArrSentence.push_back(ss);
	ss.SetText("The puppy is inside the box."); ArrSentence.push_back(ss);
	ss.SetText("We have a small garden behind the house."); ArrSentence.push_back(ss);
	ss.SetText("Nastya and Gena study at a secondary school."); ArrSentence.push_back(ss);
	ss.SetText("Take the ball out of the pit."); ArrSentence.push_back(ss);
	ss.SetText("Let's go to the cinema!"); ArrSentence.push_back(ss);
	saveSentence(ArrSentence, "Sentense.tss");*/
	openSentence(ArrSentence, "Sentense.tss");

	glutTimerFunc(50, timer, 0);
	glutDisplayFunc(Display);
	Bild_Window();
	Wnd_init();
	glutMainLoop();
	return 0;
}

void Bild_Window()
{
	//config
	{
		conf.Set_count("word_count", word_count);
		conf.Set_count("WndH", Jora::WndH);
		conf.Set_count("WndW", Jora::WndW);
		conf.setColor("textcol", text_col);
		conf.setColor("backgrcol", backgr_col);
		conf.setColor("linecol", line_col);
		conf.setColor("buttrcol", button_col);
		conf.setColor("selectcol", select_col);
	}
	FormTraining.Background_color = backgr_col;
	FormSetting.Background_color = backgr_col;
	FormMain.Background_color = backgr_col;
	FormTranslate.Background_color = backgr_col;
	Form5.Background_color = backgr_col;
	//////////////////////////////////////////////////////FormTraining
	
	//list1
	{
		list1.Size.setSize(Jora::WndW / 2,Jora::WndH*0.8);	
		list1.Position.setPosition(0,0);
		list1.Name = "list1";
		list1.Set_text_size(25);
		list1.Color = button_col;
		list1.Outline_color = line_col;
		list1.Select_color = select_col; 
		list1.Text_color = text_col;
	}
	//list2
	{
		list2.Size.setSize(Jora::WndW / 2,Jora::WndH*0.8);
		list2.Position.setPosition(Jora::WndW / 2, 0);
		list2.Name = "list2";
		list2.Set_text_size(25);
		list2.Color = button_col;
		list2.Outline_color = line_col;
		list2.Select_color = select_col;
		list2.Text_color = text_col;
	}
	//butt
	{
		butt.Size.setSize(150,30);
		butt.Position.setPosition(10, Jora::WndH - butt.Size.getSizeH() - 10 );
		butt.Name = "enter";
		butt.Set_text_size(butt.Size.getSizeH() - 5);
		butt.Text = Text_en_ru[(int)Jora::Language][0];
		butt.Color = button_col;
		butt.Outline_color = line_col;
		butt.Text_color = text_col;
	}
	//butt1
	{
		butt1.Size.setSize(150, 30);
		butt1.Position.setPosition(10, Jora::WndH - butt.Size.getSizeH() - 50);
		butt1.Name = "next";
		butt1.Set_text_size(butt.Size.getSizeH() - 5);
		butt1.Text = Text_en_ru[(int)Jora::Language][1];
		butt1.Color = button_col;
		butt1.Outline_color = line_col;
		butt1.Text_color = text_col;
	}
	//butt2
	{
		butt2.Size.setSize(150, 30);
		butt2.Position.setPosition(Jora::WndW - 160, Jora::WndH - 40 );
		butt2.Name = "setting";
		butt2.Set_text_size(butt.Size.getSizeH() - 5);
		butt2.Text = Text_en_ru[(int)Jora::Language][2];
		butt2.Color = button_col;
		butt2.Outline_color = line_col;
		butt2.Text_color = text_col;
	}
	//butt3
	{
		butt3.Size.setSize(Jora::WndW, 30);
		butt3.Position.setPosition(0, Jora::WndH*0.8 );
		butt3.Name = "inf";
		butt3.IsHover = 0;
		butt3.Set_text_size(butt.Size.getSizeH() - 5);
		butt3.Text = to_string(word_count) + "/ " + Text_en_ru[(int)Jora::Language][11] + ":" + to_string(ans_correct) + " " +
			Text_en_ru[(int)Jora::Language][12] + ":" + to_string(ans_wrong);
		butt3.Color = button_col;
		butt3.Outline_color = line_col;
		butt3.Text_color = text_col;
	}
	
	//////////////////////////////////////////////////////FormSetting
	
	//inp
	{
		inp.NumbersOnly = 1;
		inp.Size.setSize(70, 30);
		inp.Set_text_size(inp.Size.getSizeH() - 6);
		inp.Name = "textbox";
		inp.Position.setPosition(10, Jora::WndH - inp.Size.getSizeH() - 10 );
		inp.Title = Text_en_ru[(int)Jora::Language][3];
		inp.SetMin(5);
		inp.SetMax(99);
		inp.Text_max_length = 2;
		inp.Color = button_col;
		inp.Outline_color = line_col;
		inp.Text_color = text_col;
	}
	//sett_col
	{
		sett_col[0].Color = backgr_col;
		sett_col[1].Color = text_col;
		sett_col[2].Color = line_col;
		sett_col[3].Color = button_col;
		sett_col[4].Color = select_col;
		sett_col[5].Color = button_col;
		sett_col[6].Color = button_col;


		for (int i = 0; i < 7; i++)
		{
			sett_col[i].Size.setSize(30, 30);
			sett_col[i].Position.setPosition(Vector2f(10, Jora::WndH - 40 * (i + 2)));
			sett_col[i].Set_text_size(24);
			sett_col[i].Name = "setcol" + to_string(i);
			sett_col[i].Text_color = text_col;
			sett_col[i].Text = Text_en_ru[(int)Jora::Language][i + 4];
			sett_col[i].Outline_color = line_col;
			sett_col[i].IsHover = false;
		}
		sett_col[5].IsHover = true;
		sett_col[5].Size.setSize(50, 30);
	}
	//////////////////////////////////////////////////////FormMain

	//Head_menu
	for (int i = 0; i < 5; i++)
	{
		Head_menu[i].Size.setSize(300, 100);
		Head_menu[i].Position.setPosition(Jora::WndW / 2 - 150, Jora::WndH / 2 - 160 + i * 110);
		Head_menu[i].Name = "head" + to_string(i);
		Head_menu[i].Set_text_size(35);
		Head_menu[i].Text = Head_en_ru[(int)Jora::Language][i];
		Head_menu[i].Color = button_col;
		Head_menu[i].Outline_color = line_col;
		Head_menu[i].Text_color = text_col;
		Head_menu[i].Text_align = uiglMiddleCenter;
	}
	//////////////////////////////////////////////////////FormTranslate

	//list_l
	{
		list_l.Size.setSize(Jora::WndW,Jora::WndH*0.8);
		list_l.Position.setPosition(0, 0);
		list_l.Name = "list_l";
		list_l.Set_text_size(25);
		list_l.Color = button_col;
		list_l.Outline_color = line_col;
		list_l.Select_color = select_col;
		list_l.Text_color = text_col;
	}
	//inp2
	{
		inp2.Size.setSize(Jora::WndW*0.5 - 35, 30);
		inp2.Set_text_size(inp.Size.getSizeH() - 6);
		inp2.Name = "inp2";
		inp2.Position.setPosition(10, Jora::WndH - 80 );
		inp2.Color = button_col;
		inp2.Outline_color = line_col;
		inp2.Text_color = text_col;
		inp2.Text_align = uiglBottomCenter;
	}
	//favor
	{
		favor.Size.setSize(300,30);
		favor.Position.setPosition(10, Jora::WndH - butt.Size.getSizeH() - 10 );
		favor.Name = "favor";
		favor.Set_text_size(butt.Size.getSizeH() - 5);
		favor.Text = Head_en_ru[(int)Jora::Language][6];
		favor.Color = button_col;
		favor.Outline_color = line_col;
		favor.Text_color = text_col;
	}
	//cutword
	{
		cutword.Size.setSize(150, 30);
		cutword.Position.setPosition(Jora::WndW - 160, Jora::WndH*0.8+10 );
		cutword.Name = "cutword";
		cutword.Set_text_size(butt.Size.getSizeH() - 5);
		cutword.Text = Head_en_ru[(int)Jora::Language][7];
		cutword.Color = button_col;
		cutword.Outline_color = line_col;
		cutword.Text_color = text_col;
	}
	//out2
	{
		out2.Size.setSize(Jora::WndW*0.5f-35, 30);
		out2.Position.setPosition(Jora::WndW*0.5f+25, Jora::WndH - 80);
		out2.Name = "out2";
		out2.Set_text_size(butt.Size.getSizeH() - 5);
		out2.Color = button_col;
		out2.Outline_color = line_col;
		out2.Text_color = text_col;
		out2.Text_align = uiglBottomCenter;
	}
	//swap1
	{
		swap1.Size.setSize(40, 40);
		swap1.Position.setPosition(Jora::WndW*0.5f - 20, Jora::WndH - 85);	
//		swap1.Position.setPosition(Jora::WndW, Jora::WndH);		
		swap1.Name = "swap1";
		swap1.Color = button_col;
		swap1.Outline_color = line_col;
	}
	if (!Translate_to) 
	{
		inp2.Title = Head_en_ru[(int)Jora::Language][4];
		out2.Title = Head_en_ru[(int)Jora::Language][5];
	}else {
		inp2.Title = Head_en_ru[(int)Jora::Language][5];
		out2.Title = Head_en_ru[(int)Jora::Language][4];
	}
	////////////////////////////////////////////////Form5
	for (int i = 0; i < words.size(); i++)
	{
		words[i].Color = button_col;
		words[i].Outline_color = line_col;
		words[i].Text_color = text_col;
	}
	panel1.Position.setPosition(Jora::WndMinX, Jora::WndMinY);
	panel1.Size.setSize(Jora::WndW, Jora::WndH*0.8f);
	panel1.Color = select_col;
	panel1.Outline_color = line_col;
	
	///AddLineTranslation
	{
		AddLineTranslation.Size.setSize(210, 30);
		AddLineTranslation.Position.setPosition(10, Jora::WndH*0.8 + 10 + butt3.Size.getSizeH());
		AddLineTranslation.Set_text_size(butt.Size.getSizeH() - 5);
		AddLineTranslation.Text = Text_Form5[(int)Jora::Language][0];
		AddLineTranslation.Color = button_col;
		AddLineTranslation.Outline_color = line_col;
		AddLineTranslation.Text_color = text_col;
		AddLineTranslation.Name = "Translation";
	}
	///TestTranslation
	/*{
		TestTranslation.Size.setSize(150, 30);
		TestTranslation.Position.setPosition(10, Jora::WndH - TestTranslation.Size.getSizeH()-10);
		TestTranslation.Set_text_size(butt.Size.getSizeH() - 5);
		TestTranslation.Text = Text_en_ru[(int)Jora::Language][0];
		TestTranslation.Color = button_col;
		TestTranslation.Outline_color = line_col;
		TestTranslation.Text_color = text_col;
		TestTranslation.Name = "test";
	}*/
	///////////////////////////////////////////////
	switch (state_wnd)
	{
	case 0:
		cout << "FormTraining\n";
		FormTraining.Enabled = 1;
		FormSetting.Enabled = 0;
		FormMain.Enabled = 0;
		FormTranslate.Enabled = 0;
		Form5.Enabled = 0;
		formT2.Enabled = 0;
		resetlist();
		break;
	case 1:
		cout << "FormSetting\n";
		FormTraining.Enabled = 0;
		FormSetting.Enabled = 1;
		FormMain.Enabled = 0;
		FormTranslate.Enabled = 0;
		Form5.Enabled = 0;
		formT2.Enabled = 0;
		break;
	case 2:
		cout << "FormMain\n";
		FormTraining.Enabled = 0;
		FormSetting.Enabled = 0;
		FormMain.Enabled = 1;
		FormTranslate.Enabled = 0;
		Form5.Enabled = 0;
		formT2.Enabled = 0;
		break;
	case 3:
		cout << "FormTranslate\n";
		FormTraining.Enabled = 0;
		FormSetting.Enabled = 0;
		FormMain.Enabled = 0;
		FormTranslate.Enabled = 1;
		Form5.Enabled = 0;
		formT2.Enabled = 0;
		break;
	case 4:
		cout << "Form5\n";
		FormTraining.Enabled = 0;
		FormSetting.Enabled = 0;
		FormMain.Enabled = 0;
		FormTranslate.Enabled = 0;
		Form5.Enabled = 1;
		formT2.Enabled = 0;
		break;	
	case 5:
		cout << "FormT2\n";
		FormTraining.Enabled = 0;
		FormSetting.Enabled = 0;
		FormMain.Enabled = 0;
		FormTranslate.Enabled = 0;
		Form5.Enabled = 0;
		formT2.Enabled = 1;
		break;
	}
	conf.Save();
}

void Wnd_init()
{
	FormTraining.Wnd_proc = Wnd_proc;
	FormSetting.Wnd_proc = Wnd_proc;
	FormMain.Wnd_proc = Wnd_proc1;
	FormTranslate.Wnd_proc = Wnd_proc1;
	Form5.Wnd_proc = Wnd_proc_Form5;

	//////////////////////////////////////////////FormTraining
	FormTraining.Stec_push_back(&list1);
	FormTraining.Stec_push_back(&list2);
	FormTraining.Stec_push_back(&butt);
	FormTraining.Stec_push_back(&butt1);
	FormTraining.Stec_push_back(&butt2);
	FormTraining.Stec_push_back(&butt3);

	//////////////////////////////////////////////FormSetting
	FormSetting.Stec_push_back(&inp);
	FormSetting.Stec_push_back(&butt2);
	for (int i = 0; i < 7; i++)
	{
		FormSetting.Stec_push_back(&sett_col[i]);
	}
	//////////////////////////////////////////////////FormMain
	FormMain.Stec_push_back(&Head_menu[0]);
	FormMain.Stec_push_back(&Head_menu[1]);
	FormMain.Stec_push_back(&Head_menu[2]);
	FormMain.Stec_push_back(&Head_menu[3]);
	FormMain.Stec_push_back(&Head_menu[4]);
	/////////////////////////////////////////////////FormTranslate
	FormTranslate.Stec_push_back(&butt2);
	FormTranslate.Stec_push_back(&list_l);
	FormTranslate.Stec_push_back(&inp2);
	FormTranslate.Stec_push_back(&out2);
	FormTranslate.Stec_push_back(&swap1);
	FormTranslate.Stec_push_back(&favor);
	FormTranslate.Stec_push_back(&cutword);
	swap1.Open("swap.ggp");
	/////////////////////////////////////////////////Form5
	Form5.Stec_push_back(&butt2);
	for (int i = 0; i < words.size(); i++)
	{
		Form5.Stec_push_back(&words[i]);
		words[i].Name = "word" + to_string(i);
	}
	Form5.Stec_push_back(&panel1);
	Form5.Stec_push_back(&AddLineTranslation);
//	Form5.Stec_push_back(&TestTranslation);
	Form5.Stec_push_back(&butt3);
	Form5.Stec_push_back(&butt);
	Form5.Stec_push_back(&butt1);

	////////////////////////////////////////////////
	srand(time(0));
	openFavouriteWords("selfnew.txt", My_data);
	list_updat();
	cut_data(My_sub_data, My_data, word_count);
}

bool Add_word()
{
	string_int _temp;

	if (Translate_to)
	{
		if (find(list_l.Items1.begin(), list_l.Items1.end(), inp2.Text) == list_l.Items1.end())
		{
			_temp.Text1 = inp2.Text;
			_temp.Text = out2.Text;
		}
		else	return 0;

	}
	else {///en to ru
		if (find(list_l.Items.begin(), list_l.Items.end(), inp2.Text) == list_l.Items.end())
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

void resetlist()
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
	sort(list2.Items.begin(), list2.Items.end());
}

void list_updat()
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

string translate(string text_en)
{
	for (int i = 0; i < My_sub_data.size(); i++)
	{
		if (My_sub_data[i]->Text == text_en)
			return My_sub_data[i]->Text1;
	}
	return "";
}

bool cut_data(vector<string_int*>& sub_mas ,vector<string_int>& mas,int sub_mas_size)
{
	sub_mas.clear();
	sort(mas.begin(), mas.end(), [](string_int a, string_int b) {return a.Count < b.Count; });
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

	if(i >= mas.size()-1)
		for (int k = 0; k < mas.size(); k++)
			mas[k].Num = 0;

	sort(list2.Items.begin(), list2.Items.end());
	return 1;
}

void BildWords(std::string text)
{
	int _begin = 0,w_count = 0;
	for (int i = 0; i < words.size(); i++)
		words[i].Reset();
	for (int i = 0; i < text.length(); i++)
	{
		if (text[i] == ' '||text.size() == i) 
		{
			words[w_count].Text = text.substr(_begin,i-_begin);
			_begin = i+1;
			words[w_count].Visible = true;
			w_count++;
		}
	}
	words[w_count].Text = text.substr(_begin);
	words[w_count].Visible = true;
	w_count++;

	for (int i = 0; i < w_count; i++)
		words[i].Position.setPosition(rand() % (int)(Jora::WndW*0.8f)-Jora::WndMinX,rand() % (int)(Jora::WndH*0.8f-50)-Jora::WndMinY);
}

void WordsPosUpdate(int n)
{
	Vector2f a, b, c;
	int l = 0;
	a = words[n].Position.getPosition2f();
	for (int i = 0; i < words.size(); i++)
	{	
		if (i == n || !words[i].Visible) continue;
		if (!words[i].LineTranslation)
		{
			b = words[i].Position.getPosition2f();
			b = b + Vector2f(words[i].Size.getSizeW(), 0);
			c = a - b;
			l = std::sqrtf(c.X*c.X + c.Y*c.Y);
			if (l < 35)
			{
				if (words[i].Next != nullptr)
				{
					words[i].Next->Jamp();
				}
				words[n].Back = &words[i];
				words[i].Next = &words[n];
				words[i].UpdateStec();
				break;
			}
		}else {
			b = Vector2f(words[i].Size.getSizeW() + words[n].Size.getSizeH(), words[i].Size.getSizeH());
			c = a - b;
			l = std::sqrtf(c.X*c.X + c.Y*c.Y);
			if (l < 35)
			{
				if (words[i].Next != nullptr)
					words[i].Next->Jamp();
				words[n].Back = &words[i];
				words[i].Next = &words[n];
				words[i].UpdateStec();
				break;
			}
		}
	}
}

std::string  MakeSentencr()
{
	WordObj * _W_Begin = NULL;
	for (int i = 0; i < words.size(); i++)
	{
		if (words[i].Visible /*&& !words[i].LineTranslation*/)
		{
			if (words[i].Back == nullptr)
			{
				if (_W_Begin == nullptr)
				{
					_W_Begin = &words[i];
				}else { 
				//	if(!_W_Begin->LineTranslation)
						return "gap"; 
				}
			}
		}
	}

	if (_W_Begin == nullptr)
		return "loop";

	std::string text;
	for (; _W_Begin != nullptr; _W_Begin = _W_Begin->Next)
	{
		text += _W_Begin->Text + " ";
	}
	return text;
}
