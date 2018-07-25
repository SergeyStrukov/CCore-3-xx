Doc Data = { 'test' , { False , 0FF0000h } , { True , 0 } , { null , &start } , 

{
 { True , {0,0} },
 { True , {0,0} },
 { True , 0 },
 { True , 0 },
 null,null,null,null,
 null,null,null,null
} ,

{
 &scope1,
 &font1,
 &font2,
 &font3,
 &font4,
 &fmt1,
 &start
}

} ;

Font font1 = { 'font' , False , 'Times New Roman' , 24 , { True , False } , { True , False } , { True , 0 } } ;

Font font2 = { 'font_b' , True , 'Times New Roman' , 24 , { False , True } , { True , False } , { True , 0 } } ;

Font font3 = { 'font_i' , True , 'Times New Roman' , 24 , { True , False } , { False , True } , { True , 0 } } ;

Font font4 = { 'font_bi' , True , 'Times New Roman' , 24 , { False , True } , { False , True } , { True , 0 } } ;

Format fmt1 = { 'fmt' , True , { null , &font1 } , { True , 0 } , { True , 0 } , { True , 0 } } ;

TextList list1 = { 'menu' , True , { 'fmt' } , { True } , { True } , { 

{ 

{ 'item1' , { {

{ {True,null},{True,null},{True,null},{null,null},{'iframe1',null} },
{ {True,null},{True,null},{True,null},{null,null},{'iframe2',null} },
{ {True,null},{True,null},{True,null},{null,null},{'iframe3',null} }
  
} , 1 } }, 

{ 'item2' , { {

{ {True,null},{True,null},{True,null},{null,null},{'iframe1',null} },
{ {True,null},{True,null},{True,null},{null,null},{'iframe2',null} },
{ {True,null},{True,null},{True,null},{null,null},{'iframe3',null} }
  
} , 1 } },

{ 'item3' , { {

{ {True,null},{True,null},{True,null},{null,null},{'iframe1',null} },
{ {True,null},{True,null},{True,null},{null,null},{'iframe2',null} },
{ {True,null},{True,null},{True,null},{null,null},{'iframe3',null} }
  
} , 1 } } 
 
} , 2 } } ;




Scope scope1 = { 'page1' , True , 
{
 { True , {0,0} },
 { True , {0,0} },
 { True , 0 },
 { True , 0 },
 null,null,null,null,
 null,null,null,null
} ,

{
 &common_fonts,
 &elems
}

} ;

Section common_fonts = { True , 'common fonts' ,
 
{
 &font1,
 &font2,
 &font3,
 &font4
}
 
} ;

Section elems = { True , 'elements' ,
 
{
 &fmt1,
 &list1
}
 
} ;


Page start = { 'start' , True , 'test page' , { True , 0 } , { True , 0 } , {'content',null} , {null,null} , {null,null} , 

{ 

{

{ {True,null},{True,null},{True,null},{null,null},{'frame1',null} },
{ {True,null},{True,null},{True,null},{null,null},{'frame2',null} },
{ {True,null},{True,null},{True,null},{null,null},{'frame3',null} }
  
} , 1 } 

} ;
