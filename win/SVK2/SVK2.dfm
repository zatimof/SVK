object Form1: TForm1
  Left = 231
  Top = 106
  Width = 1008
  Height = 524
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label10: TLabel
    Left = 16
    Top = 128
    Width = 95
    Height = 13
    Caption = #1050#1072#1085#1072#1083' 0 [RMS 10V]'
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 985
    Height = 57
    Caption = #1057#1080#1089#1090#1077#1084#1072
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 24
      Width = 50
      Height = 13
      Caption = #1057#1054#1052'-'#1087#1086#1088#1090
    end
    object Label2: TLabel
      Left = 176
      Top = 24
      Width = 48
      Height = 13
      Caption = #1057#1082#1086#1088#1086#1089#1090#1100
    end
    object Label41: TLabel
      Left = 504
      Top = 16
      Width = 56
      Height = 16
      Caption = 'Label41'
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentColor = False
      ParentFont = False
    end
    object Label47: TLabel
      Left = 504
      Top = 32
      Width = 56
      Height = 16
      Caption = 'Label47'
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentColor = False
      ParentFont = False
      Visible = False
    end
    object ComboBox1: TComboBox
      Left = 72
      Top = 24
      Width = 89
      Height = 21
      ItemHeight = 13
      TabOrder = 0
    end
    object ComboBox2: TComboBox
      Left = 232
      Top = 24
      Width = 89
      Height = 21
      ItemHeight = 13
      TabOrder = 1
    end
    object Button1: TButton
      Left = 336
      Top = 24
      Width = 75
      Height = 25
      Caption = #1040#1074#1090#1086#1087#1086#1080#1089#1082
      TabOrder = 2
    end
    object Button2: TButton
      Left = 424
      Top = 24
      Width = 75
      Height = 25
      Caption = #1055#1086#1076#1082#1083#1102#1095#1080#1090#1100
      TabOrder = 3
      OnClick = Button2Click
    end
    object Button3: TButton
      Left = 896
      Top = 24
      Width = 75
      Height = 25
      Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
      TabOrder = 4
      OnClick = Button3Click
    end
    object Button4: TButton
      Left = 808
      Top = 24
      Width = 75
      Height = 25
      Caption = #1042#1099#1093#1086#1076
      TabOrder = 5
      OnClick = Button4Click
    end
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 72
    Width = 561
    Height = 417
    Caption = #1048#1079#1084#1077#1088#1077#1085#1080#1103
    TabOrder = 1
    object Label3: TLabel
      Left = 8
      Top = 32
      Width = 95
      Height = 13
      Caption = #1050#1072#1085#1072#1083' 0 [RMS 10V]'
    end
    object Label5: TLabel
      Left = 120
      Top = 16
      Width = 59
      Height = 13
      Caption = 'U[RMS], '#1084#1042
    end
    object Label6: TLabel
      Left = 192
      Top = 16
      Width = 50
      Height = 13
      Caption = 'U[DC], '#1084#1042
    end
    object Label4: TLabel
      Left = 264
      Top = 16
      Width = 64
      Height = 13
      Caption = 'U[AMP+], '#1084#1042
    end
    object Label7: TLabel
      Left = 336
      Top = 16
      Width = 61
      Height = 13
      Caption = 'U[AMP-], '#1084#1042
    end
    object Label8: TLabel
      Left = 424
      Top = 16
      Width = 24
      Height = 13
      Caption = 'F, '#1043#1094
    end
    object Label9: TLabel
      Left = 480
      Top = 16
      Width = 60
      Height = 13
      Caption = #1042#1072#1083#1080#1076#1085#1086#1089#1090#1100
    end
    object Label11: TLabel
      Left = 8
      Top = 56
      Width = 89
      Height = 13
      Caption = #1050#1072#1085#1072#1083' 1 [RMS 1V]'
    end
    object Label12: TLabel
      Left = 8
      Top = 80
      Width = 92
      Height = 13
      Caption = #1050#1072#1085#1072#1083' 2 [DC 100V]'
    end
    object Label13: TLabel
      Left = 8
      Top = 104
      Width = 86
      Height = 13
      Caption = #1050#1072#1085#1072#1083' 3 [DC 10V]'
    end
    object Label14: TLabel
      Left = 8
      Top = 128
      Width = 82
      Height = 13
      Caption = #1050#1072#1085#1072#1083' 4 [DC Ext]'
    end
    object Label15: TLabel
      Left = 8
      Top = 152
      Width = 95
      Height = 13
      Caption = #1050#1072#1085#1072#1083' 5 [VREF OS]'
    end
    object Label16: TLabel
      Left = 8
      Top = 176
      Width = 80
      Height = 13
      Caption = #1050#1072#1085#1072#1083' 6 [DAC 4]'
    end
    object Label17: TLabel
      Left = 8
      Top = 200
      Width = 78
      Height = 13
      Caption = #1050#1072#1085#1072#1083' 7 [PDAC]'
    end
    object Label18: TLabel
      Left = 8
      Top = 224
      Width = 96
      Height = 13
      Caption = #1050#1072#1085#1072#1083' 8 [REF MAX]'
    end
    object Label19: TLabel
      Left = 8
      Top = 248
      Width = 93
      Height = 13
      Caption = #1050#1072#1085#1072#1083' 9 [REF MIN]'
    end
    object Label20: TLabel
      Left = 8
      Top = 272
      Width = 85
      Height = 13
      Caption = #1050#1072#1085#1072#1083' 10 [TEMP]'
    end
    object Label21: TLabel
      Left = 8
      Top = 296
      Width = 85
      Height = 13
      Caption = #1050#1072#1085#1072#1083' 11 [Vcc/2]'
    end
    object Label22: TLabel
      Left = 16
      Top = 384
      Width = 80
      Height = 13
      Caption = #1058#1077#1084#1087#1077#1088#1072#1090#1091#1088#1072', '#1057
    end
    object Label23: TLabel
      Left = 344
      Top = 336
      Width = 47
      Height = 13
      Caption = 'Uvcc, '#1084#1042
    end
    object Label24: TLabel
      Left = 8
      Top = 336
      Width = 90
      Height = 13
      Caption = #1042#1077#1088#1089#1080#1103' '#1055#1054' '#1055#1051#1048#1057
    end
    object Label42: TLabel
      Left = 24
      Top = 360
      Width = 75
      Height = 13
      Caption = #1042#1077#1088#1089#1080#1103' '#1055#1054' '#1052#1050
    end
    object Label43: TLabel
      Left = 200
      Top = 336
      Width = 47
      Height = 13
      Caption = 'Uref+, '#1084#1042
    end
    object Label44: TLabel
      Left = 200
      Top = 384
      Width = 44
      Height = 13
      Caption = 'Uref-, '#1084#1042
    end
    object Label45: TLabel
      Left = 200
      Top = 360
      Width = 47
      Height = 13
      Caption = 'Uref0, '#1084#1042
    end
    object Label46: TLabel
      Left = 336
      Top = 360
      Width = 64
      Height = 13
      Caption = #1057#1072#1084#1086#1090#1077#1089#1090#1080#1088'.'
    end
    object Edit1: TEdit
      Left = 120
      Top = 32
      Width = 65
      Height = 21
      TabOrder = 0
    end
    object Edit2: TEdit
      Left = 192
      Top = 32
      Width = 65
      Height = 21
      TabOrder = 1
    end
    object Edit3: TEdit
      Left = 264
      Top = 32
      Width = 65
      Height = 21
      TabOrder = 2
    end
    object Edit4: TEdit
      Left = 336
      Top = 32
      Width = 65
      Height = 21
      TabOrder = 3
    end
    object Edit5: TEdit
      Left = 408
      Top = 32
      Width = 65
      Height = 21
      TabOrder = 4
    end
    object Edit6: TEdit
      Left = 480
      Top = 32
      Width = 65
      Height = 21
      TabOrder = 5
    end
    object Edit7: TEdit
      Left = 120
      Top = 56
      Width = 65
      Height = 21
      TabOrder = 6
    end
    object Edit8: TEdit
      Left = 192
      Top = 56
      Width = 65
      Height = 21
      TabOrder = 7
    end
    object Edit9: TEdit
      Left = 264
      Top = 56
      Width = 65
      Height = 21
      TabOrder = 8
    end
    object Edit10: TEdit
      Left = 336
      Top = 56
      Width = 65
      Height = 21
      TabOrder = 9
    end
    object Edit11: TEdit
      Left = 408
      Top = 56
      Width = 65
      Height = 21
      TabOrder = 10
    end
    object Edit12: TEdit
      Left = 480
      Top = 56
      Width = 65
      Height = 21
      TabOrder = 11
    end
    object Edit13: TEdit
      Left = 120
      Top = 80
      Width = 65
      Height = 21
      TabOrder = 12
    end
    object Edit14: TEdit
      Left = 192
      Top = 80
      Width = 65
      Height = 21
      TabOrder = 13
    end
    object Edit15: TEdit
      Left = 264
      Top = 80
      Width = 65
      Height = 21
      TabOrder = 14
    end
    object Edit16: TEdit
      Left = 336
      Top = 80
      Width = 65
      Height = 21
      TabOrder = 15
    end
    object Edit17: TEdit
      Left = 480
      Top = 80
      Width = 65
      Height = 21
      TabOrder = 16
    end
    object Edit18: TEdit
      Left = 408
      Top = 80
      Width = 65
      Height = 21
      TabOrder = 17
    end
    object Edit19: TEdit
      Left = 120
      Top = 104
      Width = 65
      Height = 21
      TabOrder = 18
    end
    object Edit20: TEdit
      Left = 192
      Top = 104
      Width = 65
      Height = 21
      TabOrder = 19
    end
    object Edit21: TEdit
      Left = 264
      Top = 104
      Width = 65
      Height = 21
      TabOrder = 20
    end
    object Edit22: TEdit
      Left = 336
      Top = 104
      Width = 65
      Height = 21
      TabOrder = 21
    end
    object Edit23: TEdit
      Left = 408
      Top = 104
      Width = 65
      Height = 21
      TabOrder = 22
    end
    object Edit24: TEdit
      Left = 480
      Top = 104
      Width = 65
      Height = 21
      TabOrder = 23
    end
    object Edit25: TEdit
      Left = 120
      Top = 128
      Width = 65
      Height = 21
      TabOrder = 24
    end
    object Edit26: TEdit
      Left = 192
      Top = 128
      Width = 65
      Height = 21
      TabOrder = 25
    end
    object Edit27: TEdit
      Left = 264
      Top = 128
      Width = 65
      Height = 21
      TabOrder = 26
    end
    object Edit28: TEdit
      Left = 336
      Top = 128
      Width = 65
      Height = 21
      TabOrder = 27
    end
    object Edit30: TEdit
      Left = 480
      Top = 128
      Width = 65
      Height = 21
      TabOrder = 28
    end
    object Edit31: TEdit
      Left = 120
      Top = 152
      Width = 65
      Height = 21
      TabOrder = 29
    end
    object Edit32: TEdit
      Left = 192
      Top = 152
      Width = 65
      Height = 21
      TabOrder = 30
    end
    object Edit33: TEdit
      Left = 264
      Top = 152
      Width = 65
      Height = 21
      TabOrder = 31
    end
    object Edit34: TEdit
      Left = 336
      Top = 152
      Width = 65
      Height = 21
      TabOrder = 32
    end
    object Edit36: TEdit
      Left = 480
      Top = 152
      Width = 65
      Height = 21
      TabOrder = 33
    end
    object Edit37: TEdit
      Left = 120
      Top = 176
      Width = 65
      Height = 21
      TabOrder = 34
    end
    object Edit38: TEdit
      Left = 192
      Top = 176
      Width = 65
      Height = 21
      TabOrder = 35
    end
    object Edit40: TEdit
      Left = 336
      Top = 176
      Width = 65
      Height = 21
      TabOrder = 36
    end
    object Edit42: TEdit
      Left = 480
      Top = 176
      Width = 65
      Height = 21
      TabOrder = 37
    end
    object Edit43: TEdit
      Left = 120
      Top = 200
      Width = 65
      Height = 21
      TabOrder = 38
    end
    object Edit44: TEdit
      Left = 192
      Top = 200
      Width = 65
      Height = 21
      TabOrder = 39
    end
    object Edit45: TEdit
      Left = 264
      Top = 200
      Width = 65
      Height = 21
      TabOrder = 40
    end
    object Edit46: TEdit
      Left = 336
      Top = 200
      Width = 65
      Height = 21
      TabOrder = 41
    end
    object Edit48: TEdit
      Left = 264
      Top = 176
      Width = 65
      Height = 21
      TabOrder = 42
    end
    object Edit49: TEdit
      Left = 480
      Top = 200
      Width = 65
      Height = 21
      TabOrder = 43
    end
    object Edit50: TEdit
      Left = 120
      Top = 224
      Width = 65
      Height = 21
      TabOrder = 44
    end
    object Edit51: TEdit
      Left = 192
      Top = 224
      Width = 65
      Height = 21
      TabOrder = 45
    end
    object Edit52: TEdit
      Left = 264
      Top = 224
      Width = 65
      Height = 21
      TabOrder = 46
    end
    object Edit53: TEdit
      Left = 336
      Top = 224
      Width = 65
      Height = 21
      TabOrder = 47
    end
    object Edit55: TEdit
      Left = 120
      Top = 248
      Width = 65
      Height = 21
      TabOrder = 48
    end
    object Edit56: TEdit
      Left = 192
      Top = 248
      Width = 65
      Height = 21
      TabOrder = 49
    end
    object Edit57: TEdit
      Left = 480
      Top = 224
      Width = 65
      Height = 21
      TabOrder = 50
    end
    object Edit58: TEdit
      Left = 264
      Top = 248
      Width = 65
      Height = 21
      TabOrder = 51
    end
    object Edit60: TEdit
      Left = 336
      Top = 248
      Width = 65
      Height = 21
      TabOrder = 52
    end
    object Edit61: TEdit
      Left = 480
      Top = 248
      Width = 65
      Height = 21
      TabOrder = 53
    end
    object Edit62: TEdit
      Left = 120
      Top = 272
      Width = 65
      Height = 21
      TabOrder = 54
    end
    object Edit63: TEdit
      Left = 192
      Top = 272
      Width = 65
      Height = 21
      TabOrder = 55
    end
    object Edit64: TEdit
      Left = 264
      Top = 272
      Width = 65
      Height = 21
      TabOrder = 56
    end
    object Edit65: TEdit
      Left = 336
      Top = 272
      Width = 65
      Height = 21
      TabOrder = 57
    end
    object Edit67: TEdit
      Left = 480
      Top = 272
      Width = 65
      Height = 21
      TabOrder = 58
    end
    object Edit68: TEdit
      Left = 120
      Top = 296
      Width = 65
      Height = 21
      TabOrder = 59
    end
    object Edit69: TEdit
      Left = 192
      Top = 296
      Width = 65
      Height = 21
      TabOrder = 60
    end
    object Edit70: TEdit
      Left = 264
      Top = 296
      Width = 65
      Height = 21
      TabOrder = 61
    end
    object Edit71: TEdit
      Left = 336
      Top = 296
      Width = 65
      Height = 21
      TabOrder = 62
    end
    object Edit73: TEdit
      Left = 480
      Top = 296
      Width = 65
      Height = 21
      TabOrder = 63
    end
    object Edit72: TEdit
      Left = 120
      Top = 384
      Width = 65
      Height = 21
      TabOrder = 64
    end
    object Edit29: TEdit
      Left = 264
      Top = 336
      Width = 65
      Height = 21
      TabOrder = 65
    end
    object Edit35: TEdit
      Left = 120
      Top = 336
      Width = 65
      Height = 21
      TabOrder = 66
    end
    object Edit79: TEdit
      Left = 120
      Top = 360
      Width = 65
      Height = 21
      TabOrder = 67
    end
    object Edit80: TEdit
      Left = 264
      Top = 360
      Width = 65
      Height = 21
      TabOrder = 68
    end
    object Edit81: TEdit
      Left = 408
      Top = 336
      Width = 65
      Height = 21
      TabOrder = 69
    end
    object Edit82: TEdit
      Left = 264
      Top = 384
      Width = 65
      Height = 21
      TabOrder = 70
    end
    object Edit83: TEdit
      Left = 408
      Top = 360
      Width = 65
      Height = 21
      TabOrder = 71
    end
  end
  object GroupBox3: TGroupBox
    Left = 576
    Top = 72
    Width = 417
    Height = 417
    Caption = #1059#1089#1090#1072#1085#1086#1074#1082#1080
    TabOrder = 2
    object GroupBox4: TGroupBox
      Left = 8
      Top = 16
      Width = 89
      Height = 121
      Caption = #1057#1073#1088#1086#1089
      TabOrder = 0
      object CheckBox1: TCheckBox
        Left = 16
        Top = 16
        Width = 57
        Height = 17
        Caption = 'USB'
        TabOrder = 0
      end
      object CheckBox2: TCheckBox
        Left = 16
        Top = 32
        Width = 57
        Height = 17
        Caption = 'DACS'
        TabOrder = 1
      end
      object CheckBox3: TCheckBox
        Left = 16
        Top = 48
        Width = 57
        Height = 17
        Caption = 'SIN'
        TabOrder = 2
      end
      object CheckBox4: TCheckBox
        Left = 16
        Top = 64
        Width = 57
        Height = 17
        Caption = 'SPI'
        TabOrder = 3
      end
    end
    object GroupBox5: TGroupBox
      Left = 104
      Top = 16
      Width = 305
      Height = 121
      Caption = #1055#1086#1088#1090#1099' '#1042'/'#1042
      TabOrder = 1
      object Label25: TLabel
        Left = 184
        Top = 16
        Width = 32
        Height = 13
        Caption = #1042#1099#1093#1086#1076
      end
      object Label26: TLabel
        Left = 8
        Top = 32
        Width = 34
        Height = 13
        Caption = #1055#1086#1088#1090' 1'
      end
      object Label27: TLabel
        Left = 8
        Top = 48
        Width = 34
        Height = 13
        Caption = #1055#1086#1088#1090' 2'
      end
      object Label28: TLabel
        Left = 8
        Top = 64
        Width = 34
        Height = 13
        Caption = #1055#1086#1088#1090' 3'
      end
      object Label29: TLabel
        Left = 8
        Top = 80
        Width = 34
        Height = 13
        Caption = #1055#1086#1088#1090' 4'
      end
      object Label30: TLabel
        Left = 48
        Top = 16
        Width = 120
        Height = 13
        Caption = ' 7   6   5   4   3    2    1   0'
      end
      object CheckBox5: TCheckBox
        Left = 48
        Top = 32
        Width = 17
        Height = 17
        TabOrder = 0
      end
      object CheckBox7: TCheckBox
        Left = 64
        Top = 32
        Width = 17
        Height = 17
        TabOrder = 1
      end
      object CheckBox8: TCheckBox
        Left = 80
        Top = 32
        Width = 17
        Height = 17
        TabOrder = 2
      end
      object CheckBox9: TCheckBox
        Left = 96
        Top = 32
        Width = 17
        Height = 17
        TabOrder = 3
      end
      object CheckBox10: TCheckBox
        Left = 112
        Top = 32
        Width = 17
        Height = 17
        TabOrder = 4
      end
      object CheckBox11: TCheckBox
        Left = 128
        Top = 32
        Width = 17
        Height = 17
        TabOrder = 5
      end
      object CheckBox12: TCheckBox
        Left = 144
        Top = 32
        Width = 17
        Height = 17
        TabOrder = 6
      end
      object CheckBox6: TCheckBox
        Left = 160
        Top = 32
        Width = 17
        Height = 17
        TabOrder = 7
      end
      object CheckBox14: TCheckBox
        Left = 48
        Top = 48
        Width = 17
        Height = 17
        TabOrder = 8
      end
      object CheckBox15: TCheckBox
        Left = 64
        Top = 48
        Width = 17
        Height = 17
        TabOrder = 9
      end
      object CheckBox16: TCheckBox
        Left = 80
        Top = 48
        Width = 17
        Height = 17
        TabOrder = 10
      end
      object CheckBox17: TCheckBox
        Left = 96
        Top = 48
        Width = 17
        Height = 17
        TabOrder = 11
      end
      object CheckBox18: TCheckBox
        Left = 112
        Top = 48
        Width = 17
        Height = 17
        TabOrder = 12
      end
      object CheckBox19: TCheckBox
        Left = 128
        Top = 48
        Width = 17
        Height = 17
        TabOrder = 13
      end
      object CheckBox20: TCheckBox
        Left = 144
        Top = 48
        Width = 17
        Height = 17
        TabOrder = 14
      end
      object CheckBox21: TCheckBox
        Left = 160
        Top = 48
        Width = 17
        Height = 17
        TabOrder = 15
      end
      object CheckBox23: TCheckBox
        Left = 48
        Top = 64
        Width = 17
        Height = 17
        TabOrder = 16
      end
      object CheckBox24: TCheckBox
        Left = 64
        Top = 64
        Width = 17
        Height = 17
        TabOrder = 17
      end
      object CheckBox25: TCheckBox
        Left = 80
        Top = 64
        Width = 17
        Height = 17
        TabOrder = 18
      end
      object CheckBox26: TCheckBox
        Left = 96
        Top = 64
        Width = 17
        Height = 17
        TabOrder = 19
      end
      object CheckBox27: TCheckBox
        Left = 112
        Top = 64
        Width = 17
        Height = 17
        TabOrder = 20
      end
      object CheckBox28: TCheckBox
        Left = 128
        Top = 64
        Width = 17
        Height = 17
        TabOrder = 21
      end
      object CheckBox29: TCheckBox
        Left = 144
        Top = 64
        Width = 17
        Height = 17
        TabOrder = 22
      end
      object CheckBox30: TCheckBox
        Left = 160
        Top = 64
        Width = 17
        Height = 17
        TabOrder = 23
      end
      object CheckBox32: TCheckBox
        Left = 48
        Top = 80
        Width = 17
        Height = 17
        TabOrder = 24
      end
      object CheckBox33: TCheckBox
        Left = 64
        Top = 80
        Width = 17
        Height = 17
        TabOrder = 25
      end
      object CheckBox34: TCheckBox
        Left = 80
        Top = 80
        Width = 17
        Height = 17
        TabOrder = 26
      end
      object CheckBox35: TCheckBox
        Left = 96
        Top = 80
        Width = 17
        Height = 17
        TabOrder = 27
      end
      object CheckBox36: TCheckBox
        Left = 112
        Top = 80
        Width = 17
        Height = 17
        TabOrder = 28
      end
      object CheckBox37: TCheckBox
        Left = 128
        Top = 80
        Width = 17
        Height = 17
        TabOrder = 29
      end
      object CheckBox38: TCheckBox
        Left = 144
        Top = 80
        Width = 17
        Height = 17
        TabOrder = 30
      end
      object CheckBox39: TCheckBox
        Left = 160
        Top = 80
        Width = 17
        Height = 17
        TabOrder = 31
      end
      object CheckBox22: TCheckBox
        Left = 192
        Top = 32
        Width = 17
        Height = 17
        TabOrder = 32
      end
      object CheckBox40: TCheckBox
        Left = 192
        Top = 48
        Width = 17
        Height = 17
        TabOrder = 33
      end
      object CheckBox42: TCheckBox
        Left = 192
        Top = 64
        Width = 17
        Height = 17
        TabOrder = 34
      end
      object CheckBox44: TCheckBox
        Left = 192
        Top = 80
        Width = 17
        Height = 17
        TabOrder = 35
      end
    end
    object GroupBox6: TGroupBox
      Left = 8
      Top = 144
      Width = 401
      Height = 153
      Caption = #1057#1080#1075#1085#1072#1083#1099
      TabOrder = 2
      object Label31: TLabel
        Left = 8
        Top = 24
        Width = 86
        Height = 13
        Caption = #1059#1088#1086#1074#1077#1085#1100' SIN, '#1084#1042
      end
      object Label32: TLabel
        Left = 8
        Top = 48
        Width = 81
        Height = 13
        Caption = #1063#1072#1089#1090#1086#1090#1072' SIN, '#1043#1094
      end
      object Label33: TLabel
        Left = 8
        Top = 72
        Width = 91
        Height = 13
        Caption = #1059#1088#1086#1074#1077#1085#1100' SQR, '#1084#1042
      end
      object Label34: TLabel
        Left = 8
        Top = 96
        Width = 92
        Height = 13
        Caption = #1063#1072#1089#1090#1086#1090#1072' SQR, '#1082#1043#1094
      end
      object Label35: TLabel
        Left = 224
        Top = 24
        Width = 82
        Height = 13
        Caption = #1059#1088#1086#1074#1077#1085#1100' U1, '#1084#1042
      end
      object Label36: TLabel
        Left = 224
        Top = 48
        Width = 82
        Height = 13
        Caption = #1059#1088#1086#1074#1077#1085#1100' U2, '#1084#1042
      end
      object Label37: TLabel
        Left = 224
        Top = 72
        Width = 82
        Height = 13
        Caption = #1059#1088#1086#1074#1077#1085#1100' U3, '#1084#1042
      end
      object Label38: TLabel
        Left = 224
        Top = 96
        Width = 82
        Height = 13
        Caption = #1059#1088#1086#1074#1077#1085#1100' U4, '#1084#1042
      end
      object Edit41: TEdit
        Left = 112
        Top = 20
        Width = 65
        Height = 21
        TabOrder = 0
      end
      object Edit47: TEdit
        Left = 112
        Top = 68
        Width = 65
        Height = 21
        TabOrder = 1
      end
      object Edit54: TEdit
        Left = 112
        Top = 44
        Width = 65
        Height = 21
        TabOrder = 2
      end
      object Edit59: TEdit
        Left = 112
        Top = 92
        Width = 65
        Height = 21
        TabOrder = 3
      end
      object Edit66: TEdit
        Left = 320
        Top = 20
        Width = 65
        Height = 21
        TabOrder = 4
      end
      object Edit74: TEdit
        Left = 320
        Top = 44
        Width = 65
        Height = 21
        TabOrder = 5
      end
      object Edit75: TEdit
        Left = 320
        Top = 68
        Width = 65
        Height = 21
        TabOrder = 6
      end
      object Edit76: TEdit
        Left = 320
        Top = 92
        Width = 65
        Height = 21
        TabOrder = 7
      end
      object Button5: TButton
        Left = 8
        Top = 120
        Width = 105
        Height = 25
        Caption = #1059#1089#1090#1072#1085#1086#1074#1080#1090#1100' SIN'
        TabOrder = 8
        OnClick = Button5Click
      end
      object Button7: TButton
        Left = 144
        Top = 120
        Width = 105
        Height = 25
        Caption = #1059#1089#1090#1072#1085#1086#1074#1080#1090#1100' SQR'
        TabOrder = 9
        OnClick = Button7Click
      end
      object Button8: TButton
        Left = 280
        Top = 120
        Width = 105
        Height = 25
        Caption = #1059#1089#1090#1072#1085#1086#1074#1080#1090#1100' U'
        TabOrder = 10
        OnClick = Button8Click
      end
    end
    object GroupBox7: TGroupBox
      Left = 8
      Top = 304
      Width = 401
      Height = 97
      Caption = #1055#1072#1084#1103#1090#1100
      TabOrder = 3
      object Label39: TLabel
        Left = 24
        Top = 16
        Width = 31
        Height = 13
        Caption = #1040#1076#1088#1077#1089
      end
      object Label40: TLabel
        Left = 88
        Top = 16
        Width = 41
        Height = 13
        Caption = #1044#1072#1085#1085#1099#1077
      end
      object Edit78: TEdit
        Left = 8
        Top = 36
        Width = 65
        Height = 21
        TabOrder = 0
      end
      object Edit77: TEdit
        Left = 80
        Top = 36
        Width = 65
        Height = 21
        TabOrder = 1
      end
      object RadioGroup1: TRadioGroup
        Left = 184
        Top = 16
        Width = 169
        Height = 57
        Caption = #1054#1087#1077#1088#1072#1094#1080#1103
        TabOrder = 2
      end
      object RadioButton1: TRadioButton
        Left = 192
        Top = 32
        Width = 89
        Height = 17
        Caption = 'EWEN/EWDS'
        Checked = True
        TabOrder = 3
        TabStop = True
      end
      object RadioButton2: TRadioButton
        Left = 192
        Top = 48
        Width = 65
        Height = 17
        Caption = 'WRITE'
        TabOrder = 4
      end
      object RadioButton3: TRadioButton
        Left = 288
        Top = 32
        Width = 57
        Height = 17
        Caption = 'READ'
        TabOrder = 5
      end
      object RadioButton4: TRadioButton
        Left = 288
        Top = 48
        Width = 57
        Height = 17
        Caption = 'ERASE'
        TabOrder = 6
      end
      object Button6: TButton
        Left = 40
        Top = 64
        Width = 75
        Height = 25
        Caption = #1042#1099#1087#1086#1083#1085#1080#1090#1100
        TabOrder = 7
      end
    end
  end
  object Timer1: TTimer
    Interval = 100
    OnTimer = Timer1Timer
    Left = 600
    Top = 24
  end
end
