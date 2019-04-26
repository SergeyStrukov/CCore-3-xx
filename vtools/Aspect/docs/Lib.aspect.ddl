//include <Aspect.ddl>

Aspect Data=
 {
  "../../../Desktop/Lib",
  {
   "",
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
   "CCore",
   New,
   {
    &Dir1,
    &Dir2
   },
   {
   }
  };

Dir Dir1=
  {
   "inc",
   New,
   {
    &Dir3
   },
   {
   }
  };

Dir Dir2=
  {
   "src",
   New,
   {
    &Dir4
   },
   {
   }
  };

Dir Dir3=
  {
   "video",
   New,
   {
    &Dir5,
    &Dir6,
    &Dir7
   },
   {
    { "BindBagProxy.h" , Green },
    { "BookFrame.h" , Red },
    { "ConfigBinder.h" , Green },
    { "ConfigEditor.h" , Red },
    { "ConfigStore.h" , Green },
    { "DirFrame.h" , Green },
    { "ExceptionFrame.h" , Green },
    { "FavFrame.h" , Green },
    { "FavList.h" , Green },
    { "FigureLib.h" , Yellow },
    { "FileFrame.h" , Green },
    { "FontReplace.h" , Green },
    { "FrameBase.h" , Green },
    { "FrameClient.h" , Yellow },
    { "Layout.h" , Yellow },
    { "LayoutCombo.h" , Yellow },
    { "Menu.h" , Green },
    { "MessageFrame.h" , Green },
    { "MinSizeType.h" , Green },
    { "ShapeLib.h" , Ignore },
    { "ToolFrame.h" , Green },
    { "UserPreference.h" , Yellow },
    { "WindowLib.h" , Ignore }
   }
  };

Dir Dir5=
  {
   "book",
   New,
   {
   },
   {
    { "Book.h" , Green },
    { "BookClient.h" , Red },
    { "BookWindow.h" , Green },
    { "DrawBook.h" , Green },
    { "DrawBookTools.h" , Green },
    { "SelectFrames.h" , Green },
    { "SpanLenEngine.h" , Green },
    { "Book1.TypeDef.gen.h" , Ignore }
   }
  };

Dir Dir6=
  {
   "lib",
   Yellow,
   {
   },
   {
    { "Shape.AllButton.h" , Green },
    { "Window.Blank.h" , Green },
    { "Shape.Button.h" , Green },
    { "Window.Button.h" , Green },
    { "Shape.ButtonState.h" , Green },
    { "Shape.Check.h" , Green },
    { "Window.Check.h" , Green },
    { "Shape.CheckState.h" , Green },
    { "Shape.Contour.h" , Green },
    { "Window.Decor.h" , Green },
    { "Shape.DragFrame.h" , Green },
    { "Window.DragFrame.h" , Green },
    { "Window.FireButton.h" , Green },
    { "Shape.FixedFrame.h" , Green },
    { "Shape.FrameBase.h" , Green },
    { "Shape.Info.h" , Green },
    { "Window.Info.h" , Green },
    { "Shape.Label.h" , Green },
    { "Shape.Light.h" , Green },
    { "Window.Light.h" , Green },
    { "Shape.Line.h" , Green },
    { "Shape.LineEdit.h" , Green },
    { "Window.LineEdit.h" , Yellow },
    { "Shape.MoveButton.h" , Green },
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
    { "Shape.ShiftSwitch.h" , Green },
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

Dir Dir7=
  {
   "pref",
   New,
   {
   },
   {
    { "ColorEdit.h" , Red },
    { "ColorListWindow.h" , Red },
    { "CoordEdit.h" , Red },
    { "FontEdit.h" , Red },
    { "MCoordEdit.h" , Red },
    { "MixColorWindow.h" , Red },
    { "PointEdit.h" , Red },
    { "RatioEdit.h" , Red }
   }
  };

Dir Dir4=
  {
   "video",
   New,
   {
    &Dir8,
    &Dir9,
    &Dir10
   },
   {
    { "BindBagProxy.cpp" , Ignore },
    { "BookFrame.cpp" , Red },
    { "ConfigBinder.cpp" , Green },
    { "ConfigEditor.cpp" , Red },
    { "ConfigStore.cpp" , Green },
    { "DirFrame.cpp" , Green },
    { "ExceptionFrame.cpp" , Green },
    { "FavFrame.cpp" , Green },
    { "FavList.cpp" , Green },
    { "FigureLib.cpp" , Yellow },
    { "FileFrame.cpp" , Green },
    { "FontReplace.cpp" , Green },
    { "FrameBase.cpp" , Green },
    { "FrameClient.cpp" , Yellow },
    { "Layout.cpp" , Yellow },
    { "LayoutCombo.cpp" , Yellow },
    { "Menu.cpp" , Green },
    { "MessageFrame.cpp" , Green },
    { "MinSizeType.cpp" , Green },
    { "ShapeLib.cpp" , Ignore },
    { "ToolFrame.cpp" , Green },
    { "UserPreference.cpp" , Yellow },
    { "WindowLib.cpp" , Ignore },
    { "ConfigTypes.ddl" , Ignore },
    { "FavData.ddl" , Ignore },
    { "FontMap.ddl" , Ignore },
    { "HitDirs.ddl" , Ignore },
    { "FavData.TypeDef.gen.h" , Ignore },
    { "FontMap.TypeDef.gen.h" , Ignore },
    { "HitDirs.TypeDef.gen.h" , Ignore },
    { "FavData.TypeSet.gen.h" , Ignore },
    { "FontMap.TypeSet.gen.h" , Ignore },
    { "HitDirs.TypeSet.gen.h" , Ignore }
   }
  };

Dir Dir8=
  {
   "book",
   New,
   {
   },
   {
    { "Book.cpp" , Green },
    { "BookClient.cpp" , Red },
    { "BookWindow.cpp" , Green },
    { "DrawBook.cpp" , Green },
    { "DrawBookTools.cpp" , Green },
    { "SelectFrames.cpp" , Green },
    { "SpanLenEngine.cpp" , Green },
    { "Book1.ddl" , Ignore },
    { "Book1.Pretext.gen.h" , Ignore },
    { "Book1.TypeSet.gen.h" , Ignore }
   }
  };

Dir Dir9=
  {
   "lib",
   Green,
   {
   },
   {
    { "Shape.AllButton.cpp" , Green },
    { "Window.Blank.cpp" , Green },
    { "Shape.Button.cpp" , Green },
    { "Window.Button.cpp" , Ignore },
    { "Shape.ButtonState.cpp" , Ignore },
    { "Shape.Check.cpp" , Green },
    { "Window.Check.cpp" , Ignore },
    { "Shape.CheckState.cpp" , Green },
    { "Shape.Contour.cpp" , Green },
    { "Window.Decor.cpp" , Ignore },
    { "Shape.DragFrame.cpp" , Green },
    { "Window.DragFrame.cpp" , Ignore },
    { "Window.FireButton.cpp" , Ignore },
    { "Shape.FixedFrame.cpp" , Green },
    { "Shape.FrameBase.cpp" , Green },
    { "Shape.Info.cpp" , Green },
    { "Window.Info.cpp" , Ignore },
    { "Shape.Label.cpp" , Green },
    { "Shape.Light.cpp" , Green },
    { "Window.Light.cpp" , Ignore },
    { "Shape.Line.cpp" , Green },
    { "Shape.LineEdit.cpp" , Green },
    { "Window.LineEdit.cpp" , Green },
    { "Shape.MoveButton.cpp" , Green },
    { "Shape.Progress.cpp" , Green },
    { "Window.Progress.cpp" , Ignore },
    { "Shape.Radio.cpp" , Green },
    { "Window.Radio.cpp" , Green },
    { "Shape.RunButton.cpp" , Green },
    { "Window.RunButton.cpp" , Ignore },
    { "Shape.Scroll.cpp" , Green },
    { "Window.Scroll.cpp" , Ignore },
    { "Shape.ScrollList.cpp" , Green },
    { "Window.ScrollList.cpp" , Ignore },
    { "Window.Scrollable.cpp" , Ignore },
    { "Shape.ShiftSwitch.cpp" , Green },
    { "Shape.SimpleTextList.cpp" , Green },
    { "Window.SimpleTextList.cpp" , Ignore },
    { "Shape.Slider.cpp" , Green },
    { "Window.Slider.cpp" , Ignore },
    { "Shape.Spinor.cpp" , Green },
    { "Window.Spinor.cpp" , Ignore },
    { "Shape.Split.cpp" , Green },
    { "Window.Split.cpp" , Ignore },
    { "Shape.Switch.cpp" , Green },
    { "Shape.Text.cpp" , Green },
    { "Window.Text.cpp" , Ignore },
    { "Shape.TextLine.cpp" , Green },
    { "Window.TextLine.cpp" , Ignore }
   }
  };

Dir Dir10=
  {
   "pref",
   New,
   {
   },
   {
    { "ColorEdit.cpp" , Red },
    { "ColorListWindow.cpp" , Red },
    { "CoordEdit.cpp" , Red },
    { "FontEdit.cpp" , Red },
    { "MCoordEdit.cpp" , Red },
    { "MixColorWindow.cpp" , Red },
    { "PointEdit.cpp" , Red },
    { "RatioEdit.cpp" , Red }
   }
  };

