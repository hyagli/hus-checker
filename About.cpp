//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <math.h>
#include <math.hpp>

#include "About.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Timer1Timer(TObject *Sender)
{
	if(Label1->Left < -(Label1->Width+10))
		Label1->Left = Width+10;
	else
		Label1->Left -= 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm4::FormShow(TObject *Sender)
{
	Timer1->Enabled = true;	
}
//---------------------------------------------------------------------------
void __fastcall TForm4::FormHide(TObject *Sender)
{
	Timer1->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm4::FormKeyDown(TObject *Sender, WORD &Key,
	  TShiftState Shift)
{
	Close();
}
//---------------------------------------------------------------------------
