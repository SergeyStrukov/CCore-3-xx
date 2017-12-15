/* Display.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: DDLDisplay 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/Display.h>

#include <CCore/inc/video/Layout.h>
#include <CCore/inc/video/SmoothDrawArt.h>

#include <CCore/inc/Printf.h>

#include <CCore/inc/algon/BinarySearch.h>

#include <CCore/inc/Exception.h>

namespace App {

/* class DDLFile */

void DDLFile::erase()
 {
  result=Null;

  engine.reset();

  updated.assert();
 }

DDLFile::DDLFile() noexcept
 : eout(64_KByte),
   engine(eout)
 {
 }

DDLFile::~DDLFile()
 {
 }

auto DDLFile::open(StrLen file_name) -> OpenResult
 {
  try
    {
     eout.cleanup();

     engine.purge();

     result=engine.process(file_name,Mutate<const char>(Range(pretext)));

     if( !result )
       {
        String str=eout.close();

        eout.cleanup();

        erase();

        return {str,false};
       }
     else
       {
        eout.cleanup();

        updated.assert();

        return {Null,true};
       }
    }
  catch(CatchType)
    {
     eout.cleanup();

     erase();

     return {"Exception"_def,false};
    }
 }

auto DDLFile::openPretext(StrLen file_name) -> OpenResult
 {
  try
    {
     FileToMem map(file_name);

     eout.cleanup();

     DDL::TextEngine engine(eout,Mutate<const char>(Range(map)));

     auto result=engine.process();

     if( !result )
       {
        String str=eout.close();

        eout.cleanup();

        updated.assert();

        return {str,false};
       }
     else
       {
        eout.cleanup();

        Swap(pretext,map);

        erase();

        return {Null,true};
       }
    }
  catch(CatchType)
    {
     eout.cleanup();

     updated.assert();

     return {"Exception"_def,false};
    }
 }

void DDLFile::noPretext()
 {
  FileToMem map;

  Swap(pretext,map);

  erase();
 }

/* struct uPoint */

Coord uPoint::BaseOf(ulen a,ulen b)
 {
  if( a<b ) return -Coord(b-a);

  return Coord(a-b);
 }

Point uPoint::baseOf(uPoint pos) const
 {
  return {BaseOf(x,pos.x),BaseOf(y,pos.y)};
 }

/* struct uPane */

bool uPane::intersect(uPane obj) const
 {
  if( size.noSize() || obj.size.noSize() ) return false;

  uPoint a=Sup(base,obj.base);
  uPoint b=Inf(base+size,obj.base+obj.size);

  return a<b;
 }

Pane uPane::baseOf(uPoint pos) const
 {
  return Pane(base.baseOf(pos),Coord(size.x),Coord(size.y));
 }

/* struct ValueTarget */

uPane ValueTarget::frame() const
 {
  if( !target ) return {};

  if( single ) return target->place;

  uPane ret;

  ret.base.x=parent->place.base.x;
  ret.size.x=parent->place.size.x;

  ret.base.y=row->y;
  ret.size.y=row->dy;

  return ret;
 }

/* struct ValueDesc */

class ValueDesc::IsScalar
 {
   bool ret = false ;

  public:

   operator bool() const { return ret; }

   void operator () (AnyType *) {}

   void operator () (StrSize *) { ret=true; }

   void operator () (PtrDesc *) { ret=true; }
 };

bool ValueDesc::isScalar() const
 {
  IsScalar ret;

  ElaborateAnyPtr(ret,ptr);

  return ret;
 }

/* class DDLView */

void DDLView::erase()
 {
  pool.erase();

  consts=Empty;

  field_name.erase();

  index_buf.erase();

  ptr_buf.erase();
 }

 // utils

void DDLView::SetTail(PtrLen<char> &ret,char ch)
 {
  ret.back(1)=ch;

  ret.len--;
 }

void DDLView::SetTail(PtrLen<char> &ret,StrLen str)
 {
  ret.suffix(str.len).copy(str.ptr);

  ret.len-=str.len;
 }

void DDLView::ProvideIndex(AnyType &obj,ulen index,ulen min_len)
 {
  if( ulen len=obj.getLen() )
    {
     if( index >= len ) obj.extend_default(index-len+1);
    }
  else
    {
     obj.extend_default(Max(min_len,LenAdd(index,1)));
    }
 }

class DDLView::GetStructNode
 {
   DDL::StructNode *struct_node = 0 ;

  public:

   explicit GetStructNode(DDL::TypeNode *type) { set(type); }

   auto operator + () const { return struct_node; }

   // operator ()

   void operator () (AnyType *) {}

   void operator () (DDL::AliasNode *node)
    {
     set(node->result_type);
    }

   void operator () (DDL::StructNode *node)
    {
     struct_node=node;
    }

   void operator () (DDL::TypeNode::Ref *ptr)
    {
     ElaborateAnyPtr(*this,ptr->ptr);
    }

   void operator () (DDL::TypeNode::Struct *ptr)
    {
     struct_node=ptr->struct_node;
    }

   // set

   void set(DDL::TypeNode *type)
    {
     ElaborateAnyPtr(*this,type->ptr);
    }
 };

 // string

StrLen DDLView::fieldName(ulen index,StrLen name)
 {
  if( !name )
    {
     Printf(Exception,"App::DDLView::fieldName(...) : internal");
    }

  ProvideIndex(field_name,index);

  StrLen &obj=field_name[index];

  if( !obj ) obj=pool.dup(name);

  return obj;
 }

StrLen DDLView::fieldName(DDL::StructNode *struct_node,ulen index)
 {
  auto cur=begin(struct_node->field_list);

  for(; index ;index--) ++cur;

  return fieldName(*cur);
 }

StrLen DDLView::buildName(DDL::ConstNode *node)
 {
  ULenSat len=node->name.name.str.len;

  {
   DDL::ScopeNode *scope=node->parent;

   for(ulen cnt=node->depth; cnt ;cnt--,scope=scope->parent)
     {
      len+=scope->name.name.str.len;
      len+=1u;
     }
  }

  if( len>MaxNameLen )
    {
     Printf(Exception,"App::DDLView::buildName(...) : too long constant name");
    }

  PtrLen<char> ret=pool.createArray_raw<char>(len.value);

  PtrLen<char> cur=ret;

  SetTail(cur,node->name.name.str);

  {
   DDL::ScopeNode *scope=node->parent;

   for(ulen cnt=node->depth; cnt ;cnt--,scope=scope->parent)
     {
      SetTail(cur,'#');
      SetTail(cur,scope->name.name.str);
     }
  }

  return ret;
 }

StrLen DDLView::toString(AnyType value)
 {
  char buf[TextBufLen];
  PrintBuf out(Range(buf));

  Putobj(out,value);

  return toString(out.close());
 }

struct DDLView::PrintText
 {
  StrLen str;

  explicit PrintText(StrLen str_) : str(str_) {}

  // print object

  static void PrintChar(PrinterType &out,char ch)
   {
    switch( ch )
      {
       case '\b' : out.put('\\'); out.put('b'); break;

       case '\t' : out.put('\\'); out.put('t'); break;

       case '\n' : out.put('\\'); out.put('n'); break;

       case '\v' : out.put('\\'); out.put('v'); break;

       case '\f' : out.put('\\'); out.put('f'); break;

       case '\r' : out.put('\\'); out.put('r'); break;

       case '\\' : out.put('\\'); out.put('\\'); break;

       default:
        {
         if( CharIsPrintable(ch) ) out.put(ch); else out.put(' ');
        }
      }
   }

  void print(PrinterType &out) const
   {
    for(char ch : str ) PrintChar(out,ch);
   }
 };

StrLen DDLView::toString(DDL::Text value)
 {
  return toString(PrintText(value.str));
 }

StrLen DDLView::toString(DDL::TypeNode::Base *type,DDL::Value value)
 {
  switch( type->type )
    {
     case DDL::TypeNode::Base::Type_sint : return toString(value.val_sint);

     case DDL::TypeNode::Base::Type_uint : return toString(value.val_uint);

     case DDL::TypeNode::Base::Type_ulen : return toString(value.val_ulen);

     case DDL::TypeNode::Base::Type_sint8 : return toString(value.val_sint8);

     case DDL::TypeNode::Base::Type_uint8 : return toString(value.val_uint8);

     case DDL::TypeNode::Base::Type_sint16 : return toString(value.val_sint16);

     case DDL::TypeNode::Base::Type_uint16 : return toString(value.val_uint16);

     case DDL::TypeNode::Base::Type_sint32 : return toString(value.val_sint32);

     case DDL::TypeNode::Base::Type_uint32 : return toString(value.val_uint32);

     case DDL::TypeNode::Base::Type_sint64 : return toString(value.val_sint64);

     case DDL::TypeNode::Base::Type_uint64 : return toString(value.val_uint64);

     case DDL::TypeNode::Base::Type_text : return toString(value.val_text);

     case DDL::TypeNode::Base::Type_ip : return toString(value.val_ip);

     default:
      {
       Printf(Exception,"App::DDLView::toString(...) : internal");

       return Null;
      }
    }
 }

 // setPtr

void DDLView::setPtr(PtrDesc *desc,DDL::Value value)
 {
  auto ptr=value.val_ptr;

  auto *node=ptr.ptr_node;

  if( !node || ptr.null )
    {
     desc->name="null"_c;
     desc->index=Empty;
     desc->target={};
    }
  else
    {
     // build index list

     ulen len=0;

     ProvideIndex(index_buf,len);

     index_buf[len++].set(node->index);

     while( auto *parent=node->parent )
       {
        node=parent;

        ProvideIndex(index_buf,len);

        index_buf[len].set(node->index);

        GetStructNode get(node->type);

        if( DDL::StructNode *struct_node = +get )
          {
           auto &obj=index_buf[len-1];

           obj.field=fieldName(struct_node,obj.index);
          }

        len++;
       }

     // reverse copy

     PtrLen<PtrDesc::Index> index=pool.createArray<PtrDesc::Index>(len);

     PtrDesc::Index *ptr=index_buf.getPtr()+len;

     for(PtrDesc::Index &obj : index ) obj=*(--ptr);

     desc->index=index;

     // insert

     ptr_buf.append_fill(desc);
    }
 }

 // build

ValueDesc DDLView::build(DDL::TypeNode::Base *type,DDL::Value value)
 {
  StrSize *desc=pool.create<StrSize>();

  *desc=toString(type,value);

  return desc;
 }

PtrLen<FieldDesc> DDLView::buildFields(DDL::StructNode *struct_node)
 {
  PtrLen<FieldDesc> ret=pool.createArray<FieldDesc>(struct_node->field_list.count);

  ulen i=0;

  for(DDL::FieldNode &field : struct_node->field_list )
    {
     ret[i].name=fieldName(field);

     i++;
    }

  return ret;
 }

ValueDesc DDLView::build(DDL::StructNode *struct_node,PtrLen<DDL::Value> value)
 {
  // create table

  PtrLen<StructDesc::Row> table=pool.createArray<StructDesc::Row>(value.len);

  for(ulen i=0; i<value.len ;i++)
    {
     PtrLen<DDL::Value> src=value[i].val_block.data;

     PtrLen<ValueDesc> dst=pool.createArray<ValueDesc>(src.len);

     ulen j=0;

     for(DDL::FieldNode &field : struct_node->field_list )
       {
        dst[j]=build(field.type_node,src[j]);

        j++;
       }

     table[i].row=dst;
    }

  // create desc

  StructDesc *desc=pool.create<StructDesc>();

  desc->fields=buildFields(struct_node);

  desc->table=table;

  return desc;
 }

ValueDesc DDLView::build(DDL::TypeNode *type,PtrLen<DDL::Value> value)
 {
  GetStructNode get(type);

  if( DDL::StructNode *struct_node = +get )
    {
     return build(struct_node,value);
    }
  else
    {
     PtrLen<ValueDesc> list=pool.createArray<ValueDesc>(value.len);

     for(ulen i=0; i<list.len ;i++) list[i]=build(type,value[i]);

     PtrLen<ValueDesc> *desc=pool.create<PtrLen<ValueDesc> >(list);

     return desc;
    }
 }

ValueDesc DDLView::build(DDL::StructNode *struct_node,DDL::Value value)
 {
  return build(struct_node,Single(value));
 }

ValueDesc DDLView::build(DDL::AliasNode *alias_node,DDL::Value value)
 {
  return build(alias_node->result_type,value);
 }

ValueDesc DDLView::build(DDL::TypeNode::Ref *type,DDL::Value value)
 {
  ValueDesc ret;

  auto obj = [this,&ret] (auto *ptr,DDL::Value value) { ret=this->build(ptr,value); } ;

  ElaborateAnyPtr(obj,type->ptr,value);

  return ret;
 }

ValueDesc DDLView::buildPtr(DDL::Value value)
 {
  PtrDesc *desc=pool.create<PtrDesc>();

  setPtr(desc,value);

  return desc;
 }

ValueDesc DDLView::build(DDL::TypeNode::Ptr *,DDL::Value value)
 {
  return buildPtr(value);
 }

ValueDesc DDLView::build(DDL::TypeNode::PolyPtr *,DDL::Value value)
 {
  return buildPtr(value);
 }

ValueDesc DDLView::build(DDL::TypeNode::Array *type,DDL::Value value)
 {
  return build(type->type_node,value.val_block.data);
 }

ValueDesc DDLView::build(DDL::TypeNode::ArrayLen *type,DDL::Value value)
 {
  return build(type->type_node,value.val_block.data);
 }

ValueDesc DDLView::build(DDL::TypeNode::Struct *type,DDL::Value value)
 {
  return build(type->struct_node,value);
 }

ValueDesc DDLView::build(DDL::TypeNode *type,DDL::Value value)
 {
  ValueDesc ret;

  auto obj = [this,&ret] (auto *ptr,DDL::Value value) { ret=this->build(ptr,value); } ;

  ElaborateAnyPtr(obj,type->ptr,value);

  return ret;
 }

class DDLView::PtrTarget
 {
   PtrLen<ValueDesc> target;
   bool single;

   ValueDesc *parent = 0 ;
   StructDesc::Row *row = 0 ;

  public:

   explicit PtrTarget(ValueDesc &target_) : target(Single(target_)),single(true) {}

   operator ValueTarget() const
    {
     if( single ) return {target,single};

     return {target,single,parent,row};
    }

   void operator () (AnyType *,PtrDesc::Index)
    {
     Printf(Exception,"App::DDLView::PtrTarget::select(...) : internal");
    }

   void operator () (StructDesc *desc,PtrDesc::Index index)
    {
     if( !index.field )
       {
        parent=target.ptr;

        row=&desc->table[index.index];

        target=row->row;
        single=false;
       }
     else
       {
        target=Single(desc->table[0].row[index.index]);
       }
    }

   void operator () (PtrLen<ValueDesc> *desc,PtrDesc::Index index)
    {
     target=Single((*desc)[index.index]);
    }

   void select(PtrDesc::Index index)
    {
     if( single )
       {
        ElaborateAnyPtr(*this,target->ptr,index);
       }
     else
       {
        target=Single(target[index.index]);
        single=true;
       }
    }
 };

void DDLView::setPtrTarget(PtrDesc *desc)
 {
  // build name

  {
   char buf[TextBufLen];
   PrintBuf out(Range(buf));

   auto index=desc->index;

   Putobj(out,"-> "_c,consts[index->index].name.str);

   for(++index; +index ;++index)
     {
      auto field=index->field;

      if( !field )
        Putobj(out,"["_c,index->index,"]"_c);
      else
        Putobj(out,"."_c,field);
     }

   desc->name=toString(out.close());
  }

  // build target

  {
   auto index=desc->index;

   PtrTarget target(consts[index->index].value);

   for(++index; +index ;++index) target.select(*index);

   desc->target=target;
  }
 }

void DDLView::setPtrTargets()
 {
  for(PtrDesc *desc : ptr_buf ) setPtrTarget(desc);
 }

void DDLView::build(const DDL::EvalResult &result)
 {
  auto list=Range(result.const_table);

  consts=pool.createArray<ConstDesc>(list.len);

  for(ulen i=0; i<list.len ;i++)
    {
     auto &src=list[i];
     auto &dst=consts[i];

     dst.name=buildName(src.node);
     dst.value=build(src.type,src.value);
    }

  setPtrTargets();

  field_name.erase();

  index_buf.erase();

  ptr_buf.erase();
 }

DDLView::DDLView()
 {
 }

DDLView::~DDLView()
 {
 }

void DDLView::update(DDL::EngineResult result)
 {
  erase();

  if( !result ) return;

  try
    {
     build(*result.eval);
    }
  catch(CatchType)
    {
     erase();

     throw;
    }
 }

/* class DDLInnerWindow */

class DDLInnerWindow::SizeProc : NoCopy
 {
   Coord space_dxy;
   Point space;
   Font font;
   Font title_font;

   ulen dxy;
   ulen exy;
   ulen ex;
   ulen ey;

  public:

   explicit SizeProc(const Config &cfg)
    : space_dxy(+cfg.space_dxy),
      space(+cfg.space),
      font(+cfg.font),
      title_font(+cfg.title_font)
    {
     dxy=Cast(space_dxy);
     exy=2*dxy;
     ex=2*Cast(space.x);
     ey=2*Cast(space.y);
    }

   uPoint size(StrSize &str) const
    {
     TextSize ts=font->text(str.str);

     IntGuard(!ts.overflow);

     ulen x=Cast(ts.full_dx);
     ulen y=Cast(ts.dy);

     str.size.x=x;
     str.size.y=y;

     return {x+ex,y+ey};
    }

   uPoint title_size(StrSize &str) const
    {
     TextSize ts=title_font->text(str.str);

     IntGuard(!ts.overflow);

     ulen x=Cast(ts.full_dx);
     ulen y=Cast(ts.dy);

     str.size.x=x;
     str.size.y=y;

     return {x+ex,y+ey};
    }

   void operator () (uPoint &ret,StrSize *ptr) const
    {
     ret=size(*ptr);
    }

   void operator () (uPoint &ret,PtrLen<ValueDesc> *ptr) const
    {
     ulen x=0;
     ulen y=0;

     for(ValueDesc &obj : *ptr )
       {
        set(obj);

        ulen dx=obj.place.size.x;
        ulen dy=obj.place.size.y;

        if( !obj.isScalar() )
          {
           dx+=exy;
           dy+=exy;
          }

        Replace_max(x,dx);

        y+=dy;
       }

     ret.x=x;
     ret.y=y;
    }

   void operator () (uPoint &ret,StructDesc *ptr) const
    {
     auto fields=ptr->fields;

     ulen y=0;

     for(FieldDesc &field : fields )
       {
        field.place.size=title_size(field.name);

        Replace_max(y,field.place.size.y);
       }

     for(FieldDesc &field : fields )
       {
        field.place.size.y=y;
       }

     y+=dxy;

     for(StructDesc::Row &row : ptr->table )
       {
        ulen row_y=0;

        for(ulen i=0; i<fields.len ;i++)
          {
           FieldDesc &field=fields[i];
           ValueDesc &obj=row.row[i];

           set(obj);

           ulen dx=obj.place.size.x;
           ulen dy=obj.place.size.y;

           if( !obj.isScalar() )
             {
              dx+=exy;
              dy+=exy;
             }

           Replace_max(field.place.size.x,dx);
           Replace_max(row_y,dy);
          }

        row.dy=row_y;

        y+=row_y;
       }

     ulen x=0;

     for(FieldDesc &field : fields )
       {
        x+=field.place.size.x;
       }

     ret.x=x;
     ret.y=y;
    }

   void operator () (uPoint &ret,PtrDesc *ptr) const
    {
     ret=size(ptr->name);
    }

   void set(ValueDesc &value) const
    {
     ElaborateAnyPtr(*this,value.place.size,value.ptr);
    }

   void operator () (ValueDesc &value) const
    {
     set(value);
    }
 };

void DDLInnerWindow::sizeView()
 {
  SizeProc size(cfg);

  auto list=view.getConstList();

  for(auto &obj : list )
    {
     obj.place.size=size.title_size(obj.name);

     size(obj.value);
    }
 }

class DDLInnerWindow::PlaceProc : NoCopy
 {
   Coord space_dxy;

   ulen dxy;
   ulen exy;

   ulen y = 0 ;

   ulen total_x = 0 ;

  public:

   explicit PlaceProc(const Config &cfg)
    : space_dxy(+cfg.space_dxy)
    {
     dxy=Cast(space_dxy);
     exy=2*dxy;
    }

   void operator () (StrSize *ptr,ulen x,ulen y)
    {
     Used(ptr);
     Used(x);
     Used(y);
    }

   void operator () (PtrLen<ValueDesc> *ptr,ulen x,ulen y)
    {
     for(ValueDesc &obj : *ptr )
       {
        if( obj.isScalar() )
          {
           set(obj,x,y);

           y+=obj.place.size.y;
          }
        else
          {
           set(obj,x+dxy,y+dxy);

           y+=obj.place.size.y+exy;
          }
       }
    }

   void operator () (StructDesc *ptr,ulen x,ulen y)
    {
     auto fields=ptr->fields;

     {
      ulen X=x;

      for(FieldDesc &field : fields )
        {
         field.place.base.x=X;
         field.place.base.y=y;

         X+=field.place.size.x;
        }
     }

     if( +fields ) y+=fields[0].place.size.y;

     y+=dxy;

     for(StructDesc::Row &row : ptr->table )
       {
        ulen X=x;

        row.y=y;

        for(ulen i=0; i<fields.len ;i++)
          {
           FieldDesc &field=fields[i];
           ValueDesc &obj=row.row[i];

           if( obj.isScalar() )
             set(obj,X,y);
           else
             set(obj,X+dxy,y+dxy);

           X+=field.place.size.x;
          }

        y+=row.dy;
       }
    }

   void operator () (PtrDesc *ptr,ulen x,ulen y)
    {
     Used(ptr);
     Used(x);
     Used(y);
    }

   void set(ValueDesc &value,ulen x,ulen y)
    {
     value.place.base.x=x;
     value.place.base.y=y;

     ElaborateAnyPtr(*this,value.ptr,x,y);
    }

   void operator () (uPane &place,ValueDesc &value)
    {
     ulen x=dxy;

     y+=dxy;

     place.base.x=x;
     place.base.y=y;

     x+=place.size.x+dxy;

     set(value,x,y);

     x+=value.place.size.x;

     Replace_max(total_x,x);

     y+=Max(place.size.y,value.place.size.y);
    }

   void getTotal(ulen &ret_x,ulen &ret_y)
    {
     ret_x=total_x+dxy;
     ret_y=y+dxy;
    }
 };

void DDLInnerWindow::placeView()
 {
  PlaceProc place(cfg);

  auto list=view.getConstList();

  ulen x=0;

  for(auto &obj : list ) Replace_max(x,obj.place.size.x);

  for(auto &obj : list )
    {
     obj.place.size.x=x;

     place(obj.place,obj.value);
    }

  place.getTotal(slide_x.total,slide_y.total);
 }

void DDLInnerWindow::layoutView()
 {
  sizeView();
  placeView();
 }

struct DDLInnerWindow::ClipProc
 {
  struct Extension
   {
    ulen x;
    ulen len;

    bool operator >= (Extension ext) const { return x+len > ext.x ; }

    bool operator <= (Extension ext) const { return x < ext.x+ext.len ; }

    bool operator >= (ulen pos) const { return x+len > pos ; }

    bool operator <= (ulen pos) const { return x <= pos ; }
   };

  static Extension ExtY(const ConstDesc &desc)
   {
    return {desc.place.base.y,Max(desc.place.size.y,desc.value.place.size.y)};
   }

  static Extension ExtX(const FieldDesc &desc)
   {
    return {desc.place.base.x,desc.place.size.x};
   }

  static Extension CellExtY(const ValueDesc &desc,ulen dxy,ulen exy)
   {
    if( desc.isScalar() )
      {
       return {desc.place.base.y,desc.place.size.y};
      }
    else
      {
       return {desc.place.base.y-dxy,desc.place.size.y+exy};
      }
   }

  static Extension RowExtY(const StructDesc::Row &row)
   {
    return {row.y,row.dy};
   }
 };

class DDLInnerWindow::FindProc : ClipProc
 {
   uPoint pos;
   bool cell = false ;

   ulen dxy;
   ulen exy;

   ValueDesc *ret = 0 ;

  private:

   template <class T>
   static T * First(PtrLen<T> list)
    {
     if( list.len ) return list.ptr;

     return 0;
    }

   template <class T,FuncType<Extension,T> Func>
   static T * Clip(PtrLen<T> list,Func func,ulen pos)
    {
     Algon::BinarySearch_if(list, [func,pos] (const T &obj) { return func(obj) >= pos ; } );

     return First( Algon::BinarySearch_if(list, [func,pos] (const T &obj) { return !( func(obj) <= pos ); } ) );
    }

   ValueDesc * clipY(PtrLen<ValueDesc> list) const
    {
     ulen dxy=this->dxy;
     ulen exy=this->exy;

     return Clip(list, [dxy,exy] (const ValueDesc &desc) { return CellExtY(desc,dxy,exy); } ,pos.y);
    }

   StructDesc::Row * clipY(PtrLen<StructDesc::Row> list) const
    {
     return Clip(list,RowExtY,pos.y);
    }

   FieldDesc * clipX(PtrLen<FieldDesc> list) const
    {
     return Clip(list,ExtX,pos.x);
    }

  public:

   FindProc(uPoint pos_,const Config &cfg)
    : pos(pos_)
    {
     Coord space_dxy=+cfg.space_dxy;

     dxy=Cast(space_dxy);
     exy=2*dxy;
    }

   operator ValueDesc * () const { return ret; }

   void operator () (ValueDesc &desc,StrSize *)
    {
     if( !cell && !desc.place.contains(pos) ) return;

     ret=&desc;
    }

   void operator () (ValueDesc &desc,PtrLen<ValueDesc> *ptr)
    {
     if( !desc.place.contains(pos) ) return;

     cell=true;

     if( auto *desc=clipY(*ptr) )
       {
        set(*desc);
       }
    }

   void operator () (ValueDesc &,StructDesc *ptr)
    {
     cell=true;

     if( auto *row=clipY(ptr->table) )
       {
        auto fields=ptr->fields;

        if( auto *clip_field=clipX(fields) )
          {
           ulen i=Dist(fields.ptr,clip_field);

           set(row->row[i]);
          }
       }
    }

   void operator () (ValueDesc &desc,PtrDesc *)
    {
     if( !cell && !desc.place.contains(pos) ) return;

     ret=&desc;
    }

   void set(ValueDesc &desc)
    {
     ElaborateAnyPtr(*this,desc,desc.ptr);
    }

   void operator () (ValueDesc &desc)
    {
     set(desc);
    }

   ConstDesc * clipY(PtrLen<ConstDesc> list) const
    {
     return Clip(list,ExtY,pos.y);
    }
 };

ValueDesc * DDLInnerWindow::find(uPoint pos) const
 {
  FindProc proc(pos,cfg);

  auto list=view.getConstList();

  if( auto *desc=proc.clipY(list) ) proc(desc->value);

  return proc;
 }

void DDLInnerWindow::moveTo(ValueTarget target,Point point)
 {
  if( !target ) return;

  moveTo(target.target->place.base,point);

  select(target.frame());
 }

void DDLInnerWindow::moveTo(uPoint target,Point point)
 {
  moveTo(target-uPoint{Cast(point.x),Cast(point.y)});
 }

void DDLInnerWindow::moveTo(uPoint pos)
 {
  slide_x.set(pos.x,scroll_x);
  slide_y.set(pos.y,scroll_y);

  //redraw();
 }

void DDLInnerWindow::select(uPane pane)
 {
  selection=pane;

  redraw();
 }

void DDLInnerWindow::posX(ulen pos)
 {
  slide_x.pos=pos;

  redraw();
 }

void DDLInnerWindow::posY(ulen pos)
 {
  slide_y.pos=pos;

  redraw();
 }

DDLInnerWindow::DDLInnerWindow(SubWindowHost &host,const Config &cfg_)
 : SubWindow(host),
   cfg(cfg_),

   connector_posX(this,&DDLInnerWindow::posX),
   connector_posY(this,&DDLInnerWindow::posY)
 {
 }

DDLInnerWindow::~DDLInnerWindow()
 {
 }

 // methods

void DDLInnerWindow::update(DDL::EngineResult result)
 {
  view.update(result);

  slide_x.pos=0;
  slide_y.pos=0;

  layoutView();
 }

 // drawing

void DDLInnerWindow::layout(unsigned)
 {
  Point size=getSize();

  slide_x.setPage(size.x);
  slide_y.setPage(size.y);

  FontSize fs=cfg.font->getSize();

  wheel_mul=fs.dy;
 }

class DDLInnerWindow::DrawProc : ClipProc
 {
   DrawBuf buf;

   MCoord width;

   Coord space_dxy;

   Point space;

   VColor top;
   VColor bottom;
   VColor text;
   VColor ptr;

   Font font;
   Font title_font;

   ulen dxy;
   ulen exy;
   ulen sdx;
   ulen widthUp;

   uPoint pos;
   uPoint size;

  private:

   void drawText(StrLen str,uPane outer,Font font,VColor vc) const
    {
     if( outer.intersect(pos,size) )
       {
        Pane pane=outer.baseOf(pos);

        font->text(buf,pane,{AlignX_Left,AlignY_Top},str,vc);
       }
    }

   static bool CapTo(ulen &x,ulen &len,ulen X,ulen L)
    {
     if( x<X )
       {
        ulen delta=X-x;

        x=X;

        if( len<=delta ) return false;

        len-=delta;
       }

     ulen off=x-X;

     if( off>=L ) return false;

     L-=off;

     if( len>L ) len=L;

     return len>0;
    }

   static bool IntersectUp(ulen x,ulen len,ulen X,ulen L)
    {
     return CapTo(x,len,X,L);
    }

   static bool IntersectDown(ulen x,ulen len,ulen X,ulen L)
    {
     if( len==0 ) return false;

     ulen dx=len-1;

     if( x>=dx )
       {
        x-=dx;
       }
     else
       {
        len=x+1;
        x=0;
       }

     return IntersectUp(x,len,X,L);
    }

   void drawLeft(uPoint base,ulen len,VColor vc) const
    {
     if( !CapTo(base.y,len,pos.y,size.y) ) return;

     if( !IntersectUp(base.x,widthUp,pos.x,size.x) ) return;

     Point a=base.baseOf(pos);
     Point b=a.addY(Coord(len-1));

     SmoothDrawArt art(buf);

     art.path(HalfPos,width,vc,MPoint(a).subXY(MPoint::Half),MPoint(b).subXaddY(MPoint::Half));
    }

   void drawTop(uPoint base,ulen len,VColor vc) const
    {
     if( !CapTo(base.x,len,pos.x,size.x) ) return;

     if( !IntersectUp(base.y,widthUp,pos.y,size.y) ) return;

     Point a=base.baseOf(pos);
     Point b=a.addX(Coord(len-1));

     SmoothDrawArt art(buf);

     art.path(HalfNeg,width,vc,MPoint(a).subXY(MPoint::Half),MPoint(b).addXsubY(MPoint::Half));
    }

   void drawRight(uPoint base,ulen len,VColor vc) const
    {
     if( !CapTo(base.y,len,pos.y,size.y) ) return;

     if( !IntersectDown(base.x,widthUp,pos.x,size.x) ) return;

     Point a=base.baseOf(pos);
     Point b=a.addY(Coord(len-1));

     SmoothDrawArt art(buf);

     art.path(HalfNeg,width,vc,MPoint(a).addXsubY(MPoint::Half),MPoint(b).addXY(MPoint::Half));
    }

   void drawBottom(uPoint base,ulen len,VColor vc) const
    {
     if( !CapTo(base.x,len,pos.x,size.x) ) return;

     if( !IntersectDown(base.y,widthUp,pos.y,size.y) ) return;

     Point a=base.baseOf(pos);
     Point b=a.addX(Coord(len-1));

     SmoothDrawArt art(buf);

     art.path(HalfPos,width,vc,MPoint(a).subXaddY(MPoint::Half),MPoint(b).addXY(MPoint::Half));
    }

  private:

   template <class T,FuncType<Extension,T> Func>
   static PtrLen<T> Clip(PtrLen<T> list,Func func,Extension ext)
    {
     Algon::BinarySearch_if(list, [func,ext] (const T &obj) { return func(obj) >= ext ; } );

     return Algon::BinarySearch_if(list, [func,ext] (const T &obj) { return !( func(obj) <= ext ); } );
    }

   PtrLen<FieldDesc> clipX(PtrLen<FieldDesc> list) const
    {
     return Clip(list,ExtX,{pos.x,size.x});
    }

   PtrLen<ValueDesc> clipY(PtrLen<ValueDesc> list) const
    {
     ulen dxy=this->dxy;
     ulen exy=this->exy;

     return Clip(list, [dxy,exy] (const ValueDesc &desc) { return CellExtY(desc,dxy,exy); } ,{pos.y,size.y});
    }

   PtrLen<StructDesc::Row> clipY(PtrLen<StructDesc::Row> list) const
    {
     return Clip(list,RowExtY,{pos.y,size.y});
    }

  public:

   DrawProc(const DrawBuf &buf_,const Config &cfg,uPoint pos_,uPoint size_)
    : buf(buf_),
      width(+cfg.width),
      space_dxy(+cfg.space_dxy),
      space(+cfg.space),
      top(+cfg.gray),
      bottom(+cfg.snow),
      text(+cfg.text),
      ptr(+cfg.ptr),
      font(+cfg.font),
      title_font(+cfg.title_font),
      pos(pos_),
      size(size_)
    {
     dxy=Cast(space_dxy);
     exy=2*dxy;
     sdx=Cast(space.x);
     widthUp=Cast(RoundUpLen(width));
    }

   void drawFrame(uPane place) const
    {
     if( place.size.noSize() ) return;

     drawLeft(place.base,place.size.y,top);
     drawTop(place.base,place.size.x,top);
     drawRight({place.base.x+place.size.x-1,place.base.y},place.size.y,bottom);
     drawBottom({place.base.x,place.base.y+place.size.y-1},place.size.x,bottom);
    }

   void drawFrame(uPane place,VColor vc) const
    {
     if( place.size.noSize() ) return;

     drawLeft(place.base,place.size.y,vc);
     drawTop(place.base,place.size.x,vc);
     drawRight({place.base.x+place.size.x-1,place.base.y},place.size.y,vc);
     drawBottom({place.base.x,place.base.y+place.size.y-1},place.size.x,vc);
    }

   void drawText(StrSize str,uPane place,Font font,VColor vc) const
    {
     uPane outer;

     outer.base.x=place.base.x+sdx;
     outer.base.y=place.base.y+(place.size.y-str.size.y)/2;

     outer.size=str.size;

     drawText(str.str,outer,font,vc);
    }

   void drawTextCenter(StrSize str,uPane place) const
    {
     uPane outer;

     outer.base.x=place.base.x+(place.size.x-str.size.x)/2;
     outer.base.y=place.base.y+(place.size.y-str.size.y)/2;

     outer.size=str.size;

     drawText(str.str,outer,title_font,text);
    }

   void draw(StrSize str,uPane place,Font font,VColor vc,bool inside=false) const
    {
     if( place.intersect(pos,size) )
       {
        if( !inside ) drawFrame(place);

        drawText(str,place,font,vc);
       }
    }

   void drawCenter(StrSize str,uPane place) const
    {
     drawFrame(place);

     drawTextCenter(str,place);
    }

   void operator () (uPane place,StrSize *ptr,bool inside) const
    {
     draw(*ptr,place,font,text,inside);
    }

   void operator () (uPane place,PtrLen<ValueDesc> *ptr,bool inside) const
    {
     Used(inside);

     uPane cell;

     cell.base=place.base;
     cell.size.x=place.size.x;

     for(ValueDesc &obj : clipY(*ptr) )
       {
        if( obj.isScalar() )
          {
           cell.base.y=obj.place.base.y;
           cell.size.y=obj.place.size.y;
          }
        else
          {
           cell.base.y=obj.place.base.y-dxy;
           cell.size.y=obj.place.size.y+exy;
          }

        draw(cell,obj);
       }
    }

   void operator () (uPane place,StructDesc *ptr,bool inside) const
    {
     Used(inside);
     Used(place);

     auto fields=ptr->fields;

     auto clip_fields=clipX(fields);

     if( !clip_fields ) return;

     ulen di=Dist(fields.ptr,clip_fields.ptr);

     for(FieldDesc &field : clip_fields )
       {
        drawCenter(field.name,field.place);
       }

     uPane cell;

     for(StructDesc::Row &row : clipY(ptr->table) )
       {
        cell.base.y=row.y;
        cell.size.y=row.dy;

        for(ulen i=0; i<clip_fields.len ;i++)
          {
           FieldDesc &field=clip_fields[i];
           ValueDesc &obj=row.row[i+di];

           cell.base.x=field.place.base.x;
           cell.size.x=field.place.size.x;

           draw(cell,obj);
          }
       }
    }

   void operator () (uPane place,PtrDesc *ptr,bool inside) const
    {
     draw(ptr->name,place,font,this->ptr,inside);
    }

   void draw(const ValueDesc &value,bool inside=false) const
    {
     if( value.place.intersect(pos,size) )
       ElaborateAnyPtr(*this,value.place,value.ptr,inside);
    }

   void draw(uPane cell,const ValueDesc &value) const
    {
     drawFrame(cell);

     draw(value,true);
    }

   void operator () (const ConstDesc &desc) const
    {
     draw(desc.name,desc.place,title_font,text);

     draw(desc.value);
    }

   // clip

   PtrLen<ConstDesc> clipY(PtrLen<ConstDesc> list) const
    {
     return Clip(list,ExtY,{pos.y,size.y});
    }
 };

void DDLInnerWindow::draw(DrawBuf buf,bool) const
 {
  buf.erase(+cfg.back);

  Point size=getSize();

  DrawProc proc(buf,cfg,{slide_x.pos,slide_y.pos},{Cast(size.x),Cast(size.y)});

  auto list=view.getConstList();

  for(auto &obj : proc.clipY(list) )
    {
     proc(obj);
    }

  if( focus ) proc.drawFrame({{0,0},{slide_x.total,slide_y.total}},+cfg.focus);

  proc.drawFrame(selection,+cfg.select);
 }

 // base

void DDLInnerWindow::open()
 {
  focus=false;
 }

 // keyboard

void DDLInnerWindow::gainFocus()
 {
  if( Change(focus,true) ) redraw();
 }

void DDLInnerWindow::looseFocus()
 {
  if( Change(focus,false) ) redraw();
 }

 // user input

void DDLInnerWindow::react(UserAction action)
 {
  action.dispatch(*this);
 }

void DDLInnerWindow::react_LeftClick(Point point,MouseKey mkey)
 {
  if( ValueDesc *desc=find({slide_x.pos+Cast(point.x),slide_y.pos+Cast(point.y)}) )
    {
     if( PtrDesc *ptr=desc->ptr.castPtr<PtrDesc>() )
       {
        if( mkey&MouseKey_Shift )
          {
           select(desc->place);
          }
        else
          {
           moveTo(ptr->target,point);
          }
       }
     else
       {
        select(desc->place);
       }
    }
 }

void DDLInnerWindow::react_Wheel(Point,MouseKey mkey,Coord delta)
 {
  if( mkey&MouseKey_Shift )
    {
     if( slide_x.move(delta,wheel_mul,scroll_x) )
       {
        redraw();
       }
    }
  else
    {
     if( slide_y.move(delta,wheel_mul,scroll_y) )
       {
        redraw();
       }
    }
 }

/* class DDLWindow */

void DDLWindow::file_updated()
 {
  inner.update(file.getResult());

  layout(LayoutUpdate);

  redraw();
 }

DDLWindow::DDLWindow(SubWindowHost &host,const Config &cfg_,DDLFile &file_)
 : ComboWindow(host),
   cfg(cfg_),
   file(file_),

   inner(wlist,cfg),
   scroll_x(wlist,cfg.x_cfg),
   scroll_y(wlist,cfg.y_cfg),

   connector_posx(&scroll_x,&XScrollWindow::setPos,inner.scroll_x),
   connector_posy(&scroll_y,&YScrollWindow::setPos,inner.scroll_y),

   connector_file_updated(this,&DDLWindow::file_updated,file_.updated)
 {
  wlist.insTop(inner);

  inner.bind(scroll_x.changed,scroll_y.changed);
 }

DDLWindow::~DDLWindow()
 {
 }

void DDLWindow::layout(unsigned flags)
 {
  Pane all(Null,getSize());
  Pane pane(all);
  Coord delta_x=scroll_y.getMinSize().dx;
  Coord delta_y=scroll_x.getMinSize().dy;

  inner.setPlace(pane,flags);

  if( inner.shortDY() )
    {
     Pane py=SplitX(pane,delta_x);

     inner.setPlace(pane,flags);
     scroll_y.setPlace(py,flags);

     wlist.insBottom(scroll_y);

     if( inner.shortDX() )
       {
        Pane px=SplitY(pane,delta_y);

        inner.setPlace(pane,flags);
        scroll_x.setPlace(px,flags);

        wlist.insBottom(scroll_x);
       }
     else
       {
        wlist.del(scroll_x);
       }
    }
  else
    {
     if( inner.shortDX() )
       {
        Pane px=SplitY(pane,delta_y);

        inner.setPlace(pane,flags);

        if( inner.shortDY() )
          {
           pane=all;
           Pane py=SplitX(pane,delta_x);
           Pane px=SplitY(pane,delta_y);

           inner.setPlace(pane,flags);
           scroll_x.setPlace(px,flags);
           scroll_y.setPlace(py,flags);

           wlist.insBottom(scroll_x);

           wlist.insBottom(scroll_y);
          }
        else
          {
           scroll_x.setPlace(px,flags);

           wlist.insBottom(scroll_x);

           wlist.del(scroll_y);
          }
       }
     else
       {
        wlist.del(scroll_x);

        wlist.del(scroll_y);
       }
    }

  setScroll();
 }

/* class DisplayWindow */

void DisplayWindow::error(StrLen str)
 {
  msg_frame.setInfo(String(str));

  if( msg_frame.isDead() ) msg_frame.create(getFrame(),"Error"_def);
 }

void DisplayWindow::setPretextFileName(StrLen file_name)
 {
  text_pretext.setText(SafeString(file_name));
 }

void DisplayWindow::setFileName(StrLen file_name)
 {
  text_file.setText(SafeString(file_name));
 }

DisplayWindow::DisplayWindow(SubWindowHost &host,const Config &cfg_)
 : ComboWindow(host),
   cfg(cfg_),

   label_pretext(wlist,cfg.label_cfg,"Pretext"_def),
   label_file(wlist,cfg.label_cfg,"File"_def),
   text_pretext(wlist,cfg.textline_cfg),
   text_file(wlist,cfg.textline_cfg),
   dline(wlist,cfg.dline_cfg),
   ddl(wlist,cfg.ddl_cfg,file),

   msg_frame(getFrameDesktop(),cfg.msg_cfg)
 {
  wlist.insTop(label_pretext,label_file,text_pretext,text_file,dline,ddl);
 }

DisplayWindow::~DisplayWindow()
 {
 }

 // methods

void DisplayWindow::open(StrLen file_name)
 {
  auto result=file.open(file_name);

  if( result.ok )
    {
     opened.assert(file_name,true);

     setFileName(file_name);

     redraw();
    }
  else
    {
     opened.assert(file_name,false);

     setFileName(Empty);

     redraw();

     error(result.etext.str());
    }
 }

void DisplayWindow::openPretext(StrLen file_name)
 {
  auto result=file.openPretext(file_name);

  if( result.ok )
    {
     setPretextFileName(file_name);
     setFileName(Empty);

     redraw();
    }
  else
    {
     error(result.etext.str());
    }
 }

void DisplayWindow::noPretext()
 {
  file.noPretext();

  setPretextFileName(Empty);
  setFileName(Empty);

  redraw();
 }

 // drawing

void DisplayWindow::layout(unsigned flags)
 {
  PaneCut pane(getSize(),+cfg.space_dxy,flags);

  pane.shrink();

  // label_pretext , text_pretext

  {
   auto label__pretext=CutPoint(label_pretext);
   auto text__pretext=CutPoint(text_pretext);

   Coord dy=SupDY(label__pretext,text__pretext);

   pane.cutTop(dy).place_cutLeftCenter(label__pretext).place(AlignCenterY(text__pretext));
  }

  // label_file , text_file

  {
   auto label__file=CutPoint(label_file);
   auto text__file=CutPoint(text_file);

   Coord dy=SupDY(label__file,text__file);

   pane.cutTop(dy).place_cutLeftCenter(label__file).place(AlignCenterY(text__file));
  }

  // dline

  pane.place_cutTop(dline);

  // ddl

  pane.place(ddl);
 }

void DisplayWindow::drawBack(DrawBuf buf,bool) const
 {
  buf.erase(+cfg.back);
 }

} // namespace App



