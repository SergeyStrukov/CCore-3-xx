include <pretext:/Book1.ddl>

Book Data = { .title = "Mandelbrot scope" , .start = & #Doc#Pages#page1 , .back = 0C0C0C0h , .fore = 00h } ;

scope Doc {

scope Pages {

Point DefaultInner = { 10 , 10 } ;

Format DefaultBulletFormat = { & font_bullet , NoColor , NoColor , 0 } ;

Format DefaultFormat = { & font , NoColor , NoColor , 0 } ;

MultiLine DefaultPlacement = { { 1 , 1 } , { 2 , 1 } } ;

Font font = { "Times New Roman" , 22 , False , False , 0 } ;

Font font_h1 = { "Times New Roman" , 56 , True , False , 0 } ;

Font font_h2 = { "Times New Roman" , 32 , True , False , 0 } ;

Font font_bold = { "Times New Roman" , 22 , True , False , 0 } ;

Font font_italic = { "Times New Roman" , 22 , False , True , 0 } ;

Font font_bullet = { "Times New Roman" , 22 , True , False , 0 } ;

Format fmt_h1 = { & font_h1 , NoColor , 0FFh , 0 } ;

Format fmt_h2 = { & font_h2 , NoColor , 06400h , 0 } ;

OneLine align_h1 = { 2 } ;

OneLine align_h2 = { 2 } ;

Format fmt_bold = { & font_bold , NoColor , NoColor , 0 } ;

Format fmt_italic = { & font_italic , NoColor , NoColor , 0 } ;

Format fmt_underline = { & font , NoColor , NoColor , 1 } ;

Page page1 = { "Manual" ,
{
{ & ANONYM1 , null , DefaultInner , DefaultOuter , NoColor }
,{ & ANONYM2 , null , DefaultInner , DefaultOuter , NoColor }
,{ & ANONYM3 , null , DefaultInner , DefaultOuter , NoColor }
,{ & ANONYM4 , null , DefaultInner , DefaultOuter , NoColor }
,{ & ANONYM5 , null , DefaultInner , DefaultOuter , NoColor }
,{ & ANONYM6 , null , DefaultInner , DefaultOuter , NoColor }
}
, NoColor , NoColor , null , null , null } ;

Text ANONYM1 = {
{
{ "Mandelbrot" , null , null }
,{ "scope" , null , null }
}
, & fmt_h1 , & align_h1 } ;

Text ANONYM2 = {
{
{ "Introduction" , null , null }
}
, & fmt_h2 , & align_h2 } ;

Bitmap ANONYM3 = { "Mandelbrot.png" } ;

Text ANONYM4 = {
{
{ "Mandelbrot" , & fmt_bold , null }
,{ "scope" , & fmt_bold , null }
,{ "(MScope.exe)" , null , null }
,{ "is" , null , null }
,{ "a" , null , null }
,{ "software" , null , null }
,{ "to" , null , null }
,{ "display" , null , null }
,{ "the" , null , null }
,{ "Mandelbrot" , null , null }
,{ "Set." , null , null }
,{ "The" , null , null }
,{ "Mandelbrot" , null , null }
,{ "Set" , null , null }
,{ "is" , null , null }
,{ "a" , null , null }
,{ "famous" , null , null }
,{ "mathematical" , null , null }
,{ "fractal" , null , null }
,{ "set," , null , null }
,{ "it" , null , null }
,{ "has" , null , null }
,{ "been" , null , null }
,{ "discovered" , null , null }
,{ "by" , null , null }
,{ "Benoit B. Mandelbrot" , & fmt_underline , null }
,{ "." , null , null }
,{ "The" , null , null }
,{ "Mandelbrot" , null , null }
,{ "Set" , null , null }
,{ "itself" , null , null }
,{ "cannot" , null , null }
,{ "be" , null , null }
,{ "calculated," , null , null }
,{ "because" , null , null }
,{ "it" , null , null }
,{ "requires" , null , null }
,{ "infinite" , null , null }
,{ "number" , null , null }
,{ "of" , null , null }
,{ "precise" , null , null }
,{ "iteration" , null , null }
,{ "per" , null , null }
,{ "point." , null , null }
,{ "But" , null , null }
,{ "we" , null , null }
,{ "can" , null , null }
,{ "calculate" , null , null }
,{ "and" , null , null }
,{ "paint" , null , null }
,{ "the" , null , null }
,{ "outer" , null , null }
,{ "of" , null , null }
,{ "it" , null , null }
,{ "up" , null , null }
,{ "to" , null , null }
,{ "some" , null , null }
,{ "level." , null , null }
,{ "The" , null , null }
,{ "rest" , null , null }
,{ "of" , null , null }
,{ "the" , null , null }
,{ "painted" , null , null }
,{ "area" , null , null }
,{ "is" , null , null }
,{ "black" , null , null }
,{ "and" , null , null }
,{ "contains" , null , null }
,{ "inside" , null , null }
,{ "" , null , null }
,{ "the" , null , null }
,{ "true" , null , null }
,{ "Mandelbrot" , null , null }
,{ "Set," , null , null }
,{ "but" , null , null }
,{ "we" , null , null }
,{ "don't" , null , null }
,{ "know" , null , null }
,{ "which" , null , null }
,{ "part." , null , null }
,{ "The" , null , null }
,{ "more" , null , null }
,{ "deeper" , null , null }
,{ "we" , null , null }
,{ "calculate," , null , null }
,{ "the" , null , null }
,{ "more" , null , null }
,{ "closer" , null , null }
,{ "we" , null , null }
,{ "are" , null , null }
,{ "coming" , null , null }
,{ "to" , null , null }
,{ "the" , null , null }
,{ "true" , null , null }
,{ "border." , null , null }
,{ "You" , null , null }
,{ "can" , null , null }
,{ "select" , null , null }
,{ "the" , null , null }
,{ "depth" , null , null }
,{ "in" , null , null }
,{ "the" , null , null }
,{ "Options" , & fmt_italic , null }
,{ "menu." , null , null }
,{ "You" , null , null }
,{ "can" , null , null }
,{ "also" , null , null }
,{ "adjust" , null , null }
,{ "the" , null , null }
,{ "color" , null , null }
,{ "palette" , null , null }
,{ "to" , null , null }
,{ "paint" , null , null }
,{ "the" , null , null }
,{ "outer" , null , null }
,{ "part." , null , null }
}
, &DefaultFormat , &DefaultPlacement } ;

Text ANONYM5 = {
{
{ "Navigation" , null , null }
}
, & fmt_h2 , & align_h2 } ;

Text ANONYM6 = {
{
{ "To" , null , null }
,{ "move" , null , null }
,{ "the" , null , null }
,{ "picture" , null , null }
,{ "drag" , null , null }
,{ "it" , null , null }
,{ "by" , null , null }
,{ "the" , null , null }
,{ "mouse." , null , null }
,{ "" , null , null }
,{ "To" , null , null }
,{ "zoom/unzoom" , null , null }
,{ "the" , null , null }
,{ "picture" , null , null }
,{ "use" , null , null }
,{ "the" , null , null }
,{ "mouse" , null , null }
,{ "wheel." , null , null }
,{ "" , null , null }
,{ "To" , null , null }
,{ "return" , null , null }
,{ "to" , null , null }
,{ "the" , null , null }
,{ "top" , null , null }
,{ "view" , null , null }
,{ "use" , null , null }
,{ "the" , null , null }
,{ "key" , null , null }
,{ "Home." , & fmt_bold , null }
}
, &DefaultFormat , &DefaultPlacement } ;

}


}

