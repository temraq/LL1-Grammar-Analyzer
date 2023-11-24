//---------------------------------------------------------------------------
#include <iostream>
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
  Form1->Memo1->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	AnsiString ansi_str = Memo1->Text; //помещает наш код из мемо в строку
	char* s = ansi_str.c_str();     //преобразует в строку типа С
	int n = 0;   //номер символа
	table_el x[NUM_ROWS];  //таблица элементов
	table_el el;
	int size = len(s);
	for(int i = 0; i < size;){
		int add = 0;
		el = parse_el(s, i, size, add);
		if(el.type != 18){
			x[n++] = el;
		}
		i += add;
	}

	size = n;
	if (programIsValid(x,size)) Form2->Edit1->Text = "Анализ прошел успешно.";
	else Form2->Edit1->Text = "Произошла ошибка.";


	Form2->Show();

}
//---------------------------------------------------------------------------
 /*
d=13+1;
a=3+254/d;
c=200/d+367/a;
if(d>=c) a=d/2; else a=a/3;
h=1;
for i=(1,d) h=h+1; a=a+h; end_for
*/

