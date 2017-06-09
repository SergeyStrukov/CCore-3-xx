/* DDLEngine.cpp */
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

#include <CCore/inc/ddl/DDLEngine.h>

namespace CCore {
namespace DDL {

/* class TextEngine */

auto TextEngine::openFile(StrLen) -> File
 {
  return File(&id,text);
 }

TextEngine::TextEngine(PrintBase &msg,StrLen text_,StrLen pretext_)
 : ParserContext(msg),
   pretext(pretext_),
   text(text_)
 {
 }

TextEngine::~TextEngine()
 {
 }

EngineResult TextEngine::process()
 {
  if( BodyNode *body_node=parseFile(StrLen(),pretext) )
    {
     if( EvalContext::Process(error,pool,body_node,result) )
       {
        return EngineResult(&result,body_node);
       }
    }

  return Nothing;
 }

} // namespace DDL
} // namespace CCore


