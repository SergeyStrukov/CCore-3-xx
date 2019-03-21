/* struct TypeSet */

struct TypeSet : TypeDefCore
 {
  ulen indexes[9];
  DynArray<ulen> ind_map;

  DDL::FindNodeMap map;

  explicit TypeSet(ulen len)
   : ind_map(len)
   {
    Range(indexes).set(ulen(-1));

    map.add(2,"Menu");
    map.add(1,"MenuItem");
    map.add(3,"Dep");
    map.add(4,"Rule");
    map.add(5,"VMake");
    map.add(7,"Cmd");
    map.add(8,"Exe");
    map.add(6,"Env");
    map.add(9,"Target");

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
                               "list",offsetof(S2,list)
                              );
        }
       return ret;

       case 1 :
        {
         indexes[0]=struct_node->index;
         ind_map[struct_node->index]=1;

         ret.set<S1>();

         DDL::SetFieldOffsets(struct_node,
                               "dst",offsetof(S1,dst),
                               "desc",offsetof(S1,desc),
                               "sub",offsetof(S1,sub)
                              );
        }
       return ret;

       case 3 :
        {
         indexes[2]=struct_node->index;
         ind_map[struct_node->index]=3;

         ret.set<S3>();

         DDL::SetFieldOffsets(struct_node,
                               "src",offsetof(S3,src),
                               "dst",offsetof(S3,dst)
                              );
        }
       return ret;

       case 4 :
        {
         indexes[3]=struct_node->index;
         ind_map[struct_node->index]=4;

         ret.set<S4>();

         DDL::SetFieldOffsets(struct_node,
                               "src",offsetof(S4,src),
                               "dst",offsetof(S4,dst),
                               "cmd",offsetof(S4,cmd)
                              );
        }
       return ret;

       case 5 :
        {
         indexes[4]=struct_node->index;
         ind_map[struct_node->index]=5;

         ret.set<S5>();

         DDL::SetFieldOffsets(struct_node,
                               "file",offsetof(S5,file),
                               "target",offsetof(S5,target),
                               "wdir",offsetof(S5,wdir),
                               "echo",offsetof(S5,echo)
                              );
        }
       return ret;

       case 7 :
        {
         indexes[6]=struct_node->index;
         ind_map[struct_node->index]=7;

         ret.set<S7>();

         DDL::SetFieldOffsets(struct_node,
                               "cmdline",offsetof(S7,cmdline),
                               "wdir",offsetof(S7,wdir),
                               "env",offsetof(S7,env),
                               "echo",offsetof(S7,echo)
                              );
        }
       return ret;

       case 8 :
        {
         indexes[7]=struct_node->index;
         ind_map[struct_node->index]=8;

         ret.set<S8>();

         DDL::SetFieldOffsets(struct_node,
                               "exe",offsetof(S8,exe),
                               "cmdline",offsetof(S8,cmdline),
                               "wdir",offsetof(S8,wdir),
                               "env",offsetof(S8,env),
                               "echo",offsetof(S8,echo)
                              );
        }
       return ret;

       case 6 :
        {
         indexes[5]=struct_node->index;
         ind_map[struct_node->index]=6;

         ret.set<S6>();

         DDL::SetFieldOffsets(struct_node,
                               "name",offsetof(S6,name),
                               "value",offsetof(S6,value)
                              );
        }
       return ret;

       case 9 :
        {
         indexes[8]=struct_node->index;
         ind_map[struct_node->index]=9;

         ret.set<S9>();

         DDL::SetFieldOffsets(struct_node,
                               "file",offsetof(S9,file)
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
                               DDL::MapRange< S1 >
                              >(*this,struct_node);
        }
       break;

       case 1 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapPtr< S9 >,
                               DDL::MapText,
                               DDL::MapRange< DDL::MapPtr< S1 > >
                              >(*this,struct_node);
        }
       break;

       case 3 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapRange< DDL::MapPtr< S9 > >,
                               DDL::MapRange< DDL::MapPtr< S9 > >
                              >(*this,struct_node);
        }
       break;

       case 4 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapRange< DDL::MapPtr< S9 > >,
                               DDL::MapRange< DDL::MapPtr< S9 > >,
                               DDL::MapRange< DDL::MapPolyPtr< S8 , S7 , S5 > >
                              >(*this,struct_node);
        }
       break;

       case 5 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               DDL::MapText,
                               DDL::MapText,
                               DDL::MapText
                              >(*this,struct_node);
        }
       break;

       case 7 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               DDL::MapText,
                               DDL::MapRange< S6 >,
                               DDL::MapText
                              >(*this,struct_node);
        }
       break;

       case 8 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               DDL::MapText,
                               DDL::MapText,
                               DDL::MapRange< S6 >,
                               DDL::MapText
                              >(*this,struct_node);
        }
       break;

       case 6 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               DDL::MapText
                              >(*this,struct_node);
        }
       break;

       case 9 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText
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
       case 1 :
        {
         S1 *obj=place;

         obj->ext=0;
        }
       break;
       case 9 :
        {
         S9 *obj=place;

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
struct TypeSet::IsStruct<TypeDefCore::S2>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[1]; }
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
struct TypeSet::IsStruct<TypeDefCore::S4>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[3]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S5>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[4]; }
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
struct TypeSet::IsStruct<TypeDefCore::S6>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[5]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S9>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[8]; }
 };

