#ifndef UIGLMAINFORM_H
#define UIGLMAINFORM_H

#include <vector>

#include "uigl.h"

namespace UIGL {

	class UiglColDiàlog;
	class UiglMessageBox;

	class UiglMainForm
	{
	public:
		UiglMainForm() {}
		~UiglMainForm() {}
		static void GluiInit(int _argc_, char** _argv_);
		static void Display(bool focus_only = false, bool clear_background = true);
		static int WndH;
		static int WndW;
		static int WndX;
		static int WndY;
		static int WndMinX;
		static int WndMinY;
		static int argc;
		static uiglLanguages Language;
		static std::vector<std::string>argv;
		static std::string Name;
		static HDC hDC;
		static HWND hWnd;
		static UiglColDiàlog ColDial;
		static UiglMessageBox MsgBox;
		static void(*WinProc)(uiglEvents, std::string);
		static void(*KeyboardFunc_ptr)(unsigned char, int, int);
		static void(*SpecialFunc_ptr)(int, int, int);
		static void(*MouseFunc_ptr)(int, int, int, int);
		static void(*MotionFunc_ptr)(int, int);
		static void(*PassiveMotionFunc_ptr)(int, int);
		static void(*MouseWheelFunc_ptr)(int, int, int, int);
		static void(*KeyboardUpFunc_ptr)(unsigned char, int, int);
		static void(*SpecialUpFunc_ptr)(int, int, int);
		static void(*PositionFunc_ptr)(int, int);
		static void(*ReshapeFunc_ptr)(int, int);
		friend class UiglForms;
	private:
		static void AddForm();
		static void KeyboardFunc(unsigned char key, int ax, int ay);
		static void SpecialFunc(int key, int ax, int ay);
		static void MouseFunc(int button, int state, int ax, int ay);
		static void MotionFunc(int ax, int ay);
		static void PassiveMotionFunc(int ax, int ay);
		static void MouseWheelFunc(int button, int state, int ax, int ay);
		static void KeyboardUpFunc(unsigned char key, int ax, int ay);
		static void SpecialUpFunc(int key, int ax, int ay);
		static void PositionFunc(int ax, int ay);
		static void ReshapeFunc(int aw, int ah);
		//static UiglText _text_;
	};

	typedef UiglMainForm Jora;
}
#endif // !UIGLMAINFORM_H