/* test.book.ddl */

include <Book.ddl>

VColor Wheat = 0F5DEB3h ;

scope Test {

/* spacing */

Point DefaultInner = { 10 , 10 } ;

Point DefaultOuter = { 5 , 5 } ;

/* font */

Font font = { 'Anonymous Pro' , 24 } ;

Font font_bold = { .face = font.face , .size = font.size , .bold = True } ;

Font font_italic = { .face = font.face , .size = font.size , .italic = True } ;

/* formats */

VColor Black = 0h ;
VColor Blue = 0FFh ;
VColor DarkGreen = 08000h ;

VColor Light = 0D0D0D0h ;

Format fmt = {&font,NoColor,Black} ;

Format fmt_keyword = {&font_bold,NoColor,Blue} ;

Format fmt_name = {null,Light,DarkGreen,Format#Underline} ;

Format fmt_iname = {&font_italic,Light,DarkGreen,Format#Strikeout} ;

/* texts */

FixedText text1 = { { 
                     { {'struct',&fmt_keyword} , {' '} , {'Size',&fmt_name} } ,
                     { {'struct',&fmt_keyword} , {' '} , {'Size',&fmt_iname} } 
                    },
                    
                    &fmt 
                  } ;

Text text2 = {} ;

Text text3 = {} ;

/* pages */

Page page1 = { 'Main page' , { 
                               { &text1 , &DefaultSingleLine },
                               { &text2 , &DefaultDoubleLine },
                               { &text3 , null , DefaultInner , DefaultOuter , 0FFh }
 
                             } } ;
                             
} // scope Test                             

Book Data = { 'Test book' , {&Test#page1} } ;

