//---------------------------------------------------------------------------
#ifndef RS232UH
#define RS232UH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
#include <DBCtrls.hpp>
#include <Graphics.hpp>
#include <Mask.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TButton *Button1;
    TButton *Button2;
    TRadioGroup *RadioGroup1;
    TRadioButton *RadioButton1;
    TRadioButton *RadioButton2;
    TRadioButton *RadioButton3;
    TRadioButton *RadioButton4;
    TButton *Button3;
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox4;
	TLabel *Label1;
        TLabel *Label2;
        TEdit *Edit3;
        TListBox *ListBox1;
        TListBox *ListBox2;
        TTimer *Timer1;
        TListBox *ListBox3;
        TGroupBox *GroupBox2;
        TLabel *Label3;
        TGroupBox *GroupBox3;
        TListBox *ListBox4;
        TLabel *Label5;
        TEdit *Edit1;
        TLabel *Label4;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall Quit(TObject *Sender);
    void __fastcall Exit(TObject *Sender);
    
    
    void __fastcall RadioButton1Click(TObject *Sender);
    void __fastcall RadioButton2Click(TObject *Sender);
    void __fastcall RadioButton3Click(TObject *Sender);
    void __fastcall RadioButton4Click(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);

        void __fastcall Edit3Change(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall ListBox2Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
