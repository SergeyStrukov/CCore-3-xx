/* test.book.ddl */

include <pretext:/Book1.ddl>

Book Data = { "test page" , &Page1#page , 0A0A0A0h , 0FFh } ;

/* Page1 */

scope Page1 {

Point DefaultInner = { 20 , 10 } ;

Point DefaultOuter = { 30 , 20 } ;

OneLine pl_left = { OneLine#Left } ;

OneLine pl_right = { OneLine#Right } ;

OneLine pl_center = { OneLine#Center } ;

Font font_text = { 'Times New Roman' , 24 } ;

// ---

Page page = { "page1" , { 
                         { .body = &t1 , .line = &line1 , .col = 0FF0000h },
                         { .body = &t2 , .line = &line1 , .col = 00000FFh },
                         { .body = &t3 , .line = &line1 , .col = 0008000h }
                         
                          
                        } , 0C0C0C0h , 0h , null , null , &Page2#page } ;

SingleLine line1 = { {2,1} , 0FF00h } ;

Text t1 = { {
             { 'aligned left' }

            } , &fmt1 , &pl_left } ;

Text t2 = { {
             { 'aligned right' }

            } , &fmt1 , &pl_right } ;
            
Text t3 = { {
             { 'aligned center' }

            } , &fmt1 , &pl_center } ;
            
Format fmt1 = { &font_text } ;

} // scope Page1

/* Page2 */

scope Page2 {

Point DefaultInner = { 20 , 10 } ;

Point DefaultOuter = { 30 , 20 } ;

OneLine pl_left = { OneLine#Left } ;

OneLine pl_right = { OneLine#Right } ;

OneLine pl_center = { OneLine#Center } ;

Font font_text = { 'Times New Roman' , 24 } ;

// ---

Page page = { "page2" , { 
                         { .body = &t1 , .line = &line1 , .col = 0FF0000h },
                         { .body = &t2 , .line = &line1 , .col = 00000FFh },
                         { .body = &t3 , .line = &line1 , .col = 0008000h }
                         
                          
                        } , NoColor , NoColor , null , &Page1#page , null } ;

DoubleLine line1 = { {1,1} } ;

Text t1 = { {
             { 'aligned left' }

            } , &fmt1 , &pl_left } ;

Text t2 = { {
             { 'aligned right' }

            } , &fmt1 , &pl_right } ;
            
Text t3 = { {
             { 'aligned center' }

            } , &fmt1 , &pl_center } ;
            
Format fmt1 = { &font_text } ;

} // scope Page2
