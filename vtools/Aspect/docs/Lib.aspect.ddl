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
    { "BindBagProxy.h" , New },
    { "BookFrame.h" , New },
    { "ConfigBinder.h" , New },
    { "ConfigEditor.h" , New },
    { "ConfigStore.h" , New },
    { "DirFrame.h" , New },
    { "ExceptionFrame.h" , New },
    { "FavFrame.h" , New },
    { "FavList.h" , New },
    { "FigureLib.h" , Green },
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
    { "Book1.TypeDef.gen.h" , New }
   }
  };

Dir Dir6=
  {
   "lib",
   New,
   {
   },
   {
    { "Shape.AllButton.h" , New },
    { "Window.Blank.h" , Ignore },
    { "Shape.Button.h" , Green },
    { "Window.Button.h" , Ignore },
    { "Shape.ButtonState.h" , New },
    { "Shape.Check.h" , Green },
    { "Window.Check.h" , Ignore },
    { "Shape.Contour.h" , Green },
    { "Window.Decor.h" , Ignore },
    { "Shape.DragFrame.h" , New },
    { "Window.DragFrame.h" , Ignore },
    { "Window.FireButton.h" , Ignore },
    { "Shape.FixedFrame.h" , New },
    { "Shape.FrameBase.h" , New },
    { "Shape.Info.h" , New },
    { "Window.Info.h" , Ignore },
    { "Shape.Label.h" , Green },
    { "Shape.Light.h" , Green },
    { "Window.Light.h" , Ignore },
    { "Shape.Line.h" , Green },
    { "Shape.LineEdit.h" , New },
    { "Window.LineEdit.h" , Ignore },
    { "Shape.MoveButton.h" , New },
    { "Shape.Progress.h" , New },
    { "Window.Progress.h" , Ignore },
    { "Shape.Radio.h" , Green },
    { "Window.Radio.h" , Ignore },
    { "Shape.RunButton.h" , Green },
    { "Window.RunButton.h" , Ignore },
    { "Shape.Scroll.h" , New },
    { "Window.Scroll.h" , Ignore },
    { "Shape.ScrollList.h" , New },
    { "Window.ScrollList.h" , Ignore },
    { "Window.Scrollable.h" , Ignore },
    { "Shape.ShiftSwitch.h" , New },
    { "Shape.SimpleTextList.h" , New },
    { "Window.SimpleTextList.h" , Ignore },
    { "Shape.Slider.h" , New },
    { "Window.Slider.h" , Ignore },
    { "Shape.Spinor.h" , New },
    { "Window.Spinor.h" , Ignore },
    { "Shape.Split.h" , Green },
    { "Window.Split.h" , Ignore },
    { "Shape.Switch.h" , Green },
    { "Shape.Text.h" , New },
    { "Window.Text.h" , Ignore },
    { "Shape.TextLine.h" , New },
    { "Window.TextLine.h" , Ignore }
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
    { "BindBagProxy.cpp" , New },
    { "BookFrame.cpp" , New },
    { "ConfigBinder.cpp" , New },
    { "ConfigEditor.cpp" , New },
    { "ConfigStore.cpp" , New },
    { "DirFrame.cpp" , New },
    { "ExceptionFrame.cpp" , New },
    { "FavFrame.cpp" , New },
    { "FavList.cpp" , New },
    { "FigureLib.cpp" , Green },
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
    { "FavData.ddl" , New },
    { "FontMap.ddl" , Ignore },
    { "HitDirs.ddl" , Ignore },
    { "FavData.TypeDef.gen.h" , New },
    { "FontMap.TypeDef.gen.h" , Ignore },
    { "HitDirs.TypeDef.gen.h" , Ignore },
    { "FavData.TypeSet.gen.h" , New },
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
    { "Shape.AllButton.cpp" , New },
    { "Window.Blank.cpp" , Ignore },
    { "Shape.Button.cpp" , Green },
    { "Window.Button.cpp" , Ignore },
    { "Shape.ButtonState.cpp" , New },
    { "Shape.Check.cpp" , Green },
    { "Window.Check.cpp" , Ignore },
    { "Shape.Contour.cpp" , Green },
    { "Window.Decor.cpp" , Ignore },
    { "Shape.DragFrame.cpp" , New },
    { "Window.DragFrame.cpp" , Ignore },
    { "Window.FireButton.cpp" , Ignore },
    { "Shape.FixedFrame.cpp" , New },
    { "Shape.FrameBase.cpp" , New },
    { "Shape.Info.cpp" , New },
    { "Window.Info.cpp" , Ignore },
    { "Shape.Label.cpp" , Green },
    { "Shape.Light.cpp" , Green },
    { "Window.Light.cpp" , Ignore },
    { "Shape.Line.cpp" , Green },
    { "Shape.LineEdit.cpp" , New },
    { "Window.LineEdit.cpp" , Ignore },
    { "Shape.MoveButton.cpp" , New },
    { "Shape.Progress.cpp" , New },
    { "Window.Progress.cpp" , Ignore },
    { "Shape.Radio.cpp" , Green },
    { "Window.Radio.cpp" , Ignore },
    { "Shape.RunButton.cpp" , Green },
    { "Window.RunButton.cpp" , Ignore },
    { "Shape.Scroll.cpp" , New },
    { "Window.Scroll.cpp" , Ignore },
    { "Shape.ScrollList.cpp" , New },
    { "Window.ScrollList.cpp" , Ignore },
    { "Window.Scrollable.cpp" , Ignore },
    { "Shape.ShiftSwitch.cpp" , New },
    { "Shape.SimpleTextList.cpp" , New },
    { "Window.SimpleTextList.cpp" , Ignore },
    { "Shape.Slider.cpp" , New },
    { "Window.Slider.cpp" , Ignore },
    { "Shape.Spinor.cpp" , New },
    { "Window.Spinor.cpp" , Ignore },
    { "Shape.Split.cpp" , Green },
    { "Window.Split.cpp" , Ignore },
    { "Shape.Switch.cpp" , Green },
    { "Shape.Text.cpp" , New },
    { "Window.Text.cpp" , Ignore },
    { "Shape.TextLine.cpp" , New },
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

