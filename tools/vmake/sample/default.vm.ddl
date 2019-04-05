/* default.vm.ddl */

/* int1 */

Target int1 = { 'int1' } ;

Rule R1 = { {} , {&int1} , {&C1} } ;

IntCmd C1 = { 'echo1' , &I1 } ;

Echo I1 = { { 'int echo1','int echo2' } , '' } ;

/* int2 */

Target int2 = { 'int2' } ;

Rule R2 = { {} , {&int2} , {&C2} } ;

IntCmd C2 = { 'echo to file' , &I2 } ;

Echo I2 = { { 'int echo' } , 'echo.txt' } ;

/* int3 */

Target int3 = { 'int3' } ;

Rule R3 = { {} , {&int3} , {&C3} } ;

IntCmd C3 = { 'cat' , &I3 , "../.obj" } ;

Cat I3 = { {'main.dep','VMakeData.dep'}  , 'test.dep' } ;

/* int4 */

Target int4 = { 'int4' } ;

Rule R4 = { {} , {&int4} , {&C4} } ;

IntCmd C4 = { 'rm' , &I4 , "../.obj" } ;

Rm I4 = { {'test.dep'} } ;

/* int5 */

Target int5 = { 'int5' } ;

Rule R5 = { {} , {&int5} , {&C5} } ;

IntCmd C5 = { 'mkdir' , &I5 } ;

Mkdir I5 = { { 'dir1/dir2/../dir3' } } ;

/* int6 */

Target int6 = { 'int6' } ;

Rule R6 = { {} , {&int6} , {&C5,&C6,&C7,&C8} } ;

IntCmd C6 = { 'echo 1' , &I6 } ;

Echo I6 = { { 'echo 1' } , 'dir1/echo1.txt' } ;

IntCmd C7 = { 'echo 2' , &I7 } ;

Echo I7 = { { 'echo 2' } , 'dir1/echo2.txt' } ;

IntCmd C8 = { 'cat' , &I8 } ;

Cat I8 = { {'dir1/echo1.txt','dir1/echo2.txt'}, 'dir1/echo.txt' } ;

/* int7 */

Target int7 = { 'int7' } ;

Rule R7 = { {} , {&int7} , {&C9} } ;

IntCmd C9 = { 'rm' , &I9 , "dir1" } ;

Rm I9 = { {'*.txt'} } ;

/* targets */

Target main = { "main" } ;

Target exe = { "exe" , "test.exe" } ;

Target map = { "map" , "map 123.txt" } ;

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

Rule ld1 = { {&obj1,&obj2} , {&exe,&map} , {&cmd3} } ;

Cmd cmd3 = { "LD test.exe" , "g++ test1.o test2.o -o test.exe \"-Wl,-Map=map 123.txt\"" } ;

Rule test1 = { {} , {&test} , {&cmd_test} } ;

Exe cmd_test = { "test" , "../test/test.exe" , {"1","2","3"} , ".." , {{"ABRA","CODABRA"}} } ;

Rule test2 = { {} , {&shell} , {&cmd_test_shell} } ;

Cmd cmd_test_shell = { "shell" , "echo $ABRA\nps\necho $HOME\necho $0" , "" , {{"ABRA","CODABRA"}} } ;

Rule test3 = { {} , {&sh} , {&cmd_test_sh} } ;

Exe cmd_test_sh = { "sh" , "sh" , {} , ".." , {{"ABRA","CODABRA"}} } ;

/* deps */

Dep dep1 = { {&h1} , {&obj1,&obj2} } ;

Dep dep2 = { {&exe,&map} , {&main} } ;

//Dep dep3 = { {&exe} , {&map} } ;


