/* FileNameMatch.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_FileNameMatch_h
#define CCore_inc_video_FileNameMatch_h

#include <CCore/inc/Array.h>

namespace CCore {

/* classes */

class FileNameFilter;

/* class FileNameFilter */

class FileNameFilter : NoCopy
 {
   class State;

   struct StateArrow;

   class FullState;

   class StateMap;

  private:

   class IndState
    {
      struct Arrow
       {
        char ch;
        ulen index;

        Arrow(const StateArrow &obj);
       };

      DynArray<Arrow> arrows;
      ulen other_index = MaxULen ;
      bool is_final;

     public:

      IndState(const FullState *state);

      // std move

      IndState(IndState &&) = default ;

      IndState & operator = (IndState &&) = default ;

      // methods

      bool isFinal() const { return is_final; }

      ulen next(char ch) const;
    };

   DynArray<IndState> states;

  private:

   void build(StrLen filter,ulen max_states);

  public:

   FileNameFilter() noexcept;

   explicit FileNameFilter(StrLen filter,ulen max_states=MaxULen);

   ~FileNameFilter();

   // props

   bool operator + () const { return states.getLen()!=0; }

   bool operator ! () const { return states.getLen()==0; }

   // methods

   void reset();

   void reset(StrLen filter,ulen max_states=MaxULen);

   bool operator () (StrLen file) const;
 };

} // namespace CCore

#endif

