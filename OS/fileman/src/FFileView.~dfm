object FileView: TFileView
  Left = 0
  Top = 0
  Width = 514
  Height = 277
  Align = alClient
  TabOrder = 0
  object ListView: TListView
    Left = 0
    Top = 49
    Width = 514
    Height = 228
    Align = alClient
    Columns = <
      item
        AutoSize = True
        Caption = #1048#1084#1103
      end
      item
        Caption = #1058#1080#1087
      end
      item
        Caption = #1056#1072#1079#1084#1077#1088
      end
      item
        Caption = #1048#1079#1084#1077#1085#1077#1085
      end
      item
        Caption = #1040#1090#1088#1080#1073#1091#1090#1099
      end>
    LargeImages = _main.iFileTypes
    RowSelect = True
    SmallImages = _main.iFileTypes
    TabOrder = 0
    ViewStyle = vsReport
    OnClick = ListViewClick
    OnDblClick = ListViewDblClick
    OnEdited = ListViewEdited
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 514
    Height = 49
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 1
    DesignSize = (
      514
      49)
    object ComboDriveBox: TComboBox
      Left = 0
      Top = 0
      Width = 65
      Height = 22
      Style = csOwnerDrawFixed
      ItemHeight = 16
      TabOrder = 0
      OnChange = ComboDriveBoxChange
    end
    object pInfo: TPanel
      Left = 72
      Top = 0
      Width = 377
      Height = 17
      Alignment = taLeftJustify
      Anchors = [akLeft, akTop, akRight]
      BevelInner = bvLowered
      BevelOuter = bvNone
      TabOrder = 1
    end
    object bRoot: TButton
      Left = 486
      Top = 0
      Width = 25
      Height = 17
      Anchors = [akTop, akRight]
      Caption = '\'
      TabOrder = 2
      OnClick = bRootClick
    end
    object bUp: TButton
      Left = 454
      Top = 0
      Width = 27
      Height = 17
      Anchors = [akTop, akRight]
      Caption = '..'
      TabOrder = 3
      OnClick = bUpClick
    end
    object ePath: TComboBox
      Left = 0
      Top = 24
      Width = 513
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      ItemHeight = 13
      TabOrder = 4
      OnKeyDown = ePathKeyDown
    end
  end
end
