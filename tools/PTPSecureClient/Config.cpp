/* Config.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: PTPSecureClient 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include "Config.h"

#include <CCore/inc/Print.h>
#include <CCore/inc/FileName.h>
#include <CCore/inc/FileToMem.h>
#include <CCore/inc/MemAllocGuard.h>

#include <CCore/inc/ddl/DDLEngine.h>
#include <CCore/inc/ddl/DDLTypeSet.h>

#include <CCore/inc/net/NetBase.h>

#include <CCore/inc/Exception.h>

namespace App {

/* TypeSet */

#include "Config.typeset.h"

/* class Config */

StrLen Config::Pretext()
 {
  return
  "struct Key"
  " {"
  "  const uint8 SHA1   = 0 ;"
  "  const uint8 SHA224 = 1 ;"
  "  const uint8 SHA256 = 2 ;"
  "  const uint8 SHA384 = 3 ;"
  "  const uint8 SHA512 = 4 ;"

  "  uint8 hash_id;"

  "  uint8[] key;"
  " };"

  "struct PTPSecureConfig"
  " {"
  "  uint16 server_pke_port  = 52102 ;"
  "  uint16 server_psec_port = 52103 ;"

  "  uint16 pke_port  = 52100 ;"
  "  uint16 psec_port = 52101 ;"

  "  uint16 keyset_len = 10 ;"
  "  uint32 ttl        = 3600 ;"
  "  uint32 utl        = 100000000 ;"

  "  ip server_ip = 127.0.0.1 ;"
  "  Key server_key;"

  "  text name;"
  "  Key key;"
  " };"_c;
 }

Config::Config(StrLen file_name)
 {
  PrintCon out;
  DDL::FileEngine<FileName,FileToMem> engine(out);

  auto result=engine.process(file_name,Pretext());

  out.flush();

  if( !result )
    {
     Printf(Exception,"App::Config::Config() : input file processing error");
    }
  else
    {
     DDL::TypedMap<TypeSet> map(result);
     MemAllocGuard guard(map.getLen());

     map(guard);

     config=map.findConst<TypeDef::PTPSecureConfig>("config");

     if( !config )
       {
        Printf(Exception,"App::Config::Config() : config is missed in the input file");
       }

     mem=guard.disarm();
    }
 }

Config::~Config()
 {
  MemFree(mem);
 }

void Config::show()
 {
  Printf(Con,"Server PKE port = #;\n",config->server_pke_port);
  Printf(Con,"Server PSec port = #;\n",config->server_psec_port);
  Printf(Con,"PKE port = #;\n",config->pke_port);
  Printf(Con,"PSec port = #;\n",config->psec_port);
  Printf(Con,"Keyset len = #;\n",config->keyset_len);
  Printf(Con,"TTL = #; sec\n",config->ttl);
  Printf(Con,"UTL = #; bytes\n",config->utl);
  Printf(Con,"Server IP = #;\n\n",Net::IPAddress(config->server_ip));
  Printf(Con,"Client name = #;\n\n",StrLen(config->name));
 }

} // namespace App



