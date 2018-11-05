#include "uiglMainForm.h"
#include "UI/uiglMessageBox.h"
#include "UI/uiglColDialog.h"
#include "uiglForm.h"

namespace UIGL {
	///UiglMainForm 
	void(*UiglMainForm::WinProc_ptr)(uiglEvents, std::string);
	void(*UiglMainForm::KeyboardFunc_ptr)(unsigned char, int, int) = NULL;
	void(*UiglMainForm::SpecialFunc_ptr)(int, int, int) = NULL;
	void(*UiglMainForm::MouseFunc_ptr)(int, int, int, int) = NULL;
	void(*UiglMainForm::MotionFunc_ptr)(int, int) = NULL;
	void(*UiglMainForm::PassiveMotionFunc_ptr)(int, int) = NULL;
	void(*UiglMainForm::MouseWheelFunc_ptr)(int, int, int, int) = NULL;
	void(*UiglMainForm::KeyboardUpFunc_ptr)(unsigned char, int, int) = NULL;
	void(*UiglMainForm::SpecialUpFunc_ptr)(int, int, int) = NULL;
	void(*UiglMainForm::PositionFunc_ptr)(int, int) = NULL;
	void(*UiglMainForm::ReshapeFunc_ptr)(int, int) = NULL;

	int UiglMainForm::WndH = 800;
	int UiglMainForm::WndW = 600;
	int UiglMainForm::WndX = 0;
	int UiglMainForm::WndY = 0;
	int UiglMainForm::WndMinX = 0;
	int UiglMainForm::WndMinY = 0;
	HDC UiglMainForm::hDC = NULL;
	HWND UiglMainForm::hWnd = NULL;
	int UiglMainForm::argc = 0;
	uiglLanguages UiglMainForm::Language = uiglLanguageEN;
	//	UiglText UiglMainForm::_text_;
	std::vector<std::string> UiglMainForm::argv;
	std::string UiglMainForm::Name;
	UiglColDiàlog UiglMainForm::ColDial;
	UiglMessageBox UiglMainForm::MsgBox;
	///UiglMainForm end
	void UiglMainForm::GluiInit(int _argc_, char ** _argv_)
	{
		std::string prog_name, prog_name1;
		Name = "";
		prog_name = _argv_[0];
		for (int i = prog_name.length() - 1; i >= 0; i--)
			if (prog_name[i] != 92)
				prog_name1 += prog_name[i];
			else break;
			if (prog_name1.length() > 4)
				for (int i = prog_name1.length() - 1; i >= 4; i--)
					Name += prog_name1[i];
			else Name = "GLUI";

			glutInit(&_argc_, _argv_);
			glutInitWindowPosition(UiglMainForm::WndX, UiglMainForm::WndY);
			glutInitWindowSize(UiglMainForm::WndW, UiglMainForm::WndH);
			glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
			glutCreateWindow(Name.c_str());

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(WndMinX, WndW, WndMinY, WndH);

			for (int i = 0; i < _argc_; i++)
				argv.push_back((std::string)_argv_[i]);

			hWnd = FindWindowA(0, Name.c_str());
			hDC = GetDC(hWnd);

			glutKeyboardFunc(KeyboardFunc);
			glutSpecialFunc(SpecialFunc);
			glutMouseWheelFunc(MouseWheelFunc);
			glutPassiveMotionFunc(PassiveMotionFunc);
			glutMotionFunc(MotionFunc);
			glutMouseFunc(MouseFunc);
			glutKeyboardUpFunc(KeyboardUpFunc);
			glutSpecialUpFunc(SpecialUpFunc);
			glutReshapeFunc(ReshapeFunc);
			glutPositionFunc(PositionFunc);
			//			_text_.setHDC(&hDC);
			MsgBox.SetHDC(&hDC);
	}
	void UiglMainForm::Display(bool OnlyFocus, bool clear_background)
	{
		int i = 0;
		for (auto it : UiglForms::Forms)
		{
			if (it != nullptr)
				it->Init_g(OnlyFocus, clear_background);
			else UiglForms::Forms.erase(UiglForms::Forms.begin() + i);
			i++;
		}
		if (MsgBox.Visible)MsgBox.Init();
	}
	void UiglMainForm::AddForm()
	{
		int i = 0;
		for (auto it : UiglForms::Forms)
		{
			if (it != nullptr)
			{
				it->SetHDC(&hDC);
				if (it->Wnd_proc == nullptr && WinProc_ptr != nullptr)
					it->Wnd_proc = WinProc_ptr;
			}
			else UiglForms::Forms.erase(UiglForms::Forms.begin() + i);
			i++;
		}
	}
	void UiglMainForm::KeyboardFunc(unsigned char key, int ax, int ay)
	{
		if (!MsgBox.Visible) {
			int i = 0;
			for (auto it : UiglForms::Forms)
			{
				if (it != nullptr)
					it->KeyboardFunc_g(key, ax, WndH - ay);
				else UiglForms::Forms.erase(UiglForms::Forms.begin() + i);
				i++;
			}
			if (KeyboardFunc_ptr != nullptr)
				KeyboardFunc_ptr(key, ax, WndH - ay);
		}
		else {
			UiglEvent ev;
			ev = MsgBox.KeyboardFunc(key, ax, WndH - ay);
			if (ev.Event != uiglEvents::uiglEventEmpty && ev.Name != "" && WinProc_ptr != nullptr)
				WinProc_ptr(ev.Event, ev.Name);
		}
	}
	void UiglMainForm::SpecialFunc(int key, int ax, int ay)
	{
		if (key == GLUT_KEY_F1)
		{
			if (Language == uiglLanguageRU)
				MsgBox.Show("Ãàãèê Ïîãîñÿí", "Àâòîð");
			else MsgBox.Show("Gagik Pogosyan", "Author");
			MsgBox.Name = "Author";
		}

		if (!MsgBox.Visible) {
			int i = 0;
			for (auto it : UiglForms::Forms)
			{
				if (it != nullptr)
					it->SpecialFunc_g(key, ax, WndH - ay);
				else UiglForms::Forms.erase(UiglForms::Forms.begin() + i);
				i++;
			}
			if (SpecialFunc_ptr != nullptr)
				SpecialFunc_ptr(key, ax, WndH - ay);
		}
		else {
			UiglEvent ev;
			ev = MsgBox.SpecialFunc(key, ax, WndH - ay);
			if (ev.Event != uiglEvents::uiglEventEmpty && ev.Name != "" && WinProc_ptr != nullptr)
				WinProc_ptr(ev.Event, ev.Name);
		}
		//	ColDial.SpecialFunc(key, ax, WndH - ay);
	}
	void UiglMainForm::MouseFunc(int button, int state, int ax, int ay)
	{
		if (!MsgBox.Visible) {
			int i = 0;
			for (auto it : UiglForms::Forms)
			{
				if (it != nullptr)
					it->MouseFunc_g(button, state, ax, WndH - ay);
				else UiglForms::Forms.erase(UiglForms::Forms.begin() + i);
				i++;
			}
			if (MouseFunc_ptr != nullptr)
				MouseFunc_ptr(button, state, ax, WndH - ay);
		}
		else {
			UiglEvent ev;
			ev = MsgBox.MouseFunc(button, state, ax, WndH - ay);
			if (ev.Event != uiglEvents::uiglEventEmpty && ev.Name != "" && WinProc_ptr != nullptr)
				WinProc_ptr(ev.Event, ev.Name);
		}
		//	ColDial.MouseFunc(button,state, ax, WndH - ay);
	}
	void UiglMainForm::MotionFunc(int ax, int ay)
	{
		if (!MsgBox.Visible) {
			int i = 0;
			for (auto it : UiglForms::Forms)
			{
				if (it != nullptr)
					it->MotionFunc_g(ax, WndH - ay);
				else UiglForms::Forms.erase(UiglForms::Forms.begin() + i);
				i++;
			}
			if (MotionFunc_ptr != nullptr)
				MotionFunc_ptr(ax, WndH - ay);
		}
		else {
			UiglEvent ev;
			ev = MsgBox.MotionFunc(ax, WndH - ay);
			if (ev.Event != uiglEvents::uiglEventEmpty && ev.Name != "" && WinProc_ptr != nullptr)
				WinProc_ptr(ev.Event, ev.Name);
		}
		//	ColDial.MotionFunc(ax, WndH - ay);
	}
	void UiglMainForm::PassiveMotionFunc(int ax, int ay)
	{
		if (!MsgBox.Visible) {
			int i = 0;
			for (auto it : UiglForms::Forms)
			{
				if (it != nullptr)
					it->PassiveMotionFunc_g(ax, WndH - ay);
				else UiglForms::Forms.erase(UiglForms::Forms.begin() + i);
				i++;
			}
			if (PassiveMotionFunc_ptr != nullptr)
				PassiveMotionFunc_ptr(ax, WndH - ay);
		}
		else {
			UiglEvent ev;
			ev = MsgBox.PassiveMotionFunc(ax, WndH - ay);
			if (ev.Event != uiglEvents::uiglEventEmpty && ev.Name != "" && WinProc_ptr != nullptr)
				WinProc_ptr(ev.Event, ev.Name);
		}
		//	ColDial.PassiveMotionFunc(ax, WndH - ay);
	}
	void UiglMainForm::MouseWheelFunc(int button, int state, int ax, int ay)
	{
		if (!MsgBox.Visible) {
			int i = 0;
			for (auto it : UiglForms::Forms)
			{
				if (it != nullptr)
					it->MouseWheelFunc_g(button, state, ax, WndH - ay);
				else UiglForms::Forms.erase(UiglForms::Forms.begin() + i);
				i++;
			}
			if (MouseWheelFunc_ptr != nullptr)
				MouseWheelFunc_ptr(button, state, ax, WndH - ay);
		}
		else {
			UiglEvent ev;
			ev = MsgBox.MouseWheelFunc(button, state, ax, WndH - ay);
			if (ev.Event != uiglEvents::uiglEventEmpty && ev.Name != "" && WinProc_ptr != nullptr)
				WinProc_ptr(ev.Event, ev.Name);
		}
		//	ColDial.MouseWheelFunc(button, state, ax, WndH - ay);
	}
	void UiglMainForm::KeyboardUpFunc(unsigned char key, int ax, int ay)
	{
		if (!MsgBox.Visible) {
			int i = 0;
			for (auto it : UiglForms::Forms)
			{
				if (it != nullptr)
					it->KeyboardUpFunc_g(key, ax, WndH - ay);
				else UiglForms::Forms.erase(UiglForms::Forms.begin() + i);
				i++;
			}
			if (KeyboardUpFunc_ptr != nullptr)
				KeyboardUpFunc_ptr(key, ax, WndH - ay);
		}
		else {
			UiglEvent ev;
			ev = MsgBox.KeyboardUpFunc(key, ax, WndH - ay);
			if (ev.Event != uiglEvents::uiglEventEmpty && ev.Name != "" && WinProc_ptr != nullptr)
				WinProc_ptr(ev.Event, ev.Name);
		}
		//	ColDial.KeyboardUpFunc(key, ax, WndH - ay);
	}
	void UiglMainForm::SpecialUpFunc(int key, int ax, int ay)
	{
		if (!MsgBox.Visible) {
			int i = 0;
			for (auto it : UiglForms::Forms)
			{
				if (it != nullptr)
					it->SpecialUpFunc_g(key, ax, WndH - ay);
				else UiglForms::Forms.erase(UiglForms::Forms.begin() + i);
				i++;
			}
			if (SpecialUpFunc_ptr != nullptr)
				SpecialUpFunc_ptr(key, ax, WndH - ay);
		}
		else {
			UiglEvent ev;
			ev = MsgBox.SpecialFunc(key, ax, WndH - ay);
			if (ev.Event != uiglEvents::uiglEventEmpty && ev.Name != "" && WinProc_ptr != nullptr)
				WinProc_ptr(ev.Event, ev.Name);
		}
		//	ColDial.SpecialFunc(key, ax, WndH - ay);
	}
	void UiglMainForm::PositionFunc(int ax, int ay)
	{
		WndX = ax;
		WndY = ay;
		if (PositionFunc_ptr != nullptr)
			PositionFunc_ptr(ax, ay);
	}
	void UiglMainForm::ReshapeFunc(int aw, int ah)
	{
		int i = 0;
		for (auto it : UiglForms::Forms)
		{
			if (it != nullptr)
				it->ReshapeFunc_g(aw, ah);
			else UiglForms::Forms.erase(UiglForms::Forms.begin() + i);
			i++;
		}

		WndH = ah;
		WndW = aw;
		if (ReshapeFunc_ptr != nullptr)
			ReshapeFunc_ptr(aw, ah);
	}
}