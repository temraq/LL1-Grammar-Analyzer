//---------------------------------------------------------------------------
#pragma once
#include "Parse.h"
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMemo *Memo;
	TStringGrid *TableL;
	TLabel *Label1;
	TLabel *Label2;
	TStringGrid *TableI;
	TButton *Button1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
void init_Table(TStringGrid* str_gr);
void clear_Table(TStringGrid* str_gr);
void refresh_StringGrids(TStringGrid* str_gr1, TStringGrid* str_gr2, table_el* x, int n);
