/* test.style.ddl */

include <pretext:/Book1.ddl>

scope Pages {

text BookName = 'test' ;
text PageName = 'Content' ;

VColor Silver = 0C0C0C0h ;
VColor Black  =       0h ;
VColor Blue   =     0FFh ;
VColor Green  =    8000h ;

VColor Wheat = 0F5DEB3h ;

VColor Back = Wheat ;
VColor Fore = Black ;

Point DefaultInner = { 10 , 10 } ;

MultiLine DefaultPlacement = { {1,1} , {2,1} } ;

Font font_h1 = { 'Times New Roman' , 56 , True } ;

Font font_h2 = { 'Times New Roman' , 33 , True } ;

Font font_p = { 'Times New Roman' , 22 } ;

Font font_b = { 'Times New Roman' , 22 , True } ;

Font font_i = { 'Times New Roman' , 22 , False , True } ;

Format fmt_h1 = { .font = &font_h1 , .fore = Blue } ;

Format fmt_h2 = { .font = &font_h2 , .fore = Green } ;

OneLine align_h1 = { OneLine#Center } ;

OneLine align_h2 = { OneLine#Center } ;

Format DefaultFormat = { .font = &font_p } ;

Format fmt_b = { .font = &font_b } ;

Format fmt_i = { .font = &font_i } ;

Format fmt_u = { .font = &font_p , .effect = Format#Underline } ;

Format fmt_h = fmt_u ;

Format fmt_li = { .font = &font_p , .fore = Blue } ;

MultiLine align_li = { {1,1} , {0,1} } ;

Font bullet_font = { 'Times New Roman' , 22 } ;

Format DefaultBulletFormat = { .font = &bullet_font } ;

} // scope Pages
