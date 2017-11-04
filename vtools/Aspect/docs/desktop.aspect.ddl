//include <Aspect.ddl>

Aspect Data=
 {
  '../../../Desktop',
  {
   '',
   New,
   {
    &Dir0
   },
   {
   }
  }
 };

Dir Dir0=
  {
   'CCore',
   New,
   {
    &Dir1,
    &Dir2,
    &Dir3
   },
   {
   }
  };

Dir Dir1=
  {
   'inc',
   Red,
   {
    &Dir4
   },
   {
   }
  };

Dir Dir2=
  {
   'src',
   Red,
   {
    &Dir5
   },
   {
   }
  };

Dir Dir3=
  {
   'test',
   Ignore,
   {
   },
   {
    { 'SpecialDrawArt.cpp' , Ignore },
    { 'wintest.cpp' , Ignore },
    { 'test7006.Ball.cpp' , Ignore },
    { 'test7007.CommonArt.cpp' , Ignore },
    { 'test7003.DragWindow.cpp' , Ignore },
    { 'test7005.DragWindow.cpp' , Ignore },
    { 'test7001.DrawAlgo.cpp' , Ignore },
    { 'test7002.DrawAlgo.cpp' , Ignore },
    { 'test7004.Font.cpp' , Ignore },
    { 'test7008.Tab.cpp' , Ignore },
    { 'SpecialDrawArt.h' , Ignore },
    { 'wintest.h' , Ignore }
   }
  };

Dir Dir4=
  {
   'video',
   Red,
   {
    &Dir6,
    &Dir7
   },
   {
    { 'ApplicationBase.h' , Green },
    { 'ButtonId.h' , Green },
    { 'ColorField.h' , Green },
    { 'CommonDrawArt.h' , Red },
    { 'ConfigBinder.h' , Red },
    { 'ConfigEditor.h' , Red },
    { 'ConfigStore.h' , Red },
    { 'CurveDriver.h' , Green },
    { 'DesktopKey.h' , Green },
    { 'DirFrame.h' , Red },
    { 'DrawAlgo.h' , Red },
    { 'DrawBuf.h' , Green },
    { 'DrawTools.h' , Green },
    { 'FigureLib.h' , Red },
    { 'FileBoss.h' , Green },
    { 'FileFrame.h' , Red },
    { 'FileNameCmp.h' , Red },
    { 'Font.h' , Red },
    { 'FontDatabase.h' , Red },
    { 'FontLookup.h' , Red },
    { 'FontParam.h' , Green },
    { 'FrameBase.h' , Red },
    { 'FrameWindow.h' , Red },
    { 'FreeType.h' , Red },
    { 'FreeTypeFont.h' , Red },
    { 'GammaTable.h' , Green },
    { 'HomeFile.h' , Red },
    { 'Incremental.h' , Red },
    { 'Info.h' , Red },
    { 'InfoSize.h' , Red },
    { 'Keyboard.h' , Green },
    { 'Layout.h' , Red },
    { 'Menu.h' , Red },
    { 'MessageFrame.h' , Red },
    { 'MinSizeType.h' , Red },
    { 'Mouse.h' , Green },
    { 'Picture.h' , Red },
    { 'PrintDDL.h' , Green },
    { 'ProgressScale.h' , Green },
    { 'RefVal.h' , Red },
    { 'ShapeLib.h' , Red },
    { 'SmoothAlgo.h' , Red },
    { 'SmoothDrawArt.h' , Red },
    { 'SubWindow.h' , Red },
    { 'ToolFrame.h' , Red },
    { 'UserAction.h' , Green },
    { 'UserPreference.h' , Red },
    { 'WindowLib.h' , Red },
    { 'WindowReport.h' , Red }
   }
  };

Dir Dir6=
  {
   'lib',
   Red,
   {
   },
   {
    { 'Window.Blank.h' , Red },
    { 'Shape.Button.h' , Red },
    { 'Window.Button.h' , Red },
    { 'Shape.Check.h' , Red },
    { 'Window.Check.h' , Red },
    { 'Shape.Contour.h' , Red },
    { 'Window.Decor.h' , Red },
    { 'Shape.DragFrame.h' , Red },
    { 'Window.DragFrame.h' , Red },
    { 'Shape.FixedFrame.h' , Red },
    { 'Shape.FrameBase.h' , Red },
    { 'Shape.Info.h' , Red },
    { 'Window.Info.h' , Red },
    { 'Shape.Label.h' , Red },
    { 'Shape.Light.h' , Red },
    { 'Window.Light.h' , Red },
    { 'Shape.Line.h' , Red },
    { 'Shape.LineEdit.h' , Red },
    { 'Window.LineEdit.h' , Red },
    { 'Shape.Progress.h' , Red },
    { 'Window.Progress.h' , Red },
    { 'Shape.Radio.h' , Red },
    { 'Window.Radio.h' , Red },
    { 'Shape.Scroll.h' , Red },
    { 'Window.Scroll.h' , Red },
    { 'Shape.ScrollList.h' , Red },
    { 'Window.ScrollList.h' , Red },
    { 'Shape.SimpleTextList.h' , Red },
    { 'Window.SimpleTextList.h' , Red },
    { 'Shape.Spinor.h' , Red },
    { 'Window.Spinor.h' , Red },
    { 'Shape.Split.h' , Red },
    { 'Window.Split.h' , Red },
    { 'Shape.Switch.h' , Red },
    { 'Shape.Text.h' , Red },
    { 'Window.Text.h' , Red },
    { 'Shape.TextLine.h' , Red },
    { 'Window.TextLine.h' , Red }
   }
  };

Dir Dir7=
  {
   'pref',
   Red,
   {
   },
   {
    { 'ColorEdit.h' , Red },
    { 'CoordEdit.h' , Red },
    { 'FontEdit.h' , Red },
    { 'MCoordEdit.h' , Red },
    { 'PointEdit.h' , Red },
    { 'RatioEdit.h' , Red }
   }
  };

Dir Dir5=
  {
   'video',
   Red,
   {
    &Dir8,
    &Dir9
   },
   {
    { 'ApplicationBase.cpp' , Green },
    { 'ButtonId.cpp' , Green },
    { 'ColorField.cpp' , Green },
    { 'CommonDrawArt.cpp' , Red },
    { 'ConfigBinder.cpp' , Red },
    { 'ConfigEditor.cpp' , Red },
    { 'ConfigStore.cpp' , Red },
    { 'CurveDriver.cpp' , Green },
    { 'DesktopKey.cpp' , Green },
    { 'DirFrame.cpp' , Red },
    { 'DrawAlgo.cpp' , Red },
    { 'DrawBuf.cpp' , Green },
    { 'DrawTools.cpp' , Green },
    { 'FigureLib.cpp' , Red },
    { 'FileBoss.cpp' , Green },
    { 'FileFrame.cpp' , Red },
    { 'FileNameCmp.cpp' , Red },
    { 'Font.cpp' , Red },
    { 'FontDatabase.cpp' , Red },
    { 'FontLookup.cpp' , Red },
    { 'FontParam.cpp' , Green },
    { 'FrameBase.cpp' , Red },
    { 'FrameWindow.cpp' , Red },
    { 'FreeType.cpp' , Red },
    { 'FreeTypeFont.cpp' , Red },
    { 'GammaTable.cpp' , Green },
    { 'HomeFile.cpp' , Red },
    { 'Incremental.cpp' , Red },
    { 'Info.cpp' , Red },
    { 'InfoSize.cpp' , Red },
    { 'Keyboard.cpp' , Green },
    { 'Layout.cpp' , Red },
    { 'Menu.cpp' , Red },
    { 'MessageFrame.cpp' , Red },
    { 'MinSizeType.cpp' , Red },
    { 'Mouse.cpp' , Green },
    { 'Picture.cpp' , Red },
    { 'PrintDDL.cpp' , Green },
    { 'ProgressScale.cpp' , Green },
    { 'RefVal.cpp' , Red },
    { 'ShapeLib.cpp' , Red },
    { 'SmoothAlgo.cpp' , Red },
    { 'SmoothDrawArt.cpp' , Red },
    { 'SubWindow.cpp' , Red },
    { 'ToolFrame.cpp' , Red },
    { 'UserAction.cpp' , Green },
    { 'UserPreference.cpp' , Red },
    { 'WindowLib.cpp' , Red },
    { 'WindowReport.cpp' , Red },
    { 'ConfigTypes.ddl' , Red },
    { 'FontInfo.ddl' , Red },
    { 'HitDirs.ddl' , Red },
    { 'FontInfo.TypeDef.gen.h' , Ignore },
    { 'HitDirs.TypeDef.gen.h' , Ignore },
    { 'FontInfo.TypeSet.gen.h' , Ignore },
    { 'HitDirs.TypeSet.gen.h' , Ignore }
   }
  };

Dir Dir8=
  {
   'lib',
   Red,
   {
   },
   {
    { 'Window.Blank.cpp' , Red },
    { 'Shape.Button.cpp' , Red },
    { 'Window.Button.cpp' , Red },
    { 'Shape.Check.cpp' , Red },
    { 'Window.Check.cpp' , Red },
    { 'Shape.Contour.cpp' , Red },
    { 'Window.Decor.cpp' , Red },
    { 'Shape.DragFrame.cpp' , Red },
    { 'Window.DragFrame.cpp' , Red },
    { 'Shape.FixedFrame.cpp' , Red },
    { 'Shape.FrameBase.cpp' , Red },
    { 'Shape.Info.cpp' , Red },
    { 'Window.Info.cpp' , Red },
    { 'Shape.Label.cpp' , Red },
    { 'Shape.Light.cpp' , Red },
    { 'Window.Light.cpp' , Red },
    { 'Shape.Line.cpp' , Red },
    { 'Shape.LineEdit.cpp' , Red },
    { 'Window.LineEdit.cpp' , Red },
    { 'Shape.Progress.cpp' , Red },
    { 'Window.Progress.cpp' , Red },
    { 'Shape.Radio.cpp' , Red },
    { 'Window.Radio.cpp' , Red },
    { 'Shape.Scroll.cpp' , Red },
    { 'Window.Scroll.cpp' , Red },
    { 'Shape.ScrollList.cpp' , Red },
    { 'Window.ScrollList.cpp' , Red },
    { 'Shape.SimpleTextList.cpp' , Red },
    { 'Window.SimpleTextList.cpp' , Red },
    { 'Shape.Spinor.cpp' , Red },
    { 'Window.Spinor.cpp' , Red },
    { 'Shape.Split.cpp' , Red },
    { 'Window.Split.cpp' , Red },
    { 'Shape.Switch.cpp' , Red },
    { 'Shape.Text.cpp' , Red },
    { 'Window.Text.cpp' , Red },
    { 'Shape.TextLine.cpp' , Red },
    { 'Window.TextLine.cpp' , Red }
   }
  };

Dir Dir9=
  {
   'pref',
   Red,
   {
   },
   {
    { 'ColorEdit.cpp' , Red },
    { 'CoordEdit.cpp' , Red },
    { 'FontEdit.cpp' , Red },
    { 'MCoordEdit.cpp' , Red },
    { 'PointEdit.cpp' , Red },
    { 'RatioEdit.cpp' , Red }
   }
  };

