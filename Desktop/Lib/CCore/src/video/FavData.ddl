/* FavData.ddl */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

type Bool = uint8 ;

Bool True = 1 ;
Bool False = 0 ;

struct FavElement
 {
  text title;
  text path;
  Bool section = False ;
  Bool open = True ;
 };

struct FavData
 {
  FavElement[] list;
  
  ulen off = 0 ;
  ulen cur = 0 ;  
 };
 
 