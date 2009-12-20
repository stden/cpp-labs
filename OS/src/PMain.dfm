object PageMain: TPageMain
  Left = 0
  Top = 0
  Width = 443
  Height = 277
  Align = alClient
  Color = clWhite
  ParentColor = False
  TabOrder = 0
  DesignSize = (
    443
    277)
  object GroupBox1: TGroupBox
    Left = 0
    Top = 216
    Width = 443
    Height = 61
    Align = alBottom
    Caption = 'System:'
    TabOrder = 0
    DesignSize = (
      443
      61)
    object labelComputerName: TLabel
      Left = 8
      Top = 16
      Width = 249
      Height = 13
      AutoSize = False
      Caption = 'ComputerName'
    end
    object labelProcessorType: TLabel
      Left = 8
      Top = 32
      Width = 71
      Height = 13
      Caption = 'ProcessorType'
    end
    object labelUserName: TLabel
      Left = 360
      Top = 8
      Width = 72
      Height = 13
      Anchors = [akTop, akRight]
      Caption = 'labelUserName'
    end
  end
  object GroupBox2: TGroupBox
    Left = 224
    Top = 8
    Width = 209
    Height = 57
    Anchors = [akTop, akRight]
    Caption = #1055#1072#1084#1103#1090#1100':'
    TabOrder = 1
    object labelMemoryTotalPhys: TLabel
      Left = 120
      Top = 16
      Width = 24
      Height = 13
      Caption = '0 GB'
    end
    object Label1: TLabel
      Left = 8
      Top = 16
      Width = 107
      Height = 13
      Alignment = taRightJustify
      Caption = #1060#1080#1079#1080#1095#1077#1089#1082#1072#1103' '#1087#1072#1084#1103#1090#1100':'
    end
    object Label2: TLabel
      Left = 8
      Top = 32
      Width = 108
      Height = 13
      Alignment = taRightJustify
      Caption = #1042#1080#1088#1090#1091#1072#1083#1100#1085#1072#1103' '#1087#1072#1084#1103#1090#1100':'
    end
    object labelMemoryTotalVirtual: TLabel
      Left = 120
      Top = 32
      Width = 24
      Height = 13
      Caption = '0 GB'
    end
  end
end
