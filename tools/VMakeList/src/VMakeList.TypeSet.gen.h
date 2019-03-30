/* struct TypeSet */

struct TypeSet : TypeDefCore
 {
  ulen indexes[1];
  DynArray<ulen> ind_map;

  DDL::FindNodeMap map;

  explicit TypeSet(ulen len)
   : ind_map(len)
   {
    Range(indexes).set(ulen(-1));

    map.add(1,"Param");

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
                               "CCORE_ROOT",offsetof(S1,CCORE_ROOT),
                               "CCORE_TARGET",offsetof(S1,CCORE_TARGET),
                               "OBJ_PATH",offsetof(S1,OBJ_PATH),
                               "SRC_PATH_LIST",offsetof(S1,SRC_PATH_LIST),
                               "CCOPT_EXTRA",offsetof(S1,CCOPT_EXTRA),
                               "LDOPT_EXTRA",offsetof(S1,LDOPT_EXTRA),
                               "TARGET",offsetof(S1,TARGET)
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
                               DDL::MapRange< DDL::MapText >,
                               DDL::MapRange< DDL::MapText >,
                               DDL::MapRange< DDL::MapText >,
                               DDL::MapText
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

