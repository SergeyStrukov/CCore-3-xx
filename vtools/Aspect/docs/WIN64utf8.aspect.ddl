//include <Aspect.ddl>

Aspect Data=
 {
  "../../../../../../home64/C++/CCore-3-xx/Target/WIN64utf8",
  {
   "",
   New,
   {
    &Dir0,
    &Dir1
   },
   {
    { "Makefile" , Green },
    { "CCore.a" , Green },
    { "Makefile.files" , Green },
    { "Makefile.tools" , Green }
   }
  }
 };

Dir Dir0=
  {
   "CCore",
   New,
   {
    &Dir2,
    &Dir3,
    &Dir4
   },
   {
   }
  };

Dir Dir1=
  {
   "test",
   Green,
   {
   },
   {
    { "Makefile" , Green },
    { "main.cpp" , Green },
    { "main.exe" , Green },
    { "Makefile.files" , Green }
   }
  };

Dir Dir2=
  {
   "inc",
   New,
   {
    &Dir5,
    &Dir6,
    &Dir7,
    &Dir8,
    &Dir9,
    &Dir10
   },
   {
    { "PlatformRandom.h" , Green }
   }
  };

Dir Dir3=
  {
   "src",
   New,
   {
    &Dir11,
    &Dir12,
    &Dir13,
    &Dir14,
    &Dir15,
    &Dir16
   },
   {
    { "PlanInit_CCore.cpp" , Green }
   }
  };

Dir Dir4=
  {
   "test",
   Green,
   {
   },
   {
    { "test6001.Atomic.cpp" , Green },
    { "test6003.Blank.cpp" , Green },
    { "test6011.Char.cpp" , Green },
    { "test6004.IntegerFastAlgo.cpp" , Green },
    { "test6006.IntelAES.cpp" , Green },
    { "test6005.IntelRandom.cpp" , Green },
    { "test6007.MemAlloc.cpp" , Green },
    { "test6010.Quick.cpp" , Green },
    { "test6012.SysError.cpp" , Green },
    { "test6009.SysFile.cpp" , Green },
    { "test6008.Time.cpp" , Green },
    { "test6002.WIN64.cpp" , Green }
   }
  };

Dir Dir5=
  {
   "base",
   Green,
   {
   },
   {
    { "PlatformBase.h" , Green },
    { "Quick.h" , Green }
   }
  };

Dir Dir6=
  {
   "crypton",
   Green,
   {
   },
   {
    { "IntelAES.h" , Green },
    { "IntelCPUID.h" , Green },
    { "IntelRandom.h" , Green },
    { "PlatformAES.h" , Green }
   }
  };

Dir Dir7=
  {
   "math",
   Green,
   {
   },
   {
    { "IntegerFastAlgo.h" , Green }
   }
  };

Dir Dir8=
  {
   "sys",
   New,
   {
   },
   {
    { "SysAbort.h" , Green },
    { "SysAtomic.h" , Green },
    { "SysCon.h" , Green },
    { "SysError.h" , Green },
    { "SysFile.h" , New },
    { "SysFileInternal.h" , New },
    { "SysFileSystem.h" , New },
    { "SysLaunchPath.h" , New },
    { "SysMemPage.h" , Green },
    { "SysNet.h" , New },
    { "SysPlanInit.h" , Green },
    { "SysProp.h" , Green },
    { "SysSem.h" , Green },
    { "SysTask.h" , Green },
    { "SysTime.h" , Green },
    { "SysTlsSlot.h" , Green },
    { "SysUtf8.h" , Green },
    { "SysWait.h" , Green },
    { "SysWaitInternal.h" , Green }
   }
  };

Dir Dir9=
  {
   "video",
   New,
   {
   },
   {
    { "Desktop.h" , New },
    { "InternalDesktop.h" , New },
    { "InternalHost.h" , New },
    { "InternalUtils.h" , New }
   }
  };

Dir Dir10=
  {
   "win64",
   New,
   {
   },
   {
    { "Win64.h" , New },
    { "Win64gui.h" , New }
   }
  };

Dir Dir11=
  {
   "base",
   Green,
   {
   },
   {
    { "PlatformBase.cpp" , Green },
    { "Quick.cpp" , Green },
    { "PlatformBase.s" , Green },
    { "Quick.s" , Green }
   }
  };

Dir Dir12=
  {
   "crypton",
   Green,
   {
   },
   {
    { "IntelAES.cpp" , Green },
    { "IntelCPUID.cpp" , Green },
    { "IntelRandom.cpp" , Green },
    { "IntelAES.s" , Green },
    { "IntelCPUID.s" , Green },
    { "IntelRandom.s" , Green }
   }
  };

Dir Dir13=
  {
   "math",
   Green,
   {
   },
   {
    { "IntegerFastAlgo.cpp" , Green }
   }
  };

Dir Dir14=
  {
   "sys",
   New,
   {
   },
   {
    { "SysAbort.cpp" , Green },
    { "SysAtomic.cpp" , Green },
    { "SysCon.cpp" , Green },
    { "SysError.cpp" , Green },
    { "SysFile.cpp" , New },
    { "SysFileInternal.cpp" , New },
    { "SysFileSystem.cpp" , New },
    { "SysLaunchPath.cpp" , New },
    { "SysMemPage.cpp" , Green },
    { "SysNet.cpp" , New },
    { "SysPlanInit.cpp" , Green },
    { "SysProp.cpp" , Green },
    { "SysSem.cpp" , Green },
    { "SysTask.cpp" , Green },
    { "SysTime.cpp" , Green },
    { "SysTlsSlot.cpp" , Green },
    { "SysUtf8.cpp" , Green },
    { "SysWait.cpp" , Green },
    { "SysWaitInternal.cpp" , Green },
    { "SysAtomic.s" , Green },
    { "SysTime.s" , Green }
   }
  };

Dir Dir15=
  {
   "video",
   New,
   {
   },
   {
    { "Desktop.cpp" , New },
    { "InternalDesktop.cpp" , New },
    { "InternalHost.cpp" , New },
    { "InternalUtils.cpp" , New }
   }
  };

Dir Dir16=
  {
   "win64",
   Green,
   {
   },
   {
    { "Win64.cpp" , Green }
   }
  };

