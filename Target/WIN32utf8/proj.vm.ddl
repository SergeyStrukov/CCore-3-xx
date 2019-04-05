text OBJ_PATH = ".obj" ;

text CC = "D:/cygwin/opt/gcc-8.3.0/bin/g++-8.3.0" ;

text AS = "as" ;

text LD = "D:/cygwin/opt/gcc-8.3.0/bin/g++-8.3.0" ;

text AR = "ar" ;

text TARGET = "CCore.a" ;

Target cpp1 = { "AES.cpp" , "../../Applied/CCore/src/./crypton/AES.cpp" } ;
Target ocpp1 = { "AES.o" , OBJ_PATH+"/AES.o" } ;
Rule rcpp1 = { {&cpp1} , {&ocpp1} , {&intdep1,&execpp1} } ;
Exe execpp1 = { "CC AES.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./crypton/AES.cpp"
 ,"-o"
 ,OBJ_PATH+"/AES.o"
} } ;

IntCmd intdep1 = { 'RM DEP' , &rmdep1 } ;

Rm rmdep1 = { { OBJ_PATH+"/AES.dep" } } ;

Target cpp2 = { "APRTest.cpp" , "../../Applied/CCore/src/./math/APRTest.cpp" } ;
Target ocpp2 = { "APRTest.o" , OBJ_PATH+"/APRTest.o" } ;
Rule rcpp2 = { {&cpp2} , {&ocpp2} , {&intdep2,&execpp2} } ;
Exe execpp2 = { "CC APRTest.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./math/APRTest.cpp"
 ,"-o"
 ,OBJ_PATH+"/APRTest.o"
} } ;

IntCmd intdep2 = { 'RM DEP' , &rmdep2 } ;

Rm rmdep2 = { { OBJ_PATH+"/APRTest.dep" } } ;

Target cpp3 = { "APRTestData.gen.cpp" , "../../Applied/CCore/src/./math/APRTestData.gen.cpp" } ;
Target ocpp3 = { "APRTestData.gen.o" , OBJ_PATH+"/APRTestData.gen.o" } ;
Rule rcpp3 = { {&cpp3} , {&ocpp3} , {&intdep3,&execpp3} } ;
Exe execpp3 = { "CC APRTestData.gen.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./math/APRTestData.gen.cpp"
 ,"-o"
 ,OBJ_PATH+"/APRTestData.gen.o"
} } ;

IntCmd intdep3 = { 'RM DEP' , &rmdep3 } ;

Rm rmdep3 = { { OBJ_PATH+"/APRTestData.gen.dep" } } ;

Target cpp4 = { "Abort.cpp" , "../../HCore/CCore/src/Abort.cpp" } ;
Target ocpp4 = { "Abort.o" , OBJ_PATH+"/Abort.o" } ;
Rule rcpp4 = { {&cpp4} , {&ocpp4} , {&intdep4,&execpp4} } ;
Exe execpp4 = { "CC Abort.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/Abort.cpp"
 ,"-o"
 ,OBJ_PATH+"/Abort.o"
} } ;

IntCmd intdep4 = { 'RM DEP' , &rmdep4 } ;

Rm rmdep4 = { { OBJ_PATH+"/Abort.dep" } } ;

Target cpp5 = { "AbortMsgFunc.cpp" , "../../Simple/CCore/src/AbortMsgFunc.cpp" } ;
Target ocpp5 = { "AbortMsgFunc.o" , OBJ_PATH+"/AbortMsgFunc.o" } ;
Rule rcpp5 = { {&cpp5} , {&ocpp5} , {&intdep5,&execpp5} } ;
Exe execpp5 = { "CC AbortMsgFunc.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/AbortMsgFunc.cpp"
 ,"-o"
 ,OBJ_PATH+"/AbortMsgFunc.o"
} } ;

IntCmd intdep5 = { 'RM DEP' , &rmdep5 } ;

Rm rmdep5 = { { OBJ_PATH+"/AbortMsgFunc.dep" } } ;

Target cpp6 = { "Activator.cpp" , "../../Desktop/Tools/CCore/src/./video/Activator.cpp" } ;
Target ocpp6 = { "Activator.o" , OBJ_PATH+"/Activator.o" } ;
Rule rcpp6 = { {&cpp6} , {&ocpp6} , {&intdep6,&execpp6} } ;
Exe execpp6 = { "CC Activator.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Tools/CCore/src/./video/Activator.cpp"
 ,"-o"
 ,OBJ_PATH+"/Activator.o"
} } ;

IntCmd intdep6 = { 'RM DEP' , &rmdep6 } ;

Rm rmdep6 = { { OBJ_PATH+"/Activator.dep" } } ;

Target cpp7 = { "AntiSem.cpp" , "../../HCore/CCore/src/./task/AntiSem.cpp" } ;
Target ocpp7 = { "AntiSem.o" , OBJ_PATH+"/AntiSem.o" } ;
Rule rcpp7 = { {&cpp7} , {&ocpp7} , {&intdep7,&execpp7} } ;
Exe execpp7 = { "CC AntiSem.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/./task/AntiSem.cpp"
 ,"-o"
 ,OBJ_PATH+"/AntiSem.o"
} } ;

IntCmd intdep7 = { 'RM DEP' , &rmdep7 } ;

Rm rmdep7 = { { OBJ_PATH+"/AntiSem.dep" } } ;

Target cpp8 = { "AnyPtr.cpp" , "../../Simple/CCore/src/AnyPtr.cpp" } ;
Target ocpp8 = { "AnyPtr.o" , OBJ_PATH+"/AnyPtr.o" } ;
Rule rcpp8 = { {&cpp8} , {&ocpp8} , {&intdep8,&execpp8} } ;
Exe execpp8 = { "CC AnyPtr.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/AnyPtr.cpp"
 ,"-o"
 ,OBJ_PATH+"/AnyPtr.o"
} } ;

IntCmd intdep8 = { 'RM DEP' , &rmdep8 } ;

Rm rmdep8 = { { OBJ_PATH+"/AnyPtr.dep" } } ;

Target cpp9 = { "AppMain.cpp" , "../../Desktop/App/CCore/src/./video/AppMain.cpp" } ;
Target ocpp9 = { "AppMain.o" , OBJ_PATH+"/AppMain.o" } ;
Rule rcpp9 = { {&cpp9} , {&ocpp9} , {&intdep9,&execpp9} } ;
Exe execpp9 = { "CC AppMain.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/App/CCore/src/./video/AppMain.cpp"
 ,"-o"
 ,OBJ_PATH+"/AppMain.o"
} } ;

IntCmd intdep9 = { 'RM DEP' , &rmdep9 } ;

Rm rmdep9 = { { OBJ_PATH+"/AppMain.dep" } } ;

Target cpp10 = { "AppOpt.cpp" , "../../Desktop/App/CCore/src/./video/AppOpt.cpp" } ;
Target ocpp10 = { "AppOpt.o" , OBJ_PATH+"/AppOpt.o" } ;
Rule rcpp10 = { {&cpp10} , {&ocpp10} , {&intdep10,&execpp10} } ;
Exe execpp10 = { "CC AppOpt.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/App/CCore/src/./video/AppOpt.cpp"
 ,"-o"
 ,OBJ_PATH+"/AppOpt.o"
} } ;

IntCmd intdep10 = { 'RM DEP' , &rmdep10 } ;

Rm rmdep10 = { { OBJ_PATH+"/AppOpt.dep" } } ;

Target cpp11 = { "ApplicationBase.cpp" , "../../Desktop/App/CCore/src/./video/ApplicationBase.cpp" } ;
Target ocpp11 = { "ApplicationBase.o" , OBJ_PATH+"/ApplicationBase.o" } ;
Rule rcpp11 = { {&cpp11} , {&ocpp11} , {&intdep11,&execpp11} } ;
Exe execpp11 = { "CC ApplicationBase.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/App/CCore/src/./video/ApplicationBase.cpp"
 ,"-o"
 ,OBJ_PATH+"/ApplicationBase.o"
} } ;

IntCmd intdep11 = { 'RM DEP' , &rmdep11 } ;

Rm rmdep11 = { { OBJ_PATH+"/ApplicationBase.dep" } } ;

Target cpp12 = { "ApplyToList.cpp" , "../../Fundamental/CCore/src/./algon/ApplyToList.cpp" } ;
Target ocpp12 = { "ApplyToList.o" , OBJ_PATH+"/ApplyToList.o" } ;
Rule rcpp12 = { {&cpp12} , {&ocpp12} , {&intdep12,&execpp12} } ;
Exe execpp12 = { "CC ApplyToList.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./algon/ApplyToList.cpp"
 ,"-o"
 ,OBJ_PATH+"/ApplyToList.o"
} } ;

IntCmd intdep12 = { 'RM DEP' , &rmdep12 } ;

Rm rmdep12 = { { OBJ_PATH+"/ApplyToList.dep" } } ;

Target cpp13 = { "ApplyToRange.cpp" , "../../Fundamental/CCore/src/./algon/ApplyToRange.cpp" } ;
Target ocpp13 = { "ApplyToRange.o" , OBJ_PATH+"/ApplyToRange.o" } ;
Rule rcpp13 = { {&cpp13} , {&ocpp13} , {&intdep13,&execpp13} } ;
Exe execpp13 = { "CC ApplyToRange.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./algon/ApplyToRange.cpp"
 ,"-o"
 ,OBJ_PATH+"/ApplyToRange.o"
} } ;

IntCmd intdep13 = { 'RM DEP' , &rmdep13 } ;

Rm rmdep13 = { { OBJ_PATH+"/ApplyToRange.dep" } } ;

Target cpp14 = { "Array.cpp" , "../../Fundamental/CCore/src/Array.cpp" } ;
Target ocpp14 = { "Array.o" , OBJ_PATH+"/Array.o" } ;
Rule rcpp14 = { {&cpp14} , {&ocpp14} , {&intdep14,&execpp14} } ;
Exe execpp14 = { "CC Array.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/Array.cpp"
 ,"-o"
 ,OBJ_PATH+"/Array.o"
} } ;

IntCmd intdep14 = { 'RM DEP' , &rmdep14 } ;

Rm rmdep14 = { { OBJ_PATH+"/Array.dep" } } ;

Target cpp15 = { "ArrayAlgo.cpp" , "../../Fundamental/CCore/src/./array/ArrayAlgo.cpp" } ;
Target ocpp15 = { "ArrayAlgo.o" , OBJ_PATH+"/ArrayAlgo.o" } ;
Rule rcpp15 = { {&cpp15} , {&ocpp15} , {&intdep15,&execpp15} } ;
Exe execpp15 = { "CC ArrayAlgo.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./array/ArrayAlgo.cpp"
 ,"-o"
 ,OBJ_PATH+"/ArrayAlgo.o"
} } ;

IntCmd intdep15 = { 'RM DEP' , &rmdep15 } ;

Rm rmdep15 = { { OBJ_PATH+"/ArrayAlgo.dep" } } ;

Target cpp16 = { "ArrayBase.cpp" , "../../Fundamental/CCore/src/./array/ArrayBase.cpp" } ;
Target ocpp16 = { "ArrayBase.o" , OBJ_PATH+"/ArrayBase.o" } ;
Rule rcpp16 = { {&cpp16} , {&ocpp16} , {&intdep16,&execpp16} } ;
Exe execpp16 = { "CC ArrayBase.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./array/ArrayBase.cpp"
 ,"-o"
 ,OBJ_PATH+"/ArrayBase.o"
} } ;

IntCmd intdep16 = { 'RM DEP' , &rmdep16 } ;

Rm rmdep16 = { { OBJ_PATH+"/ArrayBase.dep" } } ;

Target cpp17 = { "ArrayInsDel.cpp" , "../../Fundamental/CCore/src/./array/ArrayInsDel.cpp" } ;
Target ocpp17 = { "ArrayInsDel.o" , OBJ_PATH+"/ArrayInsDel.o" } ;
Rule rcpp17 = { {&cpp17} , {&ocpp17} , {&intdep17,&execpp17} } ;
Exe execpp17 = { "CC ArrayInsDel.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./array/ArrayInsDel.cpp"
 ,"-o"
 ,OBJ_PATH+"/ArrayInsDel.o"
} } ;

IntCmd intdep17 = { 'RM DEP' , &rmdep17 } ;

Rm rmdep17 = { { OBJ_PATH+"/ArrayInsDel.dep" } } ;

Target cpp18 = { "AsyncBinaryFile.cpp" , "../../Applied/CCore/src/AsyncBinaryFile.cpp" } ;
Target ocpp18 = { "AsyncBinaryFile.o" , OBJ_PATH+"/AsyncBinaryFile.o" } ;
Rule rcpp18 = { {&cpp18} , {&ocpp18} , {&intdep18,&execpp18} } ;
Exe execpp18 = { "CC AsyncBinaryFile.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/AsyncBinaryFile.cpp"
 ,"-o"
 ,OBJ_PATH+"/AsyncBinaryFile.o"
} } ;

IntCmd intdep18 = { 'RM DEP' , &rmdep18 } ;

Rm rmdep18 = { { OBJ_PATH+"/AsyncBinaryFile.dep" } } ;

Target cpp19 = { "AsyncFile.cpp" , "../../Applied/CCore/src/AsyncFile.cpp" } ;
Target ocpp19 = { "AsyncFile.o" , OBJ_PATH+"/AsyncFile.o" } ;
Rule rcpp19 = { {&cpp19} , {&ocpp19} , {&intdep19,&execpp19} } ;
Exe execpp19 = { "CC AsyncFile.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/AsyncFile.cpp"
 ,"-o"
 ,OBJ_PATH+"/AsyncFile.o"
} } ;

IntCmd intdep19 = { 'RM DEP' , &rmdep19 } ;

Rm rmdep19 = { { OBJ_PATH+"/AsyncFile.dep" } } ;

Target cpp20 = { "AsyncFileDevice.cpp" , "../../HCore/CCore/src/AsyncFileDevice.cpp" } ;
Target ocpp20 = { "AsyncFileDevice.o" , OBJ_PATH+"/AsyncFileDevice.o" } ;
Rule rcpp20 = { {&cpp20} , {&ocpp20} , {&intdep20,&execpp20} } ;
Exe execpp20 = { "CC AsyncFileDevice.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/AsyncFileDevice.cpp"
 ,"-o"
 ,OBJ_PATH+"/AsyncFileDevice.o"
} } ;

IntCmd intdep20 = { 'RM DEP' , &rmdep20 } ;

Rm rmdep20 = { { OBJ_PATH+"/AsyncFileDevice.dep" } } ;

Target cpp21 = { "AsyncFileToMem.cpp" , "../../Applied/CCore/src/AsyncFileToMem.cpp" } ;
Target ocpp21 = { "AsyncFileToMem.o" , OBJ_PATH+"/AsyncFileToMem.o" } ;
Rule rcpp21 = { {&cpp21} , {&ocpp21} , {&intdep21,&execpp21} } ;
Exe execpp21 = { "CC AsyncFileToMem.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/AsyncFileToMem.cpp"
 ,"-o"
 ,OBJ_PATH+"/AsyncFileToMem.o"
} } ;

IntCmd intdep21 = { 'RM DEP' , &rmdep21 } ;

Rm rmdep21 = { { OBJ_PATH+"/AsyncFileToMem.dep" } } ;

Target cpp22 = { "AsyncUDPDevice.cpp" , "../../HCore/CCore/src/./net/AsyncUDPDevice.cpp" } ;
Target ocpp22 = { "AsyncUDPDevice.o" , OBJ_PATH+"/AsyncUDPDevice.o" } ;
Rule rcpp22 = { {&cpp22} , {&ocpp22} , {&intdep22,&execpp22} } ;
Exe execpp22 = { "CC AsyncUDPDevice.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/./net/AsyncUDPDevice.cpp"
 ,"-o"
 ,OBJ_PATH+"/AsyncUDPDevice.o"
} } ;

IntCmd intdep22 = { 'RM DEP' , &rmdep22 } ;

Rm rmdep22 = { { OBJ_PATH+"/AsyncUDPDevice.dep" } } ;

Target cpp23 = { "Atomic.cpp" , "../../Applied/CCore/src/./task/Atomic.cpp" } ;
Target ocpp23 = { "Atomic.o" , OBJ_PATH+"/Atomic.o" } ;
Rule rcpp23 = { {&cpp23} , {&ocpp23} , {&intdep23,&execpp23} } ;
Exe execpp23 = { "CC Atomic.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./task/Atomic.cpp"
 ,"-o"
 ,OBJ_PATH+"/Atomic.o"
} } ;

IntCmd intdep23 = { 'RM DEP' , &rmdep23 } ;

Rm rmdep23 = { { OBJ_PATH+"/Atomic.dep" } } ;

Target cpp24 = { "AtomicRefArray.cpp" , "../../Fundamental/CCore/src/./array/AtomicRefArray.cpp" } ;
Target ocpp24 = { "AtomicRefArray.o" , OBJ_PATH+"/AtomicRefArray.o" } ;
Rule rcpp24 = { {&cpp24} , {&ocpp24} , {&intdep24,&execpp24} } ;
Exe execpp24 = { "CC AtomicRefArray.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./array/AtomicRefArray.cpp"
 ,"-o"
 ,OBJ_PATH+"/AtomicRefArray.o"
} } ;

IntCmd intdep24 = { 'RM DEP' , &rmdep24 } ;

Rm rmdep24 = { { OBJ_PATH+"/AtomicRefArray.dep" } } ;

Target cpp25 = { "AttachmentHost.cpp" , "../../Fundamental/CCore/src/AttachmentHost.cpp" } ;
Target ocpp25 = { "AttachmentHost.o" , OBJ_PATH+"/AttachmentHost.o" } ;
Rule rcpp25 = { {&cpp25} , {&ocpp25} , {&intdep25,&execpp25} } ;
Exe execpp25 = { "CC AttachmentHost.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/AttachmentHost.cpp"
 ,"-o"
 ,OBJ_PATH+"/AttachmentHost.o"
} } ;

IntCmd intdep25 = { 'RM DEP' , &rmdep25 } ;

Rm rmdep25 = { { OBJ_PATH+"/AttachmentHost.dep" } } ;

Target cpp26 = { "AutoCast.cpp" , "../../Simple/CCore/src/./gadget/AutoCast.cpp" } ;
Target ocpp26 = { "AutoCast.o" , OBJ_PATH+"/AutoCast.o" } ;
Rule rcpp26 = { {&cpp26} , {&ocpp26} , {&intdep26,&execpp26} } ;
Exe execpp26 = { "CC AutoCast.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/AutoCast.cpp"
 ,"-o"
 ,OBJ_PATH+"/AutoCast.o"
} } ;

IntCmd intdep26 = { 'RM DEP' , &rmdep26 } ;

Rm rmdep26 = { { OBJ_PATH+"/AutoCast.dep" } } ;

Target cpp27 = { "AutoGlobal.cpp" , "../../Fundamental/CCore/src/AutoGlobal.cpp" } ;
Target ocpp27 = { "AutoGlobal.o" , OBJ_PATH+"/AutoGlobal.o" } ;
Rule rcpp27 = { {&cpp27} , {&ocpp27} , {&intdep27,&execpp27} } ;
Exe execpp27 = { "CC AutoGlobal.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/AutoGlobal.cpp"
 ,"-o"
 ,OBJ_PATH+"/AutoGlobal.o"
} } ;

IntCmd intdep27 = { 'RM DEP' , &rmdep27 } ;

Rm rmdep27 = { { OBJ_PATH+"/AutoGlobal.dep" } } ;

Target cpp28 = { "BaseRangeAlgo.cpp" , "../../Fundamental/CCore/src/./algon/BaseRangeAlgo.cpp" } ;
Target ocpp28 = { "BaseRangeAlgo.o" , OBJ_PATH+"/BaseRangeAlgo.o" } ;
Rule rcpp28 = { {&cpp28} , {&ocpp28} , {&intdep28,&execpp28} } ;
Exe execpp28 = { "CC BaseRangeAlgo.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./algon/BaseRangeAlgo.cpp"
 ,"-o"
 ,OBJ_PATH+"/BaseRangeAlgo.o"
} } ;

IntCmd intdep28 = { 'RM DEP' , &rmdep28 } ;

Rm rmdep28 = { { OBJ_PATH+"/BaseRangeAlgo.dep" } } ;

Target cpp29 = { "BestSearch.cpp" , "../../Fundamental/CCore/src/./algon/BestSearch.cpp" } ;
Target ocpp29 = { "BestSearch.o" , OBJ_PATH+"/BestSearch.o" } ;
Rule rcpp29 = { {&cpp29} , {&ocpp29} , {&intdep29,&execpp29} } ;
Exe execpp29 = { "CC BestSearch.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./algon/BestSearch.cpp"
 ,"-o"
 ,OBJ_PATH+"/BestSearch.o"
} } ;

IntCmd intdep29 = { 'RM DEP' , &rmdep29 } ;

Rm rmdep29 = { { OBJ_PATH+"/BestSearch.dep" } } ;

Target cpp30 = { "BinFileToRead.cpp" , "../../Fundamental/CCore/src/BinFileToRead.cpp" } ;
Target ocpp30 = { "BinFileToRead.o" , OBJ_PATH+"/BinFileToRead.o" } ;
Rule rcpp30 = { {&cpp30} , {&ocpp30} , {&intdep30,&execpp30} } ;
Exe execpp30 = { "CC BinFileToRead.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/BinFileToRead.cpp"
 ,"-o"
 ,OBJ_PATH+"/BinFileToRead.o"
} } ;

IntCmd intdep30 = { 'RM DEP' , &rmdep30 } ;

Rm rmdep30 = { { OBJ_PATH+"/BinFileToRead.dep" } } ;

Target cpp31 = { "BinaryFile.cpp" , "../../HCore/CCore/src/BinaryFile.cpp" } ;
Target ocpp31 = { "BinaryFile.o" , OBJ_PATH+"/BinaryFile.o" } ;
Rule rcpp31 = { {&cpp31} , {&ocpp31} , {&intdep31,&execpp31} } ;
Exe execpp31 = { "CC BinaryFile.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/BinaryFile.cpp"
 ,"-o"
 ,OBJ_PATH+"/BinaryFile.o"
} } ;

IntCmd intdep31 = { 'RM DEP' , &rmdep31 } ;

Rm rmdep31 = { { OBJ_PATH+"/BinaryFile.dep" } } ;

Target cpp32 = { "BinarySearch.cpp" , "../../Fundamental/CCore/src/./algon/BinarySearch.cpp" } ;
Target ocpp32 = { "BinarySearch.o" , OBJ_PATH+"/BinarySearch.o" } ;
Rule rcpp32 = { {&cpp32} , {&ocpp32} , {&intdep32,&execpp32} } ;
Exe execpp32 = { "CC BinarySearch.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./algon/BinarySearch.cpp"
 ,"-o"
 ,OBJ_PATH+"/BinarySearch.o"
} } ;

IntCmd intdep32 = { 'RM DEP' , &rmdep32 } ;

Rm rmdep32 = { { OBJ_PATH+"/BinarySearch.dep" } } ;

Target cpp33 = { "BindBagProxy.cpp" , "../../Desktop/Lib/CCore/src/./video/BindBagProxy.cpp" } ;
Target ocpp33 = { "BindBagProxy.o" , OBJ_PATH+"/BindBagProxy.o" } ;
Rule rcpp33 = { {&cpp33} , {&ocpp33} , {&intdep33,&execpp33} } ;
Exe execpp33 = { "CC BindBagProxy.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/BindBagProxy.cpp"
 ,"-o"
 ,OBJ_PATH+"/BindBagProxy.o"
} } ;

IntCmd intdep33 = { 'RM DEP' , &rmdep33 } ;

Rm rmdep33 = { { OBJ_PATH+"/BindBagProxy.dep" } } ;

Target cpp34 = { "Bitmap.cpp" , "../../Desktop/Tools/CCore/src/./video/Bitmap.cpp" } ;
Target ocpp34 = { "Bitmap.o" , OBJ_PATH+"/Bitmap.o" } ;
Rule rcpp34 = { {&cpp34} , {&ocpp34} , {&intdep34,&execpp34} } ;
Exe execpp34 = { "CC Bitmap.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Tools/CCore/src/./video/Bitmap.cpp"
 ,"-o"
 ,OBJ_PATH+"/Bitmap.o"
} } ;

IntCmd intdep34 = { 'RM DEP' , &rmdep34 } ;

Rm rmdep34 = { { OBJ_PATH+"/Bitmap.dep" } } ;

Target cpp35 = { "BlockCipher.cpp" , "../../Applied/CCore/src/./crypton/BlockCipher.cpp" } ;
Target ocpp35 = { "BlockCipher.o" , OBJ_PATH+"/BlockCipher.o" } ;
Rule rcpp35 = { {&cpp35} , {&ocpp35} , {&intdep35,&execpp35} } ;
Exe execpp35 = { "CC BlockCipher.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./crypton/BlockCipher.cpp"
 ,"-o"
 ,OBJ_PATH+"/BlockCipher.o"
} } ;

IntCmd intdep35 = { 'RM DEP' , &rmdep35 } ;

Rm rmdep35 = { { OBJ_PATH+"/BlockCipher.dep" } } ;

Target cpp36 = { "BlockFifo.cpp" , "../../Simple/CCore/src/BlockFifo.cpp" } ;
Target ocpp36 = { "BlockFifo.o" , OBJ_PATH+"/BlockFifo.o" } ;
Rule rcpp36 = { {&cpp36} , {&ocpp36} , {&intdep36,&execpp36} } ;
Exe execpp36 = { "CC BlockFifo.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/BlockFifo.cpp"
 ,"-o"
 ,OBJ_PATH+"/BlockFifo.o"
} } ;

IntCmd intdep36 = { 'RM DEP' , &rmdep36 } ;

Rm rmdep36 = { { OBJ_PATH+"/BlockFifo.dep" } } ;

Target cpp37 = { "Book.cpp" , "../../Desktop/Lib/CCore/src/./video/book/Book.cpp" } ;
Target ocpp37 = { "Book.o" , OBJ_PATH+"/Book.o" } ;
Rule rcpp37 = { {&cpp37} , {&ocpp37} , {&intdep37,&execpp37} } ;
Exe execpp37 = { "CC Book.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/book/Book.cpp"
 ,"-o"
 ,OBJ_PATH+"/Book.o"
} } ;

IntCmd intdep37 = { 'RM DEP' , &rmdep37 } ;

Rm rmdep37 = { { OBJ_PATH+"/Book.dep" } } ;

Target cpp38 = { "BookAppMain.cpp" , "../../Desktop/App/CCore/src/./video/BookAppMain.cpp" } ;
Target ocpp38 = { "BookAppMain.o" , OBJ_PATH+"/BookAppMain.o" } ;
Rule rcpp38 = { {&cpp38} , {&ocpp38} , {&intdep38,&execpp38} } ;
Exe execpp38 = { "CC BookAppMain.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/App/CCore/src/./video/BookAppMain.cpp"
 ,"-o"
 ,OBJ_PATH+"/BookAppMain.o"
} } ;

IntCmd intdep38 = { 'RM DEP' , &rmdep38 } ;

Rm rmdep38 = { { OBJ_PATH+"/BookAppMain.dep" } } ;

Target cpp39 = { "BookClient.cpp" , "../../Desktop/Lib/CCore/src/./video/book/BookClient.cpp" } ;
Target ocpp39 = { "BookClient.o" , OBJ_PATH+"/BookClient.o" } ;
Rule rcpp39 = { {&cpp39} , {&ocpp39} , {&intdep39,&execpp39} } ;
Exe execpp39 = { "CC BookClient.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/book/BookClient.cpp"
 ,"-o"
 ,OBJ_PATH+"/BookClient.o"
} } ;

IntCmd intdep39 = { 'RM DEP' , &rmdep39 } ;

Rm rmdep39 = { { OBJ_PATH+"/BookClient.dep" } } ;

Target cpp40 = { "BookFrame.cpp" , "../../Desktop/Lib/CCore/src/./video/BookFrame.cpp" } ;
Target ocpp40 = { "BookFrame.o" , OBJ_PATH+"/BookFrame.o" } ;
Rule rcpp40 = { {&cpp40} , {&ocpp40} , {&intdep40,&execpp40} } ;
Exe execpp40 = { "CC BookFrame.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/BookFrame.cpp"
 ,"-o"
 ,OBJ_PATH+"/BookFrame.o"
} } ;

IntCmd intdep40 = { 'RM DEP' , &rmdep40 } ;

Rm rmdep40 = { { OBJ_PATH+"/BookFrame.dep" } } ;

Target cpp41 = { "BookWindow.cpp" , "../../Desktop/Lib/CCore/src/./video/book/BookWindow.cpp" } ;
Target ocpp41 = { "BookWindow.o" , OBJ_PATH+"/BookWindow.o" } ;
Rule rcpp41 = { {&cpp41} , {&ocpp41} , {&intdep41,&execpp41} } ;
Exe execpp41 = { "CC BookWindow.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/book/BookWindow.cpp"
 ,"-o"
 ,OBJ_PATH+"/BookWindow.o"
} } ;

IntCmd intdep41 = { 'RM DEP' , &rmdep41 } ;

Rm rmdep41 = { { OBJ_PATH+"/BookWindow.dep" } } ;

Target cpp42 = { "Bridge.cpp" , "../../Applied/CCore/src/./net/Bridge.cpp" } ;
Target ocpp42 = { "Bridge.o" , OBJ_PATH+"/Bridge.o" } ;
Rule rcpp42 = { {&cpp42} , {&ocpp42} , {&intdep42,&execpp42} } ;
Exe execpp42 = { "CC Bridge.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./net/Bridge.cpp"
 ,"-o"
 ,OBJ_PATH+"/Bridge.o"
} } ;

IntCmd intdep42 = { 'RM DEP' , &rmdep42 } ;

Rm rmdep42 = { { OBJ_PATH+"/Bridge.dep" } } ;

Target cpp43 = { "ButtonId.cpp" , "../../Desktop/Tools/CCore/src/./video/ButtonId.cpp" } ;
Target ocpp43 = { "ButtonId.o" , OBJ_PATH+"/ButtonId.o" } ;
Rule rcpp43 = { {&cpp43} , {&ocpp43} , {&intdep43,&execpp43} } ;
Exe execpp43 = { "CC ButtonId.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Tools/CCore/src/./video/ButtonId.cpp"
 ,"-o"
 ,OBJ_PATH+"/ButtonId.o"
} } ;

IntCmd intdep43 = { 'RM DEP' , &rmdep43 } ;

Rm rmdep43 = { { OBJ_PATH+"/ButtonId.dep" } } ;

Target cpp44 = { "CancelPacketList.cpp" , "../../Applied/CCore/src/CancelPacketList.cpp" } ;
Target ocpp44 = { "CancelPacketList.o" , OBJ_PATH+"/CancelPacketList.o" } ;
Rule rcpp44 = { {&cpp44} , {&ocpp44} , {&intdep44,&execpp44} } ;
Exe execpp44 = { "CC CancelPacketList.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/CancelPacketList.cpp"
 ,"-o"
 ,OBJ_PATH+"/CancelPacketList.o"
} } ;

IntCmd intdep44 = { 'RM DEP' , &rmdep44 } ;

Rm rmdep44 = { { OBJ_PATH+"/CancelPacketList.dep" } } ;

Target cpp45 = { "CapString.cpp" , "../../Simple/CCore/src/CapString.cpp" } ;
Target ocpp45 = { "CapString.o" , OBJ_PATH+"/CapString.o" } ;
Rule rcpp45 = { {&cpp45} , {&ocpp45} , {&intdep45,&execpp45} } ;
Exe execpp45 = { "CC CapString.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/CapString.cpp"
 ,"-o"
 ,OBJ_PATH+"/CapString.o"
} } ;

IntCmd intdep45 = { 'RM DEP' , &rmdep45 } ;

Rm rmdep45 = { { OBJ_PATH+"/CapString.dep" } } ;

Target cpp46 = { "CharProp.cpp" , "../../Fundamental/CCore/src/CharProp.cpp" } ;
Target ocpp46 = { "CharProp.o" , OBJ_PATH+"/CharProp.o" } ;
Rule rcpp46 = { {&cpp46} , {&ocpp46} , {&intdep46,&execpp46} } ;
Exe execpp46 = { "CC CharProp.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/CharProp.cpp"
 ,"-o"
 ,OBJ_PATH+"/CharProp.o"
} } ;

IntCmd intdep46 = { 'RM DEP' , &rmdep46 } ;

Rm rmdep46 = { { OBJ_PATH+"/CharProp.dep" } } ;

Target cpp47 = { "CharUtils.cpp" , "../../Fundamental/CCore/src/CharUtils.cpp" } ;
Target ocpp47 = { "CharUtils.o" , OBJ_PATH+"/CharUtils.o" } ;
Rule rcpp47 = { {&cpp47} , {&ocpp47} , {&intdep47,&execpp47} } ;
Exe execpp47 = { "CC CharUtils.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/CharUtils.cpp"
 ,"-o"
 ,OBJ_PATH+"/CharUtils.o"
} } ;

IntCmd intdep47 = { 'RM DEP' , &rmdep47 } ;

Rm rmdep47 = { { OBJ_PATH+"/CharUtils.dep" } } ;

Target cpp48 = { "CheckPlatformBase.cpp" , "../../Simple/CCore/src/./base/CheckPlatformBase.cpp" } ;
Target ocpp48 = { "CheckPlatformBase.o" , OBJ_PATH+"/CheckPlatformBase.o" } ;
Rule rcpp48 = { {&cpp48} , {&ocpp48} , {&intdep48,&execpp48} } ;
Exe execpp48 = { "CC CheckPlatformBase.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./base/CheckPlatformBase.cpp"
 ,"-o"
 ,OBJ_PATH+"/CheckPlatformBase.o"
} } ;

IntCmd intdep48 = { 'RM DEP' , &rmdep48 } ;

Rm rmdep48 = { { OBJ_PATH+"/CheckPlatformBase.dep" } } ;

Target cpp49 = { "CheckedData.cpp" , "../../Applied/CCore/src/./net/CheckedData.cpp" } ;
Target ocpp49 = { "CheckedData.o" , OBJ_PATH+"/CheckedData.o" } ;
Rule rcpp49 = { {&cpp49} , {&ocpp49} , {&intdep49,&execpp49} } ;
Exe execpp49 = { "CC CheckedData.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./net/CheckedData.cpp"
 ,"-o"
 ,OBJ_PATH+"/CheckedData.o"
} } ;

IntCmd intdep49 = { 'RM DEP' , &rmdep49 } ;

Rm rmdep49 = { { OBJ_PATH+"/CheckedData.dep" } } ;

Target cpp50 = { "Classification.cpp" , "../../Simple/CCore/src/./gadget/Classification.cpp" } ;
Target ocpp50 = { "Classification.o" , OBJ_PATH+"/Classification.o" } ;
Rule rcpp50 = { {&cpp50} , {&ocpp50} , {&intdep50,&execpp50} } ;
Exe execpp50 = { "CC Classification.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/Classification.cpp"
 ,"-o"
 ,OBJ_PATH+"/Classification.o"
} } ;

IntCmd intdep50 = { 'RM DEP' , &rmdep50 } ;

Rm rmdep50 = { { OBJ_PATH+"/Classification.dep" } } ;

Target cpp51 = { "CmdInput.cpp" , "../../Applied/CCore/src/CmdInput.cpp" } ;
Target ocpp51 = { "CmdInput.o" , OBJ_PATH+"/CmdInput.o" } ;
Rule rcpp51 = { {&cpp51} , {&ocpp51} , {&intdep51,&execpp51} } ;
Exe execpp51 = { "CC CmdInput.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/CmdInput.cpp"
 ,"-o"
 ,OBJ_PATH+"/CmdInput.o"
} } ;

IntCmd intdep51 = { 'RM DEP' , &rmdep51 } ;

Rm rmdep51 = { { OBJ_PATH+"/CmdInput.dep" } } ;

Target cpp52 = { "Cmp.cpp" , "../../Simple/CCore/src/Cmp.cpp" } ;
Target ocpp52 = { "Cmp.o" , OBJ_PATH+"/Cmp.o" } ;
Rule rcpp52 = { {&cpp52} , {&ocpp52} , {&intdep52,&execpp52} } ;
Exe execpp52 = { "CC Cmp.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/Cmp.cpp"
 ,"-o"
 ,OBJ_PATH+"/Cmp.o"
} } ;

IntCmd intdep52 = { 'RM DEP' , &rmdep52 } ;

Rm rmdep52 = { { OBJ_PATH+"/Cmp.dep" } } ;

Target cpp53 = { "Collector.cpp" , "../../Fundamental/CCore/src/./array/Collector.cpp" } ;
Target ocpp53 = { "Collector.o" , OBJ_PATH+"/Collector.o" } ;
Rule rcpp53 = { {&cpp53} , {&ocpp53} , {&intdep53,&execpp53} } ;
Exe execpp53 = { "CC Collector.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./array/Collector.cpp"
 ,"-o"
 ,OBJ_PATH+"/Collector.o"
} } ;

IntCmd intdep53 = { 'RM DEP' , &rmdep53 } ;

Rm rmdep53 = { { OBJ_PATH+"/Collector.dep" } } ;

Target cpp54 = { "Color.cpp" , "../../Applied/CCore/src/./video/Color.cpp" } ;
Target ocpp54 = { "Color.o" , OBJ_PATH+"/Color.o" } ;
Rule rcpp54 = { {&cpp54} , {&ocpp54} , {&intdep54,&execpp54} } ;
Exe execpp54 = { "CC Color.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./video/Color.cpp"
 ,"-o"
 ,OBJ_PATH+"/Color.o"
} } ;

IntCmd intdep54 = { 'RM DEP' , &rmdep54 } ;

Rm rmdep54 = { { OBJ_PATH+"/Color.dep" } } ;

Target cpp55 = { "ColorEdit.cpp" , "../../Desktop/Lib/CCore/src/./video/pref/ColorEdit.cpp" } ;
Target ocpp55 = { "ColorEdit.o" , OBJ_PATH+"/ColorEdit.o" } ;
Rule rcpp55 = { {&cpp55} , {&ocpp55} , {&intdep55,&execpp55} } ;
Exe execpp55 = { "CC ColorEdit.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/pref/ColorEdit.cpp"
 ,"-o"
 ,OBJ_PATH+"/ColorEdit.o"
} } ;

IntCmd intdep55 = { 'RM DEP' , &rmdep55 } ;

Rm rmdep55 = { { OBJ_PATH+"/ColorEdit.dep" } } ;

Target cpp56 = { "ColorField.cpp" , "../../Desktop/Draw/CCore/src/./video/ColorField.cpp" } ;
Target ocpp56 = { "ColorField.o" , OBJ_PATH+"/ColorField.o" } ;
Rule rcpp56 = { {&cpp56} , {&ocpp56} , {&intdep56,&execpp56} } ;
Exe execpp56 = { "CC ColorField.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Draw/CCore/src/./video/ColorField.cpp"
 ,"-o"
 ,OBJ_PATH+"/ColorField.o"
} } ;

IntCmd intdep56 = { 'RM DEP' , &rmdep56 } ;

Rm rmdep56 = { { OBJ_PATH+"/ColorField.dep" } } ;

Target cpp57 = { "ColorListWindow.cpp" , "../../Desktop/Lib/CCore/src/./video/pref/ColorListWindow.cpp" } ;
Target ocpp57 = { "ColorListWindow.o" , OBJ_PATH+"/ColorListWindow.o" } ;
Rule rcpp57 = { {&cpp57} , {&ocpp57} , {&intdep57,&execpp57} } ;
Exe execpp57 = { "CC ColorListWindow.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/pref/ColorListWindow.cpp"
 ,"-o"
 ,OBJ_PATH+"/ColorListWindow.o"
} } ;

IntCmd intdep57 = { 'RM DEP' , &rmdep57 } ;

Rm rmdep57 = { { OBJ_PATH+"/ColorListWindow.dep" } } ;

Target cpp58 = { "CommonIntAlgo.cpp" , "../../Fundamental/CCore/src/./algon/CommonIntAlgo.cpp" } ;
Target ocpp58 = { "CommonIntAlgo.o" , OBJ_PATH+"/CommonIntAlgo.o" } ;
Rule rcpp58 = { {&cpp58} , {&ocpp58} , {&intdep58,&execpp58} } ;
Exe execpp58 = { "CC CommonIntAlgo.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./algon/CommonIntAlgo.cpp"
 ,"-o"
 ,OBJ_PATH+"/CommonIntAlgo.o"
} } ;

IntCmd intdep58 = { 'RM DEP' , &rmdep58 } ;

Rm rmdep58 = { { OBJ_PATH+"/CommonIntAlgo.dep" } } ;

Target cpp59 = { "CompactList.cpp" , "../../Fundamental/CCore/src/CompactList.cpp" } ;
Target ocpp59 = { "CompactList.o" , OBJ_PATH+"/CompactList.o" } ;
Rule rcpp59 = { {&cpp59} , {&ocpp59} , {&intdep59,&execpp59} } ;
Exe execpp59 = { "CC CompactList.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/CompactList.cpp"
 ,"-o"
 ,OBJ_PATH+"/CompactList.o"
} } ;

IntCmd intdep59 = { 'RM DEP' , &rmdep59 } ;

Rm rmdep59 = { { OBJ_PATH+"/CompactList.dep" } } ;

Target cpp60 = { "CompactMap.cpp" , "../../Fundamental/CCore/src/CompactMap.cpp" } ;
Target ocpp60 = { "CompactMap.o" , OBJ_PATH+"/CompactMap.o" } ;
Rule rcpp60 = { {&cpp60} , {&ocpp60} , {&intdep60,&execpp60} } ;
Exe execpp60 = { "CC CompactMap.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/CompactMap.cpp"
 ,"-o"
 ,OBJ_PATH+"/CompactMap.o"
} } ;

IntCmd intdep60 = { 'RM DEP' , &rmdep60 } ;

Rm rmdep60 = { { OBJ_PATH+"/CompactMap.dep" } } ;

Target cpp61 = { "CompactNodeAllocator.cpp" , "../../Fundamental/CCore/src/CompactNodeAllocator.cpp" } ;
Target ocpp61 = { "CompactNodeAllocator.o" , OBJ_PATH+"/CompactNodeAllocator.o" } ;
Rule rcpp61 = { {&cpp61} , {&ocpp61} , {&intdep61,&execpp61} } ;
Exe execpp61 = { "CC CompactNodeAllocator.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/CompactNodeAllocator.cpp"
 ,"-o"
 ,OBJ_PATH+"/CompactNodeAllocator.o"
} } ;

IntCmd intdep61 = { 'RM DEP' , &rmdep61 } ;

Rm rmdep61 = { { OBJ_PATH+"/CompactNodeAllocator.dep" } } ;

Target cpp62 = { "ConfigBinder.cpp" , "../../Desktop/Lib/CCore/src/./video/ConfigBinder.cpp" } ;
Target ocpp62 = { "ConfigBinder.o" , OBJ_PATH+"/ConfigBinder.o" } ;
Rule rcpp62 = { {&cpp62} , {&ocpp62} , {&intdep62,&execpp62} } ;
Exe execpp62 = { "CC ConfigBinder.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/ConfigBinder.cpp"
 ,"-o"
 ,OBJ_PATH+"/ConfigBinder.o"
} } ;

IntCmd intdep62 = { 'RM DEP' , &rmdep62 } ;

Rm rmdep62 = { { OBJ_PATH+"/ConfigBinder.dep" } } ;

Target cpp63 = { "ConfigEditor.cpp" , "../../Desktop/Lib/CCore/src/./video/ConfigEditor.cpp" } ;
Target ocpp63 = { "ConfigEditor.o" , OBJ_PATH+"/ConfigEditor.o" } ;
Rule rcpp63 = { {&cpp63} , {&ocpp63} , {&intdep63,&execpp63} } ;
Exe execpp63 = { "CC ConfigEditor.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/ConfigEditor.cpp"
 ,"-o"
 ,OBJ_PATH+"/ConfigEditor.o"
} } ;

IntCmd intdep63 = { 'RM DEP' , &rmdep63 } ;

Rm rmdep63 = { { OBJ_PATH+"/ConfigEditor.dep" } } ;

Target cpp64 = { "ConfigStore.cpp" , "../../Desktop/Lib/CCore/src/./video/ConfigStore.cpp" } ;
Target ocpp64 = { "ConfigStore.o" , OBJ_PATH+"/ConfigStore.o" } ;
Rule rcpp64 = { {&cpp64} , {&ocpp64} , {&intdep64,&execpp64} } ;
Exe execpp64 = { "CC ConfigStore.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/ConfigStore.cpp"
 ,"-o"
 ,OBJ_PATH+"/ConfigStore.o"
} } ;

IntCmd intdep64 = { 'RM DEP' , &rmdep64 } ;

Rm rmdep64 = { { OBJ_PATH+"/ConfigStore.dep" } } ;

Target cpp65 = { "ContainerList.cpp" , "../../Fundamental/CCore/src/ContainerList.cpp" } ;
Target ocpp65 = { "ContainerList.o" , OBJ_PATH+"/ContainerList.o" } ;
Rule rcpp65 = { {&cpp65} , {&ocpp65} , {&intdep65,&execpp65} } ;
Exe execpp65 = { "CC ContainerList.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/ContainerList.cpp"
 ,"-o"
 ,OBJ_PATH+"/ContainerList.o"
} } ;

IntCmd intdep65 = { 'RM DEP' , &rmdep65 } ;

Rm rmdep65 = { { OBJ_PATH+"/ContainerList.dep" } } ;

Target cpp66 = { "CoordEdit.cpp" , "../../Desktop/Lib/CCore/src/./video/pref/CoordEdit.cpp" } ;
Target ocpp66 = { "CoordEdit.o" , OBJ_PATH+"/CoordEdit.o" } ;
Rule rcpp66 = { {&cpp66} , {&ocpp66} , {&intdep66,&execpp66} } ;
Exe execpp66 = { "CC CoordEdit.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/pref/CoordEdit.cpp"
 ,"-o"
 ,OBJ_PATH+"/CoordEdit.o"
} } ;

IntCmd intdep66 = { 'RM DEP' , &rmdep66 } ;

Rm rmdep66 = { { OBJ_PATH+"/CoordEdit.dep" } } ;

Target cpp67 = { "Counters.cpp" , "../../Simple/CCore/src/Counters.cpp" } ;
Target ocpp67 = { "Counters.o" , OBJ_PATH+"/Counters.o" } ;
Rule rcpp67 = { {&cpp67} , {&ocpp67} , {&intdep67,&execpp67} } ;
Exe execpp67 = { "CC Counters.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/Counters.cpp"
 ,"-o"
 ,OBJ_PATH+"/Counters.o"
} } ;

IntCmd intdep67 = { 'RM DEP' , &rmdep67 } ;

Rm rmdep67 = { { OBJ_PATH+"/Counters.dep" } } ;

Target cpp68 = { "Crc.cpp" , "../../Simple/CCore/src/Crc.cpp" } ;
Target ocpp68 = { "Crc.o" , OBJ_PATH+"/Crc.o" } ;
Rule rcpp68 = { {&cpp68} , {&ocpp68} , {&intdep68,&execpp68} } ;
Exe execpp68 = { "CC Crc.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/Crc.cpp"
 ,"-o"
 ,OBJ_PATH+"/Crc.o"
} } ;

IntCmd intdep68 = { 'RM DEP' , &rmdep68 } ;

Rm rmdep68 = { { OBJ_PATH+"/Crc.dep" } } ;

Target cpp69 = { "CreateAt.cpp" , "../../Simple/CCore/src/./gadget/CreateAt.cpp" } ;
Target ocpp69 = { "CreateAt.o" , OBJ_PATH+"/CreateAt.o" } ;
Rule rcpp69 = { {&cpp69} , {&ocpp69} , {&intdep69,&execpp69} } ;
Exe execpp69 = { "CC CreateAt.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/CreateAt.cpp"
 ,"-o"
 ,OBJ_PATH+"/CreateAt.o"
} } ;

IntCmd intdep69 = { 'RM DEP' , &rmdep69 } ;

Rm rmdep69 = { { OBJ_PATH+"/CreateAt.dep" } } ;

Target cpp70 = { "Creator.cpp" , "../../Fundamental/CCore/src/./array/Creator.cpp" } ;
Target ocpp70 = { "Creator.o" , OBJ_PATH+"/Creator.o" } ;
Rule rcpp70 = { {&cpp70} , {&ocpp70} , {&intdep70,&execpp70} } ;
Exe execpp70 = { "CC Creator.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./array/Creator.cpp"
 ,"-o"
 ,OBJ_PATH+"/Creator.o"
} } ;

IntCmd intdep70 = { 'RM DEP' , &rmdep70 } ;

Rm rmdep70 = { { OBJ_PATH+"/Creator.dep" } } ;

Target cpp71 = { "CurveDriver.cpp" , "../../Desktop/Draw/CCore/src/./video/CurveDriver.cpp" } ;
Target ocpp71 = { "CurveDriver.o" , OBJ_PATH+"/CurveDriver.o" } ;
Rule rcpp71 = { {&cpp71} , {&ocpp71} , {&intdep71,&execpp71} } ;
Exe execpp71 = { "CC CurveDriver.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Draw/CCore/src/./video/CurveDriver.cpp"
 ,"-o"
 ,OBJ_PATH+"/CurveDriver.o"
} } ;

IntCmd intdep71 = { 'RM DEP' , &rmdep71 } ;

Rm rmdep71 = { { OBJ_PATH+"/CurveDriver.dep" } } ;

Target cpp72 = { "DDLChar.cpp" , "../../Applied/CCore/src/./ddl/DDLChar.cpp" } ;
Target ocpp72 = { "DDLChar.o" , OBJ_PATH+"/DDLChar.o" } ;
Rule rcpp72 = { {&cpp72} , {&ocpp72} , {&intdep72,&execpp72} } ;
Exe execpp72 = { "CC DDLChar.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./ddl/DDLChar.cpp"
 ,"-o"
 ,OBJ_PATH+"/DDLChar.o"
} } ;

IntCmd intdep72 = { 'RM DEP' , &rmdep72 } ;

Rm rmdep72 = { { OBJ_PATH+"/DDLChar.dep" } } ;

Target cpp73 = { "DDLEngine.cpp" , "../../Applied/CCore/src/./ddl/DDLEngine.cpp" } ;
Target ocpp73 = { "DDLEngine.o" , OBJ_PATH+"/DDLEngine.o" } ;
Rule rcpp73 = { {&cpp73} , {&ocpp73} , {&intdep73,&execpp73} } ;
Exe execpp73 = { "CC DDLEngine.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./ddl/DDLEngine.cpp"
 ,"-o"
 ,OBJ_PATH+"/DDLEngine.o"
} } ;

IntCmd intdep73 = { 'RM DEP' , &rmdep73 } ;

Rm rmdep73 = { { OBJ_PATH+"/DDLEngine.dep" } } ;

Target cpp74 = { "DDLErrorMsg.cpp" , "../../Applied/CCore/src/./ddl/DDLErrorMsg.cpp" } ;
Target ocpp74 = { "DDLErrorMsg.o" , OBJ_PATH+"/DDLErrorMsg.o" } ;
Rule rcpp74 = { {&cpp74} , {&ocpp74} , {&intdep74,&execpp74} } ;
Exe execpp74 = { "CC DDLErrorMsg.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./ddl/DDLErrorMsg.cpp"
 ,"-o"
 ,OBJ_PATH+"/DDLErrorMsg.o"
} } ;

IntCmd intdep74 = { 'RM DEP' , &rmdep74 } ;

Rm rmdep74 = { { OBJ_PATH+"/DDLErrorMsg.dep" } } ;

Target cpp75 = { "DDLEval.cpp" , "../../Applied/CCore/src/./ddl/DDLEval.cpp" } ;
Target ocpp75 = { "DDLEval.o" , OBJ_PATH+"/DDLEval.o" } ;
Rule rcpp75 = { {&cpp75} , {&ocpp75} , {&intdep75,&execpp75} } ;
Exe execpp75 = { "CC DDLEval.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./ddl/DDLEval.cpp"
 ,"-o"
 ,OBJ_PATH+"/DDLEval.o"
} } ;

IntCmd intdep75 = { 'RM DEP' , &rmdep75 } ;

Rm rmdep75 = { { OBJ_PATH+"/DDLEval.dep" } } ;

Target cpp76 = { "DDLMap.cpp" , "../../Applied/CCore/src/./ddl/DDLMap.cpp" } ;
Target ocpp76 = { "DDLMap.o" , OBJ_PATH+"/DDLMap.o" } ;
Rule rcpp76 = { {&cpp76} , {&ocpp76} , {&intdep76,&execpp76} } ;
Exe execpp76 = { "CC DDLMap.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./ddl/DDLMap.cpp"
 ,"-o"
 ,OBJ_PATH+"/DDLMap.o"
} } ;

IntCmd intdep76 = { 'RM DEP' , &rmdep76 } ;

Rm rmdep76 = { { OBJ_PATH+"/DDLMap.dep" } } ;

Target cpp77 = { "DDLMapBase.cpp" , "../../Applied/CCore/src/./ddl/DDLMapBase.cpp" } ;
Target ocpp77 = { "DDLMapBase.o" , OBJ_PATH+"/DDLMapBase.o" } ;
Rule rcpp77 = { {&cpp77} , {&ocpp77} , {&intdep77,&execpp77} } ;
Exe execpp77 = { "CC DDLMapBase.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./ddl/DDLMapBase.cpp"
 ,"-o"
 ,OBJ_PATH+"/DDLMapBase.o"
} } ;

IntCmd intdep77 = { 'RM DEP' , &rmdep77 } ;

Rm rmdep77 = { { OBJ_PATH+"/DDLMapBase.dep" } } ;

Target cpp78 = { "DDLMapTools.cpp" , "../../Applied/CCore/src/./ddl/DDLMapTools.cpp" } ;
Target ocpp78 = { "DDLMapTools.o" , OBJ_PATH+"/DDLMapTools.o" } ;
Rule rcpp78 = { {&cpp78} , {&ocpp78} , {&intdep78,&execpp78} } ;
Exe execpp78 = { "CC DDLMapTools.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./ddl/DDLMapTools.cpp"
 ,"-o"
 ,OBJ_PATH+"/DDLMapTools.o"
} } ;

IntCmd intdep78 = { 'RM DEP' , &rmdep78 } ;

Rm rmdep78 = { { OBJ_PATH+"/DDLMapTools.dep" } } ;

Target cpp79 = { "DDLMapTypes.cpp" , "../../Applied/CCore/src/./ddl/DDLMapTypes.cpp" } ;
Target ocpp79 = { "DDLMapTypes.o" , OBJ_PATH+"/DDLMapTypes.o" } ;
Rule rcpp79 = { {&cpp79} , {&ocpp79} , {&intdep79,&execpp79} } ;
Exe execpp79 = { "CC DDLMapTypes.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./ddl/DDLMapTypes.cpp"
 ,"-o"
 ,OBJ_PATH+"/DDLMapTypes.o"
} } ;

IntCmd intdep79 = { 'RM DEP' , &rmdep79 } ;

Rm rmdep79 = { { OBJ_PATH+"/DDLMapTypes.dep" } } ;

Target cpp80 = { "DDLParser.cpp" , "../../Applied/CCore/src/./ddl/DDLParser.cpp" } ;
Target ocpp80 = { "DDLParser.o" , OBJ_PATH+"/DDLParser.o" } ;
Rule rcpp80 = { {&cpp80} , {&ocpp80} , {&intdep80,&execpp80} } ;
Exe execpp80 = { "CC DDLParser.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./ddl/DDLParser.cpp"
 ,"-o"
 ,OBJ_PATH+"/DDLParser.o"
} } ;

IntCmd intdep80 = { 'RM DEP' , &rmdep80 } ;

Rm rmdep80 = { { OBJ_PATH+"/DDLParser.dep" } } ;

Target cpp81 = { "DDLParserElements.cpp" , "../../Applied/CCore/src/./ddl/DDLParserElements.cpp" } ;
Target ocpp81 = { "DDLParserElements.o" , OBJ_PATH+"/DDLParserElements.o" } ;
Rule rcpp81 = { {&cpp81} , {&ocpp81} , {&intdep81,&execpp81} } ;
Exe execpp81 = { "CC DDLParserElements.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./ddl/DDLParserElements.cpp"
 ,"-o"
 ,OBJ_PATH+"/DDLParserElements.o"
} } ;

IntCmd intdep81 = { 'RM DEP' , &rmdep81 } ;

Rm rmdep81 = { { OBJ_PATH+"/DDLParserElements.dep" } } ;

Target cpp82 = { "DDLParserRules.cpp" , "../../Applied/CCore/src/./ddl/DDLParserRules.cpp" } ;
Target ocpp82 = { "DDLParserRules.o" , OBJ_PATH+"/DDLParserRules.o" } ;
Rule rcpp82 = { {&cpp82} , {&ocpp82} , {&intdep82,&execpp82} } ;
Exe execpp82 = { "CC DDLParserRules.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./ddl/DDLParserRules.cpp"
 ,"-o"
 ,OBJ_PATH+"/DDLParserRules.o"
} } ;

IntCmd intdep82 = { 'RM DEP' , &rmdep82 } ;

Rm rmdep82 = { { OBJ_PATH+"/DDLParserRules.dep" } } ;

Target cpp83 = { "DDLParserTable.cpp" , "../../Applied/CCore/src/./ddl/DDLParserTable.cpp" } ;
Target ocpp83 = { "DDLParserTable.o" , OBJ_PATH+"/DDLParserTable.o" } ;
Rule rcpp83 = { {&cpp83} , {&ocpp83} , {&intdep83,&execpp83} } ;
Exe execpp83 = { "CC DDLParserTable.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./ddl/DDLParserTable.cpp"
 ,"-o"
 ,OBJ_PATH+"/DDLParserTable.o"
} } ;

IntCmd intdep83 = { 'RM DEP' , &rmdep83 } ;

Rm rmdep83 = { { OBJ_PATH+"/DDLParserTable.dep" } } ;

Target cpp84 = { "DDLPlatformTypes.cpp" , "../../Applied/CCore/src/./ddl/DDLPlatformTypes.cpp" } ;
Target ocpp84 = { "DDLPlatformTypes.o" , OBJ_PATH+"/DDLPlatformTypes.o" } ;
Rule rcpp84 = { {&cpp84} , {&ocpp84} , {&intdep84,&execpp84} } ;
Exe execpp84 = { "CC DDLPlatformTypes.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./ddl/DDLPlatformTypes.cpp"
 ,"-o"
 ,OBJ_PATH+"/DDLPlatformTypes.o"
} } ;

IntCmd intdep84 = { 'RM DEP' , &rmdep84 } ;

Rm rmdep84 = { { OBJ_PATH+"/DDLPlatformTypes.dep" } } ;

Target cpp85 = { "DDLSemantic.cpp" , "../../Applied/CCore/src/./ddl/DDLSemantic.cpp" } ;
Target ocpp85 = { "DDLSemantic.o" , OBJ_PATH+"/DDLSemantic.o" } ;
Rule rcpp85 = { {&cpp85} , {&ocpp85} , {&intdep85,&execpp85} } ;
Exe execpp85 = { "CC DDLSemantic.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./ddl/DDLSemantic.cpp"
 ,"-o"
 ,OBJ_PATH+"/DDLSemantic.o"
} } ;

IntCmd intdep85 = { 'RM DEP' , &rmdep85 } ;

Rm rmdep85 = { { OBJ_PATH+"/DDLSemantic.dep" } } ;

Target cpp86 = { "DDLToken.cpp" , "../../Applied/CCore/src/./ddl/DDLToken.cpp" } ;
Target ocpp86 = { "DDLToken.o" , OBJ_PATH+"/DDLToken.o" } ;
Rule rcpp86 = { {&cpp86} , {&ocpp86} , {&intdep86,&execpp86} } ;
Exe execpp86 = { "CC DDLToken.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./ddl/DDLToken.cpp"
 ,"-o"
 ,OBJ_PATH+"/DDLToken.o"
} } ;

IntCmd intdep86 = { 'RM DEP' , &rmdep86 } ;

Rm rmdep86 = { { OBJ_PATH+"/DDLToken.dep" } } ;

Target cpp87 = { "DDLTools.cpp" , "../../Applied/CCore/src/./ddl/DDLTools.cpp" } ;
Target ocpp87 = { "DDLTools.o" , OBJ_PATH+"/DDLTools.o" } ;
Rule rcpp87 = { {&cpp87} , {&ocpp87} , {&intdep87,&execpp87} } ;
Exe execpp87 = { "CC DDLTools.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./ddl/DDLTools.cpp"
 ,"-o"
 ,OBJ_PATH+"/DDLTools.o"
} } ;

IntCmd intdep87 = { 'RM DEP' , &rmdep87 } ;

Rm rmdep87 = { { OBJ_PATH+"/DDLTools.dep" } } ;

Target cpp88 = { "DDLTypeDesc.cpp" , "../../Applied/CCore/src/./ddl/DDLTypeDesc.cpp" } ;
Target ocpp88 = { "DDLTypeDesc.o" , OBJ_PATH+"/DDLTypeDesc.o" } ;
Rule rcpp88 = { {&cpp88} , {&ocpp88} , {&intdep88,&execpp88} } ;
Exe execpp88 = { "CC DDLTypeDesc.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./ddl/DDLTypeDesc.cpp"
 ,"-o"
 ,OBJ_PATH+"/DDLTypeDesc.o"
} } ;

IntCmd intdep88 = { 'RM DEP' , &rmdep88 } ;

Rm rmdep88 = { { OBJ_PATH+"/DDLTypeDesc.dep" } } ;

Target cpp89 = { "DDLTypeSet.cpp" , "../../Applied/CCore/src/./ddl/DDLTypeSet.cpp" } ;
Target ocpp89 = { "DDLTypeSet.o" , OBJ_PATH+"/DDLTypeSet.o" } ;
Rule rcpp89 = { {&cpp89} , {&ocpp89} , {&intdep89,&execpp89} } ;
Exe execpp89 = { "CC DDLTypeSet.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./ddl/DDLTypeSet.cpp"
 ,"-o"
 ,OBJ_PATH+"/DDLTypeSet.o"
} } ;

IntCmd intdep89 = { 'RM DEP' , &rmdep89 } ;

Rm rmdep89 = { { OBJ_PATH+"/DDLTypeSet.dep" } } ;

Target cpp90 = { "DDLTypedMap.cpp" , "../../Applied/CCore/src/./ddl/DDLTypedMap.cpp" } ;
Target ocpp90 = { "DDLTypedMap.o" , OBJ_PATH+"/DDLTypedMap.o" } ;
Rule rcpp90 = { {&cpp90} , {&ocpp90} , {&intdep90,&execpp90} } ;
Exe execpp90 = { "CC DDLTypedMap.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./ddl/DDLTypedMap.cpp"
 ,"-o"
 ,OBJ_PATH+"/DDLTypedMap.o"
} } ;

IntCmd intdep90 = { 'RM DEP' , &rmdep90 } ;

Rm rmdep90 = { { OBJ_PATH+"/DDLTypedMap.dep" } } ;

Target cpp91 = { "DDLTypes.cpp" , "../../Applied/CCore/src/./ddl/DDLTypes.cpp" } ;
Target ocpp91 = { "DDLTypes.o" , OBJ_PATH+"/DDLTypes.o" } ;
Rule rcpp91 = { {&cpp91} , {&ocpp91} , {&intdep91,&execpp91} } ;
Exe execpp91 = { "CC DDLTypes.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./ddl/DDLTypes.cpp"
 ,"-o"
 ,OBJ_PATH+"/DDLTypes.o"
} } ;

IntCmd intdep91 = { 'RM DEP' , &rmdep91 } ;

Rm rmdep91 = { { OBJ_PATH+"/DDLTypes.dep" } } ;

Target cpp92 = { "DDLValue.cpp" , "../../Applied/CCore/src/./ddl/DDLValue.cpp" } ;
Target ocpp92 = { "DDLValue.o" , OBJ_PATH+"/DDLValue.o" } ;
Rule rcpp92 = { {&cpp92} , {&ocpp92} , {&intdep92,&execpp92} } ;
Exe execpp92 = { "CC DDLValue.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./ddl/DDLValue.cpp"
 ,"-o"
 ,OBJ_PATH+"/DDLValue.o"
} } ;

IntCmd intdep92 = { 'RM DEP' , &rmdep92 } ;

Rm rmdep92 = { { OBJ_PATH+"/DDLValue.dep" } } ;

Target cpp93 = { "DHExp.cpp" , "../../Applied/CCore/src/./crypton/DHExp.cpp" } ;
Target ocpp93 = { "DHExp.o" , OBJ_PATH+"/DHExp.o" } ;
Rule rcpp93 = { {&cpp93} , {&ocpp93} , {&intdep93,&execpp93} } ;
Exe execpp93 = { "CC DHExp.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./crypton/DHExp.cpp"
 ,"-o"
 ,OBJ_PATH+"/DHExp.o"
} } ;

IntCmd intdep93 = { 'RM DEP' , &rmdep93 } ;

Rm rmdep93 = { { OBJ_PATH+"/DHExp.dep" } } ;

Target cpp94 = { "DecodeFile.cpp" , "../../HCore/CCore/src/DecodeFile.cpp" } ;
Target ocpp94 = { "DecodeFile.o" , OBJ_PATH+"/DecodeFile.o" } ;
Rule rcpp94 = { {&cpp94} , {&ocpp94} , {&intdep94,&execpp94} } ;
Exe execpp94 = { "CC DecodeFile.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/DecodeFile.cpp"
 ,"-o"
 ,OBJ_PATH+"/DecodeFile.o"
} } ;

IntCmd intdep94 = { 'RM DEP' , &rmdep94 } ;

Rm rmdep94 = { { OBJ_PATH+"/DecodeFile.dep" } } ;

Target cpp95 = { "DefaultTimeout.cpp" , "../../Simple/CCore/src/./gadget/DefaultTimeout.cpp" } ;
Target ocpp95 = { "DefaultTimeout.o" , OBJ_PATH+"/DefaultTimeout.o" } ;
Rule rcpp95 = { {&cpp95} , {&ocpp95} , {&intdep95,&execpp95} } ;
Exe execpp95 = { "CC DefaultTimeout.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/DefaultTimeout.cpp"
 ,"-o"
 ,OBJ_PATH+"/DefaultTimeout.o"
} } ;

IntCmd intdep95 = { 'RM DEP' , &rmdep95 } ;

Rm rmdep95 = { { OBJ_PATH+"/DefaultTimeout.dep" } } ;

Target cpp96 = { "DeferCall.cpp" , "../../Fundamental/CCore/src/DeferCall.cpp" } ;
Target ocpp96 = { "DeferCall.o" , OBJ_PATH+"/DeferCall.o" } ;
Rule rcpp96 = { {&cpp96} , {&ocpp96} , {&intdep96,&execpp96} } ;
Exe execpp96 = { "CC DeferCall.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/DeferCall.cpp"
 ,"-o"
 ,OBJ_PATH+"/DeferCall.o"
} } ;

IntCmd intdep96 = { 'RM DEP' , &rmdep96 } ;

Rm rmdep96 = { { OBJ_PATH+"/DeferCall.dep" } } ;

Target cpp97 = { "Deflate.cpp" , "../../Applied/CCore/src/Deflate.cpp" } ;
Target ocpp97 = { "Deflate.o" , OBJ_PATH+"/Deflate.o" } ;
Rule rcpp97 = { {&cpp97} , {&ocpp97} , {&intdep97,&execpp97} } ;
Exe execpp97 = { "CC Deflate.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/Deflate.cpp"
 ,"-o"
 ,OBJ_PATH+"/Deflate.o"
} } ;

IntCmd intdep97 = { 'RM DEP' , &rmdep97 } ;

Rm rmdep97 = { { OBJ_PATH+"/Deflate.dep" } } ;

Target cpp98 = { "Desktop.cpp" , "CCore/src/./video/Desktop.cpp" } ;
Target ocpp98 = { "Desktop.o" , OBJ_PATH+"/Desktop.o" } ;
Rule rcpp98 = { {&cpp98} , {&ocpp98} , {&intdep98,&execpp98} } ;
Exe execpp98 = { "CC Desktop.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./video/Desktop.cpp"
 ,"-o"
 ,OBJ_PATH+"/Desktop.o"
} } ;

IntCmd intdep98 = { 'RM DEP' , &rmdep98 } ;

Rm rmdep98 = { { OBJ_PATH+"/Desktop.dep" } } ;

Target cpp99 = { "DesktopKey.cpp" , "../../Desktop/Tools/CCore/src/./video/DesktopKey.cpp" } ;
Target ocpp99 = { "DesktopKey.o" , OBJ_PATH+"/DesktopKey.o" } ;
Rule rcpp99 = { {&cpp99} , {&ocpp99} , {&intdep99,&execpp99} } ;
Exe execpp99 = { "CC DesktopKey.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Tools/CCore/src/./video/DesktopKey.cpp"
 ,"-o"
 ,OBJ_PATH+"/DesktopKey.o"
} } ;

IntCmd intdep99 = { 'RM DEP' , &rmdep99 } ;

Rm rmdep99 = { { OBJ_PATH+"/DesktopKey.dep" } } ;

Target cpp100 = { "DestroyGuard.cpp" , "../../Simple/CCore/src/DestroyGuard.cpp" } ;
Target ocpp100 = { "DestroyGuard.o" , OBJ_PATH+"/DestroyGuard.o" } ;
Rule rcpp100 = { {&cpp100} , {&ocpp100} , {&intdep100,&execpp100} } ;
Exe execpp100 = { "CC DestroyGuard.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/DestroyGuard.cpp"
 ,"-o"
 ,OBJ_PATH+"/DestroyGuard.o"
} } ;

IntCmd intdep100 = { 'RM DEP' , &rmdep100 } ;

Rm rmdep100 = { { OBJ_PATH+"/DestroyGuard.dep" } } ;

Target cpp101 = { "DetectProxy.cpp" , "../../Fundamental/CCore/src/DetectProxy.cpp" } ;
Target ocpp101 = { "DetectProxy.o" , OBJ_PATH+"/DetectProxy.o" } ;
Rule rcpp101 = { {&cpp101} , {&ocpp101} , {&intdep101,&execpp101} } ;
Exe execpp101 = { "CC DetectProxy.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/DetectProxy.cpp"
 ,"-o"
 ,OBJ_PATH+"/DetectProxy.o"
} } ;

IntCmd intdep101 = { 'RM DEP' , &rmdep101 } ;

Rm rmdep101 = { { OBJ_PATH+"/DetectProxy.dep" } } ;

Target cpp102 = { "DirFrame.cpp" , "../../Desktop/Lib/CCore/src/./video/DirFrame.cpp" } ;
Target ocpp102 = { "DirFrame.o" , OBJ_PATH+"/DirFrame.o" } ;
Rule rcpp102 = { {&cpp102} , {&ocpp102} , {&intdep102,&execpp102} } ;
Exe execpp102 = { "CC DirFrame.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/DirFrame.cpp"
 ,"-o"
 ,OBJ_PATH+"/DirFrame.o"
} } ;

IntCmd intdep102 = { 'RM DEP' , &rmdep102 } ;

Rm rmdep102 = { { OBJ_PATH+"/DirFrame.dep" } } ;

Target cpp103 = { "DirTreeRun.cpp" , "../../HCore/CCore/src/DirTreeRun.cpp" } ;
Target ocpp103 = { "DirTreeRun.o" , OBJ_PATH+"/DirTreeRun.o" } ;
Rule rcpp103 = { {&cpp103} , {&ocpp103} , {&intdep103,&execpp103} } ;
Exe execpp103 = { "CC DirTreeRun.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/DirTreeRun.cpp"
 ,"-o"
 ,OBJ_PATH+"/DirTreeRun.o"
} } ;

IntCmd intdep103 = { 'RM DEP' , &rmdep103 } ;

Rm rmdep103 = { { OBJ_PATH+"/DirTreeRun.dep" } } ;

Target cpp104 = { "DrawBook.cpp" , "../../Desktop/Lib/CCore/src/./video/book/DrawBook.cpp" } ;
Target ocpp104 = { "DrawBook.o" , OBJ_PATH+"/DrawBook.o" } ;
Rule rcpp104 = { {&cpp104} , {&ocpp104} , {&intdep104,&execpp104} } ;
Exe execpp104 = { "CC DrawBook.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/book/DrawBook.cpp"
 ,"-o"
 ,OBJ_PATH+"/DrawBook.o"
} } ;

IntCmd intdep104 = { 'RM DEP' , &rmdep104 } ;

Rm rmdep104 = { { OBJ_PATH+"/DrawBook.dep" } } ;

Target cpp105 = { "DrawBookTools.cpp" , "../../Desktop/Lib/CCore/src/./video/book/DrawBookTools.cpp" } ;
Target ocpp105 = { "DrawBookTools.o" , OBJ_PATH+"/DrawBookTools.o" } ;
Rule rcpp105 = { {&cpp105} , {&ocpp105} , {&intdep105,&execpp105} } ;
Exe execpp105 = { "CC DrawBookTools.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/book/DrawBookTools.cpp"
 ,"-o"
 ,OBJ_PATH+"/DrawBookTools.o"
} } ;

IntCmd intdep105 = { 'RM DEP' , &rmdep105 } ;

Rm rmdep105 = { { OBJ_PATH+"/DrawBookTools.dep" } } ;

Target cpp106 = { "DrawBuf.cpp" , "../../Desktop/Core/CCore/src/./video/DrawBuf.cpp" } ;
Target ocpp106 = { "DrawBuf.o" , OBJ_PATH+"/DrawBuf.o" } ;
Rule rcpp106 = { {&cpp106} , {&ocpp106} , {&intdep106,&execpp106} } ;
Exe execpp106 = { "CC DrawBuf.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Core/CCore/src/./video/DrawBuf.cpp"
 ,"-o"
 ,OBJ_PATH+"/DrawBuf.o"
} } ;

IntCmd intdep106 = { 'RM DEP' , &rmdep106 } ;

Rm rmdep106 = { { OBJ_PATH+"/DrawBuf.dep" } } ;

Target cpp107 = { "DrawTools.cpp" , "../../Desktop/Draw/CCore/src/./video/DrawTools.cpp" } ;
Target ocpp107 = { "DrawTools.o" , OBJ_PATH+"/DrawTools.o" } ;
Rule rcpp107 = { {&cpp107} , {&ocpp107} , {&intdep107,&execpp107} } ;
Exe execpp107 = { "CC DrawTools.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Draw/CCore/src/./video/DrawTools.cpp"
 ,"-o"
 ,OBJ_PATH+"/DrawTools.o"
} } ;

IntCmd intdep107 = { 'RM DEP' , &rmdep107 } ;

Rm rmdep107 = { { OBJ_PATH+"/DrawTools.dep" } } ;

Target cpp108 = { "DynArray.cpp" , "../../Fundamental/CCore/src/./array/DynArray.cpp" } ;
Target ocpp108 = { "DynArray.o" , OBJ_PATH+"/DynArray.o" } ;
Rule rcpp108 = { {&cpp108} , {&ocpp108} , {&intdep108,&execpp108} } ;
Exe execpp108 = { "CC DynArray.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./array/DynArray.cpp"
 ,"-o"
 ,OBJ_PATH+"/DynArray.o"
} } ;

IntCmd intdep108 = { 'RM DEP' , &rmdep108 } ;

Rm rmdep108 = { { OBJ_PATH+"/DynArray.dep" } } ;

Target cpp109 = { "DynObject.cpp" , "../../Simple/CCore/src/DynObject.cpp" } ;
Target ocpp109 = { "DynObject.o" , OBJ_PATH+"/DynObject.o" } ;
Rule rcpp109 = { {&cpp109} , {&ocpp109} , {&intdep109,&execpp109} } ;
Exe execpp109 = { "CC DynObject.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/DynObject.cpp"
 ,"-o"
 ,OBJ_PATH+"/DynObject.o"
} } ;

IntCmd intdep109 = { 'RM DEP' , &rmdep109 } ;

Rm rmdep109 = { { OBJ_PATH+"/DynObject.dep" } } ;

Target cpp110 = { "EDID.cpp" , "../../Applied/CCore/src/./video/EDID.cpp" } ;
Target ocpp110 = { "EDID.o" , OBJ_PATH+"/EDID.o" } ;
Rule rcpp110 = { {&cpp110} , {&ocpp110} , {&intdep110,&execpp110} } ;
Exe execpp110 = { "CC EDID.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./video/EDID.cpp"
 ,"-o"
 ,OBJ_PATH+"/EDID.o"
} } ;

IntCmd intdep110 = { 'RM DEP' , &rmdep110 } ;

Rm rmdep110 = { { OBJ_PATH+"/EDID.dep" } } ;

Target cpp111 = { "EchoDevice.cpp" , "../../Applied/CCore/src/./net/EchoDevice.cpp" } ;
Target ocpp111 = { "EchoDevice.o" , OBJ_PATH+"/EchoDevice.o" } ;
Rule rcpp111 = { {&cpp111} , {&ocpp111} , {&intdep111,&execpp111} } ;
Exe execpp111 = { "CC EchoDevice.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./net/EchoDevice.cpp"
 ,"-o"
 ,OBJ_PATH+"/EchoDevice.o"
} } ;

IntCmd intdep111 = { 'RM DEP' , &rmdep111 } ;

Rm rmdep111 = { { OBJ_PATH+"/EchoDevice.dep" } } ;

Target cpp112 = { "ElementPool.cpp" , "../../Fundamental/CCore/src/ElementPool.cpp" } ;
Target ocpp112 = { "ElementPool.o" , OBJ_PATH+"/ElementPool.o" } ;
Rule rcpp112 = { {&cpp112} , {&ocpp112} , {&intdep112,&execpp112} } ;
Exe execpp112 = { "CC ElementPool.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/ElementPool.cpp"
 ,"-o"
 ,OBJ_PATH+"/ElementPool.o"
} } ;

IntCmd intdep112 = { 'RM DEP' , &rmdep112 } ;

Rm rmdep112 = { { OBJ_PATH+"/ElementPool.dep" } } ;

Target cpp113 = { "Elf.cpp" , "../../Applied/CCore/src/Elf.cpp" } ;
Target ocpp113 = { "Elf.o" , OBJ_PATH+"/Elf.o" } ;
Rule rcpp113 = { {&cpp113} , {&ocpp113} , {&intdep113,&execpp113} } ;
Exe execpp113 = { "CC Elf.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/Elf.cpp"
 ,"-o"
 ,OBJ_PATH+"/Elf.o"
} } ;

IntCmd intdep113 = { 'RM DEP' , &rmdep113 } ;

Rm rmdep113 = { { OBJ_PATH+"/Elf.dep" } } ;

Target cpp114 = { "ErrorText.cpp" , "../../Simple/CCore/src/ErrorText.cpp" } ;
Target ocpp114 = { "ErrorText.o" , OBJ_PATH+"/ErrorText.o" } ;
Rule rcpp114 = { {&cpp114} , {&ocpp114} , {&intdep114,&execpp114} } ;
Exe execpp114 = { "CC ErrorText.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/ErrorText.cpp"
 ,"-o"
 ,OBJ_PATH+"/ErrorText.o"
} } ;

IntCmd intdep114 = { 'RM DEP' , &rmdep114 } ;

Rm rmdep114 = { { OBJ_PATH+"/ErrorText.dep" } } ;

Target cpp115 = { "EthDevice.cpp" , "../../Applied/CCore/src/./net/EthDevice.cpp" } ;
Target ocpp115 = { "EthDevice.o" , OBJ_PATH+"/EthDevice.o" } ;
Rule rcpp115 = { {&cpp115} , {&ocpp115} , {&intdep115,&execpp115} } ;
Exe execpp115 = { "CC EthDevice.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./net/EthDevice.cpp"
 ,"-o"
 ,OBJ_PATH+"/EthDevice.o"
} } ;

IntCmd intdep115 = { 'RM DEP' , &rmdep115 } ;

Rm rmdep115 = { { OBJ_PATH+"/EthDevice.dep" } } ;

Target cpp116 = { "EuclidRotate.cpp" , "../../Fundamental/CCore/src/./algon/EuclidRotate.cpp" } ;
Target ocpp116 = { "EuclidRotate.o" , OBJ_PATH+"/EuclidRotate.o" } ;
Rule rcpp116 = { {&cpp116} , {&ocpp116} , {&intdep116,&execpp116} } ;
Exe execpp116 = { "CC EuclidRotate.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./algon/EuclidRotate.cpp"
 ,"-o"
 ,OBJ_PATH+"/EuclidRotate.o"
} } ;

IntCmd intdep116 = { 'RM DEP' , &rmdep116 } ;

Rm rmdep116 = { { OBJ_PATH+"/EuclidRotate.dep" } } ;

Target cpp117 = { "Event.cpp" , "../../HCore/CCore/src/./task/Event.cpp" } ;
Target ocpp117 = { "Event.o" , OBJ_PATH+"/Event.o" } ;
Rule rcpp117 = { {&cpp117} , {&ocpp117} , {&intdep117,&execpp117} } ;
Exe execpp117 = { "CC Event.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/./task/Event.cpp"
 ,"-o"
 ,OBJ_PATH+"/Event.o"
} } ;

IntCmd intdep117 = { 'RM DEP' , &rmdep117 } ;

Rm rmdep117 = { { OBJ_PATH+"/Event.dep" } } ;

Target cpp118 = { "EventRecorder.cpp" , "../../Applied/CCore/src/EventRecorder.cpp" } ;
Target ocpp118 = { "EventRecorder.o" , OBJ_PATH+"/EventRecorder.o" } ;
Rule rcpp118 = { {&cpp118} , {&ocpp118} , {&intdep118,&execpp118} } ;
Exe execpp118 = { "CC EventRecorder.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/EventRecorder.cpp"
 ,"-o"
 ,OBJ_PATH+"/EventRecorder.o"
} } ;

IntCmd intdep118 = { 'RM DEP' , &rmdep118 } ;

Rm rmdep118 = { { OBJ_PATH+"/EventRecorder.dep" } } ;

Target cpp119 = { "Exception.cpp" , "../../Fundamental/CCore/src/Exception.cpp" } ;
Target ocpp119 = { "Exception.o" , OBJ_PATH+"/Exception.o" } ;
Rule rcpp119 = { {&cpp119} , {&ocpp119} , {&intdep119,&execpp119} } ;
Exe execpp119 = { "CC Exception.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/Exception.cpp"
 ,"-o"
 ,OBJ_PATH+"/Exception.o"
} } ;

IntCmd intdep119 = { 'RM DEP' , &rmdep119 } ;

Rm rmdep119 = { { OBJ_PATH+"/Exception.dep" } } ;

Target cpp120 = { "ExceptionFrame.cpp" , "../../Desktop/Lib/CCore/src/./video/ExceptionFrame.cpp" } ;
Target ocpp120 = { "ExceptionFrame.o" , OBJ_PATH+"/ExceptionFrame.o" } ;
Rule rcpp120 = { {&cpp120} , {&ocpp120} , {&intdep120,&execpp120} } ;
Exe execpp120 = { "CC ExceptionFrame.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/ExceptionFrame.cpp"
 ,"-o"
 ,OBJ_PATH+"/ExceptionFrame.o"
} } ;

IntCmd intdep120 = { 'RM DEP' , &rmdep120 } ;

Rm rmdep120 = { { OBJ_PATH+"/ExceptionFrame.dep" } } ;

Target cpp121 = { "ExceptionType.cpp" , "../../Simple/CCore/src/./gadget/ExceptionType.cpp" } ;
Target ocpp121 = { "ExceptionType.o" , OBJ_PATH+"/ExceptionType.o" } ;
Rule rcpp121 = { {&cpp121} , {&ocpp121} , {&intdep121,&execpp121} } ;
Exe execpp121 = { "CC ExceptionType.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/ExceptionType.cpp"
 ,"-o"
 ,OBJ_PATH+"/ExceptionType.o"
} } ;

IntCmd intdep121 = { 'RM DEP' , &rmdep121 } ;

Rm rmdep121 = { { OBJ_PATH+"/ExceptionType.dep" } } ;

Target cpp122 = { "FFTMul.cpp" , "../../Applied/CCore/src/./math/FFTMul.cpp" } ;
Target ocpp122 = { "FFTMul.o" , OBJ_PATH+"/FFTMul.o" } ;
Rule rcpp122 = { {&cpp122} , {&ocpp122} , {&intdep122,&execpp122} } ;
Exe execpp122 = { "CC FFTMul.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./math/FFTMul.cpp"
 ,"-o"
 ,OBJ_PATH+"/FFTMul.o"
} } ;

IntCmd intdep122 = { 'RM DEP' , &rmdep122 } ;

Rm rmdep122 = { { OBJ_PATH+"/FFTMul.dep" } } ;

Target cpp123 = { "FastMutex.cpp" , "../../HCore/CCore/src/./task/FastMutex.cpp" } ;
Target ocpp123 = { "FastMutex.o" , OBJ_PATH+"/FastMutex.o" } ;
Rule rcpp123 = { {&cpp123} , {&ocpp123} , {&intdep123,&execpp123} } ;
Exe execpp123 = { "CC FastMutex.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/./task/FastMutex.cpp"
 ,"-o"
 ,OBJ_PATH+"/FastMutex.o"
} } ;

IntCmd intdep123 = { 'RM DEP' , &rmdep123 } ;

Rm rmdep123 = { { OBJ_PATH+"/FastMutex.dep" } } ;

Target cpp124 = { "FeedBuf.cpp" , "../../Simple/CCore/src/FeedBuf.cpp" } ;
Target ocpp124 = { "FeedBuf.o" , OBJ_PATH+"/FeedBuf.o" } ;
Rule rcpp124 = { {&cpp124} , {&ocpp124} , {&intdep124,&execpp124} } ;
Exe execpp124 = { "CC FeedBuf.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/FeedBuf.cpp"
 ,"-o"
 ,OBJ_PATH+"/FeedBuf.o"
} } ;

IntCmd intdep124 = { 'RM DEP' , &rmdep124 } ;

Rm rmdep124 = { { OBJ_PATH+"/FeedBuf.dep" } } ;

Target cpp125 = { "Fifo.cpp" , "../../Simple/CCore/src/Fifo.cpp" } ;
Target ocpp125 = { "Fifo.o" , OBJ_PATH+"/Fifo.o" } ;
Rule rcpp125 = { {&cpp125} , {&ocpp125} , {&intdep125,&execpp125} } ;
Exe execpp125 = { "CC Fifo.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/Fifo.cpp"
 ,"-o"
 ,OBJ_PATH+"/Fifo.o"
} } ;

IntCmd intdep125 = { 'RM DEP' , &rmdep125 } ;

Rm rmdep125 = { { OBJ_PATH+"/Fifo.dep" } } ;

Target cpp126 = { "FigureLib.cpp" , "../../Desktop/Lib/CCore/src/./video/FigureLib.cpp" } ;
Target ocpp126 = { "FigureLib.o" , OBJ_PATH+"/FigureLib.o" } ;
Rule rcpp126 = { {&cpp126} , {&ocpp126} , {&intdep126,&execpp126} } ;
Exe execpp126 = { "CC FigureLib.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/FigureLib.cpp"
 ,"-o"
 ,OBJ_PATH+"/FigureLib.o"
} } ;

IntCmd intdep126 = { 'RM DEP' , &rmdep126 } ;

Rm rmdep126 = { { OBJ_PATH+"/FigureLib.dep" } } ;

Target cpp127 = { "FileBoss.cpp" , "../../Desktop/Tools/CCore/src/./video/FileBoss.cpp" } ;
Target ocpp127 = { "FileBoss.o" , OBJ_PATH+"/FileBoss.o" } ;
Rule rcpp127 = { {&cpp127} , {&ocpp127} , {&intdep127,&execpp127} } ;
Exe execpp127 = { "CC FileBoss.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Tools/CCore/src/./video/FileBoss.cpp"
 ,"-o"
 ,OBJ_PATH+"/FileBoss.o"
} } ;

IntCmd intdep127 = { 'RM DEP' , &rmdep127 } ;

Rm rmdep127 = { { OBJ_PATH+"/FileBoss.dep" } } ;

Target cpp128 = { "FileFrame.cpp" , "../../Desktop/Lib/CCore/src/./video/FileFrame.cpp" } ;
Target ocpp128 = { "FileFrame.o" , OBJ_PATH+"/FileFrame.o" } ;
Rule rcpp128 = { {&cpp128} , {&ocpp128} , {&intdep128,&execpp128} } ;
Exe execpp128 = { "CC FileFrame.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/FileFrame.cpp"
 ,"-o"
 ,OBJ_PATH+"/FileFrame.o"
} } ;

IntCmd intdep128 = { 'RM DEP' , &rmdep128 } ;

Rm rmdep128 = { { OBJ_PATH+"/FileFrame.dep" } } ;

Target cpp129 = { "FileName.cpp" , "../../Applied/CCore/src/FileName.cpp" } ;
Target ocpp129 = { "FileName.o" , OBJ_PATH+"/FileName.o" } ;
Rule rcpp129 = { {&cpp129} , {&ocpp129} , {&intdep129,&execpp129} } ;
Exe execpp129 = { "CC FileName.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/FileName.cpp"
 ,"-o"
 ,OBJ_PATH+"/FileName.o"
} } ;

IntCmd intdep129 = { 'RM DEP' , &rmdep129 } ;

Rm rmdep129 = { { OBJ_PATH+"/FileName.dep" } } ;

Target cpp130 = { "FileNameCmp.cpp" , "../../Desktop/Tools/CCore/src/./video/FileNameCmp.cpp" } ;
Target ocpp130 = { "FileNameCmp.o" , OBJ_PATH+"/FileNameCmp.o" } ;
Rule rcpp130 = { {&cpp130} , {&ocpp130} , {&intdep130,&execpp130} } ;
Exe execpp130 = { "CC FileNameCmp.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Tools/CCore/src/./video/FileNameCmp.cpp"
 ,"-o"
 ,OBJ_PATH+"/FileNameCmp.o"
} } ;

IntCmd intdep130 = { 'RM DEP' , &rmdep130 } ;

Rm rmdep130 = { { OBJ_PATH+"/FileNameCmp.dep" } } ;

Target cpp131 = { "FileNameMatch.cpp" , "../../Applied/CCore/src/FileNameMatch.cpp" } ;
Target ocpp131 = { "FileNameMatch.o" , OBJ_PATH+"/FileNameMatch.o" } ;
Rule rcpp131 = { {&cpp131} , {&ocpp131} , {&intdep131,&execpp131} } ;
Exe execpp131 = { "CC FileNameMatch.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/FileNameMatch.cpp"
 ,"-o"
 ,OBJ_PATH+"/FileNameMatch.o"
} } ;

IntCmd intdep131 = { 'RM DEP' , &rmdep131 } ;

Rm rmdep131 = { { OBJ_PATH+"/FileNameMatch.dep" } } ;

Target cpp132 = { "FileSystem.cpp" , "../../HCore/CCore/src/FileSystem.cpp" } ;
Target ocpp132 = { "FileSystem.o" , OBJ_PATH+"/FileSystem.o" } ;
Rule rcpp132 = { {&cpp132} , {&ocpp132} , {&intdep132,&execpp132} } ;
Exe execpp132 = { "CC FileSystem.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/FileSystem.cpp"
 ,"-o"
 ,OBJ_PATH+"/FileSystem.o"
} } ;

IntCmd intdep132 = { 'RM DEP' , &rmdep132 } ;

Rm rmdep132 = { { OBJ_PATH+"/FileSystem.dep" } } ;

Target cpp133 = { "FileToMem.cpp" , "../../HCore/CCore/src/FileToMem.cpp" } ;
Target ocpp133 = { "FileToMem.o" , OBJ_PATH+"/FileToMem.o" } ;
Rule rcpp133 = { {&cpp133} , {&ocpp133} , {&intdep133,&execpp133} } ;
Exe execpp133 = { "CC FileToMem.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/FileToMem.cpp"
 ,"-o"
 ,OBJ_PATH+"/FileToMem.o"
} } ;

IntCmd intdep133 = { 'RM DEP' , &rmdep133 } ;

Rm rmdep133 = { { OBJ_PATH+"/FileToMem.dep" } } ;

Target cpp134 = { "FileToRead.cpp" , "../../HCore/CCore/src/FileToRead.cpp" } ;
Target ocpp134 = { "FileToRead.o" , OBJ_PATH+"/FileToRead.o" } ;
Rule rcpp134 = { {&cpp134} , {&ocpp134} , {&intdep134,&execpp134} } ;
Exe execpp134 = { "CC FileToRead.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/FileToRead.cpp"
 ,"-o"
 ,OBJ_PATH+"/FileToRead.o"
} } ;

IntCmd intdep134 = { 'RM DEP' , &rmdep134 } ;

Rm rmdep134 = { { OBJ_PATH+"/FileToRead.dep" } } ;

Target cpp135 = { "Font.cpp" , "../../Desktop/Font/CCore/src/./video/Font.cpp" } ;
Target ocpp135 = { "Font.o" , OBJ_PATH+"/Font.o" } ;
Rule rcpp135 = { {&cpp135} , {&ocpp135} , {&intdep135,&execpp135} } ;
Exe execpp135 = { "CC Font.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Font/CCore/src/./video/Font.cpp"
 ,"-o"
 ,OBJ_PATH+"/Font.o"
} } ;

IntCmd intdep135 = { 'RM DEP' , &rmdep135 } ;

Rm rmdep135 = { { OBJ_PATH+"/Font.dep" } } ;

Target cpp136 = { "FontDatabase.cpp" , "../../Desktop/Tools/CCore/src/./video/FontDatabase.cpp" } ;
Target ocpp136 = { "FontDatabase.o" , OBJ_PATH+"/FontDatabase.o" } ;
Rule rcpp136 = { {&cpp136} , {&ocpp136} , {&intdep136,&execpp136} } ;
Exe execpp136 = { "CC FontDatabase.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Tools/CCore/src/./video/FontDatabase.cpp"
 ,"-o"
 ,OBJ_PATH+"/FontDatabase.o"
} } ;

IntCmd intdep136 = { 'RM DEP' , &rmdep136 } ;

Rm rmdep136 = { { OBJ_PATH+"/FontDatabase.dep" } } ;

Target cpp137 = { "FontEdit.cpp" , "../../Desktop/Lib/CCore/src/./video/pref/FontEdit.cpp" } ;
Target ocpp137 = { "FontEdit.o" , OBJ_PATH+"/FontEdit.o" } ;
Rule rcpp137 = { {&cpp137} , {&ocpp137} , {&intdep137,&execpp137} } ;
Exe execpp137 = { "CC FontEdit.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/pref/FontEdit.cpp"
 ,"-o"
 ,OBJ_PATH+"/FontEdit.o"
} } ;

IntCmd intdep137 = { 'RM DEP' , &rmdep137 } ;

Rm rmdep137 = { { OBJ_PATH+"/FontEdit.dep" } } ;

Target cpp138 = { "FontLookup.cpp" , "../../Desktop/Tools/CCore/src/./video/FontLookup.cpp" } ;
Target ocpp138 = { "FontLookup.o" , OBJ_PATH+"/FontLookup.o" } ;
Rule rcpp138 = { {&cpp138} , {&ocpp138} , {&intdep138,&execpp138} } ;
Exe execpp138 = { "CC FontLookup.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Tools/CCore/src/./video/FontLookup.cpp"
 ,"-o"
 ,OBJ_PATH+"/FontLookup.o"
} } ;

IntCmd intdep138 = { 'RM DEP' , &rmdep138 } ;

Rm rmdep138 = { { OBJ_PATH+"/FontLookup.dep" } } ;

Target cpp139 = { "FontParam.cpp" , "../../Desktop/Tools/CCore/src/./video/FontParam.cpp" } ;
Target ocpp139 = { "FontParam.o" , OBJ_PATH+"/FontParam.o" } ;
Rule rcpp139 = { {&cpp139} , {&ocpp139} , {&intdep139,&execpp139} } ;
Exe execpp139 = { "CC FontParam.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Tools/CCore/src/./video/FontParam.cpp"
 ,"-o"
 ,OBJ_PATH+"/FontParam.o"
} } ;

IntCmd intdep139 = { 'RM DEP' , &rmdep139 } ;

Rm rmdep139 = { { OBJ_PATH+"/FontParam.dep" } } ;

Target cpp140 = { "FontReplace.cpp" , "../../Desktop/Lib/CCore/src/./video/FontReplace.cpp" } ;
Target ocpp140 = { "FontReplace.o" , OBJ_PATH+"/FontReplace.o" } ;
Rule rcpp140 = { {&cpp140} , {&ocpp140} , {&intdep140,&execpp140} } ;
Exe execpp140 = { "CC FontReplace.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/FontReplace.cpp"
 ,"-o"
 ,OBJ_PATH+"/FontReplace.o"
} } ;

IntCmd intdep140 = { 'RM DEP' , &rmdep140 } ;

Rm rmdep140 = { { OBJ_PATH+"/FontReplace.dep" } } ;

Target cpp141 = { "ForLoop.cpp" , "../../Simple/CCore/src/ForLoop.cpp" } ;
Target ocpp141 = { "ForLoop.o" , OBJ_PATH+"/ForLoop.o" } ;
Rule rcpp141 = { {&cpp141} , {&ocpp141} , {&intdep141,&execpp141} } ;
Exe execpp141 = { "CC ForLoop.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/ForLoop.cpp"
 ,"-o"
 ,OBJ_PATH+"/ForLoop.o"
} } ;

IntCmd intdep141 = { 'RM DEP' , &rmdep141 } ;

Rm rmdep141 = { { OBJ_PATH+"/ForLoop.dep" } } ;

Target cpp142 = { "Forget.cpp" , "../../Applied/CCore/src/./crypton/Forget.cpp" } ;
Target ocpp142 = { "Forget.o" , OBJ_PATH+"/Forget.o" } ;
Rule rcpp142 = { {&cpp142} , {&ocpp142} , {&intdep142,&execpp142} } ;
Exe execpp142 = { "CC Forget.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./crypton/Forget.cpp"
 ,"-o"
 ,OBJ_PATH+"/Forget.o"
} } ;

IntCmd intdep142 = { 'RM DEP' , &rmdep142 } ;

Rm rmdep142 = { { OBJ_PATH+"/Forget.dep" } } ;

Target cpp143 = { "FrameBase.cpp" , "../../Desktop/Lib/CCore/src/./video/FrameBase.cpp" } ;
Target ocpp143 = { "FrameBase.o" , OBJ_PATH+"/FrameBase.o" } ;
Rule rcpp143 = { {&cpp143} , {&ocpp143} , {&intdep143,&execpp143} } ;
Exe execpp143 = { "CC FrameBase.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/FrameBase.cpp"
 ,"-o"
 ,OBJ_PATH+"/FrameBase.o"
} } ;

IntCmd intdep143 = { 'RM DEP' , &rmdep143 } ;

Rm rmdep143 = { { OBJ_PATH+"/FrameBase.dep" } } ;

Target cpp144 = { "FrameBuf.cpp" , "../../Applied/CCore/src/./video/FrameBuf.cpp" } ;
Target ocpp144 = { "FrameBuf.o" , OBJ_PATH+"/FrameBuf.o" } ;
Rule rcpp144 = { {&cpp144} , {&ocpp144} , {&intdep144,&execpp144} } ;
Exe execpp144 = { "CC FrameBuf.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./video/FrameBuf.cpp"
 ,"-o"
 ,OBJ_PATH+"/FrameBuf.o"
} } ;

IntCmd intdep144 = { 'RM DEP' , &rmdep144 } ;

Rm rmdep144 = { { OBJ_PATH+"/FrameBuf.dep" } } ;

Target cpp145 = { "FrameOf.cpp" , "../../Desktop/Lib/CCore/src/./video/FrameOf.cpp" } ;
Target ocpp145 = { "FrameOf.o" , OBJ_PATH+"/FrameOf.o" } ;
Rule rcpp145 = { {&cpp145} , {&ocpp145} , {&intdep145,&execpp145} } ;
Exe execpp145 = { "CC FrameOf.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/FrameOf.cpp"
 ,"-o"
 ,OBJ_PATH+"/FrameOf.o"
} } ;

IntCmd intdep145 = { 'RM DEP' , &rmdep145 } ;

Rm rmdep145 = { { OBJ_PATH+"/FrameOf.dep" } } ;

Target cpp146 = { "FrameWindow.cpp" , "../../Desktop/Core/CCore/src/./video/FrameWindow.cpp" } ;
Target ocpp146 = { "FrameWindow.o" , OBJ_PATH+"/FrameWindow.o" } ;
Rule rcpp146 = { {&cpp146} , {&ocpp146} , {&intdep146,&execpp146} } ;
Exe execpp146 = { "CC FrameWindow.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Core/CCore/src/./video/FrameWindow.cpp"
 ,"-o"
 ,OBJ_PATH+"/FrameWindow.o"
} } ;

IntCmd intdep146 = { 'RM DEP' , &rmdep146 } ;

Rm rmdep146 = { { OBJ_PATH+"/FrameWindow.dep" } } ;

Target cpp147 = { "FreeType.cpp" , "../../Desktop/Font/CCore/src/./video/FreeType.cpp" } ;
Target ocpp147 = { "FreeType.o" , OBJ_PATH+"/FreeType.o" } ;
Rule rcpp147 = { {&cpp147} , {&ocpp147} , {&intdep147,&execpp147} } ;
Exe execpp147 = { "CC FreeType.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Font/CCore/src/./video/FreeType.cpp"
 ,"-o"
 ,OBJ_PATH+"/FreeType.o"
} } ;

IntCmd intdep147 = { 'RM DEP' , &rmdep147 } ;

Rm rmdep147 = { { OBJ_PATH+"/FreeType.dep" } } ;

Target cpp148 = { "FreeTypeFont.cpp" , "../../Desktop/Font/CCore/src/./video/FreeTypeFont.cpp" } ;
Target ocpp148 = { "FreeTypeFont.o" , OBJ_PATH+"/FreeTypeFont.o" } ;
Rule rcpp148 = { {&cpp148} , {&ocpp148} , {&intdep148,&execpp148} } ;
Exe execpp148 = { "CC FreeTypeFont.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Font/CCore/src/./video/FreeTypeFont.cpp"
 ,"-o"
 ,OBJ_PATH+"/FreeTypeFont.o"
} } ;

IntCmd intdep148 = { 'RM DEP' , &rmdep148 } ;

Rm rmdep148 = { { OBJ_PATH+"/FreeTypeFont.dep" } } ;

Target cpp149 = { "FuncTask.cpp" , "../../Applied/CCore/src/./task/FuncTask.cpp" } ;
Target ocpp149 = { "FuncTask.o" , OBJ_PATH+"/FuncTask.o" } ;
Rule rcpp149 = { {&cpp149} , {&ocpp149} , {&intdep149,&execpp149} } ;
Exe execpp149 = { "CC FuncTask.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./task/FuncTask.cpp"
 ,"-o"
 ,OBJ_PATH+"/FuncTask.o"
} } ;

IntCmd intdep149 = { 'RM DEP' , &rmdep149 } ;

Rm rmdep149 = { { OBJ_PATH+"/FuncTask.dep" } } ;

Target cpp150 = { "Function.cpp" , "../../Simple/CCore/src/./gadget/Function.cpp" } ;
Target ocpp150 = { "Function.o" , OBJ_PATH+"/Function.o" } ;
Rule rcpp150 = { {&cpp150} , {&ocpp150} , {&intdep150,&execpp150} } ;
Exe execpp150 = { "CC Function.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/Function.cpp"
 ,"-o"
 ,OBJ_PATH+"/Function.o"
} } ;

IntCmd intdep150 = { 'RM DEP' , &rmdep150 } ;

Rm rmdep150 = { { OBJ_PATH+"/Function.dep" } } ;

Target cpp151 = { "FunctorType.cpp" , "../../Simple/CCore/src/FunctorType.cpp" } ;
Target ocpp151 = { "FunctorType.o" , OBJ_PATH+"/FunctorType.o" } ;
Rule rcpp151 = { {&cpp151} , {&ocpp151} , {&intdep151,&execpp151} } ;
Exe execpp151 = { "CC FunctorType.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/FunctorType.cpp"
 ,"-o"
 ,OBJ_PATH+"/FunctorType.o"
} } ;

IntCmd intdep151 = { 'RM DEP' , &rmdep151 } ;

Rm rmdep151 = { { OBJ_PATH+"/FunctorType.dep" } } ;

Target cpp152 = { "GCDConst.cpp" , "../../Fundamental/CCore/src/./algon/GCDConst.cpp" } ;
Target ocpp152 = { "GCDConst.o" , OBJ_PATH+"/GCDConst.o" } ;
Rule rcpp152 = { {&cpp152} , {&ocpp152} , {&intdep152,&execpp152} } ;
Exe execpp152 = { "CC GCDConst.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./algon/GCDConst.cpp"
 ,"-o"
 ,OBJ_PATH+"/GCDConst.o"
} } ;

IntCmd intdep152 = { 'RM DEP' , &rmdep152 } ;

Rm rmdep152 = { { OBJ_PATH+"/GCDConst.dep" } } ;

Target cpp153 = { "Gadget.cpp" , "../../Simple/CCore/src/Gadget.cpp" } ;
Target ocpp153 = { "Gadget.o" , OBJ_PATH+"/Gadget.o" } ;
Rule rcpp153 = { {&cpp153} , {&ocpp153} , {&intdep153,&execpp153} } ;
Exe execpp153 = { "CC Gadget.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/Gadget.cpp"
 ,"-o"
 ,OBJ_PATH+"/Gadget.o"
} } ;

IntCmd intdep153 = { 'RM DEP' , &rmdep153 } ;

Rm rmdep153 = { { OBJ_PATH+"/Gadget.dep" } } ;

Target cpp154 = { "Gamma.cpp" , "../../Applied/CCore/src/./video/Gamma.cpp" } ;
Target ocpp154 = { "Gamma.o" , OBJ_PATH+"/Gamma.o" } ;
Rule rcpp154 = { {&cpp154} , {&ocpp154} , {&intdep154,&execpp154} } ;
Exe execpp154 = { "CC Gamma.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./video/Gamma.cpp"
 ,"-o"
 ,OBJ_PATH+"/Gamma.o"
} } ;

IntCmd intdep154 = { 'RM DEP' , &rmdep154 } ;

Rm rmdep154 = { { OBJ_PATH+"/Gamma.dep" } } ;

Target cpp155 = { "GammaTable.cpp" , "../../Desktop/Draw/CCore/src/./video/GammaTable.cpp" } ;
Target ocpp155 = { "GammaTable.o" , OBJ_PATH+"/GammaTable.o" } ;
Rule rcpp155 = { {&cpp155} , {&ocpp155} , {&intdep155,&execpp155} } ;
Exe execpp155 = { "CC GammaTable.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Draw/CCore/src/./video/GammaTable.cpp"
 ,"-o"
 ,OBJ_PATH+"/GammaTable.o"
} } ;

IntCmd intdep155 = { 'RM DEP' , &rmdep155 } ;

Rm rmdep155 = { { OBJ_PATH+"/GammaTable.dep" } } ;

Target cpp156 = { "GenFile.cpp" , "../../Fundamental/CCore/src/GenFile.cpp" } ;
Target ocpp156 = { "GenFile.o" , OBJ_PATH+"/GenFile.o" } ;
Rule rcpp156 = { {&cpp156} , {&ocpp156} , {&intdep156,&execpp156} } ;
Exe execpp156 = { "CC GenFile.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/GenFile.cpp"
 ,"-o"
 ,OBJ_PATH+"/GenFile.o"
} } ;

IntCmd intdep156 = { 'RM DEP' , &rmdep156 } ;

Rm rmdep156 = { { OBJ_PATH+"/GenFile.dep" } } ;

Target cpp157 = { "HFSBase.cpp" , "../../Applied/CCore/src/./net/HFSBase.cpp" } ;
Target ocpp157 = { "HFSBase.o" , OBJ_PATH+"/HFSBase.o" } ;
Rule rcpp157 = { {&cpp157} , {&ocpp157} , {&intdep157,&execpp157} } ;
Exe execpp157 = { "CC HFSBase.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./net/HFSBase.cpp"
 ,"-o"
 ,OBJ_PATH+"/HFSBase.o"
} } ;

IntCmd intdep157 = { 'RM DEP' , &rmdep157 } ;

Rm rmdep157 = { { OBJ_PATH+"/HFSBase.dep" } } ;

Target cpp158 = { "HFSClientDevice.cpp" , "../../Applied/CCore/src/./net/HFSClientDevice.cpp" } ;
Target ocpp158 = { "HFSClientDevice.o" , OBJ_PATH+"/HFSClientDevice.o" } ;
Rule rcpp158 = { {&cpp158} , {&ocpp158} , {&intdep158,&execpp158} } ;
Exe execpp158 = { "CC HFSClientDevice.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./net/HFSClientDevice.cpp"
 ,"-o"
 ,OBJ_PATH+"/HFSClientDevice.o"
} } ;

IntCmd intdep158 = { 'RM DEP' , &rmdep158 } ;

Rm rmdep158 = { { OBJ_PATH+"/HFSClientDevice.dep" } } ;

Target cpp159 = { "HFSFileSystemDevice.cpp" , "../../Applied/CCore/src/./net/HFSFileSystemDevice.cpp" } ;
Target ocpp159 = { "HFSFileSystemDevice.o" , OBJ_PATH+"/HFSFileSystemDevice.o" } ;
Rule rcpp159 = { {&cpp159} , {&ocpp159} , {&intdep159,&execpp159} } ;
Exe execpp159 = { "CC HFSFileSystemDevice.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./net/HFSFileSystemDevice.cpp"
 ,"-o"
 ,OBJ_PATH+"/HFSFileSystemDevice.o"
} } ;

IntCmd intdep159 = { 'RM DEP' , &rmdep159 } ;

Rm rmdep159 = { { OBJ_PATH+"/HFSFileSystemDevice.dep" } } ;

Target cpp160 = { "Handle.cpp" , "../../Simple/CCore/src/./gadget/Handle.cpp" } ;
Target ocpp160 = { "Handle.o" , OBJ_PATH+"/Handle.o" } ;
Rule rcpp160 = { {&cpp160} , {&ocpp160} , {&intdep160,&execpp160} } ;
Exe execpp160 = { "CC Handle.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/Handle.cpp"
 ,"-o"
 ,OBJ_PATH+"/Handle.o"
} } ;

IntCmd intdep160 = { 'RM DEP' , &rmdep160 } ;

Rm rmdep160 = { { OBJ_PATH+"/Handle.dep" } } ;

Target cpp161 = { "HashFunction.cpp" , "../../Applied/CCore/src/./crypton/HashFunction.cpp" } ;
Target ocpp161 = { "HashFunction.o" , OBJ_PATH+"/HashFunction.o" } ;
Rule rcpp161 = { {&cpp161} , {&ocpp161} , {&intdep161,&execpp161} } ;
Exe execpp161 = { "CC HashFunction.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./crypton/HashFunction.cpp"
 ,"-o"
 ,OBJ_PATH+"/HashFunction.o"
} } ;

IntCmd intdep161 = { 'RM DEP' , &rmdep161 } ;

Rm rmdep161 = { { OBJ_PATH+"/HashFunction.dep" } } ;

Target cpp162 = { "HeapEngine.cpp" , "../../Fundamental/CCore/src/HeapEngine.cpp" } ;
Target ocpp162 = { "HeapEngine.o" , OBJ_PATH+"/HeapEngine.o" } ;
Rule rcpp162 = { {&cpp162} , {&ocpp162} , {&intdep162,&execpp162} } ;
Exe execpp162 = { "CC HeapEngine.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/HeapEngine.cpp"
 ,"-o"
 ,OBJ_PATH+"/HeapEngine.o"
} } ;

IntCmd intdep162 = { 'RM DEP' , &rmdep162 } ;

Rm rmdep162 = { { OBJ_PATH+"/HeapEngine.dep" } } ;

Target cpp163 = { "HeapSort.cpp" , "../../Fundamental/CCore/src/./sort/HeapSort.cpp" } ;
Target ocpp163 = { "HeapSort.o" , OBJ_PATH+"/HeapSort.o" } ;
Rule rcpp163 = { {&cpp163} , {&ocpp163} , {&intdep163,&execpp163} } ;
Exe execpp163 = { "CC HeapSort.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./sort/HeapSort.cpp"
 ,"-o"
 ,OBJ_PATH+"/HeapSort.o"
} } ;

IntCmd intdep163 = { 'RM DEP' , &rmdep163 } ;

Rm rmdep163 = { { OBJ_PATH+"/HeapSort.dep" } } ;

Target cpp164 = { "HomeFile.cpp" , "../../Desktop/Tools/CCore/src/./video/HomeFile.cpp" } ;
Target ocpp164 = { "HomeFile.o" , OBJ_PATH+"/HomeFile.o" } ;
Rule rcpp164 = { {&cpp164} , {&ocpp164} , {&intdep164,&execpp164} } ;
Exe execpp164 = { "CC HomeFile.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Tools/CCore/src/./video/HomeFile.cpp"
 ,"-o"
 ,OBJ_PATH+"/HomeFile.o"
} } ;

IntCmd intdep164 = { 'RM DEP' , &rmdep164 } ;

Rm rmdep164 = { { OBJ_PATH+"/HomeFile.dep" } } ;

Target cpp165 = { "Incremental.cpp" , "../../Desktop/Tools/CCore/src/./video/Incremental.cpp" } ;
Target ocpp165 = { "Incremental.o" , OBJ_PATH+"/Incremental.o" } ;
Rule rcpp165 = { {&cpp165} , {&ocpp165} , {&intdep165,&execpp165} } ;
Exe execpp165 = { "CC Incremental.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Tools/CCore/src/./video/Incremental.cpp"
 ,"-o"
 ,OBJ_PATH+"/Incremental.o"
} } ;

IntCmd intdep165 = { 'RM DEP' , &rmdep165 } ;

Rm rmdep165 = { { OBJ_PATH+"/Incremental.dep" } } ;

Target cpp166 = { "Info.cpp" , "../../Desktop/Tools/CCore/src/./video/Info.cpp" } ;
Target ocpp166 = { "Info.o" , OBJ_PATH+"/Info.o" } ;
Rule rcpp166 = { {&cpp166} , {&ocpp166} , {&intdep166,&execpp166} } ;
Exe execpp166 = { "CC Info.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Tools/CCore/src/./video/Info.cpp"
 ,"-o"
 ,OBJ_PATH+"/Info.o"
} } ;

IntCmd intdep166 = { 'RM DEP' , &rmdep166 } ;

Rm rmdep166 = { { OBJ_PATH+"/Info.dep" } } ;

Target cpp167 = { "InfoSize.cpp" , "../../Desktop/Tools/CCore/src/./video/InfoSize.cpp" } ;
Target ocpp167 = { "InfoSize.o" , OBJ_PATH+"/InfoSize.o" } ;
Rule rcpp167 = { {&cpp167} , {&ocpp167} , {&intdep167,&execpp167} } ;
Exe execpp167 = { "CC InfoSize.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Tools/CCore/src/./video/InfoSize.cpp"
 ,"-o"
 ,OBJ_PATH+"/InfoSize.o"
} } ;

IntCmd intdep167 = { 'RM DEP' , &rmdep167 } ;

Rm rmdep167 = { { OBJ_PATH+"/InfoSize.dep" } } ;

Target cpp168 = { "Init.cpp" , "../../Simple/CCore/src/./gadget/Init.cpp" } ;
Target ocpp168 = { "Init.o" , OBJ_PATH+"/Init.o" } ;
Rule rcpp168 = { {&cpp168} , {&ocpp168} , {&intdep168,&execpp168} } ;
Exe execpp168 = { "CC Init.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/Init.cpp"
 ,"-o"
 ,OBJ_PATH+"/Init.o"
} } ;

IntCmd intdep168 = { 'RM DEP' , &rmdep168 } ;

Rm rmdep168 = { { OBJ_PATH+"/Init.dep" } } ;

Target cpp169 = { "InputUtils.cpp" , "../../Applied/CCore/src/InputUtils.cpp" } ;
Target ocpp169 = { "InputUtils.o" , OBJ_PATH+"/InputUtils.o" } ;
Rule rcpp169 = { {&cpp169} , {&ocpp169} , {&intdep169,&execpp169} } ;
Exe execpp169 = { "CC InputUtils.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/InputUtils.cpp"
 ,"-o"
 ,OBJ_PATH+"/InputUtils.o"
} } ;

IntCmd intdep169 = { 'RM DEP' , &rmdep169 } ;

Rm rmdep169 = { { OBJ_PATH+"/InputUtils.dep" } } ;

Target cpp170 = { "InstanceLock.cpp" , "../../Simple/CCore/src/InstanceLock.cpp" } ;
Target ocpp170 = { "InstanceLock.o" , OBJ_PATH+"/InstanceLock.o" } ;
Rule rcpp170 = { {&cpp170} , {&ocpp170} , {&intdep170,&execpp170} } ;
Exe execpp170 = { "CC InstanceLock.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/InstanceLock.cpp"
 ,"-o"
 ,OBJ_PATH+"/InstanceLock.o"
} } ;

IntCmd intdep170 = { 'RM DEP' , &rmdep170 } ;

Rm rmdep170 = { { OBJ_PATH+"/InstanceLock.dep" } } ;

Target cpp171 = { "IntOp.cpp" , "../../Applied/CCore/src/./video/IntOp.cpp" } ;
Target ocpp171 = { "IntOp.o" , OBJ_PATH+"/IntOp.o" } ;
Rule rcpp171 = { {&cpp171} , {&ocpp171} , {&intdep171,&execpp171} } ;
Exe execpp171 = { "CC IntOp.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./video/IntOp.cpp"
 ,"-o"
 ,OBJ_PATH+"/IntOp.o"
} } ;

IntCmd intdep171 = { 'RM DEP' , &rmdep171 } ;

Rm rmdep171 = { { OBJ_PATH+"/IntOp.dep" } } ;

Target cpp172 = { "IntPrint.cpp" , "../../Fundamental/CCore/src/./printf/IntPrint.cpp" } ;
Target ocpp172 = { "IntPrint.o" , OBJ_PATH+"/IntPrint.o" } ;
Rule rcpp172 = { {&cpp172} , {&ocpp172} , {&intdep172,&execpp172} } ;
Exe execpp172 = { "CC IntPrint.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./printf/IntPrint.cpp"
 ,"-o"
 ,OBJ_PATH+"/IntPrint.o"
} } ;

IntCmd intdep172 = { 'RM DEP' , &rmdep172 } ;

Rm rmdep172 = { { OBJ_PATH+"/IntPrint.dep" } } ;

Target cpp173 = { "IntScan.cpp" , "../../Fundamental/CCore/src/./scanf/IntScan.cpp" } ;
Target ocpp173 = { "IntScan.o" , OBJ_PATH+"/IntScan.o" } ;
Rule rcpp173 = { {&cpp173} , {&ocpp173} , {&intdep173,&execpp173} } ;
Exe execpp173 = { "CC IntScan.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./scanf/IntScan.cpp"
 ,"-o"
 ,OBJ_PATH+"/IntScan.o"
} } ;

IntCmd intdep173 = { 'RM DEP' , &rmdep173 } ;

Rm rmdep173 = { { OBJ_PATH+"/IntScan.dep" } } ;

Target cpp174 = { "Integer.cpp" , "../../Applied/CCore/src/./math/Integer.cpp" } ;
Target ocpp174 = { "Integer.o" , OBJ_PATH+"/Integer.o" } ;
Rule rcpp174 = { {&cpp174} , {&ocpp174} , {&intdep174,&execpp174} } ;
Exe execpp174 = { "CC Integer.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./math/Integer.cpp"
 ,"-o"
 ,OBJ_PATH+"/Integer.o"
} } ;

IntCmd intdep174 = { 'RM DEP' , &rmdep174 } ;

Rm rmdep174 = { { OBJ_PATH+"/Integer.dep" } } ;

Target cpp175 = { "IntegerAlgo.cpp" , "../../Applied/CCore/src/./math/IntegerAlgo.cpp" } ;
Target ocpp175 = { "IntegerAlgo.o" , OBJ_PATH+"/IntegerAlgo.o" } ;
Rule rcpp175 = { {&cpp175} , {&ocpp175} , {&intdep175,&execpp175} } ;
Exe execpp175 = { "CC IntegerAlgo.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./math/IntegerAlgo.cpp"
 ,"-o"
 ,OBJ_PATH+"/IntegerAlgo.o"
} } ;

IntCmd intdep175 = { 'RM DEP' , &rmdep175 } ;

Rm rmdep175 = { { OBJ_PATH+"/IntegerAlgo.dep" } } ;

Target cpp176 = { "IntegerBuilder.cpp" , "../../Applied/CCore/src/./math/IntegerBuilder.cpp" } ;
Target ocpp176 = { "IntegerBuilder.o" , OBJ_PATH+"/IntegerBuilder.o" } ;
Rule rcpp176 = { {&cpp176} , {&ocpp176} , {&intdep176,&execpp176} } ;
Exe execpp176 = { "CC IntegerBuilder.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./math/IntegerBuilder.cpp"
 ,"-o"
 ,OBJ_PATH+"/IntegerBuilder.o"
} } ;

IntCmd intdep176 = { 'RM DEP' , &rmdep176 } ;

Rm rmdep176 = { { OBJ_PATH+"/IntegerBuilder.dep" } } ;

Target cpp177 = { "IntegerDivider.cpp" , "../../Applied/CCore/src/./math/IntegerDivider.cpp" } ;
Target ocpp177 = { "IntegerDivider.o" , OBJ_PATH+"/IntegerDivider.o" } ;
Rule rcpp177 = { {&cpp177} , {&ocpp177} , {&intdep177,&execpp177} } ;
Exe execpp177 = { "CC IntegerDivider.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./math/IntegerDivider.cpp"
 ,"-o"
 ,OBJ_PATH+"/IntegerDivider.o"
} } ;

IntCmd intdep177 = { 'RM DEP' , &rmdep177 } ;

Rm rmdep177 = { { OBJ_PATH+"/IntegerDivider.dep" } } ;

Target cpp178 = { "IntegerFastAlgo.cpp" , "CCore/src/./math/IntegerFastAlgo.cpp" } ;
Target ocpp178 = { "IntegerFastAlgo.o" , OBJ_PATH+"/IntegerFastAlgo.o" } ;
Rule rcpp178 = { {&cpp178} , {&ocpp178} , {&intdep178,&execpp178} } ;
Exe execpp178 = { "CC IntegerFastAlgo.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./math/IntegerFastAlgo.cpp"
 ,"-o"
 ,OBJ_PATH+"/IntegerFastAlgo.o"
} } ;

IntCmd intdep178 = { 'RM DEP' , &rmdep178 } ;

Rm rmdep178 = { { OBJ_PATH+"/IntegerFastAlgo.dep" } } ;

Target cpp179 = { "IntegerFromString.cpp" , "../../Applied/CCore/src/./math/IntegerFromString.cpp" } ;
Target ocpp179 = { "IntegerFromString.o" , OBJ_PATH+"/IntegerFromString.o" } ;
Rule rcpp179 = { {&cpp179} , {&ocpp179} , {&intdep179,&execpp179} } ;
Exe execpp179 = { "CC IntegerFromString.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./math/IntegerFromString.cpp"
 ,"-o"
 ,OBJ_PATH+"/IntegerFromString.o"
} } ;

IntCmd intdep179 = { 'RM DEP' , &rmdep179 } ;

Rm rmdep179 = { { OBJ_PATH+"/IntegerFromString.dep" } } ;

Target cpp180 = { "IntegerGCD.cpp" , "../../Applied/CCore/src/./math/IntegerGCD.cpp" } ;
Target ocpp180 = { "IntegerGCD.o" , OBJ_PATH+"/IntegerGCD.o" } ;
Rule rcpp180 = { {&cpp180} , {&ocpp180} , {&intdep180,&execpp180} } ;
Exe execpp180 = { "CC IntegerGCD.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./math/IntegerGCD.cpp"
 ,"-o"
 ,OBJ_PATH+"/IntegerGCD.o"
} } ;

IntCmd intdep180 = { 'RM DEP' , &rmdep180 } ;

Rm rmdep180 = { { OBJ_PATH+"/IntegerGCD.dep" } } ;

Target cpp181 = { "IntegerMulAlgo.cpp" , "../../Applied/CCore/src/./math/IntegerMulAlgo.cpp" } ;
Target ocpp181 = { "IntegerMulAlgo.o" , OBJ_PATH+"/IntegerMulAlgo.o" } ;
Rule rcpp181 = { {&cpp181} , {&ocpp181} , {&intdep181,&execpp181} } ;
Exe execpp181 = { "CC IntegerMulAlgo.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./math/IntegerMulAlgo.cpp"
 ,"-o"
 ,OBJ_PATH+"/IntegerMulAlgo.o"
} } ;

IntCmd intdep181 = { 'RM DEP' , &rmdep181 } ;

Rm rmdep181 = { { OBJ_PATH+"/IntegerMulAlgo.dep" } } ;

Target cpp182 = { "IntegerOctetBuilder.cpp" , "../../Applied/CCore/src/./math/IntegerOctetBuilder.cpp" } ;
Target ocpp182 = { "IntegerOctetBuilder.o" , OBJ_PATH+"/IntegerOctetBuilder.o" } ;
Rule rcpp182 = { {&cpp182} , {&ocpp182} , {&intdep182,&execpp182} } ;
Exe execpp182 = { "CC IntegerOctetBuilder.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./math/IntegerOctetBuilder.cpp"
 ,"-o"
 ,OBJ_PATH+"/IntegerOctetBuilder.o"
} } ;

IntCmd intdep182 = { 'RM DEP' , &rmdep182 } ;

Rm rmdep182 = { { OBJ_PATH+"/IntegerOctetBuilder.dep" } } ;

Target cpp183 = { "IntegerSlowAlgo.cpp" , "../../Applied/CCore/src/./math/IntegerSlowAlgo.cpp" } ;
Target ocpp183 = { "IntegerSlowAlgo.o" , OBJ_PATH+"/IntegerSlowAlgo.o" } ;
Rule rcpp183 = { {&cpp183} , {&ocpp183} , {&intdep183,&execpp183} } ;
Exe execpp183 = { "CC IntegerSlowAlgo.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./math/IntegerSlowAlgo.cpp"
 ,"-o"
 ,OBJ_PATH+"/IntegerSlowAlgo.o"
} } ;

IntCmd intdep183 = { 'RM DEP' , &rmdep183 } ;

Rm rmdep183 = { { OBJ_PATH+"/IntegerSlowAlgo.dep" } } ;

Target cpp184 = { "IntelAES.cpp" , "CCore/src/./crypton/IntelAES.cpp" } ;
Target ocpp184 = { "IntelAES.o" , OBJ_PATH+"/IntelAES.o" } ;
Rule rcpp184 = { {&cpp184} , {&ocpp184} , {&intdep184,&execpp184} } ;
Exe execpp184 = { "CC IntelAES.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./crypton/IntelAES.cpp"
 ,"-o"
 ,OBJ_PATH+"/IntelAES.o"
} } ;

IntCmd intdep184 = { 'RM DEP' , &rmdep184 } ;

Rm rmdep184 = { { OBJ_PATH+"/IntelAES.dep" } } ;

Target cpp185 = { "IntelCPUID.cpp" , "CCore/src/./crypton/IntelCPUID.cpp" } ;
Target ocpp185 = { "IntelCPUID.o" , OBJ_PATH+"/IntelCPUID.o" } ;
Rule rcpp185 = { {&cpp185} , {&ocpp185} , {&intdep185,&execpp185} } ;
Exe execpp185 = { "CC IntelCPUID.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./crypton/IntelCPUID.cpp"
 ,"-o"
 ,OBJ_PATH+"/IntelCPUID.o"
} } ;

IntCmd intdep185 = { 'RM DEP' , &rmdep185 } ;

Rm rmdep185 = { { OBJ_PATH+"/IntelCPUID.dep" } } ;

Target cpp186 = { "IntelRandom.cpp" , "CCore/src/./crypton/IntelRandom.cpp" } ;
Target ocpp186 = { "IntelRandom.o" , OBJ_PATH+"/IntelRandom.o" } ;
Rule rcpp186 = { {&cpp186} , {&ocpp186} , {&intdep186,&execpp186} } ;
Exe execpp186 = { "CC IntelRandom.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./crypton/IntelRandom.cpp"
 ,"-o"
 ,OBJ_PATH+"/IntelRandom.o"
} } ;

IntCmd intdep186 = { 'RM DEP' , &rmdep186 } ;

Rm rmdep186 = { { OBJ_PATH+"/IntelRandom.dep" } } ;

Target cpp187 = { "InterfaceHost.cpp" , "../../Fundamental/CCore/src/InterfaceHost.cpp" } ;
Target ocpp187 = { "InterfaceHost.o" , OBJ_PATH+"/InterfaceHost.o" } ;
Rule rcpp187 = { {&cpp187} , {&ocpp187} , {&intdep187,&execpp187} } ;
Exe execpp187 = { "CC InterfaceHost.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/InterfaceHost.cpp"
 ,"-o"
 ,OBJ_PATH+"/InterfaceHost.o"
} } ;

IntCmd intdep187 = { 'RM DEP' , &rmdep187 } ;

Rm rmdep187 = { { OBJ_PATH+"/InterfaceHost.dep" } } ;

Target cpp188 = { "InternalDesktop.cpp" , "CCore/src/./video/InternalDesktop.cpp" } ;
Target ocpp188 = { "InternalDesktop.o" , OBJ_PATH+"/InternalDesktop.o" } ;
Rule rcpp188 = { {&cpp188} , {&ocpp188} , {&intdep188,&execpp188} } ;
Exe execpp188 = { "CC InternalDesktop.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./video/InternalDesktop.cpp"
 ,"-o"
 ,OBJ_PATH+"/InternalDesktop.o"
} } ;

IntCmd intdep188 = { 'RM DEP' , &rmdep188 } ;

Rm rmdep188 = { { OBJ_PATH+"/InternalDesktop.dep" } } ;

Target cpp189 = { "InternalHost.cpp" , "CCore/src/./video/InternalHost.cpp" } ;
Target ocpp189 = { "InternalHost.o" , OBJ_PATH+"/InternalHost.o" } ;
Rule rcpp189 = { {&cpp189} , {&ocpp189} , {&intdep189,&execpp189} } ;
Exe execpp189 = { "CC InternalHost.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./video/InternalHost.cpp"
 ,"-o"
 ,OBJ_PATH+"/InternalHost.o"
} } ;

IntCmd intdep189 = { 'RM DEP' , &rmdep189 } ;

Rm rmdep189 = { { OBJ_PATH+"/InternalHost.dep" } } ;

Target cpp190 = { "InternalUtils.cpp" , "CCore/src/./video/InternalUtils.cpp" } ;
Target ocpp190 = { "InternalUtils.o" , OBJ_PATH+"/InternalUtils.o" } ;
Rule rcpp190 = { {&cpp190} , {&ocpp190} , {&intdep190,&execpp190} } ;
Exe execpp190 = { "CC InternalUtils.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./video/InternalUtils.cpp"
 ,"-o"
 ,OBJ_PATH+"/InternalUtils.o"
} } ;

IntCmd intdep190 = { 'RM DEP' , &rmdep190 } ;

Rm rmdep190 = { { OBJ_PATH+"/InternalUtils.dep" } } ;

Target cpp191 = { "IntervalTree.cpp" , "../../Applied/CCore/src/IntervalTree.cpp" } ;
Target ocpp191 = { "IntervalTree.o" , OBJ_PATH+"/IntervalTree.o" } ;
Rule rcpp191 = { {&cpp191} , {&ocpp191} , {&intdep191,&execpp191} } ;
Exe execpp191 = { "CC IntervalTree.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/IntervalTree.cpp"
 ,"-o"
 ,OBJ_PATH+"/IntervalTree.o"
} } ;

IntCmd intdep191 = { 'RM DEP' , &rmdep191 } ;

Rm rmdep191 = { { OBJ_PATH+"/IntervalTree.dep" } } ;

Target cpp192 = { "Job.cpp" , "../../Fundamental/CCore/src/Job.cpp" } ;
Target ocpp192 = { "Job.o" , OBJ_PATH+"/Job.o" } ;
Rule rcpp192 = { {&cpp192} , {&ocpp192} , {&intdep192,&execpp192} } ;
Exe execpp192 = { "CC Job.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/Job.cpp"
 ,"-o"
 ,OBJ_PATH+"/Job.o"
} } ;

IntCmd intdep192 = { 'RM DEP' , &rmdep192 } ;

Rm rmdep192 = { { OBJ_PATH+"/Job.dep" } } ;

Target cpp193 = { "Keyboard.cpp" , "../../Desktop/Core/CCore/src/./video/Keyboard.cpp" } ;
Target ocpp193 = { "Keyboard.o" , OBJ_PATH+"/Keyboard.o" } ;
Rule rcpp193 = { {&cpp193} , {&ocpp193} , {&intdep193,&execpp193} } ;
Exe execpp193 = { "CC Keyboard.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Core/CCore/src/./video/Keyboard.cpp"
 ,"-o"
 ,OBJ_PATH+"/Keyboard.o"
} } ;

IntCmd intdep193 = { 'RM DEP' , &rmdep193 } ;

Rm rmdep193 = { { OBJ_PATH+"/Keyboard.dep" } } ;

Target cpp194 = { "LangDataMap.cpp" , "../../Applied/CCore/src/./lang/LangDataMap.cpp" } ;
Target ocpp194 = { "LangDataMap.o" , OBJ_PATH+"/LangDataMap.o" } ;
Rule rcpp194 = { {&cpp194} , {&ocpp194} , {&intdep194,&execpp194} } ;
Exe execpp194 = { "CC LangDataMap.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./lang/LangDataMap.cpp"
 ,"-o"
 ,OBJ_PATH+"/LangDataMap.o"
} } ;

IntCmd intdep194 = { 'RM DEP' , &rmdep194 } ;

Rm rmdep194 = { { OBJ_PATH+"/LangDataMap.dep" } } ;

Target cpp195 = { "LaunchPath.cpp" , "../../HCore/CCore/src/LaunchPath.cpp" } ;
Target ocpp195 = { "LaunchPath.o" , OBJ_PATH+"/LaunchPath.o" } ;
Rule rcpp195 = { {&cpp195} , {&ocpp195} , {&intdep195,&execpp195} } ;
Exe execpp195 = { "CC LaunchPath.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/LaunchPath.cpp"
 ,"-o"
 ,OBJ_PATH+"/LaunchPath.o"
} } ;

IntCmd intdep195 = { 'RM DEP' , &rmdep195 } ;

Rm rmdep195 = { { OBJ_PATH+"/LaunchPath.dep" } } ;

Target cpp196 = { "Layout.cpp" , "../../Desktop/Lib/CCore/src/./video/Layout.cpp" } ;
Target ocpp196 = { "Layout.o" , OBJ_PATH+"/Layout.o" } ;
Rule rcpp196 = { {&cpp196} , {&ocpp196} , {&intdep196,&execpp196} } ;
Exe execpp196 = { "CC Layout.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/Layout.cpp"
 ,"-o"
 ,OBJ_PATH+"/Layout.o"
} } ;

IntCmd intdep196 = { 'RM DEP' , &rmdep196 } ;

Rm rmdep196 = { { OBJ_PATH+"/Layout.dep" } } ;

Target cpp197 = { "LayoutCombo.cpp" , "../../Desktop/Lib/CCore/src/./video/LayoutCombo.cpp" } ;
Target ocpp197 = { "LayoutCombo.o" , OBJ_PATH+"/LayoutCombo.o" } ;
Rule rcpp197 = { {&cpp197} , {&ocpp197} , {&intdep197,&execpp197} } ;
Exe execpp197 = { "CC LayoutCombo.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/LayoutCombo.cpp"
 ,"-o"
 ,OBJ_PATH+"/LayoutCombo.o"
} } ;

IntCmd intdep197 = { 'RM DEP' , &rmdep197 } ;

Rm rmdep197 = { { OBJ_PATH+"/LayoutCombo.dep" } } ;

Target cpp198 = { "Len.cpp" , "../../Simple/CCore/src/./gadget/Len.cpp" } ;
Target ocpp198 = { "Len.o" , OBJ_PATH+"/Len.o" } ;
Rule rcpp198 = { {&cpp198} , {&ocpp198} , {&intdep198,&execpp198} } ;
Exe execpp198 = { "CC Len.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/Len.cpp"
 ,"-o"
 ,OBJ_PATH+"/Len.o"
} } ;

IntCmd intdep198 = { 'RM DEP' , &rmdep198 } ;

Rm rmdep198 = { { OBJ_PATH+"/Len.dep" } } ;

Target cpp199 = { "LineInput.cpp" , "../../Applied/CCore/src/LineInput.cpp" } ;
Target ocpp199 = { "LineInput.o" , OBJ_PATH+"/LineInput.o" } ;
Rule rcpp199 = { {&cpp199} , {&ocpp199} , {&intdep199,&execpp199} } ;
Exe execpp199 = { "CC LineInput.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/LineInput.cpp"
 ,"-o"
 ,OBJ_PATH+"/LineInput.o"
} } ;

IntCmd intdep199 = { 'RM DEP' , &rmdep199 } ;

Rm rmdep199 = { { OBJ_PATH+"/LineInput.dep" } } ;

Target cpp200 = { "List.cpp" , "../../Fundamental/CCore/src/List.cpp" } ;
Target ocpp200 = { "List.o" , OBJ_PATH+"/List.o" } ;
Rule rcpp200 = { {&cpp200} , {&ocpp200} , {&intdep200,&execpp200} } ;
Exe execpp200 = { "CC List.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/List.cpp"
 ,"-o"
 ,OBJ_PATH+"/List.o"
} } ;

IntCmd intdep200 = { 'RM DEP' , &rmdep200 } ;

Rm rmdep200 = { { OBJ_PATH+"/List.dep" } } ;

Target cpp201 = { "ListCursor.cpp" , "../../Fundamental/CCore/src/ListCursor.cpp" } ;
Target ocpp201 = { "ListCursor.o" , OBJ_PATH+"/ListCursor.o" } ;
Rule rcpp201 = { {&cpp201} , {&ocpp201} , {&intdep201,&execpp201} } ;
Exe execpp201 = { "CC ListCursor.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/ListCursor.cpp"
 ,"-o"
 ,OBJ_PATH+"/ListCursor.o"
} } ;

IntCmd intdep201 = { 'RM DEP' , &rmdep201 } ;

Rm rmdep201 = { { OBJ_PATH+"/ListCursor.dep" } } ;

Target cpp202 = { "LockObject.cpp" , "../../Simple/CCore/src/./gadget/LockObject.cpp" } ;
Target ocpp202 = { "LockObject.o" , OBJ_PATH+"/LockObject.o" } ;
Rule rcpp202 = { {&cpp202} , {&ocpp202} , {&intdep202,&execpp202} } ;
Exe execpp202 = { "CC LockObject.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/LockObject.cpp"
 ,"-o"
 ,OBJ_PATH+"/LockObject.o"
} } ;

IntCmd intdep202 = { 'RM DEP' , &rmdep202 } ;

Rm rmdep202 = { { OBJ_PATH+"/LockObject.dep" } } ;

Target cpp203 = { "LockUse.cpp" , "../../Simple/CCore/src/./gadget/LockUse.cpp" } ;
Target ocpp203 = { "LockUse.o" , OBJ_PATH+"/LockUse.o" } ;
Rule rcpp203 = { {&cpp203} , {&ocpp203} , {&intdep203,&execpp203} } ;
Exe execpp203 = { "CC LockUse.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/LockUse.cpp"
 ,"-o"
 ,OBJ_PATH+"/LockUse.o"
} } ;

IntCmd intdep203 = { 'RM DEP' , &rmdep203 } ;

Rm rmdep203 = { { OBJ_PATH+"/LockUse.dep" } } ;

Target cpp204 = { "Locked.cpp" , "../../Simple/CCore/src/./gadget/Locked.cpp" } ;
Target ocpp204 = { "Locked.o" , OBJ_PATH+"/Locked.o" } ;
Rule rcpp204 = { {&cpp204} , {&ocpp204} , {&intdep204,&execpp204} } ;
Exe execpp204 = { "CC Locked.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/Locked.cpp"
 ,"-o"
 ,OBJ_PATH+"/Locked.o"
} } ;

IntCmd intdep204 = { 'RM DEP' , &rmdep204 } ;

Rm rmdep204 = { { OBJ_PATH+"/Locked.dep" } } ;

Target cpp205 = { "Log.cpp" , "../../Applied/CCore/src/Log.cpp" } ;
Target ocpp205 = { "Log.o" , OBJ_PATH+"/Log.o" } ;
Rule rcpp205 = { {&cpp205} , {&ocpp205} , {&intdep205,&execpp205} } ;
Exe execpp205 = { "CC Log.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/Log.cpp"
 ,"-o"
 ,OBJ_PATH+"/Log.o"
} } ;

IntCmd intdep205 = { 'RM DEP' , &rmdep205 } ;

Rm rmdep205 = { { OBJ_PATH+"/Log.dep" } } ;

Target cpp206 = { "MCoordEdit.cpp" , "../../Desktop/Lib/CCore/src/./video/pref/MCoordEdit.cpp" } ;
Target ocpp206 = { "MCoordEdit.o" , OBJ_PATH+"/MCoordEdit.o" } ;
Rule rcpp206 = { {&cpp206} , {&ocpp206} , {&intdep206,&execpp206} } ;
Exe execpp206 = { "CC MCoordEdit.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/pref/MCoordEdit.cpp"
 ,"-o"
 ,OBJ_PATH+"/MCoordEdit.o"
} } ;

IntCmd intdep206 = { 'RM DEP' , &rmdep206 } ;

Rm rmdep206 = { { OBJ_PATH+"/MCoordEdit.dep" } } ;

Target cpp207 = { "MD5.cpp" , "../../Applied/CCore/src/./crypton/MD5.cpp" } ;
Target ocpp207 = { "MD5.o" , OBJ_PATH+"/MD5.o" } ;
Rule rcpp207 = { {&cpp207} , {&ocpp207} , {&intdep207,&execpp207} } ;
Exe execpp207 = { "CC MD5.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./crypton/MD5.cpp"
 ,"-o"
 ,OBJ_PATH+"/MD5.o"
} } ;

IntCmd intdep207 = { 'RM DEP' , &rmdep207 } ;

Rm rmdep207 = { { OBJ_PATH+"/MD5.dep" } } ;

Target cpp208 = { "MPoint.cpp" , "../../Desktop/Draw/CCore/src/./video/MPoint.cpp" } ;
Target ocpp208 = { "MPoint.o" , OBJ_PATH+"/MPoint.o" } ;
Rule rcpp208 = { {&cpp208} , {&ocpp208} , {&intdep208,&execpp208} } ;
Exe execpp208 = { "CC MPoint.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Draw/CCore/src/./video/MPoint.cpp"
 ,"-o"
 ,OBJ_PATH+"/MPoint.o"
} } ;

IntCmd intdep208 = { 'RM DEP' , &rmdep208 } ;

Rm rmdep208 = { { OBJ_PATH+"/MPoint.dep" } } ;

Target cpp209 = { "MSec.cpp" , "../../Simple/CCore/src/./gadget/MSec.cpp" } ;
Target ocpp209 = { "MSec.o" , OBJ_PATH+"/MSec.o" } ;
Rule rcpp209 = { {&cpp209} , {&ocpp209} , {&intdep209,&execpp209} } ;
Exe execpp209 = { "CC MSec.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/MSec.cpp"
 ,"-o"
 ,OBJ_PATH+"/MSec.o"
} } ;

IntCmd intdep209 = { 'RM DEP' , &rmdep209 } ;

Rm rmdep209 = { { OBJ_PATH+"/MSec.dep" } } ;

Target cpp210 = { "MakeFileName.cpp" , "../../Fundamental/CCore/src/MakeFileName.cpp" } ;
Target ocpp210 = { "MakeFileName.o" , OBJ_PATH+"/MakeFileName.o" } ;
Rule rcpp210 = { {&cpp210} , {&ocpp210} , {&intdep210,&execpp210} } ;
Exe execpp210 = { "CC MakeFileName.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/MakeFileName.cpp"
 ,"-o"
 ,OBJ_PATH+"/MakeFileName.o"
} } ;

IntCmd intdep210 = { 'RM DEP' , &rmdep210 } ;

Rm rmdep210 = { { OBJ_PATH+"/MakeFileName.dep" } } ;

Target cpp211 = { "MakeString.cpp" , "../../Simple/CCore/src/MakeString.cpp" } ;
Target ocpp211 = { "MakeString.o" , OBJ_PATH+"/MakeString.o" } ;
Rule rcpp211 = { {&cpp211} , {&ocpp211} , {&intdep211,&execpp211} } ;
Exe execpp211 = { "CC MakeString.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/MakeString.cpp"
 ,"-o"
 ,OBJ_PATH+"/MakeString.o"
} } ;

IntCmd intdep211 = { 'RM DEP' , &rmdep211 } ;

Rm rmdep211 = { { OBJ_PATH+"/MakeString.dep" } } ;

Target cpp212 = { "MemAllocGuard.cpp" , "../../Simple/CCore/src/MemAllocGuard.cpp" } ;
Target ocpp212 = { "MemAllocGuard.o" , OBJ_PATH+"/MemAllocGuard.o" } ;
Rule rcpp212 = { {&cpp212} , {&ocpp212} , {&intdep212,&execpp212} } ;
Exe execpp212 = { "CC MemAllocGuard.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/MemAllocGuard.cpp"
 ,"-o"
 ,OBJ_PATH+"/MemAllocGuard.o"
} } ;

IntCmd intdep212 = { 'RM DEP' , &rmdep212 } ;

Rm rmdep212 = { { OBJ_PATH+"/MemAllocGuard.dep" } } ;

Target cpp213 = { "MemBase.cpp" , "../../HCore/CCore/src/MemBase.cpp" } ;
Target ocpp213 = { "MemBase.o" , OBJ_PATH+"/MemBase.o" } ;
Rule rcpp213 = { {&cpp213} , {&ocpp213} , {&intdep213,&execpp213} } ;
Exe execpp213 = { "CC MemBase.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/MemBase.cpp"
 ,"-o"
 ,OBJ_PATH+"/MemBase.o"
} } ;

IntCmd intdep213 = { 'RM DEP' , &rmdep213 } ;

Rm rmdep213 = { { OBJ_PATH+"/MemBase.dep" } } ;

Target cpp214 = { "MemBase_general.cpp" , "../../Fundamental/CCore/src/MemBase_general.cpp" } ;
Target ocpp214 = { "MemBase_general.o" , OBJ_PATH+"/MemBase_general.o" } ;
Rule rcpp214 = { {&cpp214} , {&ocpp214} , {&intdep214,&execpp214} } ;
Exe execpp214 = { "CC MemBase_general.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/MemBase_general.cpp"
 ,"-o"
 ,OBJ_PATH+"/MemBase_general.o"
} } ;

IntCmd intdep214 = { 'RM DEP' , &rmdep214 } ;

Rm rmdep214 = { { OBJ_PATH+"/MemBase_general.dep" } } ;

Target cpp215 = { "MemPageHeap.cpp" , "../../HCore/CCore/src/MemPageHeap.cpp" } ;
Target ocpp215 = { "MemPageHeap.o" , OBJ_PATH+"/MemPageHeap.o" } ;
Rule rcpp215 = { {&cpp215} , {&ocpp215} , {&intdep215,&execpp215} } ;
Exe execpp215 = { "CC MemPageHeap.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/MemPageHeap.cpp"
 ,"-o"
 ,OBJ_PATH+"/MemPageHeap.o"
} } ;

IntCmd intdep215 = { 'RM DEP' , &rmdep215 } ;

Rm rmdep215 = { { OBJ_PATH+"/MemPageHeap.dep" } } ;

Target cpp216 = { "MemSpaceHeap.cpp" , "../../Fundamental/CCore/src/MemSpaceHeap.cpp" } ;
Target ocpp216 = { "MemSpaceHeap.o" , OBJ_PATH+"/MemSpaceHeap.o" } ;
Rule rcpp216 = { {&cpp216} , {&ocpp216} , {&intdep216,&execpp216} } ;
Exe execpp216 = { "CC MemSpaceHeap.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/MemSpaceHeap.cpp"
 ,"-o"
 ,OBJ_PATH+"/MemSpaceHeap.o"
} } ;

IntCmd intdep216 = { 'RM DEP' , &rmdep216 } ;

Rm rmdep216 = { { OBJ_PATH+"/MemSpaceHeap.dep" } } ;

Target cpp217 = { "MemberFold.cpp" , "../../Simple/CCore/src/MemberFold.cpp" } ;
Target ocpp217 = { "MemberFold.o" , OBJ_PATH+"/MemberFold.o" } ;
Rule rcpp217 = { {&cpp217} , {&ocpp217} , {&intdep217,&execpp217} } ;
Exe execpp217 = { "CC MemberFold.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/MemberFold.cpp"
 ,"-o"
 ,OBJ_PATH+"/MemberFold.o"
} } ;

IntCmd intdep217 = { 'RM DEP' , &rmdep217 } ;

Rm rmdep217 = { { OBJ_PATH+"/MemberFold.dep" } } ;

Target cpp218 = { "Menu.cpp" , "../../Desktop/Lib/CCore/src/./video/Menu.cpp" } ;
Target ocpp218 = { "Menu.o" , OBJ_PATH+"/Menu.o" } ;
Rule rcpp218 = { {&cpp218} , {&ocpp218} , {&intdep218,&execpp218} } ;
Exe execpp218 = { "CC Menu.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/Menu.cpp"
 ,"-o"
 ,OBJ_PATH+"/Menu.o"
} } ;

IntCmd intdep218 = { 'RM DEP' , &rmdep218 } ;

Rm rmdep218 = { { OBJ_PATH+"/Menu.dep" } } ;

Target cpp219 = { "MergeSort.cpp" , "../../Fundamental/CCore/src/./sort/MergeSort.cpp" } ;
Target ocpp219 = { "MergeSort.o" , OBJ_PATH+"/MergeSort.o" } ;
Rule rcpp219 = { {&cpp219} , {&ocpp219} , {&intdep219,&execpp219} } ;
Exe execpp219 = { "CC MergeSort.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./sort/MergeSort.cpp"
 ,"-o"
 ,OBJ_PATH+"/MergeSort.o"
} } ;

IntCmd intdep219 = { 'RM DEP' , &rmdep219 } ;

Rm rmdep219 = { { OBJ_PATH+"/MergeSort.dep" } } ;

Target cpp220 = { "MersenneTwister.cpp" , "../../Fundamental/CCore/src/MersenneTwister.cpp" } ;
Target ocpp220 = { "MersenneTwister.o" , OBJ_PATH+"/MersenneTwister.o" } ;
Rule rcpp220 = { {&cpp220} , {&ocpp220} , {&intdep220,&execpp220} } ;
Exe execpp220 = { "CC MersenneTwister.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/MersenneTwister.cpp"
 ,"-o"
 ,OBJ_PATH+"/MersenneTwister.o"
} } ;

IntCmd intdep220 = { 'RM DEP' , &rmdep220 } ;

Rm rmdep220 = { { OBJ_PATH+"/MersenneTwister.dep" } } ;

Target cpp221 = { "MessageFrame.cpp" , "../../Desktop/Lib/CCore/src/./video/MessageFrame.cpp" } ;
Target ocpp221 = { "MessageFrame.o" , OBJ_PATH+"/MessageFrame.o" } ;
Rule rcpp221 = { {&cpp221} , {&ocpp221} , {&intdep221,&execpp221} } ;
Exe execpp221 = { "CC MessageFrame.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/MessageFrame.cpp"
 ,"-o"
 ,OBJ_PATH+"/MessageFrame.o"
} } ;

IntCmd intdep221 = { 'RM DEP' , &rmdep221 } ;

Rm rmdep221 = { { OBJ_PATH+"/MessageFrame.dep" } } ;

Target cpp222 = { "Meta.cpp" , "../../Simple/CCore/src/./gadget/Meta.cpp" } ;
Target ocpp222 = { "Meta.o" , OBJ_PATH+"/Meta.o" } ;
Rule rcpp222 = { {&cpp222} , {&ocpp222} , {&intdep222,&execpp222} } ;
Exe execpp222 = { "CC Meta.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/Meta.cpp"
 ,"-o"
 ,OBJ_PATH+"/Meta.o"
} } ;

IntCmd intdep222 = { 'RM DEP' , &rmdep222 } ;

Rm rmdep222 = { { OBJ_PATH+"/Meta.dep" } } ;

Target cpp223 = { "MetaList.cpp" , "../../Simple/CCore/src/./gadget/MetaList.cpp" } ;
Target ocpp223 = { "MetaList.o" , OBJ_PATH+"/MetaList.o" } ;
Rule rcpp223 = { {&cpp223} , {&ocpp223} , {&intdep223,&execpp223} } ;
Exe execpp223 = { "CC MetaList.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/MetaList.cpp"
 ,"-o"
 ,OBJ_PATH+"/MetaList.o"
} } ;

IntCmd intdep223 = { 'RM DEP' , &rmdep223 } ;

Rm rmdep223 = { { OBJ_PATH+"/MetaList.dep" } } ;

Target cpp224 = { "MinSizeType.cpp" , "../../Desktop/Lib/CCore/src/./video/MinSizeType.cpp" } ;
Target ocpp224 = { "MinSizeType.o" , OBJ_PATH+"/MinSizeType.o" } ;
Rule rcpp224 = { {&cpp224} , {&ocpp224} , {&intdep224,&execpp224} } ;
Exe execpp224 = { "CC MinSizeType.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/MinSizeType.cpp"
 ,"-o"
 ,OBJ_PATH+"/MinSizeType.o"
} } ;

IntCmd intdep224 = { 'RM DEP' , &rmdep224 } ;

Rm rmdep224 = { { OBJ_PATH+"/MinSizeType.dep" } } ;

Target cpp225 = { "MixColorWindow.cpp" , "../../Desktop/Lib/CCore/src/./video/pref/MixColorWindow.cpp" } ;
Target ocpp225 = { "MixColorWindow.o" , OBJ_PATH+"/MixColorWindow.o" } ;
Rule rcpp225 = { {&cpp225} , {&ocpp225} , {&intdep225,&execpp225} } ;
Exe execpp225 = { "CC MixColorWindow.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/pref/MixColorWindow.cpp"
 ,"-o"
 ,OBJ_PATH+"/MixColorWindow.o"
} } ;

IntCmd intdep225 = { 'RM DEP' , &rmdep225 } ;

Rm rmdep225 = { { OBJ_PATH+"/MixColorWindow.dep" } } ;

Target cpp226 = { "ModEngine.cpp" , "../../Applied/CCore/src/./math/ModEngine.cpp" } ;
Target ocpp226 = { "ModEngine.o" , OBJ_PATH+"/ModEngine.o" } ;
Rule rcpp226 = { {&cpp226} , {&ocpp226} , {&intdep226,&execpp226} } ;
Exe execpp226 = { "CC ModEngine.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./math/ModEngine.cpp"
 ,"-o"
 ,OBJ_PATH+"/ModEngine.o"
} } ;

IntCmd intdep226 = { 'RM DEP' , &rmdep226 } ;

Rm rmdep226 = { { OBJ_PATH+"/ModEngine.dep" } } ;

Target cpp227 = { "Mouse.cpp" , "../../Desktop/Core/CCore/src/./video/Mouse.cpp" } ;
Target ocpp227 = { "Mouse.o" , OBJ_PATH+"/Mouse.o" } ;
Rule rcpp227 = { {&cpp227} , {&ocpp227} , {&intdep227,&execpp227} } ;
Exe execpp227 = { "CC Mouse.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Core/CCore/src/./video/Mouse.cpp"
 ,"-o"
 ,OBJ_PATH+"/Mouse.o"
} } ;

IntCmd intdep227 = { 'RM DEP' , &rmdep227 } ;

Rm rmdep227 = { { OBJ_PATH+"/Mouse.dep" } } ;

Target cpp228 = { "Move.cpp" , "../../Simple/CCore/src/Move.cpp" } ;
Target ocpp228 = { "Move.o" , OBJ_PATH+"/Move.o" } ;
Rule rcpp228 = { {&cpp228} , {&ocpp228} , {&intdep228,&execpp228} } ;
Exe execpp228 = { "CC Move.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/Move.cpp"
 ,"-o"
 ,OBJ_PATH+"/Move.o"
} } ;

IntCmd intdep228 = { 'RM DEP' , &rmdep228 } ;

Rm rmdep228 = { { OBJ_PATH+"/Move.dep" } } ;

Target cpp229 = { "MultiEvent.cpp" , "../../HCore/CCore/src/./task/MultiEvent.cpp" } ;
Target ocpp229 = { "MultiEvent.o" , OBJ_PATH+"/MultiEvent.o" } ;
Rule rcpp229 = { {&cpp229} , {&ocpp229} , {&intdep229,&execpp229} } ;
Exe execpp229 = { "CC MultiEvent.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/./task/MultiEvent.cpp"
 ,"-o"
 ,OBJ_PATH+"/MultiEvent.o"
} } ;

IntCmd intdep229 = { 'RM DEP' , &rmdep229 } ;

Rm rmdep229 = { { OBJ_PATH+"/MultiEvent.dep" } } ;

Target cpp230 = { "MultiSem.cpp" , "../../HCore/CCore/src/./task/MultiSem.cpp" } ;
Target ocpp230 = { "MultiSem.o" , OBJ_PATH+"/MultiSem.o" } ;
Rule rcpp230 = { {&cpp230} , {&ocpp230} , {&intdep230,&execpp230} } ;
Exe execpp230 = { "CC MultiSem.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/./task/MultiSem.cpp"
 ,"-o"
 ,OBJ_PATH+"/MultiSem.o"
} } ;

IntCmd intdep230 = { 'RM DEP' , &rmdep230 } ;

Rm rmdep230 = { { OBJ_PATH+"/MultiSem.dep" } } ;

Target cpp231 = { "MultiSignal.cpp" , "../../Fundamental/CCore/src/MultiSignal.cpp" } ;
Target ocpp231 = { "MultiSignal.o" , OBJ_PATH+"/MultiSignal.o" } ;
Rule rcpp231 = { {&cpp231} , {&ocpp231} , {&intdep231,&execpp231} } ;
Exe execpp231 = { "CC MultiSignal.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/MultiSignal.cpp"
 ,"-o"
 ,OBJ_PATH+"/MultiSignal.o"
} } ;

IntCmd intdep231 = { 'RM DEP' , &rmdep231 } ;

Rm rmdep231 = { { OBJ_PATH+"/MultiSignal.dep" } } ;

Target cpp232 = { "Mutex.cpp" , "../../HCore/CCore/src/./task/Mutex.cpp" } ;
Target ocpp232 = { "Mutex.o" , OBJ_PATH+"/Mutex.o" } ;
Rule rcpp232 = { {&cpp232} , {&ocpp232} , {&intdep232,&execpp232} } ;
Exe execpp232 = { "CC Mutex.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/./task/Mutex.cpp"
 ,"-o"
 ,OBJ_PATH+"/Mutex.o"
} } ;

IntCmd intdep232 = { 'RM DEP' , &rmdep232 } ;

Rm rmdep232 = { { OBJ_PATH+"/Mutex.dep" } } ;

Target cpp233 = { "MutexSpinCount.cpp" , "../../HCore/CCore/src/./task/MutexSpinCount.cpp" } ;
Target ocpp233 = { "MutexSpinCount.o" , OBJ_PATH+"/MutexSpinCount.o" } ;
Rule rcpp233 = { {&cpp233} , {&ocpp233} , {&intdep233,&execpp233} } ;
Exe execpp233 = { "CC MutexSpinCount.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/./task/MutexSpinCount.cpp"
 ,"-o"
 ,OBJ_PATH+"/MutexSpinCount.o"
} } ;

IntCmd intdep233 = { 'RM DEP' , &rmdep233 } ;

Rm rmdep233 = { { OBJ_PATH+"/MutexSpinCount.dep" } } ;

Target cpp234 = { "NanoIPDevice.cpp" , "../../Applied/CCore/src/./net/NanoIPDevice.cpp" } ;
Target ocpp234 = { "NanoIPDevice.o" , OBJ_PATH+"/NanoIPDevice.o" } ;
Rule rcpp234 = { {&cpp234} , {&ocpp234} , {&intdep234,&execpp234} } ;
Exe execpp234 = { "CC NanoIPDevice.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./net/NanoIPDevice.cpp"
 ,"-o"
 ,OBJ_PATH+"/NanoIPDevice.o"
} } ;

IntCmd intdep234 = { 'RM DEP' , &rmdep234 } ;

Rm rmdep234 = { { OBJ_PATH+"/NanoIPDevice.dep" } } ;

Target cpp235 = { "NanoPacket.cpp" , "../../Applied/CCore/src/NanoPacket.cpp" } ;
Target ocpp235 = { "NanoPacket.o" , OBJ_PATH+"/NanoPacket.o" } ;
Rule rcpp235 = { {&cpp235} , {&ocpp235} , {&intdep235,&execpp235} } ;
Exe execpp235 = { "CC NanoPacket.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/NanoPacket.cpp"
 ,"-o"
 ,OBJ_PATH+"/NanoPacket.o"
} } ;

IntCmd intdep235 = { 'RM DEP' , &rmdep235 } ;

Rm rmdep235 = { { OBJ_PATH+"/NanoPacket.dep" } } ;

Target cpp236 = { "NegBool.cpp" , "../../Simple/CCore/src/./gadget/NegBool.cpp" } ;
Target ocpp236 = { "NegBool.o" , OBJ_PATH+"/NegBool.o" } ;
Rule rcpp236 = { {&cpp236} , {&ocpp236} , {&intdep236,&execpp236} } ;
Exe execpp236 = { "CC NegBool.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/NegBool.cpp"
 ,"-o"
 ,OBJ_PATH+"/NegBool.o"
} } ;

IntCmd intdep236 = { 'RM DEP' , &rmdep236 } ;

Rm rmdep236 = { { OBJ_PATH+"/NegBool.dep" } } ;

Target cpp237 = { "NetBase.cpp" , "../../Applied/CCore/src/./net/NetBase.cpp" } ;
Target ocpp237 = { "NetBase.o" , OBJ_PATH+"/NetBase.o" } ;
Rule rcpp237 = { {&cpp237} , {&ocpp237} , {&intdep237,&execpp237} } ;
Exe execpp237 = { "CC NetBase.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./net/NetBase.cpp"
 ,"-o"
 ,OBJ_PATH+"/NetBase.o"
} } ;

IntCmd intdep237 = { 'RM DEP' , &rmdep237 } ;

Rm rmdep237 = { { OBJ_PATH+"/NetBase.dep" } } ;

Target cpp238 = { "NetFork.cpp" , "../../Applied/CCore/src/./net/NetFork.cpp" } ;
Target ocpp238 = { "NetFork.o" , OBJ_PATH+"/NetFork.o" } ;
Rule rcpp238 = { {&cpp238} , {&ocpp238} , {&intdep238,&execpp238} } ;
Exe execpp238 = { "CC NetFork.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./net/NetFork.cpp"
 ,"-o"
 ,OBJ_PATH+"/NetFork.o"
} } ;

IntCmd intdep238 = { 'RM DEP' , &rmdep238 } ;

Rm rmdep238 = { { OBJ_PATH+"/NetFork.dep" } } ;

Target cpp239 = { "NewDelete.cpp" , "../../Simple/CCore/src/NewDelete.cpp" } ;
Target ocpp239 = { "NewDelete.o" , OBJ_PATH+"/NewDelete.o" } ;
Rule rcpp239 = { {&cpp239} , {&ocpp239} , {&intdep239,&execpp239} } ;
Exe execpp239 = { "CC NewDelete.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/NewDelete.cpp"
 ,"-o"
 ,OBJ_PATH+"/NewDelete.o"
} } ;

IntCmd intdep239 = { 'RM DEP' , &rmdep239 } ;

Rm rmdep239 = { { OBJ_PATH+"/NewDelete.dep" } } ;

Target cpp240 = { "NoCopy.cpp" , "../../Simple/CCore/src/./gadget/NoCopy.cpp" } ;
Target ocpp240 = { "NoCopy.o" , OBJ_PATH+"/NoCopy.o" } ;
Rule rcpp240 = { {&cpp240} , {&ocpp240} , {&intdep240,&execpp240} } ;
Exe execpp240 = { "CC NoCopy.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/NoCopy.cpp"
 ,"-o"
 ,OBJ_PATH+"/NoCopy.o"
} } ;

IntCmd intdep240 = { 'RM DEP' , &rmdep240 } ;

Rm rmdep240 = { { OBJ_PATH+"/NoCopy.dep" } } ;

Target cpp241 = { "NoMutex.cpp" , "../../Applied/CCore/src/./task/NoMutex.cpp" } ;
Target ocpp241 = { "NoMutex.o" , OBJ_PATH+"/NoMutex.o" } ;
Rule rcpp241 = { {&cpp241} , {&ocpp241} , {&intdep241,&execpp241} } ;
Exe execpp241 = { "CC NoMutex.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./task/NoMutex.cpp"
 ,"-o"
 ,OBJ_PATH+"/NoMutex.o"
} } ;

IntCmd intdep241 = { 'RM DEP' , &rmdep241 } ;

Rm rmdep241 = { { OBJ_PATH+"/NoMutex.dep" } } ;

Target cpp242 = { "NoPrimeTest.cpp" , "../../Applied/CCore/src/./math/NoPrimeTest.cpp" } ;
Target ocpp242 = { "NoPrimeTest.o" , OBJ_PATH+"/NoPrimeTest.o" } ;
Rule rcpp242 = { {&cpp242} , {&ocpp242} , {&intdep242,&execpp242} } ;
Exe execpp242 = { "CC NoPrimeTest.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./math/NoPrimeTest.cpp"
 ,"-o"
 ,OBJ_PATH+"/NoPrimeTest.o"
} } ;

IntCmd intdep242 = { 'RM DEP' , &rmdep242 } ;

Rm rmdep242 = { { OBJ_PATH+"/NoPrimeTest.dep" } } ;

Target cpp243 = { "NoThrowFlags.cpp" , "../../Simple/CCore/src/./gadget/NoThrowFlags.cpp" } ;
Target ocpp243 = { "NoThrowFlags.o" , OBJ_PATH+"/NoThrowFlags.o" } ;
Rule rcpp243 = { {&cpp243} , {&ocpp243} , {&intdep243,&execpp243} } ;
Exe execpp243 = { "CC NoThrowFlags.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/NoThrowFlags.cpp"
 ,"-o"
 ,OBJ_PATH+"/NoThrowFlags.o"
} } ;

IntCmd intdep243 = { 'RM DEP' , &rmdep243 } ;

Rm rmdep243 = { { OBJ_PATH+"/NoThrowFlags.dep" } } ;

Target cpp244 = { "NodeAllocator.cpp" , "../../Fundamental/CCore/src/NodeAllocator.cpp" } ;
Target ocpp244 = { "NodeAllocator.o" , OBJ_PATH+"/NodeAllocator.o" } ;
Rule rcpp244 = { {&cpp244} , {&ocpp244} , {&intdep244,&execpp244} } ;
Exe execpp244 = { "CC NodeAllocator.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/NodeAllocator.cpp"
 ,"-o"
 ,OBJ_PATH+"/NodeAllocator.o"
} } ;

IntCmd intdep244 = { 'RM DEP' , &rmdep244 } ;

Rm rmdep244 = { { OBJ_PATH+"/NodeAllocator.dep" } } ;

Target cpp245 = { "Nothing.cpp" , "../../Simple/CCore/src/./gadget/Nothing.cpp" } ;
Target ocpp245 = { "Nothing.o" , OBJ_PATH+"/Nothing.o" } ;
Rule rcpp245 = { {&cpp245} , {&ocpp245} , {&intdep245,&execpp245} } ;
Exe execpp245 = { "CC Nothing.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/Nothing.cpp"
 ,"-o"
 ,OBJ_PATH+"/Nothing.o"
} } ;

IntCmd intdep245 = { 'RM DEP' , &rmdep245 } ;

Rm rmdep245 = { { OBJ_PATH+"/Nothing.dep" } } ;

Target cpp246 = { "NullMovePtr.cpp" , "../../Simple/CCore/src/./gadget/NullMovePtr.cpp" } ;
Target ocpp246 = { "NullMovePtr.o" , OBJ_PATH+"/NullMovePtr.o" } ;
Rule rcpp246 = { {&cpp246} , {&ocpp246} , {&intdep246,&execpp246} } ;
Exe execpp246 = { "CC NullMovePtr.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/NullMovePtr.cpp"
 ,"-o"
 ,OBJ_PATH+"/NullMovePtr.o"
} } ;

IntCmd intdep246 = { 'RM DEP' , &rmdep246 } ;

Rm rmdep246 = { { OBJ_PATH+"/NullMovePtr.dep" } } ;

Target cpp247 = { "ObjHost.cpp" , "../../Fundamental/CCore/src/ObjHost.cpp" } ;
Target ocpp247 = { "ObjHost.o" , OBJ_PATH+"/ObjHost.o" } ;
Rule rcpp247 = { {&cpp247} , {&ocpp247} , {&intdep247,&execpp247} } ;
Exe execpp247 = { "CC ObjHost.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/ObjHost.cpp"
 ,"-o"
 ,OBJ_PATH+"/ObjHost.o"
} } ;

IntCmd intdep247 = { 'RM DEP' , &rmdep247 } ;

Rm rmdep247 = { { OBJ_PATH+"/ObjHost.dep" } } ;

Target cpp248 = { "ObjectDomain.cpp" , "../../Fundamental/CCore/src/ObjectDomain.cpp" } ;
Target ocpp248 = { "ObjectDomain.o" , OBJ_PATH+"/ObjectDomain.o" } ;
Rule rcpp248 = { {&cpp248} , {&ocpp248} , {&intdep248,&execpp248} } ;
Exe execpp248 = { "CC ObjectDomain.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/ObjectDomain.cpp"
 ,"-o"
 ,OBJ_PATH+"/ObjectDomain.o"
} } ;

IntCmd intdep248 = { 'RM DEP' , &rmdep248 } ;

Rm rmdep248 = { { OBJ_PATH+"/ObjectDomain.dep" } } ;

Target cpp249 = { "OpAddHelper.cpp" , "../../Simple/CCore/src/./gadget/OpAddHelper.cpp" } ;
Target ocpp249 = { "OpAddHelper.o" , OBJ_PATH+"/OpAddHelper.o" } ;
Rule rcpp249 = { {&cpp249} , {&ocpp249} , {&intdep249,&execpp249} } ;
Exe execpp249 = { "CC OpAddHelper.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/OpAddHelper.cpp"
 ,"-o"
 ,OBJ_PATH+"/OpAddHelper.o"
} } ;

IntCmd intdep249 = { 'RM DEP' , &rmdep249 } ;

Rm rmdep249 = { { OBJ_PATH+"/OpAddHelper.dep" } } ;

Target cpp250 = { "OptMember.cpp" , "../../Simple/CCore/src/OptMember.cpp" } ;
Target ocpp250 = { "OptMember.o" , OBJ_PATH+"/OptMember.o" } ;
Rule rcpp250 = { {&cpp250} , {&ocpp250} , {&intdep250,&execpp250} } ;
Exe execpp250 = { "CC OptMember.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/OptMember.cpp"
 ,"-o"
 ,OBJ_PATH+"/OptMember.o"
} } ;

IntCmd intdep250 = { 'RM DEP' , &rmdep250 } ;

Rm rmdep250 = { { OBJ_PATH+"/OptMember.dep" } } ;

Target cpp251 = { "Optional.cpp" , "../../Fundamental/CCore/src/Optional.cpp" } ;
Target ocpp251 = { "Optional.o" , OBJ_PATH+"/Optional.o" } ;
Rule rcpp251 = { {&cpp251} , {&ocpp251} , {&intdep251,&execpp251} } ;
Exe execpp251 = { "CC Optional.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/Optional.cpp"
 ,"-o"
 ,OBJ_PATH+"/Optional.o"
} } ;

IntCmd intdep251 = { 'RM DEP' , &rmdep251 } ;

Rm rmdep251 = { { OBJ_PATH+"/Optional.dep" } } ;

Target cpp252 = { "OwnPtr.cpp" , "../../Simple/CCore/src/OwnPtr.cpp" } ;
Target ocpp252 = { "OwnPtr.o" , OBJ_PATH+"/OwnPtr.o" } ;
Rule rcpp252 = { {&cpp252} , {&ocpp252} , {&intdep252,&execpp252} } ;
Exe execpp252 = { "CC OwnPtr.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/OwnPtr.cpp"
 ,"-o"
 ,OBJ_PATH+"/OwnPtr.o"
} } ;

IntCmd intdep252 = { 'RM DEP' , &rmdep252 } ;

Rm rmdep252 = { { OBJ_PATH+"/OwnPtr.dep" } } ;

Target cpp253 = { "PKE.cpp" , "../../Applied/CCore/src/./net/PKE.cpp" } ;
Target ocpp253 = { "PKE.o" , OBJ_PATH+"/PKE.o" } ;
Rule rcpp253 = { {&cpp253} , {&ocpp253} , {&intdep253,&execpp253} } ;
Exe execpp253 = { "CC PKE.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./net/PKE.cpp"
 ,"-o"
 ,OBJ_PATH+"/PKE.o"
} } ;

IntCmd intdep253 = { 'RM DEP' , &rmdep253 } ;

Rm rmdep253 = { { OBJ_PATH+"/PKE.dep" } } ;

Target cpp254 = { "PSec.cpp" , "../../Applied/CCore/src/./net/PSec.cpp" } ;
Target ocpp254 = { "PSec.o" , OBJ_PATH+"/PSec.o" } ;
Rule rcpp254 = { {&cpp254} , {&ocpp254} , {&intdep254,&execpp254} } ;
Exe execpp254 = { "CC PSec.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./net/PSec.cpp"
 ,"-o"
 ,OBJ_PATH+"/PSec.o"
} } ;

IntCmd intdep254 = { 'RM DEP' , &rmdep254 } ;

Rm rmdep254 = { { OBJ_PATH+"/PSec.dep" } } ;

Target cpp255 = { "PSecCore.cpp" , "../../Applied/CCore/src/./net/PSecCore.cpp" } ;
Target ocpp255 = { "PSecCore.o" , OBJ_PATH+"/PSecCore.o" } ;
Rule rcpp255 = { {&cpp255} , {&ocpp255} , {&intdep255,&execpp255} } ;
Exe execpp255 = { "CC PSecCore.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./net/PSecCore.cpp"
 ,"-o"
 ,OBJ_PATH+"/PSecCore.o"
} } ;

IntCmd intdep255 = { 'RM DEP' , &rmdep255 } ;

Rm rmdep255 = { { OBJ_PATH+"/PSecCore.dep" } } ;

Target cpp256 = { "PSecKey.cpp" , "../../Applied/CCore/src/./net/PSecKey.cpp" } ;
Target ocpp256 = { "PSecKey.o" , OBJ_PATH+"/PSecKey.o" } ;
Rule rcpp256 = { {&cpp256} , {&ocpp256} , {&intdep256,&execpp256} } ;
Exe execpp256 = { "CC PSecKey.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./net/PSecKey.cpp"
 ,"-o"
 ,OBJ_PATH+"/PSecKey.o"
} } ;

IntCmd intdep256 = { 'RM DEP' , &rmdep256 } ;

Rm rmdep256 = { { OBJ_PATH+"/PSecKey.dep" } } ;

Target cpp257 = { "PTPBase.cpp" , "../../Applied/CCore/src/./net/PTPBase.cpp" } ;
Target ocpp257 = { "PTPBase.o" , OBJ_PATH+"/PTPBase.o" } ;
Rule rcpp257 = { {&cpp257} , {&ocpp257} , {&intdep257,&execpp257} } ;
Exe execpp257 = { "CC PTPBase.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./net/PTPBase.cpp"
 ,"-o"
 ,OBJ_PATH+"/PTPBase.o"
} } ;

IntCmd intdep257 = { 'RM DEP' , &rmdep257 } ;

Rm rmdep257 = { { OBJ_PATH+"/PTPBase.dep" } } ;

Target cpp258 = { "PTPBoot.cpp" , "../../Applied/CCore/src/./net/PTPBoot.cpp" } ;
Target ocpp258 = { "PTPBoot.o" , OBJ_PATH+"/PTPBoot.o" } ;
Rule rcpp258 = { {&cpp258} , {&ocpp258} , {&intdep258,&execpp258} } ;
Exe execpp258 = { "CC PTPBoot.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./net/PTPBoot.cpp"
 ,"-o"
 ,OBJ_PATH+"/PTPBoot.o"
} } ;

IntCmd intdep258 = { 'RM DEP' , &rmdep258 } ;

Rm rmdep258 = { { OBJ_PATH+"/PTPBoot.dep" } } ;

Target cpp259 = { "PTPBootBase.cpp" , "../../Applied/CCore/src/./net/PTPBootBase.cpp" } ;
Target ocpp259 = { "PTPBootBase.o" , OBJ_PATH+"/PTPBootBase.o" } ;
Rule rcpp259 = { {&cpp259} , {&ocpp259} , {&intdep259,&execpp259} } ;
Exe execpp259 = { "CC PTPBootBase.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./net/PTPBootBase.cpp"
 ,"-o"
 ,OBJ_PATH+"/PTPBootBase.o"
} } ;

IntCmd intdep259 = { 'RM DEP' , &rmdep259 } ;

Rm rmdep259 = { { OBJ_PATH+"/PTPBootBase.dep" } } ;

Target cpp260 = { "PTPClientDevice.cpp" , "../../Applied/CCore/src/./net/PTPClientDevice.cpp" } ;
Target ocpp260 = { "PTPClientDevice.o" , OBJ_PATH+"/PTPClientDevice.o" } ;
Rule rcpp260 = { {&cpp260} , {&ocpp260} , {&intdep260,&execpp260} } ;
Exe execpp260 = { "CC PTPClientDevice.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./net/PTPClientDevice.cpp"
 ,"-o"
 ,OBJ_PATH+"/PTPClientDevice.o"
} } ;

IntCmd intdep260 = { 'RM DEP' , &rmdep260 } ;

Rm rmdep260 = { { OBJ_PATH+"/PTPClientDevice.dep" } } ;

Target cpp261 = { "PTPConBase.cpp" , "../../Applied/CCore/src/./net/PTPConBase.cpp" } ;
Target ocpp261 = { "PTPConBase.o" , OBJ_PATH+"/PTPConBase.o" } ;
Rule rcpp261 = { {&cpp261} , {&ocpp261} , {&intdep261,&execpp261} } ;
Exe execpp261 = { "CC PTPConBase.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./net/PTPConBase.cpp"
 ,"-o"
 ,OBJ_PATH+"/PTPConBase.o"
} } ;

IntCmd intdep261 = { 'RM DEP' , &rmdep261 } ;

Rm rmdep261 = { { OBJ_PATH+"/PTPConBase.dep" } } ;

Target cpp262 = { "PTPConDevice.cpp" , "../../Applied/CCore/src/./net/PTPConDevice.cpp" } ;
Target ocpp262 = { "PTPConDevice.o" , OBJ_PATH+"/PTPConDevice.o" } ;
Rule rcpp262 = { {&cpp262} , {&ocpp262} , {&intdep262,&execpp262} } ;
Exe execpp262 = { "CC PTPConDevice.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./net/PTPConDevice.cpp"
 ,"-o"
 ,OBJ_PATH+"/PTPConDevice.o"
} } ;

IntCmd intdep262 = { 'RM DEP' , &rmdep262 } ;

Rm rmdep262 = { { OBJ_PATH+"/PTPConDevice.dep" } } ;

Target cpp263 = { "PTPEchoTest.cpp" , "../../Applied/CCore/src/./net/PTPEchoTest.cpp" } ;
Target ocpp263 = { "PTPEchoTest.o" , OBJ_PATH+"/PTPEchoTest.o" } ;
Rule rcpp263 = { {&cpp263} , {&ocpp263} , {&intdep263,&execpp263} } ;
Exe execpp263 = { "CC PTPEchoTest.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./net/PTPEchoTest.cpp"
 ,"-o"
 ,OBJ_PATH+"/PTPEchoTest.o"
} } ;

IntCmd intdep263 = { 'RM DEP' , &rmdep263 } ;

Rm rmdep263 = { { OBJ_PATH+"/PTPEchoTest.dep" } } ;

Target cpp264 = { "PTPExtra.cpp" , "../../Applied/CCore/src/./net/PTPExtra.cpp" } ;
Target ocpp264 = { "PTPExtra.o" , OBJ_PATH+"/PTPExtra.o" } ;
Rule rcpp264 = { {&cpp264} , {&ocpp264} , {&intdep264,&execpp264} } ;
Exe execpp264 = { "CC PTPExtra.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./net/PTPExtra.cpp"
 ,"-o"
 ,OBJ_PATH+"/PTPExtra.o"
} } ;

IntCmd intdep264 = { 'RM DEP' , &rmdep264 } ;

Rm rmdep264 = { { OBJ_PATH+"/PTPExtra.dep" } } ;

Target cpp265 = { "PTPServerDevice.cpp" , "../../Applied/CCore/src/./net/PTPServerDevice.cpp" } ;
Target ocpp265 = { "PTPServerDevice.o" , OBJ_PATH+"/PTPServerDevice.o" } ;
Rule rcpp265 = { {&cpp265} , {&ocpp265} , {&intdep265,&execpp265} } ;
Exe execpp265 = { "CC PTPServerDevice.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./net/PTPServerDevice.cpp"
 ,"-o"
 ,OBJ_PATH+"/PTPServerDevice.o"
} } ;

IntCmd intdep265 = { 'RM DEP' , &rmdep265 } ;

Rm rmdep265 = { { OBJ_PATH+"/PTPServerDevice.dep" } } ;

Target cpp266 = { "PTPSupport.cpp" , "../../Applied/CCore/src/./net/PTPSupport.cpp" } ;
Target ocpp266 = { "PTPSupport.o" , OBJ_PATH+"/PTPSupport.o" } ;
Rule rcpp266 = { {&cpp266} , {&ocpp266} , {&intdep266,&execpp266} } ;
Exe execpp266 = { "CC PTPSupport.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./net/PTPSupport.cpp"
 ,"-o"
 ,OBJ_PATH+"/PTPSupport.o"
} } ;

IntCmd intdep266 = { 'RM DEP' , &rmdep266 } ;

Rm rmdep266 = { { OBJ_PATH+"/PTPSupport.dep" } } ;

Target cpp267 = { "PTPSupportBase.cpp" , "../../Applied/CCore/src/./net/PTPSupportBase.cpp" } ;
Target ocpp267 = { "PTPSupportBase.o" , OBJ_PATH+"/PTPSupportBase.o" } ;
Rule rcpp267 = { {&cpp267} , {&ocpp267} , {&intdep267,&execpp267} } ;
Exe execpp267 = { "CC PTPSupportBase.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./net/PTPSupportBase.cpp"
 ,"-o"
 ,OBJ_PATH+"/PTPSupportBase.o"
} } ;

IntCmd intdep267 = { 'RM DEP' , &rmdep267 } ;

Rm rmdep267 = { { OBJ_PATH+"/PTPSupportBase.dep" } } ;

Target cpp268 = { "Packet.cpp" , "../../Applied/CCore/src/Packet.cpp" } ;
Target ocpp268 = { "Packet.o" , OBJ_PATH+"/Packet.o" } ;
Rule rcpp268 = { {&cpp268} , {&ocpp268} , {&intdep268,&execpp268} } ;
Exe execpp268 = { "CC Packet.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/Packet.cpp"
 ,"-o"
 ,OBJ_PATH+"/Packet.o"
} } ;

IntCmd intdep268 = { 'RM DEP' , &rmdep268 } ;

Rm rmdep268 = { { OBJ_PATH+"/Packet.dep" } } ;

Target cpp269 = { "PacketEndpointDevice.cpp" , "../../Applied/CCore/src/./net/PacketEndpointDevice.cpp" } ;
Target ocpp269 = { "PacketEndpointDevice.o" , OBJ_PATH+"/PacketEndpointDevice.o" } ;
Rule rcpp269 = { {&cpp269} , {&ocpp269} , {&intdep269,&execpp269} } ;
Exe execpp269 = { "CC PacketEndpointDevice.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./net/PacketEndpointDevice.cpp"
 ,"-o"
 ,OBJ_PATH+"/PacketEndpointDevice.o"
} } ;

IntCmd intdep269 = { 'RM DEP' , &rmdep269 } ;

Rm rmdep269 = { { OBJ_PATH+"/PacketEndpointDevice.dep" } } ;

Target cpp270 = { "PacketPool.cpp" , "../../Applied/CCore/src/PacketPool.cpp" } ;
Target ocpp270 = { "PacketPool.o" , OBJ_PATH+"/PacketPool.o" } ;
Rule rcpp270 = { {&cpp270} , {&ocpp270} , {&intdep270,&execpp270} } ;
Exe execpp270 = { "CC PacketPool.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/PacketPool.cpp"
 ,"-o"
 ,OBJ_PATH+"/PacketPool.o"
} } ;

IntCmd intdep270 = { 'RM DEP' , &rmdep270 } ;

Rm rmdep270 = { { OBJ_PATH+"/PacketPool.dep" } } ;

Target cpp271 = { "PacketPool_PacketCount.cpp" , "../../Applied/CCore/src/PacketPool_PacketCount.cpp" } ;
Target ocpp271 = { "PacketPool_PacketCount.o" , OBJ_PATH+"/PacketPool_PacketCount.o" } ;
Rule rcpp271 = { {&cpp271} , {&ocpp271} , {&intdep271,&execpp271} } ;
Exe execpp271 = { "CC PacketPool_PacketCount.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/PacketPool_PacketCount.cpp"
 ,"-o"
 ,OBJ_PATH+"/PacketPool_PacketCount.o"
} } ;

IntCmd intdep271 = { 'RM DEP' , &rmdep271 } ;

Rm rmdep271 = { { OBJ_PATH+"/PacketPool_PacketCount.dep" } } ;

Target cpp272 = { "PacketPool_PacketMaxDataLen.cpp" , "../../Applied/CCore/src/PacketPool_PacketMaxDataLen.cpp" } ;
Target ocpp272 = { "PacketPool_PacketMaxDataLen.o" , OBJ_PATH+"/PacketPool_PacketMaxDataLen.o" } ;
Rule rcpp272 = { {&cpp272} , {&ocpp272} , {&intdep272,&execpp272} } ;
Exe execpp272 = { "CC PacketPool_PacketMaxDataLen.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/PacketPool_PacketMaxDataLen.cpp"
 ,"-o"
 ,OBJ_PATH+"/PacketPool_PacketMaxDataLen.o"
} } ;

IntCmd intdep272 = { 'RM DEP' , &rmdep272 } ;

Rm rmdep272 = { { OBJ_PATH+"/PacketPool_PacketMaxDataLen.dep" } } ;

Target cpp273 = { "PacketSet.cpp" , "../../Applied/CCore/src/PacketSet.cpp" } ;
Target ocpp273 = { "PacketSet.o" , OBJ_PATH+"/PacketSet.o" } ;
Rule rcpp273 = { {&cpp273} , {&ocpp273} , {&intdep273,&execpp273} } ;
Exe execpp273 = { "CC PacketSet.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/PacketSet.cpp"
 ,"-o"
 ,OBJ_PATH+"/PacketSet.o"
} } ;

IntCmd intdep273 = { 'RM DEP' , &rmdep273 } ;

Rm rmdep273 = { { OBJ_PATH+"/PacketSet.dep" } } ;

Target cpp274 = { "ParaQuickSort.cpp" , "../../Fundamental/CCore/src/./sort/ParaQuickSort.cpp" } ;
Target ocpp274 = { "ParaQuickSort.o" , OBJ_PATH+"/ParaQuickSort.o" } ;
Rule rcpp274 = { {&cpp274} , {&ocpp274} , {&intdep274,&execpp274} } ;
Exe execpp274 = { "CC ParaQuickSort.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./sort/ParaQuickSort.cpp"
 ,"-o"
 ,OBJ_PATH+"/ParaQuickSort.o"
} } ;

IntCmd intdep274 = { 'RM DEP' , &rmdep274 } ;

Rm rmdep274 = { { OBJ_PATH+"/ParaQuickSort.dep" } } ;

Target cpp275 = { "Partition.cpp" , "../../Fundamental/CCore/src/./algon/Partition.cpp" } ;
Target ocpp275 = { "Partition.o" , OBJ_PATH+"/Partition.o" } ;
Rule rcpp275 = { {&cpp275} , {&ocpp275} , {&intdep275,&execpp275} } ;
Exe execpp275 = { "CC Partition.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./algon/Partition.cpp"
 ,"-o"
 ,OBJ_PATH+"/Partition.o"
} } ;

IntCmd intdep275 = { 'RM DEP' , &rmdep275 } ;

Rm rmdep275 = { { OBJ_PATH+"/Partition.dep" } } ;

Target cpp276 = { "Path.cpp" , "../../Fundamental/CCore/src/Path.cpp" } ;
Target ocpp276 = { "Path.o" , OBJ_PATH+"/Path.o" } ;
Rule rcpp276 = { {&cpp276} , {&ocpp276} , {&intdep276,&execpp276} } ;
Exe execpp276 = { "CC Path.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/Path.cpp"
 ,"-o"
 ,OBJ_PATH+"/Path.o"
} } ;

IntCmd intdep276 = { 'RM DEP' , &rmdep276 } ;

Rm rmdep276 = { { OBJ_PATH+"/Path.dep" } } ;

Target cpp277 = { "PerTask.cpp" , "../../Applied/CCore/src/PerTask.cpp" } ;
Target ocpp277 = { "PerTask.o" , OBJ_PATH+"/PerTask.o" } ;
Rule rcpp277 = { {&cpp277} , {&ocpp277} , {&intdep277,&execpp277} } ;
Exe execpp277 = { "CC PerTask.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/PerTask.cpp"
 ,"-o"
 ,OBJ_PATH+"/PerTask.o"
} } ;

IntCmd intdep277 = { 'RM DEP' , &rmdep277 } ;

Rm rmdep277 = { { OBJ_PATH+"/PerTask.dep" } } ;

Target cpp278 = { "Picture.cpp" , "../../Desktop/Tools/CCore/src/./video/Picture.cpp" } ;
Target ocpp278 = { "Picture.o" , OBJ_PATH+"/Picture.o" } ;
Rule rcpp278 = { {&cpp278} , {&ocpp278} , {&intdep278,&execpp278} } ;
Exe execpp278 = { "CC Picture.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Tools/CCore/src/./video/Picture.cpp"
 ,"-o"
 ,OBJ_PATH+"/Picture.o"
} } ;

IntCmd intdep278 = { 'RM DEP' , &rmdep278 } ;

Rm rmdep278 = { { OBJ_PATH+"/Picture.dep" } } ;

Target cpp279 = { "Place.cpp" , "../../Simple/CCore/src/./gadget/Place.cpp" } ;
Target ocpp279 = { "Place.o" , OBJ_PATH+"/Place.o" } ;
Rule rcpp279 = { {&cpp279} , {&ocpp279} , {&intdep279,&execpp279} } ;
Exe execpp279 = { "CC Place.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/Place.cpp"
 ,"-o"
 ,OBJ_PATH+"/Place.o"
} } ;

IntCmd intdep279 = { 'RM DEP' , &rmdep279 } ;

Rm rmdep279 = { { OBJ_PATH+"/Place.dep" } } ;

Target cpp280 = { "PlanInit.cpp" , "../../Fundamental/CCore/src/PlanInit.cpp" } ;
Target ocpp280 = { "PlanInit.o" , OBJ_PATH+"/PlanInit.o" } ;
Rule rcpp280 = { {&cpp280} , {&ocpp280} , {&intdep280,&execpp280} } ;
Exe execpp280 = { "CC PlanInit.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/PlanInit.cpp"
 ,"-o"
 ,OBJ_PATH+"/PlanInit.o"
} } ;

IntCmd intdep280 = { 'RM DEP' , &rmdep280 } ;

Rm rmdep280 = { { OBJ_PATH+"/PlanInit.dep" } } ;

Target cpp281 = { "PlanInit_CCore.cpp" , "CCore/src/PlanInit_CCore.cpp" } ;
Target ocpp281 = { "PlanInit_CCore.o" , OBJ_PATH+"/PlanInit_CCore.o" } ;
Rule rcpp281 = { {&cpp281} , {&ocpp281} , {&intdep281,&execpp281} } ;
Exe execpp281 = { "CC PlanInit_CCore.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/PlanInit_CCore.cpp"
 ,"-o"
 ,OBJ_PATH+"/PlanInit_CCore.o"
} } ;

IntCmd intdep281 = { 'RM DEP' , &rmdep281 } ;

Rm rmdep281 = { { OBJ_PATH+"/PlanInit_CCore.dep" } } ;

Target cpp282 = { "PlatformBase.cpp" , "CCore/src/./base/PlatformBase.cpp" } ;
Target ocpp282 = { "PlatformBase.o" , OBJ_PATH+"/PlatformBase.o" } ;
Rule rcpp282 = { {&cpp282} , {&ocpp282} , {&intdep282,&execpp282} } ;
Exe execpp282 = { "CC PlatformBase.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./base/PlatformBase.cpp"
 ,"-o"
 ,OBJ_PATH+"/PlatformBase.o"
} } ;

IntCmd intdep282 = { 'RM DEP' , &rmdep282 } ;

Rm rmdep282 = { { OBJ_PATH+"/PlatformBase.dep" } } ;

Target cpp283 = { "Point.cpp" , "../../Applied/CCore/src/./video/Point.cpp" } ;
Target ocpp283 = { "Point.o" , OBJ_PATH+"/Point.o" } ;
Rule rcpp283 = { {&cpp283} , {&ocpp283} , {&intdep283,&execpp283} } ;
Exe execpp283 = { "CC Point.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./video/Point.cpp"
 ,"-o"
 ,OBJ_PATH+"/Point.o"
} } ;

IntCmd intdep283 = { 'RM DEP' , &rmdep283 } ;

Rm rmdep283 = { { OBJ_PATH+"/Point.dep" } } ;

Target cpp284 = { "PointEdit.cpp" , "../../Desktop/Lib/CCore/src/./video/pref/PointEdit.cpp" } ;
Target ocpp284 = { "PointEdit.o" , OBJ_PATH+"/PointEdit.o" } ;
Rule rcpp284 = { {&cpp284} , {&ocpp284} , {&intdep284,&execpp284} } ;
Exe execpp284 = { "CC PointEdit.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/pref/PointEdit.cpp"
 ,"-o"
 ,OBJ_PATH+"/PointEdit.o"
} } ;

IntCmd intdep284 = { 'RM DEP' , &rmdep284 } ;

Rm rmdep284 = { { OBJ_PATH+"/PointEdit.dep" } } ;

Target cpp285 = { "PosSub.cpp" , "../../Simple/CCore/src/./gadget/PosSub.cpp" } ;
Target ocpp285 = { "PosSub.o" , OBJ_PATH+"/PosSub.o" } ;
Rule rcpp285 = { {&cpp285} , {&ocpp285} , {&intdep285,&execpp285} } ;
Exe execpp285 = { "CC PosSub.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/PosSub.cpp"
 ,"-o"
 ,OBJ_PATH+"/PosSub.o"
} } ;

IntCmd intdep285 = { 'RM DEP' , &rmdep285 } ;

Rm rmdep285 = { { OBJ_PATH+"/PosSub.dep" } } ;

Target cpp286 = { "Pow.cpp" , "../../Simple/CCore/src/Pow.cpp" } ;
Target ocpp286 = { "Pow.o" , OBJ_PATH+"/Pow.o" } ;
Rule rcpp286 = { {&cpp286} , {&ocpp286} , {&intdep286,&execpp286} } ;
Exe execpp286 = { "CC Pow.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/Pow.cpp"
 ,"-o"
 ,OBJ_PATH+"/Pow.o"
} } ;

IntCmd intdep286 = { 'RM DEP' , &rmdep286 } ;

Rm rmdep286 = { { OBJ_PATH+"/Pow.dep" } } ;

Target cpp287 = { "PretextFileToMem.cpp" , "../../Applied/CCore/src/PretextFileToMem.cpp" } ;
Target ocpp287 = { "PretextFileToMem.o" , OBJ_PATH+"/PretextFileToMem.o" } ;
Rule rcpp287 = { {&cpp287} , {&ocpp287} , {&intdep287,&execpp287} } ;
Exe execpp287 = { "CC PretextFileToMem.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/PretextFileToMem.cpp"
 ,"-o"
 ,OBJ_PATH+"/PretextFileToMem.o"
} } ;

IntCmd intdep287 = { 'RM DEP' , &rmdep287 } ;

Rm rmdep287 = { { OBJ_PATH+"/PretextFileToMem.dep" } } ;

Target cpp288 = { "Print.cpp" , "../../HCore/CCore/src/Print.cpp" } ;
Target ocpp288 = { "Print.o" , OBJ_PATH+"/Print.o" } ;
Rule rcpp288 = { {&cpp288} , {&ocpp288} , {&intdep288,&execpp288} } ;
Exe execpp288 = { "CC Print.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/Print.cpp"
 ,"-o"
 ,OBJ_PATH+"/Print.o"
} } ;

IntCmd intdep288 = { 'RM DEP' , &rmdep288 } ;

Rm rmdep288 = { { OBJ_PATH+"/Print.dep" } } ;

Target cpp289 = { "PrintAbort.cpp" , "../../Simple/CCore/src/PrintAbort.cpp" } ;
Target ocpp289 = { "PrintAbort.o" , OBJ_PATH+"/PrintAbort.o" } ;
Rule rcpp289 = { {&cpp289} , {&ocpp289} , {&intdep289,&execpp289} } ;
Exe execpp289 = { "CC PrintAbort.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/PrintAbort.cpp"
 ,"-o"
 ,OBJ_PATH+"/PrintAbort.o"
} } ;

IntCmd intdep289 = { 'RM DEP' , &rmdep289 } ;

Rm rmdep289 = { { OBJ_PATH+"/PrintAbort.dep" } } ;

Target cpp290 = { "PrintAsyncFile.cpp" , "../../Applied/CCore/src/./print/PrintAsyncFile.cpp" } ;
Target ocpp290 = { "PrintAsyncFile.o" , OBJ_PATH+"/PrintAsyncFile.o" } ;
Rule rcpp290 = { {&cpp290} , {&ocpp290} , {&intdep290,&execpp290} } ;
Exe execpp290 = { "CC PrintAsyncFile.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./print/PrintAsyncFile.cpp"
 ,"-o"
 ,OBJ_PATH+"/PrintAsyncFile.o"
} } ;

IntCmd intdep290 = { 'RM DEP' , &rmdep290 } ;

Rm rmdep290 = { { OBJ_PATH+"/PrintAsyncFile.dep" } } ;

Target cpp291 = { "PrintBase.cpp" , "../../Fundamental/CCore/src/./printf/PrintBase.cpp" } ;
Target ocpp291 = { "PrintBase.o" , OBJ_PATH+"/PrintBase.o" } ;
Rule rcpp291 = { {&cpp291} , {&ocpp291} , {&intdep291,&execpp291} } ;
Exe execpp291 = { "CC PrintBase.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./printf/PrintBase.cpp"
 ,"-o"
 ,OBJ_PATH+"/PrintBase.o"
} } ;

IntCmd intdep291 = { 'RM DEP' , &rmdep291 } ;

Rm rmdep291 = { { OBJ_PATH+"/PrintBase.dep" } } ;

Target cpp292 = { "PrintBits.cpp" , "../../Simple/CCore/src/PrintBits.cpp" } ;
Target ocpp292 = { "PrintBits.o" , OBJ_PATH+"/PrintBits.o" } ;
Rule rcpp292 = { {&cpp292} , {&ocpp292} , {&intdep292,&execpp292} } ;
Exe execpp292 = { "CC PrintBits.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/PrintBits.cpp"
 ,"-o"
 ,OBJ_PATH+"/PrintBits.o"
} } ;

IntCmd intdep292 = { 'RM DEP' , &rmdep292 } ;

Rm rmdep292 = { { OBJ_PATH+"/PrintBits.dep" } } ;

Target cpp293 = { "PrintCon.cpp" , "../../HCore/CCore/src/./print/PrintCon.cpp" } ;
Target ocpp293 = { "PrintCon.o" , OBJ_PATH+"/PrintCon.o" } ;
Rule rcpp293 = { {&cpp293} , {&ocpp293} , {&intdep293,&execpp293} } ;
Exe execpp293 = { "CC PrintCon.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/./print/PrintCon.cpp"
 ,"-o"
 ,OBJ_PATH+"/PrintCon.o"
} } ;

IntCmd intdep293 = { 'RM DEP' , &rmdep293 } ;

Rm rmdep293 = { { OBJ_PATH+"/PrintCon.dep" } } ;

Target cpp294 = { "PrintDDL.cpp" , "../../Desktop/Tools/CCore/src/./video/PrintDDL.cpp" } ;
Target ocpp294 = { "PrintDDL.o" , OBJ_PATH+"/PrintDDL.o" } ;
Rule rcpp294 = { {&cpp294} , {&ocpp294} , {&intdep294,&execpp294} } ;
Exe execpp294 = { "CC PrintDDL.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Tools/CCore/src/./video/PrintDDL.cpp"
 ,"-o"
 ,OBJ_PATH+"/PrintDDL.o"
} } ;

IntCmd intdep294 = { 'RM DEP' , &rmdep294 } ;

Rm rmdep294 = { { OBJ_PATH+"/PrintDDL.dep" } } ;

Target cpp295 = { "PrintError.cpp" , "../../Simple/CCore/src/PrintError.cpp" } ;
Target ocpp295 = { "PrintError.o" , OBJ_PATH+"/PrintError.o" } ;
Rule rcpp295 = { {&cpp295} , {&ocpp295} , {&intdep295,&execpp295} } ;
Exe execpp295 = { "CC PrintError.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/PrintError.cpp"
 ,"-o"
 ,OBJ_PATH+"/PrintError.o"
} } ;

IntCmd intdep295 = { 'RM DEP' , &rmdep295 } ;

Rm rmdep295 = { { OBJ_PATH+"/PrintError.dep" } } ;

Target cpp296 = { "PrintFile.cpp" , "../../HCore/CCore/src/./print/PrintFile.cpp" } ;
Target ocpp296 = { "PrintFile.o" , OBJ_PATH+"/PrintFile.o" } ;
Rule rcpp296 = { {&cpp296} , {&ocpp296} , {&intdep296,&execpp296} } ;
Exe execpp296 = { "CC PrintFile.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/./print/PrintFile.cpp"
 ,"-o"
 ,OBJ_PATH+"/PrintFile.o"
} } ;

IntCmd intdep296 = { 'RM DEP' , &rmdep296 } ;

Rm rmdep296 = { { OBJ_PATH+"/PrintFile.dep" } } ;

Target cpp297 = { "PrintInteger.cpp" , "../../Applied/CCore/src/./math/PrintInteger.cpp" } ;
Target ocpp297 = { "PrintInteger.o" , OBJ_PATH+"/PrintInteger.o" } ;
Rule rcpp297 = { {&cpp297} , {&ocpp297} , {&intdep297,&execpp297} } ;
Exe execpp297 = { "CC PrintInteger.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./math/PrintInteger.cpp"
 ,"-o"
 ,OBJ_PATH+"/PrintInteger.o"
} } ;

IntCmd intdep297 = { 'RM DEP' , &rmdep297 } ;

Rm rmdep297 = { { OBJ_PATH+"/PrintInteger.dep" } } ;

Target cpp298 = { "PrintPTPCon.cpp" , "../../Applied/CCore/src/./print/PrintPTPCon.cpp" } ;
Target ocpp298 = { "PrintPTPCon.o" , OBJ_PATH+"/PrintPTPCon.o" } ;
Rule rcpp298 = { {&cpp298} , {&ocpp298} , {&intdep298,&execpp298} } ;
Exe execpp298 = { "CC PrintPTPCon.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./print/PrintPTPCon.cpp"
 ,"-o"
 ,OBJ_PATH+"/PrintPTPCon.o"
} } ;

IntCmd intdep298 = { 'RM DEP' , &rmdep298 } ;

Rm rmdep298 = { { OBJ_PATH+"/PrintPTPCon.dep" } } ;

Target cpp299 = { "PrintProxy.cpp" , "../../Fundamental/CCore/src/./printf/PrintProxy.cpp" } ;
Target ocpp299 = { "PrintProxy.o" , OBJ_PATH+"/PrintProxy.o" } ;
Rule rcpp299 = { {&cpp299} , {&ocpp299} , {&intdep299,&execpp299} } ;
Exe execpp299 = { "CC PrintProxy.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./printf/PrintProxy.cpp"
 ,"-o"
 ,OBJ_PATH+"/PrintProxy.o"
} } ;

IntCmd intdep299 = { 'RM DEP' , &rmdep299 } ;

Rm rmdep299 = { { OBJ_PATH+"/PrintProxy.dep" } } ;

Target cpp300 = { "PrintRatio.cpp" , "../../Simple/CCore/src/PrintRatio.cpp" } ;
Target ocpp300 = { "PrintRatio.o" , OBJ_PATH+"/PrintRatio.o" } ;
Rule rcpp300 = { {&cpp300} , {&ocpp300} , {&intdep300,&execpp300} } ;
Exe execpp300 = { "CC PrintRatio.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/PrintRatio.cpp"
 ,"-o"
 ,OBJ_PATH+"/PrintRatio.o"
} } ;

IntCmd intdep300 = { 'RM DEP' , &rmdep300 } ;

Rm rmdep300 = { { OBJ_PATH+"/PrintRatio.dep" } } ;

Target cpp301 = { "PrintSet.cpp" , "../../Simple/CCore/src/PrintSet.cpp" } ;
Target ocpp301 = { "PrintSet.o" , OBJ_PATH+"/PrintSet.o" } ;
Rule rcpp301 = { {&cpp301} , {&ocpp301} , {&intdep301,&execpp301} } ;
Exe execpp301 = { "CC PrintSet.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/PrintSet.cpp"
 ,"-o"
 ,OBJ_PATH+"/PrintSet.o"
} } ;

IntCmd intdep301 = { 'RM DEP' , &rmdep301 } ;

Rm rmdep301 = { { OBJ_PATH+"/PrintSet.dep" } } ;

Target cpp302 = { "PrintStem.cpp" , "../../Simple/CCore/src/PrintStem.cpp" } ;
Target ocpp302 = { "PrintStem.o" , OBJ_PATH+"/PrintStem.o" } ;
Rule rcpp302 = { {&cpp302} , {&ocpp302} , {&intdep302,&execpp302} } ;
Exe execpp302 = { "CC PrintStem.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/PrintStem.cpp"
 ,"-o"
 ,OBJ_PATH+"/PrintStem.o"
} } ;

IntCmd intdep302 = { 'RM DEP' , &rmdep302 } ;

Rm rmdep302 = { { OBJ_PATH+"/PrintStem.dep" } } ;

Target cpp303 = { "PrintTime.cpp" , "../../Simple/CCore/src/PrintTime.cpp" } ;
Target ocpp303 = { "PrintTime.o" , OBJ_PATH+"/PrintTime.o" } ;
Rule rcpp303 = { {&cpp303} , {&ocpp303} , {&intdep303,&execpp303} } ;
Exe execpp303 = { "CC PrintTime.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/PrintTime.cpp"
 ,"-o"
 ,OBJ_PATH+"/PrintTime.o"
} } ;

IntCmd intdep303 = { 'RM DEP' , &rmdep303 } ;

Rm rmdep303 = { { OBJ_PATH+"/PrintTime.dep" } } ;

Target cpp304 = { "PrintTitle.cpp" , "../../Simple/CCore/src/PrintTitle.cpp" } ;
Target ocpp304 = { "PrintTitle.o" , OBJ_PATH+"/PrintTitle.o" } ;
Rule rcpp304 = { {&cpp304} , {&ocpp304} , {&intdep304,&execpp304} } ;
Exe execpp304 = { "CC PrintTitle.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/PrintTitle.cpp"
 ,"-o"
 ,OBJ_PATH+"/PrintTitle.o"
} } ;

IntCmd intdep304 = { 'RM DEP' , &rmdep304 } ;

Rm rmdep304 = { { OBJ_PATH+"/PrintTitle.dep" } } ;

Target cpp305 = { "Printf.cpp" , "../../Fundamental/CCore/src/Printf.cpp" } ;
Target ocpp305 = { "Printf.o" , OBJ_PATH+"/Printf.o" } ;
Rule rcpp305 = { {&cpp305} , {&ocpp305} , {&intdep305,&execpp305} } ;
Exe execpp305 = { "CC Printf.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/Printf.cpp"
 ,"-o"
 ,OBJ_PATH+"/Printf.o"
} } ;

IntCmd intdep305 = { 'RM DEP' , &rmdep305 } ;

Rm rmdep305 = { { OBJ_PATH+"/Printf.dep" } } ;

Target cpp306 = { "ProgressScale.cpp" , "../../Desktop/Tools/CCore/src/./video/ProgressScale.cpp" } ;
Target ocpp306 = { "ProgressScale.o" , OBJ_PATH+"/ProgressScale.o" } ;
Rule rcpp306 = { {&cpp306} , {&ocpp306} , {&intdep306,&execpp306} } ;
Exe execpp306 = { "CC ProgressScale.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Tools/CCore/src/./video/ProgressScale.cpp"
 ,"-o"
 ,OBJ_PATH+"/ProgressScale.o"
} } ;

IntCmd intdep306 = { 'RM DEP' , &rmdep306 } ;

Rm rmdep306 = { { OBJ_PATH+"/ProgressScale.dep" } } ;

Target cpp307 = { "PtrLen.cpp" , "../../Simple/CCore/src/./gadget/PtrLen.cpp" } ;
Target ocpp307 = { "PtrLen.o" , OBJ_PATH+"/PtrLen.o" } ;
Rule rcpp307 = { {&cpp307} , {&ocpp307} , {&intdep307,&execpp307} } ;
Exe execpp307 = { "CC PtrLen.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/PtrLen.cpp"
 ,"-o"
 ,OBJ_PATH+"/PtrLen.o"
} } ;

IntCmd intdep307 = { 'RM DEP' , &rmdep307 } ;

Rm rmdep307 = { { OBJ_PATH+"/PtrLen.dep" } } ;

Target cpp308 = { "PtrLenReverse.cpp" , "../../Simple/CCore/src/./gadget/PtrLenReverse.cpp" } ;
Target ocpp308 = { "PtrLenReverse.o" , OBJ_PATH+"/PtrLenReverse.o" } ;
Rule rcpp308 = { {&cpp308} , {&ocpp308} , {&intdep308,&execpp308} } ;
Exe execpp308 = { "CC PtrLenReverse.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/PtrLenReverse.cpp"
 ,"-o"
 ,OBJ_PATH+"/PtrLenReverse.o"
} } ;

IntCmd intdep308 = { 'RM DEP' , &rmdep308 } ;

Rm rmdep308 = { { OBJ_PATH+"/PtrLenReverse.dep" } } ;

Target cpp309 = { "PtrStepLen.cpp" , "../../Simple/CCore/src/./gadget/PtrStepLen.cpp" } ;
Target ocpp309 = { "PtrStepLen.o" , OBJ_PATH+"/PtrStepLen.o" } ;
Rule rcpp309 = { {&cpp309} , {&ocpp309} , {&intdep309,&execpp309} } ;
Exe execpp309 = { "CC PtrStepLen.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/PtrStepLen.cpp"
 ,"-o"
 ,OBJ_PATH+"/PtrStepLen.o"
} } ;

IntCmd intdep309 = { 'RM DEP' , &rmdep309 } ;

Rm rmdep309 = { { OBJ_PATH+"/PtrStepLen.dep" } } ;

Target cpp310 = { "Quick.cpp" , "CCore/src/./base/Quick.cpp" } ;
Target ocpp310 = { "Quick.o" , OBJ_PATH+"/Quick.o" } ;
Rule rcpp310 = { {&cpp310} , {&ocpp310} , {&intdep310,&execpp310} } ;
Exe execpp310 = { "CC Quick.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./base/Quick.cpp"
 ,"-o"
 ,OBJ_PATH+"/Quick.o"
} } ;

IntCmd intdep310 = { 'RM DEP' , &rmdep310 } ;

Rm rmdep310 = { { OBJ_PATH+"/Quick.dep" } } ;

Target cpp311 = { "QuickSort.cpp" , "../../Fundamental/CCore/src/./sort/QuickSort.cpp" } ;
Target ocpp311 = { "QuickSort.o" , OBJ_PATH+"/QuickSort.o" } ;
Rule rcpp311 = { {&cpp311} , {&ocpp311} , {&intdep311,&execpp311} } ;
Exe execpp311 = { "CC QuickSort.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./sort/QuickSort.cpp"
 ,"-o"
 ,OBJ_PATH+"/QuickSort.o"
} } ;

IntCmd intdep311 = { 'RM DEP' , &rmdep311 } ;

Rm rmdep311 = { { OBJ_PATH+"/QuickSort.dep" } } ;

Target cpp312 = { "RBTreeBase.cpp" , "../../Fundamental/CCore/src/./tree/RBTreeBase.cpp" } ;
Target ocpp312 = { "RBTreeBase.o" , OBJ_PATH+"/RBTreeBase.o" } ;
Rule rcpp312 = { {&cpp312} , {&ocpp312} , {&intdep312,&execpp312} } ;
Exe execpp312 = { "CC RBTreeBase.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./tree/RBTreeBase.cpp"
 ,"-o"
 ,OBJ_PATH+"/RBTreeBase.o"
} } ;

IntCmd intdep312 = { 'RM DEP' , &rmdep312 } ;

Rm rmdep312 = { { OBJ_PATH+"/RBTreeBase.dep" } } ;

Target cpp313 = { "RBTreeLink.cpp" , "../../Fundamental/CCore/src/./tree/RBTreeLink.cpp" } ;
Target ocpp313 = { "RBTreeLink.o" , OBJ_PATH+"/RBTreeLink.o" } ;
Rule rcpp313 = { {&cpp313} , {&ocpp313} , {&intdep313,&execpp313} } ;
Exe execpp313 = { "CC RBTreeLink.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./tree/RBTreeLink.cpp"
 ,"-o"
 ,OBJ_PATH+"/RBTreeLink.o"
} } ;

IntCmd intdep313 = { 'RM DEP' , &rmdep313 } ;

Rm rmdep313 = { { OBJ_PATH+"/RBTreeLink.dep" } } ;

Target cpp314 = { "RBTreeUpLink.cpp" , "../../Fundamental/CCore/src/./tree/RBTreeUpLink.cpp" } ;
Target ocpp314 = { "RBTreeUpLink.o" , OBJ_PATH+"/RBTreeUpLink.o" } ;
Rule rcpp314 = { {&cpp314} , {&ocpp314} , {&intdep314,&execpp314} } ;
Exe execpp314 = { "CC RBTreeUpLink.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./tree/RBTreeUpLink.cpp"
 ,"-o"
 ,OBJ_PATH+"/RBTreeUpLink.o"
} } ;

IntCmd intdep314 = { 'RM DEP' , &rmdep314 } ;

Rm rmdep314 = { { OBJ_PATH+"/RBTreeUpLink.dep" } } ;

Target cpp315 = { "RadixHeap.cpp" , "../../Fundamental/CCore/src/RadixHeap.cpp" } ;
Target ocpp315 = { "RadixHeap.o" , OBJ_PATH+"/RadixHeap.o" } ;
Rule rcpp315 = { {&cpp315} , {&ocpp315} , {&intdep315,&execpp315} } ;
Exe execpp315 = { "CC RadixHeap.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/RadixHeap.cpp"
 ,"-o"
 ,OBJ_PATH+"/RadixHeap.o"
} } ;

IntCmd intdep315 = { 'RM DEP' , &rmdep315 } ;

Rm rmdep315 = { { OBJ_PATH+"/RadixHeap.dep" } } ;

Target cpp316 = { "Random.cpp" , "../../Fundamental/CCore/src/Random.cpp" } ;
Target ocpp316 = { "Random.o" , OBJ_PATH+"/Random.o" } ;
Rule rcpp316 = { {&cpp316} , {&ocpp316} , {&intdep316,&execpp316} } ;
Exe execpp316 = { "CC Random.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/Random.cpp"
 ,"-o"
 ,OBJ_PATH+"/Random.o"
} } ;

IntCmd intdep316 = { 'RM DEP' , &rmdep316 } ;

Rm rmdep316 = { { OBJ_PATH+"/Random.dep" } } ;

Target cpp317 = { "RangeDel.cpp" , "../../Simple/CCore/src/RangeDel.cpp" } ;
Target ocpp317 = { "RangeDel.o" , OBJ_PATH+"/RangeDel.o" } ;
Rule rcpp317 = { {&cpp317} , {&ocpp317} , {&intdep317,&execpp317} } ;
Exe execpp317 = { "CC RangeDel.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/RangeDel.cpp"
 ,"-o"
 ,OBJ_PATH+"/RangeDel.o"
} } ;

IntCmd intdep317 = { 'RM DEP' , &rmdep317 } ;

Rm rmdep317 = { { OBJ_PATH+"/RangeDel.dep" } } ;

Target cpp318 = { "RatioEdit.cpp" , "../../Desktop/Lib/CCore/src/./video/pref/RatioEdit.cpp" } ;
Target ocpp318 = { "RatioEdit.o" , OBJ_PATH+"/RatioEdit.o" } ;
Rule rcpp318 = { {&cpp318} , {&ocpp318} , {&intdep318,&execpp318} } ;
Exe execpp318 = { "CC RatioEdit.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/pref/RatioEdit.cpp"
 ,"-o"
 ,OBJ_PATH+"/RatioEdit.o"
} } ;

IntCmd intdep318 = { 'RM DEP' , &rmdep318 } ;

Rm rmdep318 = { { OBJ_PATH+"/RatioEdit.dep" } } ;

Target cpp319 = { "RawFileToRead.cpp" , "../../HCore/CCore/src/RawFileToRead.cpp" } ;
Target ocpp319 = { "RawFileToRead.o" , OBJ_PATH+"/RawFileToRead.o" } ;
Rule rcpp319 = { {&cpp319} , {&ocpp319} , {&intdep319,&execpp319} } ;
Exe execpp319 = { "CC RawFileToRead.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/RawFileToRead.cpp"
 ,"-o"
 ,OBJ_PATH+"/RawFileToRead.o"
} } ;

IntCmd intdep319 = { 'RM DEP' , &rmdep319 } ;

Rm rmdep319 = { { OBJ_PATH+"/RawFileToRead.dep" } } ;

Target cpp320 = { "ReadCon.cpp" , "../../HCore/CCore/src/ReadCon.cpp" } ;
Target ocpp320 = { "ReadCon.o" , OBJ_PATH+"/ReadCon.o" } ;
Rule rcpp320 = { {&cpp320} , {&ocpp320} , {&intdep320,&execpp320} } ;
Exe execpp320 = { "CC ReadCon.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/ReadCon.cpp"
 ,"-o"
 ,OBJ_PATH+"/ReadCon.o"
} } ;

IntCmd intdep320 = { 'RM DEP' , &rmdep320 } ;

Rm rmdep320 = { { OBJ_PATH+"/ReadCon.dep" } } ;

Target cpp321 = { "ReadConType.cpp" , "../../Fundamental/CCore/src/ReadConType.cpp" } ;
Target ocpp321 = { "ReadConType.o" , OBJ_PATH+"/ReadConType.o" } ;
Rule rcpp321 = { {&cpp321} , {&ocpp321} , {&intdep321,&execpp321} } ;
Exe execpp321 = { "CC ReadConType.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/ReadConType.cpp"
 ,"-o"
 ,OBJ_PATH+"/ReadConType.o"
} } ;

IntCmd intdep321 = { 'RM DEP' , &rmdep321 } ;

Rm rmdep321 = { { OBJ_PATH+"/ReadConType.dep" } } ;

Target cpp322 = { "RefArray.cpp" , "../../Fundamental/CCore/src/./array/RefArray.cpp" } ;
Target ocpp322 = { "RefArray.o" , OBJ_PATH+"/RefArray.o" } ;
Rule rcpp322 = { {&cpp322} , {&ocpp322} , {&intdep322,&execpp322} } ;
Exe execpp322 = { "CC RefArray.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./array/RefArray.cpp"
 ,"-o"
 ,OBJ_PATH+"/RefArray.o"
} } ;

IntCmd intdep322 = { 'RM DEP' , &rmdep322 } ;

Rm rmdep322 = { { OBJ_PATH+"/RefArray.dep" } } ;

Target cpp323 = { "RefObjectBase.cpp" , "../../Simple/CCore/src/RefObjectBase.cpp" } ;
Target ocpp323 = { "RefObjectBase.o" , OBJ_PATH+"/RefObjectBase.o" } ;
Rule rcpp323 = { {&cpp323} , {&ocpp323} , {&intdep323,&execpp323} } ;
Exe execpp323 = { "CC RefObjectBase.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/RefObjectBase.cpp"
 ,"-o"
 ,OBJ_PATH+"/RefObjectBase.o"
} } ;

IntCmd intdep323 = { 'RM DEP' , &rmdep323 } ;

Rm rmdep323 = { { OBJ_PATH+"/RefObjectBase.dep" } } ;

Target cpp324 = { "RefPtr.cpp" , "../../Simple/CCore/src/RefPtr.cpp" } ;
Target ocpp324 = { "RefPtr.o" , OBJ_PATH+"/RefPtr.o" } ;
Rule rcpp324 = { {&cpp324} , {&ocpp324} , {&intdep324,&execpp324} } ;
Exe execpp324 = { "CC RefPtr.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/RefPtr.cpp"
 ,"-o"
 ,OBJ_PATH+"/RefPtr.o"
} } ;

IntCmd intdep324 = { 'RM DEP' , &rmdep324 } ;

Rm rmdep324 = { { OBJ_PATH+"/RefPtr.dep" } } ;

Target cpp325 = { "RefVal.cpp" , "../../Desktop/Core/CCore/src/./video/RefVal.cpp" } ;
Target ocpp325 = { "RefVal.o" , OBJ_PATH+"/RefVal.o" } ;
Rule rcpp325 = { {&cpp325} , {&ocpp325} , {&intdep325,&execpp325} } ;
Exe execpp325 = { "CC RefVal.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Core/CCore/src/./video/RefVal.cpp"
 ,"-o"
 ,OBJ_PATH+"/RefVal.o"
} } ;

IntCmd intdep325 = { 'RM DEP' , &rmdep325 } ;

Rm rmdep325 = { { OBJ_PATH+"/RefVal.dep" } } ;

Target cpp326 = { "Replace.cpp" , "../../Simple/CCore/src/./gadget/Replace.cpp" } ;
Target ocpp326 = { "Replace.o" , OBJ_PATH+"/Replace.o" } ;
Rule rcpp326 = { {&cpp326} , {&ocpp326} , {&intdep326,&execpp326} } ;
Exe execpp326 = { "CC Replace.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/Replace.cpp"
 ,"-o"
 ,OBJ_PATH+"/Replace.o"
} } ;

IntCmd intdep326 = { 'RM DEP' , &rmdep326 } ;

Rm rmdep326 = { { OBJ_PATH+"/Replace.dep" } } ;

Target cpp327 = { "ResSem.cpp" , "../../HCore/CCore/src/./task/ResSem.cpp" } ;
Target ocpp327 = { "ResSem.o" , OBJ_PATH+"/ResSem.o" } ;
Rule rcpp327 = { {&cpp327} , {&ocpp327} , {&intdep327,&execpp327} } ;
Exe execpp327 = { "CC ResSem.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/./task/ResSem.cpp"
 ,"-o"
 ,OBJ_PATH+"/ResSem.o"
} } ;

IntCmd intdep327 = { 'RM DEP' , &rmdep327 } ;

Rm rmdep327 = { { OBJ_PATH+"/ResSem.dep" } } ;

Target cpp328 = { "Rot.cpp" , "../../Applied/CCore/src/./crypton/Rot.cpp" } ;
Target ocpp328 = { "Rot.o" , OBJ_PATH+"/Rot.o" } ;
Rule rcpp328 = { {&cpp328} , {&ocpp328} , {&intdep328,&execpp328} } ;
Exe execpp328 = { "CC Rot.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./crypton/Rot.cpp"
 ,"-o"
 ,OBJ_PATH+"/Rot.o"
} } ;

IntCmd intdep328 = { 'RM DEP' , &rmdep328 } ;

Rm rmdep328 = { { OBJ_PATH+"/Rot.dep" } } ;

Target cpp329 = { "SHA.cpp" , "../../Applied/CCore/src/./crypton/SHA.cpp" } ;
Target ocpp329 = { "SHA.o" , OBJ_PATH+"/SHA.o" } ;
Rule rcpp329 = { {&cpp329} , {&ocpp329} , {&intdep329,&execpp329} } ;
Exe execpp329 = { "CC SHA.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./crypton/SHA.cpp"
 ,"-o"
 ,OBJ_PATH+"/SHA.o"
} } ;

IntCmd intdep329 = { 'RM DEP' , &rmdep329 } ;

Rm rmdep329 = { { OBJ_PATH+"/SHA.dep" } } ;

Target cpp330 = { "SIntFunc.cpp" , "../../Simple/CCore/src/./gadget/SIntFunc.cpp" } ;
Target ocpp330 = { "SIntFunc.o" , OBJ_PATH+"/SIntFunc.o" } ;
Rule rcpp330 = { {&cpp330} , {&ocpp330} , {&intdep330,&execpp330} } ;
Exe execpp330 = { "CC SIntFunc.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/SIntFunc.cpp"
 ,"-o"
 ,OBJ_PATH+"/SIntFunc.o"
} } ;

IntCmd intdep330 = { 'RM DEP' , &rmdep330 } ;

Rm rmdep330 = { { OBJ_PATH+"/SIntFunc.dep" } } ;

Target cpp331 = { "SafeBuf.cpp" , "../../Simple/CCore/src/SafeBuf.cpp" } ;
Target ocpp331 = { "SafeBuf.o" , OBJ_PATH+"/SafeBuf.o" } ;
Rule rcpp331 = { {&cpp331} , {&ocpp331} , {&intdep331,&execpp331} } ;
Exe execpp331 = { "CC SafeBuf.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/SafeBuf.cpp"
 ,"-o"
 ,OBJ_PATH+"/SafeBuf.o"
} } ;

IntCmd intdep331 = { 'RM DEP' , &rmdep331 } ;

Rm rmdep331 = { { OBJ_PATH+"/SafeBuf.dep" } } ;

Target cpp332 = { "SaveLoad.cpp" , "../../Fundamental/CCore/src/SaveLoad.cpp" } ;
Target ocpp332 = { "SaveLoad.o" , OBJ_PATH+"/SaveLoad.o" } ;
Rule rcpp332 = { {&cpp332} , {&ocpp332} , {&intdep332,&execpp332} } ;
Exe execpp332 = { "CC SaveLoad.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/SaveLoad.cpp"
 ,"-o"
 ,OBJ_PATH+"/SaveLoad.o"
} } ;

IntCmd intdep332 = { 'RM DEP' , &rmdep332 } ;

Rm rmdep332 = { { OBJ_PATH+"/SaveLoad.dep" } } ;

Target cpp333 = { "Scan.cpp" , "../../HCore/CCore/src/Scan.cpp" } ;
Target ocpp333 = { "Scan.o" , OBJ_PATH+"/Scan.o" } ;
Rule rcpp333 = { {&cpp333} , {&ocpp333} , {&intdep333,&execpp333} } ;
Exe execpp333 = { "CC Scan.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/Scan.cpp"
 ,"-o"
 ,OBJ_PATH+"/Scan.o"
} } ;

IntCmd intdep333 = { 'RM DEP' , &rmdep333 } ;

Rm rmdep333 = { { OBJ_PATH+"/Scan.dep" } } ;

Target cpp334 = { "ScanAsyncFile.cpp" , "../../Applied/CCore/src/./scan/ScanAsyncFile.cpp" } ;
Target ocpp334 = { "ScanAsyncFile.o" , OBJ_PATH+"/ScanAsyncFile.o" } ;
Rule rcpp334 = { {&cpp334} , {&ocpp334} , {&intdep334,&execpp334} } ;
Exe execpp334 = { "CC ScanAsyncFile.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./scan/ScanAsyncFile.cpp"
 ,"-o"
 ,OBJ_PATH+"/ScanAsyncFile.o"
} } ;

IntCmd intdep334 = { 'RM DEP' , &rmdep334 } ;

Rm rmdep334 = { { OBJ_PATH+"/ScanAsyncFile.dep" } } ;

Target cpp335 = { "ScanBase.cpp" , "../../Fundamental/CCore/src/./scanf/ScanBase.cpp" } ;
Target ocpp335 = { "ScanBase.o" , OBJ_PATH+"/ScanBase.o" } ;
Rule rcpp335 = { {&cpp335} , {&ocpp335} , {&intdep335,&execpp335} } ;
Exe execpp335 = { "CC ScanBase.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./scanf/ScanBase.cpp"
 ,"-o"
 ,OBJ_PATH+"/ScanBase.o"
} } ;

IntCmd intdep335 = { 'RM DEP' , &rmdep335 } ;

Rm rmdep335 = { { OBJ_PATH+"/ScanBase.dep" } } ;

Target cpp336 = { "ScanBit.cpp" , "../../Simple/CCore/src/ScanBit.cpp" } ;
Target ocpp336 = { "ScanBit.o" , OBJ_PATH+"/ScanBit.o" } ;
Rule rcpp336 = { {&cpp336} , {&ocpp336} , {&intdep336,&execpp336} } ;
Exe execpp336 = { "CC ScanBit.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/ScanBit.cpp"
 ,"-o"
 ,OBJ_PATH+"/ScanBit.o"
} } ;

IntCmd intdep336 = { 'RM DEP' , &rmdep336 } ;

Rm rmdep336 = { { OBJ_PATH+"/ScanBit.dep" } } ;

Target cpp337 = { "ScanFile.cpp" , "../../HCore/CCore/src/./scan/ScanFile.cpp" } ;
Target ocpp337 = { "ScanFile.o" , OBJ_PATH+"/ScanFile.o" } ;
Rule rcpp337 = { {&cpp337} , {&ocpp337} , {&intdep337,&execpp337} } ;
Exe execpp337 = { "CC ScanFile.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/./scan/ScanFile.cpp"
 ,"-o"
 ,OBJ_PATH+"/ScanFile.o"
} } ;

IntCmd intdep337 = { 'RM DEP' , &rmdep337 } ;

Rm rmdep337 = { { OBJ_PATH+"/ScanFile.dep" } } ;

Target cpp338 = { "ScanProxy.cpp" , "../../Fundamental/CCore/src/./scanf/ScanProxy.cpp" } ;
Target ocpp338 = { "ScanProxy.o" , OBJ_PATH+"/ScanProxy.o" } ;
Rule rcpp338 = { {&cpp338} , {&ocpp338} , {&intdep338,&execpp338} } ;
Exe execpp338 = { "CC ScanProxy.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./scanf/ScanProxy.cpp"
 ,"-o"
 ,OBJ_PATH+"/ScanProxy.o"
} } ;

IntCmd intdep338 = { 'RM DEP' , &rmdep338 } ;

Rm rmdep338 = { { OBJ_PATH+"/ScanProxy.dep" } } ;

Target cpp339 = { "ScanRange.cpp" , "../../Simple/CCore/src/ScanRange.cpp" } ;
Target ocpp339 = { "ScanRange.o" , OBJ_PATH+"/ScanRange.o" } ;
Rule rcpp339 = { {&cpp339} , {&ocpp339} , {&intdep339,&execpp339} } ;
Exe execpp339 = { "CC ScanRange.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/ScanRange.cpp"
 ,"-o"
 ,OBJ_PATH+"/ScanRange.o"
} } ;

IntCmd intdep339 = { 'RM DEP' , &rmdep339 } ;

Rm rmdep339 = { { OBJ_PATH+"/ScanRange.dep" } } ;

Target cpp340 = { "ScanTools.cpp" , "../../Fundamental/CCore/src/./scanf/ScanTools.cpp" } ;
Target ocpp340 = { "ScanTools.o" , OBJ_PATH+"/ScanTools.o" } ;
Rule rcpp340 = { {&cpp340} , {&ocpp340} , {&intdep340,&execpp340} } ;
Exe execpp340 = { "CC ScanTools.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./scanf/ScanTools.cpp"
 ,"-o"
 ,OBJ_PATH+"/ScanTools.o"
} } ;

IntCmd intdep340 = { 'RM DEP' , &rmdep340 } ;

Rm rmdep340 = { { OBJ_PATH+"/ScanTools.dep" } } ;

Target cpp341 = { "Scanf.cpp" , "../../Fundamental/CCore/src/Scanf.cpp" } ;
Target ocpp341 = { "Scanf.o" , OBJ_PATH+"/Scanf.o" } ;
Rule rcpp341 = { {&cpp341} , {&ocpp341} , {&intdep341,&execpp341} } ;
Exe execpp341 = { "CC Scanf.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/Scanf.cpp"
 ,"-o"
 ,OBJ_PATH+"/Scanf.o"
} } ;

IntCmd intdep341 = { 'RM DEP' , &rmdep341 } ;

Rm rmdep341 = { { OBJ_PATH+"/Scanf.dep" } } ;

Target cpp342 = { "Scope.cpp" , "../../Fundamental/CCore/src/Scope.cpp" } ;
Target ocpp342 = { "Scope.o" , OBJ_PATH+"/Scope.o" } ;
Rule rcpp342 = { {&cpp342} , {&ocpp342} , {&intdep342,&execpp342} } ;
Exe execpp342 = { "CC Scope.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/Scope.cpp"
 ,"-o"
 ,OBJ_PATH+"/Scope.o"
} } ;

IntCmd intdep342 = { 'RM DEP' , &rmdep342 } ;

Rm rmdep342 = { { OBJ_PATH+"/Scope.dep" } } ;

Target cpp343 = { "ScopeGuard.cpp" , "../../Simple/CCore/src/./gadget/ScopeGuard.cpp" } ;
Target ocpp343 = { "ScopeGuard.o" , OBJ_PATH+"/ScopeGuard.o" } ;
Rule rcpp343 = { {&cpp343} , {&ocpp343} , {&intdep343,&execpp343} } ;
Exe execpp343 = { "CC ScopeGuard.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/ScopeGuard.cpp"
 ,"-o"
 ,OBJ_PATH+"/ScopeGuard.o"
} } ;

IntCmd intdep343 = { 'RM DEP' , &rmdep343 } ;

Rm rmdep343 = { { OBJ_PATH+"/ScopeGuard.dep" } } ;

Target cpp344 = { "SelectFrames.cpp" , "../../Desktop/Lib/CCore/src/./video/book/SelectFrames.cpp" } ;
Target ocpp344 = { "SelectFrames.o" , OBJ_PATH+"/SelectFrames.o" } ;
Rule rcpp344 = { {&cpp344} , {&ocpp344} , {&intdep344,&execpp344} } ;
Exe execpp344 = { "CC SelectFrames.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/book/SelectFrames.cpp"
 ,"-o"
 ,OBJ_PATH+"/SelectFrames.o"
} } ;

IntCmd intdep344 = { 'RM DEP' , &rmdep344 } ;

Rm rmdep344 = { { OBJ_PATH+"/SelectFrames.dep" } } ;

Target cpp345 = { "Sem.cpp" , "../../HCore/CCore/src/./task/Sem.cpp" } ;
Target ocpp345 = { "Sem.o" , OBJ_PATH+"/Sem.o" } ;
Rule rcpp345 = { {&cpp345} , {&ocpp345} , {&intdep345,&execpp345} } ;
Exe execpp345 = { "CC Sem.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/./task/Sem.cpp"
 ,"-o"
 ,OBJ_PATH+"/Sem.o"
} } ;

IntCmd intdep345 = { 'RM DEP' , &rmdep345 } ;

Rm rmdep345 = { { OBJ_PATH+"/Sem.dep" } } ;

Target cpp346 = { "Shape.Button.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.Button.cpp" } ;
Target ocpp346 = { "Shape.Button.o" , OBJ_PATH+"/Shape.Button.o" } ;
Rule rcpp346 = { {&cpp346} , {&ocpp346} , {&intdep346,&execpp346} } ;
Exe execpp346 = { "CC Shape.Button.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.Button.cpp"
 ,"-o"
 ,OBJ_PATH+"/Shape.Button.o"
} } ;

IntCmd intdep346 = { 'RM DEP' , &rmdep346 } ;

Rm rmdep346 = { { OBJ_PATH+"/Shape.Button.dep" } } ;

Target cpp347 = { "Shape.Check.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.Check.cpp" } ;
Target ocpp347 = { "Shape.Check.o" , OBJ_PATH+"/Shape.Check.o" } ;
Rule rcpp347 = { {&cpp347} , {&ocpp347} , {&intdep347,&execpp347} } ;
Exe execpp347 = { "CC Shape.Check.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.Check.cpp"
 ,"-o"
 ,OBJ_PATH+"/Shape.Check.o"
} } ;

IntCmd intdep347 = { 'RM DEP' , &rmdep347 } ;

Rm rmdep347 = { { OBJ_PATH+"/Shape.Check.dep" } } ;

Target cpp348 = { "Shape.Contour.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.Contour.cpp" } ;
Target ocpp348 = { "Shape.Contour.o" , OBJ_PATH+"/Shape.Contour.o" } ;
Rule rcpp348 = { {&cpp348} , {&ocpp348} , {&intdep348,&execpp348} } ;
Exe execpp348 = { "CC Shape.Contour.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.Contour.cpp"
 ,"-o"
 ,OBJ_PATH+"/Shape.Contour.o"
} } ;

IntCmd intdep348 = { 'RM DEP' , &rmdep348 } ;

Rm rmdep348 = { { OBJ_PATH+"/Shape.Contour.dep" } } ;

Target cpp349 = { "Shape.DragFrame.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.DragFrame.cpp" } ;
Target ocpp349 = { "Shape.DragFrame.o" , OBJ_PATH+"/Shape.DragFrame.o" } ;
Rule rcpp349 = { {&cpp349} , {&ocpp349} , {&intdep349,&execpp349} } ;
Exe execpp349 = { "CC Shape.DragFrame.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.DragFrame.cpp"
 ,"-o"
 ,OBJ_PATH+"/Shape.DragFrame.o"
} } ;

IntCmd intdep349 = { 'RM DEP' , &rmdep349 } ;

Rm rmdep349 = { { OBJ_PATH+"/Shape.DragFrame.dep" } } ;

Target cpp350 = { "Shape.FixedFrame.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.FixedFrame.cpp" } ;
Target ocpp350 = { "Shape.FixedFrame.o" , OBJ_PATH+"/Shape.FixedFrame.o" } ;
Rule rcpp350 = { {&cpp350} , {&ocpp350} , {&intdep350,&execpp350} } ;
Exe execpp350 = { "CC Shape.FixedFrame.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.FixedFrame.cpp"
 ,"-o"
 ,OBJ_PATH+"/Shape.FixedFrame.o"
} } ;

IntCmd intdep350 = { 'RM DEP' , &rmdep350 } ;

Rm rmdep350 = { { OBJ_PATH+"/Shape.FixedFrame.dep" } } ;

Target cpp351 = { "Shape.FrameBase.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.FrameBase.cpp" } ;
Target ocpp351 = { "Shape.FrameBase.o" , OBJ_PATH+"/Shape.FrameBase.o" } ;
Rule rcpp351 = { {&cpp351} , {&ocpp351} , {&intdep351,&execpp351} } ;
Exe execpp351 = { "CC Shape.FrameBase.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.FrameBase.cpp"
 ,"-o"
 ,OBJ_PATH+"/Shape.FrameBase.o"
} } ;

IntCmd intdep351 = { 'RM DEP' , &rmdep351 } ;

Rm rmdep351 = { { OBJ_PATH+"/Shape.FrameBase.dep" } } ;

Target cpp352 = { "Shape.Info.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.Info.cpp" } ;
Target ocpp352 = { "Shape.Info.o" , OBJ_PATH+"/Shape.Info.o" } ;
Rule rcpp352 = { {&cpp352} , {&ocpp352} , {&intdep352,&execpp352} } ;
Exe execpp352 = { "CC Shape.Info.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.Info.cpp"
 ,"-o"
 ,OBJ_PATH+"/Shape.Info.o"
} } ;

IntCmd intdep352 = { 'RM DEP' , &rmdep352 } ;

Rm rmdep352 = { { OBJ_PATH+"/Shape.Info.dep" } } ;

Target cpp353 = { "Shape.Label.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.Label.cpp" } ;
Target ocpp353 = { "Shape.Label.o" , OBJ_PATH+"/Shape.Label.o" } ;
Rule rcpp353 = { {&cpp353} , {&ocpp353} , {&intdep353,&execpp353} } ;
Exe execpp353 = { "CC Shape.Label.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.Label.cpp"
 ,"-o"
 ,OBJ_PATH+"/Shape.Label.o"
} } ;

IntCmd intdep353 = { 'RM DEP' , &rmdep353 } ;

Rm rmdep353 = { { OBJ_PATH+"/Shape.Label.dep" } } ;

Target cpp354 = { "Shape.Light.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.Light.cpp" } ;
Target ocpp354 = { "Shape.Light.o" , OBJ_PATH+"/Shape.Light.o" } ;
Rule rcpp354 = { {&cpp354} , {&ocpp354} , {&intdep354,&execpp354} } ;
Exe execpp354 = { "CC Shape.Light.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.Light.cpp"
 ,"-o"
 ,OBJ_PATH+"/Shape.Light.o"
} } ;

IntCmd intdep354 = { 'RM DEP' , &rmdep354 } ;

Rm rmdep354 = { { OBJ_PATH+"/Shape.Light.dep" } } ;

Target cpp355 = { "Shape.Line.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.Line.cpp" } ;
Target ocpp355 = { "Shape.Line.o" , OBJ_PATH+"/Shape.Line.o" } ;
Rule rcpp355 = { {&cpp355} , {&ocpp355} , {&intdep355,&execpp355} } ;
Exe execpp355 = { "CC Shape.Line.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.Line.cpp"
 ,"-o"
 ,OBJ_PATH+"/Shape.Line.o"
} } ;

IntCmd intdep355 = { 'RM DEP' , &rmdep355 } ;

Rm rmdep355 = { { OBJ_PATH+"/Shape.Line.dep" } } ;

Target cpp356 = { "Shape.LineEdit.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.LineEdit.cpp" } ;
Target ocpp356 = { "Shape.LineEdit.o" , OBJ_PATH+"/Shape.LineEdit.o" } ;
Rule rcpp356 = { {&cpp356} , {&ocpp356} , {&intdep356,&execpp356} } ;
Exe execpp356 = { "CC Shape.LineEdit.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.LineEdit.cpp"
 ,"-o"
 ,OBJ_PATH+"/Shape.LineEdit.o"
} } ;

IntCmd intdep356 = { 'RM DEP' , &rmdep356 } ;

Rm rmdep356 = { { OBJ_PATH+"/Shape.LineEdit.dep" } } ;

Target cpp357 = { "Shape.Progress.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.Progress.cpp" } ;
Target ocpp357 = { "Shape.Progress.o" , OBJ_PATH+"/Shape.Progress.o" } ;
Rule rcpp357 = { {&cpp357} , {&ocpp357} , {&intdep357,&execpp357} } ;
Exe execpp357 = { "CC Shape.Progress.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.Progress.cpp"
 ,"-o"
 ,OBJ_PATH+"/Shape.Progress.o"
} } ;

IntCmd intdep357 = { 'RM DEP' , &rmdep357 } ;

Rm rmdep357 = { { OBJ_PATH+"/Shape.Progress.dep" } } ;

Target cpp358 = { "Shape.Radio.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.Radio.cpp" } ;
Target ocpp358 = { "Shape.Radio.o" , OBJ_PATH+"/Shape.Radio.o" } ;
Rule rcpp358 = { {&cpp358} , {&ocpp358} , {&intdep358,&execpp358} } ;
Exe execpp358 = { "CC Shape.Radio.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.Radio.cpp"
 ,"-o"
 ,OBJ_PATH+"/Shape.Radio.o"
} } ;

IntCmd intdep358 = { 'RM DEP' , &rmdep358 } ;

Rm rmdep358 = { { OBJ_PATH+"/Shape.Radio.dep" } } ;

Target cpp359 = { "Shape.RunButton.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.RunButton.cpp" } ;
Target ocpp359 = { "Shape.RunButton.o" , OBJ_PATH+"/Shape.RunButton.o" } ;
Rule rcpp359 = { {&cpp359} , {&ocpp359} , {&intdep359,&execpp359} } ;
Exe execpp359 = { "CC Shape.RunButton.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.RunButton.cpp"
 ,"-o"
 ,OBJ_PATH+"/Shape.RunButton.o"
} } ;

IntCmd intdep359 = { 'RM DEP' , &rmdep359 } ;

Rm rmdep359 = { { OBJ_PATH+"/Shape.RunButton.dep" } } ;

Target cpp360 = { "Shape.Scroll.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.Scroll.cpp" } ;
Target ocpp360 = { "Shape.Scroll.o" , OBJ_PATH+"/Shape.Scroll.o" } ;
Rule rcpp360 = { {&cpp360} , {&ocpp360} , {&intdep360,&execpp360} } ;
Exe execpp360 = { "CC Shape.Scroll.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.Scroll.cpp"
 ,"-o"
 ,OBJ_PATH+"/Shape.Scroll.o"
} } ;

IntCmd intdep360 = { 'RM DEP' , &rmdep360 } ;

Rm rmdep360 = { { OBJ_PATH+"/Shape.Scroll.dep" } } ;

Target cpp361 = { "Shape.ScrollList.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.ScrollList.cpp" } ;
Target ocpp361 = { "Shape.ScrollList.o" , OBJ_PATH+"/Shape.ScrollList.o" } ;
Rule rcpp361 = { {&cpp361} , {&ocpp361} , {&intdep361,&execpp361} } ;
Exe execpp361 = { "CC Shape.ScrollList.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.ScrollList.cpp"
 ,"-o"
 ,OBJ_PATH+"/Shape.ScrollList.o"
} } ;

IntCmd intdep361 = { 'RM DEP' , &rmdep361 } ;

Rm rmdep361 = { { OBJ_PATH+"/Shape.ScrollList.dep" } } ;

Target cpp362 = { "Shape.ShiftSwitch.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.ShiftSwitch.cpp" } ;
Target ocpp362 = { "Shape.ShiftSwitch.o" , OBJ_PATH+"/Shape.ShiftSwitch.o" } ;
Rule rcpp362 = { {&cpp362} , {&ocpp362} , {&intdep362,&execpp362} } ;
Exe execpp362 = { "CC Shape.ShiftSwitch.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.ShiftSwitch.cpp"
 ,"-o"
 ,OBJ_PATH+"/Shape.ShiftSwitch.o"
} } ;

IntCmd intdep362 = { 'RM DEP' , &rmdep362 } ;

Rm rmdep362 = { { OBJ_PATH+"/Shape.ShiftSwitch.dep" } } ;

Target cpp363 = { "Shape.SimpleTextList.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.SimpleTextList.cpp" } ;
Target ocpp363 = { "Shape.SimpleTextList.o" , OBJ_PATH+"/Shape.SimpleTextList.o" } ;
Rule rcpp363 = { {&cpp363} , {&ocpp363} , {&intdep363,&execpp363} } ;
Exe execpp363 = { "CC Shape.SimpleTextList.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.SimpleTextList.cpp"
 ,"-o"
 ,OBJ_PATH+"/Shape.SimpleTextList.o"
} } ;

IntCmd intdep363 = { 'RM DEP' , &rmdep363 } ;

Rm rmdep363 = { { OBJ_PATH+"/Shape.SimpleTextList.dep" } } ;

Target cpp364 = { "Shape.Slider.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.Slider.cpp" } ;
Target ocpp364 = { "Shape.Slider.o" , OBJ_PATH+"/Shape.Slider.o" } ;
Rule rcpp364 = { {&cpp364} , {&ocpp364} , {&intdep364,&execpp364} } ;
Exe execpp364 = { "CC Shape.Slider.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.Slider.cpp"
 ,"-o"
 ,OBJ_PATH+"/Shape.Slider.o"
} } ;

IntCmd intdep364 = { 'RM DEP' , &rmdep364 } ;

Rm rmdep364 = { { OBJ_PATH+"/Shape.Slider.dep" } } ;

Target cpp365 = { "Shape.Spinor.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.Spinor.cpp" } ;
Target ocpp365 = { "Shape.Spinor.o" , OBJ_PATH+"/Shape.Spinor.o" } ;
Rule rcpp365 = { {&cpp365} , {&ocpp365} , {&intdep365,&execpp365} } ;
Exe execpp365 = { "CC Shape.Spinor.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.Spinor.cpp"
 ,"-o"
 ,OBJ_PATH+"/Shape.Spinor.o"
} } ;

IntCmd intdep365 = { 'RM DEP' , &rmdep365 } ;

Rm rmdep365 = { { OBJ_PATH+"/Shape.Spinor.dep" } } ;

Target cpp366 = { "Shape.Split.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.Split.cpp" } ;
Target ocpp366 = { "Shape.Split.o" , OBJ_PATH+"/Shape.Split.o" } ;
Rule rcpp366 = { {&cpp366} , {&ocpp366} , {&intdep366,&execpp366} } ;
Exe execpp366 = { "CC Shape.Split.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.Split.cpp"
 ,"-o"
 ,OBJ_PATH+"/Shape.Split.o"
} } ;

IntCmd intdep366 = { 'RM DEP' , &rmdep366 } ;

Rm rmdep366 = { { OBJ_PATH+"/Shape.Split.dep" } } ;

Target cpp367 = { "Shape.Switch.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.Switch.cpp" } ;
Target ocpp367 = { "Shape.Switch.o" , OBJ_PATH+"/Shape.Switch.o" } ;
Rule rcpp367 = { {&cpp367} , {&ocpp367} , {&intdep367,&execpp367} } ;
Exe execpp367 = { "CC Shape.Switch.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.Switch.cpp"
 ,"-o"
 ,OBJ_PATH+"/Shape.Switch.o"
} } ;

IntCmd intdep367 = { 'RM DEP' , &rmdep367 } ;

Rm rmdep367 = { { OBJ_PATH+"/Shape.Switch.dep" } } ;

Target cpp368 = { "Shape.Text.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.Text.cpp" } ;
Target ocpp368 = { "Shape.Text.o" , OBJ_PATH+"/Shape.Text.o" } ;
Rule rcpp368 = { {&cpp368} , {&ocpp368} , {&intdep368,&execpp368} } ;
Exe execpp368 = { "CC Shape.Text.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.Text.cpp"
 ,"-o"
 ,OBJ_PATH+"/Shape.Text.o"
} } ;

IntCmd intdep368 = { 'RM DEP' , &rmdep368 } ;

Rm rmdep368 = { { OBJ_PATH+"/Shape.Text.dep" } } ;

Target cpp369 = { "Shape.TextLine.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.TextLine.cpp" } ;
Target ocpp369 = { "Shape.TextLine.o" , OBJ_PATH+"/Shape.TextLine.o" } ;
Rule rcpp369 = { {&cpp369} , {&ocpp369} , {&intdep369,&execpp369} } ;
Exe execpp369 = { "CC Shape.TextLine.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.TextLine.cpp"
 ,"-o"
 ,OBJ_PATH+"/Shape.TextLine.o"
} } ;

IntCmd intdep369 = { 'RM DEP' , &rmdep369 } ;

Rm rmdep369 = { { OBJ_PATH+"/Shape.TextLine.dep" } } ;

Target cpp370 = { "ShapeLib.cpp" , "../../Desktop/Lib/CCore/src/./video/ShapeLib.cpp" } ;
Target ocpp370 = { "ShapeLib.o" , OBJ_PATH+"/ShapeLib.o" } ;
Rule rcpp370 = { {&cpp370} , {&ocpp370} , {&intdep370,&execpp370} } ;
Exe execpp370 = { "CC ShapeLib.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/ShapeLib.cpp"
 ,"-o"
 ,OBJ_PATH+"/ShapeLib.o"
} } ;

IntCmd intdep370 = { 'RM DEP' , &rmdep370 } ;

Rm rmdep370 = { { OBJ_PATH+"/ShapeLib.dep" } } ;

Target cpp371 = { "ShortSort.cpp" , "../../Fundamental/CCore/src/./sort/ShortSort.cpp" } ;
Target ocpp371 = { "ShortSort.o" , OBJ_PATH+"/ShortSort.o" } ;
Rule rcpp371 = { {&cpp371} , {&ocpp371} , {&intdep371,&execpp371} } ;
Exe execpp371 = { "CC ShortSort.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./sort/ShortSort.cpp"
 ,"-o"
 ,OBJ_PATH+"/ShortSort.o"
} } ;

IntCmd intdep371 = { 'RM DEP' , &rmdep371 } ;

Rm rmdep371 = { { OBJ_PATH+"/ShortSort.dep" } } ;

Target cpp372 = { "Signal.cpp" , "../../Fundamental/CCore/src/Signal.cpp" } ;
Target ocpp372 = { "Signal.o" , OBJ_PATH+"/Signal.o" } ;
Rule rcpp372 = { {&cpp372} , {&ocpp372} , {&intdep372,&execpp372} } ;
Exe execpp372 = { "CC Signal.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/Signal.cpp"
 ,"-o"
 ,OBJ_PATH+"/Signal.o"
} } ;

IntCmd intdep372 = { 'RM DEP' , &rmdep372 } ;

Rm rmdep372 = { { OBJ_PATH+"/Signal.dep" } } ;

Target cpp373 = { "SimpleArray.cpp" , "../../Fundamental/CCore/src/./array/SimpleArray.cpp" } ;
Target ocpp373 = { "SimpleArray.o" , OBJ_PATH+"/SimpleArray.o" } ;
Rule rcpp373 = { {&cpp373} , {&ocpp373} , {&intdep373,&execpp373} } ;
Exe execpp373 = { "CC SimpleArray.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./array/SimpleArray.cpp"
 ,"-o"
 ,OBJ_PATH+"/SimpleArray.o"
} } ;

IntCmd intdep373 = { 'RM DEP' , &rmdep373 } ;

Rm rmdep373 = { { OBJ_PATH+"/SimpleArray.dep" } } ;

Target cpp374 = { "SimpleConsole.cpp" , "../../Applied/CCore/src/./video/SimpleConsole.cpp" } ;
Target ocpp374 = { "SimpleConsole.o" , OBJ_PATH+"/SimpleConsole.o" } ;
Rule rcpp374 = { {&cpp374} , {&ocpp374} , {&intdep374,&execpp374} } ;
Exe execpp374 = { "CC SimpleConsole.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./video/SimpleConsole.cpp"
 ,"-o"
 ,OBJ_PATH+"/SimpleConsole.o"
} } ;

IntCmd intdep374 = { 'RM DEP' , &rmdep374 } ;

Rm rmdep374 = { { OBJ_PATH+"/SimpleConsole.dep" } } ;

Target cpp375 = { "SimpleRotate.cpp" , "../../Fundamental/CCore/src/./algon/SimpleRotate.cpp" } ;
Target ocpp375 = { "SimpleRotate.o" , OBJ_PATH+"/SimpleRotate.o" } ;
Rule rcpp375 = { {&cpp375} , {&ocpp375} , {&intdep375,&execpp375} } ;
Exe execpp375 = { "CC SimpleRotate.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./algon/SimpleRotate.cpp"
 ,"-o"
 ,OBJ_PATH+"/SimpleRotate.o"
} } ;

IntCmd intdep375 = { 'RM DEP' , &rmdep375 } ;

Rm rmdep375 = { { OBJ_PATH+"/SimpleRotate.dep" } } ;

Target cpp376 = { "SingleBridge.cpp" , "../../Applied/CCore/src/./net/SingleBridge.cpp" } ;
Target ocpp376 = { "SingleBridge.o" , OBJ_PATH+"/SingleBridge.o" } ;
Rule rcpp376 = { {&cpp376} , {&ocpp376} , {&intdep376,&execpp376} } ;
Exe execpp376 = { "CC SingleBridge.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./net/SingleBridge.cpp"
 ,"-o"
 ,OBJ_PATH+"/SingleBridge.o"
} } ;

IntCmd intdep376 = { 'RM DEP' , &rmdep376 } ;

Rm rmdep376 = { { OBJ_PATH+"/SingleBridge.dep" } } ;

Target cpp377 = { "SingleEchoDevice.cpp" , "../../Applied/CCore/src/./net/SingleEchoDevice.cpp" } ;
Target ocpp377 = { "SingleEchoDevice.o" , OBJ_PATH+"/SingleEchoDevice.o" } ;
Rule rcpp377 = { {&cpp377} , {&ocpp377} , {&intdep377,&execpp377} } ;
Exe execpp377 = { "CC SingleEchoDevice.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./net/SingleEchoDevice.cpp"
 ,"-o"
 ,OBJ_PATH+"/SingleEchoDevice.o"
} } ;

IntCmd intdep377 = { 'RM DEP' , &rmdep377 } ;

Rm rmdep377 = { { OBJ_PATH+"/SingleEchoDevice.dep" } } ;

Target cpp378 = { "SingleHost.cpp" , "../../Fundamental/CCore/src/SingleHost.cpp" } ;
Target ocpp378 = { "SingleHost.o" , OBJ_PATH+"/SingleHost.o" } ;
Rule rcpp378 = { {&cpp378} , {&ocpp378} , {&intdep378,&execpp378} } ;
Exe execpp378 = { "CC SingleHost.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/SingleHost.cpp"
 ,"-o"
 ,OBJ_PATH+"/SingleHost.o"
} } ;

IntCmd intdep378 = { 'RM DEP' , &rmdep378 } ;

Rm rmdep378 = { { OBJ_PATH+"/SingleHost.dep" } } ;

Target cpp379 = { "SlowSem.cpp" , "../../HCore/CCore/src/./task/SlowSem.cpp" } ;
Target ocpp379 = { "SlowSem.o" , OBJ_PATH+"/SlowSem.o" } ;
Rule rcpp379 = { {&cpp379} , {&ocpp379} , {&intdep379,&execpp379} } ;
Exe execpp379 = { "CC SlowSem.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/./task/SlowSem.cpp"
 ,"-o"
 ,OBJ_PATH+"/SlowSem.o"
} } ;

IntCmd intdep379 = { 'RM DEP' , &rmdep379 } ;

Rm rmdep379 = { { OBJ_PATH+"/SlowSem.dep" } } ;

Target cpp380 = { "SmallPrimes.cpp" , "../../Applied/CCore/src/./math/SmallPrimes.cpp" } ;
Target ocpp380 = { "SmallPrimes.o" , OBJ_PATH+"/SmallPrimes.o" } ;
Rule rcpp380 = { {&cpp380} , {&ocpp380} , {&intdep380,&execpp380} } ;
Exe execpp380 = { "CC SmallPrimes.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./math/SmallPrimes.cpp"
 ,"-o"
 ,OBJ_PATH+"/SmallPrimes.o"
} } ;

IntCmd intdep380 = { 'RM DEP' , &rmdep380 } ;

Rm rmdep380 = { { OBJ_PATH+"/SmallPrimes.dep" } } ;

Target cpp381 = { "SmoothAlgo.cpp" , "../../Desktop/Draw/CCore/src/./video/SmoothAlgo.cpp" } ;
Target ocpp381 = { "SmoothAlgo.o" , OBJ_PATH+"/SmoothAlgo.o" } ;
Rule rcpp381 = { {&cpp381} , {&ocpp381} , {&intdep381,&execpp381} } ;
Exe execpp381 = { "CC SmoothAlgo.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Draw/CCore/src/./video/SmoothAlgo.cpp"
 ,"-o"
 ,OBJ_PATH+"/SmoothAlgo.o"
} } ;

IntCmd intdep381 = { 'RM DEP' , &rmdep381 } ;

Rm rmdep381 = { { OBJ_PATH+"/SmoothAlgo.dep" } } ;

Target cpp382 = { "SmoothDrawArt.cpp" , "../../Desktop/Draw/CCore/src/./video/SmoothDrawArt.cpp" } ;
Target ocpp382 = { "SmoothDrawArt.o" , OBJ_PATH+"/SmoothDrawArt.o" } ;
Rule rcpp382 = { {&cpp382} , {&ocpp382} , {&intdep382,&execpp382} } ;
Exe execpp382 = { "CC SmoothDrawArt.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Draw/CCore/src/./video/SmoothDrawArt.cpp"
 ,"-o"
 ,OBJ_PATH+"/SmoothDrawArt.o"
} } ;

IntCmd intdep382 = { 'RM DEP' , &rmdep382 } ;

Rm rmdep382 = { { OBJ_PATH+"/SmoothDrawArt.dep" } } ;

Target cpp383 = { "Sort.cpp" , "../../Fundamental/CCore/src/Sort.cpp" } ;
Target ocpp383 = { "Sort.o" , OBJ_PATH+"/Sort.o" } ;
Rule rcpp383 = { {&cpp383} , {&ocpp383} , {&intdep383,&execpp383} } ;
Exe execpp383 = { "CC Sort.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/Sort.cpp"
 ,"-o"
 ,OBJ_PATH+"/Sort.o"
} } ;

IntCmd intdep383 = { 'RM DEP' , &rmdep383 } ;

Rm rmdep383 = { { OBJ_PATH+"/Sort.dep" } } ;

Target cpp384 = { "SortUnique.cpp" , "../../Fundamental/CCore/src/./algon/SortUnique.cpp" } ;
Target ocpp384 = { "SortUnique.o" , OBJ_PATH+"/SortUnique.o" } ;
Rule rcpp384 = { {&cpp384} , {&ocpp384} , {&intdep384,&execpp384} } ;
Exe execpp384 = { "CC SortUnique.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./algon/SortUnique.cpp"
 ,"-o"
 ,OBJ_PATH+"/SortUnique.o"
} } ;

IntCmd intdep384 = { 'RM DEP' , &rmdep384 } ;

Rm rmdep384 = { { OBJ_PATH+"/SortUnique.dep" } } ;

Target cpp385 = { "Space.cpp" , "../../Simple/CCore/src/./gadget/Space.cpp" } ;
Target ocpp385 = { "Space.o" , OBJ_PATH+"/Space.o" } ;
Rule rcpp385 = { {&cpp385} , {&ocpp385} , {&intdep385,&execpp385} } ;
Exe execpp385 = { "CC Space.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/Space.cpp"
 ,"-o"
 ,OBJ_PATH+"/Space.o"
} } ;

IntCmd intdep385 = { 'RM DEP' , &rmdep385 } ;

Rm rmdep385 = { { OBJ_PATH+"/Space.dep" } } ;

Target cpp386 = { "SpanLenEngine.cpp" , "../../Desktop/Lib/CCore/src/./video/book/SpanLenEngine.cpp" } ;
Target ocpp386 = { "SpanLenEngine.o" , OBJ_PATH+"/SpanLenEngine.o" } ;
Rule rcpp386 = { {&cpp386} , {&ocpp386} , {&intdep386,&execpp386} } ;
Exe execpp386 = { "CC SpanLenEngine.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/book/SpanLenEngine.cpp"
 ,"-o"
 ,OBJ_PATH+"/SpanLenEngine.o"
} } ;

IntCmd intdep386 = { 'RM DEP' , &rmdep386 } ;

Rm rmdep386 = { { OBJ_PATH+"/SpanLenEngine.dep" } } ;

Target cpp387 = { "SpawnProcess.cpp" , "../../HCore/CCore/src/SpawnProcess.cpp" } ;
Target ocpp387 = { "SpawnProcess.o" , OBJ_PATH+"/SpawnProcess.o" } ;
Rule rcpp387 = { {&cpp387} , {&ocpp387} , {&intdep387,&execpp387} } ;
Exe execpp387 = { "CC SpawnProcess.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/SpawnProcess.cpp"
 ,"-o"
 ,OBJ_PATH+"/SpawnProcess.o"
} } ;

IntCmd intdep387 = { 'RM DEP' , &rmdep387 } ;

Rm rmdep387 = { { OBJ_PATH+"/SpawnProcess.dep" } } ;

Target cpp388 = { "StartStop.cpp" , "../../Simple/CCore/src/StartStop.cpp" } ;
Target ocpp388 = { "StartStop.o" , OBJ_PATH+"/StartStop.o" } ;
Rule rcpp388 = { {&cpp388} , {&ocpp388} , {&intdep388,&execpp388} } ;
Exe execpp388 = { "CC StartStop.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/StartStop.cpp"
 ,"-o"
 ,OBJ_PATH+"/StartStop.o"
} } ;

IntCmd intdep388 = { 'RM DEP' , &rmdep388 } ;

Rm rmdep388 = { { OBJ_PATH+"/StartStop.dep" } } ;

Target cpp389 = { "Starter.cpp" , "../../Fundamental/CCore/src/Starter.cpp" } ;
Target ocpp389 = { "Starter.o" , OBJ_PATH+"/Starter.o" } ;
Rule rcpp389 = { {&cpp389} , {&ocpp389} , {&intdep389,&execpp389} } ;
Exe execpp389 = { "CC Starter.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/Starter.cpp"
 ,"-o"
 ,OBJ_PATH+"/Starter.o"
} } ;

IntCmd intdep389 = { 'RM DEP' , &rmdep389 } ;

Rm rmdep389 = { { OBJ_PATH+"/Starter.dep" } } ;

Target cpp390 = { "StepEval.cpp" , "../../Fundamental/CCore/src/StepEval.cpp" } ;
Target ocpp390 = { "StepEval.o" , OBJ_PATH+"/StepEval.o" } ;
Rule rcpp390 = { {&cpp390} , {&ocpp390} , {&intdep390,&execpp390} } ;
Exe execpp390 = { "CC StepEval.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/StepEval.cpp"
 ,"-o"
 ,OBJ_PATH+"/StepEval.o"
} } ;

IntCmd intdep390 = { 'RM DEP' , &rmdep390 } ;

Rm rmdep390 = { { OBJ_PATH+"/StepEval.dep" } } ;

Target cpp391 = { "StrKey.cpp" , "../../Simple/CCore/src/StrKey.cpp" } ;
Target ocpp391 = { "StrKey.o" , OBJ_PATH+"/StrKey.o" } ;
Rule rcpp391 = { {&cpp391} , {&ocpp391} , {&intdep391,&execpp391} } ;
Exe execpp391 = { "CC StrKey.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/StrKey.cpp"
 ,"-o"
 ,OBJ_PATH+"/StrKey.o"
} } ;

IntCmd intdep391 = { 'RM DEP' , &rmdep391 } ;

Rm rmdep391 = { { OBJ_PATH+"/StrKey.dep" } } ;

Target cpp392 = { "StrMap.cpp" , "../../Fundamental/CCore/src/StrMap.cpp" } ;
Target ocpp392 = { "StrMap.o" , OBJ_PATH+"/StrMap.o" } ;
Rule rcpp392 = { {&cpp392} , {&ocpp392} , {&intdep392,&execpp392} } ;
Exe execpp392 = { "CC StrMap.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/StrMap.cpp"
 ,"-o"
 ,OBJ_PATH+"/StrMap.o"
} } ;

IntCmd intdep392 = { 'RM DEP' , &rmdep392 } ;

Rm rmdep392 = { { OBJ_PATH+"/StrMap.dep" } } ;

Target cpp393 = { "StrParse.cpp" , "../../Fundamental/CCore/src/StrParse.cpp" } ;
Target ocpp393 = { "StrParse.o" , OBJ_PATH+"/StrParse.o" } ;
Rule rcpp393 = { {&cpp393} , {&ocpp393} , {&intdep393,&execpp393} } ;
Exe execpp393 = { "CC StrParse.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/StrParse.cpp"
 ,"-o"
 ,OBJ_PATH+"/StrParse.o"
} } ;

IntCmd intdep393 = { 'RM DEP' , &rmdep393 } ;

Rm rmdep393 = { { OBJ_PATH+"/StrParse.dep" } } ;

Target cpp394 = { "StrPrint.cpp" , "../../Fundamental/CCore/src/./printf/StrPrint.cpp" } ;
Target ocpp394 = { "StrPrint.o" , OBJ_PATH+"/StrPrint.o" } ;
Rule rcpp394 = { {&cpp394} , {&ocpp394} , {&intdep394,&execpp394} } ;
Exe execpp394 = { "CC StrPrint.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./printf/StrPrint.cpp"
 ,"-o"
 ,OBJ_PATH+"/StrPrint.o"
} } ;

IntCmd intdep394 = { 'RM DEP' , &rmdep394 } ;

Rm rmdep394 = { { OBJ_PATH+"/StrPrint.dep" } } ;

Target cpp395 = { "StrToChar.cpp" , "../../Applied/CCore/src/StrToChar.cpp" } ;
Target ocpp395 = { "StrToChar.o" , OBJ_PATH+"/StrToChar.o" } ;
Rule rcpp395 = { {&cpp395} , {&ocpp395} , {&intdep395,&execpp395} } ;
Exe execpp395 = { "CC StrToChar.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/StrToChar.cpp"
 ,"-o"
 ,OBJ_PATH+"/StrToChar.o"
} } ;

IntCmd intdep395 = { 'RM DEP' , &rmdep395 } ;

Rm rmdep395 = { { OBJ_PATH+"/StrToChar.dep" } } ;

Target cpp396 = { "String.cpp" , "../../Fundamental/CCore/src/String.cpp" } ;
Target ocpp396 = { "String.o" , OBJ_PATH+"/String.o" } ;
Rule rcpp396 = { {&cpp396} , {&ocpp396} , {&intdep396,&execpp396} } ;
Exe execpp396 = { "CC String.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/String.cpp"
 ,"-o"
 ,OBJ_PATH+"/String.o"
} } ;

IntCmd intdep396 = { 'RM DEP' , &rmdep396 } ;

Rm rmdep396 = { { OBJ_PATH+"/String.dep" } } ;

Target cpp397 = { "StringScan.cpp" , "../../Fundamental/CCore/src/./scanf/StringScan.cpp" } ;
Target ocpp397 = { "StringScan.o" , OBJ_PATH+"/StringScan.o" } ;
Rule rcpp397 = { {&cpp397} , {&ocpp397} , {&intdep397,&execpp397} } ;
Exe execpp397 = { "CC StringScan.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./scanf/StringScan.cpp"
 ,"-o"
 ,OBJ_PATH+"/StringScan.o"
} } ;

IntCmd intdep397 = { 'RM DEP' , &rmdep397 } ;

Rm rmdep397 = { { OBJ_PATH+"/StringScan.dep" } } ;

Target cpp398 = { "SubWindow.cpp" , "../../Desktop/Core/CCore/src/./video/SubWindow.cpp" } ;
Target ocpp398 = { "SubWindow.o" , OBJ_PATH+"/SubWindow.o" } ;
Rule rcpp398 = { {&cpp398} , {&ocpp398} , {&intdep398,&execpp398} } ;
Exe execpp398 = { "CC SubWindow.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Core/CCore/src/./video/SubWindow.cpp"
 ,"-o"
 ,OBJ_PATH+"/SubWindow.o"
} } ;

IntCmd intdep398 = { 'RM DEP' , &rmdep398 } ;

Rm rmdep398 = { { OBJ_PATH+"/SubWindow.dep" } } ;

Target cpp399 = { "Swap.cpp" , "../../Simple/CCore/src/Swap.cpp" } ;
Target ocpp399 = { "Swap.o" , OBJ_PATH+"/Swap.o" } ;
Rule rcpp399 = { {&cpp399} , {&ocpp399} , {&intdep399,&execpp399} } ;
Exe execpp399 = { "CC Swap.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/Swap.cpp"
 ,"-o"
 ,OBJ_PATH+"/Swap.o"
} } ;

IntCmd intdep399 = { 'RM DEP' , &rmdep399 } ;

Rm rmdep399 = { { OBJ_PATH+"/Swap.dep" } } ;

Target cpp400 = { "SymCount.cpp" , "../../Simple/CCore/src/SymCount.cpp" } ;
Target ocpp400 = { "SymCount.o" , OBJ_PATH+"/SymCount.o" } ;
Rule rcpp400 = { {&cpp400} , {&ocpp400} , {&intdep400,&execpp400} } ;
Exe execpp400 = { "CC SymCount.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/SymCount.cpp"
 ,"-o"
 ,OBJ_PATH+"/SymCount.o"
} } ;

IntCmd intdep400 = { 'RM DEP' , &rmdep400 } ;

Rm rmdep400 = { { OBJ_PATH+"/SymCount.dep" } } ;

Target cpp401 = { "SymPart.cpp" , "../../Simple/CCore/src/SymPart.cpp" } ;
Target ocpp401 = { "SymPart.o" , OBJ_PATH+"/SymPart.o" } ;
Rule rcpp401 = { {&cpp401} , {&ocpp401} , {&intdep401,&execpp401} } ;
Exe execpp401 = { "CC SymPart.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/SymPart.cpp"
 ,"-o"
 ,OBJ_PATH+"/SymPart.o"
} } ;

IntCmd intdep401 = { 'RM DEP' , &rmdep401 } ;

Rm rmdep401 = { { OBJ_PATH+"/SymPart.dep" } } ;

Target cpp402 = { "Symbol.cpp" , "../../Simple/CCore/src/Symbol.cpp" } ;
Target ocpp402 = { "Symbol.o" , OBJ_PATH+"/Symbol.o" } ;
Rule rcpp402 = { {&cpp402} , {&ocpp402} , {&intdep402,&execpp402} } ;
Exe execpp402 = { "CC Symbol.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/Symbol.cpp"
 ,"-o"
 ,OBJ_PATH+"/Symbol.o"
} } ;

IntCmd intdep402 = { 'RM DEP' , &rmdep402 } ;

Rm rmdep402 = { { OBJ_PATH+"/Symbol.dep" } } ;

Target cpp403 = { "SysAbort.cpp" , "CCore/src/./sys/SysAbort.cpp" } ;
Target ocpp403 = { "SysAbort.o" , OBJ_PATH+"/SysAbort.o" } ;
Rule rcpp403 = { {&cpp403} , {&ocpp403} , {&intdep403,&execpp403} } ;
Exe execpp403 = { "CC SysAbort.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./sys/SysAbort.cpp"
 ,"-o"
 ,OBJ_PATH+"/SysAbort.o"
} } ;

IntCmd intdep403 = { 'RM DEP' , &rmdep403 } ;

Rm rmdep403 = { { OBJ_PATH+"/SysAbort.dep" } } ;

Target cpp404 = { "SysAsyncFile.cpp" , "../../Applied/CCore/src/./sys/SysAsyncFile.cpp" } ;
Target ocpp404 = { "SysAsyncFile.o" , OBJ_PATH+"/SysAsyncFile.o" } ;
Rule rcpp404 = { {&cpp404} , {&ocpp404} , {&intdep404,&execpp404} } ;
Exe execpp404 = { "CC SysAsyncFile.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./sys/SysAsyncFile.cpp"
 ,"-o"
 ,OBJ_PATH+"/SysAsyncFile.o"
} } ;

IntCmd intdep404 = { 'RM DEP' , &rmdep404 } ;

Rm rmdep404 = { { OBJ_PATH+"/SysAsyncFile.dep" } } ;

Target cpp405 = { "SysAsyncFileSystem.cpp" , "../../Applied/CCore/src/./sys/SysAsyncFileSystem.cpp" } ;
Target ocpp405 = { "SysAsyncFileSystem.o" , OBJ_PATH+"/SysAsyncFileSystem.o" } ;
Rule rcpp405 = { {&cpp405} , {&ocpp405} , {&intdep405,&execpp405} } ;
Exe execpp405 = { "CC SysAsyncFileSystem.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./sys/SysAsyncFileSystem.cpp"
 ,"-o"
 ,OBJ_PATH+"/SysAsyncFileSystem.o"
} } ;

IntCmd intdep405 = { 'RM DEP' , &rmdep405 } ;

Rm rmdep405 = { { OBJ_PATH+"/SysAsyncFileSystem.dep" } } ;

Target cpp406 = { "SysAtomic.cpp" , "CCore/src/./sys/SysAtomic.cpp" } ;
Target ocpp406 = { "SysAtomic.o" , OBJ_PATH+"/SysAtomic.o" } ;
Rule rcpp406 = { {&cpp406} , {&ocpp406} , {&intdep406,&execpp406} } ;
Exe execpp406 = { "CC SysAtomic.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./sys/SysAtomic.cpp"
 ,"-o"
 ,OBJ_PATH+"/SysAtomic.o"
} } ;

IntCmd intdep406 = { 'RM DEP' , &rmdep406 } ;

Rm rmdep406 = { { OBJ_PATH+"/SysAtomic.dep" } } ;

Target cpp407 = { "SysCon.cpp" , "CCore/src/./sys/SysCon.cpp" } ;
Target ocpp407 = { "SysCon.o" , OBJ_PATH+"/SysCon.o" } ;
Rule rcpp407 = { {&cpp407} , {&ocpp407} , {&intdep407,&execpp407} } ;
Exe execpp407 = { "CC SysCon.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./sys/SysCon.cpp"
 ,"-o"
 ,OBJ_PATH+"/SysCon.o"
} } ;

IntCmd intdep407 = { 'RM DEP' , &rmdep407 } ;

Rm rmdep407 = { { OBJ_PATH+"/SysCon.dep" } } ;

Target cpp408 = { "SysEnv.cpp" , "CCore/src/./sys/SysEnv.cpp" } ;
Target ocpp408 = { "SysEnv.o" , OBJ_PATH+"/SysEnv.o" } ;
Rule rcpp408 = { {&cpp408} , {&ocpp408} , {&intdep408,&execpp408} } ;
Exe execpp408 = { "CC SysEnv.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./sys/SysEnv.cpp"
 ,"-o"
 ,OBJ_PATH+"/SysEnv.o"
} } ;

IntCmd intdep408 = { 'RM DEP' , &rmdep408 } ;

Rm rmdep408 = { { OBJ_PATH+"/SysEnv.dep" } } ;

Target cpp409 = { "SysError.cpp" , "CCore/src/./sys/SysError.cpp" } ;
Target ocpp409 = { "SysError.o" , OBJ_PATH+"/SysError.o" } ;
Rule rcpp409 = { {&cpp409} , {&ocpp409} , {&intdep409,&execpp409} } ;
Exe execpp409 = { "CC SysError.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./sys/SysError.cpp"
 ,"-o"
 ,OBJ_PATH+"/SysError.o"
} } ;

IntCmd intdep409 = { 'RM DEP' , &rmdep409 } ;

Rm rmdep409 = { { OBJ_PATH+"/SysError.dep" } } ;

Target cpp410 = { "SysFile.cpp" , "CCore/src/./sys/SysFile.cpp" } ;
Target ocpp410 = { "SysFile.o" , OBJ_PATH+"/SysFile.o" } ;
Rule rcpp410 = { {&cpp410} , {&ocpp410} , {&intdep410,&execpp410} } ;
Exe execpp410 = { "CC SysFile.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./sys/SysFile.cpp"
 ,"-o"
 ,OBJ_PATH+"/SysFile.o"
} } ;

IntCmd intdep410 = { 'RM DEP' , &rmdep410 } ;

Rm rmdep410 = { { OBJ_PATH+"/SysFile.dep" } } ;

Target cpp411 = { "SysFileInternal.cpp" , "CCore/src/./sys/SysFileInternal.cpp" } ;
Target ocpp411 = { "SysFileInternal.o" , OBJ_PATH+"/SysFileInternal.o" } ;
Rule rcpp411 = { {&cpp411} , {&ocpp411} , {&intdep411,&execpp411} } ;
Exe execpp411 = { "CC SysFileInternal.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./sys/SysFileInternal.cpp"
 ,"-o"
 ,OBJ_PATH+"/SysFileInternal.o"
} } ;

IntCmd intdep411 = { 'RM DEP' , &rmdep411 } ;

Rm rmdep411 = { { OBJ_PATH+"/SysFileInternal.dep" } } ;

Target cpp412 = { "SysFileSystem.cpp" , "CCore/src/./sys/SysFileSystem.cpp" } ;
Target ocpp412 = { "SysFileSystem.o" , OBJ_PATH+"/SysFileSystem.o" } ;
Rule rcpp412 = { {&cpp412} , {&ocpp412} , {&intdep412,&execpp412} } ;
Exe execpp412 = { "CC SysFileSystem.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./sys/SysFileSystem.cpp"
 ,"-o"
 ,OBJ_PATH+"/SysFileSystem.o"
} } ;

IntCmd intdep412 = { 'RM DEP' , &rmdep412 } ;

Rm rmdep412 = { { OBJ_PATH+"/SysFileSystem.dep" } } ;

Target cpp413 = { "SysLaunchPath.cpp" , "CCore/src/./sys/SysLaunchPath.cpp" } ;
Target ocpp413 = { "SysLaunchPath.o" , OBJ_PATH+"/SysLaunchPath.o" } ;
Rule rcpp413 = { {&cpp413} , {&ocpp413} , {&intdep413,&execpp413} } ;
Exe execpp413 = { "CC SysLaunchPath.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./sys/SysLaunchPath.cpp"
 ,"-o"
 ,OBJ_PATH+"/SysLaunchPath.o"
} } ;

IntCmd intdep413 = { 'RM DEP' , &rmdep413 } ;

Rm rmdep413 = { { OBJ_PATH+"/SysLaunchPath.dep" } } ;

Target cpp414 = { "SysMemPage.cpp" , "CCore/src/./sys/SysMemPage.cpp" } ;
Target ocpp414 = { "SysMemPage.o" , OBJ_PATH+"/SysMemPage.o" } ;
Rule rcpp414 = { {&cpp414} , {&ocpp414} , {&intdep414,&execpp414} } ;
Exe execpp414 = { "CC SysMemPage.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./sys/SysMemPage.cpp"
 ,"-o"
 ,OBJ_PATH+"/SysMemPage.o"
} } ;

IntCmd intdep414 = { 'RM DEP' , &rmdep414 } ;

Rm rmdep414 = { { OBJ_PATH+"/SysMemPage.dep" } } ;

Target cpp415 = { "SysNet.cpp" , "CCore/src/./sys/SysNet.cpp" } ;
Target ocpp415 = { "SysNet.o" , OBJ_PATH+"/SysNet.o" } ;
Rule rcpp415 = { {&cpp415} , {&ocpp415} , {&intdep415,&execpp415} } ;
Exe execpp415 = { "CC SysNet.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./sys/SysNet.cpp"
 ,"-o"
 ,OBJ_PATH+"/SysNet.o"
} } ;

IntCmd intdep415 = { 'RM DEP' , &rmdep415 } ;

Rm rmdep415 = { { OBJ_PATH+"/SysNet.dep" } } ;

Target cpp416 = { "SysPlanInit.cpp" , "CCore/src/./sys/SysPlanInit.cpp" } ;
Target ocpp416 = { "SysPlanInit.o" , OBJ_PATH+"/SysPlanInit.o" } ;
Rule rcpp416 = { {&cpp416} , {&ocpp416} , {&intdep416,&execpp416} } ;
Exe execpp416 = { "CC SysPlanInit.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./sys/SysPlanInit.cpp"
 ,"-o"
 ,OBJ_PATH+"/SysPlanInit.o"
} } ;

IntCmd intdep416 = { 'RM DEP' , &rmdep416 } ;

Rm rmdep416 = { { OBJ_PATH+"/SysPlanInit.dep" } } ;

Target cpp417 = { "SysProp.cpp" , "CCore/src/./sys/SysProp.cpp" } ;
Target ocpp417 = { "SysProp.o" , OBJ_PATH+"/SysProp.o" } ;
Rule rcpp417 = { {&cpp417} , {&ocpp417} , {&intdep417,&execpp417} } ;
Exe execpp417 = { "CC SysProp.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./sys/SysProp.cpp"
 ,"-o"
 ,OBJ_PATH+"/SysProp.o"
} } ;

IntCmd intdep417 = { 'RM DEP' , &rmdep417 } ;

Rm rmdep417 = { { OBJ_PATH+"/SysProp.dep" } } ;

Target cpp418 = { "SysSem.cpp" , "CCore/src/./sys/SysSem.cpp" } ;
Target ocpp418 = { "SysSem.o" , OBJ_PATH+"/SysSem.o" } ;
Rule rcpp418 = { {&cpp418} , {&ocpp418} , {&intdep418,&execpp418} } ;
Exe execpp418 = { "CC SysSem.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./sys/SysSem.cpp"
 ,"-o"
 ,OBJ_PATH+"/SysSem.o"
} } ;

IntCmd intdep418 = { 'RM DEP' , &rmdep418 } ;

Rm rmdep418 = { { OBJ_PATH+"/SysSem.dep" } } ;

Target cpp419 = { "SysSpawn.cpp" , "CCore/src/./sys/SysSpawn.cpp" } ;
Target ocpp419 = { "SysSpawn.o" , OBJ_PATH+"/SysSpawn.o" } ;
Rule rcpp419 = { {&cpp419} , {&ocpp419} , {&intdep419,&execpp419} } ;
Exe execpp419 = { "CC SysSpawn.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./sys/SysSpawn.cpp"
 ,"-o"
 ,OBJ_PATH+"/SysSpawn.o"
} } ;

IntCmd intdep419 = { 'RM DEP' , &rmdep419 } ;

Rm rmdep419 = { { OBJ_PATH+"/SysSpawn.dep" } } ;

Target cpp420 = { "SysSpawnInternal.cpp" , "CCore/src/./sys/SysSpawnInternal.cpp" } ;
Target ocpp420 = { "SysSpawnInternal.o" , OBJ_PATH+"/SysSpawnInternal.o" } ;
Rule rcpp420 = { {&cpp420} , {&ocpp420} , {&intdep420,&execpp420} } ;
Exe execpp420 = { "CC SysSpawnInternal.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./sys/SysSpawnInternal.cpp"
 ,"-o"
 ,OBJ_PATH+"/SysSpawnInternal.o"
} } ;

IntCmd intdep420 = { 'RM DEP' , &rmdep420 } ;

Rm rmdep420 = { { OBJ_PATH+"/SysSpawnInternal.dep" } } ;

Target cpp421 = { "SysTask.cpp" , "CCore/src/./sys/SysTask.cpp" } ;
Target ocpp421 = { "SysTask.o" , OBJ_PATH+"/SysTask.o" } ;
Rule rcpp421 = { {&cpp421} , {&ocpp421} , {&intdep421,&execpp421} } ;
Exe execpp421 = { "CC SysTask.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./sys/SysTask.cpp"
 ,"-o"
 ,OBJ_PATH+"/SysTask.o"
} } ;

IntCmd intdep421 = { 'RM DEP' , &rmdep421 } ;

Rm rmdep421 = { { OBJ_PATH+"/SysTask.dep" } } ;

Target cpp422 = { "SysTime.cpp" , "CCore/src/./sys/SysTime.cpp" } ;
Target ocpp422 = { "SysTime.o" , OBJ_PATH+"/SysTime.o" } ;
Rule rcpp422 = { {&cpp422} , {&ocpp422} , {&intdep422,&execpp422} } ;
Exe execpp422 = { "CC SysTime.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./sys/SysTime.cpp"
 ,"-o"
 ,OBJ_PATH+"/SysTime.o"
} } ;

IntCmd intdep422 = { 'RM DEP' , &rmdep422 } ;

Rm rmdep422 = { { OBJ_PATH+"/SysTime.dep" } } ;

Target cpp423 = { "SysTlsSlot.cpp" , "CCore/src/./sys/SysTlsSlot.cpp" } ;
Target ocpp423 = { "SysTlsSlot.o" , OBJ_PATH+"/SysTlsSlot.o" } ;
Rule rcpp423 = { {&cpp423} , {&ocpp423} , {&intdep423,&execpp423} } ;
Exe execpp423 = { "CC SysTlsSlot.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./sys/SysTlsSlot.cpp"
 ,"-o"
 ,OBJ_PATH+"/SysTlsSlot.o"
} } ;

IntCmd intdep423 = { 'RM DEP' , &rmdep423 } ;

Rm rmdep423 = { { OBJ_PATH+"/SysTlsSlot.dep" } } ;

Target cpp424 = { "SysUtf8.cpp" , "CCore/src/./sys/SysUtf8.cpp" } ;
Target ocpp424 = { "SysUtf8.o" , OBJ_PATH+"/SysUtf8.o" } ;
Rule rcpp424 = { {&cpp424} , {&ocpp424} , {&intdep424,&execpp424} } ;
Exe execpp424 = { "CC SysUtf8.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./sys/SysUtf8.cpp"
 ,"-o"
 ,OBJ_PATH+"/SysUtf8.o"
} } ;

IntCmd intdep424 = { 'RM DEP' , &rmdep424 } ;

Rm rmdep424 = { { OBJ_PATH+"/SysUtf8.dep" } } ;

Target cpp425 = { "SysWait.cpp" , "CCore/src/./sys/SysWait.cpp" } ;
Target ocpp425 = { "SysWait.o" , OBJ_PATH+"/SysWait.o" } ;
Rule rcpp425 = { {&cpp425} , {&ocpp425} , {&intdep425,&execpp425} } ;
Exe execpp425 = { "CC SysWait.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./sys/SysWait.cpp"
 ,"-o"
 ,OBJ_PATH+"/SysWait.o"
} } ;

IntCmd intdep425 = { 'RM DEP' , &rmdep425 } ;

Rm rmdep425 = { { OBJ_PATH+"/SysWait.dep" } } ;

Target cpp426 = { "SysWaitInternal.cpp" , "CCore/src/./sys/SysWaitInternal.cpp" } ;
Target ocpp426 = { "SysWaitInternal.o" , OBJ_PATH+"/SysWaitInternal.o" } ;
Rule rcpp426 = { {&cpp426} , {&ocpp426} , {&intdep426,&execpp426} } ;
Exe execpp426 = { "CC SysWaitInternal.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"CCore/src/./sys/SysWaitInternal.cpp"
 ,"-o"
 ,OBJ_PATH+"/SysWaitInternal.o"
} } ;

IntCmd intdep426 = { 'RM DEP' , &rmdep426 } ;

Rm rmdep426 = { { OBJ_PATH+"/SysWaitInternal.dep" } } ;

Target cpp427 = { "Task.cpp" , "../../HCore/CCore/src/Task.cpp" } ;
Target ocpp427 = { "Task.o" , OBJ_PATH+"/Task.o" } ;
Rule rcpp427 = { {&cpp427} , {&ocpp427} , {&intdep427,&execpp427} } ;
Exe execpp427 = { "CC Task.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/Task.cpp"
 ,"-o"
 ,OBJ_PATH+"/Task.o"
} } ;

IntCmd intdep427 = { 'RM DEP' , &rmdep427 } ;

Rm rmdep427 = { { OBJ_PATH+"/Task.dep" } } ;

Target cpp428 = { "TaskCore.cpp" , "../../HCore/CCore/src/./task/TaskCore.cpp" } ;
Target ocpp428 = { "TaskCore.o" , OBJ_PATH+"/TaskCore.o" } ;
Rule rcpp428 = { {&cpp428} , {&ocpp428} , {&intdep428,&execpp428} } ;
Exe execpp428 = { "CC TaskCore.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/./task/TaskCore.cpp"
 ,"-o"
 ,OBJ_PATH+"/TaskCore.o"
} } ;

IntCmd intdep428 = { 'RM DEP' , &rmdep428 } ;

Rm rmdep428 = { { OBJ_PATH+"/TaskCore.dep" } } ;

Target cpp429 = { "TaskEvent.cpp" , "../../HCore/CCore/src/./task/TaskEvent.cpp" } ;
Target ocpp429 = { "TaskEvent.o" , OBJ_PATH+"/TaskEvent.o" } ;
Rule rcpp429 = { {&cpp429} , {&ocpp429} , {&intdep429,&execpp429} } ;
Exe execpp429 = { "CC TaskEvent.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/./task/TaskEvent.cpp"
 ,"-o"
 ,OBJ_PATH+"/TaskEvent.o"
} } ;

IntCmd intdep429 = { 'RM DEP' , &rmdep429 } ;

Rm rmdep429 = { { OBJ_PATH+"/TaskEvent.dep" } } ;

Target cpp430 = { "TaskHeap.cpp" , "../../HCore/CCore/src/TaskHeap.cpp" } ;
Target ocpp430 = { "TaskHeap.o" , OBJ_PATH+"/TaskHeap.o" } ;
Rule rcpp430 = { {&cpp430} , {&ocpp430} , {&intdep430,&execpp430} } ;
Exe execpp430 = { "CC TaskHeap.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/TaskHeap.cpp"
 ,"-o"
 ,OBJ_PATH+"/TaskHeap.o"
} } ;

IntCmd intdep430 = { 'RM DEP' , &rmdep430 } ;

Rm rmdep430 = { { OBJ_PATH+"/TaskHeap.dep" } } ;

Target cpp431 = { "TaskMemStack.cpp" , "../../Applied/CCore/src/TaskMemStack.cpp" } ;
Target ocpp431 = { "TaskMemStack.o" , OBJ_PATH+"/TaskMemStack.o" } ;
Rule rcpp431 = { {&cpp431} , {&ocpp431} , {&intdep431,&execpp431} } ;
Exe execpp431 = { "CC TaskMemStack.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/TaskMemStack.cpp"
 ,"-o"
 ,OBJ_PATH+"/TaskMemStack.o"
} } ;

IntCmd intdep431 = { 'RM DEP' , &rmdep431 } ;

Rm rmdep431 = { { OBJ_PATH+"/TaskMemStack.dep" } } ;

Target cpp432 = { "TempArray.cpp" , "../../Fundamental/CCore/src/./array/TempArray.cpp" } ;
Target ocpp432 = { "TempArray.o" , OBJ_PATH+"/TempArray.o" } ;
Rule rcpp432 = { {&cpp432} , {&ocpp432} , {&intdep432,&execpp432} } ;
Exe execpp432 = { "CC TempArray.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./array/TempArray.cpp"
 ,"-o"
 ,OBJ_PATH+"/TempArray.o"
} } ;

IntCmd intdep432 = { 'RM DEP' , &rmdep432 } ;

Rm rmdep432 = { { OBJ_PATH+"/TempArray.dep" } } ;

Target cpp433 = { "TextLabel.cpp" , "../../Simple/CCore/src/TextLabel.cpp" } ;
Target ocpp433 = { "TextLabel.o" , OBJ_PATH+"/TextLabel.o" } ;
Rule rcpp433 = { {&cpp433} , {&ocpp433} , {&intdep433,&execpp433} } ;
Exe execpp433 = { "CC TextLabel.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/TextLabel.cpp"
 ,"-o"
 ,OBJ_PATH+"/TextLabel.o"
} } ;

IntCmd intdep433 = { 'RM DEP' , &rmdep433 } ;

Rm rmdep433 = { { OBJ_PATH+"/TextLabel.dep" } } ;

Target cpp434 = { "TextTools.cpp" , "../../Fundamental/CCore/src/TextTools.cpp" } ;
Target ocpp434 = { "TextTools.o" , OBJ_PATH+"/TextTools.o" } ;
Rule rcpp434 = { {&cpp434} , {&ocpp434} , {&intdep434,&execpp434} } ;
Exe execpp434 = { "CC TextTools.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/TextTools.cpp"
 ,"-o"
 ,OBJ_PATH+"/TextTools.o"
} } ;

IntCmd intdep434 = { 'RM DEP' , &rmdep434 } ;

Rm rmdep434 = { { OBJ_PATH+"/TextTools.dep" } } ;

Target cpp435 = { "TimeScope.cpp" , "../../Simple/CCore/src/TimeScope.cpp" } ;
Target ocpp435 = { "TimeScope.o" , OBJ_PATH+"/TimeScope.o" } ;
Rule rcpp435 = { {&cpp435} , {&ocpp435} , {&intdep435,&execpp435} } ;
Exe execpp435 = { "CC TimeScope.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/TimeScope.cpp"
 ,"-o"
 ,OBJ_PATH+"/TimeScope.o"
} } ;

IntCmd intdep435 = { 'RM DEP' , &rmdep435 } ;

Rm rmdep435 = { { OBJ_PATH+"/TimeScope.dep" } } ;

Target cpp436 = { "Timer.cpp" , "../../Simple/CCore/src/Timer.cpp" } ;
Target ocpp436 = { "Timer.o" , OBJ_PATH+"/Timer.o" } ;
Rule rcpp436 = { {&cpp436} , {&ocpp436} , {&intdep436,&execpp436} } ;
Exe execpp436 = { "CC Timer.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/Timer.cpp"
 ,"-o"
 ,OBJ_PATH+"/Timer.o"
} } ;

IntCmd intdep436 = { 'RM DEP' , &rmdep436 } ;

Rm rmdep436 = { { OBJ_PATH+"/Timer.dep" } } ;

Target cpp437 = { "TlsSlot.cpp" , "../../Simple/CCore/src/TlsSlot.cpp" } ;
Target ocpp437 = { "TlsSlot.o" , OBJ_PATH+"/TlsSlot.o" } ;
Rule rcpp437 = { {&cpp437} , {&ocpp437} , {&intdep437,&execpp437} } ;
Exe execpp437 = { "CC TlsSlot.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/TlsSlot.cpp"
 ,"-o"
 ,OBJ_PATH+"/TlsSlot.o"
} } ;

IntCmd intdep437 = { 'RM DEP' , &rmdep437 } ;

Rm rmdep437 = { { OBJ_PATH+"/TlsSlot.dep" } } ;

Target cpp438 = { "ToMemBase.cpp" , "../../Applied/CCore/src/ToMemBase.cpp" } ;
Target ocpp438 = { "ToMemBase.o" , OBJ_PATH+"/ToMemBase.o" } ;
Rule rcpp438 = { {&cpp438} , {&ocpp438} , {&intdep438,&execpp438} } ;
Exe execpp438 = { "CC ToMemBase.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/ToMemBase.cpp"
 ,"-o"
 ,OBJ_PATH+"/ToMemBase.o"
} } ;

IntCmd intdep438 = { 'RM DEP' , &rmdep438 } ;

Rm rmdep438 = { { OBJ_PATH+"/ToMemBase.dep" } } ;

Target cpp439 = { "ToMoveCtor.cpp" , "../../Simple/CCore/src/ToMoveCtor.cpp" } ;
Target ocpp439 = { "ToMoveCtor.o" , OBJ_PATH+"/ToMoveCtor.o" } ;
Rule rcpp439 = { {&cpp439} , {&ocpp439} , {&intdep439,&execpp439} } ;
Exe execpp439 = { "CC ToMoveCtor.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/ToMoveCtor.cpp"
 ,"-o"
 ,OBJ_PATH+"/ToMoveCtor.o"
} } ;

IntCmd intdep439 = { 'RM DEP' , &rmdep439 } ;

Rm rmdep439 = { { OBJ_PATH+"/ToMoveCtor.dep" } } ;

Target cpp440 = { "ToolFrame.cpp" , "../../Desktop/Lib/CCore/src/./video/ToolFrame.cpp" } ;
Target ocpp440 = { "ToolFrame.o" , OBJ_PATH+"/ToolFrame.o" } ;
Rule rcpp440 = { {&cpp440} , {&ocpp440} , {&intdep440,&execpp440} } ;
Exe execpp440 = { "CC ToolFrame.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/ToolFrame.cpp"
 ,"-o"
 ,OBJ_PATH+"/ToolFrame.o"
} } ;

IntCmd intdep440 = { 'RM DEP' , &rmdep440 } ;

Rm rmdep440 = { { OBJ_PATH+"/ToolFrame.dep" } } ;

Target cpp441 = { "Tree.cpp" , "../../Fundamental/CCore/src/Tree.cpp" } ;
Target ocpp441 = { "Tree.o" , OBJ_PATH+"/Tree.o" } ;
Rule rcpp441 = { {&cpp441} , {&ocpp441} , {&intdep441,&execpp441} } ;
Exe execpp441 = { "CC Tree.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/Tree.cpp"
 ,"-o"
 ,OBJ_PATH+"/Tree.o"
} } ;

IntCmd intdep441 = { 'RM DEP' , &rmdep441 } ;

Rm rmdep441 = { { OBJ_PATH+"/Tree.dep" } } ;

Target cpp442 = { "TreeBase.cpp" , "../../Fundamental/CCore/src/./tree/TreeBase.cpp" } ;
Target ocpp442 = { "TreeBase.o" , OBJ_PATH+"/TreeBase.o" } ;
Rule rcpp442 = { {&cpp442} , {&ocpp442} , {&intdep442,&execpp442} } ;
Exe execpp442 = { "CC TreeBase.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./tree/TreeBase.cpp"
 ,"-o"
 ,OBJ_PATH+"/TreeBase.o"
} } ;

IntCmd intdep442 = { 'RM DEP' , &rmdep442 } ;

Rm rmdep442 = { { OBJ_PATH+"/TreeBase.dep" } } ;

Target cpp443 = { "TreeLink.cpp" , "../../Fundamental/CCore/src/./tree/TreeLink.cpp" } ;
Target ocpp443 = { "TreeLink.o" , OBJ_PATH+"/TreeLink.o" } ;
Rule rcpp443 = { {&cpp443} , {&ocpp443} , {&intdep443,&execpp443} } ;
Exe execpp443 = { "CC TreeLink.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./tree/TreeLink.cpp"
 ,"-o"
 ,OBJ_PATH+"/TreeLink.o"
} } ;

IntCmd intdep443 = { 'RM DEP' , &rmdep443 } ;

Rm rmdep443 = { { OBJ_PATH+"/TreeLink.dep" } } ;

Target cpp444 = { "TreeMap.cpp" , "../../Fundamental/CCore/src/TreeMap.cpp" } ;
Target ocpp444 = { "TreeMap.o" , OBJ_PATH+"/TreeMap.o" } ;
Rule rcpp444 = { {&cpp444} , {&ocpp444} , {&intdep444,&execpp444} } ;
Exe execpp444 = { "CC TreeMap.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/TreeMap.cpp"
 ,"-o"
 ,OBJ_PATH+"/TreeMap.o"
} } ;

IntCmd intdep444 = { 'RM DEP' , &rmdep444 } ;

Rm rmdep444 = { { OBJ_PATH+"/TreeMap.dep" } } ;

Target cpp445 = { "TreeUpLink.cpp" , "../../Fundamental/CCore/src/./tree/TreeUpLink.cpp" } ;
Target ocpp445 = { "TreeUpLink.o" , OBJ_PATH+"/TreeUpLink.o" } ;
Rule rcpp445 = { {&cpp445} , {&ocpp445} , {&intdep445,&execpp445} } ;
Exe execpp445 = { "CC TreeUpLink.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./tree/TreeUpLink.cpp"
 ,"-o"
 ,OBJ_PATH+"/TreeUpLink.o"
} } ;

IntCmd intdep445 = { 'RM DEP' , &rmdep445 } ;

Rm rmdep445 = { { OBJ_PATH+"/TreeUpLink.dep" } } ;

Target cpp446 = { "Tuple.cpp" , "../../Simple/CCore/src/Tuple.cpp" } ;
Target ocpp446 = { "Tuple.o" , OBJ_PATH+"/Tuple.o" } ;
Rule rcpp446 = { {&cpp446} , {&ocpp446} , {&intdep446,&execpp446} } ;
Exe execpp446 = { "CC Tuple.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/Tuple.cpp"
 ,"-o"
 ,OBJ_PATH+"/Tuple.o"
} } ;

IntCmd intdep446 = { 'RM DEP' , &rmdep446 } ;

Rm rmdep446 = { { OBJ_PATH+"/Tuple.dep" } } ;

Target cpp447 = { "TypeNumber.cpp" , "../../Fundamental/CCore/src/TypeNumber.cpp" } ;
Target ocpp447 = { "TypeNumber.o" , OBJ_PATH+"/TypeNumber.o" } ;
Rule rcpp447 = { {&cpp447} , {&ocpp447} , {&intdep447,&execpp447} } ;
Exe execpp447 = { "CC TypeNumber.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/TypeNumber.cpp"
 ,"-o"
 ,OBJ_PATH+"/TypeNumber.o"
} } ;

IntCmd intdep447 = { 'RM DEP' , &rmdep447 } ;

Rm rmdep447 = { { OBJ_PATH+"/TypeNumber.dep" } } ;

Target cpp448 = { "TypeSwitch.cpp" , "../../Simple/CCore/src/TypeSwitch.cpp" } ;
Target ocpp448 = { "TypeSwitch.o" , OBJ_PATH+"/TypeSwitch.o" } ;
Rule rcpp448 = { {&cpp448} , {&ocpp448} , {&intdep448,&execpp448} } ;
Exe execpp448 = { "CC TypeSwitch.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/TypeSwitch.cpp"
 ,"-o"
 ,OBJ_PATH+"/TypeSwitch.o"
} } ;

IntCmd intdep448 = { 'RM DEP' , &rmdep448 } ;

Rm rmdep448 = { { OBJ_PATH+"/TypeSwitch.dep" } } ;

Target cpp449 = { "UDPDevice.cpp" , "../../HCore/CCore/src/./net/UDPDevice.cpp" } ;
Target ocpp449 = { "UDPDevice.o" , OBJ_PATH+"/UDPDevice.o" } ;
Rule rcpp449 = { {&cpp449} , {&ocpp449} , {&intdep449,&execpp449} } ;
Exe execpp449 = { "CC UDPDevice.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../HCore/CCore/src/./net/UDPDevice.cpp"
 ,"-o"
 ,OBJ_PATH+"/UDPDevice.o"
} } ;

IntCmd intdep449 = { 'RM DEP' , &rmdep449 } ;

Rm rmdep449 = { { OBJ_PATH+"/UDPDevice.dep" } } ;

Target cpp450 = { "UDPoint.cpp" , "../../Applied/CCore/src/./net/UDPoint.cpp" } ;
Target ocpp450 = { "UDPoint.o" , OBJ_PATH+"/UDPoint.o" } ;
Rule rcpp450 = { {&cpp450} , {&ocpp450} , {&intdep450,&execpp450} } ;
Exe execpp450 = { "CC UDPoint.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./net/UDPoint.cpp"
 ,"-o"
 ,OBJ_PATH+"/UDPoint.o"
} } ;

IntCmd intdep450 = { 'RM DEP' , &rmdep450 } ;

Rm rmdep450 = { { OBJ_PATH+"/UDPoint.dep" } } ;

Target cpp451 = { "UIntFunc.cpp" , "../../Simple/CCore/src/./gadget/UIntFunc.cpp" } ;
Target ocpp451 = { "UIntFunc.o" , OBJ_PATH+"/UIntFunc.o" } ;
Rule rcpp451 = { {&cpp451} , {&ocpp451} , {&intdep451,&execpp451} } ;
Exe execpp451 = { "CC UIntFunc.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/UIntFunc.cpp"
 ,"-o"
 ,OBJ_PATH+"/UIntFunc.o"
} } ;

IntCmd intdep451 = { 'RM DEP' , &rmdep451 } ;

Rm rmdep451 = { { OBJ_PATH+"/UIntFunc.dep" } } ;

Target cpp452 = { "UIntSat.cpp" , "../../Simple/CCore/src/./gadget/UIntSat.cpp" } ;
Target ocpp452 = { "UIntSat.o" , OBJ_PATH+"/UIntSat.o" } ;
Rule rcpp452 = { {&cpp452} , {&ocpp452} , {&intdep452,&execpp452} } ;
Exe execpp452 = { "CC UIntSat.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/UIntSat.cpp"
 ,"-o"
 ,OBJ_PATH+"/UIntSat.o"
} } ;

IntCmd intdep452 = { 'RM DEP' , &rmdep452 } ;

Rm rmdep452 = { { OBJ_PATH+"/UIntSat.dep" } } ;

Target cpp453 = { "UIntSlowMulAlgo.cpp" , "../../Fundamental/CCore/src/./math/UIntSlowMulAlgo.cpp" } ;
Target ocpp453 = { "UIntSlowMulAlgo.o" , OBJ_PATH+"/UIntSlowMulAlgo.o" } ;
Rule rcpp453 = { {&cpp453} , {&ocpp453} , {&intdep453,&execpp453} } ;
Exe execpp453 = { "CC UIntSlowMulAlgo.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/./math/UIntSlowMulAlgo.cpp"
 ,"-o"
 ,OBJ_PATH+"/UIntSlowMulAlgo.o"
} } ;

IntCmd intdep453 = { 'RM DEP' , &rmdep453 } ;

Rm rmdep453 = { { OBJ_PATH+"/UIntSlowMulAlgo.dep" } } ;

Target cpp454 = { "UIntSplit.cpp" , "../../Simple/CCore/src/UIntSplit.cpp" } ;
Target ocpp454 = { "UIntSplit.o" , OBJ_PATH+"/UIntSplit.o" } ;
Rule rcpp454 = { {&cpp454} , {&ocpp454} , {&intdep454,&execpp454} } ;
Exe execpp454 = { "CC UIntSplit.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/UIntSplit.cpp"
 ,"-o"
 ,OBJ_PATH+"/UIntSplit.o"
} } ;

IntCmd intdep454 = { 'RM DEP' , &rmdep454 } ;

Rm rmdep454 = { { OBJ_PATH+"/UIntSplit.dep" } } ;

Target cpp455 = { "Unid.cpp" , "../../Fundamental/CCore/src/Unid.cpp" } ;
Target ocpp455 = { "Unid.o" , OBJ_PATH+"/Unid.o" } ;
Rule rcpp455 = { {&cpp455} , {&ocpp455} , {&intdep455,&execpp455} } ;
Exe execpp455 = { "CC Unid.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/Unid.cpp"
 ,"-o"
 ,OBJ_PATH+"/Unid.o"
} } ;

IntCmd intdep455 = { 'RM DEP' , &rmdep455 } ;

Rm rmdep455 = { { OBJ_PATH+"/Unid.dep" } } ;

Target cpp456 = { "UserAction.cpp" , "../../Desktop/Core/CCore/src/./video/UserAction.cpp" } ;
Target ocpp456 = { "UserAction.o" , OBJ_PATH+"/UserAction.o" } ;
Rule rcpp456 = { {&cpp456} , {&ocpp456} , {&intdep456,&execpp456} } ;
Exe execpp456 = { "CC UserAction.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Core/CCore/src/./video/UserAction.cpp"
 ,"-o"
 ,OBJ_PATH+"/UserAction.o"
} } ;

IntCmd intdep456 = { 'RM DEP' , &rmdep456 } ;

Rm rmdep456 = { { OBJ_PATH+"/UserAction.dep" } } ;

Target cpp457 = { "UserPreference.cpp" , "../../Desktop/Lib/CCore/src/./video/UserPreference.cpp" } ;
Target ocpp457 = { "UserPreference.o" , OBJ_PATH+"/UserPreference.o" } ;
Rule rcpp457 = { {&cpp457} , {&ocpp457} , {&intdep457,&execpp457} } ;
Exe execpp457 = { "CC UserPreference.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/UserPreference.cpp"
 ,"-o"
 ,OBJ_PATH+"/UserPreference.o"
} } ;

IntCmd intdep457 = { 'RM DEP' , &rmdep457 } ;

Rm rmdep457 = { { OBJ_PATH+"/UserPreference.dep" } } ;

Target cpp458 = { "Utf8.cpp" , "../../Simple/CCore/src/Utf8.cpp" } ;
Target ocpp458 = { "Utf8.o" , OBJ_PATH+"/Utf8.o" } ;
Rule rcpp458 = { {&cpp458} , {&ocpp458} , {&intdep458,&execpp458} } ;
Exe execpp458 = { "CC Utf8.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/Utf8.cpp"
 ,"-o"
 ,OBJ_PATH+"/Utf8.o"
} } ;

IntCmd intdep458 = { 'RM DEP' , &rmdep458 } ;

Rm rmdep458 = { { OBJ_PATH+"/Utf8.dep" } } ;

Target cpp459 = { "UtilFunc.cpp" , "../../Simple/CCore/src/./gadget/UtilFunc.cpp" } ;
Target ocpp459 = { "UtilFunc.o" , OBJ_PATH+"/UtilFunc.o" } ;
Rule rcpp459 = { {&cpp459} , {&ocpp459} , {&intdep459,&execpp459} } ;
Exe execpp459 = { "CC UtilFunc.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Simple/CCore/src/./gadget/UtilFunc.cpp"
 ,"-o"
 ,OBJ_PATH+"/UtilFunc.o"
} } ;

IntCmd intdep459 = { 'RM DEP' , &rmdep459 } ;

Rm rmdep459 = { { OBJ_PATH+"/UtilFunc.dep" } } ;

Target cpp460 = { "VideoConsole.cpp" , "../../Applied/CCore/src/./video/VideoConsole.cpp" } ;
Target ocpp460 = { "VideoConsole.o" , OBJ_PATH+"/VideoConsole.o" } ;
Rule rcpp460 = { {&cpp460} , {&ocpp460} , {&intdep460,&execpp460} } ;
Exe execpp460 = { "CC VideoConsole.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./video/VideoConsole.cpp"
 ,"-o"
 ,OBJ_PATH+"/VideoConsole.o"
} } ;

IntCmd intdep460 = { 'RM DEP' , &rmdep460 } ;

Rm rmdep460 = { { OBJ_PATH+"/VideoConsole.dep" } } ;

Target cpp461 = { "VideoDevice.cpp" , "../../Applied/CCore/src/./video/VideoDevice.cpp" } ;
Target ocpp461 = { "VideoDevice.o" , OBJ_PATH+"/VideoDevice.o" } ;
Rule rcpp461 = { {&cpp461} , {&ocpp461} , {&intdep461,&execpp461} } ;
Exe execpp461 = { "CC VideoDevice.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./video/VideoDevice.cpp"
 ,"-o"
 ,OBJ_PATH+"/VideoDevice.o"
} } ;

IntCmd intdep461 = { 'RM DEP' , &rmdep461 } ;

Rm rmdep461 = { { OBJ_PATH+"/VideoDevice.dep" } } ;

Target cpp462 = { "Volume.cpp" , "../../Fundamental/CCore/src/Volume.cpp" } ;
Target ocpp462 = { "Volume.o" , OBJ_PATH+"/Volume.o" } ;
Rule rcpp462 = { {&cpp462} , {&ocpp462} , {&intdep462,&execpp462} } ;
Exe execpp462 = { "CC Volume.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Fundamental/CCore/src/Volume.cpp"
 ,"-o"
 ,OBJ_PATH+"/Volume.o"
} } ;

IntCmd intdep462 = { 'RM DEP' , &rmdep462 } ;

Rm rmdep462 = { { OBJ_PATH+"/Volume.dep" } } ;

Target cpp463 = { "Window.Blank.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.Blank.cpp" } ;
Target ocpp463 = { "Window.Blank.o" , OBJ_PATH+"/Window.Blank.o" } ;
Rule rcpp463 = { {&cpp463} , {&ocpp463} , {&intdep463,&execpp463} } ;
Exe execpp463 = { "CC Window.Blank.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.Blank.cpp"
 ,"-o"
 ,OBJ_PATH+"/Window.Blank.o"
} } ;

IntCmd intdep463 = { 'RM DEP' , &rmdep463 } ;

Rm rmdep463 = { { OBJ_PATH+"/Window.Blank.dep" } } ;

Target cpp464 = { "Window.Button.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.Button.cpp" } ;
Target ocpp464 = { "Window.Button.o" , OBJ_PATH+"/Window.Button.o" } ;
Rule rcpp464 = { {&cpp464} , {&ocpp464} , {&intdep464,&execpp464} } ;
Exe execpp464 = { "CC Window.Button.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.Button.cpp"
 ,"-o"
 ,OBJ_PATH+"/Window.Button.o"
} } ;

IntCmd intdep464 = { 'RM DEP' , &rmdep464 } ;

Rm rmdep464 = { { OBJ_PATH+"/Window.Button.dep" } } ;

Target cpp465 = { "Window.Check.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.Check.cpp" } ;
Target ocpp465 = { "Window.Check.o" , OBJ_PATH+"/Window.Check.o" } ;
Rule rcpp465 = { {&cpp465} , {&ocpp465} , {&intdep465,&execpp465} } ;
Exe execpp465 = { "CC Window.Check.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.Check.cpp"
 ,"-o"
 ,OBJ_PATH+"/Window.Check.o"
} } ;

IntCmd intdep465 = { 'RM DEP' , &rmdep465 } ;

Rm rmdep465 = { { OBJ_PATH+"/Window.Check.dep" } } ;

Target cpp466 = { "Window.Decor.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.Decor.cpp" } ;
Target ocpp466 = { "Window.Decor.o" , OBJ_PATH+"/Window.Decor.o" } ;
Rule rcpp466 = { {&cpp466} , {&ocpp466} , {&intdep466,&execpp466} } ;
Exe execpp466 = { "CC Window.Decor.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.Decor.cpp"
 ,"-o"
 ,OBJ_PATH+"/Window.Decor.o"
} } ;

IntCmd intdep466 = { 'RM DEP' , &rmdep466 } ;

Rm rmdep466 = { { OBJ_PATH+"/Window.Decor.dep" } } ;

Target cpp467 = { "Window.DragFrame.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.DragFrame.cpp" } ;
Target ocpp467 = { "Window.DragFrame.o" , OBJ_PATH+"/Window.DragFrame.o" } ;
Rule rcpp467 = { {&cpp467} , {&ocpp467} , {&intdep467,&execpp467} } ;
Exe execpp467 = { "CC Window.DragFrame.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.DragFrame.cpp"
 ,"-o"
 ,OBJ_PATH+"/Window.DragFrame.o"
} } ;

IntCmd intdep467 = { 'RM DEP' , &rmdep467 } ;

Rm rmdep467 = { { OBJ_PATH+"/Window.DragFrame.dep" } } ;

Target cpp468 = { "Window.FireButton.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.FireButton.cpp" } ;
Target ocpp468 = { "Window.FireButton.o" , OBJ_PATH+"/Window.FireButton.o" } ;
Rule rcpp468 = { {&cpp468} , {&ocpp468} , {&intdep468,&execpp468} } ;
Exe execpp468 = { "CC Window.FireButton.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.FireButton.cpp"
 ,"-o"
 ,OBJ_PATH+"/Window.FireButton.o"
} } ;

IntCmd intdep468 = { 'RM DEP' , &rmdep468 } ;

Rm rmdep468 = { { OBJ_PATH+"/Window.FireButton.dep" } } ;

Target cpp469 = { "Window.Info.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.Info.cpp" } ;
Target ocpp469 = { "Window.Info.o" , OBJ_PATH+"/Window.Info.o" } ;
Rule rcpp469 = { {&cpp469} , {&ocpp469} , {&intdep469,&execpp469} } ;
Exe execpp469 = { "CC Window.Info.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.Info.cpp"
 ,"-o"
 ,OBJ_PATH+"/Window.Info.o"
} } ;

IntCmd intdep469 = { 'RM DEP' , &rmdep469 } ;

Rm rmdep469 = { { OBJ_PATH+"/Window.Info.dep" } } ;

Target cpp470 = { "Window.Light.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.Light.cpp" } ;
Target ocpp470 = { "Window.Light.o" , OBJ_PATH+"/Window.Light.o" } ;
Rule rcpp470 = { {&cpp470} , {&ocpp470} , {&intdep470,&execpp470} } ;
Exe execpp470 = { "CC Window.Light.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.Light.cpp"
 ,"-o"
 ,OBJ_PATH+"/Window.Light.o"
} } ;

IntCmd intdep470 = { 'RM DEP' , &rmdep470 } ;

Rm rmdep470 = { { OBJ_PATH+"/Window.Light.dep" } } ;

Target cpp471 = { "Window.LineEdit.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.LineEdit.cpp" } ;
Target ocpp471 = { "Window.LineEdit.o" , OBJ_PATH+"/Window.LineEdit.o" } ;
Rule rcpp471 = { {&cpp471} , {&ocpp471} , {&intdep471,&execpp471} } ;
Exe execpp471 = { "CC Window.LineEdit.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.LineEdit.cpp"
 ,"-o"
 ,OBJ_PATH+"/Window.LineEdit.o"
} } ;

IntCmd intdep471 = { 'RM DEP' , &rmdep471 } ;

Rm rmdep471 = { { OBJ_PATH+"/Window.LineEdit.dep" } } ;

Target cpp472 = { "Window.Progress.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.Progress.cpp" } ;
Target ocpp472 = { "Window.Progress.o" , OBJ_PATH+"/Window.Progress.o" } ;
Rule rcpp472 = { {&cpp472} , {&ocpp472} , {&intdep472,&execpp472} } ;
Exe execpp472 = { "CC Window.Progress.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.Progress.cpp"
 ,"-o"
 ,OBJ_PATH+"/Window.Progress.o"
} } ;

IntCmd intdep472 = { 'RM DEP' , &rmdep472 } ;

Rm rmdep472 = { { OBJ_PATH+"/Window.Progress.dep" } } ;

Target cpp473 = { "Window.Radio.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.Radio.cpp" } ;
Target ocpp473 = { "Window.Radio.o" , OBJ_PATH+"/Window.Radio.o" } ;
Rule rcpp473 = { {&cpp473} , {&ocpp473} , {&intdep473,&execpp473} } ;
Exe execpp473 = { "CC Window.Radio.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.Radio.cpp"
 ,"-o"
 ,OBJ_PATH+"/Window.Radio.o"
} } ;

IntCmd intdep473 = { 'RM DEP' , &rmdep473 } ;

Rm rmdep473 = { { OBJ_PATH+"/Window.Radio.dep" } } ;

Target cpp474 = { "Window.RunButton.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.RunButton.cpp" } ;
Target ocpp474 = { "Window.RunButton.o" , OBJ_PATH+"/Window.RunButton.o" } ;
Rule rcpp474 = { {&cpp474} , {&ocpp474} , {&intdep474,&execpp474} } ;
Exe execpp474 = { "CC Window.RunButton.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.RunButton.cpp"
 ,"-o"
 ,OBJ_PATH+"/Window.RunButton.o"
} } ;

IntCmd intdep474 = { 'RM DEP' , &rmdep474 } ;

Rm rmdep474 = { { OBJ_PATH+"/Window.RunButton.dep" } } ;

Target cpp475 = { "Window.Scroll.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.Scroll.cpp" } ;
Target ocpp475 = { "Window.Scroll.o" , OBJ_PATH+"/Window.Scroll.o" } ;
Rule rcpp475 = { {&cpp475} , {&ocpp475} , {&intdep475,&execpp475} } ;
Exe execpp475 = { "CC Window.Scroll.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.Scroll.cpp"
 ,"-o"
 ,OBJ_PATH+"/Window.Scroll.o"
} } ;

IntCmd intdep475 = { 'RM DEP' , &rmdep475 } ;

Rm rmdep475 = { { OBJ_PATH+"/Window.Scroll.dep" } } ;

Target cpp476 = { "Window.ScrollList.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.ScrollList.cpp" } ;
Target ocpp476 = { "Window.ScrollList.o" , OBJ_PATH+"/Window.ScrollList.o" } ;
Rule rcpp476 = { {&cpp476} , {&ocpp476} , {&intdep476,&execpp476} } ;
Exe execpp476 = { "CC Window.ScrollList.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.ScrollList.cpp"
 ,"-o"
 ,OBJ_PATH+"/Window.ScrollList.o"
} } ;

IntCmd intdep476 = { 'RM DEP' , &rmdep476 } ;

Rm rmdep476 = { { OBJ_PATH+"/Window.ScrollList.dep" } } ;

Target cpp477 = { "Window.Scrollable.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.Scrollable.cpp" } ;
Target ocpp477 = { "Window.Scrollable.o" , OBJ_PATH+"/Window.Scrollable.o" } ;
Rule rcpp477 = { {&cpp477} , {&ocpp477} , {&intdep477,&execpp477} } ;
Exe execpp477 = { "CC Window.Scrollable.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.Scrollable.cpp"
 ,"-o"
 ,OBJ_PATH+"/Window.Scrollable.o"
} } ;

IntCmd intdep477 = { 'RM DEP' , &rmdep477 } ;

Rm rmdep477 = { { OBJ_PATH+"/Window.Scrollable.dep" } } ;

Target cpp478 = { "Window.SimpleTextList.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.SimpleTextList.cpp" } ;
Target ocpp478 = { "Window.SimpleTextList.o" , OBJ_PATH+"/Window.SimpleTextList.o" } ;
Rule rcpp478 = { {&cpp478} , {&ocpp478} , {&intdep478,&execpp478} } ;
Exe execpp478 = { "CC Window.SimpleTextList.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.SimpleTextList.cpp"
 ,"-o"
 ,OBJ_PATH+"/Window.SimpleTextList.o"
} } ;

IntCmd intdep478 = { 'RM DEP' , &rmdep478 } ;

Rm rmdep478 = { { OBJ_PATH+"/Window.SimpleTextList.dep" } } ;

Target cpp479 = { "Window.Slider.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.Slider.cpp" } ;
Target ocpp479 = { "Window.Slider.o" , OBJ_PATH+"/Window.Slider.o" } ;
Rule rcpp479 = { {&cpp479} , {&ocpp479} , {&intdep479,&execpp479} } ;
Exe execpp479 = { "CC Window.Slider.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.Slider.cpp"
 ,"-o"
 ,OBJ_PATH+"/Window.Slider.o"
} } ;

IntCmd intdep479 = { 'RM DEP' , &rmdep479 } ;

Rm rmdep479 = { { OBJ_PATH+"/Window.Slider.dep" } } ;

Target cpp480 = { "Window.Spinor.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.Spinor.cpp" } ;
Target ocpp480 = { "Window.Spinor.o" , OBJ_PATH+"/Window.Spinor.o" } ;
Rule rcpp480 = { {&cpp480} , {&ocpp480} , {&intdep480,&execpp480} } ;
Exe execpp480 = { "CC Window.Spinor.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.Spinor.cpp"
 ,"-o"
 ,OBJ_PATH+"/Window.Spinor.o"
} } ;

IntCmd intdep480 = { 'RM DEP' , &rmdep480 } ;

Rm rmdep480 = { { OBJ_PATH+"/Window.Spinor.dep" } } ;

Target cpp481 = { "Window.Split.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.Split.cpp" } ;
Target ocpp481 = { "Window.Split.o" , OBJ_PATH+"/Window.Split.o" } ;
Rule rcpp481 = { {&cpp481} , {&ocpp481} , {&intdep481,&execpp481} } ;
Exe execpp481 = { "CC Window.Split.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.Split.cpp"
 ,"-o"
 ,OBJ_PATH+"/Window.Split.o"
} } ;

IntCmd intdep481 = { 'RM DEP' , &rmdep481 } ;

Rm rmdep481 = { { OBJ_PATH+"/Window.Split.dep" } } ;

Target cpp482 = { "Window.Text.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.Text.cpp" } ;
Target ocpp482 = { "Window.Text.o" , OBJ_PATH+"/Window.Text.o" } ;
Rule rcpp482 = { {&cpp482} , {&ocpp482} , {&intdep482,&execpp482} } ;
Exe execpp482 = { "CC Window.Text.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.Text.cpp"
 ,"-o"
 ,OBJ_PATH+"/Window.Text.o"
} } ;

IntCmd intdep482 = { 'RM DEP' , &rmdep482 } ;

Rm rmdep482 = { { OBJ_PATH+"/Window.Text.dep" } } ;

Target cpp483 = { "Window.TextLine.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.TextLine.cpp" } ;
Target ocpp483 = { "Window.TextLine.o" , OBJ_PATH+"/Window.TextLine.o" } ;
Rule rcpp483 = { {&cpp483} , {&ocpp483} , {&intdep483,&execpp483} } ;
Exe execpp483 = { "CC Window.TextLine.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.TextLine.cpp"
 ,"-o"
 ,OBJ_PATH+"/Window.TextLine.o"
} } ;

IntCmd intdep483 = { 'RM DEP' , &rmdep483 } ;

Rm rmdep483 = { { OBJ_PATH+"/Window.TextLine.dep" } } ;

Target cpp484 = { "WindowLib.cpp" , "../../Desktop/Lib/CCore/src/./video/WindowLib.cpp" } ;
Target ocpp484 = { "WindowLib.o" , OBJ_PATH+"/WindowLib.o" } ;
Rule rcpp484 = { {&cpp484} , {&ocpp484} , {&intdep484,&execpp484} } ;
Exe execpp484 = { "CC WindowLib.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/Lib/CCore/src/./video/WindowLib.cpp"
 ,"-o"
 ,OBJ_PATH+"/WindowLib.o"
} } ;

IntCmd intdep484 = { 'RM DEP' , &rmdep484 } ;

Rm rmdep484 = { { OBJ_PATH+"/WindowLib.dep" } } ;

Target cpp485 = { "WindowReport.cpp" , "../../Desktop/App/CCore/src/./video/WindowReport.cpp" } ;
Target ocpp485 = { "WindowReport.o" , OBJ_PATH+"/WindowReport.o" } ;
Rule rcpp485 = { {&cpp485} , {&ocpp485} , {&intdep485,&execpp485} } ;
Exe execpp485 = { "CC WindowReport.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Desktop/App/CCore/src/./video/WindowReport.cpp"
 ,"-o"
 ,OBJ_PATH+"/WindowReport.o"
} } ;

IntCmd intdep485 = { 'RM DEP' , &rmdep485 } ;

Rm rmdep485 = { { OBJ_PATH+"/WindowReport.dep" } } ;

Target cpp486 = { "XPoint.cpp" , "../../Applied/CCore/src/./net/XPoint.cpp" } ;
Target ocpp486 = { "XPoint.o" , OBJ_PATH+"/XPoint.o" } ;
Rule rcpp486 = { {&cpp486} , {&ocpp486} , {&intdep486,&execpp486} } ;
Exe execpp486 = { "CC XPoint.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"../../Applied/CCore/src/./net/XPoint.cpp"
 ,"-o"
 ,OBJ_PATH+"/XPoint.o"
} } ;

IntCmd intdep486 = { 'RM DEP' , &rmdep486 } ;

Rm rmdep486 = { { OBJ_PATH+"/XPoint.dep" } } ;

Target asm1 = { "IntegerFastAlgo.s" , "CCore/src/./math/IntegerFastAlgo.s" } ;
Target oasm1 = { "IntegerFastAlgo.s.o" , OBJ_PATH+"/IntegerFastAlgo.s.o" } ;
Rule rasm1 = { {&asm1} , {&oasm1} , {&exeasm1} } ;
Exe exeasm1 = { "AS IntegerFastAlgo.s" , AS , {
  "CCore/src/./math/IntegerFastAlgo.s"
 ,"-o"
 ,OBJ_PATH+"/IntegerFastAlgo.s.o"
} } ;

Target asm2 = { "IntelAES.s" , "CCore/src/./crypton/IntelAES.s" } ;
Target oasm2 = { "IntelAES.s.o" , OBJ_PATH+"/IntelAES.s.o" } ;
Rule rasm2 = { {&asm2} , {&oasm2} , {&exeasm2} } ;
Exe exeasm2 = { "AS IntelAES.s" , AS , {
  "CCore/src/./crypton/IntelAES.s"
 ,"-o"
 ,OBJ_PATH+"/IntelAES.s.o"
} } ;

Target asm3 = { "IntelCPUID.s" , "CCore/src/./crypton/IntelCPUID.s" } ;
Target oasm3 = { "IntelCPUID.s.o" , OBJ_PATH+"/IntelCPUID.s.o" } ;
Rule rasm3 = { {&asm3} , {&oasm3} , {&exeasm3} } ;
Exe exeasm3 = { "AS IntelCPUID.s" , AS , {
  "CCore/src/./crypton/IntelCPUID.s"
 ,"-o"
 ,OBJ_PATH+"/IntelCPUID.s.o"
} } ;

Target asm4 = { "IntelRandom.s" , "CCore/src/./crypton/IntelRandom.s" } ;
Target oasm4 = { "IntelRandom.s.o" , OBJ_PATH+"/IntelRandom.s.o" } ;
Rule rasm4 = { {&asm4} , {&oasm4} , {&exeasm4} } ;
Exe exeasm4 = { "AS IntelRandom.s" , AS , {
  "CCore/src/./crypton/IntelRandom.s"
 ,"-o"
 ,OBJ_PATH+"/IntelRandom.s.o"
} } ;

Target asm5 = { "PlatformBase.s" , "CCore/src/./base/PlatformBase.s" } ;
Target oasm5 = { "PlatformBase.s.o" , OBJ_PATH+"/PlatformBase.s.o" } ;
Rule rasm5 = { {&asm5} , {&oasm5} , {&exeasm5} } ;
Exe exeasm5 = { "AS PlatformBase.s" , AS , {
  "CCore/src/./base/PlatformBase.s"
 ,"-o"
 ,OBJ_PATH+"/PlatformBase.s.o"
} } ;

Target asm6 = { "Quick.s" , "CCore/src/./base/Quick.s" } ;
Target oasm6 = { "Quick.s.o" , OBJ_PATH+"/Quick.s.o" } ;
Rule rasm6 = { {&asm6} , {&oasm6} , {&exeasm6} } ;
Exe exeasm6 = { "AS Quick.s" , AS , {
  "CCore/src/./base/Quick.s"
 ,"-o"
 ,OBJ_PATH+"/Quick.s.o"
} } ;

Target asm7 = { "SysAtomic.s" , "CCore/src/./sys/SysAtomic.s" } ;
Target oasm7 = { "SysAtomic.s.o" , OBJ_PATH+"/SysAtomic.s.o" } ;
Rule rasm7 = { {&asm7} , {&oasm7} , {&exeasm7} } ;
Exe exeasm7 = { "AS SysAtomic.s" , AS , {
  "CCore/src/./sys/SysAtomic.s"
 ,"-o"
 ,OBJ_PATH+"/SysAtomic.s.o"
} } ;

Target asm8 = { "SysTime.s" , "CCore/src/./sys/SysTime.s" } ;
Target oasm8 = { "SysTime.s.o" , OBJ_PATH+"/SysTime.s.o" } ;
Rule rasm8 = { {&asm8} , {&oasm8} , {&exeasm8} } ;
Exe exeasm8 = { "AS SysTime.s" , AS , {
  "CCore/src/./sys/SysTime.s"
 ,"-o"
 ,OBJ_PATH+"/SysTime.s.o"
} } ;

text ARGS = '@'+OBJ_PATH+'/target.args' ;

IntCmd intargs = { 'ARGS' , &echoargs } ;

Echo echoargs = { { 
 '"'+ocpp1.file+"\"\n"
,'"'+ocpp2.file+"\"\n"
,'"'+ocpp3.file+"\"\n"
,'"'+ocpp4.file+"\"\n"
,'"'+ocpp5.file+"\"\n"
,'"'+ocpp6.file+"\"\n"
,'"'+ocpp7.file+"\"\n"
,'"'+ocpp8.file+"\"\n"
,'"'+ocpp9.file+"\"\n"
,'"'+ocpp10.file+"\"\n"
,'"'+ocpp11.file+"\"\n"
,'"'+ocpp12.file+"\"\n"
,'"'+ocpp13.file+"\"\n"
,'"'+ocpp14.file+"\"\n"
,'"'+ocpp15.file+"\"\n"
,'"'+ocpp16.file+"\"\n"
,'"'+ocpp17.file+"\"\n"
,'"'+ocpp18.file+"\"\n"
,'"'+ocpp19.file+"\"\n"
,'"'+ocpp20.file+"\"\n"
,'"'+ocpp21.file+"\"\n"
,'"'+ocpp22.file+"\"\n"
,'"'+ocpp23.file+"\"\n"
,'"'+ocpp24.file+"\"\n"
,'"'+ocpp25.file+"\"\n"
,'"'+ocpp26.file+"\"\n"
,'"'+ocpp27.file+"\"\n"
,'"'+ocpp28.file+"\"\n"
,'"'+ocpp29.file+"\"\n"
,'"'+ocpp30.file+"\"\n"
,'"'+ocpp31.file+"\"\n"
,'"'+ocpp32.file+"\"\n"
,'"'+ocpp33.file+"\"\n"
,'"'+ocpp34.file+"\"\n"
,'"'+ocpp35.file+"\"\n"
,'"'+ocpp36.file+"\"\n"
,'"'+ocpp37.file+"\"\n"
,'"'+ocpp38.file+"\"\n"
,'"'+ocpp39.file+"\"\n"
,'"'+ocpp40.file+"\"\n"
,'"'+ocpp41.file+"\"\n"
,'"'+ocpp42.file+"\"\n"
,'"'+ocpp43.file+"\"\n"
,'"'+ocpp44.file+"\"\n"
,'"'+ocpp45.file+"\"\n"
,'"'+ocpp46.file+"\"\n"
,'"'+ocpp47.file+"\"\n"
,'"'+ocpp48.file+"\"\n"
,'"'+ocpp49.file+"\"\n"
,'"'+ocpp50.file+"\"\n"
,'"'+ocpp51.file+"\"\n"
,'"'+ocpp52.file+"\"\n"
,'"'+ocpp53.file+"\"\n"
,'"'+ocpp54.file+"\"\n"
,'"'+ocpp55.file+"\"\n"
,'"'+ocpp56.file+"\"\n"
,'"'+ocpp57.file+"\"\n"
,'"'+ocpp58.file+"\"\n"
,'"'+ocpp59.file+"\"\n"
,'"'+ocpp60.file+"\"\n"
,'"'+ocpp61.file+"\"\n"
,'"'+ocpp62.file+"\"\n"
,'"'+ocpp63.file+"\"\n"
,'"'+ocpp64.file+"\"\n"
,'"'+ocpp65.file+"\"\n"
,'"'+ocpp66.file+"\"\n"
,'"'+ocpp67.file+"\"\n"
,'"'+ocpp68.file+"\"\n"
,'"'+ocpp69.file+"\"\n"
,'"'+ocpp70.file+"\"\n"
,'"'+ocpp71.file+"\"\n"
,'"'+ocpp72.file+"\"\n"
,'"'+ocpp73.file+"\"\n"
,'"'+ocpp74.file+"\"\n"
,'"'+ocpp75.file+"\"\n"
,'"'+ocpp76.file+"\"\n"
,'"'+ocpp77.file+"\"\n"
,'"'+ocpp78.file+"\"\n"
,'"'+ocpp79.file+"\"\n"
,'"'+ocpp80.file+"\"\n"
,'"'+ocpp81.file+"\"\n"
,'"'+ocpp82.file+"\"\n"
,'"'+ocpp83.file+"\"\n"
,'"'+ocpp84.file+"\"\n"
,'"'+ocpp85.file+"\"\n"
,'"'+ocpp86.file+"\"\n"
,'"'+ocpp87.file+"\"\n"
,'"'+ocpp88.file+"\"\n"
,'"'+ocpp89.file+"\"\n"
,'"'+ocpp90.file+"\"\n"
,'"'+ocpp91.file+"\"\n"
,'"'+ocpp92.file+"\"\n"
,'"'+ocpp93.file+"\"\n"
,'"'+ocpp94.file+"\"\n"
,'"'+ocpp95.file+"\"\n"
,'"'+ocpp96.file+"\"\n"
,'"'+ocpp97.file+"\"\n"
,'"'+ocpp98.file+"\"\n"
,'"'+ocpp99.file+"\"\n"
,'"'+ocpp100.file+"\"\n"
,'"'+ocpp101.file+"\"\n"
,'"'+ocpp102.file+"\"\n"
,'"'+ocpp103.file+"\"\n"
,'"'+ocpp104.file+"\"\n"
,'"'+ocpp105.file+"\"\n"
,'"'+ocpp106.file+"\"\n"
,'"'+ocpp107.file+"\"\n"
,'"'+ocpp108.file+"\"\n"
,'"'+ocpp109.file+"\"\n"
,'"'+ocpp110.file+"\"\n"
,'"'+ocpp111.file+"\"\n"
,'"'+ocpp112.file+"\"\n"
,'"'+ocpp113.file+"\"\n"
,'"'+ocpp114.file+"\"\n"
,'"'+ocpp115.file+"\"\n"
,'"'+ocpp116.file+"\"\n"
,'"'+ocpp117.file+"\"\n"
,'"'+ocpp118.file+"\"\n"
,'"'+ocpp119.file+"\"\n"
,'"'+ocpp120.file+"\"\n"
,'"'+ocpp121.file+"\"\n"
,'"'+ocpp122.file+"\"\n"
,'"'+ocpp123.file+"\"\n"
,'"'+ocpp124.file+"\"\n"
,'"'+ocpp125.file+"\"\n"
,'"'+ocpp126.file+"\"\n"
,'"'+ocpp127.file+"\"\n"
,'"'+ocpp128.file+"\"\n"
,'"'+ocpp129.file+"\"\n"
,'"'+ocpp130.file+"\"\n"
,'"'+ocpp131.file+"\"\n"
,'"'+ocpp132.file+"\"\n"
,'"'+ocpp133.file+"\"\n"
,'"'+ocpp134.file+"\"\n"
,'"'+ocpp135.file+"\"\n"
,'"'+ocpp136.file+"\"\n"
,'"'+ocpp137.file+"\"\n"
,'"'+ocpp138.file+"\"\n"
,'"'+ocpp139.file+"\"\n"
,'"'+ocpp140.file+"\"\n"
,'"'+ocpp141.file+"\"\n"
,'"'+ocpp142.file+"\"\n"
,'"'+ocpp143.file+"\"\n"
,'"'+ocpp144.file+"\"\n"
,'"'+ocpp145.file+"\"\n"
,'"'+ocpp146.file+"\"\n"
,'"'+ocpp147.file+"\"\n"
,'"'+ocpp148.file+"\"\n"
,'"'+ocpp149.file+"\"\n"
,'"'+ocpp150.file+"\"\n"
,'"'+ocpp151.file+"\"\n"
,'"'+ocpp152.file+"\"\n"
,'"'+ocpp153.file+"\"\n"
,'"'+ocpp154.file+"\"\n"
,'"'+ocpp155.file+"\"\n"
,'"'+ocpp156.file+"\"\n"
,'"'+ocpp157.file+"\"\n"
,'"'+ocpp158.file+"\"\n"
,'"'+ocpp159.file+"\"\n"
,'"'+ocpp160.file+"\"\n"
,'"'+ocpp161.file+"\"\n"
,'"'+ocpp162.file+"\"\n"
,'"'+ocpp163.file+"\"\n"
,'"'+ocpp164.file+"\"\n"
,'"'+ocpp165.file+"\"\n"
,'"'+ocpp166.file+"\"\n"
,'"'+ocpp167.file+"\"\n"
,'"'+ocpp168.file+"\"\n"
,'"'+ocpp169.file+"\"\n"
,'"'+ocpp170.file+"\"\n"
,'"'+ocpp171.file+"\"\n"
,'"'+ocpp172.file+"\"\n"
,'"'+ocpp173.file+"\"\n"
,'"'+ocpp174.file+"\"\n"
,'"'+ocpp175.file+"\"\n"
,'"'+ocpp176.file+"\"\n"
,'"'+ocpp177.file+"\"\n"
,'"'+ocpp178.file+"\"\n"
,'"'+ocpp179.file+"\"\n"
,'"'+ocpp180.file+"\"\n"
,'"'+ocpp181.file+"\"\n"
,'"'+ocpp182.file+"\"\n"
,'"'+ocpp183.file+"\"\n"
,'"'+ocpp184.file+"\"\n"
,'"'+ocpp185.file+"\"\n"
,'"'+ocpp186.file+"\"\n"
,'"'+ocpp187.file+"\"\n"
,'"'+ocpp188.file+"\"\n"
,'"'+ocpp189.file+"\"\n"
,'"'+ocpp190.file+"\"\n"
,'"'+ocpp191.file+"\"\n"
,'"'+ocpp192.file+"\"\n"
,'"'+ocpp193.file+"\"\n"
,'"'+ocpp194.file+"\"\n"
,'"'+ocpp195.file+"\"\n"
,'"'+ocpp196.file+"\"\n"
,'"'+ocpp197.file+"\"\n"
,'"'+ocpp198.file+"\"\n"
,'"'+ocpp199.file+"\"\n"
,'"'+ocpp200.file+"\"\n"
,'"'+ocpp201.file+"\"\n"
,'"'+ocpp202.file+"\"\n"
,'"'+ocpp203.file+"\"\n"
,'"'+ocpp204.file+"\"\n"
,'"'+ocpp205.file+"\"\n"
,'"'+ocpp206.file+"\"\n"
,'"'+ocpp207.file+"\"\n"
,'"'+ocpp208.file+"\"\n"
,'"'+ocpp209.file+"\"\n"
,'"'+ocpp210.file+"\"\n"
,'"'+ocpp211.file+"\"\n"
,'"'+ocpp212.file+"\"\n"
,'"'+ocpp213.file+"\"\n"
,'"'+ocpp214.file+"\"\n"
,'"'+ocpp215.file+"\"\n"
,'"'+ocpp216.file+"\"\n"
,'"'+ocpp217.file+"\"\n"
,'"'+ocpp218.file+"\"\n"
,'"'+ocpp219.file+"\"\n"
,'"'+ocpp220.file+"\"\n"
,'"'+ocpp221.file+"\"\n"
,'"'+ocpp222.file+"\"\n"
,'"'+ocpp223.file+"\"\n"
,'"'+ocpp224.file+"\"\n"
,'"'+ocpp225.file+"\"\n"
,'"'+ocpp226.file+"\"\n"
,'"'+ocpp227.file+"\"\n"
,'"'+ocpp228.file+"\"\n"
,'"'+ocpp229.file+"\"\n"
,'"'+ocpp230.file+"\"\n"
,'"'+ocpp231.file+"\"\n"
,'"'+ocpp232.file+"\"\n"
,'"'+ocpp233.file+"\"\n"
,'"'+ocpp234.file+"\"\n"
,'"'+ocpp235.file+"\"\n"
,'"'+ocpp236.file+"\"\n"
,'"'+ocpp237.file+"\"\n"
,'"'+ocpp238.file+"\"\n"
,'"'+ocpp239.file+"\"\n"
,'"'+ocpp240.file+"\"\n"
,'"'+ocpp241.file+"\"\n"
,'"'+ocpp242.file+"\"\n"
,'"'+ocpp243.file+"\"\n"
,'"'+ocpp244.file+"\"\n"
,'"'+ocpp245.file+"\"\n"
,'"'+ocpp246.file+"\"\n"
,'"'+ocpp247.file+"\"\n"
,'"'+ocpp248.file+"\"\n"
,'"'+ocpp249.file+"\"\n"
,'"'+ocpp250.file+"\"\n"
,'"'+ocpp251.file+"\"\n"
,'"'+ocpp252.file+"\"\n"
,'"'+ocpp253.file+"\"\n"
,'"'+ocpp254.file+"\"\n"
,'"'+ocpp255.file+"\"\n"
,'"'+ocpp256.file+"\"\n"
,'"'+ocpp257.file+"\"\n"
,'"'+ocpp258.file+"\"\n"
,'"'+ocpp259.file+"\"\n"
,'"'+ocpp260.file+"\"\n"
,'"'+ocpp261.file+"\"\n"
,'"'+ocpp262.file+"\"\n"
,'"'+ocpp263.file+"\"\n"
,'"'+ocpp264.file+"\"\n"
,'"'+ocpp265.file+"\"\n"
,'"'+ocpp266.file+"\"\n"
,'"'+ocpp267.file+"\"\n"
,'"'+ocpp268.file+"\"\n"
,'"'+ocpp269.file+"\"\n"
,'"'+ocpp270.file+"\"\n"
,'"'+ocpp271.file+"\"\n"
,'"'+ocpp272.file+"\"\n"
,'"'+ocpp273.file+"\"\n"
,'"'+ocpp274.file+"\"\n"
,'"'+ocpp275.file+"\"\n"
,'"'+ocpp276.file+"\"\n"
,'"'+ocpp277.file+"\"\n"
,'"'+ocpp278.file+"\"\n"
,'"'+ocpp279.file+"\"\n"
,'"'+ocpp280.file+"\"\n"
,'"'+ocpp281.file+"\"\n"
,'"'+ocpp282.file+"\"\n"
,'"'+ocpp283.file+"\"\n"
,'"'+ocpp284.file+"\"\n"
,'"'+ocpp285.file+"\"\n"
,'"'+ocpp286.file+"\"\n"
,'"'+ocpp287.file+"\"\n"
,'"'+ocpp288.file+"\"\n"
,'"'+ocpp289.file+"\"\n"
,'"'+ocpp290.file+"\"\n"
,'"'+ocpp291.file+"\"\n"
,'"'+ocpp292.file+"\"\n"
,'"'+ocpp293.file+"\"\n"
,'"'+ocpp294.file+"\"\n"
,'"'+ocpp295.file+"\"\n"
,'"'+ocpp296.file+"\"\n"
,'"'+ocpp297.file+"\"\n"
,'"'+ocpp298.file+"\"\n"
,'"'+ocpp299.file+"\"\n"
,'"'+ocpp300.file+"\"\n"
,'"'+ocpp301.file+"\"\n"
,'"'+ocpp302.file+"\"\n"
,'"'+ocpp303.file+"\"\n"
,'"'+ocpp304.file+"\"\n"
,'"'+ocpp305.file+"\"\n"
,'"'+ocpp306.file+"\"\n"
,'"'+ocpp307.file+"\"\n"
,'"'+ocpp308.file+"\"\n"
,'"'+ocpp309.file+"\"\n"
,'"'+ocpp310.file+"\"\n"
,'"'+ocpp311.file+"\"\n"
,'"'+ocpp312.file+"\"\n"
,'"'+ocpp313.file+"\"\n"
,'"'+ocpp314.file+"\"\n"
,'"'+ocpp315.file+"\"\n"
,'"'+ocpp316.file+"\"\n"
,'"'+ocpp317.file+"\"\n"
,'"'+ocpp318.file+"\"\n"
,'"'+ocpp319.file+"\"\n"
,'"'+ocpp320.file+"\"\n"
,'"'+ocpp321.file+"\"\n"
,'"'+ocpp322.file+"\"\n"
,'"'+ocpp323.file+"\"\n"
,'"'+ocpp324.file+"\"\n"
,'"'+ocpp325.file+"\"\n"
,'"'+ocpp326.file+"\"\n"
,'"'+ocpp327.file+"\"\n"
,'"'+ocpp328.file+"\"\n"
,'"'+ocpp329.file+"\"\n"
,'"'+ocpp330.file+"\"\n"
,'"'+ocpp331.file+"\"\n"
,'"'+ocpp332.file+"\"\n"
,'"'+ocpp333.file+"\"\n"
,'"'+ocpp334.file+"\"\n"
,'"'+ocpp335.file+"\"\n"
,'"'+ocpp336.file+"\"\n"
,'"'+ocpp337.file+"\"\n"
,'"'+ocpp338.file+"\"\n"
,'"'+ocpp339.file+"\"\n"
,'"'+ocpp340.file+"\"\n"
,'"'+ocpp341.file+"\"\n"
,'"'+ocpp342.file+"\"\n"
,'"'+ocpp343.file+"\"\n"
,'"'+ocpp344.file+"\"\n"
,'"'+ocpp345.file+"\"\n"
,'"'+ocpp346.file+"\"\n"
,'"'+ocpp347.file+"\"\n"
,'"'+ocpp348.file+"\"\n"
,'"'+ocpp349.file+"\"\n"
,'"'+ocpp350.file+"\"\n"
,'"'+ocpp351.file+"\"\n"
,'"'+ocpp352.file+"\"\n"
,'"'+ocpp353.file+"\"\n"
,'"'+ocpp354.file+"\"\n"
,'"'+ocpp355.file+"\"\n"
,'"'+ocpp356.file+"\"\n"
,'"'+ocpp357.file+"\"\n"
,'"'+ocpp358.file+"\"\n"
,'"'+ocpp359.file+"\"\n"
,'"'+ocpp360.file+"\"\n"
,'"'+ocpp361.file+"\"\n"
,'"'+ocpp362.file+"\"\n"
,'"'+ocpp363.file+"\"\n"
,'"'+ocpp364.file+"\"\n"
,'"'+ocpp365.file+"\"\n"
,'"'+ocpp366.file+"\"\n"
,'"'+ocpp367.file+"\"\n"
,'"'+ocpp368.file+"\"\n"
,'"'+ocpp369.file+"\"\n"
,'"'+ocpp370.file+"\"\n"
,'"'+ocpp371.file+"\"\n"
,'"'+ocpp372.file+"\"\n"
,'"'+ocpp373.file+"\"\n"
,'"'+ocpp374.file+"\"\n"
,'"'+ocpp375.file+"\"\n"
,'"'+ocpp376.file+"\"\n"
,'"'+ocpp377.file+"\"\n"
,'"'+ocpp378.file+"\"\n"
,'"'+ocpp379.file+"\"\n"
,'"'+ocpp380.file+"\"\n"
,'"'+ocpp381.file+"\"\n"
,'"'+ocpp382.file+"\"\n"
,'"'+ocpp383.file+"\"\n"
,'"'+ocpp384.file+"\"\n"
,'"'+ocpp385.file+"\"\n"
,'"'+ocpp386.file+"\"\n"
,'"'+ocpp387.file+"\"\n"
,'"'+ocpp388.file+"\"\n"
,'"'+ocpp389.file+"\"\n"
,'"'+ocpp390.file+"\"\n"
,'"'+ocpp391.file+"\"\n"
,'"'+ocpp392.file+"\"\n"
,'"'+ocpp393.file+"\"\n"
,'"'+ocpp394.file+"\"\n"
,'"'+ocpp395.file+"\"\n"
,'"'+ocpp396.file+"\"\n"
,'"'+ocpp397.file+"\"\n"
,'"'+ocpp398.file+"\"\n"
,'"'+ocpp399.file+"\"\n"
,'"'+ocpp400.file+"\"\n"
,'"'+ocpp401.file+"\"\n"
,'"'+ocpp402.file+"\"\n"
,'"'+ocpp403.file+"\"\n"
,'"'+ocpp404.file+"\"\n"
,'"'+ocpp405.file+"\"\n"
,'"'+ocpp406.file+"\"\n"
,'"'+ocpp407.file+"\"\n"
,'"'+ocpp408.file+"\"\n"
,'"'+ocpp409.file+"\"\n"
,'"'+ocpp410.file+"\"\n"
,'"'+ocpp411.file+"\"\n"
,'"'+ocpp412.file+"\"\n"
,'"'+ocpp413.file+"\"\n"
,'"'+ocpp414.file+"\"\n"
,'"'+ocpp415.file+"\"\n"
,'"'+ocpp416.file+"\"\n"
,'"'+ocpp417.file+"\"\n"
,'"'+ocpp418.file+"\"\n"
,'"'+ocpp419.file+"\"\n"
,'"'+ocpp420.file+"\"\n"
,'"'+ocpp421.file+"\"\n"
,'"'+ocpp422.file+"\"\n"
,'"'+ocpp423.file+"\"\n"
,'"'+ocpp424.file+"\"\n"
,'"'+ocpp425.file+"\"\n"
,'"'+ocpp426.file+"\"\n"
,'"'+ocpp427.file+"\"\n"
,'"'+ocpp428.file+"\"\n"
,'"'+ocpp429.file+"\"\n"
,'"'+ocpp430.file+"\"\n"
,'"'+ocpp431.file+"\"\n"
,'"'+ocpp432.file+"\"\n"
,'"'+ocpp433.file+"\"\n"
,'"'+ocpp434.file+"\"\n"
,'"'+ocpp435.file+"\"\n"
,'"'+ocpp436.file+"\"\n"
,'"'+ocpp437.file+"\"\n"
,'"'+ocpp438.file+"\"\n"
,'"'+ocpp439.file+"\"\n"
,'"'+ocpp440.file+"\"\n"
,'"'+ocpp441.file+"\"\n"
,'"'+ocpp442.file+"\"\n"
,'"'+ocpp443.file+"\"\n"
,'"'+ocpp444.file+"\"\n"
,'"'+ocpp445.file+"\"\n"
,'"'+ocpp446.file+"\"\n"
,'"'+ocpp447.file+"\"\n"
,'"'+ocpp448.file+"\"\n"
,'"'+ocpp449.file+"\"\n"
,'"'+ocpp450.file+"\"\n"
,'"'+ocpp451.file+"\"\n"
,'"'+ocpp452.file+"\"\n"
,'"'+ocpp453.file+"\"\n"
,'"'+ocpp454.file+"\"\n"
,'"'+ocpp455.file+"\"\n"
,'"'+ocpp456.file+"\"\n"
,'"'+ocpp457.file+"\"\n"
,'"'+ocpp458.file+"\"\n"
,'"'+ocpp459.file+"\"\n"
,'"'+ocpp460.file+"\"\n"
,'"'+ocpp461.file+"\"\n"
,'"'+ocpp462.file+"\"\n"
,'"'+ocpp463.file+"\"\n"
,'"'+ocpp464.file+"\"\n"
,'"'+ocpp465.file+"\"\n"
,'"'+ocpp466.file+"\"\n"
,'"'+ocpp467.file+"\"\n"
,'"'+ocpp468.file+"\"\n"
,'"'+ocpp469.file+"\"\n"
,'"'+ocpp470.file+"\"\n"
,'"'+ocpp471.file+"\"\n"
,'"'+ocpp472.file+"\"\n"
,'"'+ocpp473.file+"\"\n"
,'"'+ocpp474.file+"\"\n"
,'"'+ocpp475.file+"\"\n"
,'"'+ocpp476.file+"\"\n"
,'"'+ocpp477.file+"\"\n"
,'"'+ocpp478.file+"\"\n"
,'"'+ocpp479.file+"\"\n"
,'"'+ocpp480.file+"\"\n"
,'"'+ocpp481.file+"\"\n"
,'"'+ocpp482.file+"\"\n"
,'"'+ocpp483.file+"\"\n"
,'"'+ocpp484.file+"\"\n"
,'"'+ocpp485.file+"\"\n"
,'"'+ocpp486.file+"\"\n"
,'"'+oasm1.file+"\"\n"
,'"'+oasm2.file+"\"\n"
,'"'+oasm3.file+"\"\n"
,'"'+oasm4.file+"\"\n"
,'"'+oasm5.file+"\"\n"
,'"'+oasm6.file+"\"\n"
,'"'+oasm7.file+"\"\n"
,'"'+oasm8.file+"\"\n" } , OBJ_PATH+'/target.args' } ;

Target main = { 'main' , TARGET } ;

Rule rmain = { { core_ptr 
,&ocpp1
,&ocpp2
,&ocpp3
,&ocpp4
,&ocpp5
,&ocpp6
,&ocpp7
,&ocpp8
,&ocpp9
,&ocpp10
,&ocpp11
,&ocpp12
,&ocpp13
,&ocpp14
,&ocpp15
,&ocpp16
,&ocpp17
,&ocpp18
,&ocpp19
,&ocpp20
,&ocpp21
,&ocpp22
,&ocpp23
,&ocpp24
,&ocpp25
,&ocpp26
,&ocpp27
,&ocpp28
,&ocpp29
,&ocpp30
,&ocpp31
,&ocpp32
,&ocpp33
,&ocpp34
,&ocpp35
,&ocpp36
,&ocpp37
,&ocpp38
,&ocpp39
,&ocpp40
,&ocpp41
,&ocpp42
,&ocpp43
,&ocpp44
,&ocpp45
,&ocpp46
,&ocpp47
,&ocpp48
,&ocpp49
,&ocpp50
,&ocpp51
,&ocpp52
,&ocpp53
,&ocpp54
,&ocpp55
,&ocpp56
,&ocpp57
,&ocpp58
,&ocpp59
,&ocpp60
,&ocpp61
,&ocpp62
,&ocpp63
,&ocpp64
,&ocpp65
,&ocpp66
,&ocpp67
,&ocpp68
,&ocpp69
,&ocpp70
,&ocpp71
,&ocpp72
,&ocpp73
,&ocpp74
,&ocpp75
,&ocpp76
,&ocpp77
,&ocpp78
,&ocpp79
,&ocpp80
,&ocpp81
,&ocpp82
,&ocpp83
,&ocpp84
,&ocpp85
,&ocpp86
,&ocpp87
,&ocpp88
,&ocpp89
,&ocpp90
,&ocpp91
,&ocpp92
,&ocpp93
,&ocpp94
,&ocpp95
,&ocpp96
,&ocpp97
,&ocpp98
,&ocpp99
,&ocpp100
,&ocpp101
,&ocpp102
,&ocpp103
,&ocpp104
,&ocpp105
,&ocpp106
,&ocpp107
,&ocpp108
,&ocpp109
,&ocpp110
,&ocpp111
,&ocpp112
,&ocpp113
,&ocpp114
,&ocpp115
,&ocpp116
,&ocpp117
,&ocpp118
,&ocpp119
,&ocpp120
,&ocpp121
,&ocpp122
,&ocpp123
,&ocpp124
,&ocpp125
,&ocpp126
,&ocpp127
,&ocpp128
,&ocpp129
,&ocpp130
,&ocpp131
,&ocpp132
,&ocpp133
,&ocpp134
,&ocpp135
,&ocpp136
,&ocpp137
,&ocpp138
,&ocpp139
,&ocpp140
,&ocpp141
,&ocpp142
,&ocpp143
,&ocpp144
,&ocpp145
,&ocpp146
,&ocpp147
,&ocpp148
,&ocpp149
,&ocpp150
,&ocpp151
,&ocpp152
,&ocpp153
,&ocpp154
,&ocpp155
,&ocpp156
,&ocpp157
,&ocpp158
,&ocpp159
,&ocpp160
,&ocpp161
,&ocpp162
,&ocpp163
,&ocpp164
,&ocpp165
,&ocpp166
,&ocpp167
,&ocpp168
,&ocpp169
,&ocpp170
,&ocpp171
,&ocpp172
,&ocpp173
,&ocpp174
,&ocpp175
,&ocpp176
,&ocpp177
,&ocpp178
,&ocpp179
,&ocpp180
,&ocpp181
,&ocpp182
,&ocpp183
,&ocpp184
,&ocpp185
,&ocpp186
,&ocpp187
,&ocpp188
,&ocpp189
,&ocpp190
,&ocpp191
,&ocpp192
,&ocpp193
,&ocpp194
,&ocpp195
,&ocpp196
,&ocpp197
,&ocpp198
,&ocpp199
,&ocpp200
,&ocpp201
,&ocpp202
,&ocpp203
,&ocpp204
,&ocpp205
,&ocpp206
,&ocpp207
,&ocpp208
,&ocpp209
,&ocpp210
,&ocpp211
,&ocpp212
,&ocpp213
,&ocpp214
,&ocpp215
,&ocpp216
,&ocpp217
,&ocpp218
,&ocpp219
,&ocpp220
,&ocpp221
,&ocpp222
,&ocpp223
,&ocpp224
,&ocpp225
,&ocpp226
,&ocpp227
,&ocpp228
,&ocpp229
,&ocpp230
,&ocpp231
,&ocpp232
,&ocpp233
,&ocpp234
,&ocpp235
,&ocpp236
,&ocpp237
,&ocpp238
,&ocpp239
,&ocpp240
,&ocpp241
,&ocpp242
,&ocpp243
,&ocpp244
,&ocpp245
,&ocpp246
,&ocpp247
,&ocpp248
,&ocpp249
,&ocpp250
,&ocpp251
,&ocpp252
,&ocpp253
,&ocpp254
,&ocpp255
,&ocpp256
,&ocpp257
,&ocpp258
,&ocpp259
,&ocpp260
,&ocpp261
,&ocpp262
,&ocpp263
,&ocpp264
,&ocpp265
,&ocpp266
,&ocpp267
,&ocpp268
,&ocpp269
,&ocpp270
,&ocpp271
,&ocpp272
,&ocpp273
,&ocpp274
,&ocpp275
,&ocpp276
,&ocpp277
,&ocpp278
,&ocpp279
,&ocpp280
,&ocpp281
,&ocpp282
,&ocpp283
,&ocpp284
,&ocpp285
,&ocpp286
,&ocpp287
,&ocpp288
,&ocpp289
,&ocpp290
,&ocpp291
,&ocpp292
,&ocpp293
,&ocpp294
,&ocpp295
,&ocpp296
,&ocpp297
,&ocpp298
,&ocpp299
,&ocpp300
,&ocpp301
,&ocpp302
,&ocpp303
,&ocpp304
,&ocpp305
,&ocpp306
,&ocpp307
,&ocpp308
,&ocpp309
,&ocpp310
,&ocpp311
,&ocpp312
,&ocpp313
,&ocpp314
,&ocpp315
,&ocpp316
,&ocpp317
,&ocpp318
,&ocpp319
,&ocpp320
,&ocpp321
,&ocpp322
,&ocpp323
,&ocpp324
,&ocpp325
,&ocpp326
,&ocpp327
,&ocpp328
,&ocpp329
,&ocpp330
,&ocpp331
,&ocpp332
,&ocpp333
,&ocpp334
,&ocpp335
,&ocpp336
,&ocpp337
,&ocpp338
,&ocpp339
,&ocpp340
,&ocpp341
,&ocpp342
,&ocpp343
,&ocpp344
,&ocpp345
,&ocpp346
,&ocpp347
,&ocpp348
,&ocpp349
,&ocpp350
,&ocpp351
,&ocpp352
,&ocpp353
,&ocpp354
,&ocpp355
,&ocpp356
,&ocpp357
,&ocpp358
,&ocpp359
,&ocpp360
,&ocpp361
,&ocpp362
,&ocpp363
,&ocpp364
,&ocpp365
,&ocpp366
,&ocpp367
,&ocpp368
,&ocpp369
,&ocpp370
,&ocpp371
,&ocpp372
,&ocpp373
,&ocpp374
,&ocpp375
,&ocpp376
,&ocpp377
,&ocpp378
,&ocpp379
,&ocpp380
,&ocpp381
,&ocpp382
,&ocpp383
,&ocpp384
,&ocpp385
,&ocpp386
,&ocpp387
,&ocpp388
,&ocpp389
,&ocpp390
,&ocpp391
,&ocpp392
,&ocpp393
,&ocpp394
,&ocpp395
,&ocpp396
,&ocpp397
,&ocpp398
,&ocpp399
,&ocpp400
,&ocpp401
,&ocpp402
,&ocpp403
,&ocpp404
,&ocpp405
,&ocpp406
,&ocpp407
,&ocpp408
,&ocpp409
,&ocpp410
,&ocpp411
,&ocpp412
,&ocpp413
,&ocpp414
,&ocpp415
,&ocpp416
,&ocpp417
,&ocpp418
,&ocpp419
,&ocpp420
,&ocpp421
,&ocpp422
,&ocpp423
,&ocpp424
,&ocpp425
,&ocpp426
,&ocpp427
,&ocpp428
,&ocpp429
,&ocpp430
,&ocpp431
,&ocpp432
,&ocpp433
,&ocpp434
,&ocpp435
,&ocpp436
,&ocpp437
,&ocpp438
,&ocpp439
,&ocpp440
,&ocpp441
,&ocpp442
,&ocpp443
,&ocpp444
,&ocpp445
,&ocpp446
,&ocpp447
,&ocpp448
,&ocpp449
,&ocpp450
,&ocpp451
,&ocpp452
,&ocpp453
,&ocpp454
,&ocpp455
,&ocpp456
,&ocpp457
,&ocpp458
,&ocpp459
,&ocpp460
,&ocpp461
,&ocpp462
,&ocpp463
,&ocpp464
,&ocpp465
,&ocpp466
,&ocpp467
,&ocpp468
,&ocpp469
,&ocpp470
,&ocpp471
,&ocpp472
,&ocpp473
,&ocpp474
,&ocpp475
,&ocpp476
,&ocpp477
,&ocpp478
,&ocpp479
,&ocpp480
,&ocpp481
,&ocpp482
,&ocpp483
,&ocpp484
,&ocpp485
,&ocpp486
,&oasm1
,&oasm2
,&oasm3
,&oasm4
,&oasm5
,&oasm6
,&oasm7
,&oasm8 } , {&main} , {&intargs,&intmain1,&exemain2} } ;

IntCmd intmain1 = { 'RM' , &rm1 } ;

Rm rm1 = { { TARGET } } ;

Exe exemain2 = { 'AR '+TARGET , AR , { 'r' , TARGET , ARGS } } ;

Target *core_ptr = null ;

include <.obj/deps.vm.ddl>
