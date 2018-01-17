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

Coord mul = 14 ;
Coord div = 10 ;

Font font_h1 = { 'Times New Roman' , (mul*40)/div , True } ;

Font font_h2 = { 'Times New Roman' , (mul*24)/div , True } ;

Font font_p = { 'Times New Roman' , (mul*16)/div } ;

Font font_b = { 'Times New Roman' , (mul*16)/div , True } ;

Font font_i = { 'Times New Roman' , (mul*16)/div , False , True } ;

Format fmt_h1 = { .font = &font_h1 , .fore = Blue } ;

Format fmt_h2 = { .font = &font_h2 , .fore = Green } ;

OneLine align_h1 = { OneLine#Center } ;

OneLine align_h2 = { OneLine#Center } ;

Format DefaultFormat = { .font = &font_p } ;

Format fmt_b = { .font = &font_b } ;

Format fmt_i = { .font = &font_i } ;

Format fmt_u = { .font = &font_p , .effect = Format#Underline } ;

} // scope Pages
