#include <iostream>
#include "Parse.h"

bool isLetter(char s){
	return (s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z');
}

bool isNumber(char s){
	return (s >= '0' && s <= '9');
}

bool isTerminal(char s){
	for(int i = 0; TERMINAL[i] != '\0'; ++i)
		 if (s == TERMINAL[i]) return true;
	return false;
}

int len(char* s){
	int size = 0;
	for(int i = 0; s[i] != '\0';++i)
		++size;
	return size;
}

table_el parse_el(char* s, int st, int size, int &add){
	 table_el x;
	 if(s[st] != '\n' && s[st] != ' ' && s[st] != '\r'){
		if(isLetter(s[st])){
			bool fl = false;
			
			if(size - st > 2 && !fl){
				if(s[st] == 'i' && s[st + 1] == 'f' && s[st + 2] == '(' && !fl){
					x.el = "if";
					x.type = 0;
					fl = true;
					add += 2;
				}
			 }
			if(size - st > 3 && !fl) {
				if(s[st] == 'f' && s[st + 1] == 'o' && s[st + 2] == 'r'  && s[st + 3] == ' ' && !fl){
					x.el = "for";
					x.type = 1;
					fl = true;
					add += 3;
				}

			}

			if(size - st > 4  && !fl){
				if(s[st] == 'e' && s[st + 1] == 'l' && s[st + 2] == 's' && s[st + 3] == 'e' && s[st + 4] == ' ' && s[st+4]!= '_' && !fl){
					x.el = "else";
					x.type = 3;
					fl = true;
					add += 4;
				}
			}

			if(size - st > 5  && !fl){
				if(s[st] == 'b' && s[st + 1] == 'e' && s[st + 2] == 'g' && s[st + 3] == 'i' && s[st + 4] == 'n' && s[st + 5] == ' ' && !fl){
					x.el = "begin";
					x.type = 5;
					fl = true;
					add += 5;
				}
			}

			if(size - st > 6  && !fl){
				if(s[st] == 'e' && s[st + 1] == 'n' && s[st + 2] == 'd' && !fl && s[st+3] == '_' && s[st+4] == 'f' && s[st+5] == 'o' && s[st+6] == 'r' && (s[st + 7] == '\0' || s[st + 7] == '\r' || s[st + 7] == ' ' || s[st + 7] == '\n')){
					x.el = "end_for";
					x.type = 2;
					fl = true;
					add += 7;
				}
			}

			if(!fl){//если не функц слова
				int cnt = 1;
				while(true){
					if(isLetter(s[st + cnt]) || isNumber(s[st + cnt]))
						++cnt;
					else{
						char* y = new char[cnt];
						for(int j = 0; j < cnt; ++j){
							y[j] = s[st + j];
						}
						x.el = y;
						x.type = 6;
						fl = true;
						add += cnt;
						break;
					}
				}
			}
		} else { //после букв "=+/><(),;"
			if(isTerminal(s[st])){
				if(s[st] == '='){
					char* y = new char[1];
					y[0] = s[st];
					x.el = y;
					x.type = 7;
				}
				if(s[st] == '+'){
					char* y = new char[1];
					y[0] = s[st];
					x.el = y;
					x.type = 8;
				}
				if(s[st] == '/'){
					char* y = new char[1];
					y[0] = s[st];
					x.el = y;
					x.type = 9;
				}
				if(s[st] == '>' && s[st+1] == '='){
					char* y = new char[2];
					
					y[0] = s[st];
					y[1] = s[st+1];
					x.el = y;
					x.type = 10;
				}
				if(s[st] == '<'){
					char* y = new char[1];
					y[0] = s[st];
					x.el = y;
					x.type = 11;
				}
				if(s[st] == '('){
					char* y = new char[1];
					y[0] = s[st];
					x.el = y;
					x.type = 12;
				}
				if(s[st] == ')'){
					char* y = new char[1];
					y[0] = s[st];
					x.el = y;
					x.type = 13;
				}
				if(s[st] == ','){
					char* y = new char[1];
					y[0] = s[st];
					x.el = y;
					x.type = 14;
				}
				if(s[st] == ';'){
					char* y = new char[1];
					y[0] = s[st];
					x.el = y;
					x.type = 15;
				}
				++add;
			} else{ //после букв и символов
				if(isNumber(s[st])){
					bool fla = true;
					int cnt = 1;
					while(true){
						if(isNumber(s[st + cnt]))
							++cnt;
						else{
							if(isLetter(s[st + cnt])){
								++cnt;
								fla = false;
							}
							else {
                                char* y = new char[cnt];
								for(int j = 0; j < cnt; ++j){
									y[j] = s[st + j];
								}
								x.el = y;
								if(fla){
									x.type = 16;
								}
								else {
									x.type = 17;
								}
								add += cnt;
								break;
							}
						}
					}
				}
				else {
					char* y = new char[1];
					y[0] = s[st];
					x.el = y;
					x.type = 17;
					++add;
				}
			}
		}
	 } else {
		++add;
		x.el = "";
		x.type = 18;
	 }
	 return x;
}  
