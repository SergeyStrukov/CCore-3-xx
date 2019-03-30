/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: VMakeList 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/Array.h>
#include <CCore/inc/Sort.h>
#include <CCore/inc/Path.h>
#include <CCore/inc/Scanf.h>
#include <CCore/inc/ElementPool.h>

#include <CCore/inc/DirTreeRun.h>
#include <CCore/inc/FileToMem.h>

namespace App {

/* using */

using namespace CCore;

/* functions */

StrLen GetFileName(StrLen path)
 {
  SplitPath split1(path);
  SplitName split2(split1.path);
  SplitExt split3(split2.name);

  return split3.name;
 }

/* classes */

class Cursor;

struct FileName;

class FileList;

struct ObjList;

struct AsmList;

struct DepList;

struct AsmObjList;

struct ObjRule;

struct AsmRule;

struct DepRule;

struct AsmObjRule;

class EngineBase;

class FileEngine;

class FindFiles;

class FindEngine;

/* class Cursor */

class Cursor
 {
   StrLen text;

  public:

   explicit Cursor(PtrLen<const char> text_) : text(text_) {}

   StrLen next()
    {
     SkipSpace(text);

     if( !text ) return text;

     StrLen start=text;

     SkipNonSpace(text);

     return start.prefix(text);
    }
 };

/* struct FileName */

struct FileName
 {
  StrLen path;
  StrLen name;

  explicit FileName(StrLen path_) : path(path_),name(GetFileName(path_)) {}

  // operators

  bool operator < (FileName file) const { return StrLess(name,file.name); }

  bool operator == (FileName file) const { return name.equal(file.name); }
 };

/* class FileList */

class FileList
 {
   DynArray<FileName> buf;

  private:

   static void Guard(FileName a,FileName b)
    {
     if( a==b )
       {
        Printf(Exception,"File name duplication: #; #;",a.path,b.path);
       }
    }

   static void Process(PtrLen<FileName> r)
    {
     Sort(r);

     for(; r.len>=2 ;++r) Guard(r[0],r[1]);
    }

  public:

   explicit FileList(PtrLen<const char> text)
    {
     Cursor cur(text);
     Collector<FileName> temp;

     for(;;)
       {
        StrLen path=cur.next();

        if( !path ) break;

        temp.append_fill(path);
       }

     temp.extractTo(buf);
    }

   explicit FileList(Collector<FileName> &src)
    {
     src.extractTo(buf);
    }

   void process()
    {
     Process(Range(buf));
    }

   void apply(FuncArgType<FileName> &func) const
    {
     for(auto r=Range(buf); +r ;++r) func(*r);
    }
 };

/* struct ObjList */

struct ObjList : NoCopy
 {
  PrintFile &out;
  StrLen obj_path;

  ObjList(PrintFile &out_,StrLen obj_path_)
   : out(out_),
     obj_path(obj_path_)
   {
    Printf(out,"OBJ_LIST = \\\n");
   }

  ~ObjList()
   {
    Printf(out,"\n\n");
   }

  void operator () (FileName file)
   {
    Printf(out,"#;/#;.o \\\n",obj_path,file.name);
   }
 };

/* struct AsmList */

struct AsmList : NoCopy
 {
  PrintFile &out;
  StrLen obj_path;

  AsmList(PrintFile &out_,StrLen obj_path_)
   : out(out_),
     obj_path(obj_path_)
   {
    Printf(out,"ASM_LIST = \\\n");
   }

  ~AsmList()
   {
    Printf(out,"\n\n");
   }

  void operator () (FileName file)
   {
    Printf(out,"#;/#;.s \\\n",obj_path,file.name);
   }
 };

/* struct DepList */

struct DepList : NoCopy
 {
  PrintFile &out;
  StrLen obj_path;

  DepList(PrintFile &out_,StrLen obj_path_)
   : out(out_),
     obj_path(obj_path_)
   {
    Printf(out,"DEP_LIST = \\\n");
   }

  ~DepList()
   {
    Printf(out,"\n\n");
   }

  void operator () (FileName file)
   {
    Printf(out,"#;/#;.dep \\\n",obj_path,file.name);
   }
 };

/* struct AsmObjList */

struct AsmObjList : NoCopy
 {
  PrintFile &out;
  StrLen obj_path;

  explicit AsmObjList(PrintFile &out_,StrLen obj_path_)
   : out(out_),
     obj_path(obj_path_)
   {
    Printf(out,"ASM_OBJ_LIST = \\\n");
   }

  ~AsmObjList()
   {
    Printf(out,"\n\n");
   }

  void operator () (FileName file)
   {
    Printf(out,"#;/#;.s.o \\\n",obj_path,file.name);
   }
 };

/* struct ObjRule */

struct ObjRule : NoCopy
 {
  PrintFile &out;
  StrLen obj_path;

  ObjRule(PrintFile &out_,StrLen obj_path_)
   : out(out_),
     obj_path(obj_path_)
   {
   }

  ~ObjRule()
   {
    Printf(out,"\n\n");
   }

  void operator () (FileName file)
   {
    Printf(out,"#;/#;.o : #;\n\t$(CC) $(CCOPT) $< -o $@\n\n",obj_path,file.name,file.path);
   }
 };

/* struct AsmRule */

struct AsmRule : NoCopy
 {
  PrintFile &out;
  StrLen obj_path;

  AsmRule(PrintFile &out_,StrLen obj_path_)
   : out(out_),
     obj_path(obj_path_)
   {
   }

  ~AsmRule()
   {
    Printf(out,"\n\n");
   }

  void operator () (FileName file)
   {
    Printf(out,"#;/#;.s : #;\n\t$(CC) -S $(CCOPT) $< -o $@\n\n",obj_path,file.name,file.path);
   }
 };

/* struct DepRule */

struct DepRule : NoCopy
 {
  PrintFile &out;
  StrLen obj_path;

  DepRule(PrintFile &out_,StrLen obj_path_)
   : out(out_),
     obj_path(obj_path_)
   {
   }

  ~DepRule()
   {
    Printf(out,"\n\n");
   }

  void operator () (FileName file)
   {
    Printf(out,"#;/#;.dep : #;\n\t$(CC) $(CCOPT) -MM -MT #;/#;.o $< -MF $@\n\n",obj_path,file.name,file.path,obj_path,file.name);
   }
 };

/* struct AsmObjRule */

struct AsmObjRule : NoCopy
 {
  PrintFile &out;
  StrLen obj_path;

  AsmObjRule(PrintFile &out_,StrLen obj_path_)
   : out(out_),
     obj_path(obj_path_)
   {
   }

  ~AsmObjRule()
   {
    Printf(out,"\n\n");
   }

  void operator () (FileName file)
   {
    Printf(out,"#;/#;.s.o : #;\n\t$(AS) $(ASOPT) $< -o $@\n\n",obj_path,file.name,file.path);
   }
 };

/* class EngineBase */

class EngineBase : NoCopy
 {
   StrLen obj_path;

   FileList cpp_list;
   FileList s_list;

   PrintFile out;

  private:

   template <class T>
   void apply_to(FileList &list)
    {
     T func(out,obj_path);

     list.apply(func);
    }

   template <class T>
   void apply_to_cpp() { apply_to<T>(cpp_list); }

   template <class T>
   void apply_to_s() { apply_to<T>(s_list); }

  public:

   EngineBase(StrLen obj_path_,PtrLen<const char> cpp_list_text,PtrLen<const char> s_list_text)
    : obj_path(obj_path_),
      cpp_list(cpp_list_text),
      s_list(s_list_text),
      out("Makefile.files")
    {
     cpp_list.process();
     s_list.process();
    }

   EngineBase(StrLen obj_path_,Collector<FileName> &cpp_src,Collector<FileName> &s_src)
    : obj_path(obj_path_),
      cpp_list(cpp_src),
      s_list(s_src),
      out("Makefile.files")
    {
     cpp_list.process();
     s_list.process();
    }

   ~EngineBase() {}

   int run()
    {
     apply_to_cpp<ObjList>();
     apply_to_cpp<AsmList>();
     apply_to_cpp<DepList>();
     apply_to_s<AsmObjList>();

     Printf(out,"include $(RULES_FILE)\n\n\n");

     apply_to_cpp<ObjRule>();
     apply_to_cpp<AsmRule>();
     apply_to_cpp<DepRule>();
     apply_to_s<AsmObjRule>();

     Printf(out,"ifneq ($(MAKECMDGOALS),clean)\n\n"

                "-include $(DEP_FILE)\n\n"

                "endif\n\n"
           );

     return 0;
    }
 };

/* class FileEngine */

class FileEngine : NoCopy
 {
   FileToMem cpp_files;
   FileToMem s_files;

   EngineBase engine;

  public:

   FileEngine(StrLen obj_path,StrLen cpp_list_file_name,StrLen s_list_file_name)
    : cpp_files(cpp_list_file_name),
      s_files(s_list_file_name),
      engine(obj_path,Mutate<const char>(Range(cpp_files)),Mutate<const char>(Range(s_files)))
    {
    }

   ~FileEngine() {}

   int run() { return engine.run(); }
 };

/* class FindFiles */

class FindFiles : NoCopy
 {
   ElementPool pool;

  private:

   class Proc : NoCopy
    {
      FindFiles &obj;

     private:

      static bool SkipDir(StrLen name)
       {
        return name.len && name[0]=='.' ;
       }

      static bool SkipFile(StrLen name)
       {
        return name.len && name[0]=='.' ;
       }

     public:

      explicit Proc(FindFiles &obj_) : obj(obj_) {}

      using DataType = void ;

      DataType * dir(StrLen root)
       {
        Used(root);

        return this;
       }

      DataType * dir(StrLen path,StrLen name,DataType *parent_data)
       {
        Used(path);

        if( !parent_data || SkipDir(name) ) return 0;

        return this;
       }

      void file(StrLen path,StrLen name,DataType *parent_data)
       {
        if( !parent_data || SkipFile(name) ) return;

        obj.appendFile(path,name);
       }

      void enddir(StrLen path,StrLen name,DataType *data)
       {
        Used(path);
        Used(name);
        Used(data);
       }
    };

   void appendFile(StrLen path,StrLen name)
    {
     if( name.hasSuffix(".cpp"_c) )
       {
        cpp_list.append_fill(pool.cat(path,"/"_c,name));
       }
     else if( name.hasSuffix(".s"_c) )
       {
        s_list.append_fill(pool.cat(path,"/"_c,name));
       }
    }

   void append(StrLen dir)
    {
     DirTreeRun dev(dir);
     Proc proc(*this);

     dev.apply(proc);
    }

  public:

   Collector<FileName> cpp_list;
   Collector<FileName> s_list;

   explicit FindFiles(PtrLen<const char *const> dir_list)
    {
     for(StrLen dir : dir_list ) append(dir);
    }
 };

/* class FindEngine */

class FindEngine : NoCopy
 {
   FindFiles find;

   EngineBase engine;

  public:

   FindEngine(StrLen obj_path,PtrLen<const char *const> dir_list)
    : find(dir_list),
      engine(obj_path,find.cpp_list,find.s_list)
    {
    }

   ~FindEngine() {}

   int run() { return engine.run(); }
 };

} // namespace App

/* main() */

using namespace App;

int usage()
 {
  Putobj(Con,"Usage: CCore-MakeList <obj-path> <cpp-list-file-name> <s-list-file-name>\n");
  Putobj(Con,"OR     CCore-MakeList <obj-path> -s <dir1> <dir2> ...\n");

  return 1;
 }

int main(int argc,const char *argv[])
 {
  try
    {
     ReportException report;

     int ret;

     {
      Putobj(Con,"--- MakeList 2.00 ---\n--- Copyright (c) 2015 Sergey Strukov. All rights reserved. ---\n\n");

      if( argc<4 ) return usage();

      StrLen arg2(argv[2]);

      if( arg2.equal("-s"_c) )
        {
         FindEngine engine(argv[1],Range(argv+3,argc-3));

         ret=engine.run();
        }
      else
        {
         if( argc!=4 ) return usage();

         FileEngine engine(argv[1],argv[2],argv[3]);

         ret=engine.run();
        }
     }

     report.guard();

     return ret;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

