include <pretext:/Book1.ddl>

Book Data = { .title = "C++ test" , .start = & #Doc#page1 } ;

scope Doc {

Point DefaultInner = { 10 , 10 } ;

Point DefaultOuter = { 5 , 5 } ;

DoubleLine line = { { 3 , 2 } , 0808080h , 0E6E6FAh } ;

Font cfont = { "Fixed" , 22 , False , False , 0 } ;

Font cfont_bold = { "Fixed" , 22 , True , False , 0 } ;

Format cfmt = { & cfont , NoColor , NoColor , 0 } ;

Format cfmt_long_comment = { & cfont , 0F5DEB3h , 06400h , 0 } ;

Format cfmt_keyword = { & cfont , NoColor , 0CDh , 0 } ;

Format cfmt_name = { & cfont , NoColor , NoColor , 0 } ;

Format cfmt_number = { & cfont , NoColor , 0800000h , 0 } ;

Format cfmt_op = { & cfont_bold , NoColor , NoColor , 0 } ;

Format cfmt_string = { & cfont , 087CEEBh , 0800000h , 0 } ;

Format cfmt_short_comment = { & cfont , 0F5DEB3h , 06400h , 1 } ;

Format cfmt_char = { & cfont , 0FFFFh , 0800000h , 0 } ;

FixedText sample1 = {
{
{
{ "hint" , & cfmt_long_comment , & page2 }
}
,{
{ "/* enum CharFlags */" , & cfmt_long_comment , null }
}
,{
}
,{
{ "enum" , & cfmt_keyword , null }
,{ " " , & cfmt , null }
,{ "CharFlags" , & cfmt_name , null }
,{ " " , & cfmt , null }
,{ ":" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "unsigned" , & cfmt_keyword , null }
}
,{
{ " " , & cfmt , null }
,{ "{" , & cfmt_op , null }
}
,{
{ "  " , & cfmt , null }
,{ "CharNull" , & cfmt_name , null }
,{ "   " , & cfmt , null }
,{ "=" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "0" , & cfmt_number , null }
,{ "," , & cfmt_op , null }
}
,{
}
,{
{ "  " , & cfmt , null }
,{ "CharLetter" , & cfmt_name , null }
,{ " " , & cfmt , null }
,{ "=" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "Bit" , & cfmt_name , null }
,{ "(" , & cfmt_op , null }
,{ "0" , & cfmt_number , null }
,{ ")" , & cfmt_op , null }
,{ "," , & cfmt_op , null }
}
,{
{ "  " , & cfmt , null }
,{ "CharDigit" , & cfmt_name , null }
,{ "  " , & cfmt , null }
,{ "=" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "Bit" , & cfmt_name , null }
,{ "(" , & cfmt_op , null }
,{ "1" , & cfmt_number , null }
,{ ")" , & cfmt_op , null }
,{ "," , & cfmt_op , null }
}
,{
{ "  " , & cfmt , null }
,{ "CharPunct" , & cfmt_name , null }
,{ "  " , & cfmt , null }
,{ "=" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "Bit" , & cfmt_name , null }
,{ "(" , & cfmt_op , null }
,{ "2" , & cfmt_number , null }
,{ ")" , & cfmt_op , null }
,{ "," , & cfmt_op , null }
}
,{
{ "  " , & cfmt , null }
,{ "CharQuote" , & cfmt_name , null }
,{ "  " , & cfmt , null }
,{ "=" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "Bit" , & cfmt_name , null }
,{ "(" , & cfmt_op , null }
,{ "3" , & cfmt_number , null }
,{ ")" , & cfmt_op , null }
,{ "," , & cfmt_op , null }
}
,{
{ "  " , & cfmt , null }
,{ "CharSpace" , & cfmt_name , null }
,{ "  " , & cfmt , null }
,{ "=" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "Bit" , & cfmt_name , null }
,{ "(" , & cfmt_op , null }
,{ "4" , & cfmt_number , null }
,{ ")" , & cfmt_op , null }
,{ "," , & cfmt_op , null }
}
,{
{ "  " , & cfmt , null }
,{ "CharEOL" , & cfmt_name , null }
,{ "    " , & cfmt , null }
,{ "=" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "Bit" , & cfmt_name , null }
,{ "(" , & cfmt_op , null }
,{ "5" , & cfmt_number , null }
,{ ")" , & cfmt_op , null }
,{ "," , & cfmt_op , null }
}
,{
}
,{
{ "  " , & cfmt , null }
,{ "CharHex" , & cfmt_name , null }
,{ "    " , & cfmt , null }
,{ "=" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "Bit" , & cfmt_name , null }
,{ "(" , & cfmt_op , null }
,{ "6" , & cfmt_number , null }
,{ ")" , & cfmt_op , null }
,{ "," , & cfmt_op , null }
}
,{
{ "  " , & cfmt , null }
,{ "CharOct" , & cfmt_name , null }
,{ "    " , & cfmt , null }
,{ "=" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "Bit" , & cfmt_name , null }
,{ "(" , & cfmt_op , null }
,{ "7" , & cfmt_number , null }
,{ ")" , & cfmt_op , null }
,{ "," , & cfmt_op , null }
}
,{
}
,{
{ "  " , & cfmt , null }
,{ "CharPunct2" , & cfmt_name , null }
,{ " " , & cfmt , null }
,{ "=" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "Bit" , & cfmt_name , null }
,{ "(" , & cfmt_op , null }
,{ "8" , & cfmt_number , null }
,{ ")" , & cfmt_op , null }
,{ "," , & cfmt_op , null }
}
,{
{ "  " , & cfmt , null }
,{ "CharPunct3" , & cfmt_name , null }
,{ " " , & cfmt , null }
,{ "=" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "Bit" , & cfmt_name , null }
,{ "(" , & cfmt_op , null }
,{ "9" , & cfmt_number , null }
,{ ")" , & cfmt_op , null }
}
,{
{ " " , & cfmt , null }
,{ "}" , & cfmt_op , null }
,{ ";" , & cfmt_op , null }
}
,{
}
,{
{ "inline" , & cfmt_keyword , null }
,{ " " , & cfmt , null }
,{ "CharFlags" , & cfmt_name , null }
,{ " " , & cfmt , null }
,{ "operator" , & cfmt_keyword , null }
,{ " " , & cfmt , null }
,{ "|" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "(" , & cfmt_op , null }
,{ "CharFlags" , & cfmt_name , null }
,{ " " , & cfmt , null }
,{ "a" , & cfmt_name , null }
,{ "," , & cfmt_op , null }
,{ "CharFlags" , & cfmt_name , null }
,{ " " , & cfmt , null }
,{ "b" , & cfmt_name , null }
,{ ")" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "{" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "return" , & cfmt_keyword , null }
,{ " " , & cfmt , null }
,{ "CharFlags" , & cfmt_name , null }
,{ "(" , & cfmt_op , null }
,{ "unsigned" , & cfmt_keyword , null }
,{ "(" , & cfmt_op , null }
,{ "a" , & cfmt_name , null }
,{ ")" , & cfmt_op , null }
,{ "|" , & cfmt_op , null }
,{ "b" , & cfmt_name , null }
,{ ")" , & cfmt_op , null }
,{ ";" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "}" , & cfmt_op , null }
}
,{
}
,{
{ "inline" , & cfmt_keyword , null }
,{ " " , & cfmt , null }
,{ "CharFlags" , & cfmt_name , null }
,{ " " , & cfmt , null }
,{ "operator" , & cfmt_keyword , null }
,{ " " , & cfmt , null }
,{ "|=" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "(" , & cfmt_op , null }
,{ "CharFlags" , & cfmt_name , null }
,{ " " , & cfmt , null }
,{ "&" , & cfmt_op , null }
,{ "a" , & cfmt_name , null }
,{ "," , & cfmt_op , null }
,{ "CharFlags" , & cfmt_name , null }
,{ " " , & cfmt , null }
,{ "b" , & cfmt_name , null }
,{ ")" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "{" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "a" , & cfmt_name , null }
,{ "=" , & cfmt_op , null }
,{ "a" , & cfmt_name , null }
,{ "|" , & cfmt_op , null }
,{ "b" , & cfmt_name , null }
,{ ";" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "return" , & cfmt_keyword , null }
,{ " " , & cfmt , null }
,{ "a" , & cfmt_name , null }
,{ ";" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "}" , & cfmt_op , null }
}
}
, & cfmt } ;

FixedText sample2 = {
{
{
{ "/* test.cpp */" , & cfmt_long_comment , null }
}
,{
{ "/*----------------------------------------------------------------------------------------" , & cfmt_long_comment , null }
}
,{
{ "//" , & cfmt_long_comment , null }
}
,{
{ "//  Project: BookLab 1.00" , & cfmt_long_comment , null }
}
,{
{ "//" , & cfmt_long_comment , null }
}
,{
{ "//  License: Boost Software License - Version 1.0 - August 17th, 2003" , & cfmt_long_comment , null }
}
,{
{ "//" , & cfmt_long_comment , null }
}
,{
{ "//            see http://www.boost.org/LICENSE_1_0.txt or the local copy" , & cfmt_long_comment , null }
}
,{
{ "//" , & cfmt_long_comment , null }
}
,{
{ "//  Copyright (c) 2019 Sergey Strukov. All rights reserved." , & cfmt_long_comment , null }
}
,{
{ "//" , & cfmt_long_comment , null }
}
,{
{ "//--------------------------------------------------------------------------------------*/" , & cfmt_long_comment , null }
}
,{
}
,{
{ "namespace" , & cfmt_keyword , null }
,{ " " , & cfmt , null }
,{ "CppText" , & cfmt_name , null }
,{ " " , & cfmt , null }
,{ "{" , & cfmt_op , null }
}
,{
}
,{
{ "int" , & cfmt_keyword , null }
,{ " " , & cfmt , null }
,{ "X" , & cfmt_name , null }
,{ "=" , & cfmt_op , null }
,{ "12345" , & cfmt_number , null }
,{ ";" , & cfmt_op , null }
}
,{
}
,{
{ "const" , & cfmt_keyword , null }
,{ " " , & cfmt , null }
,{ "char" , & cfmt_keyword , null }
,{ " " , & cfmt , null }
,{ "*" , & cfmt_op , null }
,{ "S" , & cfmt_name , null }
,{ "=" , & cfmt_op , null }
,{ "\"abcdefghijklmnopqrstuvwxyz\\n\\r\\t\\\"\\?\\123\\xABCDE\"" , & cfmt_string , null }
,{ ";" , & cfmt_op , null }
}
,{
}
,{
{ "char" , & cfmt_keyword , null }
,{ " " , & cfmt , null }
,{ "C" , & cfmt_name , null }
,{ "=" , & cfmt_op , null }
,{ "'\\x12BC'" , & cfmt_char , null }
,{ ";" , & cfmt_op , null }
}
,{
}
,{
{ "{" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "}" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "[" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "]" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "(" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ ")" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "#" , & cfmt_op , null }
}
,{
}
,{
{ ";" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ ":" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "?" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "." , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "," , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "+" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "-" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "*" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "/" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "%" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "^" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "&" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "|" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "~" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "!" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "=" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "<" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ ">" , & cfmt_op , null }
}
,{
}
,{
{ "+=" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "-=" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "*=" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "/=" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "%=" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "^=" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "&=" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "|=" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "<=" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ ">=" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "==" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "!=" , & cfmt_op , null }
}
,{
}
,{
{ ".*" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "->" , & cfmt_op , null }
}
,{
}
,{
{ "..." , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "->*" , & cfmt_op , null }
}
,{
}
,{
{ "&&" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "||" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "<<" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ ">>" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "++" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "-" , & cfmt_op , null }
,{ "-" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "::" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "##" , & cfmt_op , null }
}
,{
}
,{
{ "<<=" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ ">>=" , & cfmt_op , null }
}
,{
}
,{
{ "}" , & cfmt_op , null }
,{ " " , & cfmt , null }
,{ "// namespace CppText" , & cfmt_short_comment , null }
}
,{
}
}
, & cfmt } ;

Page page1 = { "sample" ,
{
{ & sample1 , & line , DefaultInner , DefaultOuter , NoColor }
,{ & sample2 , & line , DefaultInner , DefaultOuter , NoColor }
}
, 0C0C0C0h , 00h , null , null , null } ;

Page page2 = { "" ,
{
{ & sample2 , null , DefaultInner , DefaultOuter , NoColor }
}
, NoColor , NoColor , null , null , null } ;


}

