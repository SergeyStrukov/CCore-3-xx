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
   Yellow,
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
   Red,
   {
    &Dir8
   },
   {
   }
  };

Dir Dir3=
  {
   "Font",
   Red,
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
   Red,
   {
    &Dir11
   },
   {
   }
  };

Dir Dir6=
  {
   "CCore",
   Yellow,
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
   Yellow,
   {
    &Dir14
   },
   {
   }
  };

Dir Dir13=
  {
   "src",
   Yellow,
   {
    &Dir15
   },
   {
   }
  };

Dir Dir14=
  {
   "video",
   Yellow,
   {
   },
   {
    { "AppMain.h" , Green },
    { "AppOpt.h" , Green },
    { "ApplicationBase.h" , Green },
    { "WindowReport.h" , Yellow }
   }
  };

Dir Dir15=
  {
   "video",
   Yellow,
   {
   },
   {
    { "AppMain.cpp" , Green },
    { "AppOpt.cpp" , Green },
    { "ApplicationBase.cpp" , Green },
    { "WindowReport.cpp" , Yellow }
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
   Red,
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
   Red,
   {
    &Dir22
   },
   {
   }
  };

Dir Dir21=
  {
   "src",
   Red,
   {
    &Dir23
   },
   {
   }
  };

Dir Dir22=
  {
   "video",
   Red,
   {
   },
   {
    { "ColorField.h" , Red },
    { "CurveDriver.h" , Red },
    { "DrawTools.h" , Red },
    { "GammaTable.h" , Red },
    { "SmoothAlgo.h" , Red },
    { "SmoothDrawArt.h" , Red }
   }
  };

Dir Dir23=
  {
   "video",
   Red,
   {
   },
   {
    { "ColorField.cpp" , Red },
    { "CurveDriver.cpp" , Red },
    { "DrawTools.cpp" , Red },
    { "GammaTable.cpp" , Red },
    { "SmoothAlgo.cpp" , Red },
    { "SmoothDrawArt.cpp" , Red }
   }
  };

Dir Dir9=
  {
   "CCore",
   Red,
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
   Red,
   {
    &Dir26
   },
   {
   }
  };

Dir Dir25=
  {
   "src",
   Red,
   {
    &Dir27
   },
   {
   }
  };

Dir Dir26=
  {
   "video",
   Red,
   {
   },
   {
    { "Font.h" , Red },
    { "FreeType.h" , Red },
    { "FreeTypeFont.h" , Red }
   }
  };

Dir Dir27=
  {
   "video",
   Red,
   {
   },
   {
    { "Font.cpp" , Red },
    { "FreeType.cpp" , Red },
    { "FreeTypeFont.cpp" , Red }
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
    { "BindBagProxy.h" , Red },
    { "ConfigBinder.h" , Red },
    { "ConfigEditor.h" , Red },
    { "ConfigStore.h" , Red },
    { "DirFrame.h" , Red },
    { "ExceptionFrame.h" , Red },
    { "FigureLib.h" , Red },
    { "FileFrame.h" , Red },
    { "FrameBase.h" , Red },
    { "Layout.h" , Red },
    { "LayoutCombo.h" , Red },
    { "Menu.h" , Red },
    { "MessageFrame.h" , Red },
    { "MinSizeType.h" , Red },
    { "ShapeLib.h" , Red },
    { "ToolFrame.h" , Red },
    { "UserPreference.h" , Red },
    { "WindowLib.h" , Red }
   }
  };

Dir Dir32=
  {
   "lib",
   Red,
   {
   },
   {
    { "Window.Blank.h" , Red },
    { "Shape.Button.h" , Red },
    { "Window.Button.h" , Red },
    { "Shape.Check.h" , Red },
    { "Window.Check.h" , Red },
    { "Shape.Contour.h" , Red },
    { "Window.Decor.h" , Red },
    { "Shape.DragFrame.h" , Red },
    { "Window.DragFrame.h" , Red },
    { "Window.FireButton.h" , Red },
    { "Shape.FixedFrame.h" , Red },
    { "Shape.FrameBase.h" , Red },
    { "Shape.Info.h" , Red },
    { "Window.Info.h" , Red },
    { "Shape.Label.h" , Red },
    { "Shape.Light.h" , Red },
    { "Window.Light.h" , Red },
    { "Shape.Line.h" , Red },
    { "Shape.LineEdit.h" , Red },
    { "Window.LineEdit.h" , Red },
    { "Shape.Progress.h" , Red },
    { "Window.Progress.h" , Red },
    { "Shape.Radio.h" , Red },
    { "Window.Radio.h" , Red },
    { "Shape.RunButton.h" , Red },
    { "Window.RunButton.h" , Red },
    { "Shape.Scroll.h" , Red },
    { "Window.Scroll.h" , Red },
    { "Shape.ScrollList.h" , Red },
    { "Window.ScrollList.h" , Red },
    { "Shape.SimpleTextList.h" , Red },
    { "Window.SimpleTextList.h" , Red },
    { "Shape.Slider.h" , Red },
    { "Window.Slider.h" , Red },
    { "Shape.Spinor.h" , Red },
    { "Window.Spinor.h" , Red },
    { "Shape.Split.h" , Red },
    { "Window.Split.h" , Red },
    { "Shape.Switch.h" , Red },
    { "Shape.Text.h" , Red },
    { "Window.Text.h" , Red },
    { "Shape.TextLine.h" , Red },
    { "Window.TextLine.h" , Red }
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
    { "BindBagProxy.cpp" , Red },
    { "ConfigBinder.cpp" , Red },
    { "ConfigEditor.cpp" , Red },
    { "ConfigStore.cpp" , Red },
    { "DirFrame.cpp" , Red },
    { "ExceptionFrame.cpp" , Red },
    { "FigureLib.cpp" , Red },
    { "FileFrame.cpp" , Red },
    { "FrameBase.cpp" , Red },
    { "Layout.cpp" , Red },
    { "LayoutCombo.cpp" , Red },
    { "Menu.cpp" , Red },
    { "MessageFrame.cpp" , Red },
    { "MinSizeType.cpp" , Red },
    { "ShapeLib.cpp" , Red },
    { "ToolFrame.cpp" , Red },
    { "UserPreference.cpp" , Red },
    { "WindowLib.cpp" , Red },
    { "ConfigTypes.ddl" , Red },
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
    { "Window.Blank.cpp" , Red },
    { "Shape.Button.cpp" , Red },
    { "Window.Button.cpp" , Red },
    { "Shape.Check.cpp" , Red },
    { "Window.Check.cpp" , Red },
    { "Shape.Contour.cpp" , Red },
    { "Window.Decor.cpp" , Red },
    { "Shape.DragFrame.cpp" , Red },
    { "Window.DragFrame.cpp" , Red },
    { "Window.FireButton.cpp" , Red },
    { "Shape.FixedFrame.cpp" , Red },
    { "Shape.FrameBase.cpp" , Red },
    { "Shape.Info.cpp" , Red },
    { "Window.Info.cpp" , Red },
    { "Shape.Label.cpp" , Red },
    { "Shape.Light.cpp" , Red },
    { "Window.Light.cpp" , Red },
    { "Shape.Line.cpp" , Red },
    { "Shape.LineEdit.cpp" , Red },
    { "Window.LineEdit.cpp" , Red },
    { "Shape.Progress.cpp" , Red },
    { "Window.Progress.cpp" , Red },
    { "Shape.Radio.cpp" , Red },
    { "Window.Radio.cpp" , Red },
    { "Shape.RunButton.cpp" , Red },
    { "Window.RunButton.cpp" , Red },
    { "Shape.Scroll.cpp" , Red },
    { "Window.Scroll.cpp" , Red },
    { "Shape.ScrollList.cpp" , Red },
    { "Window.ScrollList.cpp" , Red },
    { "Shape.SimpleTextList.cpp" , Red },
    { "Window.SimpleTextList.cpp" , Red },
    { "Shape.Slider.cpp" , Red },
    { "Window.Slider.cpp" , Red },
    { "Shape.Spinor.cpp" , Red },
    { "Window.Spinor.cpp" , Red },
    { "Shape.Split.cpp" , Red },
    { "Window.Split.cpp" , Red },
    { "Shape.Switch.cpp" , Red },
    { "Shape.Text.cpp" , Red },
    { "Window.Text.cpp" , Red },
    { "Shape.TextLine.cpp" , Red },
    { "Window.TextLine.cpp" , Red }
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
   Red,
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
   Red,
   {
    &Dir38
   },
   {
   }
  };

Dir Dir37=
  {
   "src",
   Red,
   {
    &Dir39
   },
   {
   }
  };

Dir Dir38=
  {
   "video",
   Red,
   {
   },
   {
    { "Bitmap.h" , Red },
    { "ButtonId.h" , Green },
    { "DesktopKey.h" , Green },
    { "FileBoss.h" , Green },
    { "FileNameCmp.h" , Green },
    { "FontDatabase.h" , Red },
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
   Red,
   {
   },
   {
    { "Bitmap.cpp" , Red },
    { "ButtonId.cpp" , Green },
    { "DesktopKey.cpp" , Green },
    { "FileBoss.cpp" , Green },
    { "FileNameCmp.cpp" , Green },
    { "FontDatabase.cpp" , Red },
    { "FontLookup.cpp" , Green },
    { "FontParam.cpp" , Green },
    { "HomeFile.cpp" , Green },
    { "Incremental.cpp" , Green },
    { "Info.cpp" , Green },
    { "InfoSize.cpp" , Green },
    { "Picture.cpp" , Green },
    { "PrintDDL.cpp" , Green },
    { "ProgressScale.cpp" , Green },
    { "FontInfo.ddl" , Red },
    { "FontInfo.TypeDef.gen.h" , Red },
    { "FontInfo.TypeSet.gen.h" , Red }
   }
  };

