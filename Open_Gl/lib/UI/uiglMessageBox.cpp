#include "uiglMessageBox.h"
#include "../uiglMainForm.h"
#include "../uiglFunc.h"

namespace UIGL {

	UiglMessageBox::UiglMessageBox()
	{
		Position.UpdatePtr = this;
		Size.UpdatePtr = this;
		Size.setSize(350.0f, 150.0f);
		panel.IsHover = false;
		panel.is_move = true;
		panel.Color = Panel_color;
		panel.Set_text_size(22);
		B_ok.Set_text_size(22);
		B_no.Set_text_size(22);
		B_cancel.Set_text_size(22);
		textprint.setFontSize(22);
		textprint.setFont("Consolas");
		exit.Color = Red;
		panel.Size.setSize(W - Win_fon_H, Win_fon_H);
		exit.Size.setSize(Win_fon_H, Win_fon_H);
		B_ok.Size.setSize(90, Win_fon_H);
		B_no.Size.setSize(90, Win_fon_H);
		B_cancel.Size.setSize(90, Win_fon_H);
		B_ok.Color = B_no.Color = B_cancel.Color = Button_color;
		B_ok.Name = "ok";
		B_no.Name = "no";
		B_cancel.Name = "cancel";
		Name = "msgbox";
	}
	UiglEvent UiglMessageBox::MouseFunc(int button, int state, int ax, int ay)
	{
		UiglEvent result;
		if (!Visible)
			return result;
		if (ax > X && ax < X + W && ay > Y && ay < Y + H)
		{
			if (exit.MouseFunc(button, state, ax, ay).Event == uiglMouseLeftDown)
			{
				Visible = 0;
				result.Event = uiglMsgCancel;
				result.Name = Name;
			}
			panel.MouseFunc(button, state, ax, ay);

			result = B_ok.MouseFunc(button, state, ax, ay);
			if (result.Event == uiglMouseLeftDown && result.Name == "ok")
			{
				Visible = 0;
				result.Name = Name;
				result.Event = uiglMsgYes;
				return result;
			}
			result = B_no.MouseFunc(button, state, ax, ay);
			if (result.Event == uiglMouseLeftDown && result.Name == "no")
			{
				Visible = 0;
				result.Name = Name;
				result.Event = uiglMsgNo;
				return result;
			}
			result = B_cancel.MouseFunc(button, state, ax, ay);
			if (result.Event == uiglMouseLeftDown && result.Name == "cancel")
			{
				Visible = 0;
				result.Name = Name;
				result.Event = uiglMsgCancel;
				return result;
			}
		}
		else {
			if (l == 0) {
				l = 2;
				lp = 1;
				MessageBeep(1);
			}
		}
		return result;
	}
	UiglEvent UiglMessageBox::PassiveMotionFunc(int ax, int ay)
	{
		UiglEvent result;
		if (!Visible)
			return result;
		panel.PassiveMotionFunc(ax, ay);
		exit.PassiveMotionFunc(ax, ay);
		B_ok.PassiveMotionFunc(ax, ay);
		B_no.PassiveMotionFunc(ax, ay);
		B_cancel.PassiveMotionFunc(ax, ay);
		return result;
	}
	UiglEvent UiglMessageBox::MotionFunc(float ax, float ay)
	{
		UiglEvent result;
		if (!Visible)
			return result;

		panel.MotionFunc(ax, ay);
		Vector2f t = panel.Position.getPosition2f();

		if (t.X < 0) t.X = 0;
		if (t.X + W > UiglMainForm::WndW)t.X = UiglMainForm::WndW - W;
		if (t.Y - H + Win_fon_H < 0) t.Y = H - Win_fon_H;
		if (t.Y + Win_fon_H > UiglMainForm::WndH)t.Y = UiglMainForm::WndH - Win_fon_H;

		//		X = panel.Position.getPositionX();
		//		this->Position.setPosition(t);

		panel.Position.setPosition(t);
		t.Y -= H - Win_fon_H;
		this->Position.setPosition(t);
		exit.Position.setPosition(X + W - Win_fon_H, Y + H - Win_fon_H);
		B_no.Position.setPosition(X + 20, Y + 10);
		B_ok.Position.setPosition(X + 130, Y + 10);
		B_cancel.Position.setPosition(X + 240, Y + 10);
		return result;
	}
	UiglEvent UiglMessageBox::MouseWheelFunc(int button, int state, int ax, int ay)
	{
		UiglEvent result;
		if (!Visible)
			return result;
		panel.MouseWheelFunc(button, state, ax, ay);
		return result;
	}
	UiglEvent UiglMessageBox::KeyboardFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;
		if (!Visible)
			return result;
		if (key == 27)
		{
			Visible = false;
			result.Event = uiglMsgCancel;
			result.Name = Name;
		}
		return result;
	}
	UiglEvent UiglMessageBox::SpecialFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		if (!Visible)
			return result;
		return result;
	}
	UiglEvent UiglMessageBox::KeyboardUpFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;
		if (!Visible)
			return result;
		return result;
	}
	UiglEvent UiglMessageBox::SpecialUpFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		if (!Visible)
			return result;
		return result;
	}
	void UiglMessageBox::Init()
	{
		if (!Visible)
			return;
		if (l != 0) { if (lp)  l += 2; else l -= 2; }
		if (l > 6) lp = 0;
		drawRectangle(X - l, Y - l, W + 2 * l, H + 2 * l, UiglColor(0, 255, 0, 100), UiglColor(0, 255, 0, 100));
		drawRectangle(X, Y, W, H, Color, Outline_color);
		panel.Init();
		exit.Init();
		B_ok.Init();
		B_no.Init();
		B_cancel.Init();
		for (int i = 0; i < Base_Text.size(); i++)
		{
			textprint.glText(X + 10, Y + H - 23 * (i + 2) - 3, Base_Text[i]);
		}


		glLineWidth(3);
		glBegin(GL_LINES);
		glVertex2f(X + W - 7, Y + H - 7);
		glVertex2f(X + W - Win_fon_H + 7, Y + H - Win_fon_H + 7);
		glVertex2f(X + W - 7, Y + H - Win_fon_H + 7);
		glVertex2f(X + W - Win_fon_H + 7, Y + H - 7);
		glEnd();
		glLineWidth(1);
	}
	void UiglMessageBox::Show(std::string text, std::string title, uiglMsgBoxButtons _buttons)
	{
		Base_Text.clear();
		if (textprint.getTextLength(text) < Size.getSizeW())
		{
			Base_Text.push_back(text);
		}
		else {
			for (int i = text.size(); i > 0; i--)
			{
				if (text[i] == ' ')
				{
					if (textprint.getTextLength(text.substr(0, i)) < Size.getSizeW() - textprint.getTextLength("a"))
					{
						Base_Text.push_back(text.substr(0, i));
						text = text.substr(i + 1);
						i = text.size();
					}
				}
				else if (i == 1)Base_Text.push_back(text);
			}
		}
		if (Base_Text.size()>3)
			Size.setSize(350.0f, 150.0f + Base_Text.size() * 20);
		else Size.setSize(350.0f, 150.0f);

		X = (UiglMainForm::WndW - W) / 2;
		Y = (UiglMainForm::WndH - H) / 2;
		Visible = 1;
		panel.Text = title;
		Text = text;
		panel.Position.setPosition(X, Y + H - Win_fon_H);
		exit.Position.setPosition(X + W - Win_fon_H, Y + H - Win_fon_H);
		B_no.Position.setPosition(X + 20, Y + 10);
		B_ok.Position.setPosition(X + 130, Y + 10);
		B_cancel.Position.setPosition(X + 240, Y + 10);

		B_no.Text = Text_en_ru[Language][0];
		B_ok.Text = Text_en_ru[Language][1];
		B_cancel.Text = Text_en_ru[Language][2];
		switch (_buttons)
		{
		case UIGL::uiglButtonOK:			B_no.Visible = 0;	B_ok.Visible = 1;	B_cancel.Visible = 0;	break;
		case UIGL::uiglButtonNO:			B_no.Visible = 1;	B_ok.Visible = 0;	B_cancel.Visible = 0;	break;
		case UIGL::uiglButtonCancel:		B_no.Visible = 0;	B_ok.Visible = 0;	B_cancel.Visible = 1;	break;
		case UIGL::uiglButtonOKNO:			B_no.Visible = 1;	B_ok.Visible = 1;	B_cancel.Visible = 0;	break;
		case UIGL::uiglButtonOKCancel:		B_no.Visible = 0;	B_ok.Visible = 1;	B_cancel.Visible = 1;	break;
		case UIGL::uiglButtonNoCancel:		B_no.Visible = 1;	B_ok.Visible = 0;	B_cancel.Visible = 1;	break;
		case UIGL::uiglButtonOKNOCancel:	B_no.Visible = 1;	B_ok.Visible = 1;	B_cancel.Visible = 1;	break;
		}
	}
	void UiglMessageBox::SetHDC(HDC * _hdc)
	{
		hdc = _hdc;
		panel.SetHDC(_hdc);
		B_no.SetHDC(_hdc);
		B_ok.SetHDC(_hdc);
		B_cancel.SetHDC(_hdc);
		textprint.setHDC(_hdc);
	}
}