include <pretext:/Book1.ddl>

Book Data = { .title = "Mandelbrot scope" , .start = & #Doc#Pages#page1 , .back = 12632256 , .fore = 0 } ;

scope Doc {

scope Pages {

Font font = { "Times New Roman" , 22 , false , false , 0 };

Font font_h1 = { "Times New Roman" , 56 , true , false , 0 };

Font font_h2 = { "Times New Roman" , 32 , true , false , 0 };

Font font_bold = { "Times New Roman" , 22 , true , false , 0 };

Font font_italic = { "Times New Roman" , 22 , false , true , 0 };

Font font_bullet = { "Times New Roman" , 22 , true , false , 0 };

Format fmt_h1 = { & font_h1 , 4294967295 , 255 , 0 };

Format fmt_h2 = { & font_h2 , 4294967295 , 25600 , 0 };

Format fmt_t1 = { & Anonym#o1 , 4294967295 , 4294967295 , 0 };

Format fmt_bold = { & font_bold , 4294967295 , 4294967295 , 0 };

Format fmt_italic = { & font_italic , 4294967295 , 4294967295 , 0 };

Format fmt_under = { & font , 4294967295 , 4294967295 , 1 };

}


}

