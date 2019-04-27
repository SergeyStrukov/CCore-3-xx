/* struct TypeSet */

struct TypeSet : TypeDefCore
 {
  ulen indexes[52];
  DynArray<ulen> ind_map;

  DDL::FindNodeMap map;

  explicit TypeSet(ulen len)
   : ind_map(len)
   {
    Range(indexes).set(ulen(-1));

    map.add(4,"Contour");
    map.add(3,"Formula");
    map.add(5,"SolidOf");
    map.add(6,"BLoopOf");
    map.add(7,"LoopOf");
    map.add(8,"BPathOf");
    map.add(9,"PathOf");
    map.add(10,"StepOf");
    map.add(11,"Right");
    map.add(12,"Left");
    map.add(13,"Down");
    map.add(14,"Up");
    map.add(15,"Second");
    map.add(16,"First");
    map.add(17,"Mirror");
    map.add(18,"MoveLen");
    map.add(19,"Move");
    map.add(20,"RotateOrt");
    map.add(21,"Rotate");
    map.add(22,"MeetCircles");
    map.add(23,"MeetCircle");
    map.add(24,"Meet");
    map.add(25,"AngleC");
    map.add(26,"Proj");
    map.add(27,"CircleOuter");
    map.add(28,"CircleOf");
    map.add(29,"MidOrt");
    map.add(30,"Part");
    map.add(31,"Middle");
    map.add(32,"LineOf");
    map.add(33,"AngleOf");
    map.add(34,"LengthOf");
    map.add(35,"Div");
    map.add(36,"Mul");
    map.add(37,"Sub");
    map.add(38,"Add");
    map.add(39,"Neg");
    map.add(2,"Pad");
    map.add(43,"Solid");
    map.add(44,"Loop");
    map.add(45,"Path");
    map.add(46,"Step");
    map.add(42,"Dot");
    map.add(47,"Couple");
    map.add(49,"Circle");
    map.add(50,"Line");
    map.add(41,"Point");
    map.add(51,"Angle");
    map.add(48,"Length");
    map.add(52,"Ratio");
    map.add(40,"Real");
    map.add(1,"Label");

    map.complete();
   }

  DDL::MapSizeInfo structSizeInfo(DDL::StructNode *struct_node)
   {
    DDL::MapSizeInfo ret;

    switch( map.find(struct_node) )
      {
       case 4 :
        {
         indexes[3]=struct_node->index;
         ind_map[struct_node->index]=4;

         ret.set<S4>();

         DDL::SetFieldOffsets(struct_node,
                               "pads",offsetof(S4,pads),
                               "formulas",offsetof(S4,formulas)
                              );
        }
       return ret;

       case 3 :
        {
         indexes[2]=struct_node->index;
         ind_map[struct_node->index]=3;

         ret.set<S3>();

         DDL::SetFieldOffsets(struct_node,
                               "label",offsetof(S3,label),
                               "index",offsetof(S3,index),
                               "object",offsetof(S3,object)
                              );
        }
       return ret;

       case 5 :
        {
         indexes[4]=struct_node->index;
         ind_map[struct_node->index]=5;

         ret.set<S5>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S5,a)
                              );
        }
       return ret;

       case 6 :
        {
         indexes[5]=struct_node->index;
         ind_map[struct_node->index]=6;

         ret.set<S6>();

         DDL::SetFieldOffsets(struct_node,
                               "args",offsetof(S6,args)
                              );
        }
       return ret;

       case 7 :
        {
         indexes[6]=struct_node->index;
         ind_map[struct_node->index]=7;

         ret.set<S7>();

         DDL::SetFieldOffsets(struct_node,
                               "args",offsetof(S7,args)
                              );
        }
       return ret;

       case 8 :
        {
         indexes[7]=struct_node->index;
         ind_map[struct_node->index]=8;

         ret.set<S8>();

         DDL::SetFieldOffsets(struct_node,
                               "args",offsetof(S8,args)
                              );
        }
       return ret;

       case 9 :
        {
         indexes[8]=struct_node->index;
         ind_map[struct_node->index]=9;

         ret.set<S9>();

         DDL::SetFieldOffsets(struct_node,
                               "args",offsetof(S9,args)
                              );
        }
       return ret;

       case 10 :
        {
         indexes[9]=struct_node->index;
         ind_map[struct_node->index]=10;

         ret.set<S10>();

         DDL::SetFieldOffsets(struct_node,
                               "args",offsetof(S10,args)
                              );
        }
       return ret;

       case 11 :
        {
         indexes[10]=struct_node->index;
         ind_map[struct_node->index]=11;

         ret.set<S11>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S11,a),
                               "b",offsetof(S11,b)
                              );
        }
       return ret;

       case 12 :
        {
         indexes[11]=struct_node->index;
         ind_map[struct_node->index]=12;

         ret.set<S12>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S12,a),
                               "b",offsetof(S12,b)
                              );
        }
       return ret;

       case 13 :
        {
         indexes[12]=struct_node->index;
         ind_map[struct_node->index]=13;

         ret.set<S13>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S13,a),
                               "b",offsetof(S13,b)
                              );
        }
       return ret;

       case 14 :
        {
         indexes[13]=struct_node->index;
         ind_map[struct_node->index]=14;

         ret.set<S14>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S14,a),
                               "b",offsetof(S14,b)
                              );
        }
       return ret;

       case 15 :
        {
         indexes[14]=struct_node->index;
         ind_map[struct_node->index]=15;

         ret.set<S15>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S15,a)
                              );
        }
       return ret;

       case 16 :
        {
         indexes[15]=struct_node->index;
         ind_map[struct_node->index]=16;

         ret.set<S16>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S16,a)
                              );
        }
       return ret;

       case 17 :
        {
         indexes[16]=struct_node->index;
         ind_map[struct_node->index]=17;

         ret.set<S17>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S17,a),
                               "b",offsetof(S17,b)
                              );
        }
       return ret;

       case 18 :
        {
         indexes[17]=struct_node->index;
         ind_map[struct_node->index]=18;

         ret.set<S18>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S18,a),
                               "b",offsetof(S18,b),
                               "c",offsetof(S18,c)
                              );
        }
       return ret;

       case 19 :
        {
         indexes[18]=struct_node->index;
         ind_map[struct_node->index]=19;

         ret.set<S19>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S19,a),
                               "b",offsetof(S19,b),
                               "c",offsetof(S19,c)
                              );
        }
       return ret;

       case 20 :
        {
         indexes[19]=struct_node->index;
         ind_map[struct_node->index]=20;

         ret.set<S20>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S20,a),
                               "b",offsetof(S20,b)
                              );
        }
       return ret;

       case 21 :
        {
         indexes[20]=struct_node->index;
         ind_map[struct_node->index]=21;

         ret.set<S21>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S21,a),
                               "b",offsetof(S21,b),
                               "c",offsetof(S21,c)
                              );
        }
       return ret;

       case 22 :
        {
         indexes[21]=struct_node->index;
         ind_map[struct_node->index]=22;

         ret.set<S22>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S22,a),
                               "b",offsetof(S22,b)
                              );
        }
       return ret;

       case 23 :
        {
         indexes[22]=struct_node->index;
         ind_map[struct_node->index]=23;

         ret.set<S23>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S23,a),
                               "b",offsetof(S23,b)
                              );
        }
       return ret;

       case 24 :
        {
         indexes[23]=struct_node->index;
         ind_map[struct_node->index]=24;

         ret.set<S24>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S24,a),
                               "b",offsetof(S24,b)
                              );
        }
       return ret;

       case 25 :
        {
         indexes[24]=struct_node->index;
         ind_map[struct_node->index]=25;

         ret.set<S25>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S25,a),
                               "b",offsetof(S25,b),
                               "c",offsetof(S25,c)
                              );
        }
       return ret;

       case 26 :
        {
         indexes[25]=struct_node->index;
         ind_map[struct_node->index]=26;

         ret.set<S26>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S26,a),
                               "b",offsetof(S26,b)
                              );
        }
       return ret;

       case 27 :
        {
         indexes[26]=struct_node->index;
         ind_map[struct_node->index]=27;

         ret.set<S27>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S27,a),
                               "b",offsetof(S27,b),
                               "c",offsetof(S27,c)
                              );
        }
       return ret;

       case 28 :
        {
         indexes[27]=struct_node->index;
         ind_map[struct_node->index]=28;

         ret.set<S28>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S28,a),
                               "b",offsetof(S28,b)
                              );
        }
       return ret;

       case 29 :
        {
         indexes[28]=struct_node->index;
         ind_map[struct_node->index]=29;

         ret.set<S29>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S29,a),
                               "b",offsetof(S29,b)
                              );
        }
       return ret;

       case 30 :
        {
         indexes[29]=struct_node->index;
         ind_map[struct_node->index]=30;

         ret.set<S30>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S30,a),
                               "b",offsetof(S30,b),
                               "c",offsetof(S30,c)
                              );
        }
       return ret;

       case 31 :
        {
         indexes[30]=struct_node->index;
         ind_map[struct_node->index]=31;

         ret.set<S31>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S31,a),
                               "b",offsetof(S31,b)
                              );
        }
       return ret;

       case 32 :
        {
         indexes[31]=struct_node->index;
         ind_map[struct_node->index]=32;

         ret.set<S32>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S32,a),
                               "b",offsetof(S32,b)
                              );
        }
       return ret;

       case 33 :
        {
         indexes[32]=struct_node->index;
         ind_map[struct_node->index]=33;

         ret.set<S33>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S33,a),
                               "b",offsetof(S33,b),
                               "c",offsetof(S33,c)
                              );
        }
       return ret;

       case 34 :
        {
         indexes[33]=struct_node->index;
         ind_map[struct_node->index]=34;

         ret.set<S34>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S34,a),
                               "b",offsetof(S34,b)
                              );
        }
       return ret;

       case 35 :
        {
         indexes[34]=struct_node->index;
         ind_map[struct_node->index]=35;

         ret.set<S35>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S35,a),
                               "b",offsetof(S35,b)
                              );
        }
       return ret;

       case 36 :
        {
         indexes[35]=struct_node->index;
         ind_map[struct_node->index]=36;

         ret.set<S36>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S36,a),
                               "b",offsetof(S36,b)
                              );
        }
       return ret;

       case 37 :
        {
         indexes[36]=struct_node->index;
         ind_map[struct_node->index]=37;

         ret.set<S37>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S37,a),
                               "b",offsetof(S37,b)
                              );
        }
       return ret;

       case 38 :
        {
         indexes[37]=struct_node->index;
         ind_map[struct_node->index]=38;

         ret.set<S38>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S38,a),
                               "b",offsetof(S38,b)
                              );
        }
       return ret;

       case 39 :
        {
         indexes[38]=struct_node->index;
         ind_map[struct_node->index]=39;

         ret.set<S39>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S39,a)
                              );
        }
       return ret;

       case 2 :
        {
         indexes[1]=struct_node->index;
         ind_map[struct_node->index]=2;

         ret.set<S2>();

         DDL::SetFieldOffsets(struct_node,
                               "label",offsetof(S2,label),
                               "index",offsetof(S2,index),
                               "object",offsetof(S2,object)
                              );
        }
       return ret;

       case 43 :
        {
         indexes[42]=struct_node->index;
         ind_map[struct_node->index]=43;

         ret.set<S43>();

         DDL::SetFieldOffsets(struct_node,
                               "dots",offsetof(S43,dots),
                               "rex",offsetof(S43,rex)
                              );
        }
       return ret;

       case 44 :
        {
         indexes[43]=struct_node->index;
         ind_map[struct_node->index]=44;

         ret.set<S44>();

         DDL::SetFieldOffsets(struct_node,
                               "dots",offsetof(S44,dots),
                               "rex",offsetof(S44,rex)
                              );
        }
       return ret;

       case 45 :
        {
         indexes[44]=struct_node->index;
         ind_map[struct_node->index]=45;

         ret.set<S45>();

         DDL::SetFieldOffsets(struct_node,
                               "dots",offsetof(S45,dots),
                               "rex",offsetof(S45,rex)
                              );
        }
       return ret;

       case 46 :
        {
         indexes[45]=struct_node->index;
         ind_map[struct_node->index]=46;

         ret.set<S46>();

         DDL::SetFieldOffsets(struct_node,
                               "points",offsetof(S46,points),
                               "rex",offsetof(S46,rex)
                              );
        }
       return ret;

       case 42 :
        {
         indexes[41]=struct_node->index;
         ind_map[struct_node->index]=42;

         ret.set<S42>();

         DDL::SetFieldOffsets(struct_node,
                               "point",offsetof(S42,point),
                               "break_flag",offsetof(S42,break_flag)
                              );
        }
       return ret;

       case 47 :
        {
         indexes[46]=struct_node->index;
         ind_map[struct_node->index]=47;

         ret.set<S47>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S47,a),
                               "b",offsetof(S47,b),
                               "rex",offsetof(S47,rex)
                              );
        }
       return ret;

       case 49 :
        {
         indexes[48]=struct_node->index;
         ind_map[struct_node->index]=49;

         ret.set<S49>();

         DDL::SetFieldOffsets(struct_node,
                               "center",offsetof(S49,center),
                               "radius",offsetof(S49,radius),
                               "rex",offsetof(S49,rex)
                              );
        }
       return ret;

       case 50 :
        {
         indexes[49]=struct_node->index;
         ind_map[struct_node->index]=50;

         ret.set<S50>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S50,a),
                               "ort",offsetof(S50,ort),
                               "rex",offsetof(S50,rex)
                              );
        }
       return ret;

       case 41 :
        {
         indexes[40]=struct_node->index;
         ind_map[struct_node->index]=41;

         ret.set<S41>();

         DDL::SetFieldOffsets(struct_node,
                               "x",offsetof(S41,x),
                               "y",offsetof(S41,y),
                               "rex",offsetof(S41,rex)
                              );
        }
       return ret;

       case 51 :
        {
         indexes[50]=struct_node->index;
         ind_map[struct_node->index]=51;

         ret.set<S51>();

         DDL::SetFieldOffsets(struct_node,
                               "val",offsetof(S51,val),
                               "rex",offsetof(S51,rex)
                              );
        }
       return ret;

       case 48 :
        {
         indexes[47]=struct_node->index;
         ind_map[struct_node->index]=48;

         ret.set<S48>();

         DDL::SetFieldOffsets(struct_node,
                               "val",offsetof(S48,val),
                               "rex",offsetof(S48,rex)
                              );
        }
       return ret;

       case 52 :
        {
         indexes[51]=struct_node->index;
         ind_map[struct_node->index]=52;

         ret.set<S52>();

         DDL::SetFieldOffsets(struct_node,
                               "val",offsetof(S52,val),
                               "rex",offsetof(S52,rex)
                              );
        }
       return ret;

       case 40 :
        {
         indexes[39]=struct_node->index;
         ind_map[struct_node->index]=40;

         ret.set<S40>();

         DDL::SetFieldOffsets(struct_node,
                               "mantissa",offsetof(S40,mantissa),
                               "exp",offsetof(S40,exp)
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
                               "show",offsetof(S1,show),
                               "gray",offsetof(S1,gray),
                               "show_name",offsetof(S1,show_name)
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
       case 4 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapRange< S2 >,
                               DDL::MapRange< S3 >
                              >(*this,struct_node);
        }
       break;

       case 3 :
        {
         DDL::GuardFieldTypes<
                               S1,
                               DDL::ulen_type,
                               A1
                              >(*this,struct_node);
        }
       break;

       case 5 :
        {
         DDL::GuardFieldTypes<
                               A1
                              >(*this,struct_node);
        }
       break;

       case 6 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapRange< A1 >
                              >(*this,struct_node);
        }
       break;

       case 7 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapRange< A1 >
                              >(*this,struct_node);
        }
       break;

       case 8 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapRange< A1 >
                              >(*this,struct_node);
        }
       break;

       case 9 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapRange< A1 >
                              >(*this,struct_node);
        }
       break;

       case 10 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapRange< A1 >
                              >(*this,struct_node);
        }
       break;

       case 11 :
        {
         DDL::GuardFieldTypes<
                               A1,
                               A1
                              >(*this,struct_node);
        }
       break;

       case 12 :
        {
         DDL::GuardFieldTypes<
                               A1,
                               A1
                              >(*this,struct_node);
        }
       break;

       case 13 :
        {
         DDL::GuardFieldTypes<
                               A1,
                               A1
                              >(*this,struct_node);
        }
       break;

       case 14 :
        {
         DDL::GuardFieldTypes<
                               A1,
                               A1
                              >(*this,struct_node);
        }
       break;

       case 15 :
        {
         DDL::GuardFieldTypes<
                               A1
                              >(*this,struct_node);
        }
       break;

       case 16 :
        {
         DDL::GuardFieldTypes<
                               A1
                              >(*this,struct_node);
        }
       break;

       case 17 :
        {
         DDL::GuardFieldTypes<
                               A1,
                               A1
                              >(*this,struct_node);
        }
       break;

       case 18 :
        {
         DDL::GuardFieldTypes<
                               A1,
                               A1,
                               A1
                              >(*this,struct_node);
        }
       break;

       case 19 :
        {
         DDL::GuardFieldTypes<
                               A1,
                               A1,
                               A1
                              >(*this,struct_node);
        }
       break;

       case 20 :
        {
         DDL::GuardFieldTypes<
                               A1,
                               A1
                              >(*this,struct_node);
        }
       break;

       case 21 :
        {
         DDL::GuardFieldTypes<
                               A1,
                               A1,
                               A1
                              >(*this,struct_node);
        }
       break;

       case 22 :
        {
         DDL::GuardFieldTypes<
                               A1,
                               A1
                              >(*this,struct_node);
        }
       break;

       case 23 :
        {
         DDL::GuardFieldTypes<
                               A1,
                               A1
                              >(*this,struct_node);
        }
       break;

       case 24 :
        {
         DDL::GuardFieldTypes<
                               A1,
                               A1
                              >(*this,struct_node);
        }
       break;

       case 25 :
        {
         DDL::GuardFieldTypes<
                               A1,
                               A1,
                               A1
                              >(*this,struct_node);
        }
       break;

       case 26 :
        {
         DDL::GuardFieldTypes<
                               A1,
                               A1
                              >(*this,struct_node);
        }
       break;

       case 27 :
        {
         DDL::GuardFieldTypes<
                               A1,
                               A1,
                               A1
                              >(*this,struct_node);
        }
       break;

       case 28 :
        {
         DDL::GuardFieldTypes<
                               A1,
                               A1
                              >(*this,struct_node);
        }
       break;

       case 29 :
        {
         DDL::GuardFieldTypes<
                               A1,
                               A1
                              >(*this,struct_node);
        }
       break;

       case 30 :
        {
         DDL::GuardFieldTypes<
                               A1,
                               A1,
                               A1
                              >(*this,struct_node);
        }
       break;

       case 31 :
        {
         DDL::GuardFieldTypes<
                               A1,
                               A1
                              >(*this,struct_node);
        }
       break;

       case 32 :
        {
         DDL::GuardFieldTypes<
                               A1,
                               A1
                              >(*this,struct_node);
        }
       break;

       case 33 :
        {
         DDL::GuardFieldTypes<
                               A1,
                               A1,
                               A1
                              >(*this,struct_node);
        }
       break;

       case 34 :
        {
         DDL::GuardFieldTypes<
                               A1,
                               A1
                              >(*this,struct_node);
        }
       break;

       case 35 :
        {
         DDL::GuardFieldTypes<
                               A1,
                               A1
                              >(*this,struct_node);
        }
       break;

       case 36 :
        {
         DDL::GuardFieldTypes<
                               A1,
                               A1
                              >(*this,struct_node);
        }
       break;

       case 37 :
        {
         DDL::GuardFieldTypes<
                               A1,
                               A1
                              >(*this,struct_node);
        }
       break;

       case 38 :
        {
         DDL::GuardFieldTypes<
                               A1,
                               A1
                              >(*this,struct_node);
        }
       break;

       case 39 :
        {
         DDL::GuardFieldTypes<
                               A1
                              >(*this,struct_node);
        }
       break;

       case 2 :
        {
         DDL::GuardFieldTypes<
                               S1,
                               DDL::ulen_type,
                               DDL::MapPolyPtr< S52 , S48 , S51 , S41 >
                              >(*this,struct_node);
        }
       break;

       case 43 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapRange< S42 >,
                               A2
                              >(*this,struct_node);
        }
       break;

       case 44 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapRange< S42 >,
                               A2
                              >(*this,struct_node);
        }
       break;

       case 45 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapRange< S42 >,
                               A2
                              >(*this,struct_node);
        }
       break;

       case 46 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapRange< S41 >,
                               A2
                              >(*this,struct_node);
        }
       break;

       case 42 :
        {
         DDL::GuardFieldTypes<
                               S41,
                               A3
                              >(*this,struct_node);
        }
       break;

       case 47 :
        {
         DDL::GuardFieldTypes<
                               S41,
                               S41,
                               A2
                              >(*this,struct_node);
        }
       break;

       case 49 :
        {
         DDL::GuardFieldTypes<
                               S41,
                               S48,
                               A2
                              >(*this,struct_node);
        }
       break;

       case 50 :
        {
         DDL::GuardFieldTypes<
                               S41,
                               S41,
                               A2
                              >(*this,struct_node);
        }
       break;

       case 41 :
        {
         DDL::GuardFieldTypes<
                               S40,
                               S40,
                               A2
                              >(*this,struct_node);
        }
       break;

       case 51 :
        {
         DDL::GuardFieldTypes<
                               S40,
                               A2
                              >(*this,struct_node);
        }
       break;

       case 48 :
        {
         DDL::GuardFieldTypes<
                               S40,
                               A2
                              >(*this,struct_node);
        }
       break;

       case 52 :
        {
         DDL::GuardFieldTypes<
                               S40,
                               A2
                              >(*this,struct_node);
        }
       break;

       case 40 :
        {
         DDL::GuardFieldTypes<
                               sint64,
                               sint16
                              >(*this,struct_node);
        }
       break;

       case 1 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A3,
                               A3,
                               A3
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
struct TypeSet::IsStruct<TypeDefCore::S4>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[3]; }
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
struct TypeSet::IsStruct<TypeDefCore::S6>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[5]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S7>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[6]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S8>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[7]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S9>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[8]; }
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
struct TypeSet::IsStruct<TypeDefCore::S14>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[13]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S15>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[14]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S16>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[15]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S17>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[16]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S18>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[17]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S19>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[18]; }
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
struct TypeSet::IsStruct<TypeDefCore::S22>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[21]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S23>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[22]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S24>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[23]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S25>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[24]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S26>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[25]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S27>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[26]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S28>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[27]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S29>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[28]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S30>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[29]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S31>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[30]; }
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
struct TypeSet::IsStruct<TypeDefCore::S35>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[34]; }
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
struct TypeSet::IsStruct<TypeDefCore::S2>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[1]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S43>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[42]; }
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
struct TypeSet::IsStruct<TypeDefCore::S46>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[45]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S42>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[41]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S47>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[46]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S49>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[48]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S50>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[49]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S41>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[40]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S51>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[50]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S48>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[47]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S52>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[51]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S40>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[39]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S1>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[0]; }
 };

