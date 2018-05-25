//include <Aspect.ddl>

Aspect Data=
 {
  "../../../../../../winbuntu/C++/CCore-3-xx/Target/LIN64utf8",
  {
   "",
   New,
   {
    &Dir0,
    &Dir1,
    &Dir2
   },
   {
    { "Makefile" , Ignore },
    { "CCore.a" , Ignore },
    { "Makefile.files" , Ignore },
    { "Makefile.tools" , Ignore }
   }
  }
 };

Dir Dir0=
  {
   "CCore",
   New,
   {
    &Dir3,
    &Dir4,
    &Dir5
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
   "tools",
   Ignore,
   {
    &Dir6
   },
   {
   }
  };

Dir Dir3=
  {
   "inc",
   New,
   {
    &Dir7,
    &Dir8,
    &Dir9,
    &Dir10,
    &Dir11
   },
   {
    { "PlatformRandom.h" , Green }
   }
  };

Dir Dir4=
  {
   "src",
   New,
   {
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

Dir Dir5=
  {
   "test",
   New,
   {
   },
   {
    { "test6011.Char.cpp" , New },
    { "test6012.Con.cpp" , New },
    { "test6005.IntegerFastAlgo.cpp" , New },
    { "test6004.IntelAES.cpp" , New },
    { "test6003.IntelRandom.cpp" , New },
    { "test6009.KeySym.cpp" , New },
    { "test6001.LIN64.cpp" , New },
    { "test6010.MsgBox.cpp" , New },
    { "test6007.Quick.cpp" , New },
    { "test6002.SysError.cpp" , New },
    { "test6008.X11.cpp" , New },
    { "test6006.exec.cpp" , New }
   }
  };

Dir Dir7=
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

Dir Dir8=
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

Dir Dir9=
  {
   "math",
   Green,
   {
   },
   {
    { "IntegerFastAlgo.h" , Green }
   }
  };

Dir Dir10=
  {
   "sys",
   New,
   {
   },
   {
    { "SysAbort.h" , Green },
    { "SysAtomic.h" , Green },
    { "SysCon.h" , Green },
    { "SysData.h" , Green },
    { "SysError.h" , Green },
    { "SysFile.h" , New },
    { "SysFileSystem.h" , Green },
    { "SysInternal.h" , Green },
    { "SysLaunchPath.h" , Green },
    { "SysMemPage.h" , Green },
    { "SysNet.h" , New },
    { "SysPlanInit.h" , Green },
    { "SysProp.h" , Green },
    { "SysSem.h" , Green },
    { "SysTask.h" , Green },
    { "SysTime.h" , Green },
    { "SysTlsSlot.h" , Green },
    { "SysWait.h" , Green }
   }
  };

Dir Dir11=
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

Dir Dir12=
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

Dir Dir13=
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

Dir Dir14=
  {
   "math",
   Green,
   {
   },
   {
    { "IntegerFastAlgo.cpp" , Green }
   }
  };

Dir Dir15=
  {
   "sys",
   New,
   {
   },
   {
    { "SysAbort.cpp" , Green },
    { "SysAtomic.cpp" , Green },
    { "SysCon.cpp" , Green },
    { "SysData.cpp" , Green },
    { "SysError.cpp" , Green },
    { "SysFile.cpp" , New },
    { "SysFileSystem.cpp" , Green },
    { "SysInternal.cpp" , Green },
    { "SysLaunchPath.cpp" , Green },
    { "SysMemPage.cpp" , Green },
    { "SysNet.cpp" , New },
    { "SysPlanInit.cpp" , Green },
    { "SysProp.cpp" , Green },
    { "SysSem.cpp" , Green },
    { "SysTask.cpp" , Green },
    { "SysTime.cpp" , Green },
    { "SysTlsSlot.cpp" , Green },
    { "SysWait.cpp" , Green },
    { "SysAtomic.s" , Green },
    { "SysTime.s" , Green }
   }
  };

Dir Dir16=
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

Dir Dir6=
  {
   "HowToBuild",
   Ignore,
   {
    &Dir17,
    &Dir18
   },
   {
   }
  };

Dir Dir17=
  {
   "gcc-7.1.0",
   Ignore,
   {
   },
   {
    { "MakeCfg" , Ignore }
   }
  };

Dir Dir18=
  {
   "gcc-8.1.0",
   Ignore,
   {
   },
   {
    { "MakeCfg" , Ignore }
   }
  };

