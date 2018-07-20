/* struct TypeSet */

struct TypeSet : TypeDefCore
 {
  ulen indexes[45];
  DynArray<ulen> ind_map;

  DDL::FindNodeMap map;

  explicit TypeSet(ulen len)
   : ind_map(len)
   {
    Range(indexes).set(ulen(-1));

    map.add(5,"Text");
    map.add(8,"MultiLine");
    map.add(10,"OneLine");
    map.add(11,"FixedText");
    map.add(4,"Span");
    map.add(13,"Link");
    map.add(17,"Table");
    map.add(26,"Cell");
    map.add(28,"Border");
    map.add(31,"TextList");
    map.add(30,"ItemList");
    map.add(29,"Item");
    map.add(32,"Collapse");
    map.add(33,"Bitmap");
    map.add(34,"Section");
    map.add(36,"Scope");
    map.add(37,"Page");
    map.add(25,"FrameList");
    map.add(24,"Frame");
    map.add(38,"DoubleLine");
    map.add(39,"SingleLine");
    map.add(42,"Format");
    map.add(44,"Font");
    map.add(45,"Doc");
    map.add(35,"Defaults");
    map.add(1,"PlacementPtr");
    map.add(3,"RefPtr");
    map.add(16,"CellPtr");
    map.add(14,"BorderPtr");
    map.add(2,"FormatPtr");
    map.add(23,"BodyPtr");
    map.add(22,"LinePtr");
    map.add(40,"FontPtr");
    map.add(12,"PagePtr");
    map.add(18,"OptULen");
    map.add(43,"OptInt");
    map.add(15,"OptBool");
    map.add(9,"OptAlign");
    map.add(41,"OptEffect");
    map.add(7,"OptRatio");
    map.add(27,"OptCoord");
    map.add(20,"OptPoint");
    map.add(21,"OptColor");
    map.add(6,"Ratio");
    map.add(19,"Point");

    map.complete();
   }

  DDL::MapSizeInfo structSizeInfo(DDL::StructNode *struct_node)
   {
    DDL::MapSizeInfo ret;

    switch( map.find(struct_node) )
      {
       case 5 :
        {
         indexes[4]=struct_node->index;
         ind_map[struct_node->index]=5;

         ret.set<S5>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S5,name),
                               "open",offsetof(S5,open),
                               "placement",offsetof(S5,placement),
                               "format",offsetof(S5,format),
                               "list",offsetof(S5,list)
                              );
        }
       return ret;

       case 8 :
        {
         indexes[7]=struct_node->index;
         ind_map[struct_node->index]=8;

         ret.set<S8>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S8,name),
                               "open",offsetof(S8,open),
                               "line_space",offsetof(S8,line_space),
                               "first_line_space",offsetof(S8,first_line_space)
                              );
        }
       return ret;

       case 10 :
        {
         indexes[9]=struct_node->index;
         ind_map[struct_node->index]=10;

         ret.set<S10>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S10,name),
                               "open",offsetof(S10,open),
                               "align",offsetof(S10,align)
                              );
        }
       return ret;

       case 11 :
        {
         indexes[10]=struct_node->index;
         ind_map[struct_node->index]=11;

         ret.set<S11>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S11,name),
                               "open",offsetof(S11,open),
                               "format",offsetof(S11,format),
                               "list",offsetof(S11,list)
                              );
        }
       return ret;

       case 4 :
        {
         indexes[3]=struct_node->index;
         ind_map[struct_node->index]=4;

         ret.set<S4>();

         DDL::SetFieldOffsets(struct_node,
                               "body",offsetof(S4,body),
                               "format",offsetof(S4,format),
                               "ref",offsetof(S4,ref)
                              );
        }
       return ret;

       case 13 :
        {
         indexes[12]=struct_node->index;
         ind_map[struct_node->index]=13;

         ret.set<S13>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S13,name),
                               "open",offsetof(S13,open),
                               "page",offsetof(S13,page),
                               "index_list",offsetof(S13,index_list)
                              );
        }
       return ret;

       case 17 :
        {
         indexes[16]=struct_node->index;
         ind_map[struct_node->index]=17;

         ret.set<S17>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S17,name),
                               "open",offsetof(S17,open),
                               "border",offsetof(S17,border),
                               "hard",offsetof(S17,hard),
                               "width",offsetof(S17,width),
                               "table",offsetof(S17,table)
                              );
        }
       return ret;

       case 26 :
        {
         indexes[25]=struct_node->index;
         ind_map[struct_node->index]=26;

         ret.set<S26>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S26,name),
                               "open",offsetof(S26,open),
                               "span_x",offsetof(S26,span_x),
                               "span_y",offsetof(S26,span_y),
                               "list",offsetof(S26,list)
                              );
        }
       return ret;

       case 28 :
        {
         indexes[27]=struct_node->index;
         ind_map[struct_node->index]=28;

         ret.set<S28>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S28,name),
                               "open",offsetof(S28,open),
                               "space",offsetof(S28,space),
                               "width",offsetof(S28,width),
                               "line",offsetof(S28,line)
                              );
        }
       return ret;

       case 31 :
        {
         indexes[30]=struct_node->index;
         ind_map[struct_node->index]=31;

         ret.set<S31>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S31,name),
                               "open",offsetof(S31,open),
                               "format",offsetof(S31,format),
                               "bullet_space",offsetof(S31,bullet_space),
                               "item_space",offsetof(S31,item_space),
                               "list",offsetof(S31,list)
                              );
        }
       return ret;

       case 30 :
        {
         indexes[29]=struct_node->index;
         ind_map[struct_node->index]=30;

         ret.set<S30>();

         DDL::SetFieldOffsets(struct_node,
                               "list",offsetof(S30,list),
                               "cur",offsetof(S30,cur)
                              );
        }
       return ret;

       case 29 :
        {
         indexes[28]=struct_node->index;
         ind_map[struct_node->index]=29;

         ret.set<S29>();

         DDL::SetFieldOffsets(struct_node,
                               "bullet",offsetof(S29,bullet),
                               "list",offsetof(S29,list)
                              );
        }
       return ret;

       case 32 :
        {
         indexes[31]=struct_node->index;
         ind_map[struct_node->index]=32;

         ret.set<S32>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S32,name),
                               "open",offsetof(S32,open),
                               "title",offsetof(S32,title),
                               "format",offsetof(S32,format),
                               "onelist",offsetof(S32,onelist),
                               "hide",offsetof(S32,hide),
                               "list",offsetof(S32,list)
                              );
        }
       return ret;

       case 33 :
        {
         indexes[32]=struct_node->index;
         ind_map[struct_node->index]=33;

         ret.set<S33>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S33,name),
                               "file_name",offsetof(S33,file_name)
                              );
        }
       return ret;

       case 34 :
        {
         indexes[33]=struct_node->index;
         ind_map[struct_node->index]=34;

         ret.set<S34>();

         DDL::SetFieldOffsets(struct_node,
                               "open",offsetof(S34,open),
                               "comment",offsetof(S34,comment),
                               "list",offsetof(S34,list)
                              );
        }
       return ret;

       case 36 :
        {
         indexes[35]=struct_node->index;
         ind_map[struct_node->index]=36;

         ret.set<S36>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S36,name),
                               "open",offsetof(S36,open),
                               "defs",offsetof(S36,defs),
                               "list",offsetof(S36,list)
                              );
        }
       return ret;

       case 37 :
        {
         indexes[36]=struct_node->index;
         ind_map[struct_node->index]=37;

         ret.set<S37>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S37,name),
                               "open",offsetof(S37,open),
                               "title",offsetof(S37,title),
                               "back",offsetof(S37,back),
                               "fore",offsetof(S37,fore),
                               "up",offsetof(S37,up),
                               "prev",offsetof(S37,prev),
                               "next",offsetof(S37,next),
                               "list",offsetof(S37,list)
                              );
        }
       return ret;

       case 25 :
        {
         indexes[24]=struct_node->index;
         ind_map[struct_node->index]=25;

         ret.set<S25>();

         DDL::SetFieldOffsets(struct_node,
                               "list",offsetof(S25,list),
                               "cur",offsetof(S25,cur)
                              );
        }
       return ret;

       case 24 :
        {
         indexes[23]=struct_node->index;
         ind_map[struct_node->index]=24;

         ret.set<S24>();

         DDL::SetFieldOffsets(struct_node,
                               "inner",offsetof(S24,inner),
                               "outer",offsetof(S24,outer),
                               "col",offsetof(S24,col),
                               "line",offsetof(S24,line),
                               "body",offsetof(S24,body)
                              );
        }
       return ret;

       case 38 :
        {
         indexes[37]=struct_node->index;
         ind_map[struct_node->index]=38;

         ret.set<S38>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S38,name),
                               "open",offsetof(S38,open),
                               "width",offsetof(S38,width),
                               "gray",offsetof(S38,gray),
                               "snow",offsetof(S38,snow)
                              );
        }
       return ret;

       case 39 :
        {
         indexes[38]=struct_node->index;
         ind_map[struct_node->index]=39;

         ret.set<S39>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S39,name),
                               "open",offsetof(S39,open),
                               "width",offsetof(S39,width),
                               "line",offsetof(S39,line)
                              );
        }
       return ret;

       case 42 :
        {
         indexes[41]=struct_node->index;
         ind_map[struct_node->index]=42;

         ret.set<S42>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S42,name),
                               "open",offsetof(S42,open),
                               "font",offsetof(S42,font),
                               "back",offsetof(S42,back),
                               "fore",offsetof(S42,fore),
                               "effect",offsetof(S42,effect)
                              );
        }
       return ret;

       case 44 :
        {
         indexes[43]=struct_node->index;
         ind_map[struct_node->index]=44;

         ret.set<S44>();

         DDL::SetFieldOffsets(struct_node,
                               "face",offsetof(S44,face),
                               "size",offsetof(S44,size),
                               "bold",offsetof(S44,bold),
                               "italic",offsetof(S44,italic),
                               "strength",offsetof(S44,strength)
                              );
        }
       return ret;

       case 45 :
        {
         indexes[44]=struct_node->index;
         ind_map[struct_node->index]=45;

         ret.set<S45>();

         DDL::SetFieldOffsets(struct_node,
                               "title",offsetof(S45,title),
                               "back",offsetof(S45,back),
                               "fore",offsetof(S45,fore),
                               "start",offsetof(S45,start),
                               "defs",offsetof(S45,defs),
                               "list",offsetof(S45,list)
                              );
        }
       return ret;

       case 35 :
        {
         indexes[34]=struct_node->index;
         ind_map[struct_node->index]=35;

         ret.set<S35>();

         DDL::SetFieldOffsets(struct_node,
                               "inner",offsetof(S35,inner),
                               "outer",offsetof(S35,outer),
                               "bulletSpace",offsetof(S35,bulletSpace),
                               "itemSpace",offsetof(S35,itemSpace),
                               "singleLine",offsetof(S35,singleLine),
                               "doubleLine",offsetof(S35,doubleLine),
                               "collapseFormat",offsetof(S35,collapseFormat),
                               "bulletFormat",offsetof(S35,bulletFormat),
                               "border",offsetof(S35,border),
                               "textFormat",offsetof(S35,textFormat),
                               "fixedFormat",offsetof(S35,fixedFormat),
                               "placement",offsetof(S35,placement)
                              );
        }
       return ret;

       case 1 :
        {
         indexes[0]=struct_node->index;
         ind_map[struct_node->index]=1;

         ret.set<S1>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S1,name),
                               "ptr",offsetof(S1,ptr)
                              );
        }
       return ret;

       case 3 :
        {
         indexes[2]=struct_node->index;
         ind_map[struct_node->index]=3;

         ret.set<S3>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S3,name),
                               "ptr",offsetof(S3,ptr)
                              );
        }
       return ret;

       case 16 :
        {
         indexes[15]=struct_node->index;
         ind_map[struct_node->index]=16;

         ret.set<S16>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S16,name),
                               "ptr",offsetof(S16,ptr)
                              );
        }
       return ret;

       case 14 :
        {
         indexes[13]=struct_node->index;
         ind_map[struct_node->index]=14;

         ret.set<S14>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S14,name),
                               "ptr",offsetof(S14,ptr)
                              );
        }
       return ret;

       case 2 :
        {
         indexes[1]=struct_node->index;
         ind_map[struct_node->index]=2;

         ret.set<S2>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S2,name),
                               "ptr",offsetof(S2,ptr)
                              );
        }
       return ret;

       case 23 :
        {
         indexes[22]=struct_node->index;
         ind_map[struct_node->index]=23;

         ret.set<S23>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S23,name),
                               "ptr",offsetof(S23,ptr)
                              );
        }
       return ret;

       case 22 :
        {
         indexes[21]=struct_node->index;
         ind_map[struct_node->index]=22;

         ret.set<S22>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S22,name),
                               "ptr",offsetof(S22,ptr)
                              );
        }
       return ret;

       case 40 :
        {
         indexes[39]=struct_node->index;
         ind_map[struct_node->index]=40;

         ret.set<S40>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S40,name),
                               "ptr",offsetof(S40,ptr)
                              );
        }
       return ret;

       case 12 :
        {
         indexes[11]=struct_node->index;
         ind_map[struct_node->index]=12;

         ret.set<S12>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S12,name),
                               "ptr",offsetof(S12,ptr)
                              );
        }
       return ret;

       case 18 :
        {
         indexes[17]=struct_node->index;
         ind_map[struct_node->index]=18;

         ret.set<S18>();

         DDL::SetFieldOffsets(struct_node,
                               "def",offsetof(S18,def),
                               "data",offsetof(S18,data)
                              );
        }
       return ret;

       case 43 :
        {
         indexes[42]=struct_node->index;
         ind_map[struct_node->index]=43;

         ret.set<S43>();

         DDL::SetFieldOffsets(struct_node,
                               "def",offsetof(S43,def),
                               "data",offsetof(S43,data)
                              );
        }
       return ret;

       case 15 :
        {
         indexes[14]=struct_node->index;
         ind_map[struct_node->index]=15;

         ret.set<S15>();

         DDL::SetFieldOffsets(struct_node,
                               "def",offsetof(S15,def),
                               "data",offsetof(S15,data)
                              );
        }
       return ret;

       case 9 :
        {
         indexes[8]=struct_node->index;
         ind_map[struct_node->index]=9;

         ret.set<S9>();

         DDL::SetFieldOffsets(struct_node,
                               "def",offsetof(S9,def),
                               "data",offsetof(S9,data)
                              );
        }
       return ret;

       case 41 :
        {
         indexes[40]=struct_node->index;
         ind_map[struct_node->index]=41;

         ret.set<S41>();

         DDL::SetFieldOffsets(struct_node,
                               "def",offsetof(S41,def),
                               "data",offsetof(S41,data)
                              );
        }
       return ret;

       case 7 :
        {
         indexes[6]=struct_node->index;
         ind_map[struct_node->index]=7;

         ret.set<S7>();

         DDL::SetFieldOffsets(struct_node,
                               "def",offsetof(S7,def),
                               "data",offsetof(S7,data)
                              );
        }
       return ret;

       case 27 :
        {
         indexes[26]=struct_node->index;
         ind_map[struct_node->index]=27;

         ret.set<S27>();

         DDL::SetFieldOffsets(struct_node,
                               "def",offsetof(S27,def),
                               "data",offsetof(S27,data)
                              );
        }
       return ret;

       case 20 :
        {
         indexes[19]=struct_node->index;
         ind_map[struct_node->index]=20;

         ret.set<S20>();

         DDL::SetFieldOffsets(struct_node,
                               "def",offsetof(S20,def),
                               "data",offsetof(S20,data)
                              );
        }
       return ret;

       case 21 :
        {
         indexes[20]=struct_node->index;
         ind_map[struct_node->index]=21;

         ret.set<S21>();

         DDL::SetFieldOffsets(struct_node,
                               "def",offsetof(S21,def),
                               "data",offsetof(S21,data)
                              );
        }
       return ret;

       case 6 :
        {
         indexes[5]=struct_node->index;
         ind_map[struct_node->index]=6;

         ret.set<S6>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S6,a),
                               "b",offsetof(S6,b)
                              );
        }
       return ret;

       case 19 :
        {
         indexes[18]=struct_node->index;
         ind_map[struct_node->index]=19;

         ret.set<S19>();

         DDL::SetFieldOffsets(struct_node,
                               "x",offsetof(S19,x),
                               "y",offsetof(S19,y)
                              );
        }
       return ret;

       default: Printf(Exception,"Unknown structure"); return ret;
      }
   }

  template <class T> struct IsStruct;

  template <class T>
  bool isStruct(DDL::StructNode *struct_node) const { return IsStruct<T>::Do(indexes,struct_node->index); }

  void guardFieldTypes(DDL::StructNode *struct_node) const
   {
    switch( ind_map[struct_node->index] )
      {
       case 5 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A7,
                               S1,
                               S2,
                               DDL::MapRange< S4 >
                              >(*this,struct_node);
        }
       break;

       case 8 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A7,
                               S7,
                               S7
                              >(*this,struct_node);
        }
       break;

       case 10 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A7,
                               S9
                              >(*this,struct_node);
        }
       break;

       case 11 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A7,
                               S2,
                               DDL::MapRange< A1 >
                              >(*this,struct_node);
        }
       break;

       case 4 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               S2,
                               S3
                              >(*this,struct_node);
        }
       break;

       case 13 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A7,
                               S12,
                               DDL::MapRange< DDL::ulen_type >
                              >(*this,struct_node);
        }
       break;

       case 17 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A7,
                               S14,
                               S15,
                               DDL::MapRange< A5 >,
                               DDL::MapRange< S16 >
                              >(*this,struct_node);
        }
       break;

       case 26 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A7,
                               S18,
                               S18,
                               S25
                              >(*this,struct_node);
        }
       break;

       case 28 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A7,
                               S27,
                               S7,
                               S21
                              >(*this,struct_node);
        }
       break;

       case 31 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A7,
                               S2,
                               S27,
                               S27,
                               S30
                              >(*this,struct_node);
        }
       break;

       case 30 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapRange< S29 >,
                               DDL::ulen_type
                              >(*this,struct_node);
        }
       break;

       case 29 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               S25
                              >(*this,struct_node);
        }
       break;

       case 32 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A7,
                               DDL::MapText,
                               S2,
                               A7,
                               S15,
                               S25
                              >(*this,struct_node);
        }
       break;

       case 33 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               DDL::MapText
                              >(*this,struct_node);
        }
       break;

       case 34 :
        {
         DDL::GuardFieldTypes<
                               A7,
                               DDL::MapText,
                               DDL::MapRange< A2 >
                              >(*this,struct_node);
        }
       break;

       case 36 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A7,
                               S35,
                               DDL::MapRange< A2 >
                              >(*this,struct_node);
        }
       break;

       case 37 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A7,
                               DDL::MapText,
                               S21,
                               S21,
                               S12,
                               S12,
                               S12,
                               S25
                              >(*this,struct_node);
        }
       break;

       case 25 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapRange< S24 >,
                               DDL::ulen_type
                              >(*this,struct_node);
        }
       break;

       case 24 :
        {
         DDL::GuardFieldTypes<
                               S20,
                               S20,
                               S21,
                               S22,
                               S23
                              >(*this,struct_node);
        }
       break;

       case 38 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A7,
                               S7,
                               S21,
                               S21
                              >(*this,struct_node);
        }
       break;

       case 39 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A7,
                               S7,
                               S21
                              >(*this,struct_node);
        }
       break;

       case 42 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A7,
                               S40,
                               S21,
                               S21,
                               S41
                              >(*this,struct_node);
        }
       break;

       case 44 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A5,
                               S15,
                               S15,
                               S43
                              >(*this,struct_node);
        }
       break;

       case 45 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               S21,
                               S21,
                               S12,
                               S35,
                               DDL::MapRange< A2 >
                              >(*this,struct_node);
        }
       break;

       case 35 :
        {
         DDL::GuardFieldTypes<
                               S20,
                               S20,
                               S27,
                               S27,
                               DDL::MapPtr< S39 >,
                               DDL::MapPtr< S38 >,
                               DDL::MapPtr< S42 >,
                               DDL::MapPtr< S42 >,
                               DDL::MapPtr< S28 >,
                               DDL::MapPtr< S42 >,
                               DDL::MapPtr< S42 >,
                               DDL::MapPolyPtr< S10 , S8 >
                              >(*this,struct_node);
        }
       break;

       case 1 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               DDL::MapPolyPtr< S10 , S8 >
                              >(*this,struct_node);
        }
       break;

       case 3 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               DDL::MapPolyPtr< S13 , S37 >
                              >(*this,struct_node);
        }
       break;

       case 16 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               DDL::MapPtr< S26 >
                              >(*this,struct_node);
        }
       break;

       case 14 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               DDL::MapPtr< S28 >
                              >(*this,struct_node);
        }
       break;

       case 2 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               DDL::MapPtr< S42 >
                              >(*this,struct_node);
        }
       break;

       case 23 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               DDL::MapPolyPtr< S33 , S32 , S31 , S17 , S5 , S11 >
                              >(*this,struct_node);
        }
       break;

       case 22 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               DDL::MapPolyPtr< S39 , S38 >
                              >(*this,struct_node);
        }
       break;

       case 40 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               DDL::MapPtr< S44 >
                              >(*this,struct_node);
        }
       break;

       case 12 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               DDL::MapPtr< S37 >
                              >(*this,struct_node);
        }
       break;

       case 18 :
        {
         DDL::GuardFieldTypes<
                               A7,
                               DDL::ulen_type
                              >(*this,struct_node);
        }
       break;

       case 43 :
        {
         DDL::GuardFieldTypes<
                               A7,
                               DDL::sint_type
                              >(*this,struct_node);
        }
       break;

       case 15 :
        {
         DDL::GuardFieldTypes<
                               A7,
                               A7
                              >(*this,struct_node);
        }
       break;

       case 9 :
        {
         DDL::GuardFieldTypes<
                               A7,
                               A3
                              >(*this,struct_node);
        }
       break;

       case 41 :
        {
         DDL::GuardFieldTypes<
                               A7,
                               A4
                              >(*this,struct_node);
        }
       break;

       case 7 :
        {
         DDL::GuardFieldTypes<
                               A7,
                               S6
                              >(*this,struct_node);
        }
       break;

       case 27 :
        {
         DDL::GuardFieldTypes<
                               A7,
                               A5
                              >(*this,struct_node);
        }
       break;

       case 20 :
        {
         DDL::GuardFieldTypes<
                               A7,
                               S19
                              >(*this,struct_node);
        }
       break;

       case 21 :
        {
         DDL::GuardFieldTypes<
                               A7,
                               A6
                              >(*this,struct_node);
        }
       break;

       case 6 :
        {
         DDL::GuardFieldTypes<
                               A5,
                               A5
                              >(*this,struct_node);
        }
       break;

       case 19 :
        {
         DDL::GuardFieldTypes<
                               A5,
                               A5
                              >(*this,struct_node);
        }
       break;

       default: Printf(Exception,"Unknown structure");
      }
   }
 };

template <class T>
struct TypeSet::IsStruct
 {
  static bool Do(const ulen *,ulen) { return false; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S5>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[4]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S8>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[7]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S10>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[9]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S11>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[10]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S4>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[3]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S13>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[12]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S17>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[16]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S26>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[25]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S28>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[27]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S31>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[30]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S30>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[29]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S29>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[28]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S32>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[31]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S33>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[32]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S34>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[33]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S36>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[35]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S37>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[36]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S25>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[24]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S24>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[23]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S38>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[37]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S39>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[38]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S42>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[41]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S44>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[43]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S45>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[44]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S35>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[34]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S1>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[0]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S3>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[2]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S16>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[15]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S14>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[13]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S2>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[1]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S23>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[22]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S22>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[21]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S40>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[39]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S12>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[11]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S18>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[17]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S43>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[42]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S15>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[14]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S9>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[8]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S41>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[40]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S7>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[6]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S27>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[26]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S20>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[19]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S21>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[20]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S6>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[5]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S19>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[18]; }
 };

