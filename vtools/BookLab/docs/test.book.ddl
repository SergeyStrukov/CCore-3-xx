/* test.book.ddl */

include <pretext:/Book1.ddl>

Book Data = { "test page" , &Page1#page , 0A0A0A0h , 0FFh } ;

Font font = { 'Times New Roman' , 24 } ;

Font font_b = { 'Times New Roman' , 24 , True } ;

Font font_i = { 'Times New Roman' , 24 , False , True } ;

Font font_bi = { 'Times New Roman' , 24 , True , True } ;

Format fmt = { &font } ;

Format fmt_b = { &font_b } ;

Format fmt_i = { &font_i } ;

Format fmt_bi = { .font = &font_bi , .back = 0D0D0D0h } ;

Format fmt_u = { .font = &font , .effect = Format#Underline } ;

Format fmt_s = { .font = &font , .effect = Format#Strikeout } ;

/* Page1 */

scope Page1 {

Point DefaultInner = { 20 , 10 } ;

Point DefaultOuter = { 30 , 20 } ;

OneLine pl_left = { OneLine#Left } ;

OneLine pl_right = { OneLine#Right } ;

OneLine pl_center = { OneLine#Center } ;

MultiLine pl_1_0 = { {1,1} , {2,1} } ;

MultiLine pl_1_5 = { {3,2} , {2,1} } ;

// ---

Page page = { "page1" , { 
                         { .body = &t1 , .line = &line1 , .col = 0FF0000h },
                         { .body = &t2 , .line = &line1 , .col = 00000FFh },
                         { .body = &t3 , .line = &line1 , .col = 0008000h },
                         { .body = &t4 , .line = &line1 , .col = 0008080h },
                         { .body = &t5 , .line = &line1 }
                         
                          
                        } , 0C0C0C0h , 0h , null , null , &Page2#page } ;

SingleLine line1 = { {2,1} , 0FF00h } ;

Text t1 = { {
             { 'aligned left' }

            } , &fmt , &pl_left } ;

Text t2 = { {
             { 'aligned right' }

            } , &fmt , &pl_right } ;
            
Text t3 = { {
             { 'aligned center' }

            } , &fmt , &pl_center } ;
            
Text t4 = { {
              {"The"}
             ,{"spinor",&fmt_i}
             ,{"Len",&fmt_b}
             ,{"determines"}
             ,{"the"}
             ,{"number"}
             ,{"of"}
             ,{"colors",&fmt_u}
             ,{"between"}
             ,{"pivot",&fmt_bi}
             ,{"colors."}
             ,{"The"}
             ,{"full"}
             ,{"color",&fmt_s}
             ,{"palette"}
             ,{"is"}
             ,{"built"}
             ,{"upon"}
             ,{"the"}
             ,{"pivot"}
             ,{"color"}
             ,{"list."}
             ,{"Between"}
             ,{"two"}
             ,{"consecutive"}
             ,{"pivot"}
             ,{"colors"}
             ,{"a"}
             ,{"number"}
             ,{"of"}
             ,{"intermediate"}
             ,{"colors"}
             ,{"are"}
             ,{"inserted,"}
             ,{"using"}
             ,{"progressive"}
             ,{"blending"}
             ,{"of"}
             ,{"edge"}
             ,{"colors."}
             ,{"The"}
             ,{"pivot"}
             ,{"list"}
             ,{"is"}
             ,{"cycled,"}
             ,{"when"}
             ,{"needed,"}
             ,{"except"}
             ,{"the"}
             ,{"first"}
             ,{"pivot"}
             ,{"color,"}
             ,{"which"}
             ,{"is"}
             ,{"usually"}
             ,{"Blue",&fmt_b}
             ,{"."}
             
            } , &fmt , &pl_1_0 } ;            

Text t5 = { {

             {"Mandelbrot",&fmt_b}
             ,{"scope",&fmt_b}
             ,{"(MScope.exe)"}
             ,{"is"}
             ,{"a"}
             ,{"software"}
             ,{"to"}
             ,{"display"}
             ,{"the"}
             ,{"Mandelbrot"}
             ,{"Set."}
             ,{"The"}
             ,{"Mandelbrot"}
             ,{"Set"}
             ,{"is"}
             ,{"a"}
             ,{"famous"}
             ,{"mathematical"}
             ,{"fractal"}
             ,{"set,"}
             ,{"it"}
             ,{"has"}
             ,{"been"}
             ,{"discovered"}
             ,{"by"}
             ,{"Benoit B. Mandelbrot",&fmt_u}
             ,{"."}
             ,{"The"}
             ,{"Mandelbrot"}
             ,{"Set"}
             ,{"itself"}
             ,{"cannot"}
             ,{"be"}
             ,{"calculated,"}
             ,{"because"}
             ,{"it"}
             ,{"requires"}
             ,{"infinite"}
             ,{"number"}
             ,{"of"}
             ,{"precise"}
             ,{"iteration"}
             ,{"per"}
             ,{"point."}
             ,{"But"}
             ,{"we"}
             ,{"can"}
             ,{"calculate"}
             ,{"and"}
             ,{"paint"}
             ,{"the"}
             ,{"outer"}
             ,{"of"}
             ,{"it"}
             ,{"up"}
             ,{"to"}
             ,{"some"}
             ,{"level."}
             ,{"The"}
             ,{"rest"}
             ,{"of"}
             ,{"the"}
             ,{"painted"}
             ,{"area"}
             ,{"is"}
             ,{"black"}
             ,{"and"}
             ,{"contains"}
             ,{"inside"}
             ,{"the"}
             ,{"true"}
             ,{"Mandelbrot"}
             ,{"Set,"}
             ,{"but"}
             ,{"we"}
             ,{"don't"}
             ,{"know"}
             ,{"which"}
             ,{"part."}
             ,{"The"}
             ,{"more"}
             ,{"deeper"}
             ,{"we"}
             ,{"calculate,"}
             ,{"the"}
             ,{"more"}
             ,{"closer"}
             ,{"we"}
             ,{"are"}
             ,{"coming"}
             ,{"to"}
             ,{"the"}
             ,{"true"}
             ,{"border."}
             ,{"You"}
             ,{"can"}
             ,{"select"}
             ,{"the"}
             ,{"depth"}
             ,{"in"}
             ,{"the"}
             ,{"Options",&fmt_i}
             ,{"menu."}
             ,{"You"}
             ,{"can"}
             ,{"also"}
             ,{"adjust"}
             ,{"the"}
             ,{"color"}
             ,{"palette"}
             ,{"to"}
             ,{"paint"}
             ,{"the"}
             ,{"outer"}
             ,{"part."}

            } , &fmt , &pl_1_5 } ;
                        
} // scope Page1

/* Page2 */

scope Page2 {

Point DefaultInner = { 20 , 10 } ;

Point DefaultOuter = { 30 , 20 } ;

OneLine pl_left = { OneLine#Left } ;

OneLine pl_right = { OneLine#Right } ;

OneLine pl_center = { OneLine#Center } ;

// ---

Page page = { "page2" , { 
                         { .body = &t1 , .line = &line1 , .col = 0FF0000h },
                         { .body = &t2 , .line = &line1 , .col = 00000FFh },
                         { .body = &t3 , .line = &line1 , .col = 0008000h }
                         
                          
                        } , NoColor , NoColor , null , &Page1#page , null } ;

DoubleLine line1 = { {1,1} } ;

Text t1 = { {
             { 'aligned left' }

            } , &fmt , &pl_left } ;

Text t2 = { {
             { 'aligned right' }

            } , &fmt , &pl_right } ;
            
Text t3 = { {
             { 'aligned center' }

            } , &fmt , &pl_center } ;

} // scope Page2
