text CC = "D:/cygwin"+"/opt/gcc-8.3.0/bin/g++-8.3.0" ;

text VMDEP = "D:/active/home"+"/bin/CCore-VMakeDep.exe" ;

text OBJ_PATH = ".vmobj" ;

text TARGET = "./main.exe" ;

Target obj = { 'obj' , OBJ_PATH+'/empty' } ;

Rule robj = { {} , {&obj} , {&intobj1,&intobj2} } ;

IntCmd intobj1 = { 'MKDIR' , &mkdir1 } ;

Mkdir mkdir1 = { OBJ_PATH } ;

IntCmd intobj2 = { 'ECHO' , &echo1 } ;

Echo echo1 = { 'empty' , OBJ_PATH+'/empty' } ;

Target clean = { 'clean' } ;

Rule rclean = { {} , {&clean} , {&intclean} } ;

IntCmd intclean = { 'CLEAN' , &rm1 } ;

Rm rm1 = { { TARGET , OBJ_PATH+"/*" } } ;

text DEP = OBJ_PATH+'/deps.vm.ddl' ;

Target cpp1 = { "AES.cpp" , "../../Applied/CCore/src/./crypton/AES.cpp" } ;
Target dcpp1 = { "AES.dep" , OBJ_PATH+"/AES.dep" } ;
Rule rdcpp1 = { {&cpp1,&obj} , {&dcpp1} , {&execpp1} } ;
Exe execpp1 = { "CC-DEP AES.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/AES.o"
 ,"../../Applied/CCore/src/./crypton/AES.cpp"
 ,"-MF"
 ,OBJ_PATH+"/AES.dep"
} } ;

Target vdcpp1 = { "AES.vm.dep" , OBJ_PATH+"/AES.vm.dep" } ;
Rule rvdcpp1 = { {&dcpp1} , {&vdcpp1} , {&exedcpp1} } ;
Exe exedcpp1 = { "CC-VM-DEP AES.cpp" , VMDEP , { OBJ_PATH+"/AES.dep" , OBJ_PATH+"/AES.vm.dep" , "1" } } ;

Target cpp2 = { "APRTest.cpp" , "../../Applied/CCore/src/./math/APRTest.cpp" } ;
Target dcpp2 = { "APRTest.dep" , OBJ_PATH+"/APRTest.dep" } ;
Rule rdcpp2 = { {&cpp2,&obj} , {&dcpp2} , {&execpp2} } ;
Exe execpp2 = { "CC-DEP APRTest.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/APRTest.o"
 ,"../../Applied/CCore/src/./math/APRTest.cpp"
 ,"-MF"
 ,OBJ_PATH+"/APRTest.dep"
} } ;

Target vdcpp2 = { "APRTest.vm.dep" , OBJ_PATH+"/APRTest.vm.dep" } ;
Rule rvdcpp2 = { {&dcpp2} , {&vdcpp2} , {&exedcpp2} } ;
Exe exedcpp2 = { "CC-VM-DEP APRTest.cpp" , VMDEP , { OBJ_PATH+"/APRTest.dep" , OBJ_PATH+"/APRTest.vm.dep" , "2" } } ;

Target cpp3 = { "APRTestData.gen.cpp" , "../../Applied/CCore/src/./math/APRTestData.gen.cpp" } ;
Target dcpp3 = { "APRTestData.gen.dep" , OBJ_PATH+"/APRTestData.gen.dep" } ;
Rule rdcpp3 = { {&cpp3,&obj} , {&dcpp3} , {&execpp3} } ;
Exe execpp3 = { "CC-DEP APRTestData.gen.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/APRTestData.gen.o"
 ,"../../Applied/CCore/src/./math/APRTestData.gen.cpp"
 ,"-MF"
 ,OBJ_PATH+"/APRTestData.gen.dep"
} } ;

Target vdcpp3 = { "APRTestData.gen.vm.dep" , OBJ_PATH+"/APRTestData.gen.vm.dep" } ;
Rule rvdcpp3 = { {&dcpp3} , {&vdcpp3} , {&exedcpp3} } ;
Exe exedcpp3 = { "CC-VM-DEP APRTestData.gen.cpp" , VMDEP , { OBJ_PATH+"/APRTestData.gen.dep" , OBJ_PATH+"/APRTestData.gen.vm.dep" , "3" } } ;

Target cpp4 = { "Abort.cpp" , "../../HCore/CCore/src/Abort.cpp" } ;
Target dcpp4 = { "Abort.dep" , OBJ_PATH+"/Abort.dep" } ;
Rule rdcpp4 = { {&cpp4,&obj} , {&dcpp4} , {&execpp4} } ;
Exe execpp4 = { "CC-DEP Abort.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Abort.o"
 ,"../../HCore/CCore/src/Abort.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Abort.dep"
} } ;

Target vdcpp4 = { "Abort.vm.dep" , OBJ_PATH+"/Abort.vm.dep" } ;
Rule rvdcpp4 = { {&dcpp4} , {&vdcpp4} , {&exedcpp4} } ;
Exe exedcpp4 = { "CC-VM-DEP Abort.cpp" , VMDEP , { OBJ_PATH+"/Abort.dep" , OBJ_PATH+"/Abort.vm.dep" , "4" } } ;

Target cpp5 = { "AbortMsgFunc.cpp" , "../../Simple/CCore/src/AbortMsgFunc.cpp" } ;
Target dcpp5 = { "AbortMsgFunc.dep" , OBJ_PATH+"/AbortMsgFunc.dep" } ;
Rule rdcpp5 = { {&cpp5,&obj} , {&dcpp5} , {&execpp5} } ;
Exe execpp5 = { "CC-DEP AbortMsgFunc.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/AbortMsgFunc.o"
 ,"../../Simple/CCore/src/AbortMsgFunc.cpp"
 ,"-MF"
 ,OBJ_PATH+"/AbortMsgFunc.dep"
} } ;

Target vdcpp5 = { "AbortMsgFunc.vm.dep" , OBJ_PATH+"/AbortMsgFunc.vm.dep" } ;
Rule rvdcpp5 = { {&dcpp5} , {&vdcpp5} , {&exedcpp5} } ;
Exe exedcpp5 = { "CC-VM-DEP AbortMsgFunc.cpp" , VMDEP , { OBJ_PATH+"/AbortMsgFunc.dep" , OBJ_PATH+"/AbortMsgFunc.vm.dep" , "5" } } ;

Target cpp6 = { "Activator.cpp" , "../../Desktop/Tools/CCore/src/./video/Activator.cpp" } ;
Target dcpp6 = { "Activator.dep" , OBJ_PATH+"/Activator.dep" } ;
Rule rdcpp6 = { {&cpp6,&obj} , {&dcpp6} , {&execpp6} } ;
Exe execpp6 = { "CC-DEP Activator.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Activator.o"
 ,"../../Desktop/Tools/CCore/src/./video/Activator.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Activator.dep"
} } ;

Target vdcpp6 = { "Activator.vm.dep" , OBJ_PATH+"/Activator.vm.dep" } ;
Rule rvdcpp6 = { {&dcpp6} , {&vdcpp6} , {&exedcpp6} } ;
Exe exedcpp6 = { "CC-VM-DEP Activator.cpp" , VMDEP , { OBJ_PATH+"/Activator.dep" , OBJ_PATH+"/Activator.vm.dep" , "6" } } ;

Target cpp7 = { "AntiSem.cpp" , "../../HCore/CCore/src/./task/AntiSem.cpp" } ;
Target dcpp7 = { "AntiSem.dep" , OBJ_PATH+"/AntiSem.dep" } ;
Rule rdcpp7 = { {&cpp7,&obj} , {&dcpp7} , {&execpp7} } ;
Exe execpp7 = { "CC-DEP AntiSem.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/AntiSem.o"
 ,"../../HCore/CCore/src/./task/AntiSem.cpp"
 ,"-MF"
 ,OBJ_PATH+"/AntiSem.dep"
} } ;

Target vdcpp7 = { "AntiSem.vm.dep" , OBJ_PATH+"/AntiSem.vm.dep" } ;
Rule rvdcpp7 = { {&dcpp7} , {&vdcpp7} , {&exedcpp7} } ;
Exe exedcpp7 = { "CC-VM-DEP AntiSem.cpp" , VMDEP , { OBJ_PATH+"/AntiSem.dep" , OBJ_PATH+"/AntiSem.vm.dep" , "7" } } ;

Target cpp8 = { "AnyPtr.cpp" , "../../Simple/CCore/src/AnyPtr.cpp" } ;
Target dcpp8 = { "AnyPtr.dep" , OBJ_PATH+"/AnyPtr.dep" } ;
Rule rdcpp8 = { {&cpp8,&obj} , {&dcpp8} , {&execpp8} } ;
Exe execpp8 = { "CC-DEP AnyPtr.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/AnyPtr.o"
 ,"../../Simple/CCore/src/AnyPtr.cpp"
 ,"-MF"
 ,OBJ_PATH+"/AnyPtr.dep"
} } ;

Target vdcpp8 = { "AnyPtr.vm.dep" , OBJ_PATH+"/AnyPtr.vm.dep" } ;
Rule rvdcpp8 = { {&dcpp8} , {&vdcpp8} , {&exedcpp8} } ;
Exe exedcpp8 = { "CC-VM-DEP AnyPtr.cpp" , VMDEP , { OBJ_PATH+"/AnyPtr.dep" , OBJ_PATH+"/AnyPtr.vm.dep" , "8" } } ;

Target cpp9 = { "AppMain.cpp" , "../../Desktop/App/CCore/src/./video/AppMain.cpp" } ;
Target dcpp9 = { "AppMain.dep" , OBJ_PATH+"/AppMain.dep" } ;
Rule rdcpp9 = { {&cpp9,&obj} , {&dcpp9} , {&execpp9} } ;
Exe execpp9 = { "CC-DEP AppMain.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/AppMain.o"
 ,"../../Desktop/App/CCore/src/./video/AppMain.cpp"
 ,"-MF"
 ,OBJ_PATH+"/AppMain.dep"
} } ;

Target vdcpp9 = { "AppMain.vm.dep" , OBJ_PATH+"/AppMain.vm.dep" } ;
Rule rvdcpp9 = { {&dcpp9} , {&vdcpp9} , {&exedcpp9} } ;
Exe exedcpp9 = { "CC-VM-DEP AppMain.cpp" , VMDEP , { OBJ_PATH+"/AppMain.dep" , OBJ_PATH+"/AppMain.vm.dep" , "9" } } ;

Target cpp10 = { "AppOpt.cpp" , "../../Desktop/App/CCore/src/./video/AppOpt.cpp" } ;
Target dcpp10 = { "AppOpt.dep" , OBJ_PATH+"/AppOpt.dep" } ;
Rule rdcpp10 = { {&cpp10,&obj} , {&dcpp10} , {&execpp10} } ;
Exe execpp10 = { "CC-DEP AppOpt.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/AppOpt.o"
 ,"../../Desktop/App/CCore/src/./video/AppOpt.cpp"
 ,"-MF"
 ,OBJ_PATH+"/AppOpt.dep"
} } ;

Target vdcpp10 = { "AppOpt.vm.dep" , OBJ_PATH+"/AppOpt.vm.dep" } ;
Rule rvdcpp10 = { {&dcpp10} , {&vdcpp10} , {&exedcpp10} } ;
Exe exedcpp10 = { "CC-VM-DEP AppOpt.cpp" , VMDEP , { OBJ_PATH+"/AppOpt.dep" , OBJ_PATH+"/AppOpt.vm.dep" , "10" } } ;

Target cpp11 = { "ApplicationBase.cpp" , "../../Desktop/App/CCore/src/./video/ApplicationBase.cpp" } ;
Target dcpp11 = { "ApplicationBase.dep" , OBJ_PATH+"/ApplicationBase.dep" } ;
Rule rdcpp11 = { {&cpp11,&obj} , {&dcpp11} , {&execpp11} } ;
Exe execpp11 = { "CC-DEP ApplicationBase.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ApplicationBase.o"
 ,"../../Desktop/App/CCore/src/./video/ApplicationBase.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ApplicationBase.dep"
} } ;

Target vdcpp11 = { "ApplicationBase.vm.dep" , OBJ_PATH+"/ApplicationBase.vm.dep" } ;
Rule rvdcpp11 = { {&dcpp11} , {&vdcpp11} , {&exedcpp11} } ;
Exe exedcpp11 = { "CC-VM-DEP ApplicationBase.cpp" , VMDEP , { OBJ_PATH+"/ApplicationBase.dep" , OBJ_PATH+"/ApplicationBase.vm.dep" , "11" } } ;

Target cpp12 = { "ApplyToList.cpp" , "../../Fundamental/CCore/src/./algon/ApplyToList.cpp" } ;
Target dcpp12 = { "ApplyToList.dep" , OBJ_PATH+"/ApplyToList.dep" } ;
Rule rdcpp12 = { {&cpp12,&obj} , {&dcpp12} , {&execpp12} } ;
Exe execpp12 = { "CC-DEP ApplyToList.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ApplyToList.o"
 ,"../../Fundamental/CCore/src/./algon/ApplyToList.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ApplyToList.dep"
} } ;

Target vdcpp12 = { "ApplyToList.vm.dep" , OBJ_PATH+"/ApplyToList.vm.dep" } ;
Rule rvdcpp12 = { {&dcpp12} , {&vdcpp12} , {&exedcpp12} } ;
Exe exedcpp12 = { "CC-VM-DEP ApplyToList.cpp" , VMDEP , { OBJ_PATH+"/ApplyToList.dep" , OBJ_PATH+"/ApplyToList.vm.dep" , "12" } } ;

Target cpp13 = { "ApplyToRange.cpp" , "../../Fundamental/CCore/src/./algon/ApplyToRange.cpp" } ;
Target dcpp13 = { "ApplyToRange.dep" , OBJ_PATH+"/ApplyToRange.dep" } ;
Rule rdcpp13 = { {&cpp13,&obj} , {&dcpp13} , {&execpp13} } ;
Exe execpp13 = { "CC-DEP ApplyToRange.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ApplyToRange.o"
 ,"../../Fundamental/CCore/src/./algon/ApplyToRange.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ApplyToRange.dep"
} } ;

Target vdcpp13 = { "ApplyToRange.vm.dep" , OBJ_PATH+"/ApplyToRange.vm.dep" } ;
Rule rvdcpp13 = { {&dcpp13} , {&vdcpp13} , {&exedcpp13} } ;
Exe exedcpp13 = { "CC-VM-DEP ApplyToRange.cpp" , VMDEP , { OBJ_PATH+"/ApplyToRange.dep" , OBJ_PATH+"/ApplyToRange.vm.dep" , "13" } } ;

Target cpp14 = { "Array.cpp" , "../../Fundamental/CCore/src/Array.cpp" } ;
Target dcpp14 = { "Array.dep" , OBJ_PATH+"/Array.dep" } ;
Rule rdcpp14 = { {&cpp14,&obj} , {&dcpp14} , {&execpp14} } ;
Exe execpp14 = { "CC-DEP Array.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Array.o"
 ,"../../Fundamental/CCore/src/Array.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Array.dep"
} } ;

Target vdcpp14 = { "Array.vm.dep" , OBJ_PATH+"/Array.vm.dep" } ;
Rule rvdcpp14 = { {&dcpp14} , {&vdcpp14} , {&exedcpp14} } ;
Exe exedcpp14 = { "CC-VM-DEP Array.cpp" , VMDEP , { OBJ_PATH+"/Array.dep" , OBJ_PATH+"/Array.vm.dep" , "14" } } ;

Target cpp15 = { "ArrayAlgo.cpp" , "../../Fundamental/CCore/src/./array/ArrayAlgo.cpp" } ;
Target dcpp15 = { "ArrayAlgo.dep" , OBJ_PATH+"/ArrayAlgo.dep" } ;
Rule rdcpp15 = { {&cpp15,&obj} , {&dcpp15} , {&execpp15} } ;
Exe execpp15 = { "CC-DEP ArrayAlgo.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ArrayAlgo.o"
 ,"../../Fundamental/CCore/src/./array/ArrayAlgo.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ArrayAlgo.dep"
} } ;

Target vdcpp15 = { "ArrayAlgo.vm.dep" , OBJ_PATH+"/ArrayAlgo.vm.dep" } ;
Rule rvdcpp15 = { {&dcpp15} , {&vdcpp15} , {&exedcpp15} } ;
Exe exedcpp15 = { "CC-VM-DEP ArrayAlgo.cpp" , VMDEP , { OBJ_PATH+"/ArrayAlgo.dep" , OBJ_PATH+"/ArrayAlgo.vm.dep" , "15" } } ;

Target cpp16 = { "ArrayBase.cpp" , "../../Fundamental/CCore/src/./array/ArrayBase.cpp" } ;
Target dcpp16 = { "ArrayBase.dep" , OBJ_PATH+"/ArrayBase.dep" } ;
Rule rdcpp16 = { {&cpp16,&obj} , {&dcpp16} , {&execpp16} } ;
Exe execpp16 = { "CC-DEP ArrayBase.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ArrayBase.o"
 ,"../../Fundamental/CCore/src/./array/ArrayBase.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ArrayBase.dep"
} } ;

Target vdcpp16 = { "ArrayBase.vm.dep" , OBJ_PATH+"/ArrayBase.vm.dep" } ;
Rule rvdcpp16 = { {&dcpp16} , {&vdcpp16} , {&exedcpp16} } ;
Exe exedcpp16 = { "CC-VM-DEP ArrayBase.cpp" , VMDEP , { OBJ_PATH+"/ArrayBase.dep" , OBJ_PATH+"/ArrayBase.vm.dep" , "16" } } ;

Target cpp17 = { "ArrayInsDel.cpp" , "../../Fundamental/CCore/src/./array/ArrayInsDel.cpp" } ;
Target dcpp17 = { "ArrayInsDel.dep" , OBJ_PATH+"/ArrayInsDel.dep" } ;
Rule rdcpp17 = { {&cpp17,&obj} , {&dcpp17} , {&execpp17} } ;
Exe execpp17 = { "CC-DEP ArrayInsDel.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ArrayInsDel.o"
 ,"../../Fundamental/CCore/src/./array/ArrayInsDel.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ArrayInsDel.dep"
} } ;

Target vdcpp17 = { "ArrayInsDel.vm.dep" , OBJ_PATH+"/ArrayInsDel.vm.dep" } ;
Rule rvdcpp17 = { {&dcpp17} , {&vdcpp17} , {&exedcpp17} } ;
Exe exedcpp17 = { "CC-VM-DEP ArrayInsDel.cpp" , VMDEP , { OBJ_PATH+"/ArrayInsDel.dep" , OBJ_PATH+"/ArrayInsDel.vm.dep" , "17" } } ;

Target cpp18 = { "AsyncBinaryFile.cpp" , "../../Applied/CCore/src/AsyncBinaryFile.cpp" } ;
Target dcpp18 = { "AsyncBinaryFile.dep" , OBJ_PATH+"/AsyncBinaryFile.dep" } ;
Rule rdcpp18 = { {&cpp18,&obj} , {&dcpp18} , {&execpp18} } ;
Exe execpp18 = { "CC-DEP AsyncBinaryFile.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/AsyncBinaryFile.o"
 ,"../../Applied/CCore/src/AsyncBinaryFile.cpp"
 ,"-MF"
 ,OBJ_PATH+"/AsyncBinaryFile.dep"
} } ;

Target vdcpp18 = { "AsyncBinaryFile.vm.dep" , OBJ_PATH+"/AsyncBinaryFile.vm.dep" } ;
Rule rvdcpp18 = { {&dcpp18} , {&vdcpp18} , {&exedcpp18} } ;
Exe exedcpp18 = { "CC-VM-DEP AsyncBinaryFile.cpp" , VMDEP , { OBJ_PATH+"/AsyncBinaryFile.dep" , OBJ_PATH+"/AsyncBinaryFile.vm.dep" , "18" } } ;

Target cpp19 = { "AsyncFile.cpp" , "../../Applied/CCore/src/AsyncFile.cpp" } ;
Target dcpp19 = { "AsyncFile.dep" , OBJ_PATH+"/AsyncFile.dep" } ;
Rule rdcpp19 = { {&cpp19,&obj} , {&dcpp19} , {&execpp19} } ;
Exe execpp19 = { "CC-DEP AsyncFile.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/AsyncFile.o"
 ,"../../Applied/CCore/src/AsyncFile.cpp"
 ,"-MF"
 ,OBJ_PATH+"/AsyncFile.dep"
} } ;

Target vdcpp19 = { "AsyncFile.vm.dep" , OBJ_PATH+"/AsyncFile.vm.dep" } ;
Rule rvdcpp19 = { {&dcpp19} , {&vdcpp19} , {&exedcpp19} } ;
Exe exedcpp19 = { "CC-VM-DEP AsyncFile.cpp" , VMDEP , { OBJ_PATH+"/AsyncFile.dep" , OBJ_PATH+"/AsyncFile.vm.dep" , "19" } } ;

Target cpp20 = { "AsyncFileDevice.cpp" , "../../HCore/CCore/src/AsyncFileDevice.cpp" } ;
Target dcpp20 = { "AsyncFileDevice.dep" , OBJ_PATH+"/AsyncFileDevice.dep" } ;
Rule rdcpp20 = { {&cpp20,&obj} , {&dcpp20} , {&execpp20} } ;
Exe execpp20 = { "CC-DEP AsyncFileDevice.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/AsyncFileDevice.o"
 ,"../../HCore/CCore/src/AsyncFileDevice.cpp"
 ,"-MF"
 ,OBJ_PATH+"/AsyncFileDevice.dep"
} } ;

Target vdcpp20 = { "AsyncFileDevice.vm.dep" , OBJ_PATH+"/AsyncFileDevice.vm.dep" } ;
Rule rvdcpp20 = { {&dcpp20} , {&vdcpp20} , {&exedcpp20} } ;
Exe exedcpp20 = { "CC-VM-DEP AsyncFileDevice.cpp" , VMDEP , { OBJ_PATH+"/AsyncFileDevice.dep" , OBJ_PATH+"/AsyncFileDevice.vm.dep" , "20" } } ;

Target cpp21 = { "AsyncFileToMem.cpp" , "../../Applied/CCore/src/AsyncFileToMem.cpp" } ;
Target dcpp21 = { "AsyncFileToMem.dep" , OBJ_PATH+"/AsyncFileToMem.dep" } ;
Rule rdcpp21 = { {&cpp21,&obj} , {&dcpp21} , {&execpp21} } ;
Exe execpp21 = { "CC-DEP AsyncFileToMem.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/AsyncFileToMem.o"
 ,"../../Applied/CCore/src/AsyncFileToMem.cpp"
 ,"-MF"
 ,OBJ_PATH+"/AsyncFileToMem.dep"
} } ;

Target vdcpp21 = { "AsyncFileToMem.vm.dep" , OBJ_PATH+"/AsyncFileToMem.vm.dep" } ;
Rule rvdcpp21 = { {&dcpp21} , {&vdcpp21} , {&exedcpp21} } ;
Exe exedcpp21 = { "CC-VM-DEP AsyncFileToMem.cpp" , VMDEP , { OBJ_PATH+"/AsyncFileToMem.dep" , OBJ_PATH+"/AsyncFileToMem.vm.dep" , "21" } } ;

Target cpp22 = { "AsyncUDPDevice.cpp" , "../../HCore/CCore/src/./net/AsyncUDPDevice.cpp" } ;
Target dcpp22 = { "AsyncUDPDevice.dep" , OBJ_PATH+"/AsyncUDPDevice.dep" } ;
Rule rdcpp22 = { {&cpp22,&obj} , {&dcpp22} , {&execpp22} } ;
Exe execpp22 = { "CC-DEP AsyncUDPDevice.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/AsyncUDPDevice.o"
 ,"../../HCore/CCore/src/./net/AsyncUDPDevice.cpp"
 ,"-MF"
 ,OBJ_PATH+"/AsyncUDPDevice.dep"
} } ;

Target vdcpp22 = { "AsyncUDPDevice.vm.dep" , OBJ_PATH+"/AsyncUDPDevice.vm.dep" } ;
Rule rvdcpp22 = { {&dcpp22} , {&vdcpp22} , {&exedcpp22} } ;
Exe exedcpp22 = { "CC-VM-DEP AsyncUDPDevice.cpp" , VMDEP , { OBJ_PATH+"/AsyncUDPDevice.dep" , OBJ_PATH+"/AsyncUDPDevice.vm.dep" , "22" } } ;

Target cpp23 = { "Atomic.cpp" , "../../Applied/CCore/src/./task/Atomic.cpp" } ;
Target dcpp23 = { "Atomic.dep" , OBJ_PATH+"/Atomic.dep" } ;
Rule rdcpp23 = { {&cpp23,&obj} , {&dcpp23} , {&execpp23} } ;
Exe execpp23 = { "CC-DEP Atomic.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Atomic.o"
 ,"../../Applied/CCore/src/./task/Atomic.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Atomic.dep"
} } ;

Target vdcpp23 = { "Atomic.vm.dep" , OBJ_PATH+"/Atomic.vm.dep" } ;
Rule rvdcpp23 = { {&dcpp23} , {&vdcpp23} , {&exedcpp23} } ;
Exe exedcpp23 = { "CC-VM-DEP Atomic.cpp" , VMDEP , { OBJ_PATH+"/Atomic.dep" , OBJ_PATH+"/Atomic.vm.dep" , "23" } } ;

Target cpp24 = { "AtomicRefArray.cpp" , "../../Fundamental/CCore/src/./array/AtomicRefArray.cpp" } ;
Target dcpp24 = { "AtomicRefArray.dep" , OBJ_PATH+"/AtomicRefArray.dep" } ;
Rule rdcpp24 = { {&cpp24,&obj} , {&dcpp24} , {&execpp24} } ;
Exe execpp24 = { "CC-DEP AtomicRefArray.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/AtomicRefArray.o"
 ,"../../Fundamental/CCore/src/./array/AtomicRefArray.cpp"
 ,"-MF"
 ,OBJ_PATH+"/AtomicRefArray.dep"
} } ;

Target vdcpp24 = { "AtomicRefArray.vm.dep" , OBJ_PATH+"/AtomicRefArray.vm.dep" } ;
Rule rvdcpp24 = { {&dcpp24} , {&vdcpp24} , {&exedcpp24} } ;
Exe exedcpp24 = { "CC-VM-DEP AtomicRefArray.cpp" , VMDEP , { OBJ_PATH+"/AtomicRefArray.dep" , OBJ_PATH+"/AtomicRefArray.vm.dep" , "24" } } ;

Target cpp25 = { "AttachmentHost.cpp" , "../../Fundamental/CCore/src/AttachmentHost.cpp" } ;
Target dcpp25 = { "AttachmentHost.dep" , OBJ_PATH+"/AttachmentHost.dep" } ;
Rule rdcpp25 = { {&cpp25,&obj} , {&dcpp25} , {&execpp25} } ;
Exe execpp25 = { "CC-DEP AttachmentHost.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/AttachmentHost.o"
 ,"../../Fundamental/CCore/src/AttachmentHost.cpp"
 ,"-MF"
 ,OBJ_PATH+"/AttachmentHost.dep"
} } ;

Target vdcpp25 = { "AttachmentHost.vm.dep" , OBJ_PATH+"/AttachmentHost.vm.dep" } ;
Rule rvdcpp25 = { {&dcpp25} , {&vdcpp25} , {&exedcpp25} } ;
Exe exedcpp25 = { "CC-VM-DEP AttachmentHost.cpp" , VMDEP , { OBJ_PATH+"/AttachmentHost.dep" , OBJ_PATH+"/AttachmentHost.vm.dep" , "25" } } ;

Target cpp26 = { "AutoCast.cpp" , "../../Simple/CCore/src/./gadget/AutoCast.cpp" } ;
Target dcpp26 = { "AutoCast.dep" , OBJ_PATH+"/AutoCast.dep" } ;
Rule rdcpp26 = { {&cpp26,&obj} , {&dcpp26} , {&execpp26} } ;
Exe execpp26 = { "CC-DEP AutoCast.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/AutoCast.o"
 ,"../../Simple/CCore/src/./gadget/AutoCast.cpp"
 ,"-MF"
 ,OBJ_PATH+"/AutoCast.dep"
} } ;

Target vdcpp26 = { "AutoCast.vm.dep" , OBJ_PATH+"/AutoCast.vm.dep" } ;
Rule rvdcpp26 = { {&dcpp26} , {&vdcpp26} , {&exedcpp26} } ;
Exe exedcpp26 = { "CC-VM-DEP AutoCast.cpp" , VMDEP , { OBJ_PATH+"/AutoCast.dep" , OBJ_PATH+"/AutoCast.vm.dep" , "26" } } ;

Target cpp27 = { "AutoGlobal.cpp" , "../../Fundamental/CCore/src/AutoGlobal.cpp" } ;
Target dcpp27 = { "AutoGlobal.dep" , OBJ_PATH+"/AutoGlobal.dep" } ;
Rule rdcpp27 = { {&cpp27,&obj} , {&dcpp27} , {&execpp27} } ;
Exe execpp27 = { "CC-DEP AutoGlobal.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/AutoGlobal.o"
 ,"../../Fundamental/CCore/src/AutoGlobal.cpp"
 ,"-MF"
 ,OBJ_PATH+"/AutoGlobal.dep"
} } ;

Target vdcpp27 = { "AutoGlobal.vm.dep" , OBJ_PATH+"/AutoGlobal.vm.dep" } ;
Rule rvdcpp27 = { {&dcpp27} , {&vdcpp27} , {&exedcpp27} } ;
Exe exedcpp27 = { "CC-VM-DEP AutoGlobal.cpp" , VMDEP , { OBJ_PATH+"/AutoGlobal.dep" , OBJ_PATH+"/AutoGlobal.vm.dep" , "27" } } ;

Target cpp28 = { "BaseRangeAlgo.cpp" , "../../Fundamental/CCore/src/./algon/BaseRangeAlgo.cpp" } ;
Target dcpp28 = { "BaseRangeAlgo.dep" , OBJ_PATH+"/BaseRangeAlgo.dep" } ;
Rule rdcpp28 = { {&cpp28,&obj} , {&dcpp28} , {&execpp28} } ;
Exe execpp28 = { "CC-DEP BaseRangeAlgo.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/BaseRangeAlgo.o"
 ,"../../Fundamental/CCore/src/./algon/BaseRangeAlgo.cpp"
 ,"-MF"
 ,OBJ_PATH+"/BaseRangeAlgo.dep"
} } ;

Target vdcpp28 = { "BaseRangeAlgo.vm.dep" , OBJ_PATH+"/BaseRangeAlgo.vm.dep" } ;
Rule rvdcpp28 = { {&dcpp28} , {&vdcpp28} , {&exedcpp28} } ;
Exe exedcpp28 = { "CC-VM-DEP BaseRangeAlgo.cpp" , VMDEP , { OBJ_PATH+"/BaseRangeAlgo.dep" , OBJ_PATH+"/BaseRangeAlgo.vm.dep" , "28" } } ;

Target cpp29 = { "BestSearch.cpp" , "../../Fundamental/CCore/src/./algon/BestSearch.cpp" } ;
Target dcpp29 = { "BestSearch.dep" , OBJ_PATH+"/BestSearch.dep" } ;
Rule rdcpp29 = { {&cpp29,&obj} , {&dcpp29} , {&execpp29} } ;
Exe execpp29 = { "CC-DEP BestSearch.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/BestSearch.o"
 ,"../../Fundamental/CCore/src/./algon/BestSearch.cpp"
 ,"-MF"
 ,OBJ_PATH+"/BestSearch.dep"
} } ;

Target vdcpp29 = { "BestSearch.vm.dep" , OBJ_PATH+"/BestSearch.vm.dep" } ;
Rule rvdcpp29 = { {&dcpp29} , {&vdcpp29} , {&exedcpp29} } ;
Exe exedcpp29 = { "CC-VM-DEP BestSearch.cpp" , VMDEP , { OBJ_PATH+"/BestSearch.dep" , OBJ_PATH+"/BestSearch.vm.dep" , "29" } } ;

Target cpp30 = { "BinFileToRead.cpp" , "../../Fundamental/CCore/src/BinFileToRead.cpp" } ;
Target dcpp30 = { "BinFileToRead.dep" , OBJ_PATH+"/BinFileToRead.dep" } ;
Rule rdcpp30 = { {&cpp30,&obj} , {&dcpp30} , {&execpp30} } ;
Exe execpp30 = { "CC-DEP BinFileToRead.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/BinFileToRead.o"
 ,"../../Fundamental/CCore/src/BinFileToRead.cpp"
 ,"-MF"
 ,OBJ_PATH+"/BinFileToRead.dep"
} } ;

Target vdcpp30 = { "BinFileToRead.vm.dep" , OBJ_PATH+"/BinFileToRead.vm.dep" } ;
Rule rvdcpp30 = { {&dcpp30} , {&vdcpp30} , {&exedcpp30} } ;
Exe exedcpp30 = { "CC-VM-DEP BinFileToRead.cpp" , VMDEP , { OBJ_PATH+"/BinFileToRead.dep" , OBJ_PATH+"/BinFileToRead.vm.dep" , "30" } } ;

Target cpp31 = { "BinaryFile.cpp" , "../../HCore/CCore/src/BinaryFile.cpp" } ;
Target dcpp31 = { "BinaryFile.dep" , OBJ_PATH+"/BinaryFile.dep" } ;
Rule rdcpp31 = { {&cpp31,&obj} , {&dcpp31} , {&execpp31} } ;
Exe execpp31 = { "CC-DEP BinaryFile.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/BinaryFile.o"
 ,"../../HCore/CCore/src/BinaryFile.cpp"
 ,"-MF"
 ,OBJ_PATH+"/BinaryFile.dep"
} } ;

Target vdcpp31 = { "BinaryFile.vm.dep" , OBJ_PATH+"/BinaryFile.vm.dep" } ;
Rule rvdcpp31 = { {&dcpp31} , {&vdcpp31} , {&exedcpp31} } ;
Exe exedcpp31 = { "CC-VM-DEP BinaryFile.cpp" , VMDEP , { OBJ_PATH+"/BinaryFile.dep" , OBJ_PATH+"/BinaryFile.vm.dep" , "31" } } ;

Target cpp32 = { "BinarySearch.cpp" , "../../Fundamental/CCore/src/./algon/BinarySearch.cpp" } ;
Target dcpp32 = { "BinarySearch.dep" , OBJ_PATH+"/BinarySearch.dep" } ;
Rule rdcpp32 = { {&cpp32,&obj} , {&dcpp32} , {&execpp32} } ;
Exe execpp32 = { "CC-DEP BinarySearch.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/BinarySearch.o"
 ,"../../Fundamental/CCore/src/./algon/BinarySearch.cpp"
 ,"-MF"
 ,OBJ_PATH+"/BinarySearch.dep"
} } ;

Target vdcpp32 = { "BinarySearch.vm.dep" , OBJ_PATH+"/BinarySearch.vm.dep" } ;
Rule rvdcpp32 = { {&dcpp32} , {&vdcpp32} , {&exedcpp32} } ;
Exe exedcpp32 = { "CC-VM-DEP BinarySearch.cpp" , VMDEP , { OBJ_PATH+"/BinarySearch.dep" , OBJ_PATH+"/BinarySearch.vm.dep" , "32" } } ;

Target cpp33 = { "BindBagProxy.cpp" , "../../Desktop/Lib/CCore/src/./video/BindBagProxy.cpp" } ;
Target dcpp33 = { "BindBagProxy.dep" , OBJ_PATH+"/BindBagProxy.dep" } ;
Rule rdcpp33 = { {&cpp33,&obj} , {&dcpp33} , {&execpp33} } ;
Exe execpp33 = { "CC-DEP BindBagProxy.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/BindBagProxy.o"
 ,"../../Desktop/Lib/CCore/src/./video/BindBagProxy.cpp"
 ,"-MF"
 ,OBJ_PATH+"/BindBagProxy.dep"
} } ;

Target vdcpp33 = { "BindBagProxy.vm.dep" , OBJ_PATH+"/BindBagProxy.vm.dep" } ;
Rule rvdcpp33 = { {&dcpp33} , {&vdcpp33} , {&exedcpp33} } ;
Exe exedcpp33 = { "CC-VM-DEP BindBagProxy.cpp" , VMDEP , { OBJ_PATH+"/BindBagProxy.dep" , OBJ_PATH+"/BindBagProxy.vm.dep" , "33" } } ;

Target cpp34 = { "Bitmap.cpp" , "../../Desktop/Tools/CCore/src/./video/Bitmap.cpp" } ;
Target dcpp34 = { "Bitmap.dep" , OBJ_PATH+"/Bitmap.dep" } ;
Rule rdcpp34 = { {&cpp34,&obj} , {&dcpp34} , {&execpp34} } ;
Exe execpp34 = { "CC-DEP Bitmap.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Bitmap.o"
 ,"../../Desktop/Tools/CCore/src/./video/Bitmap.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Bitmap.dep"
} } ;

Target vdcpp34 = { "Bitmap.vm.dep" , OBJ_PATH+"/Bitmap.vm.dep" } ;
Rule rvdcpp34 = { {&dcpp34} , {&vdcpp34} , {&exedcpp34} } ;
Exe exedcpp34 = { "CC-VM-DEP Bitmap.cpp" , VMDEP , { OBJ_PATH+"/Bitmap.dep" , OBJ_PATH+"/Bitmap.vm.dep" , "34" } } ;

Target cpp35 = { "BlockCipher.cpp" , "../../Applied/CCore/src/./crypton/BlockCipher.cpp" } ;
Target dcpp35 = { "BlockCipher.dep" , OBJ_PATH+"/BlockCipher.dep" } ;
Rule rdcpp35 = { {&cpp35,&obj} , {&dcpp35} , {&execpp35} } ;
Exe execpp35 = { "CC-DEP BlockCipher.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/BlockCipher.o"
 ,"../../Applied/CCore/src/./crypton/BlockCipher.cpp"
 ,"-MF"
 ,OBJ_PATH+"/BlockCipher.dep"
} } ;

Target vdcpp35 = { "BlockCipher.vm.dep" , OBJ_PATH+"/BlockCipher.vm.dep" } ;
Rule rvdcpp35 = { {&dcpp35} , {&vdcpp35} , {&exedcpp35} } ;
Exe exedcpp35 = { "CC-VM-DEP BlockCipher.cpp" , VMDEP , { OBJ_PATH+"/BlockCipher.dep" , OBJ_PATH+"/BlockCipher.vm.dep" , "35" } } ;

Target cpp36 = { "BlockFifo.cpp" , "../../Simple/CCore/src/BlockFifo.cpp" } ;
Target dcpp36 = { "BlockFifo.dep" , OBJ_PATH+"/BlockFifo.dep" } ;
Rule rdcpp36 = { {&cpp36,&obj} , {&dcpp36} , {&execpp36} } ;
Exe execpp36 = { "CC-DEP BlockFifo.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/BlockFifo.o"
 ,"../../Simple/CCore/src/BlockFifo.cpp"
 ,"-MF"
 ,OBJ_PATH+"/BlockFifo.dep"
} } ;

Target vdcpp36 = { "BlockFifo.vm.dep" , OBJ_PATH+"/BlockFifo.vm.dep" } ;
Rule rvdcpp36 = { {&dcpp36} , {&vdcpp36} , {&exedcpp36} } ;
Exe exedcpp36 = { "CC-VM-DEP BlockFifo.cpp" , VMDEP , { OBJ_PATH+"/BlockFifo.dep" , OBJ_PATH+"/BlockFifo.vm.dep" , "36" } } ;

Target cpp37 = { "Book.cpp" , "../../Desktop/Lib/CCore/src/./video/book/Book.cpp" } ;
Target dcpp37 = { "Book.dep" , OBJ_PATH+"/Book.dep" } ;
Rule rdcpp37 = { {&cpp37,&obj} , {&dcpp37} , {&execpp37} } ;
Exe execpp37 = { "CC-DEP Book.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Book.o"
 ,"../../Desktop/Lib/CCore/src/./video/book/Book.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Book.dep"
} } ;

Target vdcpp37 = { "Book.vm.dep" , OBJ_PATH+"/Book.vm.dep" } ;
Rule rvdcpp37 = { {&dcpp37} , {&vdcpp37} , {&exedcpp37} } ;
Exe exedcpp37 = { "CC-VM-DEP Book.cpp" , VMDEP , { OBJ_PATH+"/Book.dep" , OBJ_PATH+"/Book.vm.dep" , "37" } } ;

Target cpp38 = { "BookAppMain.cpp" , "../../Desktop/App/CCore/src/./video/BookAppMain.cpp" } ;
Target dcpp38 = { "BookAppMain.dep" , OBJ_PATH+"/BookAppMain.dep" } ;
Rule rdcpp38 = { {&cpp38,&obj} , {&dcpp38} , {&execpp38} } ;
Exe execpp38 = { "CC-DEP BookAppMain.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/BookAppMain.o"
 ,"../../Desktop/App/CCore/src/./video/BookAppMain.cpp"
 ,"-MF"
 ,OBJ_PATH+"/BookAppMain.dep"
} } ;

Target vdcpp38 = { "BookAppMain.vm.dep" , OBJ_PATH+"/BookAppMain.vm.dep" } ;
Rule rvdcpp38 = { {&dcpp38} , {&vdcpp38} , {&exedcpp38} } ;
Exe exedcpp38 = { "CC-VM-DEP BookAppMain.cpp" , VMDEP , { OBJ_PATH+"/BookAppMain.dep" , OBJ_PATH+"/BookAppMain.vm.dep" , "38" } } ;

Target cpp39 = { "BookClient.cpp" , "../../Desktop/Lib/CCore/src/./video/book/BookClient.cpp" } ;
Target dcpp39 = { "BookClient.dep" , OBJ_PATH+"/BookClient.dep" } ;
Rule rdcpp39 = { {&cpp39,&obj} , {&dcpp39} , {&execpp39} } ;
Exe execpp39 = { "CC-DEP BookClient.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/BookClient.o"
 ,"../../Desktop/Lib/CCore/src/./video/book/BookClient.cpp"
 ,"-MF"
 ,OBJ_PATH+"/BookClient.dep"
} } ;

Target vdcpp39 = { "BookClient.vm.dep" , OBJ_PATH+"/BookClient.vm.dep" } ;
Rule rvdcpp39 = { {&dcpp39} , {&vdcpp39} , {&exedcpp39} } ;
Exe exedcpp39 = { "CC-VM-DEP BookClient.cpp" , VMDEP , { OBJ_PATH+"/BookClient.dep" , OBJ_PATH+"/BookClient.vm.dep" , "39" } } ;

Target cpp40 = { "BookFrame.cpp" , "../../Desktop/Lib/CCore/src/./video/BookFrame.cpp" } ;
Target dcpp40 = { "BookFrame.dep" , OBJ_PATH+"/BookFrame.dep" } ;
Rule rdcpp40 = { {&cpp40,&obj} , {&dcpp40} , {&execpp40} } ;
Exe execpp40 = { "CC-DEP BookFrame.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/BookFrame.o"
 ,"../../Desktop/Lib/CCore/src/./video/BookFrame.cpp"
 ,"-MF"
 ,OBJ_PATH+"/BookFrame.dep"
} } ;

Target vdcpp40 = { "BookFrame.vm.dep" , OBJ_PATH+"/BookFrame.vm.dep" } ;
Rule rvdcpp40 = { {&dcpp40} , {&vdcpp40} , {&exedcpp40} } ;
Exe exedcpp40 = { "CC-VM-DEP BookFrame.cpp" , VMDEP , { OBJ_PATH+"/BookFrame.dep" , OBJ_PATH+"/BookFrame.vm.dep" , "40" } } ;

Target cpp41 = { "BookWindow.cpp" , "../../Desktop/Lib/CCore/src/./video/book/BookWindow.cpp" } ;
Target dcpp41 = { "BookWindow.dep" , OBJ_PATH+"/BookWindow.dep" } ;
Rule rdcpp41 = { {&cpp41,&obj} , {&dcpp41} , {&execpp41} } ;
Exe execpp41 = { "CC-DEP BookWindow.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/BookWindow.o"
 ,"../../Desktop/Lib/CCore/src/./video/book/BookWindow.cpp"
 ,"-MF"
 ,OBJ_PATH+"/BookWindow.dep"
} } ;

Target vdcpp41 = { "BookWindow.vm.dep" , OBJ_PATH+"/BookWindow.vm.dep" } ;
Rule rvdcpp41 = { {&dcpp41} , {&vdcpp41} , {&exedcpp41} } ;
Exe exedcpp41 = { "CC-VM-DEP BookWindow.cpp" , VMDEP , { OBJ_PATH+"/BookWindow.dep" , OBJ_PATH+"/BookWindow.vm.dep" , "41" } } ;

Target cpp42 = { "Bridge.cpp" , "../../Applied/CCore/src/./net/Bridge.cpp" } ;
Target dcpp42 = { "Bridge.dep" , OBJ_PATH+"/Bridge.dep" } ;
Rule rdcpp42 = { {&cpp42,&obj} , {&dcpp42} , {&execpp42} } ;
Exe execpp42 = { "CC-DEP Bridge.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Bridge.o"
 ,"../../Applied/CCore/src/./net/Bridge.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Bridge.dep"
} } ;

Target vdcpp42 = { "Bridge.vm.dep" , OBJ_PATH+"/Bridge.vm.dep" } ;
Rule rvdcpp42 = { {&dcpp42} , {&vdcpp42} , {&exedcpp42} } ;
Exe exedcpp42 = { "CC-VM-DEP Bridge.cpp" , VMDEP , { OBJ_PATH+"/Bridge.dep" , OBJ_PATH+"/Bridge.vm.dep" , "42" } } ;

Target cpp43 = { "ButtonId.cpp" , "../../Desktop/Tools/CCore/src/./video/ButtonId.cpp" } ;
Target dcpp43 = { "ButtonId.dep" , OBJ_PATH+"/ButtonId.dep" } ;
Rule rdcpp43 = { {&cpp43,&obj} , {&dcpp43} , {&execpp43} } ;
Exe execpp43 = { "CC-DEP ButtonId.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ButtonId.o"
 ,"../../Desktop/Tools/CCore/src/./video/ButtonId.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ButtonId.dep"
} } ;

Target vdcpp43 = { "ButtonId.vm.dep" , OBJ_PATH+"/ButtonId.vm.dep" } ;
Rule rvdcpp43 = { {&dcpp43} , {&vdcpp43} , {&exedcpp43} } ;
Exe exedcpp43 = { "CC-VM-DEP ButtonId.cpp" , VMDEP , { OBJ_PATH+"/ButtonId.dep" , OBJ_PATH+"/ButtonId.vm.dep" , "43" } } ;

Target cpp44 = { "CancelPacketList.cpp" , "../../Applied/CCore/src/CancelPacketList.cpp" } ;
Target dcpp44 = { "CancelPacketList.dep" , OBJ_PATH+"/CancelPacketList.dep" } ;
Rule rdcpp44 = { {&cpp44,&obj} , {&dcpp44} , {&execpp44} } ;
Exe execpp44 = { "CC-DEP CancelPacketList.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/CancelPacketList.o"
 ,"../../Applied/CCore/src/CancelPacketList.cpp"
 ,"-MF"
 ,OBJ_PATH+"/CancelPacketList.dep"
} } ;

Target vdcpp44 = { "CancelPacketList.vm.dep" , OBJ_PATH+"/CancelPacketList.vm.dep" } ;
Rule rvdcpp44 = { {&dcpp44} , {&vdcpp44} , {&exedcpp44} } ;
Exe exedcpp44 = { "CC-VM-DEP CancelPacketList.cpp" , VMDEP , { OBJ_PATH+"/CancelPacketList.dep" , OBJ_PATH+"/CancelPacketList.vm.dep" , "44" } } ;

Target cpp45 = { "CapString.cpp" , "../../Simple/CCore/src/CapString.cpp" } ;
Target dcpp45 = { "CapString.dep" , OBJ_PATH+"/CapString.dep" } ;
Rule rdcpp45 = { {&cpp45,&obj} , {&dcpp45} , {&execpp45} } ;
Exe execpp45 = { "CC-DEP CapString.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/CapString.o"
 ,"../../Simple/CCore/src/CapString.cpp"
 ,"-MF"
 ,OBJ_PATH+"/CapString.dep"
} } ;

Target vdcpp45 = { "CapString.vm.dep" , OBJ_PATH+"/CapString.vm.dep" } ;
Rule rvdcpp45 = { {&dcpp45} , {&vdcpp45} , {&exedcpp45} } ;
Exe exedcpp45 = { "CC-VM-DEP CapString.cpp" , VMDEP , { OBJ_PATH+"/CapString.dep" , OBJ_PATH+"/CapString.vm.dep" , "45" } } ;

Target cpp46 = { "CharProp.cpp" , "../../Fundamental/CCore/src/CharProp.cpp" } ;
Target dcpp46 = { "CharProp.dep" , OBJ_PATH+"/CharProp.dep" } ;
Rule rdcpp46 = { {&cpp46,&obj} , {&dcpp46} , {&execpp46} } ;
Exe execpp46 = { "CC-DEP CharProp.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/CharProp.o"
 ,"../../Fundamental/CCore/src/CharProp.cpp"
 ,"-MF"
 ,OBJ_PATH+"/CharProp.dep"
} } ;

Target vdcpp46 = { "CharProp.vm.dep" , OBJ_PATH+"/CharProp.vm.dep" } ;
Rule rvdcpp46 = { {&dcpp46} , {&vdcpp46} , {&exedcpp46} } ;
Exe exedcpp46 = { "CC-VM-DEP CharProp.cpp" , VMDEP , { OBJ_PATH+"/CharProp.dep" , OBJ_PATH+"/CharProp.vm.dep" , "46" } } ;

Target cpp47 = { "CharUtils.cpp" , "../../Fundamental/CCore/src/CharUtils.cpp" } ;
Target dcpp47 = { "CharUtils.dep" , OBJ_PATH+"/CharUtils.dep" } ;
Rule rdcpp47 = { {&cpp47,&obj} , {&dcpp47} , {&execpp47} } ;
Exe execpp47 = { "CC-DEP CharUtils.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/CharUtils.o"
 ,"../../Fundamental/CCore/src/CharUtils.cpp"
 ,"-MF"
 ,OBJ_PATH+"/CharUtils.dep"
} } ;

Target vdcpp47 = { "CharUtils.vm.dep" , OBJ_PATH+"/CharUtils.vm.dep" } ;
Rule rvdcpp47 = { {&dcpp47} , {&vdcpp47} , {&exedcpp47} } ;
Exe exedcpp47 = { "CC-VM-DEP CharUtils.cpp" , VMDEP , { OBJ_PATH+"/CharUtils.dep" , OBJ_PATH+"/CharUtils.vm.dep" , "47" } } ;

Target cpp48 = { "CheckPlatformBase.cpp" , "../../Simple/CCore/src/./base/CheckPlatformBase.cpp" } ;
Target dcpp48 = { "CheckPlatformBase.dep" , OBJ_PATH+"/CheckPlatformBase.dep" } ;
Rule rdcpp48 = { {&cpp48,&obj} , {&dcpp48} , {&execpp48} } ;
Exe execpp48 = { "CC-DEP CheckPlatformBase.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/CheckPlatformBase.o"
 ,"../../Simple/CCore/src/./base/CheckPlatformBase.cpp"
 ,"-MF"
 ,OBJ_PATH+"/CheckPlatformBase.dep"
} } ;

Target vdcpp48 = { "CheckPlatformBase.vm.dep" , OBJ_PATH+"/CheckPlatformBase.vm.dep" } ;
Rule rvdcpp48 = { {&dcpp48} , {&vdcpp48} , {&exedcpp48} } ;
Exe exedcpp48 = { "CC-VM-DEP CheckPlatformBase.cpp" , VMDEP , { OBJ_PATH+"/CheckPlatformBase.dep" , OBJ_PATH+"/CheckPlatformBase.vm.dep" , "48" } } ;

Target cpp49 = { "CheckedData.cpp" , "../../Applied/CCore/src/./net/CheckedData.cpp" } ;
Target dcpp49 = { "CheckedData.dep" , OBJ_PATH+"/CheckedData.dep" } ;
Rule rdcpp49 = { {&cpp49,&obj} , {&dcpp49} , {&execpp49} } ;
Exe execpp49 = { "CC-DEP CheckedData.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/CheckedData.o"
 ,"../../Applied/CCore/src/./net/CheckedData.cpp"
 ,"-MF"
 ,OBJ_PATH+"/CheckedData.dep"
} } ;

Target vdcpp49 = { "CheckedData.vm.dep" , OBJ_PATH+"/CheckedData.vm.dep" } ;
Rule rvdcpp49 = { {&dcpp49} , {&vdcpp49} , {&exedcpp49} } ;
Exe exedcpp49 = { "CC-VM-DEP CheckedData.cpp" , VMDEP , { OBJ_PATH+"/CheckedData.dep" , OBJ_PATH+"/CheckedData.vm.dep" , "49" } } ;

Target cpp50 = { "Classification.cpp" , "../../Simple/CCore/src/./gadget/Classification.cpp" } ;
Target dcpp50 = { "Classification.dep" , OBJ_PATH+"/Classification.dep" } ;
Rule rdcpp50 = { {&cpp50,&obj} , {&dcpp50} , {&execpp50} } ;
Exe execpp50 = { "CC-DEP Classification.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Classification.o"
 ,"../../Simple/CCore/src/./gadget/Classification.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Classification.dep"
} } ;

Target vdcpp50 = { "Classification.vm.dep" , OBJ_PATH+"/Classification.vm.dep" } ;
Rule rvdcpp50 = { {&dcpp50} , {&vdcpp50} , {&exedcpp50} } ;
Exe exedcpp50 = { "CC-VM-DEP Classification.cpp" , VMDEP , { OBJ_PATH+"/Classification.dep" , OBJ_PATH+"/Classification.vm.dep" , "50" } } ;

Target cpp51 = { "CmdInput.cpp" , "../../Applied/CCore/src/CmdInput.cpp" } ;
Target dcpp51 = { "CmdInput.dep" , OBJ_PATH+"/CmdInput.dep" } ;
Rule rdcpp51 = { {&cpp51,&obj} , {&dcpp51} , {&execpp51} } ;
Exe execpp51 = { "CC-DEP CmdInput.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/CmdInput.o"
 ,"../../Applied/CCore/src/CmdInput.cpp"
 ,"-MF"
 ,OBJ_PATH+"/CmdInput.dep"
} } ;

Target vdcpp51 = { "CmdInput.vm.dep" , OBJ_PATH+"/CmdInput.vm.dep" } ;
Rule rvdcpp51 = { {&dcpp51} , {&vdcpp51} , {&exedcpp51} } ;
Exe exedcpp51 = { "CC-VM-DEP CmdInput.cpp" , VMDEP , { OBJ_PATH+"/CmdInput.dep" , OBJ_PATH+"/CmdInput.vm.dep" , "51" } } ;

Target cpp52 = { "Cmp.cpp" , "../../Simple/CCore/src/Cmp.cpp" } ;
Target dcpp52 = { "Cmp.dep" , OBJ_PATH+"/Cmp.dep" } ;
Rule rdcpp52 = { {&cpp52,&obj} , {&dcpp52} , {&execpp52} } ;
Exe execpp52 = { "CC-DEP Cmp.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Cmp.o"
 ,"../../Simple/CCore/src/Cmp.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Cmp.dep"
} } ;

Target vdcpp52 = { "Cmp.vm.dep" , OBJ_PATH+"/Cmp.vm.dep" } ;
Rule rvdcpp52 = { {&dcpp52} , {&vdcpp52} , {&exedcpp52} } ;
Exe exedcpp52 = { "CC-VM-DEP Cmp.cpp" , VMDEP , { OBJ_PATH+"/Cmp.dep" , OBJ_PATH+"/Cmp.vm.dep" , "52" } } ;

Target cpp53 = { "Collector.cpp" , "../../Fundamental/CCore/src/./array/Collector.cpp" } ;
Target dcpp53 = { "Collector.dep" , OBJ_PATH+"/Collector.dep" } ;
Rule rdcpp53 = { {&cpp53,&obj} , {&dcpp53} , {&execpp53} } ;
Exe execpp53 = { "CC-DEP Collector.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Collector.o"
 ,"../../Fundamental/CCore/src/./array/Collector.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Collector.dep"
} } ;

Target vdcpp53 = { "Collector.vm.dep" , OBJ_PATH+"/Collector.vm.dep" } ;
Rule rvdcpp53 = { {&dcpp53} , {&vdcpp53} , {&exedcpp53} } ;
Exe exedcpp53 = { "CC-VM-DEP Collector.cpp" , VMDEP , { OBJ_PATH+"/Collector.dep" , OBJ_PATH+"/Collector.vm.dep" , "53" } } ;

Target cpp54 = { "Color.cpp" , "../../Applied/CCore/src/./video/Color.cpp" } ;
Target dcpp54 = { "Color.dep" , OBJ_PATH+"/Color.dep" } ;
Rule rdcpp54 = { {&cpp54,&obj} , {&dcpp54} , {&execpp54} } ;
Exe execpp54 = { "CC-DEP Color.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Color.o"
 ,"../../Applied/CCore/src/./video/Color.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Color.dep"
} } ;

Target vdcpp54 = { "Color.vm.dep" , OBJ_PATH+"/Color.vm.dep" } ;
Rule rvdcpp54 = { {&dcpp54} , {&vdcpp54} , {&exedcpp54} } ;
Exe exedcpp54 = { "CC-VM-DEP Color.cpp" , VMDEP , { OBJ_PATH+"/Color.dep" , OBJ_PATH+"/Color.vm.dep" , "54" } } ;

Target cpp55 = { "ColorEdit.cpp" , "../../Desktop/Lib/CCore/src/./video/pref/ColorEdit.cpp" } ;
Target dcpp55 = { "ColorEdit.dep" , OBJ_PATH+"/ColorEdit.dep" } ;
Rule rdcpp55 = { {&cpp55,&obj} , {&dcpp55} , {&execpp55} } ;
Exe execpp55 = { "CC-DEP ColorEdit.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ColorEdit.o"
 ,"../../Desktop/Lib/CCore/src/./video/pref/ColorEdit.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ColorEdit.dep"
} } ;

Target vdcpp55 = { "ColorEdit.vm.dep" , OBJ_PATH+"/ColorEdit.vm.dep" } ;
Rule rvdcpp55 = { {&dcpp55} , {&vdcpp55} , {&exedcpp55} } ;
Exe exedcpp55 = { "CC-VM-DEP ColorEdit.cpp" , VMDEP , { OBJ_PATH+"/ColorEdit.dep" , OBJ_PATH+"/ColorEdit.vm.dep" , "55" } } ;

Target cpp56 = { "ColorField.cpp" , "../../Desktop/Draw/CCore/src/./video/ColorField.cpp" } ;
Target dcpp56 = { "ColorField.dep" , OBJ_PATH+"/ColorField.dep" } ;
Rule rdcpp56 = { {&cpp56,&obj} , {&dcpp56} , {&execpp56} } ;
Exe execpp56 = { "CC-DEP ColorField.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ColorField.o"
 ,"../../Desktop/Draw/CCore/src/./video/ColorField.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ColorField.dep"
} } ;

Target vdcpp56 = { "ColorField.vm.dep" , OBJ_PATH+"/ColorField.vm.dep" } ;
Rule rvdcpp56 = { {&dcpp56} , {&vdcpp56} , {&exedcpp56} } ;
Exe exedcpp56 = { "CC-VM-DEP ColorField.cpp" , VMDEP , { OBJ_PATH+"/ColorField.dep" , OBJ_PATH+"/ColorField.vm.dep" , "56" } } ;

Target cpp57 = { "ColorListWindow.cpp" , "../../Desktop/Lib/CCore/src/./video/pref/ColorListWindow.cpp" } ;
Target dcpp57 = { "ColorListWindow.dep" , OBJ_PATH+"/ColorListWindow.dep" } ;
Rule rdcpp57 = { {&cpp57,&obj} , {&dcpp57} , {&execpp57} } ;
Exe execpp57 = { "CC-DEP ColorListWindow.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ColorListWindow.o"
 ,"../../Desktop/Lib/CCore/src/./video/pref/ColorListWindow.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ColorListWindow.dep"
} } ;

Target vdcpp57 = { "ColorListWindow.vm.dep" , OBJ_PATH+"/ColorListWindow.vm.dep" } ;
Rule rvdcpp57 = { {&dcpp57} , {&vdcpp57} , {&exedcpp57} } ;
Exe exedcpp57 = { "CC-VM-DEP ColorListWindow.cpp" , VMDEP , { OBJ_PATH+"/ColorListWindow.dep" , OBJ_PATH+"/ColorListWindow.vm.dep" , "57" } } ;

Target cpp58 = { "CommonIntAlgo.cpp" , "../../Fundamental/CCore/src/./algon/CommonIntAlgo.cpp" } ;
Target dcpp58 = { "CommonIntAlgo.dep" , OBJ_PATH+"/CommonIntAlgo.dep" } ;
Rule rdcpp58 = { {&cpp58,&obj} , {&dcpp58} , {&execpp58} } ;
Exe execpp58 = { "CC-DEP CommonIntAlgo.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/CommonIntAlgo.o"
 ,"../../Fundamental/CCore/src/./algon/CommonIntAlgo.cpp"
 ,"-MF"
 ,OBJ_PATH+"/CommonIntAlgo.dep"
} } ;

Target vdcpp58 = { "CommonIntAlgo.vm.dep" , OBJ_PATH+"/CommonIntAlgo.vm.dep" } ;
Rule rvdcpp58 = { {&dcpp58} , {&vdcpp58} , {&exedcpp58} } ;
Exe exedcpp58 = { "CC-VM-DEP CommonIntAlgo.cpp" , VMDEP , { OBJ_PATH+"/CommonIntAlgo.dep" , OBJ_PATH+"/CommonIntAlgo.vm.dep" , "58" } } ;

Target cpp59 = { "CompactList.cpp" , "../../Fundamental/CCore/src/CompactList.cpp" } ;
Target dcpp59 = { "CompactList.dep" , OBJ_PATH+"/CompactList.dep" } ;
Rule rdcpp59 = { {&cpp59,&obj} , {&dcpp59} , {&execpp59} } ;
Exe execpp59 = { "CC-DEP CompactList.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/CompactList.o"
 ,"../../Fundamental/CCore/src/CompactList.cpp"
 ,"-MF"
 ,OBJ_PATH+"/CompactList.dep"
} } ;

Target vdcpp59 = { "CompactList.vm.dep" , OBJ_PATH+"/CompactList.vm.dep" } ;
Rule rvdcpp59 = { {&dcpp59} , {&vdcpp59} , {&exedcpp59} } ;
Exe exedcpp59 = { "CC-VM-DEP CompactList.cpp" , VMDEP , { OBJ_PATH+"/CompactList.dep" , OBJ_PATH+"/CompactList.vm.dep" , "59" } } ;

Target cpp60 = { "CompactMap.cpp" , "../../Fundamental/CCore/src/CompactMap.cpp" } ;
Target dcpp60 = { "CompactMap.dep" , OBJ_PATH+"/CompactMap.dep" } ;
Rule rdcpp60 = { {&cpp60,&obj} , {&dcpp60} , {&execpp60} } ;
Exe execpp60 = { "CC-DEP CompactMap.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/CompactMap.o"
 ,"../../Fundamental/CCore/src/CompactMap.cpp"
 ,"-MF"
 ,OBJ_PATH+"/CompactMap.dep"
} } ;

Target vdcpp60 = { "CompactMap.vm.dep" , OBJ_PATH+"/CompactMap.vm.dep" } ;
Rule rvdcpp60 = { {&dcpp60} , {&vdcpp60} , {&exedcpp60} } ;
Exe exedcpp60 = { "CC-VM-DEP CompactMap.cpp" , VMDEP , { OBJ_PATH+"/CompactMap.dep" , OBJ_PATH+"/CompactMap.vm.dep" , "60" } } ;

Target cpp61 = { "CompactNodeAllocator.cpp" , "../../Fundamental/CCore/src/CompactNodeAllocator.cpp" } ;
Target dcpp61 = { "CompactNodeAllocator.dep" , OBJ_PATH+"/CompactNodeAllocator.dep" } ;
Rule rdcpp61 = { {&cpp61,&obj} , {&dcpp61} , {&execpp61} } ;
Exe execpp61 = { "CC-DEP CompactNodeAllocator.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/CompactNodeAllocator.o"
 ,"../../Fundamental/CCore/src/CompactNodeAllocator.cpp"
 ,"-MF"
 ,OBJ_PATH+"/CompactNodeAllocator.dep"
} } ;

Target vdcpp61 = { "CompactNodeAllocator.vm.dep" , OBJ_PATH+"/CompactNodeAllocator.vm.dep" } ;
Rule rvdcpp61 = { {&dcpp61} , {&vdcpp61} , {&exedcpp61} } ;
Exe exedcpp61 = { "CC-VM-DEP CompactNodeAllocator.cpp" , VMDEP , { OBJ_PATH+"/CompactNodeAllocator.dep" , OBJ_PATH+"/CompactNodeAllocator.vm.dep" , "61" } } ;

Target cpp62 = { "ConfigBinder.cpp" , "../../Desktop/Lib/CCore/src/./video/ConfigBinder.cpp" } ;
Target dcpp62 = { "ConfigBinder.dep" , OBJ_PATH+"/ConfigBinder.dep" } ;
Rule rdcpp62 = { {&cpp62,&obj} , {&dcpp62} , {&execpp62} } ;
Exe execpp62 = { "CC-DEP ConfigBinder.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ConfigBinder.o"
 ,"../../Desktop/Lib/CCore/src/./video/ConfigBinder.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ConfigBinder.dep"
} } ;

Target vdcpp62 = { "ConfigBinder.vm.dep" , OBJ_PATH+"/ConfigBinder.vm.dep" } ;
Rule rvdcpp62 = { {&dcpp62} , {&vdcpp62} , {&exedcpp62} } ;
Exe exedcpp62 = { "CC-VM-DEP ConfigBinder.cpp" , VMDEP , { OBJ_PATH+"/ConfigBinder.dep" , OBJ_PATH+"/ConfigBinder.vm.dep" , "62" } } ;

Target cpp63 = { "ConfigEditor.cpp" , "../../Desktop/Lib/CCore/src/./video/ConfigEditor.cpp" } ;
Target dcpp63 = { "ConfigEditor.dep" , OBJ_PATH+"/ConfigEditor.dep" } ;
Rule rdcpp63 = { {&cpp63,&obj} , {&dcpp63} , {&execpp63} } ;
Exe execpp63 = { "CC-DEP ConfigEditor.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ConfigEditor.o"
 ,"../../Desktop/Lib/CCore/src/./video/ConfigEditor.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ConfigEditor.dep"
} } ;

Target vdcpp63 = { "ConfigEditor.vm.dep" , OBJ_PATH+"/ConfigEditor.vm.dep" } ;
Rule rvdcpp63 = { {&dcpp63} , {&vdcpp63} , {&exedcpp63} } ;
Exe exedcpp63 = { "CC-VM-DEP ConfigEditor.cpp" , VMDEP , { OBJ_PATH+"/ConfigEditor.dep" , OBJ_PATH+"/ConfigEditor.vm.dep" , "63" } } ;

Target cpp64 = { "ConfigStore.cpp" , "../../Desktop/Lib/CCore/src/./video/ConfigStore.cpp" } ;
Target dcpp64 = { "ConfigStore.dep" , OBJ_PATH+"/ConfigStore.dep" } ;
Rule rdcpp64 = { {&cpp64,&obj} , {&dcpp64} , {&execpp64} } ;
Exe execpp64 = { "CC-DEP ConfigStore.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ConfigStore.o"
 ,"../../Desktop/Lib/CCore/src/./video/ConfigStore.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ConfigStore.dep"
} } ;

Target vdcpp64 = { "ConfigStore.vm.dep" , OBJ_PATH+"/ConfigStore.vm.dep" } ;
Rule rvdcpp64 = { {&dcpp64} , {&vdcpp64} , {&exedcpp64} } ;
Exe exedcpp64 = { "CC-VM-DEP ConfigStore.cpp" , VMDEP , { OBJ_PATH+"/ConfigStore.dep" , OBJ_PATH+"/ConfigStore.vm.dep" , "64" } } ;

Target cpp65 = { "ContainerList.cpp" , "../../Fundamental/CCore/src/ContainerList.cpp" } ;
Target dcpp65 = { "ContainerList.dep" , OBJ_PATH+"/ContainerList.dep" } ;
Rule rdcpp65 = { {&cpp65,&obj} , {&dcpp65} , {&execpp65} } ;
Exe execpp65 = { "CC-DEP ContainerList.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ContainerList.o"
 ,"../../Fundamental/CCore/src/ContainerList.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ContainerList.dep"
} } ;

Target vdcpp65 = { "ContainerList.vm.dep" , OBJ_PATH+"/ContainerList.vm.dep" } ;
Rule rvdcpp65 = { {&dcpp65} , {&vdcpp65} , {&exedcpp65} } ;
Exe exedcpp65 = { "CC-VM-DEP ContainerList.cpp" , VMDEP , { OBJ_PATH+"/ContainerList.dep" , OBJ_PATH+"/ContainerList.vm.dep" , "65" } } ;

Target cpp66 = { "CoordEdit.cpp" , "../../Desktop/Lib/CCore/src/./video/pref/CoordEdit.cpp" } ;
Target dcpp66 = { "CoordEdit.dep" , OBJ_PATH+"/CoordEdit.dep" } ;
Rule rdcpp66 = { {&cpp66,&obj} , {&dcpp66} , {&execpp66} } ;
Exe execpp66 = { "CC-DEP CoordEdit.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/CoordEdit.o"
 ,"../../Desktop/Lib/CCore/src/./video/pref/CoordEdit.cpp"
 ,"-MF"
 ,OBJ_PATH+"/CoordEdit.dep"
} } ;

Target vdcpp66 = { "CoordEdit.vm.dep" , OBJ_PATH+"/CoordEdit.vm.dep" } ;
Rule rvdcpp66 = { {&dcpp66} , {&vdcpp66} , {&exedcpp66} } ;
Exe exedcpp66 = { "CC-VM-DEP CoordEdit.cpp" , VMDEP , { OBJ_PATH+"/CoordEdit.dep" , OBJ_PATH+"/CoordEdit.vm.dep" , "66" } } ;

Target cpp67 = { "Counters.cpp" , "../../Simple/CCore/src/Counters.cpp" } ;
Target dcpp67 = { "Counters.dep" , OBJ_PATH+"/Counters.dep" } ;
Rule rdcpp67 = { {&cpp67,&obj} , {&dcpp67} , {&execpp67} } ;
Exe execpp67 = { "CC-DEP Counters.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Counters.o"
 ,"../../Simple/CCore/src/Counters.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Counters.dep"
} } ;

Target vdcpp67 = { "Counters.vm.dep" , OBJ_PATH+"/Counters.vm.dep" } ;
Rule rvdcpp67 = { {&dcpp67} , {&vdcpp67} , {&exedcpp67} } ;
Exe exedcpp67 = { "CC-VM-DEP Counters.cpp" , VMDEP , { OBJ_PATH+"/Counters.dep" , OBJ_PATH+"/Counters.vm.dep" , "67" } } ;

Target cpp68 = { "Crc.cpp" , "../../Simple/CCore/src/Crc.cpp" } ;
Target dcpp68 = { "Crc.dep" , OBJ_PATH+"/Crc.dep" } ;
Rule rdcpp68 = { {&cpp68,&obj} , {&dcpp68} , {&execpp68} } ;
Exe execpp68 = { "CC-DEP Crc.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Crc.o"
 ,"../../Simple/CCore/src/Crc.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Crc.dep"
} } ;

Target vdcpp68 = { "Crc.vm.dep" , OBJ_PATH+"/Crc.vm.dep" } ;
Rule rvdcpp68 = { {&dcpp68} , {&vdcpp68} , {&exedcpp68} } ;
Exe exedcpp68 = { "CC-VM-DEP Crc.cpp" , VMDEP , { OBJ_PATH+"/Crc.dep" , OBJ_PATH+"/Crc.vm.dep" , "68" } } ;

Target cpp69 = { "CreateAt.cpp" , "../../Simple/CCore/src/./gadget/CreateAt.cpp" } ;
Target dcpp69 = { "CreateAt.dep" , OBJ_PATH+"/CreateAt.dep" } ;
Rule rdcpp69 = { {&cpp69,&obj} , {&dcpp69} , {&execpp69} } ;
Exe execpp69 = { "CC-DEP CreateAt.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/CreateAt.o"
 ,"../../Simple/CCore/src/./gadget/CreateAt.cpp"
 ,"-MF"
 ,OBJ_PATH+"/CreateAt.dep"
} } ;

Target vdcpp69 = { "CreateAt.vm.dep" , OBJ_PATH+"/CreateAt.vm.dep" } ;
Rule rvdcpp69 = { {&dcpp69} , {&vdcpp69} , {&exedcpp69} } ;
Exe exedcpp69 = { "CC-VM-DEP CreateAt.cpp" , VMDEP , { OBJ_PATH+"/CreateAt.dep" , OBJ_PATH+"/CreateAt.vm.dep" , "69" } } ;

Target cpp70 = { "Creator.cpp" , "../../Fundamental/CCore/src/./array/Creator.cpp" } ;
Target dcpp70 = { "Creator.dep" , OBJ_PATH+"/Creator.dep" } ;
Rule rdcpp70 = { {&cpp70,&obj} , {&dcpp70} , {&execpp70} } ;
Exe execpp70 = { "CC-DEP Creator.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Creator.o"
 ,"../../Fundamental/CCore/src/./array/Creator.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Creator.dep"
} } ;

Target vdcpp70 = { "Creator.vm.dep" , OBJ_PATH+"/Creator.vm.dep" } ;
Rule rvdcpp70 = { {&dcpp70} , {&vdcpp70} , {&exedcpp70} } ;
Exe exedcpp70 = { "CC-VM-DEP Creator.cpp" , VMDEP , { OBJ_PATH+"/Creator.dep" , OBJ_PATH+"/Creator.vm.dep" , "70" } } ;

Target cpp71 = { "CurveDriver.cpp" , "../../Desktop/Draw/CCore/src/./video/CurveDriver.cpp" } ;
Target dcpp71 = { "CurveDriver.dep" , OBJ_PATH+"/CurveDriver.dep" } ;
Rule rdcpp71 = { {&cpp71,&obj} , {&dcpp71} , {&execpp71} } ;
Exe execpp71 = { "CC-DEP CurveDriver.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/CurveDriver.o"
 ,"../../Desktop/Draw/CCore/src/./video/CurveDriver.cpp"
 ,"-MF"
 ,OBJ_PATH+"/CurveDriver.dep"
} } ;

Target vdcpp71 = { "CurveDriver.vm.dep" , OBJ_PATH+"/CurveDriver.vm.dep" } ;
Rule rvdcpp71 = { {&dcpp71} , {&vdcpp71} , {&exedcpp71} } ;
Exe exedcpp71 = { "CC-VM-DEP CurveDriver.cpp" , VMDEP , { OBJ_PATH+"/CurveDriver.dep" , OBJ_PATH+"/CurveDriver.vm.dep" , "71" } } ;

Target cpp72 = { "DDLChar.cpp" , "../../Applied/CCore/src/./ddl/DDLChar.cpp" } ;
Target dcpp72 = { "DDLChar.dep" , OBJ_PATH+"/DDLChar.dep" } ;
Rule rdcpp72 = { {&cpp72,&obj} , {&dcpp72} , {&execpp72} } ;
Exe execpp72 = { "CC-DEP DDLChar.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DDLChar.o"
 ,"../../Applied/CCore/src/./ddl/DDLChar.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DDLChar.dep"
} } ;

Target vdcpp72 = { "DDLChar.vm.dep" , OBJ_PATH+"/DDLChar.vm.dep" } ;
Rule rvdcpp72 = { {&dcpp72} , {&vdcpp72} , {&exedcpp72} } ;
Exe exedcpp72 = { "CC-VM-DEP DDLChar.cpp" , VMDEP , { OBJ_PATH+"/DDLChar.dep" , OBJ_PATH+"/DDLChar.vm.dep" , "72" } } ;

Target cpp73 = { "DDLEngine.cpp" , "../../Applied/CCore/src/./ddl/DDLEngine.cpp" } ;
Target dcpp73 = { "DDLEngine.dep" , OBJ_PATH+"/DDLEngine.dep" } ;
Rule rdcpp73 = { {&cpp73,&obj} , {&dcpp73} , {&execpp73} } ;
Exe execpp73 = { "CC-DEP DDLEngine.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DDLEngine.o"
 ,"../../Applied/CCore/src/./ddl/DDLEngine.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DDLEngine.dep"
} } ;

Target vdcpp73 = { "DDLEngine.vm.dep" , OBJ_PATH+"/DDLEngine.vm.dep" } ;
Rule rvdcpp73 = { {&dcpp73} , {&vdcpp73} , {&exedcpp73} } ;
Exe exedcpp73 = { "CC-VM-DEP DDLEngine.cpp" , VMDEP , { OBJ_PATH+"/DDLEngine.dep" , OBJ_PATH+"/DDLEngine.vm.dep" , "73" } } ;

Target cpp74 = { "DDLErrorMsg.cpp" , "../../Applied/CCore/src/./ddl/DDLErrorMsg.cpp" } ;
Target dcpp74 = { "DDLErrorMsg.dep" , OBJ_PATH+"/DDLErrorMsg.dep" } ;
Rule rdcpp74 = { {&cpp74,&obj} , {&dcpp74} , {&execpp74} } ;
Exe execpp74 = { "CC-DEP DDLErrorMsg.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DDLErrorMsg.o"
 ,"../../Applied/CCore/src/./ddl/DDLErrorMsg.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DDLErrorMsg.dep"
} } ;

Target vdcpp74 = { "DDLErrorMsg.vm.dep" , OBJ_PATH+"/DDLErrorMsg.vm.dep" } ;
Rule rvdcpp74 = { {&dcpp74} , {&vdcpp74} , {&exedcpp74} } ;
Exe exedcpp74 = { "CC-VM-DEP DDLErrorMsg.cpp" , VMDEP , { OBJ_PATH+"/DDLErrorMsg.dep" , OBJ_PATH+"/DDLErrorMsg.vm.dep" , "74" } } ;

Target cpp75 = { "DDLEval.cpp" , "../../Applied/CCore/src/./ddl/DDLEval.cpp" } ;
Target dcpp75 = { "DDLEval.dep" , OBJ_PATH+"/DDLEval.dep" } ;
Rule rdcpp75 = { {&cpp75,&obj} , {&dcpp75} , {&execpp75} } ;
Exe execpp75 = { "CC-DEP DDLEval.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DDLEval.o"
 ,"../../Applied/CCore/src/./ddl/DDLEval.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DDLEval.dep"
} } ;

Target vdcpp75 = { "DDLEval.vm.dep" , OBJ_PATH+"/DDLEval.vm.dep" } ;
Rule rvdcpp75 = { {&dcpp75} , {&vdcpp75} , {&exedcpp75} } ;
Exe exedcpp75 = { "CC-VM-DEP DDLEval.cpp" , VMDEP , { OBJ_PATH+"/DDLEval.dep" , OBJ_PATH+"/DDLEval.vm.dep" , "75" } } ;

Target cpp76 = { "DDLMap.cpp" , "../../Applied/CCore/src/./ddl/DDLMap.cpp" } ;
Target dcpp76 = { "DDLMap.dep" , OBJ_PATH+"/DDLMap.dep" } ;
Rule rdcpp76 = { {&cpp76,&obj} , {&dcpp76} , {&execpp76} } ;
Exe execpp76 = { "CC-DEP DDLMap.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DDLMap.o"
 ,"../../Applied/CCore/src/./ddl/DDLMap.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DDLMap.dep"
} } ;

Target vdcpp76 = { "DDLMap.vm.dep" , OBJ_PATH+"/DDLMap.vm.dep" } ;
Rule rvdcpp76 = { {&dcpp76} , {&vdcpp76} , {&exedcpp76} } ;
Exe exedcpp76 = { "CC-VM-DEP DDLMap.cpp" , VMDEP , { OBJ_PATH+"/DDLMap.dep" , OBJ_PATH+"/DDLMap.vm.dep" , "76" } } ;

Target cpp77 = { "DDLMapBase.cpp" , "../../Applied/CCore/src/./ddl/DDLMapBase.cpp" } ;
Target dcpp77 = { "DDLMapBase.dep" , OBJ_PATH+"/DDLMapBase.dep" } ;
Rule rdcpp77 = { {&cpp77,&obj} , {&dcpp77} , {&execpp77} } ;
Exe execpp77 = { "CC-DEP DDLMapBase.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DDLMapBase.o"
 ,"../../Applied/CCore/src/./ddl/DDLMapBase.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DDLMapBase.dep"
} } ;

Target vdcpp77 = { "DDLMapBase.vm.dep" , OBJ_PATH+"/DDLMapBase.vm.dep" } ;
Rule rvdcpp77 = { {&dcpp77} , {&vdcpp77} , {&exedcpp77} } ;
Exe exedcpp77 = { "CC-VM-DEP DDLMapBase.cpp" , VMDEP , { OBJ_PATH+"/DDLMapBase.dep" , OBJ_PATH+"/DDLMapBase.vm.dep" , "77" } } ;

Target cpp78 = { "DDLMapTools.cpp" , "../../Applied/CCore/src/./ddl/DDLMapTools.cpp" } ;
Target dcpp78 = { "DDLMapTools.dep" , OBJ_PATH+"/DDLMapTools.dep" } ;
Rule rdcpp78 = { {&cpp78,&obj} , {&dcpp78} , {&execpp78} } ;
Exe execpp78 = { "CC-DEP DDLMapTools.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DDLMapTools.o"
 ,"../../Applied/CCore/src/./ddl/DDLMapTools.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DDLMapTools.dep"
} } ;

Target vdcpp78 = { "DDLMapTools.vm.dep" , OBJ_PATH+"/DDLMapTools.vm.dep" } ;
Rule rvdcpp78 = { {&dcpp78} , {&vdcpp78} , {&exedcpp78} } ;
Exe exedcpp78 = { "CC-VM-DEP DDLMapTools.cpp" , VMDEP , { OBJ_PATH+"/DDLMapTools.dep" , OBJ_PATH+"/DDLMapTools.vm.dep" , "78" } } ;

Target cpp79 = { "DDLMapTypes.cpp" , "../../Applied/CCore/src/./ddl/DDLMapTypes.cpp" } ;
Target dcpp79 = { "DDLMapTypes.dep" , OBJ_PATH+"/DDLMapTypes.dep" } ;
Rule rdcpp79 = { {&cpp79,&obj} , {&dcpp79} , {&execpp79} } ;
Exe execpp79 = { "CC-DEP DDLMapTypes.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DDLMapTypes.o"
 ,"../../Applied/CCore/src/./ddl/DDLMapTypes.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DDLMapTypes.dep"
} } ;

Target vdcpp79 = { "DDLMapTypes.vm.dep" , OBJ_PATH+"/DDLMapTypes.vm.dep" } ;
Rule rvdcpp79 = { {&dcpp79} , {&vdcpp79} , {&exedcpp79} } ;
Exe exedcpp79 = { "CC-VM-DEP DDLMapTypes.cpp" , VMDEP , { OBJ_PATH+"/DDLMapTypes.dep" , OBJ_PATH+"/DDLMapTypes.vm.dep" , "79" } } ;

Target cpp80 = { "DDLParser.cpp" , "../../Applied/CCore/src/./ddl/DDLParser.cpp" } ;
Target dcpp80 = { "DDLParser.dep" , OBJ_PATH+"/DDLParser.dep" } ;
Rule rdcpp80 = { {&cpp80,&obj} , {&dcpp80} , {&execpp80} } ;
Exe execpp80 = { "CC-DEP DDLParser.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DDLParser.o"
 ,"../../Applied/CCore/src/./ddl/DDLParser.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DDLParser.dep"
} } ;

Target vdcpp80 = { "DDLParser.vm.dep" , OBJ_PATH+"/DDLParser.vm.dep" } ;
Rule rvdcpp80 = { {&dcpp80} , {&vdcpp80} , {&exedcpp80} } ;
Exe exedcpp80 = { "CC-VM-DEP DDLParser.cpp" , VMDEP , { OBJ_PATH+"/DDLParser.dep" , OBJ_PATH+"/DDLParser.vm.dep" , "80" } } ;

Target cpp81 = { "DDLParserElements.cpp" , "../../Applied/CCore/src/./ddl/DDLParserElements.cpp" } ;
Target dcpp81 = { "DDLParserElements.dep" , OBJ_PATH+"/DDLParserElements.dep" } ;
Rule rdcpp81 = { {&cpp81,&obj} , {&dcpp81} , {&execpp81} } ;
Exe execpp81 = { "CC-DEP DDLParserElements.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DDLParserElements.o"
 ,"../../Applied/CCore/src/./ddl/DDLParserElements.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DDLParserElements.dep"
} } ;

Target vdcpp81 = { "DDLParserElements.vm.dep" , OBJ_PATH+"/DDLParserElements.vm.dep" } ;
Rule rvdcpp81 = { {&dcpp81} , {&vdcpp81} , {&exedcpp81} } ;
Exe exedcpp81 = { "CC-VM-DEP DDLParserElements.cpp" , VMDEP , { OBJ_PATH+"/DDLParserElements.dep" , OBJ_PATH+"/DDLParserElements.vm.dep" , "81" } } ;

Target cpp82 = { "DDLParserRules.cpp" , "../../Applied/CCore/src/./ddl/DDLParserRules.cpp" } ;
Target dcpp82 = { "DDLParserRules.dep" , OBJ_PATH+"/DDLParserRules.dep" } ;
Rule rdcpp82 = { {&cpp82,&obj} , {&dcpp82} , {&execpp82} } ;
Exe execpp82 = { "CC-DEP DDLParserRules.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DDLParserRules.o"
 ,"../../Applied/CCore/src/./ddl/DDLParserRules.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DDLParserRules.dep"
} } ;

Target vdcpp82 = { "DDLParserRules.vm.dep" , OBJ_PATH+"/DDLParserRules.vm.dep" } ;
Rule rvdcpp82 = { {&dcpp82} , {&vdcpp82} , {&exedcpp82} } ;
Exe exedcpp82 = { "CC-VM-DEP DDLParserRules.cpp" , VMDEP , { OBJ_PATH+"/DDLParserRules.dep" , OBJ_PATH+"/DDLParserRules.vm.dep" , "82" } } ;

Target cpp83 = { "DDLParserTable.cpp" , "../../Applied/CCore/src/./ddl/DDLParserTable.cpp" } ;
Target dcpp83 = { "DDLParserTable.dep" , OBJ_PATH+"/DDLParserTable.dep" } ;
Rule rdcpp83 = { {&cpp83,&obj} , {&dcpp83} , {&execpp83} } ;
Exe execpp83 = { "CC-DEP DDLParserTable.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DDLParserTable.o"
 ,"../../Applied/CCore/src/./ddl/DDLParserTable.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DDLParserTable.dep"
} } ;

Target vdcpp83 = { "DDLParserTable.vm.dep" , OBJ_PATH+"/DDLParserTable.vm.dep" } ;
Rule rvdcpp83 = { {&dcpp83} , {&vdcpp83} , {&exedcpp83} } ;
Exe exedcpp83 = { "CC-VM-DEP DDLParserTable.cpp" , VMDEP , { OBJ_PATH+"/DDLParserTable.dep" , OBJ_PATH+"/DDLParserTable.vm.dep" , "83" } } ;

Target cpp84 = { "DDLPlatformTypes.cpp" , "../../Applied/CCore/src/./ddl/DDLPlatformTypes.cpp" } ;
Target dcpp84 = { "DDLPlatformTypes.dep" , OBJ_PATH+"/DDLPlatformTypes.dep" } ;
Rule rdcpp84 = { {&cpp84,&obj} , {&dcpp84} , {&execpp84} } ;
Exe execpp84 = { "CC-DEP DDLPlatformTypes.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DDLPlatformTypes.o"
 ,"../../Applied/CCore/src/./ddl/DDLPlatformTypes.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DDLPlatformTypes.dep"
} } ;

Target vdcpp84 = { "DDLPlatformTypes.vm.dep" , OBJ_PATH+"/DDLPlatformTypes.vm.dep" } ;
Rule rvdcpp84 = { {&dcpp84} , {&vdcpp84} , {&exedcpp84} } ;
Exe exedcpp84 = { "CC-VM-DEP DDLPlatformTypes.cpp" , VMDEP , { OBJ_PATH+"/DDLPlatformTypes.dep" , OBJ_PATH+"/DDLPlatformTypes.vm.dep" , "84" } } ;

Target cpp85 = { "DDLSemantic.cpp" , "../../Applied/CCore/src/./ddl/DDLSemantic.cpp" } ;
Target dcpp85 = { "DDLSemantic.dep" , OBJ_PATH+"/DDLSemantic.dep" } ;
Rule rdcpp85 = { {&cpp85,&obj} , {&dcpp85} , {&execpp85} } ;
Exe execpp85 = { "CC-DEP DDLSemantic.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DDLSemantic.o"
 ,"../../Applied/CCore/src/./ddl/DDLSemantic.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DDLSemantic.dep"
} } ;

Target vdcpp85 = { "DDLSemantic.vm.dep" , OBJ_PATH+"/DDLSemantic.vm.dep" } ;
Rule rvdcpp85 = { {&dcpp85} , {&vdcpp85} , {&exedcpp85} } ;
Exe exedcpp85 = { "CC-VM-DEP DDLSemantic.cpp" , VMDEP , { OBJ_PATH+"/DDLSemantic.dep" , OBJ_PATH+"/DDLSemantic.vm.dep" , "85" } } ;

Target cpp86 = { "DDLToken.cpp" , "../../Applied/CCore/src/./ddl/DDLToken.cpp" } ;
Target dcpp86 = { "DDLToken.dep" , OBJ_PATH+"/DDLToken.dep" } ;
Rule rdcpp86 = { {&cpp86,&obj} , {&dcpp86} , {&execpp86} } ;
Exe execpp86 = { "CC-DEP DDLToken.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DDLToken.o"
 ,"../../Applied/CCore/src/./ddl/DDLToken.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DDLToken.dep"
} } ;

Target vdcpp86 = { "DDLToken.vm.dep" , OBJ_PATH+"/DDLToken.vm.dep" } ;
Rule rvdcpp86 = { {&dcpp86} , {&vdcpp86} , {&exedcpp86} } ;
Exe exedcpp86 = { "CC-VM-DEP DDLToken.cpp" , VMDEP , { OBJ_PATH+"/DDLToken.dep" , OBJ_PATH+"/DDLToken.vm.dep" , "86" } } ;

Target cpp87 = { "DDLTools.cpp" , "../../Applied/CCore/src/./ddl/DDLTools.cpp" } ;
Target dcpp87 = { "DDLTools.dep" , OBJ_PATH+"/DDLTools.dep" } ;
Rule rdcpp87 = { {&cpp87,&obj} , {&dcpp87} , {&execpp87} } ;
Exe execpp87 = { "CC-DEP DDLTools.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DDLTools.o"
 ,"../../Applied/CCore/src/./ddl/DDLTools.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DDLTools.dep"
} } ;

Target vdcpp87 = { "DDLTools.vm.dep" , OBJ_PATH+"/DDLTools.vm.dep" } ;
Rule rvdcpp87 = { {&dcpp87} , {&vdcpp87} , {&exedcpp87} } ;
Exe exedcpp87 = { "CC-VM-DEP DDLTools.cpp" , VMDEP , { OBJ_PATH+"/DDLTools.dep" , OBJ_PATH+"/DDLTools.vm.dep" , "87" } } ;

Target cpp88 = { "DDLTypeDesc.cpp" , "../../Applied/CCore/src/./ddl/DDLTypeDesc.cpp" } ;
Target dcpp88 = { "DDLTypeDesc.dep" , OBJ_PATH+"/DDLTypeDesc.dep" } ;
Rule rdcpp88 = { {&cpp88,&obj} , {&dcpp88} , {&execpp88} } ;
Exe execpp88 = { "CC-DEP DDLTypeDesc.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DDLTypeDesc.o"
 ,"../../Applied/CCore/src/./ddl/DDLTypeDesc.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DDLTypeDesc.dep"
} } ;

Target vdcpp88 = { "DDLTypeDesc.vm.dep" , OBJ_PATH+"/DDLTypeDesc.vm.dep" } ;
Rule rvdcpp88 = { {&dcpp88} , {&vdcpp88} , {&exedcpp88} } ;
Exe exedcpp88 = { "CC-VM-DEP DDLTypeDesc.cpp" , VMDEP , { OBJ_PATH+"/DDLTypeDesc.dep" , OBJ_PATH+"/DDLTypeDesc.vm.dep" , "88" } } ;

Target cpp89 = { "DDLTypeSet.cpp" , "../../Applied/CCore/src/./ddl/DDLTypeSet.cpp" } ;
Target dcpp89 = { "DDLTypeSet.dep" , OBJ_PATH+"/DDLTypeSet.dep" } ;
Rule rdcpp89 = { {&cpp89,&obj} , {&dcpp89} , {&execpp89} } ;
Exe execpp89 = { "CC-DEP DDLTypeSet.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DDLTypeSet.o"
 ,"../../Applied/CCore/src/./ddl/DDLTypeSet.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DDLTypeSet.dep"
} } ;

Target vdcpp89 = { "DDLTypeSet.vm.dep" , OBJ_PATH+"/DDLTypeSet.vm.dep" } ;
Rule rvdcpp89 = { {&dcpp89} , {&vdcpp89} , {&exedcpp89} } ;
Exe exedcpp89 = { "CC-VM-DEP DDLTypeSet.cpp" , VMDEP , { OBJ_PATH+"/DDLTypeSet.dep" , OBJ_PATH+"/DDLTypeSet.vm.dep" , "89" } } ;

Target cpp90 = { "DDLTypedMap.cpp" , "../../Applied/CCore/src/./ddl/DDLTypedMap.cpp" } ;
Target dcpp90 = { "DDLTypedMap.dep" , OBJ_PATH+"/DDLTypedMap.dep" } ;
Rule rdcpp90 = { {&cpp90,&obj} , {&dcpp90} , {&execpp90} } ;
Exe execpp90 = { "CC-DEP DDLTypedMap.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DDLTypedMap.o"
 ,"../../Applied/CCore/src/./ddl/DDLTypedMap.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DDLTypedMap.dep"
} } ;

Target vdcpp90 = { "DDLTypedMap.vm.dep" , OBJ_PATH+"/DDLTypedMap.vm.dep" } ;
Rule rvdcpp90 = { {&dcpp90} , {&vdcpp90} , {&exedcpp90} } ;
Exe exedcpp90 = { "CC-VM-DEP DDLTypedMap.cpp" , VMDEP , { OBJ_PATH+"/DDLTypedMap.dep" , OBJ_PATH+"/DDLTypedMap.vm.dep" , "90" } } ;

Target cpp91 = { "DDLTypes.cpp" , "../../Applied/CCore/src/./ddl/DDLTypes.cpp" } ;
Target dcpp91 = { "DDLTypes.dep" , OBJ_PATH+"/DDLTypes.dep" } ;
Rule rdcpp91 = { {&cpp91,&obj} , {&dcpp91} , {&execpp91} } ;
Exe execpp91 = { "CC-DEP DDLTypes.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DDLTypes.o"
 ,"../../Applied/CCore/src/./ddl/DDLTypes.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DDLTypes.dep"
} } ;

Target vdcpp91 = { "DDLTypes.vm.dep" , OBJ_PATH+"/DDLTypes.vm.dep" } ;
Rule rvdcpp91 = { {&dcpp91} , {&vdcpp91} , {&exedcpp91} } ;
Exe exedcpp91 = { "CC-VM-DEP DDLTypes.cpp" , VMDEP , { OBJ_PATH+"/DDLTypes.dep" , OBJ_PATH+"/DDLTypes.vm.dep" , "91" } } ;

Target cpp92 = { "DDLValue.cpp" , "../../Applied/CCore/src/./ddl/DDLValue.cpp" } ;
Target dcpp92 = { "DDLValue.dep" , OBJ_PATH+"/DDLValue.dep" } ;
Rule rdcpp92 = { {&cpp92,&obj} , {&dcpp92} , {&execpp92} } ;
Exe execpp92 = { "CC-DEP DDLValue.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DDLValue.o"
 ,"../../Applied/CCore/src/./ddl/DDLValue.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DDLValue.dep"
} } ;

Target vdcpp92 = { "DDLValue.vm.dep" , OBJ_PATH+"/DDLValue.vm.dep" } ;
Rule rvdcpp92 = { {&dcpp92} , {&vdcpp92} , {&exedcpp92} } ;
Exe exedcpp92 = { "CC-VM-DEP DDLValue.cpp" , VMDEP , { OBJ_PATH+"/DDLValue.dep" , OBJ_PATH+"/DDLValue.vm.dep" , "92" } } ;

Target cpp93 = { "DHExp.cpp" , "../../Applied/CCore/src/./crypton/DHExp.cpp" } ;
Target dcpp93 = { "DHExp.dep" , OBJ_PATH+"/DHExp.dep" } ;
Rule rdcpp93 = { {&cpp93,&obj} , {&dcpp93} , {&execpp93} } ;
Exe execpp93 = { "CC-DEP DHExp.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DHExp.o"
 ,"../../Applied/CCore/src/./crypton/DHExp.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DHExp.dep"
} } ;

Target vdcpp93 = { "DHExp.vm.dep" , OBJ_PATH+"/DHExp.vm.dep" } ;
Rule rvdcpp93 = { {&dcpp93} , {&vdcpp93} , {&exedcpp93} } ;
Exe exedcpp93 = { "CC-VM-DEP DHExp.cpp" , VMDEP , { OBJ_PATH+"/DHExp.dep" , OBJ_PATH+"/DHExp.vm.dep" , "93" } } ;

Target cpp94 = { "DecodeFile.cpp" , "../../HCore/CCore/src/DecodeFile.cpp" } ;
Target dcpp94 = { "DecodeFile.dep" , OBJ_PATH+"/DecodeFile.dep" } ;
Rule rdcpp94 = { {&cpp94,&obj} , {&dcpp94} , {&execpp94} } ;
Exe execpp94 = { "CC-DEP DecodeFile.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DecodeFile.o"
 ,"../../HCore/CCore/src/DecodeFile.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DecodeFile.dep"
} } ;

Target vdcpp94 = { "DecodeFile.vm.dep" , OBJ_PATH+"/DecodeFile.vm.dep" } ;
Rule rvdcpp94 = { {&dcpp94} , {&vdcpp94} , {&exedcpp94} } ;
Exe exedcpp94 = { "CC-VM-DEP DecodeFile.cpp" , VMDEP , { OBJ_PATH+"/DecodeFile.dep" , OBJ_PATH+"/DecodeFile.vm.dep" , "94" } } ;

Target cpp95 = { "DefaultTimeout.cpp" , "../../Simple/CCore/src/./gadget/DefaultTimeout.cpp" } ;
Target dcpp95 = { "DefaultTimeout.dep" , OBJ_PATH+"/DefaultTimeout.dep" } ;
Rule rdcpp95 = { {&cpp95,&obj} , {&dcpp95} , {&execpp95} } ;
Exe execpp95 = { "CC-DEP DefaultTimeout.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DefaultTimeout.o"
 ,"../../Simple/CCore/src/./gadget/DefaultTimeout.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DefaultTimeout.dep"
} } ;

Target vdcpp95 = { "DefaultTimeout.vm.dep" , OBJ_PATH+"/DefaultTimeout.vm.dep" } ;
Rule rvdcpp95 = { {&dcpp95} , {&vdcpp95} , {&exedcpp95} } ;
Exe exedcpp95 = { "CC-VM-DEP DefaultTimeout.cpp" , VMDEP , { OBJ_PATH+"/DefaultTimeout.dep" , OBJ_PATH+"/DefaultTimeout.vm.dep" , "95" } } ;

Target cpp96 = { "DeferCall.cpp" , "../../Fundamental/CCore/src/DeferCall.cpp" } ;
Target dcpp96 = { "DeferCall.dep" , OBJ_PATH+"/DeferCall.dep" } ;
Rule rdcpp96 = { {&cpp96,&obj} , {&dcpp96} , {&execpp96} } ;
Exe execpp96 = { "CC-DEP DeferCall.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DeferCall.o"
 ,"../../Fundamental/CCore/src/DeferCall.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DeferCall.dep"
} } ;

Target vdcpp96 = { "DeferCall.vm.dep" , OBJ_PATH+"/DeferCall.vm.dep" } ;
Rule rvdcpp96 = { {&dcpp96} , {&vdcpp96} , {&exedcpp96} } ;
Exe exedcpp96 = { "CC-VM-DEP DeferCall.cpp" , VMDEP , { OBJ_PATH+"/DeferCall.dep" , OBJ_PATH+"/DeferCall.vm.dep" , "96" } } ;

Target cpp97 = { "Deflate.cpp" , "../../Applied/CCore/src/Deflate.cpp" } ;
Target dcpp97 = { "Deflate.dep" , OBJ_PATH+"/Deflate.dep" } ;
Rule rdcpp97 = { {&cpp97,&obj} , {&dcpp97} , {&execpp97} } ;
Exe execpp97 = { "CC-DEP Deflate.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Deflate.o"
 ,"../../Applied/CCore/src/Deflate.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Deflate.dep"
} } ;

Target vdcpp97 = { "Deflate.vm.dep" , OBJ_PATH+"/Deflate.vm.dep" } ;
Rule rvdcpp97 = { {&dcpp97} , {&vdcpp97} , {&exedcpp97} } ;
Exe exedcpp97 = { "CC-VM-DEP Deflate.cpp" , VMDEP , { OBJ_PATH+"/Deflate.dep" , OBJ_PATH+"/Deflate.vm.dep" , "97" } } ;

Target cpp98 = { "Desktop.cpp" , "CCore/src/./video/Desktop.cpp" } ;
Target dcpp98 = { "Desktop.dep" , OBJ_PATH+"/Desktop.dep" } ;
Rule rdcpp98 = { {&cpp98,&obj} , {&dcpp98} , {&execpp98} } ;
Exe execpp98 = { "CC-DEP Desktop.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Desktop.o"
 ,"CCore/src/./video/Desktop.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Desktop.dep"
} } ;

Target vdcpp98 = { "Desktop.vm.dep" , OBJ_PATH+"/Desktop.vm.dep" } ;
Rule rvdcpp98 = { {&dcpp98} , {&vdcpp98} , {&exedcpp98} } ;
Exe exedcpp98 = { "CC-VM-DEP Desktop.cpp" , VMDEP , { OBJ_PATH+"/Desktop.dep" , OBJ_PATH+"/Desktop.vm.dep" , "98" } } ;

Target cpp99 = { "DesktopKey.cpp" , "../../Desktop/Tools/CCore/src/./video/DesktopKey.cpp" } ;
Target dcpp99 = { "DesktopKey.dep" , OBJ_PATH+"/DesktopKey.dep" } ;
Rule rdcpp99 = { {&cpp99,&obj} , {&dcpp99} , {&execpp99} } ;
Exe execpp99 = { "CC-DEP DesktopKey.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DesktopKey.o"
 ,"../../Desktop/Tools/CCore/src/./video/DesktopKey.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DesktopKey.dep"
} } ;

Target vdcpp99 = { "DesktopKey.vm.dep" , OBJ_PATH+"/DesktopKey.vm.dep" } ;
Rule rvdcpp99 = { {&dcpp99} , {&vdcpp99} , {&exedcpp99} } ;
Exe exedcpp99 = { "CC-VM-DEP DesktopKey.cpp" , VMDEP , { OBJ_PATH+"/DesktopKey.dep" , OBJ_PATH+"/DesktopKey.vm.dep" , "99" } } ;

Target cpp100 = { "DestroyGuard.cpp" , "../../Simple/CCore/src/DestroyGuard.cpp" } ;
Target dcpp100 = { "DestroyGuard.dep" , OBJ_PATH+"/DestroyGuard.dep" } ;
Rule rdcpp100 = { {&cpp100,&obj} , {&dcpp100} , {&execpp100} } ;
Exe execpp100 = { "CC-DEP DestroyGuard.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DestroyGuard.o"
 ,"../../Simple/CCore/src/DestroyGuard.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DestroyGuard.dep"
} } ;

Target vdcpp100 = { "DestroyGuard.vm.dep" , OBJ_PATH+"/DestroyGuard.vm.dep" } ;
Rule rvdcpp100 = { {&dcpp100} , {&vdcpp100} , {&exedcpp100} } ;
Exe exedcpp100 = { "CC-VM-DEP DestroyGuard.cpp" , VMDEP , { OBJ_PATH+"/DestroyGuard.dep" , OBJ_PATH+"/DestroyGuard.vm.dep" , "100" } } ;

Target cpp101 = { "DetectProxy.cpp" , "../../Fundamental/CCore/src/DetectProxy.cpp" } ;
Target dcpp101 = { "DetectProxy.dep" , OBJ_PATH+"/DetectProxy.dep" } ;
Rule rdcpp101 = { {&cpp101,&obj} , {&dcpp101} , {&execpp101} } ;
Exe execpp101 = { "CC-DEP DetectProxy.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DetectProxy.o"
 ,"../../Fundamental/CCore/src/DetectProxy.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DetectProxy.dep"
} } ;

Target vdcpp101 = { "DetectProxy.vm.dep" , OBJ_PATH+"/DetectProxy.vm.dep" } ;
Rule rvdcpp101 = { {&dcpp101} , {&vdcpp101} , {&exedcpp101} } ;
Exe exedcpp101 = { "CC-VM-DEP DetectProxy.cpp" , VMDEP , { OBJ_PATH+"/DetectProxy.dep" , OBJ_PATH+"/DetectProxy.vm.dep" , "101" } } ;

Target cpp102 = { "DirFrame.cpp" , "../../Desktop/Lib/CCore/src/./video/DirFrame.cpp" } ;
Target dcpp102 = { "DirFrame.dep" , OBJ_PATH+"/DirFrame.dep" } ;
Rule rdcpp102 = { {&cpp102,&obj} , {&dcpp102} , {&execpp102} } ;
Exe execpp102 = { "CC-DEP DirFrame.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DirFrame.o"
 ,"../../Desktop/Lib/CCore/src/./video/DirFrame.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DirFrame.dep"
} } ;

Target vdcpp102 = { "DirFrame.vm.dep" , OBJ_PATH+"/DirFrame.vm.dep" } ;
Rule rvdcpp102 = { {&dcpp102} , {&vdcpp102} , {&exedcpp102} } ;
Exe exedcpp102 = { "CC-VM-DEP DirFrame.cpp" , VMDEP , { OBJ_PATH+"/DirFrame.dep" , OBJ_PATH+"/DirFrame.vm.dep" , "102" } } ;

Target cpp103 = { "DirTreeRun.cpp" , "../../HCore/CCore/src/DirTreeRun.cpp" } ;
Target dcpp103 = { "DirTreeRun.dep" , OBJ_PATH+"/DirTreeRun.dep" } ;
Rule rdcpp103 = { {&cpp103,&obj} , {&dcpp103} , {&execpp103} } ;
Exe execpp103 = { "CC-DEP DirTreeRun.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DirTreeRun.o"
 ,"../../HCore/CCore/src/DirTreeRun.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DirTreeRun.dep"
} } ;

Target vdcpp103 = { "DirTreeRun.vm.dep" , OBJ_PATH+"/DirTreeRun.vm.dep" } ;
Rule rvdcpp103 = { {&dcpp103} , {&vdcpp103} , {&exedcpp103} } ;
Exe exedcpp103 = { "CC-VM-DEP DirTreeRun.cpp" , VMDEP , { OBJ_PATH+"/DirTreeRun.dep" , OBJ_PATH+"/DirTreeRun.vm.dep" , "103" } } ;

Target cpp104 = { "DrawBook.cpp" , "../../Desktop/Lib/CCore/src/./video/book/DrawBook.cpp" } ;
Target dcpp104 = { "DrawBook.dep" , OBJ_PATH+"/DrawBook.dep" } ;
Rule rdcpp104 = { {&cpp104,&obj} , {&dcpp104} , {&execpp104} } ;
Exe execpp104 = { "CC-DEP DrawBook.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DrawBook.o"
 ,"../../Desktop/Lib/CCore/src/./video/book/DrawBook.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DrawBook.dep"
} } ;

Target vdcpp104 = { "DrawBook.vm.dep" , OBJ_PATH+"/DrawBook.vm.dep" } ;
Rule rvdcpp104 = { {&dcpp104} , {&vdcpp104} , {&exedcpp104} } ;
Exe exedcpp104 = { "CC-VM-DEP DrawBook.cpp" , VMDEP , { OBJ_PATH+"/DrawBook.dep" , OBJ_PATH+"/DrawBook.vm.dep" , "104" } } ;

Target cpp105 = { "DrawBookTools.cpp" , "../../Desktop/Lib/CCore/src/./video/book/DrawBookTools.cpp" } ;
Target dcpp105 = { "DrawBookTools.dep" , OBJ_PATH+"/DrawBookTools.dep" } ;
Rule rdcpp105 = { {&cpp105,&obj} , {&dcpp105} , {&execpp105} } ;
Exe execpp105 = { "CC-DEP DrawBookTools.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DrawBookTools.o"
 ,"../../Desktop/Lib/CCore/src/./video/book/DrawBookTools.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DrawBookTools.dep"
} } ;

Target vdcpp105 = { "DrawBookTools.vm.dep" , OBJ_PATH+"/DrawBookTools.vm.dep" } ;
Rule rvdcpp105 = { {&dcpp105} , {&vdcpp105} , {&exedcpp105} } ;
Exe exedcpp105 = { "CC-VM-DEP DrawBookTools.cpp" , VMDEP , { OBJ_PATH+"/DrawBookTools.dep" , OBJ_PATH+"/DrawBookTools.vm.dep" , "105" } } ;

Target cpp106 = { "DrawBuf.cpp" , "../../Desktop/Core/CCore/src/./video/DrawBuf.cpp" } ;
Target dcpp106 = { "DrawBuf.dep" , OBJ_PATH+"/DrawBuf.dep" } ;
Rule rdcpp106 = { {&cpp106,&obj} , {&dcpp106} , {&execpp106} } ;
Exe execpp106 = { "CC-DEP DrawBuf.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DrawBuf.o"
 ,"../../Desktop/Core/CCore/src/./video/DrawBuf.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DrawBuf.dep"
} } ;

Target vdcpp106 = { "DrawBuf.vm.dep" , OBJ_PATH+"/DrawBuf.vm.dep" } ;
Rule rvdcpp106 = { {&dcpp106} , {&vdcpp106} , {&exedcpp106} } ;
Exe exedcpp106 = { "CC-VM-DEP DrawBuf.cpp" , VMDEP , { OBJ_PATH+"/DrawBuf.dep" , OBJ_PATH+"/DrawBuf.vm.dep" , "106" } } ;

Target cpp107 = { "DrawTools.cpp" , "../../Desktop/Draw/CCore/src/./video/DrawTools.cpp" } ;
Target dcpp107 = { "DrawTools.dep" , OBJ_PATH+"/DrawTools.dep" } ;
Rule rdcpp107 = { {&cpp107,&obj} , {&dcpp107} , {&execpp107} } ;
Exe execpp107 = { "CC-DEP DrawTools.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DrawTools.o"
 ,"../../Desktop/Draw/CCore/src/./video/DrawTools.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DrawTools.dep"
} } ;

Target vdcpp107 = { "DrawTools.vm.dep" , OBJ_PATH+"/DrawTools.vm.dep" } ;
Rule rvdcpp107 = { {&dcpp107} , {&vdcpp107} , {&exedcpp107} } ;
Exe exedcpp107 = { "CC-VM-DEP DrawTools.cpp" , VMDEP , { OBJ_PATH+"/DrawTools.dep" , OBJ_PATH+"/DrawTools.vm.dep" , "107" } } ;

Target cpp108 = { "DynArray.cpp" , "../../Fundamental/CCore/src/./array/DynArray.cpp" } ;
Target dcpp108 = { "DynArray.dep" , OBJ_PATH+"/DynArray.dep" } ;
Rule rdcpp108 = { {&cpp108,&obj} , {&dcpp108} , {&execpp108} } ;
Exe execpp108 = { "CC-DEP DynArray.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DynArray.o"
 ,"../../Fundamental/CCore/src/./array/DynArray.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DynArray.dep"
} } ;

Target vdcpp108 = { "DynArray.vm.dep" , OBJ_PATH+"/DynArray.vm.dep" } ;
Rule rvdcpp108 = { {&dcpp108} , {&vdcpp108} , {&exedcpp108} } ;
Exe exedcpp108 = { "CC-VM-DEP DynArray.cpp" , VMDEP , { OBJ_PATH+"/DynArray.dep" , OBJ_PATH+"/DynArray.vm.dep" , "108" } } ;

Target cpp109 = { "DynObject.cpp" , "../../Simple/CCore/src/DynObject.cpp" } ;
Target dcpp109 = { "DynObject.dep" , OBJ_PATH+"/DynObject.dep" } ;
Rule rdcpp109 = { {&cpp109,&obj} , {&dcpp109} , {&execpp109} } ;
Exe execpp109 = { "CC-DEP DynObject.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/DynObject.o"
 ,"../../Simple/CCore/src/DynObject.cpp"
 ,"-MF"
 ,OBJ_PATH+"/DynObject.dep"
} } ;

Target vdcpp109 = { "DynObject.vm.dep" , OBJ_PATH+"/DynObject.vm.dep" } ;
Rule rvdcpp109 = { {&dcpp109} , {&vdcpp109} , {&exedcpp109} } ;
Exe exedcpp109 = { "CC-VM-DEP DynObject.cpp" , VMDEP , { OBJ_PATH+"/DynObject.dep" , OBJ_PATH+"/DynObject.vm.dep" , "109" } } ;

Target cpp110 = { "EDID.cpp" , "../../Applied/CCore/src/./video/EDID.cpp" } ;
Target dcpp110 = { "EDID.dep" , OBJ_PATH+"/EDID.dep" } ;
Rule rdcpp110 = { {&cpp110,&obj} , {&dcpp110} , {&execpp110} } ;
Exe execpp110 = { "CC-DEP EDID.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/EDID.o"
 ,"../../Applied/CCore/src/./video/EDID.cpp"
 ,"-MF"
 ,OBJ_PATH+"/EDID.dep"
} } ;

Target vdcpp110 = { "EDID.vm.dep" , OBJ_PATH+"/EDID.vm.dep" } ;
Rule rvdcpp110 = { {&dcpp110} , {&vdcpp110} , {&exedcpp110} } ;
Exe exedcpp110 = { "CC-VM-DEP EDID.cpp" , VMDEP , { OBJ_PATH+"/EDID.dep" , OBJ_PATH+"/EDID.vm.dep" , "110" } } ;

Target cpp111 = { "EchoDevice.cpp" , "../../Applied/CCore/src/./net/EchoDevice.cpp" } ;
Target dcpp111 = { "EchoDevice.dep" , OBJ_PATH+"/EchoDevice.dep" } ;
Rule rdcpp111 = { {&cpp111,&obj} , {&dcpp111} , {&execpp111} } ;
Exe execpp111 = { "CC-DEP EchoDevice.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/EchoDevice.o"
 ,"../../Applied/CCore/src/./net/EchoDevice.cpp"
 ,"-MF"
 ,OBJ_PATH+"/EchoDevice.dep"
} } ;

Target vdcpp111 = { "EchoDevice.vm.dep" , OBJ_PATH+"/EchoDevice.vm.dep" } ;
Rule rvdcpp111 = { {&dcpp111} , {&vdcpp111} , {&exedcpp111} } ;
Exe exedcpp111 = { "CC-VM-DEP EchoDevice.cpp" , VMDEP , { OBJ_PATH+"/EchoDevice.dep" , OBJ_PATH+"/EchoDevice.vm.dep" , "111" } } ;

Target cpp112 = { "ElementPool.cpp" , "../../Fundamental/CCore/src/ElementPool.cpp" } ;
Target dcpp112 = { "ElementPool.dep" , OBJ_PATH+"/ElementPool.dep" } ;
Rule rdcpp112 = { {&cpp112,&obj} , {&dcpp112} , {&execpp112} } ;
Exe execpp112 = { "CC-DEP ElementPool.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ElementPool.o"
 ,"../../Fundamental/CCore/src/ElementPool.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ElementPool.dep"
} } ;

Target vdcpp112 = { "ElementPool.vm.dep" , OBJ_PATH+"/ElementPool.vm.dep" } ;
Rule rvdcpp112 = { {&dcpp112} , {&vdcpp112} , {&exedcpp112} } ;
Exe exedcpp112 = { "CC-VM-DEP ElementPool.cpp" , VMDEP , { OBJ_PATH+"/ElementPool.dep" , OBJ_PATH+"/ElementPool.vm.dep" , "112" } } ;

Target cpp113 = { "Elf.cpp" , "../../Applied/CCore/src/Elf.cpp" } ;
Target dcpp113 = { "Elf.dep" , OBJ_PATH+"/Elf.dep" } ;
Rule rdcpp113 = { {&cpp113,&obj} , {&dcpp113} , {&execpp113} } ;
Exe execpp113 = { "CC-DEP Elf.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Elf.o"
 ,"../../Applied/CCore/src/Elf.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Elf.dep"
} } ;

Target vdcpp113 = { "Elf.vm.dep" , OBJ_PATH+"/Elf.vm.dep" } ;
Rule rvdcpp113 = { {&dcpp113} , {&vdcpp113} , {&exedcpp113} } ;
Exe exedcpp113 = { "CC-VM-DEP Elf.cpp" , VMDEP , { OBJ_PATH+"/Elf.dep" , OBJ_PATH+"/Elf.vm.dep" , "113" } } ;

Target cpp114 = { "ErrorText.cpp" , "../../Simple/CCore/src/ErrorText.cpp" } ;
Target dcpp114 = { "ErrorText.dep" , OBJ_PATH+"/ErrorText.dep" } ;
Rule rdcpp114 = { {&cpp114,&obj} , {&dcpp114} , {&execpp114} } ;
Exe execpp114 = { "CC-DEP ErrorText.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ErrorText.o"
 ,"../../Simple/CCore/src/ErrorText.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ErrorText.dep"
} } ;

Target vdcpp114 = { "ErrorText.vm.dep" , OBJ_PATH+"/ErrorText.vm.dep" } ;
Rule rvdcpp114 = { {&dcpp114} , {&vdcpp114} , {&exedcpp114} } ;
Exe exedcpp114 = { "CC-VM-DEP ErrorText.cpp" , VMDEP , { OBJ_PATH+"/ErrorText.dep" , OBJ_PATH+"/ErrorText.vm.dep" , "114" } } ;

Target cpp115 = { "EthDevice.cpp" , "../../Applied/CCore/src/./net/EthDevice.cpp" } ;
Target dcpp115 = { "EthDevice.dep" , OBJ_PATH+"/EthDevice.dep" } ;
Rule rdcpp115 = { {&cpp115,&obj} , {&dcpp115} , {&execpp115} } ;
Exe execpp115 = { "CC-DEP EthDevice.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/EthDevice.o"
 ,"../../Applied/CCore/src/./net/EthDevice.cpp"
 ,"-MF"
 ,OBJ_PATH+"/EthDevice.dep"
} } ;

Target vdcpp115 = { "EthDevice.vm.dep" , OBJ_PATH+"/EthDevice.vm.dep" } ;
Rule rvdcpp115 = { {&dcpp115} , {&vdcpp115} , {&exedcpp115} } ;
Exe exedcpp115 = { "CC-VM-DEP EthDevice.cpp" , VMDEP , { OBJ_PATH+"/EthDevice.dep" , OBJ_PATH+"/EthDevice.vm.dep" , "115" } } ;

Target cpp116 = { "EuclidRotate.cpp" , "../../Fundamental/CCore/src/./algon/EuclidRotate.cpp" } ;
Target dcpp116 = { "EuclidRotate.dep" , OBJ_PATH+"/EuclidRotate.dep" } ;
Rule rdcpp116 = { {&cpp116,&obj} , {&dcpp116} , {&execpp116} } ;
Exe execpp116 = { "CC-DEP EuclidRotate.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/EuclidRotate.o"
 ,"../../Fundamental/CCore/src/./algon/EuclidRotate.cpp"
 ,"-MF"
 ,OBJ_PATH+"/EuclidRotate.dep"
} } ;

Target vdcpp116 = { "EuclidRotate.vm.dep" , OBJ_PATH+"/EuclidRotate.vm.dep" } ;
Rule rvdcpp116 = { {&dcpp116} , {&vdcpp116} , {&exedcpp116} } ;
Exe exedcpp116 = { "CC-VM-DEP EuclidRotate.cpp" , VMDEP , { OBJ_PATH+"/EuclidRotate.dep" , OBJ_PATH+"/EuclidRotate.vm.dep" , "116" } } ;

Target cpp117 = { "Event.cpp" , "../../HCore/CCore/src/./task/Event.cpp" } ;
Target dcpp117 = { "Event.dep" , OBJ_PATH+"/Event.dep" } ;
Rule rdcpp117 = { {&cpp117,&obj} , {&dcpp117} , {&execpp117} } ;
Exe execpp117 = { "CC-DEP Event.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Event.o"
 ,"../../HCore/CCore/src/./task/Event.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Event.dep"
} } ;

Target vdcpp117 = { "Event.vm.dep" , OBJ_PATH+"/Event.vm.dep" } ;
Rule rvdcpp117 = { {&dcpp117} , {&vdcpp117} , {&exedcpp117} } ;
Exe exedcpp117 = { "CC-VM-DEP Event.cpp" , VMDEP , { OBJ_PATH+"/Event.dep" , OBJ_PATH+"/Event.vm.dep" , "117" } } ;

Target cpp118 = { "EventRecorder.cpp" , "../../Applied/CCore/src/EventRecorder.cpp" } ;
Target dcpp118 = { "EventRecorder.dep" , OBJ_PATH+"/EventRecorder.dep" } ;
Rule rdcpp118 = { {&cpp118,&obj} , {&dcpp118} , {&execpp118} } ;
Exe execpp118 = { "CC-DEP EventRecorder.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/EventRecorder.o"
 ,"../../Applied/CCore/src/EventRecorder.cpp"
 ,"-MF"
 ,OBJ_PATH+"/EventRecorder.dep"
} } ;

Target vdcpp118 = { "EventRecorder.vm.dep" , OBJ_PATH+"/EventRecorder.vm.dep" } ;
Rule rvdcpp118 = { {&dcpp118} , {&vdcpp118} , {&exedcpp118} } ;
Exe exedcpp118 = { "CC-VM-DEP EventRecorder.cpp" , VMDEP , { OBJ_PATH+"/EventRecorder.dep" , OBJ_PATH+"/EventRecorder.vm.dep" , "118" } } ;

Target cpp119 = { "Exception.cpp" , "../../Fundamental/CCore/src/Exception.cpp" } ;
Target dcpp119 = { "Exception.dep" , OBJ_PATH+"/Exception.dep" } ;
Rule rdcpp119 = { {&cpp119,&obj} , {&dcpp119} , {&execpp119} } ;
Exe execpp119 = { "CC-DEP Exception.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Exception.o"
 ,"../../Fundamental/CCore/src/Exception.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Exception.dep"
} } ;

Target vdcpp119 = { "Exception.vm.dep" , OBJ_PATH+"/Exception.vm.dep" } ;
Rule rvdcpp119 = { {&dcpp119} , {&vdcpp119} , {&exedcpp119} } ;
Exe exedcpp119 = { "CC-VM-DEP Exception.cpp" , VMDEP , { OBJ_PATH+"/Exception.dep" , OBJ_PATH+"/Exception.vm.dep" , "119" } } ;

Target cpp120 = { "ExceptionFrame.cpp" , "../../Desktop/Lib/CCore/src/./video/ExceptionFrame.cpp" } ;
Target dcpp120 = { "ExceptionFrame.dep" , OBJ_PATH+"/ExceptionFrame.dep" } ;
Rule rdcpp120 = { {&cpp120,&obj} , {&dcpp120} , {&execpp120} } ;
Exe execpp120 = { "CC-DEP ExceptionFrame.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ExceptionFrame.o"
 ,"../../Desktop/Lib/CCore/src/./video/ExceptionFrame.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ExceptionFrame.dep"
} } ;

Target vdcpp120 = { "ExceptionFrame.vm.dep" , OBJ_PATH+"/ExceptionFrame.vm.dep" } ;
Rule rvdcpp120 = { {&dcpp120} , {&vdcpp120} , {&exedcpp120} } ;
Exe exedcpp120 = { "CC-VM-DEP ExceptionFrame.cpp" , VMDEP , { OBJ_PATH+"/ExceptionFrame.dep" , OBJ_PATH+"/ExceptionFrame.vm.dep" , "120" } } ;

Target cpp121 = { "ExceptionType.cpp" , "../../Simple/CCore/src/./gadget/ExceptionType.cpp" } ;
Target dcpp121 = { "ExceptionType.dep" , OBJ_PATH+"/ExceptionType.dep" } ;
Rule rdcpp121 = { {&cpp121,&obj} , {&dcpp121} , {&execpp121} } ;
Exe execpp121 = { "CC-DEP ExceptionType.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ExceptionType.o"
 ,"../../Simple/CCore/src/./gadget/ExceptionType.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ExceptionType.dep"
} } ;

Target vdcpp121 = { "ExceptionType.vm.dep" , OBJ_PATH+"/ExceptionType.vm.dep" } ;
Rule rvdcpp121 = { {&dcpp121} , {&vdcpp121} , {&exedcpp121} } ;
Exe exedcpp121 = { "CC-VM-DEP ExceptionType.cpp" , VMDEP , { OBJ_PATH+"/ExceptionType.dep" , OBJ_PATH+"/ExceptionType.vm.dep" , "121" } } ;

Target cpp122 = { "FFTMul.cpp" , "../../Applied/CCore/src/./math/FFTMul.cpp" } ;
Target dcpp122 = { "FFTMul.dep" , OBJ_PATH+"/FFTMul.dep" } ;
Rule rdcpp122 = { {&cpp122,&obj} , {&dcpp122} , {&execpp122} } ;
Exe execpp122 = { "CC-DEP FFTMul.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/FFTMul.o"
 ,"../../Applied/CCore/src/./math/FFTMul.cpp"
 ,"-MF"
 ,OBJ_PATH+"/FFTMul.dep"
} } ;

Target vdcpp122 = { "FFTMul.vm.dep" , OBJ_PATH+"/FFTMul.vm.dep" } ;
Rule rvdcpp122 = { {&dcpp122} , {&vdcpp122} , {&exedcpp122} } ;
Exe exedcpp122 = { "CC-VM-DEP FFTMul.cpp" , VMDEP , { OBJ_PATH+"/FFTMul.dep" , OBJ_PATH+"/FFTMul.vm.dep" , "122" } } ;

Target cpp123 = { "FastMutex.cpp" , "../../HCore/CCore/src/./task/FastMutex.cpp" } ;
Target dcpp123 = { "FastMutex.dep" , OBJ_PATH+"/FastMutex.dep" } ;
Rule rdcpp123 = { {&cpp123,&obj} , {&dcpp123} , {&execpp123} } ;
Exe execpp123 = { "CC-DEP FastMutex.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/FastMutex.o"
 ,"../../HCore/CCore/src/./task/FastMutex.cpp"
 ,"-MF"
 ,OBJ_PATH+"/FastMutex.dep"
} } ;

Target vdcpp123 = { "FastMutex.vm.dep" , OBJ_PATH+"/FastMutex.vm.dep" } ;
Rule rvdcpp123 = { {&dcpp123} , {&vdcpp123} , {&exedcpp123} } ;
Exe exedcpp123 = { "CC-VM-DEP FastMutex.cpp" , VMDEP , { OBJ_PATH+"/FastMutex.dep" , OBJ_PATH+"/FastMutex.vm.dep" , "123" } } ;

Target cpp124 = { "FeedBuf.cpp" , "../../Simple/CCore/src/FeedBuf.cpp" } ;
Target dcpp124 = { "FeedBuf.dep" , OBJ_PATH+"/FeedBuf.dep" } ;
Rule rdcpp124 = { {&cpp124,&obj} , {&dcpp124} , {&execpp124} } ;
Exe execpp124 = { "CC-DEP FeedBuf.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/FeedBuf.o"
 ,"../../Simple/CCore/src/FeedBuf.cpp"
 ,"-MF"
 ,OBJ_PATH+"/FeedBuf.dep"
} } ;

Target vdcpp124 = { "FeedBuf.vm.dep" , OBJ_PATH+"/FeedBuf.vm.dep" } ;
Rule rvdcpp124 = { {&dcpp124} , {&vdcpp124} , {&exedcpp124} } ;
Exe exedcpp124 = { "CC-VM-DEP FeedBuf.cpp" , VMDEP , { OBJ_PATH+"/FeedBuf.dep" , OBJ_PATH+"/FeedBuf.vm.dep" , "124" } } ;

Target cpp125 = { "Fifo.cpp" , "../../Simple/CCore/src/Fifo.cpp" } ;
Target dcpp125 = { "Fifo.dep" , OBJ_PATH+"/Fifo.dep" } ;
Rule rdcpp125 = { {&cpp125,&obj} , {&dcpp125} , {&execpp125} } ;
Exe execpp125 = { "CC-DEP Fifo.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Fifo.o"
 ,"../../Simple/CCore/src/Fifo.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Fifo.dep"
} } ;

Target vdcpp125 = { "Fifo.vm.dep" , OBJ_PATH+"/Fifo.vm.dep" } ;
Rule rvdcpp125 = { {&dcpp125} , {&vdcpp125} , {&exedcpp125} } ;
Exe exedcpp125 = { "CC-VM-DEP Fifo.cpp" , VMDEP , { OBJ_PATH+"/Fifo.dep" , OBJ_PATH+"/Fifo.vm.dep" , "125" } } ;

Target cpp126 = { "FigureLib.cpp" , "../../Desktop/Lib/CCore/src/./video/FigureLib.cpp" } ;
Target dcpp126 = { "FigureLib.dep" , OBJ_PATH+"/FigureLib.dep" } ;
Rule rdcpp126 = { {&cpp126,&obj} , {&dcpp126} , {&execpp126} } ;
Exe execpp126 = { "CC-DEP FigureLib.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/FigureLib.o"
 ,"../../Desktop/Lib/CCore/src/./video/FigureLib.cpp"
 ,"-MF"
 ,OBJ_PATH+"/FigureLib.dep"
} } ;

Target vdcpp126 = { "FigureLib.vm.dep" , OBJ_PATH+"/FigureLib.vm.dep" } ;
Rule rvdcpp126 = { {&dcpp126} , {&vdcpp126} , {&exedcpp126} } ;
Exe exedcpp126 = { "CC-VM-DEP FigureLib.cpp" , VMDEP , { OBJ_PATH+"/FigureLib.dep" , OBJ_PATH+"/FigureLib.vm.dep" , "126" } } ;

Target cpp127 = { "FileBoss.cpp" , "../../Desktop/Tools/CCore/src/./video/FileBoss.cpp" } ;
Target dcpp127 = { "FileBoss.dep" , OBJ_PATH+"/FileBoss.dep" } ;
Rule rdcpp127 = { {&cpp127,&obj} , {&dcpp127} , {&execpp127} } ;
Exe execpp127 = { "CC-DEP FileBoss.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/FileBoss.o"
 ,"../../Desktop/Tools/CCore/src/./video/FileBoss.cpp"
 ,"-MF"
 ,OBJ_PATH+"/FileBoss.dep"
} } ;

Target vdcpp127 = { "FileBoss.vm.dep" , OBJ_PATH+"/FileBoss.vm.dep" } ;
Rule rvdcpp127 = { {&dcpp127} , {&vdcpp127} , {&exedcpp127} } ;
Exe exedcpp127 = { "CC-VM-DEP FileBoss.cpp" , VMDEP , { OBJ_PATH+"/FileBoss.dep" , OBJ_PATH+"/FileBoss.vm.dep" , "127" } } ;

Target cpp128 = { "FileFrame.cpp" , "../../Desktop/Lib/CCore/src/./video/FileFrame.cpp" } ;
Target dcpp128 = { "FileFrame.dep" , OBJ_PATH+"/FileFrame.dep" } ;
Rule rdcpp128 = { {&cpp128,&obj} , {&dcpp128} , {&execpp128} } ;
Exe execpp128 = { "CC-DEP FileFrame.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/FileFrame.o"
 ,"../../Desktop/Lib/CCore/src/./video/FileFrame.cpp"
 ,"-MF"
 ,OBJ_PATH+"/FileFrame.dep"
} } ;

Target vdcpp128 = { "FileFrame.vm.dep" , OBJ_PATH+"/FileFrame.vm.dep" } ;
Rule rvdcpp128 = { {&dcpp128} , {&vdcpp128} , {&exedcpp128} } ;
Exe exedcpp128 = { "CC-VM-DEP FileFrame.cpp" , VMDEP , { OBJ_PATH+"/FileFrame.dep" , OBJ_PATH+"/FileFrame.vm.dep" , "128" } } ;

Target cpp129 = { "FileName.cpp" , "../../Applied/CCore/src/FileName.cpp" } ;
Target dcpp129 = { "FileName.dep" , OBJ_PATH+"/FileName.dep" } ;
Rule rdcpp129 = { {&cpp129,&obj} , {&dcpp129} , {&execpp129} } ;
Exe execpp129 = { "CC-DEP FileName.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/FileName.o"
 ,"../../Applied/CCore/src/FileName.cpp"
 ,"-MF"
 ,OBJ_PATH+"/FileName.dep"
} } ;

Target vdcpp129 = { "FileName.vm.dep" , OBJ_PATH+"/FileName.vm.dep" } ;
Rule rvdcpp129 = { {&dcpp129} , {&vdcpp129} , {&exedcpp129} } ;
Exe exedcpp129 = { "CC-VM-DEP FileName.cpp" , VMDEP , { OBJ_PATH+"/FileName.dep" , OBJ_PATH+"/FileName.vm.dep" , "129" } } ;

Target cpp130 = { "FileNameCmp.cpp" , "../../Desktop/Tools/CCore/src/./video/FileNameCmp.cpp" } ;
Target dcpp130 = { "FileNameCmp.dep" , OBJ_PATH+"/FileNameCmp.dep" } ;
Rule rdcpp130 = { {&cpp130,&obj} , {&dcpp130} , {&execpp130} } ;
Exe execpp130 = { "CC-DEP FileNameCmp.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/FileNameCmp.o"
 ,"../../Desktop/Tools/CCore/src/./video/FileNameCmp.cpp"
 ,"-MF"
 ,OBJ_PATH+"/FileNameCmp.dep"
} } ;

Target vdcpp130 = { "FileNameCmp.vm.dep" , OBJ_PATH+"/FileNameCmp.vm.dep" } ;
Rule rvdcpp130 = { {&dcpp130} , {&vdcpp130} , {&exedcpp130} } ;
Exe exedcpp130 = { "CC-VM-DEP FileNameCmp.cpp" , VMDEP , { OBJ_PATH+"/FileNameCmp.dep" , OBJ_PATH+"/FileNameCmp.vm.dep" , "130" } } ;

Target cpp131 = { "FileNameMatch.cpp" , "../../Applied/CCore/src/FileNameMatch.cpp" } ;
Target dcpp131 = { "FileNameMatch.dep" , OBJ_PATH+"/FileNameMatch.dep" } ;
Rule rdcpp131 = { {&cpp131,&obj} , {&dcpp131} , {&execpp131} } ;
Exe execpp131 = { "CC-DEP FileNameMatch.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/FileNameMatch.o"
 ,"../../Applied/CCore/src/FileNameMatch.cpp"
 ,"-MF"
 ,OBJ_PATH+"/FileNameMatch.dep"
} } ;

Target vdcpp131 = { "FileNameMatch.vm.dep" , OBJ_PATH+"/FileNameMatch.vm.dep" } ;
Rule rvdcpp131 = { {&dcpp131} , {&vdcpp131} , {&exedcpp131} } ;
Exe exedcpp131 = { "CC-VM-DEP FileNameMatch.cpp" , VMDEP , { OBJ_PATH+"/FileNameMatch.dep" , OBJ_PATH+"/FileNameMatch.vm.dep" , "131" } } ;

Target cpp132 = { "FileSystem.cpp" , "../../HCore/CCore/src/FileSystem.cpp" } ;
Target dcpp132 = { "FileSystem.dep" , OBJ_PATH+"/FileSystem.dep" } ;
Rule rdcpp132 = { {&cpp132,&obj} , {&dcpp132} , {&execpp132} } ;
Exe execpp132 = { "CC-DEP FileSystem.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/FileSystem.o"
 ,"../../HCore/CCore/src/FileSystem.cpp"
 ,"-MF"
 ,OBJ_PATH+"/FileSystem.dep"
} } ;

Target vdcpp132 = { "FileSystem.vm.dep" , OBJ_PATH+"/FileSystem.vm.dep" } ;
Rule rvdcpp132 = { {&dcpp132} , {&vdcpp132} , {&exedcpp132} } ;
Exe exedcpp132 = { "CC-VM-DEP FileSystem.cpp" , VMDEP , { OBJ_PATH+"/FileSystem.dep" , OBJ_PATH+"/FileSystem.vm.dep" , "132" } } ;

Target cpp133 = { "FileToMem.cpp" , "../../HCore/CCore/src/FileToMem.cpp" } ;
Target dcpp133 = { "FileToMem.dep" , OBJ_PATH+"/FileToMem.dep" } ;
Rule rdcpp133 = { {&cpp133,&obj} , {&dcpp133} , {&execpp133} } ;
Exe execpp133 = { "CC-DEP FileToMem.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/FileToMem.o"
 ,"../../HCore/CCore/src/FileToMem.cpp"
 ,"-MF"
 ,OBJ_PATH+"/FileToMem.dep"
} } ;

Target vdcpp133 = { "FileToMem.vm.dep" , OBJ_PATH+"/FileToMem.vm.dep" } ;
Rule rvdcpp133 = { {&dcpp133} , {&vdcpp133} , {&exedcpp133} } ;
Exe exedcpp133 = { "CC-VM-DEP FileToMem.cpp" , VMDEP , { OBJ_PATH+"/FileToMem.dep" , OBJ_PATH+"/FileToMem.vm.dep" , "133" } } ;

Target cpp134 = { "FileToRead.cpp" , "../../HCore/CCore/src/FileToRead.cpp" } ;
Target dcpp134 = { "FileToRead.dep" , OBJ_PATH+"/FileToRead.dep" } ;
Rule rdcpp134 = { {&cpp134,&obj} , {&dcpp134} , {&execpp134} } ;
Exe execpp134 = { "CC-DEP FileToRead.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/FileToRead.o"
 ,"../../HCore/CCore/src/FileToRead.cpp"
 ,"-MF"
 ,OBJ_PATH+"/FileToRead.dep"
} } ;

Target vdcpp134 = { "FileToRead.vm.dep" , OBJ_PATH+"/FileToRead.vm.dep" } ;
Rule rvdcpp134 = { {&dcpp134} , {&vdcpp134} , {&exedcpp134} } ;
Exe exedcpp134 = { "CC-VM-DEP FileToRead.cpp" , VMDEP , { OBJ_PATH+"/FileToRead.dep" , OBJ_PATH+"/FileToRead.vm.dep" , "134" } } ;

Target cpp135 = { "Font.cpp" , "../../Desktop/Font/CCore/src/./video/Font.cpp" } ;
Target dcpp135 = { "Font.dep" , OBJ_PATH+"/Font.dep" } ;
Rule rdcpp135 = { {&cpp135,&obj} , {&dcpp135} , {&execpp135} } ;
Exe execpp135 = { "CC-DEP Font.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Font.o"
 ,"../../Desktop/Font/CCore/src/./video/Font.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Font.dep"
} } ;

Target vdcpp135 = { "Font.vm.dep" , OBJ_PATH+"/Font.vm.dep" } ;
Rule rvdcpp135 = { {&dcpp135} , {&vdcpp135} , {&exedcpp135} } ;
Exe exedcpp135 = { "CC-VM-DEP Font.cpp" , VMDEP , { OBJ_PATH+"/Font.dep" , OBJ_PATH+"/Font.vm.dep" , "135" } } ;

Target cpp136 = { "FontDatabase.cpp" , "../../Desktop/Tools/CCore/src/./video/FontDatabase.cpp" } ;
Target dcpp136 = { "FontDatabase.dep" , OBJ_PATH+"/FontDatabase.dep" } ;
Rule rdcpp136 = { {&cpp136,&obj} , {&dcpp136} , {&execpp136} } ;
Exe execpp136 = { "CC-DEP FontDatabase.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/FontDatabase.o"
 ,"../../Desktop/Tools/CCore/src/./video/FontDatabase.cpp"
 ,"-MF"
 ,OBJ_PATH+"/FontDatabase.dep"
} } ;

Target vdcpp136 = { "FontDatabase.vm.dep" , OBJ_PATH+"/FontDatabase.vm.dep" } ;
Rule rvdcpp136 = { {&dcpp136} , {&vdcpp136} , {&exedcpp136} } ;
Exe exedcpp136 = { "CC-VM-DEP FontDatabase.cpp" , VMDEP , { OBJ_PATH+"/FontDatabase.dep" , OBJ_PATH+"/FontDatabase.vm.dep" , "136" } } ;

Target cpp137 = { "FontEdit.cpp" , "../../Desktop/Lib/CCore/src/./video/pref/FontEdit.cpp" } ;
Target dcpp137 = { "FontEdit.dep" , OBJ_PATH+"/FontEdit.dep" } ;
Rule rdcpp137 = { {&cpp137,&obj} , {&dcpp137} , {&execpp137} } ;
Exe execpp137 = { "CC-DEP FontEdit.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/FontEdit.o"
 ,"../../Desktop/Lib/CCore/src/./video/pref/FontEdit.cpp"
 ,"-MF"
 ,OBJ_PATH+"/FontEdit.dep"
} } ;

Target vdcpp137 = { "FontEdit.vm.dep" , OBJ_PATH+"/FontEdit.vm.dep" } ;
Rule rvdcpp137 = { {&dcpp137} , {&vdcpp137} , {&exedcpp137} } ;
Exe exedcpp137 = { "CC-VM-DEP FontEdit.cpp" , VMDEP , { OBJ_PATH+"/FontEdit.dep" , OBJ_PATH+"/FontEdit.vm.dep" , "137" } } ;

Target cpp138 = { "FontLookup.cpp" , "../../Desktop/Tools/CCore/src/./video/FontLookup.cpp" } ;
Target dcpp138 = { "FontLookup.dep" , OBJ_PATH+"/FontLookup.dep" } ;
Rule rdcpp138 = { {&cpp138,&obj} , {&dcpp138} , {&execpp138} } ;
Exe execpp138 = { "CC-DEP FontLookup.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/FontLookup.o"
 ,"../../Desktop/Tools/CCore/src/./video/FontLookup.cpp"
 ,"-MF"
 ,OBJ_PATH+"/FontLookup.dep"
} } ;

Target vdcpp138 = { "FontLookup.vm.dep" , OBJ_PATH+"/FontLookup.vm.dep" } ;
Rule rvdcpp138 = { {&dcpp138} , {&vdcpp138} , {&exedcpp138} } ;
Exe exedcpp138 = { "CC-VM-DEP FontLookup.cpp" , VMDEP , { OBJ_PATH+"/FontLookup.dep" , OBJ_PATH+"/FontLookup.vm.dep" , "138" } } ;

Target cpp139 = { "FontParam.cpp" , "../../Desktop/Tools/CCore/src/./video/FontParam.cpp" } ;
Target dcpp139 = { "FontParam.dep" , OBJ_PATH+"/FontParam.dep" } ;
Rule rdcpp139 = { {&cpp139,&obj} , {&dcpp139} , {&execpp139} } ;
Exe execpp139 = { "CC-DEP FontParam.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/FontParam.o"
 ,"../../Desktop/Tools/CCore/src/./video/FontParam.cpp"
 ,"-MF"
 ,OBJ_PATH+"/FontParam.dep"
} } ;

Target vdcpp139 = { "FontParam.vm.dep" , OBJ_PATH+"/FontParam.vm.dep" } ;
Rule rvdcpp139 = { {&dcpp139} , {&vdcpp139} , {&exedcpp139} } ;
Exe exedcpp139 = { "CC-VM-DEP FontParam.cpp" , VMDEP , { OBJ_PATH+"/FontParam.dep" , OBJ_PATH+"/FontParam.vm.dep" , "139" } } ;

Target cpp140 = { "FontReplace.cpp" , "../../Desktop/Lib/CCore/src/./video/FontReplace.cpp" } ;
Target dcpp140 = { "FontReplace.dep" , OBJ_PATH+"/FontReplace.dep" } ;
Rule rdcpp140 = { {&cpp140,&obj} , {&dcpp140} , {&execpp140} } ;
Exe execpp140 = { "CC-DEP FontReplace.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/FontReplace.o"
 ,"../../Desktop/Lib/CCore/src/./video/FontReplace.cpp"
 ,"-MF"
 ,OBJ_PATH+"/FontReplace.dep"
} } ;

Target vdcpp140 = { "FontReplace.vm.dep" , OBJ_PATH+"/FontReplace.vm.dep" } ;
Rule rvdcpp140 = { {&dcpp140} , {&vdcpp140} , {&exedcpp140} } ;
Exe exedcpp140 = { "CC-VM-DEP FontReplace.cpp" , VMDEP , { OBJ_PATH+"/FontReplace.dep" , OBJ_PATH+"/FontReplace.vm.dep" , "140" } } ;

Target cpp141 = { "ForLoop.cpp" , "../../Simple/CCore/src/ForLoop.cpp" } ;
Target dcpp141 = { "ForLoop.dep" , OBJ_PATH+"/ForLoop.dep" } ;
Rule rdcpp141 = { {&cpp141,&obj} , {&dcpp141} , {&execpp141} } ;
Exe execpp141 = { "CC-DEP ForLoop.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ForLoop.o"
 ,"../../Simple/CCore/src/ForLoop.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ForLoop.dep"
} } ;

Target vdcpp141 = { "ForLoop.vm.dep" , OBJ_PATH+"/ForLoop.vm.dep" } ;
Rule rvdcpp141 = { {&dcpp141} , {&vdcpp141} , {&exedcpp141} } ;
Exe exedcpp141 = { "CC-VM-DEP ForLoop.cpp" , VMDEP , { OBJ_PATH+"/ForLoop.dep" , OBJ_PATH+"/ForLoop.vm.dep" , "141" } } ;

Target cpp142 = { "Forget.cpp" , "../../Applied/CCore/src/./crypton/Forget.cpp" } ;
Target dcpp142 = { "Forget.dep" , OBJ_PATH+"/Forget.dep" } ;
Rule rdcpp142 = { {&cpp142,&obj} , {&dcpp142} , {&execpp142} } ;
Exe execpp142 = { "CC-DEP Forget.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Forget.o"
 ,"../../Applied/CCore/src/./crypton/Forget.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Forget.dep"
} } ;

Target vdcpp142 = { "Forget.vm.dep" , OBJ_PATH+"/Forget.vm.dep" } ;
Rule rvdcpp142 = { {&dcpp142} , {&vdcpp142} , {&exedcpp142} } ;
Exe exedcpp142 = { "CC-VM-DEP Forget.cpp" , VMDEP , { OBJ_PATH+"/Forget.dep" , OBJ_PATH+"/Forget.vm.dep" , "142" } } ;

Target cpp143 = { "FrameBase.cpp" , "../../Desktop/Lib/CCore/src/./video/FrameBase.cpp" } ;
Target dcpp143 = { "FrameBase.dep" , OBJ_PATH+"/FrameBase.dep" } ;
Rule rdcpp143 = { {&cpp143,&obj} , {&dcpp143} , {&execpp143} } ;
Exe execpp143 = { "CC-DEP FrameBase.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/FrameBase.o"
 ,"../../Desktop/Lib/CCore/src/./video/FrameBase.cpp"
 ,"-MF"
 ,OBJ_PATH+"/FrameBase.dep"
} } ;

Target vdcpp143 = { "FrameBase.vm.dep" , OBJ_PATH+"/FrameBase.vm.dep" } ;
Rule rvdcpp143 = { {&dcpp143} , {&vdcpp143} , {&exedcpp143} } ;
Exe exedcpp143 = { "CC-VM-DEP FrameBase.cpp" , VMDEP , { OBJ_PATH+"/FrameBase.dep" , OBJ_PATH+"/FrameBase.vm.dep" , "143" } } ;

Target cpp144 = { "FrameBuf.cpp" , "../../Applied/CCore/src/./video/FrameBuf.cpp" } ;
Target dcpp144 = { "FrameBuf.dep" , OBJ_PATH+"/FrameBuf.dep" } ;
Rule rdcpp144 = { {&cpp144,&obj} , {&dcpp144} , {&execpp144} } ;
Exe execpp144 = { "CC-DEP FrameBuf.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/FrameBuf.o"
 ,"../../Applied/CCore/src/./video/FrameBuf.cpp"
 ,"-MF"
 ,OBJ_PATH+"/FrameBuf.dep"
} } ;

Target vdcpp144 = { "FrameBuf.vm.dep" , OBJ_PATH+"/FrameBuf.vm.dep" } ;
Rule rvdcpp144 = { {&dcpp144} , {&vdcpp144} , {&exedcpp144} } ;
Exe exedcpp144 = { "CC-VM-DEP FrameBuf.cpp" , VMDEP , { OBJ_PATH+"/FrameBuf.dep" , OBJ_PATH+"/FrameBuf.vm.dep" , "144" } } ;

Target cpp145 = { "FrameOf.cpp" , "../../Desktop/Lib/CCore/src/./video/FrameOf.cpp" } ;
Target dcpp145 = { "FrameOf.dep" , OBJ_PATH+"/FrameOf.dep" } ;
Rule rdcpp145 = { {&cpp145,&obj} , {&dcpp145} , {&execpp145} } ;
Exe execpp145 = { "CC-DEP FrameOf.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/FrameOf.o"
 ,"../../Desktop/Lib/CCore/src/./video/FrameOf.cpp"
 ,"-MF"
 ,OBJ_PATH+"/FrameOf.dep"
} } ;

Target vdcpp145 = { "FrameOf.vm.dep" , OBJ_PATH+"/FrameOf.vm.dep" } ;
Rule rvdcpp145 = { {&dcpp145} , {&vdcpp145} , {&exedcpp145} } ;
Exe exedcpp145 = { "CC-VM-DEP FrameOf.cpp" , VMDEP , { OBJ_PATH+"/FrameOf.dep" , OBJ_PATH+"/FrameOf.vm.dep" , "145" } } ;

Target cpp146 = { "FrameWindow.cpp" , "../../Desktop/Core/CCore/src/./video/FrameWindow.cpp" } ;
Target dcpp146 = { "FrameWindow.dep" , OBJ_PATH+"/FrameWindow.dep" } ;
Rule rdcpp146 = { {&cpp146,&obj} , {&dcpp146} , {&execpp146} } ;
Exe execpp146 = { "CC-DEP FrameWindow.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/FrameWindow.o"
 ,"../../Desktop/Core/CCore/src/./video/FrameWindow.cpp"
 ,"-MF"
 ,OBJ_PATH+"/FrameWindow.dep"
} } ;

Target vdcpp146 = { "FrameWindow.vm.dep" , OBJ_PATH+"/FrameWindow.vm.dep" } ;
Rule rvdcpp146 = { {&dcpp146} , {&vdcpp146} , {&exedcpp146} } ;
Exe exedcpp146 = { "CC-VM-DEP FrameWindow.cpp" , VMDEP , { OBJ_PATH+"/FrameWindow.dep" , OBJ_PATH+"/FrameWindow.vm.dep" , "146" } } ;

Target cpp147 = { "FreeType.cpp" , "../../Desktop/Font/CCore/src/./video/FreeType.cpp" } ;
Target dcpp147 = { "FreeType.dep" , OBJ_PATH+"/FreeType.dep" } ;
Rule rdcpp147 = { {&cpp147,&obj} , {&dcpp147} , {&execpp147} } ;
Exe execpp147 = { "CC-DEP FreeType.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/FreeType.o"
 ,"../../Desktop/Font/CCore/src/./video/FreeType.cpp"
 ,"-MF"
 ,OBJ_PATH+"/FreeType.dep"
} } ;

Target vdcpp147 = { "FreeType.vm.dep" , OBJ_PATH+"/FreeType.vm.dep" } ;
Rule rvdcpp147 = { {&dcpp147} , {&vdcpp147} , {&exedcpp147} } ;
Exe exedcpp147 = { "CC-VM-DEP FreeType.cpp" , VMDEP , { OBJ_PATH+"/FreeType.dep" , OBJ_PATH+"/FreeType.vm.dep" , "147" } } ;

Target cpp148 = { "FreeTypeFont.cpp" , "../../Desktop/Font/CCore/src/./video/FreeTypeFont.cpp" } ;
Target dcpp148 = { "FreeTypeFont.dep" , OBJ_PATH+"/FreeTypeFont.dep" } ;
Rule rdcpp148 = { {&cpp148,&obj} , {&dcpp148} , {&execpp148} } ;
Exe execpp148 = { "CC-DEP FreeTypeFont.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/FreeTypeFont.o"
 ,"../../Desktop/Font/CCore/src/./video/FreeTypeFont.cpp"
 ,"-MF"
 ,OBJ_PATH+"/FreeTypeFont.dep"
} } ;

Target vdcpp148 = { "FreeTypeFont.vm.dep" , OBJ_PATH+"/FreeTypeFont.vm.dep" } ;
Rule rvdcpp148 = { {&dcpp148} , {&vdcpp148} , {&exedcpp148} } ;
Exe exedcpp148 = { "CC-VM-DEP FreeTypeFont.cpp" , VMDEP , { OBJ_PATH+"/FreeTypeFont.dep" , OBJ_PATH+"/FreeTypeFont.vm.dep" , "148" } } ;

Target cpp149 = { "FuncTask.cpp" , "../../Applied/CCore/src/./task/FuncTask.cpp" } ;
Target dcpp149 = { "FuncTask.dep" , OBJ_PATH+"/FuncTask.dep" } ;
Rule rdcpp149 = { {&cpp149,&obj} , {&dcpp149} , {&execpp149} } ;
Exe execpp149 = { "CC-DEP FuncTask.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/FuncTask.o"
 ,"../../Applied/CCore/src/./task/FuncTask.cpp"
 ,"-MF"
 ,OBJ_PATH+"/FuncTask.dep"
} } ;

Target vdcpp149 = { "FuncTask.vm.dep" , OBJ_PATH+"/FuncTask.vm.dep" } ;
Rule rvdcpp149 = { {&dcpp149} , {&vdcpp149} , {&exedcpp149} } ;
Exe exedcpp149 = { "CC-VM-DEP FuncTask.cpp" , VMDEP , { OBJ_PATH+"/FuncTask.dep" , OBJ_PATH+"/FuncTask.vm.dep" , "149" } } ;

Target cpp150 = { "Function.cpp" , "../../Simple/CCore/src/./gadget/Function.cpp" } ;
Target dcpp150 = { "Function.dep" , OBJ_PATH+"/Function.dep" } ;
Rule rdcpp150 = { {&cpp150,&obj} , {&dcpp150} , {&execpp150} } ;
Exe execpp150 = { "CC-DEP Function.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Function.o"
 ,"../../Simple/CCore/src/./gadget/Function.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Function.dep"
} } ;

Target vdcpp150 = { "Function.vm.dep" , OBJ_PATH+"/Function.vm.dep" } ;
Rule rvdcpp150 = { {&dcpp150} , {&vdcpp150} , {&exedcpp150} } ;
Exe exedcpp150 = { "CC-VM-DEP Function.cpp" , VMDEP , { OBJ_PATH+"/Function.dep" , OBJ_PATH+"/Function.vm.dep" , "150" } } ;

Target cpp151 = { "FunctorType.cpp" , "../../Simple/CCore/src/FunctorType.cpp" } ;
Target dcpp151 = { "FunctorType.dep" , OBJ_PATH+"/FunctorType.dep" } ;
Rule rdcpp151 = { {&cpp151,&obj} , {&dcpp151} , {&execpp151} } ;
Exe execpp151 = { "CC-DEP FunctorType.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/FunctorType.o"
 ,"../../Simple/CCore/src/FunctorType.cpp"
 ,"-MF"
 ,OBJ_PATH+"/FunctorType.dep"
} } ;

Target vdcpp151 = { "FunctorType.vm.dep" , OBJ_PATH+"/FunctorType.vm.dep" } ;
Rule rvdcpp151 = { {&dcpp151} , {&vdcpp151} , {&exedcpp151} } ;
Exe exedcpp151 = { "CC-VM-DEP FunctorType.cpp" , VMDEP , { OBJ_PATH+"/FunctorType.dep" , OBJ_PATH+"/FunctorType.vm.dep" , "151" } } ;

Target cpp152 = { "GCDConst.cpp" , "../../Fundamental/CCore/src/./algon/GCDConst.cpp" } ;
Target dcpp152 = { "GCDConst.dep" , OBJ_PATH+"/GCDConst.dep" } ;
Rule rdcpp152 = { {&cpp152,&obj} , {&dcpp152} , {&execpp152} } ;
Exe execpp152 = { "CC-DEP GCDConst.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/GCDConst.o"
 ,"../../Fundamental/CCore/src/./algon/GCDConst.cpp"
 ,"-MF"
 ,OBJ_PATH+"/GCDConst.dep"
} } ;

Target vdcpp152 = { "GCDConst.vm.dep" , OBJ_PATH+"/GCDConst.vm.dep" } ;
Rule rvdcpp152 = { {&dcpp152} , {&vdcpp152} , {&exedcpp152} } ;
Exe exedcpp152 = { "CC-VM-DEP GCDConst.cpp" , VMDEP , { OBJ_PATH+"/GCDConst.dep" , OBJ_PATH+"/GCDConst.vm.dep" , "152" } } ;

Target cpp153 = { "Gadget.cpp" , "../../Simple/CCore/src/Gadget.cpp" } ;
Target dcpp153 = { "Gadget.dep" , OBJ_PATH+"/Gadget.dep" } ;
Rule rdcpp153 = { {&cpp153,&obj} , {&dcpp153} , {&execpp153} } ;
Exe execpp153 = { "CC-DEP Gadget.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Gadget.o"
 ,"../../Simple/CCore/src/Gadget.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Gadget.dep"
} } ;

Target vdcpp153 = { "Gadget.vm.dep" , OBJ_PATH+"/Gadget.vm.dep" } ;
Rule rvdcpp153 = { {&dcpp153} , {&vdcpp153} , {&exedcpp153} } ;
Exe exedcpp153 = { "CC-VM-DEP Gadget.cpp" , VMDEP , { OBJ_PATH+"/Gadget.dep" , OBJ_PATH+"/Gadget.vm.dep" , "153" } } ;

Target cpp154 = { "Gamma.cpp" , "../../Applied/CCore/src/./video/Gamma.cpp" } ;
Target dcpp154 = { "Gamma.dep" , OBJ_PATH+"/Gamma.dep" } ;
Rule rdcpp154 = { {&cpp154,&obj} , {&dcpp154} , {&execpp154} } ;
Exe execpp154 = { "CC-DEP Gamma.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Gamma.o"
 ,"../../Applied/CCore/src/./video/Gamma.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Gamma.dep"
} } ;

Target vdcpp154 = { "Gamma.vm.dep" , OBJ_PATH+"/Gamma.vm.dep" } ;
Rule rvdcpp154 = { {&dcpp154} , {&vdcpp154} , {&exedcpp154} } ;
Exe exedcpp154 = { "CC-VM-DEP Gamma.cpp" , VMDEP , { OBJ_PATH+"/Gamma.dep" , OBJ_PATH+"/Gamma.vm.dep" , "154" } } ;

Target cpp155 = { "GammaTable.cpp" , "../../Desktop/Draw/CCore/src/./video/GammaTable.cpp" } ;
Target dcpp155 = { "GammaTable.dep" , OBJ_PATH+"/GammaTable.dep" } ;
Rule rdcpp155 = { {&cpp155,&obj} , {&dcpp155} , {&execpp155} } ;
Exe execpp155 = { "CC-DEP GammaTable.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/GammaTable.o"
 ,"../../Desktop/Draw/CCore/src/./video/GammaTable.cpp"
 ,"-MF"
 ,OBJ_PATH+"/GammaTable.dep"
} } ;

Target vdcpp155 = { "GammaTable.vm.dep" , OBJ_PATH+"/GammaTable.vm.dep" } ;
Rule rvdcpp155 = { {&dcpp155} , {&vdcpp155} , {&exedcpp155} } ;
Exe exedcpp155 = { "CC-VM-DEP GammaTable.cpp" , VMDEP , { OBJ_PATH+"/GammaTable.dep" , OBJ_PATH+"/GammaTable.vm.dep" , "155" } } ;

Target cpp156 = { "GenFile.cpp" , "../../Fundamental/CCore/src/GenFile.cpp" } ;
Target dcpp156 = { "GenFile.dep" , OBJ_PATH+"/GenFile.dep" } ;
Rule rdcpp156 = { {&cpp156,&obj} , {&dcpp156} , {&execpp156} } ;
Exe execpp156 = { "CC-DEP GenFile.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/GenFile.o"
 ,"../../Fundamental/CCore/src/GenFile.cpp"
 ,"-MF"
 ,OBJ_PATH+"/GenFile.dep"
} } ;

Target vdcpp156 = { "GenFile.vm.dep" , OBJ_PATH+"/GenFile.vm.dep" } ;
Rule rvdcpp156 = { {&dcpp156} , {&vdcpp156} , {&exedcpp156} } ;
Exe exedcpp156 = { "CC-VM-DEP GenFile.cpp" , VMDEP , { OBJ_PATH+"/GenFile.dep" , OBJ_PATH+"/GenFile.vm.dep" , "156" } } ;

Target cpp157 = { "HFSBase.cpp" , "../../Applied/CCore/src/./net/HFSBase.cpp" } ;
Target dcpp157 = { "HFSBase.dep" , OBJ_PATH+"/HFSBase.dep" } ;
Rule rdcpp157 = { {&cpp157,&obj} , {&dcpp157} , {&execpp157} } ;
Exe execpp157 = { "CC-DEP HFSBase.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/HFSBase.o"
 ,"../../Applied/CCore/src/./net/HFSBase.cpp"
 ,"-MF"
 ,OBJ_PATH+"/HFSBase.dep"
} } ;

Target vdcpp157 = { "HFSBase.vm.dep" , OBJ_PATH+"/HFSBase.vm.dep" } ;
Rule rvdcpp157 = { {&dcpp157} , {&vdcpp157} , {&exedcpp157} } ;
Exe exedcpp157 = { "CC-VM-DEP HFSBase.cpp" , VMDEP , { OBJ_PATH+"/HFSBase.dep" , OBJ_PATH+"/HFSBase.vm.dep" , "157" } } ;

Target cpp158 = { "HFSClientDevice.cpp" , "../../Applied/CCore/src/./net/HFSClientDevice.cpp" } ;
Target dcpp158 = { "HFSClientDevice.dep" , OBJ_PATH+"/HFSClientDevice.dep" } ;
Rule rdcpp158 = { {&cpp158,&obj} , {&dcpp158} , {&execpp158} } ;
Exe execpp158 = { "CC-DEP HFSClientDevice.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/HFSClientDevice.o"
 ,"../../Applied/CCore/src/./net/HFSClientDevice.cpp"
 ,"-MF"
 ,OBJ_PATH+"/HFSClientDevice.dep"
} } ;

Target vdcpp158 = { "HFSClientDevice.vm.dep" , OBJ_PATH+"/HFSClientDevice.vm.dep" } ;
Rule rvdcpp158 = { {&dcpp158} , {&vdcpp158} , {&exedcpp158} } ;
Exe exedcpp158 = { "CC-VM-DEP HFSClientDevice.cpp" , VMDEP , { OBJ_PATH+"/HFSClientDevice.dep" , OBJ_PATH+"/HFSClientDevice.vm.dep" , "158" } } ;

Target cpp159 = { "HFSFileSystemDevice.cpp" , "../../Applied/CCore/src/./net/HFSFileSystemDevice.cpp" } ;
Target dcpp159 = { "HFSFileSystemDevice.dep" , OBJ_PATH+"/HFSFileSystemDevice.dep" } ;
Rule rdcpp159 = { {&cpp159,&obj} , {&dcpp159} , {&execpp159} } ;
Exe execpp159 = { "CC-DEP HFSFileSystemDevice.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/HFSFileSystemDevice.o"
 ,"../../Applied/CCore/src/./net/HFSFileSystemDevice.cpp"
 ,"-MF"
 ,OBJ_PATH+"/HFSFileSystemDevice.dep"
} } ;

Target vdcpp159 = { "HFSFileSystemDevice.vm.dep" , OBJ_PATH+"/HFSFileSystemDevice.vm.dep" } ;
Rule rvdcpp159 = { {&dcpp159} , {&vdcpp159} , {&exedcpp159} } ;
Exe exedcpp159 = { "CC-VM-DEP HFSFileSystemDevice.cpp" , VMDEP , { OBJ_PATH+"/HFSFileSystemDevice.dep" , OBJ_PATH+"/HFSFileSystemDevice.vm.dep" , "159" } } ;

Target cpp160 = { "Handle.cpp" , "../../Simple/CCore/src/./gadget/Handle.cpp" } ;
Target dcpp160 = { "Handle.dep" , OBJ_PATH+"/Handle.dep" } ;
Rule rdcpp160 = { {&cpp160,&obj} , {&dcpp160} , {&execpp160} } ;
Exe execpp160 = { "CC-DEP Handle.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Handle.o"
 ,"../../Simple/CCore/src/./gadget/Handle.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Handle.dep"
} } ;

Target vdcpp160 = { "Handle.vm.dep" , OBJ_PATH+"/Handle.vm.dep" } ;
Rule rvdcpp160 = { {&dcpp160} , {&vdcpp160} , {&exedcpp160} } ;
Exe exedcpp160 = { "CC-VM-DEP Handle.cpp" , VMDEP , { OBJ_PATH+"/Handle.dep" , OBJ_PATH+"/Handle.vm.dep" , "160" } } ;

Target cpp161 = { "HashFunction.cpp" , "../../Applied/CCore/src/./crypton/HashFunction.cpp" } ;
Target dcpp161 = { "HashFunction.dep" , OBJ_PATH+"/HashFunction.dep" } ;
Rule rdcpp161 = { {&cpp161,&obj} , {&dcpp161} , {&execpp161} } ;
Exe execpp161 = { "CC-DEP HashFunction.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/HashFunction.o"
 ,"../../Applied/CCore/src/./crypton/HashFunction.cpp"
 ,"-MF"
 ,OBJ_PATH+"/HashFunction.dep"
} } ;

Target vdcpp161 = { "HashFunction.vm.dep" , OBJ_PATH+"/HashFunction.vm.dep" } ;
Rule rvdcpp161 = { {&dcpp161} , {&vdcpp161} , {&exedcpp161} } ;
Exe exedcpp161 = { "CC-VM-DEP HashFunction.cpp" , VMDEP , { OBJ_PATH+"/HashFunction.dep" , OBJ_PATH+"/HashFunction.vm.dep" , "161" } } ;

Target cpp162 = { "HeapEngine.cpp" , "../../Fundamental/CCore/src/HeapEngine.cpp" } ;
Target dcpp162 = { "HeapEngine.dep" , OBJ_PATH+"/HeapEngine.dep" } ;
Rule rdcpp162 = { {&cpp162,&obj} , {&dcpp162} , {&execpp162} } ;
Exe execpp162 = { "CC-DEP HeapEngine.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/HeapEngine.o"
 ,"../../Fundamental/CCore/src/HeapEngine.cpp"
 ,"-MF"
 ,OBJ_PATH+"/HeapEngine.dep"
} } ;

Target vdcpp162 = { "HeapEngine.vm.dep" , OBJ_PATH+"/HeapEngine.vm.dep" } ;
Rule rvdcpp162 = { {&dcpp162} , {&vdcpp162} , {&exedcpp162} } ;
Exe exedcpp162 = { "CC-VM-DEP HeapEngine.cpp" , VMDEP , { OBJ_PATH+"/HeapEngine.dep" , OBJ_PATH+"/HeapEngine.vm.dep" , "162" } } ;

Target cpp163 = { "HeapSort.cpp" , "../../Fundamental/CCore/src/./sort/HeapSort.cpp" } ;
Target dcpp163 = { "HeapSort.dep" , OBJ_PATH+"/HeapSort.dep" } ;
Rule rdcpp163 = { {&cpp163,&obj} , {&dcpp163} , {&execpp163} } ;
Exe execpp163 = { "CC-DEP HeapSort.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/HeapSort.o"
 ,"../../Fundamental/CCore/src/./sort/HeapSort.cpp"
 ,"-MF"
 ,OBJ_PATH+"/HeapSort.dep"
} } ;

Target vdcpp163 = { "HeapSort.vm.dep" , OBJ_PATH+"/HeapSort.vm.dep" } ;
Rule rvdcpp163 = { {&dcpp163} , {&vdcpp163} , {&exedcpp163} } ;
Exe exedcpp163 = { "CC-VM-DEP HeapSort.cpp" , VMDEP , { OBJ_PATH+"/HeapSort.dep" , OBJ_PATH+"/HeapSort.vm.dep" , "163" } } ;

Target cpp164 = { "HomeFile.cpp" , "../../Desktop/Tools/CCore/src/./video/HomeFile.cpp" } ;
Target dcpp164 = { "HomeFile.dep" , OBJ_PATH+"/HomeFile.dep" } ;
Rule rdcpp164 = { {&cpp164,&obj} , {&dcpp164} , {&execpp164} } ;
Exe execpp164 = { "CC-DEP HomeFile.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/HomeFile.o"
 ,"../../Desktop/Tools/CCore/src/./video/HomeFile.cpp"
 ,"-MF"
 ,OBJ_PATH+"/HomeFile.dep"
} } ;

Target vdcpp164 = { "HomeFile.vm.dep" , OBJ_PATH+"/HomeFile.vm.dep" } ;
Rule rvdcpp164 = { {&dcpp164} , {&vdcpp164} , {&exedcpp164} } ;
Exe exedcpp164 = { "CC-VM-DEP HomeFile.cpp" , VMDEP , { OBJ_PATH+"/HomeFile.dep" , OBJ_PATH+"/HomeFile.vm.dep" , "164" } } ;

Target cpp165 = { "Incremental.cpp" , "../../Desktop/Tools/CCore/src/./video/Incremental.cpp" } ;
Target dcpp165 = { "Incremental.dep" , OBJ_PATH+"/Incremental.dep" } ;
Rule rdcpp165 = { {&cpp165,&obj} , {&dcpp165} , {&execpp165} } ;
Exe execpp165 = { "CC-DEP Incremental.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Incremental.o"
 ,"../../Desktop/Tools/CCore/src/./video/Incremental.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Incremental.dep"
} } ;

Target vdcpp165 = { "Incremental.vm.dep" , OBJ_PATH+"/Incremental.vm.dep" } ;
Rule rvdcpp165 = { {&dcpp165} , {&vdcpp165} , {&exedcpp165} } ;
Exe exedcpp165 = { "CC-VM-DEP Incremental.cpp" , VMDEP , { OBJ_PATH+"/Incremental.dep" , OBJ_PATH+"/Incremental.vm.dep" , "165" } } ;

Target cpp166 = { "Info.cpp" , "../../Desktop/Tools/CCore/src/./video/Info.cpp" } ;
Target dcpp166 = { "Info.dep" , OBJ_PATH+"/Info.dep" } ;
Rule rdcpp166 = { {&cpp166,&obj} , {&dcpp166} , {&execpp166} } ;
Exe execpp166 = { "CC-DEP Info.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Info.o"
 ,"../../Desktop/Tools/CCore/src/./video/Info.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Info.dep"
} } ;

Target vdcpp166 = { "Info.vm.dep" , OBJ_PATH+"/Info.vm.dep" } ;
Rule rvdcpp166 = { {&dcpp166} , {&vdcpp166} , {&exedcpp166} } ;
Exe exedcpp166 = { "CC-VM-DEP Info.cpp" , VMDEP , { OBJ_PATH+"/Info.dep" , OBJ_PATH+"/Info.vm.dep" , "166" } } ;

Target cpp167 = { "InfoSize.cpp" , "../../Desktop/Tools/CCore/src/./video/InfoSize.cpp" } ;
Target dcpp167 = { "InfoSize.dep" , OBJ_PATH+"/InfoSize.dep" } ;
Rule rdcpp167 = { {&cpp167,&obj} , {&dcpp167} , {&execpp167} } ;
Exe execpp167 = { "CC-DEP InfoSize.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/InfoSize.o"
 ,"../../Desktop/Tools/CCore/src/./video/InfoSize.cpp"
 ,"-MF"
 ,OBJ_PATH+"/InfoSize.dep"
} } ;

Target vdcpp167 = { "InfoSize.vm.dep" , OBJ_PATH+"/InfoSize.vm.dep" } ;
Rule rvdcpp167 = { {&dcpp167} , {&vdcpp167} , {&exedcpp167} } ;
Exe exedcpp167 = { "CC-VM-DEP InfoSize.cpp" , VMDEP , { OBJ_PATH+"/InfoSize.dep" , OBJ_PATH+"/InfoSize.vm.dep" , "167" } } ;

Target cpp168 = { "Init.cpp" , "../../Simple/CCore/src/./gadget/Init.cpp" } ;
Target dcpp168 = { "Init.dep" , OBJ_PATH+"/Init.dep" } ;
Rule rdcpp168 = { {&cpp168,&obj} , {&dcpp168} , {&execpp168} } ;
Exe execpp168 = { "CC-DEP Init.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Init.o"
 ,"../../Simple/CCore/src/./gadget/Init.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Init.dep"
} } ;

Target vdcpp168 = { "Init.vm.dep" , OBJ_PATH+"/Init.vm.dep" } ;
Rule rvdcpp168 = { {&dcpp168} , {&vdcpp168} , {&exedcpp168} } ;
Exe exedcpp168 = { "CC-VM-DEP Init.cpp" , VMDEP , { OBJ_PATH+"/Init.dep" , OBJ_PATH+"/Init.vm.dep" , "168" } } ;

Target cpp169 = { "InputUtils.cpp" , "../../Applied/CCore/src/InputUtils.cpp" } ;
Target dcpp169 = { "InputUtils.dep" , OBJ_PATH+"/InputUtils.dep" } ;
Rule rdcpp169 = { {&cpp169,&obj} , {&dcpp169} , {&execpp169} } ;
Exe execpp169 = { "CC-DEP InputUtils.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/InputUtils.o"
 ,"../../Applied/CCore/src/InputUtils.cpp"
 ,"-MF"
 ,OBJ_PATH+"/InputUtils.dep"
} } ;

Target vdcpp169 = { "InputUtils.vm.dep" , OBJ_PATH+"/InputUtils.vm.dep" } ;
Rule rvdcpp169 = { {&dcpp169} , {&vdcpp169} , {&exedcpp169} } ;
Exe exedcpp169 = { "CC-VM-DEP InputUtils.cpp" , VMDEP , { OBJ_PATH+"/InputUtils.dep" , OBJ_PATH+"/InputUtils.vm.dep" , "169" } } ;

Target cpp170 = { "InstanceLock.cpp" , "../../Simple/CCore/src/InstanceLock.cpp" } ;
Target dcpp170 = { "InstanceLock.dep" , OBJ_PATH+"/InstanceLock.dep" } ;
Rule rdcpp170 = { {&cpp170,&obj} , {&dcpp170} , {&execpp170} } ;
Exe execpp170 = { "CC-DEP InstanceLock.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/InstanceLock.o"
 ,"../../Simple/CCore/src/InstanceLock.cpp"
 ,"-MF"
 ,OBJ_PATH+"/InstanceLock.dep"
} } ;

Target vdcpp170 = { "InstanceLock.vm.dep" , OBJ_PATH+"/InstanceLock.vm.dep" } ;
Rule rvdcpp170 = { {&dcpp170} , {&vdcpp170} , {&exedcpp170} } ;
Exe exedcpp170 = { "CC-VM-DEP InstanceLock.cpp" , VMDEP , { OBJ_PATH+"/InstanceLock.dep" , OBJ_PATH+"/InstanceLock.vm.dep" , "170" } } ;

Target cpp171 = { "IntOp.cpp" , "../../Applied/CCore/src/./video/IntOp.cpp" } ;
Target dcpp171 = { "IntOp.dep" , OBJ_PATH+"/IntOp.dep" } ;
Rule rdcpp171 = { {&cpp171,&obj} , {&dcpp171} , {&execpp171} } ;
Exe execpp171 = { "CC-DEP IntOp.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/IntOp.o"
 ,"../../Applied/CCore/src/./video/IntOp.cpp"
 ,"-MF"
 ,OBJ_PATH+"/IntOp.dep"
} } ;

Target vdcpp171 = { "IntOp.vm.dep" , OBJ_PATH+"/IntOp.vm.dep" } ;
Rule rvdcpp171 = { {&dcpp171} , {&vdcpp171} , {&exedcpp171} } ;
Exe exedcpp171 = { "CC-VM-DEP IntOp.cpp" , VMDEP , { OBJ_PATH+"/IntOp.dep" , OBJ_PATH+"/IntOp.vm.dep" , "171" } } ;

Target cpp172 = { "IntPrint.cpp" , "../../Fundamental/CCore/src/./printf/IntPrint.cpp" } ;
Target dcpp172 = { "IntPrint.dep" , OBJ_PATH+"/IntPrint.dep" } ;
Rule rdcpp172 = { {&cpp172,&obj} , {&dcpp172} , {&execpp172} } ;
Exe execpp172 = { "CC-DEP IntPrint.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/IntPrint.o"
 ,"../../Fundamental/CCore/src/./printf/IntPrint.cpp"
 ,"-MF"
 ,OBJ_PATH+"/IntPrint.dep"
} } ;

Target vdcpp172 = { "IntPrint.vm.dep" , OBJ_PATH+"/IntPrint.vm.dep" } ;
Rule rvdcpp172 = { {&dcpp172} , {&vdcpp172} , {&exedcpp172} } ;
Exe exedcpp172 = { "CC-VM-DEP IntPrint.cpp" , VMDEP , { OBJ_PATH+"/IntPrint.dep" , OBJ_PATH+"/IntPrint.vm.dep" , "172" } } ;

Target cpp173 = { "IntScan.cpp" , "../../Fundamental/CCore/src/./scanf/IntScan.cpp" } ;
Target dcpp173 = { "IntScan.dep" , OBJ_PATH+"/IntScan.dep" } ;
Rule rdcpp173 = { {&cpp173,&obj} , {&dcpp173} , {&execpp173} } ;
Exe execpp173 = { "CC-DEP IntScan.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/IntScan.o"
 ,"../../Fundamental/CCore/src/./scanf/IntScan.cpp"
 ,"-MF"
 ,OBJ_PATH+"/IntScan.dep"
} } ;

Target vdcpp173 = { "IntScan.vm.dep" , OBJ_PATH+"/IntScan.vm.dep" } ;
Rule rvdcpp173 = { {&dcpp173} , {&vdcpp173} , {&exedcpp173} } ;
Exe exedcpp173 = { "CC-VM-DEP IntScan.cpp" , VMDEP , { OBJ_PATH+"/IntScan.dep" , OBJ_PATH+"/IntScan.vm.dep" , "173" } } ;

Target cpp174 = { "Integer.cpp" , "../../Applied/CCore/src/./math/Integer.cpp" } ;
Target dcpp174 = { "Integer.dep" , OBJ_PATH+"/Integer.dep" } ;
Rule rdcpp174 = { {&cpp174,&obj} , {&dcpp174} , {&execpp174} } ;
Exe execpp174 = { "CC-DEP Integer.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Integer.o"
 ,"../../Applied/CCore/src/./math/Integer.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Integer.dep"
} } ;

Target vdcpp174 = { "Integer.vm.dep" , OBJ_PATH+"/Integer.vm.dep" } ;
Rule rvdcpp174 = { {&dcpp174} , {&vdcpp174} , {&exedcpp174} } ;
Exe exedcpp174 = { "CC-VM-DEP Integer.cpp" , VMDEP , { OBJ_PATH+"/Integer.dep" , OBJ_PATH+"/Integer.vm.dep" , "174" } } ;

Target cpp175 = { "IntegerAlgo.cpp" , "../../Applied/CCore/src/./math/IntegerAlgo.cpp" } ;
Target dcpp175 = { "IntegerAlgo.dep" , OBJ_PATH+"/IntegerAlgo.dep" } ;
Rule rdcpp175 = { {&cpp175,&obj} , {&dcpp175} , {&execpp175} } ;
Exe execpp175 = { "CC-DEP IntegerAlgo.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/IntegerAlgo.o"
 ,"../../Applied/CCore/src/./math/IntegerAlgo.cpp"
 ,"-MF"
 ,OBJ_PATH+"/IntegerAlgo.dep"
} } ;

Target vdcpp175 = { "IntegerAlgo.vm.dep" , OBJ_PATH+"/IntegerAlgo.vm.dep" } ;
Rule rvdcpp175 = { {&dcpp175} , {&vdcpp175} , {&exedcpp175} } ;
Exe exedcpp175 = { "CC-VM-DEP IntegerAlgo.cpp" , VMDEP , { OBJ_PATH+"/IntegerAlgo.dep" , OBJ_PATH+"/IntegerAlgo.vm.dep" , "175" } } ;

Target cpp176 = { "IntegerBuilder.cpp" , "../../Applied/CCore/src/./math/IntegerBuilder.cpp" } ;
Target dcpp176 = { "IntegerBuilder.dep" , OBJ_PATH+"/IntegerBuilder.dep" } ;
Rule rdcpp176 = { {&cpp176,&obj} , {&dcpp176} , {&execpp176} } ;
Exe execpp176 = { "CC-DEP IntegerBuilder.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/IntegerBuilder.o"
 ,"../../Applied/CCore/src/./math/IntegerBuilder.cpp"
 ,"-MF"
 ,OBJ_PATH+"/IntegerBuilder.dep"
} } ;

Target vdcpp176 = { "IntegerBuilder.vm.dep" , OBJ_PATH+"/IntegerBuilder.vm.dep" } ;
Rule rvdcpp176 = { {&dcpp176} , {&vdcpp176} , {&exedcpp176} } ;
Exe exedcpp176 = { "CC-VM-DEP IntegerBuilder.cpp" , VMDEP , { OBJ_PATH+"/IntegerBuilder.dep" , OBJ_PATH+"/IntegerBuilder.vm.dep" , "176" } } ;

Target cpp177 = { "IntegerDivider.cpp" , "../../Applied/CCore/src/./math/IntegerDivider.cpp" } ;
Target dcpp177 = { "IntegerDivider.dep" , OBJ_PATH+"/IntegerDivider.dep" } ;
Rule rdcpp177 = { {&cpp177,&obj} , {&dcpp177} , {&execpp177} } ;
Exe execpp177 = { "CC-DEP IntegerDivider.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/IntegerDivider.o"
 ,"../../Applied/CCore/src/./math/IntegerDivider.cpp"
 ,"-MF"
 ,OBJ_PATH+"/IntegerDivider.dep"
} } ;

Target vdcpp177 = { "IntegerDivider.vm.dep" , OBJ_PATH+"/IntegerDivider.vm.dep" } ;
Rule rvdcpp177 = { {&dcpp177} , {&vdcpp177} , {&exedcpp177} } ;
Exe exedcpp177 = { "CC-VM-DEP IntegerDivider.cpp" , VMDEP , { OBJ_PATH+"/IntegerDivider.dep" , OBJ_PATH+"/IntegerDivider.vm.dep" , "177" } } ;

Target cpp178 = { "IntegerFastAlgo.cpp" , "CCore/src/./math/IntegerFastAlgo.cpp" } ;
Target dcpp178 = { "IntegerFastAlgo.dep" , OBJ_PATH+"/IntegerFastAlgo.dep" } ;
Rule rdcpp178 = { {&cpp178,&obj} , {&dcpp178} , {&execpp178} } ;
Exe execpp178 = { "CC-DEP IntegerFastAlgo.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/IntegerFastAlgo.o"
 ,"CCore/src/./math/IntegerFastAlgo.cpp"
 ,"-MF"
 ,OBJ_PATH+"/IntegerFastAlgo.dep"
} } ;

Target vdcpp178 = { "IntegerFastAlgo.vm.dep" , OBJ_PATH+"/IntegerFastAlgo.vm.dep" } ;
Rule rvdcpp178 = { {&dcpp178} , {&vdcpp178} , {&exedcpp178} } ;
Exe exedcpp178 = { "CC-VM-DEP IntegerFastAlgo.cpp" , VMDEP , { OBJ_PATH+"/IntegerFastAlgo.dep" , OBJ_PATH+"/IntegerFastAlgo.vm.dep" , "178" } } ;

Target cpp179 = { "IntegerFromString.cpp" , "../../Applied/CCore/src/./math/IntegerFromString.cpp" } ;
Target dcpp179 = { "IntegerFromString.dep" , OBJ_PATH+"/IntegerFromString.dep" } ;
Rule rdcpp179 = { {&cpp179,&obj} , {&dcpp179} , {&execpp179} } ;
Exe execpp179 = { "CC-DEP IntegerFromString.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/IntegerFromString.o"
 ,"../../Applied/CCore/src/./math/IntegerFromString.cpp"
 ,"-MF"
 ,OBJ_PATH+"/IntegerFromString.dep"
} } ;

Target vdcpp179 = { "IntegerFromString.vm.dep" , OBJ_PATH+"/IntegerFromString.vm.dep" } ;
Rule rvdcpp179 = { {&dcpp179} , {&vdcpp179} , {&exedcpp179} } ;
Exe exedcpp179 = { "CC-VM-DEP IntegerFromString.cpp" , VMDEP , { OBJ_PATH+"/IntegerFromString.dep" , OBJ_PATH+"/IntegerFromString.vm.dep" , "179" } } ;

Target cpp180 = { "IntegerGCD.cpp" , "../../Applied/CCore/src/./math/IntegerGCD.cpp" } ;
Target dcpp180 = { "IntegerGCD.dep" , OBJ_PATH+"/IntegerGCD.dep" } ;
Rule rdcpp180 = { {&cpp180,&obj} , {&dcpp180} , {&execpp180} } ;
Exe execpp180 = { "CC-DEP IntegerGCD.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/IntegerGCD.o"
 ,"../../Applied/CCore/src/./math/IntegerGCD.cpp"
 ,"-MF"
 ,OBJ_PATH+"/IntegerGCD.dep"
} } ;

Target vdcpp180 = { "IntegerGCD.vm.dep" , OBJ_PATH+"/IntegerGCD.vm.dep" } ;
Rule rvdcpp180 = { {&dcpp180} , {&vdcpp180} , {&exedcpp180} } ;
Exe exedcpp180 = { "CC-VM-DEP IntegerGCD.cpp" , VMDEP , { OBJ_PATH+"/IntegerGCD.dep" , OBJ_PATH+"/IntegerGCD.vm.dep" , "180" } } ;

Target cpp181 = { "IntegerMulAlgo.cpp" , "../../Applied/CCore/src/./math/IntegerMulAlgo.cpp" } ;
Target dcpp181 = { "IntegerMulAlgo.dep" , OBJ_PATH+"/IntegerMulAlgo.dep" } ;
Rule rdcpp181 = { {&cpp181,&obj} , {&dcpp181} , {&execpp181} } ;
Exe execpp181 = { "CC-DEP IntegerMulAlgo.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/IntegerMulAlgo.o"
 ,"../../Applied/CCore/src/./math/IntegerMulAlgo.cpp"
 ,"-MF"
 ,OBJ_PATH+"/IntegerMulAlgo.dep"
} } ;

Target vdcpp181 = { "IntegerMulAlgo.vm.dep" , OBJ_PATH+"/IntegerMulAlgo.vm.dep" } ;
Rule rvdcpp181 = { {&dcpp181} , {&vdcpp181} , {&exedcpp181} } ;
Exe exedcpp181 = { "CC-VM-DEP IntegerMulAlgo.cpp" , VMDEP , { OBJ_PATH+"/IntegerMulAlgo.dep" , OBJ_PATH+"/IntegerMulAlgo.vm.dep" , "181" } } ;

Target cpp182 = { "IntegerOctetBuilder.cpp" , "../../Applied/CCore/src/./math/IntegerOctetBuilder.cpp" } ;
Target dcpp182 = { "IntegerOctetBuilder.dep" , OBJ_PATH+"/IntegerOctetBuilder.dep" } ;
Rule rdcpp182 = { {&cpp182,&obj} , {&dcpp182} , {&execpp182} } ;
Exe execpp182 = { "CC-DEP IntegerOctetBuilder.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/IntegerOctetBuilder.o"
 ,"../../Applied/CCore/src/./math/IntegerOctetBuilder.cpp"
 ,"-MF"
 ,OBJ_PATH+"/IntegerOctetBuilder.dep"
} } ;

Target vdcpp182 = { "IntegerOctetBuilder.vm.dep" , OBJ_PATH+"/IntegerOctetBuilder.vm.dep" } ;
Rule rvdcpp182 = { {&dcpp182} , {&vdcpp182} , {&exedcpp182} } ;
Exe exedcpp182 = { "CC-VM-DEP IntegerOctetBuilder.cpp" , VMDEP , { OBJ_PATH+"/IntegerOctetBuilder.dep" , OBJ_PATH+"/IntegerOctetBuilder.vm.dep" , "182" } } ;

Target cpp183 = { "IntegerSlowAlgo.cpp" , "../../Applied/CCore/src/./math/IntegerSlowAlgo.cpp" } ;
Target dcpp183 = { "IntegerSlowAlgo.dep" , OBJ_PATH+"/IntegerSlowAlgo.dep" } ;
Rule rdcpp183 = { {&cpp183,&obj} , {&dcpp183} , {&execpp183} } ;
Exe execpp183 = { "CC-DEP IntegerSlowAlgo.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/IntegerSlowAlgo.o"
 ,"../../Applied/CCore/src/./math/IntegerSlowAlgo.cpp"
 ,"-MF"
 ,OBJ_PATH+"/IntegerSlowAlgo.dep"
} } ;

Target vdcpp183 = { "IntegerSlowAlgo.vm.dep" , OBJ_PATH+"/IntegerSlowAlgo.vm.dep" } ;
Rule rvdcpp183 = { {&dcpp183} , {&vdcpp183} , {&exedcpp183} } ;
Exe exedcpp183 = { "CC-VM-DEP IntegerSlowAlgo.cpp" , VMDEP , { OBJ_PATH+"/IntegerSlowAlgo.dep" , OBJ_PATH+"/IntegerSlowAlgo.vm.dep" , "183" } } ;

Target cpp184 = { "IntelAES.cpp" , "CCore/src/./crypton/IntelAES.cpp" } ;
Target dcpp184 = { "IntelAES.dep" , OBJ_PATH+"/IntelAES.dep" } ;
Rule rdcpp184 = { {&cpp184,&obj} , {&dcpp184} , {&execpp184} } ;
Exe execpp184 = { "CC-DEP IntelAES.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/IntelAES.o"
 ,"CCore/src/./crypton/IntelAES.cpp"
 ,"-MF"
 ,OBJ_PATH+"/IntelAES.dep"
} } ;

Target vdcpp184 = { "IntelAES.vm.dep" , OBJ_PATH+"/IntelAES.vm.dep" } ;
Rule rvdcpp184 = { {&dcpp184} , {&vdcpp184} , {&exedcpp184} } ;
Exe exedcpp184 = { "CC-VM-DEP IntelAES.cpp" , VMDEP , { OBJ_PATH+"/IntelAES.dep" , OBJ_PATH+"/IntelAES.vm.dep" , "184" } } ;

Target cpp185 = { "IntelCPUID.cpp" , "CCore/src/./crypton/IntelCPUID.cpp" } ;
Target dcpp185 = { "IntelCPUID.dep" , OBJ_PATH+"/IntelCPUID.dep" } ;
Rule rdcpp185 = { {&cpp185,&obj} , {&dcpp185} , {&execpp185} } ;
Exe execpp185 = { "CC-DEP IntelCPUID.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/IntelCPUID.o"
 ,"CCore/src/./crypton/IntelCPUID.cpp"
 ,"-MF"
 ,OBJ_PATH+"/IntelCPUID.dep"
} } ;

Target vdcpp185 = { "IntelCPUID.vm.dep" , OBJ_PATH+"/IntelCPUID.vm.dep" } ;
Rule rvdcpp185 = { {&dcpp185} , {&vdcpp185} , {&exedcpp185} } ;
Exe exedcpp185 = { "CC-VM-DEP IntelCPUID.cpp" , VMDEP , { OBJ_PATH+"/IntelCPUID.dep" , OBJ_PATH+"/IntelCPUID.vm.dep" , "185" } } ;

Target cpp186 = { "IntelRandom.cpp" , "CCore/src/./crypton/IntelRandom.cpp" } ;
Target dcpp186 = { "IntelRandom.dep" , OBJ_PATH+"/IntelRandom.dep" } ;
Rule rdcpp186 = { {&cpp186,&obj} , {&dcpp186} , {&execpp186} } ;
Exe execpp186 = { "CC-DEP IntelRandom.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/IntelRandom.o"
 ,"CCore/src/./crypton/IntelRandom.cpp"
 ,"-MF"
 ,OBJ_PATH+"/IntelRandom.dep"
} } ;

Target vdcpp186 = { "IntelRandom.vm.dep" , OBJ_PATH+"/IntelRandom.vm.dep" } ;
Rule rvdcpp186 = { {&dcpp186} , {&vdcpp186} , {&exedcpp186} } ;
Exe exedcpp186 = { "CC-VM-DEP IntelRandom.cpp" , VMDEP , { OBJ_PATH+"/IntelRandom.dep" , OBJ_PATH+"/IntelRandom.vm.dep" , "186" } } ;

Target cpp187 = { "InterfaceHost.cpp" , "../../Fundamental/CCore/src/InterfaceHost.cpp" } ;
Target dcpp187 = { "InterfaceHost.dep" , OBJ_PATH+"/InterfaceHost.dep" } ;
Rule rdcpp187 = { {&cpp187,&obj} , {&dcpp187} , {&execpp187} } ;
Exe execpp187 = { "CC-DEP InterfaceHost.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/InterfaceHost.o"
 ,"../../Fundamental/CCore/src/InterfaceHost.cpp"
 ,"-MF"
 ,OBJ_PATH+"/InterfaceHost.dep"
} } ;

Target vdcpp187 = { "InterfaceHost.vm.dep" , OBJ_PATH+"/InterfaceHost.vm.dep" } ;
Rule rvdcpp187 = { {&dcpp187} , {&vdcpp187} , {&exedcpp187} } ;
Exe exedcpp187 = { "CC-VM-DEP InterfaceHost.cpp" , VMDEP , { OBJ_PATH+"/InterfaceHost.dep" , OBJ_PATH+"/InterfaceHost.vm.dep" , "187" } } ;

Target cpp188 = { "InternalDesktop.cpp" , "CCore/src/./video/InternalDesktop.cpp" } ;
Target dcpp188 = { "InternalDesktop.dep" , OBJ_PATH+"/InternalDesktop.dep" } ;
Rule rdcpp188 = { {&cpp188,&obj} , {&dcpp188} , {&execpp188} } ;
Exe execpp188 = { "CC-DEP InternalDesktop.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/InternalDesktop.o"
 ,"CCore/src/./video/InternalDesktop.cpp"
 ,"-MF"
 ,OBJ_PATH+"/InternalDesktop.dep"
} } ;

Target vdcpp188 = { "InternalDesktop.vm.dep" , OBJ_PATH+"/InternalDesktop.vm.dep" } ;
Rule rvdcpp188 = { {&dcpp188} , {&vdcpp188} , {&exedcpp188} } ;
Exe exedcpp188 = { "CC-VM-DEP InternalDesktop.cpp" , VMDEP , { OBJ_PATH+"/InternalDesktop.dep" , OBJ_PATH+"/InternalDesktop.vm.dep" , "188" } } ;

Target cpp189 = { "InternalHost.cpp" , "CCore/src/./video/InternalHost.cpp" } ;
Target dcpp189 = { "InternalHost.dep" , OBJ_PATH+"/InternalHost.dep" } ;
Rule rdcpp189 = { {&cpp189,&obj} , {&dcpp189} , {&execpp189} } ;
Exe execpp189 = { "CC-DEP InternalHost.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/InternalHost.o"
 ,"CCore/src/./video/InternalHost.cpp"
 ,"-MF"
 ,OBJ_PATH+"/InternalHost.dep"
} } ;

Target vdcpp189 = { "InternalHost.vm.dep" , OBJ_PATH+"/InternalHost.vm.dep" } ;
Rule rvdcpp189 = { {&dcpp189} , {&vdcpp189} , {&exedcpp189} } ;
Exe exedcpp189 = { "CC-VM-DEP InternalHost.cpp" , VMDEP , { OBJ_PATH+"/InternalHost.dep" , OBJ_PATH+"/InternalHost.vm.dep" , "189" } } ;

Target cpp190 = { "InternalUtils.cpp" , "CCore/src/./video/InternalUtils.cpp" } ;
Target dcpp190 = { "InternalUtils.dep" , OBJ_PATH+"/InternalUtils.dep" } ;
Rule rdcpp190 = { {&cpp190,&obj} , {&dcpp190} , {&execpp190} } ;
Exe execpp190 = { "CC-DEP InternalUtils.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/InternalUtils.o"
 ,"CCore/src/./video/InternalUtils.cpp"
 ,"-MF"
 ,OBJ_PATH+"/InternalUtils.dep"
} } ;

Target vdcpp190 = { "InternalUtils.vm.dep" , OBJ_PATH+"/InternalUtils.vm.dep" } ;
Rule rvdcpp190 = { {&dcpp190} , {&vdcpp190} , {&exedcpp190} } ;
Exe exedcpp190 = { "CC-VM-DEP InternalUtils.cpp" , VMDEP , { OBJ_PATH+"/InternalUtils.dep" , OBJ_PATH+"/InternalUtils.vm.dep" , "190" } } ;

Target cpp191 = { "IntervalTree.cpp" , "../../Applied/CCore/src/IntervalTree.cpp" } ;
Target dcpp191 = { "IntervalTree.dep" , OBJ_PATH+"/IntervalTree.dep" } ;
Rule rdcpp191 = { {&cpp191,&obj} , {&dcpp191} , {&execpp191} } ;
Exe execpp191 = { "CC-DEP IntervalTree.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/IntervalTree.o"
 ,"../../Applied/CCore/src/IntervalTree.cpp"
 ,"-MF"
 ,OBJ_PATH+"/IntervalTree.dep"
} } ;

Target vdcpp191 = { "IntervalTree.vm.dep" , OBJ_PATH+"/IntervalTree.vm.dep" } ;
Rule rvdcpp191 = { {&dcpp191} , {&vdcpp191} , {&exedcpp191} } ;
Exe exedcpp191 = { "CC-VM-DEP IntervalTree.cpp" , VMDEP , { OBJ_PATH+"/IntervalTree.dep" , OBJ_PATH+"/IntervalTree.vm.dep" , "191" } } ;

Target cpp192 = { "Job.cpp" , "../../Fundamental/CCore/src/Job.cpp" } ;
Target dcpp192 = { "Job.dep" , OBJ_PATH+"/Job.dep" } ;
Rule rdcpp192 = { {&cpp192,&obj} , {&dcpp192} , {&execpp192} } ;
Exe execpp192 = { "CC-DEP Job.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Job.o"
 ,"../../Fundamental/CCore/src/Job.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Job.dep"
} } ;

Target vdcpp192 = { "Job.vm.dep" , OBJ_PATH+"/Job.vm.dep" } ;
Rule rvdcpp192 = { {&dcpp192} , {&vdcpp192} , {&exedcpp192} } ;
Exe exedcpp192 = { "CC-VM-DEP Job.cpp" , VMDEP , { OBJ_PATH+"/Job.dep" , OBJ_PATH+"/Job.vm.dep" , "192" } } ;

Target cpp193 = { "Keyboard.cpp" , "../../Desktop/Core/CCore/src/./video/Keyboard.cpp" } ;
Target dcpp193 = { "Keyboard.dep" , OBJ_PATH+"/Keyboard.dep" } ;
Rule rdcpp193 = { {&cpp193,&obj} , {&dcpp193} , {&execpp193} } ;
Exe execpp193 = { "CC-DEP Keyboard.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Keyboard.o"
 ,"../../Desktop/Core/CCore/src/./video/Keyboard.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Keyboard.dep"
} } ;

Target vdcpp193 = { "Keyboard.vm.dep" , OBJ_PATH+"/Keyboard.vm.dep" } ;
Rule rvdcpp193 = { {&dcpp193} , {&vdcpp193} , {&exedcpp193} } ;
Exe exedcpp193 = { "CC-VM-DEP Keyboard.cpp" , VMDEP , { OBJ_PATH+"/Keyboard.dep" , OBJ_PATH+"/Keyboard.vm.dep" , "193" } } ;

Target cpp194 = { "LangDataMap.cpp" , "../../Applied/CCore/src/./lang/LangDataMap.cpp" } ;
Target dcpp194 = { "LangDataMap.dep" , OBJ_PATH+"/LangDataMap.dep" } ;
Rule rdcpp194 = { {&cpp194,&obj} , {&dcpp194} , {&execpp194} } ;
Exe execpp194 = { "CC-DEP LangDataMap.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/LangDataMap.o"
 ,"../../Applied/CCore/src/./lang/LangDataMap.cpp"
 ,"-MF"
 ,OBJ_PATH+"/LangDataMap.dep"
} } ;

Target vdcpp194 = { "LangDataMap.vm.dep" , OBJ_PATH+"/LangDataMap.vm.dep" } ;
Rule rvdcpp194 = { {&dcpp194} , {&vdcpp194} , {&exedcpp194} } ;
Exe exedcpp194 = { "CC-VM-DEP LangDataMap.cpp" , VMDEP , { OBJ_PATH+"/LangDataMap.dep" , OBJ_PATH+"/LangDataMap.vm.dep" , "194" } } ;

Target cpp195 = { "LaunchPath.cpp" , "../../HCore/CCore/src/LaunchPath.cpp" } ;
Target dcpp195 = { "LaunchPath.dep" , OBJ_PATH+"/LaunchPath.dep" } ;
Rule rdcpp195 = { {&cpp195,&obj} , {&dcpp195} , {&execpp195} } ;
Exe execpp195 = { "CC-DEP LaunchPath.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/LaunchPath.o"
 ,"../../HCore/CCore/src/LaunchPath.cpp"
 ,"-MF"
 ,OBJ_PATH+"/LaunchPath.dep"
} } ;

Target vdcpp195 = { "LaunchPath.vm.dep" , OBJ_PATH+"/LaunchPath.vm.dep" } ;
Rule rvdcpp195 = { {&dcpp195} , {&vdcpp195} , {&exedcpp195} } ;
Exe exedcpp195 = { "CC-VM-DEP LaunchPath.cpp" , VMDEP , { OBJ_PATH+"/LaunchPath.dep" , OBJ_PATH+"/LaunchPath.vm.dep" , "195" } } ;

Target cpp196 = { "Layout.cpp" , "../../Desktop/Lib/CCore/src/./video/Layout.cpp" } ;
Target dcpp196 = { "Layout.dep" , OBJ_PATH+"/Layout.dep" } ;
Rule rdcpp196 = { {&cpp196,&obj} , {&dcpp196} , {&execpp196} } ;
Exe execpp196 = { "CC-DEP Layout.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Layout.o"
 ,"../../Desktop/Lib/CCore/src/./video/Layout.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Layout.dep"
} } ;

Target vdcpp196 = { "Layout.vm.dep" , OBJ_PATH+"/Layout.vm.dep" } ;
Rule rvdcpp196 = { {&dcpp196} , {&vdcpp196} , {&exedcpp196} } ;
Exe exedcpp196 = { "CC-VM-DEP Layout.cpp" , VMDEP , { OBJ_PATH+"/Layout.dep" , OBJ_PATH+"/Layout.vm.dep" , "196" } } ;

Target cpp197 = { "LayoutCombo.cpp" , "../../Desktop/Lib/CCore/src/./video/LayoutCombo.cpp" } ;
Target dcpp197 = { "LayoutCombo.dep" , OBJ_PATH+"/LayoutCombo.dep" } ;
Rule rdcpp197 = { {&cpp197,&obj} , {&dcpp197} , {&execpp197} } ;
Exe execpp197 = { "CC-DEP LayoutCombo.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/LayoutCombo.o"
 ,"../../Desktop/Lib/CCore/src/./video/LayoutCombo.cpp"
 ,"-MF"
 ,OBJ_PATH+"/LayoutCombo.dep"
} } ;

Target vdcpp197 = { "LayoutCombo.vm.dep" , OBJ_PATH+"/LayoutCombo.vm.dep" } ;
Rule rvdcpp197 = { {&dcpp197} , {&vdcpp197} , {&exedcpp197} } ;
Exe exedcpp197 = { "CC-VM-DEP LayoutCombo.cpp" , VMDEP , { OBJ_PATH+"/LayoutCombo.dep" , OBJ_PATH+"/LayoutCombo.vm.dep" , "197" } } ;

Target cpp198 = { "Len.cpp" , "../../Simple/CCore/src/./gadget/Len.cpp" } ;
Target dcpp198 = { "Len.dep" , OBJ_PATH+"/Len.dep" } ;
Rule rdcpp198 = { {&cpp198,&obj} , {&dcpp198} , {&execpp198} } ;
Exe execpp198 = { "CC-DEP Len.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Len.o"
 ,"../../Simple/CCore/src/./gadget/Len.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Len.dep"
} } ;

Target vdcpp198 = { "Len.vm.dep" , OBJ_PATH+"/Len.vm.dep" } ;
Rule rvdcpp198 = { {&dcpp198} , {&vdcpp198} , {&exedcpp198} } ;
Exe exedcpp198 = { "CC-VM-DEP Len.cpp" , VMDEP , { OBJ_PATH+"/Len.dep" , OBJ_PATH+"/Len.vm.dep" , "198" } } ;

Target cpp199 = { "LineInput.cpp" , "../../Applied/CCore/src/LineInput.cpp" } ;
Target dcpp199 = { "LineInput.dep" , OBJ_PATH+"/LineInput.dep" } ;
Rule rdcpp199 = { {&cpp199,&obj} , {&dcpp199} , {&execpp199} } ;
Exe execpp199 = { "CC-DEP LineInput.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/LineInput.o"
 ,"../../Applied/CCore/src/LineInput.cpp"
 ,"-MF"
 ,OBJ_PATH+"/LineInput.dep"
} } ;

Target vdcpp199 = { "LineInput.vm.dep" , OBJ_PATH+"/LineInput.vm.dep" } ;
Rule rvdcpp199 = { {&dcpp199} , {&vdcpp199} , {&exedcpp199} } ;
Exe exedcpp199 = { "CC-VM-DEP LineInput.cpp" , VMDEP , { OBJ_PATH+"/LineInput.dep" , OBJ_PATH+"/LineInput.vm.dep" , "199" } } ;

Target cpp200 = { "List.cpp" , "../../Fundamental/CCore/src/List.cpp" } ;
Target dcpp200 = { "List.dep" , OBJ_PATH+"/List.dep" } ;
Rule rdcpp200 = { {&cpp200,&obj} , {&dcpp200} , {&execpp200} } ;
Exe execpp200 = { "CC-DEP List.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/List.o"
 ,"../../Fundamental/CCore/src/List.cpp"
 ,"-MF"
 ,OBJ_PATH+"/List.dep"
} } ;

Target vdcpp200 = { "List.vm.dep" , OBJ_PATH+"/List.vm.dep" } ;
Rule rvdcpp200 = { {&dcpp200} , {&vdcpp200} , {&exedcpp200} } ;
Exe exedcpp200 = { "CC-VM-DEP List.cpp" , VMDEP , { OBJ_PATH+"/List.dep" , OBJ_PATH+"/List.vm.dep" , "200" } } ;

Target cpp201 = { "ListCursor.cpp" , "../../Fundamental/CCore/src/ListCursor.cpp" } ;
Target dcpp201 = { "ListCursor.dep" , OBJ_PATH+"/ListCursor.dep" } ;
Rule rdcpp201 = { {&cpp201,&obj} , {&dcpp201} , {&execpp201} } ;
Exe execpp201 = { "CC-DEP ListCursor.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ListCursor.o"
 ,"../../Fundamental/CCore/src/ListCursor.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ListCursor.dep"
} } ;

Target vdcpp201 = { "ListCursor.vm.dep" , OBJ_PATH+"/ListCursor.vm.dep" } ;
Rule rvdcpp201 = { {&dcpp201} , {&vdcpp201} , {&exedcpp201} } ;
Exe exedcpp201 = { "CC-VM-DEP ListCursor.cpp" , VMDEP , { OBJ_PATH+"/ListCursor.dep" , OBJ_PATH+"/ListCursor.vm.dep" , "201" } } ;

Target cpp202 = { "LockObject.cpp" , "../../Simple/CCore/src/./gadget/LockObject.cpp" } ;
Target dcpp202 = { "LockObject.dep" , OBJ_PATH+"/LockObject.dep" } ;
Rule rdcpp202 = { {&cpp202,&obj} , {&dcpp202} , {&execpp202} } ;
Exe execpp202 = { "CC-DEP LockObject.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/LockObject.o"
 ,"../../Simple/CCore/src/./gadget/LockObject.cpp"
 ,"-MF"
 ,OBJ_PATH+"/LockObject.dep"
} } ;

Target vdcpp202 = { "LockObject.vm.dep" , OBJ_PATH+"/LockObject.vm.dep" } ;
Rule rvdcpp202 = { {&dcpp202} , {&vdcpp202} , {&exedcpp202} } ;
Exe exedcpp202 = { "CC-VM-DEP LockObject.cpp" , VMDEP , { OBJ_PATH+"/LockObject.dep" , OBJ_PATH+"/LockObject.vm.dep" , "202" } } ;

Target cpp203 = { "LockUse.cpp" , "../../Simple/CCore/src/./gadget/LockUse.cpp" } ;
Target dcpp203 = { "LockUse.dep" , OBJ_PATH+"/LockUse.dep" } ;
Rule rdcpp203 = { {&cpp203,&obj} , {&dcpp203} , {&execpp203} } ;
Exe execpp203 = { "CC-DEP LockUse.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/LockUse.o"
 ,"../../Simple/CCore/src/./gadget/LockUse.cpp"
 ,"-MF"
 ,OBJ_PATH+"/LockUse.dep"
} } ;

Target vdcpp203 = { "LockUse.vm.dep" , OBJ_PATH+"/LockUse.vm.dep" } ;
Rule rvdcpp203 = { {&dcpp203} , {&vdcpp203} , {&exedcpp203} } ;
Exe exedcpp203 = { "CC-VM-DEP LockUse.cpp" , VMDEP , { OBJ_PATH+"/LockUse.dep" , OBJ_PATH+"/LockUse.vm.dep" , "203" } } ;

Target cpp204 = { "Locked.cpp" , "../../Simple/CCore/src/./gadget/Locked.cpp" } ;
Target dcpp204 = { "Locked.dep" , OBJ_PATH+"/Locked.dep" } ;
Rule rdcpp204 = { {&cpp204,&obj} , {&dcpp204} , {&execpp204} } ;
Exe execpp204 = { "CC-DEP Locked.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Locked.o"
 ,"../../Simple/CCore/src/./gadget/Locked.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Locked.dep"
} } ;

Target vdcpp204 = { "Locked.vm.dep" , OBJ_PATH+"/Locked.vm.dep" } ;
Rule rvdcpp204 = { {&dcpp204} , {&vdcpp204} , {&exedcpp204} } ;
Exe exedcpp204 = { "CC-VM-DEP Locked.cpp" , VMDEP , { OBJ_PATH+"/Locked.dep" , OBJ_PATH+"/Locked.vm.dep" , "204" } } ;

Target cpp205 = { "Log.cpp" , "../../Applied/CCore/src/Log.cpp" } ;
Target dcpp205 = { "Log.dep" , OBJ_PATH+"/Log.dep" } ;
Rule rdcpp205 = { {&cpp205,&obj} , {&dcpp205} , {&execpp205} } ;
Exe execpp205 = { "CC-DEP Log.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Log.o"
 ,"../../Applied/CCore/src/Log.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Log.dep"
} } ;

Target vdcpp205 = { "Log.vm.dep" , OBJ_PATH+"/Log.vm.dep" } ;
Rule rvdcpp205 = { {&dcpp205} , {&vdcpp205} , {&exedcpp205} } ;
Exe exedcpp205 = { "CC-VM-DEP Log.cpp" , VMDEP , { OBJ_PATH+"/Log.dep" , OBJ_PATH+"/Log.vm.dep" , "205" } } ;

Target cpp206 = { "MCoordEdit.cpp" , "../../Desktop/Lib/CCore/src/./video/pref/MCoordEdit.cpp" } ;
Target dcpp206 = { "MCoordEdit.dep" , OBJ_PATH+"/MCoordEdit.dep" } ;
Rule rdcpp206 = { {&cpp206,&obj} , {&dcpp206} , {&execpp206} } ;
Exe execpp206 = { "CC-DEP MCoordEdit.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/MCoordEdit.o"
 ,"../../Desktop/Lib/CCore/src/./video/pref/MCoordEdit.cpp"
 ,"-MF"
 ,OBJ_PATH+"/MCoordEdit.dep"
} } ;

Target vdcpp206 = { "MCoordEdit.vm.dep" , OBJ_PATH+"/MCoordEdit.vm.dep" } ;
Rule rvdcpp206 = { {&dcpp206} , {&vdcpp206} , {&exedcpp206} } ;
Exe exedcpp206 = { "CC-VM-DEP MCoordEdit.cpp" , VMDEP , { OBJ_PATH+"/MCoordEdit.dep" , OBJ_PATH+"/MCoordEdit.vm.dep" , "206" } } ;

Target cpp207 = { "MD5.cpp" , "../../Applied/CCore/src/./crypton/MD5.cpp" } ;
Target dcpp207 = { "MD5.dep" , OBJ_PATH+"/MD5.dep" } ;
Rule rdcpp207 = { {&cpp207,&obj} , {&dcpp207} , {&execpp207} } ;
Exe execpp207 = { "CC-DEP MD5.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/MD5.o"
 ,"../../Applied/CCore/src/./crypton/MD5.cpp"
 ,"-MF"
 ,OBJ_PATH+"/MD5.dep"
} } ;

Target vdcpp207 = { "MD5.vm.dep" , OBJ_PATH+"/MD5.vm.dep" } ;
Rule rvdcpp207 = { {&dcpp207} , {&vdcpp207} , {&exedcpp207} } ;
Exe exedcpp207 = { "CC-VM-DEP MD5.cpp" , VMDEP , { OBJ_PATH+"/MD5.dep" , OBJ_PATH+"/MD5.vm.dep" , "207" } } ;

Target cpp208 = { "MPoint.cpp" , "../../Desktop/Draw/CCore/src/./video/MPoint.cpp" } ;
Target dcpp208 = { "MPoint.dep" , OBJ_PATH+"/MPoint.dep" } ;
Rule rdcpp208 = { {&cpp208,&obj} , {&dcpp208} , {&execpp208} } ;
Exe execpp208 = { "CC-DEP MPoint.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/MPoint.o"
 ,"../../Desktop/Draw/CCore/src/./video/MPoint.cpp"
 ,"-MF"
 ,OBJ_PATH+"/MPoint.dep"
} } ;

Target vdcpp208 = { "MPoint.vm.dep" , OBJ_PATH+"/MPoint.vm.dep" } ;
Rule rvdcpp208 = { {&dcpp208} , {&vdcpp208} , {&exedcpp208} } ;
Exe exedcpp208 = { "CC-VM-DEP MPoint.cpp" , VMDEP , { OBJ_PATH+"/MPoint.dep" , OBJ_PATH+"/MPoint.vm.dep" , "208" } } ;

Target cpp209 = { "MSec.cpp" , "../../Simple/CCore/src/./gadget/MSec.cpp" } ;
Target dcpp209 = { "MSec.dep" , OBJ_PATH+"/MSec.dep" } ;
Rule rdcpp209 = { {&cpp209,&obj} , {&dcpp209} , {&execpp209} } ;
Exe execpp209 = { "CC-DEP MSec.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/MSec.o"
 ,"../../Simple/CCore/src/./gadget/MSec.cpp"
 ,"-MF"
 ,OBJ_PATH+"/MSec.dep"
} } ;

Target vdcpp209 = { "MSec.vm.dep" , OBJ_PATH+"/MSec.vm.dep" } ;
Rule rvdcpp209 = { {&dcpp209} , {&vdcpp209} , {&exedcpp209} } ;
Exe exedcpp209 = { "CC-VM-DEP MSec.cpp" , VMDEP , { OBJ_PATH+"/MSec.dep" , OBJ_PATH+"/MSec.vm.dep" , "209" } } ;

Target cpp210 = { "MakeFileName.cpp" , "../../Fundamental/CCore/src/MakeFileName.cpp" } ;
Target dcpp210 = { "MakeFileName.dep" , OBJ_PATH+"/MakeFileName.dep" } ;
Rule rdcpp210 = { {&cpp210,&obj} , {&dcpp210} , {&execpp210} } ;
Exe execpp210 = { "CC-DEP MakeFileName.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/MakeFileName.o"
 ,"../../Fundamental/CCore/src/MakeFileName.cpp"
 ,"-MF"
 ,OBJ_PATH+"/MakeFileName.dep"
} } ;

Target vdcpp210 = { "MakeFileName.vm.dep" , OBJ_PATH+"/MakeFileName.vm.dep" } ;
Rule rvdcpp210 = { {&dcpp210} , {&vdcpp210} , {&exedcpp210} } ;
Exe exedcpp210 = { "CC-VM-DEP MakeFileName.cpp" , VMDEP , { OBJ_PATH+"/MakeFileName.dep" , OBJ_PATH+"/MakeFileName.vm.dep" , "210" } } ;

Target cpp211 = { "MakeString.cpp" , "../../Simple/CCore/src/MakeString.cpp" } ;
Target dcpp211 = { "MakeString.dep" , OBJ_PATH+"/MakeString.dep" } ;
Rule rdcpp211 = { {&cpp211,&obj} , {&dcpp211} , {&execpp211} } ;
Exe execpp211 = { "CC-DEP MakeString.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/MakeString.o"
 ,"../../Simple/CCore/src/MakeString.cpp"
 ,"-MF"
 ,OBJ_PATH+"/MakeString.dep"
} } ;

Target vdcpp211 = { "MakeString.vm.dep" , OBJ_PATH+"/MakeString.vm.dep" } ;
Rule rvdcpp211 = { {&dcpp211} , {&vdcpp211} , {&exedcpp211} } ;
Exe exedcpp211 = { "CC-VM-DEP MakeString.cpp" , VMDEP , { OBJ_PATH+"/MakeString.dep" , OBJ_PATH+"/MakeString.vm.dep" , "211" } } ;

Target cpp212 = { "MemAllocGuard.cpp" , "../../Simple/CCore/src/MemAllocGuard.cpp" } ;
Target dcpp212 = { "MemAllocGuard.dep" , OBJ_PATH+"/MemAllocGuard.dep" } ;
Rule rdcpp212 = { {&cpp212,&obj} , {&dcpp212} , {&execpp212} } ;
Exe execpp212 = { "CC-DEP MemAllocGuard.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/MemAllocGuard.o"
 ,"../../Simple/CCore/src/MemAllocGuard.cpp"
 ,"-MF"
 ,OBJ_PATH+"/MemAllocGuard.dep"
} } ;

Target vdcpp212 = { "MemAllocGuard.vm.dep" , OBJ_PATH+"/MemAllocGuard.vm.dep" } ;
Rule rvdcpp212 = { {&dcpp212} , {&vdcpp212} , {&exedcpp212} } ;
Exe exedcpp212 = { "CC-VM-DEP MemAllocGuard.cpp" , VMDEP , { OBJ_PATH+"/MemAllocGuard.dep" , OBJ_PATH+"/MemAllocGuard.vm.dep" , "212" } } ;

Target cpp213 = { "MemBase.cpp" , "../../HCore/CCore/src/MemBase.cpp" } ;
Target dcpp213 = { "MemBase.dep" , OBJ_PATH+"/MemBase.dep" } ;
Rule rdcpp213 = { {&cpp213,&obj} , {&dcpp213} , {&execpp213} } ;
Exe execpp213 = { "CC-DEP MemBase.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/MemBase.o"
 ,"../../HCore/CCore/src/MemBase.cpp"
 ,"-MF"
 ,OBJ_PATH+"/MemBase.dep"
} } ;

Target vdcpp213 = { "MemBase.vm.dep" , OBJ_PATH+"/MemBase.vm.dep" } ;
Rule rvdcpp213 = { {&dcpp213} , {&vdcpp213} , {&exedcpp213} } ;
Exe exedcpp213 = { "CC-VM-DEP MemBase.cpp" , VMDEP , { OBJ_PATH+"/MemBase.dep" , OBJ_PATH+"/MemBase.vm.dep" , "213" } } ;

Target cpp214 = { "MemBase_general.cpp" , "../../Fundamental/CCore/src/MemBase_general.cpp" } ;
Target dcpp214 = { "MemBase_general.dep" , OBJ_PATH+"/MemBase_general.dep" } ;
Rule rdcpp214 = { {&cpp214,&obj} , {&dcpp214} , {&execpp214} } ;
Exe execpp214 = { "CC-DEP MemBase_general.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/MemBase_general.o"
 ,"../../Fundamental/CCore/src/MemBase_general.cpp"
 ,"-MF"
 ,OBJ_PATH+"/MemBase_general.dep"
} } ;

Target vdcpp214 = { "MemBase_general.vm.dep" , OBJ_PATH+"/MemBase_general.vm.dep" } ;
Rule rvdcpp214 = { {&dcpp214} , {&vdcpp214} , {&exedcpp214} } ;
Exe exedcpp214 = { "CC-VM-DEP MemBase_general.cpp" , VMDEP , { OBJ_PATH+"/MemBase_general.dep" , OBJ_PATH+"/MemBase_general.vm.dep" , "214" } } ;

Target cpp215 = { "MemPageHeap.cpp" , "../../HCore/CCore/src/MemPageHeap.cpp" } ;
Target dcpp215 = { "MemPageHeap.dep" , OBJ_PATH+"/MemPageHeap.dep" } ;
Rule rdcpp215 = { {&cpp215,&obj} , {&dcpp215} , {&execpp215} } ;
Exe execpp215 = { "CC-DEP MemPageHeap.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/MemPageHeap.o"
 ,"../../HCore/CCore/src/MemPageHeap.cpp"
 ,"-MF"
 ,OBJ_PATH+"/MemPageHeap.dep"
} } ;

Target vdcpp215 = { "MemPageHeap.vm.dep" , OBJ_PATH+"/MemPageHeap.vm.dep" } ;
Rule rvdcpp215 = { {&dcpp215} , {&vdcpp215} , {&exedcpp215} } ;
Exe exedcpp215 = { "CC-VM-DEP MemPageHeap.cpp" , VMDEP , { OBJ_PATH+"/MemPageHeap.dep" , OBJ_PATH+"/MemPageHeap.vm.dep" , "215" } } ;

Target cpp216 = { "MemSpaceHeap.cpp" , "../../Fundamental/CCore/src/MemSpaceHeap.cpp" } ;
Target dcpp216 = { "MemSpaceHeap.dep" , OBJ_PATH+"/MemSpaceHeap.dep" } ;
Rule rdcpp216 = { {&cpp216,&obj} , {&dcpp216} , {&execpp216} } ;
Exe execpp216 = { "CC-DEP MemSpaceHeap.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/MemSpaceHeap.o"
 ,"../../Fundamental/CCore/src/MemSpaceHeap.cpp"
 ,"-MF"
 ,OBJ_PATH+"/MemSpaceHeap.dep"
} } ;

Target vdcpp216 = { "MemSpaceHeap.vm.dep" , OBJ_PATH+"/MemSpaceHeap.vm.dep" } ;
Rule rvdcpp216 = { {&dcpp216} , {&vdcpp216} , {&exedcpp216} } ;
Exe exedcpp216 = { "CC-VM-DEP MemSpaceHeap.cpp" , VMDEP , { OBJ_PATH+"/MemSpaceHeap.dep" , OBJ_PATH+"/MemSpaceHeap.vm.dep" , "216" } } ;

Target cpp217 = { "MemberFold.cpp" , "../../Simple/CCore/src/MemberFold.cpp" } ;
Target dcpp217 = { "MemberFold.dep" , OBJ_PATH+"/MemberFold.dep" } ;
Rule rdcpp217 = { {&cpp217,&obj} , {&dcpp217} , {&execpp217} } ;
Exe execpp217 = { "CC-DEP MemberFold.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/MemberFold.o"
 ,"../../Simple/CCore/src/MemberFold.cpp"
 ,"-MF"
 ,OBJ_PATH+"/MemberFold.dep"
} } ;

Target vdcpp217 = { "MemberFold.vm.dep" , OBJ_PATH+"/MemberFold.vm.dep" } ;
Rule rvdcpp217 = { {&dcpp217} , {&vdcpp217} , {&exedcpp217} } ;
Exe exedcpp217 = { "CC-VM-DEP MemberFold.cpp" , VMDEP , { OBJ_PATH+"/MemberFold.dep" , OBJ_PATH+"/MemberFold.vm.dep" , "217" } } ;

Target cpp218 = { "Menu.cpp" , "../../Desktop/Lib/CCore/src/./video/Menu.cpp" } ;
Target dcpp218 = { "Menu.dep" , OBJ_PATH+"/Menu.dep" } ;
Rule rdcpp218 = { {&cpp218,&obj} , {&dcpp218} , {&execpp218} } ;
Exe execpp218 = { "CC-DEP Menu.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Menu.o"
 ,"../../Desktop/Lib/CCore/src/./video/Menu.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Menu.dep"
} } ;

Target vdcpp218 = { "Menu.vm.dep" , OBJ_PATH+"/Menu.vm.dep" } ;
Rule rvdcpp218 = { {&dcpp218} , {&vdcpp218} , {&exedcpp218} } ;
Exe exedcpp218 = { "CC-VM-DEP Menu.cpp" , VMDEP , { OBJ_PATH+"/Menu.dep" , OBJ_PATH+"/Menu.vm.dep" , "218" } } ;

Target cpp219 = { "MergeSort.cpp" , "../../Fundamental/CCore/src/./sort/MergeSort.cpp" } ;
Target dcpp219 = { "MergeSort.dep" , OBJ_PATH+"/MergeSort.dep" } ;
Rule rdcpp219 = { {&cpp219,&obj} , {&dcpp219} , {&execpp219} } ;
Exe execpp219 = { "CC-DEP MergeSort.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/MergeSort.o"
 ,"../../Fundamental/CCore/src/./sort/MergeSort.cpp"
 ,"-MF"
 ,OBJ_PATH+"/MergeSort.dep"
} } ;

Target vdcpp219 = { "MergeSort.vm.dep" , OBJ_PATH+"/MergeSort.vm.dep" } ;
Rule rvdcpp219 = { {&dcpp219} , {&vdcpp219} , {&exedcpp219} } ;
Exe exedcpp219 = { "CC-VM-DEP MergeSort.cpp" , VMDEP , { OBJ_PATH+"/MergeSort.dep" , OBJ_PATH+"/MergeSort.vm.dep" , "219" } } ;

Target cpp220 = { "MersenneTwister.cpp" , "../../Fundamental/CCore/src/MersenneTwister.cpp" } ;
Target dcpp220 = { "MersenneTwister.dep" , OBJ_PATH+"/MersenneTwister.dep" } ;
Rule rdcpp220 = { {&cpp220,&obj} , {&dcpp220} , {&execpp220} } ;
Exe execpp220 = { "CC-DEP MersenneTwister.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/MersenneTwister.o"
 ,"../../Fundamental/CCore/src/MersenneTwister.cpp"
 ,"-MF"
 ,OBJ_PATH+"/MersenneTwister.dep"
} } ;

Target vdcpp220 = { "MersenneTwister.vm.dep" , OBJ_PATH+"/MersenneTwister.vm.dep" } ;
Rule rvdcpp220 = { {&dcpp220} , {&vdcpp220} , {&exedcpp220} } ;
Exe exedcpp220 = { "CC-VM-DEP MersenneTwister.cpp" , VMDEP , { OBJ_PATH+"/MersenneTwister.dep" , OBJ_PATH+"/MersenneTwister.vm.dep" , "220" } } ;

Target cpp221 = { "MessageFrame.cpp" , "../../Desktop/Lib/CCore/src/./video/MessageFrame.cpp" } ;
Target dcpp221 = { "MessageFrame.dep" , OBJ_PATH+"/MessageFrame.dep" } ;
Rule rdcpp221 = { {&cpp221,&obj} , {&dcpp221} , {&execpp221} } ;
Exe execpp221 = { "CC-DEP MessageFrame.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/MessageFrame.o"
 ,"../../Desktop/Lib/CCore/src/./video/MessageFrame.cpp"
 ,"-MF"
 ,OBJ_PATH+"/MessageFrame.dep"
} } ;

Target vdcpp221 = { "MessageFrame.vm.dep" , OBJ_PATH+"/MessageFrame.vm.dep" } ;
Rule rvdcpp221 = { {&dcpp221} , {&vdcpp221} , {&exedcpp221} } ;
Exe exedcpp221 = { "CC-VM-DEP MessageFrame.cpp" , VMDEP , { OBJ_PATH+"/MessageFrame.dep" , OBJ_PATH+"/MessageFrame.vm.dep" , "221" } } ;

Target cpp222 = { "Meta.cpp" , "../../Simple/CCore/src/./gadget/Meta.cpp" } ;
Target dcpp222 = { "Meta.dep" , OBJ_PATH+"/Meta.dep" } ;
Rule rdcpp222 = { {&cpp222,&obj} , {&dcpp222} , {&execpp222} } ;
Exe execpp222 = { "CC-DEP Meta.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Meta.o"
 ,"../../Simple/CCore/src/./gadget/Meta.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Meta.dep"
} } ;

Target vdcpp222 = { "Meta.vm.dep" , OBJ_PATH+"/Meta.vm.dep" } ;
Rule rvdcpp222 = { {&dcpp222} , {&vdcpp222} , {&exedcpp222} } ;
Exe exedcpp222 = { "CC-VM-DEP Meta.cpp" , VMDEP , { OBJ_PATH+"/Meta.dep" , OBJ_PATH+"/Meta.vm.dep" , "222" } } ;

Target cpp223 = { "MetaList.cpp" , "../../Simple/CCore/src/./gadget/MetaList.cpp" } ;
Target dcpp223 = { "MetaList.dep" , OBJ_PATH+"/MetaList.dep" } ;
Rule rdcpp223 = { {&cpp223,&obj} , {&dcpp223} , {&execpp223} } ;
Exe execpp223 = { "CC-DEP MetaList.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/MetaList.o"
 ,"../../Simple/CCore/src/./gadget/MetaList.cpp"
 ,"-MF"
 ,OBJ_PATH+"/MetaList.dep"
} } ;

Target vdcpp223 = { "MetaList.vm.dep" , OBJ_PATH+"/MetaList.vm.dep" } ;
Rule rvdcpp223 = { {&dcpp223} , {&vdcpp223} , {&exedcpp223} } ;
Exe exedcpp223 = { "CC-VM-DEP MetaList.cpp" , VMDEP , { OBJ_PATH+"/MetaList.dep" , OBJ_PATH+"/MetaList.vm.dep" , "223" } } ;

Target cpp224 = { "MinSizeType.cpp" , "../../Desktop/Lib/CCore/src/./video/MinSizeType.cpp" } ;
Target dcpp224 = { "MinSizeType.dep" , OBJ_PATH+"/MinSizeType.dep" } ;
Rule rdcpp224 = { {&cpp224,&obj} , {&dcpp224} , {&execpp224} } ;
Exe execpp224 = { "CC-DEP MinSizeType.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/MinSizeType.o"
 ,"../../Desktop/Lib/CCore/src/./video/MinSizeType.cpp"
 ,"-MF"
 ,OBJ_PATH+"/MinSizeType.dep"
} } ;

Target vdcpp224 = { "MinSizeType.vm.dep" , OBJ_PATH+"/MinSizeType.vm.dep" } ;
Rule rvdcpp224 = { {&dcpp224} , {&vdcpp224} , {&exedcpp224} } ;
Exe exedcpp224 = { "CC-VM-DEP MinSizeType.cpp" , VMDEP , { OBJ_PATH+"/MinSizeType.dep" , OBJ_PATH+"/MinSizeType.vm.dep" , "224" } } ;

Target cpp225 = { "MixColorWindow.cpp" , "../../Desktop/Lib/CCore/src/./video/pref/MixColorWindow.cpp" } ;
Target dcpp225 = { "MixColorWindow.dep" , OBJ_PATH+"/MixColorWindow.dep" } ;
Rule rdcpp225 = { {&cpp225,&obj} , {&dcpp225} , {&execpp225} } ;
Exe execpp225 = { "CC-DEP MixColorWindow.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/MixColorWindow.o"
 ,"../../Desktop/Lib/CCore/src/./video/pref/MixColorWindow.cpp"
 ,"-MF"
 ,OBJ_PATH+"/MixColorWindow.dep"
} } ;

Target vdcpp225 = { "MixColorWindow.vm.dep" , OBJ_PATH+"/MixColorWindow.vm.dep" } ;
Rule rvdcpp225 = { {&dcpp225} , {&vdcpp225} , {&exedcpp225} } ;
Exe exedcpp225 = { "CC-VM-DEP MixColorWindow.cpp" , VMDEP , { OBJ_PATH+"/MixColorWindow.dep" , OBJ_PATH+"/MixColorWindow.vm.dep" , "225" } } ;

Target cpp226 = { "ModEngine.cpp" , "../../Applied/CCore/src/./math/ModEngine.cpp" } ;
Target dcpp226 = { "ModEngine.dep" , OBJ_PATH+"/ModEngine.dep" } ;
Rule rdcpp226 = { {&cpp226,&obj} , {&dcpp226} , {&execpp226} } ;
Exe execpp226 = { "CC-DEP ModEngine.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ModEngine.o"
 ,"../../Applied/CCore/src/./math/ModEngine.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ModEngine.dep"
} } ;

Target vdcpp226 = { "ModEngine.vm.dep" , OBJ_PATH+"/ModEngine.vm.dep" } ;
Rule rvdcpp226 = { {&dcpp226} , {&vdcpp226} , {&exedcpp226} } ;
Exe exedcpp226 = { "CC-VM-DEP ModEngine.cpp" , VMDEP , { OBJ_PATH+"/ModEngine.dep" , OBJ_PATH+"/ModEngine.vm.dep" , "226" } } ;

Target cpp227 = { "Mouse.cpp" , "../../Desktop/Core/CCore/src/./video/Mouse.cpp" } ;
Target dcpp227 = { "Mouse.dep" , OBJ_PATH+"/Mouse.dep" } ;
Rule rdcpp227 = { {&cpp227,&obj} , {&dcpp227} , {&execpp227} } ;
Exe execpp227 = { "CC-DEP Mouse.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Mouse.o"
 ,"../../Desktop/Core/CCore/src/./video/Mouse.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Mouse.dep"
} } ;

Target vdcpp227 = { "Mouse.vm.dep" , OBJ_PATH+"/Mouse.vm.dep" } ;
Rule rvdcpp227 = { {&dcpp227} , {&vdcpp227} , {&exedcpp227} } ;
Exe exedcpp227 = { "CC-VM-DEP Mouse.cpp" , VMDEP , { OBJ_PATH+"/Mouse.dep" , OBJ_PATH+"/Mouse.vm.dep" , "227" } } ;

Target cpp228 = { "Move.cpp" , "../../Simple/CCore/src/Move.cpp" } ;
Target dcpp228 = { "Move.dep" , OBJ_PATH+"/Move.dep" } ;
Rule rdcpp228 = { {&cpp228,&obj} , {&dcpp228} , {&execpp228} } ;
Exe execpp228 = { "CC-DEP Move.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Move.o"
 ,"../../Simple/CCore/src/Move.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Move.dep"
} } ;

Target vdcpp228 = { "Move.vm.dep" , OBJ_PATH+"/Move.vm.dep" } ;
Rule rvdcpp228 = { {&dcpp228} , {&vdcpp228} , {&exedcpp228} } ;
Exe exedcpp228 = { "CC-VM-DEP Move.cpp" , VMDEP , { OBJ_PATH+"/Move.dep" , OBJ_PATH+"/Move.vm.dep" , "228" } } ;

Target cpp229 = { "MultiEvent.cpp" , "../../HCore/CCore/src/./task/MultiEvent.cpp" } ;
Target dcpp229 = { "MultiEvent.dep" , OBJ_PATH+"/MultiEvent.dep" } ;
Rule rdcpp229 = { {&cpp229,&obj} , {&dcpp229} , {&execpp229} } ;
Exe execpp229 = { "CC-DEP MultiEvent.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/MultiEvent.o"
 ,"../../HCore/CCore/src/./task/MultiEvent.cpp"
 ,"-MF"
 ,OBJ_PATH+"/MultiEvent.dep"
} } ;

Target vdcpp229 = { "MultiEvent.vm.dep" , OBJ_PATH+"/MultiEvent.vm.dep" } ;
Rule rvdcpp229 = { {&dcpp229} , {&vdcpp229} , {&exedcpp229} } ;
Exe exedcpp229 = { "CC-VM-DEP MultiEvent.cpp" , VMDEP , { OBJ_PATH+"/MultiEvent.dep" , OBJ_PATH+"/MultiEvent.vm.dep" , "229" } } ;

Target cpp230 = { "MultiSem.cpp" , "../../HCore/CCore/src/./task/MultiSem.cpp" } ;
Target dcpp230 = { "MultiSem.dep" , OBJ_PATH+"/MultiSem.dep" } ;
Rule rdcpp230 = { {&cpp230,&obj} , {&dcpp230} , {&execpp230} } ;
Exe execpp230 = { "CC-DEP MultiSem.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/MultiSem.o"
 ,"../../HCore/CCore/src/./task/MultiSem.cpp"
 ,"-MF"
 ,OBJ_PATH+"/MultiSem.dep"
} } ;

Target vdcpp230 = { "MultiSem.vm.dep" , OBJ_PATH+"/MultiSem.vm.dep" } ;
Rule rvdcpp230 = { {&dcpp230} , {&vdcpp230} , {&exedcpp230} } ;
Exe exedcpp230 = { "CC-VM-DEP MultiSem.cpp" , VMDEP , { OBJ_PATH+"/MultiSem.dep" , OBJ_PATH+"/MultiSem.vm.dep" , "230" } } ;

Target cpp231 = { "MultiSignal.cpp" , "../../Fundamental/CCore/src/MultiSignal.cpp" } ;
Target dcpp231 = { "MultiSignal.dep" , OBJ_PATH+"/MultiSignal.dep" } ;
Rule rdcpp231 = { {&cpp231,&obj} , {&dcpp231} , {&execpp231} } ;
Exe execpp231 = { "CC-DEP MultiSignal.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/MultiSignal.o"
 ,"../../Fundamental/CCore/src/MultiSignal.cpp"
 ,"-MF"
 ,OBJ_PATH+"/MultiSignal.dep"
} } ;

Target vdcpp231 = { "MultiSignal.vm.dep" , OBJ_PATH+"/MultiSignal.vm.dep" } ;
Rule rvdcpp231 = { {&dcpp231} , {&vdcpp231} , {&exedcpp231} } ;
Exe exedcpp231 = { "CC-VM-DEP MultiSignal.cpp" , VMDEP , { OBJ_PATH+"/MultiSignal.dep" , OBJ_PATH+"/MultiSignal.vm.dep" , "231" } } ;

Target cpp232 = { "Mutex.cpp" , "../../HCore/CCore/src/./task/Mutex.cpp" } ;
Target dcpp232 = { "Mutex.dep" , OBJ_PATH+"/Mutex.dep" } ;
Rule rdcpp232 = { {&cpp232,&obj} , {&dcpp232} , {&execpp232} } ;
Exe execpp232 = { "CC-DEP Mutex.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Mutex.o"
 ,"../../HCore/CCore/src/./task/Mutex.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Mutex.dep"
} } ;

Target vdcpp232 = { "Mutex.vm.dep" , OBJ_PATH+"/Mutex.vm.dep" } ;
Rule rvdcpp232 = { {&dcpp232} , {&vdcpp232} , {&exedcpp232} } ;
Exe exedcpp232 = { "CC-VM-DEP Mutex.cpp" , VMDEP , { OBJ_PATH+"/Mutex.dep" , OBJ_PATH+"/Mutex.vm.dep" , "232" } } ;

Target cpp233 = { "MutexSpinCount.cpp" , "../../HCore/CCore/src/./task/MutexSpinCount.cpp" } ;
Target dcpp233 = { "MutexSpinCount.dep" , OBJ_PATH+"/MutexSpinCount.dep" } ;
Rule rdcpp233 = { {&cpp233,&obj} , {&dcpp233} , {&execpp233} } ;
Exe execpp233 = { "CC-DEP MutexSpinCount.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/MutexSpinCount.o"
 ,"../../HCore/CCore/src/./task/MutexSpinCount.cpp"
 ,"-MF"
 ,OBJ_PATH+"/MutexSpinCount.dep"
} } ;

Target vdcpp233 = { "MutexSpinCount.vm.dep" , OBJ_PATH+"/MutexSpinCount.vm.dep" } ;
Rule rvdcpp233 = { {&dcpp233} , {&vdcpp233} , {&exedcpp233} } ;
Exe exedcpp233 = { "CC-VM-DEP MutexSpinCount.cpp" , VMDEP , { OBJ_PATH+"/MutexSpinCount.dep" , OBJ_PATH+"/MutexSpinCount.vm.dep" , "233" } } ;

Target cpp234 = { "NanoIPDevice.cpp" , "../../Applied/CCore/src/./net/NanoIPDevice.cpp" } ;
Target dcpp234 = { "NanoIPDevice.dep" , OBJ_PATH+"/NanoIPDevice.dep" } ;
Rule rdcpp234 = { {&cpp234,&obj} , {&dcpp234} , {&execpp234} } ;
Exe execpp234 = { "CC-DEP NanoIPDevice.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/NanoIPDevice.o"
 ,"../../Applied/CCore/src/./net/NanoIPDevice.cpp"
 ,"-MF"
 ,OBJ_PATH+"/NanoIPDevice.dep"
} } ;

Target vdcpp234 = { "NanoIPDevice.vm.dep" , OBJ_PATH+"/NanoIPDevice.vm.dep" } ;
Rule rvdcpp234 = { {&dcpp234} , {&vdcpp234} , {&exedcpp234} } ;
Exe exedcpp234 = { "CC-VM-DEP NanoIPDevice.cpp" , VMDEP , { OBJ_PATH+"/NanoIPDevice.dep" , OBJ_PATH+"/NanoIPDevice.vm.dep" , "234" } } ;

Target cpp235 = { "NanoPacket.cpp" , "../../Applied/CCore/src/NanoPacket.cpp" } ;
Target dcpp235 = { "NanoPacket.dep" , OBJ_PATH+"/NanoPacket.dep" } ;
Rule rdcpp235 = { {&cpp235,&obj} , {&dcpp235} , {&execpp235} } ;
Exe execpp235 = { "CC-DEP NanoPacket.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/NanoPacket.o"
 ,"../../Applied/CCore/src/NanoPacket.cpp"
 ,"-MF"
 ,OBJ_PATH+"/NanoPacket.dep"
} } ;

Target vdcpp235 = { "NanoPacket.vm.dep" , OBJ_PATH+"/NanoPacket.vm.dep" } ;
Rule rvdcpp235 = { {&dcpp235} , {&vdcpp235} , {&exedcpp235} } ;
Exe exedcpp235 = { "CC-VM-DEP NanoPacket.cpp" , VMDEP , { OBJ_PATH+"/NanoPacket.dep" , OBJ_PATH+"/NanoPacket.vm.dep" , "235" } } ;

Target cpp236 = { "NegBool.cpp" , "../../Simple/CCore/src/./gadget/NegBool.cpp" } ;
Target dcpp236 = { "NegBool.dep" , OBJ_PATH+"/NegBool.dep" } ;
Rule rdcpp236 = { {&cpp236,&obj} , {&dcpp236} , {&execpp236} } ;
Exe execpp236 = { "CC-DEP NegBool.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/NegBool.o"
 ,"../../Simple/CCore/src/./gadget/NegBool.cpp"
 ,"-MF"
 ,OBJ_PATH+"/NegBool.dep"
} } ;

Target vdcpp236 = { "NegBool.vm.dep" , OBJ_PATH+"/NegBool.vm.dep" } ;
Rule rvdcpp236 = { {&dcpp236} , {&vdcpp236} , {&exedcpp236} } ;
Exe exedcpp236 = { "CC-VM-DEP NegBool.cpp" , VMDEP , { OBJ_PATH+"/NegBool.dep" , OBJ_PATH+"/NegBool.vm.dep" , "236" } } ;

Target cpp237 = { "NetBase.cpp" , "../../Applied/CCore/src/./net/NetBase.cpp" } ;
Target dcpp237 = { "NetBase.dep" , OBJ_PATH+"/NetBase.dep" } ;
Rule rdcpp237 = { {&cpp237,&obj} , {&dcpp237} , {&execpp237} } ;
Exe execpp237 = { "CC-DEP NetBase.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/NetBase.o"
 ,"../../Applied/CCore/src/./net/NetBase.cpp"
 ,"-MF"
 ,OBJ_PATH+"/NetBase.dep"
} } ;

Target vdcpp237 = { "NetBase.vm.dep" , OBJ_PATH+"/NetBase.vm.dep" } ;
Rule rvdcpp237 = { {&dcpp237} , {&vdcpp237} , {&exedcpp237} } ;
Exe exedcpp237 = { "CC-VM-DEP NetBase.cpp" , VMDEP , { OBJ_PATH+"/NetBase.dep" , OBJ_PATH+"/NetBase.vm.dep" , "237" } } ;

Target cpp238 = { "NetFork.cpp" , "../../Applied/CCore/src/./net/NetFork.cpp" } ;
Target dcpp238 = { "NetFork.dep" , OBJ_PATH+"/NetFork.dep" } ;
Rule rdcpp238 = { {&cpp238,&obj} , {&dcpp238} , {&execpp238} } ;
Exe execpp238 = { "CC-DEP NetFork.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/NetFork.o"
 ,"../../Applied/CCore/src/./net/NetFork.cpp"
 ,"-MF"
 ,OBJ_PATH+"/NetFork.dep"
} } ;

Target vdcpp238 = { "NetFork.vm.dep" , OBJ_PATH+"/NetFork.vm.dep" } ;
Rule rvdcpp238 = { {&dcpp238} , {&vdcpp238} , {&exedcpp238} } ;
Exe exedcpp238 = { "CC-VM-DEP NetFork.cpp" , VMDEP , { OBJ_PATH+"/NetFork.dep" , OBJ_PATH+"/NetFork.vm.dep" , "238" } } ;

Target cpp239 = { "NewDelete.cpp" , "../../Simple/CCore/src/NewDelete.cpp" } ;
Target dcpp239 = { "NewDelete.dep" , OBJ_PATH+"/NewDelete.dep" } ;
Rule rdcpp239 = { {&cpp239,&obj} , {&dcpp239} , {&execpp239} } ;
Exe execpp239 = { "CC-DEP NewDelete.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/NewDelete.o"
 ,"../../Simple/CCore/src/NewDelete.cpp"
 ,"-MF"
 ,OBJ_PATH+"/NewDelete.dep"
} } ;

Target vdcpp239 = { "NewDelete.vm.dep" , OBJ_PATH+"/NewDelete.vm.dep" } ;
Rule rvdcpp239 = { {&dcpp239} , {&vdcpp239} , {&exedcpp239} } ;
Exe exedcpp239 = { "CC-VM-DEP NewDelete.cpp" , VMDEP , { OBJ_PATH+"/NewDelete.dep" , OBJ_PATH+"/NewDelete.vm.dep" , "239" } } ;

Target cpp240 = { "NoCopy.cpp" , "../../Simple/CCore/src/./gadget/NoCopy.cpp" } ;
Target dcpp240 = { "NoCopy.dep" , OBJ_PATH+"/NoCopy.dep" } ;
Rule rdcpp240 = { {&cpp240,&obj} , {&dcpp240} , {&execpp240} } ;
Exe execpp240 = { "CC-DEP NoCopy.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/NoCopy.o"
 ,"../../Simple/CCore/src/./gadget/NoCopy.cpp"
 ,"-MF"
 ,OBJ_PATH+"/NoCopy.dep"
} } ;

Target vdcpp240 = { "NoCopy.vm.dep" , OBJ_PATH+"/NoCopy.vm.dep" } ;
Rule rvdcpp240 = { {&dcpp240} , {&vdcpp240} , {&exedcpp240} } ;
Exe exedcpp240 = { "CC-VM-DEP NoCopy.cpp" , VMDEP , { OBJ_PATH+"/NoCopy.dep" , OBJ_PATH+"/NoCopy.vm.dep" , "240" } } ;

Target cpp241 = { "NoMutex.cpp" , "../../Applied/CCore/src/./task/NoMutex.cpp" } ;
Target dcpp241 = { "NoMutex.dep" , OBJ_PATH+"/NoMutex.dep" } ;
Rule rdcpp241 = { {&cpp241,&obj} , {&dcpp241} , {&execpp241} } ;
Exe execpp241 = { "CC-DEP NoMutex.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/NoMutex.o"
 ,"../../Applied/CCore/src/./task/NoMutex.cpp"
 ,"-MF"
 ,OBJ_PATH+"/NoMutex.dep"
} } ;

Target vdcpp241 = { "NoMutex.vm.dep" , OBJ_PATH+"/NoMutex.vm.dep" } ;
Rule rvdcpp241 = { {&dcpp241} , {&vdcpp241} , {&exedcpp241} } ;
Exe exedcpp241 = { "CC-VM-DEP NoMutex.cpp" , VMDEP , { OBJ_PATH+"/NoMutex.dep" , OBJ_PATH+"/NoMutex.vm.dep" , "241" } } ;

Target cpp242 = { "NoPrimeTest.cpp" , "../../Applied/CCore/src/./math/NoPrimeTest.cpp" } ;
Target dcpp242 = { "NoPrimeTest.dep" , OBJ_PATH+"/NoPrimeTest.dep" } ;
Rule rdcpp242 = { {&cpp242,&obj} , {&dcpp242} , {&execpp242} } ;
Exe execpp242 = { "CC-DEP NoPrimeTest.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/NoPrimeTest.o"
 ,"../../Applied/CCore/src/./math/NoPrimeTest.cpp"
 ,"-MF"
 ,OBJ_PATH+"/NoPrimeTest.dep"
} } ;

Target vdcpp242 = { "NoPrimeTest.vm.dep" , OBJ_PATH+"/NoPrimeTest.vm.dep" } ;
Rule rvdcpp242 = { {&dcpp242} , {&vdcpp242} , {&exedcpp242} } ;
Exe exedcpp242 = { "CC-VM-DEP NoPrimeTest.cpp" , VMDEP , { OBJ_PATH+"/NoPrimeTest.dep" , OBJ_PATH+"/NoPrimeTest.vm.dep" , "242" } } ;

Target cpp243 = { "NoThrowFlags.cpp" , "../../Simple/CCore/src/./gadget/NoThrowFlags.cpp" } ;
Target dcpp243 = { "NoThrowFlags.dep" , OBJ_PATH+"/NoThrowFlags.dep" } ;
Rule rdcpp243 = { {&cpp243,&obj} , {&dcpp243} , {&execpp243} } ;
Exe execpp243 = { "CC-DEP NoThrowFlags.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/NoThrowFlags.o"
 ,"../../Simple/CCore/src/./gadget/NoThrowFlags.cpp"
 ,"-MF"
 ,OBJ_PATH+"/NoThrowFlags.dep"
} } ;

Target vdcpp243 = { "NoThrowFlags.vm.dep" , OBJ_PATH+"/NoThrowFlags.vm.dep" } ;
Rule rvdcpp243 = { {&dcpp243} , {&vdcpp243} , {&exedcpp243} } ;
Exe exedcpp243 = { "CC-VM-DEP NoThrowFlags.cpp" , VMDEP , { OBJ_PATH+"/NoThrowFlags.dep" , OBJ_PATH+"/NoThrowFlags.vm.dep" , "243" } } ;

Target cpp244 = { "NodeAllocator.cpp" , "../../Fundamental/CCore/src/NodeAllocator.cpp" } ;
Target dcpp244 = { "NodeAllocator.dep" , OBJ_PATH+"/NodeAllocator.dep" } ;
Rule rdcpp244 = { {&cpp244,&obj} , {&dcpp244} , {&execpp244} } ;
Exe execpp244 = { "CC-DEP NodeAllocator.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/NodeAllocator.o"
 ,"../../Fundamental/CCore/src/NodeAllocator.cpp"
 ,"-MF"
 ,OBJ_PATH+"/NodeAllocator.dep"
} } ;

Target vdcpp244 = { "NodeAllocator.vm.dep" , OBJ_PATH+"/NodeAllocator.vm.dep" } ;
Rule rvdcpp244 = { {&dcpp244} , {&vdcpp244} , {&exedcpp244} } ;
Exe exedcpp244 = { "CC-VM-DEP NodeAllocator.cpp" , VMDEP , { OBJ_PATH+"/NodeAllocator.dep" , OBJ_PATH+"/NodeAllocator.vm.dep" , "244" } } ;

Target cpp245 = { "Nothing.cpp" , "../../Simple/CCore/src/./gadget/Nothing.cpp" } ;
Target dcpp245 = { "Nothing.dep" , OBJ_PATH+"/Nothing.dep" } ;
Rule rdcpp245 = { {&cpp245,&obj} , {&dcpp245} , {&execpp245} } ;
Exe execpp245 = { "CC-DEP Nothing.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Nothing.o"
 ,"../../Simple/CCore/src/./gadget/Nothing.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Nothing.dep"
} } ;

Target vdcpp245 = { "Nothing.vm.dep" , OBJ_PATH+"/Nothing.vm.dep" } ;
Rule rvdcpp245 = { {&dcpp245} , {&vdcpp245} , {&exedcpp245} } ;
Exe exedcpp245 = { "CC-VM-DEP Nothing.cpp" , VMDEP , { OBJ_PATH+"/Nothing.dep" , OBJ_PATH+"/Nothing.vm.dep" , "245" } } ;

Target cpp246 = { "NullMovePtr.cpp" , "../../Simple/CCore/src/./gadget/NullMovePtr.cpp" } ;
Target dcpp246 = { "NullMovePtr.dep" , OBJ_PATH+"/NullMovePtr.dep" } ;
Rule rdcpp246 = { {&cpp246,&obj} , {&dcpp246} , {&execpp246} } ;
Exe execpp246 = { "CC-DEP NullMovePtr.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/NullMovePtr.o"
 ,"../../Simple/CCore/src/./gadget/NullMovePtr.cpp"
 ,"-MF"
 ,OBJ_PATH+"/NullMovePtr.dep"
} } ;

Target vdcpp246 = { "NullMovePtr.vm.dep" , OBJ_PATH+"/NullMovePtr.vm.dep" } ;
Rule rvdcpp246 = { {&dcpp246} , {&vdcpp246} , {&exedcpp246} } ;
Exe exedcpp246 = { "CC-VM-DEP NullMovePtr.cpp" , VMDEP , { OBJ_PATH+"/NullMovePtr.dep" , OBJ_PATH+"/NullMovePtr.vm.dep" , "246" } } ;

Target cpp247 = { "ObjHost.cpp" , "../../Fundamental/CCore/src/ObjHost.cpp" } ;
Target dcpp247 = { "ObjHost.dep" , OBJ_PATH+"/ObjHost.dep" } ;
Rule rdcpp247 = { {&cpp247,&obj} , {&dcpp247} , {&execpp247} } ;
Exe execpp247 = { "CC-DEP ObjHost.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ObjHost.o"
 ,"../../Fundamental/CCore/src/ObjHost.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ObjHost.dep"
} } ;

Target vdcpp247 = { "ObjHost.vm.dep" , OBJ_PATH+"/ObjHost.vm.dep" } ;
Rule rvdcpp247 = { {&dcpp247} , {&vdcpp247} , {&exedcpp247} } ;
Exe exedcpp247 = { "CC-VM-DEP ObjHost.cpp" , VMDEP , { OBJ_PATH+"/ObjHost.dep" , OBJ_PATH+"/ObjHost.vm.dep" , "247" } } ;

Target cpp248 = { "ObjectDomain.cpp" , "../../Fundamental/CCore/src/ObjectDomain.cpp" } ;
Target dcpp248 = { "ObjectDomain.dep" , OBJ_PATH+"/ObjectDomain.dep" } ;
Rule rdcpp248 = { {&cpp248,&obj} , {&dcpp248} , {&execpp248} } ;
Exe execpp248 = { "CC-DEP ObjectDomain.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ObjectDomain.o"
 ,"../../Fundamental/CCore/src/ObjectDomain.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ObjectDomain.dep"
} } ;

Target vdcpp248 = { "ObjectDomain.vm.dep" , OBJ_PATH+"/ObjectDomain.vm.dep" } ;
Rule rvdcpp248 = { {&dcpp248} , {&vdcpp248} , {&exedcpp248} } ;
Exe exedcpp248 = { "CC-VM-DEP ObjectDomain.cpp" , VMDEP , { OBJ_PATH+"/ObjectDomain.dep" , OBJ_PATH+"/ObjectDomain.vm.dep" , "248" } } ;

Target cpp249 = { "OpAddHelper.cpp" , "../../Simple/CCore/src/./gadget/OpAddHelper.cpp" } ;
Target dcpp249 = { "OpAddHelper.dep" , OBJ_PATH+"/OpAddHelper.dep" } ;
Rule rdcpp249 = { {&cpp249,&obj} , {&dcpp249} , {&execpp249} } ;
Exe execpp249 = { "CC-DEP OpAddHelper.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/OpAddHelper.o"
 ,"../../Simple/CCore/src/./gadget/OpAddHelper.cpp"
 ,"-MF"
 ,OBJ_PATH+"/OpAddHelper.dep"
} } ;

Target vdcpp249 = { "OpAddHelper.vm.dep" , OBJ_PATH+"/OpAddHelper.vm.dep" } ;
Rule rvdcpp249 = { {&dcpp249} , {&vdcpp249} , {&exedcpp249} } ;
Exe exedcpp249 = { "CC-VM-DEP OpAddHelper.cpp" , VMDEP , { OBJ_PATH+"/OpAddHelper.dep" , OBJ_PATH+"/OpAddHelper.vm.dep" , "249" } } ;

Target cpp250 = { "OptMember.cpp" , "../../Simple/CCore/src/OptMember.cpp" } ;
Target dcpp250 = { "OptMember.dep" , OBJ_PATH+"/OptMember.dep" } ;
Rule rdcpp250 = { {&cpp250,&obj} , {&dcpp250} , {&execpp250} } ;
Exe execpp250 = { "CC-DEP OptMember.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/OptMember.o"
 ,"../../Simple/CCore/src/OptMember.cpp"
 ,"-MF"
 ,OBJ_PATH+"/OptMember.dep"
} } ;

Target vdcpp250 = { "OptMember.vm.dep" , OBJ_PATH+"/OptMember.vm.dep" } ;
Rule rvdcpp250 = { {&dcpp250} , {&vdcpp250} , {&exedcpp250} } ;
Exe exedcpp250 = { "CC-VM-DEP OptMember.cpp" , VMDEP , { OBJ_PATH+"/OptMember.dep" , OBJ_PATH+"/OptMember.vm.dep" , "250" } } ;

Target cpp251 = { "Optional.cpp" , "../../Fundamental/CCore/src/Optional.cpp" } ;
Target dcpp251 = { "Optional.dep" , OBJ_PATH+"/Optional.dep" } ;
Rule rdcpp251 = { {&cpp251,&obj} , {&dcpp251} , {&execpp251} } ;
Exe execpp251 = { "CC-DEP Optional.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Optional.o"
 ,"../../Fundamental/CCore/src/Optional.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Optional.dep"
} } ;

Target vdcpp251 = { "Optional.vm.dep" , OBJ_PATH+"/Optional.vm.dep" } ;
Rule rvdcpp251 = { {&dcpp251} , {&vdcpp251} , {&exedcpp251} } ;
Exe exedcpp251 = { "CC-VM-DEP Optional.cpp" , VMDEP , { OBJ_PATH+"/Optional.dep" , OBJ_PATH+"/Optional.vm.dep" , "251" } } ;

Target cpp252 = { "OwnPtr.cpp" , "../../Simple/CCore/src/OwnPtr.cpp" } ;
Target dcpp252 = { "OwnPtr.dep" , OBJ_PATH+"/OwnPtr.dep" } ;
Rule rdcpp252 = { {&cpp252,&obj} , {&dcpp252} , {&execpp252} } ;
Exe execpp252 = { "CC-DEP OwnPtr.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/OwnPtr.o"
 ,"../../Simple/CCore/src/OwnPtr.cpp"
 ,"-MF"
 ,OBJ_PATH+"/OwnPtr.dep"
} } ;

Target vdcpp252 = { "OwnPtr.vm.dep" , OBJ_PATH+"/OwnPtr.vm.dep" } ;
Rule rvdcpp252 = { {&dcpp252} , {&vdcpp252} , {&exedcpp252} } ;
Exe exedcpp252 = { "CC-VM-DEP OwnPtr.cpp" , VMDEP , { OBJ_PATH+"/OwnPtr.dep" , OBJ_PATH+"/OwnPtr.vm.dep" , "252" } } ;

Target cpp253 = { "PKE.cpp" , "../../Applied/CCore/src/./net/PKE.cpp" } ;
Target dcpp253 = { "PKE.dep" , OBJ_PATH+"/PKE.dep" } ;
Rule rdcpp253 = { {&cpp253,&obj} , {&dcpp253} , {&execpp253} } ;
Exe execpp253 = { "CC-DEP PKE.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PKE.o"
 ,"../../Applied/CCore/src/./net/PKE.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PKE.dep"
} } ;

Target vdcpp253 = { "PKE.vm.dep" , OBJ_PATH+"/PKE.vm.dep" } ;
Rule rvdcpp253 = { {&dcpp253} , {&vdcpp253} , {&exedcpp253} } ;
Exe exedcpp253 = { "CC-VM-DEP PKE.cpp" , VMDEP , { OBJ_PATH+"/PKE.dep" , OBJ_PATH+"/PKE.vm.dep" , "253" } } ;

Target cpp254 = { "PSec.cpp" , "../../Applied/CCore/src/./net/PSec.cpp" } ;
Target dcpp254 = { "PSec.dep" , OBJ_PATH+"/PSec.dep" } ;
Rule rdcpp254 = { {&cpp254,&obj} , {&dcpp254} , {&execpp254} } ;
Exe execpp254 = { "CC-DEP PSec.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PSec.o"
 ,"../../Applied/CCore/src/./net/PSec.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PSec.dep"
} } ;

Target vdcpp254 = { "PSec.vm.dep" , OBJ_PATH+"/PSec.vm.dep" } ;
Rule rvdcpp254 = { {&dcpp254} , {&vdcpp254} , {&exedcpp254} } ;
Exe exedcpp254 = { "CC-VM-DEP PSec.cpp" , VMDEP , { OBJ_PATH+"/PSec.dep" , OBJ_PATH+"/PSec.vm.dep" , "254" } } ;

Target cpp255 = { "PSecCore.cpp" , "../../Applied/CCore/src/./net/PSecCore.cpp" } ;
Target dcpp255 = { "PSecCore.dep" , OBJ_PATH+"/PSecCore.dep" } ;
Rule rdcpp255 = { {&cpp255,&obj} , {&dcpp255} , {&execpp255} } ;
Exe execpp255 = { "CC-DEP PSecCore.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PSecCore.o"
 ,"../../Applied/CCore/src/./net/PSecCore.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PSecCore.dep"
} } ;

Target vdcpp255 = { "PSecCore.vm.dep" , OBJ_PATH+"/PSecCore.vm.dep" } ;
Rule rvdcpp255 = { {&dcpp255} , {&vdcpp255} , {&exedcpp255} } ;
Exe exedcpp255 = { "CC-VM-DEP PSecCore.cpp" , VMDEP , { OBJ_PATH+"/PSecCore.dep" , OBJ_PATH+"/PSecCore.vm.dep" , "255" } } ;

Target cpp256 = { "PSecKey.cpp" , "../../Applied/CCore/src/./net/PSecKey.cpp" } ;
Target dcpp256 = { "PSecKey.dep" , OBJ_PATH+"/PSecKey.dep" } ;
Rule rdcpp256 = { {&cpp256,&obj} , {&dcpp256} , {&execpp256} } ;
Exe execpp256 = { "CC-DEP PSecKey.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PSecKey.o"
 ,"../../Applied/CCore/src/./net/PSecKey.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PSecKey.dep"
} } ;

Target vdcpp256 = { "PSecKey.vm.dep" , OBJ_PATH+"/PSecKey.vm.dep" } ;
Rule rvdcpp256 = { {&dcpp256} , {&vdcpp256} , {&exedcpp256} } ;
Exe exedcpp256 = { "CC-VM-DEP PSecKey.cpp" , VMDEP , { OBJ_PATH+"/PSecKey.dep" , OBJ_PATH+"/PSecKey.vm.dep" , "256" } } ;

Target cpp257 = { "PTPBase.cpp" , "../../Applied/CCore/src/./net/PTPBase.cpp" } ;
Target dcpp257 = { "PTPBase.dep" , OBJ_PATH+"/PTPBase.dep" } ;
Rule rdcpp257 = { {&cpp257,&obj} , {&dcpp257} , {&execpp257} } ;
Exe execpp257 = { "CC-DEP PTPBase.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PTPBase.o"
 ,"../../Applied/CCore/src/./net/PTPBase.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PTPBase.dep"
} } ;

Target vdcpp257 = { "PTPBase.vm.dep" , OBJ_PATH+"/PTPBase.vm.dep" } ;
Rule rvdcpp257 = { {&dcpp257} , {&vdcpp257} , {&exedcpp257} } ;
Exe exedcpp257 = { "CC-VM-DEP PTPBase.cpp" , VMDEP , { OBJ_PATH+"/PTPBase.dep" , OBJ_PATH+"/PTPBase.vm.dep" , "257" } } ;

Target cpp258 = { "PTPBoot.cpp" , "../../Applied/CCore/src/./net/PTPBoot.cpp" } ;
Target dcpp258 = { "PTPBoot.dep" , OBJ_PATH+"/PTPBoot.dep" } ;
Rule rdcpp258 = { {&cpp258,&obj} , {&dcpp258} , {&execpp258} } ;
Exe execpp258 = { "CC-DEP PTPBoot.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PTPBoot.o"
 ,"../../Applied/CCore/src/./net/PTPBoot.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PTPBoot.dep"
} } ;

Target vdcpp258 = { "PTPBoot.vm.dep" , OBJ_PATH+"/PTPBoot.vm.dep" } ;
Rule rvdcpp258 = { {&dcpp258} , {&vdcpp258} , {&exedcpp258} } ;
Exe exedcpp258 = { "CC-VM-DEP PTPBoot.cpp" , VMDEP , { OBJ_PATH+"/PTPBoot.dep" , OBJ_PATH+"/PTPBoot.vm.dep" , "258" } } ;

Target cpp259 = { "PTPBootBase.cpp" , "../../Applied/CCore/src/./net/PTPBootBase.cpp" } ;
Target dcpp259 = { "PTPBootBase.dep" , OBJ_PATH+"/PTPBootBase.dep" } ;
Rule rdcpp259 = { {&cpp259,&obj} , {&dcpp259} , {&execpp259} } ;
Exe execpp259 = { "CC-DEP PTPBootBase.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PTPBootBase.o"
 ,"../../Applied/CCore/src/./net/PTPBootBase.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PTPBootBase.dep"
} } ;

Target vdcpp259 = { "PTPBootBase.vm.dep" , OBJ_PATH+"/PTPBootBase.vm.dep" } ;
Rule rvdcpp259 = { {&dcpp259} , {&vdcpp259} , {&exedcpp259} } ;
Exe exedcpp259 = { "CC-VM-DEP PTPBootBase.cpp" , VMDEP , { OBJ_PATH+"/PTPBootBase.dep" , OBJ_PATH+"/PTPBootBase.vm.dep" , "259" } } ;

Target cpp260 = { "PTPClientDevice.cpp" , "../../Applied/CCore/src/./net/PTPClientDevice.cpp" } ;
Target dcpp260 = { "PTPClientDevice.dep" , OBJ_PATH+"/PTPClientDevice.dep" } ;
Rule rdcpp260 = { {&cpp260,&obj} , {&dcpp260} , {&execpp260} } ;
Exe execpp260 = { "CC-DEP PTPClientDevice.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PTPClientDevice.o"
 ,"../../Applied/CCore/src/./net/PTPClientDevice.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PTPClientDevice.dep"
} } ;

Target vdcpp260 = { "PTPClientDevice.vm.dep" , OBJ_PATH+"/PTPClientDevice.vm.dep" } ;
Rule rvdcpp260 = { {&dcpp260} , {&vdcpp260} , {&exedcpp260} } ;
Exe exedcpp260 = { "CC-VM-DEP PTPClientDevice.cpp" , VMDEP , { OBJ_PATH+"/PTPClientDevice.dep" , OBJ_PATH+"/PTPClientDevice.vm.dep" , "260" } } ;

Target cpp261 = { "PTPConBase.cpp" , "../../Applied/CCore/src/./net/PTPConBase.cpp" } ;
Target dcpp261 = { "PTPConBase.dep" , OBJ_PATH+"/PTPConBase.dep" } ;
Rule rdcpp261 = { {&cpp261,&obj} , {&dcpp261} , {&execpp261} } ;
Exe execpp261 = { "CC-DEP PTPConBase.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PTPConBase.o"
 ,"../../Applied/CCore/src/./net/PTPConBase.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PTPConBase.dep"
} } ;

Target vdcpp261 = { "PTPConBase.vm.dep" , OBJ_PATH+"/PTPConBase.vm.dep" } ;
Rule rvdcpp261 = { {&dcpp261} , {&vdcpp261} , {&exedcpp261} } ;
Exe exedcpp261 = { "CC-VM-DEP PTPConBase.cpp" , VMDEP , { OBJ_PATH+"/PTPConBase.dep" , OBJ_PATH+"/PTPConBase.vm.dep" , "261" } } ;

Target cpp262 = { "PTPConDevice.cpp" , "../../Applied/CCore/src/./net/PTPConDevice.cpp" } ;
Target dcpp262 = { "PTPConDevice.dep" , OBJ_PATH+"/PTPConDevice.dep" } ;
Rule rdcpp262 = { {&cpp262,&obj} , {&dcpp262} , {&execpp262} } ;
Exe execpp262 = { "CC-DEP PTPConDevice.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PTPConDevice.o"
 ,"../../Applied/CCore/src/./net/PTPConDevice.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PTPConDevice.dep"
} } ;

Target vdcpp262 = { "PTPConDevice.vm.dep" , OBJ_PATH+"/PTPConDevice.vm.dep" } ;
Rule rvdcpp262 = { {&dcpp262} , {&vdcpp262} , {&exedcpp262} } ;
Exe exedcpp262 = { "CC-VM-DEP PTPConDevice.cpp" , VMDEP , { OBJ_PATH+"/PTPConDevice.dep" , OBJ_PATH+"/PTPConDevice.vm.dep" , "262" } } ;

Target cpp263 = { "PTPEchoTest.cpp" , "../../Applied/CCore/src/./net/PTPEchoTest.cpp" } ;
Target dcpp263 = { "PTPEchoTest.dep" , OBJ_PATH+"/PTPEchoTest.dep" } ;
Rule rdcpp263 = { {&cpp263,&obj} , {&dcpp263} , {&execpp263} } ;
Exe execpp263 = { "CC-DEP PTPEchoTest.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PTPEchoTest.o"
 ,"../../Applied/CCore/src/./net/PTPEchoTest.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PTPEchoTest.dep"
} } ;

Target vdcpp263 = { "PTPEchoTest.vm.dep" , OBJ_PATH+"/PTPEchoTest.vm.dep" } ;
Rule rvdcpp263 = { {&dcpp263} , {&vdcpp263} , {&exedcpp263} } ;
Exe exedcpp263 = { "CC-VM-DEP PTPEchoTest.cpp" , VMDEP , { OBJ_PATH+"/PTPEchoTest.dep" , OBJ_PATH+"/PTPEchoTest.vm.dep" , "263" } } ;

Target cpp264 = { "PTPExtra.cpp" , "../../Applied/CCore/src/./net/PTPExtra.cpp" } ;
Target dcpp264 = { "PTPExtra.dep" , OBJ_PATH+"/PTPExtra.dep" } ;
Rule rdcpp264 = { {&cpp264,&obj} , {&dcpp264} , {&execpp264} } ;
Exe execpp264 = { "CC-DEP PTPExtra.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PTPExtra.o"
 ,"../../Applied/CCore/src/./net/PTPExtra.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PTPExtra.dep"
} } ;

Target vdcpp264 = { "PTPExtra.vm.dep" , OBJ_PATH+"/PTPExtra.vm.dep" } ;
Rule rvdcpp264 = { {&dcpp264} , {&vdcpp264} , {&exedcpp264} } ;
Exe exedcpp264 = { "CC-VM-DEP PTPExtra.cpp" , VMDEP , { OBJ_PATH+"/PTPExtra.dep" , OBJ_PATH+"/PTPExtra.vm.dep" , "264" } } ;

Target cpp265 = { "PTPServerDevice.cpp" , "../../Applied/CCore/src/./net/PTPServerDevice.cpp" } ;
Target dcpp265 = { "PTPServerDevice.dep" , OBJ_PATH+"/PTPServerDevice.dep" } ;
Rule rdcpp265 = { {&cpp265,&obj} , {&dcpp265} , {&execpp265} } ;
Exe execpp265 = { "CC-DEP PTPServerDevice.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PTPServerDevice.o"
 ,"../../Applied/CCore/src/./net/PTPServerDevice.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PTPServerDevice.dep"
} } ;

Target vdcpp265 = { "PTPServerDevice.vm.dep" , OBJ_PATH+"/PTPServerDevice.vm.dep" } ;
Rule rvdcpp265 = { {&dcpp265} , {&vdcpp265} , {&exedcpp265} } ;
Exe exedcpp265 = { "CC-VM-DEP PTPServerDevice.cpp" , VMDEP , { OBJ_PATH+"/PTPServerDevice.dep" , OBJ_PATH+"/PTPServerDevice.vm.dep" , "265" } } ;

Target cpp266 = { "PTPSupport.cpp" , "../../Applied/CCore/src/./net/PTPSupport.cpp" } ;
Target dcpp266 = { "PTPSupport.dep" , OBJ_PATH+"/PTPSupport.dep" } ;
Rule rdcpp266 = { {&cpp266,&obj} , {&dcpp266} , {&execpp266} } ;
Exe execpp266 = { "CC-DEP PTPSupport.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PTPSupport.o"
 ,"../../Applied/CCore/src/./net/PTPSupport.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PTPSupport.dep"
} } ;

Target vdcpp266 = { "PTPSupport.vm.dep" , OBJ_PATH+"/PTPSupport.vm.dep" } ;
Rule rvdcpp266 = { {&dcpp266} , {&vdcpp266} , {&exedcpp266} } ;
Exe exedcpp266 = { "CC-VM-DEP PTPSupport.cpp" , VMDEP , { OBJ_PATH+"/PTPSupport.dep" , OBJ_PATH+"/PTPSupport.vm.dep" , "266" } } ;

Target cpp267 = { "PTPSupportBase.cpp" , "../../Applied/CCore/src/./net/PTPSupportBase.cpp" } ;
Target dcpp267 = { "PTPSupportBase.dep" , OBJ_PATH+"/PTPSupportBase.dep" } ;
Rule rdcpp267 = { {&cpp267,&obj} , {&dcpp267} , {&execpp267} } ;
Exe execpp267 = { "CC-DEP PTPSupportBase.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PTPSupportBase.o"
 ,"../../Applied/CCore/src/./net/PTPSupportBase.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PTPSupportBase.dep"
} } ;

Target vdcpp267 = { "PTPSupportBase.vm.dep" , OBJ_PATH+"/PTPSupportBase.vm.dep" } ;
Rule rvdcpp267 = { {&dcpp267} , {&vdcpp267} , {&exedcpp267} } ;
Exe exedcpp267 = { "CC-VM-DEP PTPSupportBase.cpp" , VMDEP , { OBJ_PATH+"/PTPSupportBase.dep" , OBJ_PATH+"/PTPSupportBase.vm.dep" , "267" } } ;

Target cpp268 = { "Packet.cpp" , "../../Applied/CCore/src/Packet.cpp" } ;
Target dcpp268 = { "Packet.dep" , OBJ_PATH+"/Packet.dep" } ;
Rule rdcpp268 = { {&cpp268,&obj} , {&dcpp268} , {&execpp268} } ;
Exe execpp268 = { "CC-DEP Packet.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Packet.o"
 ,"../../Applied/CCore/src/Packet.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Packet.dep"
} } ;

Target vdcpp268 = { "Packet.vm.dep" , OBJ_PATH+"/Packet.vm.dep" } ;
Rule rvdcpp268 = { {&dcpp268} , {&vdcpp268} , {&exedcpp268} } ;
Exe exedcpp268 = { "CC-VM-DEP Packet.cpp" , VMDEP , { OBJ_PATH+"/Packet.dep" , OBJ_PATH+"/Packet.vm.dep" , "268" } } ;

Target cpp269 = { "PacketEndpointDevice.cpp" , "../../Applied/CCore/src/./net/PacketEndpointDevice.cpp" } ;
Target dcpp269 = { "PacketEndpointDevice.dep" , OBJ_PATH+"/PacketEndpointDevice.dep" } ;
Rule rdcpp269 = { {&cpp269,&obj} , {&dcpp269} , {&execpp269} } ;
Exe execpp269 = { "CC-DEP PacketEndpointDevice.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PacketEndpointDevice.o"
 ,"../../Applied/CCore/src/./net/PacketEndpointDevice.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PacketEndpointDevice.dep"
} } ;

Target vdcpp269 = { "PacketEndpointDevice.vm.dep" , OBJ_PATH+"/PacketEndpointDevice.vm.dep" } ;
Rule rvdcpp269 = { {&dcpp269} , {&vdcpp269} , {&exedcpp269} } ;
Exe exedcpp269 = { "CC-VM-DEP PacketEndpointDevice.cpp" , VMDEP , { OBJ_PATH+"/PacketEndpointDevice.dep" , OBJ_PATH+"/PacketEndpointDevice.vm.dep" , "269" } } ;

Target cpp270 = { "PacketPool.cpp" , "../../Applied/CCore/src/PacketPool.cpp" } ;
Target dcpp270 = { "PacketPool.dep" , OBJ_PATH+"/PacketPool.dep" } ;
Rule rdcpp270 = { {&cpp270,&obj} , {&dcpp270} , {&execpp270} } ;
Exe execpp270 = { "CC-DEP PacketPool.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PacketPool.o"
 ,"../../Applied/CCore/src/PacketPool.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PacketPool.dep"
} } ;

Target vdcpp270 = { "PacketPool.vm.dep" , OBJ_PATH+"/PacketPool.vm.dep" } ;
Rule rvdcpp270 = { {&dcpp270} , {&vdcpp270} , {&exedcpp270} } ;
Exe exedcpp270 = { "CC-VM-DEP PacketPool.cpp" , VMDEP , { OBJ_PATH+"/PacketPool.dep" , OBJ_PATH+"/PacketPool.vm.dep" , "270" } } ;

Target cpp271 = { "PacketPool_PacketCount.cpp" , "../../Applied/CCore/src/PacketPool_PacketCount.cpp" } ;
Target dcpp271 = { "PacketPool_PacketCount.dep" , OBJ_PATH+"/PacketPool_PacketCount.dep" } ;
Rule rdcpp271 = { {&cpp271,&obj} , {&dcpp271} , {&execpp271} } ;
Exe execpp271 = { "CC-DEP PacketPool_PacketCount.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PacketPool_PacketCount.o"
 ,"../../Applied/CCore/src/PacketPool_PacketCount.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PacketPool_PacketCount.dep"
} } ;

Target vdcpp271 = { "PacketPool_PacketCount.vm.dep" , OBJ_PATH+"/PacketPool_PacketCount.vm.dep" } ;
Rule rvdcpp271 = { {&dcpp271} , {&vdcpp271} , {&exedcpp271} } ;
Exe exedcpp271 = { "CC-VM-DEP PacketPool_PacketCount.cpp" , VMDEP , { OBJ_PATH+"/PacketPool_PacketCount.dep" , OBJ_PATH+"/PacketPool_PacketCount.vm.dep" , "271" } } ;

Target cpp272 = { "PacketPool_PacketMaxDataLen.cpp" , "../../Applied/CCore/src/PacketPool_PacketMaxDataLen.cpp" } ;
Target dcpp272 = { "PacketPool_PacketMaxDataLen.dep" , OBJ_PATH+"/PacketPool_PacketMaxDataLen.dep" } ;
Rule rdcpp272 = { {&cpp272,&obj} , {&dcpp272} , {&execpp272} } ;
Exe execpp272 = { "CC-DEP PacketPool_PacketMaxDataLen.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PacketPool_PacketMaxDataLen.o"
 ,"../../Applied/CCore/src/PacketPool_PacketMaxDataLen.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PacketPool_PacketMaxDataLen.dep"
} } ;

Target vdcpp272 = { "PacketPool_PacketMaxDataLen.vm.dep" , OBJ_PATH+"/PacketPool_PacketMaxDataLen.vm.dep" } ;
Rule rvdcpp272 = { {&dcpp272} , {&vdcpp272} , {&exedcpp272} } ;
Exe exedcpp272 = { "CC-VM-DEP PacketPool_PacketMaxDataLen.cpp" , VMDEP , { OBJ_PATH+"/PacketPool_PacketMaxDataLen.dep" , OBJ_PATH+"/PacketPool_PacketMaxDataLen.vm.dep" , "272" } } ;

Target cpp273 = { "PacketSet.cpp" , "../../Applied/CCore/src/PacketSet.cpp" } ;
Target dcpp273 = { "PacketSet.dep" , OBJ_PATH+"/PacketSet.dep" } ;
Rule rdcpp273 = { {&cpp273,&obj} , {&dcpp273} , {&execpp273} } ;
Exe execpp273 = { "CC-DEP PacketSet.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PacketSet.o"
 ,"../../Applied/CCore/src/PacketSet.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PacketSet.dep"
} } ;

Target vdcpp273 = { "PacketSet.vm.dep" , OBJ_PATH+"/PacketSet.vm.dep" } ;
Rule rvdcpp273 = { {&dcpp273} , {&vdcpp273} , {&exedcpp273} } ;
Exe exedcpp273 = { "CC-VM-DEP PacketSet.cpp" , VMDEP , { OBJ_PATH+"/PacketSet.dep" , OBJ_PATH+"/PacketSet.vm.dep" , "273" } } ;

Target cpp274 = { "ParaQuickSort.cpp" , "../../Fundamental/CCore/src/./sort/ParaQuickSort.cpp" } ;
Target dcpp274 = { "ParaQuickSort.dep" , OBJ_PATH+"/ParaQuickSort.dep" } ;
Rule rdcpp274 = { {&cpp274,&obj} , {&dcpp274} , {&execpp274} } ;
Exe execpp274 = { "CC-DEP ParaQuickSort.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ParaQuickSort.o"
 ,"../../Fundamental/CCore/src/./sort/ParaQuickSort.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ParaQuickSort.dep"
} } ;

Target vdcpp274 = { "ParaQuickSort.vm.dep" , OBJ_PATH+"/ParaQuickSort.vm.dep" } ;
Rule rvdcpp274 = { {&dcpp274} , {&vdcpp274} , {&exedcpp274} } ;
Exe exedcpp274 = { "CC-VM-DEP ParaQuickSort.cpp" , VMDEP , { OBJ_PATH+"/ParaQuickSort.dep" , OBJ_PATH+"/ParaQuickSort.vm.dep" , "274" } } ;

Target cpp275 = { "Partition.cpp" , "../../Fundamental/CCore/src/./algon/Partition.cpp" } ;
Target dcpp275 = { "Partition.dep" , OBJ_PATH+"/Partition.dep" } ;
Rule rdcpp275 = { {&cpp275,&obj} , {&dcpp275} , {&execpp275} } ;
Exe execpp275 = { "CC-DEP Partition.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Partition.o"
 ,"../../Fundamental/CCore/src/./algon/Partition.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Partition.dep"
} } ;

Target vdcpp275 = { "Partition.vm.dep" , OBJ_PATH+"/Partition.vm.dep" } ;
Rule rvdcpp275 = { {&dcpp275} , {&vdcpp275} , {&exedcpp275} } ;
Exe exedcpp275 = { "CC-VM-DEP Partition.cpp" , VMDEP , { OBJ_PATH+"/Partition.dep" , OBJ_PATH+"/Partition.vm.dep" , "275" } } ;

Target cpp276 = { "Path.cpp" , "../../Fundamental/CCore/src/Path.cpp" } ;
Target dcpp276 = { "Path.dep" , OBJ_PATH+"/Path.dep" } ;
Rule rdcpp276 = { {&cpp276,&obj} , {&dcpp276} , {&execpp276} } ;
Exe execpp276 = { "CC-DEP Path.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Path.o"
 ,"../../Fundamental/CCore/src/Path.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Path.dep"
} } ;

Target vdcpp276 = { "Path.vm.dep" , OBJ_PATH+"/Path.vm.dep" } ;
Rule rvdcpp276 = { {&dcpp276} , {&vdcpp276} , {&exedcpp276} } ;
Exe exedcpp276 = { "CC-VM-DEP Path.cpp" , VMDEP , { OBJ_PATH+"/Path.dep" , OBJ_PATH+"/Path.vm.dep" , "276" } } ;

Target cpp277 = { "PerTask.cpp" , "../../Applied/CCore/src/PerTask.cpp" } ;
Target dcpp277 = { "PerTask.dep" , OBJ_PATH+"/PerTask.dep" } ;
Rule rdcpp277 = { {&cpp277,&obj} , {&dcpp277} , {&execpp277} } ;
Exe execpp277 = { "CC-DEP PerTask.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PerTask.o"
 ,"../../Applied/CCore/src/PerTask.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PerTask.dep"
} } ;

Target vdcpp277 = { "PerTask.vm.dep" , OBJ_PATH+"/PerTask.vm.dep" } ;
Rule rvdcpp277 = { {&dcpp277} , {&vdcpp277} , {&exedcpp277} } ;
Exe exedcpp277 = { "CC-VM-DEP PerTask.cpp" , VMDEP , { OBJ_PATH+"/PerTask.dep" , OBJ_PATH+"/PerTask.vm.dep" , "277" } } ;

Target cpp278 = { "Picture.cpp" , "../../Desktop/Tools/CCore/src/./video/Picture.cpp" } ;
Target dcpp278 = { "Picture.dep" , OBJ_PATH+"/Picture.dep" } ;
Rule rdcpp278 = { {&cpp278,&obj} , {&dcpp278} , {&execpp278} } ;
Exe execpp278 = { "CC-DEP Picture.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Picture.o"
 ,"../../Desktop/Tools/CCore/src/./video/Picture.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Picture.dep"
} } ;

Target vdcpp278 = { "Picture.vm.dep" , OBJ_PATH+"/Picture.vm.dep" } ;
Rule rvdcpp278 = { {&dcpp278} , {&vdcpp278} , {&exedcpp278} } ;
Exe exedcpp278 = { "CC-VM-DEP Picture.cpp" , VMDEP , { OBJ_PATH+"/Picture.dep" , OBJ_PATH+"/Picture.vm.dep" , "278" } } ;

Target cpp279 = { "Place.cpp" , "../../Simple/CCore/src/./gadget/Place.cpp" } ;
Target dcpp279 = { "Place.dep" , OBJ_PATH+"/Place.dep" } ;
Rule rdcpp279 = { {&cpp279,&obj} , {&dcpp279} , {&execpp279} } ;
Exe execpp279 = { "CC-DEP Place.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Place.o"
 ,"../../Simple/CCore/src/./gadget/Place.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Place.dep"
} } ;

Target vdcpp279 = { "Place.vm.dep" , OBJ_PATH+"/Place.vm.dep" } ;
Rule rvdcpp279 = { {&dcpp279} , {&vdcpp279} , {&exedcpp279} } ;
Exe exedcpp279 = { "CC-VM-DEP Place.cpp" , VMDEP , { OBJ_PATH+"/Place.dep" , OBJ_PATH+"/Place.vm.dep" , "279" } } ;

Target cpp280 = { "PlanInit.cpp" , "../../Fundamental/CCore/src/PlanInit.cpp" } ;
Target dcpp280 = { "PlanInit.dep" , OBJ_PATH+"/PlanInit.dep" } ;
Rule rdcpp280 = { {&cpp280,&obj} , {&dcpp280} , {&execpp280} } ;
Exe execpp280 = { "CC-DEP PlanInit.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PlanInit.o"
 ,"../../Fundamental/CCore/src/PlanInit.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PlanInit.dep"
} } ;

Target vdcpp280 = { "PlanInit.vm.dep" , OBJ_PATH+"/PlanInit.vm.dep" } ;
Rule rvdcpp280 = { {&dcpp280} , {&vdcpp280} , {&exedcpp280} } ;
Exe exedcpp280 = { "CC-VM-DEP PlanInit.cpp" , VMDEP , { OBJ_PATH+"/PlanInit.dep" , OBJ_PATH+"/PlanInit.vm.dep" , "280" } } ;

Target cpp281 = { "PlanInit_CCore.cpp" , "CCore/src/PlanInit_CCore.cpp" } ;
Target dcpp281 = { "PlanInit_CCore.dep" , OBJ_PATH+"/PlanInit_CCore.dep" } ;
Rule rdcpp281 = { {&cpp281,&obj} , {&dcpp281} , {&execpp281} } ;
Exe execpp281 = { "CC-DEP PlanInit_CCore.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PlanInit_CCore.o"
 ,"CCore/src/PlanInit_CCore.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PlanInit_CCore.dep"
} } ;

Target vdcpp281 = { "PlanInit_CCore.vm.dep" , OBJ_PATH+"/PlanInit_CCore.vm.dep" } ;
Rule rvdcpp281 = { {&dcpp281} , {&vdcpp281} , {&exedcpp281} } ;
Exe exedcpp281 = { "CC-VM-DEP PlanInit_CCore.cpp" , VMDEP , { OBJ_PATH+"/PlanInit_CCore.dep" , OBJ_PATH+"/PlanInit_CCore.vm.dep" , "281" } } ;

Target cpp282 = { "PlatformBase.cpp" , "CCore/src/./base/PlatformBase.cpp" } ;
Target dcpp282 = { "PlatformBase.dep" , OBJ_PATH+"/PlatformBase.dep" } ;
Rule rdcpp282 = { {&cpp282,&obj} , {&dcpp282} , {&execpp282} } ;
Exe execpp282 = { "CC-DEP PlatformBase.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PlatformBase.o"
 ,"CCore/src/./base/PlatformBase.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PlatformBase.dep"
} } ;

Target vdcpp282 = { "PlatformBase.vm.dep" , OBJ_PATH+"/PlatformBase.vm.dep" } ;
Rule rvdcpp282 = { {&dcpp282} , {&vdcpp282} , {&exedcpp282} } ;
Exe exedcpp282 = { "CC-VM-DEP PlatformBase.cpp" , VMDEP , { OBJ_PATH+"/PlatformBase.dep" , OBJ_PATH+"/PlatformBase.vm.dep" , "282" } } ;

Target cpp283 = { "Point.cpp" , "../../Applied/CCore/src/./video/Point.cpp" } ;
Target dcpp283 = { "Point.dep" , OBJ_PATH+"/Point.dep" } ;
Rule rdcpp283 = { {&cpp283,&obj} , {&dcpp283} , {&execpp283} } ;
Exe execpp283 = { "CC-DEP Point.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Point.o"
 ,"../../Applied/CCore/src/./video/Point.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Point.dep"
} } ;

Target vdcpp283 = { "Point.vm.dep" , OBJ_PATH+"/Point.vm.dep" } ;
Rule rvdcpp283 = { {&dcpp283} , {&vdcpp283} , {&exedcpp283} } ;
Exe exedcpp283 = { "CC-VM-DEP Point.cpp" , VMDEP , { OBJ_PATH+"/Point.dep" , OBJ_PATH+"/Point.vm.dep" , "283" } } ;

Target cpp284 = { "PointEdit.cpp" , "../../Desktop/Lib/CCore/src/./video/pref/PointEdit.cpp" } ;
Target dcpp284 = { "PointEdit.dep" , OBJ_PATH+"/PointEdit.dep" } ;
Rule rdcpp284 = { {&cpp284,&obj} , {&dcpp284} , {&execpp284} } ;
Exe execpp284 = { "CC-DEP PointEdit.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PointEdit.o"
 ,"../../Desktop/Lib/CCore/src/./video/pref/PointEdit.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PointEdit.dep"
} } ;

Target vdcpp284 = { "PointEdit.vm.dep" , OBJ_PATH+"/PointEdit.vm.dep" } ;
Rule rvdcpp284 = { {&dcpp284} , {&vdcpp284} , {&exedcpp284} } ;
Exe exedcpp284 = { "CC-VM-DEP PointEdit.cpp" , VMDEP , { OBJ_PATH+"/PointEdit.dep" , OBJ_PATH+"/PointEdit.vm.dep" , "284" } } ;

Target cpp285 = { "PosSub.cpp" , "../../Simple/CCore/src/./gadget/PosSub.cpp" } ;
Target dcpp285 = { "PosSub.dep" , OBJ_PATH+"/PosSub.dep" } ;
Rule rdcpp285 = { {&cpp285,&obj} , {&dcpp285} , {&execpp285} } ;
Exe execpp285 = { "CC-DEP PosSub.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PosSub.o"
 ,"../../Simple/CCore/src/./gadget/PosSub.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PosSub.dep"
} } ;

Target vdcpp285 = { "PosSub.vm.dep" , OBJ_PATH+"/PosSub.vm.dep" } ;
Rule rvdcpp285 = { {&dcpp285} , {&vdcpp285} , {&exedcpp285} } ;
Exe exedcpp285 = { "CC-VM-DEP PosSub.cpp" , VMDEP , { OBJ_PATH+"/PosSub.dep" , OBJ_PATH+"/PosSub.vm.dep" , "285" } } ;

Target cpp286 = { "Pow.cpp" , "../../Simple/CCore/src/Pow.cpp" } ;
Target dcpp286 = { "Pow.dep" , OBJ_PATH+"/Pow.dep" } ;
Rule rdcpp286 = { {&cpp286,&obj} , {&dcpp286} , {&execpp286} } ;
Exe execpp286 = { "CC-DEP Pow.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Pow.o"
 ,"../../Simple/CCore/src/Pow.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Pow.dep"
} } ;

Target vdcpp286 = { "Pow.vm.dep" , OBJ_PATH+"/Pow.vm.dep" } ;
Rule rvdcpp286 = { {&dcpp286} , {&vdcpp286} , {&exedcpp286} } ;
Exe exedcpp286 = { "CC-VM-DEP Pow.cpp" , VMDEP , { OBJ_PATH+"/Pow.dep" , OBJ_PATH+"/Pow.vm.dep" , "286" } } ;

Target cpp287 = { "PretextFileToMem.cpp" , "../../Applied/CCore/src/PretextFileToMem.cpp" } ;
Target dcpp287 = { "PretextFileToMem.dep" , OBJ_PATH+"/PretextFileToMem.dep" } ;
Rule rdcpp287 = { {&cpp287,&obj} , {&dcpp287} , {&execpp287} } ;
Exe execpp287 = { "CC-DEP PretextFileToMem.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PretextFileToMem.o"
 ,"../../Applied/CCore/src/PretextFileToMem.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PretextFileToMem.dep"
} } ;

Target vdcpp287 = { "PretextFileToMem.vm.dep" , OBJ_PATH+"/PretextFileToMem.vm.dep" } ;
Rule rvdcpp287 = { {&dcpp287} , {&vdcpp287} , {&exedcpp287} } ;
Exe exedcpp287 = { "CC-VM-DEP PretextFileToMem.cpp" , VMDEP , { OBJ_PATH+"/PretextFileToMem.dep" , OBJ_PATH+"/PretextFileToMem.vm.dep" , "287" } } ;

Target cpp288 = { "Print.cpp" , "../../HCore/CCore/src/Print.cpp" } ;
Target dcpp288 = { "Print.dep" , OBJ_PATH+"/Print.dep" } ;
Rule rdcpp288 = { {&cpp288,&obj} , {&dcpp288} , {&execpp288} } ;
Exe execpp288 = { "CC-DEP Print.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Print.o"
 ,"../../HCore/CCore/src/Print.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Print.dep"
} } ;

Target vdcpp288 = { "Print.vm.dep" , OBJ_PATH+"/Print.vm.dep" } ;
Rule rvdcpp288 = { {&dcpp288} , {&vdcpp288} , {&exedcpp288} } ;
Exe exedcpp288 = { "CC-VM-DEP Print.cpp" , VMDEP , { OBJ_PATH+"/Print.dep" , OBJ_PATH+"/Print.vm.dep" , "288" } } ;

Target cpp289 = { "PrintAbort.cpp" , "../../Simple/CCore/src/PrintAbort.cpp" } ;
Target dcpp289 = { "PrintAbort.dep" , OBJ_PATH+"/PrintAbort.dep" } ;
Rule rdcpp289 = { {&cpp289,&obj} , {&dcpp289} , {&execpp289} } ;
Exe execpp289 = { "CC-DEP PrintAbort.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PrintAbort.o"
 ,"../../Simple/CCore/src/PrintAbort.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PrintAbort.dep"
} } ;

Target vdcpp289 = { "PrintAbort.vm.dep" , OBJ_PATH+"/PrintAbort.vm.dep" } ;
Rule rvdcpp289 = { {&dcpp289} , {&vdcpp289} , {&exedcpp289} } ;
Exe exedcpp289 = { "CC-VM-DEP PrintAbort.cpp" , VMDEP , { OBJ_PATH+"/PrintAbort.dep" , OBJ_PATH+"/PrintAbort.vm.dep" , "289" } } ;

Target cpp290 = { "PrintAsyncFile.cpp" , "../../Applied/CCore/src/./print/PrintAsyncFile.cpp" } ;
Target dcpp290 = { "PrintAsyncFile.dep" , OBJ_PATH+"/PrintAsyncFile.dep" } ;
Rule rdcpp290 = { {&cpp290,&obj} , {&dcpp290} , {&execpp290} } ;
Exe execpp290 = { "CC-DEP PrintAsyncFile.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PrintAsyncFile.o"
 ,"../../Applied/CCore/src/./print/PrintAsyncFile.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PrintAsyncFile.dep"
} } ;

Target vdcpp290 = { "PrintAsyncFile.vm.dep" , OBJ_PATH+"/PrintAsyncFile.vm.dep" } ;
Rule rvdcpp290 = { {&dcpp290} , {&vdcpp290} , {&exedcpp290} } ;
Exe exedcpp290 = { "CC-VM-DEP PrintAsyncFile.cpp" , VMDEP , { OBJ_PATH+"/PrintAsyncFile.dep" , OBJ_PATH+"/PrintAsyncFile.vm.dep" , "290" } } ;

Target cpp291 = { "PrintBase.cpp" , "../../Fundamental/CCore/src/./printf/PrintBase.cpp" } ;
Target dcpp291 = { "PrintBase.dep" , OBJ_PATH+"/PrintBase.dep" } ;
Rule rdcpp291 = { {&cpp291,&obj} , {&dcpp291} , {&execpp291} } ;
Exe execpp291 = { "CC-DEP PrintBase.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PrintBase.o"
 ,"../../Fundamental/CCore/src/./printf/PrintBase.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PrintBase.dep"
} } ;

Target vdcpp291 = { "PrintBase.vm.dep" , OBJ_PATH+"/PrintBase.vm.dep" } ;
Rule rvdcpp291 = { {&dcpp291} , {&vdcpp291} , {&exedcpp291} } ;
Exe exedcpp291 = { "CC-VM-DEP PrintBase.cpp" , VMDEP , { OBJ_PATH+"/PrintBase.dep" , OBJ_PATH+"/PrintBase.vm.dep" , "291" } } ;

Target cpp292 = { "PrintBits.cpp" , "../../Simple/CCore/src/PrintBits.cpp" } ;
Target dcpp292 = { "PrintBits.dep" , OBJ_PATH+"/PrintBits.dep" } ;
Rule rdcpp292 = { {&cpp292,&obj} , {&dcpp292} , {&execpp292} } ;
Exe execpp292 = { "CC-DEP PrintBits.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PrintBits.o"
 ,"../../Simple/CCore/src/PrintBits.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PrintBits.dep"
} } ;

Target vdcpp292 = { "PrintBits.vm.dep" , OBJ_PATH+"/PrintBits.vm.dep" } ;
Rule rvdcpp292 = { {&dcpp292} , {&vdcpp292} , {&exedcpp292} } ;
Exe exedcpp292 = { "CC-VM-DEP PrintBits.cpp" , VMDEP , { OBJ_PATH+"/PrintBits.dep" , OBJ_PATH+"/PrintBits.vm.dep" , "292" } } ;

Target cpp293 = { "PrintCon.cpp" , "../../HCore/CCore/src/./print/PrintCon.cpp" } ;
Target dcpp293 = { "PrintCon.dep" , OBJ_PATH+"/PrintCon.dep" } ;
Rule rdcpp293 = { {&cpp293,&obj} , {&dcpp293} , {&execpp293} } ;
Exe execpp293 = { "CC-DEP PrintCon.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PrintCon.o"
 ,"../../HCore/CCore/src/./print/PrintCon.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PrintCon.dep"
} } ;

Target vdcpp293 = { "PrintCon.vm.dep" , OBJ_PATH+"/PrintCon.vm.dep" } ;
Rule rvdcpp293 = { {&dcpp293} , {&vdcpp293} , {&exedcpp293} } ;
Exe exedcpp293 = { "CC-VM-DEP PrintCon.cpp" , VMDEP , { OBJ_PATH+"/PrintCon.dep" , OBJ_PATH+"/PrintCon.vm.dep" , "293" } } ;

Target cpp294 = { "PrintDDL.cpp" , "../../Desktop/Tools/CCore/src/./video/PrintDDL.cpp" } ;
Target dcpp294 = { "PrintDDL.dep" , OBJ_PATH+"/PrintDDL.dep" } ;
Rule rdcpp294 = { {&cpp294,&obj} , {&dcpp294} , {&execpp294} } ;
Exe execpp294 = { "CC-DEP PrintDDL.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PrintDDL.o"
 ,"../../Desktop/Tools/CCore/src/./video/PrintDDL.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PrintDDL.dep"
} } ;

Target vdcpp294 = { "PrintDDL.vm.dep" , OBJ_PATH+"/PrintDDL.vm.dep" } ;
Rule rvdcpp294 = { {&dcpp294} , {&vdcpp294} , {&exedcpp294} } ;
Exe exedcpp294 = { "CC-VM-DEP PrintDDL.cpp" , VMDEP , { OBJ_PATH+"/PrintDDL.dep" , OBJ_PATH+"/PrintDDL.vm.dep" , "294" } } ;

Target cpp295 = { "PrintError.cpp" , "../../Simple/CCore/src/PrintError.cpp" } ;
Target dcpp295 = { "PrintError.dep" , OBJ_PATH+"/PrintError.dep" } ;
Rule rdcpp295 = { {&cpp295,&obj} , {&dcpp295} , {&execpp295} } ;
Exe execpp295 = { "CC-DEP PrintError.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PrintError.o"
 ,"../../Simple/CCore/src/PrintError.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PrintError.dep"
} } ;

Target vdcpp295 = { "PrintError.vm.dep" , OBJ_PATH+"/PrintError.vm.dep" } ;
Rule rvdcpp295 = { {&dcpp295} , {&vdcpp295} , {&exedcpp295} } ;
Exe exedcpp295 = { "CC-VM-DEP PrintError.cpp" , VMDEP , { OBJ_PATH+"/PrintError.dep" , OBJ_PATH+"/PrintError.vm.dep" , "295" } } ;

Target cpp296 = { "PrintFile.cpp" , "../../HCore/CCore/src/./print/PrintFile.cpp" } ;
Target dcpp296 = { "PrintFile.dep" , OBJ_PATH+"/PrintFile.dep" } ;
Rule rdcpp296 = { {&cpp296,&obj} , {&dcpp296} , {&execpp296} } ;
Exe execpp296 = { "CC-DEP PrintFile.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PrintFile.o"
 ,"../../HCore/CCore/src/./print/PrintFile.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PrintFile.dep"
} } ;

Target vdcpp296 = { "PrintFile.vm.dep" , OBJ_PATH+"/PrintFile.vm.dep" } ;
Rule rvdcpp296 = { {&dcpp296} , {&vdcpp296} , {&exedcpp296} } ;
Exe exedcpp296 = { "CC-VM-DEP PrintFile.cpp" , VMDEP , { OBJ_PATH+"/PrintFile.dep" , OBJ_PATH+"/PrintFile.vm.dep" , "296" } } ;

Target cpp297 = { "PrintInteger.cpp" , "../../Applied/CCore/src/./math/PrintInteger.cpp" } ;
Target dcpp297 = { "PrintInteger.dep" , OBJ_PATH+"/PrintInteger.dep" } ;
Rule rdcpp297 = { {&cpp297,&obj} , {&dcpp297} , {&execpp297} } ;
Exe execpp297 = { "CC-DEP PrintInteger.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PrintInteger.o"
 ,"../../Applied/CCore/src/./math/PrintInteger.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PrintInteger.dep"
} } ;

Target vdcpp297 = { "PrintInteger.vm.dep" , OBJ_PATH+"/PrintInteger.vm.dep" } ;
Rule rvdcpp297 = { {&dcpp297} , {&vdcpp297} , {&exedcpp297} } ;
Exe exedcpp297 = { "CC-VM-DEP PrintInteger.cpp" , VMDEP , { OBJ_PATH+"/PrintInteger.dep" , OBJ_PATH+"/PrintInteger.vm.dep" , "297" } } ;

Target cpp298 = { "PrintPTPCon.cpp" , "../../Applied/CCore/src/./print/PrintPTPCon.cpp" } ;
Target dcpp298 = { "PrintPTPCon.dep" , OBJ_PATH+"/PrintPTPCon.dep" } ;
Rule rdcpp298 = { {&cpp298,&obj} , {&dcpp298} , {&execpp298} } ;
Exe execpp298 = { "CC-DEP PrintPTPCon.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PrintPTPCon.o"
 ,"../../Applied/CCore/src/./print/PrintPTPCon.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PrintPTPCon.dep"
} } ;

Target vdcpp298 = { "PrintPTPCon.vm.dep" , OBJ_PATH+"/PrintPTPCon.vm.dep" } ;
Rule rvdcpp298 = { {&dcpp298} , {&vdcpp298} , {&exedcpp298} } ;
Exe exedcpp298 = { "CC-VM-DEP PrintPTPCon.cpp" , VMDEP , { OBJ_PATH+"/PrintPTPCon.dep" , OBJ_PATH+"/PrintPTPCon.vm.dep" , "298" } } ;

Target cpp299 = { "PrintProxy.cpp" , "../../Fundamental/CCore/src/./printf/PrintProxy.cpp" } ;
Target dcpp299 = { "PrintProxy.dep" , OBJ_PATH+"/PrintProxy.dep" } ;
Rule rdcpp299 = { {&cpp299,&obj} , {&dcpp299} , {&execpp299} } ;
Exe execpp299 = { "CC-DEP PrintProxy.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PrintProxy.o"
 ,"../../Fundamental/CCore/src/./printf/PrintProxy.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PrintProxy.dep"
} } ;

Target vdcpp299 = { "PrintProxy.vm.dep" , OBJ_PATH+"/PrintProxy.vm.dep" } ;
Rule rvdcpp299 = { {&dcpp299} , {&vdcpp299} , {&exedcpp299} } ;
Exe exedcpp299 = { "CC-VM-DEP PrintProxy.cpp" , VMDEP , { OBJ_PATH+"/PrintProxy.dep" , OBJ_PATH+"/PrintProxy.vm.dep" , "299" } } ;

Target cpp300 = { "PrintRatio.cpp" , "../../Simple/CCore/src/PrintRatio.cpp" } ;
Target dcpp300 = { "PrintRatio.dep" , OBJ_PATH+"/PrintRatio.dep" } ;
Rule rdcpp300 = { {&cpp300,&obj} , {&dcpp300} , {&execpp300} } ;
Exe execpp300 = { "CC-DEP PrintRatio.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PrintRatio.o"
 ,"../../Simple/CCore/src/PrintRatio.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PrintRatio.dep"
} } ;

Target vdcpp300 = { "PrintRatio.vm.dep" , OBJ_PATH+"/PrintRatio.vm.dep" } ;
Rule rvdcpp300 = { {&dcpp300} , {&vdcpp300} , {&exedcpp300} } ;
Exe exedcpp300 = { "CC-VM-DEP PrintRatio.cpp" , VMDEP , { OBJ_PATH+"/PrintRatio.dep" , OBJ_PATH+"/PrintRatio.vm.dep" , "300" } } ;

Target cpp301 = { "PrintSet.cpp" , "../../Simple/CCore/src/PrintSet.cpp" } ;
Target dcpp301 = { "PrintSet.dep" , OBJ_PATH+"/PrintSet.dep" } ;
Rule rdcpp301 = { {&cpp301,&obj} , {&dcpp301} , {&execpp301} } ;
Exe execpp301 = { "CC-DEP PrintSet.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PrintSet.o"
 ,"../../Simple/CCore/src/PrintSet.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PrintSet.dep"
} } ;

Target vdcpp301 = { "PrintSet.vm.dep" , OBJ_PATH+"/PrintSet.vm.dep" } ;
Rule rvdcpp301 = { {&dcpp301} , {&vdcpp301} , {&exedcpp301} } ;
Exe exedcpp301 = { "CC-VM-DEP PrintSet.cpp" , VMDEP , { OBJ_PATH+"/PrintSet.dep" , OBJ_PATH+"/PrintSet.vm.dep" , "301" } } ;

Target cpp302 = { "PrintStem.cpp" , "../../Simple/CCore/src/PrintStem.cpp" } ;
Target dcpp302 = { "PrintStem.dep" , OBJ_PATH+"/PrintStem.dep" } ;
Rule rdcpp302 = { {&cpp302,&obj} , {&dcpp302} , {&execpp302} } ;
Exe execpp302 = { "CC-DEP PrintStem.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PrintStem.o"
 ,"../../Simple/CCore/src/PrintStem.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PrintStem.dep"
} } ;

Target vdcpp302 = { "PrintStem.vm.dep" , OBJ_PATH+"/PrintStem.vm.dep" } ;
Rule rvdcpp302 = { {&dcpp302} , {&vdcpp302} , {&exedcpp302} } ;
Exe exedcpp302 = { "CC-VM-DEP PrintStem.cpp" , VMDEP , { OBJ_PATH+"/PrintStem.dep" , OBJ_PATH+"/PrintStem.vm.dep" , "302" } } ;

Target cpp303 = { "PrintTime.cpp" , "../../Simple/CCore/src/PrintTime.cpp" } ;
Target dcpp303 = { "PrintTime.dep" , OBJ_PATH+"/PrintTime.dep" } ;
Rule rdcpp303 = { {&cpp303,&obj} , {&dcpp303} , {&execpp303} } ;
Exe execpp303 = { "CC-DEP PrintTime.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PrintTime.o"
 ,"../../Simple/CCore/src/PrintTime.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PrintTime.dep"
} } ;

Target vdcpp303 = { "PrintTime.vm.dep" , OBJ_PATH+"/PrintTime.vm.dep" } ;
Rule rvdcpp303 = { {&dcpp303} , {&vdcpp303} , {&exedcpp303} } ;
Exe exedcpp303 = { "CC-VM-DEP PrintTime.cpp" , VMDEP , { OBJ_PATH+"/PrintTime.dep" , OBJ_PATH+"/PrintTime.vm.dep" , "303" } } ;

Target cpp304 = { "PrintTitle.cpp" , "../../Simple/CCore/src/PrintTitle.cpp" } ;
Target dcpp304 = { "PrintTitle.dep" , OBJ_PATH+"/PrintTitle.dep" } ;
Rule rdcpp304 = { {&cpp304,&obj} , {&dcpp304} , {&execpp304} } ;
Exe execpp304 = { "CC-DEP PrintTitle.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PrintTitle.o"
 ,"../../Simple/CCore/src/PrintTitle.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PrintTitle.dep"
} } ;

Target vdcpp304 = { "PrintTitle.vm.dep" , OBJ_PATH+"/PrintTitle.vm.dep" } ;
Rule rvdcpp304 = { {&dcpp304} , {&vdcpp304} , {&exedcpp304} } ;
Exe exedcpp304 = { "CC-VM-DEP PrintTitle.cpp" , VMDEP , { OBJ_PATH+"/PrintTitle.dep" , OBJ_PATH+"/PrintTitle.vm.dep" , "304" } } ;

Target cpp305 = { "Printf.cpp" , "../../Fundamental/CCore/src/Printf.cpp" } ;
Target dcpp305 = { "Printf.dep" , OBJ_PATH+"/Printf.dep" } ;
Rule rdcpp305 = { {&cpp305,&obj} , {&dcpp305} , {&execpp305} } ;
Exe execpp305 = { "CC-DEP Printf.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Printf.o"
 ,"../../Fundamental/CCore/src/Printf.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Printf.dep"
} } ;

Target vdcpp305 = { "Printf.vm.dep" , OBJ_PATH+"/Printf.vm.dep" } ;
Rule rvdcpp305 = { {&dcpp305} , {&vdcpp305} , {&exedcpp305} } ;
Exe exedcpp305 = { "CC-VM-DEP Printf.cpp" , VMDEP , { OBJ_PATH+"/Printf.dep" , OBJ_PATH+"/Printf.vm.dep" , "305" } } ;

Target cpp306 = { "ProgressScale.cpp" , "../../Desktop/Tools/CCore/src/./video/ProgressScale.cpp" } ;
Target dcpp306 = { "ProgressScale.dep" , OBJ_PATH+"/ProgressScale.dep" } ;
Rule rdcpp306 = { {&cpp306,&obj} , {&dcpp306} , {&execpp306} } ;
Exe execpp306 = { "CC-DEP ProgressScale.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ProgressScale.o"
 ,"../../Desktop/Tools/CCore/src/./video/ProgressScale.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ProgressScale.dep"
} } ;

Target vdcpp306 = { "ProgressScale.vm.dep" , OBJ_PATH+"/ProgressScale.vm.dep" } ;
Rule rvdcpp306 = { {&dcpp306} , {&vdcpp306} , {&exedcpp306} } ;
Exe exedcpp306 = { "CC-VM-DEP ProgressScale.cpp" , VMDEP , { OBJ_PATH+"/ProgressScale.dep" , OBJ_PATH+"/ProgressScale.vm.dep" , "306" } } ;

Target cpp307 = { "PtrLen.cpp" , "../../Simple/CCore/src/./gadget/PtrLen.cpp" } ;
Target dcpp307 = { "PtrLen.dep" , OBJ_PATH+"/PtrLen.dep" } ;
Rule rdcpp307 = { {&cpp307,&obj} , {&dcpp307} , {&execpp307} } ;
Exe execpp307 = { "CC-DEP PtrLen.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PtrLen.o"
 ,"../../Simple/CCore/src/./gadget/PtrLen.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PtrLen.dep"
} } ;

Target vdcpp307 = { "PtrLen.vm.dep" , OBJ_PATH+"/PtrLen.vm.dep" } ;
Rule rvdcpp307 = { {&dcpp307} , {&vdcpp307} , {&exedcpp307} } ;
Exe exedcpp307 = { "CC-VM-DEP PtrLen.cpp" , VMDEP , { OBJ_PATH+"/PtrLen.dep" , OBJ_PATH+"/PtrLen.vm.dep" , "307" } } ;

Target cpp308 = { "PtrLenReverse.cpp" , "../../Simple/CCore/src/./gadget/PtrLenReverse.cpp" } ;
Target dcpp308 = { "PtrLenReverse.dep" , OBJ_PATH+"/PtrLenReverse.dep" } ;
Rule rdcpp308 = { {&cpp308,&obj} , {&dcpp308} , {&execpp308} } ;
Exe execpp308 = { "CC-DEP PtrLenReverse.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PtrLenReverse.o"
 ,"../../Simple/CCore/src/./gadget/PtrLenReverse.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PtrLenReverse.dep"
} } ;

Target vdcpp308 = { "PtrLenReverse.vm.dep" , OBJ_PATH+"/PtrLenReverse.vm.dep" } ;
Rule rvdcpp308 = { {&dcpp308} , {&vdcpp308} , {&exedcpp308} } ;
Exe exedcpp308 = { "CC-VM-DEP PtrLenReverse.cpp" , VMDEP , { OBJ_PATH+"/PtrLenReverse.dep" , OBJ_PATH+"/PtrLenReverse.vm.dep" , "308" } } ;

Target cpp309 = { "PtrStepLen.cpp" , "../../Simple/CCore/src/./gadget/PtrStepLen.cpp" } ;
Target dcpp309 = { "PtrStepLen.dep" , OBJ_PATH+"/PtrStepLen.dep" } ;
Rule rdcpp309 = { {&cpp309,&obj} , {&dcpp309} , {&execpp309} } ;
Exe execpp309 = { "CC-DEP PtrStepLen.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/PtrStepLen.o"
 ,"../../Simple/CCore/src/./gadget/PtrStepLen.cpp"
 ,"-MF"
 ,OBJ_PATH+"/PtrStepLen.dep"
} } ;

Target vdcpp309 = { "PtrStepLen.vm.dep" , OBJ_PATH+"/PtrStepLen.vm.dep" } ;
Rule rvdcpp309 = { {&dcpp309} , {&vdcpp309} , {&exedcpp309} } ;
Exe exedcpp309 = { "CC-VM-DEP PtrStepLen.cpp" , VMDEP , { OBJ_PATH+"/PtrStepLen.dep" , OBJ_PATH+"/PtrStepLen.vm.dep" , "309" } } ;

Target cpp310 = { "Quick.cpp" , "CCore/src/./base/Quick.cpp" } ;
Target dcpp310 = { "Quick.dep" , OBJ_PATH+"/Quick.dep" } ;
Rule rdcpp310 = { {&cpp310,&obj} , {&dcpp310} , {&execpp310} } ;
Exe execpp310 = { "CC-DEP Quick.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Quick.o"
 ,"CCore/src/./base/Quick.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Quick.dep"
} } ;

Target vdcpp310 = { "Quick.vm.dep" , OBJ_PATH+"/Quick.vm.dep" } ;
Rule rvdcpp310 = { {&dcpp310} , {&vdcpp310} , {&exedcpp310} } ;
Exe exedcpp310 = { "CC-VM-DEP Quick.cpp" , VMDEP , { OBJ_PATH+"/Quick.dep" , OBJ_PATH+"/Quick.vm.dep" , "310" } } ;

Target cpp311 = { "QuickSort.cpp" , "../../Fundamental/CCore/src/./sort/QuickSort.cpp" } ;
Target dcpp311 = { "QuickSort.dep" , OBJ_PATH+"/QuickSort.dep" } ;
Rule rdcpp311 = { {&cpp311,&obj} , {&dcpp311} , {&execpp311} } ;
Exe execpp311 = { "CC-DEP QuickSort.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/QuickSort.o"
 ,"../../Fundamental/CCore/src/./sort/QuickSort.cpp"
 ,"-MF"
 ,OBJ_PATH+"/QuickSort.dep"
} } ;

Target vdcpp311 = { "QuickSort.vm.dep" , OBJ_PATH+"/QuickSort.vm.dep" } ;
Rule rvdcpp311 = { {&dcpp311} , {&vdcpp311} , {&exedcpp311} } ;
Exe exedcpp311 = { "CC-VM-DEP QuickSort.cpp" , VMDEP , { OBJ_PATH+"/QuickSort.dep" , OBJ_PATH+"/QuickSort.vm.dep" , "311" } } ;

Target cpp312 = { "RBTreeBase.cpp" , "../../Fundamental/CCore/src/./tree/RBTreeBase.cpp" } ;
Target dcpp312 = { "RBTreeBase.dep" , OBJ_PATH+"/RBTreeBase.dep" } ;
Rule rdcpp312 = { {&cpp312,&obj} , {&dcpp312} , {&execpp312} } ;
Exe execpp312 = { "CC-DEP RBTreeBase.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/RBTreeBase.o"
 ,"../../Fundamental/CCore/src/./tree/RBTreeBase.cpp"
 ,"-MF"
 ,OBJ_PATH+"/RBTreeBase.dep"
} } ;

Target vdcpp312 = { "RBTreeBase.vm.dep" , OBJ_PATH+"/RBTreeBase.vm.dep" } ;
Rule rvdcpp312 = { {&dcpp312} , {&vdcpp312} , {&exedcpp312} } ;
Exe exedcpp312 = { "CC-VM-DEP RBTreeBase.cpp" , VMDEP , { OBJ_PATH+"/RBTreeBase.dep" , OBJ_PATH+"/RBTreeBase.vm.dep" , "312" } } ;

Target cpp313 = { "RBTreeLink.cpp" , "../../Fundamental/CCore/src/./tree/RBTreeLink.cpp" } ;
Target dcpp313 = { "RBTreeLink.dep" , OBJ_PATH+"/RBTreeLink.dep" } ;
Rule rdcpp313 = { {&cpp313,&obj} , {&dcpp313} , {&execpp313} } ;
Exe execpp313 = { "CC-DEP RBTreeLink.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/RBTreeLink.o"
 ,"../../Fundamental/CCore/src/./tree/RBTreeLink.cpp"
 ,"-MF"
 ,OBJ_PATH+"/RBTreeLink.dep"
} } ;

Target vdcpp313 = { "RBTreeLink.vm.dep" , OBJ_PATH+"/RBTreeLink.vm.dep" } ;
Rule rvdcpp313 = { {&dcpp313} , {&vdcpp313} , {&exedcpp313} } ;
Exe exedcpp313 = { "CC-VM-DEP RBTreeLink.cpp" , VMDEP , { OBJ_PATH+"/RBTreeLink.dep" , OBJ_PATH+"/RBTreeLink.vm.dep" , "313" } } ;

Target cpp314 = { "RBTreeUpLink.cpp" , "../../Fundamental/CCore/src/./tree/RBTreeUpLink.cpp" } ;
Target dcpp314 = { "RBTreeUpLink.dep" , OBJ_PATH+"/RBTreeUpLink.dep" } ;
Rule rdcpp314 = { {&cpp314,&obj} , {&dcpp314} , {&execpp314} } ;
Exe execpp314 = { "CC-DEP RBTreeUpLink.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/RBTreeUpLink.o"
 ,"../../Fundamental/CCore/src/./tree/RBTreeUpLink.cpp"
 ,"-MF"
 ,OBJ_PATH+"/RBTreeUpLink.dep"
} } ;

Target vdcpp314 = { "RBTreeUpLink.vm.dep" , OBJ_PATH+"/RBTreeUpLink.vm.dep" } ;
Rule rvdcpp314 = { {&dcpp314} , {&vdcpp314} , {&exedcpp314} } ;
Exe exedcpp314 = { "CC-VM-DEP RBTreeUpLink.cpp" , VMDEP , { OBJ_PATH+"/RBTreeUpLink.dep" , OBJ_PATH+"/RBTreeUpLink.vm.dep" , "314" } } ;

Target cpp315 = { "RadixHeap.cpp" , "../../Fundamental/CCore/src/RadixHeap.cpp" } ;
Target dcpp315 = { "RadixHeap.dep" , OBJ_PATH+"/RadixHeap.dep" } ;
Rule rdcpp315 = { {&cpp315,&obj} , {&dcpp315} , {&execpp315} } ;
Exe execpp315 = { "CC-DEP RadixHeap.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/RadixHeap.o"
 ,"../../Fundamental/CCore/src/RadixHeap.cpp"
 ,"-MF"
 ,OBJ_PATH+"/RadixHeap.dep"
} } ;

Target vdcpp315 = { "RadixHeap.vm.dep" , OBJ_PATH+"/RadixHeap.vm.dep" } ;
Rule rvdcpp315 = { {&dcpp315} , {&vdcpp315} , {&exedcpp315} } ;
Exe exedcpp315 = { "CC-VM-DEP RadixHeap.cpp" , VMDEP , { OBJ_PATH+"/RadixHeap.dep" , OBJ_PATH+"/RadixHeap.vm.dep" , "315" } } ;

Target cpp316 = { "Random.cpp" , "../../Fundamental/CCore/src/Random.cpp" } ;
Target dcpp316 = { "Random.dep" , OBJ_PATH+"/Random.dep" } ;
Rule rdcpp316 = { {&cpp316,&obj} , {&dcpp316} , {&execpp316} } ;
Exe execpp316 = { "CC-DEP Random.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Random.o"
 ,"../../Fundamental/CCore/src/Random.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Random.dep"
} } ;

Target vdcpp316 = { "Random.vm.dep" , OBJ_PATH+"/Random.vm.dep" } ;
Rule rvdcpp316 = { {&dcpp316} , {&vdcpp316} , {&exedcpp316} } ;
Exe exedcpp316 = { "CC-VM-DEP Random.cpp" , VMDEP , { OBJ_PATH+"/Random.dep" , OBJ_PATH+"/Random.vm.dep" , "316" } } ;

Target cpp317 = { "RangeDel.cpp" , "../../Simple/CCore/src/RangeDel.cpp" } ;
Target dcpp317 = { "RangeDel.dep" , OBJ_PATH+"/RangeDel.dep" } ;
Rule rdcpp317 = { {&cpp317,&obj} , {&dcpp317} , {&execpp317} } ;
Exe execpp317 = { "CC-DEP RangeDel.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/RangeDel.o"
 ,"../../Simple/CCore/src/RangeDel.cpp"
 ,"-MF"
 ,OBJ_PATH+"/RangeDel.dep"
} } ;

Target vdcpp317 = { "RangeDel.vm.dep" , OBJ_PATH+"/RangeDel.vm.dep" } ;
Rule rvdcpp317 = { {&dcpp317} , {&vdcpp317} , {&exedcpp317} } ;
Exe exedcpp317 = { "CC-VM-DEP RangeDel.cpp" , VMDEP , { OBJ_PATH+"/RangeDel.dep" , OBJ_PATH+"/RangeDel.vm.dep" , "317" } } ;

Target cpp318 = { "RatioEdit.cpp" , "../../Desktop/Lib/CCore/src/./video/pref/RatioEdit.cpp" } ;
Target dcpp318 = { "RatioEdit.dep" , OBJ_PATH+"/RatioEdit.dep" } ;
Rule rdcpp318 = { {&cpp318,&obj} , {&dcpp318} , {&execpp318} } ;
Exe execpp318 = { "CC-DEP RatioEdit.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/RatioEdit.o"
 ,"../../Desktop/Lib/CCore/src/./video/pref/RatioEdit.cpp"
 ,"-MF"
 ,OBJ_PATH+"/RatioEdit.dep"
} } ;

Target vdcpp318 = { "RatioEdit.vm.dep" , OBJ_PATH+"/RatioEdit.vm.dep" } ;
Rule rvdcpp318 = { {&dcpp318} , {&vdcpp318} , {&exedcpp318} } ;
Exe exedcpp318 = { "CC-VM-DEP RatioEdit.cpp" , VMDEP , { OBJ_PATH+"/RatioEdit.dep" , OBJ_PATH+"/RatioEdit.vm.dep" , "318" } } ;

Target cpp319 = { "RawFileToRead.cpp" , "../../HCore/CCore/src/RawFileToRead.cpp" } ;
Target dcpp319 = { "RawFileToRead.dep" , OBJ_PATH+"/RawFileToRead.dep" } ;
Rule rdcpp319 = { {&cpp319,&obj} , {&dcpp319} , {&execpp319} } ;
Exe execpp319 = { "CC-DEP RawFileToRead.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/RawFileToRead.o"
 ,"../../HCore/CCore/src/RawFileToRead.cpp"
 ,"-MF"
 ,OBJ_PATH+"/RawFileToRead.dep"
} } ;

Target vdcpp319 = { "RawFileToRead.vm.dep" , OBJ_PATH+"/RawFileToRead.vm.dep" } ;
Rule rvdcpp319 = { {&dcpp319} , {&vdcpp319} , {&exedcpp319} } ;
Exe exedcpp319 = { "CC-VM-DEP RawFileToRead.cpp" , VMDEP , { OBJ_PATH+"/RawFileToRead.dep" , OBJ_PATH+"/RawFileToRead.vm.dep" , "319" } } ;

Target cpp320 = { "ReadCon.cpp" , "../../HCore/CCore/src/ReadCon.cpp" } ;
Target dcpp320 = { "ReadCon.dep" , OBJ_PATH+"/ReadCon.dep" } ;
Rule rdcpp320 = { {&cpp320,&obj} , {&dcpp320} , {&execpp320} } ;
Exe execpp320 = { "CC-DEP ReadCon.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ReadCon.o"
 ,"../../HCore/CCore/src/ReadCon.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ReadCon.dep"
} } ;

Target vdcpp320 = { "ReadCon.vm.dep" , OBJ_PATH+"/ReadCon.vm.dep" } ;
Rule rvdcpp320 = { {&dcpp320} , {&vdcpp320} , {&exedcpp320} } ;
Exe exedcpp320 = { "CC-VM-DEP ReadCon.cpp" , VMDEP , { OBJ_PATH+"/ReadCon.dep" , OBJ_PATH+"/ReadCon.vm.dep" , "320" } } ;

Target cpp321 = { "ReadConType.cpp" , "../../Fundamental/CCore/src/ReadConType.cpp" } ;
Target dcpp321 = { "ReadConType.dep" , OBJ_PATH+"/ReadConType.dep" } ;
Rule rdcpp321 = { {&cpp321,&obj} , {&dcpp321} , {&execpp321} } ;
Exe execpp321 = { "CC-DEP ReadConType.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ReadConType.o"
 ,"../../Fundamental/CCore/src/ReadConType.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ReadConType.dep"
} } ;

Target vdcpp321 = { "ReadConType.vm.dep" , OBJ_PATH+"/ReadConType.vm.dep" } ;
Rule rvdcpp321 = { {&dcpp321} , {&vdcpp321} , {&exedcpp321} } ;
Exe exedcpp321 = { "CC-VM-DEP ReadConType.cpp" , VMDEP , { OBJ_PATH+"/ReadConType.dep" , OBJ_PATH+"/ReadConType.vm.dep" , "321" } } ;

Target cpp322 = { "RefArray.cpp" , "../../Fundamental/CCore/src/./array/RefArray.cpp" } ;
Target dcpp322 = { "RefArray.dep" , OBJ_PATH+"/RefArray.dep" } ;
Rule rdcpp322 = { {&cpp322,&obj} , {&dcpp322} , {&execpp322} } ;
Exe execpp322 = { "CC-DEP RefArray.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/RefArray.o"
 ,"../../Fundamental/CCore/src/./array/RefArray.cpp"
 ,"-MF"
 ,OBJ_PATH+"/RefArray.dep"
} } ;

Target vdcpp322 = { "RefArray.vm.dep" , OBJ_PATH+"/RefArray.vm.dep" } ;
Rule rvdcpp322 = { {&dcpp322} , {&vdcpp322} , {&exedcpp322} } ;
Exe exedcpp322 = { "CC-VM-DEP RefArray.cpp" , VMDEP , { OBJ_PATH+"/RefArray.dep" , OBJ_PATH+"/RefArray.vm.dep" , "322" } } ;

Target cpp323 = { "RefObjectBase.cpp" , "../../Simple/CCore/src/RefObjectBase.cpp" } ;
Target dcpp323 = { "RefObjectBase.dep" , OBJ_PATH+"/RefObjectBase.dep" } ;
Rule rdcpp323 = { {&cpp323,&obj} , {&dcpp323} , {&execpp323} } ;
Exe execpp323 = { "CC-DEP RefObjectBase.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/RefObjectBase.o"
 ,"../../Simple/CCore/src/RefObjectBase.cpp"
 ,"-MF"
 ,OBJ_PATH+"/RefObjectBase.dep"
} } ;

Target vdcpp323 = { "RefObjectBase.vm.dep" , OBJ_PATH+"/RefObjectBase.vm.dep" } ;
Rule rvdcpp323 = { {&dcpp323} , {&vdcpp323} , {&exedcpp323} } ;
Exe exedcpp323 = { "CC-VM-DEP RefObjectBase.cpp" , VMDEP , { OBJ_PATH+"/RefObjectBase.dep" , OBJ_PATH+"/RefObjectBase.vm.dep" , "323" } } ;

Target cpp324 = { "RefPtr.cpp" , "../../Simple/CCore/src/RefPtr.cpp" } ;
Target dcpp324 = { "RefPtr.dep" , OBJ_PATH+"/RefPtr.dep" } ;
Rule rdcpp324 = { {&cpp324,&obj} , {&dcpp324} , {&execpp324} } ;
Exe execpp324 = { "CC-DEP RefPtr.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/RefPtr.o"
 ,"../../Simple/CCore/src/RefPtr.cpp"
 ,"-MF"
 ,OBJ_PATH+"/RefPtr.dep"
} } ;

Target vdcpp324 = { "RefPtr.vm.dep" , OBJ_PATH+"/RefPtr.vm.dep" } ;
Rule rvdcpp324 = { {&dcpp324} , {&vdcpp324} , {&exedcpp324} } ;
Exe exedcpp324 = { "CC-VM-DEP RefPtr.cpp" , VMDEP , { OBJ_PATH+"/RefPtr.dep" , OBJ_PATH+"/RefPtr.vm.dep" , "324" } } ;

Target cpp325 = { "RefVal.cpp" , "../../Desktop/Core/CCore/src/./video/RefVal.cpp" } ;
Target dcpp325 = { "RefVal.dep" , OBJ_PATH+"/RefVal.dep" } ;
Rule rdcpp325 = { {&cpp325,&obj} , {&dcpp325} , {&execpp325} } ;
Exe execpp325 = { "CC-DEP RefVal.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/RefVal.o"
 ,"../../Desktop/Core/CCore/src/./video/RefVal.cpp"
 ,"-MF"
 ,OBJ_PATH+"/RefVal.dep"
} } ;

Target vdcpp325 = { "RefVal.vm.dep" , OBJ_PATH+"/RefVal.vm.dep" } ;
Rule rvdcpp325 = { {&dcpp325} , {&vdcpp325} , {&exedcpp325} } ;
Exe exedcpp325 = { "CC-VM-DEP RefVal.cpp" , VMDEP , { OBJ_PATH+"/RefVal.dep" , OBJ_PATH+"/RefVal.vm.dep" , "325" } } ;

Target cpp326 = { "Replace.cpp" , "../../Simple/CCore/src/./gadget/Replace.cpp" } ;
Target dcpp326 = { "Replace.dep" , OBJ_PATH+"/Replace.dep" } ;
Rule rdcpp326 = { {&cpp326,&obj} , {&dcpp326} , {&execpp326} } ;
Exe execpp326 = { "CC-DEP Replace.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Replace.o"
 ,"../../Simple/CCore/src/./gadget/Replace.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Replace.dep"
} } ;

Target vdcpp326 = { "Replace.vm.dep" , OBJ_PATH+"/Replace.vm.dep" } ;
Rule rvdcpp326 = { {&dcpp326} , {&vdcpp326} , {&exedcpp326} } ;
Exe exedcpp326 = { "CC-VM-DEP Replace.cpp" , VMDEP , { OBJ_PATH+"/Replace.dep" , OBJ_PATH+"/Replace.vm.dep" , "326" } } ;

Target cpp327 = { "ResSem.cpp" , "../../HCore/CCore/src/./task/ResSem.cpp" } ;
Target dcpp327 = { "ResSem.dep" , OBJ_PATH+"/ResSem.dep" } ;
Rule rdcpp327 = { {&cpp327,&obj} , {&dcpp327} , {&execpp327} } ;
Exe execpp327 = { "CC-DEP ResSem.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ResSem.o"
 ,"../../HCore/CCore/src/./task/ResSem.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ResSem.dep"
} } ;

Target vdcpp327 = { "ResSem.vm.dep" , OBJ_PATH+"/ResSem.vm.dep" } ;
Rule rvdcpp327 = { {&dcpp327} , {&vdcpp327} , {&exedcpp327} } ;
Exe exedcpp327 = { "CC-VM-DEP ResSem.cpp" , VMDEP , { OBJ_PATH+"/ResSem.dep" , OBJ_PATH+"/ResSem.vm.dep" , "327" } } ;

Target cpp328 = { "Rot.cpp" , "../../Applied/CCore/src/./crypton/Rot.cpp" } ;
Target dcpp328 = { "Rot.dep" , OBJ_PATH+"/Rot.dep" } ;
Rule rdcpp328 = { {&cpp328,&obj} , {&dcpp328} , {&execpp328} } ;
Exe execpp328 = { "CC-DEP Rot.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Rot.o"
 ,"../../Applied/CCore/src/./crypton/Rot.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Rot.dep"
} } ;

Target vdcpp328 = { "Rot.vm.dep" , OBJ_PATH+"/Rot.vm.dep" } ;
Rule rvdcpp328 = { {&dcpp328} , {&vdcpp328} , {&exedcpp328} } ;
Exe exedcpp328 = { "CC-VM-DEP Rot.cpp" , VMDEP , { OBJ_PATH+"/Rot.dep" , OBJ_PATH+"/Rot.vm.dep" , "328" } } ;

Target cpp329 = { "SHA.cpp" , "../../Applied/CCore/src/./crypton/SHA.cpp" } ;
Target dcpp329 = { "SHA.dep" , OBJ_PATH+"/SHA.dep" } ;
Rule rdcpp329 = { {&cpp329,&obj} , {&dcpp329} , {&execpp329} } ;
Exe execpp329 = { "CC-DEP SHA.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SHA.o"
 ,"../../Applied/CCore/src/./crypton/SHA.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SHA.dep"
} } ;

Target vdcpp329 = { "SHA.vm.dep" , OBJ_PATH+"/SHA.vm.dep" } ;
Rule rvdcpp329 = { {&dcpp329} , {&vdcpp329} , {&exedcpp329} } ;
Exe exedcpp329 = { "CC-VM-DEP SHA.cpp" , VMDEP , { OBJ_PATH+"/SHA.dep" , OBJ_PATH+"/SHA.vm.dep" , "329" } } ;

Target cpp330 = { "SIntFunc.cpp" , "../../Simple/CCore/src/./gadget/SIntFunc.cpp" } ;
Target dcpp330 = { "SIntFunc.dep" , OBJ_PATH+"/SIntFunc.dep" } ;
Rule rdcpp330 = { {&cpp330,&obj} , {&dcpp330} , {&execpp330} } ;
Exe execpp330 = { "CC-DEP SIntFunc.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SIntFunc.o"
 ,"../../Simple/CCore/src/./gadget/SIntFunc.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SIntFunc.dep"
} } ;

Target vdcpp330 = { "SIntFunc.vm.dep" , OBJ_PATH+"/SIntFunc.vm.dep" } ;
Rule rvdcpp330 = { {&dcpp330} , {&vdcpp330} , {&exedcpp330} } ;
Exe exedcpp330 = { "CC-VM-DEP SIntFunc.cpp" , VMDEP , { OBJ_PATH+"/SIntFunc.dep" , OBJ_PATH+"/SIntFunc.vm.dep" , "330" } } ;

Target cpp331 = { "SafeBuf.cpp" , "../../Simple/CCore/src/SafeBuf.cpp" } ;
Target dcpp331 = { "SafeBuf.dep" , OBJ_PATH+"/SafeBuf.dep" } ;
Rule rdcpp331 = { {&cpp331,&obj} , {&dcpp331} , {&execpp331} } ;
Exe execpp331 = { "CC-DEP SafeBuf.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SafeBuf.o"
 ,"../../Simple/CCore/src/SafeBuf.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SafeBuf.dep"
} } ;

Target vdcpp331 = { "SafeBuf.vm.dep" , OBJ_PATH+"/SafeBuf.vm.dep" } ;
Rule rvdcpp331 = { {&dcpp331} , {&vdcpp331} , {&exedcpp331} } ;
Exe exedcpp331 = { "CC-VM-DEP SafeBuf.cpp" , VMDEP , { OBJ_PATH+"/SafeBuf.dep" , OBJ_PATH+"/SafeBuf.vm.dep" , "331" } } ;

Target cpp332 = { "SaveLoad.cpp" , "../../Fundamental/CCore/src/SaveLoad.cpp" } ;
Target dcpp332 = { "SaveLoad.dep" , OBJ_PATH+"/SaveLoad.dep" } ;
Rule rdcpp332 = { {&cpp332,&obj} , {&dcpp332} , {&execpp332} } ;
Exe execpp332 = { "CC-DEP SaveLoad.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SaveLoad.o"
 ,"../../Fundamental/CCore/src/SaveLoad.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SaveLoad.dep"
} } ;

Target vdcpp332 = { "SaveLoad.vm.dep" , OBJ_PATH+"/SaveLoad.vm.dep" } ;
Rule rvdcpp332 = { {&dcpp332} , {&vdcpp332} , {&exedcpp332} } ;
Exe exedcpp332 = { "CC-VM-DEP SaveLoad.cpp" , VMDEP , { OBJ_PATH+"/SaveLoad.dep" , OBJ_PATH+"/SaveLoad.vm.dep" , "332" } } ;

Target cpp333 = { "Scan.cpp" , "../../HCore/CCore/src/Scan.cpp" } ;
Target dcpp333 = { "Scan.dep" , OBJ_PATH+"/Scan.dep" } ;
Rule rdcpp333 = { {&cpp333,&obj} , {&dcpp333} , {&execpp333} } ;
Exe execpp333 = { "CC-DEP Scan.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Scan.o"
 ,"../../HCore/CCore/src/Scan.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Scan.dep"
} } ;

Target vdcpp333 = { "Scan.vm.dep" , OBJ_PATH+"/Scan.vm.dep" } ;
Rule rvdcpp333 = { {&dcpp333} , {&vdcpp333} , {&exedcpp333} } ;
Exe exedcpp333 = { "CC-VM-DEP Scan.cpp" , VMDEP , { OBJ_PATH+"/Scan.dep" , OBJ_PATH+"/Scan.vm.dep" , "333" } } ;

Target cpp334 = { "ScanAsyncFile.cpp" , "../../Applied/CCore/src/./scan/ScanAsyncFile.cpp" } ;
Target dcpp334 = { "ScanAsyncFile.dep" , OBJ_PATH+"/ScanAsyncFile.dep" } ;
Rule rdcpp334 = { {&cpp334,&obj} , {&dcpp334} , {&execpp334} } ;
Exe execpp334 = { "CC-DEP ScanAsyncFile.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ScanAsyncFile.o"
 ,"../../Applied/CCore/src/./scan/ScanAsyncFile.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ScanAsyncFile.dep"
} } ;

Target vdcpp334 = { "ScanAsyncFile.vm.dep" , OBJ_PATH+"/ScanAsyncFile.vm.dep" } ;
Rule rvdcpp334 = { {&dcpp334} , {&vdcpp334} , {&exedcpp334} } ;
Exe exedcpp334 = { "CC-VM-DEP ScanAsyncFile.cpp" , VMDEP , { OBJ_PATH+"/ScanAsyncFile.dep" , OBJ_PATH+"/ScanAsyncFile.vm.dep" , "334" } } ;

Target cpp335 = { "ScanBase.cpp" , "../../Fundamental/CCore/src/./scanf/ScanBase.cpp" } ;
Target dcpp335 = { "ScanBase.dep" , OBJ_PATH+"/ScanBase.dep" } ;
Rule rdcpp335 = { {&cpp335,&obj} , {&dcpp335} , {&execpp335} } ;
Exe execpp335 = { "CC-DEP ScanBase.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ScanBase.o"
 ,"../../Fundamental/CCore/src/./scanf/ScanBase.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ScanBase.dep"
} } ;

Target vdcpp335 = { "ScanBase.vm.dep" , OBJ_PATH+"/ScanBase.vm.dep" } ;
Rule rvdcpp335 = { {&dcpp335} , {&vdcpp335} , {&exedcpp335} } ;
Exe exedcpp335 = { "CC-VM-DEP ScanBase.cpp" , VMDEP , { OBJ_PATH+"/ScanBase.dep" , OBJ_PATH+"/ScanBase.vm.dep" , "335" } } ;

Target cpp336 = { "ScanBit.cpp" , "../../Simple/CCore/src/ScanBit.cpp" } ;
Target dcpp336 = { "ScanBit.dep" , OBJ_PATH+"/ScanBit.dep" } ;
Rule rdcpp336 = { {&cpp336,&obj} , {&dcpp336} , {&execpp336} } ;
Exe execpp336 = { "CC-DEP ScanBit.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ScanBit.o"
 ,"../../Simple/CCore/src/ScanBit.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ScanBit.dep"
} } ;

Target vdcpp336 = { "ScanBit.vm.dep" , OBJ_PATH+"/ScanBit.vm.dep" } ;
Rule rvdcpp336 = { {&dcpp336} , {&vdcpp336} , {&exedcpp336} } ;
Exe exedcpp336 = { "CC-VM-DEP ScanBit.cpp" , VMDEP , { OBJ_PATH+"/ScanBit.dep" , OBJ_PATH+"/ScanBit.vm.dep" , "336" } } ;

Target cpp337 = { "ScanFile.cpp" , "../../HCore/CCore/src/./scan/ScanFile.cpp" } ;
Target dcpp337 = { "ScanFile.dep" , OBJ_PATH+"/ScanFile.dep" } ;
Rule rdcpp337 = { {&cpp337,&obj} , {&dcpp337} , {&execpp337} } ;
Exe execpp337 = { "CC-DEP ScanFile.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ScanFile.o"
 ,"../../HCore/CCore/src/./scan/ScanFile.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ScanFile.dep"
} } ;

Target vdcpp337 = { "ScanFile.vm.dep" , OBJ_PATH+"/ScanFile.vm.dep" } ;
Rule rvdcpp337 = { {&dcpp337} , {&vdcpp337} , {&exedcpp337} } ;
Exe exedcpp337 = { "CC-VM-DEP ScanFile.cpp" , VMDEP , { OBJ_PATH+"/ScanFile.dep" , OBJ_PATH+"/ScanFile.vm.dep" , "337" } } ;

Target cpp338 = { "ScanProxy.cpp" , "../../Fundamental/CCore/src/./scanf/ScanProxy.cpp" } ;
Target dcpp338 = { "ScanProxy.dep" , OBJ_PATH+"/ScanProxy.dep" } ;
Rule rdcpp338 = { {&cpp338,&obj} , {&dcpp338} , {&execpp338} } ;
Exe execpp338 = { "CC-DEP ScanProxy.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ScanProxy.o"
 ,"../../Fundamental/CCore/src/./scanf/ScanProxy.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ScanProxy.dep"
} } ;

Target vdcpp338 = { "ScanProxy.vm.dep" , OBJ_PATH+"/ScanProxy.vm.dep" } ;
Rule rvdcpp338 = { {&dcpp338} , {&vdcpp338} , {&exedcpp338} } ;
Exe exedcpp338 = { "CC-VM-DEP ScanProxy.cpp" , VMDEP , { OBJ_PATH+"/ScanProxy.dep" , OBJ_PATH+"/ScanProxy.vm.dep" , "338" } } ;

Target cpp339 = { "ScanRange.cpp" , "../../Simple/CCore/src/ScanRange.cpp" } ;
Target dcpp339 = { "ScanRange.dep" , OBJ_PATH+"/ScanRange.dep" } ;
Rule rdcpp339 = { {&cpp339,&obj} , {&dcpp339} , {&execpp339} } ;
Exe execpp339 = { "CC-DEP ScanRange.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ScanRange.o"
 ,"../../Simple/CCore/src/ScanRange.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ScanRange.dep"
} } ;

Target vdcpp339 = { "ScanRange.vm.dep" , OBJ_PATH+"/ScanRange.vm.dep" } ;
Rule rvdcpp339 = { {&dcpp339} , {&vdcpp339} , {&exedcpp339} } ;
Exe exedcpp339 = { "CC-VM-DEP ScanRange.cpp" , VMDEP , { OBJ_PATH+"/ScanRange.dep" , OBJ_PATH+"/ScanRange.vm.dep" , "339" } } ;

Target cpp340 = { "ScanTools.cpp" , "../../Fundamental/CCore/src/./scanf/ScanTools.cpp" } ;
Target dcpp340 = { "ScanTools.dep" , OBJ_PATH+"/ScanTools.dep" } ;
Rule rdcpp340 = { {&cpp340,&obj} , {&dcpp340} , {&execpp340} } ;
Exe execpp340 = { "CC-DEP ScanTools.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ScanTools.o"
 ,"../../Fundamental/CCore/src/./scanf/ScanTools.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ScanTools.dep"
} } ;

Target vdcpp340 = { "ScanTools.vm.dep" , OBJ_PATH+"/ScanTools.vm.dep" } ;
Rule rvdcpp340 = { {&dcpp340} , {&vdcpp340} , {&exedcpp340} } ;
Exe exedcpp340 = { "CC-VM-DEP ScanTools.cpp" , VMDEP , { OBJ_PATH+"/ScanTools.dep" , OBJ_PATH+"/ScanTools.vm.dep" , "340" } } ;

Target cpp341 = { "Scanf.cpp" , "../../Fundamental/CCore/src/Scanf.cpp" } ;
Target dcpp341 = { "Scanf.dep" , OBJ_PATH+"/Scanf.dep" } ;
Rule rdcpp341 = { {&cpp341,&obj} , {&dcpp341} , {&execpp341} } ;
Exe execpp341 = { "CC-DEP Scanf.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Scanf.o"
 ,"../../Fundamental/CCore/src/Scanf.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Scanf.dep"
} } ;

Target vdcpp341 = { "Scanf.vm.dep" , OBJ_PATH+"/Scanf.vm.dep" } ;
Rule rvdcpp341 = { {&dcpp341} , {&vdcpp341} , {&exedcpp341} } ;
Exe exedcpp341 = { "CC-VM-DEP Scanf.cpp" , VMDEP , { OBJ_PATH+"/Scanf.dep" , OBJ_PATH+"/Scanf.vm.dep" , "341" } } ;

Target cpp342 = { "Scope.cpp" , "../../Fundamental/CCore/src/Scope.cpp" } ;
Target dcpp342 = { "Scope.dep" , OBJ_PATH+"/Scope.dep" } ;
Rule rdcpp342 = { {&cpp342,&obj} , {&dcpp342} , {&execpp342} } ;
Exe execpp342 = { "CC-DEP Scope.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Scope.o"
 ,"../../Fundamental/CCore/src/Scope.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Scope.dep"
} } ;

Target vdcpp342 = { "Scope.vm.dep" , OBJ_PATH+"/Scope.vm.dep" } ;
Rule rvdcpp342 = { {&dcpp342} , {&vdcpp342} , {&exedcpp342} } ;
Exe exedcpp342 = { "CC-VM-DEP Scope.cpp" , VMDEP , { OBJ_PATH+"/Scope.dep" , OBJ_PATH+"/Scope.vm.dep" , "342" } } ;

Target cpp343 = { "ScopeGuard.cpp" , "../../Simple/CCore/src/./gadget/ScopeGuard.cpp" } ;
Target dcpp343 = { "ScopeGuard.dep" , OBJ_PATH+"/ScopeGuard.dep" } ;
Rule rdcpp343 = { {&cpp343,&obj} , {&dcpp343} , {&execpp343} } ;
Exe execpp343 = { "CC-DEP ScopeGuard.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ScopeGuard.o"
 ,"../../Simple/CCore/src/./gadget/ScopeGuard.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ScopeGuard.dep"
} } ;

Target vdcpp343 = { "ScopeGuard.vm.dep" , OBJ_PATH+"/ScopeGuard.vm.dep" } ;
Rule rvdcpp343 = { {&dcpp343} , {&vdcpp343} , {&exedcpp343} } ;
Exe exedcpp343 = { "CC-VM-DEP ScopeGuard.cpp" , VMDEP , { OBJ_PATH+"/ScopeGuard.dep" , OBJ_PATH+"/ScopeGuard.vm.dep" , "343" } } ;

Target cpp344 = { "SelectFrames.cpp" , "../../Desktop/Lib/CCore/src/./video/book/SelectFrames.cpp" } ;
Target dcpp344 = { "SelectFrames.dep" , OBJ_PATH+"/SelectFrames.dep" } ;
Rule rdcpp344 = { {&cpp344,&obj} , {&dcpp344} , {&execpp344} } ;
Exe execpp344 = { "CC-DEP SelectFrames.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SelectFrames.o"
 ,"../../Desktop/Lib/CCore/src/./video/book/SelectFrames.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SelectFrames.dep"
} } ;

Target vdcpp344 = { "SelectFrames.vm.dep" , OBJ_PATH+"/SelectFrames.vm.dep" } ;
Rule rvdcpp344 = { {&dcpp344} , {&vdcpp344} , {&exedcpp344} } ;
Exe exedcpp344 = { "CC-VM-DEP SelectFrames.cpp" , VMDEP , { OBJ_PATH+"/SelectFrames.dep" , OBJ_PATH+"/SelectFrames.vm.dep" , "344" } } ;

Target cpp345 = { "Sem.cpp" , "../../HCore/CCore/src/./task/Sem.cpp" } ;
Target dcpp345 = { "Sem.dep" , OBJ_PATH+"/Sem.dep" } ;
Rule rdcpp345 = { {&cpp345,&obj} , {&dcpp345} , {&execpp345} } ;
Exe execpp345 = { "CC-DEP Sem.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Sem.o"
 ,"../../HCore/CCore/src/./task/Sem.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Sem.dep"
} } ;

Target vdcpp345 = { "Sem.vm.dep" , OBJ_PATH+"/Sem.vm.dep" } ;
Rule rvdcpp345 = { {&dcpp345} , {&vdcpp345} , {&exedcpp345} } ;
Exe exedcpp345 = { "CC-VM-DEP Sem.cpp" , VMDEP , { OBJ_PATH+"/Sem.dep" , OBJ_PATH+"/Sem.vm.dep" , "345" } } ;

Target cpp346 = { "Shape.Button.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.Button.cpp" } ;
Target dcpp346 = { "Shape.Button.dep" , OBJ_PATH+"/Shape.Button.dep" } ;
Rule rdcpp346 = { {&cpp346,&obj} , {&dcpp346} , {&execpp346} } ;
Exe execpp346 = { "CC-DEP Shape.Button.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Shape.Button.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.Button.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Shape.Button.dep"
} } ;

Target vdcpp346 = { "Shape.Button.vm.dep" , OBJ_PATH+"/Shape.Button.vm.dep" } ;
Rule rvdcpp346 = { {&dcpp346} , {&vdcpp346} , {&exedcpp346} } ;
Exe exedcpp346 = { "CC-VM-DEP Shape.Button.cpp" , VMDEP , { OBJ_PATH+"/Shape.Button.dep" , OBJ_PATH+"/Shape.Button.vm.dep" , "346" } } ;

Target cpp347 = { "Shape.Check.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.Check.cpp" } ;
Target dcpp347 = { "Shape.Check.dep" , OBJ_PATH+"/Shape.Check.dep" } ;
Rule rdcpp347 = { {&cpp347,&obj} , {&dcpp347} , {&execpp347} } ;
Exe execpp347 = { "CC-DEP Shape.Check.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Shape.Check.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.Check.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Shape.Check.dep"
} } ;

Target vdcpp347 = { "Shape.Check.vm.dep" , OBJ_PATH+"/Shape.Check.vm.dep" } ;
Rule rvdcpp347 = { {&dcpp347} , {&vdcpp347} , {&exedcpp347} } ;
Exe exedcpp347 = { "CC-VM-DEP Shape.Check.cpp" , VMDEP , { OBJ_PATH+"/Shape.Check.dep" , OBJ_PATH+"/Shape.Check.vm.dep" , "347" } } ;

Target cpp348 = { "Shape.Contour.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.Contour.cpp" } ;
Target dcpp348 = { "Shape.Contour.dep" , OBJ_PATH+"/Shape.Contour.dep" } ;
Rule rdcpp348 = { {&cpp348,&obj} , {&dcpp348} , {&execpp348} } ;
Exe execpp348 = { "CC-DEP Shape.Contour.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Shape.Contour.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.Contour.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Shape.Contour.dep"
} } ;

Target vdcpp348 = { "Shape.Contour.vm.dep" , OBJ_PATH+"/Shape.Contour.vm.dep" } ;
Rule rvdcpp348 = { {&dcpp348} , {&vdcpp348} , {&exedcpp348} } ;
Exe exedcpp348 = { "CC-VM-DEP Shape.Contour.cpp" , VMDEP , { OBJ_PATH+"/Shape.Contour.dep" , OBJ_PATH+"/Shape.Contour.vm.dep" , "348" } } ;

Target cpp349 = { "Shape.DragFrame.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.DragFrame.cpp" } ;
Target dcpp349 = { "Shape.DragFrame.dep" , OBJ_PATH+"/Shape.DragFrame.dep" } ;
Rule rdcpp349 = { {&cpp349,&obj} , {&dcpp349} , {&execpp349} } ;
Exe execpp349 = { "CC-DEP Shape.DragFrame.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Shape.DragFrame.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.DragFrame.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Shape.DragFrame.dep"
} } ;

Target vdcpp349 = { "Shape.DragFrame.vm.dep" , OBJ_PATH+"/Shape.DragFrame.vm.dep" } ;
Rule rvdcpp349 = { {&dcpp349} , {&vdcpp349} , {&exedcpp349} } ;
Exe exedcpp349 = { "CC-VM-DEP Shape.DragFrame.cpp" , VMDEP , { OBJ_PATH+"/Shape.DragFrame.dep" , OBJ_PATH+"/Shape.DragFrame.vm.dep" , "349" } } ;

Target cpp350 = { "Shape.FixedFrame.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.FixedFrame.cpp" } ;
Target dcpp350 = { "Shape.FixedFrame.dep" , OBJ_PATH+"/Shape.FixedFrame.dep" } ;
Rule rdcpp350 = { {&cpp350,&obj} , {&dcpp350} , {&execpp350} } ;
Exe execpp350 = { "CC-DEP Shape.FixedFrame.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Shape.FixedFrame.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.FixedFrame.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Shape.FixedFrame.dep"
} } ;

Target vdcpp350 = { "Shape.FixedFrame.vm.dep" , OBJ_PATH+"/Shape.FixedFrame.vm.dep" } ;
Rule rvdcpp350 = { {&dcpp350} , {&vdcpp350} , {&exedcpp350} } ;
Exe exedcpp350 = { "CC-VM-DEP Shape.FixedFrame.cpp" , VMDEP , { OBJ_PATH+"/Shape.FixedFrame.dep" , OBJ_PATH+"/Shape.FixedFrame.vm.dep" , "350" } } ;

Target cpp351 = { "Shape.FrameBase.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.FrameBase.cpp" } ;
Target dcpp351 = { "Shape.FrameBase.dep" , OBJ_PATH+"/Shape.FrameBase.dep" } ;
Rule rdcpp351 = { {&cpp351,&obj} , {&dcpp351} , {&execpp351} } ;
Exe execpp351 = { "CC-DEP Shape.FrameBase.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Shape.FrameBase.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.FrameBase.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Shape.FrameBase.dep"
} } ;

Target vdcpp351 = { "Shape.FrameBase.vm.dep" , OBJ_PATH+"/Shape.FrameBase.vm.dep" } ;
Rule rvdcpp351 = { {&dcpp351} , {&vdcpp351} , {&exedcpp351} } ;
Exe exedcpp351 = { "CC-VM-DEP Shape.FrameBase.cpp" , VMDEP , { OBJ_PATH+"/Shape.FrameBase.dep" , OBJ_PATH+"/Shape.FrameBase.vm.dep" , "351" } } ;

Target cpp352 = { "Shape.Info.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.Info.cpp" } ;
Target dcpp352 = { "Shape.Info.dep" , OBJ_PATH+"/Shape.Info.dep" } ;
Rule rdcpp352 = { {&cpp352,&obj} , {&dcpp352} , {&execpp352} } ;
Exe execpp352 = { "CC-DEP Shape.Info.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Shape.Info.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.Info.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Shape.Info.dep"
} } ;

Target vdcpp352 = { "Shape.Info.vm.dep" , OBJ_PATH+"/Shape.Info.vm.dep" } ;
Rule rvdcpp352 = { {&dcpp352} , {&vdcpp352} , {&exedcpp352} } ;
Exe exedcpp352 = { "CC-VM-DEP Shape.Info.cpp" , VMDEP , { OBJ_PATH+"/Shape.Info.dep" , OBJ_PATH+"/Shape.Info.vm.dep" , "352" } } ;

Target cpp353 = { "Shape.Label.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.Label.cpp" } ;
Target dcpp353 = { "Shape.Label.dep" , OBJ_PATH+"/Shape.Label.dep" } ;
Rule rdcpp353 = { {&cpp353,&obj} , {&dcpp353} , {&execpp353} } ;
Exe execpp353 = { "CC-DEP Shape.Label.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Shape.Label.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.Label.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Shape.Label.dep"
} } ;

Target vdcpp353 = { "Shape.Label.vm.dep" , OBJ_PATH+"/Shape.Label.vm.dep" } ;
Rule rvdcpp353 = { {&dcpp353} , {&vdcpp353} , {&exedcpp353} } ;
Exe exedcpp353 = { "CC-VM-DEP Shape.Label.cpp" , VMDEP , { OBJ_PATH+"/Shape.Label.dep" , OBJ_PATH+"/Shape.Label.vm.dep" , "353" } } ;

Target cpp354 = { "Shape.Light.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.Light.cpp" } ;
Target dcpp354 = { "Shape.Light.dep" , OBJ_PATH+"/Shape.Light.dep" } ;
Rule rdcpp354 = { {&cpp354,&obj} , {&dcpp354} , {&execpp354} } ;
Exe execpp354 = { "CC-DEP Shape.Light.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Shape.Light.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.Light.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Shape.Light.dep"
} } ;

Target vdcpp354 = { "Shape.Light.vm.dep" , OBJ_PATH+"/Shape.Light.vm.dep" } ;
Rule rvdcpp354 = { {&dcpp354} , {&vdcpp354} , {&exedcpp354} } ;
Exe exedcpp354 = { "CC-VM-DEP Shape.Light.cpp" , VMDEP , { OBJ_PATH+"/Shape.Light.dep" , OBJ_PATH+"/Shape.Light.vm.dep" , "354" } } ;

Target cpp355 = { "Shape.Line.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.Line.cpp" } ;
Target dcpp355 = { "Shape.Line.dep" , OBJ_PATH+"/Shape.Line.dep" } ;
Rule rdcpp355 = { {&cpp355,&obj} , {&dcpp355} , {&execpp355} } ;
Exe execpp355 = { "CC-DEP Shape.Line.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Shape.Line.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.Line.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Shape.Line.dep"
} } ;

Target vdcpp355 = { "Shape.Line.vm.dep" , OBJ_PATH+"/Shape.Line.vm.dep" } ;
Rule rvdcpp355 = { {&dcpp355} , {&vdcpp355} , {&exedcpp355} } ;
Exe exedcpp355 = { "CC-VM-DEP Shape.Line.cpp" , VMDEP , { OBJ_PATH+"/Shape.Line.dep" , OBJ_PATH+"/Shape.Line.vm.dep" , "355" } } ;

Target cpp356 = { "Shape.LineEdit.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.LineEdit.cpp" } ;
Target dcpp356 = { "Shape.LineEdit.dep" , OBJ_PATH+"/Shape.LineEdit.dep" } ;
Rule rdcpp356 = { {&cpp356,&obj} , {&dcpp356} , {&execpp356} } ;
Exe execpp356 = { "CC-DEP Shape.LineEdit.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Shape.LineEdit.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.LineEdit.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Shape.LineEdit.dep"
} } ;

Target vdcpp356 = { "Shape.LineEdit.vm.dep" , OBJ_PATH+"/Shape.LineEdit.vm.dep" } ;
Rule rvdcpp356 = { {&dcpp356} , {&vdcpp356} , {&exedcpp356} } ;
Exe exedcpp356 = { "CC-VM-DEP Shape.LineEdit.cpp" , VMDEP , { OBJ_PATH+"/Shape.LineEdit.dep" , OBJ_PATH+"/Shape.LineEdit.vm.dep" , "356" } } ;

Target cpp357 = { "Shape.Progress.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.Progress.cpp" } ;
Target dcpp357 = { "Shape.Progress.dep" , OBJ_PATH+"/Shape.Progress.dep" } ;
Rule rdcpp357 = { {&cpp357,&obj} , {&dcpp357} , {&execpp357} } ;
Exe execpp357 = { "CC-DEP Shape.Progress.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Shape.Progress.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.Progress.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Shape.Progress.dep"
} } ;

Target vdcpp357 = { "Shape.Progress.vm.dep" , OBJ_PATH+"/Shape.Progress.vm.dep" } ;
Rule rvdcpp357 = { {&dcpp357} , {&vdcpp357} , {&exedcpp357} } ;
Exe exedcpp357 = { "CC-VM-DEP Shape.Progress.cpp" , VMDEP , { OBJ_PATH+"/Shape.Progress.dep" , OBJ_PATH+"/Shape.Progress.vm.dep" , "357" } } ;

Target cpp358 = { "Shape.Radio.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.Radio.cpp" } ;
Target dcpp358 = { "Shape.Radio.dep" , OBJ_PATH+"/Shape.Radio.dep" } ;
Rule rdcpp358 = { {&cpp358,&obj} , {&dcpp358} , {&execpp358} } ;
Exe execpp358 = { "CC-DEP Shape.Radio.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Shape.Radio.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.Radio.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Shape.Radio.dep"
} } ;

Target vdcpp358 = { "Shape.Radio.vm.dep" , OBJ_PATH+"/Shape.Radio.vm.dep" } ;
Rule rvdcpp358 = { {&dcpp358} , {&vdcpp358} , {&exedcpp358} } ;
Exe exedcpp358 = { "CC-VM-DEP Shape.Radio.cpp" , VMDEP , { OBJ_PATH+"/Shape.Radio.dep" , OBJ_PATH+"/Shape.Radio.vm.dep" , "358" } } ;

Target cpp359 = { "Shape.RunButton.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.RunButton.cpp" } ;
Target dcpp359 = { "Shape.RunButton.dep" , OBJ_PATH+"/Shape.RunButton.dep" } ;
Rule rdcpp359 = { {&cpp359,&obj} , {&dcpp359} , {&execpp359} } ;
Exe execpp359 = { "CC-DEP Shape.RunButton.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Shape.RunButton.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.RunButton.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Shape.RunButton.dep"
} } ;

Target vdcpp359 = { "Shape.RunButton.vm.dep" , OBJ_PATH+"/Shape.RunButton.vm.dep" } ;
Rule rvdcpp359 = { {&dcpp359} , {&vdcpp359} , {&exedcpp359} } ;
Exe exedcpp359 = { "CC-VM-DEP Shape.RunButton.cpp" , VMDEP , { OBJ_PATH+"/Shape.RunButton.dep" , OBJ_PATH+"/Shape.RunButton.vm.dep" , "359" } } ;

Target cpp360 = { "Shape.Scroll.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.Scroll.cpp" } ;
Target dcpp360 = { "Shape.Scroll.dep" , OBJ_PATH+"/Shape.Scroll.dep" } ;
Rule rdcpp360 = { {&cpp360,&obj} , {&dcpp360} , {&execpp360} } ;
Exe execpp360 = { "CC-DEP Shape.Scroll.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Shape.Scroll.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.Scroll.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Shape.Scroll.dep"
} } ;

Target vdcpp360 = { "Shape.Scroll.vm.dep" , OBJ_PATH+"/Shape.Scroll.vm.dep" } ;
Rule rvdcpp360 = { {&dcpp360} , {&vdcpp360} , {&exedcpp360} } ;
Exe exedcpp360 = { "CC-VM-DEP Shape.Scroll.cpp" , VMDEP , { OBJ_PATH+"/Shape.Scroll.dep" , OBJ_PATH+"/Shape.Scroll.vm.dep" , "360" } } ;

Target cpp361 = { "Shape.ScrollList.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.ScrollList.cpp" } ;
Target dcpp361 = { "Shape.ScrollList.dep" , OBJ_PATH+"/Shape.ScrollList.dep" } ;
Rule rdcpp361 = { {&cpp361,&obj} , {&dcpp361} , {&execpp361} } ;
Exe execpp361 = { "CC-DEP Shape.ScrollList.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Shape.ScrollList.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.ScrollList.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Shape.ScrollList.dep"
} } ;

Target vdcpp361 = { "Shape.ScrollList.vm.dep" , OBJ_PATH+"/Shape.ScrollList.vm.dep" } ;
Rule rvdcpp361 = { {&dcpp361} , {&vdcpp361} , {&exedcpp361} } ;
Exe exedcpp361 = { "CC-VM-DEP Shape.ScrollList.cpp" , VMDEP , { OBJ_PATH+"/Shape.ScrollList.dep" , OBJ_PATH+"/Shape.ScrollList.vm.dep" , "361" } } ;

Target cpp362 = { "Shape.ShiftSwitch.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.ShiftSwitch.cpp" } ;
Target dcpp362 = { "Shape.ShiftSwitch.dep" , OBJ_PATH+"/Shape.ShiftSwitch.dep" } ;
Rule rdcpp362 = { {&cpp362,&obj} , {&dcpp362} , {&execpp362} } ;
Exe execpp362 = { "CC-DEP Shape.ShiftSwitch.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Shape.ShiftSwitch.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.ShiftSwitch.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Shape.ShiftSwitch.dep"
} } ;

Target vdcpp362 = { "Shape.ShiftSwitch.vm.dep" , OBJ_PATH+"/Shape.ShiftSwitch.vm.dep" } ;
Rule rvdcpp362 = { {&dcpp362} , {&vdcpp362} , {&exedcpp362} } ;
Exe exedcpp362 = { "CC-VM-DEP Shape.ShiftSwitch.cpp" , VMDEP , { OBJ_PATH+"/Shape.ShiftSwitch.dep" , OBJ_PATH+"/Shape.ShiftSwitch.vm.dep" , "362" } } ;

Target cpp363 = { "Shape.SimpleTextList.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.SimpleTextList.cpp" } ;
Target dcpp363 = { "Shape.SimpleTextList.dep" , OBJ_PATH+"/Shape.SimpleTextList.dep" } ;
Rule rdcpp363 = { {&cpp363,&obj} , {&dcpp363} , {&execpp363} } ;
Exe execpp363 = { "CC-DEP Shape.SimpleTextList.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Shape.SimpleTextList.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.SimpleTextList.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Shape.SimpleTextList.dep"
} } ;

Target vdcpp363 = { "Shape.SimpleTextList.vm.dep" , OBJ_PATH+"/Shape.SimpleTextList.vm.dep" } ;
Rule rvdcpp363 = { {&dcpp363} , {&vdcpp363} , {&exedcpp363} } ;
Exe exedcpp363 = { "CC-VM-DEP Shape.SimpleTextList.cpp" , VMDEP , { OBJ_PATH+"/Shape.SimpleTextList.dep" , OBJ_PATH+"/Shape.SimpleTextList.vm.dep" , "363" } } ;

Target cpp364 = { "Shape.Slider.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.Slider.cpp" } ;
Target dcpp364 = { "Shape.Slider.dep" , OBJ_PATH+"/Shape.Slider.dep" } ;
Rule rdcpp364 = { {&cpp364,&obj} , {&dcpp364} , {&execpp364} } ;
Exe execpp364 = { "CC-DEP Shape.Slider.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Shape.Slider.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.Slider.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Shape.Slider.dep"
} } ;

Target vdcpp364 = { "Shape.Slider.vm.dep" , OBJ_PATH+"/Shape.Slider.vm.dep" } ;
Rule rvdcpp364 = { {&dcpp364} , {&vdcpp364} , {&exedcpp364} } ;
Exe exedcpp364 = { "CC-VM-DEP Shape.Slider.cpp" , VMDEP , { OBJ_PATH+"/Shape.Slider.dep" , OBJ_PATH+"/Shape.Slider.vm.dep" , "364" } } ;

Target cpp365 = { "Shape.Spinor.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.Spinor.cpp" } ;
Target dcpp365 = { "Shape.Spinor.dep" , OBJ_PATH+"/Shape.Spinor.dep" } ;
Rule rdcpp365 = { {&cpp365,&obj} , {&dcpp365} , {&execpp365} } ;
Exe execpp365 = { "CC-DEP Shape.Spinor.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Shape.Spinor.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.Spinor.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Shape.Spinor.dep"
} } ;

Target vdcpp365 = { "Shape.Spinor.vm.dep" , OBJ_PATH+"/Shape.Spinor.vm.dep" } ;
Rule rvdcpp365 = { {&dcpp365} , {&vdcpp365} , {&exedcpp365} } ;
Exe exedcpp365 = { "CC-VM-DEP Shape.Spinor.cpp" , VMDEP , { OBJ_PATH+"/Shape.Spinor.dep" , OBJ_PATH+"/Shape.Spinor.vm.dep" , "365" } } ;

Target cpp366 = { "Shape.Split.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.Split.cpp" } ;
Target dcpp366 = { "Shape.Split.dep" , OBJ_PATH+"/Shape.Split.dep" } ;
Rule rdcpp366 = { {&cpp366,&obj} , {&dcpp366} , {&execpp366} } ;
Exe execpp366 = { "CC-DEP Shape.Split.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Shape.Split.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.Split.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Shape.Split.dep"
} } ;

Target vdcpp366 = { "Shape.Split.vm.dep" , OBJ_PATH+"/Shape.Split.vm.dep" } ;
Rule rvdcpp366 = { {&dcpp366} , {&vdcpp366} , {&exedcpp366} } ;
Exe exedcpp366 = { "CC-VM-DEP Shape.Split.cpp" , VMDEP , { OBJ_PATH+"/Shape.Split.dep" , OBJ_PATH+"/Shape.Split.vm.dep" , "366" } } ;

Target cpp367 = { "Shape.Switch.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.Switch.cpp" } ;
Target dcpp367 = { "Shape.Switch.dep" , OBJ_PATH+"/Shape.Switch.dep" } ;
Rule rdcpp367 = { {&cpp367,&obj} , {&dcpp367} , {&execpp367} } ;
Exe execpp367 = { "CC-DEP Shape.Switch.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Shape.Switch.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.Switch.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Shape.Switch.dep"
} } ;

Target vdcpp367 = { "Shape.Switch.vm.dep" , OBJ_PATH+"/Shape.Switch.vm.dep" } ;
Rule rvdcpp367 = { {&dcpp367} , {&vdcpp367} , {&exedcpp367} } ;
Exe exedcpp367 = { "CC-VM-DEP Shape.Switch.cpp" , VMDEP , { OBJ_PATH+"/Shape.Switch.dep" , OBJ_PATH+"/Shape.Switch.vm.dep" , "367" } } ;

Target cpp368 = { "Shape.Text.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.Text.cpp" } ;
Target dcpp368 = { "Shape.Text.dep" , OBJ_PATH+"/Shape.Text.dep" } ;
Rule rdcpp368 = { {&cpp368,&obj} , {&dcpp368} , {&execpp368} } ;
Exe execpp368 = { "CC-DEP Shape.Text.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Shape.Text.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.Text.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Shape.Text.dep"
} } ;

Target vdcpp368 = { "Shape.Text.vm.dep" , OBJ_PATH+"/Shape.Text.vm.dep" } ;
Rule rvdcpp368 = { {&dcpp368} , {&vdcpp368} , {&exedcpp368} } ;
Exe exedcpp368 = { "CC-VM-DEP Shape.Text.cpp" , VMDEP , { OBJ_PATH+"/Shape.Text.dep" , OBJ_PATH+"/Shape.Text.vm.dep" , "368" } } ;

Target cpp369 = { "Shape.TextLine.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Shape.TextLine.cpp" } ;
Target dcpp369 = { "Shape.TextLine.dep" , OBJ_PATH+"/Shape.TextLine.dep" } ;
Rule rdcpp369 = { {&cpp369,&obj} , {&dcpp369} , {&execpp369} } ;
Exe execpp369 = { "CC-DEP Shape.TextLine.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Shape.TextLine.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Shape.TextLine.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Shape.TextLine.dep"
} } ;

Target vdcpp369 = { "Shape.TextLine.vm.dep" , OBJ_PATH+"/Shape.TextLine.vm.dep" } ;
Rule rvdcpp369 = { {&dcpp369} , {&vdcpp369} , {&exedcpp369} } ;
Exe exedcpp369 = { "CC-VM-DEP Shape.TextLine.cpp" , VMDEP , { OBJ_PATH+"/Shape.TextLine.dep" , OBJ_PATH+"/Shape.TextLine.vm.dep" , "369" } } ;

Target cpp370 = { "ShapeLib.cpp" , "../../Desktop/Lib/CCore/src/./video/ShapeLib.cpp" } ;
Target dcpp370 = { "ShapeLib.dep" , OBJ_PATH+"/ShapeLib.dep" } ;
Rule rdcpp370 = { {&cpp370,&obj} , {&dcpp370} , {&execpp370} } ;
Exe execpp370 = { "CC-DEP ShapeLib.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ShapeLib.o"
 ,"../../Desktop/Lib/CCore/src/./video/ShapeLib.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ShapeLib.dep"
} } ;

Target vdcpp370 = { "ShapeLib.vm.dep" , OBJ_PATH+"/ShapeLib.vm.dep" } ;
Rule rvdcpp370 = { {&dcpp370} , {&vdcpp370} , {&exedcpp370} } ;
Exe exedcpp370 = { "CC-VM-DEP ShapeLib.cpp" , VMDEP , { OBJ_PATH+"/ShapeLib.dep" , OBJ_PATH+"/ShapeLib.vm.dep" , "370" } } ;

Target cpp371 = { "ShortSort.cpp" , "../../Fundamental/CCore/src/./sort/ShortSort.cpp" } ;
Target dcpp371 = { "ShortSort.dep" , OBJ_PATH+"/ShortSort.dep" } ;
Rule rdcpp371 = { {&cpp371,&obj} , {&dcpp371} , {&execpp371} } ;
Exe execpp371 = { "CC-DEP ShortSort.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ShortSort.o"
 ,"../../Fundamental/CCore/src/./sort/ShortSort.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ShortSort.dep"
} } ;

Target vdcpp371 = { "ShortSort.vm.dep" , OBJ_PATH+"/ShortSort.vm.dep" } ;
Rule rvdcpp371 = { {&dcpp371} , {&vdcpp371} , {&exedcpp371} } ;
Exe exedcpp371 = { "CC-VM-DEP ShortSort.cpp" , VMDEP , { OBJ_PATH+"/ShortSort.dep" , OBJ_PATH+"/ShortSort.vm.dep" , "371" } } ;

Target cpp372 = { "Signal.cpp" , "../../Fundamental/CCore/src/Signal.cpp" } ;
Target dcpp372 = { "Signal.dep" , OBJ_PATH+"/Signal.dep" } ;
Rule rdcpp372 = { {&cpp372,&obj} , {&dcpp372} , {&execpp372} } ;
Exe execpp372 = { "CC-DEP Signal.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Signal.o"
 ,"../../Fundamental/CCore/src/Signal.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Signal.dep"
} } ;

Target vdcpp372 = { "Signal.vm.dep" , OBJ_PATH+"/Signal.vm.dep" } ;
Rule rvdcpp372 = { {&dcpp372} , {&vdcpp372} , {&exedcpp372} } ;
Exe exedcpp372 = { "CC-VM-DEP Signal.cpp" , VMDEP , { OBJ_PATH+"/Signal.dep" , OBJ_PATH+"/Signal.vm.dep" , "372" } } ;

Target cpp373 = { "SimpleArray.cpp" , "../../Fundamental/CCore/src/./array/SimpleArray.cpp" } ;
Target dcpp373 = { "SimpleArray.dep" , OBJ_PATH+"/SimpleArray.dep" } ;
Rule rdcpp373 = { {&cpp373,&obj} , {&dcpp373} , {&execpp373} } ;
Exe execpp373 = { "CC-DEP SimpleArray.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SimpleArray.o"
 ,"../../Fundamental/CCore/src/./array/SimpleArray.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SimpleArray.dep"
} } ;

Target vdcpp373 = { "SimpleArray.vm.dep" , OBJ_PATH+"/SimpleArray.vm.dep" } ;
Rule rvdcpp373 = { {&dcpp373} , {&vdcpp373} , {&exedcpp373} } ;
Exe exedcpp373 = { "CC-VM-DEP SimpleArray.cpp" , VMDEP , { OBJ_PATH+"/SimpleArray.dep" , OBJ_PATH+"/SimpleArray.vm.dep" , "373" } } ;

Target cpp374 = { "SimpleConsole.cpp" , "../../Applied/CCore/src/./video/SimpleConsole.cpp" } ;
Target dcpp374 = { "SimpleConsole.dep" , OBJ_PATH+"/SimpleConsole.dep" } ;
Rule rdcpp374 = { {&cpp374,&obj} , {&dcpp374} , {&execpp374} } ;
Exe execpp374 = { "CC-DEP SimpleConsole.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SimpleConsole.o"
 ,"../../Applied/CCore/src/./video/SimpleConsole.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SimpleConsole.dep"
} } ;

Target vdcpp374 = { "SimpleConsole.vm.dep" , OBJ_PATH+"/SimpleConsole.vm.dep" } ;
Rule rvdcpp374 = { {&dcpp374} , {&vdcpp374} , {&exedcpp374} } ;
Exe exedcpp374 = { "CC-VM-DEP SimpleConsole.cpp" , VMDEP , { OBJ_PATH+"/SimpleConsole.dep" , OBJ_PATH+"/SimpleConsole.vm.dep" , "374" } } ;

Target cpp375 = { "SimpleRotate.cpp" , "../../Fundamental/CCore/src/./algon/SimpleRotate.cpp" } ;
Target dcpp375 = { "SimpleRotate.dep" , OBJ_PATH+"/SimpleRotate.dep" } ;
Rule rdcpp375 = { {&cpp375,&obj} , {&dcpp375} , {&execpp375} } ;
Exe execpp375 = { "CC-DEP SimpleRotate.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SimpleRotate.o"
 ,"../../Fundamental/CCore/src/./algon/SimpleRotate.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SimpleRotate.dep"
} } ;

Target vdcpp375 = { "SimpleRotate.vm.dep" , OBJ_PATH+"/SimpleRotate.vm.dep" } ;
Rule rvdcpp375 = { {&dcpp375} , {&vdcpp375} , {&exedcpp375} } ;
Exe exedcpp375 = { "CC-VM-DEP SimpleRotate.cpp" , VMDEP , { OBJ_PATH+"/SimpleRotate.dep" , OBJ_PATH+"/SimpleRotate.vm.dep" , "375" } } ;

Target cpp376 = { "SingleBridge.cpp" , "../../Applied/CCore/src/./net/SingleBridge.cpp" } ;
Target dcpp376 = { "SingleBridge.dep" , OBJ_PATH+"/SingleBridge.dep" } ;
Rule rdcpp376 = { {&cpp376,&obj} , {&dcpp376} , {&execpp376} } ;
Exe execpp376 = { "CC-DEP SingleBridge.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SingleBridge.o"
 ,"../../Applied/CCore/src/./net/SingleBridge.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SingleBridge.dep"
} } ;

Target vdcpp376 = { "SingleBridge.vm.dep" , OBJ_PATH+"/SingleBridge.vm.dep" } ;
Rule rvdcpp376 = { {&dcpp376} , {&vdcpp376} , {&exedcpp376} } ;
Exe exedcpp376 = { "CC-VM-DEP SingleBridge.cpp" , VMDEP , { OBJ_PATH+"/SingleBridge.dep" , OBJ_PATH+"/SingleBridge.vm.dep" , "376" } } ;

Target cpp377 = { "SingleEchoDevice.cpp" , "../../Applied/CCore/src/./net/SingleEchoDevice.cpp" } ;
Target dcpp377 = { "SingleEchoDevice.dep" , OBJ_PATH+"/SingleEchoDevice.dep" } ;
Rule rdcpp377 = { {&cpp377,&obj} , {&dcpp377} , {&execpp377} } ;
Exe execpp377 = { "CC-DEP SingleEchoDevice.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SingleEchoDevice.o"
 ,"../../Applied/CCore/src/./net/SingleEchoDevice.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SingleEchoDevice.dep"
} } ;

Target vdcpp377 = { "SingleEchoDevice.vm.dep" , OBJ_PATH+"/SingleEchoDevice.vm.dep" } ;
Rule rvdcpp377 = { {&dcpp377} , {&vdcpp377} , {&exedcpp377} } ;
Exe exedcpp377 = { "CC-VM-DEP SingleEchoDevice.cpp" , VMDEP , { OBJ_PATH+"/SingleEchoDevice.dep" , OBJ_PATH+"/SingleEchoDevice.vm.dep" , "377" } } ;

Target cpp378 = { "SingleHost.cpp" , "../../Fundamental/CCore/src/SingleHost.cpp" } ;
Target dcpp378 = { "SingleHost.dep" , OBJ_PATH+"/SingleHost.dep" } ;
Rule rdcpp378 = { {&cpp378,&obj} , {&dcpp378} , {&execpp378} } ;
Exe execpp378 = { "CC-DEP SingleHost.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SingleHost.o"
 ,"../../Fundamental/CCore/src/SingleHost.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SingleHost.dep"
} } ;

Target vdcpp378 = { "SingleHost.vm.dep" , OBJ_PATH+"/SingleHost.vm.dep" } ;
Rule rvdcpp378 = { {&dcpp378} , {&vdcpp378} , {&exedcpp378} } ;
Exe exedcpp378 = { "CC-VM-DEP SingleHost.cpp" , VMDEP , { OBJ_PATH+"/SingleHost.dep" , OBJ_PATH+"/SingleHost.vm.dep" , "378" } } ;

Target cpp379 = { "SlowSem.cpp" , "../../HCore/CCore/src/./task/SlowSem.cpp" } ;
Target dcpp379 = { "SlowSem.dep" , OBJ_PATH+"/SlowSem.dep" } ;
Rule rdcpp379 = { {&cpp379,&obj} , {&dcpp379} , {&execpp379} } ;
Exe execpp379 = { "CC-DEP SlowSem.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SlowSem.o"
 ,"../../HCore/CCore/src/./task/SlowSem.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SlowSem.dep"
} } ;

Target vdcpp379 = { "SlowSem.vm.dep" , OBJ_PATH+"/SlowSem.vm.dep" } ;
Rule rvdcpp379 = { {&dcpp379} , {&vdcpp379} , {&exedcpp379} } ;
Exe exedcpp379 = { "CC-VM-DEP SlowSem.cpp" , VMDEP , { OBJ_PATH+"/SlowSem.dep" , OBJ_PATH+"/SlowSem.vm.dep" , "379" } } ;

Target cpp380 = { "SmallPrimes.cpp" , "../../Applied/CCore/src/./math/SmallPrimes.cpp" } ;
Target dcpp380 = { "SmallPrimes.dep" , OBJ_PATH+"/SmallPrimes.dep" } ;
Rule rdcpp380 = { {&cpp380,&obj} , {&dcpp380} , {&execpp380} } ;
Exe execpp380 = { "CC-DEP SmallPrimes.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SmallPrimes.o"
 ,"../../Applied/CCore/src/./math/SmallPrimes.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SmallPrimes.dep"
} } ;

Target vdcpp380 = { "SmallPrimes.vm.dep" , OBJ_PATH+"/SmallPrimes.vm.dep" } ;
Rule rvdcpp380 = { {&dcpp380} , {&vdcpp380} , {&exedcpp380} } ;
Exe exedcpp380 = { "CC-VM-DEP SmallPrimes.cpp" , VMDEP , { OBJ_PATH+"/SmallPrimes.dep" , OBJ_PATH+"/SmallPrimes.vm.dep" , "380" } } ;

Target cpp381 = { "SmoothAlgo.cpp" , "../../Desktop/Draw/CCore/src/./video/SmoothAlgo.cpp" } ;
Target dcpp381 = { "SmoothAlgo.dep" , OBJ_PATH+"/SmoothAlgo.dep" } ;
Rule rdcpp381 = { {&cpp381,&obj} , {&dcpp381} , {&execpp381} } ;
Exe execpp381 = { "CC-DEP SmoothAlgo.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SmoothAlgo.o"
 ,"../../Desktop/Draw/CCore/src/./video/SmoothAlgo.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SmoothAlgo.dep"
} } ;

Target vdcpp381 = { "SmoothAlgo.vm.dep" , OBJ_PATH+"/SmoothAlgo.vm.dep" } ;
Rule rvdcpp381 = { {&dcpp381} , {&vdcpp381} , {&exedcpp381} } ;
Exe exedcpp381 = { "CC-VM-DEP SmoothAlgo.cpp" , VMDEP , { OBJ_PATH+"/SmoothAlgo.dep" , OBJ_PATH+"/SmoothAlgo.vm.dep" , "381" } } ;

Target cpp382 = { "SmoothDrawArt.cpp" , "../../Desktop/Draw/CCore/src/./video/SmoothDrawArt.cpp" } ;
Target dcpp382 = { "SmoothDrawArt.dep" , OBJ_PATH+"/SmoothDrawArt.dep" } ;
Rule rdcpp382 = { {&cpp382,&obj} , {&dcpp382} , {&execpp382} } ;
Exe execpp382 = { "CC-DEP SmoothDrawArt.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SmoothDrawArt.o"
 ,"../../Desktop/Draw/CCore/src/./video/SmoothDrawArt.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SmoothDrawArt.dep"
} } ;

Target vdcpp382 = { "SmoothDrawArt.vm.dep" , OBJ_PATH+"/SmoothDrawArt.vm.dep" } ;
Rule rvdcpp382 = { {&dcpp382} , {&vdcpp382} , {&exedcpp382} } ;
Exe exedcpp382 = { "CC-VM-DEP SmoothDrawArt.cpp" , VMDEP , { OBJ_PATH+"/SmoothDrawArt.dep" , OBJ_PATH+"/SmoothDrawArt.vm.dep" , "382" } } ;

Target cpp383 = { "Sort.cpp" , "../../Fundamental/CCore/src/Sort.cpp" } ;
Target dcpp383 = { "Sort.dep" , OBJ_PATH+"/Sort.dep" } ;
Rule rdcpp383 = { {&cpp383,&obj} , {&dcpp383} , {&execpp383} } ;
Exe execpp383 = { "CC-DEP Sort.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Sort.o"
 ,"../../Fundamental/CCore/src/Sort.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Sort.dep"
} } ;

Target vdcpp383 = { "Sort.vm.dep" , OBJ_PATH+"/Sort.vm.dep" } ;
Rule rvdcpp383 = { {&dcpp383} , {&vdcpp383} , {&exedcpp383} } ;
Exe exedcpp383 = { "CC-VM-DEP Sort.cpp" , VMDEP , { OBJ_PATH+"/Sort.dep" , OBJ_PATH+"/Sort.vm.dep" , "383" } } ;

Target cpp384 = { "SortUnique.cpp" , "../../Fundamental/CCore/src/./algon/SortUnique.cpp" } ;
Target dcpp384 = { "SortUnique.dep" , OBJ_PATH+"/SortUnique.dep" } ;
Rule rdcpp384 = { {&cpp384,&obj} , {&dcpp384} , {&execpp384} } ;
Exe execpp384 = { "CC-DEP SortUnique.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SortUnique.o"
 ,"../../Fundamental/CCore/src/./algon/SortUnique.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SortUnique.dep"
} } ;

Target vdcpp384 = { "SortUnique.vm.dep" , OBJ_PATH+"/SortUnique.vm.dep" } ;
Rule rvdcpp384 = { {&dcpp384} , {&vdcpp384} , {&exedcpp384} } ;
Exe exedcpp384 = { "CC-VM-DEP SortUnique.cpp" , VMDEP , { OBJ_PATH+"/SortUnique.dep" , OBJ_PATH+"/SortUnique.vm.dep" , "384" } } ;

Target cpp385 = { "Space.cpp" , "../../Simple/CCore/src/./gadget/Space.cpp" } ;
Target dcpp385 = { "Space.dep" , OBJ_PATH+"/Space.dep" } ;
Rule rdcpp385 = { {&cpp385,&obj} , {&dcpp385} , {&execpp385} } ;
Exe execpp385 = { "CC-DEP Space.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Space.o"
 ,"../../Simple/CCore/src/./gadget/Space.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Space.dep"
} } ;

Target vdcpp385 = { "Space.vm.dep" , OBJ_PATH+"/Space.vm.dep" } ;
Rule rvdcpp385 = { {&dcpp385} , {&vdcpp385} , {&exedcpp385} } ;
Exe exedcpp385 = { "CC-VM-DEP Space.cpp" , VMDEP , { OBJ_PATH+"/Space.dep" , OBJ_PATH+"/Space.vm.dep" , "385" } } ;

Target cpp386 = { "SpanLenEngine.cpp" , "../../Desktop/Lib/CCore/src/./video/book/SpanLenEngine.cpp" } ;
Target dcpp386 = { "SpanLenEngine.dep" , OBJ_PATH+"/SpanLenEngine.dep" } ;
Rule rdcpp386 = { {&cpp386,&obj} , {&dcpp386} , {&execpp386} } ;
Exe execpp386 = { "CC-DEP SpanLenEngine.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SpanLenEngine.o"
 ,"../../Desktop/Lib/CCore/src/./video/book/SpanLenEngine.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SpanLenEngine.dep"
} } ;

Target vdcpp386 = { "SpanLenEngine.vm.dep" , OBJ_PATH+"/SpanLenEngine.vm.dep" } ;
Rule rvdcpp386 = { {&dcpp386} , {&vdcpp386} , {&exedcpp386} } ;
Exe exedcpp386 = { "CC-VM-DEP SpanLenEngine.cpp" , VMDEP , { OBJ_PATH+"/SpanLenEngine.dep" , OBJ_PATH+"/SpanLenEngine.vm.dep" , "386" } } ;

Target cpp387 = { "SpawnProcess.cpp" , "../../HCore/CCore/src/SpawnProcess.cpp" } ;
Target dcpp387 = { "SpawnProcess.dep" , OBJ_PATH+"/SpawnProcess.dep" } ;
Rule rdcpp387 = { {&cpp387,&obj} , {&dcpp387} , {&execpp387} } ;
Exe execpp387 = { "CC-DEP SpawnProcess.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SpawnProcess.o"
 ,"../../HCore/CCore/src/SpawnProcess.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SpawnProcess.dep"
} } ;

Target vdcpp387 = { "SpawnProcess.vm.dep" , OBJ_PATH+"/SpawnProcess.vm.dep" } ;
Rule rvdcpp387 = { {&dcpp387} , {&vdcpp387} , {&exedcpp387} } ;
Exe exedcpp387 = { "CC-VM-DEP SpawnProcess.cpp" , VMDEP , { OBJ_PATH+"/SpawnProcess.dep" , OBJ_PATH+"/SpawnProcess.vm.dep" , "387" } } ;

Target cpp388 = { "StartStop.cpp" , "../../Simple/CCore/src/StartStop.cpp" } ;
Target dcpp388 = { "StartStop.dep" , OBJ_PATH+"/StartStop.dep" } ;
Rule rdcpp388 = { {&cpp388,&obj} , {&dcpp388} , {&execpp388} } ;
Exe execpp388 = { "CC-DEP StartStop.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/StartStop.o"
 ,"../../Simple/CCore/src/StartStop.cpp"
 ,"-MF"
 ,OBJ_PATH+"/StartStop.dep"
} } ;

Target vdcpp388 = { "StartStop.vm.dep" , OBJ_PATH+"/StartStop.vm.dep" } ;
Rule rvdcpp388 = { {&dcpp388} , {&vdcpp388} , {&exedcpp388} } ;
Exe exedcpp388 = { "CC-VM-DEP StartStop.cpp" , VMDEP , { OBJ_PATH+"/StartStop.dep" , OBJ_PATH+"/StartStop.vm.dep" , "388" } } ;

Target cpp389 = { "Starter.cpp" , "../../Fundamental/CCore/src/Starter.cpp" } ;
Target dcpp389 = { "Starter.dep" , OBJ_PATH+"/Starter.dep" } ;
Rule rdcpp389 = { {&cpp389,&obj} , {&dcpp389} , {&execpp389} } ;
Exe execpp389 = { "CC-DEP Starter.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Starter.o"
 ,"../../Fundamental/CCore/src/Starter.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Starter.dep"
} } ;

Target vdcpp389 = { "Starter.vm.dep" , OBJ_PATH+"/Starter.vm.dep" } ;
Rule rvdcpp389 = { {&dcpp389} , {&vdcpp389} , {&exedcpp389} } ;
Exe exedcpp389 = { "CC-VM-DEP Starter.cpp" , VMDEP , { OBJ_PATH+"/Starter.dep" , OBJ_PATH+"/Starter.vm.dep" , "389" } } ;

Target cpp390 = { "StepEval.cpp" , "../../Fundamental/CCore/src/StepEval.cpp" } ;
Target dcpp390 = { "StepEval.dep" , OBJ_PATH+"/StepEval.dep" } ;
Rule rdcpp390 = { {&cpp390,&obj} , {&dcpp390} , {&execpp390} } ;
Exe execpp390 = { "CC-DEP StepEval.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/StepEval.o"
 ,"../../Fundamental/CCore/src/StepEval.cpp"
 ,"-MF"
 ,OBJ_PATH+"/StepEval.dep"
} } ;

Target vdcpp390 = { "StepEval.vm.dep" , OBJ_PATH+"/StepEval.vm.dep" } ;
Rule rvdcpp390 = { {&dcpp390} , {&vdcpp390} , {&exedcpp390} } ;
Exe exedcpp390 = { "CC-VM-DEP StepEval.cpp" , VMDEP , { OBJ_PATH+"/StepEval.dep" , OBJ_PATH+"/StepEval.vm.dep" , "390" } } ;

Target cpp391 = { "StrKey.cpp" , "../../Simple/CCore/src/StrKey.cpp" } ;
Target dcpp391 = { "StrKey.dep" , OBJ_PATH+"/StrKey.dep" } ;
Rule rdcpp391 = { {&cpp391,&obj} , {&dcpp391} , {&execpp391} } ;
Exe execpp391 = { "CC-DEP StrKey.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/StrKey.o"
 ,"../../Simple/CCore/src/StrKey.cpp"
 ,"-MF"
 ,OBJ_PATH+"/StrKey.dep"
} } ;

Target vdcpp391 = { "StrKey.vm.dep" , OBJ_PATH+"/StrKey.vm.dep" } ;
Rule rvdcpp391 = { {&dcpp391} , {&vdcpp391} , {&exedcpp391} } ;
Exe exedcpp391 = { "CC-VM-DEP StrKey.cpp" , VMDEP , { OBJ_PATH+"/StrKey.dep" , OBJ_PATH+"/StrKey.vm.dep" , "391" } } ;

Target cpp392 = { "StrMap.cpp" , "../../Fundamental/CCore/src/StrMap.cpp" } ;
Target dcpp392 = { "StrMap.dep" , OBJ_PATH+"/StrMap.dep" } ;
Rule rdcpp392 = { {&cpp392,&obj} , {&dcpp392} , {&execpp392} } ;
Exe execpp392 = { "CC-DEP StrMap.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/StrMap.o"
 ,"../../Fundamental/CCore/src/StrMap.cpp"
 ,"-MF"
 ,OBJ_PATH+"/StrMap.dep"
} } ;

Target vdcpp392 = { "StrMap.vm.dep" , OBJ_PATH+"/StrMap.vm.dep" } ;
Rule rvdcpp392 = { {&dcpp392} , {&vdcpp392} , {&exedcpp392} } ;
Exe exedcpp392 = { "CC-VM-DEP StrMap.cpp" , VMDEP , { OBJ_PATH+"/StrMap.dep" , OBJ_PATH+"/StrMap.vm.dep" , "392" } } ;

Target cpp393 = { "StrParse.cpp" , "../../Fundamental/CCore/src/StrParse.cpp" } ;
Target dcpp393 = { "StrParse.dep" , OBJ_PATH+"/StrParse.dep" } ;
Rule rdcpp393 = { {&cpp393,&obj} , {&dcpp393} , {&execpp393} } ;
Exe execpp393 = { "CC-DEP StrParse.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/StrParse.o"
 ,"../../Fundamental/CCore/src/StrParse.cpp"
 ,"-MF"
 ,OBJ_PATH+"/StrParse.dep"
} } ;

Target vdcpp393 = { "StrParse.vm.dep" , OBJ_PATH+"/StrParse.vm.dep" } ;
Rule rvdcpp393 = { {&dcpp393} , {&vdcpp393} , {&exedcpp393} } ;
Exe exedcpp393 = { "CC-VM-DEP StrParse.cpp" , VMDEP , { OBJ_PATH+"/StrParse.dep" , OBJ_PATH+"/StrParse.vm.dep" , "393" } } ;

Target cpp394 = { "StrPrint.cpp" , "../../Fundamental/CCore/src/./printf/StrPrint.cpp" } ;
Target dcpp394 = { "StrPrint.dep" , OBJ_PATH+"/StrPrint.dep" } ;
Rule rdcpp394 = { {&cpp394,&obj} , {&dcpp394} , {&execpp394} } ;
Exe execpp394 = { "CC-DEP StrPrint.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/StrPrint.o"
 ,"../../Fundamental/CCore/src/./printf/StrPrint.cpp"
 ,"-MF"
 ,OBJ_PATH+"/StrPrint.dep"
} } ;

Target vdcpp394 = { "StrPrint.vm.dep" , OBJ_PATH+"/StrPrint.vm.dep" } ;
Rule rvdcpp394 = { {&dcpp394} , {&vdcpp394} , {&exedcpp394} } ;
Exe exedcpp394 = { "CC-VM-DEP StrPrint.cpp" , VMDEP , { OBJ_PATH+"/StrPrint.dep" , OBJ_PATH+"/StrPrint.vm.dep" , "394" } } ;

Target cpp395 = { "StrToChar.cpp" , "../../Applied/CCore/src/StrToChar.cpp" } ;
Target dcpp395 = { "StrToChar.dep" , OBJ_PATH+"/StrToChar.dep" } ;
Rule rdcpp395 = { {&cpp395,&obj} , {&dcpp395} , {&execpp395} } ;
Exe execpp395 = { "CC-DEP StrToChar.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/StrToChar.o"
 ,"../../Applied/CCore/src/StrToChar.cpp"
 ,"-MF"
 ,OBJ_PATH+"/StrToChar.dep"
} } ;

Target vdcpp395 = { "StrToChar.vm.dep" , OBJ_PATH+"/StrToChar.vm.dep" } ;
Rule rvdcpp395 = { {&dcpp395} , {&vdcpp395} , {&exedcpp395} } ;
Exe exedcpp395 = { "CC-VM-DEP StrToChar.cpp" , VMDEP , { OBJ_PATH+"/StrToChar.dep" , OBJ_PATH+"/StrToChar.vm.dep" , "395" } } ;

Target cpp396 = { "String.cpp" , "../../Fundamental/CCore/src/String.cpp" } ;
Target dcpp396 = { "String.dep" , OBJ_PATH+"/String.dep" } ;
Rule rdcpp396 = { {&cpp396,&obj} , {&dcpp396} , {&execpp396} } ;
Exe execpp396 = { "CC-DEP String.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/String.o"
 ,"../../Fundamental/CCore/src/String.cpp"
 ,"-MF"
 ,OBJ_PATH+"/String.dep"
} } ;

Target vdcpp396 = { "String.vm.dep" , OBJ_PATH+"/String.vm.dep" } ;
Rule rvdcpp396 = { {&dcpp396} , {&vdcpp396} , {&exedcpp396} } ;
Exe exedcpp396 = { "CC-VM-DEP String.cpp" , VMDEP , { OBJ_PATH+"/String.dep" , OBJ_PATH+"/String.vm.dep" , "396" } } ;

Target cpp397 = { "StringScan.cpp" , "../../Fundamental/CCore/src/./scanf/StringScan.cpp" } ;
Target dcpp397 = { "StringScan.dep" , OBJ_PATH+"/StringScan.dep" } ;
Rule rdcpp397 = { {&cpp397,&obj} , {&dcpp397} , {&execpp397} } ;
Exe execpp397 = { "CC-DEP StringScan.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/StringScan.o"
 ,"../../Fundamental/CCore/src/./scanf/StringScan.cpp"
 ,"-MF"
 ,OBJ_PATH+"/StringScan.dep"
} } ;

Target vdcpp397 = { "StringScan.vm.dep" , OBJ_PATH+"/StringScan.vm.dep" } ;
Rule rvdcpp397 = { {&dcpp397} , {&vdcpp397} , {&exedcpp397} } ;
Exe exedcpp397 = { "CC-VM-DEP StringScan.cpp" , VMDEP , { OBJ_PATH+"/StringScan.dep" , OBJ_PATH+"/StringScan.vm.dep" , "397" } } ;

Target cpp398 = { "SubWindow.cpp" , "../../Desktop/Core/CCore/src/./video/SubWindow.cpp" } ;
Target dcpp398 = { "SubWindow.dep" , OBJ_PATH+"/SubWindow.dep" } ;
Rule rdcpp398 = { {&cpp398,&obj} , {&dcpp398} , {&execpp398} } ;
Exe execpp398 = { "CC-DEP SubWindow.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SubWindow.o"
 ,"../../Desktop/Core/CCore/src/./video/SubWindow.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SubWindow.dep"
} } ;

Target vdcpp398 = { "SubWindow.vm.dep" , OBJ_PATH+"/SubWindow.vm.dep" } ;
Rule rvdcpp398 = { {&dcpp398} , {&vdcpp398} , {&exedcpp398} } ;
Exe exedcpp398 = { "CC-VM-DEP SubWindow.cpp" , VMDEP , { OBJ_PATH+"/SubWindow.dep" , OBJ_PATH+"/SubWindow.vm.dep" , "398" } } ;

Target cpp399 = { "Swap.cpp" , "../../Simple/CCore/src/Swap.cpp" } ;
Target dcpp399 = { "Swap.dep" , OBJ_PATH+"/Swap.dep" } ;
Rule rdcpp399 = { {&cpp399,&obj} , {&dcpp399} , {&execpp399} } ;
Exe execpp399 = { "CC-DEP Swap.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Swap.o"
 ,"../../Simple/CCore/src/Swap.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Swap.dep"
} } ;

Target vdcpp399 = { "Swap.vm.dep" , OBJ_PATH+"/Swap.vm.dep" } ;
Rule rvdcpp399 = { {&dcpp399} , {&vdcpp399} , {&exedcpp399} } ;
Exe exedcpp399 = { "CC-VM-DEP Swap.cpp" , VMDEP , { OBJ_PATH+"/Swap.dep" , OBJ_PATH+"/Swap.vm.dep" , "399" } } ;

Target cpp400 = { "SymCount.cpp" , "../../Simple/CCore/src/SymCount.cpp" } ;
Target dcpp400 = { "SymCount.dep" , OBJ_PATH+"/SymCount.dep" } ;
Rule rdcpp400 = { {&cpp400,&obj} , {&dcpp400} , {&execpp400} } ;
Exe execpp400 = { "CC-DEP SymCount.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SymCount.o"
 ,"../../Simple/CCore/src/SymCount.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SymCount.dep"
} } ;

Target vdcpp400 = { "SymCount.vm.dep" , OBJ_PATH+"/SymCount.vm.dep" } ;
Rule rvdcpp400 = { {&dcpp400} , {&vdcpp400} , {&exedcpp400} } ;
Exe exedcpp400 = { "CC-VM-DEP SymCount.cpp" , VMDEP , { OBJ_PATH+"/SymCount.dep" , OBJ_PATH+"/SymCount.vm.dep" , "400" } } ;

Target cpp401 = { "SymPart.cpp" , "../../Simple/CCore/src/SymPart.cpp" } ;
Target dcpp401 = { "SymPart.dep" , OBJ_PATH+"/SymPart.dep" } ;
Rule rdcpp401 = { {&cpp401,&obj} , {&dcpp401} , {&execpp401} } ;
Exe execpp401 = { "CC-DEP SymPart.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SymPart.o"
 ,"../../Simple/CCore/src/SymPart.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SymPart.dep"
} } ;

Target vdcpp401 = { "SymPart.vm.dep" , OBJ_PATH+"/SymPart.vm.dep" } ;
Rule rvdcpp401 = { {&dcpp401} , {&vdcpp401} , {&exedcpp401} } ;
Exe exedcpp401 = { "CC-VM-DEP SymPart.cpp" , VMDEP , { OBJ_PATH+"/SymPart.dep" , OBJ_PATH+"/SymPart.vm.dep" , "401" } } ;

Target cpp402 = { "Symbol.cpp" , "../../Simple/CCore/src/Symbol.cpp" } ;
Target dcpp402 = { "Symbol.dep" , OBJ_PATH+"/Symbol.dep" } ;
Rule rdcpp402 = { {&cpp402,&obj} , {&dcpp402} , {&execpp402} } ;
Exe execpp402 = { "CC-DEP Symbol.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Symbol.o"
 ,"../../Simple/CCore/src/Symbol.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Symbol.dep"
} } ;

Target vdcpp402 = { "Symbol.vm.dep" , OBJ_PATH+"/Symbol.vm.dep" } ;
Rule rvdcpp402 = { {&dcpp402} , {&vdcpp402} , {&exedcpp402} } ;
Exe exedcpp402 = { "CC-VM-DEP Symbol.cpp" , VMDEP , { OBJ_PATH+"/Symbol.dep" , OBJ_PATH+"/Symbol.vm.dep" , "402" } } ;

Target cpp403 = { "SysAbort.cpp" , "CCore/src/./sys/SysAbort.cpp" } ;
Target dcpp403 = { "SysAbort.dep" , OBJ_PATH+"/SysAbort.dep" } ;
Rule rdcpp403 = { {&cpp403,&obj} , {&dcpp403} , {&execpp403} } ;
Exe execpp403 = { "CC-DEP SysAbort.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SysAbort.o"
 ,"CCore/src/./sys/SysAbort.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SysAbort.dep"
} } ;

Target vdcpp403 = { "SysAbort.vm.dep" , OBJ_PATH+"/SysAbort.vm.dep" } ;
Rule rvdcpp403 = { {&dcpp403} , {&vdcpp403} , {&exedcpp403} } ;
Exe exedcpp403 = { "CC-VM-DEP SysAbort.cpp" , VMDEP , { OBJ_PATH+"/SysAbort.dep" , OBJ_PATH+"/SysAbort.vm.dep" , "403" } } ;

Target cpp404 = { "SysAsyncFile.cpp" , "../../Applied/CCore/src/./sys/SysAsyncFile.cpp" } ;
Target dcpp404 = { "SysAsyncFile.dep" , OBJ_PATH+"/SysAsyncFile.dep" } ;
Rule rdcpp404 = { {&cpp404,&obj} , {&dcpp404} , {&execpp404} } ;
Exe execpp404 = { "CC-DEP SysAsyncFile.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SysAsyncFile.o"
 ,"../../Applied/CCore/src/./sys/SysAsyncFile.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SysAsyncFile.dep"
} } ;

Target vdcpp404 = { "SysAsyncFile.vm.dep" , OBJ_PATH+"/SysAsyncFile.vm.dep" } ;
Rule rvdcpp404 = { {&dcpp404} , {&vdcpp404} , {&exedcpp404} } ;
Exe exedcpp404 = { "CC-VM-DEP SysAsyncFile.cpp" , VMDEP , { OBJ_PATH+"/SysAsyncFile.dep" , OBJ_PATH+"/SysAsyncFile.vm.dep" , "404" } } ;

Target cpp405 = { "SysAsyncFileSystem.cpp" , "../../Applied/CCore/src/./sys/SysAsyncFileSystem.cpp" } ;
Target dcpp405 = { "SysAsyncFileSystem.dep" , OBJ_PATH+"/SysAsyncFileSystem.dep" } ;
Rule rdcpp405 = { {&cpp405,&obj} , {&dcpp405} , {&execpp405} } ;
Exe execpp405 = { "CC-DEP SysAsyncFileSystem.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SysAsyncFileSystem.o"
 ,"../../Applied/CCore/src/./sys/SysAsyncFileSystem.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SysAsyncFileSystem.dep"
} } ;

Target vdcpp405 = { "SysAsyncFileSystem.vm.dep" , OBJ_PATH+"/SysAsyncFileSystem.vm.dep" } ;
Rule rvdcpp405 = { {&dcpp405} , {&vdcpp405} , {&exedcpp405} } ;
Exe exedcpp405 = { "CC-VM-DEP SysAsyncFileSystem.cpp" , VMDEP , { OBJ_PATH+"/SysAsyncFileSystem.dep" , OBJ_PATH+"/SysAsyncFileSystem.vm.dep" , "405" } } ;

Target cpp406 = { "SysAtomic.cpp" , "CCore/src/./sys/SysAtomic.cpp" } ;
Target dcpp406 = { "SysAtomic.dep" , OBJ_PATH+"/SysAtomic.dep" } ;
Rule rdcpp406 = { {&cpp406,&obj} , {&dcpp406} , {&execpp406} } ;
Exe execpp406 = { "CC-DEP SysAtomic.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SysAtomic.o"
 ,"CCore/src/./sys/SysAtomic.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SysAtomic.dep"
} } ;

Target vdcpp406 = { "SysAtomic.vm.dep" , OBJ_PATH+"/SysAtomic.vm.dep" } ;
Rule rvdcpp406 = { {&dcpp406} , {&vdcpp406} , {&exedcpp406} } ;
Exe exedcpp406 = { "CC-VM-DEP SysAtomic.cpp" , VMDEP , { OBJ_PATH+"/SysAtomic.dep" , OBJ_PATH+"/SysAtomic.vm.dep" , "406" } } ;

Target cpp407 = { "SysCon.cpp" , "CCore/src/./sys/SysCon.cpp" } ;
Target dcpp407 = { "SysCon.dep" , OBJ_PATH+"/SysCon.dep" } ;
Rule rdcpp407 = { {&cpp407,&obj} , {&dcpp407} , {&execpp407} } ;
Exe execpp407 = { "CC-DEP SysCon.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SysCon.o"
 ,"CCore/src/./sys/SysCon.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SysCon.dep"
} } ;

Target vdcpp407 = { "SysCon.vm.dep" , OBJ_PATH+"/SysCon.vm.dep" } ;
Rule rvdcpp407 = { {&dcpp407} , {&vdcpp407} , {&exedcpp407} } ;
Exe exedcpp407 = { "CC-VM-DEP SysCon.cpp" , VMDEP , { OBJ_PATH+"/SysCon.dep" , OBJ_PATH+"/SysCon.vm.dep" , "407" } } ;

Target cpp408 = { "SysEnv.cpp" , "CCore/src/./sys/SysEnv.cpp" } ;
Target dcpp408 = { "SysEnv.dep" , OBJ_PATH+"/SysEnv.dep" } ;
Rule rdcpp408 = { {&cpp408,&obj} , {&dcpp408} , {&execpp408} } ;
Exe execpp408 = { "CC-DEP SysEnv.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SysEnv.o"
 ,"CCore/src/./sys/SysEnv.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SysEnv.dep"
} } ;

Target vdcpp408 = { "SysEnv.vm.dep" , OBJ_PATH+"/SysEnv.vm.dep" } ;
Rule rvdcpp408 = { {&dcpp408} , {&vdcpp408} , {&exedcpp408} } ;
Exe exedcpp408 = { "CC-VM-DEP SysEnv.cpp" , VMDEP , { OBJ_PATH+"/SysEnv.dep" , OBJ_PATH+"/SysEnv.vm.dep" , "408" } } ;

Target cpp409 = { "SysError.cpp" , "CCore/src/./sys/SysError.cpp" } ;
Target dcpp409 = { "SysError.dep" , OBJ_PATH+"/SysError.dep" } ;
Rule rdcpp409 = { {&cpp409,&obj} , {&dcpp409} , {&execpp409} } ;
Exe execpp409 = { "CC-DEP SysError.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SysError.o"
 ,"CCore/src/./sys/SysError.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SysError.dep"
} } ;

Target vdcpp409 = { "SysError.vm.dep" , OBJ_PATH+"/SysError.vm.dep" } ;
Rule rvdcpp409 = { {&dcpp409} , {&vdcpp409} , {&exedcpp409} } ;
Exe exedcpp409 = { "CC-VM-DEP SysError.cpp" , VMDEP , { OBJ_PATH+"/SysError.dep" , OBJ_PATH+"/SysError.vm.dep" , "409" } } ;

Target cpp410 = { "SysFile.cpp" , "CCore/src/./sys/SysFile.cpp" } ;
Target dcpp410 = { "SysFile.dep" , OBJ_PATH+"/SysFile.dep" } ;
Rule rdcpp410 = { {&cpp410,&obj} , {&dcpp410} , {&execpp410} } ;
Exe execpp410 = { "CC-DEP SysFile.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SysFile.o"
 ,"CCore/src/./sys/SysFile.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SysFile.dep"
} } ;

Target vdcpp410 = { "SysFile.vm.dep" , OBJ_PATH+"/SysFile.vm.dep" } ;
Rule rvdcpp410 = { {&dcpp410} , {&vdcpp410} , {&exedcpp410} } ;
Exe exedcpp410 = { "CC-VM-DEP SysFile.cpp" , VMDEP , { OBJ_PATH+"/SysFile.dep" , OBJ_PATH+"/SysFile.vm.dep" , "410" } } ;

Target cpp411 = { "SysFileInternal.cpp" , "CCore/src/./sys/SysFileInternal.cpp" } ;
Target dcpp411 = { "SysFileInternal.dep" , OBJ_PATH+"/SysFileInternal.dep" } ;
Rule rdcpp411 = { {&cpp411,&obj} , {&dcpp411} , {&execpp411} } ;
Exe execpp411 = { "CC-DEP SysFileInternal.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SysFileInternal.o"
 ,"CCore/src/./sys/SysFileInternal.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SysFileInternal.dep"
} } ;

Target vdcpp411 = { "SysFileInternal.vm.dep" , OBJ_PATH+"/SysFileInternal.vm.dep" } ;
Rule rvdcpp411 = { {&dcpp411} , {&vdcpp411} , {&exedcpp411} } ;
Exe exedcpp411 = { "CC-VM-DEP SysFileInternal.cpp" , VMDEP , { OBJ_PATH+"/SysFileInternal.dep" , OBJ_PATH+"/SysFileInternal.vm.dep" , "411" } } ;

Target cpp412 = { "SysFileSystem.cpp" , "CCore/src/./sys/SysFileSystem.cpp" } ;
Target dcpp412 = { "SysFileSystem.dep" , OBJ_PATH+"/SysFileSystem.dep" } ;
Rule rdcpp412 = { {&cpp412,&obj} , {&dcpp412} , {&execpp412} } ;
Exe execpp412 = { "CC-DEP SysFileSystem.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SysFileSystem.o"
 ,"CCore/src/./sys/SysFileSystem.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SysFileSystem.dep"
} } ;

Target vdcpp412 = { "SysFileSystem.vm.dep" , OBJ_PATH+"/SysFileSystem.vm.dep" } ;
Rule rvdcpp412 = { {&dcpp412} , {&vdcpp412} , {&exedcpp412} } ;
Exe exedcpp412 = { "CC-VM-DEP SysFileSystem.cpp" , VMDEP , { OBJ_PATH+"/SysFileSystem.dep" , OBJ_PATH+"/SysFileSystem.vm.dep" , "412" } } ;

Target cpp413 = { "SysLaunchPath.cpp" , "CCore/src/./sys/SysLaunchPath.cpp" } ;
Target dcpp413 = { "SysLaunchPath.dep" , OBJ_PATH+"/SysLaunchPath.dep" } ;
Rule rdcpp413 = { {&cpp413,&obj} , {&dcpp413} , {&execpp413} } ;
Exe execpp413 = { "CC-DEP SysLaunchPath.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SysLaunchPath.o"
 ,"CCore/src/./sys/SysLaunchPath.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SysLaunchPath.dep"
} } ;

Target vdcpp413 = { "SysLaunchPath.vm.dep" , OBJ_PATH+"/SysLaunchPath.vm.dep" } ;
Rule rvdcpp413 = { {&dcpp413} , {&vdcpp413} , {&exedcpp413} } ;
Exe exedcpp413 = { "CC-VM-DEP SysLaunchPath.cpp" , VMDEP , { OBJ_PATH+"/SysLaunchPath.dep" , OBJ_PATH+"/SysLaunchPath.vm.dep" , "413" } } ;

Target cpp414 = { "SysMemPage.cpp" , "CCore/src/./sys/SysMemPage.cpp" } ;
Target dcpp414 = { "SysMemPage.dep" , OBJ_PATH+"/SysMemPage.dep" } ;
Rule rdcpp414 = { {&cpp414,&obj} , {&dcpp414} , {&execpp414} } ;
Exe execpp414 = { "CC-DEP SysMemPage.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SysMemPage.o"
 ,"CCore/src/./sys/SysMemPage.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SysMemPage.dep"
} } ;

Target vdcpp414 = { "SysMemPage.vm.dep" , OBJ_PATH+"/SysMemPage.vm.dep" } ;
Rule rvdcpp414 = { {&dcpp414} , {&vdcpp414} , {&exedcpp414} } ;
Exe exedcpp414 = { "CC-VM-DEP SysMemPage.cpp" , VMDEP , { OBJ_PATH+"/SysMemPage.dep" , OBJ_PATH+"/SysMemPage.vm.dep" , "414" } } ;

Target cpp415 = { "SysNet.cpp" , "CCore/src/./sys/SysNet.cpp" } ;
Target dcpp415 = { "SysNet.dep" , OBJ_PATH+"/SysNet.dep" } ;
Rule rdcpp415 = { {&cpp415,&obj} , {&dcpp415} , {&execpp415} } ;
Exe execpp415 = { "CC-DEP SysNet.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SysNet.o"
 ,"CCore/src/./sys/SysNet.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SysNet.dep"
} } ;

Target vdcpp415 = { "SysNet.vm.dep" , OBJ_PATH+"/SysNet.vm.dep" } ;
Rule rvdcpp415 = { {&dcpp415} , {&vdcpp415} , {&exedcpp415} } ;
Exe exedcpp415 = { "CC-VM-DEP SysNet.cpp" , VMDEP , { OBJ_PATH+"/SysNet.dep" , OBJ_PATH+"/SysNet.vm.dep" , "415" } } ;

Target cpp416 = { "SysPlanInit.cpp" , "CCore/src/./sys/SysPlanInit.cpp" } ;
Target dcpp416 = { "SysPlanInit.dep" , OBJ_PATH+"/SysPlanInit.dep" } ;
Rule rdcpp416 = { {&cpp416,&obj} , {&dcpp416} , {&execpp416} } ;
Exe execpp416 = { "CC-DEP SysPlanInit.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SysPlanInit.o"
 ,"CCore/src/./sys/SysPlanInit.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SysPlanInit.dep"
} } ;

Target vdcpp416 = { "SysPlanInit.vm.dep" , OBJ_PATH+"/SysPlanInit.vm.dep" } ;
Rule rvdcpp416 = { {&dcpp416} , {&vdcpp416} , {&exedcpp416} } ;
Exe exedcpp416 = { "CC-VM-DEP SysPlanInit.cpp" , VMDEP , { OBJ_PATH+"/SysPlanInit.dep" , OBJ_PATH+"/SysPlanInit.vm.dep" , "416" } } ;

Target cpp417 = { "SysProp.cpp" , "CCore/src/./sys/SysProp.cpp" } ;
Target dcpp417 = { "SysProp.dep" , OBJ_PATH+"/SysProp.dep" } ;
Rule rdcpp417 = { {&cpp417,&obj} , {&dcpp417} , {&execpp417} } ;
Exe execpp417 = { "CC-DEP SysProp.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SysProp.o"
 ,"CCore/src/./sys/SysProp.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SysProp.dep"
} } ;

Target vdcpp417 = { "SysProp.vm.dep" , OBJ_PATH+"/SysProp.vm.dep" } ;
Rule rvdcpp417 = { {&dcpp417} , {&vdcpp417} , {&exedcpp417} } ;
Exe exedcpp417 = { "CC-VM-DEP SysProp.cpp" , VMDEP , { OBJ_PATH+"/SysProp.dep" , OBJ_PATH+"/SysProp.vm.dep" , "417" } } ;

Target cpp418 = { "SysSem.cpp" , "CCore/src/./sys/SysSem.cpp" } ;
Target dcpp418 = { "SysSem.dep" , OBJ_PATH+"/SysSem.dep" } ;
Rule rdcpp418 = { {&cpp418,&obj} , {&dcpp418} , {&execpp418} } ;
Exe execpp418 = { "CC-DEP SysSem.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SysSem.o"
 ,"CCore/src/./sys/SysSem.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SysSem.dep"
} } ;

Target vdcpp418 = { "SysSem.vm.dep" , OBJ_PATH+"/SysSem.vm.dep" } ;
Rule rvdcpp418 = { {&dcpp418} , {&vdcpp418} , {&exedcpp418} } ;
Exe exedcpp418 = { "CC-VM-DEP SysSem.cpp" , VMDEP , { OBJ_PATH+"/SysSem.dep" , OBJ_PATH+"/SysSem.vm.dep" , "418" } } ;

Target cpp419 = { "SysSpawn.cpp" , "CCore/src/./sys/SysSpawn.cpp" } ;
Target dcpp419 = { "SysSpawn.dep" , OBJ_PATH+"/SysSpawn.dep" } ;
Rule rdcpp419 = { {&cpp419,&obj} , {&dcpp419} , {&execpp419} } ;
Exe execpp419 = { "CC-DEP SysSpawn.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SysSpawn.o"
 ,"CCore/src/./sys/SysSpawn.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SysSpawn.dep"
} } ;

Target vdcpp419 = { "SysSpawn.vm.dep" , OBJ_PATH+"/SysSpawn.vm.dep" } ;
Rule rvdcpp419 = { {&dcpp419} , {&vdcpp419} , {&exedcpp419} } ;
Exe exedcpp419 = { "CC-VM-DEP SysSpawn.cpp" , VMDEP , { OBJ_PATH+"/SysSpawn.dep" , OBJ_PATH+"/SysSpawn.vm.dep" , "419" } } ;

Target cpp420 = { "SysSpawnInternal.cpp" , "CCore/src/./sys/SysSpawnInternal.cpp" } ;
Target dcpp420 = { "SysSpawnInternal.dep" , OBJ_PATH+"/SysSpawnInternal.dep" } ;
Rule rdcpp420 = { {&cpp420,&obj} , {&dcpp420} , {&execpp420} } ;
Exe execpp420 = { "CC-DEP SysSpawnInternal.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SysSpawnInternal.o"
 ,"CCore/src/./sys/SysSpawnInternal.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SysSpawnInternal.dep"
} } ;

Target vdcpp420 = { "SysSpawnInternal.vm.dep" , OBJ_PATH+"/SysSpawnInternal.vm.dep" } ;
Rule rvdcpp420 = { {&dcpp420} , {&vdcpp420} , {&exedcpp420} } ;
Exe exedcpp420 = { "CC-VM-DEP SysSpawnInternal.cpp" , VMDEP , { OBJ_PATH+"/SysSpawnInternal.dep" , OBJ_PATH+"/SysSpawnInternal.vm.dep" , "420" } } ;

Target cpp421 = { "SysTask.cpp" , "CCore/src/./sys/SysTask.cpp" } ;
Target dcpp421 = { "SysTask.dep" , OBJ_PATH+"/SysTask.dep" } ;
Rule rdcpp421 = { {&cpp421,&obj} , {&dcpp421} , {&execpp421} } ;
Exe execpp421 = { "CC-DEP SysTask.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SysTask.o"
 ,"CCore/src/./sys/SysTask.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SysTask.dep"
} } ;

Target vdcpp421 = { "SysTask.vm.dep" , OBJ_PATH+"/SysTask.vm.dep" } ;
Rule rvdcpp421 = { {&dcpp421} , {&vdcpp421} , {&exedcpp421} } ;
Exe exedcpp421 = { "CC-VM-DEP SysTask.cpp" , VMDEP , { OBJ_PATH+"/SysTask.dep" , OBJ_PATH+"/SysTask.vm.dep" , "421" } } ;

Target cpp422 = { "SysTime.cpp" , "CCore/src/./sys/SysTime.cpp" } ;
Target dcpp422 = { "SysTime.dep" , OBJ_PATH+"/SysTime.dep" } ;
Rule rdcpp422 = { {&cpp422,&obj} , {&dcpp422} , {&execpp422} } ;
Exe execpp422 = { "CC-DEP SysTime.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SysTime.o"
 ,"CCore/src/./sys/SysTime.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SysTime.dep"
} } ;

Target vdcpp422 = { "SysTime.vm.dep" , OBJ_PATH+"/SysTime.vm.dep" } ;
Rule rvdcpp422 = { {&dcpp422} , {&vdcpp422} , {&exedcpp422} } ;
Exe exedcpp422 = { "CC-VM-DEP SysTime.cpp" , VMDEP , { OBJ_PATH+"/SysTime.dep" , OBJ_PATH+"/SysTime.vm.dep" , "422" } } ;

Target cpp423 = { "SysTlsSlot.cpp" , "CCore/src/./sys/SysTlsSlot.cpp" } ;
Target dcpp423 = { "SysTlsSlot.dep" , OBJ_PATH+"/SysTlsSlot.dep" } ;
Rule rdcpp423 = { {&cpp423,&obj} , {&dcpp423} , {&execpp423} } ;
Exe execpp423 = { "CC-DEP SysTlsSlot.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SysTlsSlot.o"
 ,"CCore/src/./sys/SysTlsSlot.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SysTlsSlot.dep"
} } ;

Target vdcpp423 = { "SysTlsSlot.vm.dep" , OBJ_PATH+"/SysTlsSlot.vm.dep" } ;
Rule rvdcpp423 = { {&dcpp423} , {&vdcpp423} , {&exedcpp423} } ;
Exe exedcpp423 = { "CC-VM-DEP SysTlsSlot.cpp" , VMDEP , { OBJ_PATH+"/SysTlsSlot.dep" , OBJ_PATH+"/SysTlsSlot.vm.dep" , "423" } } ;

Target cpp424 = { "SysUtf8.cpp" , "CCore/src/./sys/SysUtf8.cpp" } ;
Target dcpp424 = { "SysUtf8.dep" , OBJ_PATH+"/SysUtf8.dep" } ;
Rule rdcpp424 = { {&cpp424,&obj} , {&dcpp424} , {&execpp424} } ;
Exe execpp424 = { "CC-DEP SysUtf8.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SysUtf8.o"
 ,"CCore/src/./sys/SysUtf8.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SysUtf8.dep"
} } ;

Target vdcpp424 = { "SysUtf8.vm.dep" , OBJ_PATH+"/SysUtf8.vm.dep" } ;
Rule rvdcpp424 = { {&dcpp424} , {&vdcpp424} , {&exedcpp424} } ;
Exe exedcpp424 = { "CC-VM-DEP SysUtf8.cpp" , VMDEP , { OBJ_PATH+"/SysUtf8.dep" , OBJ_PATH+"/SysUtf8.vm.dep" , "424" } } ;

Target cpp425 = { "SysWait.cpp" , "CCore/src/./sys/SysWait.cpp" } ;
Target dcpp425 = { "SysWait.dep" , OBJ_PATH+"/SysWait.dep" } ;
Rule rdcpp425 = { {&cpp425,&obj} , {&dcpp425} , {&execpp425} } ;
Exe execpp425 = { "CC-DEP SysWait.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SysWait.o"
 ,"CCore/src/./sys/SysWait.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SysWait.dep"
} } ;

Target vdcpp425 = { "SysWait.vm.dep" , OBJ_PATH+"/SysWait.vm.dep" } ;
Rule rvdcpp425 = { {&dcpp425} , {&vdcpp425} , {&exedcpp425} } ;
Exe exedcpp425 = { "CC-VM-DEP SysWait.cpp" , VMDEP , { OBJ_PATH+"/SysWait.dep" , OBJ_PATH+"/SysWait.vm.dep" , "425" } } ;

Target cpp426 = { "SysWaitInternal.cpp" , "CCore/src/./sys/SysWaitInternal.cpp" } ;
Target dcpp426 = { "SysWaitInternal.dep" , OBJ_PATH+"/SysWaitInternal.dep" } ;
Rule rdcpp426 = { {&cpp426,&obj} , {&dcpp426} , {&execpp426} } ;
Exe execpp426 = { "CC-DEP SysWaitInternal.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/SysWaitInternal.o"
 ,"CCore/src/./sys/SysWaitInternal.cpp"
 ,"-MF"
 ,OBJ_PATH+"/SysWaitInternal.dep"
} } ;

Target vdcpp426 = { "SysWaitInternal.vm.dep" , OBJ_PATH+"/SysWaitInternal.vm.dep" } ;
Rule rvdcpp426 = { {&dcpp426} , {&vdcpp426} , {&exedcpp426} } ;
Exe exedcpp426 = { "CC-VM-DEP SysWaitInternal.cpp" , VMDEP , { OBJ_PATH+"/SysWaitInternal.dep" , OBJ_PATH+"/SysWaitInternal.vm.dep" , "426" } } ;

Target cpp427 = { "Task.cpp" , "../../HCore/CCore/src/Task.cpp" } ;
Target dcpp427 = { "Task.dep" , OBJ_PATH+"/Task.dep" } ;
Rule rdcpp427 = { {&cpp427,&obj} , {&dcpp427} , {&execpp427} } ;
Exe execpp427 = { "CC-DEP Task.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Task.o"
 ,"../../HCore/CCore/src/Task.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Task.dep"
} } ;

Target vdcpp427 = { "Task.vm.dep" , OBJ_PATH+"/Task.vm.dep" } ;
Rule rvdcpp427 = { {&dcpp427} , {&vdcpp427} , {&exedcpp427} } ;
Exe exedcpp427 = { "CC-VM-DEP Task.cpp" , VMDEP , { OBJ_PATH+"/Task.dep" , OBJ_PATH+"/Task.vm.dep" , "427" } } ;

Target cpp428 = { "TaskCore.cpp" , "../../HCore/CCore/src/./task/TaskCore.cpp" } ;
Target dcpp428 = { "TaskCore.dep" , OBJ_PATH+"/TaskCore.dep" } ;
Rule rdcpp428 = { {&cpp428,&obj} , {&dcpp428} , {&execpp428} } ;
Exe execpp428 = { "CC-DEP TaskCore.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/TaskCore.o"
 ,"../../HCore/CCore/src/./task/TaskCore.cpp"
 ,"-MF"
 ,OBJ_PATH+"/TaskCore.dep"
} } ;

Target vdcpp428 = { "TaskCore.vm.dep" , OBJ_PATH+"/TaskCore.vm.dep" } ;
Rule rvdcpp428 = { {&dcpp428} , {&vdcpp428} , {&exedcpp428} } ;
Exe exedcpp428 = { "CC-VM-DEP TaskCore.cpp" , VMDEP , { OBJ_PATH+"/TaskCore.dep" , OBJ_PATH+"/TaskCore.vm.dep" , "428" } } ;

Target cpp429 = { "TaskEvent.cpp" , "../../HCore/CCore/src/./task/TaskEvent.cpp" } ;
Target dcpp429 = { "TaskEvent.dep" , OBJ_PATH+"/TaskEvent.dep" } ;
Rule rdcpp429 = { {&cpp429,&obj} , {&dcpp429} , {&execpp429} } ;
Exe execpp429 = { "CC-DEP TaskEvent.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/TaskEvent.o"
 ,"../../HCore/CCore/src/./task/TaskEvent.cpp"
 ,"-MF"
 ,OBJ_PATH+"/TaskEvent.dep"
} } ;

Target vdcpp429 = { "TaskEvent.vm.dep" , OBJ_PATH+"/TaskEvent.vm.dep" } ;
Rule rvdcpp429 = { {&dcpp429} , {&vdcpp429} , {&exedcpp429} } ;
Exe exedcpp429 = { "CC-VM-DEP TaskEvent.cpp" , VMDEP , { OBJ_PATH+"/TaskEvent.dep" , OBJ_PATH+"/TaskEvent.vm.dep" , "429" } } ;

Target cpp430 = { "TaskHeap.cpp" , "../../HCore/CCore/src/TaskHeap.cpp" } ;
Target dcpp430 = { "TaskHeap.dep" , OBJ_PATH+"/TaskHeap.dep" } ;
Rule rdcpp430 = { {&cpp430,&obj} , {&dcpp430} , {&execpp430} } ;
Exe execpp430 = { "CC-DEP TaskHeap.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/TaskHeap.o"
 ,"../../HCore/CCore/src/TaskHeap.cpp"
 ,"-MF"
 ,OBJ_PATH+"/TaskHeap.dep"
} } ;

Target vdcpp430 = { "TaskHeap.vm.dep" , OBJ_PATH+"/TaskHeap.vm.dep" } ;
Rule rvdcpp430 = { {&dcpp430} , {&vdcpp430} , {&exedcpp430} } ;
Exe exedcpp430 = { "CC-VM-DEP TaskHeap.cpp" , VMDEP , { OBJ_PATH+"/TaskHeap.dep" , OBJ_PATH+"/TaskHeap.vm.dep" , "430" } } ;

Target cpp431 = { "TaskMemStack.cpp" , "../../Applied/CCore/src/TaskMemStack.cpp" } ;
Target dcpp431 = { "TaskMemStack.dep" , OBJ_PATH+"/TaskMemStack.dep" } ;
Rule rdcpp431 = { {&cpp431,&obj} , {&dcpp431} , {&execpp431} } ;
Exe execpp431 = { "CC-DEP TaskMemStack.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/TaskMemStack.o"
 ,"../../Applied/CCore/src/TaskMemStack.cpp"
 ,"-MF"
 ,OBJ_PATH+"/TaskMemStack.dep"
} } ;

Target vdcpp431 = { "TaskMemStack.vm.dep" , OBJ_PATH+"/TaskMemStack.vm.dep" } ;
Rule rvdcpp431 = { {&dcpp431} , {&vdcpp431} , {&exedcpp431} } ;
Exe exedcpp431 = { "CC-VM-DEP TaskMemStack.cpp" , VMDEP , { OBJ_PATH+"/TaskMemStack.dep" , OBJ_PATH+"/TaskMemStack.vm.dep" , "431" } } ;

Target cpp432 = { "TempArray.cpp" , "../../Fundamental/CCore/src/./array/TempArray.cpp" } ;
Target dcpp432 = { "TempArray.dep" , OBJ_PATH+"/TempArray.dep" } ;
Rule rdcpp432 = { {&cpp432,&obj} , {&dcpp432} , {&execpp432} } ;
Exe execpp432 = { "CC-DEP TempArray.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/TempArray.o"
 ,"../../Fundamental/CCore/src/./array/TempArray.cpp"
 ,"-MF"
 ,OBJ_PATH+"/TempArray.dep"
} } ;

Target vdcpp432 = { "TempArray.vm.dep" , OBJ_PATH+"/TempArray.vm.dep" } ;
Rule rvdcpp432 = { {&dcpp432} , {&vdcpp432} , {&exedcpp432} } ;
Exe exedcpp432 = { "CC-VM-DEP TempArray.cpp" , VMDEP , { OBJ_PATH+"/TempArray.dep" , OBJ_PATH+"/TempArray.vm.dep" , "432" } } ;

Target cpp433 = { "TextLabel.cpp" , "../../Simple/CCore/src/TextLabel.cpp" } ;
Target dcpp433 = { "TextLabel.dep" , OBJ_PATH+"/TextLabel.dep" } ;
Rule rdcpp433 = { {&cpp433,&obj} , {&dcpp433} , {&execpp433} } ;
Exe execpp433 = { "CC-DEP TextLabel.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/TextLabel.o"
 ,"../../Simple/CCore/src/TextLabel.cpp"
 ,"-MF"
 ,OBJ_PATH+"/TextLabel.dep"
} } ;

Target vdcpp433 = { "TextLabel.vm.dep" , OBJ_PATH+"/TextLabel.vm.dep" } ;
Rule rvdcpp433 = { {&dcpp433} , {&vdcpp433} , {&exedcpp433} } ;
Exe exedcpp433 = { "CC-VM-DEP TextLabel.cpp" , VMDEP , { OBJ_PATH+"/TextLabel.dep" , OBJ_PATH+"/TextLabel.vm.dep" , "433" } } ;

Target cpp434 = { "TextTools.cpp" , "../../Fundamental/CCore/src/TextTools.cpp" } ;
Target dcpp434 = { "TextTools.dep" , OBJ_PATH+"/TextTools.dep" } ;
Rule rdcpp434 = { {&cpp434,&obj} , {&dcpp434} , {&execpp434} } ;
Exe execpp434 = { "CC-DEP TextTools.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/TextTools.o"
 ,"../../Fundamental/CCore/src/TextTools.cpp"
 ,"-MF"
 ,OBJ_PATH+"/TextTools.dep"
} } ;

Target vdcpp434 = { "TextTools.vm.dep" , OBJ_PATH+"/TextTools.vm.dep" } ;
Rule rvdcpp434 = { {&dcpp434} , {&vdcpp434} , {&exedcpp434} } ;
Exe exedcpp434 = { "CC-VM-DEP TextTools.cpp" , VMDEP , { OBJ_PATH+"/TextTools.dep" , OBJ_PATH+"/TextTools.vm.dep" , "434" } } ;

Target cpp435 = { "TimeScope.cpp" , "../../Simple/CCore/src/TimeScope.cpp" } ;
Target dcpp435 = { "TimeScope.dep" , OBJ_PATH+"/TimeScope.dep" } ;
Rule rdcpp435 = { {&cpp435,&obj} , {&dcpp435} , {&execpp435} } ;
Exe execpp435 = { "CC-DEP TimeScope.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/TimeScope.o"
 ,"../../Simple/CCore/src/TimeScope.cpp"
 ,"-MF"
 ,OBJ_PATH+"/TimeScope.dep"
} } ;

Target vdcpp435 = { "TimeScope.vm.dep" , OBJ_PATH+"/TimeScope.vm.dep" } ;
Rule rvdcpp435 = { {&dcpp435} , {&vdcpp435} , {&exedcpp435} } ;
Exe exedcpp435 = { "CC-VM-DEP TimeScope.cpp" , VMDEP , { OBJ_PATH+"/TimeScope.dep" , OBJ_PATH+"/TimeScope.vm.dep" , "435" } } ;

Target cpp436 = { "Timer.cpp" , "../../Simple/CCore/src/Timer.cpp" } ;
Target dcpp436 = { "Timer.dep" , OBJ_PATH+"/Timer.dep" } ;
Rule rdcpp436 = { {&cpp436,&obj} , {&dcpp436} , {&execpp436} } ;
Exe execpp436 = { "CC-DEP Timer.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Timer.o"
 ,"../../Simple/CCore/src/Timer.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Timer.dep"
} } ;

Target vdcpp436 = { "Timer.vm.dep" , OBJ_PATH+"/Timer.vm.dep" } ;
Rule rvdcpp436 = { {&dcpp436} , {&vdcpp436} , {&exedcpp436} } ;
Exe exedcpp436 = { "CC-VM-DEP Timer.cpp" , VMDEP , { OBJ_PATH+"/Timer.dep" , OBJ_PATH+"/Timer.vm.dep" , "436" } } ;

Target cpp437 = { "TlsSlot.cpp" , "../../Simple/CCore/src/TlsSlot.cpp" } ;
Target dcpp437 = { "TlsSlot.dep" , OBJ_PATH+"/TlsSlot.dep" } ;
Rule rdcpp437 = { {&cpp437,&obj} , {&dcpp437} , {&execpp437} } ;
Exe execpp437 = { "CC-DEP TlsSlot.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/TlsSlot.o"
 ,"../../Simple/CCore/src/TlsSlot.cpp"
 ,"-MF"
 ,OBJ_PATH+"/TlsSlot.dep"
} } ;

Target vdcpp437 = { "TlsSlot.vm.dep" , OBJ_PATH+"/TlsSlot.vm.dep" } ;
Rule rvdcpp437 = { {&dcpp437} , {&vdcpp437} , {&exedcpp437} } ;
Exe exedcpp437 = { "CC-VM-DEP TlsSlot.cpp" , VMDEP , { OBJ_PATH+"/TlsSlot.dep" , OBJ_PATH+"/TlsSlot.vm.dep" , "437" } } ;

Target cpp438 = { "ToMemBase.cpp" , "../../Applied/CCore/src/ToMemBase.cpp" } ;
Target dcpp438 = { "ToMemBase.dep" , OBJ_PATH+"/ToMemBase.dep" } ;
Rule rdcpp438 = { {&cpp438,&obj} , {&dcpp438} , {&execpp438} } ;
Exe execpp438 = { "CC-DEP ToMemBase.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ToMemBase.o"
 ,"../../Applied/CCore/src/ToMemBase.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ToMemBase.dep"
} } ;

Target vdcpp438 = { "ToMemBase.vm.dep" , OBJ_PATH+"/ToMemBase.vm.dep" } ;
Rule rvdcpp438 = { {&dcpp438} , {&vdcpp438} , {&exedcpp438} } ;
Exe exedcpp438 = { "CC-VM-DEP ToMemBase.cpp" , VMDEP , { OBJ_PATH+"/ToMemBase.dep" , OBJ_PATH+"/ToMemBase.vm.dep" , "438" } } ;

Target cpp439 = { "ToMoveCtor.cpp" , "../../Simple/CCore/src/ToMoveCtor.cpp" } ;
Target dcpp439 = { "ToMoveCtor.dep" , OBJ_PATH+"/ToMoveCtor.dep" } ;
Rule rdcpp439 = { {&cpp439,&obj} , {&dcpp439} , {&execpp439} } ;
Exe execpp439 = { "CC-DEP ToMoveCtor.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ToMoveCtor.o"
 ,"../../Simple/CCore/src/ToMoveCtor.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ToMoveCtor.dep"
} } ;

Target vdcpp439 = { "ToMoveCtor.vm.dep" , OBJ_PATH+"/ToMoveCtor.vm.dep" } ;
Rule rvdcpp439 = { {&dcpp439} , {&vdcpp439} , {&exedcpp439} } ;
Exe exedcpp439 = { "CC-VM-DEP ToMoveCtor.cpp" , VMDEP , { OBJ_PATH+"/ToMoveCtor.dep" , OBJ_PATH+"/ToMoveCtor.vm.dep" , "439" } } ;

Target cpp440 = { "ToolFrame.cpp" , "../../Desktop/Lib/CCore/src/./video/ToolFrame.cpp" } ;
Target dcpp440 = { "ToolFrame.dep" , OBJ_PATH+"/ToolFrame.dep" } ;
Rule rdcpp440 = { {&cpp440,&obj} , {&dcpp440} , {&execpp440} } ;
Exe execpp440 = { "CC-DEP ToolFrame.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/ToolFrame.o"
 ,"../../Desktop/Lib/CCore/src/./video/ToolFrame.cpp"
 ,"-MF"
 ,OBJ_PATH+"/ToolFrame.dep"
} } ;

Target vdcpp440 = { "ToolFrame.vm.dep" , OBJ_PATH+"/ToolFrame.vm.dep" } ;
Rule rvdcpp440 = { {&dcpp440} , {&vdcpp440} , {&exedcpp440} } ;
Exe exedcpp440 = { "CC-VM-DEP ToolFrame.cpp" , VMDEP , { OBJ_PATH+"/ToolFrame.dep" , OBJ_PATH+"/ToolFrame.vm.dep" , "440" } } ;

Target cpp441 = { "Tree.cpp" , "../../Fundamental/CCore/src/Tree.cpp" } ;
Target dcpp441 = { "Tree.dep" , OBJ_PATH+"/Tree.dep" } ;
Rule rdcpp441 = { {&cpp441,&obj} , {&dcpp441} , {&execpp441} } ;
Exe execpp441 = { "CC-DEP Tree.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Tree.o"
 ,"../../Fundamental/CCore/src/Tree.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Tree.dep"
} } ;

Target vdcpp441 = { "Tree.vm.dep" , OBJ_PATH+"/Tree.vm.dep" } ;
Rule rvdcpp441 = { {&dcpp441} , {&vdcpp441} , {&exedcpp441} } ;
Exe exedcpp441 = { "CC-VM-DEP Tree.cpp" , VMDEP , { OBJ_PATH+"/Tree.dep" , OBJ_PATH+"/Tree.vm.dep" , "441" } } ;

Target cpp442 = { "TreeBase.cpp" , "../../Fundamental/CCore/src/./tree/TreeBase.cpp" } ;
Target dcpp442 = { "TreeBase.dep" , OBJ_PATH+"/TreeBase.dep" } ;
Rule rdcpp442 = { {&cpp442,&obj} , {&dcpp442} , {&execpp442} } ;
Exe execpp442 = { "CC-DEP TreeBase.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/TreeBase.o"
 ,"../../Fundamental/CCore/src/./tree/TreeBase.cpp"
 ,"-MF"
 ,OBJ_PATH+"/TreeBase.dep"
} } ;

Target vdcpp442 = { "TreeBase.vm.dep" , OBJ_PATH+"/TreeBase.vm.dep" } ;
Rule rvdcpp442 = { {&dcpp442} , {&vdcpp442} , {&exedcpp442} } ;
Exe exedcpp442 = { "CC-VM-DEP TreeBase.cpp" , VMDEP , { OBJ_PATH+"/TreeBase.dep" , OBJ_PATH+"/TreeBase.vm.dep" , "442" } } ;

Target cpp443 = { "TreeLink.cpp" , "../../Fundamental/CCore/src/./tree/TreeLink.cpp" } ;
Target dcpp443 = { "TreeLink.dep" , OBJ_PATH+"/TreeLink.dep" } ;
Rule rdcpp443 = { {&cpp443,&obj} , {&dcpp443} , {&execpp443} } ;
Exe execpp443 = { "CC-DEP TreeLink.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/TreeLink.o"
 ,"../../Fundamental/CCore/src/./tree/TreeLink.cpp"
 ,"-MF"
 ,OBJ_PATH+"/TreeLink.dep"
} } ;

Target vdcpp443 = { "TreeLink.vm.dep" , OBJ_PATH+"/TreeLink.vm.dep" } ;
Rule rvdcpp443 = { {&dcpp443} , {&vdcpp443} , {&exedcpp443} } ;
Exe exedcpp443 = { "CC-VM-DEP TreeLink.cpp" , VMDEP , { OBJ_PATH+"/TreeLink.dep" , OBJ_PATH+"/TreeLink.vm.dep" , "443" } } ;

Target cpp444 = { "TreeMap.cpp" , "../../Fundamental/CCore/src/TreeMap.cpp" } ;
Target dcpp444 = { "TreeMap.dep" , OBJ_PATH+"/TreeMap.dep" } ;
Rule rdcpp444 = { {&cpp444,&obj} , {&dcpp444} , {&execpp444} } ;
Exe execpp444 = { "CC-DEP TreeMap.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/TreeMap.o"
 ,"../../Fundamental/CCore/src/TreeMap.cpp"
 ,"-MF"
 ,OBJ_PATH+"/TreeMap.dep"
} } ;

Target vdcpp444 = { "TreeMap.vm.dep" , OBJ_PATH+"/TreeMap.vm.dep" } ;
Rule rvdcpp444 = { {&dcpp444} , {&vdcpp444} , {&exedcpp444} } ;
Exe exedcpp444 = { "CC-VM-DEP TreeMap.cpp" , VMDEP , { OBJ_PATH+"/TreeMap.dep" , OBJ_PATH+"/TreeMap.vm.dep" , "444" } } ;

Target cpp445 = { "TreeUpLink.cpp" , "../../Fundamental/CCore/src/./tree/TreeUpLink.cpp" } ;
Target dcpp445 = { "TreeUpLink.dep" , OBJ_PATH+"/TreeUpLink.dep" } ;
Rule rdcpp445 = { {&cpp445,&obj} , {&dcpp445} , {&execpp445} } ;
Exe execpp445 = { "CC-DEP TreeUpLink.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/TreeUpLink.o"
 ,"../../Fundamental/CCore/src/./tree/TreeUpLink.cpp"
 ,"-MF"
 ,OBJ_PATH+"/TreeUpLink.dep"
} } ;

Target vdcpp445 = { "TreeUpLink.vm.dep" , OBJ_PATH+"/TreeUpLink.vm.dep" } ;
Rule rvdcpp445 = { {&dcpp445} , {&vdcpp445} , {&exedcpp445} } ;
Exe exedcpp445 = { "CC-VM-DEP TreeUpLink.cpp" , VMDEP , { OBJ_PATH+"/TreeUpLink.dep" , OBJ_PATH+"/TreeUpLink.vm.dep" , "445" } } ;

Target cpp446 = { "Tuple.cpp" , "../../Simple/CCore/src/Tuple.cpp" } ;
Target dcpp446 = { "Tuple.dep" , OBJ_PATH+"/Tuple.dep" } ;
Rule rdcpp446 = { {&cpp446,&obj} , {&dcpp446} , {&execpp446} } ;
Exe execpp446 = { "CC-DEP Tuple.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Tuple.o"
 ,"../../Simple/CCore/src/Tuple.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Tuple.dep"
} } ;

Target vdcpp446 = { "Tuple.vm.dep" , OBJ_PATH+"/Tuple.vm.dep" } ;
Rule rvdcpp446 = { {&dcpp446} , {&vdcpp446} , {&exedcpp446} } ;
Exe exedcpp446 = { "CC-VM-DEP Tuple.cpp" , VMDEP , { OBJ_PATH+"/Tuple.dep" , OBJ_PATH+"/Tuple.vm.dep" , "446" } } ;

Target cpp447 = { "TypeNumber.cpp" , "../../Fundamental/CCore/src/TypeNumber.cpp" } ;
Target dcpp447 = { "TypeNumber.dep" , OBJ_PATH+"/TypeNumber.dep" } ;
Rule rdcpp447 = { {&cpp447,&obj} , {&dcpp447} , {&execpp447} } ;
Exe execpp447 = { "CC-DEP TypeNumber.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/TypeNumber.o"
 ,"../../Fundamental/CCore/src/TypeNumber.cpp"
 ,"-MF"
 ,OBJ_PATH+"/TypeNumber.dep"
} } ;

Target vdcpp447 = { "TypeNumber.vm.dep" , OBJ_PATH+"/TypeNumber.vm.dep" } ;
Rule rvdcpp447 = { {&dcpp447} , {&vdcpp447} , {&exedcpp447} } ;
Exe exedcpp447 = { "CC-VM-DEP TypeNumber.cpp" , VMDEP , { OBJ_PATH+"/TypeNumber.dep" , OBJ_PATH+"/TypeNumber.vm.dep" , "447" } } ;

Target cpp448 = { "TypeSwitch.cpp" , "../../Simple/CCore/src/TypeSwitch.cpp" } ;
Target dcpp448 = { "TypeSwitch.dep" , OBJ_PATH+"/TypeSwitch.dep" } ;
Rule rdcpp448 = { {&cpp448,&obj} , {&dcpp448} , {&execpp448} } ;
Exe execpp448 = { "CC-DEP TypeSwitch.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/TypeSwitch.o"
 ,"../../Simple/CCore/src/TypeSwitch.cpp"
 ,"-MF"
 ,OBJ_PATH+"/TypeSwitch.dep"
} } ;

Target vdcpp448 = { "TypeSwitch.vm.dep" , OBJ_PATH+"/TypeSwitch.vm.dep" } ;
Rule rvdcpp448 = { {&dcpp448} , {&vdcpp448} , {&exedcpp448} } ;
Exe exedcpp448 = { "CC-VM-DEP TypeSwitch.cpp" , VMDEP , { OBJ_PATH+"/TypeSwitch.dep" , OBJ_PATH+"/TypeSwitch.vm.dep" , "448" } } ;

Target cpp449 = { "UDPDevice.cpp" , "../../HCore/CCore/src/./net/UDPDevice.cpp" } ;
Target dcpp449 = { "UDPDevice.dep" , OBJ_PATH+"/UDPDevice.dep" } ;
Rule rdcpp449 = { {&cpp449,&obj} , {&dcpp449} , {&execpp449} } ;
Exe execpp449 = { "CC-DEP UDPDevice.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/UDPDevice.o"
 ,"../../HCore/CCore/src/./net/UDPDevice.cpp"
 ,"-MF"
 ,OBJ_PATH+"/UDPDevice.dep"
} } ;

Target vdcpp449 = { "UDPDevice.vm.dep" , OBJ_PATH+"/UDPDevice.vm.dep" } ;
Rule rvdcpp449 = { {&dcpp449} , {&vdcpp449} , {&exedcpp449} } ;
Exe exedcpp449 = { "CC-VM-DEP UDPDevice.cpp" , VMDEP , { OBJ_PATH+"/UDPDevice.dep" , OBJ_PATH+"/UDPDevice.vm.dep" , "449" } } ;

Target cpp450 = { "UDPoint.cpp" , "../../Applied/CCore/src/./net/UDPoint.cpp" } ;
Target dcpp450 = { "UDPoint.dep" , OBJ_PATH+"/UDPoint.dep" } ;
Rule rdcpp450 = { {&cpp450,&obj} , {&dcpp450} , {&execpp450} } ;
Exe execpp450 = { "CC-DEP UDPoint.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/UDPoint.o"
 ,"../../Applied/CCore/src/./net/UDPoint.cpp"
 ,"-MF"
 ,OBJ_PATH+"/UDPoint.dep"
} } ;

Target vdcpp450 = { "UDPoint.vm.dep" , OBJ_PATH+"/UDPoint.vm.dep" } ;
Rule rvdcpp450 = { {&dcpp450} , {&vdcpp450} , {&exedcpp450} } ;
Exe exedcpp450 = { "CC-VM-DEP UDPoint.cpp" , VMDEP , { OBJ_PATH+"/UDPoint.dep" , OBJ_PATH+"/UDPoint.vm.dep" , "450" } } ;

Target cpp451 = { "UIntFunc.cpp" , "../../Simple/CCore/src/./gadget/UIntFunc.cpp" } ;
Target dcpp451 = { "UIntFunc.dep" , OBJ_PATH+"/UIntFunc.dep" } ;
Rule rdcpp451 = { {&cpp451,&obj} , {&dcpp451} , {&execpp451} } ;
Exe execpp451 = { "CC-DEP UIntFunc.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/UIntFunc.o"
 ,"../../Simple/CCore/src/./gadget/UIntFunc.cpp"
 ,"-MF"
 ,OBJ_PATH+"/UIntFunc.dep"
} } ;

Target vdcpp451 = { "UIntFunc.vm.dep" , OBJ_PATH+"/UIntFunc.vm.dep" } ;
Rule rvdcpp451 = { {&dcpp451} , {&vdcpp451} , {&exedcpp451} } ;
Exe exedcpp451 = { "CC-VM-DEP UIntFunc.cpp" , VMDEP , { OBJ_PATH+"/UIntFunc.dep" , OBJ_PATH+"/UIntFunc.vm.dep" , "451" } } ;

Target cpp452 = { "UIntSat.cpp" , "../../Simple/CCore/src/./gadget/UIntSat.cpp" } ;
Target dcpp452 = { "UIntSat.dep" , OBJ_PATH+"/UIntSat.dep" } ;
Rule rdcpp452 = { {&cpp452,&obj} , {&dcpp452} , {&execpp452} } ;
Exe execpp452 = { "CC-DEP UIntSat.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/UIntSat.o"
 ,"../../Simple/CCore/src/./gadget/UIntSat.cpp"
 ,"-MF"
 ,OBJ_PATH+"/UIntSat.dep"
} } ;

Target vdcpp452 = { "UIntSat.vm.dep" , OBJ_PATH+"/UIntSat.vm.dep" } ;
Rule rvdcpp452 = { {&dcpp452} , {&vdcpp452} , {&exedcpp452} } ;
Exe exedcpp452 = { "CC-VM-DEP UIntSat.cpp" , VMDEP , { OBJ_PATH+"/UIntSat.dep" , OBJ_PATH+"/UIntSat.vm.dep" , "452" } } ;

Target cpp453 = { "UIntSlowMulAlgo.cpp" , "../../Fundamental/CCore/src/./math/UIntSlowMulAlgo.cpp" } ;
Target dcpp453 = { "UIntSlowMulAlgo.dep" , OBJ_PATH+"/UIntSlowMulAlgo.dep" } ;
Rule rdcpp453 = { {&cpp453,&obj} , {&dcpp453} , {&execpp453} } ;
Exe execpp453 = { "CC-DEP UIntSlowMulAlgo.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/UIntSlowMulAlgo.o"
 ,"../../Fundamental/CCore/src/./math/UIntSlowMulAlgo.cpp"
 ,"-MF"
 ,OBJ_PATH+"/UIntSlowMulAlgo.dep"
} } ;

Target vdcpp453 = { "UIntSlowMulAlgo.vm.dep" , OBJ_PATH+"/UIntSlowMulAlgo.vm.dep" } ;
Rule rvdcpp453 = { {&dcpp453} , {&vdcpp453} , {&exedcpp453} } ;
Exe exedcpp453 = { "CC-VM-DEP UIntSlowMulAlgo.cpp" , VMDEP , { OBJ_PATH+"/UIntSlowMulAlgo.dep" , OBJ_PATH+"/UIntSlowMulAlgo.vm.dep" , "453" } } ;

Target cpp454 = { "UIntSplit.cpp" , "../../Simple/CCore/src/UIntSplit.cpp" } ;
Target dcpp454 = { "UIntSplit.dep" , OBJ_PATH+"/UIntSplit.dep" } ;
Rule rdcpp454 = { {&cpp454,&obj} , {&dcpp454} , {&execpp454} } ;
Exe execpp454 = { "CC-DEP UIntSplit.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/UIntSplit.o"
 ,"../../Simple/CCore/src/UIntSplit.cpp"
 ,"-MF"
 ,OBJ_PATH+"/UIntSplit.dep"
} } ;

Target vdcpp454 = { "UIntSplit.vm.dep" , OBJ_PATH+"/UIntSplit.vm.dep" } ;
Rule rvdcpp454 = { {&dcpp454} , {&vdcpp454} , {&exedcpp454} } ;
Exe exedcpp454 = { "CC-VM-DEP UIntSplit.cpp" , VMDEP , { OBJ_PATH+"/UIntSplit.dep" , OBJ_PATH+"/UIntSplit.vm.dep" , "454" } } ;

Target cpp455 = { "Unid.cpp" , "../../Fundamental/CCore/src/Unid.cpp" } ;
Target dcpp455 = { "Unid.dep" , OBJ_PATH+"/Unid.dep" } ;
Rule rdcpp455 = { {&cpp455,&obj} , {&dcpp455} , {&execpp455} } ;
Exe execpp455 = { "CC-DEP Unid.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Unid.o"
 ,"../../Fundamental/CCore/src/Unid.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Unid.dep"
} } ;

Target vdcpp455 = { "Unid.vm.dep" , OBJ_PATH+"/Unid.vm.dep" } ;
Rule rvdcpp455 = { {&dcpp455} , {&vdcpp455} , {&exedcpp455} } ;
Exe exedcpp455 = { "CC-VM-DEP Unid.cpp" , VMDEP , { OBJ_PATH+"/Unid.dep" , OBJ_PATH+"/Unid.vm.dep" , "455" } } ;

Target cpp456 = { "UserAction.cpp" , "../../Desktop/Core/CCore/src/./video/UserAction.cpp" } ;
Target dcpp456 = { "UserAction.dep" , OBJ_PATH+"/UserAction.dep" } ;
Rule rdcpp456 = { {&cpp456,&obj} , {&dcpp456} , {&execpp456} } ;
Exe execpp456 = { "CC-DEP UserAction.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/UserAction.o"
 ,"../../Desktop/Core/CCore/src/./video/UserAction.cpp"
 ,"-MF"
 ,OBJ_PATH+"/UserAction.dep"
} } ;

Target vdcpp456 = { "UserAction.vm.dep" , OBJ_PATH+"/UserAction.vm.dep" } ;
Rule rvdcpp456 = { {&dcpp456} , {&vdcpp456} , {&exedcpp456} } ;
Exe exedcpp456 = { "CC-VM-DEP UserAction.cpp" , VMDEP , { OBJ_PATH+"/UserAction.dep" , OBJ_PATH+"/UserAction.vm.dep" , "456" } } ;

Target cpp457 = { "UserPreference.cpp" , "../../Desktop/Lib/CCore/src/./video/UserPreference.cpp" } ;
Target dcpp457 = { "UserPreference.dep" , OBJ_PATH+"/UserPreference.dep" } ;
Rule rdcpp457 = { {&cpp457,&obj} , {&dcpp457} , {&execpp457} } ;
Exe execpp457 = { "CC-DEP UserPreference.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/UserPreference.o"
 ,"../../Desktop/Lib/CCore/src/./video/UserPreference.cpp"
 ,"-MF"
 ,OBJ_PATH+"/UserPreference.dep"
} } ;

Target vdcpp457 = { "UserPreference.vm.dep" , OBJ_PATH+"/UserPreference.vm.dep" } ;
Rule rvdcpp457 = { {&dcpp457} , {&vdcpp457} , {&exedcpp457} } ;
Exe exedcpp457 = { "CC-VM-DEP UserPreference.cpp" , VMDEP , { OBJ_PATH+"/UserPreference.dep" , OBJ_PATH+"/UserPreference.vm.dep" , "457" } } ;

Target cpp458 = { "Utf8.cpp" , "../../Simple/CCore/src/Utf8.cpp" } ;
Target dcpp458 = { "Utf8.dep" , OBJ_PATH+"/Utf8.dep" } ;
Rule rdcpp458 = { {&cpp458,&obj} , {&dcpp458} , {&execpp458} } ;
Exe execpp458 = { "CC-DEP Utf8.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Utf8.o"
 ,"../../Simple/CCore/src/Utf8.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Utf8.dep"
} } ;

Target vdcpp458 = { "Utf8.vm.dep" , OBJ_PATH+"/Utf8.vm.dep" } ;
Rule rvdcpp458 = { {&dcpp458} , {&vdcpp458} , {&exedcpp458} } ;
Exe exedcpp458 = { "CC-VM-DEP Utf8.cpp" , VMDEP , { OBJ_PATH+"/Utf8.dep" , OBJ_PATH+"/Utf8.vm.dep" , "458" } } ;

Target cpp459 = { "UtilFunc.cpp" , "../../Simple/CCore/src/./gadget/UtilFunc.cpp" } ;
Target dcpp459 = { "UtilFunc.dep" , OBJ_PATH+"/UtilFunc.dep" } ;
Rule rdcpp459 = { {&cpp459,&obj} , {&dcpp459} , {&execpp459} } ;
Exe execpp459 = { "CC-DEP UtilFunc.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/UtilFunc.o"
 ,"../../Simple/CCore/src/./gadget/UtilFunc.cpp"
 ,"-MF"
 ,OBJ_PATH+"/UtilFunc.dep"
} } ;

Target vdcpp459 = { "UtilFunc.vm.dep" , OBJ_PATH+"/UtilFunc.vm.dep" } ;
Rule rvdcpp459 = { {&dcpp459} , {&vdcpp459} , {&exedcpp459} } ;
Exe exedcpp459 = { "CC-VM-DEP UtilFunc.cpp" , VMDEP , { OBJ_PATH+"/UtilFunc.dep" , OBJ_PATH+"/UtilFunc.vm.dep" , "459" } } ;

Target cpp460 = { "VideoConsole.cpp" , "../../Applied/CCore/src/./video/VideoConsole.cpp" } ;
Target dcpp460 = { "VideoConsole.dep" , OBJ_PATH+"/VideoConsole.dep" } ;
Rule rdcpp460 = { {&cpp460,&obj} , {&dcpp460} , {&execpp460} } ;
Exe execpp460 = { "CC-DEP VideoConsole.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/VideoConsole.o"
 ,"../../Applied/CCore/src/./video/VideoConsole.cpp"
 ,"-MF"
 ,OBJ_PATH+"/VideoConsole.dep"
} } ;

Target vdcpp460 = { "VideoConsole.vm.dep" , OBJ_PATH+"/VideoConsole.vm.dep" } ;
Rule rvdcpp460 = { {&dcpp460} , {&vdcpp460} , {&exedcpp460} } ;
Exe exedcpp460 = { "CC-VM-DEP VideoConsole.cpp" , VMDEP , { OBJ_PATH+"/VideoConsole.dep" , OBJ_PATH+"/VideoConsole.vm.dep" , "460" } } ;

Target cpp461 = { "VideoDevice.cpp" , "../../Applied/CCore/src/./video/VideoDevice.cpp" } ;
Target dcpp461 = { "VideoDevice.dep" , OBJ_PATH+"/VideoDevice.dep" } ;
Rule rdcpp461 = { {&cpp461,&obj} , {&dcpp461} , {&execpp461} } ;
Exe execpp461 = { "CC-DEP VideoDevice.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/VideoDevice.o"
 ,"../../Applied/CCore/src/./video/VideoDevice.cpp"
 ,"-MF"
 ,OBJ_PATH+"/VideoDevice.dep"
} } ;

Target vdcpp461 = { "VideoDevice.vm.dep" , OBJ_PATH+"/VideoDevice.vm.dep" } ;
Rule rvdcpp461 = { {&dcpp461} , {&vdcpp461} , {&exedcpp461} } ;
Exe exedcpp461 = { "CC-VM-DEP VideoDevice.cpp" , VMDEP , { OBJ_PATH+"/VideoDevice.dep" , OBJ_PATH+"/VideoDevice.vm.dep" , "461" } } ;

Target cpp462 = { "Volume.cpp" , "../../Fundamental/CCore/src/Volume.cpp" } ;
Target dcpp462 = { "Volume.dep" , OBJ_PATH+"/Volume.dep" } ;
Rule rdcpp462 = { {&cpp462,&obj} , {&dcpp462} , {&execpp462} } ;
Exe execpp462 = { "CC-DEP Volume.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Volume.o"
 ,"../../Fundamental/CCore/src/Volume.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Volume.dep"
} } ;

Target vdcpp462 = { "Volume.vm.dep" , OBJ_PATH+"/Volume.vm.dep" } ;
Rule rvdcpp462 = { {&dcpp462} , {&vdcpp462} , {&exedcpp462} } ;
Exe exedcpp462 = { "CC-VM-DEP Volume.cpp" , VMDEP , { OBJ_PATH+"/Volume.dep" , OBJ_PATH+"/Volume.vm.dep" , "462" } } ;

Target cpp463 = { "Window.Blank.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.Blank.cpp" } ;
Target dcpp463 = { "Window.Blank.dep" , OBJ_PATH+"/Window.Blank.dep" } ;
Rule rdcpp463 = { {&cpp463,&obj} , {&dcpp463} , {&execpp463} } ;
Exe execpp463 = { "CC-DEP Window.Blank.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Window.Blank.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.Blank.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Window.Blank.dep"
} } ;

Target vdcpp463 = { "Window.Blank.vm.dep" , OBJ_PATH+"/Window.Blank.vm.dep" } ;
Rule rvdcpp463 = { {&dcpp463} , {&vdcpp463} , {&exedcpp463} } ;
Exe exedcpp463 = { "CC-VM-DEP Window.Blank.cpp" , VMDEP , { OBJ_PATH+"/Window.Blank.dep" , OBJ_PATH+"/Window.Blank.vm.dep" , "463" } } ;

Target cpp464 = { "Window.Button.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.Button.cpp" } ;
Target dcpp464 = { "Window.Button.dep" , OBJ_PATH+"/Window.Button.dep" } ;
Rule rdcpp464 = { {&cpp464,&obj} , {&dcpp464} , {&execpp464} } ;
Exe execpp464 = { "CC-DEP Window.Button.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Window.Button.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.Button.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Window.Button.dep"
} } ;

Target vdcpp464 = { "Window.Button.vm.dep" , OBJ_PATH+"/Window.Button.vm.dep" } ;
Rule rvdcpp464 = { {&dcpp464} , {&vdcpp464} , {&exedcpp464} } ;
Exe exedcpp464 = { "CC-VM-DEP Window.Button.cpp" , VMDEP , { OBJ_PATH+"/Window.Button.dep" , OBJ_PATH+"/Window.Button.vm.dep" , "464" } } ;

Target cpp465 = { "Window.Check.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.Check.cpp" } ;
Target dcpp465 = { "Window.Check.dep" , OBJ_PATH+"/Window.Check.dep" } ;
Rule rdcpp465 = { {&cpp465,&obj} , {&dcpp465} , {&execpp465} } ;
Exe execpp465 = { "CC-DEP Window.Check.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Window.Check.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.Check.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Window.Check.dep"
} } ;

Target vdcpp465 = { "Window.Check.vm.dep" , OBJ_PATH+"/Window.Check.vm.dep" } ;
Rule rvdcpp465 = { {&dcpp465} , {&vdcpp465} , {&exedcpp465} } ;
Exe exedcpp465 = { "CC-VM-DEP Window.Check.cpp" , VMDEP , { OBJ_PATH+"/Window.Check.dep" , OBJ_PATH+"/Window.Check.vm.dep" , "465" } } ;

Target cpp466 = { "Window.Decor.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.Decor.cpp" } ;
Target dcpp466 = { "Window.Decor.dep" , OBJ_PATH+"/Window.Decor.dep" } ;
Rule rdcpp466 = { {&cpp466,&obj} , {&dcpp466} , {&execpp466} } ;
Exe execpp466 = { "CC-DEP Window.Decor.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Window.Decor.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.Decor.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Window.Decor.dep"
} } ;

Target vdcpp466 = { "Window.Decor.vm.dep" , OBJ_PATH+"/Window.Decor.vm.dep" } ;
Rule rvdcpp466 = { {&dcpp466} , {&vdcpp466} , {&exedcpp466} } ;
Exe exedcpp466 = { "CC-VM-DEP Window.Decor.cpp" , VMDEP , { OBJ_PATH+"/Window.Decor.dep" , OBJ_PATH+"/Window.Decor.vm.dep" , "466" } } ;

Target cpp467 = { "Window.DragFrame.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.DragFrame.cpp" } ;
Target dcpp467 = { "Window.DragFrame.dep" , OBJ_PATH+"/Window.DragFrame.dep" } ;
Rule rdcpp467 = { {&cpp467,&obj} , {&dcpp467} , {&execpp467} } ;
Exe execpp467 = { "CC-DEP Window.DragFrame.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Window.DragFrame.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.DragFrame.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Window.DragFrame.dep"
} } ;

Target vdcpp467 = { "Window.DragFrame.vm.dep" , OBJ_PATH+"/Window.DragFrame.vm.dep" } ;
Rule rvdcpp467 = { {&dcpp467} , {&vdcpp467} , {&exedcpp467} } ;
Exe exedcpp467 = { "CC-VM-DEP Window.DragFrame.cpp" , VMDEP , { OBJ_PATH+"/Window.DragFrame.dep" , OBJ_PATH+"/Window.DragFrame.vm.dep" , "467" } } ;

Target cpp468 = { "Window.FireButton.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.FireButton.cpp" } ;
Target dcpp468 = { "Window.FireButton.dep" , OBJ_PATH+"/Window.FireButton.dep" } ;
Rule rdcpp468 = { {&cpp468,&obj} , {&dcpp468} , {&execpp468} } ;
Exe execpp468 = { "CC-DEP Window.FireButton.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Window.FireButton.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.FireButton.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Window.FireButton.dep"
} } ;

Target vdcpp468 = { "Window.FireButton.vm.dep" , OBJ_PATH+"/Window.FireButton.vm.dep" } ;
Rule rvdcpp468 = { {&dcpp468} , {&vdcpp468} , {&exedcpp468} } ;
Exe exedcpp468 = { "CC-VM-DEP Window.FireButton.cpp" , VMDEP , { OBJ_PATH+"/Window.FireButton.dep" , OBJ_PATH+"/Window.FireButton.vm.dep" , "468" } } ;

Target cpp469 = { "Window.Info.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.Info.cpp" } ;
Target dcpp469 = { "Window.Info.dep" , OBJ_PATH+"/Window.Info.dep" } ;
Rule rdcpp469 = { {&cpp469,&obj} , {&dcpp469} , {&execpp469} } ;
Exe execpp469 = { "CC-DEP Window.Info.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Window.Info.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.Info.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Window.Info.dep"
} } ;

Target vdcpp469 = { "Window.Info.vm.dep" , OBJ_PATH+"/Window.Info.vm.dep" } ;
Rule rvdcpp469 = { {&dcpp469} , {&vdcpp469} , {&exedcpp469} } ;
Exe exedcpp469 = { "CC-VM-DEP Window.Info.cpp" , VMDEP , { OBJ_PATH+"/Window.Info.dep" , OBJ_PATH+"/Window.Info.vm.dep" , "469" } } ;

Target cpp470 = { "Window.Light.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.Light.cpp" } ;
Target dcpp470 = { "Window.Light.dep" , OBJ_PATH+"/Window.Light.dep" } ;
Rule rdcpp470 = { {&cpp470,&obj} , {&dcpp470} , {&execpp470} } ;
Exe execpp470 = { "CC-DEP Window.Light.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Window.Light.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.Light.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Window.Light.dep"
} } ;

Target vdcpp470 = { "Window.Light.vm.dep" , OBJ_PATH+"/Window.Light.vm.dep" } ;
Rule rvdcpp470 = { {&dcpp470} , {&vdcpp470} , {&exedcpp470} } ;
Exe exedcpp470 = { "CC-VM-DEP Window.Light.cpp" , VMDEP , { OBJ_PATH+"/Window.Light.dep" , OBJ_PATH+"/Window.Light.vm.dep" , "470" } } ;

Target cpp471 = { "Window.LineEdit.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.LineEdit.cpp" } ;
Target dcpp471 = { "Window.LineEdit.dep" , OBJ_PATH+"/Window.LineEdit.dep" } ;
Rule rdcpp471 = { {&cpp471,&obj} , {&dcpp471} , {&execpp471} } ;
Exe execpp471 = { "CC-DEP Window.LineEdit.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Window.LineEdit.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.LineEdit.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Window.LineEdit.dep"
} } ;

Target vdcpp471 = { "Window.LineEdit.vm.dep" , OBJ_PATH+"/Window.LineEdit.vm.dep" } ;
Rule rvdcpp471 = { {&dcpp471} , {&vdcpp471} , {&exedcpp471} } ;
Exe exedcpp471 = { "CC-VM-DEP Window.LineEdit.cpp" , VMDEP , { OBJ_PATH+"/Window.LineEdit.dep" , OBJ_PATH+"/Window.LineEdit.vm.dep" , "471" } } ;

Target cpp472 = { "Window.Progress.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.Progress.cpp" } ;
Target dcpp472 = { "Window.Progress.dep" , OBJ_PATH+"/Window.Progress.dep" } ;
Rule rdcpp472 = { {&cpp472,&obj} , {&dcpp472} , {&execpp472} } ;
Exe execpp472 = { "CC-DEP Window.Progress.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Window.Progress.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.Progress.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Window.Progress.dep"
} } ;

Target vdcpp472 = { "Window.Progress.vm.dep" , OBJ_PATH+"/Window.Progress.vm.dep" } ;
Rule rvdcpp472 = { {&dcpp472} , {&vdcpp472} , {&exedcpp472} } ;
Exe exedcpp472 = { "CC-VM-DEP Window.Progress.cpp" , VMDEP , { OBJ_PATH+"/Window.Progress.dep" , OBJ_PATH+"/Window.Progress.vm.dep" , "472" } } ;

Target cpp473 = { "Window.Radio.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.Radio.cpp" } ;
Target dcpp473 = { "Window.Radio.dep" , OBJ_PATH+"/Window.Radio.dep" } ;
Rule rdcpp473 = { {&cpp473,&obj} , {&dcpp473} , {&execpp473} } ;
Exe execpp473 = { "CC-DEP Window.Radio.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Window.Radio.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.Radio.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Window.Radio.dep"
} } ;

Target vdcpp473 = { "Window.Radio.vm.dep" , OBJ_PATH+"/Window.Radio.vm.dep" } ;
Rule rvdcpp473 = { {&dcpp473} , {&vdcpp473} , {&exedcpp473} } ;
Exe exedcpp473 = { "CC-VM-DEP Window.Radio.cpp" , VMDEP , { OBJ_PATH+"/Window.Radio.dep" , OBJ_PATH+"/Window.Radio.vm.dep" , "473" } } ;

Target cpp474 = { "Window.RunButton.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.RunButton.cpp" } ;
Target dcpp474 = { "Window.RunButton.dep" , OBJ_PATH+"/Window.RunButton.dep" } ;
Rule rdcpp474 = { {&cpp474,&obj} , {&dcpp474} , {&execpp474} } ;
Exe execpp474 = { "CC-DEP Window.RunButton.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Window.RunButton.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.RunButton.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Window.RunButton.dep"
} } ;

Target vdcpp474 = { "Window.RunButton.vm.dep" , OBJ_PATH+"/Window.RunButton.vm.dep" } ;
Rule rvdcpp474 = { {&dcpp474} , {&vdcpp474} , {&exedcpp474} } ;
Exe exedcpp474 = { "CC-VM-DEP Window.RunButton.cpp" , VMDEP , { OBJ_PATH+"/Window.RunButton.dep" , OBJ_PATH+"/Window.RunButton.vm.dep" , "474" } } ;

Target cpp475 = { "Window.Scroll.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.Scroll.cpp" } ;
Target dcpp475 = { "Window.Scroll.dep" , OBJ_PATH+"/Window.Scroll.dep" } ;
Rule rdcpp475 = { {&cpp475,&obj} , {&dcpp475} , {&execpp475} } ;
Exe execpp475 = { "CC-DEP Window.Scroll.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Window.Scroll.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.Scroll.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Window.Scroll.dep"
} } ;

Target vdcpp475 = { "Window.Scroll.vm.dep" , OBJ_PATH+"/Window.Scroll.vm.dep" } ;
Rule rvdcpp475 = { {&dcpp475} , {&vdcpp475} , {&exedcpp475} } ;
Exe exedcpp475 = { "CC-VM-DEP Window.Scroll.cpp" , VMDEP , { OBJ_PATH+"/Window.Scroll.dep" , OBJ_PATH+"/Window.Scroll.vm.dep" , "475" } } ;

Target cpp476 = { "Window.ScrollList.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.ScrollList.cpp" } ;
Target dcpp476 = { "Window.ScrollList.dep" , OBJ_PATH+"/Window.ScrollList.dep" } ;
Rule rdcpp476 = { {&cpp476,&obj} , {&dcpp476} , {&execpp476} } ;
Exe execpp476 = { "CC-DEP Window.ScrollList.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Window.ScrollList.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.ScrollList.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Window.ScrollList.dep"
} } ;

Target vdcpp476 = { "Window.ScrollList.vm.dep" , OBJ_PATH+"/Window.ScrollList.vm.dep" } ;
Rule rvdcpp476 = { {&dcpp476} , {&vdcpp476} , {&exedcpp476} } ;
Exe exedcpp476 = { "CC-VM-DEP Window.ScrollList.cpp" , VMDEP , { OBJ_PATH+"/Window.ScrollList.dep" , OBJ_PATH+"/Window.ScrollList.vm.dep" , "476" } } ;

Target cpp477 = { "Window.Scrollable.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.Scrollable.cpp" } ;
Target dcpp477 = { "Window.Scrollable.dep" , OBJ_PATH+"/Window.Scrollable.dep" } ;
Rule rdcpp477 = { {&cpp477,&obj} , {&dcpp477} , {&execpp477} } ;
Exe execpp477 = { "CC-DEP Window.Scrollable.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Window.Scrollable.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.Scrollable.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Window.Scrollable.dep"
} } ;

Target vdcpp477 = { "Window.Scrollable.vm.dep" , OBJ_PATH+"/Window.Scrollable.vm.dep" } ;
Rule rvdcpp477 = { {&dcpp477} , {&vdcpp477} , {&exedcpp477} } ;
Exe exedcpp477 = { "CC-VM-DEP Window.Scrollable.cpp" , VMDEP , { OBJ_PATH+"/Window.Scrollable.dep" , OBJ_PATH+"/Window.Scrollable.vm.dep" , "477" } } ;

Target cpp478 = { "Window.SimpleTextList.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.SimpleTextList.cpp" } ;
Target dcpp478 = { "Window.SimpleTextList.dep" , OBJ_PATH+"/Window.SimpleTextList.dep" } ;
Rule rdcpp478 = { {&cpp478,&obj} , {&dcpp478} , {&execpp478} } ;
Exe execpp478 = { "CC-DEP Window.SimpleTextList.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Window.SimpleTextList.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.SimpleTextList.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Window.SimpleTextList.dep"
} } ;

Target vdcpp478 = { "Window.SimpleTextList.vm.dep" , OBJ_PATH+"/Window.SimpleTextList.vm.dep" } ;
Rule rvdcpp478 = { {&dcpp478} , {&vdcpp478} , {&exedcpp478} } ;
Exe exedcpp478 = { "CC-VM-DEP Window.SimpleTextList.cpp" , VMDEP , { OBJ_PATH+"/Window.SimpleTextList.dep" , OBJ_PATH+"/Window.SimpleTextList.vm.dep" , "478" } } ;

Target cpp479 = { "Window.Slider.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.Slider.cpp" } ;
Target dcpp479 = { "Window.Slider.dep" , OBJ_PATH+"/Window.Slider.dep" } ;
Rule rdcpp479 = { {&cpp479,&obj} , {&dcpp479} , {&execpp479} } ;
Exe execpp479 = { "CC-DEP Window.Slider.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Window.Slider.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.Slider.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Window.Slider.dep"
} } ;

Target vdcpp479 = { "Window.Slider.vm.dep" , OBJ_PATH+"/Window.Slider.vm.dep" } ;
Rule rvdcpp479 = { {&dcpp479} , {&vdcpp479} , {&exedcpp479} } ;
Exe exedcpp479 = { "CC-VM-DEP Window.Slider.cpp" , VMDEP , { OBJ_PATH+"/Window.Slider.dep" , OBJ_PATH+"/Window.Slider.vm.dep" , "479" } } ;

Target cpp480 = { "Window.Spinor.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.Spinor.cpp" } ;
Target dcpp480 = { "Window.Spinor.dep" , OBJ_PATH+"/Window.Spinor.dep" } ;
Rule rdcpp480 = { {&cpp480,&obj} , {&dcpp480} , {&execpp480} } ;
Exe execpp480 = { "CC-DEP Window.Spinor.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Window.Spinor.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.Spinor.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Window.Spinor.dep"
} } ;

Target vdcpp480 = { "Window.Spinor.vm.dep" , OBJ_PATH+"/Window.Spinor.vm.dep" } ;
Rule rvdcpp480 = { {&dcpp480} , {&vdcpp480} , {&exedcpp480} } ;
Exe exedcpp480 = { "CC-VM-DEP Window.Spinor.cpp" , VMDEP , { OBJ_PATH+"/Window.Spinor.dep" , OBJ_PATH+"/Window.Spinor.vm.dep" , "480" } } ;

Target cpp481 = { "Window.Split.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.Split.cpp" } ;
Target dcpp481 = { "Window.Split.dep" , OBJ_PATH+"/Window.Split.dep" } ;
Rule rdcpp481 = { {&cpp481,&obj} , {&dcpp481} , {&execpp481} } ;
Exe execpp481 = { "CC-DEP Window.Split.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Window.Split.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.Split.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Window.Split.dep"
} } ;

Target vdcpp481 = { "Window.Split.vm.dep" , OBJ_PATH+"/Window.Split.vm.dep" } ;
Rule rvdcpp481 = { {&dcpp481} , {&vdcpp481} , {&exedcpp481} } ;
Exe exedcpp481 = { "CC-VM-DEP Window.Split.cpp" , VMDEP , { OBJ_PATH+"/Window.Split.dep" , OBJ_PATH+"/Window.Split.vm.dep" , "481" } } ;

Target cpp482 = { "Window.Text.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.Text.cpp" } ;
Target dcpp482 = { "Window.Text.dep" , OBJ_PATH+"/Window.Text.dep" } ;
Rule rdcpp482 = { {&cpp482,&obj} , {&dcpp482} , {&execpp482} } ;
Exe execpp482 = { "CC-DEP Window.Text.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Window.Text.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.Text.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Window.Text.dep"
} } ;

Target vdcpp482 = { "Window.Text.vm.dep" , OBJ_PATH+"/Window.Text.vm.dep" } ;
Rule rvdcpp482 = { {&dcpp482} , {&vdcpp482} , {&exedcpp482} } ;
Exe exedcpp482 = { "CC-VM-DEP Window.Text.cpp" , VMDEP , { OBJ_PATH+"/Window.Text.dep" , OBJ_PATH+"/Window.Text.vm.dep" , "482" } } ;

Target cpp483 = { "Window.TextLine.cpp" , "../../Desktop/Lib/CCore/src/./video/lib/Window.TextLine.cpp" } ;
Target dcpp483 = { "Window.TextLine.dep" , OBJ_PATH+"/Window.TextLine.dep" } ;
Rule rdcpp483 = { {&cpp483,&obj} , {&dcpp483} , {&execpp483} } ;
Exe execpp483 = { "CC-DEP Window.TextLine.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Window.TextLine.o"
 ,"../../Desktop/Lib/CCore/src/./video/lib/Window.TextLine.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Window.TextLine.dep"
} } ;

Target vdcpp483 = { "Window.TextLine.vm.dep" , OBJ_PATH+"/Window.TextLine.vm.dep" } ;
Rule rvdcpp483 = { {&dcpp483} , {&vdcpp483} , {&exedcpp483} } ;
Exe exedcpp483 = { "CC-VM-DEP Window.TextLine.cpp" , VMDEP , { OBJ_PATH+"/Window.TextLine.dep" , OBJ_PATH+"/Window.TextLine.vm.dep" , "483" } } ;

Target cpp484 = { "WindowLib.cpp" , "../../Desktop/Lib/CCore/src/./video/WindowLib.cpp" } ;
Target dcpp484 = { "WindowLib.dep" , OBJ_PATH+"/WindowLib.dep" } ;
Rule rdcpp484 = { {&cpp484,&obj} , {&dcpp484} , {&execpp484} } ;
Exe execpp484 = { "CC-DEP WindowLib.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/WindowLib.o"
 ,"../../Desktop/Lib/CCore/src/./video/WindowLib.cpp"
 ,"-MF"
 ,OBJ_PATH+"/WindowLib.dep"
} } ;

Target vdcpp484 = { "WindowLib.vm.dep" , OBJ_PATH+"/WindowLib.vm.dep" } ;
Rule rvdcpp484 = { {&dcpp484} , {&vdcpp484} , {&exedcpp484} } ;
Exe exedcpp484 = { "CC-VM-DEP WindowLib.cpp" , VMDEP , { OBJ_PATH+"/WindowLib.dep" , OBJ_PATH+"/WindowLib.vm.dep" , "484" } } ;

Target cpp485 = { "WindowReport.cpp" , "../../Desktop/App/CCore/src/./video/WindowReport.cpp" } ;
Target dcpp485 = { "WindowReport.dep" , OBJ_PATH+"/WindowReport.dep" } ;
Rule rdcpp485 = { {&cpp485,&obj} , {&dcpp485} , {&execpp485} } ;
Exe execpp485 = { "CC-DEP WindowReport.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/WindowReport.o"
 ,"../../Desktop/App/CCore/src/./video/WindowReport.cpp"
 ,"-MF"
 ,OBJ_PATH+"/WindowReport.dep"
} } ;

Target vdcpp485 = { "WindowReport.vm.dep" , OBJ_PATH+"/WindowReport.vm.dep" } ;
Rule rvdcpp485 = { {&dcpp485} , {&vdcpp485} , {&exedcpp485} } ;
Exe exedcpp485 = { "CC-VM-DEP WindowReport.cpp" , VMDEP , { OBJ_PATH+"/WindowReport.dep" , OBJ_PATH+"/WindowReport.vm.dep" , "485" } } ;

Target cpp486 = { "XPoint.cpp" , "../../Applied/CCore/src/./net/XPoint.cpp" } ;
Target dcpp486 = { "XPoint.dep" , OBJ_PATH+"/XPoint.dep" } ;
Rule rdcpp486 = { {&cpp486,&obj} , {&dcpp486} , {&execpp486} } ;
Exe execpp486 = { "CC-DEP XPoint.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/XPoint.o"
 ,"../../Applied/CCore/src/./net/XPoint.cpp"
 ,"-MF"
 ,OBJ_PATH+"/XPoint.dep"
} } ;

Target vdcpp486 = { "XPoint.vm.dep" , OBJ_PATH+"/XPoint.vm.dep" } ;
Rule rvdcpp486 = { {&dcpp486} , {&vdcpp486} , {&exedcpp486} } ;
Exe exedcpp486 = { "CC-VM-DEP XPoint.cpp" , VMDEP , { OBJ_PATH+"/XPoint.dep" , OBJ_PATH+"/XPoint.vm.dep" , "486" } } ;

Target make_dep = { 'make_dep' , DEP } ;

Rule rmkdep = { {&obj
,&vdcpp1
,&vdcpp2
,&vdcpp3
,&vdcpp4
,&vdcpp5
,&vdcpp6
,&vdcpp7
,&vdcpp8
,&vdcpp9
,&vdcpp10
,&vdcpp11
,&vdcpp12
,&vdcpp13
,&vdcpp14
,&vdcpp15
,&vdcpp16
,&vdcpp17
,&vdcpp18
,&vdcpp19
,&vdcpp20
,&vdcpp21
,&vdcpp22
,&vdcpp23
,&vdcpp24
,&vdcpp25
,&vdcpp26
,&vdcpp27
,&vdcpp28
,&vdcpp29
,&vdcpp30
,&vdcpp31
,&vdcpp32
,&vdcpp33
,&vdcpp34
,&vdcpp35
,&vdcpp36
,&vdcpp37
,&vdcpp38
,&vdcpp39
,&vdcpp40
,&vdcpp41
,&vdcpp42
,&vdcpp43
,&vdcpp44
,&vdcpp45
,&vdcpp46
,&vdcpp47
,&vdcpp48
,&vdcpp49
,&vdcpp50
,&vdcpp51
,&vdcpp52
,&vdcpp53
,&vdcpp54
,&vdcpp55
,&vdcpp56
,&vdcpp57
,&vdcpp58
,&vdcpp59
,&vdcpp60
,&vdcpp61
,&vdcpp62
,&vdcpp63
,&vdcpp64
,&vdcpp65
,&vdcpp66
,&vdcpp67
,&vdcpp68
,&vdcpp69
,&vdcpp70
,&vdcpp71
,&vdcpp72
,&vdcpp73
,&vdcpp74
,&vdcpp75
,&vdcpp76
,&vdcpp77
,&vdcpp78
,&vdcpp79
,&vdcpp80
,&vdcpp81
,&vdcpp82
,&vdcpp83
,&vdcpp84
,&vdcpp85
,&vdcpp86
,&vdcpp87
,&vdcpp88
,&vdcpp89
,&vdcpp90
,&vdcpp91
,&vdcpp92
,&vdcpp93
,&vdcpp94
,&vdcpp95
,&vdcpp96
,&vdcpp97
,&vdcpp98
,&vdcpp99
,&vdcpp100
,&vdcpp101
,&vdcpp102
,&vdcpp103
,&vdcpp104
,&vdcpp105
,&vdcpp106
,&vdcpp107
,&vdcpp108
,&vdcpp109
,&vdcpp110
,&vdcpp111
,&vdcpp112
,&vdcpp113
,&vdcpp114
,&vdcpp115
,&vdcpp116
,&vdcpp117
,&vdcpp118
,&vdcpp119
,&vdcpp120
,&vdcpp121
,&vdcpp122
,&vdcpp123
,&vdcpp124
,&vdcpp125
,&vdcpp126
,&vdcpp127
,&vdcpp128
,&vdcpp129
,&vdcpp130
,&vdcpp131
,&vdcpp132
,&vdcpp133
,&vdcpp134
,&vdcpp135
,&vdcpp136
,&vdcpp137
,&vdcpp138
,&vdcpp139
,&vdcpp140
,&vdcpp141
,&vdcpp142
,&vdcpp143
,&vdcpp144
,&vdcpp145
,&vdcpp146
,&vdcpp147
,&vdcpp148
,&vdcpp149
,&vdcpp150
,&vdcpp151
,&vdcpp152
,&vdcpp153
,&vdcpp154
,&vdcpp155
,&vdcpp156
,&vdcpp157
,&vdcpp158
,&vdcpp159
,&vdcpp160
,&vdcpp161
,&vdcpp162
,&vdcpp163
,&vdcpp164
,&vdcpp165
,&vdcpp166
,&vdcpp167
,&vdcpp168
,&vdcpp169
,&vdcpp170
,&vdcpp171
,&vdcpp172
,&vdcpp173
,&vdcpp174
,&vdcpp175
,&vdcpp176
,&vdcpp177
,&vdcpp178
,&vdcpp179
,&vdcpp180
,&vdcpp181
,&vdcpp182
,&vdcpp183
,&vdcpp184
,&vdcpp185
,&vdcpp186
,&vdcpp187
,&vdcpp188
,&vdcpp189
,&vdcpp190
,&vdcpp191
,&vdcpp192
,&vdcpp193
,&vdcpp194
,&vdcpp195
,&vdcpp196
,&vdcpp197
,&vdcpp198
,&vdcpp199
,&vdcpp200
,&vdcpp201
,&vdcpp202
,&vdcpp203
,&vdcpp204
,&vdcpp205
,&vdcpp206
,&vdcpp207
,&vdcpp208
,&vdcpp209
,&vdcpp210
,&vdcpp211
,&vdcpp212
,&vdcpp213
,&vdcpp214
,&vdcpp215
,&vdcpp216
,&vdcpp217
,&vdcpp218
,&vdcpp219
,&vdcpp220
,&vdcpp221
,&vdcpp222
,&vdcpp223
,&vdcpp224
,&vdcpp225
,&vdcpp226
,&vdcpp227
,&vdcpp228
,&vdcpp229
,&vdcpp230
,&vdcpp231
,&vdcpp232
,&vdcpp233
,&vdcpp234
,&vdcpp235
,&vdcpp236
,&vdcpp237
,&vdcpp238
,&vdcpp239
,&vdcpp240
,&vdcpp241
,&vdcpp242
,&vdcpp243
,&vdcpp244
,&vdcpp245
,&vdcpp246
,&vdcpp247
,&vdcpp248
,&vdcpp249
,&vdcpp250
,&vdcpp251
,&vdcpp252
,&vdcpp253
,&vdcpp254
,&vdcpp255
,&vdcpp256
,&vdcpp257
,&vdcpp258
,&vdcpp259
,&vdcpp260
,&vdcpp261
,&vdcpp262
,&vdcpp263
,&vdcpp264
,&vdcpp265
,&vdcpp266
,&vdcpp267
,&vdcpp268
,&vdcpp269
,&vdcpp270
,&vdcpp271
,&vdcpp272
,&vdcpp273
,&vdcpp274
,&vdcpp275
,&vdcpp276
,&vdcpp277
,&vdcpp278
,&vdcpp279
,&vdcpp280
,&vdcpp281
,&vdcpp282
,&vdcpp283
,&vdcpp284
,&vdcpp285
,&vdcpp286
,&vdcpp287
,&vdcpp288
,&vdcpp289
,&vdcpp290
,&vdcpp291
,&vdcpp292
,&vdcpp293
,&vdcpp294
,&vdcpp295
,&vdcpp296
,&vdcpp297
,&vdcpp298
,&vdcpp299
,&vdcpp300
,&vdcpp301
,&vdcpp302
,&vdcpp303
,&vdcpp304
,&vdcpp305
,&vdcpp306
,&vdcpp307
,&vdcpp308
,&vdcpp309
,&vdcpp310
,&vdcpp311
,&vdcpp312
,&vdcpp313
,&vdcpp314
,&vdcpp315
,&vdcpp316
,&vdcpp317
,&vdcpp318
,&vdcpp319
,&vdcpp320
,&vdcpp321
,&vdcpp322
,&vdcpp323
,&vdcpp324
,&vdcpp325
,&vdcpp326
,&vdcpp327
,&vdcpp328
,&vdcpp329
,&vdcpp330
,&vdcpp331
,&vdcpp332
,&vdcpp333
,&vdcpp334
,&vdcpp335
,&vdcpp336
,&vdcpp337
,&vdcpp338
,&vdcpp339
,&vdcpp340
,&vdcpp341
,&vdcpp342
,&vdcpp343
,&vdcpp344
,&vdcpp345
,&vdcpp346
,&vdcpp347
,&vdcpp348
,&vdcpp349
,&vdcpp350
,&vdcpp351
,&vdcpp352
,&vdcpp353
,&vdcpp354
,&vdcpp355
,&vdcpp356
,&vdcpp357
,&vdcpp358
,&vdcpp359
,&vdcpp360
,&vdcpp361
,&vdcpp362
,&vdcpp363
,&vdcpp364
,&vdcpp365
,&vdcpp366
,&vdcpp367
,&vdcpp368
,&vdcpp369
,&vdcpp370
,&vdcpp371
,&vdcpp372
,&vdcpp373
,&vdcpp374
,&vdcpp375
,&vdcpp376
,&vdcpp377
,&vdcpp378
,&vdcpp379
,&vdcpp380
,&vdcpp381
,&vdcpp382
,&vdcpp383
,&vdcpp384
,&vdcpp385
,&vdcpp386
,&vdcpp387
,&vdcpp388
,&vdcpp389
,&vdcpp390
,&vdcpp391
,&vdcpp392
,&vdcpp393
,&vdcpp394
,&vdcpp395
,&vdcpp396
,&vdcpp397
,&vdcpp398
,&vdcpp399
,&vdcpp400
,&vdcpp401
,&vdcpp402
,&vdcpp403
,&vdcpp404
,&vdcpp405
,&vdcpp406
,&vdcpp407
,&vdcpp408
,&vdcpp409
,&vdcpp410
,&vdcpp411
,&vdcpp412
,&vdcpp413
,&vdcpp414
,&vdcpp415
,&vdcpp416
,&vdcpp417
,&vdcpp418
,&vdcpp419
,&vdcpp420
,&vdcpp421
,&vdcpp422
,&vdcpp423
,&vdcpp424
,&vdcpp425
,&vdcpp426
,&vdcpp427
,&vdcpp428
,&vdcpp429
,&vdcpp430
,&vdcpp431
,&vdcpp432
,&vdcpp433
,&vdcpp434
,&vdcpp435
,&vdcpp436
,&vdcpp437
,&vdcpp438
,&vdcpp439
,&vdcpp440
,&vdcpp441
,&vdcpp442
,&vdcpp443
,&vdcpp444
,&vdcpp445
,&vdcpp446
,&vdcpp447
,&vdcpp448
,&vdcpp449
,&vdcpp450
,&vdcpp451
,&vdcpp452
,&vdcpp453
,&vdcpp454
,&vdcpp455
,&vdcpp456
,&vdcpp457
,&vdcpp458
,&vdcpp459
,&vdcpp460
,&vdcpp461
,&vdcpp462
,&vdcpp463
,&vdcpp464
,&vdcpp465
,&vdcpp466
,&vdcpp467
,&vdcpp468
,&vdcpp469
,&vdcpp470
,&vdcpp471
,&vdcpp472
,&vdcpp473
,&vdcpp474
,&vdcpp475
,&vdcpp476
,&vdcpp477
,&vdcpp478
,&vdcpp479
,&vdcpp480
,&vdcpp481
,&vdcpp482
,&vdcpp483
,&vdcpp484
,&vdcpp485
,&vdcpp486} , {&make_dep} , {&intmkdep} } ; 

IntCmd intmkdep = { 'CAT' , &cat1 } ;

Cat cat1 = { { 
 vdcpp1.file
,vdcpp2.file
,vdcpp3.file
,vdcpp4.file
,vdcpp5.file
,vdcpp6.file
,vdcpp7.file
,vdcpp8.file
,vdcpp9.file
,vdcpp10.file
,vdcpp11.file
,vdcpp12.file
,vdcpp13.file
,vdcpp14.file
,vdcpp15.file
,vdcpp16.file
,vdcpp17.file
,vdcpp18.file
,vdcpp19.file
,vdcpp20.file
,vdcpp21.file
,vdcpp22.file
,vdcpp23.file
,vdcpp24.file
,vdcpp25.file
,vdcpp26.file
,vdcpp27.file
,vdcpp28.file
,vdcpp29.file
,vdcpp30.file
,vdcpp31.file
,vdcpp32.file
,vdcpp33.file
,vdcpp34.file
,vdcpp35.file
,vdcpp36.file
,vdcpp37.file
,vdcpp38.file
,vdcpp39.file
,vdcpp40.file
,vdcpp41.file
,vdcpp42.file
,vdcpp43.file
,vdcpp44.file
,vdcpp45.file
,vdcpp46.file
,vdcpp47.file
,vdcpp48.file
,vdcpp49.file
,vdcpp50.file
,vdcpp51.file
,vdcpp52.file
,vdcpp53.file
,vdcpp54.file
,vdcpp55.file
,vdcpp56.file
,vdcpp57.file
,vdcpp58.file
,vdcpp59.file
,vdcpp60.file
,vdcpp61.file
,vdcpp62.file
,vdcpp63.file
,vdcpp64.file
,vdcpp65.file
,vdcpp66.file
,vdcpp67.file
,vdcpp68.file
,vdcpp69.file
,vdcpp70.file
,vdcpp71.file
,vdcpp72.file
,vdcpp73.file
,vdcpp74.file
,vdcpp75.file
,vdcpp76.file
,vdcpp77.file
,vdcpp78.file
,vdcpp79.file
,vdcpp80.file
,vdcpp81.file
,vdcpp82.file
,vdcpp83.file
,vdcpp84.file
,vdcpp85.file
,vdcpp86.file
,vdcpp87.file
,vdcpp88.file
,vdcpp89.file
,vdcpp90.file
,vdcpp91.file
,vdcpp92.file
,vdcpp93.file
,vdcpp94.file
,vdcpp95.file
,vdcpp96.file
,vdcpp97.file
,vdcpp98.file
,vdcpp99.file
,vdcpp100.file
,vdcpp101.file
,vdcpp102.file
,vdcpp103.file
,vdcpp104.file
,vdcpp105.file
,vdcpp106.file
,vdcpp107.file
,vdcpp108.file
,vdcpp109.file
,vdcpp110.file
,vdcpp111.file
,vdcpp112.file
,vdcpp113.file
,vdcpp114.file
,vdcpp115.file
,vdcpp116.file
,vdcpp117.file
,vdcpp118.file
,vdcpp119.file
,vdcpp120.file
,vdcpp121.file
,vdcpp122.file
,vdcpp123.file
,vdcpp124.file
,vdcpp125.file
,vdcpp126.file
,vdcpp127.file
,vdcpp128.file
,vdcpp129.file
,vdcpp130.file
,vdcpp131.file
,vdcpp132.file
,vdcpp133.file
,vdcpp134.file
,vdcpp135.file
,vdcpp136.file
,vdcpp137.file
,vdcpp138.file
,vdcpp139.file
,vdcpp140.file
,vdcpp141.file
,vdcpp142.file
,vdcpp143.file
,vdcpp144.file
,vdcpp145.file
,vdcpp146.file
,vdcpp147.file
,vdcpp148.file
,vdcpp149.file
,vdcpp150.file
,vdcpp151.file
,vdcpp152.file
,vdcpp153.file
,vdcpp154.file
,vdcpp155.file
,vdcpp156.file
,vdcpp157.file
,vdcpp158.file
,vdcpp159.file
,vdcpp160.file
,vdcpp161.file
,vdcpp162.file
,vdcpp163.file
,vdcpp164.file
,vdcpp165.file
,vdcpp166.file
,vdcpp167.file
,vdcpp168.file
,vdcpp169.file
,vdcpp170.file
,vdcpp171.file
,vdcpp172.file
,vdcpp173.file
,vdcpp174.file
,vdcpp175.file
,vdcpp176.file
,vdcpp177.file
,vdcpp178.file
,vdcpp179.file
,vdcpp180.file
,vdcpp181.file
,vdcpp182.file
,vdcpp183.file
,vdcpp184.file
,vdcpp185.file
,vdcpp186.file
,vdcpp187.file
,vdcpp188.file
,vdcpp189.file
,vdcpp190.file
,vdcpp191.file
,vdcpp192.file
,vdcpp193.file
,vdcpp194.file
,vdcpp195.file
,vdcpp196.file
,vdcpp197.file
,vdcpp198.file
,vdcpp199.file
,vdcpp200.file
,vdcpp201.file
,vdcpp202.file
,vdcpp203.file
,vdcpp204.file
,vdcpp205.file
,vdcpp206.file
,vdcpp207.file
,vdcpp208.file
,vdcpp209.file
,vdcpp210.file
,vdcpp211.file
,vdcpp212.file
,vdcpp213.file
,vdcpp214.file
,vdcpp215.file
,vdcpp216.file
,vdcpp217.file
,vdcpp218.file
,vdcpp219.file
,vdcpp220.file
,vdcpp221.file
,vdcpp222.file
,vdcpp223.file
,vdcpp224.file
,vdcpp225.file
,vdcpp226.file
,vdcpp227.file
,vdcpp228.file
,vdcpp229.file
,vdcpp230.file
,vdcpp231.file
,vdcpp232.file
,vdcpp233.file
,vdcpp234.file
,vdcpp235.file
,vdcpp236.file
,vdcpp237.file
,vdcpp238.file
,vdcpp239.file
,vdcpp240.file
,vdcpp241.file
,vdcpp242.file
,vdcpp243.file
,vdcpp244.file
,vdcpp245.file
,vdcpp246.file
,vdcpp247.file
,vdcpp248.file
,vdcpp249.file
,vdcpp250.file
,vdcpp251.file
,vdcpp252.file
,vdcpp253.file
,vdcpp254.file
,vdcpp255.file
,vdcpp256.file
,vdcpp257.file
,vdcpp258.file
,vdcpp259.file
,vdcpp260.file
,vdcpp261.file
,vdcpp262.file
,vdcpp263.file
,vdcpp264.file
,vdcpp265.file
,vdcpp266.file
,vdcpp267.file
,vdcpp268.file
,vdcpp269.file
,vdcpp270.file
,vdcpp271.file
,vdcpp272.file
,vdcpp273.file
,vdcpp274.file
,vdcpp275.file
,vdcpp276.file
,vdcpp277.file
,vdcpp278.file
,vdcpp279.file
,vdcpp280.file
,vdcpp281.file
,vdcpp282.file
,vdcpp283.file
,vdcpp284.file
,vdcpp285.file
,vdcpp286.file
,vdcpp287.file
,vdcpp288.file
,vdcpp289.file
,vdcpp290.file
,vdcpp291.file
,vdcpp292.file
,vdcpp293.file
,vdcpp294.file
,vdcpp295.file
,vdcpp296.file
,vdcpp297.file
,vdcpp298.file
,vdcpp299.file
,vdcpp300.file
,vdcpp301.file
,vdcpp302.file
,vdcpp303.file
,vdcpp304.file
,vdcpp305.file
,vdcpp306.file
,vdcpp307.file
,vdcpp308.file
,vdcpp309.file
,vdcpp310.file
,vdcpp311.file
,vdcpp312.file
,vdcpp313.file
,vdcpp314.file
,vdcpp315.file
,vdcpp316.file
,vdcpp317.file
,vdcpp318.file
,vdcpp319.file
,vdcpp320.file
,vdcpp321.file
,vdcpp322.file
,vdcpp323.file
,vdcpp324.file
,vdcpp325.file
,vdcpp326.file
,vdcpp327.file
,vdcpp328.file
,vdcpp329.file
,vdcpp330.file
,vdcpp331.file
,vdcpp332.file
,vdcpp333.file
,vdcpp334.file
,vdcpp335.file
,vdcpp336.file
,vdcpp337.file
,vdcpp338.file
,vdcpp339.file
,vdcpp340.file
,vdcpp341.file
,vdcpp342.file
,vdcpp343.file
,vdcpp344.file
,vdcpp345.file
,vdcpp346.file
,vdcpp347.file
,vdcpp348.file
,vdcpp349.file
,vdcpp350.file
,vdcpp351.file
,vdcpp352.file
,vdcpp353.file
,vdcpp354.file
,vdcpp355.file
,vdcpp356.file
,vdcpp357.file
,vdcpp358.file
,vdcpp359.file
,vdcpp360.file
,vdcpp361.file
,vdcpp362.file
,vdcpp363.file
,vdcpp364.file
,vdcpp365.file
,vdcpp366.file
,vdcpp367.file
,vdcpp368.file
,vdcpp369.file
,vdcpp370.file
,vdcpp371.file
,vdcpp372.file
,vdcpp373.file
,vdcpp374.file
,vdcpp375.file
,vdcpp376.file
,vdcpp377.file
,vdcpp378.file
,vdcpp379.file
,vdcpp380.file
,vdcpp381.file
,vdcpp382.file
,vdcpp383.file
,vdcpp384.file
,vdcpp385.file
,vdcpp386.file
,vdcpp387.file
,vdcpp388.file
,vdcpp389.file
,vdcpp390.file
,vdcpp391.file
,vdcpp392.file
,vdcpp393.file
,vdcpp394.file
,vdcpp395.file
,vdcpp396.file
,vdcpp397.file
,vdcpp398.file
,vdcpp399.file
,vdcpp400.file
,vdcpp401.file
,vdcpp402.file
,vdcpp403.file
,vdcpp404.file
,vdcpp405.file
,vdcpp406.file
,vdcpp407.file
,vdcpp408.file
,vdcpp409.file
,vdcpp410.file
,vdcpp411.file
,vdcpp412.file
,vdcpp413.file
,vdcpp414.file
,vdcpp415.file
,vdcpp416.file
,vdcpp417.file
,vdcpp418.file
,vdcpp419.file
,vdcpp420.file
,vdcpp421.file
,vdcpp422.file
,vdcpp423.file
,vdcpp424.file
,vdcpp425.file
,vdcpp426.file
,vdcpp427.file
,vdcpp428.file
,vdcpp429.file
,vdcpp430.file
,vdcpp431.file
,vdcpp432.file
,vdcpp433.file
,vdcpp434.file
,vdcpp435.file
,vdcpp436.file
,vdcpp437.file
,vdcpp438.file
,vdcpp439.file
,vdcpp440.file
,vdcpp441.file
,vdcpp442.file
,vdcpp443.file
,vdcpp444.file
,vdcpp445.file
,vdcpp446.file
,vdcpp447.file
,vdcpp448.file
,vdcpp449.file
,vdcpp450.file
,vdcpp451.file
,vdcpp452.file
,vdcpp453.file
,vdcpp454.file
,vdcpp455.file
,vdcpp456.file
,vdcpp457.file
,vdcpp458.file
,vdcpp459.file
,vdcpp460.file
,vdcpp461.file
,vdcpp462.file
,vdcpp463.file
,vdcpp464.file
,vdcpp465.file
,vdcpp466.file
,vdcpp467.file
,vdcpp468.file
,vdcpp469.file
,vdcpp470.file
,vdcpp471.file
,vdcpp472.file
,vdcpp473.file
,vdcpp474.file
,vdcpp475.file
,vdcpp476.file
,vdcpp477.file
,vdcpp478.file
,vdcpp479.file
,vdcpp480.file
,vdcpp481.file
,vdcpp482.file
,vdcpp483.file
,vdcpp484.file
,vdcpp485.file
,vdcpp486.file } , DEP } ;

