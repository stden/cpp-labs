object ProcDumpDlg: TProcDumpDlg
  Left = 230
  Top = 128
  Width = 1339
  Height = 730
  Caption = 'Process Memory Map'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 120
  TextHeight = 17
  object lvMemoryMap: TListView
    Left = 0
    Top = 113
    Width = 1331
    Height = 589
    Align = alClient
    Columns = <
      item
        Caption = 'Address:'
        Width = 105
      end
      item
        Caption = 'Size:'
        Width = 105
      end
      item
        Caption = 'Owner:'
        Width = 131
      end
      item
        Caption = 'Section:'
        Width = 105
      end
      item
        Caption = 'Contains:'
        Width = 255
      end
      item
        Caption = 'Type:'
        Width = 105
      end
      item
        Caption = 'Access:'
        Width = 111
      end
      item
        Caption = 'Initial Access:'
        Width = 118
      end
      item
        Caption = 'Mapped as:'
        Width = 262
      end>
    ReadOnly = True
    RowSelect = True
    TabOrder = 0
    ViewStyle = vsReport
    OnCustomDrawItem = lvMemoryMapCustomDrawItem
  end
  object pnProcess: TPanel
    Left = 0
    Top = 0
    Width = 1331
    Height = 113
    Align = alTop
    TabOrder = 1
    DesignSize = (
      1331
      113)
    object lblHint: TLabel
      Left = 16
      Top = 8
      Width = 92
      Height = 17
      Caption = 'Select process:'
    end
    object cbProcess: TComboBox
      Left = 16
      Top = 32
      Width = 1187
      Height = 25
      Style = csDropDownList
      Anchors = [akLeft, akTop, akRight]
      ItemHeight = 17
      TabOrder = 0
      OnChange = cbProcessChange
    end
    object cbShowFreeMem: TCheckBox
      Left = 16
      Top = 64
      Width = 153
      Height = 17
      Caption = 'Show Free Memory'
      TabOrder = 1
    end
    object cbShowReserve: TCheckBox
      Left = 16
      Top = 88
      Width = 177
      Height = 17
      Caption = 'Show Reserved Memory'
      TabOrder = 2
    end
    object btnRefresh: TButton
      Left = 1210
      Top = 32
      Width = 113
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Refresh'
      TabOrder = 3
      OnClick = btnRefreshClick
    end
  end
end
