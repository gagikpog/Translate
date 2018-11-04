#ifndef SENTENCE_H
#define SENTENCE_H

#include <algorithm>

#include "../lib/freeuigl.h"

struct Sentence
{
	Sentence() {}
	void SetText(std::string _text);
	bool AddText(std::string _txt);
	std::string GetText();
	int GetSize();
	void Clear();
	bool Test(std::string _txt);
	int Rating = 1000;
	std::string Text = "";
	std::vector<std::vector<char>> arr{};
	bool use = 0;
};

#endif // !SENTENCE_H