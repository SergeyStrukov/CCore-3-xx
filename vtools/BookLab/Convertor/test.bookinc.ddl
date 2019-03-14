scope Index {

Text b0 = { {
 { "CCore" }
} , & fmt_h1 , & align_h1 } ;

Text b1_0 = { {
 { "Introduction" , & fmt_list_a }
} , & fmt_list , & align_list } ;

Text b1_1 = { {
 { "Installation" , & fmt_list_a }
} , & fmt_list , & align_list } ;

Text b1_2 = { {
 { "Preliminary" }
 ,{ "considerations" }
Page page = { "CCore 3.xx" ,
{
 { & b0 , null , inner_h1 , outer_h1 , back_h1 }
 ,{ & b1 , null , inner_list , outer_list , back_list }
} , NoColor , NoColor , null , null , null };

Link link = { &page } ;

}

