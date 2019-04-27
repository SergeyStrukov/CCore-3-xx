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

    map.add(2,"AppState");
    map.add(1,"Place");

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
                               "place",offsetof(S2,place),
                               "recent_files",offsetof(S2,recent_files)
                              );
        }
       return ret;

       case 1 :
        {
         indexes[0]=struct_node->index;
         ind_map[struct_node->index]=1;

         ret.set<S1>();

         DDL::SetFieldOffsets(struct_node,
                               "x",offsetof(S1,x),
                               "y",offsetof(S1,y),
                               "dx",offsetof(S1,dx),
                               "dy",offsetof(S1,dy),
                               "ok",offsetof(S1,ok)
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
                               S1,
                               DDL::MapRange< DDL::MapText >
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
                               A1
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

