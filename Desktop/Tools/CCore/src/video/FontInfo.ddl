/* FontInfo.ddl */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

type Bool = uint8 ;

Bool True = 1 ;
Bool False = 0 ;

struct FontInfo
 {
  text file_name;

  text family;
  text style;
  
  uint font_class;

  Bool scalable;
  Bool monospace;
  Bool italic;
  Bool bold;
 };

type FontDatabase = FontInfo[] ;
