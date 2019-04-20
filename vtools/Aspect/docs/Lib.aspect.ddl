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
    { "BookFrame.h" , New },
    { "ConfigBinder.h" , Green },
    { "ConfigEditor.h" , New },
    { "ConfigStore.h" , Green },
    { "DirFrame.h" , New },
    { "ExceptionFrame.h" , Red },
    { "FavFrame.h" , New },
    { "FavList.h" , New },
    { "FigureLib.h" , Yellow },
    { "FileFrame.h" , New },
    { "FontReplace.h" , New },
    { "FrameBase.h" , New },
    { "FrameOf.h" , New },
    { "Layout.h" , Red },
    { "LayoutCombo.h" , Red },
    { "Menu.h" , Red },
    { "MessageFrame.h" , Red },
    { "MinSizeType.h" , Green },
    { "ShapeLib.h" , Ignore },
    { "ToolFrame.h" , New },
    { "UserPreference.h" , New },
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
    { "Book.h" , New },
    { "BookClient.h" , New },
    { "BookWindow.h" , New },
    { "DrawBook.h" , New },
    { "DrawBookTools.h" , New },
    { "SelectFrames.h" , New },
    { "SpanLenEngine.h" , New },
    { "Book1.TypeDef.gen.h" , Ignore }
   }
  };

Dir Dir6=
  {
   "lib",
   Red,
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
    { "Shape.DragFrame.h" , Yellow },
    { "Window.DragFrame.h" , Yellow },
    { "Window.FireButton.h" , Green },
    { "Shape.FixedFrame.h" , Yellow },
    { "Shape.FrameBase.h" , Yellow },
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
    { "ColorEdit.h" , New },
    { "ColorListWindow.h" , New },
    { "CoordEdit.h" , New },
    { "FontEdit.h" , New },
    { "MCoordEdit.h" , New },
    { "MixColorWindow.h" , New },
    { "PointEdit.h" , New },
    { "RatioEdit.h" , New }
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
    { "BookFrame.cpp" , New },
    { "ConfigBinder.cpp" , Green },
    { "ConfigEditor.cpp" , New },
    { "ConfigStore.cpp" , Green },
    { "DirFrame.cpp" , New },
    { "ExceptionFrame.cpp" , Red },
    { "FavFrame.cpp" , New },
    { "FavList.cpp" , New },
    { "FigureLib.cpp" , Yellow },
    { "FileFrame.cpp" , New },
    { "FontReplace.cpp" , New },
    { "FrameBase.cpp" , New },
    { "FrameOf.cpp" , New },
    { "Layout.cpp" , Red },
    { "LayoutCombo.cpp" , Red },
    { "Menu.cpp" , Red },
    { "MessageFrame.cpp" , Red },
    { "MinSizeType.cpp" , Green },
    { "ShapeLib.cpp" , Ignore },
    { "ToolFrame.cpp" , New },
    { "UserPreference.cpp" , New },
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
    { "Book.cpp" , New },
    { "BookClient.cpp" , New },
    { "BookWindow.cpp" , New },
    { "DrawBook.cpp" , New },
    { "DrawBookTools.cpp" , New },
    { "SelectFrames.cpp" , New },
    { "SpanLenEngine.cpp" , New },
    { "Book1.ddl" , New },
    { "Book1.Pretext.gen.h" , New },
    { "Book1.TypeSet.gen.h" , New }
   }
  };

Dir Dir9=
  {
   "lib",
   New,
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
    { "Shape.DragFrame.cpp" , Yellow },
    { "Window.DragFrame.cpp" , Ignore },
    { "Window.FireButton.cpp" , Ignore },
    { "Shape.FixedFrame.cpp" , Yellow },
    { "Shape.FrameBase.cpp" , Yellow },
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
    { "ColorEdit.cpp" , New },
    { "ColorListWindow.cpp" , New },
    { "CoordEdit.cpp" , New },
    { "FontEdit.cpp" , New },
    { "MCoordEdit.cpp" , New },
    { "MixColorWindow.cpp" , New },
    { "PointEdit.cpp" , New },
    { "RatioEdit.cpp" , New }
   }
  };

