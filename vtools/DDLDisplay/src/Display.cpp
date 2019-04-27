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

#include <CCore/inc/video/LayoutCombo.h>
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

     return {"Exception"_str,false};
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

     return {"Exception"_str,false};
    }
 }

void DDLFile::noPretext()
 {
  FileToMem map;

  Swap(pretext,map);

  erase();
 }

/* struct ValueTarget */

Pane ValueTarget::frame() const
 {
  if( !target ) return Null;

  if( single ) return target->place;

  Pane ret;

  SetExtX(ret,GetExtX(parent->place));

  SetExtY(ret,row->exty);

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

  return toString(TrimText(out.close()));
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

   desc->name=toString(TrimText(out.close()));
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

   Coord dxy;
   Coord exy;

   Point delta;

  private:

   Point size(const Font &font,StrSize &str) const
    {
     TextSize ts=font->text(str.str);

     Point s=ts.getSize();

     str.size=s;

     return s+delta;
    }

  public:

   explicit SizeProc(const Config &cfg)
    : space_dxy(+cfg.space_dxy),
      space(+cfg.space),
      font(+cfg.font),
      title_font(+cfg.title_font)
    {
     dxy=space_dxy;
     exy=2*dxy;

     delta=2*space;
    }

   Point size(StrSize &str) const
    {
     return size(font,str);
    }

   Point title_size(StrSize &str) const
    {
     return size(title_font,str);
    }

   void operator () (Point &ret,StrSize *ptr) const
    {
     ret=size(*ptr);
    }

   void operator () (Point &ret,PtrLen<ValueDesc> *ptr) const
    {
     Point s;

     for(ValueDesc &obj : *ptr )
       {
        set(obj);

        Point ds=obj.place.getSize();

        if( !obj.isScalar() ) ds+=Point::Diag(exy);

        s=StackYSize(s,ds);
       }

     ret=s;
    }

   void operator () (Point &ret,StructDesc *ptr) const
    {
     auto fields=ptr->fields;

     Coord y=0;

     for(FieldDesc &field : fields )
       {
        field.setSize(title_size(field.name));

        Replace_max(y,field.place.dy);
       }

     for(FieldDesc &field : fields )
       {
        field.place.dy=y;
       }

     y+=dxy;

     for(StructDesc::Row &row : ptr->table )
       {
        Coord row_y=0;

        for(ulen i=0; i<fields.len ;i++)
          {
           FieldDesc &field=fields[i];
           ValueDesc &obj=row.row[i];

           set(obj);

           Point ds=obj.place.getSize();

           if( !obj.isScalar() ) ds+=Point::Diag(exy);

           Replace_max(field.place.dx,ds.x);
           Replace_max(row_y,ds.y);
          }

        row.exty.len=row_y;

        y+=row_y;
       }

     Coord x=0;

     for(FieldDesc &field : fields )
       {
        x+=field.place.dx;
       }

     ret.x=x;
     ret.y=y;
    }

   void operator () (Point &ret,PtrDesc *ptr) const
    {
     ret=size(ptr->name);
    }

   void set(ValueDesc &value) const
    {
     Point size;

     ElaborateAnyPtr(*this,size,value.ptr);

     value.setSize(size);
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
     obj.setTitleSize(size.title_size(obj.name));

     size(obj.value);
    }
 }

class DDLInnerWindow::PlaceProc : NoCopy
 {
   Coord space_dxy;

   Coord dxy;
   Coord exy;

   Coord y = 0 ;

   Coord total_x = 0 ;

  public:

   explicit PlaceProc(const Config &cfg)
    : space_dxy(+cfg.space_dxy)
    {
     dxy=space_dxy;
     exy=2*dxy;
    }

   void operator () (StrSize *ptr,Coord x,Coord y)
    {
     Used(ptr);
     Used(x);
     Used(y);
    }

   void operator () (PtrLen<ValueDesc> *ptr,Coord x,Coord y)
    {
     for(ValueDesc &obj : *ptr )
       {
        if( obj.isScalar() )
          {
           set(obj,x,y);

           y+=obj.place.dy;
          }
        else
          {
           set(obj,x+dxy,y+dxy);

           y+=obj.place.dy+exy;
          }
       }
    }

   void operator () (StructDesc *ptr,Coord x,Coord y)
    {
     auto fields=ptr->fields;

     {
      Coord X=x;

      for(FieldDesc &field : fields )
        {
         field.place.x=X;
         field.place.y=y;

         X+=field.place.dx;
        }
     }

     if( +fields ) y+=fields[0].place.dy;

     y+=dxy;

     for(StructDesc::Row &row : ptr->table )
       {
        Coord X=x;

        row.exty.pos=y;

        for(ulen i=0; i<fields.len ;i++)
          {
           FieldDesc &field=fields[i];
           ValueDesc &obj=row.row[i];

           if( obj.isScalar() )
             set(obj,X,y);
           else
             set(obj,X+dxy,y+dxy);

           X+=field.place.dx;
          }

        y+=row.exty.len;
       }
    }

   void operator () (PtrDesc *ptr,Coord x,Coord y)
    {
     Used(ptr);
     Used(x);
     Used(y);
    }

   void set(ValueDesc &value,Coord x,Coord y)
    {
     value.place.x=x;
     value.place.y=y;

     ElaborateAnyPtr(*this,value.ptr,x,y);
    }

   void operator () (Pane &place,ValueDesc &value)
    {
     Coord x=dxy;

     y+=dxy;

     place.x=x;
     place.y=y;

     x+=place.dx+dxy;

     set(value,x,y);

     x+=value.place.dx;

     Replace_max(total_x,x);

     y+=Max(place.dy,value.place.dy);
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

  Coord x=0;

  for(auto &obj : list ) Replace_max(x,obj.place.dx);

  for(auto &obj : list )
    {
     obj.place.dx=x;

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
  static Extension ExtY(const ConstDesc &desc) { return desc.getExtY(); }

  static Extension ExtX(const FieldDesc &desc) { return desc.getExtX(); }

  static Extension CellExtY(const ValueDesc &desc,Coord dxy,Coord exy)
   {
    Extension ext=desc.getExtY();

    if( desc.isScalar() )
      {
       return ext;
      }
    else
      {
       return ext.expand(dxy,exy);
      }
   }

  static Extension RowExtY(const StructDesc::Row &row) { return row.exty; }

  template <class T,FuncType<Extension,T> Func,class Pos>
  static PtrLen<T> Clip(PtrLen<T> list,Func func,Pos pos)
   {
    Algon::BinarySearch_if(list, [func,pos] (const T &obj) { return func(obj) >= pos ; } );

    return Algon::BinarySearch_if(list, [func,pos] (const T &obj) { return !( func(obj) <= pos ); } );
   }

  template <class T>
  static T * First(PtrLen<T> list)
   {
    if( list.len ) return list.ptr;

    return 0;
   }

  template <class T,FuncType<Extension,T> Func,class Pos>
  static T * ClipFirst(PtrLen<T> list,Func func,Pos pos) { return First( Clip(list,func,pos) ); }
 };

class DDLInnerWindow::FindProc : ClipProc
 {
   Point pos;
   bool cell = false ;

   Coord dxy;
   Coord exy;

   ValueDesc *ret = 0 ;

  private:

   ValueDesc * clipY(PtrLen<ValueDesc> list) const
    {
     Coord dxy=this->dxy;
     Coord exy=this->exy;

     return ClipFirst(list, [dxy,exy] (const ValueDesc &desc) { return CellExtY(desc,dxy,exy); } ,pos.y);
    }

   StructDesc::Row * clipY(PtrLen<StructDesc::Row> list) const { return ClipFirst(list,RowExtY,pos.y); }

   FieldDesc * clipX(PtrLen<FieldDesc> list) const { return ClipFirst(list,ExtX,pos.x); }

  public:

   FindProc(Point pos_,const Config &cfg)
    : pos(pos_)
    {
     Coord space_dxy=+cfg.space_dxy;

     dxy=space_dxy;
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

   ConstDesc * clipY(PtrLen<ConstDesc> list) const { return ClipFirst(list,ExtY,pos.y); }
 };

ValueDesc * DDLInnerWindow::find(Point pos) const
 {
  FindProc proc(pos,cfg);

  auto list=view.getConstList();

  if( auto *desc=proc.clipY(list) ) proc(desc->value);

  return proc;
 }

void DDLInnerWindow::moveTo(ValueTarget target,Point point)
 {
  if( !target ) return;

  moveTo(target.target->place.getBase(),point);

  select(target.frame());
 }

void DDLInnerWindow::moveTo(Point target,Point point)
 {
  moveTo(Sup(target-point,Null));
 }

void DDLInnerWindow::moveTo(Point pos)
 {
  slide_x.set(pos.x,scroll_x);
  slide_y.set(pos.y,scroll_y);

  redraw();
 }

void DDLInnerWindow::select(Pane pane)
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

void DDLInnerWindow::updated(unsigned flags)
 {
  if( flags&LayoutUpdate ) update();
 }

DDLInnerWindow::DDLInnerWindow(SubWindowHost &host,const Config &cfg_)
 : SubWindow(host),
   cfg(cfg_),

   connector_posX(this,&DDLInnerWindow::posX),
   connector_posY(this,&DDLInnerWindow::posY),
   connector_updated(this,&DDLInnerWindow::updated,host.getFrame()->updated)
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

  update();
 }

 // drawing

void DDLInnerWindow::layout()
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

   Coord dxy;
   Coord exy;
   Coord sdx;
   Coord widthUp;

   Point pos;
   Point size;

  private:

   bool intersect(Pane place) const
    {
     return +Inf( Pane(pos,size) , place );
    }

   void drawText(StrLen str,Pane outer,Font font,VColor vc) const
    {
     if( intersect(outer) )
       {
        Pane pane=outer-pos;

        font->text(buf,pane,{AlignX_Left,AlignY_Top},str,vc);
       }
    }

   static bool CapTo(Coord &x,Coord &len,Coord X,Coord L)
    {
     if( x<X )
       {
        Coord delta=X-x;

        x=X;

        if( len<=delta ) return false;

        len-=delta;
       }

     Coord off=x-X;

     if( off>=L ) return false;

     L-=off;

     if( len>L ) len=L;

     return len>0;
    }

   static bool CapTo(Coord &x,Coord &len,Coord X,Coord L,Coord ext)
    {
     return CapTo(x,len,X-ext,L+2*ext);
    }

   void solid(MPoint A,MPoint B,MPoint C,MPoint D,VColor vc) const
    {
     SmoothDrawArt art(buf);

     MPoint temp[]={A,B,C,D};

     art.solid(Range(temp),SolidAll,vc);
    }

   void drawLeft(Point base,Coord len,VColor vc) const
    {
     if( !CapTo(base.y,len,pos.y,size.y,widthUp) ) return;

     Point a=base-pos;
     Point b=a.addY(len-1);

     MPoint A(a);
     MPoint B(b);

     A=A.subXY(MPoint::Half);
     B=B.subXaddY(MPoint::Half);

     MPoint C=B.addXsubY(width);
     MPoint D=A.addXY(width);

     solid(A,B,C,D,vc);
    }

   void drawTop(Point base,Coord len,VColor vc) const
    {
     if( !CapTo(base.x,len,pos.x,size.x,widthUp) ) return;

     Point a=base-pos;
     Point b=a.addX(len-1);

     MPoint A(a);
     MPoint B(b);

     A=A.subXY(MPoint::Half);
     B=B.addXsubY(MPoint::Half);

     MPoint C=B.subXaddY(width);
     MPoint D=A.addXY(width);

     solid(A,B,C,D,vc);
    }

   void drawRight(Point base,Coord len,VColor vc) const
    {
     if( !CapTo(base.y,len,pos.y,size.y,widthUp) ) return;

     Point a=base-pos;
     Point b=a.addY(len-1);

     MPoint A(a);
     MPoint B(b);

     A=A.addXsubY(MPoint::Half);
     B=B.addXY(MPoint::Half);

     MPoint C=B.subXY(width);
     MPoint D=A.subXaddY(width);

     solid(A,B,C,D,vc);
    }

   void drawBottom(Point base,Coord len,VColor vc) const
    {
     if( !CapTo(base.x,len,pos.x,size.x,widthUp) ) return;

     Point a=base-pos;
     Point b=a.addX(len-1);

     MPoint A(a);
     MPoint B(b);

     A=A.subXaddY(MPoint::Half);
     B=B.addXY(MPoint::Half);

     MPoint C=B.subXY(width);
     MPoint D=A.addXsubY(width);

     solid(A,B,C,D,vc);
    }

  private:

   static Point GetTopRight(Pane pane) { return Point(pane.x+pane.dx-1,pane.y); }

   static Point GetBottomLeft(Pane pane) { return Point(pane.x,pane.y+pane.dy-1); }

   Extension getExtX() const { return {pos.x,size.x}; }

   Extension getExtY() const { return {pos.y,size.y}; }

   PtrLen<FieldDesc> clipX(PtrLen<FieldDesc> list) const { return Clip(list,ExtX,getExtX()); }

   PtrLen<ValueDesc> clipY(PtrLen<ValueDesc> list) const
    {
     Coord dxy=this->dxy;
     Coord exy=this->exy;

     return Clip(list, [dxy,exy] (const ValueDesc &desc) { return CellExtY(desc,dxy,exy); } ,getExtY());
    }

   PtrLen<StructDesc::Row> clipY(PtrLen<StructDesc::Row> list) const { return Clip(list,RowExtY,getExtY()); }

  public:

   DrawProc(const DrawBuf &buf_,const Config &cfg,Point pos_,Point size_)
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
     dxy=space_dxy;
     exy=2*dxy;
     sdx=space.x;
     widthUp=RoundUpLen(width);
    }

   void drawFrame(Pane place) const
    {
     if( !place ) return;

     drawLeft(place.getBase(),place.dy,top);
     drawTop(place.getBase(),place.dx,top);

     drawRight(GetTopRight(place),place.dy,bottom);
     drawBottom(GetBottomLeft(place),place.dx,bottom);
    }

   void drawFrame(Pane place,VColor vc) const
    {
     if( !place ) return;

     drawLeft(place.getBase(),place.dy,vc);
     drawTop(place.getBase(),place.dx,vc);

     drawRight(GetTopRight(place),place.dy,vc);
     drawBottom(GetBottomLeft(place),place.dx,vc);
    }

   void drawText(StrSize str,Pane place,Font font,VColor vc) const
    {
     Point base=place.getBase()+Point(sdx,(place.dy-str.size.y)/2);

     Pane outer(base,str.size);

     drawText(str.str,outer,font,vc);
    }

   void drawTextCenter(StrSize str,Pane place) const
    {
     Point base=place.getBase()+(place.getSize()-str.size)/2;

     Pane outer(base,str.size);

     drawText(str.str,outer,title_font,text);
    }

   void draw(StrSize str,Pane place,Font font,VColor vc,bool inside=false) const
    {
     if( intersect(place) )
       {
        if( !inside ) drawFrame(place);

        drawText(str,place,font,vc);
       }
    }

   void drawCenter(StrSize str,Pane place) const
    {
     drawFrame(place);

     drawTextCenter(str,place);
    }

   void operator () (Pane place,StrSize *ptr,bool inside) const
    {
     draw(*ptr,place,font,text,inside);
    }

   void operator () (Pane place,PtrLen<ValueDesc> *ptr,bool inside) const
    {
     Used(inside);

     Pane cell;

     SetExtX(cell,GetExtX(place));

     for(ValueDesc &obj : clipY(*ptr) )
       {
        SetExtY(cell,CellExtY(obj,dxy,exy));

        draw(cell,obj);
       }
    }

   void operator () (Pane place,StructDesc *ptr,bool inside) const
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

     Pane cell;

     for(StructDesc::Row &row : clipY(ptr->table) )
       {
        SetExtY(cell,row.exty);

        for(ulen i=0; i<clip_fields.len ;i++)
          {
           FieldDesc &field=clip_fields[i];
           ValueDesc &obj=row.row[i+di];

           SetExtX(cell,field.getExtX());

           draw(cell,obj);
          }
       }
    }

   void operator () (Pane place,PtrDesc *ptr,bool inside) const
    {
     draw(ptr->name,place,font,this->ptr,inside);
    }

   void draw(const ValueDesc &value,bool inside=false) const
    {
     if( intersect(value.place) )
       ElaborateAnyPtr(*this,value.place,value.ptr,inside);
    }

   void draw(Pane cell,const ValueDesc &value) const
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
     return Clip(list,ExtY,getExtY());
    }
 };

void DDLInnerWindow::draw(DrawBuf buf,DrawParam draw_param) const
 {
  draw_param.erase(buf,+cfg.back);

  Point size=getSize();

  DrawProc proc(buf,cfg,getOff(),size);

  auto list=view.getConstList();

  for(auto &obj : proc.clipY(list) )
    {
     proc(obj);
    }

  if( focus ) proc.drawFrame(Pane(getOff(),size),+cfg.focus);

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
  if( ValueDesc *desc=find(getOff()+point) )
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
  window.update(file.getResult());

  layout();

  redraw();
 }

DDLWindow::DDLWindow(SubWindowHost &host,const Config &cfg,DDLFile &file_)
 : ScrollableWindow<DDLInnerWindow>(host,cfg),
   file(file_),

   connector_file_updated(this,&DDLWindow::file_updated,file_.updated)
 {
 }

DDLWindow::~DDLWindow()
 {
 }

/* class DisplayWindow */

void DisplayWindow::error(StrLen str)
 {
  msg_frame.setInfo(String(str));

  if( msg_frame.isDead() ) msg_frame.create(getFrame(),"Error"_str);
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

   label_pretext(wlist,cfg.label_cfg,"Pretext"_str),
   label_file(wlist,cfg.label_cfg,"File"_str),
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

Point DisplayWindow::getMinSize() const
 {
  Coord space=+cfg.space_dxy;

  // label_pretext , text_pretext

  LayToRightCenter lay1{Lay(label_pretext),Lay(text_pretext)};

  // label_file , text_file

  LayToRightCenter lay2{Lay(label_file),Lay(text_file)};

  // lay

  LayToBottom lay(lay1,lay2,Lay(dline),Lay(ddl));

  return ExtLay(lay).getMinSize(space);
 }

void DisplayWindow::open(StrLen file_name)
 {
  ComboWindow::open();

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

     error(Range(result.etext));
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
     error(Range(result.etext));
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

void DisplayWindow::layout()
 {
  Coord space=+cfg.space_dxy;

  // label_pretext , text_pretext

  LayToRightCenter lay1{Lay(label_pretext),Lay(text_pretext)};

  // label_file , text_file

  LayToRightCenter lay2{Lay(label_file),Lay(text_file)};

  // lay

  LayToBottom lay(lay1,lay2,Lay(dline),Lay(ddl));

  ExtLay(lay).setPlace(getPane(),space);
 }

void DisplayWindow::drawBack(DrawBuf buf,DrawParam &draw_param) const
 {
  draw_param.erase(buf,+cfg.back);
 }

} // namespace App



