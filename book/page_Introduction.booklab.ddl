Doc Data = { "" , { True , 00h } , { True , 00h } , { null , null } , { { True , { 0 , 0 } } , { True , { 0 , 0 } } , { True , 0 } , { True , 0 } , null , null , null , null , null , null } , 

{
& o1,
& o2,
& o3,
& o4
}

 };

Extern o1 = { & o5 };

Extern o2 = { & o6 };

Page o3 = { "page_Introduction" , True , "" , { True , NoColor } , { True , NoColor } , { null , null } , { null , null } , { null , null } , {

{
{ { True , { 0 , 0 } } , { True , { 0 , 0 } } , { True , NoColor } , { null , null } , { null , & o7 } }
}

 , 0 } };

Format o5 = { "fmt_h1" , True , { null , null } , { True , NoColor } , { True , NoColor } , { True , 0 } };

OneLine o6 = { "align_h1" , True , { True , 0 } };

Text o7 = { "" , True , { "align_h1" , null } , { "fmt_h1" , null } , 

{


{
{ "Introduction" , { null , null } , { null , null } }
}


}

 };

Link o4 = { "link_Introduction" , True , f1 };

Frame *f1 = o3.list.list+0 ;

