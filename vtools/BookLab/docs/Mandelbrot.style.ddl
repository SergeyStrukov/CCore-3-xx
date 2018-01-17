/* Mandelbrot.style.ddl */

include <Book.ddl>

scope Pages {

VColor Silver = 0C0C0C0h ;
VColor Black  =       0h ;
VColor Blue   =     0FFh ;
VColor Green  =    8000h ;

VColor Back = Silver ;
VColor Fore = Black ;

Point DefaultInner = { 5 , 5 } ;

MultiLine DefaultPlacement = { {1,1} , {2,1} } ;

OneLine Left = { OneLine#Left } ;

OneLine Center = { OneLine#Center } ;

Coord mul = 14 ;
Coord div = 10 ;

Font font_h1 = { 'Times New Roman' , (mul*40)/div , True } ;

Font font_h2 = { 'Times New Roman' , (mul*24)/div , True } ;

Font font_p = { 'Times New Roman' , (mul*16)/div } ;

Format fmt_h1 = { .font = &font_h1 , .fore = Blue } ;

Format fmt_h2 = { .font = &font_h2 , .fore = Green } ;

Format DefaultFormat = { .font = &font_p } ;

} // scope Pages
