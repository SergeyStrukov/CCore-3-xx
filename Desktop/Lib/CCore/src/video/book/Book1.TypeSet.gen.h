/* Book1.TypeSet.gen.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

/* struct TypeSet */

struct TypeSet : TypeDefCore
 {
  ulen indexes[22];
  DynArray<ulen> ind_map;

  DDL::FindNodeMap map;

  explicit TypeSet(ulen len)
   : ind_map(len)
   {
    Range(indexes).set(ulen(-1));

    map.add(1,"Book");
    map.add(4,"Page");
    map.add(3,"Frame");
    map.add(6,"DoubleLine");
    map.add(7,"SingleLine");
    map.add(8,"Table");
    map.add(9,"Border");
    map.add(10,"Cell");
    map.add(11,"Collapse");
    map.add(13,"TextList");
    map.add(12,"ListItem");
    map.add(14,"Bitmap");
    map.add(16,"FixedText");
    map.add(17,"Text");
    map.add(18,"MultiLine");
    map.add(19,"OneLine");
    map.add(20,"Link");
    map.add(15,"Span");
    map.add(21,"Format");
    map.add(22,"Font");
    map.add(5,"Ratio");
    map.add(2,"Point");

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
                               "title",offsetof(S1,title),
                               "start",offsetof(S1,start),
                               "back",offsetof(S1,back),
                               "fore",offsetof(S1,fore)
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
                               "list",offsetof(S4,list),
                               "back",offsetof(S4,back),
                               "fore",offsetof(S4,fore),
                               "up",offsetof(S4,up),
                               "prev",offsetof(S4,prev),
                               "next",offsetof(S4,next)
                              );
        }
       return ret;

       case 3 :
        {
         indexes[2]=struct_node->index;
         ind_map[struct_node->index]=3;

         ret.set<S3>();

         DDL::SetFieldOffsets(struct_node,
                               "body",offsetof(S3,body),
                               "line",offsetof(S3,line),
                               "inner",offsetof(S3,inner),
                               "outer",offsetof(S3,outer),
                               "col",offsetof(S3,col)
                              );
        }
       return ret;

       case 6 :
        {
         indexes[5]=struct_node->index;
         ind_map[struct_node->index]=6;

         ret.set<S6>();

         DDL::SetFieldOffsets(struct_node,
                               "width",offsetof(S6,width),
                               "gray",offsetof(S6,gray),
                               "snow",offsetof(S6,snow)
                              );
        }
       return ret;

       case 7 :
        {
         indexes[6]=struct_node->index;
         ind_map[struct_node->index]=7;

         ret.set<S7>();

         DDL::SetFieldOffsets(struct_node,
                               "width",offsetof(S7,width),
                               "line",offsetof(S7,line)
                              );
        }
       return ret;

       case 8 :
        {
         indexes[7]=struct_node->index;
         ind_map[struct_node->index]=8;

         ret.set<S8>();

         DDL::SetFieldOffsets(struct_node,
                               "width",offsetof(S8,width),
                               "rows",offsetof(S8,rows),
                               "border",offsetof(S8,border),
                               "hard",offsetof(S8,hard)
                              );
        }
       return ret;

       case 9 :
        {
         indexes[8]=struct_node->index;
         ind_map[struct_node->index]=9;

         ret.set<S9>();

         DDL::SetFieldOffsets(struct_node,
                               "space",offsetof(S9,space),
                               "width",offsetof(S9,width),
                               "line",offsetof(S9,line)
                              );
        }
       return ret;

       case 10 :
        {
         indexes[9]=struct_node->index;
         ind_map[struct_node->index]=10;

         ret.set<S10>();

         DDL::SetFieldOffsets(struct_node,
                               "list",offsetof(S10,list),
                               "span_x",offsetof(S10,span_x),
                               "span_y",offsetof(S10,span_y)
                              );
        }
       return ret;

       case 11 :
        {
         indexes[10]=struct_node->index;
         ind_map[struct_node->index]=11;

         ret.set<S11>();

         DDL::SetFieldOffsets(struct_node,
                               "title",offsetof(S11,title),
                               "list",offsetof(S11,list),
                               "collapse_fmt",offsetof(S11,collapse_fmt),
                               "open",offsetof(S11,open),
                               "hide",offsetof(S11,hide)
                              );
        }
       return ret;

       case 13 :
        {
         indexes[12]=struct_node->index;
         ind_map[struct_node->index]=13;

         ret.set<S13>();

         DDL::SetFieldOffsets(struct_node,
                               "list",offsetof(S13,list),
                               "bullet_fmt",offsetof(S13,bullet_fmt),
                               "bullet_space",offsetof(S13,bullet_space),
                               "item_space",offsetof(S13,item_space)
                              );
        }
       return ret;

       case 12 :
        {
         indexes[11]=struct_node->index;
         ind_map[struct_node->index]=12;

         ret.set<S12>();

         DDL::SetFieldOffsets(struct_node,
                               "bullet",offsetof(S12,bullet),
                               "list",offsetof(S12,list)
                              );
        }
       return ret;

       case 14 :
        {
         indexes[13]=struct_node->index;
         ind_map[struct_node->index]=14;

         ret.set<S14>();

         DDL::SetFieldOffsets(struct_node,
                               "file_name",offsetof(S14,file_name)
                              );
        }
       return ret;

       case 16 :
        {
         indexes[15]=struct_node->index;
         ind_map[struct_node->index]=16;

         ret.set<S16>();

         DDL::SetFieldOffsets(struct_node,
                               "list",offsetof(S16,list),
                               "fmt",offsetof(S16,fmt)
                              );
        }
       return ret;

       case 17 :
        {
         indexes[16]=struct_node->index;
         ind_map[struct_node->index]=17;

         ret.set<S17>();

         DDL::SetFieldOffsets(struct_node,
                               "list",offsetof(S17,list),
                               "fmt",offsetof(S17,fmt),
                               "placement",offsetof(S17,placement)
                              );
        }
       return ret;

       case 18 :
        {
         indexes[17]=struct_node->index;
         ind_map[struct_node->index]=18;

         ret.set<S18>();

         DDL::SetFieldOffsets(struct_node,
                               "line_space",offsetof(S18,line_space),
                               "first_line_space",offsetof(S18,first_line_space)
                              );
        }
       return ret;

       case 19 :
        {
         indexes[18]=struct_node->index;
         ind_map[struct_node->index]=19;

         ret.set<S19>();

         DDL::SetFieldOffsets(struct_node,
                               "align",offsetof(S19,align)
                              );
        }
       return ret;

       case 20 :
        {
         indexes[19]=struct_node->index;
         ind_map[struct_node->index]=20;

         ret.set<S20>();

         DDL::SetFieldOffsets(struct_node,
                               "page",offsetof(S20,page),
                               "index_list",offsetof(S20,index_list)
                              );
        }
       return ret;

       case 15 :
        {
         indexes[14]=struct_node->index;
         ind_map[struct_node->index]=15;

         ret.set<S15>();

         DDL::SetFieldOffsets(struct_node,
                               "body",offsetof(S15,body),
                               "fmt",offsetof(S15,fmt),
                               "ref",offsetof(S15,ref)
                              );
        }
       return ret;

       case 21 :
        {
         indexes[20]=struct_node->index;
         ind_map[struct_node->index]=21;

         ret.set<S21>();

         DDL::SetFieldOffsets(struct_node,
                               "font",offsetof(S21,font),
                               "back",offsetof(S21,back),
                               "fore",offsetof(S21,fore),
                               "effect",offsetof(S21,effect)
                              );
        }
       return ret;

       case 22 :
        {
         indexes[21]=struct_node->index;
         ind_map[struct_node->index]=22;

         ret.set<S22>();

         DDL::SetFieldOffsets(struct_node,
                               "face",offsetof(S22,face),
                               "size",offsetof(S22,size),
                               "bold",offsetof(S22,bold),
                               "italic",offsetof(S22,italic),
                               "strength",offsetof(S22,strength)
                              );
        }
       return ret;

       case 5 :
        {
         indexes[4]=struct_node->index;
         ind_map[struct_node->index]=5;

         ret.set<S5>();

         DDL::SetFieldOffsets(struct_node,
                               "a",offsetof(S5,a),
                               "b",offsetof(S5,b)
                              );
        }
       return ret;

       case 2 :
        {
         indexes[1]=struct_node->index;
         ind_map[struct_node->index]=2;

         ret.set<S2>();

         DDL::SetFieldOffsets(struct_node,
                               "x",offsetof(S2,x),
                               "y",offsetof(S2,y)
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
                               DDL::MapText,
                               DDL::MapPtr< S4 >,
                               A5,
                               A5
                              >(*this,struct_node);
        }
       break;

       case 4 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               DDL::MapRange< S3 >,
                               A5,
                               A5,
                               DDL::MapPtr< S4 >,
                               DDL::MapPtr< S4 >,
                               DDL::MapPtr< S4 >
                              >(*this,struct_node);
        }
       break;

       case 3 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapPolyPtr< S17 , S16 , S14 , S13 , S11 , S8 >,
                               DDL::MapPolyPtr< S7 , S6 >,
                               S2,
                               S2,
                               A5
                              >(*this,struct_node);
        }
       break;

       case 6 :
        {
         DDL::GuardFieldTypes<
                               S5,
                               A5,
                               A5
                              >(*this,struct_node);
        }
       break;

       case 7 :
        {
         DDL::GuardFieldTypes<
                               S5,
                               A5
                              >(*this,struct_node);
        }
       break;

       case 8 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapRange< A4 >,
                               DDL::MapRange< DDL::MapRange< DDL::MapPtr< S10 > > >,
                               DDL::MapPtr< S9 >,
                               A6
                              >(*this,struct_node);
        }
       break;

       case 9 :
        {
         DDL::GuardFieldTypes<
                               A4,
                               S5,
                               A5
                              >(*this,struct_node);
        }
       break;

       case 10 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapRange< S3 >,
                               DDL::ulen_type,
                               DDL::ulen_type
                              >(*this,struct_node);
        }
       break;

       case 11 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               DDL::MapRange< S3 >,
                               DDL::MapPtr< S21 >,
                               A6,
                               A6
                              >(*this,struct_node);
        }
       break;

       case 13 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapRange< S12 >,
                               DDL::MapPtr< S21 >,
                               A4,
                               A4
                              >(*this,struct_node);
        }
       break;

       case 12 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               DDL::MapRange< S3 >
                              >(*this,struct_node);
        }
       break;

       case 14 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText
                              >(*this,struct_node);
        }
       break;

       case 16 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapRange< A1 >,
                               DDL::MapPtr< S21 >
                              >(*this,struct_node);
        }
       break;

       case 17 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapRange< S15 >,
                               DDL::MapPtr< S21 >,
                               DDL::MapPolyPtr< S19 , S18 >
                              >(*this,struct_node);
        }
       break;

       case 18 :
        {
         DDL::GuardFieldTypes<
                               S5,
                               S5
                              >(*this,struct_node);
        }
       break;

       case 19 :
        {
         DDL::GuardFieldTypes<
                               A2
                              >(*this,struct_node);
        }
       break;

       case 20 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapPtr< S4 >,
                               DDL::MapRange< DDL::ulen_type >
                              >(*this,struct_node);
        }
       break;

       case 15 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               DDL::MapPtr< S21 >,
                               DDL::MapPolyPtr< S20 , S4 >
                              >(*this,struct_node);
        }
       break;

       case 21 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapPtr< S22 >,
                               A5,
                               A5,
                               A3
                              >(*this,struct_node);
        }
       break;

       case 22 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               A4,
                               A6,
                               A6,
                               DDL::sint_type
                              >(*this,struct_node);
        }
       break;

       case 5 :
        {
         DDL::GuardFieldTypes<
                               A4,
                               A4
                              >(*this,struct_node);
        }
       break;

       case 2 :
        {
         DDL::GuardFieldTypes<
                               A4,
                               A4
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
       case 3 :
        {
         S3 *obj=place;

         obj->ext=0;
        }
       break;
       case 14 :
        {
         S14 *obj=place;

         obj->ext=0;
        }
       break;
       case 22 :
        {
         S22 *obj=place;

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
struct TypeSet::IsStruct<TypeDefCore::S13>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[12]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S12>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[11]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S14>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[13]; }
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
struct TypeSet::IsStruct<TypeDefCore::S15>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[14]; }
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
struct TypeSet::IsStruct<TypeDefCore::S5>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[4]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S2>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[1]; }
 };

