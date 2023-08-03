//---------------------------------------------------------------------------
#include <stdio.h>
#include <vcl.h>
#pragma hdrstop

#include "SVK2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//function declare
HANDLE InitComPort(LPCTSTR szDCS);
unsigned char Send(HANDLE hPort, unsigned char size, unsigned char* byte);
void clrb(void);

//variables
HANDLE hPort;
char str[255], num=0;
bool sem1=false, sem2=false, sem3=false;
AnsiString com="COM1", baud="9600", command;

char a[255], b[255], c[255], d[255], e[255];

TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
int i;

  Label41->Visible=false;

  for(i=1;i<21;i++)
  {
    com.sprintf("COM%d",i);
    hPort=InitComPort(com.c_str());
    if(hPort!=INVALID_HANDLE_VALUE)
    {
      ComboBox1->Items->Add(com);
      CloseHandle(hPort);
    }
  }

  ComboBox1->ItemIndex=0;
  ComboBox2->Items->Add("1200");
  ComboBox2->Items->Add("2400");
  ComboBox2->Items->Add("4800");
  ComboBox2->Items->Add("9600");
  ComboBox2->Items->Add("14400");
  ComboBox2->Items->Add("38400");
  ComboBox2->Items->Add("57600");
  ComboBox2->Items->Add("115200");
  ComboBox2->ItemIndex=7;
}

//---------------------------------------------------------------------------
HANDLE InitComPort(LPCTSTR szDCS)
{
COMMTIMEOUTS CommTimeOuts;
DCB dcb;
HANDLE hPort;

hPort=CreateFile(szDCS,GENERIC_READ|GENERIC_WRITE,NULL,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
GetCommState(hPort,&dcb);
dcb.BaudRate=StrToInt(baud);
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
CommTimeOuts.ReadIntervalTimeout=100;
CommTimeOuts.ReadTotalTimeoutMultiplier=0;
CommTimeOuts.ReadTotalTimeoutConstant=1000;
CommTimeOuts.WriteTotalTimeoutMultiplier=0;
CommTimeOuts.WriteTotalTimeoutConstant=0;
SetCommTimeouts(hPort,&CommTimeOuts);
PurgeComm(hPort,PURGE_RXCLEAR|PURGE_TXCLEAR);
ClearCommError(hPort,NULL,NULL);
EscapeCommFunction(hPort,SETDTR);
EscapeCommFunction(hPort,SETRTS);
return hPort;
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

bt='\n';
WriteFile(hPort,&bt,1,&tr,NULL);

return 0;
}

//---------------------------------------------------------------------------
void clrb(void)
{
int i;

for(i=0;i<255;i++)
{
  str[i]=0;
  a[i]=0;
  b[i]=0;
  c[i]=0;
  d[i]=0;
  e[i]=0;
}
return;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
AnsiString com, mes;

if(Button2->Caption=="Подключить")
{
  com=ComboBox1->Items->Strings[ComboBox1->ItemIndex];
  baud=ComboBox2->Items->Strings[ComboBox2->ItemIndex];
  //ShowMessage(com);

  hPort=InitComPort(com.c_str());
  if(hPort==INVALID_HANDLE_VALUE)
	  ShowMessage(mes.sprintf("Ошибка инициализация порта %s",com));
  else
  {
    Button2->Caption="Отключить";
    Label41->Visible=true;
    Label41->Caption=mes.sprintf("%s подключен на %s", com, baud);
    Timer1->Enabled=true;
    Label47->Visible=false;
  }
}
else
{
  CloseHandle(hPort);
  Button2->Caption="Подключить";
  Timer1->Enabled=false;
  Label41->Visible=false;
  Label47->Visible=false;
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
if(Button2->Caption!="Подключить")
  CloseHandle(hPort);
exit(EXIT_SUCCESS);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
MessageBox(NULL,"SVK v. 1.0.0.","О программе",MB_APPLMODAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
unsigned long iRead;
char val;
int val1, val2, val3;

  if(hPort!=INVALID_HANDLE_VALUE)
  switch(num)
  {
    case 0:
    Label25->Font->Style=TFontStyles();
    Label22->Font->Style=TFontStyles()<<fsBold;
    command="*MT";
    if(Send(hPort,command.Length(),command.c_str()))
      goto err;
    clrb();
    ReadFile(hPort,&str,255,&iRead,NULL);
    sscanf(str,"TEMP: %s DEG CEL\n",&a);
    Edit72->Text=AnsiString(a);
    break;

    case 1:
    Label22->Font->Style=TFontStyles();
    Label43->Font->Style=TFontStyles()<<fsBold;
    Label44->Font->Style=TFontStyles()<<fsBold;
    Label45->Font->Style=TFontStyles()<<fsBold;
    Label46->Font->Style=TFontStyles()<<fsBold;
    Label23->Font->Style=TFontStyles()<<fsBold;
    command="*MS";
    if(Send(hPort,command.Length(),command.c_str()))
      goto err;
    clrb();
    ReadFile(hPort,&str,255,&iRead,NULL);
    sscanf(str,"REF+: %s REF0: %s REF-: %s Ucc: %s VAL: %s\n",&a ,&b, &c, &d, &e);
    Edit29->Text=AnsiString(a);
    Edit80->Text=AnsiString(b);
    Edit82->Text=AnsiString(c);
    Edit81->Text=AnsiString(d);
    Edit83->Text=AnsiString(e);
    break;

    case 2:
    Label43->Font->Style=TFontStyles();
    Label44->Font->Style=TFontStyles();
    Label45->Font->Style=TFontStyles();
    Label46->Font->Style=TFontStyles();
    Label23->Font->Style=TFontStyles();
    Label42->Font->Style=TFontStyles()<<fsBold;
    command="*MVM";
    if(Send(hPort,command.Length(),command.c_str()))
      goto err;
    clrb();
    ReadFile(hPort,&str,255,&iRead,NULL);
    sscanf(str,"Version firmvare MSP430: %s\n",&a);
    Edit79->Text=AnsiString(a);
    break;

    case 3:
    Label42->Font->Style=TFontStyles();
    Label24->Font->Style=TFontStyles()<<fsBold;
    command="*MVE";
    if(Send(hPort,command.Length(),command.c_str()))
      goto err;
    clrb();
    ReadFile(hPort,&str,255,&iRead,NULL);
    sscanf(str,"Version firmvare EPM1270: %s\n",&a);
    Edit35->Text=AnsiString(a);
    break;

    case 4:
    Label24->Font->Style=TFontStyles();
    Label8->Font->Style=TFontStyles()<<fsBold;
    command="*MF";
    if(Send(hPort,command.Length(),command.c_str()))
      goto err;
    clrb();
    ReadFile(hPort,&str,255,&iRead,NULL);
    sscanf(str,"CH0: %s CH1: %s CH2: %s CH3: %s\n",&a ,&b, &c, &d);
    Edit5->Text=AnsiString(a);
    Edit11->Text=AnsiString(b);
    Edit18->Text=AnsiString(c);
    Edit23->Text=AnsiString(d);
    break;

    case 5:
    Label8->Font->Style=TFontStyles();
    Label3->Font->Style=TFontStyles()<<fsBold;
    command="*MC00";
    if(Send(hPort,command.Length(),command.c_str()))
      goto err;
    clrb();
    ReadFile(hPort,&str,255,&iRead,NULL);
    sscanf(str,"CH: %d RMS: %s DC: %s AMP+: %s AMP-: %s VAL: %s\n", &val, &a ,&b, &c, &d, &e);
    Edit1->Text=AnsiString(a);
    Edit2->Text=AnsiString(b);
    Edit3->Text=AnsiString(c);
    Edit4->Text=AnsiString(d);
    Edit6->Text=AnsiString(e);
    break;

    case 6:
    Label3->Font->Style=TFontStyles();
    Label11->Font->Style=TFontStyles()<<fsBold;
    command="*MC01";
    if(Send(hPort,command.Length(),command.c_str()))
      goto err;
    clrb();
    ReadFile(hPort,&str,255,&iRead,NULL);
    sscanf(str,"CH: %d RMS: %s DC: %s AMP+: %s AMP-: %s VAL: %s\n", &val, &a ,&b, &c, &d, &e);
    Edit7->Text=AnsiString(a);
    Edit8->Text=AnsiString(b);
    Edit9->Text=AnsiString(c);
    Edit10->Text=AnsiString(d);
    Edit12->Text=AnsiString(e);
    break;

    case 7:
    Label11->Font->Style=TFontStyles();
    Label12->Font->Style=TFontStyles()<<fsBold;
    command="*MC02";
    if(Send(hPort,command.Length(),command.c_str()))
      goto err;
    clrb();
    ReadFile(hPort,&str,255,&iRead,NULL);
    sscanf(str,"CH: %d RMS: %s DC: %s AMP+: %s AMP-: %s VAL: %s\n", &val, &a ,&b, &c, &d, &e);
    Edit13->Text=AnsiString(a);
    Edit14->Text=AnsiString(b);
    Edit15->Text=AnsiString(c);
    Edit16->Text=AnsiString(d);
    Edit17->Text=AnsiString(e);
    break;

    case 8:
    Label12->Font->Style=TFontStyles();
    Label13->Font->Style=TFontStyles()<<fsBold;
    command="*MC03";
    if(Send(hPort,command.Length(),command.c_str()))
      goto err;
    clrb();
    ReadFile(hPort,&str,255,&iRead,NULL);
    sscanf(str,"CH: %d RMS: %s DC: %s AMP+: %s AMP-: %s VAL: %s\n", &val, &a ,&b, &c, &d, &e);
    Edit19->Text=AnsiString(a);
    Edit20->Text=AnsiString(b);
    Edit21->Text=AnsiString(c);
    Edit22->Text=AnsiString(d);
    Edit24->Text=AnsiString(e);
    break;

    case 9:
    Label13->Font->Style=TFontStyles();
    Label14->Font->Style=TFontStyles()<<fsBold;
    command="*MC04";
    if(Send(hPort,command.Length(),command.c_str()))
      goto err;
    clrb();
    ReadFile(hPort,&str,255,&iRead,NULL);
    sscanf(str,"CH: %d RMS: %s DC: %s AMP+: %s AMP-: %s VAL: %s\n", &val, &a ,&b, &c, &d, &e);
    Edit25->Text=AnsiString(a);
    Edit26->Text=AnsiString(b);
    Edit27->Text=AnsiString(c);
    Edit28->Text=AnsiString(d);
    Edit30->Text=AnsiString(e);
    break;

    case 10:
    Label14->Font->Style=TFontStyles();
    Label15->Font->Style=TFontStyles()<<fsBold;
    command="*MC05";
    if(Send(hPort,command.Length(),command.c_str()))
      goto err;
    clrb();
    ReadFile(hPort,&str,255,&iRead,NULL);
    sscanf(str,"CH: %d RMS: %s DC: %s AMP+: %s AMP-: %s VAL: %s\n", &val, &a ,&b, &c, &d, &e);
    Edit31->Text=AnsiString(a);
    Edit32->Text=AnsiString(b);
    Edit33->Text=AnsiString(c);
    Edit34->Text=AnsiString(d);
    Edit36->Text=AnsiString(e);
    break;

    case 11:
    Label15->Font->Style=TFontStyles();
    Label16->Font->Style=TFontStyles()<<fsBold;
    command="*MC06";
    if(Send(hPort,command.Length(),command.c_str()))
      goto err;
    clrb();
    ReadFile(hPort,&str,255,&iRead,NULL);
    sscanf(str,"CH: %d RMS: %s DC: %s AMP+: %s AMP-: %s VAL: %s\n", &val, &a ,&b, &c, &d, &e);
    Edit37->Text=AnsiString(a);
    Edit38->Text=AnsiString(b);
    Edit48->Text=AnsiString(c);
    Edit40->Text=AnsiString(d);
    Edit42->Text=AnsiString(e);
    break;

    case 12:
    Label16->Font->Style=TFontStyles();
    Label17->Font->Style=TFontStyles()<<fsBold;
    command="*MC07";
    if(Send(hPort,command.Length(),command.c_str()))
      goto err;
    clrb();
    ReadFile(hPort,&str,255,&iRead,NULL);
    sscanf(str,"CH: %d RMS: %s DC: %s AMP+: %s AMP-: %s VAL: %s\n", &val, &a ,&b, &c, &d, &e);
    Edit43->Text=AnsiString(a);
    Edit44->Text=AnsiString(b);
    Edit45->Text=AnsiString(c);
    Edit46->Text=AnsiString(d);
    Edit49->Text=AnsiString(e);
    break;

    case 13:
    Label17->Font->Style=TFontStyles();
    Label18->Font->Style=TFontStyles()<<fsBold;
    command="*MC08";
    if(Send(hPort,command.Length(),command.c_str()))
      goto err;
    clrb();
    ReadFile(hPort,&str,255,&iRead,NULL);
    sscanf(str,"CH: %d RMS: %s DC: %s AMP+: %s AMP-: %s VAL: %s\n", &val, &a ,&b, &c, &d, &e);
    Edit50->Text=AnsiString(a);
    Edit51->Text=AnsiString(b);
    Edit52->Text=AnsiString(c);
    Edit53->Text=AnsiString(d);
    Edit57->Text=AnsiString(e);
    break;

    case 14:
    Label18->Font->Style=TFontStyles();
    Label19->Font->Style=TFontStyles()<<fsBold;
    command="*MC09";
    if(Send(hPort,command.Length(),command.c_str()))
      goto err;
    clrb();
    ReadFile(hPort,&str,255,&iRead,NULL);
    sscanf(str,"CH: %d RMS: %s DC: %s AMP+: %s AMP-: %s VAL: %s\n", &val, &a ,&b, &c, &d, &e);
    Edit55->Text=AnsiString(a);
    Edit56->Text=AnsiString(b);
    Edit58->Text=AnsiString(c);
    Edit60->Text=AnsiString(d);
    Edit61->Text=AnsiString(e);
    break;

    case 15:
    Label19->Font->Style=TFontStyles();
    Label20->Font->Style=TFontStyles()<<fsBold;
    command="*MC10";
    if(Send(hPort,command.Length(),command.c_str()))
      goto err;
    clrb();
    ReadFile(hPort,&str,255,&iRead,NULL);
    sscanf(str,"CH: %d RMS: %s DC: %s AMP+: %s AMP-: %s VAL: %s\n", &val, &a ,&b, &c, &d, &e);
    Edit62->Text=AnsiString(a);
    Edit63->Text=AnsiString(b);
    Edit64->Text=AnsiString(c);
    Edit65->Text=AnsiString(d);
    Edit67->Text=AnsiString(e);
    break;

    case 16:
    Label20->Font->Style=TFontStyles();
    Label21->Font->Style=TFontStyles()<<fsBold;
    command="*MC11";
    if(Send(hPort,command.Length(),command.c_str()))
      goto err;
    clrb();
    ReadFile(hPort,&str,255,&iRead,NULL);
    sscanf(str,"CH: %d RMS: %s DC: %s AMP+: %s AMP-: %s VAL: %s\n", &val, &a ,&b, &c, &d, &e);
    Edit68->Text=AnsiString(a);
    Edit69->Text=AnsiString(b);
    Edit70->Text=AnsiString(c);
    Edit71->Text=AnsiString(d);
    Edit73->Text=AnsiString(e);
    break;

    case 17:
    Label21->Font->Style=TFontStyles();
    Label26->Font->Style=TFontStyles()<<fsBold;
    command="*MI0";
    if(Send(hPort,command.Length(),command.c_str()))
      goto err;
    clrb();
    ReadFile(hPort,&str,255,&iRead,NULL);
    sscanf(str,"PORT0: %d\n", &val);
    if(!(CheckBox22->Checked))
    {
      if(val&0x01)
        CheckBox6->Checked=true;
      else
        CheckBox6->Checked=false;
      if(val&0x02)
        CheckBox12->Checked=true;
      else
        CheckBox12->Checked=false;
      if(val&0x04)
        CheckBox11->Checked=true;
      else
        CheckBox11->Checked=false;
      if(val&0x08)
        CheckBox10->Checked=true;
      else
        CheckBox10->Checked=false;
      if(val&0x10)
        CheckBox9->Checked=true;
      else
        CheckBox9->Checked=false;
      if(val&0x20)
        CheckBox8->Checked=true;
      else
        CheckBox8->Checked=false;
      if(val&0x40)
        CheckBox7->Checked=true;
      else
        CheckBox7->Checked=false;
      if(val&0x80)
        CheckBox5->Checked=true;
      else
        CheckBox5->Checked=false;
    }
    break;

    case 18:
    Label26->Font->Style=TFontStyles();
    Label27->Font->Style=TFontStyles()<<fsBold;
    command="*MI1";
    if(Send(hPort,command.Length(),command.c_str()))
      goto err;
    clrb();
    ReadFile(hPort,&str,255,&iRead,NULL);
    sscanf(str,"PORT1: %d\n", &val);
    if(!(CheckBox40->Checked))
    {
      if(val&0x01)
        CheckBox21->Checked=true;
      else
        CheckBox21->Checked=false;
      if(val&0x02)
        CheckBox20->Checked=true;
      else
        CheckBox20->Checked=false;
      if(val&0x04)
        CheckBox19->Checked=true;
      else
        CheckBox19->Checked=false;
      if(val&0x08)
        CheckBox18->Checked=true;
      else
        CheckBox18->Checked=false;
      if(val&0x10)
        CheckBox17->Checked=true;
      else
        CheckBox17->Checked=false;
      if(val&0x20)
        CheckBox16->Checked=true;
      else
        CheckBox16->Checked=false;
      if(val&0x40)
        CheckBox15->Checked=true;
      else
        CheckBox15->Checked=false;
      if(val&0x80)
        CheckBox14->Checked=true;
      else
        CheckBox14->Checked=false;
    }
    break;

    case 19:
    Label27->Font->Style=TFontStyles();
    Label28->Font->Style=TFontStyles()<<fsBold;
    command="*MI2";
    if(Send(hPort,command.Length(),command.c_str()))
      goto err;
    clrb();
    ReadFile(hPort,&str,255,&iRead,NULL);
    sscanf(str,"PORT2: %d\n", &val);
    if(!(CheckBox42->Checked))
    {
      if(val&0x01)
        CheckBox30->Checked=true;
      else
        CheckBox30->Checked=false;
      if(val&0x02)
        CheckBox29->Checked=true;
      else
        CheckBox29->Checked=false;
      if(val&0x04)
        CheckBox28->Checked=true;
      else
        CheckBox28->Checked=false;
      if(val&0x08)
        CheckBox27->Checked=true;
      else
        CheckBox27->Checked=false;
      if(val&0x10)
        CheckBox26->Checked=true;
      else
        CheckBox26->Checked=false;
      if(val&0x20)
        CheckBox25->Checked=true;
      else
        CheckBox25->Checked=false;
      if(val&0x40)
        CheckBox24->Checked=true;
      else
        CheckBox24->Checked=false;
      if(val&0x80)
        CheckBox23->Checked=true;
      else
        CheckBox23->Checked=false;
    }
    break;

    case 20:
    Label28->Font->Style=TFontStyles();
    Label29->Font->Style=TFontStyles()<<fsBold;
    command="*MI3";
    if(Send(hPort,command.Length(),command.c_str()))
      goto err;
    clrb();
    ReadFile(hPort,&str,255,&iRead,NULL);
    sscanf(str,"PORT3: %d\n", &val);
    if(!(CheckBox44->Checked))
    {
      if(val&0x01)
        CheckBox39->Checked=true;
      else
        CheckBox39->Checked=false;
      if(val&0x02)
        CheckBox38->Checked=true;
      else
        CheckBox38->Checked=false;
      if(val&0x04)
        CheckBox37->Checked=true;
      else
        CheckBox37->Checked=false;
      if(val&0x08)
        CheckBox36->Checked=true;
      else
        CheckBox36->Checked=false;
      if(val&0x10)
        CheckBox35->Checked=true;
      else
        CheckBox35->Checked=false;
      if(val&0x20)
        CheckBox34->Checked=true;
      else
        CheckBox34->Checked=false;
      if(val&0x40)
        CheckBox33->Checked=true;
      else
        CheckBox33->Checked=false;
      if(val&0x80)
        CheckBox32->Checked=true;
      else
        CheckBox32->Checked=false;
    }
    break;

    case 21:
    Label29->Font->Style=TFontStyles();
    Label25->Font->Style=TFontStyles()<<fsBold;
    val1=0;
    val2=0;
    val1|=(CheckBox22->Checked)?0x01:0x00;
    val1|=(CheckBox40->Checked)?0x02:0x00;
    val1|=(CheckBox42->Checked)?0x04:0x00;
    val1|=(CheckBox44->Checked)?0x08:0x00;
    while(val1>9)
    {
      val1-=10;
      val2++;
    }
    command="*SD"+IntToStr(val2)+IntToStr(val1);

    if(Send(hPort,command.Length(),command.c_str()))
      goto err;
    clrb();
    ReadFile(hPort,&str,255,&iRead,NULL);

    if(CheckBox22->Checked)
    {
      val1=0;
      val2=0;
      val3=0;
      val1|=(CheckBox6->Checked)?0x01:0x00;
      val1|=(CheckBox12->Checked)?0x02:0x00;
      val1|=(CheckBox11->Checked)?0x04:0x00;
      val1|=(CheckBox10->Checked)?0x08:0x00;
      val1|=(CheckBox9->Checked)?0x10:0x00;
      val1|=(CheckBox8->Checked)?0x20:0x00;
      val1|=(CheckBox7->Checked)?0x40:0x00;
      val1|=(CheckBox5->Checked)?0x80:0x00;
      while(val1>99)
      {
        val1-=100;
        val2++;
      }
      while(val1>9)
      {
        val1-=10;
        val3++;
      }
      command="*SI0"+IntToStr(val2)+IntToStr(val3)+IntToStr(val1);
      if(Send(hPort,command.Length(),command.c_str()))
        goto err;
      clrb();
      ReadFile(hPort,&str,255,&iRead,NULL);
    }

    if(CheckBox40->Checked)
    {
      val1=0;
      val2=0;
      val3=0;
      val1|=(CheckBox21->Checked)?0x01:0x00;
      val1|=(CheckBox20->Checked)?0x02:0x00;
      val1|=(CheckBox19->Checked)?0x04:0x00;
      val1|=(CheckBox18->Checked)?0x08:0x00;
      val1|=(CheckBox17->Checked)?0x10:0x00;
      val1|=(CheckBox16->Checked)?0x20:0x00;
      val1|=(CheckBox15->Checked)?0x40:0x00;
      val1|=(CheckBox14->Checked)?0x80:0x00;
      while(val1>99)
      {
        val1-=100;
        val2++;
      }
      while(val1>9)
      {
        val1-=10;
        val3++;
      }
      command="*SI1"+IntToStr(val2)+IntToStr(val3)+IntToStr(val1);
      if(Send(hPort,command.Length(),command.c_str()))
        goto err;
      clrb();
      ReadFile(hPort,&str,255,&iRead,NULL);
    }

    if(CheckBox42->Checked)
    {
      val1=0;
      val2=0;
      val3=0;
      val1|=(CheckBox30->Checked)?0x01:0x00;
      val1|=(CheckBox29->Checked)?0x02:0x00;
      val1|=(CheckBox28->Checked)?0x04:0x00;
      val1|=(CheckBox27->Checked)?0x08:0x00;
      val1|=(CheckBox26->Checked)?0x10:0x00;
      val1|=(CheckBox25->Checked)?0x20:0x00;
      val1|=(CheckBox24->Checked)?0x40:0x00;
      val1|=(CheckBox23->Checked)?0x80:0x00;
      while(val1>99)
      {
        val1-=100;
        val2++;
      }
      while(val1>9)
      {
        val1-=10;
        val3++;
      }
      command="*SI2"+IntToStr(val2)+IntToStr(val3)+IntToStr(val1);
      if(Send(hPort,command.Length(),command.c_str()))
        goto err;
      clrb();
      ReadFile(hPort,&str,255,&iRead,NULL);
    }

    if(CheckBox44->Checked)
    {
      val1=0;
      val2=0;
      val3=0;
      val1|=(CheckBox39->Checked)?0x01:0x00;
      val1|=(CheckBox38->Checked)?0x02:0x00;
      val1|=(CheckBox37->Checked)?0x04:0x00;
      val1|=(CheckBox36->Checked)?0x08:0x00;
      val1|=(CheckBox35->Checked)?0x10:0x00;
      val1|=(CheckBox34->Checked)?0x20:0x00;
      val1|=(CheckBox33->Checked)?0x40:0x00;
      val1|=(CheckBox32->Checked)?0x80:0x00;
      while(val1>99)
      {
        val1-=100;
        val2++;
      }
      while(val1>9)
      {
        val1-=10;
        val3++;
      }
       command="*SI3"+IntToStr(val2)+IntToStr(val3)+IntToStr(val1);
      if(Send(hPort,command.Length(),command.c_str()))
        goto err;
      clrb();
      ReadFile(hPort,&str,255,&iRead,NULL);
    }
    break;

    case 22:
    if(sem1)
    {
    if(Edit41->Text.Length())
    {
      Edit41->Font->Color=clWindowText;
      for(val1=0;val1<Edit41->Text.Length();val1++)
        if((Edit41->Text.c_str()[val1]<'0')||(Edit41->Text.c_str()[val1]>'9'))
          Edit41->Font->Color=clRed;
      if(Edit41->Text.Length()>3)
        Edit41->Font->Color=clRed;
    }
    else
      Edit41->Font->Color=clRed;

    if(Edit54->Text.Length())
    {
      Edit54->Font->Color=clWindowText;
      for(val1=0;val1<Edit54->Text.Length();val1++)
        if((Edit54->Text.c_str()[val1]<'0')||(Edit54->Text.c_str()[val1]>'9'))
          Edit54->Font->Color=clRed;
      if(Edit54->Text.Length()>4)
        Edit54->Font->Color=clRed;
    }
    else
      Edit54->Font->Color=clRed;

    if((Edit41->Font->Color==clWindowText)&&(Edit54->Font->Color==clWindowText))
    {
      command="*SS";
      if(Edit41->Text.Length()<3)
        command+="0";
      if(Edit41->Text.Length()<2)
        command+="0";
      command+=Edit41->Text;
      if(Edit54->Text.Length()<4)
        command+="0";
      if(Edit54->Text.Length()<3)
        command+="0";
      command+=(Edit54->Text).Delete(Edit54->Text.Length()-1,1);
      //Label47->Caption=command;
      if(Send(hPort,command.Length(),command.c_str()))
        goto err;
      clrb();
      ReadFile(hPort,&str,255,&iRead,NULL);
      sscanf(str,"Set SIN OK. AMP: %s FREQ: %s\n", &a ,&b);
      Edit41->Text=AnsiString(a);
      Edit54->Text=AnsiString(b);
    }
    sem1=false;
    }
    break;

    case 23:
    if(sem2)
    {
    if(Edit47->Text.Length())
    {
      Edit47->Font->Color=clWindowText;
      for(val1=0;val1<Edit47->Text.Length();val1++)
        if((Edit47->Text.c_str()[val1]<'0')||(Edit47->Text.c_str()[val1]>'9'))
          Edit47->Font->Color=clRed;
      if(Edit47->Text.Length()>3)
        Edit47->Font->Color=clRed;
    }
    else
      Edit47->Font->Color=clRed;

    if(Edit59->Text.Length())
    {
      Edit59->Font->Color=clWindowText;
      for(val1=0;val1<Edit59->Text.Length();val1++)
        if((Edit59->Text.c_str()[val1]<'0')||(Edit59->Text.c_str()[val1]>'9'))
          Edit59->Font->Color=clRed;
      if(Edit59->Text.Length()>3)
        Edit59->Font->Color=clRed;
    }
    else
      Edit59->Font->Color=clRed;

    if((Edit47->Font->Color==clWindowText)&&(Edit59->Font->Color==clWindowText))
    {
      command="*SQ";
      if(Edit47->Text.Length()<3)
        command+="0";
      if(Edit47->Text.Length()<2)
        command+="0";
      command+=Edit47->Text;
      if(Edit59->Text.Length()<3)
        command+="0";
      if(Edit59->Text.Length()<2)
        command+="0";
      command+=Edit59->Text;
      //Label47->Caption=command;
      if(Send(hPort,command.Length(),command.c_str()))
        goto err;
      clrb();
      ReadFile(hPort,&str,255,&iRead,NULL);
      sscanf(str,"Set SQR OK. AMP: %s FREQ: %s\n", &a ,&b);
      Edit47->Text=AnsiString(a);
      Edit59->Text=AnsiString(b);
    }
    sem2=false;
    }
    break;

    case 24:
    if(sem3)
    {
    if(Edit66->Text.Length())
    {
      Edit66->Font->Color=clWindowText;
      for(val1=0;val1<Edit66->Text.Length();val1++)
        if((Edit66->Text.c_str()[val1]<'0')||(Edit66->Text.c_str()[val1]>'9'))
          Edit66->Font->Color=clRed;
      if(Edit66->Text.Length()>4)
        Edit66->Font->Color=clRed;
    }
    else
      Edit66->Font->Color=clRed;

    if(Edit74->Text.Length())
    {
      Edit74->Font->Color=clWindowText;
      for(val1=0;val1<Edit74->Text.Length();val1++)
        if((Edit74->Text.c_str()[val1]<'0')||(Edit74->Text.c_str()[val1]>'9'))
          Edit74->Font->Color=clRed;
      if(Edit74->Text.Length()>4)
        Edit74->Font->Color=clRed;
    }
    else
      Edit74->Font->Color=clRed;

    if(Edit75->Text.Length())
    {
      Edit75->Font->Color=clWindowText;
      for(val1=0;val1<Edit75->Text.Length();val1++)
        if((Edit75->Text.c_str()[val1]<'0')||(Edit75->Text.c_str()[val1]>'9'))
          Edit75->Font->Color=clRed;
      if(Edit75->Text.Length()>4)
        Edit75->Font->Color=clRed;
    }
    else
      Edit75->Font->Color=clRed;

    if(Edit76->Text.Length())
    {
      Edit76->Font->Color=clWindowText;
      for(val1=0;val1<Edit76->Text.Length();val1++)
        if((Edit76->Text.c_str()[val1]<'0')||(Edit76->Text.c_str()[val1]>'9'))
          Edit76->Font->Color=clRed;
      if(Edit76->Text.Length()>4)
        Edit76->Font->Color=clRed;
    }
    else
      Edit76->Font->Color=clRed;

    if(Edit66->Font->Color==clWindowText)
    {
      command="*SV0";
      if(Edit66->Text.Length()<4)
        command+="0";
      if(Edit66->Text.Length()<3)
        command+="0";
      if(Edit66->Text.Length()<2)
        command+="0";
      command+=Edit66->Text;
      if(Send(hPort,command.Length(),command.c_str()))
        goto err;
      clrb();
      ReadFile(hPort,&str,255,&iRead,NULL);
    }

    if(Edit74->Font->Color==clWindowText)
    {
      command="*SV1";
      if(Edit74->Text.Length()<4)
        command+="0";
      if(Edit74->Text.Length()<3)
        command+="0";
      if(Edit74->Text.Length()<2)
        command+="0";
      command+=Edit74->Text;
      if(Send(hPort,command.Length(),command.c_str()))
        goto err;
      clrb();
      ReadFile(hPort,&str,255,&iRead,NULL);
    }

    if(Edit75->Font->Color==clWindowText)
    {
      command="*SV2";
      if(Edit75->Text.Length()<4)
        command+="0";
      if(Edit75->Text.Length()<3)
        command+="0";
      if(Edit75->Text.Length()<2)
        command+="0";
      command+=Edit75->Text;
      if(Send(hPort,command.Length(),command.c_str()))
        goto err;
      clrb();
      ReadFile(hPort,&str,255,&iRead,NULL);
    }

    if(Edit76->Font->Color==clWindowText)
    {
      command="*SV3";
      if(Edit76->Text.Length()<4)
        command+="0";
      if(Edit76->Text.Length()<3)
        command+="0";
      if(Edit76->Text.Length()<2)
        command+="0";
      command+=Edit76->Text;
      if(Send(hPort,command.Length(),command.c_str()))
        goto err;
      clrb();
      ReadFile(hPort,&str,255,&iRead,NULL);
    }

    sem3=false;
    }
    break;


    default:
    break;
  }

  num++;
  if(num==25)
    num=0;
  return;
err:
  Label47->Caption="Ошибка передачи команды";
  Label47->Visible=true;
  Timer1->Enabled=false;
  return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
  sem3=true;
//  num=24;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
  sem1=true;
//  num=22;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
  sem2=true;
//  num=23;
}
//---------------------------------------------------------------------------

