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

Font font_code = { 'Anonymous Pro' , 22 , False , False , 30 } ;

Format fmt_code = { .font = &font_code } ;

Format fmt_code_keyword = { .font = &font_code , .fore = 0FFh } ;

Font font_bullet = { 'Georgia' , 20 } ;

Format fmt_bullet = { .font = &font_bullet , .back = 0D0D0D0h } ;

Font font_collapse = { 'Georgia' , 24 } ;

/* Page1 */

scope Page1 {

Point DefaultInner = { 20 , 10 } ;

Point DefaultOuter = { 30 , 20 } ;

OneLine pl_left = { OneLine#Left } ;

OneLine pl_right = { OneLine#Right } ;

OneLine pl_center = { OneLine#Center } ;

MultiLine pl_1_0 = { {1,1} , {2,1} } ;

MultiLine pl_1_5 = { {3,2} , {2,1} } ;

MultiLine pl_item = { {1,1} , {0,1} } ;

Format DefaultCollapseFormat = { .font = &font_collapse , .back = 0D0D0D0h } ;

// ---

Page page = { "page1" , { 
                         { .body = &t1 , .line = &line1 , .col = 0FF0000h },
                         { .body = &t2 , .line = &line1 , .col = 00000FFh },
                         { .body = &t3 , .line = &line1 , .col = 0008000h },
                         { .body = &t4 , .line = &line1 , .col = 0008080h },
                         { .body = &t5 , .line = &line1 },
                         { .body = &t6 , .line = &line2 },
                         { .body = &t7 , .line = &line2 },
                         { .body = &table1 , .line = &line2 },
                         { .body = &t8 , .line = &line2 }
                          
                        } , 0C0C0C0h , 0h , null , null , &Page2#page } ;

SingleLine line1 = { {2,1} , 0FF00h } ;

SingleLine line2 = { {1,1} , 0FF0000h } ;

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
            
FixedText t6 = { {
                  {{'struct',&fmt_code_keyword},{' NoCopyType'}},
                  {{' {'}},
                  {{'  NoCopyType() = '},{'default',&fmt_code_keyword},{' ;'}},
                  {{''}},
                  {{'  NoCopyType('},{'const',&fmt_code_keyword},{' NoCopyType &) = '},{'delete',&fmt_code_keyword},{' ;'}},
                  {{''}},
                  {{'  '},{'void',&fmt_code_keyword},{' '},{'operator',&fmt_code_keyword},{' = ('},{'const',&fmt_code_keyword},{' NoCopyType &) = '},{'delete',&fmt_code_keyword},{' ;'}},
                  {{' };'}}

                 } , &fmt_code } ;
                 
TextList t7 = { {
                 { '1)' , {{ .body = &i1 , .inner = {5,5} , .outer = {0,0} }} },
                 { '2)' , {{ .body = &i2 , .inner = {5,5} , .outer = {0,0} }} },
                 { '3)' , {{ .body = &i3 , .inner = {5,5} , .outer = {0,0} }} },
                 
                 { '4)->' , {{ .body = &i4 , .inner = {0,0} , .outer = {0,0} }} },
                 { '5)->' , {{ .body = &i5 , .inner = {0,0} , .outer = {0,0} }} },
                 { '6)->' , {{ .body = &i6 , .inner = {0,0} , .outer = {0,0} }} }


                } , &fmt_bullet , 5 , 5 } ;

                
Text i1 = { {
             {"aligned left",null,&link1}

            } , &fmt , &pl_item } ;     
            
Link link1 = { &page } ;
                        
Text i2 = { {
             {"aligned right",null,&link2}

            } , &fmt , &pl_item } ;     
            
Link link2 = { &page , { 1 } } ;

Text i3 = { {
             {"aligned center",null,&link3}

            } , &fmt , &pl_item } ;     
            
Link link3 = { &page , { 2 } } ;


Text i4 = { {
             {"aligned left",null,&link4}

            } , &fmt , &pl_item } ;     
            
Link link4 = { &Page2#page , { 0 } } ;
                        
Text i5 = { {
             {"aligned right",null,&link5}

            } , &fmt , &pl_item } ;     
            
Link link5 = { &Page2#page , { 1 } } ;

Text i6 = { {
             {"aligned center",null,&link6}

            } , &fmt , &pl_item } ;     
            
Link link6 = { &Page2#page , { 2 } } ;

Collapse t8 = { .title = 'hidden text' , .list = {

                                                  { .body = &t1 , .line = &line2 , .col = 0FF0000h },
                                                  { .body = &t2 , .line = &line2 , .col = 00000FFh },
                                                  { .body = &t3 , .line = &line2 , .col = 0008000h },
                                                  { .body = &t9 , .line = &line2 },
                                                  { .body = &t10 , .line = &line2 }
  
                                                 } , .open = True , .hide = False } ;

Collapse t9 = { .title = 'hidden text' , .list = {

                                                  { .body = &t1 , .line = &line2 , .col = 0FF0000h }
  
                                                 } , .open = True } ;
                                                 
Collapse t10 = { .title = 'hidden text' , .list = {

                                                   { .body = &t1 , .line = &line2 , .col = 0FF0000h }
  
                                                  } , .open = False } ;

Border tb1 = { .space = 5 , .line = 0008000h } ;

Table table1 = { { 25 , 25 , 50 } , {
                                     {&Cell#c1_1,&Cell#c1_2,&Cell#c1_3},
                                     {&Cell#c2_1,&Cell#c2_2,&Cell#c2_3},
                                     {&Cell#c3_1,&Cell#c3_2,&Cell#c3_3},
                                     {&Cell#c4_1,&Cell#c4_2,&Cell#c4_3}
                                    } , &tb1 , True } ;
                                
scope Cell {                                
              
Point DefaultInner = { 5 , 5 } ;

Point DefaultOuter = { 0 , 0 } ;
                                
Cell c1_1 = { {{&t1_1}} } ;
Cell c1_2 = { {{&t1_2}} } ;
Cell c1_3 = { {{&t1_3}} } ;

Cell c2_1 = { {{&t2_1}} } ;
Cell c2_2 = { {{&t2_2}} , 2 , 2 } ;
Cell c2_3 = { {{&t2_3}} } ;

Cell c3_1 = { {{&t3_1}} } ;
Cell c3_2 = { {{&t3_2}} } ;
Cell c3_3 = { {{&t3_3}} } ;

Cell c4_1 = { {{&t4_1}} } ;
Cell c4_2 = { {{&t4_2}} } ;
Cell c4_3 = { {{&t4_3}} } ;

Font font = { 'Times New Roman' , 16 } ;

Format DefaultFormat = { &font } ;

Format fmt1 = { .font = &font , .back = 0D0D0D0h } ;

MultiLine DefaultPlacement = { {1,1} , {0,1} } ;

Text t1_1 = { { {'Source'},{'type'} } , &fmt1 } ;

Text t1_2 = { { {'Target'},{'type'} } , &fmt1 } ;

Text t1_3 = { { {'List'},{'of'},{'operations'} } , &fmt1 } ;

Text t2_1 = { { {'int'} } } ;

Text t2_2 = { { {'long'},{'XXXXX'},{'XXXXX'},{'XXXXX'},{'XXXXX'},{'XXXXX'},{'XXXXX'},{'LLLLL',&fmt_u,&Page2#page} } } ;

Text t2_3 = { { {'cast'},{'+'},{'-'} } } ;

Text t3_1 = { { {'short'} } } ;

Text t3_2 = { { {'int'} } } ;

Text t3_3 = { { {'cast'} } } ;

Text t4_1 = { { {'int'} } } ;

Text t4_2 = { { {'int'} } } ;

Text t4_3 = { { {'+'},{'-'} } } ;

} // scope Cell                               
                                                 
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
                         { .body = &t3 , .line = &line1 , .col = 0008000h },
                         { .body = &t4 , .line = &line2 }
                          
                        } , NoColor , NoColor , null , &Page1#page , null } ;

DoubleLine line1 = { {1,1} } ;

SingleLine line2 = { {1,1} , 0FF0000h } ;

Text t1 = { {
             { 'aligned left' }

            } , &fmt , &pl_left } ;

Text t2 = { {
             { 'aligned right' }

            } , &fmt , &pl_right } ;
            
Text t3 = { {
             { 'aligned center' }

            } , &fmt , &pl_center } ;

Collapse t4 = { .title = 'hidden page' , .list = {
                                                   { .body = &Page1#t1 , .line = &line1 , .col = 0FF0000h },
                                                   { .body = &Page1#t2 , .line = &line1 , .col = 00000FFh },
                                                   { .body = &Page1#t3 , .line = &line1 , .col = 0008000h },
                                                   { .body = &Page1#t4 , .line = &line1 , .col = 0008080h },
                                                   { .body = &Page1#t5 , .line = &line1 },
                                                   { .body = &Page1#t6 , .line = &line2 },
                                                   { .body = &Page1#t7 , .line = &line2 },
                                                   { .body = &Page1#t8 , .line = &line2 },
                                                   { .body = &Page1#table1 , .line = &line2 }
  
                                                 } , .open = False } ;
                                                  
} // scope Page2


