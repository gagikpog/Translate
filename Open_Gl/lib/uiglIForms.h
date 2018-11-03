#ifndef UIGLIFORMS_H
#define UIGLIFORMS_H

#include "uiglObj.h"
#include "uiglColor.h"
#include "uigl.h"

namespace UIGL {
	class UiglIForms :virtual public UiglObj
	{
	public:
		UiglIForms() {}
		~UiglIForms() {}
		//имя объекта //передается в функцию Wnd_proc
		std::string Name = "no_naem";
		//цвет заливки
		UiglColor Color = White;
		//цвет контура
		UiglColor Outline_color = UiglColor(70, 70, 70, 255);
		bool IsHover = 1;
		bool Visible = 1;
		//если истина, то разрешает перетаскивание объекта мышью
		bool is_move = 0;
		virtual UiglEvent MouseFunc(int button, int state, int ax, int ay) = 0;
		virtual UiglEvent PassiveMotionFunc(int ax, int ay) = 0;
		virtual UiglEvent MotionFunc(float ax, float ay) = 0;
		virtual UiglEvent MouseWheelFunc(int button, int state, int ax, int ay) = 0;
		virtual UiglEvent KeyboardFunc(unsigned char key, int ax, int ay) = 0;
		virtual UiglEvent SpecialFunc(int key, int ax, int ay) = 0;
		virtual UiglEvent KeyboardUpFunc(unsigned char key, int ax, int ay) = 0;
		virtual UiglEvent SpecialUpFunc(int key, int ax, int ay) = 0;
		virtual UiglEvent PositionFunc(int aw, int ah) { return UiglEvent(); }
		virtual UiglEvent ReshapeFunc(int ax, int ay) { return UiglEvent(); }
		//выполняет отрисовку объекта
		virtual void Init() = 0;
		//устанавливает дескриптор контекста устройства
		virtual void SetHDC(HDC* _hdc) { hdc = _hdc; }

		friend class UiglForms;
		friend class UiglColDiаlog;
	protected:
		//находится ли объект в фокусе
		bool in_focus = false;
		bool Mouse_in_button = 0, moved = 0;
		//время предыдущего нажатия мыши в clock -ах
		unsigned int double_ckick = 0;
		//разница между координатом мышы и координатом объекта во время перетаскивания объекта
		float  mx = 0, my = 0;
		//дескриптор окна
		HDC* hdc;
	};
}
#endif // !UIGLIFORMS_H