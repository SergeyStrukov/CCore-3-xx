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

    map.add(1,"Tools");
    map.add(2,"Param");

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
                               "CC",offsetof(S1,CC),
                               "AS",offsetof(S1,AS),
                               "LD",offsetof(S1,LD),
                               "AR",offsetof(S1,AR),
                               "RM",offsetof(S1,RM),
                               "CCOPT",offsetof(S1,CCOPT),
                               "ASOPT",offsetof(S1,ASOPT),
                               "LDOPT",offsetof(S1,LDOPT),
                               "LDOPT_DESKTOP",offsetof(S1,LDOPT_DESKTOP),
                               "CORELIB",offsetof(S1,CORELIB)
                              );
        }
       return ret;

       case 2 :
        {
         indexes[1]=struct_node->index;
         ind_map[struct_node->index]=2;

         ret.set<S2>();

         DDL::SetFieldOffsets(struct_node,
                               "CCORE_ROOT",offsetof(S2,CCORE_ROOT),
                               "CCORE_TARGET",offsetof(S2,CCORE_TARGET),
                               "OBJ_PATH",offsetof(S2,OBJ_PATH),
                               "SRC_PATH_LIST",offsetof(S2,SRC_PATH_LIST),
                               "CCOPT_EXTRA",offsetof(S2,CCOPT_EXTRA),
                               "ASOPT_EXTRA",offsetof(S2,ASOPT_EXTRA),
                               "LDOPT_EXTRA",offsetof(S2,LDOPT_EXTRA),
                               "TARGET",offsetof(S2,TARGET),
                               "target",offsetof(S2,target),
                               "tools",offsetof(S2,tools)
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
                               DDL::MapText,
                               DDL::MapText,
                               DDL::MapText,
                               DDL::MapText,
                               DDL::MapRange< DDL::MapText >,
                               DDL::MapRange< DDL::MapText >,
                               DDL::MapRange< DDL::MapText >,
                               DDL::MapRange< DDL::MapText >,
                               DDL::MapText
                              >(*this,struct_node);
        }
       break;

       case 2 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               DDL::MapText,
                               DDL::MapText,
                               DDL::MapRange< DDL::MapText >,
                               DDL::MapRange< DDL::MapText >,
                               DDL::MapRange< DDL::MapText >,
                               DDL::MapRange< DDL::MapText >,
                               DDL::MapText,
                               DDL::sint_type,
                               DDL::MapPtr< S1 >
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
struct TypeSet::IsStruct<TypeDefCore::S1>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[0]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S2>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[1]; }
 };

