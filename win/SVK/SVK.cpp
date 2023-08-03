//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdlib.h>
#pragma hdrstop
#include "SVK.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#define FSIZE 262144
TForm1 *Form1;

//function declare
HANDLE InitComPort(LPCTSTR szDCS);
unsigned char Send(HANDLE hPort, unsigned char size, unsigned char* byte);

//variables
HANDLE hPort;
int alltr=0,allres=0;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
  : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
hPort=InitComPort("COM1");
if(hPort==INVALID_HANDLE_VALUE)
	MessageBox(NULL,"Ошибка инициализация СОМ1-порта!","Ошибка!",MB_APPLMODAL);
}

//transmit function----------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{

if(Edit3->Text.Length())
{
        if(Send(hPort,Edit3->Text.Length(),Edit3->Text.c_str()))
        {        MessageBox(NULL,"Ошибка передачи!","Ошибка!",MB_APPLMODAL);                        ;
        }
        else
        {
                ListBox1->Items->Add(Edit3->Text);
                ListBox1->TopIndex=ListBox1->Items->Count-1;
                ListBox3->Items->Add(Edit3->Text.Length());
                ListBox3->TopIndex=ListBox1->Items->Count-1;
                alltr+=StrToInt(Edit3->Text.Length());
                Label7->Caption=IntToStr(alltr);
                Label7->Visible=true;
        }
}
}

//----------------------------------------------------------------------------
unsigned char Send(HANDLE hPort,unsigned char size,unsigned char* byte)
{
DWORD tr;
unsigned char bt,i;

for(i=0;i<size;i++)
{
        bt=byte[i];
        if(WriteFile(hPort,&bt,1,&tr,NULL)==FALSE)
                return 1;
}

//bt='\n';
//WriteFile(hPort,&bt,1,&tr,NULL);

return 0;
}

//---------------------------------------------------------------------------
HANDLE InitComPort(LPCTSTR szDCS)
{
COMMTIMEOUTS CommTimeOuts;
DCB dcb;
HANDLE hPort;

hPort=CreateFile(szDCS,GENERIC_READ|GENERIC_WRITE,NULL,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
GetCommState(hPort,&dcb);
dcb.BaudRate=CBR_115200;
dcb.fBinary=TRUE;
dcb.fParity=FALSE;
dcb.fOutxCtsFlow=FALSE;
dcb.fOutxDsrFlow=FALSE;
dcb.fDtrControl=DTR_CONTROL_ENABLE;
dcb.fDsrSensitivity=FALSE;
dcb.fTXContinueOnXoff=FALSE;
dcb.fOutX=FALSE;
dcb.fInX=FALSE;
dcb.fErrorChar=FALSE;
dcb.fNull=FALSE;
dcb.fRtsControl=RTS_CONTROL_ENABLE;
dcb.fAbortOnError=FALSE;
dcb.XonLim=0;
dcb.ByteSize=8;
dcb.Parity=NOPARITY;
dcb.StopBits=ONESTOPBIT;
SetCommState(hPort,&dcb);
CommTimeOuts.ReadIntervalTimeout=0;
CommTimeOuts.ReadTotalTimeoutMultiplier=0;
CommTimeOuts.ReadTotalTimeoutConstant=100;
CommTimeOuts.WriteTotalTimeoutMultiplier=0;
CommTimeOuts.WriteTotalTimeoutConstant=0;
SetCommTimeouts(hPort,&CommTimeOuts);
PurgeComm(hPort,PURGE_RXCLEAR|PURGE_TXCLEAR);
ClearCommError(hPort,NULL,NULL);
EscapeCommFunction(hPort,SETDTR);
EscapeCommFunction(hPort,SETRTS);
return hPort;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Quit(TObject *Sender)
{
CloseHandle(hPort);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Exit(TObject *Sender)
{
exit(EXIT_SUCCESS);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioButton1Click(TObject *Sender)
{
CloseHandle(hPort);
hPort=InitComPort("COM1");
if(hPort==INVALID_HANDLE_VALUE)
        MessageBox(NULL,"Ошибка инициализация СОМ1-порта!","Ошибка!",MB_APPLMODAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton2Click(TObject *Sender)
{
CloseHandle(hPort);
hPort=InitComPort("COM2");
if(hPort==INVALID_HANDLE_VALUE)
        MessageBox(NULL,"Ошибка инициализация СОМ2-порта!","Ошибка!",MB_APPLMODAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton3Click(TObject *Sender)
{
CloseHandle(hPort);
hPort=InitComPort("COM3");
if(hPort==INVALID_HANDLE_VALUE)
        MessageBox(NULL,"Ошибка инициализация СОМ3-порта!","Ошибка!",MB_APPLMODAL);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::RadioButton4Click(TObject *Sender)
{
CloseHandle(hPort);
hPort=InitComPort("COM4");
if(hPort==INVALID_HANDLE_VALUE)
        MessageBox(NULL,"Ошибка инициализация СОМ4-порта!","Ошибка!",MB_APPLMODAL);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
MessageBox(NULL,"RS232 Sender v. 1.0.0. Build 0001\nCopyright ZTinc, 2007. All rights reserved.\n ","О программе",MB_APPLMODAL);
}

//---------------------------------------------------------------------------


void __fastcall TForm1::Edit3Change(TObject *Sender)
{
Button1->Caption="Отправить " + IntToStr(Edit3->Text.Length())+ " байт";
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
unsigned long iRead;
char szText[255];

for(unsigned char i=0;i<255;i++)
        szText[i]=0;

if((ReadFile(hPort,&szText,255,&iRead,NULL)!=FALSE)&&(iRead!=0))
{
        ListBox2->Items->Add(AnsiString(szText));
        ListBox2->TopIndex=ListBox2->Items->Count-1;
        ListBox4->Items->Add(IntToStr(iRead));
        ListBox4->TopIndex=ListBox4->Items->Count-1;
        allres+=iRead;
        Label8->Caption=IntToStr(allres);
        Label8->Visible=true;
}
}


void __fastcall TForm1::ListBox2Click(TObject *Sender)
{
Edit1->Text=ListBox2->Items->Strings[ListBox2->ItemIndex];
}
//---------------------------------------------------------------------------

