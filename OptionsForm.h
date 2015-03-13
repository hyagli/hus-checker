//---------------------------------------------------------------------------

#ifndef OptionsFormH
#define OptionsFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <IniFiles.hpp>
//---------------------------------------------------------------------------
class TOptions : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl;
	TButton *CancelButton;
	TButton *OkButton;
	TTabSheet *ConnectionPage;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *ThreadEdit;
	TUpDown *UpDown1;
	TEdit *RetryEdit;
	TUpDown *UpDown2;
	TCheckBox *RetryBox;
	TGroupBox *GroupBox3;
	TCheckBox *DisplayFakeBox;
	TCheckBox *DirectConnectionBox;
	TTabSheet *MircPage;
	TGroupBox *GroupBox2;
	TLabel *Label7;
	TLabel *Label8;
	TEdit *ServiceNameEdit;
	TEdit *ChannelNameEdit;
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall RetryBoxClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall OkButtonClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
	void __fastcall SaveSettings();
    void __fastcall LoadSettings();
    void __fastcall LoadIni();
    void __fastcall SaveIni();

    TIniFile *IniFile;

	//settings
    TStringList *FResumes;
	int FMaxThreads;
	int FMaxRetry;
	bool FAlwaysRetry;
    bool FDisplayFake;
    bool FDirectConnection;
	String FServiceName;
	String FChannelName;

public:		// User declarations
	__fastcall TOptions(TComponent* Owner);
    int  __fastcall GetResume(String ListFile);
    void __fastcall SetResume(String ListFile,int Line);

	//settings
	__property int MaxThreads = { read=FMaxThreads };
	__property int MaxRetry = { read=FMaxRetry };
	__property bool AlwaysRetry = { read=FAlwaysRetry };
    __property bool DisplayFake = { read=FDisplayFake };
    __property bool DirectConnection = { read=FDirectConnection };
	__property String ServiceName = { read=FServiceName };
	__property String ChannelName = { read=FChannelName };
};
//---------------------------------------------------------------------------
extern PACKAGE TOptions *Options;
//---------------------------------------------------------------------------
#endif
