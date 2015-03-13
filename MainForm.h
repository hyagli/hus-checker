//---------------------------------------------------------------------------

#ifndef mainformH
#define mainformH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DdeMan.hpp>
#include "SHDocVw_OCX.h"
#include <OleCtrls.hpp>
#include <ScktComp.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>

#define ST_WAIT 0
#define ST_DONE 1
#define ST_NONE 2

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TDdeClientConv *DdeConv;
	TDdeServerItem *Check;
	TMemo *Results;
	TMainMenu *MainMenu1;
	TMenuItem *File1;
	TMenuItem *Exit1;
	TMenuItem *Edit1;
	TMenuItem *Options1;
	TMenuItem *Help1;
	TMenuItem *About1;
	TGroupBox *GroupBox2;
	TLabel *Label5;
	TLabel *Label6;
	TButton *CommandButton;
	TEdit *CommEdit;
	TEdit *ManualEdit;
	TButton *ManualButton;
	TMenuItem *OpenProxy1;
	TMenuItem *N1;
	TOpenDialog *OpenDialog;
	TMenuItem *AddProxy1;
	TStatusBar *StatusBar;
	TDdeServerItem *Exec;
	TMenuItem *CheckFile1;
	TMenuItem *N2;
	TSaveDialog *SaveDialog;
	TComboBox *SpecialBox;
	TButton *SpecialButton;
	TLabel *Label1;
	TButton *StopSpecialButton;
	TGroupBox *GroupBox1;
	TMenuItem *UserManual1;
	void __fastcall CheckChange(TObject *Sender);
	void __fastcall ManualButtonClick(TObject *Sender);
	void __fastcall ManualEditEnter(TObject *Sender);
	void __fastcall CommEditEnter(TObject *Sender);
	void __fastcall CommandButtonClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Exit1Click(TObject *Sender);
	void __fastcall Options1Click(TObject *Sender);
	void __fastcall About1Click(TObject *Sender);
	void __fastcall OpenProxy1Click(TObject *Sender);
	void __fastcall AddProxy1Click(TObject *Sender);
	void __fastcall ResultsDblClick(TObject *Sender);
	void __fastcall ExecChange(TObject *Sender);
	void __fastcall CheckFile1Click(TObject *Sender);
	void __fastcall SpecialButtonClick(TObject *Sender);
	void __fastcall StopSpecialButtonClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall UserManual1Click(TObject *Sender);
	void __fastcall ResultsChange(TObject *Sender);
private:
	void __fastcall CheckSpecial(String ListFile,bool Resume);

	bool Paused;
	String CurrentFile;
    String CurrentSpecial;
	int Rotater;
public:
    //status variables
    int FileLineCount;
    int SpecialLineCount;
    int SpecialProcessingCount;
    bool StopSpecialThreads;
	int ThreadCount;

    //Current Proxies
	TStringList *ProxyList;

    //Result buffer for the results of the lists
	TStringList *FileResult;
	TStringList *SpecialGood;
	TStringList *SpecialBad;

    //used buffers for the lists
	TStringList *DdeBuffer;
	TStringList *ManualBuffer;
	TStringList *FileBuffer;
    TStringList *SpecialBuffer;

	__fastcall TForm1(TComponent* Owner);
	void __fastcall SendDde(String service, String topic,
	                        String item   , String msg);
	//functions used by buffers for result purposes
	void __fastcall ThreadDone();
    void __fastcall FileDone();
    void __fastcall SpecialDone();

    //function to supply proxies for the threads
    String GetProxy();

    //error messages
    void __fastcall MyError(String err);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
