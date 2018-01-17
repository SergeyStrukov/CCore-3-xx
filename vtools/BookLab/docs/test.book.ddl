/* test.book.ddl */

include <Book.ddl>

VColor Wheat = 0F5DEB3h ;

scope Test {

/* spacing */

Point DefaultInner = { 10 , 10 } ;

Point DefaultOuter = { 5 , 5 } ;

/* font */

Font fixed = { 'Anonymous Pro' , 24 } ;

Font fixed_bold = { .face = fixed.face , .size = fixed.size , .bold = True } ;

Font fixed_italic = { .face = fixed.face , .size = fixed.size , .italic = True } ;

Font font = { 'Times New Roman' , 28 } ;

Font font_italic = { .face = font.face , .size=font.size , .italic = True } ;

/* formats */

VColor Black = 0h ;
VColor Blue = 0FFh ;
VColor DarkGreen = 08000h ;

VColor Light = 0D0D0D0h ;

Format fmt = {&fixed,NoColor,Black} ;

Format fmt_keyword = {&fixed_bold,NoColor,Blue} ;

Format fmt_name = {null,Light,DarkGreen,Format#Underline} ;

Format fmt_iname = {&fixed_italic,Light,DarkGreen,Format#Strikeout} ;

Format fmt_H1 = {&font} ;

Format fmt_H1_italic = { .font = &font_italic , .back = Light } ;

/* placement */

OneLine H1 = { OneLine#Center } ;

MultiLine DefaultPlacement = { {5,4} , {3,1} } ;
               
/* texts */

FixedText text1 = { { 
                     { {'struct',&fmt_keyword} , {' '} , {'Size',&fmt_name} } ,
                     { {'struct',&fmt_keyword} , {' '} , {'Size',&fmt_iname} } 
                    },
                    
                    &fmt 
                  } ;



Text text2 = { { 
                { 'Header H1 this is' } , 
                { 'a test book' , &fmt_H1_italic } , 
                { 'with test content' } 
               } , &fmt_H1 , &H1 } ;
               
Text text3 = { { {'The'},{'full'},{'color'},{'palette'},{'is'},{'shown'},{'on'},{'the'},{'bottom'},{'part'},
                 {'of'},{'the'},{'dialog.'} } } ;                            

Bitmap pict1 = 
 {
  { Black , Black , Black , Black , Black , Black , Black , Black , Black , Black , Black , Black , Black , Black , Black , Black , Black , Black , Black , Black , Black , Black } ,
  
  { Black , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Black } ,
  { Black , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Black } ,
  { Black , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Black } ,
  { Black , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Black } ,
  { Black , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Black } ,
  { Black , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Black } ,
  { Black , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Black } ,
  { Black , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Black } ,
  { Black , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Black } ,
  { Black , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Blue , Black } ,
  
  { Black , Black , Black , Black , Black , Black , Black , Black , Black , Black , Black , Black , Black , Black , Black , Black , Black , Black , Black , Black , Black , Black }
 };

/* pages */

Page page1 = { 'Main page' , { 
                               { &text1 , &DefaultSingleLine },
                               { &text2 , &DefaultDoubleLine },
                               { &text3 , &DefaultSingleLine },
                               { &pict1 , null , DefaultInner , DefaultOuter , 0FFh }
 
                             } } ;
                             
} // scope Test                             

Book Data = { 'Test book' , {&Test#page1} } ;

