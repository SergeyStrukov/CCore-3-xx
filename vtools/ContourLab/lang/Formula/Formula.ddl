/* Formula.ddl */

//include <LangTypes.ddl>

Lang lang=
 {
   {
    { 0 , "(" , lang.elements+0 },
    { 1 , ")" , lang.elements+1 },
    { 2 , "*" , lang.elements+2 },
    { 3 , "+" , lang.elements+3 },
    { 4 , "," , lang.elements+4 },
    { 5 , "-" , lang.elements+5 },
    { 6 , "/" , lang.elements+6 },
    { 7 , "=" , lang.elements+7 },
    { 8 , "Angle" , lang.elements+8 },
    { 9 , "Length" , lang.elements+9 },
    { 10 , "Name" , lang.elements+10 },
    { 11 , "Number" , lang.elements+11 }
   },
   {
    { 0 , "FORMULA" , { { 0 , 0 , "" , lang.synts+0 , lang.elements+12 ,
                                                                         {
                                                                          lang.top_rules+0,
                                                                          lang.top_rules+1,
                                                                          lang.top_rules+2,
                                                                          lang.top_rules+3
                                                                         }
                        }
                      } ,
                      {
                       lang.rules+0
                      }
    },
    { 1 , "EXPR" ,
                   {
                    { 1 , 0 , "A" , lang.synts+1 , lang.elements+13 ,
                                                                      {
                                                                       lang.top_rules+4,
                                                                       lang.top_rules+5,
                                                                       lang.top_rules+6,
                                                                       lang.top_rules+7,
                                                                       lang.top_rules+8,
                                                                       lang.top_rules+9,
                                                                       lang.top_rules+10,
                                                                       lang.top_rules+11,
                                                                       lang.top_rules+12,
                                                                       lang.top_rules+13,
                                                                       lang.top_rules+14,
                                                                       lang.top_rules+15,
                                                                       lang.top_rules+16,
                                                                       lang.top_rules+17,
                                                                       lang.top_rules+18,
                                                                       lang.top_rules+19,
                                                                       lang.top_rules+20,
                                                                       lang.top_rules+21,
                                                                       lang.top_rules+22,
                                                                       lang.top_rules+23,
                                                                       lang.top_rules+24,
                                                                       lang.top_rules+25,
                                                                       lang.top_rules+26,
                                                                       lang.top_rules+27
                                                                      }
                    },
                    { 2 , 1 , "M" , lang.synts+1 , lang.elements+14 ,
                                                                      {
                                                                       lang.top_rules+28,
                                                                       lang.top_rules+29,
                                                                       lang.top_rules+30,
                                                                       lang.top_rules+31,
                                                                       lang.top_rules+32,
                                                                       lang.top_rules+33,
                                                                       lang.top_rules+34,
                                                                       lang.top_rules+35,
                                                                       lang.top_rules+36,
                                                                       lang.top_rules+37,
                                                                       lang.top_rules+38,
                                                                       lang.top_rules+39
                                                                      }
                    },
                    { 3 , 2 , "U" , lang.synts+1 , lang.elements+15 ,
                                                                      {
                                                                       lang.top_rules+40
                                                                      }
                    },
                    { 4 , 3 , "P" , lang.synts+1 , lang.elements+16 ,
                                                                      {
                                                                       lang.top_rules+41,
                                                                       lang.top_rules+42,
                                                                       lang.top_rules+43,
                                                                       lang.top_rules+44,
                                                                       lang.top_rules+45,
                                                                       lang.top_rules+46,
                                                                       lang.top_rules+47,
                                                                       lang.top_rules+48,
                                                                       lang.top_rules+49,
                                                                       lang.top_rules+50,
                                                                       lang.top_rules+51
                                                                      }
                    }
                   } ,
                   {
                    lang.rules+1,
                    lang.rules+2,
                    lang.rules+3,
                    lang.rules+4,
                    lang.rules+5,
                    lang.rules+6,
                    lang.rules+7,
                    lang.rules+8,
                    lang.rules+9,
                    lang.rules+10,
                    lang.rules+11,
                    lang.rules+12
                   }
    },
    { 2 , "EXPR_LIST" ,
                        {
                         { 5 , 0 , "E" , lang.synts+2 , lang.elements+17 ,
                                                                           {
                                                                            lang.top_rules+52
                                                                           }
                         },
                         { 6 , 1 , "N" , lang.synts+2 , lang.elements+18 ,
                                                                           {
                                                                            lang.top_rules+53,
                                                                            lang.top_rules+54,
                                                                            lang.top_rules+55,
                                                                            lang.top_rules+56,
                                                                            lang.top_rules+57,
                                                                            lang.top_rules+58,
                                                                            lang.top_rules+59,
                                                                            lang.top_rules+60
                                                                           }
                         }
                        } ,
                        {
                         lang.rules+13,
                         lang.rules+14,
                         lang.rules+15
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
    { 12 , lang.synts[0].kinds+0 },
    { 13 , lang.synts[1].kinds+0 },
    { 14 , lang.synts[1].kinds+1 },
    { 15 , lang.synts[1].kinds+2 },
    { 16 , lang.synts[1].kinds+3 },
    { 17 , lang.synts[2].kinds+0 },
    { 18 , lang.synts[2].kinds+1 }
   },
   {
    { 0 , "set" , lang.synts[0].kinds+0 ,
                                          {
                                           lang.atoms+10,
                                           lang.atoms+7,
                                           lang.synts+1
                                          }
    },
    { 1 , "add" , lang.synts[1].kinds+0 ,
                                          {
                                           lang.synts+1,
                                           lang.atoms+3,
                                           lang.synts+1
                                          }
    },
    { 2 , "sub" , lang.synts[1].kinds+0 ,
                                          {
                                           lang.synts+1,
                                           lang.atoms+5,
                                           lang.synts+1
                                          }
    },
    { 3 , "mul" , lang.synts[1].kinds+1 ,
                                          {
                                           lang.synts+1,
                                           lang.atoms+2,
                                           lang.synts+1
                                          }
    },
    { 4 , "div" , lang.synts[1].kinds+1 ,
                                          {
                                           lang.synts+1,
                                           lang.atoms+6,
                                           lang.synts+1
                                          }
    },
    { 5 , "neg" , lang.synts[1].kinds+2 ,
                                          {
                                           lang.atoms+5,
                                           lang.synts+1
                                          }
    },
    { 6 , "brace" , lang.synts[1].kinds+3 ,
                                            {
                                             lang.atoms+0,
                                             lang.synts+1,
                                             lang.atoms+1
                                            }
    },
    { 7 , "func" , lang.synts[1].kinds+3 ,
                                           {
                                            lang.atoms+10,
                                            lang.atoms+0,
                                            lang.synts+2,
                                            lang.atoms+1
                                           }
    },
    { 8 , "arg" , lang.synts[1].kinds+3 ,
                                          {
                                           lang.atoms+10
                                          }
    },
    { 9 , "number" , lang.synts[1].kinds+3 ,
                                             {
                                              lang.atoms+11
                                             }
    },
    { 10 , "angle" , lang.synts[1].kinds+3 ,
                                             {
                                              lang.atoms+8
                                             }
    },
    { 11 , "length" , lang.synts[1].kinds+3 ,
                                              {
                                               lang.atoms+9
                                              }
    },
    { 12 , "point" , lang.synts[1].kinds+3 ,
                                             {
                                              lang.atoms+0,
                                              lang.atoms+11,
                                              lang.atoms+4,
                                              lang.atoms+11,
                                              lang.atoms+1
                                             }
    },
    { 13 , "empty" , lang.synts[2].kinds+0 ,
                                             {
                                              
                                             }
    },
    { 14 , "one" , lang.synts[2].kinds+1 ,
                                           {
                                            lang.synts+1
                                           }
    },
    { 15 , "ext" , lang.synts[2].kinds+1 ,
                                           {
                                            lang.synts+2,
                                            lang.atoms+4,
                                            lang.synts+1
                                           }
    }
   },
   {
    { 0 , "set.A" , lang.rules+0 , lang.synts[0].kinds+0 ,
                                                           {
                                                            lang.atoms+10,
                                                            lang.atoms+7,
                                                            lang.synts[1].kinds+0
                                                           }
    },
    { 1 , "set.M" , lang.rules+0 , lang.synts[0].kinds+0 ,
                                                           {
                                                            lang.atoms+10,
                                                            lang.atoms+7,
                                                            lang.synts[1].kinds+1
                                                           }
    },
    { 2 , "set.U" , lang.rules+0 , lang.synts[0].kinds+0 ,
                                                           {
                                                            lang.atoms+10,
                                                            lang.atoms+7,
                                                            lang.synts[1].kinds+2
                                                           }
    },
    { 3 , "set.P" , lang.rules+0 , lang.synts[0].kinds+0 ,
                                                           {
                                                            lang.atoms+10,
                                                            lang.atoms+7,
                                                            lang.synts[1].kinds+3
                                                           }
    },
    { 4 , "add.A.M" , lang.rules+1 , lang.synts[1].kinds+0 ,
                                                             {
                                                              lang.synts[1].kinds+0,
                                                              lang.atoms+3,
                                                              lang.synts[1].kinds+1
                                                             }
    },
    { 5 , "add.M.M" , lang.rules+1 , lang.synts[1].kinds+0 ,
                                                             {
                                                              lang.synts[1].kinds+1,
                                                              lang.atoms+3,
                                                              lang.synts[1].kinds+1
                                                             }
    },
    { 6 , "add.U.M" , lang.rules+1 , lang.synts[1].kinds+0 ,
                                                             {
                                                              lang.synts[1].kinds+2,
                                                              lang.atoms+3,
                                                              lang.synts[1].kinds+1
                                                             }
    },
    { 7 , "add.P.M" , lang.rules+1 , lang.synts[1].kinds+0 ,
                                                             {
                                                              lang.synts[1].kinds+3,
                                                              lang.atoms+3,
                                                              lang.synts[1].kinds+1
                                                             }
    },
    { 8 , "add.A.U" , lang.rules+1 , lang.synts[1].kinds+0 ,
                                                             {
                                                              lang.synts[1].kinds+0,
                                                              lang.atoms+3,
                                                              lang.synts[1].kinds+2
                                                             }
    },
    { 9 , "add.M.U" , lang.rules+1 , lang.synts[1].kinds+0 ,
                                                             {
                                                              lang.synts[1].kinds+1,
                                                              lang.atoms+3,
                                                              lang.synts[1].kinds+2
                                                             }
    },
    { 10 , "add.U.U" , lang.rules+1 , lang.synts[1].kinds+0 ,
                                                              {
                                                               lang.synts[1].kinds+2,
                                                               lang.atoms+3,
                                                               lang.synts[1].kinds+2
                                                              }
    },
    { 11 , "add.P.U" , lang.rules+1 , lang.synts[1].kinds+0 ,
                                                              {
                                                               lang.synts[1].kinds+3,
                                                               lang.atoms+3,
                                                               lang.synts[1].kinds+2
                                                              }
    },
    { 12 , "add.A.P" , lang.rules+1 , lang.synts[1].kinds+0 ,
                                                              {
                                                               lang.synts[1].kinds+0,
                                                               lang.atoms+3,
                                                               lang.synts[1].kinds+3
                                                              }
    },
    { 13 , "add.M.P" , lang.rules+1 , lang.synts[1].kinds+0 ,
                                                              {
                                                               lang.synts[1].kinds+1,
                                                               lang.atoms+3,
                                                               lang.synts[1].kinds+3
                                                              }
    },
    { 14 , "add.U.P" , lang.rules+1 , lang.synts[1].kinds+0 ,
                                                              {
                                                               lang.synts[1].kinds+2,
                                                               lang.atoms+3,
                                                               lang.synts[1].kinds+3
                                                              }
    },
    { 15 , "add.P.P" , lang.rules+1 , lang.synts[1].kinds+0 ,
                                                              {
                                                               lang.synts[1].kinds+3,
                                                               lang.atoms+3,
                                                               lang.synts[1].kinds+3
                                                              }
    },
    { 16 , "sub.A.M" , lang.rules+2 , lang.synts[1].kinds+0 ,
                                                              {
                                                               lang.synts[1].kinds+0,
                                                               lang.atoms+5,
                                                               lang.synts[1].kinds+1
                                                              }
    },
    { 17 , "sub.M.M" , lang.rules+2 , lang.synts[1].kinds+0 ,
                                                              {
                                                               lang.synts[1].kinds+1,
                                                               lang.atoms+5,
                                                               lang.synts[1].kinds+1
                                                              }
    },
    { 18 , "sub.U.M" , lang.rules+2 , lang.synts[1].kinds+0 ,
                                                              {
                                                               lang.synts[1].kinds+2,
                                                               lang.atoms+5,
                                                               lang.synts[1].kinds+1
                                                              }
    },
    { 19 , "sub.P.M" , lang.rules+2 , lang.synts[1].kinds+0 ,
                                                              {
                                                               lang.synts[1].kinds+3,
                                                               lang.atoms+5,
                                                               lang.synts[1].kinds+1
                                                              }
    },
    { 20 , "sub.A.U" , lang.rules+2 , lang.synts[1].kinds+0 ,
                                                              {
                                                               lang.synts[1].kinds+0,
                                                               lang.atoms+5,
                                                               lang.synts[1].kinds+2
                                                              }
    },
    { 21 , "sub.M.U" , lang.rules+2 , lang.synts[1].kinds+0 ,
                                                              {
                                                               lang.synts[1].kinds+1,
                                                               lang.atoms+5,
                                                               lang.synts[1].kinds+2
                                                              }
    },
    { 22 , "sub.U.U" , lang.rules+2 , lang.synts[1].kinds+0 ,
                                                              {
                                                               lang.synts[1].kinds+2,
                                                               lang.atoms+5,
                                                               lang.synts[1].kinds+2
                                                              }
    },
    { 23 , "sub.P.U" , lang.rules+2 , lang.synts[1].kinds+0 ,
                                                              {
                                                               lang.synts[1].kinds+3,
                                                               lang.atoms+5,
                                                               lang.synts[1].kinds+2
                                                              }
    },
    { 24 , "sub.A.P" , lang.rules+2 , lang.synts[1].kinds+0 ,
                                                              {
                                                               lang.synts[1].kinds+0,
                                                               lang.atoms+5,
                                                               lang.synts[1].kinds+3
                                                              }
    },
    { 25 , "sub.M.P" , lang.rules+2 , lang.synts[1].kinds+0 ,
                                                              {
                                                               lang.synts[1].kinds+1,
                                                               lang.atoms+5,
                                                               lang.synts[1].kinds+3
                                                              }
    },
    { 26 , "sub.U.P" , lang.rules+2 , lang.synts[1].kinds+0 ,
                                                              {
                                                               lang.synts[1].kinds+2,
                                                               lang.atoms+5,
                                                               lang.synts[1].kinds+3
                                                              }
    },
    { 27 , "sub.P.P" , lang.rules+2 , lang.synts[1].kinds+0 ,
                                                              {
                                                               lang.synts[1].kinds+3,
                                                               lang.atoms+5,
                                                               lang.synts[1].kinds+3
                                                              }
    },
    { 28 , "mul.M.U" , lang.rules+3 , lang.synts[1].kinds+1 ,
                                                              {
                                                               lang.synts[1].kinds+1,
                                                               lang.atoms+2,
                                                               lang.synts[1].kinds+2
                                                              }
    },
    { 29 , "mul.U.U" , lang.rules+3 , lang.synts[1].kinds+1 ,
                                                              {
                                                               lang.synts[1].kinds+2,
                                                               lang.atoms+2,
                                                               lang.synts[1].kinds+2
                                                              }
    },
    { 30 , "mul.P.U" , lang.rules+3 , lang.synts[1].kinds+1 ,
                                                              {
                                                               lang.synts[1].kinds+3,
                                                               lang.atoms+2,
                                                               lang.synts[1].kinds+2
                                                              }
    },
    { 31 , "mul.M.P" , lang.rules+3 , lang.synts[1].kinds+1 ,
                                                              {
                                                               lang.synts[1].kinds+1,
                                                               lang.atoms+2,
                                                               lang.synts[1].kinds+3
                                                              }
    },
    { 32 , "mul.U.P" , lang.rules+3 , lang.synts[1].kinds+1 ,
                                                              {
                                                               lang.synts[1].kinds+2,
                                                               lang.atoms+2,
                                                               lang.synts[1].kinds+3
                                                              }
    },
    { 33 , "mul.P.P" , lang.rules+3 , lang.synts[1].kinds+1 ,
                                                              {
                                                               lang.synts[1].kinds+3,
                                                               lang.atoms+2,
                                                               lang.synts[1].kinds+3
                                                              }
    },
    { 34 , "div.M.U" , lang.rules+4 , lang.synts[1].kinds+1 ,
                                                              {
                                                               lang.synts[1].kinds+1,
                                                               lang.atoms+6,
                                                               lang.synts[1].kinds+2
                                                              }
    },
    { 35 , "div.U.U" , lang.rules+4 , lang.synts[1].kinds+1 ,
                                                              {
                                                               lang.synts[1].kinds+2,
                                                               lang.atoms+6,
                                                               lang.synts[1].kinds+2
                                                              }
    },
    { 36 , "div.P.U" , lang.rules+4 , lang.synts[1].kinds+1 ,
                                                              {
                                                               lang.synts[1].kinds+3,
                                                               lang.atoms+6,
                                                               lang.synts[1].kinds+2
                                                              }
    },
    { 37 , "div.M.P" , lang.rules+4 , lang.synts[1].kinds+1 ,
                                                              {
                                                               lang.synts[1].kinds+1,
                                                               lang.atoms+6,
                                                               lang.synts[1].kinds+3
                                                              }
    },
    { 38 , "div.U.P" , lang.rules+4 , lang.synts[1].kinds+1 ,
                                                              {
                                                               lang.synts[1].kinds+2,
                                                               lang.atoms+6,
                                                               lang.synts[1].kinds+3
                                                              }
    },
    { 39 , "div.P.P" , lang.rules+4 , lang.synts[1].kinds+1 ,
                                                              {
                                                               lang.synts[1].kinds+3,
                                                               lang.atoms+6,
                                                               lang.synts[1].kinds+3
                                                              }
    },
    { 40 , "neg.P" , lang.rules+5 , lang.synts[1].kinds+2 ,
                                                            {
                                                             lang.atoms+5,
                                                             lang.synts[1].kinds+3
                                                            }
    },
    { 41 , "brace.A" , lang.rules+6 , lang.synts[1].kinds+3 ,
                                                              {
                                                               lang.atoms+0,
                                                               lang.synts[1].kinds+0,
                                                               lang.atoms+1
                                                              }
    },
    { 42 , "brace.M" , lang.rules+6 , lang.synts[1].kinds+3 ,
                                                              {
                                                               lang.atoms+0,
                                                               lang.synts[1].kinds+1,
                                                               lang.atoms+1
                                                              }
    },
    { 43 , "brace.U" , lang.rules+6 , lang.synts[1].kinds+3 ,
                                                              {
                                                               lang.atoms+0,
                                                               lang.synts[1].kinds+2,
                                                               lang.atoms+1
                                                              }
    },
    { 44 , "brace.P" , lang.rules+6 , lang.synts[1].kinds+3 ,
                                                              {
                                                               lang.atoms+0,
                                                               lang.synts[1].kinds+3,
                                                               lang.atoms+1
                                                              }
    },
    { 45 , "func.E" , lang.rules+7 , lang.synts[1].kinds+3 ,
                                                             {
                                                              lang.atoms+10,
                                                              lang.atoms+0,
                                                              lang.synts[2].kinds+0,
                                                              lang.atoms+1
                                                             }
    },
    { 46 , "func.N" , lang.rules+7 , lang.synts[1].kinds+3 ,
                                                             {
                                                              lang.atoms+10,
                                                              lang.atoms+0,
                                                              lang.synts[2].kinds+1,
                                                              lang.atoms+1
                                                             }
    },
    { 47 , "arg" , lang.rules+8 , lang.synts[1].kinds+3 ,
                                                          {
                                                           lang.atoms+10
                                                          }
    },
    { 48 , "number" , lang.rules+9 , lang.synts[1].kinds+3 ,
                                                             {
                                                              lang.atoms+11
                                                             }
    },
    { 49 , "angle" , lang.rules+10 , lang.synts[1].kinds+3 ,
                                                             {
                                                              lang.atoms+8
                                                             }
    },
    { 50 , "length" , lang.rules+11 , lang.synts[1].kinds+3 ,
                                                              {
                                                               lang.atoms+9
                                                              }
    },
    { 51 , "point" , lang.rules+12 , lang.synts[1].kinds+3 ,
                                                             {
                                                              lang.atoms+0,
                                                              lang.atoms+11,
                                                              lang.atoms+4,
                                                              lang.atoms+11,
                                                              lang.atoms+1
                                                             }
    },
    { 52 , "empty" , lang.rules+13 , lang.synts[2].kinds+0 ,
                                                             {
                                                              
                                                             }
    },
    { 53 , "one.A" , lang.rules+14 , lang.synts[2].kinds+1 ,
                                                             {
                                                              lang.synts[1].kinds+0
                                                             }
    },
    { 54 , "one.M" , lang.rules+14 , lang.synts[2].kinds+1 ,
                                                             {
                                                              lang.synts[1].kinds+1
                                                             }
    },
    { 55 , "one.U" , lang.rules+14 , lang.synts[2].kinds+1 ,
                                                             {
                                                              lang.synts[1].kinds+2
                                                             }
    },
    { 56 , "one.P" , lang.rules+14 , lang.synts[2].kinds+1 ,
                                                             {
                                                              lang.synts[1].kinds+3
                                                             }
    },
    { 57 , "ext.N.A" , lang.rules+15 , lang.synts[2].kinds+1 ,
                                                               {
                                                                lang.synts[2].kinds+1,
                                                                lang.atoms+4,
                                                                lang.synts[1].kinds+0
                                                               }
    },
    { 58 , "ext.N.M" , lang.rules+15 , lang.synts[2].kinds+1 ,
                                                               {
                                                                lang.synts[2].kinds+1,
                                                                lang.atoms+4,
                                                                lang.synts[1].kinds+1
                                                               }
    },
    { 59 , "ext.N.U" , lang.rules+15 , lang.synts[2].kinds+1 ,
                                                               {
                                                                lang.synts[2].kinds+1,
                                                                lang.atoms+4,
                                                                lang.synts[1].kinds+2
                                                               }
    },
    { 60 , "ext.N.P" , lang.rules+15 , lang.synts[2].kinds+1 ,
                                                               {
                                                                lang.synts[2].kinds+1,
                                                                lang.atoms+4,
                                                                lang.synts[1].kinds+3
                                                               }
    }
   },
   {
    { 0 , lang.finals+37 ,
                           {
                            { lang.elements+10 , lang.states+69 },
                            { lang.elements+12 , lang.states+88 }
                           }
    },
    { 1 , lang.finals+1 ,
                          {
                           { lang.elements+0 , lang.states+3 }
                          }
    },
    { 2 , lang.finals+2 ,
                          {
                           { lang.elements+0 , lang.states+10 },
                           { lang.elements+5 , lang.states+22 },
                           { lang.elements+8 , lang.states+44 },
                           { lang.elements+9 , lang.states+46 },
                           { lang.elements+10 , lang.states+70 },
                           { lang.elements+11 , lang.states+39 },
                           { lang.elements+13 , lang.states+51 },
                           { lang.elements+14 , lang.states+50 },
                           { lang.elements+15 , lang.states+50 },
                           { lang.elements+16 , lang.states+50 },
                           { lang.elements+17 , lang.states+54 },
                           { lang.elements+18 , lang.states+66 }
                          }
    },
    { 3 , lang.finals+2 ,
                          {
                           { lang.elements+0 , lang.states+10 },
                           { lang.elements+5 , lang.states+22 },
                           { lang.elements+8 , lang.states+44 },
                           { lang.elements+9 , lang.states+46 },
                           { lang.elements+10 , lang.states+70 },
                           { lang.elements+11 , lang.states+39 },
                           { lang.elements+13 , lang.states+51 },
                           { lang.elements+14 , lang.states+50 },
                           { lang.elements+15 , lang.states+50 },
                           { lang.elements+16 , lang.states+50 },
                           { lang.elements+17 , lang.states+55 },
                           { lang.elements+18 , lang.states+67 }
                          }
    },
    { 4 , lang.finals+2 ,
                          {
                           { lang.elements+0 , lang.states+10 },
                           { lang.elements+5 , lang.states+22 },
                           { lang.elements+8 , lang.states+44 },
                           { lang.elements+9 , lang.states+46 },
                           { lang.elements+10 , lang.states+70 },
                           { lang.elements+11 , lang.states+39 },
                           { lang.elements+13 , lang.states+51 },
                           { lang.elements+14 , lang.states+50 },
                           { lang.elements+15 , lang.states+50 },
                           { lang.elements+16 , lang.states+50 },
                           { lang.elements+17 , lang.states+58 },
                           { lang.elements+18 , lang.states+68 }
                          }
    },
    { 5 , lang.finals+3 ,
                          {
                           { lang.elements+0 , lang.states+10 },
                           { lang.elements+5 , lang.states+22 },
                           { lang.elements+8 , lang.states+44 },
                           { lang.elements+9 , lang.states+46 },
                           { lang.elements+10 , lang.states+70 },
                           { lang.elements+11 , lang.states+39 },
                           { lang.elements+13 , lang.states+53 },
                           { lang.elements+14 , lang.states+52 },
                           { lang.elements+15 , lang.states+52 },
                           { lang.elements+16 , lang.states+52 }
                          }
    },
    { 6 , lang.finals+3 ,
                          {
                           { lang.elements+0 , lang.states+10 },
                           { lang.elements+5 , lang.states+22 },
                           { lang.elements+8 , lang.states+44 },
                           { lang.elements+9 , lang.states+46 },
                           { lang.elements+10 , lang.states+70 },
                           { lang.elements+11 , lang.states+39 },
                           { lang.elements+14 , lang.states+25 },
                           { lang.elements+15 , lang.states+25 },
                           { lang.elements+16 , lang.states+25 }
                          }
    },
    { 7 , lang.finals+3 ,
                          {
                           { lang.elements+0 , lang.states+10 },
                           { lang.elements+5 , lang.states+22 },
                           { lang.elements+8 , lang.states+44 },
                           { lang.elements+9 , lang.states+46 },
                           { lang.elements+10 , lang.states+70 },
                           { lang.elements+11 , lang.states+39 },
                           { lang.elements+14 , lang.states+27 },
                           { lang.elements+15 , lang.states+27 },
                           { lang.elements+16 , lang.states+27 }
                          }
    },
    { 8 , lang.finals+3 ,
                          {
                           { lang.elements+0 , lang.states+10 },
                           { lang.elements+5 , lang.states+22 },
                           { lang.elements+8 , lang.states+44 },
                           { lang.elements+9 , lang.states+46 },
                           { lang.elements+10 , lang.states+70 },
                           { lang.elements+11 , lang.states+39 },
                           { lang.elements+15 , lang.states+29 },
                           { lang.elements+16 , lang.states+29 }
                          }
    },
    { 9 , lang.finals+3 ,
                          {
                           { lang.elements+0 , lang.states+10 },
                           { lang.elements+5 , lang.states+22 },
                           { lang.elements+8 , lang.states+44 },
                           { lang.elements+9 , lang.states+46 },
                           { lang.elements+10 , lang.states+70 },
                           { lang.elements+11 , lang.states+39 },
                           { lang.elements+15 , lang.states+31 },
                           { lang.elements+16 , lang.states+31 }
                          }
    },
    { 10 , lang.finals+3 ,
                           {
                            { lang.elements+0 , lang.states+11 },
                            { lang.elements+5 , lang.states+23 },
                            { lang.elements+8 , lang.states+45 },
                            { lang.elements+9 , lang.states+47 },
                            { lang.elements+10 , lang.states+1 },
                            { lang.elements+11 , lang.states+40 },
                            { lang.elements+13 , lang.states+63 },
                            { lang.elements+14 , lang.states+60 },
                            { lang.elements+15 , lang.states+60 },
                            { lang.elements+16 , lang.states+60 }
                           }
    },
    { 11 , lang.finals+3 ,
                           {
                            { lang.elements+0 , lang.states+11 },
                            { lang.elements+5 , lang.states+23 },
                            { lang.elements+8 , lang.states+45 },
                            { lang.elements+9 , lang.states+47 },
                            { lang.elements+10 , lang.states+1 },
                            { lang.elements+11 , lang.states+41 },
                            { lang.elements+13 , lang.states+64 },
                            { lang.elements+14 , lang.states+61 },
                            { lang.elements+15 , lang.states+61 },
                            { lang.elements+16 , lang.states+61 }
                           }
    },
    { 12 , lang.finals+3 ,
                           {
                            { lang.elements+0 , lang.states+11 },
                            { lang.elements+5 , lang.states+23 },
                            { lang.elements+8 , lang.states+45 },
                            { lang.elements+9 , lang.states+47 },
                            { lang.elements+10 , lang.states+1 },
                            { lang.elements+11 , lang.states+42 },
                            { lang.elements+13 , lang.states+65 },
                            { lang.elements+14 , lang.states+62 },
                            { lang.elements+15 , lang.states+62 },
                            { lang.elements+16 , lang.states+62 }
                           }
    },
    { 13 , lang.finals+3 ,
                           {
                            { lang.elements+0 , lang.states+11 },
                            { lang.elements+5 , lang.states+23 },
                            { lang.elements+8 , lang.states+45 },
                            { lang.elements+9 , lang.states+47 },
                            { lang.elements+10 , lang.states+1 },
                            { lang.elements+11 , lang.states+43 },
                            { lang.elements+14 , lang.states+26 },
                            { lang.elements+15 , lang.states+26 },
                            { lang.elements+16 , lang.states+26 }
                           }
    },
    { 14 , lang.finals+3 ,
                           {
                            { lang.elements+0 , lang.states+11 },
                            { lang.elements+5 , lang.states+23 },
                            { lang.elements+8 , lang.states+45 },
                            { lang.elements+9 , lang.states+47 },
                            { lang.elements+10 , lang.states+1 },
                            { lang.elements+11 , lang.states+43 },
                            { lang.elements+14 , lang.states+28 },
                            { lang.elements+15 , lang.states+28 },
                            { lang.elements+16 , lang.states+28 }
                           }
    },
    { 15 , lang.finals+3 ,
                           {
                            { lang.elements+0 , lang.states+11 },
                            { lang.elements+5 , lang.states+23 },
                            { lang.elements+8 , lang.states+45 },
                            { lang.elements+9 , lang.states+47 },
                            { lang.elements+10 , lang.states+1 },
                            { lang.elements+11 , lang.states+43 },
                            { lang.elements+15 , lang.states+30 },
                            { lang.elements+16 , lang.states+30 }
                           }
    },
    { 16 , lang.finals+3 ,
                           {
                            { lang.elements+0 , lang.states+11 },
                            { lang.elements+5 , lang.states+23 },
                            { lang.elements+8 , lang.states+45 },
                            { lang.elements+9 , lang.states+47 },
                            { lang.elements+10 , lang.states+1 },
                            { lang.elements+11 , lang.states+43 },
                            { lang.elements+15 , lang.states+32 },
                            { lang.elements+16 , lang.states+32 }
                           }
    },
    { 17 , lang.finals+3 ,
                           {
                            { lang.elements+0 , lang.states+12 },
                            { lang.elements+5 , lang.states+24 },
                            { lang.elements+8 , lang.states+85 },
                            { lang.elements+9 , lang.states+86 },
                            { lang.elements+10 , lang.states+83 },
                            { lang.elements+11 , lang.states+84 },
                            { lang.elements+13 , lang.states+75 },
                            { lang.elements+14 , lang.states+74 },
                            { lang.elements+15 , lang.states+74 },
                            { lang.elements+16 , lang.states+74 }
                           }
    },
    { 18 , lang.finals+3 ,
                           {
                            { lang.elements+0 , lang.states+12 },
                            { lang.elements+5 , lang.states+24 },
                            { lang.elements+8 , lang.states+85 },
                            { lang.elements+9 , lang.states+86 },
                            { lang.elements+10 , lang.states+83 },
                            { lang.elements+11 , lang.states+84 },
                            { lang.elements+14 , lang.states+76 },
                            { lang.elements+15 , lang.states+76 },
                            { lang.elements+16 , lang.states+76 }
                           }
    },
    { 19 , lang.finals+3 ,
                           {
                            { lang.elements+0 , lang.states+12 },
                            { lang.elements+5 , lang.states+24 },
                            { lang.elements+8 , lang.states+85 },
                            { lang.elements+9 , lang.states+86 },
                            { lang.elements+10 , lang.states+83 },
                            { lang.elements+11 , lang.states+84 },
                            { lang.elements+14 , lang.states+77 },
                            { lang.elements+15 , lang.states+77 },
                            { lang.elements+16 , lang.states+77 }
                           }
    },
    { 20 , lang.finals+3 ,
                           {
                            { lang.elements+0 , lang.states+12 },
                            { lang.elements+5 , lang.states+24 },
                            { lang.elements+8 , lang.states+85 },
                            { lang.elements+9 , lang.states+86 },
                            { lang.elements+10 , lang.states+83 },
                            { lang.elements+11 , lang.states+84 },
                            { lang.elements+15 , lang.states+78 },
                            { lang.elements+16 , lang.states+78 }
                           }
    },
    { 21 , lang.finals+3 ,
                           {
                            { lang.elements+0 , lang.states+12 },
                            { lang.elements+5 , lang.states+24 },
                            { lang.elements+8 , lang.states+85 },
                            { lang.elements+9 , lang.states+86 },
                            { lang.elements+10 , lang.states+83 },
                            { lang.elements+11 , lang.states+84 },
                            { lang.elements+15 , lang.states+79 },
                            { lang.elements+16 , lang.states+79 }
                           }
    },
    { 22 , lang.finals+4 ,
                           {
                            { lang.elements+0 , lang.states+10 },
                            { lang.elements+8 , lang.states+44 },
                            { lang.elements+9 , lang.states+46 },
                            { lang.elements+10 , lang.states+70 },
                            { lang.elements+11 , lang.states+39 },
                            { lang.elements+16 , lang.states+33 }
                           }
    },
    { 23 , lang.finals+4 ,
                           {
                            { lang.elements+0 , lang.states+11 },
                            { lang.elements+8 , lang.states+45 },
                            { lang.elements+9 , lang.states+47 },
                            { lang.elements+10 , lang.states+1 },
                            { lang.elements+11 , lang.states+43 },
                            { lang.elements+16 , lang.states+34 }
                           }
    },
    { 24 , lang.finals+4 ,
                           {
                            { lang.elements+0 , lang.states+12 },
                            { lang.elements+8 , lang.states+85 },
                            { lang.elements+9 , lang.states+86 },
                            { lang.elements+10 , lang.states+83 },
                            { lang.elements+11 , lang.states+84 },
                            { lang.elements+16 , lang.states+80 }
                           }
    },
    { 25 , lang.finals+5 ,
                           {
                            { lang.elements+2 , lang.states+8 },
                            { lang.elements+6 , lang.states+9 }
                           }
    },
    { 26 , lang.finals+6 ,
                           {
                            { lang.elements+2 , lang.states+15 },
                            { lang.elements+6 , lang.states+16 }
                           }
    },
    { 27 , lang.finals+7 ,
                           {
                            { lang.elements+2 , lang.states+8 },
                            { lang.elements+6 , lang.states+9 }
                           }
    },
    { 28 , lang.finals+8 ,
                           {
                            { lang.elements+2 , lang.states+15 },
                            { lang.elements+6 , lang.states+16 }
                           }
    },
    { 29 , lang.finals+9 ,
                           {
                            
                           }
    },
    { 30 , lang.finals+10 ,
                            {
                             
                            }
    },
    { 31 , lang.finals+11 ,
                            {
                             
                            }
    },
    { 32 , lang.finals+12 ,
                            {
                             
                            }
    },
    { 33 , lang.finals+13 ,
                            {
                             
                            }
    },
    { 34 , lang.finals+14 ,
                            {
                             
                            }
    },
    { 35 , lang.finals+15 ,
                            {
                             
                            }
    },
    { 36 , lang.finals+16 ,
                            {
                             
                            }
    },
    { 37 , lang.finals+17 ,
                            {
                             
                            }
    },
    { 38 , lang.finals+18 ,
                            {
                             
                            }
    },
    { 39 , lang.finals+19 ,
                            {
                             
                            }
    },
    { 40 , lang.finals+20 ,
                            {
                             { lang.elements+4 , lang.states+71 }
                            }
    },
    { 41 , lang.finals+20 ,
                            {
                             { lang.elements+4 , lang.states+72 }
                            }
    },
    { 42 , lang.finals+20 ,
                            {
                             { lang.elements+4 , lang.states+73 }
                            }
    },
    { 43 , lang.finals+21 ,
                            {
                             
                            }
    },
    { 44 , lang.finals+22 ,
                            {
                             
                            }
    },
    { 45 , lang.finals+23 ,
                            {
                             
                            }
    },
    { 46 , lang.finals+24 ,
                            {
                             
                            }
    },
    { 47 , lang.finals+25 ,
                            {
                             
                            }
    },
    { 48 , lang.finals+26 ,
                            {
                             
                            }
    },
    { 49 , lang.finals+27 ,
                            {
                             
                            }
    },
    { 50 , lang.finals+28 ,
                            {
                             { lang.elements+2 , lang.states+8 },
                             { lang.elements+3 , lang.states+6 },
                             { lang.elements+5 , lang.states+7 },
                             { lang.elements+6 , lang.states+9 }
                            }
    },
    { 51 , lang.finals+29 ,
                            {
                             { lang.elements+3 , lang.states+6 },
                             { lang.elements+5 , lang.states+7 }
                            }
    },
    { 52 , lang.finals+30 ,
                            {
                             { lang.elements+2 , lang.states+8 },
                             { lang.elements+3 , lang.states+6 },
                             { lang.elements+5 , lang.states+7 },
                             { lang.elements+6 , lang.states+9 }
                            }
    },
    { 53 , lang.finals+31 ,
                            {
                             { lang.elements+3 , lang.states+6 },
                             { lang.elements+5 , lang.states+7 }
                            }
    },
    { 54 , lang.finals+32 ,
                            {
                             { lang.elements+1 , lang.states+37 }
                            }
    },
    { 55 , lang.finals+32 ,
                            {
                             { lang.elements+1 , lang.states+38 }
                            }
    },
    { 56 , lang.finals+32 ,
                            {
                             { lang.elements+1 , lang.states+48 }
                            }
    },
    { 57 , lang.finals+32 ,
                            {
                             { lang.elements+1 , lang.states+49 }
                            }
    },
    { 58 , lang.finals+32 ,
                            {
                             { lang.elements+1 , lang.states+82 }
                            }
    },
    { 59 , lang.finals+32 ,
                            {
                             { lang.elements+1 , lang.states+87 }
                            }
    },
    { 60 , lang.finals+33 ,
                            {
                             { lang.elements+1 , lang.states+35 },
                             { lang.elements+2 , lang.states+15 },
                             { lang.elements+3 , lang.states+13 },
                             { lang.elements+5 , lang.states+14 },
                             { lang.elements+6 , lang.states+16 }
                            }
    },
    { 61 , lang.finals+33 ,
                            {
                             { lang.elements+1 , lang.states+36 },
                             { lang.elements+2 , lang.states+15 },
                             { lang.elements+3 , lang.states+13 },
                             { lang.elements+5 , lang.states+14 },
                             { lang.elements+6 , lang.states+16 }
                            }
    },
    { 62 , lang.finals+33 ,
                            {
                             { lang.elements+1 , lang.states+81 },
                             { lang.elements+2 , lang.states+15 },
                             { lang.elements+3 , lang.states+13 },
                             { lang.elements+5 , lang.states+14 },
                             { lang.elements+6 , lang.states+16 }
                            }
    },
    { 63 , lang.finals+34 ,
                            {
                             { lang.elements+1 , lang.states+35 },
                             { lang.elements+3 , lang.states+13 },
                             { lang.elements+5 , lang.states+14 }
                            }
    },
    { 64 , lang.finals+34 ,
                            {
                             { lang.elements+1 , lang.states+36 },
                             { lang.elements+3 , lang.states+13 },
                             { lang.elements+5 , lang.states+14 }
                            }
    },
    { 65 , lang.finals+34 ,
                            {
                             { lang.elements+1 , lang.states+81 },
                             { lang.elements+3 , lang.states+13 },
                             { lang.elements+5 , lang.states+14 }
                            }
    },
    { 66 , lang.finals+35 ,
                            {
                             { lang.elements+1 , lang.states+37 },
                             { lang.elements+4 , lang.states+5 }
                            }
    },
    { 67 , lang.finals+35 ,
                            {
                             { lang.elements+1 , lang.states+38 },
                             { lang.elements+4 , lang.states+5 }
                            }
    },
    { 68 , lang.finals+35 ,
                            {
                             { lang.elements+1 , lang.states+82 },
                             { lang.elements+4 , lang.states+5 }
                            }
    },
    { 69 , lang.finals+36 ,
                            {
                             { lang.elements+7 , lang.states+17 }
                            }
    },
    { 70 , lang.finals+0 ,
                           {
                            { lang.elements+0 , lang.states+2 }
                           }
    },
    { 71 , lang.finals+38 ,
                            {
                             { lang.elements+11 , lang.states+56 }
                            }
    },
    { 72 , lang.finals+38 ,
                            {
                             { lang.elements+11 , lang.states+57 }
                            }
    },
    { 73 , lang.finals+38 ,
                            {
                             { lang.elements+11 , lang.states+59 }
                            }
    },
    { 74 , lang.finals+39 ,
                            {
                             { lang.elements+2 , lang.states+20 },
                             { lang.elements+3 , lang.states+18 },
                             { lang.elements+5 , lang.states+19 },
                             { lang.elements+6 , lang.states+21 }
                            }
    },
    { 75 , lang.finals+40 ,
                            {
                             { lang.elements+3 , lang.states+18 },
                             { lang.elements+5 , lang.states+19 }
                            }
    },
    { 76 , lang.finals+41 ,
                            {
                             { lang.elements+2 , lang.states+20 },
                             { lang.elements+6 , lang.states+21 }
                            }
    },
    { 77 , lang.finals+42 ,
                            {
                             { lang.elements+2 , lang.states+20 },
                             { lang.elements+6 , lang.states+21 }
                            }
    },
    { 78 , lang.finals+43 ,
                            {
                             
                            }
    },
    { 79 , lang.finals+44 ,
                            {
                             
                            }
    },
    { 80 , lang.finals+45 ,
                            {
                             
                            }
    },
    { 81 , lang.finals+46 ,
                            {
                             
                            }
    },
    { 82 , lang.finals+47 ,
                            {
                             
                            }
    },
    { 83 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+4 }
                            }
    },
    { 84 , lang.finals+49 ,
                            {
                             
                            }
    },
    { 85 , lang.finals+50 ,
                            {
                             
                            }
    },
    { 86 , lang.finals+51 ,
                            {
                             
                            }
    },
    { 87 , lang.finals+52 ,
                            {
                             
                            }
    },
    { 88 , lang.finals+53 ,
                            {
                             
                            }
    }
   },
   {
    { 0 ,
          {
           { lang.atoms+0 , null },
           { lang.atoms+1 , lang.rules+8 },
           { lang.atoms+2 , lang.rules+8 },
           { lang.atoms+3 , lang.rules+8 },
           { lang.atoms+4 , lang.rules+8 },
           { lang.atoms+5 , lang.rules+8 },
           { lang.atoms+6 , lang.rules+8 }
          }
    },
    { 1 ,
          {
           { lang.atoms+0 , null },
           { lang.atoms+1 , lang.rules+8 },
           { lang.atoms+2 , lang.rules+8 },
           { lang.atoms+3 , lang.rules+8 },
           { lang.atoms+5 , lang.rules+8 },
           { lang.atoms+6 , lang.rules+8 }
          }
    },
    { 2 ,
          {
           { lang.atoms+0 , null },
           { lang.atoms+1 , lang.rules+13 },
           { lang.atoms+5 , null },
           { lang.atoms+8 , null },
           { lang.atoms+9 , null },
           { lang.atoms+10 , null },
           { lang.atoms+11 , null }
          }
    },
    { 3 ,
          {
           { lang.atoms+0 , null },
           { lang.atoms+5 , null },
           { lang.atoms+8 , null },
           { lang.atoms+9 , null },
           { lang.atoms+10 , null },
           { lang.atoms+11 , null }
          }
    },
    { 4 ,
          {
           { lang.atoms+0 , null },
           { lang.atoms+8 , null },
           { lang.atoms+9 , null },
           { lang.atoms+10 , null },
           { lang.atoms+11 , null }
          }
    },
    { 5 ,
          {
           { lang.atoms+1 , lang.rules+1 },
           { lang.atoms+2 , null },
           { lang.atoms+3 , lang.rules+1 },
           { lang.atoms+4 , lang.rules+1 },
           { lang.atoms+5 , lang.rules+1 },
           { lang.atoms+6 , null }
          }
    },
    { 6 ,
          {
           { lang.atoms+1 , lang.rules+1 },
           { lang.atoms+2 , null },
           { lang.atoms+3 , lang.rules+1 },
           { lang.atoms+5 , lang.rules+1 },
           { lang.atoms+6 , null }
          }
    },
    { 7 ,
          {
           { lang.atoms+1 , lang.rules+2 },
           { lang.atoms+2 , null },
           { lang.atoms+3 , lang.rules+2 },
           { lang.atoms+4 , lang.rules+2 },
           { lang.atoms+5 , lang.rules+2 },
           { lang.atoms+6 , null }
          }
    },
    { 8 ,
          {
           { lang.atoms+1 , lang.rules+2 },
           { lang.atoms+2 , null },
           { lang.atoms+3 , lang.rules+2 },
           { lang.atoms+5 , lang.rules+2 },
           { lang.atoms+6 , null }
          }
    },
    { 9 ,
          {
           { lang.atoms+1 , lang.rules+3 },
           { lang.atoms+2 , lang.rules+3 },
           { lang.atoms+3 , lang.rules+3 },
           { lang.atoms+4 , lang.rules+3 },
           { lang.atoms+5 , lang.rules+3 },
           { lang.atoms+6 , lang.rules+3 }
          }
    },
    { 10 ,
           {
            { lang.atoms+1 , lang.rules+3 },
            { lang.atoms+2 , lang.rules+3 },
            { lang.atoms+3 , lang.rules+3 },
            { lang.atoms+5 , lang.rules+3 },
            { lang.atoms+6 , lang.rules+3 }
           }
    },
    { 11 ,
           {
            { lang.atoms+1 , lang.rules+4 },
            { lang.atoms+2 , lang.rules+4 },
            { lang.atoms+3 , lang.rules+4 },
            { lang.atoms+4 , lang.rules+4 },
            { lang.atoms+5 , lang.rules+4 },
            { lang.atoms+6 , lang.rules+4 }
           }
    },
    { 12 ,
           {
            { lang.atoms+1 , lang.rules+4 },
            { lang.atoms+2 , lang.rules+4 },
            { lang.atoms+3 , lang.rules+4 },
            { lang.atoms+5 , lang.rules+4 },
            { lang.atoms+6 , lang.rules+4 }
           }
    },
    { 13 ,
           {
            { lang.atoms+1 , lang.rules+5 },
            { lang.atoms+2 , lang.rules+5 },
            { lang.atoms+3 , lang.rules+5 },
            { lang.atoms+4 , lang.rules+5 },
            { lang.atoms+5 , lang.rules+5 },
            { lang.atoms+6 , lang.rules+5 }
           }
    },
    { 14 ,
           {
            { lang.atoms+1 , lang.rules+5 },
            { lang.atoms+2 , lang.rules+5 },
            { lang.atoms+3 , lang.rules+5 },
            { lang.atoms+5 , lang.rules+5 },
            { lang.atoms+6 , lang.rules+5 }
           }
    },
    { 15 ,
           {
            { lang.atoms+1 , lang.rules+6 },
            { lang.atoms+2 , lang.rules+6 },
            { lang.atoms+3 , lang.rules+6 },
            { lang.atoms+4 , lang.rules+6 },
            { lang.atoms+5 , lang.rules+6 },
            { lang.atoms+6 , lang.rules+6 }
           }
    },
    { 16 ,
           {
            { lang.atoms+1 , lang.rules+6 },
            { lang.atoms+2 , lang.rules+6 },
            { lang.atoms+3 , lang.rules+6 },
            { lang.atoms+5 , lang.rules+6 },
            { lang.atoms+6 , lang.rules+6 }
           }
    },
    { 17 ,
           {
            { lang.atoms+1 , lang.rules+7 },
            { lang.atoms+2 , lang.rules+7 },
            { lang.atoms+3 , lang.rules+7 },
            { lang.atoms+4 , lang.rules+7 },
            { lang.atoms+5 , lang.rules+7 },
            { lang.atoms+6 , lang.rules+7 }
           }
    },
    { 18 ,
           {
            { lang.atoms+1 , lang.rules+7 },
            { lang.atoms+2 , lang.rules+7 },
            { lang.atoms+3 , lang.rules+7 },
            { lang.atoms+5 , lang.rules+7 },
            { lang.atoms+6 , lang.rules+7 }
           }
    },
    { 19 ,
           {
            { lang.atoms+1 , lang.rules+9 },
            { lang.atoms+2 , lang.rules+9 },
            { lang.atoms+3 , lang.rules+9 },
            { lang.atoms+4 , lang.rules+9 },
            { lang.atoms+5 , lang.rules+9 },
            { lang.atoms+6 , lang.rules+9 }
           }
    },
    { 20 ,
           {
            { lang.atoms+1 , lang.rules+9 },
            { lang.atoms+2 , lang.rules+9 },
            { lang.atoms+3 , lang.rules+9 },
            { lang.atoms+4 , null },
            { lang.atoms+5 , lang.rules+9 },
            { lang.atoms+6 , lang.rules+9 }
           }
    },
    { 21 ,
           {
            { lang.atoms+1 , lang.rules+9 },
            { lang.atoms+2 , lang.rules+9 },
            { lang.atoms+3 , lang.rules+9 },
            { lang.atoms+5 , lang.rules+9 },
            { lang.atoms+6 , lang.rules+9 }
           }
    },
    { 22 ,
           {
            { lang.atoms+1 , lang.rules+10 },
            { lang.atoms+2 , lang.rules+10 },
            { lang.atoms+3 , lang.rules+10 },
            { lang.atoms+4 , lang.rules+10 },
            { lang.atoms+5 , lang.rules+10 },
            { lang.atoms+6 , lang.rules+10 }
           }
    },
    { 23 ,
           {
            { lang.atoms+1 , lang.rules+10 },
            { lang.atoms+2 , lang.rules+10 },
            { lang.atoms+3 , lang.rules+10 },
            { lang.atoms+5 , lang.rules+10 },
            { lang.atoms+6 , lang.rules+10 }
           }
    },
    { 24 ,
           {
            { lang.atoms+1 , lang.rules+11 },
            { lang.atoms+2 , lang.rules+11 },
            { lang.atoms+3 , lang.rules+11 },
            { lang.atoms+4 , lang.rules+11 },
            { lang.atoms+5 , lang.rules+11 },
            { lang.atoms+6 , lang.rules+11 }
           }
    },
    { 25 ,
           {
            { lang.atoms+1 , lang.rules+11 },
            { lang.atoms+2 , lang.rules+11 },
            { lang.atoms+3 , lang.rules+11 },
            { lang.atoms+5 , lang.rules+11 },
            { lang.atoms+6 , lang.rules+11 }
           }
    },
    { 26 ,
           {
            { lang.atoms+1 , lang.rules+12 },
            { lang.atoms+2 , lang.rules+12 },
            { lang.atoms+3 , lang.rules+12 },
            { lang.atoms+4 , lang.rules+12 },
            { lang.atoms+5 , lang.rules+12 },
            { lang.atoms+6 , lang.rules+12 }
           }
    },
    { 27 ,
           {
            { lang.atoms+1 , lang.rules+12 },
            { lang.atoms+2 , lang.rules+12 },
            { lang.atoms+3 , lang.rules+12 },
            { lang.atoms+5 , lang.rules+12 },
            { lang.atoms+6 , lang.rules+12 }
           }
    },
    { 28 ,
           {
            { lang.atoms+1 , lang.rules+14 },
            { lang.atoms+2 , null },
            { lang.atoms+3 , null },
            { lang.atoms+4 , lang.rules+14 },
            { lang.atoms+5 , null },
            { lang.atoms+6 , null }
           }
    },
    { 29 ,
           {
            { lang.atoms+1 , lang.rules+14 },
            { lang.atoms+3 , null },
            { lang.atoms+4 , lang.rules+14 },
            { lang.atoms+5 , null }
           }
    },
    { 30 ,
           {
            { lang.atoms+1 , lang.rules+15 },
            { lang.atoms+2 , null },
            { lang.atoms+3 , null },
            { lang.atoms+4 , lang.rules+15 },
            { lang.atoms+5 , null },
            { lang.atoms+6 , null }
           }
    },
    { 31 ,
           {
            { lang.atoms+1 , lang.rules+15 },
            { lang.atoms+3 , null },
            { lang.atoms+4 , lang.rules+15 },
            { lang.atoms+5 , null }
           }
    },
    { 32 ,
           {
            { lang.atoms+1 , null }
           }
    },
    { 33 ,
           {
            { lang.atoms+1 , null },
            { lang.atoms+2 , null },
            { lang.atoms+3 , null },
            { lang.atoms+5 , null },
            { lang.atoms+6 , null }
           }
    },
    { 34 ,
           {
            { lang.atoms+1 , null },
            { lang.atoms+3 , null },
            { lang.atoms+5 , null }
           }
    },
    { 35 ,
           {
            { lang.atoms+1 , null },
            { lang.atoms+4 , null }
           }
    },
    { 36 ,
           {
            { lang.atoms+7 , null }
           }
    },
    { 37 ,
           {
            { lang.atoms+10 , null }
           }
    },
    { 38 ,
           {
            { lang.atoms+11 , null }
           }
    },
    { 39 ,
           {
            { null , lang.rules+0 },
            { lang.atoms+2 , null },
            { lang.atoms+3 , null },
            { lang.atoms+5 , null },
            { lang.atoms+6 , null }
           }
    },
    { 40 ,
           {
            { null , lang.rules+0 },
            { lang.atoms+3 , null },
            { lang.atoms+5 , null }
           }
    },
    { 41 ,
           {
            { null , lang.rules+1 },
            { lang.atoms+2 , null },
            { lang.atoms+3 , lang.rules+1 },
            { lang.atoms+5 , lang.rules+1 },
            { lang.atoms+6 , null }
           }
    },
    { 42 ,
           {
            { null , lang.rules+2 },
            { lang.atoms+2 , null },
            { lang.atoms+3 , lang.rules+2 },
            { lang.atoms+5 , lang.rules+2 },
            { lang.atoms+6 , null }
           }
    },
    { 43 ,
           {
            { null , lang.rules+3 },
            { lang.atoms+2 , lang.rules+3 },
            { lang.atoms+3 , lang.rules+3 },
            { lang.atoms+5 , lang.rules+3 },
            { lang.atoms+6 , lang.rules+3 }
           }
    },
    { 44 ,
           {
            { null , lang.rules+4 },
            { lang.atoms+2 , lang.rules+4 },
            { lang.atoms+3 , lang.rules+4 },
            { lang.atoms+5 , lang.rules+4 },
            { lang.atoms+6 , lang.rules+4 }
           }
    },
    { 45 ,
           {
            { null , lang.rules+5 },
            { lang.atoms+2 , lang.rules+5 },
            { lang.atoms+3 , lang.rules+5 },
            { lang.atoms+5 , lang.rules+5 },
            { lang.atoms+6 , lang.rules+5 }
           }
    },
    { 46 ,
           {
            { null , lang.rules+6 },
            { lang.atoms+2 , lang.rules+6 },
            { lang.atoms+3 , lang.rules+6 },
            { lang.atoms+5 , lang.rules+6 },
            { lang.atoms+6 , lang.rules+6 }
           }
    },
    { 47 ,
           {
            { null , lang.rules+7 },
            { lang.atoms+2 , lang.rules+7 },
            { lang.atoms+3 , lang.rules+7 },
            { lang.atoms+5 , lang.rules+7 },
            { lang.atoms+6 , lang.rules+7 }
           }
    },
    { 48 ,
           {
            { null , lang.rules+8 },
            { lang.atoms+0 , null },
            { lang.atoms+2 , lang.rules+8 },
            { lang.atoms+3 , lang.rules+8 },
            { lang.atoms+5 , lang.rules+8 },
            { lang.atoms+6 , lang.rules+8 }
           }
    },
    { 49 ,
           {
            { null , lang.rules+9 },
            { lang.atoms+2 , lang.rules+9 },
            { lang.atoms+3 , lang.rules+9 },
            { lang.atoms+5 , lang.rules+9 },
            { lang.atoms+6 , lang.rules+9 }
           }
    },
    { 50 ,
           {
            { null , lang.rules+10 },
            { lang.atoms+2 , lang.rules+10 },
            { lang.atoms+3 , lang.rules+10 },
            { lang.atoms+5 , lang.rules+10 },
            { lang.atoms+6 , lang.rules+10 }
           }
    },
    { 51 ,
           {
            { null , lang.rules+11 },
            { lang.atoms+2 , lang.rules+11 },
            { lang.atoms+3 , lang.rules+11 },
            { lang.atoms+5 , lang.rules+11 },
            { lang.atoms+6 , lang.rules+11 }
           }
    },
    { 52 ,
           {
            { null , lang.rules+12 },
            { lang.atoms+2 , lang.rules+12 },
            { lang.atoms+3 , lang.rules+12 },
            { lang.atoms+5 , lang.rules+12 },
            { lang.atoms+6 , lang.rules+12 }
           }
    },
    { 53 ,
           {
            { null , null }
           }
    }
   }
 };

