/* test.book.ddl */

include <Book.ddl>

VColor Wheat = 0F5DEB3h ;

scope Test {

Point DefaultInner = { 10 , 10 } ;

Point DefaultOuter = { 5 , 5 } ;

Text text1 = {} ;
Text text2 = {} ;
Text text3 = {} ;

Page page1 = { 'Main page' , { 
                               { &text1 , &DefaultSingleLine },
                               { &text2 , &DefaultDoubleLine },
                               { &text3 , null , DefaultInner , DefaultOuter , 0FFh }
 
                             } } ;
                             
} // scope Test                             

Book Data = { 'Test book' , {&Test#page1} } ;

