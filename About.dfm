object Form4: TForm4
  Left = 221
  Top = 185
  AlphaBlend = True
  AlphaBlendValue = 128
  BorderIcons = [biSystemMenu]
  BorderStyle = bsToolWindow
  Caption = 'About'
  ClientHeight = 107
  ClientWidth = 407
  Color = clNavy
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnHide = FormHide
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 367
    Top = 29
    Width = 546
    Height = 55
    Caption = 'Project "Checker" by RageX'
    Color = clNavy
    Font.Charset = TURKISH_CHARSET
    Font.Color = clYellow
    Font.Height = -40
    Font.Name = 'Comic Sans MS'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 100
    OnTimer = Timer1Timer
  end
end
