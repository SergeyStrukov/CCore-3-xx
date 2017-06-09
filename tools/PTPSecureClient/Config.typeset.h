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

    map.add(2,"PTPSecureConfig");
    map.add(1,"Key");

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
                               "server_pke_port",offsetof(S2,server_pke_port),
                               "server_psec_port",offsetof(S2,server_psec_port),
                               "pke_port",offsetof(S2,pke_port),
                               "psec_port",offsetof(S2,psec_port),
                               "keyset_len",offsetof(S2,keyset_len),
                               "ttl",offsetof(S2,ttl),
                               "utl",offsetof(S2,utl),
                               "server_ip",offsetof(S2,server_ip),
                               "server_key",offsetof(S2,server_key),
                               "name",offsetof(S2,name),
                               "key",offsetof(S2,key)
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
       case 2 :
        {
         DDL::GuardFieldTypes<
                               uint16,
                               uint16,
                               uint16,
                               uint16,
                               uint16,
                               uint32,
                               uint32,
                               uint32,
                               S1,
                               DDL::MapText,
                               S1
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
struct TypeSet::IsStruct<TypeDefCore::S2>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[1]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S1>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[0]; }
 };

