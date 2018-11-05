#ifndef READFROMFILE_H
#define READFROMFILE_H
#include <string>
#include <vector>
#include "../lib/freeuigl.h"
#include "Sentence.h"

bool TranslateFromFile(std::string file_name, std::string Text_en, std::string &Text_ru);

bool openFavouriteWords(std::string file_name, std::vector<UIGL::string_int>& mas);
bool saveFavouriteWords(std::string file_name, std::vector<UIGL::string_int>& mas);


bool saveSentence(const std::vector<Sentence>& _sentence, std::string file_name);
bool openSentence(std::vector<Sentence>& _sentence, std::string file_name);

#endif // !READFROMFILE_H