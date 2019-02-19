include <pretext:/Book1.ddl>

Book Data = { .title = "ContourLab manual" , .start = & #Doc#Pages#page1 , .back = 0C0C0C0h , .fore = 00h } ;

scope Doc {

scope Pages {

Point DefaultOuter = { 5 , 5 } ;

MultiLine DefaultPlacement = { { 12 , 10 } , { 2 , 1 } } ;

Font font_h1 = { "Bookman Old Style" , 60 , True , False , 0 } ;

Font font_h2 = { "Bookman Old Style" , 30 , False , False , 0 } ;

Font font = { "Cambria" , 22 , False , False , 15 } ;

Font font_bold = { "Cambria" , 22 , True , False , 15 } ;

Format fmt_h1 = { & font_h1 , NoColor , 0FFh , 0 } ;

Format fmt_h2 = { & font_h2 , NoColor , 06400h , 0 } ;

Format fmt = { & font , NoColor , 00h , 0 } ;

Format fmt_bold = { & font_bold , NoColor , 00h , 0 } ;

OneLine pl_h1 = { 2 } ;

OneLine pl_h2 = { 2 } ;

Font font_bullet1 = { "Georgia" , 22 , False , False , 0 } ;

Format fmt_bullet1 = { & font_bullet1 , NoColor , 0FFh , 0 } ;

Font font_b1 = { "Georgia" , 22 , False , True , 0 } ;

Format fmt_b1 = { & font_b1 , NoColor , 0FFh , 1 } ;

Font font_fixed = { "Anonymous Pro" , 22 , False , False , 0 } ;

Format fmt_fixed = { & font_fixed , 0D3D3D3h , 00h , 0 } ;

Page page1 = { "Introduction" ,
{
{ & ANONYM1 , null , DefaultInner , { 30 , 30 } , NoColor }
,{ & ANONYM2 , null , DefaultInner , { 20 , 20 } , NoColor }
,{ & ANONYM3 , null , DefaultInner , DefaultOuter , NoColor }
,{ & ANONYM4 , null , DefaultInner , { 20 , 20 } , NoColor }
,{ & ANONYM5 , null , DefaultInner , DefaultOuter , NoColor }
,{ & ANONYM6 , null , DefaultInner , { 10 , 10 } , NoColor }
}
, NoColor , NoColor , null , null , null } ;

Text ANONYM1 = {
{
{ "ContourLab" , null , null }
,{ "manual" , null , null }
}
, & fmt_h1 , & pl_h1 } ;

Text ANONYM2 = {
{
{ "1." , null , null }
,{ "Introduction." , null , null }
}
, & fmt_h2 , & pl_h2 } ;

Text ANONYM3 = {
{
{ "ContourLab" , & fmt_bold , null }
,{ "is" , null , null }
,{ "a" , null , null }
,{ "tool" , null , null }
,{ "for" , null , null }
,{ "the" , null , null }
,{ "geometrical" , null , null }
,{ "drawing." , null , null }
}
, & fmt , &DefaultPlacement } ;

Text ANONYM4 = {
{
{ "2." , null , null }
,{ "Pads" , null , null }
,{ "and" , null , null }
,{ "formulas." , null , null }
}
, & fmt_h2 , & pl_h2 } ;

Text ANONYM5 = {
{
{ "Here" , null , null }
,{ "is" , null , null }
,{ "a" , null , null }
,{ "list" , null , null }
,{ "of" , null , null }
,{ "pads" , null , null }
,{ "and" , null , null }
,{ "formulas." , null , null }
}
, & fmt , &DefaultPlacement } ;

TextList ANONYM6 = {
{
{ "•" ,
{
{ & ANONYM7 , null , DefaultInner , DefaultOuter , NoColor }
,{ & pads , null , { 10 , 10 } , DefaultOuter , NoColor }
}
}
,{ "•" ,
{
{ & ANONYM8 , null , DefaultInner , DefaultOuter , NoColor }
,{ & formulas , null , { 10 , 10 } , DefaultOuter , NoColor }
}
}
}
, & fmt_bullet1 , 5 , 5 } ;

FixedText ANONYM7 = {
{
{
{ "Pads" , null , null }
}
}
, & fmt_b1 } ;

FixedText ANONYM8 = {
{
{
{ "Formulas" , null , null }
}
}
, & fmt_b1 } ;

FixedText formulas = {
{
{
{ "------                                                                                     " , null , null }
,{ "" , null , null }
}
,{
}
,{
{ "Len(A,B)" , null , null }
}
,{
}
,{
{ "Angle(A,O,B)" , null , null }
}
,{
}
,{
{ "AngleC(a,b,c)" , null , null }
}
,{
}
,{
{ "------" , null , null }
}
,{
}
,{
{ "Mid(A,B)" , null , null }
}
,{
}
,{
{ "Part(A,B,ratio)" , null , null }
}
,{
}
,{
{ "Move(A,B,P)" , null , null }
}
,{
}
,{
{ "MoveLen(line,len,P)" , null , null }
}
,{
}
,{
{ "Proj(line,P)" , null , null }
}
,{
}
,{
{ "Mirror(line,P)" , null , null }
}
,{
}
,{
{ "------" , null , null }
}
,{
}
,{
{ "Up(len,P)" , null , null }
}
,{
}
,{
{ "Down(len,P)" , null , null }
}
,{
}
,{
{ "Left(len,P)" , null , null }
}
,{
}
,{
{ "Right(len,P)" , null , null }
}
,{
}
,{
{ "------" , null , null }
}
,{
}
,{
{ "Rot(O,angle,P)" , null , null }
}
,{
}
,{
{ "RotOrt(O,P)" , null , null }
}
,{
}
,{
{ "------" , null , null }
}
,{
}
,{
{ "Line(A,B)" , null , null }
}
,{
}
,{
{ "MidOrt(A,B)" , null , null }
}
,{
}
,{
{ "Cir(A,len)" , null , null }
}
,{
}
,{
{ "OCir(A,B,C)" , null , null }
}
,{
}
,{
{ "------" , null , null }
}
,{
}
,{
{ "Meet(line,line)" , null , null }
}
,{
}
,{
{ "Meet(line,cir)" , null , null }
}
,{
}
,{
{ "Meet(cir,cir)" , null , null }
}
,{
}
,{
{ "First(couple)" , null , null }
}
,{
}
,{
{ "Second(couple)" , null , null }
}
,{
}
,{
{ "------" , null , null }
}
,{
}
,{
{ "Path(A...)" , null , null }
}
,{
}
,{
{ "Loop(A...)" , null , null }
}
,{
}
,{
{ "------" , null , null }
}
,{
}
,{
{ "Step(A...)" , null , null }
}
,{
}
,{
{ "BPath(step...)" , null , null }
}
,{
}
,{
{ "BLoop(step...)" , null , null }
}
,{
}
,{
{ "------" , null , null }
}
,{
}
,{
{ "Solid(loop)" , null , null }
}
,{
}
,{
{ "------" , null , null }
}
}
, & fmt_fixed } ;

FixedText pads = {
{
{
{ "------ Literals                                                                            " , null , null }
}
,{
{ "" , null , null }
}
,{
{ "123.456" , null , null }
}
,{
}
,{
{ "123.456p length" , null , null }
}
,{
}
,{
{ "123.456g angle" , null , null }
}
,{
{ "" , null , null }
}
,{
{ "------ Basic types" , null , null }
}
,{
{ "" , null , null }
}
,{
{ "" , null , null }
,{ "point" , null , null }
}
,{
{ "len" , null , null }
}
,{
{ "angle" , null , null }
}
,{
{ "ratio" , null , null }
}
,{
{ "" , null , null }
}
,{
{ "------ Points" , null , null }
}
,{
}
,{
{ "point P(123,456)" , null , null }
}
,{
}
,{
{ "P(123,456)" , null , null }
}
,{
}
,{
{ "------ Length" , null , null }
}
,{
}
,{
{ "len width = 123" , null , null }
}
,{
}
,{
{ "len width = 123p" , null , null }
}
,{
}
,{
{ "width = 123p" , null , null }
}
,{
}
,{
{ "------ Angle" , null , null }
}
,{
}
,{
{ "angle alpha = 45" , null , null }
}
,{
}
,{
{ "angle alpha = 45g" , null , null }
}
,{
}
,{
{ "alpha = 45g" , null , null }
}
,{
}
,{
{ "------ Ratio" , null , null }
}
,{
}
,{
{ "ratio lambda = 1.5" , null , null }
}
,{
}
,{
{ "lambda = 1.5" , null , null }
,{ "" , null , null }
}
}
, & fmt_fixed } ;

}


}

