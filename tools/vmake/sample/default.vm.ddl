/* default.vm.ddl */

/* targets */

Target main = { "main" } ;

Target exe = { "exe" , "test.exe" } ;

Target obj1 = { "obj1" , "test1.o" } ;

Target obj2 = { "obj2" , "test2.o" } ;

Target cpp1 = { "cpp1" , "test1.cpp" } ;

Target cpp2 = { "cpp2" , "test2.cpp" } ;

Target h1 = { "h1" , "test.h" } ;

Target test = { "test" } ;

Target shell = { "test shell" } ;

Target sh = { "test sh" } ;

/* rules */

Rule cc1 = { {&cpp1} , {&obj1} , {&cmd1} } ;

Cmd cmd1 = { "CC test1.cpp" , "g++ -c test1.cpp -o test1.o" } ;

Rule cc2 = { {&cpp2} , {&obj2} , {&cmd2} } ;

Cmd cmd2 = { "CC test2.cpp" , "g++ -c test2.cpp -o test2.o" } ;

Rule ld1 = { {&obj1,&obj2} , {&exe} , {&cmd3} } ;

Cmd cmd3 = { "LD test.exe" , "g++ test1.o test2.o -o test.exe" } ;

Rule test1 = { {} , {&test} , {&cmd_test} } ;

Exe cmd_test = { "test" , "test/test.exe" , "1 2 3" , ".." , {{"ABRA","CODABRA"}} } ;

Rule test2 = { {} , {&shell} , {&cmd_test_shell} } ;

Cmd cmd_test_shell = { "shell" , "echo $ABRA\nps\necho $HOME" , "" , {{"ABRA","CODABRA"}} } ;

Rule test3 = { {} , {&sh} , {&cmd_test_sh} } ;

Exe cmd_test_sh = { "sh" , "/bin/sh" , "" , ".." , {{"ABRA","CODABRA"}} } ;

/* deps */

Dep dep1 = { {&h1} , {&obj1,&obj2} } ;

Dep dep2 = { {&exe} , {&main} } ;

