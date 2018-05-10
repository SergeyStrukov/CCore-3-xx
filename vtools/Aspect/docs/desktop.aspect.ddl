//include <Aspect.ddl>

Aspect Data=
 {
  "../../../Desktop",
  {
   "",
   Red,
   {
    &Dir0,
    &Dir1,
    &Dir2,
    &Dir3,
    &Dir4,
    &Dir5
   },
   {
   }
  }
 };

Dir Dir0=
  {
   "App",
   Green,
   {
    &Dir6
   },
   {
   }
  };

Dir Dir1=
  {
   "Core",
   Green,
   {
    &Dir7
   },
   {
   }
  };

Dir Dir2=
  {
   "Draw",
   Green,
   {
    &Dir8
   },
   {
   }
  };

Dir Dir3=
  {
   "Font",
   Green,
   {
    &Dir9
   },
   {
   }
  };

Dir Dir4=
  {
   "Lib",
   Red,
   {
    &Dir10
   },
   {
   }
  };

Dir Dir5=
  {
   "Tools",
   Green,
   {
    &Dir11
   },
   {
   }
  };

Dir Dir6=
  {
   "CCore",
   Green,
   {
    &Dir12,
    &Dir13
   },
   {
   }
  };

Dir Dir12=
  {
   "inc",
   Green,
   {
    &Dir14
   },
   {
   }
  };

Dir Dir13=
  {
   "src",
   Green,
   {
    &Dir15
   },
   {
   }
  };

Dir Dir14=
  {
   "video",
   Green,
   {
   },
   {
    { "AppMain.h" , Green },
    { "AppOpt.h" , Green },
    { "ApplicationBase.h" , Green },
    { "WindowReport.h" , Green }
   }
  };

Dir Dir15=
  {
   "video",
   Green,
   {
   },
   {
    { "AppMain.cpp" , Green },
    { "AppOpt.cpp" , Green },
    { "ApplicationBase.cpp" , Green },
    { "WindowReport.cpp" , Green }
   }
  };

Dir Dir7=
  {
   "CCore",
   Green,
   {
    &Dir16,
    &Dir17
   },
   {
   }
  };

Dir Dir16=
  {
   "inc",
   Green,
   {
    &Dir18
   },
   {
   }
  };

Dir Dir17=
  {
   "src",
   Green,
   {
    &Dir19
   },
   {
   }
  };

Dir Dir18=
  {
   "video",
   Green,
   {
   },
   {
    { "DrawBuf.h" , Green },
    { "FrameWindow.h" , Green },
    { "Keyboard.h" , Green },
    { "Mouse.h" , Green },
    { "RefVal.h" , Green },
    { "SubWindow.h" , Green },
    { "UserAction.h" , Green }
   }
  };

Dir Dir19=
  {
   "video",
   Green,
   {
   },
   {
    { "DrawBuf.cpp" , Green },
    { "FrameWindow.cpp" , Green },
    { "Keyboard.cpp" , Green },
    { "Mouse.cpp" , Green },
    { "RefVal.cpp" , Green },
    { "SubWindow.cpp" , Green },
    { "UserAction.cpp" , Green }
   }
  };

Dir Dir8=
  {
   "CCore",
   Green,
   {
    &Dir20,
    &Dir21
   },
   {
   }
  };

Dir Dir20=
  {
   "inc",
   Green,
   {
    &Dir22
   },
   {
   }
  };

Dir Dir21=
  {
   "src",
   Green,
   {
    &Dir23
   },
   {
   }
  };

Dir Dir22=
  {
   "video",
   Green,
   {
   },
   {
    { "ColorField.h" , Green },
    { "CurveDriver.h" , Green },
    { "DrawTools.h" , Green },
    { "GammaTable.h" , Green },
    { "MPoint.h" , Green },
    { "SmoothAlgo.h" , Green },
    { "SmoothDrawArt.h" , Green }
   }
  };

Dir Dir23=
  {
   "video",
   Green,
   {
   },
   {
    { "ColorField.cpp" , Green },
    { "CurveDriver.cpp" , Green },
    { "DrawTools.cpp" , Green },
    { "GammaTable.cpp" , Green },
    { "MPoint.cpp" , Green },
    { "SmoothAlgo.cpp" , Green },
    { "SmoothDrawArt.cpp" , Green }
   }
  };

Dir Dir9=
  {
   "CCore",
   Green,
   {
    &Dir24,
    &Dir25
   },
   {
   }
  };

Dir Dir24=
  {
   "inc",
   Green,
   {
    &Dir26
   },
   {
   }
  };

Dir Dir25=
  {
   "src",
   Green,
   {
    &Dir27
   },
   {
   }
  };

Dir Dir26=
  {
   "video",
   Green,
   {
   },
   {
    { "Font.h" , Green },
    { "FreeType.h" , Green },
    { "FreeTypeFont.h" , Green }
   }
  };

Dir Dir27=
  {
   "video",
   Green,
   {
   },
   {
    { "Font.cpp" , Green },
    { "FreeType.cpp" , Green },
    { "FreeTypeFont.cpp" , Green }
   }
  };

Dir Dir10=
  {
   "CCore",
   Red,
   {
    &Dir28,
    &Dir29
   },
   {
   }
  };

Dir Dir28=
  {
   "inc",
   Red,
   {
    &Dir30
   },
   {
   }
  };

Dir Dir29=
  {
   "src",
   Red,
   {
    &Dir31
   },
   {
   }
  };

Dir Dir30=
  {
   "video",
   Red,
   {
    &Dir32,
    &Dir33
   },
   {
    { "BindBagProxy.h" , Green },
    { "ConfigBinder.h" , Green },
    { "ConfigEditor.h" , Red },
    { "ConfigStore.h" , Green },
    { "DirFrame.h" , Red },
    { "ExceptionFrame.h" , Green },
    { "FigureLib.h" , Red },
    { "FileFrame.h" , Red },
    { "FrameBase.h" , Red },
    { "Layout.h" , Red },
    { "LayoutCombo.h" , Red },
    { "Menu.h" , Red },
    { "MessageFrame.h" , Red },
    { "MinSizeType.h" , Green },
    { "ShapeLib.h" , Green },
    { "ToolFrame.h" , Red },
    { "UserPreference.h" , Red },
    { "WindowLib.h" , Green }
   }
  };

Dir Dir32=
  {
   "lib",
   Red,
   {
   },
   {
    { "Window.Blank.h" , Green },
    { "Shape.Button.h" , Green },
    { "Window.Button.h" , Green },
    { "Shape.Check.h" , Green },
    { "Window.Check.h" , Green },
    { "Shape.Contour.h" , Green },
    { "Window.Decor.h" , Green },
    { "Shape.DragFrame.h" , Red },
    { "Window.DragFrame.h" , Red },
    { "Window.FireButton.h" , Green },
    { "Shape.FixedFrame.h" , Red },
    { "Shape.FrameBase.h" , Red },
    { "Shape.Info.h" , Green },
    { "Window.Info.h" , Green },
    { "Shape.Label.h" , Green },
    { "Shape.Light.h" , Green },
    { "Window.Light.h" , Green },
    { "Shape.Line.h" , Green },
    { "Shape.LineEdit.h" , Green },
    { "Window.LineEdit.h" , Green },
    { "Shape.Progress.h" , Green },
    { "Window.Progress.h" , Green },
    { "Shape.Radio.h" , Green },
    { "Window.Radio.h" , Green },
    { "Shape.RunButton.h" , Green },
    { "Window.RunButton.h" , Green },
    { "Shape.Scroll.h" , Green },
    { "Window.Scroll.h" , Green },
    { "Shape.ScrollList.h" , Green },
    { "Window.ScrollList.h" , Green },
    { "Window.Scrollable.h" , Green },
    { "Shape.SimpleTextList.h" , Green },
    { "Window.SimpleTextList.h" , Green },
    { "Shape.Slider.h" , Green },
    { "Window.Slider.h" , Green },
    { "Shape.Spinor.h" , Green },
    { "Window.Spinor.h" , Green },
    { "Shape.Split.h" , Green },
    { "Window.Split.h" , Green },
    { "Shape.Switch.h" , Green },
    { "Shape.Text.h" , Green },
    { "Window.Text.h" , Green },
    { "Shape.TextLine.h" , Green },
    { "Window.TextLine.h" , Green }
   }
  };

Dir Dir33=
  {
   "pref",
   Red,
   {
   },
   {
    { "ColorEdit.h" , Red },
    { "CoordEdit.h" , Red },
    { "FontEdit.h" , Red },
    { "MCoordEdit.h" , Red },
    { "PointEdit.h" , Red },
    { "RatioEdit.h" , Red }
   }
  };

Dir Dir31=
  {
   "video",
   Red,
   {
    &Dir34,
    &Dir35
   },
   {
    { "BindBagProxy.cpp" , Green },
    { "ConfigBinder.cpp" , Green },
    { "ConfigEditor.cpp" , Red },
    { "ConfigStore.cpp" , Green },
    { "DirFrame.cpp" , Red },
    { "ExceptionFrame.cpp" , Green },
    { "FigureLib.cpp" , Red },
    { "FileFrame.cpp" , Red },
    { "FrameBase.cpp" , Red },
    { "Layout.cpp" , Red },
    { "LayoutCombo.cpp" , Red },
    { "Menu.cpp" , Red },
    { "MessageFrame.cpp" , Red },
    { "MinSizeType.cpp" , Green },
    { "ShapeLib.cpp" , Green },
    { "ToolFrame.cpp" , Red },
    { "UserPreference.cpp" , Red },
    { "WindowLib.cpp" , Green },
    { "ConfigTypes.ddl" , Green },
    { "HitDirs.ddl" , Red },
    { "HitDirs.TypeDef.gen.h" , Red },
    { "HitDirs.TypeSet.gen.h" , Red }
   }
  };

Dir Dir34=
  {
   "lib",
   Red,
   {
   },
   {
    { "Window.Blank.cpp" , Green },
    { "Shape.Button.cpp" , Green },
    { "Window.Button.cpp" , Green },
    { "Shape.Check.cpp" , Green },
    { "Window.Check.cpp" , Green },
    { "Shape.Contour.cpp" , Green },
    { "Window.Decor.cpp" , Green },
    { "Shape.DragFrame.cpp" , Red },
    { "Window.DragFrame.cpp" , Red },
    { "Window.FireButton.cpp" , Green },
    { "Shape.FixedFrame.cpp" , Red },
    { "Shape.FrameBase.cpp" , Red },
    { "Shape.Info.cpp" , Green },
    { "Window.Info.cpp" , Green },
    { "Shape.Label.cpp" , Green },
    { "Shape.Light.cpp" , Green },
    { "Window.Light.cpp" , Green },
    { "Shape.Line.cpp" , Green },
    { "Shape.LineEdit.cpp" , Green },
    { "Window.LineEdit.cpp" , Green },
    { "Shape.Progress.cpp" , Green },
    { "Window.Progress.cpp" , Green },
    { "Shape.Radio.cpp" , Green },
    { "Window.Radio.cpp" , Green },
    { "Shape.RunButton.cpp" , Green },
    { "Window.RunButton.cpp" , Green },
    { "Shape.Scroll.cpp" , Green },
    { "Window.Scroll.cpp" , Green },
    { "Shape.ScrollList.cpp" , Green },
    { "Window.ScrollList.cpp" , Green },
    { "Window.Scrollable.cpp" , Green },
    { "Shape.SimpleTextList.cpp" , Green },
    { "Window.SimpleTextList.cpp" , Green },
    { "Shape.Slider.cpp" , Green },
    { "Window.Slider.cpp" , Green },
    { "Shape.Spinor.cpp" , Green },
    { "Window.Spinor.cpp" , Green },
    { "Shape.Split.cpp" , Green },
    { "Window.Split.cpp" , Green },
    { "Shape.Switch.cpp" , Green },
    { "Shape.Text.cpp" , Green },
    { "Window.Text.cpp" , Green },
    { "Shape.TextLine.cpp" , Green },
    { "Window.TextLine.cpp" , Green }
   }
  };

Dir Dir35=
  {
   "pref",
   Red,
   {
   },
   {
    { "ColorEdit.cpp" , Red },
    { "CoordEdit.cpp" , Red },
    { "FontEdit.cpp" , Red },
    { "MCoordEdit.cpp" , Red },
    { "PointEdit.cpp" , Red },
    { "RatioEdit.cpp" , Red }
   }
  };

Dir Dir11=
  {
   "CCore",
   Green,
   {
    &Dir36,
    &Dir37
   },
   {
   }
  };

Dir Dir36=
  {
   "inc",
   Green,
   {
    &Dir38
   },
   {
   }
  };

Dir Dir37=
  {
   "src",
   Green,
   {
    &Dir39
   },
   {
   }
  };

Dir Dir38=
  {
   "video",
   Green,
   {
   },
   {
    { "Bitmap.h" , Green },
    { "ButtonId.h" , Green },
    { "DesktopKey.h" , Green },
    { "FileBoss.h" , Green },
    { "FileNameCmp.h" , Green },
    { "FontDatabase.h" , Green },
    { "FontLookup.h" , Green },
    { "FontParam.h" , Green },
    { "HomeFile.h" , Green },
    { "Incremental.h" , Green },
    { "Info.h" , Green },
    { "InfoSize.h" , Green },
    { "Picture.h" , Green },
    { "PrintDDL.h" , Green },
    { "ProgressScale.h" , Green }
   }
  };

Dir Dir39=
  {
   "video",
   Green,
   {
   },
   {
    { "Bitmap.cpp" , Green },
    { "ButtonId.cpp" , Green },
    { "DesktopKey.cpp" , Green },
    { "FileBoss.cpp" , Green },
    { "FileNameCmp.cpp" , Green },
    { "FontDatabase.cpp" , Green },
    { "FontLookup.cpp" , Green },
    { "FontParam.cpp" , Green },
    { "HomeFile.cpp" , Green },
    { "Incremental.cpp" , Green },
    { "Info.cpp" , Green },
    { "InfoSize.cpp" , Green },
    { "Picture.cpp" , Green },
    { "PrintDDL.cpp" , Green },
    { "ProgressScale.cpp" , Green },
    { "FontInfo.ddl" , Green },
    { "FontInfo.TypeDef.gen.h" , Green },
    { "FontInfo.TypeSet.gen.h" , Green }
   }
  };

