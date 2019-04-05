text OBJ_PATH = ".obj" ;

text CC = "D:/cygwin/opt/gcc-8.3.0/bin/g++-8.3.0" ;

text AS = "as" ;

text LD = "D:/cygwin/opt/gcc-8.3.0/bin/g++-8.3.0" ;

text AR = "ar" ;

text TARGET = "D:/active/home/bin/CCore-VMakeList.exe" ;

Target cpp1 = { "Engine.cpp" , "src/Engine.cpp" } ;
Target ocpp1 = { "Engine.o" , OBJ_PATH+"/Engine.o" } ;
Rule rcpp1 = { {&cpp1} , {&ocpp1} , {&intdep1,&execpp1} } ;
Exe execpp1 = { "CC Engine.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"-I."
 ,"src/Engine.cpp"
 ,"-o"
 ,OBJ_PATH+"/Engine.o"
} } ;

IntCmd intdep1 = { 'RM DEP' , &rmdep1 } ;

Rm rmdep1 = { { OBJ_PATH+"/Engine.dep" } } ;

Target cpp2 = { "Utils.cpp" , "src/Utils.cpp" } ;
Target ocpp2 = { "Utils.o" , OBJ_PATH+"/Utils.o" } ;
Rule rcpp2 = { {&cpp2} , {&ocpp2} , {&intdep2,&execpp2} } ;
Exe execpp2 = { "CC Utils.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"-I."
 ,"src/Utils.cpp"
 ,"-o"
 ,OBJ_PATH+"/Utils.o"
} } ;

IntCmd intdep2 = { 'RM DEP' , &rmdep2 } ;

Rm rmdep2 = { { OBJ_PATH+"/Utils.dep" } } ;

Target cpp3 = { "VMakeList.cpp" , "src/VMakeList.cpp" } ;
Target ocpp3 = { "VMakeList.o" , OBJ_PATH+"/VMakeList.o" } ;
Rule rcpp3 = { {&cpp3} , {&ocpp3} , {&intdep3,&execpp3} } ;
Exe execpp3 = { "CC VMakeList.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"-I."
 ,"src/VMakeList.cpp"
 ,"-o"
 ,OBJ_PATH+"/VMakeList.o"
} } ;

IntCmd intdep3 = { 'RM DEP' , &rmdep3 } ;

Rm rmdep3 = { { OBJ_PATH+"/VMakeList.dep" } } ;

Target cpp4 = { "main.cpp" , "src/main.cpp" } ;
Target ocpp4 = { "main.o" , OBJ_PATH+"/main.o" } ;
Rule rcpp4 = { {&cpp4} , {&ocpp4} , {&intdep4,&execpp4} } ;
Exe execpp4 = { "CC main.cpp" , CC , {
  "-c"
 ,"-std=c++17"
 ,"-fconcepts"
 ,"-fwrapv"
 ,"-O3"
 ,"-march=ivybridge"
 ,"-mmmx"
 ,"-msse"
 ,"-msse2"
 ,"-Wall"
 ,"-Wextra"
 ,"-Wno-non-virtual-dtor"
 ,"-Wno-switch"
 ,"-Wno-type-limits"
 ,"-Wno-enum-compare"
 ,"-Wno-missing-field-initializers"
 ,"-Wno-delete-non-virtual-dtor"
 ,"-Wno-misleading-indentation"
 ,"-I../../Target/WIN32utf8"
 ,"-I../../HCore"
 ,"-I../../Simple"
 ,"-I../../Fundamental"
 ,"-I../../Applied"
 ,"-I../../Desktop/Core"
 ,"-I../../Desktop/Draw"
 ,"-I../../Desktop/Font"
 ,"-I../../Desktop/Lib"
 ,"-I../../Desktop/Tools"
 ,"-I../../Desktop/App"
 ,"-I."
 ,"src/main.cpp"
 ,"-o"
 ,OBJ_PATH+"/main.o"
} } ;

IntCmd intdep4 = { 'RM DEP' , &rmdep4 } ;

Rm rmdep4 = { { OBJ_PATH+"/main.dep" } } ;

