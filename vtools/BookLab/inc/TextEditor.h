/* TextEditor.h */
//----------------------------------------------------------------------------------------
//
//  Project: BookLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef TextEditor_h
#define TextEditor_h

#include <inc/BookLab.h>

namespace App {

/* classes */

class TextEditor;

/* class TextEditor */

class TextEditor : public SubWindow
 {
  public:

   struct Config
    {
     // user

     RefVal<Coord> space_dxy = 10 ;

     RefVal<VColor> back = Silver ;

     // app

     template <class AppPref>
     Config(const UserPreference &user_pref,const AppPref &app_pref) noexcept
      {
       bindUser(user_pref.get(),user_pref.getSmartConfig());
       bindApp(app_pref.get());
      }

     template <class Bag,class Proxy>
     void bindUser(const Bag &bag,Proxy proxy)
      {
       Used(proxy);

       space_dxy.bind(bag.space_dxy);

       back.bind(bag.back);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       Used(bag);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

  public:

   TextEditor(SubWindowHost &host,const Config &cfg);

   virtual ~TextEditor();

   // methods

   Point getMinSize() const;

   void blank();

   void load(PtrLen<BookLab::Span> text);

   void load(PtrLen<BookLab::TextLine> text);

   void save(DynArray<BookLab::Span> *pad);

   void save(DynArray<BookLab::TextLine> *pad);
 };

} // namespace App

#endif


