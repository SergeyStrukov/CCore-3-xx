" \n"
" \n"
" \n"
" \n"
" \n"
" \n"
" \n"
" \n"
" \n"
" \n"
" \n"
" \n"
"\n"
"int TargetConsole = 1 ;\n"
"int TargetDesktop = 2 ;\n"
"int TargetLib     = 3 ;\n"
"int TargetCCore   = 4 ;\n"
"\n"
"struct Param\n"
" {\n"
"  text CCORE_ROOT = \"\" ;\n"
"\n"
"  text CCORE_TARGET = \"\" ;\n"
"\n"
"  text OBJ_PATH = \".obj\" ;\n"
"\n"
"  text[] SRC_PATH_LIST = {\".\"} ;\n"
"\n"
"  text[] CCOPT_EXTRA = {} ;\n"
"\n"
"  text[] LDOPT_EXTRA = {} ;\n"
"  \n"
"  text TARGET = \"./main.exe\" ;\n"
"  \n"
"  int target;\n"
"  \n"
"  Tools * tools = null ;\n"
" };\n"
" \n"
"struct Tools\n"
" {\n"
"  text CC = \"g++\" ;\n"
"  text LD = \"g++\" ;\n"
"  text AS = \"as\" ;\n"
"  text AR = \"ar\" ;\n"
"  text RM = \"rm -f\" ;\n"
"  \n"
"  text[] CCOPT;\n"
"  text[] LDOPT;\n"
"  text[] ASOPT;\n"
"  \n"
"  text[] LDOPT_DESKTOP;\n"
"  \n"
"  text CORELIB;\n"
" };\n"
"\n"
"\n"
"\n"
"\n"
