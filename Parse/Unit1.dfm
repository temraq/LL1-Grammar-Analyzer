object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 532
  ClientWidth = 613
  Color = clBtnHighlight
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OnCreate = FormCreate
  TextHeight = 13
  object Label1: TLabel
    Left = 224
    Top = 16
    Width = 50
    Height = 14
    Caption = #1051#1077#1082#1089#1077#1084#1099
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 14
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 408
    Top = 16
    Width = 99
    Height = 14
    Caption = #1048#1076#1077#1085#1090#1080#1092#1080#1082#1072#1090#1086#1088#1099
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 14
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Memo: TMemo
    Left = 16
    Top = 36
    Width = 177
    Height = 237
    Lines.Strings = (
      'Memo')
    TabOrder = 1
  end
  object TableL: TStringGrid
    Left = 224
    Top = 36
    Width = 145
    Height = 453
    ColCount = 2
    DefaultColWidth = 75
    DefaultRowHeight = 20
    FixedCols = 0
    RowCount = 100
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSelect]
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object TableI: TStringGrid
    Left = 408
    Top = 36
    Width = 145
    Height = 453
    ColCount = 2
    DefaultColWidth = 75
    DefaultRowHeight = 20
    FixedCols = 0
    RowCount = 100
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSelect, goFixedRowDefAlign]
    ScrollBars = ssVertical
    TabOrder = 2
    RowHeights = (
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20
      20)
  end
  object Button1: TButton
    Left = 48
    Top = 297
    Width = 99
    Height = 25
    Caption = #1040#1085#1072#1083#1080#1079
    TabOrder = 3
    OnClick = Button1Click
  end
end
