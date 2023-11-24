#include <iostream>
#include <cstring>
#include <stack>
#include "Project1PCH1.h"


using namespace std;

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

void Pop_Shift(const char*& LexemType, const char* GotLexType, stack<const char*>& PDA, bool& result, bool& keep) {
	if (LexemType == GotLexType) {
		PDA.pop();
	} else {
		result = false;
	}
	keep = false;
}

table_el parse_el(char* s, int st, int size, int &add){ //возвращает объект типа table_el
	 table_el x;
	 char nim1 = s[st-1];
	 char nim2 = s[st];
	 char nim = s[st+1];

	 if(s[st] != '\n' && s[st] != ' ' && s[st] != '\r'){
		if(isLetter(s[st])){
			bool fl = false;

			if(size - st > 2 && !fl){
				if(s[st] == 'i' && s[st + 1] == 'f' && s[st + 2] == '(' && !fl){
					x.el = "if";
					x.type = 1;
					fl = true;
					add += 2;
				}
			 }
			if(size - st > 3 && !fl) {
				if(s[st] == 'f' && s[st + 1] == 'o' && s[st + 2] == 'r'  && s[st + 3] == ' ' && !fl){
					x.el = "for";
					x.type = 2;
					fl = true;
					add += 3;
				}

			}

			if(size - st > 4  && !fl){
				if(s[st] == 'e' && s[st + 1] == 'l' && s[st + 2] == 's' && s[st + 3] == 'e' && s[st + 4] == ' ' && s[st+4]!= '_' && !fl){
					x.el = "else";
					x.type = 4;
					fl = true;
					add += 4;
				}
			}



			if(size - st > 6  && !fl){
				if(s[st] == 'e' && s[st + 1] == 'n' && s[st + 2] == 'd' && !fl && s[st+3] == '_' && s[st+4] == 'f' && s[st+5] == 'o' && s[st+6] == 'r' && (s[st + 7] == '\0' || s[st + 7] == '\r' || s[st + 7] == ' ' || s[st + 7] == '\n')){
					x.el = "end_for";
					x.type = 5;
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


bool programIsValid (table_el x[], int size){
			bool result = true;
			bool keep = false;
			bool bra_opened = false;
			bool inside_for = false;

			const char* LexemType;
			stack<const char*> PDA;     //стек из строк
			PDA.push("<.>");
			PDA.push("<program>");
			int i = -1;

			while (result && !PDA.empty() && i<size)
			{   if (i >= size) break;
				if (!keep)
				{
					i++;
					if (i >= size) break;
					char* Lexem = x[i].el;
					LexemType = TYPE[x[i].type-1];
					if (strcmp(LexemType,"UNKNOWN")==0)
					{
						result = false;
						continue;
					}
				}

				const char* k = PDA.top();

					if (strcmp(k,"<program>")==0){
						if (strcmp(LexemType,"ID")==0 || strcmp(LexemType,"L_IF")==0 || strcmp(LexemType,"L_FOR")==0)
                        {
							PDA.pop();
							PDA.push("<operators list>");
							PDA.push("<operator>");
						}
                        else result = false;
						keep = true;
						continue;
					}
					//a=a+1;     <program><.> <operator><operators list><.> <=><E><;><operators list><.>
					

					if (strcmp(k,"<operators list>")==0){
						if (strcmp(LexemType,"ID")==0 || strcmp(LexemType, "L_IF") ==0 || strcmp(LexemType,"L_FOR") ==0)
						{
                            PDA.pop();
                            PDA.push("<operators list>");
                            PDA.push("<operator>");
                        }
						else if (strcmp(LexemType,"L_ENDFOR") == 0 ||  strcmp(LexemType,"L_ELSE") ==0)
                        {
							PDA.pop();
                        }
						else result = false;
                        keep = true;
						continue;
					}


					if (strcmp(k,"<operator>")==0){
						if (strcmp(LexemType,"ID") ==0)
						{
                            PDA.pop();
							PDA.push("<;>");
                            PDA.push("<E>");
							PDA.push("<=>");
						   //	keep = true;
						   //	continue;
                        }


						else if (strcmp(LexemType,"L_IF")==0)
                        {
							PDA.pop();
							PDA.push("<else block>");
							PDA.push("<operator>");
							PDA.push("<)>");
							PDA.push("<logical expression>");
							PDA.push("<(>");
							//keep = true;
							//continue;
						}

						else if (strcmp(LexemType, "L_FOR")==0) {
							PDA.pop();
							PDA.push("<END_FOR>");
							PDA.push("<operators list>");
							PDA.push("<)>");
							PDA.push("<ID>");
							PDA.push("<,>");
							PDA.push("<INT>");
							PDA.push("<(>");
							PDA.push("<=>");
							PDA.push("<ID>");

							 }

						else result = false;
						keep = false;
						continue;
					}

					if (strcmp(k,"<else block>")==0){
						if (strcmp(LexemType, "L_ELSE")==0)
                        {
                            PDA.pop();
							PDA.push("<operator>");
							keep = false;
							continue;
                        }
						else if (strcmp(LexemType,"ID")==0 ||
						 strcmp(LexemType, "L_IF")==0 || strcmp(LexemType, "L_FOR")==0)
						{
							PDA.pop();
							keep = true;
							continue;
						}
						else {   
							PDA.pop();
							keep = true;
							continue;

						}
					   //	else result = false;
					   //	continue;
					}

					 if (strcmp(k,"<logical expression>")==0){
						if (strcmp(LexemType, "ID")==0 || strcmp(LexemType,"INT")==0)
						{
							PDA.pop();
							PDA.push("<F>");
							PDA.push("<logical operator>");
							PDA.push("<F>");
							keep = true;
						}
						else result = false;
						continue;
				   }



				   if (strcmp(k,"<logical operator>")==0){
						if (strcmp(LexemType,"L_LESS")==0) {
							PDA.pop();
							
							keep = false;
							continue;
							}
						else if (strcmp(LexemType,"L_MORE")==0)  {
							PDA.pop();
							i++;
							if (i >= size) break;
							keep = false;
							continue;
                        }
						else result = false;
						keep = false;
						continue;
				   }

				   if (strcmp(k, "<E>")==0){
						if (strcmp(LexemType, "ID")==0 || strcmp(LexemType, "INT")==0)
						{
                            PDA.pop();
							PDA.push("<E list>");
                            PDA.push("<T>");
						}
                        else result = false;
                        keep = true;
						continue;
				   }

					if (strcmp(k,"<E list>")==0){
						if (strcmp(LexemType,"L_POS")==0)
                        {
							PDA.pop();
                            PDA.push("<E list>");
							PDA.push("<T>");
							keep = false;
							continue;
						}
						else //if (strcmp(LexemType,"L_DC")==0 || (strcmp(LexemType,"L_CLS")==0 && bra_opened && inside_for))
						{
							PDA.pop();
							keep = true;
							continue;
						}
						//else result = false;
						//continue;
					}

					if (strcmp(k,"<T>")==0){
						if ((strcmp(LexemType, "ID") == 0) || (strcmp(LexemType, "INT")==0))
                        {
                            PDA.pop();
                            PDA.push("<T list>");
							PDA.push("<F>");

                        }
						else result = false;
						keep = true;
						continue;
					}

					if (strcmp(k,"<T list>")==0){
						if (strcmp(LexemType, "L_DIV")==0 )
                        {
                            PDA.pop();
							PDA.push("<T list>");
                            PDA.push("<F>");
							keep = false;
							continue;
						}
						else //if (strcmp(LexemType,"L_DC")== 0 || (strcmp(LexemType,"L_CLS")==0 && bra_opened && inside_for))
						{
							PDA.pop();
							keep = true;
							continue;
						}    
						//else {result = false;
						//continue;
					}

					if (strcmp(k, "<F>")==0){
						if (strcmp(LexemType, "ID") ==0 || strcmp(LexemType, "INT") == 0)
                        {
						   PDA.pop();
						   const char* smth = PDA.top();
						   i++;
						   if (i >= size) break;
						   char* Lexem = x[i].el;
						   LexemType = TYPE[x[i].type-1];
						   /*if (strcmp(LexemType,"L_DC")== 0 || (strcmp(LexemType,"L_CLS")==0 && bra_opened && inside_for)) {
								keep = true;
								continue;
						   }  */
						   keep = true;
						   //continue;
						  
						}
						else result = false;
						continue;
					}



					if (strcmp(k,"<=>")==0){
						Pop_Shift(ref (LexemType), "L_EQ", ref (PDA), ref (result), ref (keep));
						continue;
					}

					if (strcmp(k,"<;>")==0){
						Pop_Shift(ref (LexemType), "L_DC", ref (PDA), ref (result), ref (keep));
						continue;
					}


					if (strcmp(k,"<(>")==0){
						bra_opened = true;
						Pop_Shift(ref (LexemType), "L_OPS", ref (PDA), ref (result), ref (keep));
						continue;
					}

					if (strcmp(k, "<)>")==0){
						bra_opened = false;
						Pop_Shift(ref (LexemType), "L_CLS", ref (PDA), ref (result), ref (keep));
						continue;
					}

					if (strcmp(k,"<.>")==0){
						Pop_Shift(ref (LexemType), "L_END", ref (PDA), ref (result), ref (keep));
						continue;
					}

					if (strcmp(k,"<,>")==0){
						Pop_Shift(ref (LexemType), "L_COM", ref (PDA), ref (result), ref (keep));
						continue;
					}

					if (strcmp(k,"<ID>")==0){
						Pop_Shift(ref (LexemType), "ID", ref (PDA), ref (result), ref (keep));
						continue;
					}

					if (strcmp(k,"<INT>")==0){
						Pop_Shift(ref (LexemType), "INT", ref (PDA), ref (result), ref (keep));
						continue;
					}

					if (strcmp(k, "<END_FOR>")==0){
						Pop_Shift(ref (LexemType), "L_ENDFOR", ref (PDA), ref (result), ref (keep));
						continue;
					}

					if (i >= size) break;
					else {result = false;
					continue;}


			}
            return result;
}







