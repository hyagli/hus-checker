object Form1: TForm1
  Left = 201
  Top = 123
  AlphaBlendValue = 128
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = '-'
  ClientHeight = 306
  ClientWidth = 470
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 149
    Top = 0
    Width = 321
    Height = 287
    Align = alRight
    Caption = 'Status'
    TabOrder = 0
    object Results: TMemo
      Left = 4
      Top = 13
      Width = 310
      Height = 272
      Hint = 'Double click to clear'
      TabStop = False
      Color = 8257405
      Font.Charset = ANSI_CHARSET
      Font.Color = 3372543
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ReadOnly = True
      ScrollBars = ssBoth
      ShowHint = True
      TabOrder = 0
      WantTabs = True
      OnChange = ResultsChange
      OnDblClick = ResultsDblClick
    end
  end
  object GroupBox2: TGroupBox
    Left = 0
    Top = 0
    Width = 149
    Height = 287
    Align = alLeft
    Caption = 'Tools'
    TabOrder = 1
    object Label5: TLabel
      Left = 8
      Top = 104
      Width = 116
      Height = 13
      Caption = 'Send Command to mIRC'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label6: TLabel
      Left = 8
      Top = 16
      Width = 68
      Height = 13
      Caption = 'Manual check'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label1: TLabel
      Left = 8
      Top = 200
      Width = 59
      Height = 13
      Caption = 'Special Files'
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = 11369795
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
    end
    object CommandButton: TButton
      Left = 32
      Top = 144
      Width = 75
      Height = 25
      Caption = 'Send'
      Default = True
      TabOrder = 0
      TabStop = False
      OnClick = CommandButtonClick
    end
    object CommEdit: TEdit
      Left = 8
      Top = 120
      Width = 121
      Height = 21
      Color = 16766935
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      Text = 'command'
      OnEnter = CommEditEnter
    end
    object ManualEdit: TEdit
      Left = 8
      Top = 32
      Width = 121
      Height = 21
      Color = 12566527
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      Text = 'url-pass'
      OnEnter = ManualEditEnter
    end
    object ManualButton: TButton
      Left = 32
      Top = 56
      Width = 75
      Height = 25
      Caption = 'Check'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      TabStop = False
      OnClick = ManualButtonClick
    end
    object SpecialBox: TComboBox
      Left = 8
      Top = 216
      Width = 121
      Height = 21
      AutoDropDown = True
      Style = csDropDownList
      Color = 11369795
      Font.Charset = DEFAULT_CHARSET
      Font.Color = 16512968
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemHeight = 13
      ItemIndex = 0
      ParentFont = False
      TabOrder = 4
      Text = 'regular'
      Items.Strings = (
        'regular'
        'elite'
        'god'
        'crackers')
    end
    object SpecialButton: TButton
      Left = 8
      Top = 241
      Width = 57
      Height = 25
      Caption = 'Check'
      TabOrder = 5
      OnClick = SpecialButtonClick
    end
    object StopSpecialButton: TButton
      Left = 72
      Top = 241
      Width = 57
      Height = 25
      Caption = 'Stop'
      Enabled = False
      TabOrder = 6
      OnClick = StopSpecialButtonClick
    end
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 287
    Width = 470
    Height = 19
    Panels = <>
    SimplePanel = True
    SimpleText = 'Idle'
  end
  object DdeConv: TDdeClientConv
    ConnectMode = ddeManual
    Left = 424
    Top = 48
  end
  object Check: TDdeServerItem
    Lines.Strings = (
      '')
    OnChange = CheckChange
    Left = 424
    Top = 16
  end
  object MainMenu1: TMainMenu
    Left = 424
    Top = 80
    object File1: TMenuItem
      Caption = 'File'
      object AddProxy1: TMenuItem
        Caption = 'Add Proxy'
        Hint = 'Adds the new proxies to the existing proxies'
        OnClick = AddProxy1Click
      end
      object OpenProxy1: TMenuItem
        Caption = 'Open Proxy'
        Hint = 
          'Open a proxy file of the form "server:port" sets the new proxy l' +
          'ist'
        OnClick = OpenProxy1Click
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Exit1: TMenuItem
        Caption = 'Exit'
        OnClick = Exit1Click
      end
    end
    object Edit1: TMenuItem
      Caption = 'Tools'
      object CheckFile1: TMenuItem
        Caption = 'Check Simple List'
        OnClick = CheckFile1Click
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object Options1: TMenuItem
        Caption = 'Options'
        OnClick = Options1Click
      end
    end
    object Help1: TMenuItem
      Caption = 'Help'
      object UserManual1: TMenuItem
        Caption = 'User Manual'
        ShortCut = 112
        OnClick = UserManual1Click
      end
      object About1: TMenuItem
        Caption = 'About'
        OnClick = About1Click
      end
    end
  end
  object OpenDialog: TOpenDialog
    Filter = 'All Files|*.*'
    Options = [ofPathMustExist, ofFileMustExist, ofEnableSizing]
    Left = 424
    Top = 112
  end
  object Exec: TDdeServerItem
    Lines.Strings = (
      '')
    OnChange = ExecChange
    Left = 392
    Top = 16
  end
  object SaveDialog: TSaveDialog
    Filter = 'All Files|*.*'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Title = 'Save The List file As'
    Left = 424
    Top = 144
  end
end
