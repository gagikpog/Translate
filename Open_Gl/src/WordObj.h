#ifndef WORDOBJ_H
#define WORDOBJ_H

#include "../lib/freeuigl.h"

class WordObj :public UIGL::UiglIForms
{
public:
	WordObj();
	~WordObj() {}
	UIGL::UiglEvent MouseFunc(int button, int state, int ax, int ay);
	UIGL::UiglEvent PassiveMotionFunc(int ax, int ay);
	UIGL::UiglEvent MotionFunc(float ax, float ay);
	UIGL::UiglEvent MouseWheelFunc(int button, int state, int ax, int ay);
	UIGL::UiglEvent KeyboardFunc(unsigned char key, int ax, int ay);
	UIGL::UiglEvent SpecialFunc(int key, int ax, int ay);
	UIGL::UiglEvent KeyboardUpFunc(unsigned char key, int ax, int ay);
	UIGL::UiglEvent SpecialUpFunc(int key, int ax, int ay);
	void Init();
	void SetHDC(HDC* _hdc);
	void Set_text_size(float _size);
	void Update();
	void UpdateStec(bool m = 0);
	void Jamp();
	WordObj operator=(WordObj operator2);
	void Reset();
	UIGL::UiglColor Text_color;
	std::string Text;
	WordObj* Next = NULL;
	WordObj* Back = NULL;
	bool LineTranslation = 0;
private:
	UIGL::UiglRectangle contextmenu;
	void Init2();
	UIGL::UiglEvent MouseFunc2(int button, int state, int ax, int ay);
	UIGL::UiglEvent MotionFunc2(float ax, float ay);
	void Update2();
	int _moved = 0;
	bool hover2 = 0;
protected:
	float Text_size = 30;
	UIGL::UiglText textprint;
private:
};
#endif // !WORDOBJ_H