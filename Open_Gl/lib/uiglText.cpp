#include "uiglText.h"
#include "EasyOpenGL.h"

#pragma region UiglText

namespace UIGL {

	UiglText::UiglText()
	{
		size_text = 12;
		W = H = 0;
	}
	UiglText::~UiglText()
	{
		KillFont();
	}
	void UiglText::setFontSize(int _size)
	{
		//	KillFont();
		size_text = _size;
		H = 0;
		BildFont();

	}
	void UiglText::setHeightText(int _h)
	{
		H = _h;
		size_text = _h;
		BildFont();
	}
	void UiglText::setWidthText(int _w)
	{
		W = _w;
	}
	void UiglText::glText(float x, float y, const std::string txt, UiglColor col)
	{
		col.Init();
		if (H > 0)
			y += H*0.1f;

		glRasterPos2d(x, y);
		glPushAttrib(GL_LIST_BIT);
		glListBase(arial - 32);
#ifndef NDEBUG
		glCallLists((GLsizei)txt.length(), GL_UNSIGNED_BYTE, txt.c_str());
#else// NDEBUG
		std::wstring stemp = std::wstring(txt.begin(), txt.end());
		LPCWSTR sw = stemp.c_str();
		glCallLists((GLsizei)txt.length(), GL_SHORT, sw);
#endif// NDEBUG
		glPopAttrib();
	}
	float UiglText::getTextLength(std::string txt)
	{
		if ("Consolas" != Font)
			return 0;

		float _l = 0.55f;
		int _count(0);

		for (int i = 0; i < txt.size(); i++)
			if (txt[i] >= ' ' && txt[i] <= '~' || txt[i] >= 'À' && txt[i] <= 'ÿ')
				_count++;

		switch (size_text)
		{
		case	1: _l = 1.0f; break;
		case	2: _l = 0.5f; break;
		case	3: _l = 0.6666f; break;
		case	4: _l = 0.501001f; break;
		case	5: _l = 0.60099f; break;
		case	6: _l = 0.501001f; break;
		case	7: _l = 0.571f; break;
		case	8: _l = 0.5f; break;
		case	9: _l = 0.556f; break;
		case	10: _l = 0.501001f; break;
		case	11: _l = 0.547f; break;
		case	12: _l = 0.584f; break;
		case	13: _l = 0.539f; break;
		case	14: _l = 0.572f; break;
		case	15: _l = 0.533f; break;
		case	16: _l = 0.562f; break;
		case	17: _l = 0.529f; break;
		case	18: _l = 0.556f; break;
		case	19: _l = 0.526f; break;
		case	20: _l = 0.55f; break;
		case	21: _l = 0.571f; break;
		case	22: _l = 0.545f; break;
		case	23: _l = 0.565f; break;
		case	24: _l = 0.542f; break;
		case	25: _l = 0.56f; break;
		case	26: _l = 0.538f; break;
		case	27: _l = 0.555f; break;
		case	28: _l = 0.535f; break;
		case	29: _l = 0.551f; break;
		case	30: _l = 0.533f; break;
		case	31: _l = 0.548f; break;
		case	32: _l = 0.561f; break;
		case	33: _l = 0.545f; break;
		case	34: _l = 0.558f; break;
		case	35: _l = 0.542f; break;
		case	36: _l = 0.556f; break;
		case	37: _l = 0.541f; break;
		case	38: _l = 0.553f; break;
		case	39: _l = 0.539f; break;
		case	40: _l = 0.55f; break;
		case	41: _l = 0.561f; break;
		case	42: _l = 0.548f; break;
		case	43: _l = 0.558f; break;
		case	44: _l = 0.545f; break;
		case	45: _l = 0.556f; break;
		case	46: _l = 0.543f; break;
		case	47: _l = 0.553f; break;
		case	48: _l = 0.541f; break;
		case	49: _l = 0.551f; break;
		case	50: _l = 0.54f; break;
		case	51: _l = 0.548f; break;
		case	52: _l = 0.557f; break;
		case	53: _l = 0.547f; break;
		case	54: _l = 0.555f; break;
		case	55: _l = 0.545f; break;
		case	56: _l = 0.553f; break;
		case	57: _l = 0.543f; break;
		case	58: _l = 0.551f; break;
		case	59: _l = 0.542f; break;
		case	60: _l = 0.549f; break;
		case	61: _l = 0.557f; break;
		case	62: _l = 0.548f; break;
		case	63: _l = 0.555f; break;
		case	64: _l = 0.546f; break;
		case	65: _l = 0.553f; break;
		case	66: _l = 0.545f; break;
		case	67: _l = 0.551f; break;
		case	68: _l = 0.544f; break;
		case	69: _l = 0.55f; break;
		case	70: _l = 0.543f; break;
		case	71: _l = 0.549f; break;
		case	72: _l = 0.555f; break;
		case	73: _l = 0.547f; break;
		case	74: _l = 0.553f; break;
		case	75: _l = 0.546f; break;
		case	76: _l = 0.552f; break;
		case	77: _l = 0.545f; break;
		case	78: _l = 0.551f; break;
		case	79: _l = 0.544f; break;
		case	80: _l = 0.549f; break;
		case	81: _l = 0.554f; break;
		case	82: _l = 0.548f; break;
		case	83: _l = 0.553f; break;
		case	84: _l = 0.547f; break;
		case	85: _l = 0.551f; break;
		case	86: _l = 0.546f; break;
		case	87: _l = 0.551f; break;
		case	88: _l = 0.544f; break;
		case	89: _l = 0.55f; break;
		case	90: _l = 0.544f; break;
		case	91: _l = 0.548f; break;
		case	92: _l = 0.553f; break;
		case	93: _l = 0.547f; break;
		case	94: _l = 0.552f; break;
		case	95: _l = 0.547f; break;
		case	96: _l = 0.552f; break;
		case	97: _l = 0.546f; break;
		case	98: _l = 0.551f; break;
		case	99: _l = 0.545f; break;
		case	100: _l = 0.55f; break;
		case	101: _l = 0.554f; break;
		case	102: _l = 0.549f; break;
		case	103: _l = 0.553f; break;
		case	104: _l = 0.548f; break;
		case	105: _l = 0.552f; break;
		case	106: _l = 0.547f; break;
		case	107: _l = 0.551f; break;
		case	108: _l = 0.546f; break;
		case	109: _l = 0.55f; break;
		case	110: _l = 0.545f; break;
		case	111: _l = 0.549f; break;
		case	112: _l = 0.553f; break;
		case	113: _l = 0.548f; break;
		case	114: _l = 0.552f; break;
		case	115: _l = 0.547f; break;
		default:
			_l = 0.55f;
			break;
		}
		return _l*(float)(size_text*_count);
	}
	void UiglText::setHDC(HDC * _hdc)
	{
		hdc = _hdc;
		BildFont();
	}
	void UiglText::setFont(std::string font_name)
	{
		Font = font_name;
		//	KillFont();
		BildFont();
	}
	void UiglText::BildFont()
	{
		hdc = &Glui_MainForm::hDC;
		HFONT   oldfont;
		if (!hdc)
			return;
		KillFont();
		arial = glGenLists(255);
		font = CreateFontA(-size_text, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
			RUSSIAN_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
			ANTIALIASED_QUALITY, DEFAULT_QUALITY | DEFAULT_PITCH,
			Font.c_str());

		oldfont = (HFONT)SelectObject(*hdc, font);
		wglUseFontBitmaps(*hdc, 32, 224, arial);
		SelectObject(*hdc, oldfont);
		DeleteObject(font);

	}
	void UiglText::KillFont()
	{
		glDeleteLists(arial, 255);
	}

}
#pragma endregion