include <pretext:/Book1.ddl>

Book Data = { .title = "Mandelbrot scope" , .start = & #Doc#Pages#page1 , .back = 0C0C0C0h , .fore = 00h } ;

scope Doc {

Point DefaultInner = { 5 , 5 } ;

scope Pages {

Point DefaultInner = { 10 , 10 } ;

Format DefaultBulletFormat = { & font_bullet , NoColor , NoColor , 0 } ;

Format DefaultFormat = { & font , NoColor , NoColor , 0 } ;

MultiLine DefaultPlacement = { { 1 , 1 } , { 2 , 1 } } ;

Font font = { "Times New Roman" , 22 , False , False , 0 } ;

Font font_h1 = { "Times New Roman" , 56 , True , False , 0 } ;

Font font_h2 = { "Times New Roman" , 32 , True , False , 0 } ;

Font font_bold = { "Times New Roman" , 22 , True , False , 0 } ;

Font font_italic = { "Times New Roman" , 22 , False , True , 0 } ;

Font font_bullet = { "Times New Roman" , 22 , True , False , 0 } ;

Format fmt_h1 = { & font_h1 , NoColor , 0FFh , 0 } ;

Format fmt_h2 = { & font_h2 , NoColor , 06400h , 0 } ;

Format fmt_t1 = { & Anonym#o1 , NoColor , NoColor , 0 } ;

OneLine align_h1 = { 2 } ;

OneLine align_h2 = { 2 } ;

Format fmt_bold = { & font_bold , NoColor , NoColor , 0 } ;

Format fmt_italic = { & font_italic , NoColor , NoColor , 0 } ;

Format fmt_under = { & font , NoColor , NoColor , 1 } ;

}


}

