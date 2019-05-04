text CC = "D:/cygwin/opt/gcc-9.1.0/bin/g++-9.1.0" ;

text VMDEP = "D:/active/home/bin/CCore-VMakeDep.exe" ;

text OBJ_PATH = ".obj" ;

text TARGET = "D:/active/home/bin/CCore-VMakeList.exe" ;

text DEP = OBJ_PATH+'/deps.vm.ddl' ;

Target obj = { 'obj' , OBJ_PATH+'/empty' } ;

Rule robj = { {} , {&obj} , {&intobj1,&intobj2} } ;

IntCmd intobj1 = { 'MKDIR' , &mkdir1 } ;

Mkdir mkdir1 = { { OBJ_PATH } } ;

IntCmd intobj2 = { 'ECHO' , &echo1 } ;

Echo echo1 = { { 'empty' } , OBJ_PATH+'/empty' } ;

Target clean = { 'clean' } ;

Rule rclean = { {} , {&clean} , {&intclean} } ;

IntCmd intclean = { 'CLEAN' , &rm1 } ;

Rm rm1 = { { TARGET , OBJ_PATH+'/*' } } ;

Target clean_dep = { 'clean dep' } ;

Rule rclean_dep = { {} , {&clean_dep} , {&intclean_dep} } ;

IntCmd intclean_dep = { 'CLEAN DEP' , &rm2 } ;

Rm rm2 = { { DEP , OBJ_PATH+'/*.dep' } } ;

Target clean_vdep = { 'clean vdep' } ;

Rule rclean_vdep = { {} , {&clean_vdep} , {&intclean_vdep} } ;

IntCmd intclean_vdep = { 'CLEAN VDEP' , &rm3 } ;

Rm rm3 = { { DEP , OBJ_PATH+'/*.vm.dep' } } ;

Target cpp1 = { "Engine.cpp" , "src/Engine.cpp" } ;
Target dcpp1 = { "Engine.dep" , OBJ_PATH+"/Engine.dep" } ;
Rule rdcpp1 = { {&cpp1,&obj} , {&dcpp1} , {&execpp1} } ;
Exe execpp1 = { "CC-DEP Engine.cpp" , CC , {
  "-I../../Target/WIN32utf8"
 ,"-I../../HCore"
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
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Engine.o"
 ,"src/Engine.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Engine.dep"
} } ;

Target vdcpp1 = { "Engine.vm.dep" , OBJ_PATH+"/Engine.vm.dep" } ;
Rule rvdcpp1 = { {&dcpp1} , {&vdcpp1} , {&exedcpp1} } ;
Exe exedcpp1 = { "CC-VM-DEP Engine.cpp" , VMDEP , { OBJ_PATH+"/Engine.dep" , OBJ_PATH+"/Engine.vm.dep" , '1' } } ;

Target cpp2 = { "VMakeList.cpp" , "src/VMakeList.cpp" } ;
Target dcpp2 = { "VMakeList.dep" , OBJ_PATH+"/VMakeList.dep" } ;
Rule rdcpp2 = { {&cpp2,&obj} , {&dcpp2} , {&execpp2} } ;
Exe execpp2 = { "CC-DEP VMakeList.cpp" , CC , {
  "-I../../Target/WIN32utf8"
 ,"-I../../HCore"
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
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/VMakeList.o"
 ,"src/VMakeList.cpp"
 ,"-MF"
 ,OBJ_PATH+"/VMakeList.dep"
} } ;

Target vdcpp2 = { "VMakeList.vm.dep" , OBJ_PATH+"/VMakeList.vm.dep" } ;
Rule rvdcpp2 = { {&dcpp2} , {&vdcpp2} , {&exedcpp2} } ;
Exe exedcpp2 = { "CC-VM-DEP VMakeList.cpp" , VMDEP , { OBJ_PATH+"/VMakeList.dep" , OBJ_PATH+"/VMakeList.vm.dep" , '2' } } ;

Target cpp3 = { "main.cpp" , "src/main.cpp" } ;
Target dcpp3 = { "main.dep" , OBJ_PATH+"/main.dep" } ;
Rule rdcpp3 = { {&cpp3,&obj} , {&dcpp3} , {&execpp3} } ;
Exe execpp3 = { "CC-DEP main.cpp" , CC , {
  "-I../../Target/WIN32utf8"
 ,"-I../../HCore"
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
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/main.o"
 ,"src/main.cpp"
 ,"-MF"
 ,OBJ_PATH+"/main.dep"
} } ;

Target vdcpp3 = { "main.vm.dep" , OBJ_PATH+"/main.vm.dep" } ;
Rule rvdcpp3 = { {&dcpp3} , {&vdcpp3} , {&exedcpp3} } ;
Exe exedcpp3 = { "CC-VM-DEP main.cpp" , VMDEP , { OBJ_PATH+"/main.dep" , OBJ_PATH+"/main.vm.dep" , '3' } } ;

Target make_dep = { 'make_dep' , DEP } ;

Rule rmkdep = { {&obj
,&vdcpp1
,&vdcpp2
,&vdcpp3} , {&make_dep} , {&intmkdep} } ; 

IntCmd intmkdep = { 'CAT' , &cat1 } ;

Cat cat1 = { { 
 vdcpp1.file
,vdcpp2.file
,vdcpp3.file } , DEP } ;

