Text b0 = { {
{ "Arrays" }
} , & fmt_h2 , & align_h2 } ;

Text b1 = { {
{ "Files" }
,{ "CCore/inc/Array.h" , & fmt_text_Files_b }
,{ "CCore/src/Array.cpp" , & fmt_text_Files_b }
} , & fmt_text_Files , & align_text_Files } ;

Text b2 = { {
{ "Subfolders" }
,{ "CCore/inc/array" , & fmt_text_Files_b }
,{ "CCore/src/array" , & fmt_text_Files_b }
} , & fmt_text_Files , & align_text_Files } ;

Text b3 = { {
{ "Helpers" }
} , & fmt_h3 , & align_h3 } ;

Text b4 = { {
{ "There" }
,{ "are" }
,{ "several" }
,{ "types" }
,{ "that" }
,{ "are" }
,{ "used" }
,{ "to" }
,{ "specify" }
,{ "the" }
,{ "constructor" }
,{ "behavior." }
} , & fmt_text , & align_text } ;

Text b5 = { {
{ "DoBuild" , & fmt_text_b }
,{ "and" }
,{ "DoReserve" , & fmt_text_b }
,{ "are" }
,{ "word" , & fmt_text_b }
,{ "s." }
,{ "They" }
,{ "designate" }
,{ "the" }
,{ "build" }
,{ "and" }
,{ "the" }
,{ "reserve" }
,{ "variant" }
,{ "of" }
,{ "the" }
,{ "constructor" }
,{ "respectively." }
} , & fmt_text , & align_text } ;

Text b6 = { {
{ "DoRaw" , & fmt_text_b }
,{ "," }
,{ "DoFill" , & fmt_text_b }
,{ "," }
,{ "DoCopy" , & fmt_text_b }
,{ "," }
,{ "DoCast" , & fmt_text_b }
,{ "," }
,{ "DoSwap" , & fmt_text_b }
,{ "," }
,{ "DoCreate" , & fmt_text_b }
,{ "are" }
,{ "not" }
,{ "word" , & fmt_text_b }
,{ "s," }
,{ "but" }
,{ "Small" , & fmt_text_b }
,{ "Data" , & fmt_text_b }
,{ "Type" , & fmt_text_b }
,{ "s." }
,{ "They" }
,{ "designate" }
,{ "the" }
,{ "correspondent" }
,{ "variant" }
,{ "of" }
,{ "the" }
,{ "constructor" }
,{ "and" }
,{ "carry" }
,{ "two" }
,{ "parameters:" }
,{ "the" }
,{ "array" }
,{ "length" }
,{ "and" }
,{ "the" }
,{ "reserved" }
,{ "length." }
,{ "When" }
,{ "the" }
,{ "array" }
,{ "is" }
,{ "being" }
,{ "created," }
,{ "the" }
,{ "reserved" }
,{ "length" }
,{ "determines" }
,{ "the" }
,{ "memory" }
,{ "space" }
,{ "to" }
,{ "be" }
,{ "allocated," }
,{ "and" }
,{ "the" }
,{ "length" }
,{ "is" }
,{ "the" }
,{ "number" }
,{ "of" }
,{ "elements" }
,{ "to" }
,{ "be" }
,{ "created." }
,{ "An" }
,{ "exception" }
,{ "is" }
,{ "thrown," }
,{ "if" }
,{ "len" , & fmt_text_b }
,{ "is" }
,{ "greater" }
,{ "than" }
,{ "maxlen" , & fmt_text_b }
,{ "." }
} , & fmt_text , & align_text } ;

Text b7 = { {
{ "Arrays" }
} , & fmt_h3 , & align_h3 } ;

Text b8 = { {
{ "Array" , & fmt_text_b }
,{ "is" }
,{ "a" }
,{ "container," }
,{ "where" }
,{ "multiple" }
,{ "items" }
,{ "comprise" }
,{ "a" }
,{ "continuous" }
,{ "range." }
,{ "The" }
,{ "simplest" }
,{ "such" }
,{ "\"container\"" }
,{ "is" }
,{ "the" }
,{ "embedded" }
,{ "type" }
,{ "\"array" }
,{ "of\"" }
,{ "T[Len]" , & fmt_text_b }
,{ "." }
,{ "Unfortunately," }
,{ "this" }
,{ "type" }
,{ "lacks" }
,{ "many" }
,{ "abilities," }
,{ "required" }
,{ "in" }
,{ "applications," }
,{ "so" }
,{ "we" }
,{ "need" }
,{ "a" }
,{ "variety" }
,{ "of" }
,{ "Array" , & fmt_text_b }
,{ "s." }
,{ "We" }
,{ "don't" }
,{ "use" }
,{ "STL" }
,{ "vector" , & fmt_text_b }
,{ "," }
,{ "because" }
,{ "it" }
,{ "also" }
,{ "has" }
,{ "many" }
,{ "deficiencies." }
,{ "CCore" , & fmt_text_b }
,{ "Array" , & fmt_text_b }
,{ "s" }
,{ "use" }
,{ "the" }
,{ "CCore" , & fmt_text_b }
,{ "heap" }
,{ "with" }
,{ "its" }
,{ "extra" }
,{ "functionality." }
,{ "They" }
,{ "also" }
,{ "customizable" }
,{ "using" }
,{ "an" }
,{ "Algorithm" , & fmt_text_b }
,{ "Package" , & fmt_text_b }
,{ "of" }
,{ "array" }
,{ "algorithms." }
} , & fmt_text , & align_text } ;

Text b9 = { {
{ "CCore" , & fmt_text_b }
,{ "Array" , & fmt_text_b }
,{ "s" }
,{ "implement" }
,{ "Range" , & fmt_text_b }
,{ "Access" , & fmt_text_b }
,{ "Interface" , & fmt_text_b }
,{ "." }
,{ "They" }
,{ "also" }
,{ "provide" }
,{ "the" }
,{ "index" }
,{ "access" }
,{ "to" }
,{ "elements" }
,{ "through" }
,{ "the" }
,{ "overloaded" }
,{ "operator" , & fmt_text_b }
,{ "[]" , & fmt_text_b }
,{ "and" }
,{ "the" }
,{ "checked" }
,{ "index" }
,{ "access" }
,{ "with" }
,{ "the" }
,{ "method" }
,{ "at()" , & fmt_text_b }
,{ "." }
} , & fmt_text , & align_text } ;

Text b10 = { {
{ "Constant" }
,{ "CCore" , & fmt_text_b }
,{ "Array" , & fmt_text_b }
,{ "s" }
,{ "give" }
,{ "constant" }
,{ "access" }
,{ "to" }
,{ "its" }
,{ "elements." }
} , & fmt_text , & align_text } ;

Text b11 = { {
{ "Allocation" }
,{ "errors" }
,{ "and" }
,{ "index" }
,{ "check" }
,{ "errors" }
,{ "throw" }
,{ "exceptions." }
,{ "Default" }
,{ "constructors" }
,{ "are" }
,{ "no-throw." }
} , & fmt_text , & align_text } ;

Text b12 = { {
{ "The" }
,{ "method" }
,{ "apply()" , & fmt_text_b }
,{ "applies" }
,{ "the" }
,{ "functor," }
,{ "given" }
,{ "by" }
,{ "a" }
,{ "Functor" , & fmt_text_b }
,{ "Init" , & fmt_text_b }
,{ "," }
,{ "to" }
,{ "array" }
,{ "elements." }
,{ "If" }
,{ "the" }
,{ "array" }
,{ "is" }
,{ "constant," }
,{ "then" }
,{ "element" }
,{ "references" }
,{ "are" }
,{ "constant" }
,{ "too." }
,{ "The" }
,{ "variant" }
,{ "apply_const()" , & fmt_text_b }
,{ "also" }
,{ "enforces" }
,{ "constantness." }
,{ "It" }
,{ "also" }
,{ "may" }
,{ "return" }
,{ "a" }
,{ "functor" }
,{ "result" }
,{ "." }
} , & fmt_text , & align_text } ;

Text b13 = { {
{ "The" }
,{ "method" }
,{ "applyReverse()" , & fmt_text_b }
,{ "applies" }
,{ "the" }
,{ "functor," }
,{ "given" }
,{ "by" }
,{ "a" }
,{ "Functor" , & fmt_text_b }
,{ "Init" , & fmt_text_b }
,{ "," }
,{ "to" }
,{ "array" }
,{ "elements" }
,{ "in" }
,{ "the" }
,{ "reverse" }
,{ "order." }
,{ "If" }
,{ "the" }
,{ "array" }
,{ "is" }
,{ "constant," }
,{ "then" }
,{ "element" }
,{ "references" }
,{ "are" }
,{ "constant" }
,{ "too." }
,{ "The" }
,{ "variant" }
,{ "applyReverse_const()" , & fmt_text_b }
,{ "also" }
,{ "enforces" }
,{ "constantness." }
} , & fmt_text , & align_text } ;

Text b14 = { {
{ "Array" , & fmt_text_b }
,{ "s" }
,{ "can" }
,{ "be" }
,{ "used" }
,{ "with" }
,{ "most" }
,{ "types," }
,{ "there" }
,{ "is" }
,{ "no" }
,{ "hard" }
,{ "restrictions" }
,{ "on" }
,{ "type" }
,{ "properties." }
,{ "The" }
,{ "only" }
,{ "strong" }
,{ "requirement" }
,{ "is:" }
,{ "the" }
,{ "type" }
,{ "destructor" }
,{ "must" }
,{ "be" }
,{ "no-throw." }
,{ "Some" }
,{ "operations," }
,{ "however," }
,{ "require" }
,{ "additional" }
,{ "type" }
,{ "properties." }
,{ "For" }
,{ "example," }
,{ "to" }
,{ "use" }
,{ "cloneTo()" , & fmt_text_b }
,{ "methods" }
,{ "the" }
,{ "type" }
,{ "must" }
,{ "be" }
,{ "copyable." }
} , & fmt_text , & align_text } ;

Text b15 = { {
{ "All" }
,{ "CCore" , & fmt_text_b }
,{ "Array" , & fmt_text_b }
,{ "s" }
,{ "available" }
,{ "through" }
,{ "the" }
,{ "header" }
,{ "CCore/inc/Array.h" , & fmt_text_b }
,{ "." }
} , & fmt_text , & align_text } ;

Text b16 = { {
{ "TempArray" }
} , & fmt_h4 , & align_h4 } ;

Text b17 = { {
{ "TempArray" , & fmt_text_b }
,{ "is" }
,{ "the" }
,{ "simplest" }
,{ "of" }
,{ "Array" , & fmt_text_b }
,{ "s." }
,{ "It" }
,{ "is" }
,{ "applicable" }
,{ "only" }
,{ "to" }
,{ "POD" }
,{ "types." }
,{ "This" }
,{ "container" }
,{ "combines" }
,{ "stack" }
,{ "storage" }
,{ "and" }
,{ "dynamic" }
,{ "storage" }
,{ "to" }
,{ "speed" }
,{ "up" }
,{ "the" }
,{ "array" }
,{ "construction/destruction" }
,{ "for" }
,{ "a" }
,{ "short" }
,{ "lengths." }
,{ "Use" }
,{ "this" }
,{ "Array" , & fmt_text_b }
,{ "if" }
,{ "you" }
,{ "need" }
,{ "a" }
,{ "temporary" }
,{ "buffer" }
,{ "with" }
,{ "expected" }
,{ "short" }
,{ "length" }
,{ "in" }
,{ "the" }
,{ "most" }
,{ "cases." }
} , & fmt_text , & align_text } ;

Text b18 = { {
{ "If" }
,{ "the" }
,{ "array" }
,{ "length" }
,{ "is" }
,{ "not" }
,{ "greater" }
,{ "than" }
,{ "StackLen" , & fmt_text_b }
,{ "," }
,{ "then" }
,{ "TempArray" , & fmt_text_b }
,{ "uses" }
,{ "the" }
,{ "internal" }
,{ "buffer." }
,{ "Otherwise," }
,{ "the" }
,{ "space" }
,{ "for" }
,{ "elements" }
,{ "is" }
,{ "dynamically" }
,{ "allocated." }
} , & fmt_text , & align_text } ;

Text b19 = { {
{ "provide()" , & fmt_text_b }
,{ "ensures" }
,{ "the" }
,{ "array" }
,{ "has" }
,{ "at" }
,{ "least" }
,{ "the" }
,{ "given" }
,{ "length," }
,{ "reallocating" }
,{ "it" }
,{ "if" }
,{ "required." }
,{ "The" }
,{ "previous" }
,{ "array" }
,{ "content" }
,{ "may" }
,{ "be" }
,{ "lost." }
,{ "The" }
,{ "new" }
,{ "content" }
,{ "is" }
,{ "not" }
,{ "initialized." }
} , & fmt_text , & align_text } ;

Text b20 = { {
{ "reset()" , & fmt_text_b }
,{ "recreates" }
,{ "the" }
,{ "array" }
,{ "with" }
,{ "the" }
,{ "given" }
,{ "length," }
,{ "reallocating" }
,{ "it" }
,{ "if" }
,{ "required." }
,{ "The" }
,{ "previous" }
,{ "array" }
,{ "content" }
,{ "may" }
,{ "be" }
,{ "lost." }
,{ "The" }
,{ "new" }
,{ "content" }
,{ "is" }
,{ "not" }
,{ "initialized." }
} , & fmt_text , & align_text } ;

Text b21 = { {
{ "extend()" , & fmt_text_b }
,{ "extends" }
,{ "the" }
,{ "array" }
,{ "up" }
,{ "to" }
,{ "the" }
,{ "given" }
,{ "length." }
,{ "If" }
,{ "len" , & fmt_text_b }
,{ "is" }
,{ "less" }
,{ "or" }
,{ "equal" }
,{ "than" }
,{ "the" }
,{ "current" }
,{ "array" }
,{ "length," }
,{ "the" }
,{ "method" }
,{ "does" }
,{ "nothing" }
,{ "and" }
,{ "returns" }
,{ "false" , & fmt_text_b }
,{ "." }
,{ "Otherwise" }
,{ "it" }
,{ "extends" }
,{ "the" }
,{ "array," }
,{ "preserving" }
,{ "the" }
,{ "current" }
,{ "content," }
,{ "and" }
,{ "returns" }
,{ "true" , & fmt_text_b }
,{ "." }
,{ "The" }
,{ "new" }
,{ "content" }
,{ "is" }
,{ "not" }
,{ "initialized." }
,{ "An" }
,{ "exception" }
,{ "is" }
,{ "thrown" }
,{ "if" }
,{ "there" }
,{ "is" }
,{ "no" }
,{ "memory." }
} , & fmt_text , & align_text } ;

Text b22 = { {
{ "erase()" , & fmt_text_b }
,{ "erases" }
,{ "the" }
,{ "array." }
} , & fmt_text , & align_text } ;

Text b23 = { {
{ "Other" }
,{ "methods" }
,{ "are" }
,{ "standard" }
,{ "array" }
,{ "methods." }
} , & fmt_text , & align_text } ;

Text b24 = { {
{ "SimpleArray" }
} , & fmt_h4 , & align_h4 } ;

Text b25 = { {
{ "SimpleArray" , & fmt_text_b }
,{ "is" }
,{ "another" }
,{ "\"simple" }
,{ "array\"." }
,{ "It" }
,{ "is" }
,{ "applicable" }
,{ "to" }
,{ "(almost)" }
,{ "any" }
,{ "types." }
} , & fmt_text , & align_text } ;

Text b26 = { {
{ "The" }
,{ "second" }
,{ "template" }
,{ "argument" }
,{ "of" }
,{ "SimpleArray" , & fmt_text_b }
,{ "is" }
,{ "an" }
,{ "Algorithm" , & fmt_text_b }
,{ "Package" , & fmt_text_b }
,{ "of" }
,{ "array" }
,{ "algorithms." }
,{ "SimpleArray" , & fmt_text_b }
,{ "uses" }
,{ "only" }
,{ "two" }
,{ "of" }
,{ "them:" }
,{ "Create_default()" , & fmt_text_b }
,{ "and" }
,{ "Destroy()" , & fmt_text_b }
,{ "." }
,{ "See" }
,{ "below" }
,{ "about" }
,{ "array" }
,{ "algorithms." }
} , & fmt_text , & align_text } ;

Text b27 = { {
{ "SimpleArray" , & fmt_text_b }
,{ "allocates" }
,{ "space" }
,{ "dynamically." }
} , & fmt_text , & align_text } ;

Text b28 = { {
{ "SimpleArray" , & fmt_text_b }
,{ "is" }
,{ "std" }
,{ "movable." }
,{ "The" }
,{ "original" }
,{ "object" }
,{ "is" }
,{ "nullified" }
,{ "during" }
,{ "the" }
,{ "move." }
} , & fmt_text , & align_text } ;

Text b29 = { {
{ "Unlike" }
,{ "TempArray" , & fmt_text_b }
,{ "," }
,{ "SimpleArray" , & fmt_text_b }
,{ "is" }
,{ "swappable" }
,{ "and" }
,{ "movable." }
} , & fmt_text , & align_text } ;

Text b30 = { {
{ "DynArray" }
} , & fmt_h4 , & align_h4 } ;

Text b31 = { {
{ "DynArray" , & fmt_text_b }
,{ "is" }
,{ "the" }
,{ "\"main\"" }
,{ "of" }
,{ "Array" , & fmt_text_b }
,{ "s." }
,{ "It" }
,{ "stores" }
,{ "elements" }
,{ "in" }
,{ "a" }
,{ "memory" }
,{ "space" }
,{ "with" }
,{ "some" }
,{ "reserved" }
,{ "memory" }
,{ "behind." }
,{ "It" }
,{ "can" }
,{ "extend" }
,{ "the" }
,{ "range" }
,{ "of" }
,{ "elements," }
,{ "if" }
,{ "there" }
,{ "is" }
,{ "an" }
,{ "extra" }
,{ "memory." }
,{ "If" }
,{ "not" }
,{ "and" }
,{ "the" }
,{ "type" }
,{ "T" , & fmt_text_b }
,{ "supports" }
,{ "moving" }
,{ "," }
,{ "then" }
,{ "the" }
,{ "array" }
,{ "extension" }
,{ "can" }
,{ "be" }
,{ "performed" }
,{ "with" }
,{ "either" }
,{ "the" }
,{ "memory" }
,{ "block" }
,{ "extension" }
,{ "(using" }
,{ "MemExtend()" , & fmt_text_b }
,{ ")" }
,{ "or" }
,{ "the" }
,{ "total" }
,{ "reallocation" }
,{ "with" }
,{ "the" }
,{ "content" }
,{ "moving." }
,{ "You" }
,{ "can" }
,{ "also" }
,{ "release" }
,{ "the" }
,{ "extra" }
,{ "memory." }
,{ "All" }
,{ "details" }
,{ "of" }
,{ "the" }
,{ "array" }
,{ "functionality" }
,{ "can" }
,{ "be" }
,{ "customized" }
,{ "using" }
,{ "the" }
,{ "second" }
,{ "template" }
,{ "argument," }
,{ "which" }
,{ "is" }
,{ "an" }
,{ "Algorithm" , & fmt_text_b }
,{ "Package" , & fmt_text_b }
,{ "of" }
,{ "array" }
,{ "algorithms." }
} , & fmt_text , & align_text } ;

Text b32 = { {
{ "Alone" }
,{ "with" }
,{ "standard" }
,{ "methods," }
,{ "DynArray" , & fmt_text_b }
,{ "has" }
,{ "a" }
,{ "bunch" }
,{ "of" }
,{ "methods" }
,{ "to" }
,{ "initialize" }
,{ "and" }
,{ "control" }
,{ "the" }
,{ "array" }
,{ "content." }
} , & fmt_text , & align_text } ;

Text b33 = { {
{ "Non-default" }
,{ "constructors" }
,{ "reserve" }
,{ "some" }
,{ "space" }
,{ "and" }
,{ "build" }
,{ "some" }
,{ "elements." }
,{ "The" }
,{ "DoRaw" , & fmt_text_b }
,{ "," }
,{ "...," }
,{ "DoCreate" , & fmt_text_b }
,{ "arguments" }
,{ "carry" }
,{ "the" }
,{ "length" }
,{ "and" }
,{ "the" }
,{ "reserved" }
,{ "length" }
,{ "of" }
,{ "the" }
,{ "array" }
,{ "to" }
,{ "be" }
,{ "used." }
} , & fmt_text , & align_text } ;

Text b34 = { {
{ "Non-default" }
,{ "constructors" }
,{ "work" }
,{ "the" }
,{ "same" }
,{ "way" }
,{ "as" }
,{ "the" }
,{ "correspondent" }
,{ "extend...()" , & fmt_text_b }
,{ "methods." }
} , & fmt_text , & align_text } ;

Text b35 = { {
{ "DynArray(std::initializer_list<S>" , & fmt_text_b }
,{ "il)" , & fmt_text_b }
,{ "uses" }
,{ "the" }
,{ "initialization" }
,{ "list" }
,{ "to" }
,{ "\"cast\"" }
,{ "elements" }
,{ "from" }
,{ "the" }
,{ "given." }
} , & fmt_text , & align_text } ;

Text b36 = { {
{ "DynArray(ulen" , & fmt_text_b }
,{ "len)" , & fmt_text_b }
,{ "creates" }
,{ "the" }
,{ "array" }
,{ "of" }
,{ "the" }
,{ "len" , & fmt_text_b }
,{ "elements" }
,{ "using" }
,{ "the" }
,{ "default" }
,{ "constructor." }
} , & fmt_text , & align_text } ;

Text b37 = { {
{ "DynArray(ulen" , & fmt_text_b }
,{ "len,ulen" , & fmt_text_b }
,{ "maxlen)" , & fmt_text_b }
,{ "also" }
,{ "performs" }
,{ "the" }
,{ "default" }
,{ "initialization" }
,{ "of" }
,{ "the" }
,{ "len" , & fmt_text_b }
,{ "elements," }
,{ "but" }
,{ "reserves" }
,{ "a" }
,{ "space" }
,{ "for" }
,{ "the" }
,{ "maxlen" , & fmt_text_b }
,{ "elements." }
,{ "An" }
,{ "exception" }
,{ "is" }
,{ "thrown," }
,{ "if" }
,{ "len" , & fmt_text_b }
,{ "is" }
,{ "greater" }
,{ "than" }
,{ "maxlen" , & fmt_text_b }
,{ "." }
} , & fmt_text , & align_text } ;

Text b38 = { {
{ "DynArray(DoReserveType,ulen" , & fmt_text_b }
,{ "maxlen)" , & fmt_text_b }
,{ "just" }
,{ "reserves" }
,{ "a" }
,{ "space." }
} , & fmt_text , & align_text } ;

Text b39 = { {
{ "DynArray(DoRaw" , & fmt_text_b }
,{ "dotype)" , & fmt_text_b }
,{ "performs" }
,{ "the" }
,{ "\"raw\"" }
,{ "initialization." }
,{ "If" }
,{ "the" }
,{ "T" , & fmt_text_b }
,{ "is" }
,{ "a" }
,{ "POD" }
,{ "type," }
,{ "elements" }
,{ "are" }
,{ "not" }
,{ "initialized." }
,{ "If" }
,{ "not," }
,{ "the" }
,{ "default" }
,{ "initialization" }
,{ "is" }
,{ "performed." }
} , & fmt_text , & align_text } ;

Text b40 = { {
{ "DynArray(DoFill" , & fmt_text_b }
,{ "dotype,SS" , & fmt_text_b }
,{ "&&" , & fmt_text_b }
,{ "..." , & fmt_text_b }
,{ "ss)" , & fmt_text_b }
,{ "creates" }
,{ "new" }
,{ "elements" }
,{ "using" }
,{ "some" }
,{ "constructor," }
,{ "the" }
,{ "specified" }
,{ "arguments" }
,{ "are" }
,{ "forwarded" }
,{ "to" }
,{ "this" }
,{ "constructor." }
} , & fmt_text , & align_text } ;

Text b41 = { {
{ "DynArray(DoCopy" , & fmt_text_b }
,{ "dotype,const" , & fmt_text_b }
,{ "T" , & fmt_text_b }
,{ "src[])" , & fmt_text_b }
,{ "creates" }
,{ "new" }
,{ "elements" }
,{ "using" }
,{ "the" }
,{ "copy" }
,{ "constructor," }
,{ "src" , & fmt_text_b }
,{ "is" }
,{ "a" }
,{ "range" }
,{ "of" }
,{ "length" }
,{ "dotype.getLen()" , & fmt_text_b }
,{ "," }
,{ "its" }
,{ "members" }
,{ "are" }
,{ "copied" }
,{ "memberwise." }
} , & fmt_text , & align_text } ;

Text b42 = { {
{ "DynArray(DoCast" , & fmt_text_b }
,{ "dotype,const" , & fmt_text_b }
,{ "S" , & fmt_text_b }
,{ "src[])" , & fmt_text_b }
,{ "creates" }
,{ "new" }
,{ "elements" }
,{ "using" }
,{ "the" }
,{ "\"cast\"" }
,{ "constructor," }
,{ "src" , & fmt_text_b }
,{ "is" }
,{ "a" }
,{ "range" }
,{ "of" }
,{ "length" }
,{ "dotype.getLen()" , & fmt_text_b }
,{ "," }
,{ "its" }
,{ "members" }
,{ "are" }
,{ "casted" }
,{ "memberwise." }
} , & fmt_text , & align_text } ;

Text b43 = { {
{ "DynArray(DoSwap" , & fmt_text_b }
,{ "dotype,T" , & fmt_text_b }
,{ "objs[])" , & fmt_text_b }
,{ "creates" }
,{ "new" }
,{ "elements" }
,{ "using" }
,{ "the" }
,{ "\"swap" }
,{ "move\"" }
,{ "approach." }
,{ "I.e." }
,{ "new" }
,{ "elements" }
,{ "are" }
,{ "created" }
,{ "using" }
,{ "the" }
,{ "default" }
,{ "constructor" }
,{ "and" }
,{ "swapped" }
,{ "with" }
,{ "members" }
,{ "of" }
,{ "the" }
,{ "range" }
,{ "objs" , & fmt_text_b }
,{ "." }
} , & fmt_text , & align_text } ;

Text b44 = { {
{ "DynArray(DoCreate" , & fmt_text_b }
,{ "dotype,CreatorType<T>" , & fmt_text_b }
,{ "creator)" , & fmt_text_b }
,{ "uses" }
,{ "the" }
,{ "given" }
,{ "Creator" , & fmt_text_b }
,{ "object" }
,{ "to" }
,{ "create" }
,{ "new" }
,{ "elements." }
} , & fmt_text , & align_text } ;

Text b45 = { {
{ "DynArray(DoBuildType,BuilderType<T>" , & fmt_text_b }
,{ "builder)" , & fmt_text_b }
,{ "uses" }
,{ "the" }
,{ "given" }
,{ "Builder" , & fmt_text_b }
,{ "object" }
,{ "to" }
,{ "create" }
,{ "new" }
,{ "elements." }
} , & fmt_text , & align_text } ;

Text b46 = { {
{ "DynArray" , & fmt_text_b }
,{ "is" }
,{ "std" }
,{ "movable." }
,{ "The" }
,{ "original" }
,{ "object" }
,{ "is" }
,{ "nullified" }
,{ "during" }
,{ "the" }
,{ "move." }
} , & fmt_text , & align_text } ;

Text b47 = { {
{ "Range" }
,{ "access" }
,{ "and" }
,{ "index" }
,{ "access" }
,{ "methods" }
,{ "are" }
,{ "standard." }
,{ "Two" }
,{ "additional" }
,{ "methods" }
,{ "report" }
,{ "memory" }
,{ "allocation." }
} , & fmt_text , & align_text } ;

Text b48 = { {
{ "getMaxLen()" , & fmt_text_b }
,{ "returns" }
,{ "the" }
,{ "reserved" }
,{ "array" }
,{ "length" }
,{ "(in" }
,{ "objects)." }
} , & fmt_text , & align_text } ;

Text b49 = { {
{ "getExtraLen()" , & fmt_text_b }
,{ "is" }
,{ "the" }
,{ "extra" }
,{ "space" }
,{ "available" }
,{ "(in" }
,{ "objects)." }
} , & fmt_text , & align_text } ;

Text b50 = { {
{ "isEmpty()" , & fmt_text_b }
,{ "returns" }
,{ "true" , & fmt_text_b }
,{ "iff" }
,{ "the" }
,{ "array" }
,{ "is" }
,{ "empty." }
} , & fmt_text , & align_text } ;

Text b51 = { {
{ "notEmpty()" , & fmt_text_b }
,{ "returns" }
,{ "true" , & fmt_text_b }
,{ "iff" }
,{ "the" }
,{ "array" }
,{ "is" }
,{ "not" }
,{ "empty." }
} , & fmt_text , & align_text } ;

Text b52 = { {
{ "cloneTo()" , & fmt_text_b }
,{ "clones" }
,{ "the" }
,{ "array." }
,{ "The" }
,{ "reserved" }
,{ "length" }
,{ "is" }
,{ "also" }
,{ "preserved." }
,{ "The" }
,{ "type" }
,{ "T" , & fmt_text_b }
,{ "must" }
,{ "be" }
,{ "copyable." }
} , & fmt_text , & align_text } ;

Text b53 = { {
{ "reserve()" , & fmt_text_b }
,{ "reserves" }
,{ "the" }
,{ "space" }
,{ "for" }
,{ "extra_len" , & fmt_text_b }
,{ "objects." }
} , & fmt_text , & align_text } ;

Text b54 = { {
{ "erase()" , & fmt_text_b }
,{ "erases" }
,{ "the" }
,{ "array," }
,{ "it" }
,{ "gets" }
,{ "to" }
,{ "the" }
,{ "null" }
,{ "state," }
,{ "with" }
,{ "no" }
,{ "objects" }
,{ "and" }
,{ "no" }
,{ "memory" }
,{ "allocated." }
} , & fmt_text , & align_text } ;

Text b55 = { {
{ "shrink()" , & fmt_text_b }
,{ "destroys" }
,{ "the" }
,{ "last" }
,{ "up" }
,{ "to" }
,{ "delta_len" , & fmt_text_b }
,{ "elements" }
,{ "of" }
,{ "the" }
,{ "array." }
,{ "It" }
,{ "returns" }
,{ "the" }
,{ "number" }
,{ "of" }
,{ "elements" }
,{ "destroyed." }
} , & fmt_text , & align_text } ;

Text b56 = { {
{ "shrink_one()" , & fmt_text_b }
,{ "destroys" }
,{ "the" }
,{ "last" }
,{ "element" }
,{ "(if" }
,{ "any)." }
,{ "It" }
,{ "returns" }
,{ "true" , & fmt_text_b }
,{ "," }
,{ "if" }
,{ "the" }
,{ "element" }
,{ "is" }
,{ "destroyed," }
,{ "and" }
,{ "false" , & fmt_text_b }
,{ "if" }
,{ "the" }
,{ "array" }
,{ "is" }
,{ "empty." }
} , & fmt_text , & align_text } ;

Text b57 = { {
{ "shrink_all()" , & fmt_text_b }
,{ "destroys" }
,{ "all" }
,{ "array" }
,{ "elements." }
,{ "It" }
,{ "returns" }
,{ "the" }
,{ "number" }
,{ "of" }
,{ "elements" }
,{ "destroyed." }
} , & fmt_text , & align_text } ;

Text b58 = { {
{ "These" }
,{ "three" }
,{ "methods" }
,{ "doesn't" }
,{ "change" }
,{ "the" }
,{ "reserved" }
,{ "array" }
,{ "length." }
} , & fmt_text , & align_text } ;

Text b59 = { {
{ "shrink_extra()" , & fmt_text_b }
,{ "shrinks" }
,{ "the" }
,{ "memory" }
,{ "block," }
,{ "returning" }
,{ "the" }
,{ "extra" }
,{ "memory" }
,{ "to" }
,{ "the" }
,{ "heap." }
,{ "After" }
,{ "this" }
,{ "method" }
,{ "the" }
,{ "reserved" }
,{ "array" }
,{ "length" }
,{ "becomes" }
,{ "equal" }
,{ "to" }
,{ "the" }
,{ "array" }
,{ "length." }
} , & fmt_text , & align_text } ;

Text b60 = { {
{ "shrink_reserve(ulen" , & fmt_text_b }
,{ "maxlen)" , & fmt_text_b }
,{ "may" }
,{ "shrink" }
,{ "the" }
,{ "memory" }
,{ "block" }
,{ "to" }
,{ "store" }
,{ "the" }
,{ "given" }
,{ "number" }
,{ "of" }
,{ "elements." }
,{ "It" }
,{ "gives" }
,{ "a" }
,{ "more" }
,{ "precise" }
,{ "control" }
,{ "over" }
,{ "the" }
,{ "reserved" }
,{ "memory." }
,{ "It" }
,{ "works" }
,{ "only" }
,{ "if" }
,{ "the" }
,{ "following" }
,{ "natural" }
,{ "condition" }
,{ "satisfied:" }
,{ "maxlen<getMaxLen()" , & fmt_text_b }
,{ "and" }
,{ "maxlen>=getLen()" , & fmt_text_b }
,{ "." }
} , & fmt_text , & align_text } ;

Text b61 = { {
{ "shrink_reserve()" , & fmt_text_b }
,{ "works" }
,{ "as" }
,{ "shrink_reserve(ulen" , & fmt_text_b }
,{ "maxlen)" , & fmt_text_b }
,{ "with" }
,{ "maxlen" , & fmt_text_b }
,{ "equals" }
,{ "\"double" }
,{ "size\"" }
,{ "of" }
,{ "the" }
,{ "actual" }
,{ "array" }
,{ "length." }
} , & fmt_text , & align_text } ;

Text b62 = { {
{ "extend...()" , & fmt_text_b }
,{ "is" }
,{ "a" }
,{ "family" }
,{ "of" }
,{ "methods," }
,{ "which" }
,{ "extends" }
,{ "the" }
,{ "array" }
,{ "with" }
,{ "number" }
,{ "elements." }
,{ "They" }
,{ "differ" }
,{ "in" }
,{ "element" }
,{ "construction" }
,{ "ways." }
,{ "All" }
,{ "of" }
,{ "them," }
,{ "except" }
,{ "the" }
,{ "last," }
,{ "has" }
,{ "the" }
,{ "first" }
,{ "argument" }
,{ "delta_len" , & fmt_text_b }
,{ "," }
,{ "which" }
,{ "is" }
,{ "the" }
,{ "number" }
,{ "of" }
,{ "new" }
,{ "elements." }
,{ "The" }
,{ "return" }
,{ "value" }
,{ "is" }
,{ "the" }
,{ "range" }
,{ "of" }
,{ "these" }
,{ "new" }
,{ "elements." }
,{ "extend...()" , & fmt_text_b }
,{ "are" }
,{ "transactional," }
,{ "i.e." }
,{ "if" }
,{ "the" }
,{ "method" }
,{ "has" }
,{ "failed," }
,{ "then" }
,{ "the" }
,{ "array" }
,{ "remains" }
,{ "in" }
,{ "the" }
,{ "original" }
,{ "state," }
,{ "an" }
,{ "exception" }
,{ "is" }
,{ "thrown." }
} , & fmt_text , & align_text } ;

Text b63 = { {
{ "extend_raw()" , & fmt_text_b }
,{ "for" }
,{ "POD" }
,{ "types" }
,{ "leaves" }
,{ "new" }
,{ "elements" }
,{ "uninitialized." }
,{ "For" }
,{ "other" }
,{ "types" }
,{ "it" }
,{ "works" }
,{ "like" }
,{ "extend_default()" , & fmt_text_b }
,{ "." }
} , & fmt_text , & align_text } ;

Text b64 = { {
{ "extend_default()" , & fmt_text_b }
,{ "creates" }
,{ "new" }
,{ "elements" }
,{ "using" }
,{ "the" }
,{ "default" }
,{ "constructor." }
} , & fmt_text , & align_text } ;

Text b65 = { {
{ "extend_fill()" , & fmt_text_b }
,{ "creates" }
,{ "new" }
,{ "elements" }
,{ "using" }
,{ "some" }
,{ "constructor," }
,{ "the" }
,{ "specified" }
,{ "arguments" }
,{ "are" }
,{ "forwarded" }
,{ "to" }
,{ "this" }
,{ "constructor." }
} , & fmt_text , & align_text } ;

Text b66 = { {
{ "extend_copy()" , & fmt_text_b }
,{ "creates" }
,{ "new" }
,{ "elements" }
,{ "using" }
,{ "the" }
,{ "copy" }
,{ "constructor," }
,{ "src" , & fmt_text_b }
,{ "is" }
,{ "a" }
,{ "range" }
,{ "of" }
,{ "length" }
,{ "delta_len" , & fmt_text_b }
,{ "," }
,{ "its" }
,{ "members" }
,{ "are" }
,{ "copied" }
,{ "memberwise." }
} , & fmt_text , & align_text } ;

Text b67 = { {
{ "extend_cast()" , & fmt_text_b }
,{ "creates" }
,{ "new" }
,{ "elements" }
,{ "using" }
,{ "the" }
,{ "\"cast\"" }
,{ "constructor," }
,{ "src" , & fmt_text_b }
,{ "is" }
,{ "a" }
,{ "range" }
,{ "of" }
,{ "length" }
,{ "delta_len" , & fmt_text_b }
,{ "," }
,{ "its" }
,{ "members" }
,{ "are" }
,{ "casted" }
,{ "memberwise." }
} , & fmt_text , & align_text } ;

Text b68 = { {
{ "extend_swap()" , & fmt_text_b }
,{ "creates" }
,{ "new" }
,{ "elements" }
,{ "using" }
,{ "the" }
,{ "\"swap" }
,{ "move\"" }
,{ "approach." }
,{ "I.e." }
,{ "new" }
,{ "elements" }
,{ "are" }
,{ "created" }
,{ "using" }
,{ "the" }
,{ "default" }
,{ "constructor" }
,{ "and" }
,{ "swapped" }
,{ "with" }
,{ "members" }
,{ "of" }
,{ "the" }
,{ "range" }
,{ "objs" , & fmt_text_b }
,{ "." }
} , & fmt_text , & align_text } ;

Text b69 = { {
{ "Two" }
,{ "final" }
,{ "extend()" , & fmt_text_b }
,{ "are" }
,{ "generic." }
,{ "The" }
,{ "first" }
,{ "of" }
,{ "them" }
,{ "uses" }
,{ "the" }
,{ "given" }
,{ "Creator" , & fmt_text_b }
,{ "object" }
,{ "to" }
,{ "create" }
,{ "new" }
,{ "elements," }
,{ "and" }
,{ "the" }
,{ "second" }
,{ "uses" }
,{ "the" }
,{ "Builder" , & fmt_text_b }
,{ "." }
,{ "See" }
,{ "below" }
,{ "explanations" }
,{ "about" }
,{ "Creator" , & fmt_text_b }
,{ "s" }
,{ "and" }
,{ "Builder" , & fmt_text_b }
,{ "s." }
} , & fmt_text , & align_text } ;

Text b70 = { {
{ "append...()" , & fmt_text_b }
,{ "is" }
,{ "a" }
,{ "family" }
,{ "of" }
,{ "methods" }
,{ "to" }
,{ "append" }
,{ "one" }
,{ "element" }
,{ "to" }
,{ "the" }
,{ "array." }
,{ "They" }
,{ "are" }
,{ "similar" }
,{ "to" }
,{ "the" }
,{ "correspondent" }
,{ "extend...()" , & fmt_text_b }
,{ "methods" }
,{ "and" }
,{ "do" }
,{ "exactly" }
,{ "the" }
,{ "same" }
,{ "with" }
,{ "delta_len" , & fmt_text_b }
,{ "equals" }
,{ "1." }
,{ "The" }
,{ "return" }
,{ "value" }
,{ "is" }
,{ "a" }
,{ "pointer" }
,{ "to" }
,{ "the" }
,{ "created" }
,{ "element." }
} , & fmt_text , & align_text } ;

Text b71 = { {
{ "apply...()" , & fmt_text_b }
,{ "methods" }
,{ "are" }
,{ "standard." }
} , & fmt_text , & align_text } ;

Text b72 = { {
{ "DynArray" , & fmt_text_b }
,{ "is" }
,{ "swappable" }
,{ "and" }
,{ "movable." }
} , & fmt_text , & align_text } ;

Text b73 = { {
{ "RefArray" }
,{ "and" }
,{ "AtomicRefArray" }
} , & fmt_h4 , & align_h4 } ;

Text b74 = { {
{ "RefArray" , & fmt_text_b }
,{ "and" }
,{ "AtomicRefArray" , & fmt_text_b }
,{ "are" }
,{ "copyable" }
,{ "arrays" }
,{ "with" }
,{ "efficient" }
,{ "copy" }
,{ "constructors." }
,{ "It's" }
,{ "assumed," }
,{ "the" }
,{ "type" }
,{ "T" , & fmt_text_b }
,{ "is" }
,{ "copyable." }
,{ "Multiple" }
,{ "copies" }
,{ "of" }
,{ "arrays" }
,{ "may" }
,{ "share" }
,{ "the" }
,{ "same" }
,{ "state." }
,{ "The" }
,{ "state" }
,{ "has" }
,{ "a" }
,{ "reference" }
,{ "counter," }
,{ "which" }
,{ "is" }
,{ "used" }
,{ "to" }
,{ "end" }
,{ "its" }
,{ "life-time." }
,{ "The" }
,{ "only" }
,{ "difference" }
,{ "between" }
,{ "RefArray" , & fmt_text_b }
,{ "and" }
,{ "AtomicRefArray" , & fmt_text_b }
,{ "is" }
,{ "the" }
,{ "former" }
,{ "uses" }
,{ "the" }
,{ "atomic" }
,{ "reference" }
,{ "counting" }
,{ "to" }
,{ "be" }
,{ "viable" }
,{ "in" }
,{ "a" }
,{ "multi-threaded" }
,{ "environment." }
} , & fmt_text , & align_text } ;

Text b75 = { {
{ "RefArray" , & fmt_text_b }
,{ "has" }
,{ "a" }
,{ "simulated" }
,{ "value" }
,{ "semantic." }
,{ "It" }
,{ "means," }
,{ "that" }
,{ "you" }
,{ "may" }
,{ "consider" }
,{ "different" }
,{ "copies" }
,{ "of" }
,{ "an" }
,{ "array" }
,{ "as" }
,{ "independent" }
,{ "variables," }
,{ "despite" }
,{ "they" }
,{ "may" }
,{ "share" }
,{ "the" }
,{ "state." }
,{ "That" }
,{ "is" }
,{ "because" }
,{ "RefArray" , & fmt_text_b }
,{ "provides" }
,{ "only" }
,{ "a" }
,{ "constant" }
,{ "access" }
,{ "to" }
,{ "elements." }
,{ "So" }
,{ "far" }
,{ "you" }
,{ "don't" }
,{ "violate" }
,{ "this" }
,{ "constantness" }
,{ "(using" }
,{ "the" }
,{ "const-cast," }
,{ "for" }
,{ "example)," }
,{ "you" }
,{ "may" }
,{ "safely" }
,{ "assume" }
,{ "that" }
,{ "each" }
,{ "copy" }
,{ "is" }
,{ "different." }
,{ "To" }
,{ "modify" }
,{ "the" }
,{ "array" }
,{ "you" }
,{ "have" }
,{ "to" }
,{ "call" }
,{ "the" }
,{ "method" }
,{ "modify()" , & fmt_text_b }
,{ "(or" }
,{ "modifyReverse()" , & fmt_text_b }
,{ ")." }
,{ "This" }
,{ "method" }
,{ "\"unshares\"" }
,{ "the" }
,{ "array," }
,{ "if" }
,{ "necessary," }
,{ "and" }
,{ "gives" }
,{ "a" }
,{ "non-constant" }
,{ "access" }
,{ "to" }
,{ "elements." }
,{ "modifyReverse()" , & fmt_text_b }
,{ "is" }
,{ "doing" }
,{ "the" }
,{ "same" }
,{ "thing" }
,{ "as" }
,{ "modify()" , & fmt_text_b }
,{ "," }
,{ "but" }
,{ "gives" }
,{ "a" }
,{ "\"reversed\"" }
,{ "range" }
,{ "of" }
,{ "elements." }
} , & fmt_text , & align_text } ;

Text b76 = { {
{ "The" }
,{ "RefArray" , & fmt_text_b }
,{ "methods" }
,{ "are" }
,{ "mostly" }
,{ "the" }
,{ "same" }
,{ "as" }
,{ "DynArray" , & fmt_text_b }
,{ "methods." }
,{ "The" }
,{ "differences" }
,{ "are:" }
,{ "index" }
,{ "and" }
,{ "range" }
,{ "access" }
,{ "methods" }
,{ "gives" }
,{ "only" }
,{ "the" }
,{ "constant" }
,{ "access," }
,{ "and" }
,{ "new" }
,{ "class-specific" }
,{ "methods" }
,{ "modify()" , & fmt_text_b }
,{ "and" }
,{ "modifyReverse()" , & fmt_text_b }
,{ "exist." }
} , & fmt_text , & align_text } ;

Text b77 = { {
{ "apply_modify()" , & fmt_text_b }
,{ "applies" }
,{ "the" }
,{ "functor," }
,{ "given" }
,{ "by" }
,{ "a" }
,{ "Functor" , & fmt_text_b }
,{ "Init" , & fmt_text_b }
,{ "," }
,{ "to" }
,{ "array" }
,{ "elements." }
,{ "The" }
,{ "array" }
,{ "is" }
,{ "unshared" }
,{ "first." }
} , & fmt_text , & align_text } ;

Text b78 = { {
{ "applyReverse_modify()" , & fmt_text_b }
,{ "applies" }
,{ "the" }
,{ "functor," }
,{ "given" }
,{ "by" }
,{ "a" }
,{ "Functor" , & fmt_text_b }
,{ "Init" , & fmt_text_b }
,{ "," }
,{ "to" }
,{ "array" }
,{ "elements" }
,{ "in" }
,{ "the" }
,{ "reverse" }
,{ "order." }
,{ "The" }
,{ "array" }
,{ "is" }
,{ "unshared" }
,{ "first." }
} , & fmt_text , & align_text } ;

Text b79 = { {
{ "apply()" , & fmt_text_b }
,{ "applies" }
,{ "the" }
,{ "functor," }
,{ "given" }
,{ "by" }
,{ "a" }
,{ "Functor" , & fmt_text_b }
,{ "Init" , & fmt_text_b }
,{ "," }
,{ "to" }
,{ "array" }
,{ "elements." }
,{ "This" }
,{ "is" }
,{ "a" }
,{ "constant" }
,{ "method." }
} , & fmt_text , & align_text } ;

Text b80 = { {
{ "applyReverse()" , & fmt_text_b }
,{ "applies" }
,{ "the" }
,{ "functor," }
,{ "given" }
,{ "by" }
,{ "a" }
,{ "Functor" , & fmt_text_b }
,{ "Init" , & fmt_text_b }
,{ "," }
,{ "to" }
,{ "array" }
,{ "elements" }
,{ "in" }
,{ "the" }
,{ "reverse" }
,{ "order." }
,{ "This" }
,{ "is" }
,{ "a" }
,{ "constant" }
,{ "method." }
} , & fmt_text , & align_text } ;

Text b81 = { {
{ "AtomicRefArray" , & fmt_text_b }
,{ "methods" }
,{ "shrink_extra()" , & fmt_text_b }
,{ "and" }
,{ "shrink_reserve()" , & fmt_text_b }
,{ "are" }
,{ "not" }
,{ "working," }
,{ "if" }
,{ "the" }
,{ "array" }
,{ "is" }
,{ "shared." }
} , & fmt_text , & align_text } ;

Text b82 = { {
{ "AtomicRefArray" , & fmt_text_b }
,{ "has" }
,{ "an" }
,{ "extra" }
,{ "special" }
,{ "constructor" }
} , & fmt_text , & align_text } ;

Text b83 = { {
{ "This" }
,{ "constructor" }
,{ "can" }
,{ "be" }
,{ "used" }
,{ "to" }
,{ "create" }
,{ "a" }
,{ "static" }
,{ "AtomicRefArray" , & fmt_text_b }
,{ "with" }
,{ "unlimited" }
,{ "life-time." }
,{ "The" }
,{ "type" }
,{ "T" , & fmt_text_b }
,{ "must" }
,{ "have" }
,{ "a" }
,{ "trivial" }
,{ "destructor," }
,{ "however." }
,{ "You" }
,{ "must" }
,{ "supply" }
,{ "a" }
,{ "statically" }
,{ "allocated" }
,{ "memory," }
,{ "aligned" }
,{ "and" }
,{ "proper" }
,{ "size." }
,{ "You" }
,{ "also" }
,{ "must" }
,{ "supply" }
,{ "a" }
,{ "maximum" }
,{ "number" }
,{ "of" }
,{ "elements" }
,{ "(>0)" }
,{ "and" }
,{ "an" }
,{ "intializer" }
,{ "list." }
,{ "To" }
,{ "calculate" }
,{ "the" }
,{ "required" }
,{ "memory" }
,{ "size" }
,{ "use" }
,{ "the" }
,{ "meta" }
,{ "constant" }
,{ "StaticMemLen" , & fmt_text_b }
,{ "." }
,{ "The" }
,{ "object" }
,{ "state," }
,{ "created" }
,{ "with" }
,{ "this" }
,{ "constructor," }
,{ "lives" }
,{ "forever" }
,{ "and" }
,{ "contains" }
,{ "the" }
,{ "initial" }
,{ "object" }
,{ "array," }
,{ "initialized" }
,{ "from" }
,{ "the" }
,{ "given" }
,{ "intializer" }
,{ "list." }
} , & fmt_text , & align_text } ;

Text b84 = { {
{ "Collector" }
} , & fmt_h4 , & align_h4 } ;

Text b85 = { {
{ "Collector" , & fmt_text_b }
,{ "is" }
,{ "not" }
,{ "an" }
,{ "array!" }
,{ "The" }
,{ "purpose" }
,{ "of" }
,{ "this" }
,{ "container" }
,{ "is" }
,{ "to" }
,{ "be" }
,{ "an" }
,{ "efficient" }
,{ "collector" }
,{ "of" }
,{ "elements." }
,{ "This" }
,{ "container" }
,{ "stores" }
,{ "a" }
,{ "sequence" }
,{ "of" }
,{ "elements" }
,{ "in" }
,{ "a" }
,{ "list" }
,{ "of" }
,{ "arrays." }
,{ "So" }
,{ "appending" }
,{ "and" }
,{ "extending" }
,{ "operations" }
,{ "are" }
,{ "the" }
,{ "most" }
,{ "efficient." }
,{ "At" }
,{ "desired" }
,{ "moment" }
,{ "you" }
,{ "can" }
,{ "copy" }
,{ "or" }
,{ "move" }
,{ "this" }
,{ "sequence" }
,{ "into" }
,{ "true" }
,{ "array." }
,{ "Or" }
,{ "you" }
,{ "can" }
,{ "\"flat\"" }
,{ "the" }
,{ "Collector" , & fmt_text_b }
,{ "itself." }
} , & fmt_text , & align_text } ;

Text b86 = { {
{ "The" }
,{ "argument" }
,{ "of" }
,{ "the" }
,{ "Collector" , & fmt_text_b }
,{ "constructor" }
,{ "is" }
,{ "the" }
,{ "number" }
,{ "of" }
,{ "elements" }
,{ "in" }
,{ "the" }
,{ "single" }
,{ "element" }
,{ "block." }
,{ "The" }
,{ "default" }
,{ "value" }
,{ "is" }
,{ "1024." }
} , & fmt_text , & align_text } ;

Text b87 = { {
{ "Collector" , & fmt_text_b }
,{ "is" }
,{ "std" }
,{ "movable." }
,{ "The" }
,{ "original" }
,{ "object" }
,{ "is" }
,{ "nullified" }
,{ "during" }
,{ "the" }
,{ "move." }
} , & fmt_text , & align_text } ;

Text b88 = { {
{ "Collector" , & fmt_text_b }
,{ "does" }
,{ "not" }
,{ "provide" }
,{ "a" }
,{ "direct" }
,{ "access" }
,{ "to" }
,{ "its" }
,{ "content." }
} , & fmt_text , & align_text } ;

Text b89 = { {
{ "isEmpty()" , & fmt_text_b }
,{ "returns" }
,{ "true" , & fmt_text_b }
,{ "iff" }
,{ "the" }
,{ "array" }
,{ "is" }
,{ "empty." }
} , & fmt_text , & align_text } ;

Text b90 = { {
{ "notEmpty()" , & fmt_text_b }
,{ "returns" }
,{ "true" , & fmt_text_b }
,{ "iff" }
,{ "the" }
,{ "array" }
,{ "is" }
,{ "not" }
,{ "empty." }
} , & fmt_text , & align_text } ;

Text b91 = { {
{ "getLen()" , & fmt_text_b }
,{ "is" }
,{ "the" }
,{ "number" }
,{ "of" }
,{ "the" }
,{ "collected" }
,{ "elements." }
} , & fmt_text , & align_text } ;

Text b92 = { {
{ "erase()" , & fmt_text_b }
,{ "cleanup" }
,{ "the" }
,{ "container" }
,{ "and" }
,{ "put" }
,{ "it" }
,{ "into" }
,{ "the" }
,{ "null" }
,{ "state." }
} , & fmt_text , & align_text } ;

Text b93 = { {
{ "extractTo()" , & fmt_text_b }
,{ "moves" }
,{ "the" }
,{ "content" }
,{ "to" }
,{ "another" }
,{ "(array)" }
,{ "container." }
,{ "The" }
,{ "target" }
,{ "container" }
,{ "must" }
,{ "have" }
,{ "the" }
,{ "Build" , & fmt_text_b }
,{ "constructor." }
,{ "Collector" , & fmt_text_b }
,{ "becomes" }
,{ "empty" }
,{ "after" }
,{ "this" }
,{ "operation." }
} , & fmt_text , & align_text } ;

Text b94 = { {
{ "copyTo()" , & fmt_text_b }
,{ "copies" }
,{ "the" }
,{ "content" }
,{ "to" }
,{ "another" }
,{ "(array)" }
,{ "container." }
,{ "The" }
,{ "target" }
,{ "container" }
,{ "must" }
,{ "have" }
,{ "the" }
,{ "Build" , & fmt_text_b }
,{ "constructor." }
} , & fmt_text , & align_text } ;

Text b95 = { {
{ "flat()" , & fmt_text_b }
,{ "rebuilds" }
,{ "the" }
,{ "internal" }
,{ "data" }
,{ "storage," }
,{ "making" }
,{ "it" }
,{ "continuous." }
,{ "It" }
,{ "returns" }
,{ "the" }
,{ "range" }
,{ "of" }
,{ "elements." }
,{ "This" }
,{ "range" }
,{ "remains" }
,{ "valid" }
,{ "after" }
,{ "extend" }
,{ "or" }
,{ "append" }
,{ "operations" }
,{ "(but" }
,{ "may" }
,{ "become" }
,{ "invalid" }
,{ "after" }
,{ "any" }
,{ "other" }
,{ "modifying" }
,{ "operations)." }
} , & fmt_text , & align_text } ;

Text b96 = { {
{ "shrink...()" , & fmt_text_b }
,{ "," }
,{ "extend...()" , & fmt_text_b }
,{ "and" }
,{ "append...()" , & fmt_text_b }
,{ "methods" }
,{ "are" }
,{ "the" }
,{ "same" }
,{ "as" }
,{ "for" }
,{ "DynArray" , & fmt_text_b }
,{ "." }
} , & fmt_text , & align_text } ;

Text b97 = { {
{ "Collector" , & fmt_text_b }
,{ "is" }
,{ "swappable" }
,{ "and" }
,{ "movable." }
} , & fmt_text , & align_text } ;

Text b98 = { {
{ "Array" }
,{ "algorithms" }
} , & fmt_h3 , & align_h3 } ;

Text b99 = { {
{ "CCore" , & fmt_text_b }
,{ "Array" , & fmt_text_b }
,{ "implementation" }
,{ "is" }
,{ "based" }
,{ "on" }
,{ "the" }
,{ "Array" , & fmt_text_b }
,{ "Algorithm" , & fmt_text_b }
,{ "Package" , & fmt_text_b }
,{ "s." }
,{ "The" }
,{ "default" }
,{ "package" }
,{ "is" }
,{ "the" }
,{ "ArrayAlgo" , & fmt_text_b }
,{ "." }
} , & fmt_text , & align_text } ;

Text b100 = { {
{ "The" }
,{ "exact" }
,{ "implementation" }
,{ "depends" }
,{ "on" }
,{ "the" }
,{ "kind" }
,{ "of" }
,{ "T" , & fmt_text_b }
,{ "." }
} , & fmt_text , & align_text } ;

Text b101 = { {
{ "If" }
,{ "the" }
,{ "type" }
,{ "T" , & fmt_text_b }
,{ "defines" }
,{ "the" }
,{ "inner" }
,{ "type" }
,{ "ArrayAlgoType" , & fmt_text_b }
,{ "," }
,{ "then" }
,{ "this" }
,{ "type" }
,{ "will" }
,{ "be" }
,{ "used" }
,{ "as" }
,{ "the" }
,{ "package." }
} , & fmt_text , & align_text } ;

Text b102 = { {
{ "Otherwise" }
,{ "there" }
,{ "are" }
,{ "two" }
,{ "variants:" }
,{ "one" }
,{ "for" }
,{ "the" }
,{ "POD" }
,{ "types," }
,{ "another" }
,{ "for" }
,{ "the" }
,{ "other" }
,{ "(class)" }
,{ "types." }
} , & fmt_text , & align_text } ;

Text b103 = { {
{ "ArrayAlgo_class" }
} , & fmt_h4 , & align_h4 } ;

Text b104 = { {
{ "ArrayAlgo_class" , & fmt_text_b }
,{ "is" }
,{ "the" }
,{ "generic" }
,{ "(class)" }
,{ "variant." }
,{ "The" }
,{ "template" }
,{ "argument" }
,{ "Flags" , & fmt_text_b }
,{ "provides" }
,{ "two" }
,{ "flags:" }
,{ "Default_no_throw" , & fmt_text_b }
,{ "and" }
,{ "Copy_no_throw" , & fmt_text_b }
,{ "." }
,{ "The" }
,{ "flag" }
,{ "is" }
,{ "true" , & fmt_text_b }
,{ "," }
,{ "if" }
,{ "the" }
,{ "correspondent" }
,{ "constructor" }
,{ "(default" }
,{ "or" }
,{ "copy)" }
,{ "is" }
,{ "no-throw" , & fmt_text_b }
,{ "or" }
,{ "does" }
,{ "not" }
,{ "exist." }
,{ "It's" }
,{ "an" }
,{ "obligation" }
,{ "of" }
,{ "the" }
,{ "class." }
,{ "The" }
,{ "flag" }
,{ "MoveTo_exist" , & fmt_text_b }
,{ "is" }
,{ "true" , & fmt_text_b }
,{ "for" }
,{ "replaceable" }
,{ "types." }
,{ "For" }
,{ "such" }
,{ "types" }
,{ "an" }
,{ "array" }
,{ "can" }
,{ "grow" }
,{ "above" }
,{ "the" }
,{ "initial" }
,{ "memory" }
,{ "allocation" }
,{ "length." }
} , & fmt_text , & align_text } ;

Text b105 = { {
{ "The" }
,{ "package" }
,{ "has" }
,{ "the" }
,{ "following" }
,{ "members." }
} , & fmt_text , & align_text } ;

Text b106 = { {
{ "Flags" }
,{ "Default_no_throw" , & fmt_text_b }
,{ "and" }
,{ "Copy_no_throw" , & fmt_text_b }
,{ "are" }
,{ "copied" }
,{ "from" }
,{ "the" }
,{ "Flags" , & fmt_text_b }
,{ "." }
} , & fmt_text , & align_text } ;

Text b107 = { {
{ "Flag" }
,{ "MoveTo_exist" , & fmt_text_b }
,{ "is" }
,{ "true" , & fmt_text_b }
,{ "for" }
,{ "replaceable" }
,{ "types." }
} , & fmt_text , & align_text } ;

Text b108 = { {
{ "Create_...()" , & fmt_text_b }
,{ "creates" }
,{ "a" }
,{ "range" }
,{ "of" }
,{ "objects" }
,{ "of" }
,{ "the" }
,{ "type" }
,{ "T" , & fmt_text_b }
,{ "at" }
,{ "the" }
,{ "given" }
,{ "place." }
,{ "To" }
,{ "create" }
,{ "an" }
,{ "object," }
,{ "the" }
,{ "correspondent" }
,{ "constructor" }
,{ "is" }
,{ "called." }
,{ "Objects" }
,{ "are" }
,{ "created" }
,{ "in" }
,{ "the" }
,{ "ascending" }
,{ "order." }
,{ "If" }
,{ "some" }
,{ "constructor" }
,{ "throw" }
,{ "an" }
,{ "exception," }
,{ "then" }
,{ "the" }
,{ "previously" }
,{ "constructed" }
,{ "objects" }
,{ "are" }
,{ "destroyed" }
,{ "and" }
,{ "the" }
,{ "exception" }
,{ "is" }
,{ "propagated." }
,{ "The" }
,{ "range" }
,{ "of" }
,{ "the" }
,{ "created" }
,{ "objects" }
,{ "is" }
,{ "returned." }
,{ "The" }
,{ "first" }
,{ "two" }
,{ "arguments" }
,{ "are:" }
,{ "the" }
,{ "place" }
,{ "to" }
,{ "construct" }
,{ "and" }
,{ "the" }
,{ "number" }
,{ "of" }
,{ "elements" }
,{ "to" }
,{ "construct." }
,{ "The" }
,{ "place" }
,{ "must" }
,{ "be" }
,{ "properly" }
,{ "aligned" }
,{ "and" }
,{ "the" }
,{ "memory" }
,{ "space" }
,{ "must" }
,{ "be" }
,{ "large" }
,{ "enough" }
,{ "to" }
,{ "contain" }
,{ "the" }
,{ "required" }
,{ "number" }
,{ "of" }
,{ "objects." }
} , & fmt_text , & align_text } ;

Text b109 = { {
{ "Create_raw()" , & fmt_text_b }
,{ "and" }
,{ "Create_default()" , & fmt_text_b }
,{ "use" }
,{ "the" }
,{ "default" }
,{ "constructor." }
} , & fmt_text , & align_text } ;

Text b110 = { {
{ "Create_fill()" , & fmt_text_b }
,{ "uses" }
,{ "a" }
,{ "constructor" }
,{ "with" }
,{ "the" }
,{ "given" }
,{ "set" }
,{ "of" }
,{ "arguments" }
,{ "for" }
,{ "each" }
,{ "object." }
} , & fmt_text , & align_text } ;

Text b111 = { {
{ "Create_copy()" , & fmt_text_b }
,{ "uses" }
,{ "the" }
,{ "copy" }
,{ "constructor." }
,{ "The" }
,{ "arguments" }
,{ "are" }
,{ "memberwise" }
,{ "selected" }
,{ "from" }
,{ "the" }
,{ "provided" }
,{ "range" }
,{ "of" }
,{ "objects." }
} , & fmt_text , & align_text } ;

Text b112 = { {
{ "Create_cast()" , & fmt_text_b }
,{ "uses" }
,{ "the" }
,{ "\"cast\"" }
,{ "constructor." }
,{ "The" }
,{ "arguments" }
,{ "are" }
,{ "memberwise" }
,{ "selected" }
,{ "from" }
,{ "the" }
,{ "provided" }
,{ "range" }
,{ "of" }
,{ "objects." }
} , & fmt_text , & align_text } ;

Text b113 = { {
{ "Create_swap()" , & fmt_text_b }
,{ "uses" }
,{ "the" }
,{ "default" }
,{ "constructor" }
,{ "and" }
,{ "the" }
,{ "swap" }
,{ "operation" }
,{ "to" }
,{ "create" }
,{ "objects." }
,{ "The" }
,{ "arguments" }
,{ "for" }
,{ "the" }
,{ "swap" }
,{ "are" }
,{ "memberwise" }
,{ "selected" }
,{ "from" }
,{ "the" }
,{ "provided" }
,{ "range" }
,{ "of" }
,{ "objects." }
} , & fmt_text , & align_text } ;

Text b114 = { {
{ "The" }
,{ "single" }
,{ "Create_swap()" , & fmt_text_b }
,{ "function" }
,{ "\"creates-swap\"" }
,{ "a" }
,{ "single" }
,{ "object." }
} , & fmt_text , & align_text } ;

Text b115 = { {
{ "ProvideLen()" , & fmt_text_b }
,{ "is" }
,{ "used" }
,{ "to" }
,{ "reallocate" }
,{ "an" }
,{ "array." }
,{ "It" }
,{ "is" }
,{ "called" }
,{ "if" }
,{ "there" }
,{ "is" }
,{ "no" }
,{ "sufficient" }
,{ "memory" }
,{ "to" }
,{ "extend" }
,{ "the" }
,{ "array." }
,{ "The" }
,{ "len" , & fmt_text_b }
,{ "is" }
,{ "the" }
,{ "array" }
,{ "length," }
,{ "the" }
,{ "extra_len" , & fmt_text_b }
,{ "is" }
,{ "the" }
,{ "number" }
,{ "of" }
,{ "extra" }
,{ "objects" }
,{ "to" }
,{ "be" }
,{ "constructed," }
,{ "the" }
,{ "maxlen" , & fmt_text_b }
,{ "is" }
,{ "the" }
,{ "allocated" }
,{ "length." }
,{ "The" }
,{ "length" }
,{ "returned" }
,{ "is" }
,{ "sufficient" }
,{ "to" }
,{ "extend" }
,{ "the" }
,{ "array" }
,{ "and" }
,{ "at" }
,{ "least" }
,{ "double" }
,{ "of" }
,{ "the" }
,{ "maxlen" , & fmt_text_b }
,{ "." }
,{ "An" }
,{ "exception" }
,{ "is" }
,{ "thrown" }
,{ "in" }
,{ "case" }
,{ "of" }
,{ "overflow." }
} , & fmt_text , & align_text } ;

Text b116 = { {
{ "MoveTo()" , & fmt_text_b }
,{ "moves" }
,{ "the" }
,{ "given" }
,{ "range" }
,{ "to" }
,{ "a" }
,{ "new" }
,{ "place." }
,{ "The" }
,{ "old" }
,{ "place" }
,{ "becomes" }
,{ "a" }
,{ "raw" }
,{ "memory." }
,{ "The" }
,{ "range" }
,{ "of" }
,{ "new" }
,{ "objects" }
,{ "is" }
,{ "returned." }
} , & fmt_text , & align_text } ;

Text b117 = { {
{ "Other" }
,{ "members" }
,{ "are" }
,{ "inherited" }
,{ "from" }
,{ "the" }
,{ "ArrayAlgoBase<T>" , & fmt_text_b }
,{ "." }
} , & fmt_text , & align_text } ;

Text b118 = { {
{ "ArrayAlgo_pod" }
} , & fmt_h4 , & align_h4 } ;

Text b119 = { {
{ "ArrayAlgo_pod" , & fmt_text_b }
,{ "is" }
,{ "the" }
,{ "POD" }
,{ "variant." }
} , & fmt_text , & align_text } ;

Text b120 = { {
{ "Flags" }
,{ "Default_no_throw" , & fmt_text_b }
,{ "," }
,{ "Copy_no_throw" , & fmt_text_b }
,{ "and" }
,{ "MoveTo_exist" , & fmt_text_b }
,{ "are" }
,{ "all" }
,{ "true" , & fmt_text_b }
,{ "." }
} , & fmt_text , & align_text } ;

Text b121 = { {
{ "Create_raw()" , & fmt_text_b }
,{ "is" }
,{ "not" }
,{ "using" }
,{ "default" }
,{ "initialization." }
,{ "It" }
,{ "leaves" }
,{ "the" }
,{ "memory" }
,{ "uninitialized." }
} , & fmt_text , & align_text } ;

Text b122 = { {
{ "Other" }
,{ "members" }
,{ "are" }
,{ "inherited" }
,{ "from" }
,{ "the" }
,{ "ArrayAlgoBase_nodtor<T>" , & fmt_text_b }
,{ "." }
} , & fmt_text , & align_text } ;

Text b123 = { {
{ "ArrayAlgo_mini" }
} , & fmt_h4 , & align_h4 } ;

Text b124 = { {
{ "ArrayAlgo_mini" , & fmt_text_b }
,{ "is" }
,{ "the" }
,{ "mini" }
,{ "variant" }
,{ "without" }
,{ "object" }
,{ "moving." }
,{ "It" }
,{ "is" }
,{ "assumed" }
,{ "only," }
,{ "that" }
,{ "the" }
,{ "destructor" }
,{ "~T()" , & fmt_text_b }
,{ "is" }
,{ "no-throw" , & fmt_text_b }
,{ "." }
,{ "Swap" }
,{ "and" }
,{ "move" }
,{ "are" }
,{ "not" }
,{ "used." }
} , & fmt_text , & align_text } ;

Text b125 = { {
{ "The" }
,{ "flag" }
,{ "MoveTo_exist" , & fmt_text_b }
,{ "is" }
,{ "false" , & fmt_text_b }
,{ "." }
} , & fmt_text , & align_text } ;

Text b126 = { {
{ "Other" }
,{ "members" }
,{ "are" }
,{ "inherited" }
,{ "from" }
,{ "the" }
,{ "ArrayAlgoBase<T>" , & fmt_text_b }
,{ "." }
} , & fmt_text , & align_text } ;

Text b127 = { {
{ "The" }
,{ "following" }
,{ "functions:" }
,{ "Create_swap()" , & fmt_text_b }
,{ "," }
,{ "ProvideLen()" , & fmt_text_b }
,{ "," }
,{ "MoveTo()" , & fmt_text_b }
,{ "are" }
,{ "omitted." }
,{ "Array," }
,{ "constructed" }
,{ "with" }
,{ "this" }
,{ "algorithm" }
,{ "package," }
,{ "cannot" }
,{ "be" }
,{ "extended" }
,{ "beyond" }
,{ "the" }
,{ "initial" }
,{ "memory" }
,{ "allocation" }
,{ "length." }
} , & fmt_text , & align_text } ;

Text b128 = { {
{ "To" }
,{ "use" }
,{ "this" }
,{ "package" }
,{ "with" }
,{ "the" }
,{ "DynArray" , & fmt_text_b }
,{ "you" }
,{ "can" }
,{ "use" }
,{ "the" }
,{ "following" }
,{ "type:" }
} , & fmt_text , & align_text } ;

Text b129 = { {
{ "ArrayAlgoBase" }
} , & fmt_h4 , & align_h4 } ;

Text b130 = { {
{ "ArrayAlgoBase" , & fmt_text_b }
,{ "is" }
,{ "a" }
,{ "common" }
,{ "package" }
,{ "for" }
,{ "all" }
,{ "ArrayAlgo" , & fmt_text_b }
,{ "s." }
,{ "It" }
,{ "has" }
,{ "two" }
,{ "variants:" }
,{ "common" }
,{ "and" }
,{ "specialized" }
,{ "ArrayAlgoBase_nodtor" , & fmt_text_b }
,{ "for" }
,{ "types" }
,{ "with" }
,{ "the" }
,{ "trivial" }
,{ "destructor." }
} , & fmt_text , & align_text } ;

Text b131 = { {
{ "Create()" , & fmt_text_b }
,{ "uses" }
,{ "the" }
,{ "given" }
,{ "creator" }
,{ "for" }
,{ "the" }
,{ "object" }
,{ "creation." }
,{ "See" }
,{ "below" }
,{ "about" }
,{ "creators." }
} , & fmt_text , & align_text } ;

Text b132 = { {
{ "Single" }
,{ "Destroy()" , & fmt_text_b }
,{ "destroys" }
,{ "the" }
,{ "object" }
,{ "(but" }
,{ "don't" }
,{ "free" }
,{ "the" }
,{ "memory)." }
} , & fmt_text , & align_text } ;

Text b133 = { {
{ "Range" }
,{ "Destroy()" , & fmt_text_b }
,{ "destroys" }
,{ "the" }
,{ "given" }
,{ "range" }
,{ "of" }
,{ "objects." }
} , & fmt_text , & align_text } ;

Text b134 = { {
{ "There" }
,{ "are" }
,{ "four" }
,{ "inner" }
,{ "\"guard\"" }
,{ "classes." }
,{ "They" }
,{ "are" }
,{ "used" }
,{ "to" }
,{ "created" }
,{ "a" }
,{ "range" }
,{ "of" }
,{ "objects." }
,{ "Guards" }
,{ "are" }
,{ "responsible" }
,{ "for" }
,{ "the" }
,{ "object" }
,{ "destruction" }
,{ "in" }
,{ "case" }
,{ "of" }
,{ "failure." }
} , & fmt_text , & align_text } ;

Text b135 = { {
{ "BuildGuard" , & fmt_text_b }
,{ "is" }
,{ "used" }
,{ "to" }
,{ "create" }
,{ "a" }
,{ "range" }
,{ "of" }
,{ "objects." }
,{ "The" }
,{ "constructor" }
,{ "argument" }
,{ "is" }
,{ "the" }
,{ "place" }
,{ "for" }
,{ "the" }
,{ "range." }
,{ "It" }
,{ "must" }
,{ "be" }
,{ "properly" }
,{ "aligned" }
,{ "and" }
,{ "the" }
,{ "memory" }
,{ "space" }
,{ "must" }
,{ "be" }
,{ "large" }
,{ "enough" }
,{ "to" }
,{ "store" }
,{ "the" }
,{ "range." }
} , & fmt_text , & align_text } ;

Text b136 = { {
{ "at()" , & fmt_text_b }
,{ "is" }
,{ "the" }
,{ "current" }
,{ "place" }
,{ "for" }
,{ "the" }
,{ "object" }
,{ "creation." }
} , & fmt_text , & align_text } ;

Text b137 = { {
{ "operator" , & fmt_text_b }
,{ "++" , & fmt_text_b }
,{ "()" , & fmt_text_b }
,{ "must" }
,{ "be" }
,{ "called" }
,{ "after" }
,{ "the" }
,{ "successful" }
,{ "creation" }
,{ "of" }
,{ "an" }
,{ "object" }
,{ "at" }
,{ "the" }
,{ "current" }
,{ "position," }
,{ "it" }
,{ "moves" }
,{ "to" }
,{ "the" }
,{ "next" }
,{ "object" }
,{ "position." }
} , & fmt_text , & align_text } ;

Text b138 = { {
{ "disarm()" , & fmt_text_b }
,{ "is" }
,{ "called" }
,{ "after" }
,{ "the" }
,{ "desired" }
,{ "number" }
,{ "of" }
,{ "objects" }
,{ "are" }
,{ "created." }
,{ "It" }
,{ "\"disarms\"" }
,{ "the" }
,{ "guard" }
,{ "and" }
,{ "returns" }
,{ "the" }
,{ "created" }
,{ "range." }
} , & fmt_text , & align_text } ;

Text b139 = { {
{ "The" }
,{ "BuildGuard" , & fmt_text_b }
,{ "destructor" }
,{ "destroys" }
,{ "the" }
,{ "created" }
,{ "objects." }
,{ "It" }
,{ "must" }
,{ "be" }
,{ "disarmed" }
,{ "to" }
,{ "prevent" }
,{ "the" }
,{ "destruction." }
} , & fmt_text , & align_text } ;

Text b140 = { {
{ "CreateGuard" , & fmt_text_b }
,{ "is" }
,{ "used" }
,{ "for" }
,{ "creation" }
,{ "a" }
,{ "range" }
,{ "of" }
,{ "objects" }
,{ "with" }
,{ "the" }
,{ "given" }
,{ "length." }
,{ "Constructor's" }
,{ "arguments" }
,{ "are:" }
,{ "the" }
,{ "place" }
,{ "of" }
,{ "the" }
,{ "range" }
,{ "and" }
,{ "the" }
,{ "final" }
,{ "number" }
,{ "of" }
,{ "objects." }
,{ "The" }
,{ "remaining" }
,{ "methods" }
,{ "are" }
,{ "the" }
,{ "same" }
,{ "as" }
,{ "for" }
,{ "BuildGuard" , & fmt_text_b }
,{ "." }
,{ "Using" }
,{ "CreateGuard" , & fmt_text_b }
,{ "you" }
,{ "must" }
,{ "create" }
,{ "the" }
,{ "exact" }
,{ "number" }
,{ "of" }
,{ "objects." }
} , & fmt_text , & align_text } ;

Text b141 = { {
{ "CreateGuard_nothrow" , & fmt_text_b }
,{ "is" }
,{ "a" }
,{ "\"no-throw\"" }
,{ "variant" }
,{ "of" }
,{ "the" }
,{ "CreateGuard" , & fmt_text_b }
,{ "." }
,{ "It" }
,{ "is" }
,{ "used" }
,{ "for" }
,{ "the" }
,{ "creation" }
,{ "of" }
,{ "a" }
,{ "range" }
,{ "of" }
,{ "objects" }
,{ "with" }
,{ "the" }
,{ "given" }
,{ "length," }
,{ "if" }
,{ "there" }
,{ "will" }
,{ "be" }
,{ "no" }
,{ "exceptions" }
,{ "during" }
,{ "the" }
,{ "objects" }
,{ "construction." }
} , & fmt_text , & align_text } ;

Text b142 = { {
{ "CreateGuardNoThrow" , & fmt_text_b }
,{ "is" }
,{ "the" }
,{ "one" }
,{ "of" }
,{ "the" }
,{ "CreateGuard" , & fmt_text_b }
,{ "and" }
,{ "CreateGuard_nothrow" , & fmt_text_b }
,{ "," }
,{ "depending" }
,{ "on" }
,{ "the" }
,{ "no_throw" , & fmt_text_b }
,{ "template" }
,{ "parameter." }
} , & fmt_text , & align_text } ;

Text b143 = { {
{ "Below" }
,{ "is" }
,{ "the" }
,{ "implementation" }
,{ "of" }
,{ "the" }
,{ "generic" }
,{ "Create" , & fmt_text_b }
,{ "," }
,{ "it" }
,{ "uses" }
,{ "the" }
,{ "CreateGuardNoThrow" , & fmt_text_b }
,{ "." }
} , & fmt_text , & align_text } ;

Text b144 = { {
{ "ArrayAlgoBase_nodtor<T>" , & fmt_text_b }
,{ "provides" }
,{ "the" }
,{ "same" }
,{ "set" }
,{ "of" }
,{ "algorithms," }
,{ "but" }
,{ "implemented" }
,{ "with" }
,{ "respect" }
,{ "to" }
,{ "destructor" }
,{ "triviality." }
} , & fmt_text , & align_text } ;

Text b145 = { {
{ "Creators" }
,{ "and" }
,{ "Builders" }
} , & fmt_h4 , & align_h4 } ;

Text b146 = { {
{ "Creator" , & fmt_text_b }
,{ "is" }
,{ "a" }
,{ "functor," }
,{ "creating" }
,{ "objects." }
,{ "It" }
,{ "looks" }
,{ "like" }
,{ "this:" }
} , & fmt_text , & align_text } ;

Text b147 = { {
{ "Or" }
,{ "like" }
,{ "this:" }
} , & fmt_text , & align_text } ;

Text b148 = { {
{ "You" }
,{ "may" }
,{ "use" }
,{ "a" }
,{ "Creator" , & fmt_text_b }
,{ "in" }
,{ "a" }
,{ "generic" }
,{ "array" }
,{ "\"Creator\"" }
,{ "constructors" }
,{ "and" }
,{ "methods." }
} , & fmt_text , & align_text } ;

Text b149 = { {
{ "Builder" , & fmt_text_b }
,{ "is" }
,{ "a" }
,{ "functor," }
,{ "creating" }
,{ "a" }
,{ "range" }
,{ "of" }
,{ "objects." }
,{ "It" }
,{ "looks" }
,{ "like:" }
} , & fmt_text , & align_text } ;

Text b150 = { {
{ "Or" }
,{ "like" }
,{ "this:" }
} , & fmt_text , & align_text } ;

Text b151 = { {
{ "Builder" , & fmt_text_b }
,{ "reports" }
,{ "the" }
,{ "maximum" }
,{ "object" }
,{ "number" }
,{ "it" }
,{ "will" }
,{ "create" }
,{ "through" }
,{ "the" }
,{ "method" }
,{ "getLen()" , & fmt_text_b }
,{ "." }
,{ "operator" , & fmt_text_b }
,{ "()" , & fmt_text_b }
,{ "gets" }
,{ "the" }
,{ "place" }
,{ "for" }
,{ "the" }
,{ "range" }
,{ "of" }
,{ "getLen()" , & fmt_text_b }
,{ "elements," }
,{ "it" }
,{ "either" }
,{ "creates" }
,{ "the" }
,{ "range" }
,{ "of" }
,{ "objects" }
,{ "up" }
,{ "to" }
,{ "this" }
,{ "length" }
,{ "and" }
,{ "returns" }
,{ "it," }
,{ "or" }
,{ "leaves" }
,{ "the" }
,{ "memory" }
,{ "raw" }
,{ "and" }
,{ "throws" }
,{ "an" }
,{ "exception." }
} , & fmt_text , & align_text } ;

Text b152 = { {
{ "You" }
,{ "may" }
,{ "use" }
,{ "a" }
,{ "Builder" , & fmt_text_b }
,{ "in" }
,{ "a" }
,{ "generic" }
,{ "array" }
,{ "\"Builder\"" }
,{ "constructors" }
,{ "and" }
,{ "methods." }
} , & fmt_text , & align_text } ;

Text b153 = { {
{ "There" }
,{ "are" }
,{ "two" }
,{ "concepts" }
,{ "for" }
,{ "creators" }
,{ "and" }
,{ "builders:" }
} , & fmt_text , & align_text } ;

Text b154 = { {
{ "Standard" }
,{ "creators" }
} , & fmt_h4 , & align_h4 } ;

Text b155 = { {
{ "There" }
,{ "is" }
,{ "a" }
,{ "list" }
,{ "of" }
,{ "standard" }
,{ "creators." }
} , & fmt_text , & align_text } ;

Text b156 = { {
{ "Memory" }
,{ "management" }
} , & fmt_h4 , & align_h4 } ;

Text b157 = { {
{ "All" }
,{ "default" }
,{ "algorithm" }
,{ "packages" }
,{ "inherit" }
,{ "the" }
,{ "base" }
,{ "class" }
,{ "ArrayAlgoMemBase" , & fmt_text_b }
,{ "." }
} , & fmt_text , & align_text } ;

Text b158 = { {
{ "This" }
,{ "class" }
,{ "defines" }
,{ "default" }
,{ "memory-management" }
,{ "functions," }
,{ "used" }
,{ "by" }
,{ "arrays" }
,{ "to" }
,{ "allocate," }
,{ "extend," }
,{ "shrink" }
,{ "and" }
,{ "release" }
,{ "memory" }
,{ "blocks." }
,{ "If" }
,{ "you" }
,{ "define" }
,{ "a" }
,{ "custom" }
,{ "algorithm" }
,{ "package" }
,{ "for" }
,{ "your" }
,{ "purpose," }
,{ "you" }
,{ "may" }
,{ "define" }
,{ "custom" }
,{ "memory" }
,{ "allocation" }
,{ "functions" }
,{ "with" }
,{ "the" }
,{ "following" }
,{ "semantic." }
} , & fmt_text , & align_text } ;

Text b159 = { {
{ "MemAlloc()" , & fmt_text_b }
,{ "allocates" }
,{ "a" }
,{ "memory" }
,{ "block" }
,{ "of" }
,{ "the" }
,{ "required" }
,{ "length." }
,{ "The" }
,{ "block" }
,{ "is" }
,{ "aligned." }
,{ "An" }
,{ "exception" }
,{ "is" }
,{ "thrown" }
,{ "in" }
,{ "case" }
,{ "of" }
,{ "error." }
} , & fmt_text , & align_text } ;

Text b160 = { {
{ "MemFree()" , & fmt_text_b }
,{ "releases" }
,{ "the" }
,{ "previously" }
,{ "allocated" }
,{ "memory" }
,{ "block." }
,{ "The" }
,{ "function" }
,{ "is" }
,{ "never" }
,{ "called" }
,{ "with" }
,{ "the" }
,{ "null" }
,{ "argument." }
} , & fmt_text , & align_text } ;

Text b161 = { {
{ "MemExtend()" , & fmt_text_b }
,{ "tries" }
,{ "to" }
,{ "extend" }
,{ "the" }
,{ "previously" }
,{ "allocated" }
,{ "memory" }
,{ "block" }
,{ "length" }
,{ "to" }
,{ "be" }
,{ "at" }
,{ "least" }
,{ "the" }
,{ "given" }
,{ "argument." }
,{ "If" }
,{ "the" }
,{ "return" }
,{ "value" }
,{ "is" }
,{ "true" , & fmt_text_b }
,{ "," }
,{ "then" }
,{ "the" }
,{ "attempt" }
,{ "was" }
,{ "successful." }
} , & fmt_text , & align_text } ;

Text b162 = { {
{ "MemShrink()" , & fmt_text_b }
,{ "shrinks" }
,{ "the" }
,{ "memory" }
,{ "block" }
,{ "length" }
,{ "to" }
,{ "be" }
,{ "at" }
,{ "least" }
,{ "the" }
,{ "given" }
,{ "argument." }
,{ "The" }
,{ "return" }
,{ "value" }
,{ "is" }
,{ "never" }
,{ "used." }
} , & fmt_text , & align_text } ;

Text b163 = { {
{ "Insert/Delete" }
,{ "algorithms" }
} , & fmt_h4 , & align_h4 } ;

Text b164 = { {
{ "Insert" }
,{ "or" }
,{ "delete" }
,{ "array" }
,{ "elements" }
,{ "in" }
,{ "the" }
,{ "middle" }
,{ "of" }
,{ "the" }
,{ "array" }
,{ "are" }
,{ "not" }
,{ "natural" }
,{ "array" }
,{ "methods." }
,{ "They" }
,{ "have" }
,{ "a" }
,{ "linear" }
,{ "complexity." }
,{ "But" }
,{ "sometimes" }
,{ "they" }
,{ "are" }
,{ "necessary." }
,{ "These" }
,{ "algorithms" }
,{ "are" }
,{ "implemented" }
,{ "as" }
,{ "free" }
,{ "functions." }
} , & fmt_text , & align_text } ;

Text b165 = { {
{ "These" }
,{ "functions" }
,{ "delete" }
,{ "an" }
,{ "element" }
,{ "from" }
,{ "the" }
,{ "array" }
,{ "at" }
,{ "the" }
,{ "given" }
,{ "index." }
,{ "The" }
,{ "first" }
,{ "two" }
,{ "return" }
,{ "false" , & fmt_text_b }
,{ "if" }
,{ "the" }
,{ "index" }
,{ "is" }
,{ "invalid." }
,{ "The" }
,{ "last" }
,{ "two" }
,{ "throw" }
,{ "an" }
,{ "exception" }
,{ "in" }
,{ "such" }
,{ "case." }
,{ "CopyDel" , & fmt_text_b }
,{ "copies" }
,{ "elements," }
,{ "SwapDel" , & fmt_text_b }
,{ "uses" }
,{ "swapping." }
} , & fmt_text , & align_text } ;

Text b166 = { {
{ "These" }
,{ "functions" }
,{ "delete" }
,{ "a" }
,{ "range" }
,{ "of" }
,{ "elements" }
,{ "from" }
,{ "the" }
,{ "array." }
,{ "The" }
,{ "first" }
,{ "two" }
,{ "return" }
,{ "the" }
,{ "count" }
,{ "of" }
,{ "deleted" }
,{ "elements." }
,{ "The" }
,{ "last" }
,{ "two" }
,{ "throw" }
,{ "an" }
,{ "exception" }
,{ "if" }
,{ "the" }
,{ "subrange" }
,{ "does" }
,{ "not" }
,{ "fit" }
,{ "the" }
,{ "array" }
,{ "range." }
,{ "CopyDel" , & fmt_text_b }
,{ "copies" }
,{ "elements," }
,{ "SwapDel" , & fmt_text_b }
,{ "uses" }
,{ "swapping." }
} , & fmt_text , & align_text } ;

Text b167 = { {
{ "These" }
,{ "functions" }
,{ "insert" }
,{ "an" }
,{ "element" }
,{ "to" }
,{ "the" }
,{ "array" }
,{ "at" }
,{ "the" }
,{ "given" }
,{ "index." }
,{ "The" }
,{ "valid" }
,{ "index" }
,{ "range" }
,{ "is" }
,{ "[0,len]" , & fmt_text_b }
,{ "," }
,{ "where" }
,{ "len" , & fmt_text_b }
,{ "is" }
,{ "the" }
,{ "array" }
,{ "length." }
,{ "The" }
,{ "first" }
,{ "two" }
,{ "cap" }
,{ "the" }
,{ "index" }
,{ "and" }
,{ "return" }
,{ "false" , & fmt_text_b }
,{ "if" }
,{ "the" }
,{ "index" }
,{ "is" }
,{ "out" }
,{ "of" }
,{ "range." }
,{ "The" }
,{ "last" }
,{ "two" }
,{ "throw" }
,{ "an" }
,{ "exception" }
,{ "in" }
,{ "such" }
,{ "case." }
,{ "They" }
,{ "also" }
,{ "return" }
,{ "the" }
,{ "pointer" }
,{ "to" }
,{ "the" }
,{ "inserted" }
,{ "object." }
,{ "CopyIns" , & fmt_text_b }
,{ "copies" }
,{ "elements," }
,{ "SwapIns" , & fmt_text_b }
,{ "uses" }
,{ "swapping." }
,{ "Extra" }
,{ "arguments" }
,{ "are" }
,{ "used" }
,{ "to" }
,{ "call" }
,{ "an" }
,{ "element" }
,{ "constructor." }
} , & fmt_text , & align_text } ;

Text b168 = { {
{ "All" }
,{ "these" }
,{ "functions" }
,{ "insert" }
,{ "a" }
,{ "range" }
,{ "of" }
,{ "elements" }
,{ "into" }
,{ "the" }
,{ "array." }
,{ "ind" , & fmt_text_b }
,{ "determines" }
,{ "the" }
,{ "index" }
,{ "of" }
,{ "insertion." }
,{ "The" }
,{ "range" }
,{ "(as" }
,{ "PtrLen" , & fmt_text_b }
,{ ")" }
,{ "of" }
,{ "created" }
,{ "elements" }
,{ "if" }
,{ "returned." }
,{ "If" }
,{ "ind" , & fmt_text_b }
,{ "exceeds" }
,{ "the" }
,{ "array" }
,{ "length," }
,{ "elements" }
,{ "are" }
,{ "created" }
,{ "at" }
,{ "the" }
,{ "end" }
,{ "of" }
,{ "the" }
,{ "array." }
} , & fmt_text , & align_text } ;

Text b169 = { {
{ "These" }
,{ "functions" }
,{ "can" }
,{ "be" }
,{ "used" }
,{ "to" }
,{ "\"prepare\"" }
,{ "the" }
,{ "array" }
,{ "for" }
,{ "an" }
,{ "element" }
,{ "insertion." }
,{ "They" }
,{ "are" }
,{ "intended" }
,{ "to" }
,{ "be" }
,{ "used" }
,{ "with" }
,{ "conjunction" }
,{ "of" }
,{ "insertion" }
,{ "functions." }
} , & fmt_text , & align_text } ;

Text b170 = { {
{ "ArrayInsRangeGuard()" , & fmt_text_b }
,{ "throws" }
,{ "an" }
,{ "exception" }
,{ "if" }
,{ "ind" , & fmt_text_b }
,{ "exceeds" }
,{ "the" }
,{ "array" }
,{ "length." }
} , & fmt_text , & align_text } ;

Text b171 = { {
{ "ArrayInsRangeFill()" , & fmt_text_b }
,{ "extends" }
,{ "the" }
,{ "array" }
,{ "if" }
,{ "ind" , & fmt_text_b }
,{ "exceeds" }
,{ "the" }
,{ "array" }
,{ "length" }
,{ "to" }
,{ "equalize" }
,{ "them." }
,{ "The" }
,{ "second" }
,{ "variant" }
,{ "reserves" }
,{ "additional" }
,{ "memory" }
,{ "behind" }
,{ "for" }
,{ "further" }
,{ "extension" }
,{ "by" }
,{ "count" , & fmt_text_b }
,{ "elements." }
} , & fmt_text , & align_text } ;

Page page = { "test" ,
{
 { & b0 , null , inner_h2 , outer_h2 , back_h2 }
 ,{ & b1 , null , inner_text_Files , outer_text_Files , back_text_Files }
 ,{ & b2 , null , inner_text_Files , outer_text_Files , back_text_Files }
 ,{ & b3 , null , inner_h3 , outer_h3 , back_h3 }
 ,{ & b4 , null , inner_text , outer_text , back_text }
 ,{ & b5 , null , inner_text , outer_text , back_text }
 ,{ & b6 , null , inner_text , outer_text , back_text }
 ,{ & b7 , null , inner_h3 , outer_h3 , back_h3 }
 ,{ & b8 , null , inner_text , outer_text , back_text }
 ,{ & b9 , null , inner_text , outer_text , back_text }
 ,{ & b10 , null , inner_text , outer_text , back_text }
 ,{ & b11 , null , inner_text , outer_text , back_text }
 ,{ & b12 , null , inner_text , outer_text , back_text }
 ,{ & b13 , null , inner_text , outer_text , back_text }
 ,{ & b14 , null , inner_text , outer_text , back_text }
 ,{ & b15 , null , inner_text , outer_text , back_text }
 ,{ & b16 , null , inner_h4 , outer_h4 , back_h4 }
 ,{ & b17 , null , inner_text , outer_text , back_text }
 ,{ & b18 , null , inner_text , outer_text , back_text }
 ,{ & b19 , null , inner_text , outer_text , back_text }
 ,{ & b20 , null , inner_text , outer_text , back_text }
 ,{ & b21 , null , inner_text , outer_text , back_text }
 ,{ & b22 , null , inner_text , outer_text , back_text }
 ,{ & b23 , null , inner_text , outer_text , back_text }
 ,{ & b24 , null , inner_h4 , outer_h4 , back_h4 }
 ,{ & b25 , null , inner_text , outer_text , back_text }
 ,{ & b26 , null , inner_text , outer_text , back_text }
 ,{ & b27 , null , inner_text , outer_text , back_text }
 ,{ & b28 , null , inner_text , outer_text , back_text }
 ,{ & b29 , null , inner_text , outer_text , back_text }
 ,{ & b30 , null , inner_h4 , outer_h4 , back_h4 }
 ,{ & b31 , null , inner_text , outer_text , back_text }
 ,{ & b32 , null , inner_text , outer_text , back_text }
 ,{ & b33 , null , inner_text , outer_text , back_text }
 ,{ & b34 , null , inner_text , outer_text , back_text }
 ,{ & b35 , null , inner_text , outer_text , back_text }
 ,{ & b36 , null , inner_text , outer_text , back_text }
 ,{ & b37 , null , inner_text , outer_text , back_text }
 ,{ & b38 , null , inner_text , outer_text , back_text }
 ,{ & b39 , null , inner_text , outer_text , back_text }
 ,{ & b40 , null , inner_text , outer_text , back_text }
 ,{ & b41 , null , inner_text , outer_text , back_text }
 ,{ & b42 , null , inner_text , outer_text , back_text }
 ,{ & b43 , null , inner_text , outer_text , back_text }
 ,{ & b44 , null , inner_text , outer_text , back_text }
 ,{ & b45 , null , inner_text , outer_text , back_text }
 ,{ & b46 , null , inner_text , outer_text , back_text }
 ,{ & b47 , null , inner_text , outer_text , back_text }
 ,{ & b48 , null , inner_text , outer_text , back_text }
 ,{ & b49 , null , inner_text , outer_text , back_text }
 ,{ & b50 , null , inner_text , outer_text , back_text }
 ,{ & b51 , null , inner_text , outer_text , back_text }
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
 ,{ & b65 , null , inner_text , outer_text , back_text }
 ,{ & b66 , null , inner_text , outer_text , back_text }
 ,{ & b67 , null , inner_text , outer_text , back_text }
 ,{ & b68 , null , inner_text , outer_text , back_text }
 ,{ & b69 , null , inner_text , outer_text , back_text }
 ,{ & b70 , null , inner_text , outer_text , back_text }
 ,{ & b71 , null , inner_text , outer_text , back_text }
 ,{ & b72 , null , inner_text , outer_text , back_text }
 ,{ & b73 , null , inner_h4 , outer_h4 , back_h4 }
 ,{ & b74 , null , inner_text , outer_text , back_text }
 ,{ & b75 , null , inner_text , outer_text , back_text }
 ,{ & b76 , null , inner_text , outer_text , back_text }
 ,{ & b77 , null , inner_text , outer_text , back_text }
 ,{ & b78 , null , inner_text , outer_text , back_text }
 ,{ & b79 , null , inner_text , outer_text , back_text }
 ,{ & b80 , null , inner_text , outer_text , back_text }
 ,{ & b81 , null , inner_text , outer_text , back_text }
 ,{ & b82 , null , inner_text , outer_text , back_text }
 ,{ & b83 , null , inner_text , outer_text , back_text }
 ,{ & b84 , null , inner_h4 , outer_h4 , back_h4 }
 ,{ & b85 , null , inner_text , outer_text , back_text }
 ,{ & b86 , null , inner_text , outer_text , back_text }
 ,{ & b87 , null , inner_text , outer_text , back_text }
 ,{ & b88 , null , inner_text , outer_text , back_text }
 ,{ & b89 , null , inner_text , outer_text , back_text }
 ,{ & b90 , null , inner_text , outer_text , back_text }
 ,{ & b91 , null , inner_text , outer_text , back_text }
 ,{ & b92 , null , inner_text , outer_text , back_text }
 ,{ & b93 , null , inner_text , outer_text , back_text }
 ,{ & b94 , null , inner_text , outer_text , back_text }
 ,{ & b95 , null , inner_text , outer_text , back_text }
 ,{ & b96 , null , inner_text , outer_text , back_text }
 ,{ & b97 , null , inner_text , outer_text , back_text }
 ,{ & b98 , null , inner_h3 , outer_h3 , back_h3 }
 ,{ & b99 , null , inner_text , outer_text , back_text }
 ,{ & b100 , null , inner_text , outer_text , back_text }
 ,{ & b101 , null , inner_text , outer_text , back_text }
 ,{ & b102 , null , inner_text , outer_text , back_text }
 ,{ & b103 , null , inner_h4 , outer_h4 , back_h4 }
 ,{ & b104 , null , inner_text , outer_text , back_text }
 ,{ & b105 , null , inner_text , outer_text , back_text }
 ,{ & b106 , null , inner_text , outer_text , back_text }
 ,{ & b107 , null , inner_text , outer_text , back_text }
 ,{ & b108 , null , inner_text , outer_text , back_text }
 ,{ & b109 , null , inner_text , outer_text , back_text }
 ,{ & b110 , null , inner_text , outer_text , back_text }
 ,{ & b111 , null , inner_text , outer_text , back_text }
 ,{ & b112 , null , inner_text , outer_text , back_text }
 ,{ & b113 , null , inner_text , outer_text , back_text }
 ,{ & b114 , null , inner_text , outer_text , back_text }
 ,{ & b115 , null , inner_text , outer_text , back_text }
 ,{ & b116 , null , inner_text , outer_text , back_text }
 ,{ & b117 , null , inner_text , outer_text , back_text }
 ,{ & b118 , null , inner_h4 , outer_h4 , back_h4 }
 ,{ & b119 , null , inner_text , outer_text , back_text }
 ,{ & b120 , null , inner_text , outer_text , back_text }
 ,{ & b121 , null , inner_text , outer_text , back_text }
 ,{ & b122 , null , inner_text , outer_text , back_text }
 ,{ & b123 , null , inner_h4 , outer_h4 , back_h4 }
 ,{ & b124 , null , inner_text , outer_text , back_text }
 ,{ & b125 , null , inner_text , outer_text , back_text }
 ,{ & b126 , null , inner_text , outer_text , back_text }
 ,{ & b127 , null , inner_text , outer_text , back_text }
 ,{ & b128 , null , inner_text , outer_text , back_text }
 ,{ & b129 , null , inner_h4 , outer_h4 , back_h4 }
 ,{ & b130 , null , inner_text , outer_text , back_text }
 ,{ & b131 , null , inner_text , outer_text , back_text }
 ,{ & b132 , null , inner_text , outer_text , back_text }
 ,{ & b133 , null , inner_text , outer_text , back_text }
 ,{ & b134 , null , inner_text , outer_text , back_text }
 ,{ & b135 , null , inner_text , outer_text , back_text }
 ,{ & b136 , null , inner_text , outer_text , back_text }
 ,{ & b137 , null , inner_text , outer_text , back_text }
 ,{ & b138 , null , inner_text , outer_text , back_text }
 ,{ & b139 , null , inner_text , outer_text , back_text }
 ,{ & b140 , null , inner_text , outer_text , back_text }
 ,{ & b141 , null , inner_text , outer_text , back_text }
 ,{ & b142 , null , inner_text , outer_text , back_text }
 ,{ & b143 , null , inner_text , outer_text , back_text }
 ,{ & b144 , null , inner_text , outer_text , back_text }
 ,{ & b145 , null , inner_h4 , outer_h4 , back_h4 }
 ,{ & b146 , null , inner_text , outer_text , back_text }
 ,{ & b147 , null , inner_text , outer_text , back_text }
 ,{ & b148 , null , inner_text , outer_text , back_text }
 ,{ & b149 , null , inner_text , outer_text , back_text }
 ,{ & b150 , null , inner_text , outer_text , back_text }
 ,{ & b151 , null , inner_text , outer_text , back_text }
 ,{ & b152 , null , inner_text , outer_text , back_text }
 ,{ & b153 , null , inner_text , outer_text , back_text }
 ,{ & b154 , null , inner_h4 , outer_h4 , back_h4 }
 ,{ & b155 , null , inner_text , outer_text , back_text }
 ,{ & b156 , null , inner_h4 , outer_h4 , back_h4 }
 ,{ & b157 , null , inner_text , outer_text , back_text }
 ,{ & b158 , null , inner_text , outer_text , back_text }
 ,{ & b159 , null , inner_text , outer_text , back_text }
 ,{ & b160 , null , inner_text , outer_text , back_text }
 ,{ & b161 , null , inner_text , outer_text , back_text }
 ,{ & b162 , null , inner_text , outer_text , back_text }
 ,{ & b163 , null , inner_h4 , outer_h4 , back_h4 }
 ,{ & b164 , null , inner_text , outer_text , back_text }
 ,{ & b165 , null , inner_text , outer_text , back_text }
 ,{ & b166 , null , inner_text , outer_text , back_text }
 ,{ & b167 , null , inner_text , outer_text , back_text }
 ,{ & b168 , null , inner_text , outer_text , back_text }
 ,{ & b169 , null , inner_text , outer_text , back_text }
 ,{ & b170 , null , inner_text , outer_text , back_text }
 ,{ & b171 , null , inner_text , outer_text , back_text }
} , NoColor , NoColor , null , null , null };

