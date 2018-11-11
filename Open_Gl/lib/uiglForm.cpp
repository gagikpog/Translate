#include <iostream>

#include "uiglForm.h"
#include "uiglFunc.h"
//#include "EasyOpengl.h"
#include "UI/uiglMessageBox.h"
#include "uiglMainForm.h"


namespace UIGL {
	
	std::vector<UiglForms*> UiglForms::Forms;
	UiglForms::UiglForms()
	{
		Forms.push_back(this);
		UiglMainForm::AddForm();
	}
	UiglForms::UiglForms(bool add_in_main_forms)
	{
		if (add_in_main_forms)
		{
			Forms.push_back(this);
			UiglMainForm::AddForm();
		}
	}
	void UiglForms::MouseWheelFunc_g(int button, int state, int ax, int ay)
	{
		if (1 != Enabled)
			return;
		UiglEvent msg;
		if (Wnd_proc == NULL) {
			std::cout << "Function Win_proc not found\n";
			return;
		}
		if (Focus.size())
		{
			msg = Focus[Focus.size() - 1]->MouseWheelFunc(button, state, ax, ay);
			if (msg.Event == UIGL::uiglEvents::uiglEraseMsg)
				Focus.pop_back();
			if (msg.Name != "")
				Wnd_proc(msg.Event, msg.Name);
		}
		else {
			int i = 0;
			for (std::list<UiglIForms*>::iterator it = Stec.begin(); it != Stec.end(); it++, i++)
			{
				msg = (*it)->MouseWheelFunc(button, state, ax, ay);
				if (msg.Event == UIGL::uiglEvents::uiglEraseMsg) {
					Stec.erase(it);
					if (i <= in_focus)
						in_focus--;
				}
				if (msg.Name != "")
				{
					Wnd_proc(msg.Event, msg.Name);
					break;
				}
			}
		}
	}
	void UiglForms::PassiveMotionFunc_g(int ax, int ay)
	{
		if (1 != Enabled)
			return;
		UiglEvent msg;
		if (Wnd_proc == NULL)
		{
			std::cout << "Function Win_proc not found\n";
			return;
		}
		if (Focus.size())
		{
			msg = Focus[Focus.size() - 1]->PassiveMotionFunc(ax, ay);
			if (msg.Event == UIGL::uiglEvents::uiglEraseMsg)
				Focus.pop_back();
			if (msg.Name != "") {
				Wnd_proc(msg.Event, msg.Name);
			}
		}
		else {
			int i = 0;
			for (std::list<UiglIForms*>::iterator it = Stec.begin(); it != Stec.end(); i++)
			{
				msg = (*it)->PassiveMotionFunc(ax, ay);
				if (msg.Event == UIGL::uiglEvents::uiglEraseMsg)
				{
					Stec.erase(it);
					it = Stec.begin();
					std::advance(it, i);
					if (i <= in_focus)
						in_focus--;
				}
				else it++;
				if (msg.Name != "")
					Wnd_proc(msg.Event, msg.Name);
			}
		}
	}
	void UiglForms::MotionFunc_g(int ax, int ay)
	{
		if (1 != Enabled)
			return;
		UiglEvent msg;
		if (Wnd_proc == NULL)
		{
			std::cout << "Function Win_proc not found\n";
			return;
		}
		if (Focus.size())
		{
			msg = Focus[Focus.size() - 1]->MotionFunc(ax, ay);
			if (msg.Event == UIGL::uiglEvents::uiglEraseMsg)
				Focus.pop_back();
			if (msg.Name != "")
				Wnd_proc(msg.Event, msg.Name);
		}
		else {
			int i = 0;
			for (std::list<UiglIForms*>::iterator it = Stec.begin(); it != Stec.end(); it++, i++)
			{
				msg = (*it)->MotionFunc(ax, ay);
				if (msg.Event == UIGL::uiglEvents::uiglEraseMsg)
				{
					Stec.erase(it);
					if (i <= in_focus)
						in_focus--;
				}
				if (msg.Name != "")
				{
					Wnd_proc(msg.Event, msg.Name);
					break;
				}
			}
		}
	}
	void UiglForms::MouseFunc_g(int button, int state, int ax, int ay)
	{
		if (1 != Enabled)
			return;
		UiglEvent msg;
		if (Wnd_proc == NULL)
		{
			std::cout << "Function Win_proc not found\n";
			return;
		}
		if (Focus.size())
		{
			msg = Focus[Focus.size() - 1]->MouseFunc(button, state, ax, ay);
			if (msg.Event == UIGL::uiglEvents::uiglEraseMsg)
				Focus.pop_back();
			if (msg.Name != "")
				Wnd_proc(msg.Event, msg.Name);
		}
		else {
			int i = 0;
			for (std::list<UiglIForms*>::iterator it = Stec.begin(); it != Stec.end(); it++, i++)
			{
				msg = (*it)->MouseFunc(button, state, ax, ay);
				if (msg.Event == UIGL::uiglEvents::uiglEraseMsg)
				{
					Stec.erase(it);
					if (i <= in_focus)
						in_focus--;
				}
				if (msg.Name != "")
				{
					Wnd_proc(msg.Event, msg.Name);
					in_focus = 0;
					if (it != Stec.begin())
					{
						Stec.push_front(*it);
						Stec.erase(it);
					}
					break;
				}
			}
		}
		Set_Focus();
	}
	void UiglForms::KeyboardFunc_g(unsigned char key, int ax, int ay)
	{
		if (1 != Enabled)
			return;
		UiglEvent msg;
		if (Wnd_proc == NULL)
		{
			std::cout << "Function Win_proc not found\n";
			return;
		}
		if (Focus.size())
		{
			msg = Focus[Focus.size() - 1]->KeyboardFunc(key, ax, ay);
			if (msg.Event == UIGL::uiglEvents::uiglEraseMsg)
				Focus.pop_back();
			if (msg.Name != "")
			{
				Wnd_proc(msg.Event, msg.Name);
			}
		}
		else {
			if (key == 9 && !Shift_press)
			{
				if (in_focus < Stec.size() - 1)
					in_focus++;
				else in_focus = 0;
				Set_Focus();
			}
			if (Shift_press && key == 9)
			{
				if (in_focus > 0)
					in_focus--;
				else in_focus = Stec.size() - 1;
				Set_Focus();
			}
			std::list<UiglIForms*>::iterator it = Stec.begin();
			std::advance(it, in_focus);
			msg = (*it)->KeyboardFunc(key, ax, ay);
			if (msg.Event == UIGL::uiglEvents::uiglEraseMsg)
			{
				Stec.erase(it);
				in_focus--;
			}
			if (msg.Name != "")
				Wnd_proc(msg.Event, msg.Name);

		}
	}
	void UiglForms::SpecialFunc_g(int key, int ax, int ay)
	{
		if (1 != Enabled)
			return;
		UiglEvent msg;
		if (Wnd_proc == NULL)
		{
			std::cout << "Function Win_proc not found\n";
			return;
		}
		if (key == 112)
			Shift_press = 1;
		if (Focus.size())
		{
			msg = Focus[Focus.size() - 1]->SpecialFunc(key, ax, ay);
			if (msg.Event == UIGL::uiglEvents::uiglEraseMsg)
				Focus.pop_back();
			if (msg.Name != "")
			{
				Wnd_proc(msg.Event, msg.Name);
			}
		}
		else {
			std::list<UiglIForms*>::iterator it = Stec.begin();
			std::advance(it, in_focus);
			msg = (*it)->SpecialFunc(key, ax, ay);
			if (msg.Event == UIGL::uiglEvents::uiglEraseMsg)
			{
				Stec.erase(it);
				in_focus--;
			}
			if (msg.Name != "")
				Wnd_proc(msg.Event, msg.Name);
		}
	}
	void UiglForms::KeyboardUpFunc_g(unsigned char key, int ax, int ay)
	{
		if (1 != Enabled)
			return;
		UiglEvent msg;
		if (Wnd_proc == NULL) {
			std::cout << "Function Win_proc not found\n";
			return;
		}
		if (Focus.size())
		{
			msg = Focus[Focus.size() - 1]->KeyboardUpFunc(key, ax, ay);
			if (msg.Event == UIGL::uiglEvents::uiglEraseMsg)
				Focus.pop_back();
			if (msg.Name != "")
			{
				Wnd_proc(msg.Event, msg.Name);
			}
		}
		else {
			std::list<UiglIForms*>::iterator it = Stec.begin();
			std::advance(it, in_focus);
			msg = (*it)->KeyboardUpFunc(key, ax, ay);
			if (msg.Event == UIGL::uiglEvents::uiglEraseMsg)
			{
				Stec.erase(it);
				in_focus--;
			}
			if (msg.Name != "")
				Wnd_proc(msg.Event, msg.Name);
		}
	}
	void UiglForms::SpecialUpFunc_g(int key, int ax, int ay)
	{
		if (key == 112)
			Shift_press = 0;
		if (1 != Enabled)
			return;
		UiglEvent msg;
		if (Wnd_proc == NULL)
		{
			std::cout << "Function Win_proc not found\n";
			return;
		}
		if (Focus.size())
		{
			msg = Focus[Focus.size() - 1]->SpecialUpFunc(key, ax, ay);
			if (msg.Event == UIGL::uiglEvents::uiglEraseMsg)
				Focus.pop_back();
			if (msg.Name != "")
				Wnd_proc(msg.Event, msg.Name);
		}
		else {
			std::list<UiglIForms*>::iterator it = Stec.begin();
			std::advance(it, in_focus);
			msg = (*it)->SpecialUpFunc(key, ax, ay);
			if (msg.Event == UIGL::uiglEvents::uiglEraseMsg)
			{
				Stec.erase(it);
				in_focus--;
			}
			if (msg.Name != "")
				Wnd_proc(msg.Event, msg.Name);
		}
	}
	void UiglForms::Init_g(bool focus_only, bool clear_background)
	{
		if (Enabled == 0)
			return;
		if (clear_background)
			drawRectangle(UiglMainForm::WndMinX, UiglMainForm::WndMinY, UiglMainForm::WndW, UiglMainForm::WndH, Background_color, Background_color);

		if (!Focus.size() || !focus_only)
			for (std::list<UiglIForms*>::reverse_iterator it = Stec.rbegin(); it != Stec.rend(); ++it)
				(*it)->Init();

		for (int i = 0; i < Focus.size(); i++)
			Focus[i]->Init();
	}
	void UiglForms::Focus_push_back(UiglIForms * func)
	{
		func->SetHDC(_hdc);
		Focus.push_back(func);
	}
	void UiglForms::Focus_pop_back()
	{
		Focus.pop_back();
	}
	void UiglForms::Focus_erase(int num)
	{
		if (num < Focus.size())
			Focus.erase(Focus.begin() + num);
	}
	void UiglForms::Stec_erase(int num)
	{
		if (num < Stec.size())
		{
			std::list<UiglIForms*>::iterator it = Stec.begin();
			std::advance(it, num);
			Stec.erase(it);
		}
		if (in_focus < num)
		{
			in_focus--;
		}
	}
	void UiglForms::Stec_push_back(UiglIForms * func)
	{
		func->SetHDC(_hdc);
		Stec.push_back(func);
	}
	void UiglForms::Stec_pop_back()
	{
		Stec.pop_back();
		if (in_focus == Stec.size() - 1)
			in_focus--;
	}
	void UiglForms::SetHDC(HDC * _hdc_)
	{
		_hdc = _hdc_;
		for (std::list<UiglIForms*>::iterator it = Stec.begin(); it != Stec.end(); it++)
			(*it)->SetHDC(_hdc);
		for (int i = 0; i < Focus.size(); i++)
			Focus[i]->SetHDC(_hdc);
	}
	void UiglForms::Set_Focus()
	{
		for (std::list<UiglIForms*>::iterator it = Stec.begin(); it != Stec.end(); it++)
			(*it)->in_focus = 0;
		if (!Stec.empty())
		{
			std::list<UiglIForms*>::iterator it = Stec.begin();
			std::advance(it, in_focus);
			(*it)->in_focus = 1;
		}
	}
}