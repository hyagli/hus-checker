//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "OptionsForm.h"
#include "Htmlhelp.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"
TOptions *Options;
//---------------------------------------------------------------------------

__fastcall TOptions::TOptions(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TOptions::FormCreate(TObject *Sender)
{
    FResumes = new TStringList;
	IniFile = new TIniFile(ChangeFileExt(Application->ExeName,".ini"));
    LoadIni();
}
//---------------------------------------------------------------------------

void __fastcall TOptions::FormKeyPress(TObject *Sender, char &Key)
{
	if(Key == VK_RETURN){
    	SaveSettings();
		ModalResult = mrOk;
    }
	else if(Key == VK_ESCAPE)
		ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

void __fastcall TOptions::RetryBoxClick(TObject *Sender)
{
	RetryEdit->Enabled = !RetryBox->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TOptions::LoadIni(){
	//Read the connection settings
   	FMaxThreads = IniFile->ReadInteger("Connection","MaxThreads",10);
	FMaxRetry = IniFile->ReadInteger("Connection","MaxRetry",50);
	FAlwaysRetry = IniFile->ReadBool("Connection","AlwaysRetry",false);
	FDisplayFake = IniFile->ReadBool("Connection","DisplayFake",false);
	FDirectConnection = IniFile->ReadBool("Connection","DirectConnection",false);

    //Read mirc settings
	FServiceName = IniFile->ReadString("mIRC","ServiceName","mIRC");
	FChannelName = IniFile->ReadString("mIRC","ChannelName","#loginhere");

    //Read resume settings
    FResumes->Values["god"] = IniFile->ReadInteger("Resume","god",0);
    FResumes->Values["regular"] = IniFile->ReadInteger("Resume","regular",0);
    FResumes->Values["elite"] = IniFile->ReadInteger("Resume","elite",0);
    FResumes->Values["crackers"] = IniFile->ReadInteger("Resume","crackers",0);
}
//---------------------------------------------------------------------------

void __fastcall TOptions::SaveIni(){
	//Write the connection settings
   	IniFile->WriteInteger("Connection","MaxThreads",FMaxThreads);
	IniFile->WriteInteger("Connection","MaxRetry",FMaxRetry);
	IniFile->WriteBool("Connection","AlwaysRetry",FAlwaysRetry);
	IniFile->WriteBool("Connection","DisplayFake",FDisplayFake);
	IniFile->WriteBool("Connection","DirectConnection",FDirectConnection);

    //Write mirc settings
	IniFile->WriteString("mIRC","ServiceName",FServiceName);
	IniFile->WriteString("mIRC","ChannelName",FChannelName);

    //Write resume settings
    IniFile->WriteString("Resume","god",FResumes->Values["god"]);
    IniFile->WriteString("Resume","regular",FResumes->Values["regular"]);
    IniFile->WriteString("Resume","elite",FResumes->Values["elite"]);
    IniFile->WriteString("Resume","crackers",FResumes->Values["crackers"]);
}
//---------------------------------------------------------------------------

void __fastcall TOptions::FormShow(TObject *Sender)
{
    LoadSettings();
}
//---------------------------------------------------------------------------

void __fastcall TOptions::OkButtonClick(TObject *Sender)
{
    SaveSettings();
}
//---------------------------------------------------------------------------

void __fastcall TOptions::LoadSettings(){
	ThreadEdit->Text = String(FMaxThreads);
	RetryEdit->Text = String(FMaxRetry);
	RetryBox->Checked = FAlwaysRetry;
    DisplayFakeBox->Checked = FDisplayFake;
	DirectConnectionBox->Checked = FDirectConnection;
	ServiceNameEdit->Text = FServiceName;
	ChannelNameEdit->Text = FChannelName;
}
//---------------------------------------------------------------------------

void __fastcall TOptions::SaveSettings(){
	FAlwaysRetry = RetryBox->Checked ? 1 : 0;
   	FDisplayFake = DisplayFakeBox->Checked ? 1 : 0;
    FDirectConnection = DirectConnectionBox->Checked ? 1 : 0;
	FServiceName = ServiceNameEdit->Text;
	FChannelName = ChannelNameEdit->Text;
	FMaxThreads = StrToIntDef(ThreadEdit->Text,10);
    FMaxRetry = StrToIntDef(RetryEdit->Text,50);
}
//---------------------------------------------------------------------------

void __fastcall TOptions::FormDestroy(TObject *Sender)
{
	SaveIni();
	IniFile->UpdateFile();
    delete IniFile;
    delete FResumes;
}
//---------------------------------------------------------------------------

int __fastcall TOptions::GetResume(String ListFile){
	return StrToIntDef(FResumes->Values[ListFile],0);
}
//---------------------------------------------------------------------------

void __fastcall TOptions::SetResume(String ListFile,int Line){
	FResumes->Values[ListFile] = String(Line);
}
//---------------------------------------------------------------------------

