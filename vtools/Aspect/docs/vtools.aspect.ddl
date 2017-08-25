//include <Aspect.ddl>

Aspect Data=
 {
  '../..',
  {
   '',
   New,
   {
    &Dir0,
    &Dir1,
    &Dir2,
    &Dir3,
    &Dir4,
    &Dir5,
    &Dir6,
    &Dir7
   },
   {
    { 'Makefile' , New }
   }
  }
 };

Dir Dir0=
  {
   'Aspect',
   New,
   {
    &Dir8,
    &Dir9,
    &Dir10
   },
   {
    { 'Makefile' , New },
    { 'Makefile.files' , New }
   }
  };

Dir Dir1=
  {
   'ContourLab',
   New,
   {
    &Dir11,
    &Dir12,
    &Dir13,
    &Dir14
   },
   {
    { 'Makefile' , New },
    { 'ContourLab.exe' , New },
    { 'Makefile.files' , New }
   }
  };

Dir Dir2=
  {
   'DDLDisplay',
   New,
   {
    &Dir15,
    &Dir16
   },
   {
    { 'Makefile' , New },
    { 'Makefile.files' , New }
   }
  };

Dir Dir3=
  {
   'EventView',
   New,
   {
    &Dir17
   },
   {
   }
  };

Dir Dir4=
  {
   'RandomId',
   New,
   {
    &Dir18,
    &Dir19
   },
   {
    { 'Makefile' , New },
    { 'Makefile.files' , New }
   }
  };

Dir Dir5=
  {
   'Sample',
   New,
   {
    &Dir20,
    &Dir21
   },
   {
    { 'Makefile' , New },
    { 'Sample.exe' , New },
    { 'Makefile.files' , New }
   }
  };

Dir Dir6=
  {
   'SubLab',
   New,
   {
    &Dir22,
    &Dir23
   },
   {
    { 'Makefile' , New },
    { 'SubLab.exe' , New },
    { 'Makefile.files' , New }
   }
  };

Dir Dir7=
  {
   'UserPreference',
   New,
   {
    &Dir24,
    &Dir25
   },
   {
    { 'Makefile' , New },
    { 'Makefile.files' , New }
   }
  };

Dir Dir8=
  {
   'docs',
   New,
   {
   },
   {
    { 'gcc7.aspect.ddl' , New },
    { 'vtools.aspect.ddl' , New }
   }
  };

Dir Dir9=
  {
   'inc',
   New,
   {
   },
   {
    { 'Application.h' , New },
    { 'AppState.h' , New },
    { 'Aspect.h' , New },
    { 'AspectData.h' , New },
    { 'Client.h' , New },
    { 'ErrorText.h' , New }
   }
  };

Dir Dir10=
  {
   'src',
   New,
   {
   },
   {
    { 'Application.cpp' , New },
    { 'AppState.cpp' , New },
    { 'Aspect.cpp' , New },
    { 'AspectData.cpp' , New },
    { 'Client.cpp' , New },
    { 'ErrorText.cpp' , New },
    { 'main.cpp' , New },
    { 'AppState.ddl' , New },
    { 'Aspect.ddl' , New },
    { 'AppState.TypeDef.gen.h' , New },
    { 'Aspect.TypeDef.gen.h' , New },
    { 'AppState.TypeSet.gen.h' , New },
    { 'Aspect.TypeSet.gen.h' , New }
   }
  };

Dir Dir11=
  {
   'docs',
   New,
   {
   },
   {
    { 'loop.cont.ddl' , New },
    { 'question.cont.ddl' , New },
    { 'test.cont.ddl' , New },
    { 'test1.cont.ddl' , New },
    { 'test2.cont.ddl' , New },
    { 'triangle.cont.ddl' , New },
    { 'Дезарг.cont.ddl' , New }
   }
  };

Dir Dir12=
  {
   'inc',
   New,
   {
   },
   {
    { 'Application.h' , New },
    { 'Client.h' , New },
    { 'Contour.h' , New },
    { 'EditAngleWindow.h' , New },
    { 'EditLengthWindow.h' , New },
    { 'Editor.h' , New },
    { 'EditRatioWindow.h' , New },
    { 'Geometry.h' , New },
    { 'GeometryWindow.h' , New },
    { 'ItemListWindow.h' , New },
    { 'Parser.h' , New }
   }
  };

Dir Dir13=
  {
   'lang',
   New,
   {
    &Dir26,
    &Dir27
   },
   {
   }
  };

Dir Dir14=
  {
   'src',
   New,
   {
   },
   {
    { 'Application.cpp' , New },
    { 'Client.cpp' , New },
    { 'Contour.cpp' , New },
    { 'EditAngleWindow.cpp' , New },
    { 'EditLengthWindow.cpp' , New },
    { 'Editor.cpp' , New },
    { 'EditRatioWindow.cpp' , New },
    { 'Geometry.cpp' , New },
    { 'GeometryWindow.cpp' , New },
    { 'ItemListWindow.cpp' , New },
    { 'main.cpp' , New },
    { 'Parser.cpp' , New },
    { 'ParserData.cpp' , New },
    { 'Contour.ddl' , New },
    { 'Contour.TypeDef.gen.h' , New },
    { 'Contour.TypeSet.gen.h' , New }
   }
  };

Dir Dir26=
  {
   'Formula',
   New,
   {
   },
   {
    { 'Makefile' , New },
    { 'Formula.gen.cpp_' , New },
    { 'Formula.ddl' , New },
    { 'Formula.gen.h_' , New },
    { 'Formula.lang' , New },
    { 'Formula.txt' , New }
   }
  };

Dir Dir27=
  {
   'Pad',
   New,
   {
   },
   {
    { 'Makefile' , New },
    { 'Pad.ddl' , New },
    { 'Pad.lang' , New },
    { 'Pad.txt' , New }
   }
  };

Dir Dir15=
  {
   'inc',
   New,
   {
   },
   {
    { 'Application.h' , New },
    { 'Client.h' , New },
    { 'Display.h' , New }
   }
  };

Dir Dir16=
  {
   'src',
   New,
   {
   },
   {
    { 'Application.cpp' , New },
    { 'Client.cpp' , New },
    { 'Display.cpp' , New },
    { 'main.cpp' , New }
   }
  };

Dir Dir17=
  {
   'prototype',
   New,
   {
   },
   {
    { 'EventView.exe.config' , New },
    { 'EventView.exe' , New }
   }
  };

Dir Dir18=
  {
   'inc',
   New,
   {
   },
   {
    { 'Application.h' , New },
    { 'Client.h' , New },
    { 'RandomId.h' , New }
   }
  };

Dir Dir19=
  {
   'src',
   New,
   {
   },
   {
    { 'Application.cpp' , New },
    { 'Client.cpp' , New },
    { 'main.cpp' , New },
    { 'RandomId.cpp' , New }
   }
  };

Dir Dir20=
  {
   'inc',
   New,
   {
   },
   {
    { 'Application.h' , New },
    { 'Client.h' , New },
    { 'Sample.h' , New }
   }
  };

Dir Dir21=
  {
   'src',
   New,
   {
   },
   {
    { 'Application.cpp' , New },
    { 'Client.cpp' , New },
    { 'main.cpp' , New },
    { 'Sample.cpp' , New }
   }
  };

Dir Dir22=
  {
   'inc',
   New,
   {
   },
   {
    { 'Application.h' , New },
    { 'Client.h' , New }
   }
  };

Dir Dir23=
  {
   'src',
   New,
   {
   },
   {
    { 'Application.cpp' , New },
    { 'Client.cpp' , New },
    { 'main.cpp' , New }
   }
  };

Dir Dir24=
  {
   'inc',
   New,
   {
   },
   {
    { 'Application.h' , New },
    { 'TestFrame.h' , New }
   }
  };

Dir Dir25=
  {
   'src',
   New,
   {
   },
   {
    { 'Application.cpp' , New },
    { 'main.cpp' , New },
    { 'TestFrame.cpp' , New }
   }
  };

