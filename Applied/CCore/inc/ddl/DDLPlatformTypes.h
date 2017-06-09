/* DDLPlatformTypes.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_ddl_DDLPlatformTypes_h
#define CCore_inc_ddl_DDLPlatformTypes_h

#include <CCore/inc/Gadget.h>

namespace CCore {
namespace DDL {

/* types */

using sint_type = Meta::Select<( MaxUInt<unsigned> <= MaxUInt<uint32> ), sint32 , sint64 > ;

using uint_type = Meta::Select<( MaxUInt<unsigned> <= MaxUInt<uint32> ), uint32 , uint64 > ;

using ulen_type = Meta::Select<( MaxUInt<ulen> <= MaxUInt<uint32> && MaxUInt<unsigned> <= MaxUInt<uint32> ), uint32 , uint64 > ;

} // namespace DDL
} // namespace CCore

#endif


