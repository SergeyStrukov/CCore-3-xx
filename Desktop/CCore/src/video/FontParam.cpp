/* FontParam.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
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

#include <CCore/inc/video/FontParam.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Video {

/* struct FontParam */

const char * GetTextDesc(FontParam::EngineType engine_type)
 {
  switch( engine_type )
    {
     default: return "???";

     case FontParam::EngineDefault : return "EngineDefault";

     case FontParam::EngineFreeType : return "EngineFreeType";
    }
 }

const char * GetTextDesc(FontParam::SizeType size_type)
 {
  switch( size_type )
    {
     default: return "???";

     case FontParam::SizeXY : return "SizeXY";

     case FontParam::SizePoint : return "SizePoint";

     case FontParam::SizeIndex : return "SizeIndex";
    }
 }

Font FontParam::create() const
 {
  switch( engine_type )
    {
     default:
      {
       Printf(Exception,"CCore::Video::FontParam::create() : unknown engine type #;",engine_type);
      }
     [[fallthrough]];

     case EngineDefault : return Font();

     case EngineFreeType :
      {
       FreeTypeFont ret(Range(file_name));

       switch( size_type )
         {
          case SizeXY :
           {
            ret.setSize(set_size.size_xy);
           }
          break;

          case SizePoint :
           {
            ret.setSize(set_size.size);
           }
          break;

          case SizeIndex :
           {
            ret.setFixedSize(set_size.index);
           }
          break;

          default:
           {
            Printf(Exception,"CCore::Video::FontParam::create() : unknown size type #;",size_type);
           }
         }

       ret.setConfig(cfg);

       return ret;
      }
    }
 }

} // namespace Video
} // namespace CCore

