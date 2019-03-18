/* CCore.book.ddl */

include <pretext:/Book1.ddl>

include <ColorSet.ddl>

scope Pages {

/* defaults */

Point DefaultInner = { 10 , 2 } ;

Point DefaultOuter = { 10 , 10 } ;

Coord DefaultBulletSpace = 10 ;

Coord DefaultItemSpace = 5 ;

Format DefaultBulletFormat = DefaultFormat ;

Format DefaultFormat = fmt_text ;

MultiLine DefaultPlacement = { { 12 , 10 } , { 2 , 1 } } ;

/* format */

 // colors

VColor vc_h1 = Blue ;

VColor vc_h1_back = DarkGray ;

VColor vc_h2 = DarkGreen ;

VColor vc_h2_back = Wheat ;

VColor vc_h3 = DarkGreen ;

VColor vc_h4 = Indigo ;

VColor vc_a = Blue ;

VColor vc_Alert = Red ;

VColor vc_Hint = Blue ;

VColor vc_Att = Purple ;

VColor vc_Files = Aqua ;

VColor vc_cpp = Silver ;

 // font faces

text face = "Bookman Old Style" ;

text fixed = "Fixed" ;

 // text

Font font_text = { face , 20 } ;

Format fmt_text = { & font_text } ;

Point inner_text = DefaultInner ;

Point outer_text = DefaultOuter ;

VColor back_text = NoColor ;

MultiLine align_text = DefaultPlacement ;

Font font_text_b = font_text { .bold = True  } ;

Format fmt_text_b = { & font_text_b } ;

Font font_text_i = font_text { .italic = True  } ;

Format fmt_text_i = { & font_text_i } ;

Format fmt_text_u = fmt_text { .effect=Format#Underline } ;

 // text_c1

Font font_text_c1 = { face , 80 } ;

Format fmt_text_c1 = { & font_text_c1 } ;

Point inner_text_c1 = { 10 , 50 } ;

Point outer_text_c1 = DefaultOuter ;

VColor back_text_c1 = NoColor ;

OneLine align_text_c1 = { OneLine#Center } ;

 // text_c2

Format fmt_text_c2 = fmt_text ;

Point inner_text_c2 = DefaultInner ;

Point outer_text_c2 = DefaultOuter ;

VColor back_text_c2 = NoColor ;

OneLine align_text_c2 = { OneLine#Center } ;

 // text_c3

Format fmt_text_c3 = fmt_text ;

Point inner_text_c3 = { 10 , 200 } ;

Point outer_text_c3 = DefaultOuter ;

VColor back_text_c3 = NoColor ;

MultiLine align_text_c3 = DefaultPlacement ;

 // text_cpp

Font font_cpp = { fixed , 22 } ;

Format fmt_cpp = { & font_cpp , vc_cpp } ;

Point inner_cpp = DefaultInner ;

Point outer_cpp = DefaultOuter ;

VColor back_cpp = NoColor ;

Font font_cpp_b = font_cpp { .bold = True } ;

Format fmt_cpp_b = fmt_cpp { .font = & font_cpp_b } ;

Font font_cpp_i = font_cpp { .italic = True } ;

Format fmt_cpp_i = fmt_cpp { .font = & font_cpp_i } ;

Format fmt_cpp_Att = fmt_cpp { .fore = vc_Att } ; 

Format fmt_cpp_a = fmt_cpp { .fore = vc_a , .effect = Format#Underline } ; 

Format fmt_cpp_Alert = fmt_cpp { .fore = vc_Alert } ; 


Format fmt_cpp_cfmt_name = { & font_cpp , NoColor , NoColor } ;

Format fmt_cpp_cfmt_keyword = { & font_cpp , NoColor , MediumBlue } ;

Format fmt_cpp_cfmt_number = { & font_cpp , NoColor , Maroon } ;

Format fmt_cpp_cfmt_op = { & font_cpp_b , NoColor , MediumBlue } ;

Format fmt_cpp_cfmt_string = { & font_cpp , SkyBlue , Maroon } ;

Format fmt_cpp_cfmt_char = { & font_cpp , Aqua , Maroon } ;

Format fmt_cpp_cfmt = { & font_cpp , NoColor , NoColor } ;

Format fmt_cpp_cfmt_short_comment = { & font_cpp , Wheat , DarkGreen } ;

Format fmt_cpp_cfmt_long_comment = { & font_cpp , Wheat , DarkGreen } ;

Format fmt_cpp_cfmt_other = { & font_cpp , NoColor , Red } ;

 // text_Files

Font font_text_Files = { fixed , 22 } ;

Format fmt_text_Files = { & font_text_Files , vc_Files } ;

Point inner_text_Files = DefaultInner ;

Point outer_text_Files = DefaultOuter ;

VColor back_text_Files = NoColor ;

OneLine align_text_Files = { OneLine#Left } ;

Font font_text_Files_b = font_text_Files { .bold = True  } ;

Format fmt_text_Files_b = fmt_text_Files { .font = & font_text_Files_b } ;

 // text_Alert

Format fmt_text_Alert = fmt_text { .fore = vc_Alert } ;

 // text_Hint

Format fmt_text_Hint = fmt_text { .fore = vc_Hint } ;

 // text_Att

Format fmt_text_Att = fmt_text { .fore = vc_Att } ;

 // h1

Font font_h1 = { face , 60 } ;

Format fmt_h1 = { & font_h1 , vc_h1_back , vc_h1 } ; 

Point inner_h1 = DefaultInner ;

Point outer_h1 = DefaultOuter ;

VColor back_h1 = NoColor ;

OneLine align_h1 = { OneLine#Center } ;

 // h2

Font font_h2 = { face , 36 } ;

Format fmt_h2 = { & font_h2 , vc_h2_back , vc_h2 } ;

Point inner_h2 = DefaultInner ;

Point outer_h2 = DefaultOuter ;

VColor back_h2 = NoColor ;

OneLine align_h2 = { OneLine#Left } ;

Format fmt_h2_a = fmt_h2 { .fore = vc_a , .effect = Format#Underline } ;

 // h3

Font font_h3 = { face , 30 } ;

Format fmt_h3 = { & font_h3 , NoColor , vc_h3 , Format#Underline } ;

Point inner_h3 = DefaultInner ;

Point outer_h3 = DefaultOuter ;

VColor back_h3 = NoColor ;

OneLine align_h3 = { OneLine#Left } ;

Font font_h3_i = font_h3 { .italic = True } ;

Format fmt_h3_i =  fmt_h3 { .font = & font_h3_i } ;

Font font_h3_b = font_h3 { .bold = True } ;

Format fmt_h3_b =  fmt_h3 { .font = & font_h3_b } ;

 // h4

Font font_h4 = { face , 24 } ;

Format fmt_h4 = { & font_h4 , NoColor , vc_h4 , Format#Underline } ;

Point inner_h4 = DefaultInner ;

Point outer_h4 = DefaultOuter ;

VColor back_h4 = NoColor ;

OneLine align_h4 = { OneLine#Left } ;

 // list

Format fmt_list = fmt_text ;

Point inner_list = { 0 , 0 } ;

Point outer_list = { 40 , 0 } ;

VColor back_list = NoColor ;

OneLine align_list = { OneLine#Left } ;

Point ItemInner = { 2 , 2 } ;

Point ItemOuter = { 0 , 0 } ;

Format fmt_list_b = fmt_text_b ;

Format fmt_list_a = fmt_list { .fore = vc_a , .effect = Format#Underline } ;

Format fmt_list_Alert = fmt_list { .fore = vc_Alert } ;

Font font_Cmd = { fixed , 22 } ;

Format fmt_list_Cmd = { & font_Cmd , White , Black } ;

 // img

Point inner_img = DefaultInner ;

Point outer_img = DefaultOuter ;

VColor back_img = NoColor ;

 // a

Format fmt_text_a = fmt_text { .fore = vc_a , .effect = Format#Underline } ;

/* content */

Page content = { "Content" , { { & list } } } ;

OneLine align_item = { OneLine#Left } ;

include <CCore.bookinc.ddl>

}

Book Data = { .title = "CCore 3-xx" , .start = Pages#start , .back = PapayaWhip , .fore = Black } ;





