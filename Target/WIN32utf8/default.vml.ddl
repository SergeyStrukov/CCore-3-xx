/* default.vml.ddl */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

text CCoreRoot = "../.." ;

text CCoreTarget = "WIN32utf8" ;

Param Data = {

.OBJ_PATH = ".vmobj" ,

.SRC_PATH_LIST = {
                  CCoreRoot+"/Simple/CCore/src",
                  CCoreRoot+"/Fundamental/CCore/src",
                  CCoreRoot+"/Applied/CCore/src",
                  CCoreRoot+"/Desktop/Core/CCore/src",
                  CCoreRoot+"/Desktop/Draw/CCore/src",
                  CCoreRoot+"/Desktop/Font/CCore/src",
                  CCoreRoot+"/Desktop/Lib/CCore/src",
                  CCoreRoot+"/Desktop/Tools/CCore/src",
                  CCoreRoot+"/Desktop/App/CCore/src",
                  CCoreRoot+"/HCore/CCore/src",
                  "CCore/src"
                 },

.target = TargetCCore

};

