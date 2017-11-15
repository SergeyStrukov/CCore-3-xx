//include <Aspect.ddl>

Aspect Data=
 {
  '../../../Desktop',
  {
   '',
   Red,
   {
    &Dir0,
    &Dir1,
    &Dir2,
    &Dir3,
    &Dir4
   },
   {
   }
  }
 };

Dir Dir0=
  {
   'Core',
   Green,
   {
    &Dir5
   },
   {
   }
  };

Dir Dir1=
  {
   'Draw',
   Red,
   {
    &Dir6
   },
   {
   }
  };

Dir Dir2=
  {
   'Font',
   Red,
   {
    &Dir7
   },
   {
   }
  };

Dir Dir3=
  {
   'Lib',
   Red,
   {
    &Dir8
   },
   {
   }
  };

Dir Dir4=
  {
   'Tools',
   Green,
   {
    &Dir9
   },
   {
   }
  };

Dir Dir5=
  {
   'CCore',
   Green,
   {
    &Dir10,
    &Dir11
   },
   {
   }
  };

Dir Dir10=
  {
   'inc',
   Green,
   {
    &Dir12
   },
   {
   }
  };

Dir Dir11=
  {
   'src',
   Green,
   {
    &Dir13
   },
   {
   }
  };

Dir Dir12=
  {
   'video',
   Green,
   {
   },
   {
    { 'DrawBuf.h' , Green },
    { 'FrameWindow.h' , Green },
    { 'Keyboard.h' , Green },
    { 'Mouse.h' , Green },
    { 'RefVal.h' , Green },
    { 'SubWindow.h' , Green },
    { 'UserAction.h' , Green }
   }
  };

Dir Dir13=
  {
   'video',
   Green,
   {
   },
   {
    { 'DrawBuf.cpp' , Green },
    { 'FrameWindow.cpp' , Green },
    { 'Keyboard.cpp' , Green },
    { 'Mouse.cpp' , Green },
    { 'RefVal.cpp' , Green },
    { 'SubWindow.cpp' , Green },
    { 'UserAction.cpp' , Green }
   }
  };

Dir Dir6=
  {
   'CCore',
   Red,
   {
    &Dir14,
    &Dir15
   },
   {
   }
  };

Dir Dir14=
  {
   'inc',
   Red,
   {
    &Dir16
   },
   {
   }
  };

Dir Dir15=
  {
   'src',
   Red,
   {
    &Dir17
   },
   {
   }
  };

Dir Dir16=
  {
   'video',
   Red,
   {
   },
   {
    { 'ColorField.h' , Green },
    { 'CommonDrawArt.h' , Red },
    { 'CurveDriver.h' , Green },
    { 'DrawAlgo.h' , Red },
    { 'DrawTools.h' , Green },
    { 'GammaTable.h' , Green },
    { 'SmoothAlgo.h' , Red },
    { 'SmoothDrawArt.h' , Red }
   }
  };

Dir Dir17=
  {
   'video',
   Red,
   {
   },
   {
    { 'ColorField.cpp' , Green },
    { 'CommonDrawArt.cpp' , Red },
    { 'CurveDriver.cpp' , Green },
    { 'DrawAlgo.cpp' , Red },
    { 'DrawTools.cpp' , Green },
    { 'GammaTable.cpp' , Green },
    { 'SmoothAlgo.cpp' , Red },
    { 'SmoothDrawArt.cpp' , Red }
   }
  };

Dir Dir7=
  {
   'CCore',
   Red,
   {
    &Dir18,
    &Dir19
   },
   {
   }
  };

Dir Dir18=
  {
   'inc',
   Red,
   {
    &Dir20
   },
   {
   }
  };

Dir Dir19=
  {
   'src',
   Red,
   {
    &Dir21
   },
   {
   }
  };

Dir Dir20=
  {
   'video',
   Red,
   {
   },
   {
    { 'Font.h' , Red },
    { 'FreeType.h' , Red },
    { 'FreeTypeFont.h' , Red }
   }
  };

Dir Dir21=
  {
   'video',
   Red,
   {
   },
   {
    { 'Font.cpp' , Red },
    { 'FreeType.cpp' , Red },
    { 'FreeTypeFont.cpp' , Red }
   }
  };

Dir Dir8=
  {
   'CCore',
   Red,
   {
    &Dir22,
    &Dir23,
    &Dir24
   },
   {
   }
  };

Dir Dir22=
  {
   'inc',
   Red,
   {
    &Dir25
   },
   {
   }
  };

Dir Dir23=
  {
   'src',
   Red,
   {
    &Dir26
   },
   {
   }
  };

Dir Dir24=
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

Dir Dir25=
  {
   'video',
   Red,
   {
    &Dir27,
    &Dir28
   },
   {
    { 'ApplicationBase.h' , Green },
    { 'BindBagProxy.h' , Green },
    { 'ConfigBinder.h' , Green },
    { 'ConfigEditor.h' , Red },
    { 'ConfigStore.h' , Green },
    { 'DirFrame.h' , Red },
    { 'FigureLib.h' , Red },
    { 'FileFrame.h' , Red },
    { 'FrameBase.h' , Green },
    { 'Layout.h' , Red },
    { 'Menu.h' , Red },
    { 'MessageFrame.h' , Red },
    { 'MinSizeType.h' , Green },
    { 'ShapeLib.h' , Green },
    { 'ToolFrame.h' , Red },
    { 'UserPreference.h' , Red },
    { 'WindowLib.h' , Green },
    { 'WindowReport.h' , Red }
   }
  };

Dir Dir27=
  {
   'lib',
   Red,
   {
   },
   {
    { 'Window.Blank.h' , Green },
    { 'Shape.Button.h' , Green },
    { 'Window.Button.h' , Green },
    { 'Shape.Check.h' , Green },
    { 'Window.Check.h' , Green },
    { 'Shape.Contour.h' , Green },
    { 'Window.Decor.h' , Green },
    { 'Shape.DragFrame.h' , Red },
    { 'Window.DragFrame.h' , Red },
    { 'Window.FireButton.h' , Green },
    { 'Shape.FixedFrame.h' , Red },
    { 'Shape.FrameBase.h' , Red },
    { 'Shape.Info.h' , Green },
    { 'Window.Info.h' , Green },
    { 'Shape.Label.h' , Green },
    { 'Shape.Light.h' , Green },
    { 'Window.Light.h' , Green },
    { 'Shape.Line.h' , Green },
    { 'Shape.LineEdit.h' , Red },
    { 'Window.LineEdit.h' , Red },
    { 'Shape.Progress.h' , Green },
    { 'Window.Progress.h' , Green },
    { 'Shape.Radio.h' , Green },
    { 'Window.Radio.h' , Green },
    { 'Shape.Scroll.h' , Red },
    { 'Window.Scroll.h' , Red },
    { 'Shape.ScrollList.h' , Red },
    { 'Window.ScrollList.h' , Red },
    { 'Shape.SimpleTextList.h' , Red },
    { 'Window.SimpleTextList.h' , Red },
    { 'Shape.Slider.h' , Yellow },
    { 'Window.Slider.h' , Green },
    { 'Shape.Spinor.h' , Green },
    { 'Window.Spinor.h' , Green },
    { 'Shape.Split.h' , Green },
    { 'Window.Split.h' , Green },
    { 'Shape.Switch.h' , Green },
    { 'Shape.Text.h' , Green },
    { 'Window.Text.h' , Green },
    { 'Shape.TextLine.h' , Green },
    { 'Window.TextLine.h' , Green }
   }
  };

Dir Dir28=
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

Dir Dir26=
  {
   'video',
   Red,
   {
    &Dir29,
    &Dir30
   },
   {
    { 'ApplicationBase.cpp' , Green },
    { 'BindBagProxy.cpp' , Green },
    { 'ConfigBinder.cpp' , Green },
    { 'ConfigEditor.cpp' , Red },
    { 'ConfigStore.cpp' , Green },
    { 'DirFrame.cpp' , Red },
    { 'FigureLib.cpp' , Red },
    { 'FileFrame.cpp' , Red },
    { 'FrameBase.cpp' , Green },
    { 'Layout.cpp' , Red },
    { 'Menu.cpp' , Red },
    { 'MessageFrame.cpp' , Red },
    { 'MinSizeType.cpp' , Green },
    { 'ShapeLib.cpp' , Green },
    { 'ToolFrame.cpp' , Red },
    { 'UserPreference.cpp' , Red },
    { 'WindowLib.cpp' , Green },
    { 'WindowReport.cpp' , Red },
    { 'ConfigTypes.ddl' , Green },
    { 'HitDirs.ddl' , Red },
    { 'HitDirs.TypeDef.gen.h' , Red },
    { 'HitDirs.TypeSet.gen.h' , Red }
   }
  };

Dir Dir29=
  {
   'lib',
   Red,
   {
   },
   {
    { 'Window.Blank.cpp' , Green },
    { 'Shape.Button.cpp' , Green },
    { 'Window.Button.cpp' , Green },
    { 'Shape.Check.cpp' , Green },
    { 'Window.Check.cpp' , Green },
    { 'Shape.Contour.cpp' , Green },
    { 'Window.Decor.cpp' , Green },
    { 'Shape.DragFrame.cpp' , Red },
    { 'Window.DragFrame.cpp' , Red },
    { 'Window.FireButton.cpp' , Green },
    { 'Shape.FixedFrame.cpp' , Red },
    { 'Shape.FrameBase.cpp' , Red },
    { 'Shape.Info.cpp' , Green },
    { 'Window.Info.cpp' , Green },
    { 'Shape.Label.cpp' , Green },
    { 'Shape.Light.cpp' , Green },
    { 'Window.Light.cpp' , Green },
    { 'Shape.Line.cpp' , Green },
    { 'Shape.LineEdit.cpp' , Red },
    { 'Window.LineEdit.cpp' , Red },
    { 'Shape.Progress.cpp' , Green },
    { 'Window.Progress.cpp' , Green },
    { 'Shape.Radio.cpp' , Green },
    { 'Window.Radio.cpp' , Green },
    { 'Shape.Scroll.cpp' , Red },
    { 'Window.Scroll.cpp' , Red },
    { 'Shape.ScrollList.cpp' , Red },
    { 'Window.ScrollList.cpp' , Red },
    { 'Shape.SimpleTextList.cpp' , Red },
    { 'Window.SimpleTextList.cpp' , Red },
    { 'Shape.Slider.cpp' , Yellow },
    { 'Window.Slider.cpp' , Green },
    { 'Shape.Spinor.cpp' , Green },
    { 'Window.Spinor.cpp' , Green },
    { 'Shape.Split.cpp' , Green },
    { 'Window.Split.cpp' , Green },
    { 'Shape.Switch.cpp' , Green },
    { 'Shape.Text.cpp' , Green },
    { 'Window.Text.cpp' , Green },
    { 'Shape.TextLine.cpp' , Green },
    { 'Window.TextLine.cpp' , Green }
   }
  };

Dir Dir30=
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

Dir Dir9=
  {
   'CCore',
   Green,
   {
    &Dir31,
    &Dir32
   },
   {
   }
  };

Dir Dir31=
  {
   'inc',
   Green,
   {
    &Dir33
   },
   {
   }
  };

Dir Dir32=
  {
   'src',
   Green,
   {
    &Dir34
   },
   {
   }
  };

Dir Dir33=
  {
   'video',
   Green,
   {
   },
   {
    { 'ButtonId.h' , Green },
    { 'DesktopKey.h' , Green },
    { 'FileBoss.h' , Green },
    { 'FileNameCmp.h' , Green },
    { 'FontDatabase.h' , Green },
    { 'FontLookup.h' , Green },
    { 'FontParam.h' , Green },
    { 'HomeFile.h' , Green },
    { 'Incremental.h' , Green },
    { 'Info.h' , Green },
    { 'InfoSize.h' , Green },
    { 'Picture.h' , Green },
    { 'PrintDDL.h' , Green },
    { 'ProgressScale.h' , Green }
   }
  };

Dir Dir34=
  {
   'video',
   Green,
   {
   },
   {
    { 'ButtonId.cpp' , Green },
    { 'DesktopKey.cpp' , Green },
    { 'FileBoss.cpp' , Green },
    { 'FileNameCmp.cpp' , Green },
    { 'FontDatabase.cpp' , Green },
    { 'FontLookup.cpp' , Green },
    { 'FontParam.cpp' , Green },
    { 'HomeFile.cpp' , Green },
    { 'Incremental.cpp' , Green },
    { 'Info.cpp' , Green },
    { 'InfoSize.cpp' , Green },
    { 'Picture.cpp' , Green },
    { 'PrintDDL.cpp' , Green },
    { 'ProgressScale.cpp' , Green },
    { 'FontInfo.ddl' , Green },
    { 'FontInfo.TypeDef.gen.h' , Green },
    { 'FontInfo.TypeSet.gen.h' , Green }
   }
  };

