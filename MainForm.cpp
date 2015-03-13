//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <time.h>
using namespace std;
#include "mainform.h"
#include "CheckThread.h"
#include "About.h"
#include "OptionsForm.h"
#include "Htmlhelp.h"

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


void __fastcall TForm1::FormCreate(TObject *Sender)
{
	//Open the proxy file
	ProxyList = new TStringList;
	try{
		ProxyList->LoadFromFile(ExtractFilePath(Application->ExeName)+"proxy.txt");
	}catch(...){
		MyError("Error reading the proxy file (proxy.txt)");
		MyError("You must provide some proxies or choose direct connection");
	}

	//Post Buffers
	DdeBuffer     = new TStringList;
	ManualBuffer  = new TStringList;

	FileBuffer    = new TStringList;
	FileResult    = new TStringList;

    SpecialBuffer = new TStringList;
    SpecialGood   = new TStringList;
    SpecialBad    = new TStringList;

    //Settings -- will use ini file
    CurrentFile = "";
    CurrentSpecial = "";
	Paused = false;
    Rotater = 0;
    StopSpecialThreads = false;
    ThreadCount = 0;
}
//---------------------------------------------------------------------------


//A new post has come from the bot
void __fastcall TForm1::CheckChange(TObject *Sender)
{
	if(Paused)
		return;
	DdeBuffer->Add(Check->Text);
	if(ThreadCount < Options->MaxThreads){
		CheckUrlPass *newthread = new CheckUrlPass;
		if(newthread)
			StatusBar->SimpleText = String(++ThreadCount)+" threads running";
        else
   	    	MyError("Error launching new thread in CheckChange");
	}
}
//---------------------------------------------------------------------------

//A new exec message from mirc
void __fastcall TForm1::ExecChange(TObject *Sender)
{
	String Cmd = Exec->Text;
	if(Cmd == "exit")
		Application->Terminate();
	else if(Cmd == "pause")
		Paused = true;
	else if(Cmd == "resume")
		Paused = false;
    else if(Cmd.SubString(1,Cmd.Pos(" ")-1) == "check")
    	CheckSpecial(Cmd.SubString(Cmd.Pos(" ")+1,Cmd.Length()),false);
	else if(Cmd.SubString(1,Cmd.Pos(" ")-1) == "resume")
		CheckSpecial(Cmd.SubString(Cmd.Pos(" ")+1,Cmd.Length()),true);
}
//---------------------------------------------------------------------------

//A new post has been added manually
void __fastcall TForm1::ManualButtonClick(TObject *Sender)
{
	ManualBuffer->Add(ManualEdit->Text);
    //Create a new thread
	if(ThreadCount < Options->MaxThreads){
		CheckUrlPass *newthread = new CheckUrlPass;
		if(newthread)
			StatusBar->SimpleText = String(++ThreadCount)+" threads running";
        else
   	    	MyError("Error launching new thread in ManualButtonClick");
	}
}
//---------------------------------------------------------------------------

//Give focus to button
void __fastcall TForm1::ManualEditEnter(TObject *Sender)
{
	CommandButton->Default = false;
	ManualButton->Default = true;
}
//---------------------------------------------------------------------------

//Give focus to button
void __fastcall TForm1::CommEditEnter(TObject *Sender)
{
	ManualButton->Default = false;
	CommandButton->Default = true;
}
//---------------------------------------------------------------------------

//Send dde messages to mirc
void __fastcall TForm1::SendDde(String service, String topic,
                                String item   , String msg){
	DdeConv->SetLink(service,topic);
	if(!DdeConv->OpenLink()){
		MyError("Mirc is not running or the service name is invalid");
        MyError("Change it from Edit->Options");
		return;
	}
	DdeConv->PokeData(item,msg.c_str());
	DdeConv->CloseLink();
	return;
}
//---------------------------------------------------------------------------

//Send command to mirc (demonstration purposes :))
void __fastcall TForm1::CommandButtonClick(TObject *Sender)
{
	SendDde(Options->ServiceName,"COMMAND",0,CommEdit->Text);
}
//---------------------------------------------------------------------------

//Menu exit
void __fastcall TForm1::Exit1Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

//Options
void __fastcall TForm1::Options1Click(TObject *Sender)
{
	//if the maximum number of threads is increased, reach it
	int temp = Options->MaxThreads;
	Options->ShowModal();
    if(Options->MaxThreads > temp)
		while(ThreadCount < Options->MaxThreads){
        	CheckUrlPass *newthread = new CheckUrlPass;
            if(newthread)
            	StatusBar->SimpleText = String(++ThreadCount)+" threads running";
	        else
    	    	MyError("Error launching new thread in Options1Click");
        }
}
//---------------------------------------------------------------------------

//Menu about
void __fastcall TForm1::About1Click(TObject *Sender)
{
	Form4->DoubleBuffered = true;
	Form4->ShowModal();
}
//---------------------------------------------------------------------------

//Replace the current proxy list with a new one
void __fastcall TForm1::OpenProxy1Click(TObject *Sender)
{
	TStringList *temp = new TStringList;
	if(OpenDialog->Execute()){
		try{
			temp->LoadFromFile(OpenDialog->FileName);
		}catch(...){
			MyError("Error reading the proxy file ("+OpenDialog->FileName+")");
        	MyError("Previous proxies will be kept");
			delete temp;
			return;
		}
		ProxyList = temp;
		temp->Clear();
	}
	delete temp;
}
//---------------------------------------------------------------------------

//Add new proxies to the current list
void __fastcall TForm1::AddProxy1Click(TObject *Sender)
{
	TStringList *temp = new TStringList;
	if(OpenDialog->Execute()){
		try{
			temp->LoadFromFile(OpenDialog->FileName);
		}catch(...){
			MyError("Error reading the proxy file ("+OpenDialog->FileName+")");
			delete temp;
			return;
		}
		ProxyList->AddStrings(temp);
		temp->Clear();
	}
	delete temp;
}
//---------------------------------------------------------------------------

//A thread has finished execution
void __fastcall TForm1::ThreadDone(){
	if(--ThreadCount)
		StatusBar->SimpleText = String(ThreadCount)+" threads running";
	else
		StatusBar->SimpleText = "Idle";
}
//---------------------------------------------------------------------------

//Double click the status window
void __fastcall TForm1::ResultsDblClick(TObject *Sender)
{
	Results->Text = "";
}
//---------------------------------------------------------------------------

//Menu - Check a list file
void __fastcall TForm1::CheckFile1Click(TObject *Sender)
{
	if(OpenDialog->Execute()){
        try{
			FileBuffer->LoadFromFile(OpenDialog->FileName);
        }catch(...){
            MyError("Error reading the file ("+OpenDialog->FileName+")");
            FileBuffer->Clear();
			return;
        }
        CurrentFile = OpenDialog->FileName;
        FileLineCount = FileBuffer->Count;
        CheckFile1->Enabled = false;
		while(ThreadCount < Options->MaxThreads){
			CheckUrlPass *newthread = new CheckUrlPass;
			if(newthread)
				StatusBar->SimpleText = String(++ThreadCount)+" threads running";
	        else
    	    	MyError("Error launching new thread in CheckFile");
		}
	}
}
//---------------------------------------------------------------------------

//ListFile checked
void __fastcall TForm1::FileDone(){
	SaveDialog->FileName = CurrentFile;
    if(SaveDialog->Execute()){
		try{
        	FileResult->SaveToFile(SaveDialog->FileName);
        }catch(...){
			MyError("Error saving the results to file ("+OpenDialog->FileName+")");
        }
    }
    FileResult->Clear();
    CurrentFile = "";
    CheckFile1->Enabled = true;
}
//---------------------------------------------------------------------------

//Check Special button
void __fastcall TForm1::SpecialButtonClick(TObject *Sender)
{
    if(Options->GetResume(SpecialBox->Text) &&
       (MessageBox(Handle,"A resume information is present\nDo you want to resume",
                          "Resume Possible",MB_YESNO|MB_ICONQUESTION) == ID_YES))
    	CheckSpecial(SpecialBox->Text,true);
	else
	    CheckSpecial(SpecialBox->Text,false);
}
//---------------------------------------------------------------------------

//Check Special list from beginning
void __fastcall TForm1::CheckSpecial(String ListFile, bool Resume){
    //Check if there is a current operation
	if(!CurrentSpecial.IsEmpty()){
    	MyError("Request to check: ("+ListFile+") ");
        MyError("was denied, a file is already being checked");
        return;
    }

    //Check if this is a valid special file
	if(SpecialBox->Items->IndexOf(ListFile) == -1)
    	return;

    //open file
	try{
		SpecialBuffer->LoadFromFile(ListFile+".txt");
	}catch(...){
		MyError("Error reading list file ("+ListFile+".txt)");
		SpecialBuffer->Clear();
		return;
    }

    //Resume operation
    if(Resume){
    	int Count = Options->GetResume(ListFile);
		while(Count-- > 0 && SpecialBuffer->Count > 0){
			SpecialGood->Add(SpecialBuffer->Strings[0]);
            SpecialBuffer->Delete(0);
        }
        Options->SetResume(ListFile,0);
    }

    //update states
    CurrentSpecial = ListFile;
    SpecialLineCount = SpecialBuffer->Count;
    SpecialButton->Enabled = false;
    StopSpecialButton->Enabled = true;

    //create new threads
	while(ThreadCount < Options->MaxThreads){
		CheckUrlPass *newthread = new CheckUrlPass;
		if(newthread)
			StatusBar->SimpleText = String(++ThreadCount)+" threads running";
        else
        	MyError("Error launching new thread in CheckSpecial");
    }
}
//---------------------------------------------------------------------------

//Special file checked
void __fastcall TForm1::SpecialDone(){
	// the check process has not been finished
    // do some resume operations
	if(SpecialBuffer->Count > 0){
    	Options->SetResume(CurrentSpecial,SpecialGood->Count);
		SpecialGood->AddStrings(SpecialBuffer);
        SpecialBuffer->Clear();
    }

	//Save good posts
	try{
       	SpecialGood->SaveToFile(CurrentSpecial+".txt");
    }catch(...){
		MyError("Error saving the results to file ("+CurrentSpecial+".txt)");
    }
    SpecialGood->Clear();

    //Open Post.txt
    TStringList *File = new TStringList;
    try{
		File->LoadFromFile("post.txt");
	}catch(...){
		MyError("Error reading (post.txt)");
		delete File;
		return;
    }

    //Search in post.txt, when a bad post is found;
    //take the ident and delete the line
    int i=0, b;
    String Current;
    while(i<File->Count){
    	Current  = File->Strings[i];
        Current  = Current.SubString(2,Current.Pos(" ")-1);
        //search this post number in bad posts
        b = SpecialBad->IndexOf(Current);
        if(b != -1){
        	//Found the post, take the ident and delete the line
        	Current = File->Strings[i];
            Current = Current.SubString(Current.Pos(" ")+2,Current.Length());
            Current  = Current.SubString(1,Current.Pos(" ")-1);
    	    SpecialBad->Strings[b] = Current;
            File->Delete(i);
        }
        else
        	i++;
    }

	//save post.txt
   	try{
       	File->SaveToFile("post.txt");
    }catch(...){
		MyError("Error saving (post.txt)");
    }
    delete File;

    //open users.ini
    TIniFile *Users = new TIniFile(ExtractFilePath(Application->ExeName)+"users.ini");

    //search bad post in user.ini and decrease the required field when found
    while(SpecialBad->Count > 0){
    	Current = SpecialBad->Strings[0];
        //Is the user existing
        if(Users->SectionExists(Current)){
        	//Update the users field
            int OldValue = Users->ReadInteger(Current,CurrentSpecial+"-post",1);
            Users->WriteInteger(Current,CurrentSpecial+"-post",OldValue-1);
        }
        SpecialBad->Delete(0);
    }

	//save users.ini
    Users->UpdateFile();
    delete Users;

    //Update states
    SpecialBad->Clear();
    CurrentSpecial = "";
    SpecialButton->Enabled = true;
}
//---------------------------------------------------------------------------

//Error output function
void __fastcall TForm1::MyError(String Err){
	TColor previous = Results->Font->Color;
	Results->Font->Color = clRed;
	Results->Font->Style = TFontStyles() << fsBold;
	Results->Lines->Add(Err);
    Results->Font->Style = TFontStyles();
    Results->Font->Color = previous;
}
//---------------------------------------------------------------------------

//Give the next proxy to the thread
String TForm1::GetProxy(){
    if(!ProxyList->Count)
    	return "";

    if(Rotater >= Form1->ProxyList->Count)
    	Rotater = 0;

	return ProxyList->Strings[Rotater++];
}
//---------------------------------------------------------------------------

//Stop special operation
void __fastcall TForm1::StopSpecialButtonClick(TObject *Sender)
{
	StopSpecialThreads = true;
    StopSpecialButton->Enabled = false;
}
//---------------------------------------------------------------------------

//If Form is closed when there is still an operation
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	if(ThreadCount > 0){
		if(MessageBox(Handle,"There are still unfinished jobs\nIf you exit"
        " now you will lose all the previous check results","Confirm",
        MB_OKCANCEL|MB_ICONQUESTION) == ID_CANCEL)
        	Action = caNone;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::UserManual1Click(TObject *Sender)
{
	String Help = ChangeFileExt(Application->ExeName,".chm");
    if(FileExists(Help)){
    	Help = Help + ">main";
		if(!HtmlHelp(GetDesktopWindow(),Help.c_str(),HH_DISPLAY_TOPIC,NULL))
        	MyError("!!!Cannot Open the Help File!!!");
    }else{
    	MyError("!!!Cannot Find the Help File!!!");
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ResultsChange(TObject *Sender)
{
	if(Results->Lines->Count > 1000)
    	Results->Clear();
}
//---------------------------------------------------------------------------

