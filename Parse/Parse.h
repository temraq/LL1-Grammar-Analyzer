#pragma once
#include <fstream>

const int NUM_ROWS = 100;
const char* TERMINAL = "=+/><(),;";
const char* TYPE[] = {"L_IF", "L_FOR", "L_END", "L_ELSE", "L_ENDFOR", "L_BEGIN", "ID",
					"L_EQ", "L_POS", "L_DIV", "L_MORE", "L_LESS", "L_OPS", "L_CLS",
					"L_COM", "L_DC", "INT", "UNKNOWN"};

struct table_el{
	char* el;
	int type;
};

table_el parse_el(char* s, int st, int size, int &add);
int len(char* s);
bool isLetter(char s);
bool isNumber(char s);
bool isTerminal(char s);

