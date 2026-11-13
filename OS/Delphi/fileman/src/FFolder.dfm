object _folder: T_folder
  Left = 192
  Top = 107
  BorderStyle = bsDialog
  Caption = #1053#1086#1074#1099#1081' '#1082#1072#1090#1072#1083#1086#1075
  ClientHeight = 63
  ClientWidth = 304
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object bCreate: TButton
    Left = 224
    Top = 32
    Width = 75
    Height = 25
    Caption = #1057#1086#1079#1076#1072#1090#1100
    TabOrder = 0
    OnClick = bCreateClick
  end
  object eFolderName: TComboBox
    Left = 8
    Top = 8
    Width = 289
    Height = 21
    ItemHeight = 13
    TabOrder = 1
  end
end
