//---------------------------------------------------------------------------
 #include <iostream>
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void init_Table(TStringGrid* str_gr){
	str_gr->RowCount = NUM_ROWS;
	str_gr->Cells[0][0] = "Name";
	str_gr->Cells[1][0] = "Class";
	return;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	init_Table(TableL);
	init_Table(TableI);
	Memo->Clear();
}
//---------------------------------------------------------------------------
void clear_Table(TStringGrid* str_gr){
	for(int i = 1; i < NUM_ROWS; ++i){
		str_gr->Cells[0][i] = "";
		str_gr->Cells[1][i] = "";
	}
	return;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	AnsiString ansi_str = Memo->Text;
	char* s = ansi_str.c_str();
	int n = 0;
	table_el x[NUM_ROWS];
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
	refresh_StringGrids(TableL, TableI, x, n);
}
//---------------------------------------------------------------------------
void refresh_StringGrids(TStringGrid* str_gr1, TStringGrid* str_gr2, table_el* x, int n){
	clear_Table(str_gr1);
	clear_Table(str_gr2);
	int cnt = 0;
	table_el id[NUM_ROWS];
	for(int i = 0; i < n; ++i){
		str_gr1->Cells[0][i + 1] = x[i].el;
		str_gr1->Cells[1][i + 1] = TYPE[x[i].type];
		if(x[i].type == 16 || x[i].type == 6){
			bool fl = true;
			for(int j = 0; j < cnt; ++j){
			   if(!strcmp(id[j].el, x[i].el))
					fl = false;
			}
			if(fl)
				id[cnt++] = x[i];
		}
	}
	for(int i = 0; i < cnt; ++i){
		str_gr2->Cells[0][i + 1] = id[i].el;
		str_gr2->Cells[1][i + 1] = TYPE[id[i].type];
	}
	return;
}
/*
d=23-1;
a=3-254%d;
c=200%d-367%a;
if(d>c) a=d%2; else a=d%3; endif
h=10;
do i=1,d begin h=h-1; end
*/

/*
d=13+1;
a=3+254/d;
c=200/d+367/a;
if(d>c) a=d/2; else a=a/3;
h=1;
for i=1,d begin h=h+1; a=a+h; end_for
*/
