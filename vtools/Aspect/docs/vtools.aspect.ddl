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
    &Dir9,
    &Dir10
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
    &Dir11,
    &Dir12,
    &Dir13,
    &Dir14,
    &Dir15
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
    &Dir16,
    &Dir17,
    &Dir18
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
    &Dir19
   },
   {
   }
  };

Dir Dir4=
  {
   'Sample',
   New,
   {
    &Dir20,
    &Dir21,
    &Dir22
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
    &Dir23,
    &Dir24,
    &Dir25
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
    &Dir26,
    &Dir27,
    &Dir28
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
   'obj',
   New,
   {
   },
   {
    { 'empty' , New },
    { 'Application.dep' , New },
    { 'Aspect.dep' , New },
    { 'AspectData.dep' , New },
    { 'Client.dep' , New },
    { 'ErrorText.dep' , New },
    { 'main.dep' , New },
    { 'Makefile.dep' , New },
    { 'Application.o' , New },
    { 'Aspect.o' , New },
    { 'AspectData.o' , New },
    { 'Client.o' , New },
    { 'ErrorText.o' , New },
    { 'main.o' , New }
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
    &Dir29,
    &Dir30
   },
   {
   }
  };

Dir Dir14=
  {
   'obj',
   New,
   {
   },
   {
    { 'empty' , New },
    { 'Application.dep' , New },
    { 'Client.dep' , New },
    { 'Contour.dep' , New },
    { 'EditAngleWindow.dep' , New },
    { 'EditLengthWindow.dep' , New },
    { 'Editor.dep' , New },
    { 'EditRatioWindow.dep' , New },
    { 'Geometry.dep' , New },
    { 'GeometryWindow.dep' , New },
    { 'ItemListWindow.dep' , New },
    { 'main.dep' , New },
    { 'Makefile.dep' , New },
    { 'Parser.dep' , New },
    { 'ParserData.dep' , New },
    { 'Application.o' , New },
    { 'Client.o' , New },
    { 'Contour.o' , New },
    { 'EditAngleWindow.o' , New },
    { 'EditLengthWindow.o' , New },
    { 'Editor.o' , New },
    { 'EditRatioWindow.o' , New },
    { 'Geometry.o' , New },
    { 'GeometryWindow.o' , New },
    { 'ItemListWindow.o' , New },
    { 'main.o' , New },
    { 'Parser.o' , New },
    { 'ParserData.o' , New }
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

Dir Dir29=
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

Dir Dir30=
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

Dir Dir16=
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

Dir Dir17=
  {
   'obj',
   New,
   {
   },
   {
    { 'empty' , New },
    { 'Application.dep' , New },
    { 'Client.dep' , New },
    { 'Display.dep' , New },
    { 'main.dep' , New },
    { 'Makefile.dep' , New },
    { 'Application.o' , New },
    { 'Client.o' , New },
    { 'Display.o' , New },
    { 'main.o' , New }
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
    { 'Display.cpp' , New },
    { 'main.cpp' , New }
   }
  };

Dir Dir19=
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
   'obj',
   New,
   {
   },
   {
    { 'empty' , New },
    { 'Application.dep' , New },
    { 'Client.dep' , New },
    { 'main.dep' , New },
    { 'Makefile.dep' , New },
    { 'Sample.dep' , New },
    { 'Application.o' , New },
    { 'Client.o' , New },
    { 'main.o' , New },
    { 'Sample.o' , New }
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
    { 'Client.cpp' , New },
    { 'main.cpp' , New },
    { 'Sample.cpp' , New }
   }
  };

Dir Dir23=
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

Dir Dir24=
  {
   'obj',
   New,
   {
   },
   {
    { 'empty' , New },
    { 'Application.dep' , New },
    { 'Client.dep' , New },
    { 'main.dep' , New },
    { 'Makefile.dep' , New },
    { 'Application.o' , New },
    { 'Client.o' , New },
    { 'main.o' , New }
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
    { 'Client.cpp' , New },
    { 'main.cpp' , New }
   }
  };

Dir Dir26=
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

Dir Dir27=
  {
   'obj',
   New,
   {
   },
   {
    { 'empty' , New },
    { 'Application.dep' , New },
    { 'main.dep' , New },
    { 'Makefile.dep' , New },
    { 'TestFrame.dep' , New },
    { 'Application.o' , New },
    { 'main.o' , New },
    { 'TestFrame.o' , New }
   }
  };

Dir Dir28=
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

