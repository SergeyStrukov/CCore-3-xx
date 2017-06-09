/* struct TypeSet */

struct TypeSet : TypeDefCore
 {
  ulen indexes[3];
  DynArray<ulen> ind_map;

  DDL::FindNodeMap map;

  explicit TypeSet(ulen len)
   : ind_map(len)
   {
    Range(indexes).set(ulen(-1));

    map.add(3,"PTPSecureConfig");
    map.add(2,"Client");
    map.add(1,"Key");

    map.complete();
   }

  DDL::MapSizeInfo structSizeInfo(DDL::StructNode *struct_node)
   {
    DDL::MapSizeInfo ret;

    switch( map.find(struct_node) )
      {
       case 3 :
        {
         indexes[2]=struct_node->index;
         ind_map[struct_node->index]=3;

         ret.set<S3>();

         DDL::SetFieldOffsets(struct_node,
                               "pke_port",offsetof(S3,pke_port),
                               "psec_port",offsetof(S3,psec_port),
                               "keyset_len",offsetof(S3,keyset_len),
                               "ttl",offsetof(S3,ttl),
                               "utl",offsetof(S3,utl),
                               "max_clients",offsetof(S3,max_clients),
                               "root",offsetof(S3,root),
                               "server_key",offsetof(S3,server_key),
                               "admin_name",offsetof(S3,admin_name),
                               "admin_key",offsetof(S3,admin_key),
                               "clients",offsetof(S3,clients)
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
                               "key",offsetof(S2,key),
                               "access_read",offsetof(S2,access_read),
                               "access_write",offsetof(S2,access_write),
                               "has_home",offsetof(S2,has_home)
                              );
        }
       return ret;

       case 1 :
        {
         indexes[0]=struct_node->index;
         ind_map[struct_node->index]=1;

         ret.set<S1>();

         DDL::SetFieldOffsets(struct_node,
                               "hash_id",offsetof(S1,hash_id),
                               "key",offsetof(S1,key)
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
       case 3 :
        {
         DDL::GuardFieldTypes<
                               uint16,
                               uint16,
                               uint16,
                               uint32,
                               uint32,
                               uint32,
                               DDL::MapText,
                               S1,
                               DDL::MapText,
                               S1,
                               DDL::MapRange< S2 >
                              >(*this,struct_node);
        }
       break;

       case 2 :
        {
         DDL::GuardFieldTypes<
                               DDL::MapText,
                               S1,
                               A1,
                               A1,
                               A1
                              >(*this,struct_node);
        }
       break;

       case 1 :
        {
         DDL::GuardFieldTypes<
                               uint8,
                               DDL::MapRange< uint8 >
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
struct TypeSet::IsStruct<TypeDefCore::S3>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[2]; }
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

