Doc Data = { "Mandelbrot scope" , { False , 0C0C0C0h } , { False , 00h } , { "Pages#page1" , null } , { { False , { 5 , 5 } } , { True , { 0 , 0 } } , { True , 0 } , { True , 0 } , null , null , null , null , null , null , null , null } , 

{
& o1
}

 };

Scope o1 = { "Pages" , True , { { False , { 10 , 10 } } , { True , { 0 , 0 } } , { True , 0 } , { True , 0 } , null , null , null , & o2 , null , & o3 , null , & o4 } , 

{
& o5,
& o6
}

 };

Format o2 = { "" , True , { "font_bullet" , null } , { True , NoColor } , { True , NoColor } , { True , 0 } };

Format o3 = { "" , True , { "font" , null } , { True , NoColor } , { True , NoColor } , { True , 0 } };

MultiLine o4 = { "" , True , { False , { 1 , 1 } } , { False , { 2 , 1 } } };

Section o5 = { True , "Style" , 

{
& o7,
& o8,
& o9,
& o10,
& o11,
& o12,
& o13,
& o14,
& o15,
& o16,
& o17,
& o18,
& o19,
& o20
}

 };

Section o6 = { True , "Text" , 

{
& o21,
& o22
}

 };

Font o7 = { "font" , False , "Times New Roman" , 22 , { False , False } , { False , False } , { False , 0 } };

Font o8 = { "font_h1" , False , "Times New Roman" , 56 , { False , True } , { False , False } , { False , 0 } };

Font o9 = { "font_h2" , False , "Times New Roman" , 32 , { False , True } , { False , False } , { False , 0 } };

Font o10 = { "font_bold" , False , "Times New Roman" , 22 , { False , True } , { False , False } , { False , 0 } };

Font o11 = { "font_italic" , False , "Times New Roman" , 22 , { False , False } , { False , True } , { False , 0 } };

Font o12 = { "font_bullet" , False , "Times New Roman" , 22 , { False , True } , { False , False } , { False , 0 } };

Format o13 = { "fmt_h1" , False , { "font_h1" , null } , { True , NoColor } , { False , 0FFh } , { True , 0 } };

Format o14 = { "fmt_h2" , True , { "font_h2" , null } , { True , NoColor } , { False , 06400h } , { True , 0 } };

Format o15 = { "fmt_t1" , True , { null , & o23 } , { True , NoColor } , { True , NoColor } , { True , 0 } };

OneLine o16 = { "align_h1" , False , { False , 2 } };

OneLine o17 = { "align_h2" , False , { False , 2 } };

Format o18 = { "fmt_bold" , False , { "font_bold" , null } , { True , NoColor } , { True , NoColor } , { True , 0 } };

Format o19 = { "fmt_italic" , False , { "font_italic" , null } , { True , NoColor } , { True , NoColor } , { True , 0 } };

Format o20 = { "fmt_under" , False , { "font" , null } , { True , NoColor } , { True , NoColor } , { False , 1 } };

Page o21 = { "page1" , True , "Manual" , { True , NoColor } , { True , NoColor } , { null , null } , { null , null } , { null , null } , {

{
{ { True , { 0 , 0 } } , { True , { 0 , 0 } } , { True , NoColor } , { null , null } , { null , & o24 } },
{ { True , { 0 , 0 } } , { True , { 0 , 0 } } , { True , NoColor } , { null , null } , { null , & o25 } },
{ { True , { 0 , 0 } } , { True , { 0 , 0 } } , { True , NoColor } , { null , null } , { null , null } },
{ { True , { 0 , 0 } } , { True , { 0 , 0 } } , { True , NoColor } , { null , null } , { null , null } },
{ { True , { 0 , 0 } } , { True , { 0 , 0 } } , { True , NoColor } , { null , null } , { null , null } },
{ { True , { 0 , 0 } } , { True , { 0 , 0 } } , { True , NoColor } , { null , null } , { null , null } },
{ { True , { 0 , 0 } } , { True , { 0 , 0 } } , { True , NoColor } , { null , null } , { null , null } }
}

 , 1 } };

Font o23 = { "" , True , "Courier" , 20 , { True , False } , { True , False } , { True , 0 } };

Text o24 = { "" , True , { "align_h1" , null } , { "fmt_h1" , null } , 

{

}

 };

Text o25 = { "" , True , { "align_h2" , null } , { "fmt_h2" , null } , 

{

}

 };

Link o22 = { "link1" , True , f1 };

Frame *f1 = o21.list.list+1 ;

