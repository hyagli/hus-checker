//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CheckThread.h"
#include "mainform.h"
#include "OptionsForm.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

__fastcall CheckUrlPass::CheckUrlPass()
	: TThread(false)
{
	MyClient = new TIdHTTP(Form1);
	MyClient->HandleRedirects = false;
	FreeOnTerminate = true;
	Synchronize(GetNewLink);
}
//---------------------------------------------------------------------------


void __fastcall CheckUrlPass::Execute(){
	while(SourceType != stEMPTY && !Terminated && (Form1->ThreadCount <= Options->MaxThreads)){
		Process();
		MyClient->Disconnect();
		Synchronize(GetNewLink);
	}
	Synchronize(Form1->ThreadDone);
	delete MyClient;
}
//---------------------------------------------------------------------------


void __fastcall CheckUrlPass::Process()
{
	if(Data.Length() == 0){
    	ResCode = rtEMPTY;
        Synchronize(Result);
        return;
    }
	String LData = Data;
	ResCode = rtBAD;

	//if the pass is sent from MIRC(dde) or a special file is being checked
    //the first word is the sender so parse the first word as <SentBy>
	if(SourceType == stDDE || SourceType == stSPECIAL){
		SentBy = LData.SubString(1,LData.Pos(" ")-1);
		LData = LData.SubString(LData.Pos(" ")+1,LData.Length());
	}

   	String User = "User";
	String Pass = "Pass";
	String Port = "80";
	String Host = "";
	if(LData.Pos("http://"))
		LData = LData.SubString(LData.Pos("http://")+7,LData.Length());
	else if(LData.Pos("HTTP://"))
		LData = LData.SubString(LData.Pos("HTTP://")+7,LData.Length());

	//----------USER PASS--------------------
	//	http://www.site.com l:login p:pass
	String PL="",LP="";
   	if(LData.Pos(" l:") && LData.Pos(" p:")){
		PL = " p:";   LP = " l:";
	}
	else if(LData.Pos(" L:") && LData.Pos(" P:")){
		PL = " P:";   LP = " L:";
	}

	if(PL!=""){
		User = LData.SubString(LData.Pos(LP)+3,LData.Length());
		Pass = User.SubString(User.Pos(PL)+3,LData.Length());
		User = User.SubString(1,User.Pos(PL)-1);
		LData = LData.SubString(1,LData.Pos(LP)-1);
	}
	//----------USER PASS--------------------
	// http://user:pass@www.site.com
	else if(LData.Pos("@")){
		User = "";
		while(LData.Pos("@")){
			User += LData.SubString(1,LData.Pos("@"));
	   		LData = LData.SubString(LData.Pos("@")+1,LData.Length());
		}
		User = User.SubString(1,User.Length()-1);
		Pass = User.SubString(User.Pos(":")+1,User.Length());
		User = User.SubString(1,User.Pos(":")-1);
		if(User == "" || Pass == ""){
			ResultText = "No username or password";
			Synchronize(Result);
			return;
		}
	}
	else{
		ResultText = "Couldn't parse the username and password";
		Synchronize(Result);
		return;
	}

	//----------PORT
	if(LData.Pos(":")){
		Host = LData.SubString(1,LData.Pos(":")-1);
		LData = LData.SubString(LData.Pos(":")+1,LData.Length());
		Port = "";
		while(LData!="" && isdigit(LData[1])){
			Port = Port + LData[1];
			LData = LData.SubString(2,LData.Length());
		}
	}

	//----------HOST
	if(LData == ""){
		ResultText = "Invalid URL";
		Synchronize(Result);
		return;
	}
	if(LData.Pos("/")){
		Host = LData.SubString(1,LData.Pos("/")-1);
		LData = LData.SubString(LData.Pos("/"),LData.Length());
	}
	else{
		Host = LData;
		LData = "/";
	}

	//Connection Settings
	MyClient->Host = Host;
	MyClient->Port = StrToIntDef(Port,80);
	MyClient->Request->UserAgent = "Mozilla/4.0 (compatible; MSIE 5.00; Windows 98)";
	MyClient->ProtocolVersion = pv1_1;
	MyClient->Request->Accept = "*/*";
	MyClient->HandleRedirects = false;
	MyClient->Request->ProxyServer = "";

//------------------------------------------------------------
	int Retry = 0;
	//----------PROXY----
	while(!Options->DirectConnection && Form1->ProxyList->Count){
		if(Terminated)
			return;

		Retry++;
		if(!Options->AlwaysRetry && Retry > Options->MaxRetry){
			ResultText = "Connection Problem";
			Synchronize(Result);
			return;
		}

		Synchronize(GetProxy);
		if(ProxyHost == ""){
			ShowMessage("Load some proxy");
			Terminate();
			return;
		}

		String ProxyPort = ProxyHost.SubString(ProxyHost.Pos(":")+1,ProxyHost.Length());
		ProxyHost = ProxyHost.SubString(1,ProxyHost.Pos(":")-1);

		try{
			MyClient->Request->ProxyServer = ProxyHost;
			MyClient->Request->ProxyPort = ProxyPort.ToInt();
			MyClient->Connect();
		}catch(...){
			continue;
		}   break;
	}//proxy while

	if(!Options->DirectConnection && !Form1->ProxyList->Count){
		ShowMessage("Load some proxy");
		Terminate();
		return;
	}

	if(Terminated)
		return;
//---------------------------------------------------
//  finally the real job

	//Check for fake addresses(do not require password)
	MyClient->Request->Username = "";
	MyClient->Request->Password = "";

	try{
		MyClient->Head("http://"+Host+LData);
	}catch(...){}
	if(MyClient->ResponseCode != 401 &&
	   MyClient->ResponseCode != 403){
		ResultText = "Fake. Do not require password";
		ResCode = rtFAKE;
		Synchronize(Result);
		return;
	}

	//set the username
	MyClient->Request->Username = User;
	MyClient->Request->Password = Pass;

	try{
		MyClient->Head("http://"+Host+LData);
	}catch(...){
		ResultText = MyClient->ResponseText;
		Synchronize(Result);
		return;
	}

	ResultText = MyClient->ResponseText;
	if(MyClient->ResponseCode == 200){
		ResCode = rtGOOD;
		Synchronize(Result);
		return;
	}
	Synchronize(Result);
	return;
}
//---------------------------------------------------------------------------

//ask for a new proxy
void __fastcall CheckUrlPass::GetProxy(void){
	ProxyHost = RemoveSpaces(Form1->GetProxy());
}
//---------------------------------------------------------------------------

//Get a new link from the buffers, set the type of source
void __fastcall CheckUrlPass::GetNewLink(void){
	if(Form1->FileBuffer->Count){
		Data = Form1->FileBuffer->Strings[0];
		Form1->FileBuffer->Delete(0);
		SourceType = stFILE;
	}
    else if(Form1->StopSpecialThreads == false && Form1->SpecialBuffer->Count){
    	Data = Form1->SpecialBuffer->Strings[0];
        Form1->SpecialBuffer->Delete(0);
        SourceType = stSPECIAL;
        Form1->SpecialProcessingCount++;
    }
	else if(Form1->ManualBuffer->Count){
		Data = Form1->ManualBuffer->Strings[0];
		Form1->ManualBuffer->Delete(0);
		SourceType = stMANUAL;
	}
	else if(Form1->DdeBuffer->Count){
		Data = Form1->DdeBuffer->Strings[0];
		Form1->DdeBuffer->Delete(0);
		SourceType = stDDE;
	}
	else
		SourceType = stEMPTY;
	Data = RemoveSpaces(Data);
}
//---------------------------------------------------------------------------


//Do the result processing
void __fastcall CheckUrlPass::Result(void){
	String ToAdd = (ResCode==rtGOOD)?(".g "):(".b ");
    if(Options->DisplayFake && ResCode==rtFAKE)
    	ToAdd = ".f ";

    //pass sent from MIRC
	if(SourceType == stDDE){
		Form1->SendDde(Options->ServiceName,"COMMAND",0,"/msg "+
					   Options->ChannelName+" "+ToAdd+SentBy);
		ToAdd = "DDE "+ToAdd+": "+Data;
	}
    //pass entered manually
	else if(SourceType == stMANUAL){
		ToAdd = "\r\n//-----MANUAL: | "+ToAdd+"|-----\r\n"+Data+"\r\n";
	}
    //pass from a pass file
	else if(SourceType == stFILE){
		ToAdd  = "FILE "+ToAdd+": "+Data;
        if(ResCode == rtGOOD)
        	Form1->FileResult->Add(Data);
		if(--Form1->FileLineCount < 1)
    		Form1->FileDone();
	}
    //pass from a spec file
    else if(SourceType == stSPECIAL){
        Form1->SpecialLineCount--;
        Form1->SpecialProcessingCount--;
    	ToAdd = "SPECIAL "+ToAdd+": "+Data;
        if(ResCode == rtGOOD)
        	Form1->SpecialGood->Add(Data);
        else if(ResCode != rtEMPTY)
        	Form1->SpecialBad->Add(SentBy);
        if(Form1->SpecialLineCount < 1 ||
          (Form1->SpecialProcessingCount < 1 && Form1->StopSpecialThreads))
        	Form1->SpecialDone();
    }

    if(ResCode != rtEMPTY)
		Form1->Results->Lines->Add(ToAdd);
}
//---------------------------------------------------------------------------


//Function that removes the spaces at the beginning or end of the string
String __fastcall CheckUrlPass::RemoveSpaces(String Data){
	if(Data.Length() == 0)
    	return Data;
	int i=0;
	while(++i<Data.Length() && Data[i]==' ');
	Data = Data.SubString(i,Data.Length());
	i=Data.Length()+1;
	while(i>1 && Data[--i]==' ');
	return Data.SubString(1,i);
}
//---------------------------------------------------------------------------

