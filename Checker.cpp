//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USEFORM("MainForm.cpp", Form1);
USEFORM("OptionsForm.cpp", Options);
USEFORM("About.cpp", Form4);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TForm1), &Form1);
		Application->CreateForm(__classid(TOptions), &Options);
		Application->CreateForm(__classid(TForm4), &Form4);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------
