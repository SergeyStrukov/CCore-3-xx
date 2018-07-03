/* ForLoop.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Simple Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_ForLoop_h
#define CCore_inc_ForLoop_h

#include <CCore/inc/Gadget.h>

namespace CCore {

/* classes */

template <SUIntType SUInt> class IndLim;

template <ForType Cur> class ForLoop;

/* class IndLim<SUInt> */

template <SUIntType SUInt>
class IndLim
 {
   SUInt ind;
   SUInt lim;

  public:

   IndLim(SUInt ind_,SUInt lim_) : ind(ind_),lim(lim_) {}

   explicit IndLim(SUInt lim_) : ind(0),lim(lim_) {}

   // loop

   bool operator != (Meta::Empty) const { return ind<lim; }

   SUInt operator * () const { return ind; }

   void operator ++ () { ind++; }

   // begin()/end()

   IndLim begin() const { return *this; }

   Meta::Empty end() const { return {}; }
 };

/* class ForLoop<Cur> */

template <ForType Cur>
class ForLoop
 {
   Cur cur;

  public:

   explicit ForLoop(const Cur &cur_) : cur(cur_) {}

   template <class ... SS>
   explicit ForLoop(SS && ... ss) : cur( std::forward<SS>(ss)... ) {}

   // loop

   bool operator != (Meta::Empty) const { return +cur; }

   decltype(auto) operator * () const { return *cur; }

   void operator ++ () { ++cur; }

   // begin()/end()

   ForLoop begin() const { return *this; }

   Meta::Empty end() const { return {}; }
 };

} // namespace CCore

#endif

