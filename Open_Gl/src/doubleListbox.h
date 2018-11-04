#ifndef DOUBLELISTBOX_H
#define DOUBLELISTBOX_H
#include "../lib/freeuigl.h"

class doubleListbox :public UIGL::UiglListbox
{
public:
	doubleListbox() {}
	~doubleListbox() {}
	void Init();
	std::vector<std::string>Items1;
private:
};
#endif // !DOUBLELISTBOX_H