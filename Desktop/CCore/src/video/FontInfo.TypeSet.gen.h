/* FontInfo.TypeSet.gen.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

/* struct TypeSet */

struct TypeSet : TypeDefCore
 {
  ulen indexes[2];
  DynArray<ulen> ind_map;

  DDL::FindNodeMap map;

  explicit TypeSet(ulen len)
   : ind_map(len)
   {
    Range(indexes).set(ulen(-1));

    map.add(2,"FontInfo");
    map.add(1,"FontSize");

    map.complete();
   }

  DDL::MapSizeInfo structSizeInfo(DDL::StructNode *struct_node)
   {
    DDL::MapSizeInfo ret;

    switch( map.find(struct_node) )
      {
       case 2 :
        {
         indexes[1]=struct_node->index;
         ind_map[struct_node->index]=2;

         ret.set<S2>();

         DDL::SetFieldOffsets(struct_node,
                               "file_name",offsetof(S2,file_name),
                               "family",offsetof(S2,family),
                               "style",offsetof(S2,style),
                               "scalable",offsetof(S2,scalable),
                               "monospace",offsetof(S2,monospace),
                               "italic",offsetof(S2,italic),
                               "bold",offsetof(S2,bold),
                               "def_size",offsetof(S2,def_size)
                              );
        }
       return ret;

       case 1 :
        {
         indexes[0]=struct_node->index;
         ind_map[struct_node->index]=1;

         ret.set<S1>();

         DDL::SetFieldOffsets(struct_node,
                               "min_dx",offsetof(S1,min_dx),
                               "max_dx",offsetof(S1,max_dx),
                               "dy",offsetof(S1,dy),
                               "by",offsetof(S1,by),
                               "dx0",offsetof(S1,dx0),
                               "dx1",offsetof(S1,dx1),
                               "skew",offsetof(S1,skew)
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
       case 2 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               DDL::MapText,
                               DDL::MapText,
                               A3,
                               A3,
                               A3,
                               A3,
                               S1
                              >(*this,struct_node);
        }
       break;

       case 1 :
        {
         DDL::GuardFieldTypes<
                               A2,
                               A2,
                               A2,
                               A2,
                               A2,
                               A2,
                               A2
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
struct TypeSet::IsStruct<TypeDefCore::S2>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[1]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S1>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[0]; }
 };

