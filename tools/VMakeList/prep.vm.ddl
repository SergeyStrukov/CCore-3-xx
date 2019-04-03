text CC = "D:/cygwin"+"/opt/gcc-8.3.0/bin/g++-8.3.0" ;

text VMDEP = "D:/active/home"+"/bin/CCore-VMakeDep.exe" ;

text CAT = "cat" ;

text OBJ_PATH = ".obj" ;

text TARGET = "D:/active/home"+"/bin/CCore-VMakeList.exe" ;

text DEP = OBJ_PATH+'/deps.vm.ddl' ;

Target obj = { 'obj' , OBJ_PATH+'/empty' } ;

Rule robj = { {} , {&obj} , {&cmdobj} } ;

Cmd cmdobj = { 'MKDIR '+OBJ_PATH , "mkdir -p \""+OBJ_PATH+"\" ; echo \\\"empty file\\\" > \""+OBJ_PATH+'"/empty' } ;

Target clean = { 'clean' } ;

Rule rclean = { {} , {&clean} , {&cmdclean} } ;

Cmd cmdclean = { 'CLEAN' , "rm -f \""+TARGET+"\" \""+OBJ_PATH+"\"/*" } ;

Target cpp1 = { "Engine.cpp" , "src/Engine.cpp" } ;
Target dcpp1 = { "Engine.dep" , OBJ_PATH+"/Engine.dep" } ;
Rule rdcpp1 = { {&cpp1,&obj} , {&dcpp1} , {&execpp1} } ;
Exe execpp1 = { "CC-DEP Engine.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
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
Exe exedcpp1 = { "CC-VM-DEP Engine.cpp" , VMDEP , { OBJ_PATH+"/Engine.dep" , OBJ_PATH+"/Engine.vm.dep" } } ;

Target cpp2 = { "Utils.cpp" , "src/Utils.cpp" } ;
Target dcpp2 = { "Utils.dep" , OBJ_PATH+"/Utils.dep" } ;
Rule rdcpp2 = { {&cpp2,&obj} , {&dcpp2} , {&execpp2} } ;
Exe execpp2 = { "CC-DEP Utils.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-I."
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/Utils.o"
 ,"src/Utils.cpp"
 ,"-MF"
 ,OBJ_PATH+"/Utils.dep"
} } ;

Target vdcpp2 = { "Utils.vm.dep" , OBJ_PATH+"/Utils.vm.dep" } ;
Rule rvdcpp2 = { {&dcpp2} , {&vdcpp2} , {&exedcpp2} } ;
Exe exedcpp2 = { "CC-VM-DEP Utils.cpp" , VMDEP , { OBJ_PATH+"/Utils.dep" , OBJ_PATH+"/Utils.vm.dep" } } ;

Target cpp3 = { "VMakeList.cpp" , "src/VMakeList.cpp" } ;
Target dcpp3 = { "VMakeList.dep" , OBJ_PATH+"/VMakeList.dep" } ;
Rule rdcpp3 = { {&cpp3,&obj} , {&dcpp3} , {&execpp3} } ;
Exe execpp3 = { "CC-DEP VMakeList.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-I."
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/VMakeList.o"
 ,"src/VMakeList.cpp"
 ,"-MF"
 ,OBJ_PATH+"/VMakeList.dep"
} } ;

Target vdcpp3 = { "VMakeList.vm.dep" , OBJ_PATH+"/VMakeList.vm.dep" } ;
Rule rvdcpp3 = { {&dcpp3} , {&vdcpp3} , {&exedcpp3} } ;
Exe exedcpp3 = { "CC-VM-DEP VMakeList.cpp" , VMDEP , { OBJ_PATH+"/VMakeList.dep" , OBJ_PATH+"/VMakeList.vm.dep" } } ;

Target cpp4 = { "main.cpp" , "src/main.cpp" } ;
Target dcpp4 = { "main.dep" , OBJ_PATH+"/main.dep" } ;
Rule rdcpp4 = { {&cpp4,&obj} , {&dcpp4} , {&execpp4} } ;
Exe execpp4 = { "CC-DEP main.cpp" , CC , {
  "-I"+"../.."+"/Target/"+"WIN32utf8"
 ,"-I"+"../.."+"/HCore"
 ,"-I"+"../.."+"/Simple"
 ,"-I"+"../.."+"/Fundamental"
 ,"-I"+"../.."+"/Applied"
 ,"-I"+"../.."+"/Desktop/Core"
 ,"-I"+"../.."+"/Desktop/Draw"
 ,"-I"+"../.."+"/Desktop/Font"
 ,"-I"+"../.."+"/Desktop/Lib"
 ,"-I"+"../.."+"/Desktop/Tools"
 ,"-I"+"../.."+"/Desktop/App"
 ,"-I."
 ,"-MM"
 ,"-MT"
 ,OBJ_PATH+"/main.o"
 ,"src/main.cpp"
 ,"-MF"
 ,OBJ_PATH+"/main.dep"
} } ;

Target vdcpp4 = { "main.vm.dep" , OBJ_PATH+"/main.vm.dep" } ;
Rule rvdcpp4 = { {&dcpp4} , {&vdcpp4} , {&exedcpp4} } ;
Exe exedcpp4 = { "CC-VM-DEP main.cpp" , VMDEP , { OBJ_PATH+"/main.dep" , OBJ_PATH+"/main.vm.dep" } } ;

Target make_dep = { 'make_dep' , DEP } ;

Rule rmkdep = { {&obj
,&vdcpp1
,&vdcpp2
,&vdcpp3
,&vdcpp4} , {&make_dep} , {&cmdmkdep} } ;

Cmd cmdmkdep = { 'CAT' , CAT
+" \""+OBJ_PATH+"/Engine.vm.dep\""
+" \""+OBJ_PATH+"/Utils.vm.dep\""
+" \""+OBJ_PATH+"/VMakeList.vm.dep\""
+" \""+OBJ_PATH+"/main.vm.dep\""+
" > \""+DEP+"\"" } ;

