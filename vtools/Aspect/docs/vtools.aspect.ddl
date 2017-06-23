//#include <Aspect.ddl>

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
    &Dir6
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
    &Dir7,
    &Dir8,
    &Dir9
   },
   {
    { 'Makefile' , New },
    { 'Makefile.cpp-files' , New },
    { 'Makefile.files' , New },
    { 'Makefile.s-files' , New }
   }
  };

Dir Dir1=
  {
   'ContourLab',
   New,
   {
    &Dir10,
    &Dir11,
    &Dir12,
    &Dir13
   },
   {
    { 'Makefile' , New },
    { 'Makefile.cpp-files' , New },
    { 'ContourLab.exe' , New },
    { 'Makefile.files' , New },
    { 'Makefile.s-files' , New }
   }
  };

Dir Dir2=
  {
   'DDLDisplay',
   New,
   {
    &Dir14,
    &Dir15
   },
   {
    { 'Makefile' , New },
    { 'Makefile.cpp-files' , New },
    { 'Makefile.files' , New },
    { 'Makefile.s-files' , New }
   }
  };

Dir Dir3=
  {
   'EventView',
   New,
   {
    &Dir16
   },
   {
   }
  };

Dir Dir4=
  {
   'Sample',
   New,
   {
    &Dir17,
    &Dir18
   },
   {
    { 'Makefile' , New },
    { 'Makefile.cpp-files' , New },
    { 'Sample.exe' , New },
    { 'Makefile.files' , New },
    { 'Makefile.s-files' , New }
   }
  };

Dir Dir5=
  {
   'SubLab',
   New,
   {
    &Dir19,
    &Dir20
   },
   {
    { 'Makefile' , New },
    { 'Makefile.cpp-files' , New },
    { 'SubLab.exe' , New },
    { 'Makefile.files' , New },
    { 'Makefile.s-files' , New }
   }
  };

Dir Dir6=
  {
   'UserPreference',
   New,
   {
    &Dir21,
    &Dir22
   },
   {
    { 'Makefile' , New },
    { 'Makefile.cpp-files' , New },
    { 'Makefile.files' , New },
    { 'Makefile.s-files' , New }
   }
  };

Dir Dir7=
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

Dir Dir8=
  {
   'inc',
   New,
   {
   },
   {
    { 'Application.h' , New },
    { 'Aspect.h' , New },
    { 'AspectData.h' , New },
    { 'Client.h' , New },
    { 'ErrorText.h' , New }
   }
  };

Dir Dir9=
  {
   'src',
   New,
   {
   },
   {
    { 'Application.cpp' , New },
    { 'Aspect.cpp' , New },
    { 'AspectData.cpp' , New },
    { 'Client.cpp' , New },
    { 'ErrorText.cpp' , New },
    { 'main.cpp' , New },
    { 'Aspect.ddl' , New },
    { 'Aspect.TypeDef.gen.h' , New },
    { 'Aspect.TypeSet.gen.h' , New }
   }
  };

Dir Dir10=
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

Dir Dir11=
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

Dir Dir12=
  {
   'lang',
   New,
   {
    &Dir23,
    &Dir24
   },
   {
   }
  };

Dir Dir13=
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

Dir Dir23=
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

Dir Dir24=
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

Dir Dir14=
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

Dir Dir15=
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

Dir Dir16=
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

Dir Dir17=
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

Dir Dir18=
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

Dir Dir19=
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

Dir Dir20=
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

Dir Dir21=
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

Dir Dir22=
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

