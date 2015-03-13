object Options: TOptions
  Left = 246
  Top = 142
  ActiveControl = ThreadEdit
  AlphaBlendValue = 200
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'Options'
  ClientHeight = 249
  ClientWidth = 367
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl: TPageControl
    Left = 0
    Top = 0
    Width = 367
    Height = 209
    ActivePage = ConnectionPage
    Align = alTop
    TabIndex = 0
    TabOrder = 0
    object ConnectionPage: TTabSheet
      Caption = 'Connection'
      ImageIndex = 1
      object GroupBox1: TGroupBox
        Left = 3
        Top = 8
        Width = 342
        Height = 81
        Caption = 'Limits'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        object Label1: TLabel
          Left = 8
          Top = 19
          Width = 135
          Height = 13
          Hint = 'The maximum number of simultaneous threads working'
          Caption = 'Number of simultaneous jobs'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object Label2: TLabel
          Left = 8
          Top = 51
          Width = 80
          Height = 13
          Hint = 'Number of retry in case of error'
          Caption = 'Number of retries'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object ThreadEdit: TEdit
          Left = 176
          Top = 15
          Width = 31
          Height = 24
          Hint = 'The maximum number of simultaneous threads working'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ReadOnly = True
          TabOrder = 0
          Text = '10'
        end
        object UpDown1: TUpDown
          Left = 207
          Top = 15
          Width = 16
          Height = 24
          Hint = 'Minimum 1 - Maximum 30'
          Associate = ThreadEdit
          Min = 1
          Max = 30
          Position = 10
          TabOrder = 1
          Wrap = False
        end
        object RetryEdit: TEdit
          Left = 176
          Top = 47
          Width = 31
          Height = 24
          Hint = 'Number of retry in case of error'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ReadOnly = True
          TabOrder = 2
          Text = '50'
        end
        object UpDown2: TUpDown
          Left = 207
          Top = 47
          Width = 16
          Height = 24
          Hint = 'Minimum 1 - Maximum 99'
          Associate = RetryEdit
          Min = 1
          Max = 99
          Position = 50
          TabOrder = 3
          Wrap = False
        end
        object RetryBox: TCheckBox
          Left = 240
          Top = 49
          Width = 89
          Height = 17
          Hint = 'Ignore the number of errors and continue checking forever'
          Caption = 'Always Retry'
          TabOrder = 4
          OnClick = RetryBoxClick
        end
      end
      object GroupBox3: TGroupBox
        Left = 3
        Top = 96
        Width = 342
        Height = 73
        Caption = 'Other'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        object DisplayFakeBox: TCheckBox
          Left = 8
          Top = 16
          Width = 153
          Height = 17
          Hint = 'Used in posting messages to MIRC'
          Caption = 'Display fake passes as <.f>'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
        end
        object DirectConnectionBox: TCheckBox
          Left = 8
          Top = 40
          Width = 153
          Height = 17
          Hint = 'Use with extreme precaution ;)'
          Caption = 'DIRECT CONNECTION'
          Color = clBtnFace
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clRed
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentColor = False
          ParentFont = False
          TabOrder = 1
        end
      end
    end
    object MircPage: TTabSheet
      Caption = 'mIRC'
      ImageIndex = 2
      object GroupBox2: TGroupBox
        Left = 3
        Top = 12
        Width = 342
        Height = 81
        Caption = 'Mirc&&Dde Settings'
        Color = clBtnFace
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentColor = False
        ParentFont = False
        TabOrder = 0
        object Label7: TLabel
          Left = 10
          Top = 21
          Width = 116
          Height = 13
          Hint = 'Consult the mirc help for more info'
          Caption = 'Mirc DDE Service Name'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object Label8: TLabel
          Left = 10
          Top = 49
          Width = 108
          Height = 13
          Hint = 'The name of the #channel to send the results as messages'
          Caption = 'Channel to Post results'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object ServiceNameEdit: TEdit
          Left = 176
          Top = 17
          Width = 145
          Height = 21
          Hint = 'Consult the mirc help for more info'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
          TabOrder = 0
          Text = 'mIRC'
        end
        object ChannelNameEdit: TEdit
          Left = 176
          Top = 49
          Width = 145
          Height = 21
          Hint = 'The name of the #channel to send the results as messages'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = 3416963
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
          TabOrder = 1
          Text = '#loginhere'
        end
      end
    end
  end
  object CancelButton: TButton
    Left = 184
    Top = 216
    Width = 75
    Height = 25
    Caption = 'CANCEL'
    ModalResult = 2
    TabOrder = 1
  end
  object OkButton: TButton
    Left = 88
    Top = 216
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 2
    OnClick = OkButtonClick
  end
end
