text OBJ_PATH = ".obj" ;

text TARGET = "D:/active/home"+"/bin/CCore-VMakeList.exe" ;

Target obj = { 'obj' , OBJ_PATH+'/empty' } ;

Rule robj = { {} , {&obj} , {&cmdobj} } ;

Cmd cmdobj = { 'OBJ' , "mkdir -p \""+OBJ_PATH+"\" ; echo \\\"empty file\\\" > \""+OBJ_PATH+'"/empty' } ;

Target clean = { 'clean' } ;

Rule rclean = { {} , {&clean} , {&cmdclean} } ;

Cmd cmdclean = { 'CLEAN' , "rm -f \""+TARGET+"\" \""+OBJ_PATH+"\"/*" } ;

