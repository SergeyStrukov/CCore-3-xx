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
    { "ConfigBinder.h" , New },
    { "ConfigEditor.h" , New },
    { "ConfigStore.h" , New },
    { "DirFrame.h" , New },
    { "ExceptionFrame.h" , New },
    { "FavFrame.h" , New },
    { "FavList.h" , New },
    { "FigureLib.h" , Yellow },
    { "FileFrame.h" , New },
    { "FontReplace.h" , New },
    { "FrameBase.h" , New },
    { "FrameOf.h" , New },
    { "Layout.h" , New },
    { "LayoutCombo.h" , New },
    { "Menu.h" , New },
    { "MessageFrame.h" , New },
    { "MinSizeType.h" , New },
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
    { "Shape.AllButton.h" , Red },
    { "Window.Blank.h" , Green },
    { "Shape.Button.h" , Yellow },
    { "Window.Button.h" , Yellow },
    { "Shape.ButtonState.h" , Green },
    { "Shape.Check.h" , Green },
    { "Window.Check.h" , Green },
    { "Shape.CheckState.h" , Green },
    { "Shape.Contour.h" , Green },
    { "Window.Decor.h" , Green },
    { "Shape.DragFrame.h" , Yellow },
    { "Window.DragFrame.h" , Yellow },
    { "Window.FireButton.h" , Yellow },
    { "Shape.FixedFrame.h" , Yellow },
    { "Shape.FrameBase.h" , Yellow },
    { "Shape.Info.h" , Yellow },
    { "Window.Info.h" , Yellow },
    { "Shape.Label.h" , Green },
    { "Shape.Light.h" , Green },
    { "Window.Light.h" , Green },
    { "Shape.Line.h" , Green },
    { "Shape.LineEdit.h" , Yellow },
    { "Window.LineEdit.h" , Yellow },
    { "Shape.MoveButton.h" , Yellow },
    { "Shape.Progress.h" , Yellow },
    { "Window.Progress.h" , Yellow },
    { "Shape.Radio.h" , Yellow },
    { "Window.Radio.h" , Yellow },
    { "Shape.RunButton.h" , Yellow },
    { "Window.RunButton.h" , Yellow },
    { "Shape.Scroll.h" , Yellow },
    { "Window.Scroll.h" , Yellow },
    { "Shape.ScrollList.h" , Yellow },
    { "Window.ScrollList.h" , Yellow },
    { "Window.Scrollable.h" , Yellow },
    { "Shape.ShiftSwitch.h" , Green },
    { "Shape.SimpleTextList.h" , Yellow },
    { "Window.SimpleTextList.h" , Yellow },
    { "Shape.Slider.h" , Yellow },
    { "Window.Slider.h" , Yellow },
    { "Shape.Spinor.h" , Yellow },
    { "Window.Spinor.h" , Yellow },
    { "Shape.Split.h" , Yellow },
    { "Window.Split.h" , Yellow },
    { "Shape.Switch.h" , Green },
    { "Shape.Text.h" , Green },
    { "Window.Text.h" , Green },
    { "Shape.TextLine.h" , Yellow },
    { "Window.TextLine.h" , Yellow }
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
    { "ConfigBinder.cpp" , New },
    { "ConfigEditor.cpp" , New },
    { "ConfigStore.cpp" , New },
    { "DirFrame.cpp" , New },
    { "ExceptionFrame.cpp" , New },
    { "FavFrame.cpp" , New },
    { "FavList.cpp" , New },
    { "FigureLib.cpp" , Yellow },
    { "FileFrame.cpp" , New },
    { "FontReplace.cpp" , New },
    { "FrameBase.cpp" , New },
    { "FrameOf.cpp" , New },
    { "Layout.cpp" , New },
    { "LayoutCombo.cpp" , New },
    { "Menu.cpp" , New },
    { "MessageFrame.cpp" , New },
    { "MinSizeType.cpp" , New },
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
    { "Shape.AllButton.cpp" , Red },
    { "Window.Blank.cpp" , Green },
    { "Shape.Button.cpp" , Yellow },
    { "Window.Button.cpp" , Ignore },
    { "Shape.ButtonState.cpp" , Ignore },
    { "Shape.Check.cpp" , Green },
    { "Window.Check.cpp" , Ignore },
    { "Shape.CheckState.cpp" , Green },
    { "Shape.Contour.cpp" , Green },
    { "Window.Decor.cpp" , Ignore },
    { "Shape.DragFrame.cpp" , Red },
    { "Window.DragFrame.cpp" , Ignore },
    { "Window.FireButton.cpp" , Ignore },
    { "Shape.FixedFrame.cpp" , Red },
    { "Shape.FrameBase.cpp" , Red },
    { "Shape.Info.cpp" , Red },
    { "Window.Info.cpp" , Ignore },
    { "Shape.Label.cpp" , Green },
    { "Shape.Light.cpp" , Green },
    { "Window.Light.cpp" , Ignore },
    { "Shape.Line.cpp" , Green },
    { "Shape.LineEdit.cpp" , Red },
    { "Window.LineEdit.cpp" , Yellow },
    { "Shape.MoveButton.cpp" , Red },
    { "Shape.Progress.cpp" , Red },
    { "Window.Progress.cpp" , Ignore },
    { "Shape.Radio.cpp" , Yellow },
    { "Window.Radio.cpp" , Yellow },
    { "Shape.RunButton.cpp" , Yellow },
    { "Window.RunButton.cpp" , Ignore },
    { "Shape.Scroll.cpp" , Red },
    { "Window.Scroll.cpp" , Ignore },
    { "Shape.ScrollList.cpp" , Red },
    { "Window.ScrollList.cpp" , Ignore },
    { "Window.Scrollable.cpp" , Ignore },
    { "Shape.ShiftSwitch.cpp" , Green },
    { "Shape.SimpleTextList.cpp" , Red },
    { "Window.SimpleTextList.cpp" , Ignore },
    { "Shape.Slider.cpp" , Red },
    { "Window.Slider.cpp" , Ignore },
    { "Shape.Spinor.cpp" , Red },
    { "Window.Spinor.cpp" , Ignore },
    { "Shape.Split.cpp" , Yellow },
    { "Window.Split.cpp" , Ignore },
    { "Shape.Switch.cpp" , Green },
    { "Shape.Text.cpp" , Green },
    { "Window.Text.cpp" , Ignore },
    { "Shape.TextLine.cpp" , Red },
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

