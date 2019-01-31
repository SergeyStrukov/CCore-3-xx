include <pretext:/Book1.ddl>

Book Data = { .title = "C++ test" , .start = & #Doc#page1 } ;

scope Doc {

Font cfont = { "Anonymous Pro" , 22 , False , False , 0 } ;

Font cfont_bold = { "Anonymous Pro" , 22 , True , False , 0 } ;

Format cfmt = { & cfont , NoColor , NoColor , 0 } ;

Format cfmt_long_comment = { & cfont , NoColor , 06400h , 0 } ;

Format cfmt_keyword = { & cfont , NoColor , 0CDh , 0 } ;

Format cfmt_name = { & cfont , NoColor , NoColor , 0 } ;

Format cfmt_number = { & cfont , NoColor , 0800000h , 0 } ;

Format cfmt_op = { & cfont_bold , NoColor , NoColor , 0 } ;

FixedText sample = {
{
{
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

Page page1 = { "sample" ,
{
{ & sample , & ANONYM1 , { 10 , 10 } , { 5 , 5 } , NoColor }
}
, 0C0C0C0h , 00h , null , null , null } ;

DoubleLine ANONYM1 = { { 3 , 2 } , 0808080h , 0E6E6FAh } ;


}

