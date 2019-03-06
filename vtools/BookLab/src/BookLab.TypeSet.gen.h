/* struct TypeSet */

struct TypeSet : TypeDefCore
 {
  ulen indexes[47];
  DynArray<ulen> ind_map;

  DDL::FindNodeMap map;

  explicit TypeSet(ulen len)
   : ind_map(len)
   {
    Range(indexes).set(ulen(-1));

    map.add(1,"Extern");
    map.add(2,"Include");
    map.add(7,"Text");
    map.add(10,"MultiLine");
    map.add(12,"OneLine");
    map.add(13,"FixedText");
    map.add(6,"Span");
    map.add(14,"Link");
    map.add(18,"Table");
    map.add(27,"Cell");
    map.add(29,"Border");
    map.add(32,"TextList");
    map.add(31,"ItemList");
    map.add(30,"Item");
    map.add(33,"Collapse");
    map.add(34,"Bitmap");
    map.add(35,"Section");
    map.add(37,"Scope");
    map.add(39,"Page");
    map.add(26,"FrameList");
    map.add(25,"Frame");
    map.add(40,"DoubleLine");
    map.add(41,"SingleLine");
    map.add(44,"Format");
    map.add(46,"Font");
    map.add(47,"Doc");
    map.add(36,"Defaults");
    map.add(3,"PlacementPtr");
    map.add(5,"RefPtr");
    map.add(17,"CellPtr");
    map.add(15,"BorderPtr");
    map.add(4,"FormatPtr");
    map.add(24,"BodyPtr");
    map.add(23,"LinePtr");
    map.add(42,"FontPtr");
    map.add(38,"PagePtr");
    map.add(19,"OptULen");
    map.add(45,"OptInt");
    map.add(16,"OptBool");
    map.add(11,"OptAlign");
    map.add(43,"OptEffect");
    map.add(9,"OptRatio");
    map.add(28,"OptCoord");
    map.add(21,"OptPoint");
    map.add(22,"OptColor");
    map.add(8,"Ratio");
    map.add(20,"Point");

    map.complete();
   }

  DDL::MapSizeInfo structSizeInfo(DDL::StructNode *struct_node)
   {
    DDL::MapSizeInfo ret;

    switch( map.find(struct_node) )
      {
       case 1 :
        {
         indexes[0]=struct_node->index;
         ind_map[struct_node->index]=1;

         ret.set<S1>();

         DDL::SetFieldOffsets(struct_node,
                               "ptr",offsetof(S1,ptr)
                              );
        }
       return ret;

       case 2 :
        {
         indexes[1]=struct_node->index;
         ind_map[struct_node->index]=2;

         ret.set<S2>();

         DDL::SetFieldOffsets(struct_node,
                               "file_name",offsetof(S2,file_name)
                              );
        }
       return ret;

       case 7 :
        {
         indexes[6]=struct_node->index;
         ind_map[struct_node->index]=7;

         ret.set<S7>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S7,name),
                               "open",offsetof(S7,open),
                               "placement",offsetof(S7,placement),
                               "format",offsetof(S7,format),
                               "list",offsetof(S7,list)
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
                               "line_space",offsetof(S10,line_space),
                               "first_line_space",offsetof(S10,first_line_space)
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
                               "open",offsetof(S12,open),
                               "align",offsetof(S12,align)
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
                               "format",offsetof(S13,format),
                               "list",offsetof(S13,list)
                              );
        }
       return ret;

       case 6 :
        {
         indexes[5]=struct_node->index;
         ind_map[struct_node->index]=6;

         ret.set<S6>();

         DDL::SetFieldOffsets(struct_node,
                               "body",offsetof(S6,body),
                               "format",offsetof(S6,format),
                               "ref",offsetof(S6,ref)
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
                               "open",offsetof(S14,open),
                               "frame",offsetof(S14,frame)
                              );
        }
       return ret;

       case 18 :
        {
         indexes[17]=struct_node->index;
         ind_map[struct_node->index]=18;

         ret.set<S18>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S18,name),
                               "open",offsetof(S18,open),
                               "border",offsetof(S18,border),
                               "hard",offsetof(S18,hard),
                               "width",offsetof(S18,width),
                               "table",offsetof(S18,table)
                              );
        }
       return ret;

       case 27 :
        {
         indexes[26]=struct_node->index;
         ind_map[struct_node->index]=27;

         ret.set<S27>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S27,name),
                               "open",offsetof(S27,open),
                               "span_x",offsetof(S27,span_x),
                               "span_y",offsetof(S27,span_y),
                               "list",offsetof(S27,list)
                              );
        }
       return ret;

       case 29 :
        {
         indexes[28]=struct_node->index;
         ind_map[struct_node->index]=29;

         ret.set<S29>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S29,name),
                               "open",offsetof(S29,open),
                               "space",offsetof(S29,space),
                               "width",offsetof(S29,width),
                               "line",offsetof(S29,line)
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
                               "format",offsetof(S32,format),
                               "bullet_space",offsetof(S32,bullet_space),
                               "item_space",offsetof(S32,item_space),
                               "frame_inner",offsetof(S32,frame_inner),
                               "frame_outer",offsetof(S32,frame_outer),
                               "text_format",offsetof(S32,text_format),
                               "placement",offsetof(S32,placement),
                               "list",offsetof(S32,list)
                              );
        }
       return ret;

       case 31 :
        {
         indexes[30]=struct_node->index;
         ind_map[struct_node->index]=31;

         ret.set<S31>();

         DDL::SetFieldOffsets(struct_node,
                               "list",offsetof(S31,list),
                               "cur",offsetof(S31,cur)
                              );
        }
       return ret;

       case 30 :
        {
         indexes[29]=struct_node->index;
         ind_map[struct_node->index]=30;

         ret.set<S30>();

         DDL::SetFieldOffsets(struct_node,
                               "bullet",offsetof(S30,bullet),
                               "list",offsetof(S30,list)
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
                               "open",offsetof(S33,open),
                               "title",offsetof(S33,title),
                               "format",offsetof(S33,format),
                               "openlist",offsetof(S33,openlist),
                               "hide",offsetof(S33,hide),
                               "list",offsetof(S33,list)
                              );
        }
       return ret;

       case 34 :
        {
         indexes[33]=struct_node->index;
         ind_map[struct_node->index]=34;

         ret.set<S34>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S34,name),
                               "file_name",offsetof(S34,file_name)
                              );
        }
       return ret;

       case 35 :
        {
         indexes[34]=struct_node->index;
         ind_map[struct_node->index]=35;

         ret.set<S35>();

         DDL::SetFieldOffsets(struct_node,
                               "open",offsetof(S35,open),
                               "comment",offsetof(S35,comment),
                               "list",offsetof(S35,list)
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
                               "defs",offsetof(S37,defs),
                               "list",offsetof(S37,list)
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
                               "title",offsetof(S39,title),
                               "back",offsetof(S39,back),
                               "fore",offsetof(S39,fore),
                               "up",offsetof(S39,up),
                               "prev",offsetof(S39,prev),
                               "next",offsetof(S39,next),
                               "list",offsetof(S39,list)
                              );
        }
       return ret;

       case 26 :
        {
         indexes[25]=struct_node->index;
         ind_map[struct_node->index]=26;

         ret.set<S26>();

         DDL::SetFieldOffsets(struct_node,
                               "list",offsetof(S26,list),
                               "cur",offsetof(S26,cur)
                              );
        }
       return ret;

       case 25 :
        {
         indexes[24]=struct_node->index;
         ind_map[struct_node->index]=25;

         ret.set<S25>();

         DDL::SetFieldOffsets(struct_node,
                               "inner",offsetof(S25,inner),
                               "outer",offsetof(S25,outer),
                               "col",offsetof(S25,col),
                               "line",offsetof(S25,line),
                               "body",offsetof(S25,body)
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
                               "open",offsetof(S40,open),
                               "width",offsetof(S40,width),
                               "gray",offsetof(S40,gray),
                               "snow",offsetof(S40,snow)
                              );
        }
       return ret;

       case 41 :
        {
         indexes[40]=struct_node->index;
         ind_map[struct_node->index]=41;

         ret.set<S41>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S41,name),
                               "open",offsetof(S41,open),
                               "width",offsetof(S41,width),
                               "line",offsetof(S41,line)
                              );
        }
       return ret;

       case 44 :
        {
         indexes[43]=struct_node->index;
         ind_map[struct_node->index]=44;

         ret.set<S44>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S44,name),
                               "open",offsetof(S44,open),
                               "font",offsetof(S44,font),
                               "back",offsetof(S44,back),
                               "fore",offsetof(S44,fore),
                               "effect",offsetof(S44,effect)
                              );
        }
       return ret;

       case 46 :
        {
         indexes[45]=struct_node->index;
         ind_map[struct_node->index]=46;

         ret.set<S46>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S46,name),
                               "open",offsetof(S46,open),
                               "face",offsetof(S46,face),
                               "size",offsetof(S46,size),
                               "bold",offsetof(S46,bold),
                               "italic",offsetof(S46,italic),
                               "strength",offsetof(S46,strength)
                              );
        }
       return ret;

       case 47 :
        {
         indexes[46]=struct_node->index;
         ind_map[struct_node->index]=47;

         ret.set<S47>();

         DDL::SetFieldOffsets(struct_node,
                               "title",offsetof(S47,title),
                               "back",offsetof(S47,back),
                               "fore",offsetof(S47,fore),
                               "start",offsetof(S47,start),
                               "defs",offsetof(S47,defs),
                               "list",offsetof(S47,list)
                              );
        }
       return ret;

       case 36 :
        {
         indexes[35]=struct_node->index;
         ind_map[struct_node->index]=36;

         ret.set<S36>();

         DDL::SetFieldOffsets(struct_node,
                               "inner",offsetof(S36,inner),
                               "outer",offsetof(S36,outer),
                               "bulletSpace",offsetof(S36,bulletSpace),
                               "itemSpace",offsetof(S36,itemSpace),
                               "collapseFormat",offsetof(S36,collapseFormat),
                               "bulletFormat",offsetof(S36,bulletFormat),
                               "border",offsetof(S36,border),
                               "textFormat",offsetof(S36,textFormat),
                               "fixedFormat",offsetof(S36,fixedFormat),
                               "placement",offsetof(S36,placement)
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

       case 5 :
        {
         indexes[4]=struct_node->index;
         ind_map[struct_node->index]=5;

         ret.set<S5>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S5,name),
                               "ptr",offsetof(S5,ptr)
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
                               "ptr",offsetof(S17,ptr)
                              );
        }
       return ret;

       case 15 :
        {
         indexes[14]=struct_node->index;
         ind_map[struct_node->index]=15;

         ret.set<S15>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S15,name),
                               "ptr",offsetof(S15,ptr)
                              );
        }
       return ret;

       case 4 :
        {
         indexes[3]=struct_node->index;
         ind_map[struct_node->index]=4;

         ret.set<S4>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S4,name),
                               "ptr",offsetof(S4,ptr)
                              );
        }
       return ret;

       case 24 :
        {
         indexes[23]=struct_node->index;
         ind_map[struct_node->index]=24;

         ret.set<S24>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S24,name),
                               "ptr",offsetof(S24,ptr)
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

       case 42 :
        {
         indexes[41]=struct_node->index;
         ind_map[struct_node->index]=42;

         ret.set<S42>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S42,name),
                               "ptr",offsetof(S42,ptr)
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
                               "ptr",offsetof(S38,ptr)
                              );
        }
       return ret;

       case 19 :
        {
         indexes[18]=struct_node->index;
         ind_map[struct_node->index]=19;

         ret.set<S19>();

         DDL::SetFieldOffsets(struct_node,
                               "def",offsetof(S19,def),
                               "data",offsetof(S19,data)
                              );
        }
       return ret;

       case 45 :
        {
         indexes[44]=struct_node->index;
         ind_map[struct_node->index]=45;

         ret.set<S45>();

         DDL::SetFieldOffsets(struct_node,
                               "def",offsetof(S45,def),
                               "data",offsetof(S45,data)
                              );
        }
       return ret;

       case 16 :
        {
         indexes[15]=struct_node->index;
         ind_map[struct_node->index]=16;

         ret.set<S16>();

         DDL::SetFieldOffsets(struct_node,
                               "def",offsetof(S16,def),
                               "data",offsetof(S16,data)
                              );
        }
       return ret;

       case 11 :
        {
         indexes[10]=struct_node->index;
         ind_map[struct_node->index]=11;

         ret.set<S11>();

         DDL::SetFieldOffsets(struct_node,
                               "def",offsetof(S11,def),
                               "data",offsetof(S11,data)
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

       case 28 :
        {
         indexes[27]=struct_node->index;
         ind_map[struct_node->index]=28;

         ret.set<S28>();

         DDL::SetFieldOffsets(struct_node,
                               "def",offsetof(S28,def),
                               "data",offsetof(S28,data)
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

       case 22 :
        {
         indexes[21]=struct_node->index;
         ind_map[struct_node->index]=22;

         ret.set<S22>();

         DDL::SetFieldOffsets(struct_node,
                               "def",offsetof(S22,def),
                               "data",offsetof(S22,data)
                              );
        }
       return ret;

       case 8 :
        {
         indexes[7]=struct_node->index;
         ind_map[struct_node->index]=8;

         ret.set<S8>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S8,a),
                               "b",offsetof(S8,b)
                              );
        }
       return ret;

       case 20 :
        {
         indexes[19]=struct_node->index;
         ind_map[struct_node->index]=20;

         ret.set<S20>();

         DDL::SetFieldOffsets(struct_node,
                               "x",offsetof(S20,x),
                               "y",offsetof(S20,y)
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
       case 1 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapPolyPtr< S46 , S44 , S41 , S40 , S39 , S33 , S32 , S29 , S27 , S18 , S14 , S13 , S12 , S10 , S7 >
                              >(*this,struct_node);
        }
       break;

       case 2 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText
                              >(*this,struct_node);
        }
       break;

       case 7 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A7,
                               S3,
                               S4,
                               DDL::MapRange< A1 >
                              >(*this,struct_node);
        }
       break;

       case 10 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A7,
                               S9,
                               S9
                              >(*this,struct_node);
        }
       break;

       case 12 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A7,
                               S11
                              >(*this,struct_node);
        }
       break;

       case 13 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A7,
                               S4,
                               DDL::MapRange< A1 >
                              >(*this,struct_node);
        }
       break;

       case 6 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               S4,
                               S5
                              >(*this,struct_node);
        }
       break;

       case 14 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A7,
                               DDL::MapPtr< S25 >
                              >(*this,struct_node);
        }
       break;

       case 18 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A7,
                               S15,
                               S16,
                               DDL::MapRange< A5 >,
                               DDL::MapRange< S17 >
                              >(*this,struct_node);
        }
       break;

       case 27 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A7,
                               S19,
                               S19,
                               S26
                              >(*this,struct_node);
        }
       break;

       case 29 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A7,
                               S28,
                               S9,
                               S22
                              >(*this,struct_node);
        }
       break;

       case 32 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A7,
                               S4,
                               S28,
                               S28,
                               S21,
                               S21,
                               S4,
                               S3,
                               S31
                              >(*this,struct_node);
        }
       break;

       case 31 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapRange< S30 >,
                               DDL::ulen_type
                              >(*this,struct_node);
        }
       break;

       case 30 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               S26
                              >(*this,struct_node);
        }
       break;

       case 33 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A7,
                               DDL::MapText,
                               S4,
                               A7,
                               S16,
                               S26
                              >(*this,struct_node);
        }
       break;

       case 34 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               DDL::MapText
                              >(*this,struct_node);
        }
       break;

       case 35 :
        {
         DDL::GuardFieldTypes<
                               A7,
                               DDL::MapText,
                               DDL::MapRange< A2 >
                              >(*this,struct_node);
        }
       break;

       case 37 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A7,
                               S36,
                               DDL::MapRange< A2 >
                              >(*this,struct_node);
        }
       break;

       case 39 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A7,
                               DDL::MapText,
                               S22,
                               S22,
                               S38,
                               S38,
                               S38,
                               S26
                              >(*this,struct_node);
        }
       break;

       case 26 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapRange< S25 >,
                               DDL::ulen_type
                              >(*this,struct_node);
        }
       break;

       case 25 :
        {
         DDL::GuardFieldTypes<
                               S21,
                               S21,
                               S22,
                               S23,
                               S24
                              >(*this,struct_node);
        }
       break;

       case 40 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A7,
                               S9,
                               S22,
                               S22
                              >(*this,struct_node);
        }
       break;

       case 41 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A7,
                               S9,
                               S22
                              >(*this,struct_node);
        }
       break;

       case 44 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A7,
                               S42,
                               S22,
                               S22,
                               S43
                              >(*this,struct_node);
        }
       break;

       case 46 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A7,
                               DDL::MapText,
                               A5,
                               S16,
                               S16,
                               S45
                              >(*this,struct_node);
        }
       break;

       case 47 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               S22,
                               S22,
                               S38,
                               S36,
                               DDL::MapRange< A2 >
                              >(*this,struct_node);
        }
       break;

       case 36 :
        {
         DDL::GuardFieldTypes<
                               S21,
                               S21,
                               S28,
                               S28,
                               DDL::MapPtr< S44 >,
                               DDL::MapPtr< S44 >,
                               DDL::MapPtr< S29 >,
                               DDL::MapPtr< S44 >,
                               DDL::MapPtr< S44 >,
                               DDL::MapPolyPtr< S12 , S10 >
                              >(*this,struct_node);
        }
       break;

       case 3 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               DDL::MapPolyPtr< S12 , S10 >
                              >(*this,struct_node);
        }
       break;

       case 5 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               DDL::MapPolyPtr< S14 , S39 >
                              >(*this,struct_node);
        }
       break;

       case 17 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               DDL::MapPtr< S27 >
                              >(*this,struct_node);
        }
       break;

       case 15 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               DDL::MapPtr< S29 >
                              >(*this,struct_node);
        }
       break;

       case 4 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               DDL::MapPtr< S44 >
                              >(*this,struct_node);
        }
       break;

       case 24 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               DDL::MapPolyPtr< S34 , S33 , S32 , S18 , S7 , S13 >
                              >(*this,struct_node);
        }
       break;

       case 23 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               DDL::MapPolyPtr< S41 , S40 >
                              >(*this,struct_node);
        }
       break;

       case 42 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               DDL::MapPtr< S46 >
                              >(*this,struct_node);
        }
       break;

       case 38 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               DDL::MapPtr< S39 >
                              >(*this,struct_node);
        }
       break;

       case 19 :
        {
         DDL::GuardFieldTypes<
                               A7,
                               DDL::ulen_type
                              >(*this,struct_node);
        }
       break;

       case 45 :
        {
         DDL::GuardFieldTypes<
                               A7,
                               DDL::sint_type
                              >(*this,struct_node);
        }
       break;

       case 16 :
        {
         DDL::GuardFieldTypes<
                               A7,
                               A7
                              >(*this,struct_node);
        }
       break;

       case 11 :
        {
         DDL::GuardFieldTypes<
                               A7,
                               A3
                              >(*this,struct_node);
        }
       break;

       case 43 :
        {
         DDL::GuardFieldTypes<
                               A7,
                               A4
                              >(*this,struct_node);
        }
       break;

       case 9 :
        {
         DDL::GuardFieldTypes<
                               A7,
                               S8
                              >(*this,struct_node);
        }
       break;

       case 28 :
        {
         DDL::GuardFieldTypes<
                               A7,
                               A5
                              >(*this,struct_node);
        }
       break;

       case 21 :
        {
         DDL::GuardFieldTypes<
                               A7,
                               S20
                              >(*this,struct_node);
        }
       break;

       case 22 :
        {
         DDL::GuardFieldTypes<
                               A7,
                               A6
                              >(*this,struct_node);
        }
       break;

       case 8 :
        {
         DDL::GuardFieldTypes<
                               A5,
                               A5
                              >(*this,struct_node);
        }
       break;

       case 20 :
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

  void erase(Place<void> place,DDL::StructNode *struct_node) const
   {
    switch( ind_map[struct_node->index] )
      {
       case 25 :
        {
         S25 *obj=place;

         obj->ext=0;
        }
       break;
      }
   }
 };

template <class T>
struct TypeSet::IsStruct
 {
  static bool Do(const ulen *,ulen) { return false; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S1>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[0]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S2>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[1]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S7>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[6]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S10>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[9]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S12>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[11]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S13>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[12]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S6>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[5]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S14>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[13]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S18>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[17]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S27>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[26]; }
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
struct TypeSet::IsStruct<TypeDefCore::S35>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[34]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S37>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[36]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S39>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[38]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S26>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[25]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S25>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[24]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S40>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[39]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S41>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[40]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S44>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[43]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S46>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[45]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S47>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[46]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S36>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[35]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S3>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[2]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S5>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[4]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S17>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[16]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S15>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[14]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S4>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[3]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S24>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[23]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S23>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[22]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S42>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[41]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S38>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[37]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S19>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[18]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S45>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[44]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S16>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[15]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S11>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[10]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S43>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[42]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S9>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[8]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S28>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[27]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S21>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[20]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S22>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[21]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S8>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[7]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S20>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[19]; }
 };

