/* Pad.ddl */

//include <LangTypes.ddl>

Lang lang=
 {
   {
    { 0 , "(" , lang.elements+0 },
    { 1 , ")" , lang.elements+1 },
    { 2 , "," , lang.elements+2 },
    { 3 , "=" , lang.elements+3 },
    { 4 , "Angle" , lang.elements+4 },
    { 5 , "Length" , lang.elements+5 },
    { 6 , "Name" , lang.elements+6 },
    { 7 , "Number" , lang.elements+7 },
    { 8 , "angle" , lang.elements+8 },
    { 9 , "len" , lang.elements+9 },
    { 10 , "point" , lang.elements+10 },
    { 11 , "ratio" , lang.elements+11 }
   },
   {
    { 0 , "DECL" , { { 0 , 0 , "" , lang.synts+0 , lang.elements+12 ,
                                                                      {
                                                                       lang.top_rules+0,
                                                                       lang.top_rules+1,
                                                                       lang.top_rules+2,
                                                                       lang.top_rules+3,
                                                                       lang.top_rules+4,
                                                                       lang.top_rules+5,
                                                                       lang.top_rules+6,
                                                                       lang.top_rules+7,
                                                                       lang.top_rules+8,
                                                                       lang.top_rules+9
                                                                      }
                     }
                   } ,
                   {
                    lang.rules+0,
                    lang.rules+1,
                    lang.rules+2,
                    lang.rules+3,
                    lang.rules+4,
                    lang.rules+5,
                    lang.rules+6,
                    lang.rules+7,
                    lang.rules+8,
                    lang.rules+9
                   }
    }
   },
   {
    lang.synts+0
   },
   {
    { 0 , lang.atoms+0 },
    { 1 , lang.atoms+1 },
    { 2 , lang.atoms+2 },
    { 3 , lang.atoms+3 },
    { 4 , lang.atoms+4 },
    { 5 , lang.atoms+5 },
    { 6 , lang.atoms+6 },
    { 7 , lang.atoms+7 },
    { 8 , lang.atoms+8 },
    { 9 , lang.atoms+9 },
    { 10 , lang.atoms+10 },
    { 11 , lang.atoms+11 },
    { 12 , lang.synts[0].kinds+0 }
   },
   {
    { 0 , "point@v1" , lang.synts[0].kinds+0 ,
                                               {
                                                lang.atoms+10,
                                                lang.atoms+6,
                                                lang.atoms+0,
                                                lang.atoms+7,
                                                lang.atoms+2,
                                                lang.atoms+7,
                                                lang.atoms+1
                                               }
    },
    { 1 , "point@v2" , lang.synts[0].kinds+0 ,
                                               {
                                                lang.atoms+6,
                                                lang.atoms+0,
                                                lang.atoms+7,
                                                lang.atoms+2,
                                                lang.atoms+7,
                                                lang.atoms+1
                                               }
    },
    { 2 , "length@v1" , lang.synts[0].kinds+0 ,
                                                {
                                                 lang.atoms+9,
                                                 lang.atoms+6,
                                                 lang.atoms+3,
                                                 lang.atoms+7
                                                }
    },
    { 3 , "length@v2" , lang.synts[0].kinds+0 ,
                                                {
                                                 lang.atoms+9,
                                                 lang.atoms+6,
                                                 lang.atoms+3,
                                                 lang.atoms+5
                                                }
    },
    { 4 , "length@v3" , lang.synts[0].kinds+0 ,
                                                {
                                                 lang.atoms+6,
                                                 lang.atoms+3,
                                                 lang.atoms+5
                                                }
    },
    { 5 , "angle@v1" , lang.synts[0].kinds+0 ,
                                               {
                                                lang.atoms+8,
                                                lang.atoms+6,
                                                lang.atoms+3,
                                                lang.atoms+7
                                               }
    },
    { 6 , "angle@v2" , lang.synts[0].kinds+0 ,
                                               {
                                                lang.atoms+8,
                                                lang.atoms+6,
                                                lang.atoms+3,
                                                lang.atoms+4
                                               }
    },
    { 7 , "angle@v3" , lang.synts[0].kinds+0 ,
                                               {
                                                lang.atoms+6,
                                                lang.atoms+3,
                                                lang.atoms+4
                                               }
    },
    { 8 , "ratio@v1" , lang.synts[0].kinds+0 ,
                                               {
                                                lang.atoms+11,
                                                lang.atoms+6,
                                                lang.atoms+3,
                                                lang.atoms+7
                                               }
    },
    { 9 , "ratio@v2" , lang.synts[0].kinds+0 ,
                                               {
                                                lang.atoms+6,
                                                lang.atoms+3,
                                                lang.atoms+7
                                               }
    }
   },
   {
    { 0 , "point@v1" , lang.rules+0 , lang.synts[0].kinds+0 ,
                                                              {
                                                               lang.atoms+10,
                                                               lang.atoms+6,
                                                               lang.atoms+0,
                                                               lang.atoms+7,
                                                               lang.atoms+2,
                                                               lang.atoms+7,
                                                               lang.atoms+1
                                                              }
    },
    { 1 , "point@v2" , lang.rules+1 , lang.synts[0].kinds+0 ,
                                                              {
                                                               lang.atoms+6,
                                                               lang.atoms+0,
                                                               lang.atoms+7,
                                                               lang.atoms+2,
                                                               lang.atoms+7,
                                                               lang.atoms+1
                                                              }
    },
    { 2 , "length@v1" , lang.rules+2 , lang.synts[0].kinds+0 ,
                                                               {
                                                                lang.atoms+9,
                                                                lang.atoms+6,
                                                                lang.atoms+3,
                                                                lang.atoms+7
                                                               }
    },
    { 3 , "length@v2" , lang.rules+3 , lang.synts[0].kinds+0 ,
                                                               {
                                                                lang.atoms+9,
                                                                lang.atoms+6,
                                                                lang.atoms+3,
                                                                lang.atoms+5
                                                               }
    },
    { 4 , "length@v3" , lang.rules+4 , lang.synts[0].kinds+0 ,
                                                               {
                                                                lang.atoms+6,
                                                                lang.atoms+3,
                                                                lang.atoms+5
                                                               }
    },
    { 5 , "angle@v1" , lang.rules+5 , lang.synts[0].kinds+0 ,
                                                              {
                                                               lang.atoms+8,
                                                               lang.atoms+6,
                                                               lang.atoms+3,
                                                               lang.atoms+7
                                                              }
    },
    { 6 , "angle@v2" , lang.rules+6 , lang.synts[0].kinds+0 ,
                                                              {
                                                               lang.atoms+8,
                                                               lang.atoms+6,
                                                               lang.atoms+3,
                                                               lang.atoms+4
                                                              }
    },
    { 7 , "angle@v3" , lang.rules+7 , lang.synts[0].kinds+0 ,
                                                              {
                                                               lang.atoms+6,
                                                               lang.atoms+3,
                                                               lang.atoms+4
                                                              }
    },
    { 8 , "ratio@v1" , lang.rules+8 , lang.synts[0].kinds+0 ,
                                                              {
                                                               lang.atoms+11,
                                                               lang.atoms+6,
                                                               lang.atoms+3,
                                                               lang.atoms+7
                                                              }
    },
    { 9 , "ratio@v2" , lang.rules+9 , lang.synts[0].kinds+0 ,
                                                              {
                                                               lang.atoms+6,
                                                               lang.atoms+3,
                                                               lang.atoms+7
                                                              }
    }
   },
   {
    { 0 , lang.finals+9 ,
                          {
                           { lang.elements+6 , lang.states+1 },
                           { lang.elements+8 , lang.states+13 },
                           { lang.elements+9 , lang.states+14 },
                           { lang.elements+10 , lang.states+12 },
                           { lang.elements+11 , lang.states+15 },
                           { lang.elements+12 , lang.states+32 }
                          }
    },
    { 1 , lang.finals+1 ,
                          {
                           { lang.elements+0 , lang.states+20 },
                           { lang.elements+3 , lang.states+9 }
                          }
    },
    { 2 , lang.finals+2 ,
                          {
                           { lang.elements+1 , lang.states+22 }
                          }
    },
    { 3 , lang.finals+2 ,
                          {
                           { lang.elements+1 , lang.states+23 }
                          }
    },
    { 4 , lang.finals+3 ,
                          {
                           { lang.elements+2 , lang.states+17 }
                          }
    },
    { 5 , lang.finals+3 ,
                          {
                           { lang.elements+2 , lang.states+18 }
                          }
    },
    { 6 , lang.finals+4 ,
                          {
                           { lang.elements+3 , lang.states+10 }
                          }
    },
    { 7 , lang.finals+4 ,
                          {
                           { lang.elements+3 , lang.states+11 }
                          }
    },
    { 8 , lang.finals+4 ,
                          {
                           { lang.elements+3 , lang.states+21 }
                          }
    },
    { 9 , lang.finals+5 ,
                          {
                           { lang.elements+4 , lang.states+29 },
                           { lang.elements+5 , lang.states+26 },
                           { lang.elements+7 , lang.states+31 }
                          }
    },
    { 10 , lang.finals+6 ,
                           {
                            { lang.elements+4 , lang.states+28 },
                            { lang.elements+7 , lang.states+27 }
                           }
    },
    { 11 , lang.finals+7 ,
                           {
                            { lang.elements+5 , lang.states+25 },
                            { lang.elements+7 , lang.states+24 }
                           }
    },
    { 12 , lang.finals+8 ,
                           {
                            { lang.elements+6 , lang.states+16 }
                           }
    },
    { 13 , lang.finals+8 ,
                           {
                            { lang.elements+6 , lang.states+6 }
                           }
    },
    { 14 , lang.finals+8 ,
                           {
                            { lang.elements+6 , lang.states+7 }
                           }
    },
    { 15 , lang.finals+8 ,
                           {
                            { lang.elements+6 , lang.states+8 }
                           }
    },
    { 16 , lang.finals+0 ,
                           {
                            { lang.elements+0 , lang.states+19 }
                           }
    },
    { 17 , lang.finals+10 ,
                            {
                             { lang.elements+7 , lang.states+2 }
                            }
    },
    { 18 , lang.finals+10 ,
                            {
                             { lang.elements+7 , lang.states+3 }
                            }
    },
    { 19 , lang.finals+10 ,
                            {
                             { lang.elements+7 , lang.states+4 }
                            }
    },
    { 20 , lang.finals+10 ,
                            {
                             { lang.elements+7 , lang.states+5 }
                            }
    },
    { 21 , lang.finals+10 ,
                            {
                             { lang.elements+7 , lang.states+30 }
                            }
    },
    { 22 , lang.finals+11 ,
                            {
                             
                            }
    },
    { 23 , lang.finals+12 ,
                            {
                             
                            }
    },
    { 24 , lang.finals+13 ,
                            {
                             
                            }
    },
    { 25 , lang.finals+14 ,
                            {
                             
                            }
    },
    { 26 , lang.finals+15 ,
                            {
                             
                            }
    },
    { 27 , lang.finals+16 ,
                            {
                             
                            }
    },
    { 28 , lang.finals+17 ,
                            {
                             
                            }
    },
    { 29 , lang.finals+18 ,
                            {
                             
                            }
    },
    { 30 , lang.finals+19 ,
                            {
                             
                            }
    },
    { 31 , lang.finals+20 ,
                            {
                             
                            }
    },
    { 32 , lang.finals+21 ,
                            {
                             
                            }
    }
   },
   {
    { 0 ,
          {
           { lang.atoms+0 , null }
          }
    },
    { 1 ,
          {
           { lang.atoms+0 , null },
           { lang.atoms+3 , null }
          }
    },
    { 2 ,
          {
           { lang.atoms+1 , null }
          }
    },
    { 3 ,
          {
           { lang.atoms+2 , null }
          }
    },
    { 4 ,
          {
           { lang.atoms+3 , null }
          }
    },
    { 5 ,
          {
           { lang.atoms+4 , null },
           { lang.atoms+5 , null },
           { lang.atoms+7 , null }
          }
    },
    { 6 ,
          {
           { lang.atoms+4 , null },
           { lang.atoms+7 , null }
          }
    },
    { 7 ,
          {
           { lang.atoms+5 , null },
           { lang.atoms+7 , null }
          }
    },
    { 8 ,
          {
           { lang.atoms+6 , null }
          }
    },
    { 9 ,
          {
           { lang.atoms+6 , null },
           { lang.atoms+8 , null },
           { lang.atoms+9 , null },
           { lang.atoms+10 , null },
           { lang.atoms+11 , null }
          }
    },
    { 10 ,
           {
            { lang.atoms+7 , null }
           }
    },
    { 11 ,
           {
            { null , lang.rules+0 }
           }
    },
    { 12 ,
           {
            { null , lang.rules+1 }
           }
    },
    { 13 ,
           {
            { null , lang.rules+2 }
           }
    },
    { 14 ,
           {
            { null , lang.rules+3 }
           }
    },
    { 15 ,
           {
            { null , lang.rules+4 }
           }
    },
    { 16 ,
           {
            { null , lang.rules+5 }
           }
    },
    { 17 ,
           {
            { null , lang.rules+6 }
           }
    },
    { 18 ,
           {
            { null , lang.rules+7 }
           }
    },
    { 19 ,
           {
            { null , lang.rules+8 }
           }
    },
    { 20 ,
           {
            { null , lang.rules+9 }
           }
    },
    { 21 ,
           {
            { null , null }
           }
    }
   }
 };

