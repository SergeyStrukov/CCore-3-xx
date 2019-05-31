scope page_Abort {

Text b0 = { {
  { "Abort" }
} , & fmt_h2 , & align_h2 } ;

Text b1 = { {
  { "Files" }
 ,{ "CCore/inc/Abort.h" , & fmt_text_Files_b }
 ,{ "CCore/src/AbortMsgFunc.cpp" , & fmt_text_Files_b }
 ,{ "HCore/src/Abort.cpp" , & fmt_text_Files_b }
 ,{ "XCore/src/Abort.cpp" , & fmt_text_Files_b }
} , & fmt_text_Files , & align_text_Files } ;

Text b2 = { {
  { "There" }
 ,{ "are" }
 ,{ "two" }
 ,{ "functions" }
 ,{ "to" }
 ,{ "abort" }
 ,{ "a" }
 ,{ "program" }
 ,{ "execution" }
 ,{ "with" }
 ,{ "a" }
 ,{ "diagnostic" }
 ,{ "message:" }
} , & fmt_text , & align_text } ;

FixedText b3 = { {
{
}
,
{
}
,
{
  { "void" , & fmt_cpp_cfmt_keyword }
 ,{ " " , & fmt_cpp_cfmt }
 ,{ "Abort" , & fmt_cpp_Att }
 ,{ "(" , & fmt_cpp_cfmt_op }
 ,{ "StrLen" , & fmt_cpp_cfmt_name }
 ,{ " " , & fmt_cpp_cfmt }
 ,{ "str" , & fmt_cpp_cfmt_name }
 ,{ ")" , & fmt_cpp_cfmt_op }
 ,{ ";" , & fmt_cpp_cfmt_op }
}
,
{
  { " " , & fmt_cpp_cfmt }
}
,
{
  { "void" , & fmt_cpp_cfmt_keyword }
 ,{ " " , & fmt_cpp_cfmt }
 ,{ "Abort" , & fmt_cpp_Att }
 ,{ "(" , & fmt_cpp_cfmt_op }
 ,{ "const" , & fmt_cpp_cfmt_keyword }
 ,{ " " , & fmt_cpp_cfmt }
 ,{ "char" , & fmt_cpp_cfmt_keyword }
 ,{ " " , & fmt_cpp_cfmt }
 ,{ "*" , & fmt_cpp_cfmt_op }
 ,{ "zstr" , & fmt_cpp_cfmt_name }
 ,{ ")" , & fmt_cpp_cfmt_op }
 ,{ ";" , & fmt_cpp_cfmt_op }
}
,
{
}
,
{
}
} , & fmt_cpp } ;

Text b4 = { {
  { "First" }
 ,{ "of" }
 ,{ "them" }
 ,{ "accepts" }
 ,{ "a" }
 ,{ "message" }
 ,{ "text" }
 ,{ "as" }
 ,{ "a" }
 ,{ "StrLen" , & fmt_text_b }
 ,{ "argument," }
 ,{ "second" }
 ,{ "—" }
 ,{ "as" }
 ,{ "a" }
 ,{ "zero-terminated" }
 ,{ "character" }
 ,{ "string." }
 ,{ "The" }
 ,{ "exact" }
 ,{ "method" }
 ,{ "of" }
 ,{ "the" }
 ,{ "sending" }
 ,{ "a" }
 ,{ "diagnostic" }
 ,{ "message" }
 ,{ "is" }
 ,{ "target-dependent" }
 ,{ "and" }
 ,{ "implemented" }
 ,{ "differently" }
 ,{ "for" }
 ,{ "HCore" , & fmt_text_b }
 ,{ "and" }
 ,{ "XCore" , & fmt_text_b }
 ,{ "targets." }
} , & fmt_text , & align_text } ;

Text b5 = { {
  { "There" }
 ,{ "is" }
 ,{ "also" }
 ,{ "the" }
 ,{ "global" }
 ,{ "constant" }
 ,{ "function" }
 ,{ "pointer," }
 ,{ "which" }
 ,{ "can" }
 ,{ "be" }
 ,{ "used" }
 ,{ "to" }
 ,{ "alter" }
 ,{ "the" }
 ,{ "Abort()" , & fmt_text_b }
 ,{ "behavior." }
} , & fmt_text , & align_text } ;

FixedText b6 = { {
{
}
,
{
}
,
{
  { "/* types */" , & fmt_cpp_cfmt_long_comment }
 ,{ " " , & fmt_cpp_cfmt }
}
,
{
}
,
{
  { "using" , & fmt_cpp_cfmt_keyword }
 ,{ " " , & fmt_cpp_cfmt }
 ,{ "AbortMsgFuncType" , & fmt_cpp_Att }
 ,{ " " , & fmt_cpp_cfmt }
 ,{ "=" , & fmt_cpp_cfmt_op }
 ,{ " " , & fmt_cpp_cfmt }
 ,{ "void" , & fmt_cpp_cfmt_keyword }
 ,{ " " , & fmt_cpp_cfmt }
 ,{ "(" , & fmt_cpp_cfmt_op }
 ,{ "*" , & fmt_cpp_cfmt_op }
 ,{ ")" , & fmt_cpp_cfmt_op }
 ,{ "(" , & fmt_cpp_cfmt_op }
 ,{ "StrLen" , & fmt_cpp_cfmt_name }
 ,{ " " , & fmt_cpp_cfmt }
 ,{ "str" , & fmt_cpp_cfmt_name }
 ,{ ")" , & fmt_cpp_cfmt_op }
 ,{ " " , & fmt_cpp_cfmt }
 ,{ ";" , & fmt_cpp_cfmt_op }
}
,
{
}
,
{
  { "/* global const AbortMsgFunc */" , & fmt_cpp_cfmt_long_comment }
 ,{ " " , & fmt_cpp_cfmt }
}
,
{
}
,
{
  { "extern" , & fmt_cpp_cfmt_keyword }
 ,{ " " , & fmt_cpp_cfmt }
 ,{ "const" , & fmt_cpp_cfmt_keyword }
 ,{ " " , & fmt_cpp_cfmt }
 ,{ "AbortMsgFuncType" , & fmt_cpp_cfmt_name }
 ,{ " " , & fmt_cpp_cfmt }
 ,{ "AbortMsgFunc" , & fmt_cpp_Att }
 ,{ ";" , & fmt_cpp_cfmt_op }
}
,
{
}
,
{
}
} , & fmt_cpp } ;

Text b7 = { {
  { "You" }
 ,{ "may" }
 ,{ "link" }
 ,{ "an" }
 ,{ "object" }
 ,{ "file" }
 ,{ "in" }
 ,{ "your" }
 ,{ "project" }
 ,{ "with" }
 ,{ "this" }
 ,{ "constant" }
 ,{ "defined" }
 ,{ "to" }
 ,{ "introduce" }
 ,{ "a" }
 ,{ "hook" }
 ,{ "in" }
 ,{ "Abort()" , & fmt_text_b }
 ,{ "." }
 ,{ "Be" }
 ,{ "reasonable" }
 ,{ "with" }
 ,{ "hook" }
 ,{ "actions:" }
 ,{ "on" }
 ,{ "XCore" , & fmt_text_b }
 ,{ "targets" }
 ,{ "it" }
 ,{ "may" }
 ,{ "be" }
 ,{ "called" }
 ,{ "in" }
 ,{ "any" }
 ,{ "context," }
 ,{ "so" }
 ,{ "you" }
 ,{ "cannot" }
 ,{ "do" }
 ,{ "any" }
 ,{ "\"heavy\"" }
 ,{ "job" }
 ,{ "inside." }
 ,{ "The" }
 ,{ "same" }
 ,{ "is" }
 ,{ "true" }
 ,{ "on" }
 ,{ "HCore" , & fmt_text_b }
 ,{ "targets:" }
 ,{ "use" }
 ,{ "it" }
 ,{ "just" }
 ,{ "to" }
 ,{ "show" }
 ,{ "or" }
 ,{ "log" }
 ,{ "a" }
 ,{ "message" }
 ,{ "(using" }
 ,{ "MessageBox()" , & fmt_text_b }
 ,{ "," }
 ,{ "for" }
 ,{ "example)." }
} , & fmt_text , & align_text } ;

Page page = { "CCore -> Abort" ,
{
  { & b0 , null , inner_h2 , outer_h2 , back_h2 }
 ,{ & b1 , null , inner_text_Files , outer_text_Files , back_text_Files }
 ,{ & b2 , null , inner_text , outer_text , back_text }
 ,{ & b3 , null , inner_cpp , outer_cpp , back_cpp }
 ,{ & b4 , null , inner_text , outer_text , back_text }
 ,{ & b5 , null , inner_text , outer_text , back_text }
 ,{ & b6 , null , inner_cpp , outer_cpp , back_cpp }
 ,{ & b7 , null , inner_text , outer_text , back_text }
} , NoColor , NoColor , null , null , null };

Link link = { &page } ;

}

