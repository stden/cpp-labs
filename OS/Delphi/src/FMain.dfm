object _main: T_main
  Left = 105
  Top = 140
  Width = 868
  Height = 638
  Caption = 'OSInfo'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu
  OldCreateOrder = False
  Position = poDefaultPosOnly
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Split: TSplitter
    Left = 185
    Top = 0
    Height = 573
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 573
    Width = 860
    Height = 19
    Panels = <
      item
        Width = 50
      end
      item
        Alignment = taRightJustify
        BiDiMode = bdRightToLeftReadingOnly
        ParentBiDiMode = False
        Style = psOwnerDraw
        Text = 'test'
        Width = 100
      end
      item
        Style = psOwnerDraw
        Width = 100
      end
      item
        Width = 50
      end>
  end
  object PageArea: TPanel
    Left = 188
    Top = 0
    Width = 672
    Height = 573
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 1
  end
  object NavPanel: TPanel
    Left = 0
    Top = 0
    Width = 185
    Height = 573
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 2
    object NavView: TTreeView
      Left = 0
      Top = 0
      Width = 185
      Height = 542
      Align = alClient
      BevelInner = bvNone
      BorderStyle = bsNone
      Indent = 19
      ReadOnly = True
      TabOrder = 0
      OnChange = NavViewChange
    end
    object Panel2: TPanel
      Left = 0
      Top = 542
      Width = 185
      Height = 31
      Align = alBottom
      BevelInner = bvRaised
      BevelOuter = bvLowered
      TabOrder = 1
    end
  end
  object MainMenu: TMainMenu
    Left = 8
    Top = 8
    object m_File: TMenuItem
      Caption = #1060#1072#1081#1083
      object mi_FileExit: TMenuItem
        Caption = #1042#1099#1093#1086#1076
        OnClick = mi_FileExitClick
      end
    end
    object m_Help: TMenuItem
      Caption = #1057#1087#1088#1072#1074#1082#1072
      object mi_HelpAbout: TMenuItem
        Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077'...'
        OnClick = mi_HelpAboutClick
      end
    end
  end
  object TimerUpdateInfo: TTimer
    OnTimer = TimerUpdateInfoTimer
    Left = 44
    Top = 8
  end
  object XPManifest: TXPManifest
    Left = 80
    Top = 8
  end
  object TimerUpdateSystemInfo: TTimer
    Interval = 5000
    OnTimer = TimerUpdateSystemInfoTimer
    Left = 112
    Top = 8
  end
end
