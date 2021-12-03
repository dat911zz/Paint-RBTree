#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_
//Struct and Constant
struct Dictionary
{
	char word[100];
	char mean[100];
};
//Functions
bool operator > (Dictionary a, Dictionary b)
{
	return strcmp(a.word,b.word) == 1;
}
bool operator < (Dictionary a, Dictionary b)
{
	return strcmp(a.word, b.word) == -1;
}
bool operator == (Dictionary a, Dictionary b)
{
	return strcmp(a.word, b.word) == 0;
}

#endif // !_DICTIONARY_H_