include <Mandelbrot.style.ddl>

scope Pages {

Text text1 = { { {{'Mandelbrot scope'}} } , &fmt_h1 , &Center } ;

Text text2 = { { {{'Introduction'}} } , &fmt_h2 , &Center } ;

Text text3 = { {   {{'This'}},{{'is'}},{{'a'}},{{'text'}}   } } ;

Page page1 = { 'Manual' ,
  {
   { &text1 },
   { &text2 },
   { &text3 }
  }
 };

} // scope Pages

Book Data = { 'Mandelbrot scope' , {&Pages#page1} , Pages#Back , Pages#Fore } ;