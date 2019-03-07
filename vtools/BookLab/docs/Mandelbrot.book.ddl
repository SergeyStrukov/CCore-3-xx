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
,{ & ANONYM7 , null , DefaultInner , DefaultOuter , NoColor }
,{ & ANONYM8 , null , DefaultInner , DefaultOuter , NoColor }
,{ & ANONYM9 , null , DefaultInner , DefaultOuter , NoColor }
,{ & ANONYM10 , null , DefaultInner , DefaultOuter , NoColor }
,{ & ANONYM11 , null , DefaultInner , DefaultOuter , NoColor }
,{ & ANONYM12 , null , DefaultInner , DefaultOuter , NoColor }
,{ & ANONYM13 , null , DefaultInner , DefaultOuter , NoColor }
,{ & ANONYM14 , null , DefaultInner , DefaultOuter , NoColor }
,{ & ANONYM15 , null , DefaultInner , DefaultOuter , NoColor }
,{ & ANONYM16 , null , DefaultInner , DefaultOuter , NoColor }
,{ & ANONYM17 , null , DefaultInner , DefaultOuter , NoColor }
,{ & ANONYM18 , null , DefaultInner , DefaultOuter , NoColor }
,{ & ANONYM19 , null , DefaultInner , DefaultOuter , NoColor }
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

Bitmap ANONYM3 = { "Mandelbrot.zipmap" } ;

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

Text ANONYM7 = {
{
{ "Software" , null , null }
,{ "options" , null , null }
}
, & fmt_h2 , & align_h2 } ;

Text ANONYM8 = {
{
{ "The" , null , null }
,{ "menu" , null , null }
,{ "Options" , & fmt_italic , null }
,{ "contains" , null , null }
,{ "three" , null , null }
,{ "submenus:" , null , null }
,{ "Global," , & fmt_italic , null }
,{ "Application," , & fmt_italic , null }
,{ "Colors." , & fmt_italic , null }
,{ "" , null , null }
,{ "The" , null , null }
,{ "first" , null , null }
,{ "submenu" , null , null }
,{ "opens" , null , null }
,{ "the" , null , null }
,{ "dialog" , null , null }
,{ "to" , null , null }
,{ "edit" , null , null }
,{ "preferences," , null , null }
,{ "shared" , null , null }
,{ "by" , null , null }
,{ "all" , null , null }
,{ "applications." , null , null }
,{ "" , null , null }
,{ "The" , null , null }
,{ "second" , null , null }
,{ "submenu" , null , null }
,{ "opens" , null , null }
,{ "the" , null , null }
,{ "dialog" , null , null }
,{ "to" , null , null }
,{ "edit" , null , null }
,{ "preferences," , null , null }
,{ "specific" , null , null }
,{ "to" , null , null }
,{ "the" , null , null }
,{ "application." , null , null }
,{ "" , null , null }
,{ "The" , null , null }
,{ "submenu" , null , null }
,{ "Colors" , & fmt_italic , null }
,{ "opens" , null , null }
,{ "the" , null , null }
,{ "dialog," , null , null }
,{ "used" , null , null }
,{ "to" , null , null }
,{ "change" , null , null }
,{ "the" , null , null }
,{ "color" , null , null }
,{ "palette" , null , null }
,{ "and" , null , null }
,{ "the" , null , null }
,{ "depth" , null , null }
,{ "of" , null , null }
,{ "the" , null , null }
,{ "calculation." , null , null }
}
, &DefaultFormat , &DefaultPlacement } ;

Bitmap ANONYM9 = { "Colors.zipmap" } ;

Text ANONYM10 = {
{
{ "There" , null , null }
,{ "are" , null , null }
,{ "several" , null , null }
,{ "configuration" , null , null }
,{ "options" , null , null }
,{ "on" , null , null }
,{ "this" , null , null }
,{ "dialog." , null , null }
}
, &DefaultFormat , &DefaultPlacement } ;

Text ANONYM11 = {
{
{ "The" , null , null }
,{ "spinor" , null , null }
,{ "Cap" , & fmt_bold , null }
,{ "controls" , null , null }
,{ "the" , null , null }
,{ "calculation" , null , null }
,{ "depth." , null , null }
}
, &DefaultFormat , &DefaultPlacement } ;

Text ANONYM12 = {
{
{ "The" , null , null }
,{ "spinor" , null , null }
,{ "Len" , & fmt_bold , null }
,{ "determines" , null , null }
,{ "the" , null , null }
,{ "number" , null , null }
,{ "of" , null , null }
,{ "colors" , null , null }
,{ "between" , null , null }
,{ "pivot" , null , null }
,{ "colors." , null , null }
,{ "" , null , null }
,{ "The" , null , null }
,{ "full" , null , null }
,{ "color" , null , null }
,{ "palette" , null , null }
,{ "is" , null , null }
,{ "built" , null , null }
,{ "upon" , null , null }
,{ "the" , null , null }
,{ "pivot" , null , null }
,{ "color" , null , null }
,{ "list." , null , null }
,{ "" , null , null }
,{ "Between" , null , null }
,{ "two" , null , null }
,{ "consecutive" , null , null }
,{ "pivot" , null , null }
,{ "colors" , null , null }
,{ "a" , null , null }
,{ "number" , null , null }
,{ "of" , null , null }
,{ "intermediate" , null , null }
,{ "colors" , null , null }
,{ "are" , null , null }
,{ "inserted," , null , null }
,{ "using" , null , null }
,{ "progressive" , null , null }
,{ "blending" , null , null }
,{ "of" , null , null }
,{ "edge" , null , null }
,{ "colors." , null , null }
,{ "" , null , null }
,{ "The" , null , null }
,{ "pivot" , null , null }
,{ "list" , null , null }
,{ "is" , null , null }
,{ "cycled," , null , null }
,{ "when" , null , null }
,{ "needed," , null , null }
,{ "except" , null , null }
,{ "the" , null , null }
,{ "first" , null , null }
,{ "pivot" , null , null }
,{ "color," , null , null }
,{ "which" , null , null }
,{ "is" , null , null }
,{ "usually" , null , null }
,{ "Blue." , & fmt_bold , null }
}
, &DefaultFormat , &DefaultPlacement } ;

Text ANONYM13 = {
{
{ "The" , null , null }
,{ "full" , null , null }
,{ "color" , null , null }
,{ "palette" , null , null }
,{ "is" , null , null }
,{ "shown" , null , null }
,{ "on" , null , null }
,{ "the" , null , null }
,{ "bottom" , null , null }
,{ "part" , null , null }
,{ "of" , null , null }
,{ "the" , null , null }
,{ "dialog." , null , null }
}
, &DefaultFormat , &DefaultPlacement } ;

Text ANONYM14 = {
{
{ "The" , null , null }
,{ "list" , null , null }
,{ "of" , null , null }
,{ "pivot" , null , null }
,{ "colors" , null , null }
,{ "is" , null , null }
,{ "presented" , null , null }
,{ "in" , null , null }
,{ "the" , null , null }
,{ "middle" , null , null }
,{ "left" , null , null }
,{ "part" , null , null }
,{ "of" , null , null }
,{ "the" , null , null }
,{ "dialog." , null , null }
,{ "" , null , null }
,{ "You" , null , null }
,{ "can" , null , null }
,{ "insert" , null , null }
,{ "a" , null , null }
,{ "new" , null , null }
,{ "element" , null , null }
,{ "or" , null , null }
,{ "delete" , null , null }
,{ "an" , null , null }
,{ "existing" , null , null }
,{ "element" , null , null }
,{ "from" , null , null }
,{ "the" , null , null }
,{ "list" , null , null }
,{ "using" , null , null }
,{ "buttons" , null , null }
,{ "or" , null , null }
,{ "keys" , null , null }
,{ "Insert" , & fmt_bold , null }
,{ "and" , null , null }
,{ "Delete." , & fmt_bold , null }
,{ "" , null , null }
,{ "You" , null , null }
,{ "can" , null , null }
,{ "also" , null , null }
,{ "change" , null , null }
,{ "the" , null , null }
,{ "selected" , null , null }
,{ "color" , null , null }
,{ "using" , null , null }
,{ "RGB" , null , null }
,{ "spinors" , null , null }
,{ "or" , null , null }
,{ "the" , null , null }
,{ "color" , null , null }
,{ "cube." , null , null }
}
, &DefaultFormat , &DefaultPlacement } ;

Text ANONYM15 = {
{
{ "System" , null , null }
,{ "requirements" , null , null }
}
, & fmt_h2 , & align_h2 } ;

Text ANONYM16 = {
{
{ "To" , null , null }
,{ "run" , null , null }
,{ "this" , null , null }
,{ "software" , null , null }
,{ "you" , null , null }
,{ "will" , null , null }
,{ "need" , null , null }
,{ "a" , null , null }
,{ "quit" , null , null }
,{ "fast" , null , null }
,{ "PC" , null , null }
,{ "with" , null , null }
,{ "GPU" , null , null }
,{ "(or" , null , null }
,{ "another" , null , null }
,{ "OpenCL" , null , null }
,{ "accelerator)." , null , null }
,{ "" , null , null }
,{ "Operating" , null , null }
,{ "system" , null , null }
,{ "Windows" , null , null }
,{ "10" , null , null }
,{ "is" , null , null }
,{ "required," , null , null }
,{ "but" , null , null }
,{ "you" , null , null }
,{ "may" , null , null }
,{ "try" , null , null }
,{ "earlier" , null , null }
,{ "versions" , null , null }
,{ "(not" , null , null }
,{ "guaranteed)." , null , null }
,{ "" , null , null }
,{ "To" , null , null }
,{ "perform" , null , null }
,{ "calculation" , null , null }
,{ "an" , null , null }
,{ "OpenCL" , null , null }
,{ "provider" , null , null }
,{ "is" , null , null }
,{ "required." , null , null }
,{ "" , null , null }
,{ "It" , null , null }
,{ "is" , null , null }
,{ "installed" , null , null }
,{ "automatically" , null , null }
,{ "with" , null , null }
,{ "modern" , null , null }
,{ "GPU" , null , null }
,{ "drivers." , null , null }
}
, &DefaultFormat , &DefaultPlacement } ;

Text ANONYM17 = {
{
{ "Copyright" , null , null }
,{ "notes" , null , null }
}
, & fmt_h2 , & align_h2 } ;

Text ANONYM18 = {
{
{ "Copyright" , null , null }
,{ "(c)" , null , null }
,{ "2017" , null , null }
,{ "Sergey" , null , null }
,{ "Strukov." , null , null }
,{ "All" , null , null }
,{ "rights" , null , null }
,{ "reserved." , null , null }
}
, &DefaultFormat , &DefaultPlacement } ;

Text ANONYM19 = {
{
{ "This" , null , null }
,{ "software" , null , null }
,{ "is" , null , null }
,{ "distributed" , null , null }
,{ "under" , null , null }
,{ "the" , null , null }
,{ "commercial" , null , null }
,{ "license," , null , null }
,{ "see" , null , null }
,{ "the" , null , null }
,{ "License.txt" , & fmt_bold , null }
,{ "for" , null , null }
,{ "details." , null , null }
,{ "Goto top" , null , & test }
}
, &DefaultFormat , &DefaultPlacement } ;

Link test = { ANONYM20 , { 0 } } ;

}


}

Page * ANONYM20 = & #Doc#Pages#page1 ;

