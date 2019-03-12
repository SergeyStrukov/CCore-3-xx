Text b0 = { {
 { "Paths" }
} , & fmt_h2 , & align_h2 } ;

Text b1 = { {
 { "Files" }
 ,{ "CCore/inc/Path.h" , & fmt_text_Files_b }
 ,{ "CCore/src/Path.cpp" , & fmt_text_Files_b }
} , & fmt_text_Files , & align_text_Files } ;

Text b2 = { {
 { "There" }
 ,{ "is" }
 ,{ "a" }
 ,{ "set" }
 ,{ "of" }
 ,{ "classes" }
 ,{ "to" }
 ,{ "work" }
 ,{ "with" }
 ,{ "file" }
 ,{ "paths." }
 ,{ "A" }
 ,{ "path" }
 ,{ "may" }
 ,{ "have" }
 ,{ "the" }
 ,{ "following" }
 ,{ "components:" }
} , & fmt_text , & align_text } ;

Text b3_0 = { {
 { "device," }
 ,{ "ended" }
 ,{ "with" }
 ,{ "':'" , & fmt_list_b }
} , & fmt_list , & align_list } ;

Text b3_1 = { {
 { "directory," }
 ,{ "separated" }
 ,{ "with" }
 ,{ "'/'" , & fmt_list_b }
 ,{ "or" }
 ,{ "'\\'" , & fmt_list_b }
} , & fmt_list , & align_list } ;

Text b3_2 = { {
 { "file" }
 ,{ "name" }
} , & fmt_list , & align_list } ;

Text b3_3 = { {
 { "file" }
 ,{ "extension," }
 ,{ "started" }
 ,{ "with" }
 ,{ "'.'" , & fmt_list_b }
} , & fmt_list , & align_list } ;

TextList b3 = { {
 { '1.' , { { & b3_0 , null , ItemInner , ItemOuter } } }
 ,{ '2.' , { { & b3_1 , null , ItemInner , ItemOuter } } }
 ,{ '3.' , { { & b3_2 , null , ItemInner , ItemOuter } } }
 ,{ '4.' , { { & b3_3 , null , ItemInner , ItemOuter } } }
} } ;

Text b4 = { {
 { "A" }
 ,{ "path" }
 ,{ "may" }
 ,{ "have" }
 ,{ "multiple" }
 ,{ "device" }
 ,{ "components," }
 ,{ "directory" }
 ,{ "components," }
 ,{ "a" }
 ,{ "file" }
 ,{ "name" }
 ,{ "may" }
 ,{ "have" }
 ,{ "multiple" }
 ,{ "file" }
 ,{ "extension" }
 ,{ "components:" }
} , & fmt_text , & align_text } ;

Text b5 = { {
 { "PrefixPath()" }
} , & fmt_h4 , & align_h4 } ;

Text b6 = { {
 { "PrefixPath()" , & fmt_text_b }
 ,{ "returns" }
 ,{ "the" }
 ,{ "prefix" }
 ,{ "of" }
 ,{ "the" }
 ,{ "given" }
 ,{ "file" }
 ,{ "name" }
 ,{ "which" }
 ,{ "is" }
 ,{ "a" }
 ,{ "path." }
 ,{ "I.e." }
} , & fmt_text , & align_text } ;

Text b7 = { {
 { "But" }
} , & fmt_text , & align_text } ;

Text b8 = { {
 { "SuffixExt()" }
} , & fmt_h4 , & align_h4 } ;

Text b9 = { {
 { "SuffixExt()" , & fmt_text_b }
 ,{ "returns" }
 ,{ "the" }
 ,{ "suffix" }
 ,{ "of" }
 ,{ "the" }
 ,{ "given" }
 ,{ "file" }
 ,{ "name" }
 ,{ "which" }
 ,{ "is" }
 ,{ "an" }
 ,{ "extension." }
 ,{ "I.e." }
} , & fmt_text , & align_text } ;

Text b10 = { {
 { "PathBase" }
} , & fmt_h4 , & align_h4 } ;

Text b11 = { {
 { "This" }
 ,{ "structure" }
 ,{ "is" }
 ,{ "a" }
 ,{ "collection" }
 ,{ "of" }
 ,{ "tools" }
 ,{ "for" }
 ,{ "the" }
 ,{ "path" }
 ,{ "scanning." }
} , & fmt_text , & align_text } ;

Text b12 = { {
 { "IsSlash()" , & fmt_text_b }
 ,{ "tests" }
 ,{ "if" }
 ,{ "the" }
 ,{ "given" }
 ,{ "character" }
 ,{ "is" }
 ,{ "a" }
 ,{ "slash." }
} , & fmt_text , & align_text } ;

Text b13 = { {
 { "IsDot()" , & fmt_text_b }
 ,{ "tests" }
 ,{ "if" }
 ,{ "the" }
 ,{ "given" }
 ,{ "character" }
 ,{ "is" }
 ,{ "dot." }
} , & fmt_text , & align_text } ;

Text b14 = { {
 { "IsColon()" , & fmt_text_b }
 ,{ "tests" }
 ,{ "if" }
 ,{ "the" }
 ,{ "given" }
 ,{ "character" }
 ,{ "is" }
 ,{ "colon." }
} , & fmt_text , & align_text } ;

Text b15 = { {
 { "IsDot()" , & fmt_text_b }
 ,{ "tests" }
 ,{ "if" }
 ,{ "the" }
 ,{ "given" }
 ,{ "name" }
 ,{ "is" }
 ,{ "the" }
 ,{ "single" }
 ,{ "dot" }
 ,{ "name." }
} , & fmt_text , & align_text } ;

Text b16 = { {
 { "IsDotDot()" , & fmt_text_b }
 ,{ "tests" }
 ,{ "if" }
 ,{ "the" }
 ,{ "given" }
 ,{ "name" }
 ,{ "is" }
 ,{ "the" }
 ,{ "double" }
 ,{ "dot" }
 ,{ "name." }
} , & fmt_text , & align_text } ;

Text b17 = { {
 { "IsSpecial()" , & fmt_text_b }
 ,{ "tests" }
 ,{ "if" }
 ,{ "the" }
 ,{ "given" }
 ,{ "name" }
 ,{ "is" }
 ,{ "a" }
 ,{ "special" }
 ,{ "name," }
 ,{ "i.e." }
 ,{ "is" }
 ,{ "the" }
 ,{ "single" }
 ,{ "dot" }
 ,{ "or" }
 ,{ "double" }
 ,{ "dot" }
 ,{ "name." }
} , & fmt_text , & align_text } ;

Text b18 = { {
 { "IsTilde()" , & fmt_text_b }
 ,{ "tests" }
 ,{ "if" }
 ,{ "the" }
 ,{ "given" }
 ,{ "name" }
 ,{ "is" }
 ,{ "the" }
 ,{ "single" }
 ,{ "tilde" }
 ,{ "name." }
} , & fmt_text , & align_text } ;

Text b19 = { {
 { "TurnSlash()" , & fmt_text_b }
 ,{ "turns" }
 ,{ "all" }
 ,{ "slashes" }
 ,{ "into" }
 ,{ "'/'" , & fmt_text_b }
 ,{ "." }
} , & fmt_text , & align_text } ;

Text b20 = { {
 { "GetNameType()" , & fmt_text_b }
 ,{ "checks" }
 ,{ "the" }
 ,{ "type" }
 ,{ "of" }
 ,{ "the" }
 ,{ "given" }
 ,{ "name." }
 ,{ "There" }
 ,{ "are" }
 ,{ "four" }
 ,{ "possible" }
 ,{ "answers:" }
} , & fmt_text , & align_text } ;

Text b21_0 = { {
 { "Name" }
 ,{ "$" }
 ,{ "a" }
 ,{ "regular" }
 ,{ "file" }
 ,{ "name" }
} , & fmt_list , & align_list } ;

Text b21_1 = { {
 { "EmptyName" }
 ,{ "$" }
 ,{ "the" }
 ,{ "empty" }
 ,{ "name" }
} , & fmt_list , & align_list } ;

Text b21_2 = { {
 { "DotName" }
 ,{ "$" }
 ,{ "the" }
 ,{ "single" }
 ,{ "dot" }
 ,{ "name" }
} , & fmt_list , & align_list } ;

Text b21_3 = { {
 { "DotDotName" }
 ,{ "$" }
 ,{ "the" }
 ,{ "double" }
 ,{ "dot" }
 ,{ "name" }
} , & fmt_list , & align_list } ;

TextList b21 = { {
 { '•' , { { & b21_0 , null , ItemInner , ItemOuter } } }
 ,{ '•' , { { & b21_1 , null , ItemInner , ItemOuter } } }
 ,{ '•' , { { & b21_2 , null , ItemInner , ItemOuter } } }
 ,{ '•' , { { & b21_3 , null , ItemInner , ItemOuter } } }
} } ;

Text b22 = { {
 { "The" }
 ,{ "following" }
 ,{ "set" }
 ,{ "of" }
 ,{ "classes" }
 ,{ "is" }
 ,{ "used" }
 ,{ "to" }
 ,{ "split" }
 ,{ "the" }
 ,{ "given" }
 ,{ "string" }
 ,{ "into" }
 ,{ "components." }
} , & fmt_text , & align_text } ;

Text b23 = { {
 { "ForwardScan" , & fmt_text_b }
 ,{ "scans" }
 ,{ "forward" }
 ,{ "the" }
 ,{ "given" }
 ,{ "string" }
 ,{ "for" }
 ,{ "the" }
 ,{ "character," }
 ,{ "satisfying" }
 ,{ "the" }
 ,{ "given" }
 ,{ "condition." }
 ,{ "If" }
 ,{ "such" }
 ,{ "character" }
 ,{ "is" }
 ,{ "found," }
 ,{ "it" }
 ,{ "calls" }
 ,{ "the" }
 ,{ "method" }
 ,{ "set(StrLen" , & fmt_text_b }
 ,{ "str,StrLen" , & fmt_text_b }
 ,{ "cur)" , & fmt_text_b }
 ,{ "of" }
 ,{ "the" }
 ,{ "base" }
 ,{ "class." }
 ,{ "Otherwise" }
 ,{ "the" }
 ,{ "method" }
 ,{ "set(StrLen" , & fmt_text_b }
 ,{ "str)" , & fmt_text_b }
 ,{ "is" }
 ,{ "called." }
} , & fmt_text , & align_text } ;

Text b24 = { {
 { "BackwardScan" , & fmt_text_b }
 ,{ "is" }
 ,{ "similar" }
 ,{ "to" }
 ,{ "the" }
 ,{ "ForwardScan" , & fmt_text_b }
 ,{ "," }
 ,{ "but" }
 ,{ "scans" }
 ,{ "backward." }
} , & fmt_text , & align_text } ;

Text b25 = { {
 { "The" }
 ,{ "remaining" }
 ,{ "classes" }
 ,{ "are" }
 ,{ "used" }
 ,{ "to" }
 ,{ "split" }
 ,{ "the" }
 ,{ "string" }
 ,{ "at" }
 ,{ "the" }
 ,{ "found" }
 ,{ "position." }
} , & fmt_text , & align_text } ;

Text b26 = { {
 { "ToPrefix" , & fmt_text_b }
 ,{ "splits" }
 ,{ "after" }
 ,{ "the" }
 ,{ "found" }
 ,{ "position," }
 ,{ "i.e." }
 ,{ "the" }
 ,{ "found" }
 ,{ "character" }
 ,{ "goes" }
 ,{ "to" }
 ,{ "the" }
 ,{ "prefix." }
 ,{ "In" }
 ,{ "case" }
 ,{ "the" }
 ,{ "required" }
 ,{ "character" }
 ,{ "is" }
 ,{ "not" }
 ,{ "found," }
 ,{ "the" }
 ,{ "prefix" }
 ,{ "is" }
 ,{ "empty." }
} , & fmt_text , & align_text } ;

Text b27 = { {
 { "ToPrefixDel" , & fmt_text_b }
 ,{ "is" }
 ,{ "similar" }
 ,{ "to" }
 ,{ "the" }
 ,{ "ToPrefix" , & fmt_text_b }
 ,{ "," }
 ,{ "but" }
 ,{ "it" }
 ,{ "removes" }
 ,{ "the" }
 ,{ "found" }
 ,{ "character" }
 ,{ "from" }
 ,{ "the" }
 ,{ "prefix." }
} , & fmt_text , & align_text } ;

Text b28 = { {
 { "ToSuffix" , & fmt_text_b }
 ,{ "splits" }
 ,{ "before" }
 ,{ "the" }
 ,{ "found" }
 ,{ "position," }
 ,{ "i.e." }
 ,{ "the" }
 ,{ "found" }
 ,{ "character" }
 ,{ "goes" }
 ,{ "to" }
 ,{ "the" }
 ,{ "suffix." }
 ,{ "In" }
 ,{ "case" }
 ,{ "the" }
 ,{ "required" }
 ,{ "character" }
 ,{ "is" }
 ,{ "not" }
 ,{ "found," }
 ,{ "the" }
 ,{ "suffix" }
 ,{ "is" }
 ,{ "empty." }
} , & fmt_text , & align_text } ;

Text b29 = { {
 { "SplitDev" }
} , & fmt_h4 , & align_h4 } ;

Text b30 = { {
 { "This" }
 ,{ "Class-function" , & fmt_text_b }
 ,{ "splits" }
 ,{ "the" }
 ,{ "given" }
 ,{ "path" }
 ,{ "into" }
 ,{ "the" }
 ,{ "first" }
 ,{ "device" }
 ,{ "component" }
 ,{ "and" }
 ,{ "the" }
 ,{ "rest." }
 ,{ "The" }
 ,{ "no_dev" , & fmt_text_b }
 ,{ "is" }
 ,{ "true" , & fmt_text_b }
 ,{ "," }
 ,{ "if" }
 ,{ "there" }
 ,{ "is" }
 ,{ "no" }
 ,{ "device" }
 ,{ "component." }
 ,{ "In" }
 ,{ "this" }
 ,{ "case" }
 ,{ "the" }
 ,{ "dev" , & fmt_text_b }
 ,{ "is" }
 ,{ "null" }
 ,{ "and" }
 ,{ "the" }
 ,{ "dev_path" , & fmt_text_b }
 ,{ "is" }
 ,{ "the" }
 ,{ "given" }
 ,{ "path." }
 ,{ "Colon" }
 ,{ "goes" }
 ,{ "to" }
 ,{ "the" }
 ,{ "dev" , & fmt_text_b }
 ,{ "." }
} , & fmt_text , & align_text } ;

Text b31 = { {
 { "SplitPath" }
} , & fmt_h4 , & align_h4 } ;

Text b32 = { {
 { "This" }
 ,{ "Class-function" , & fmt_text_b }
 ,{ "splits" }
 ,{ "the" }
 ,{ "given" }
 ,{ "path" }
 ,{ "into" }
 ,{ "the" }
 ,{ "all" }
 ,{ "device" }
 ,{ "components" }
 ,{ "and" }
 ,{ "the" }
 ,{ "rest." }
 ,{ "The" }
 ,{ "no_dev" , & fmt_text_b }
 ,{ "is" }
 ,{ "true" , & fmt_text_b }
 ,{ "," }
 ,{ "if" }
 ,{ "there" }
 ,{ "is" }
 ,{ "no" }
 ,{ "device" }
 ,{ "component." }
 ,{ "In" }
 ,{ "this" }
 ,{ "case" }
 ,{ "the" }
 ,{ "dev" , & fmt_text_b }
 ,{ "is" }
 ,{ "null" }
 ,{ "and" }
 ,{ "the" }
 ,{ "path" , & fmt_text_b }
 ,{ "is" }
 ,{ "the" }
 ,{ "given" }
 ,{ "path." }
 ,{ "Colon" }
 ,{ "goes" }
 ,{ "to" }
 ,{ "the" }
 ,{ "dev" , & fmt_text_b }
 ,{ "." }
} , & fmt_text , & align_text } ;

Text b33 = { {
 { "SplitDir" }
} , & fmt_h4 , & align_h4 } ;

Text b34 = { {
 { "This" }
 ,{ "Class-function" , & fmt_text_b }
 ,{ "splits" }
 ,{ "the" }
 ,{ "given" }
 ,{ "path" }
 ,{ "(assumed" }
 ,{ "without" }
 ,{ "device" }
 ,{ "component)" }
 ,{ "into" }
 ,{ "the" }
 ,{ "first" }
 ,{ "directory" }
 ,{ "component" }
 ,{ "and" }
 ,{ "the" }
 ,{ "rest." }
 ,{ "The" }
 ,{ "no_path" , & fmt_text_b }
 ,{ "is" }
 ,{ "true" , & fmt_text_b }
 ,{ "," }
 ,{ "if" }
 ,{ "there" }
 ,{ "is" }
 ,{ "no" }
 ,{ "directory" }
 ,{ "component." }
 ,{ "In" }
 ,{ "this" }
 ,{ "case" }
 ,{ "the" }
 ,{ "dir" , & fmt_text_b }
 ,{ "is" }
 ,{ "null" }
 ,{ "and" }
 ,{ "the" }
 ,{ "path" , & fmt_text_b }
 ,{ "is" }
 ,{ "the" }
 ,{ "given" }
 ,{ "path." }
 ,{ "Slash" }
 ,{ "goes" }
 ,{ "to" }
 ,{ "the" }
 ,{ "dir" , & fmt_text_b }
 ,{ "." }
} , & fmt_text , & align_text } ;

Text b35 = { {
 { "SplitName" }
} , & fmt_h4 , & align_h4 } ;

Text b36 = { {
 { "This" }
 ,{ "Class-function" , & fmt_text_b }
 ,{ "splits" }
 ,{ "the" }
 ,{ "given" }
 ,{ "path" }
 ,{ "(assumed" }
 ,{ "without" }
 ,{ "device" }
 ,{ "component)" }
 ,{ "into" }
 ,{ "the" }
 ,{ "all" }
 ,{ "directory" }
 ,{ "components" }
 ,{ "and" }
 ,{ "the" }
 ,{ "rest." }
 ,{ "The" }
 ,{ "no_path" , & fmt_text_b }
 ,{ "is" }
 ,{ "true" , & fmt_text_b }
 ,{ "," }
 ,{ "if" }
 ,{ "there" }
 ,{ "is" }
 ,{ "no" }
 ,{ "directory" }
 ,{ "component." }
 ,{ "In" }
 ,{ "this" }
 ,{ "case" }
 ,{ "path" , & fmt_text_b }
 ,{ "is" }
 ,{ "null" }
 ,{ "and" }
 ,{ "the" }
 ,{ "name" , & fmt_text_b }
 ,{ "is" }
 ,{ "the" }
 ,{ "given" }
 ,{ "path." }
 ,{ "Slash" }
 ,{ "goes" }
 ,{ "to" }
 ,{ "the" }
 ,{ "path" , & fmt_text_b }
 ,{ "." }
} , & fmt_text , & align_text } ;

Text b37 = { {
 { "getNameType()" , & fmt_text_b }
 ,{ "returns" }
 ,{ "the" }
 ,{ "type" }
 ,{ "of" }
 ,{ "the" }
 ,{ "file" }
 ,{ "name" }
 ,{ "component." }
} , & fmt_text , & align_text } ;

Text b38 = { {
 { "SplitFullExt" }
} , & fmt_h4 , & align_h4 } ;

Text b39 = { {
 { "This" }
 ,{ "Class-function" , & fmt_text_b }
 ,{ "splits" }
 ,{ "the" }
 ,{ "given" }
 ,{ "file" }
 ,{ "name" }
 ,{ "into" }
 ,{ "the" }
 ,{ "all" }
 ,{ "extensions" }
 ,{ "and" }
 ,{ "the" }
 ,{ "name." }
 ,{ "The" }
 ,{ "no_ext" , & fmt_text_b }
 ,{ "is" }
 ,{ "true" , & fmt_text_b }
 ,{ "," }
 ,{ "if" }
 ,{ "there" }
 ,{ "is" }
 ,{ "no" }
 ,{ "extension." }
 ,{ "In" }
 ,{ "this" }
 ,{ "case" }
 ,{ "the" }
 ,{ "ext" , & fmt_text_b }
 ,{ "is" }
 ,{ "null" }
 ,{ "and" }
 ,{ "the" }
 ,{ "name" , & fmt_text_b }
 ,{ "is" }
 ,{ "the" }
 ,{ "given" }
 ,{ "name." }
 ,{ "Dot" }
 ,{ "goes" }
 ,{ "to" }
 ,{ "the" }
 ,{ "ext" , & fmt_text_b }
 ,{ "." }
} , & fmt_text , & align_text } ;

Text b40 = { {
 { "SplitExt" }
} , & fmt_h4 , & align_h4 } ;

Text b41 = { {
 { "This" }
 ,{ "Class-function" , & fmt_text_b }
 ,{ "splits" }
 ,{ "the" }
 ,{ "given" }
 ,{ "file" }
 ,{ "name" }
 ,{ "into" }
 ,{ "the" }
 ,{ "last" }
 ,{ "extension" }
 ,{ "and" }
 ,{ "the" }
 ,{ "rest." }
 ,{ "The" }
 ,{ "no_ext" , & fmt_text_b }
 ,{ "is" }
 ,{ "true" , & fmt_text_b }
 ,{ "," }
 ,{ "if" }
 ,{ "there" }
 ,{ "is" }
 ,{ "no" }
 ,{ "extension." }
 ,{ "In" }
 ,{ "this" }
 ,{ "case" }
 ,{ "the" }
 ,{ "ext" , & fmt_text_b }
 ,{ "is" }
 ,{ "null" }
 ,{ "and" }
 ,{ "the" }
 ,{ "name" , & fmt_text_b }
 ,{ "is" }
 ,{ "the" }
 ,{ "given" }
 ,{ "name." }
 ,{ "Dot" }
 ,{ "goes" }
 ,{ "to" }
 ,{ "the" }
 ,{ "ext" , & fmt_text_b }
 ,{ "." }
} , & fmt_text , & align_text } ;

Text b42 = { {
 { "SplitDevName" }
} , & fmt_h4 , & align_h4 } ;

Text b43 = { {
 { "SplitDevName" , & fmt_text_b }
 ,{ "is" }
 ,{ "similar" }
 ,{ "to" }
 ,{ "the" }
 ,{ "SplitDev" , & fmt_text_b }
 ,{ "," }
 ,{ "except" }
 ,{ "it" }
 ,{ "removes" }
 ,{ "colon" }
 ,{ "from" }
 ,{ "the" }
 ,{ "dev_name" , & fmt_text_b }
 ,{ "." }
} , & fmt_text , & align_text } ;

Text b44 = { {
 { "SplitDirName" }
} , & fmt_h4 , & align_h4 } ;

Text b45 = { {
 { "SplitDirName" , & fmt_text_b }
 ,{ "is" }
 ,{ "similar" }
 ,{ "to" }
 ,{ "the" }
 ,{ "SplitDir" , & fmt_text_b }
 ,{ "," }
 ,{ "except" }
 ,{ "it" }
 ,{ "removes" }
 ,{ "slash" }
 ,{ "from" }
 ,{ "the" }
 ,{ "dir_name" , & fmt_text_b }
 ,{ "." }
} , & fmt_text , & align_text } ;

Text b46 = { {
 { "getNameType()" , & fmt_text_b }
 ,{ "returns" }
 ,{ "the" }
 ,{ "type" }
 ,{ "of" }
 ,{ "the" }
 ,{ "directory" }
 ,{ "name" }
 ,{ "component." }
} , & fmt_text , & align_text } ;

Text b47 = { {
 { "SplitPathName" }
} , & fmt_h4 , & align_h4 } ;

Text b48 = { {
 { "SplitPathName" , & fmt_text_b }
 ,{ "is" }
 ,{ "similar" }
 ,{ "to" }
 ,{ "the" }
 ,{ "SplitName" , & fmt_text_b }
 ,{ "," }
 ,{ "except" }
 ,{ "it" }
 ,{ "removes" }
 ,{ "slash" }
 ,{ "from" }
 ,{ "the" }
 ,{ "path" , & fmt_text_b }
 ,{ "." }
} , & fmt_text , & align_text } ;

Text b49 = { {
 { "WalkPath()" }
} , & fmt_h4 , & align_h4 } ;

Text b50 = { {
 { "This" }
 ,{ "function" }
 ,{ "calls" }
 ,{ "the" }
 ,{ "second" }
 ,{ "argument" }
 ,{ "for" }
 ,{ "each" }
 ,{ "subpath" }
 ,{ "of" }
 ,{ "the" }
 ,{ "first" }
 ,{ "argument." }
 ,{ "I.e." }
} , & fmt_text , & align_text } ;

Text b51 = { {
 { "Path" }
} , & fmt_h4 , & align_h4 } ;

Text b52 = { {
 { "The" }
 ,{ "class" }
 ,{ "Path" , & fmt_text_b }
 ,{ "is" }
 ,{ "designed" }
 ,{ "to" }
 ,{ "manipulate" }
 ,{ "with" }
 ,{ "a" }
 ,{ "path." }
 ,{ "The" }
 ,{ "path" }
 ,{ "inside" }
 ,{ "Path" , & fmt_text_b }
 ,{ "is" }
 ,{ "stored" }
 ,{ "in" }
 ,{ "the" }
 ,{ "internal" }
 ,{ "buffer." }
 ,{ "It" }
 ,{ "has" }
 ,{ "a" }
 ,{ "non-mutable" }
 ,{ "prefix." }
 ,{ "This" }
 ,{ "prefix" }
 ,{ "is" }
 ,{ "determined" }
 ,{ "by" }
 ,{ "the" }
 ,{ "constructor." }
 ,{ "The" }
 ,{ "string" }
 ,{ "after" }
 ,{ "prefix" }
 ,{ "is" }
 ,{ "a" }
 ,{ "normalized" }
 ,{ "path." }
 ,{ "I.e." }
 ,{ "it" }
 ,{ "may" }
 ,{ "be" }
 ,{ "empty" }
 ,{ "or" }
 ,{ "\".\"" , & fmt_text_b }
 ,{ "or" }
 ,{ "\"dir1/dir2/.../dir_or_file\"" , & fmt_text_b }
 ,{ "," }
 ,{ "where" }
 ,{ "dir" , & fmt_text_b }
 ,{ "s" }
 ,{ "are" }
 ,{ "normal" }
 ,{ "names," }
 ,{ "dir_of_file" , & fmt_text_b }
 ,{ "may" }
 ,{ "be" }
 ,{ "\".\"" , & fmt_text_b }
 ,{ "." }
} , & fmt_text , & align_text } ;

Text b53 = { {
 { "Path(Path::BeginEmpty)" , & fmt_text_b }
 ,{ "constructor" }
 ,{ "creates" }
 ,{ "a" }
 ,{ "path" }
 ,{ "object" }
 ,{ "with" }
 ,{ "the" }
 ,{ "empty" }
 ,{ "path" }
 ,{ "prefix." }
} , & fmt_text , & align_text } ;

Text b54 = { {
 { "Path(Path::BeginRoot)" , & fmt_text_b }
 ,{ "constructor" }
 ,{ "creates" }
 ,{ "a" }
 ,{ "path" }
 ,{ "object" }
 ,{ "with" }
 ,{ "the" }
 ,{ "path" }
 ,{ "prefix" }
 ,{ "equals" }
 ,{ "\"/\"" , & fmt_text_b }
 ,{ "." }
} , & fmt_text , & align_text } ;

Text b55 = { {
 { "Path(StrLen" , & fmt_text_b }
 ,{ "dev_name)" , & fmt_text_b }
 ,{ "constructor" }
 ,{ "creates" }
 ,{ "a" }
 ,{ "path" }
 ,{ "object," }
 ,{ "which" }
 ,{ "has" }
 ,{ "the" }
 ,{ "path" }
 ,{ "prefix" }
 ,{ "dev_name+\":/\"" , & fmt_text_b }
 ,{ ";" }
} , & fmt_text , & align_text } ;

Text b56 = { {
 { "Path" , & fmt_text_b }
 ,{ "is" }
 ,{ "castable" }
 ,{ "to" }
 ,{ "the" }
 ,{ "StrLen" , & fmt_text_b }
 ,{ "type" }
 ,{ "and" }
 ,{ "printable" }
 ,{ "using" }
 ,{ "this" }
 ,{ "type" }
 ,{ "as" }
 ,{ "the" }
 ,{ "PrintProxyType" , & fmt_text_b }
 ,{ "." }
} , & fmt_text , & align_text } ;

Text b57 = { {
 { "root()" , & fmt_text_b }
 ,{ "sets" }
 ,{ "the" }
 ,{ "Path" , & fmt_text_b }
 ,{ "value" }
 ,{ "to" }
 ,{ "its" }
 ,{ "path" }
 ,{ "prefix." }
} , & fmt_text , & align_text } ;

Text b58 = { {
 { "rootDir()" , & fmt_text_b }
 ,{ "sets" }
 ,{ "the" }
 ,{ "Path" , & fmt_text_b }
 ,{ "value" }
 ,{ "to" }
 ,{ "its" }
 ,{ "path" }
 ,{ "prefix" }
 ,{ "+" }
 ,{ "\".\"" , & fmt_text_b }
 ,{ "." }
} , & fmt_text , & align_text } ;

Text b59 = { {
 { "isRoot()" , & fmt_text_b }
 ,{ "checks" }
 ,{ "if" }
 ,{ "the" }
 ,{ "object" }
 ,{ "is" }
 ,{ "at" }
 ,{ "the" }
 ,{ "root()" , & fmt_text_b }
 ,{ "state." }
} , & fmt_text , & align_text } ;

Text b60 = { {
 { "isRootDir()" , & fmt_text_b }
 ,{ "checks" }
 ,{ "if" }
 ,{ "the" }
 ,{ "object" }
 ,{ "is" }
 ,{ "at" }
 ,{ "the" }
 ,{ "rootDir()" , & fmt_text_b }
 ,{ "state." }
} , & fmt_text , & align_text } ;

Text b61 = { {
 { "add()" , & fmt_text_b }
 ,{ "adds" }
 ,{ "a" }
 ,{ "top" }
 ,{ "path" }
 ,{ "component." }
 ,{ "It" }
 ,{ "properly" }
 ,{ "handles" }
 ,{ "single" }
 ,{ "dot" }
 ,{ "and" }
 ,{ "double" }
 ,{ "dot" }
 ,{ "names." }
 ,{ "An" }
 ,{ "exception" }
 ,{ "is" }
 ,{ "thrown" }
 ,{ "in" }
 ,{ "case" }
 ,{ "of" }
 ,{ "error." }
} , & fmt_text , & align_text } ;

Text b62 = { {
 { "back()" , & fmt_text_b }
 ,{ "removes" }
 ,{ "the" }
 ,{ "top" }
 ,{ "path" }
 ,{ "component." }
 ,{ "The" }
 ,{ "path" }
 ,{ "must" }
 ,{ "not" }
 ,{ "be" }
 ,{ "in" }
 ,{ "the" }
 ,{ "root()" , & fmt_text_b }
 ,{ "or" }
 ,{ "the" }
 ,{ "rootDir()" , & fmt_text_b }
 ,{ "state" }
 ,{ "$" }
 ,{ "an" }
 ,{ "exception" }
 ,{ "will" }
 ,{ "be" }
 ,{ "thrown." }
} , & fmt_text , & align_text } ;

Text b63 = { {
 { "addPath()" , & fmt_text_b }
 ,{ "adds" }
 ,{ "multiple" }
 ,{ "path" }
 ,{ "components." }
 ,{ "If" }
 ,{ "the" }
 ,{ "argument" }
 ,{ "is" }
 ,{ "started" }
 ,{ "with" }
 ,{ "slash," }
 ,{ "then" }
 ,{ "path" , & fmt_text_b }
 ,{ "is" }
 ,{ "assumed" }
 ,{ "absolute," }
 ,{ "otherwise" }
 ,{ "$" }
 ,{ "relative" }
 ,{ "to" }
 ,{ "the" }
 ,{ "current" }
 ,{ "value." }
 ,{ "The" }
 ,{ "empty" }
 ,{ "argument" }
 ,{ "does" }
 ,{ "nothing." }
} , & fmt_text , & align_text } ;

Text b64 = { {
 { "copyPath()" , & fmt_text_b }
 ,{ "copies" }
 ,{ "the" }
 ,{ "argument." }
} , & fmt_text , & align_text } ;

Page page = { "test" ,
{
 { & b0 , null , inner_h2 , outer_h2 , back_h2 }
 ,{ & b1 , null , inner_text_Files , outer_text_Files , back_text_Files }
 ,{ & b2 , null , inner_text , outer_text , back_text }
 ,{ & b3 , null , inner_list , outer_list , back_list }
 ,{ & b4 , null , inner_text , outer_text , back_text }
 ,{ & b5 , null , inner_h4 , outer_h4 , back_h4 }
 ,{ & b6 , null , inner_text , outer_text , back_text }
 ,{ & b7 , null , inner_text , outer_text , back_text }
 ,{ & b8 , null , inner_h4 , outer_h4 , back_h4 }
 ,{ & b9 , null , inner_text , outer_text , back_text }
 ,{ & b10 , null , inner_h4 , outer_h4 , back_h4 }
 ,{ & b11 , null , inner_text , outer_text , back_text }
 ,{ & b12 , null , inner_text , outer_text , back_text }
 ,{ & b13 , null , inner_text , outer_text , back_text }
 ,{ & b14 , null , inner_text , outer_text , back_text }
 ,{ & b15 , null , inner_text , outer_text , back_text }
 ,{ & b16 , null , inner_text , outer_text , back_text }
 ,{ & b17 , null , inner_text , outer_text , back_text }
 ,{ & b18 , null , inner_text , outer_text , back_text }
 ,{ & b19 , null , inner_text , outer_text , back_text }
 ,{ & b20 , null , inner_text , outer_text , back_text }
 ,{ & b21 , null , inner_list , outer_list , back_list }
 ,{ & b22 , null , inner_text , outer_text , back_text }
 ,{ & b23 , null , inner_text , outer_text , back_text }
 ,{ & b24 , null , inner_text , outer_text , back_text }
 ,{ & b25 , null , inner_text , outer_text , back_text }
 ,{ & b26 , null , inner_text , outer_text , back_text }
 ,{ & b27 , null , inner_text , outer_text , back_text }
 ,{ & b28 , null , inner_text , outer_text , back_text }
 ,{ & b29 , null , inner_h4 , outer_h4 , back_h4 }
 ,{ & b30 , null , inner_text , outer_text , back_text }
 ,{ & b31 , null , inner_h4 , outer_h4 , back_h4 }
 ,{ & b32 , null , inner_text , outer_text , back_text }
 ,{ & b33 , null , inner_h4 , outer_h4 , back_h4 }
 ,{ & b34 , null , inner_text , outer_text , back_text }
 ,{ & b35 , null , inner_h4 , outer_h4 , back_h4 }
 ,{ & b36 , null , inner_text , outer_text , back_text }
 ,{ & b37 , null , inner_text , outer_text , back_text }
 ,{ & b38 , null , inner_h4 , outer_h4 , back_h4 }
 ,{ & b39 , null , inner_text , outer_text , back_text }
 ,{ & b40 , null , inner_h4 , outer_h4 , back_h4 }
 ,{ & b41 , null , inner_text , outer_text , back_text }
 ,{ & b42 , null , inner_h4 , outer_h4 , back_h4 }
 ,{ & b43 , null , inner_text , outer_text , back_text }
 ,{ & b44 , null , inner_h4 , outer_h4 , back_h4 }
 ,{ & b45 , null , inner_text , outer_text , back_text }
 ,{ & b46 , null , inner_text , outer_text , back_text }
 ,{ & b47 , null , inner_h4 , outer_h4 , back_h4 }
 ,{ & b48 , null , inner_text , outer_text , back_text }
 ,{ & b49 , null , inner_h4 , outer_h4 , back_h4 }
 ,{ & b50 , null , inner_text , outer_text , back_text }
 ,{ & b51 , null , inner_h4 , outer_h4 , back_h4 }
 ,{ & b52 , null , inner_text , outer_text , back_text }
 ,{ & b53 , null , inner_text , outer_text , back_text }
 ,{ & b54 , null , inner_text , outer_text , back_text }
 ,{ & b55 , null , inner_text , outer_text , back_text }
 ,{ & b56 , null , inner_text , outer_text , back_text }
 ,{ & b57 , null , inner_text , outer_text , back_text }
 ,{ & b58 , null , inner_text , outer_text , back_text }
 ,{ & b59 , null , inner_text , outer_text , back_text }
 ,{ & b60 , null , inner_text , outer_text , back_text }
 ,{ & b61 , null , inner_text , outer_text , back_text }
 ,{ & b62 , null , inner_text , outer_text , back_text }
 ,{ & b63 , null , inner_text , outer_text , back_text }
 ,{ & b64 , null , inner_text , outer_text , back_text }
} , NoColor , NoColor , null , null , null };

