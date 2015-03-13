//---------------------------------------------------------------------------

#ifndef CheckThreadH
#define CheckThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <IdHTTP.hpp>

//result types
#define rtEMPTY  0
#define rtGOOD   1
#define rtBAD    2
#define rtFAKE   3

//source types
#define stEMPTY   0
#define stDDE     1
#define stMANUAL  2
#define stFILE    3
#define stSPECIAL 4

//---------------------------------------------------------------------------
class CheckUrlPass : public TThread
{
private:
	TIdHTTP *MyClient;
	int SourceType;
	int ProxyIndex;
	String Data;
	String ProxyHost;
	String SentBy;
	String ResultText;
	int   ResCode;
	void __fastcall Result(void);
	void __fastcall GetProxy(void);
	void __fastcall GetNewLink(void);
	void __fastcall Process();
protected:
	void __fastcall Execute();
public:
	String __fastcall RemoveSpaces(String Data);
	__fastcall CheckUrlPass();
};
//---------------------------------------------------------------------------
#endif
