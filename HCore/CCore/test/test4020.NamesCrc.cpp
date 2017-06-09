/* test4020.NamesCrc.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: HCore Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/FileToMem.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/Sort.h>
#include <CCore/inc/Crc.h>
#include <CCore/inc/CharProp.h>
#include <CCore/inc/algon/SortUnique.h>

namespace App {

namespace Private_4020 {

/* struct Rec<Crc> */

template <class Crc>
struct Rec
 {
  StrLen name;
  typename Crc::ResultType crc;

  Rec(StrLen name_)
   : name(name_)
   {
    Crc dev;

    dev.addRange(name);

    crc=dev;
   }

  bool operator < (const Rec<Crc> &obj) const
   {
    return crc<obj.crc || ( crc==obj.crc && StrLess(name,obj.name) ) ;
   }

  template <class P>
  void print(P &out) const
   {
    Printf(out,"#8.16i; #;",crc,name);
   }
 };

/* struct StrEqual */

struct StrEqual
 {
  StrLen str;

  StrEqual(StrLen str_) : str(str_) {}

  auto operator != (StrEqual obj) const
   {
    return StrCmp(str,obj.str);
   }
 };

/* class Engine<Crc> */

template <class Crc>
class Engine : NoCopy
 {
   FileToMem text_file;
   PrintFile out_file;

   DynArray<Rec<Crc> > rec_list;

  private:

   void fillList()
    {
     Printf(Con,"fill...");

     for(StrLen text=Mutate<const char>(Range(text_file)); +text ;)
       {
        StrLen name=CutLine(text);

        rec_list.append_fill(name);
       }

     Printf(Con," done\n");
    }

   void sortList()
    {
     Printf(Con,"sort...");

     Sort(Range(rec_list));

     Printf(Con," done\n");
    }

   ulen process(PtrLen<const Rec<Crc> > list)
    {
     ulen count=0;

     Algon::ApplyUniqueBy(list, [] (const Rec<Crc> &rec) -> StrEqual { return rec.name; } ,
                                [&] (const Rec<Crc> &rec)
                                    {
                                     count++;

                                     if( count>1 )
                                       {
                                        if( count==2 ) Printf(out_file,"#;\n",*list);

                                        Printf(out_file,"#;\n",rec);
                                       }

                                    } );

     if( count>1 )
       {
        Printf(out_file,"\ncount = #;\n\n#;\n\n",count,TextDivider());
       }

     return count;
    }

   void cutList()
    {
     Printf(Con,"cut...");

     Printf(out_file,"#;\n\n",TextDivider());

     ulen max_count=0;

     Algon::ApplyUniqueRangeBy(Range_const(rec_list), [] (const Rec<Crc> &rec) { return rec.crc; } ,
                                                      [&] (PtrLen<const Rec<Crc> > r) { Replace_max(max_count,process(r)); } );

     Printf(Con," done\n\nmax_count = #;\n\n",max_count);

     Printf(out_file,"max_count = #;\n",max_count);
    }

   void printList()
    {
     Printf(out_file,"name list #;\n\n",rec_list.getLen());

     for(auto r=Range_const(rec_list); +r ;++r)
       {
        Printf(out_file,"#;\n",*r);
       }
    }

  public:

   Engine(const char *text_file_name,const char *out_file_name)
    : text_file(text_file_name),
      out_file(out_file_name)
    {
    }

   ~Engine()
    {
    }

   void run()
    {
     fillList();

     sortList();

     cutList();

     //printList();
    }
 };

} // namespace Private_4020

using namespace Private_4020;

/* Testit<4020> */

template<>
const char *const Testit<4020>::Name="Test4020 NamesCrc";

template<>
bool Testit<4020>::Main()
 {
  {
   Printf(Con,"Crc16 test\n\n");

   Engine<Crc16>("../../../HCore/files/NameList.txt","Crc16Test.txt").run();
  }

  {
   Printf(Con,"Crc24 test\n\n");

   Engine<Crc24>("../../../HCore/files/NameList.txt","Crc24Test.txt").run();
  }

  {
   Printf(Con,"Crc32 test\n\n");

   Engine<Crc32>("../../../HCore/files/NameList.txt","Crc32Test.txt").run();
  }

  return true;
 }

} // namespace App

