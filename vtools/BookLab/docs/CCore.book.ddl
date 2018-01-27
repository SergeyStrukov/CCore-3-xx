/* CCore.book.ddl */

include <CCore.style.ddl>

scope Pages {

Page page1 = { Pages#PageName , {
{ &o1 }
,{ &o2 }
} };

Text o1 = { {
{"CCore"}
} , &fmt_h1 , &align_h1 } ;



TextList o2 = { {{"1.",{
{ &o3 , null , {0,0} , {0,0} }
}}
,{"2.",{
{ &o5 , null , {0,0} , {0,0} }
}}
,{"3.",{
{ &o7 , null , {0,0} , {0,0} }
,{ &o8 , null , {0,0} , {0,0} }
}}
,{"4.",{
{ &o16 , null , {0,0} , {0,0} }
,{ &o17 , null , {0,0} , {0,0} }
}}
,{"5.",{
{ &o172 , null , {0,0} , {0,0} }
,{ &o173 , null , {0,0} , {0,0} }
}}
,{"6.",{
{ &o297 , null , {0,0} , {0,0} }
,{ &o298 , null , {0,0} , {0,0} }
}}
,{"7.",{
{ &o321 , null , {0,0} , {0,0} }
,{ &o322 , null , {0,0} , {0,0} }
}}
,{"8.",{
{ &o372 , null , {0,0} , {0,0} }
,{ &o373 , null , {0,0} , {0,0} }
}}
,{"9.",{
{ &o381 , null , {0,0} , {0,0} }
,{ &o382 , null , {0,0} , {0,0} }
}}
,{"10.",{
{ &o388 , null , {0,0} , {0,0} }
,{ &o389 , null , {0,0} , {0,0} }
}}
,{"11.",{
{ &o401 , null , {0,0} , {0,0} }
,{ &o402 , null , {0,0} , {0,0} }
}}
,{"12.",{
{ &o418 , null , {0,0} , {0,0} }
,{ &o419 , null , {0,0} , {0,0} }
}}
,{"13.",{
{ &o429 , null , {0,0} , {0,0} }
}}
,{"14.",{
{ &o431 , null , {0,0} , {0,0} }
}}
,{"15.",{
{ &o433 , null , {0,0} , {0,0} }
}}
,{"16.",{
{ &o435 , null , {0,0} , {0,0} }
}}
,{"17.",{
{ &o437 , null , {0,0} , {0,0} }
,{ &o438 , null , {0,0} , {0,0} }
}}
,{"18.",{
{ &o450 , null , {0,0} , {0,0} }
,{ &o451 , null , {0,0} , {0,0} }
}}
,{"19.",{
{ &o469 , null , {0,0} , {0,0} }
,{ &o470 , null , {0,0} , {0,0} }
}}
,{"20.",{
{ &o488 , null , {0,0} , {0,0} }
,{ &o489 , null , {0,0} , {0,0} }
}}
,{"21.",{
{ &o495 , null , {0,0} , {0,0} }
,{ &o496 , null , {0,0} , {0,0} }
}}
,{"22.",{
{ &o542 , null , {0,0} , {0,0} }
}}
,{"23.",{
{ &o544 , null , {0,0} , {0,0} }
}}
,{"24.",{
{ &o546 , null , {0,0} , {0,0} }
,{ &o547 , null , {0,0} , {0,0} }
}}
,{"25.",{
{ &o587 , null , {0,0} , {0,0} }
,{ &o588 , null , {0,0} , {0,0} }
}}
,{"26.",{
{ &o633 , null , {0,0} , {0,0} }
,{ &o634 , null , {0,0} , {0,0} }
}}
} };

Text o3 = { {
{"Introduction",&fmt_h}
} , &fmt_li , &align_li } ;



Text o5 = { {
{"Installation",&fmt_h}
} , &fmt_li , &align_li } ;



Text o7 = { {
{"Preliminary"}
,{"considerations"}
} , &fmt_li , &align_li } ;



TextList o8 = { {{"1.",{
{ &o9 , null , {0,0} , {0,0} }
}}
,{"2.",{
{ &o11 , null , {0,0} , {0,0} }
}}
,{"3.",{
{ &o13 , null , {0,0} , {0,0} }
}}
} };

Text o9 = { {
{"Metaphysics of the programming",&fmt_h}
} , &fmt_li , &align_li } ;



Text o11 = { {
{"Taxonomy of classes",&fmt_h}
} , &fmt_li , &align_li } ;



Text o13 = { {
{"CCore general",&fmt_h}
} , &fmt_li , &align_li } ;





Text o16 = { {
{"Simples"}
} , &fmt_li , &align_li } ;



TextList o17 = { {{"1.",{
{ &o18 , null , {0,0} , {0,0} }
,{ &o19 , null , {0,0} , {0,0} }
}}
,{"2.",{
{ &o81 , null , {0,0} , {0,0} }
}}
,{"3.",{
{ &o83 , null , {0,0} , {0,0} }
}}
,{"4.",{
{ &o85 , null , {0,0} , {0,0} }
}}
,{"5.",{
{ &o87 , null , {0,0} , {0,0} }
}}
,{"6.",{
{ &o89 , null , {0,0} , {0,0} }
}}
,{"7.",{
{ &o91 , null , {0,0} , {0,0} }
}}
,{"8.",{
{ &o93 , null , {0,0} , {0,0} }
}}
,{"9.",{
{ &o95 , null , {0,0} , {0,0} }
}}
,{"10.",{
{ &o97 , null , {0,0} , {0,0} }
}}
,{"11.",{
{ &o99 , null , {0,0} , {0,0} }
}}
,{"12.",{
{ &o101 , null , {0,0} , {0,0} }
}}
,{"13.",{
{ &o103 , null , {0,0} , {0,0} }
}}
,{"14.",{
{ &o105 , null , {0,0} , {0,0} }
}}
,{"15.",{
{ &o107 , null , {0,0} , {0,0} }
}}
,{"16.",{
{ &o109 , null , {0,0} , {0,0} }
}}
,{"17.",{
{ &o111 , null , {0,0} , {0,0} }
}}
,{"18.",{
{ &o113 , null , {0,0} , {0,0} }
}}
,{"19.",{
{ &o115 , null , {0,0} , {0,0} }
}}
,{"20.",{
{ &o117 , null , {0,0} , {0,0} }
}}
,{"21.",{
{ &o119 , null , {0,0} , {0,0} }
}}
,{"22.",{
{ &o121 , null , {0,0} , {0,0} }
}}
,{"23.",{
{ &o123 , null , {0,0} , {0,0} }
}}
,{"24.",{
{ &o125 , null , {0,0} , {0,0} }
}}
,{"25.",{
{ &o127 , null , {0,0} , {0,0} }
}}
,{"26.",{
{ &o129 , null , {0,0} , {0,0} }
}}
,{"27.",{
{ &o131 , null , {0,0} , {0,0} }
}}
,{"28.",{
{ &o133 , null , {0,0} , {0,0} }
}}
,{"29.",{
{ &o135 , null , {0,0} , {0,0} }
}}
,{"30.",{
{ &o137 , null , {0,0} , {0,0} }
}}
,{"31.",{
{ &o139 , null , {0,0} , {0,0} }
}}
,{"32.",{
{ &o141 , null , {0,0} , {0,0} }
}}
,{"33.",{
{ &o143 , null , {0,0} , {0,0} }
}}
,{"34.",{
{ &o145 , null , {0,0} , {0,0} }
}}
,{"35.",{
{ &o147 , null , {0,0} , {0,0} }
}}
,{"36.",{
{ &o149 , null , {0,0} , {0,0} }
}}
,{"37.",{
{ &o151 , null , {0,0} , {0,0} }
}}
,{"38.",{
{ &o153 , null , {0,0} , {0,0} }
}}
,{"39.",{
{ &o155 , null , {0,0} , {0,0} }
}}
,{"40.",{
{ &o157 , null , {0,0} , {0,0} }
}}
,{"41.",{
{ &o159 , null , {0,0} , {0,0} }
}}
,{"42.",{
{ &o161 , null , {0,0} , {0,0} }
}}
,{"43.",{
{ &o163 , null , {0,0} , {0,0} }
}}
,{"44.",{
{ &o165 , null , {0,0} , {0,0} }
}}
,{"45.",{
{ &o167 , null , {0,0} , {0,0} }
}}
,{"46.",{
{ &o169 , null , {0,0} , {0,0} }
}}
} };

Text o18 = { {
{"Gadgets",&fmt_h}
} , &fmt_li , &align_li } ;



TextList o19 = { {{"1.",{
{ &o20 , null , {0,0} , {0,0} }
}}
,{"2.",{
{ &o22 , null , {0,0} , {0,0} }
}}
,{"3.",{
{ &o24 , null , {0,0} , {0,0} }
}}
,{"4.",{
{ &o26 , null , {0,0} , {0,0} }
}}
,{"5.",{
{ &o28 , null , {0,0} , {0,0} }
}}
,{"6.",{
{ &o30 , null , {0,0} , {0,0} }
}}
,{"7.",{
{ &o32 , null , {0,0} , {0,0} }
}}
,{"8.",{
{ &o34 , null , {0,0} , {0,0} }
}}
,{"9.",{
{ &o36 , null , {0,0} , {0,0} }
}}
,{"10.",{
{ &o38 , null , {0,0} , {0,0} }
}}
,{"11.",{
{ &o40 , null , {0,0} , {0,0} }
}}
,{"12.",{
{ &o42 , null , {0,0} , {0,0} }
}}
,{"13.",{
{ &o44 , null , {0,0} , {0,0} }
}}
,{"14.",{
{ &o46 , null , {0,0} , {0,0} }
}}
,{"15.",{
{ &o48 , null , {0,0} , {0,0} }
}}
,{"16.",{
{ &o50 , null , {0,0} , {0,0} }
}}
,{"17.",{
{ &o52 , null , {0,0} , {0,0} }
}}
,{"18.",{
{ &o54 , null , {0,0} , {0,0} }
}}
,{"19.",{
{ &o56 , null , {0,0} , {0,0} }
}}
,{"20.",{
{ &o58 , null , {0,0} , {0,0} }
}}
,{"21.",{
{ &o60 , null , {0,0} , {0,0} }
}}
,{"22.",{
{ &o62 , null , {0,0} , {0,0} }
}}
,{"23.",{
{ &o64 , null , {0,0} , {0,0} }
}}
,{"24.",{
{ &o66 , null , {0,0} , {0,0} }
}}
,{"25.",{
{ &o68 , null , {0,0} , {0,0} }
}}
,{"26.",{
{ &o70 , null , {0,0} , {0,0} }
}}
,{"27.",{
{ &o72 , null , {0,0} , {0,0} }
}}
,{"28.",{
{ &o74 , null , {0,0} , {0,0} }
}}
,{"29.",{
{ &o76 , null , {0,0} , {0,0} }
}}
,{"30.",{
{ &o78 , null , {0,0} , {0,0} }
}}
} };

Text o20 = { {
{"Meta",&fmt_h}
} , &fmt_li , &align_li } ;



Text o22 = { {
{"MetaList",&fmt_h}
} , &fmt_li , &align_li } ;



Text o24 = { {
{"Classification",&fmt_h}
} , &fmt_li , &align_li } ;



Text o26 = { {
{"NoCopy",&fmt_h}
} , &fmt_li , &align_li } ;



Text o28 = { {
{"Nothing",&fmt_h}
} , &fmt_li , &align_li } ;



Text o30 = { {
{"MSec",&fmt_h}
} , &fmt_li , &align_li } ;



Text o32 = { {
{"DefaultTimeout",&fmt_h}
} , &fmt_li , &align_li } ;



Text o34 = { {
{"ExceptionType",&fmt_h}
} , &fmt_li , &align_li } ;



Text o36 = { {
{"LockObject",&fmt_h}
} , &fmt_li , &align_li } ;



Text o38 = { {
{"Locked",&fmt_h}
} , &fmt_li , &align_li } ;



Text o40 = { {
{"NegBool",&fmt_h}
} , &fmt_li , &align_li } ;



Text o42 = { {
{"PosSub",&fmt_h}
} , &fmt_li , &align_li } ;



Text o44 = { {
{"Replace",&fmt_h}
} , &fmt_li , &align_li } ;



Text o46 = { {
{"Space",&fmt_h}
} , &fmt_li , &align_li } ;



Text o48 = { {
{"Len",&fmt_h}
} , &fmt_li , &align_li } ;



Text o50 = { {
{"Place",&fmt_h}
} , &fmt_li , &align_li } ;



Text o52 = { {
{"UtilFunc",&fmt_h}
} , &fmt_li , &align_li } ;



Text o54 = { {
{"UIntFunc",&fmt_h}
} , &fmt_li , &align_li } ;



Text o56 = { {
{"SIntFunc",&fmt_h}
} , &fmt_li , &align_li } ;



Text o58 = { {
{"UIntSat",&fmt_h}
} , &fmt_li , &align_li } ;



Text o60 = { {
{"Init",&fmt_h}
} , &fmt_li , &align_li } ;



Text o62 = { {
{"Handle",&fmt_h}
} , &fmt_li , &align_li } ;



Text o64 = { {
{"Function",&fmt_h}
} , &fmt_li , &align_li } ;



Text o66 = { {
{"PtrLen",&fmt_h}
} , &fmt_li , &align_li } ;



Text o68 = { {
{"PtrLenReverse",&fmt_h}
} , &fmt_li , &align_li } ;



Text o70 = { {
{"PtrStepLen",&fmt_h}
} , &fmt_li , &align_li } ;



Text o72 = { {
{"CreateAt",&fmt_h}
} , &fmt_li , &align_li } ;



Text o74 = { {
{"NoThrowFlags",&fmt_h}
} , &fmt_li , &align_li } ;



Text o76 = { {
{"OpAddHelper",&fmt_h}
} , &fmt_li , &align_li } ;



Text o78 = { {
{"ScopeGuard",&fmt_h}
} , &fmt_li , &align_li } ;





Text o81 = { {
{"Abort",&fmt_h}
} , &fmt_li , &align_li } ;



Text o83 = { {
{"Swap",&fmt_h}
} , &fmt_li , &align_li } ;



Text o85 = { {
{"Move",&fmt_h}
} , &fmt_li , &align_li } ;



Text o87 = { {
{"Cmp",&fmt_h}
} , &fmt_li , &align_li } ;



Text o89 = { {
{"FunctorType",&fmt_h}
} , &fmt_li , &align_li } ;



Text o91 = { {
{"Tuple",&fmt_h}
} , &fmt_li , &align_li } ;



Text o93 = { {
{"OwnPtr",&fmt_h}
} , &fmt_li , &align_li } ;



Text o95 = { {
{"RefPtr",&fmt_h}
} , &fmt_li , &align_li } ;



Text o97 = { {
{"Timer",&fmt_h}
} , &fmt_li , &align_li } ;



Text o99 = { {
{"TimeScope",&fmt_h}
} , &fmt_li , &align_li } ;



Text o101 = { {
{"TextLabel",&fmt_h}
} , &fmt_li , &align_li } ;



Text o103 = { {
{"ScanBit",&fmt_h}
} , &fmt_li , &align_li } ;



Text o105 = { {
{"UIntSplit",&fmt_h}
} , &fmt_li , &align_li } ;



Text o107 = { {
{"MemAllocGuard",&fmt_h}
} , &fmt_li , &align_li } ;



Text o109 = { {
{"TlsSlot",&fmt_h}
} , &fmt_li , &align_li } ;



Text o111 = { {
{"PrintSet",&fmt_h}
} , &fmt_li , &align_li } ;



Text o113 = { {
{"PrintTitle",&fmt_h}
} , &fmt_li , &align_li } ;



Text o115 = { {
{"PrintTime",&fmt_h}
} , &fmt_li , &align_li } ;



Text o117 = { {
{"PrintError",&fmt_h}
} , &fmt_li , &align_li } ;



Text o119 = { {
{"PrintAbort",&fmt_h}
} , &fmt_li , &align_li } ;



Text o121 = { {
{"PrintBits",&fmt_h}
} , &fmt_li , &align_li } ;



Text o123 = { {
{"Counters",&fmt_h}
} , &fmt_li , &align_li } ;



Text o125 = { {
{"Fifo",&fmt_h}
} , &fmt_li , &align_li } ;



Text o127 = { {
{"SafeBuf",&fmt_h}
} , &fmt_li , &align_li } ;



Text o129 = { {
{"Crc",&fmt_h}
} , &fmt_li , &align_li } ;



Text o131 = { {
{"StrKey",&fmt_h}
} , &fmt_li , &align_li } ;



Text o133 = { {
{"Utf8",&fmt_h}
} , &fmt_li , &align_li } ;



Text o135 = { {
{"Symbol",&fmt_h}
} , &fmt_li , &align_li } ;



Text o137 = { {
{"SymCount",&fmt_h}
} , &fmt_li , &align_li } ;



Text o139 = { {
{"FeedBuf",&fmt_h}
} , &fmt_li , &align_li } ;



Text o141 = { {
{"PrintStem",&fmt_h}
} , &fmt_li , &align_li } ;



Text o143 = { {
{"CapString",&fmt_h}
} , &fmt_li , &align_li } ;



Text o145 = { {
{"MakeString",&fmt_h}
} , &fmt_li , &align_li } ;



Text o147 = { {
{"InstanceLock",&fmt_h}
} , &fmt_li , &align_li } ;



Text o149 = { {
{"BlockFifo",&fmt_h}
} , &fmt_li , &align_li } ;



Text o151 = { {
{"TypeSwitch",&fmt_h}
} , &fmt_li , &align_li } ;



Text o153 = { {
{"NewDelete",&fmt_h}
} , &fmt_li , &align_li } ;



Text o155 = { {
{"DynObject",&fmt_h}
} , &fmt_li , &align_li } ;



Text o157 = { {
{"AnyPtr",&fmt_h}
} , &fmt_li , &align_li } ;



Text o159 = { {
{"StartStop",&fmt_h}
} , &fmt_li , &align_li } ;



Text o161 = { {
{"RefObjectBase",&fmt_h}
} , &fmt_li , &align_li } ;



Text o163 = { {
{"DestroyGuard",&fmt_h}
} , &fmt_li , &align_li } ;



Text o165 = { {
{"RangeDel",&fmt_h}
} , &fmt_li , &align_li } ;



Text o167 = { {
{"Pow",&fmt_h}
} , &fmt_li , &align_li } ;



Text o169 = { {
{"PrintRatio",&fmt_h}
} , &fmt_li , &align_li } ;





Text o172 = { {
{"Fundamentals"}
} , &fmt_li , &align_li } ;



TextList o173 = { {{"1.",{
{ &o174 , null , {0,0} , {0,0} }
,{ &o175 , null , {0,0} , {0,0} }
}}
,{"2.",{
{ &o199 , null , {0,0} , {0,0} }
}}
,{"3.",{
{ &o201 , null , {0,0} , {0,0} }
}}
,{"4.",{
{ &o203 , null , {0,0} , {0,0} }
}}
,{"5.",{
{ &o205 , null , {0,0} , {0,0} }
}}
,{"6.",{
{ &o207 , null , {0,0} , {0,0} }
}}
,{"7.",{
{ &o209 , null , {0,0} , {0,0} }
,{ &o210 , null , {0,0} , {0,0} }
}}
,{"8.",{
{ &o216 , null , {0,0} , {0,0} }
}}
,{"9.",{
{ &o218 , null , {0,0} , {0,0} }
}}
,{"10.",{
{ &o220 , null , {0,0} , {0,0} }
}}
,{"11.",{
{ &o222 , null , {0,0} , {0,0} }
}}
,{"12.",{
{ &o224 , null , {0,0} , {0,0} }
}}
,{"13.",{
{ &o226 , null , {0,0} , {0,0} }
}}
,{"14.",{
{ &o228 , null , {0,0} , {0,0} }
}}
,{"15.",{
{ &o230 , null , {0,0} , {0,0} }
}}
,{"16.",{
{ &o232 , null , {0,0} , {0,0} }
}}
,{"17.",{
{ &o234 , null , {0,0} , {0,0} }
,{ &o235 , null , {0,0} , {0,0} }
}}
,{"18.",{
{ &o245 , null , {0,0} , {0,0} }
}}
,{"19.",{
{ &o247 , null , {0,0} , {0,0} }
}}
,{"20.",{
{ &o249 , null , {0,0} , {0,0} }
}}
,{"21.",{
{ &o251 , null , {0,0} , {0,0} }
}}
,{"22.",{
{ &o253 , null , {0,0} , {0,0} }
}}
,{"23.",{
{ &o255 , null , {0,0} , {0,0} }
,{ &o256 , null , {0,0} , {0,0} }
}}
,{"24.",{
{ &o262 , null , {0,0} , {0,0} }
}}
,{"25.",{
{ &o264 , null , {0,0} , {0,0} }
}}
,{"26.",{
{ &o266 , null , {0,0} , {0,0} }
}}
,{"27.",{
{ &o268 , null , {0,0} , {0,0} }
}}
,{"28.",{
{ &o270 , null , {0,0} , {0,0} }
}}
,{"29.",{
{ &o272 , null , {0,0} , {0,0} }
}}
,{"30.",{
{ &o274 , null , {0,0} , {0,0} }
}}
,{"31.",{
{ &o276 , null , {0,0} , {0,0} }
}}
,{"32.",{
{ &o278 , null , {0,0} , {0,0} }
}}
,{"33.",{
{ &o280 , null , {0,0} , {0,0} }
}}
,{"34.",{
{ &o282 , null , {0,0} , {0,0} }
}}
,{"35.",{
{ &o284 , null , {0,0} , {0,0} }
}}
,{"36.",{
{ &o286 , null , {0,0} , {0,0} }
}}
,{"37.",{
{ &o288 , null , {0,0} , {0,0} }
}}
,{"38.",{
{ &o290 , null , {0,0} , {0,0} }
}}
,{"39.",{
{ &o292 , null , {0,0} , {0,0} }
}}
,{"40.",{
{ &o294 , null , {0,0} , {0,0} }
}}
} };

Text o174 = { {
{"Algon",&fmt_h}
} , &fmt_li , &align_li } ;



TextList o175 = { {{"1.",{
{ &o176 , null , {0,0} , {0,0} }
}}
,{"2.",{
{ &o178 , null , {0,0} , {0,0} }
}}
,{"3.",{
{ &o180 , null , {0,0} , {0,0} }
}}
,{"4.",{
{ &o182 , null , {0,0} , {0,0} }
}}
,{"5.",{
{ &o184 , null , {0,0} , {0,0} }
}}
,{"6.",{
{ &o186 , null , {0,0} , {0,0} }
}}
,{"7.",{
{ &o188 , null , {0,0} , {0,0} }
}}
,{"8.",{
{ &o190 , null , {0,0} , {0,0} }
}}
,{"9.",{
{ &o192 , null , {0,0} , {0,0} }
}}
,{"10.",{
{ &o194 , null , {0,0} , {0,0} }
}}
,{"11.",{
{ &o196 , null , {0,0} , {0,0} }
}}
} };

Text o176 = { {
{"ApplyToRange",&fmt_h}
} , &fmt_li , &align_li } ;



Text o178 = { {
{"ApplyToList",&fmt_h}
} , &fmt_li , &align_li } ;



Text o180 = { {
{"BaseRangeAlgo",&fmt_h}
} , &fmt_li , &align_li } ;



Text o182 = { {
{"BinarySearch",&fmt_h}
} , &fmt_li , &align_li } ;



Text o184 = { {
{"BestSearch",&fmt_h}
} , &fmt_li , &align_li } ;



Text o186 = { {
{"SimpleRotate",&fmt_h}
} , &fmt_li , &align_li } ;



Text o188 = { {
{"EuclidRotate",&fmt_h}
} , &fmt_li , &align_li } ;



Text o190 = { {
{"CommonIntAlgo",&fmt_h}
} , &fmt_li , &align_li } ;



Text o192 = { {
{"GCDConst",&fmt_h}
} , &fmt_li , &align_li } ;



Text o194 = { {
{"SortUnique",&fmt_h}
} , &fmt_li , &align_li } ;



Text o196 = { {
{"Partition",&fmt_h}
} , &fmt_li , &align_li } ;





Text o199 = { {
{"PlanInit",&fmt_h}
} , &fmt_li , &align_li } ;



Text o201 = { {
{"Printing",&fmt_h}
} , &fmt_li , &align_li } ;



Text o203 = { {
{"Scanning",&fmt_h}
} , &fmt_li , &align_li } ;



Text o205 = { {
{"Exceptions",&fmt_h}
} , &fmt_li , &align_li } ;



Text o207 = { {
{"Scope",&fmt_h}
} , &fmt_li , &align_li } ;



Text o209 = { {
{"Memory management",&fmt_h}
} , &fmt_li , &align_li } ;



TextList o210 = { {{"1.",{
{ &o211 , null , {0,0} , {0,0} }
}}
,{"2.",{
{ &o213 , null , {0,0} , {0,0} }
}}
} };

Text o211 = { {
{"RadixHeap",&fmt_h}
} , &fmt_li , &align_li } ;



Text o213 = { {
{"HeapEngine",&fmt_h}
} , &fmt_li , &align_li } ;





Text o216 = { {
{"Element pool",&fmt_h}
} , &fmt_li , &align_li } ;



Text o218 = { {
{"Arrays",&fmt_h}
} , &fmt_li , &align_li } ;



Text o220 = { {
{"Lists",&fmt_h}
} , &fmt_li , &align_li } ;



Text o222 = { {
{"Trees",&fmt_h}
} , &fmt_li , &align_li } ;



Text o224 = { {
{"Strings",&fmt_h}
} , &fmt_li , &align_li } ;



Text o226 = { {
{"Working thread pool",&fmt_h}
} , &fmt_li , &align_li } ;



Text o228 = { {
{"Sort",&fmt_h}
} , &fmt_li , &align_li } ;



Text o230 = { {
{"Serialization (SaveLoad)",&fmt_h}
} , &fmt_li , &align_li } ;



Text o232 = { {
{"Random",&fmt_h}
} , &fmt_li , &align_li } ;



Text o234 = { {
{"Text"}
,{"and"}
,{"characters"}
} , &fmt_li , &align_li } ;



TextList o235 = { {{"1.",{
{ &o236 , null , {0,0} , {0,0} }
}}
,{"2.",{
{ &o238 , null , {0,0} , {0,0} }
}}
,{"3.",{
{ &o240 , null , {0,0} , {0,0} }
}}
,{"4.",{
{ &o242 , null , {0,0} , {0,0} }
}}
} };

Text o236 = { {
{"Simple string parsing",&fmt_h}
} , &fmt_li , &align_li } ;



Text o238 = { {
{"Basic character properties",&fmt_h}
} , &fmt_li , &align_li } ;



Text o240 = { {
{"Text tools",&fmt_h}
} , &fmt_li , &align_li } ;



Text o242 = { {
{"Character utilities",&fmt_h}
} , &fmt_li , &align_li } ;





Text o245 = { {
{"Files",&fmt_h}
} , &fmt_li , &align_li } ;



Text o247 = { {
{"Paths",&fmt_h}
} , &fmt_li , &align_li } ;



Text o249 = { {
{"Unid",&fmt_h}
} , &fmt_li , &align_li } ;



Text o251 = { {
{"TypeNumber",&fmt_h}
} , &fmt_li , &align_li } ;



Text o253 = { {
{"InterfaceHost",&fmt_h}
} , &fmt_li , &align_li } ;



Text o255 = { {
{"Object hosting",&fmt_h}
} , &fmt_li , &align_li } ;



TextList o256 = { {{"1.",{
{ &o257 , null , {0,0} , {0,0} }
}}
,{"2.",{
{ &o259 , null , {0,0} , {0,0} }
}}
} };

Text o257 = { {
{"SingleHost",&fmt_h}
} , &fmt_li , &align_li } ;



Text o259 = { {
{"ObjectHost",&fmt_h}
} , &fmt_li , &align_li } ;





Text o262 = { {
{"Node allocators",&fmt_h}
} , &fmt_li , &align_li } ;



Text o264 = { {
{"Container lists",&fmt_h}
} , &fmt_li , &align_li } ;



Text o266 = { {
{"Tree maps",&fmt_h}
} , &fmt_li , &align_li } ;



Text o268 = { {
{"Compact node allocator",&fmt_h}
} , &fmt_li , &align_li } ;



Text o270 = { {
{"Compact lists",&fmt_h}
} , &fmt_li , &align_li } ;



Text o272 = { {
{"Compact maps",&fmt_h}
} , &fmt_li , &align_li } ;



Text o274 = { {
{"Unsigned multiplication and division",&fmt_h}
} , &fmt_li , &align_li } ;



Text o276 = { {
{"AutoGlobal",&fmt_h}
} , &fmt_li , &align_li } ;



Text o278 = { {
{"MakeFileName",&fmt_h}
} , &fmt_li , &align_li } ;



Text o280 = { {
{"StrMap",&fmt_h}
} , &fmt_li , &align_li } ;



Text o282 = { {
{"AttachmentHost",&fmt_h}
} , &fmt_li , &align_li } ;



Text o284 = { {
{"Signals",&fmt_h}
} , &fmt_li , &align_li } ;



Text o286 = { {
{"Optional",&fmt_h}
} , &fmt_li , &align_li } ;



Text o288 = { {
{"Defer calls",&fmt_h}
} , &fmt_li , &align_li } ;



Text o290 = { {
{"MultiSignals",&fmt_h}
} , &fmt_li , &align_li } ;



Text o292 = { {
{"Object Domain",&fmt_h}
} , &fmt_li , &align_li } ;



Text o294 = { {
{"StepEval",&fmt_h}
} , &fmt_li , &align_li } ;





Text o297 = { {
{"Applied"}
} , &fmt_li , &align_li } ;



TextList o298 = { {{"1.",{
{ &o299 , null , {0,0} , {0,0} }
}}
,{"2.",{
{ &o301 , null , {0,0} , {0,0} }
}}
,{"3.",{
{ &o303 , null , {0,0} , {0,0} }
}}
,{"4.",{
{ &o305 , null , {0,0} , {0,0} }
}}
,{"5.",{
{ &o307 , null , {0,0} , {0,0} }
,{ &o308 , null , {0,0} , {0,0} }
}}
,{"6.",{
{ &o316 , null , {0,0} , {0,0} }
}}
,{"7.",{
{ &o318 , null , {0,0} , {0,0} }
}}
} };

Text o299 = { {
{"ToMemBase",&fmt_h}
} , &fmt_li , &align_li } ;



Text o301 = { {
{"FileName",&fmt_h}
} , &fmt_li , &align_li } ;



Text o303 = { {
{"FileNameMatch",&fmt_h}
} , &fmt_li , &align_li } ;



Text o305 = { {
{"StrToChar",&fmt_h}
} , &fmt_li , &align_li } ;



Text o307 = { {
{"Async"}
,{"Files"}
} , &fmt_li , &align_li } ;



TextList o308 = { {{"1.",{
{ &o309 , null , {0,0} , {0,0} }
}}
,{"2.",{
{ &o311 , null , {0,0} , {0,0} }
}}
,{"3.",{
{ &o313 , null , {0,0} , {0,0} }
}}
} };

Text o309 = { {
{"Interface",&fmt_h}
} , &fmt_li , &align_li } ;



Text o311 = { {
{"Clients",&fmt_h}
} , &fmt_li , &align_li } ;



Text o313 = { {
{"Binary",&fmt_h}
} , &fmt_li , &align_li } ;





Text o316 = { {
{"ELF format parser",&fmt_h}
} , &fmt_li , &align_li } ;



Text o318 = { {
{"LangDataMap",&fmt_h}
} , &fmt_li , &align_li } ;





Text o321 = { {
{"Tasks"}
,{"and"}
,{"synchronization"}
} , &fmt_li , &align_li } ;



TextList o322 = { {{"1.",{
{ &o323 , null , {0,0} , {0,0} }
}}
,{"2.",{
{ &o325 , null , {0,0} , {0,0} }
}}
,{"3.",{
{ &o327 , null , {0,0} , {0,0} }
}}
,{"4.",{
{ &o329 , null , {0,0} , {0,0} }
}}
,{"5.",{
{ &o331 , null , {0,0} , {0,0} }
}}
,{"6.",{
{ &o333 , null , {0,0} , {0,0} }
}}
,{"7.",{
{ &o335 , null , {0,0} , {0,0} }
}}
,{"8.",{
{ &o337 , null , {0,0} , {0,0} }
}}
,{"9.",{
{ &o339 , null , {0,0} , {0,0} }
}}
,{"10.",{
{ &o341 , null , {0,0} , {0,0} }
}}
,{"11.",{
{ &o343 , null , {0,0} , {0,0} }
}}
,{"12.",{
{ &o345 , null , {0,0} , {0,0} }
}}
,{"13.",{
{ &o347 , null , {0,0} , {0,0} }
}}
,{"14.",{
{ &o349 , null , {0,0} , {0,0} }
,{ &o350 , null , {0,0} , {0,0} }
}}
,{"15.",{
{ &o354 , null , {0,0} , {0,0} }
,{ &o355 , null , {0,0} , {0,0} }
}}
,{"16.",{
{ &o365 , null , {0,0} , {0,0} }
}}
,{"17.",{
{ &o367 , null , {0,0} , {0,0} }
}}
,{"18.",{
{ &o369 , null , {0,0} , {0,0} }
}}
} };

Text o323 = { {
{"Tasks",&fmt_h}
} , &fmt_li , &align_li } ;



Text o325 = { {
{"FuncTask",&fmt_h}
} , &fmt_li , &align_li } ;



Text o327 = { {
{"Atomic",&fmt_h}
} , &fmt_li , &align_li } ;



Text o329 = { {
{"Synchronization objects",&fmt_h}
} , &fmt_li , &align_li } ;



Text o331 = { {
{"NoMutex",&fmt_h}
} , &fmt_li , &align_li } ;



Text o333 = { {
{"Mutex",&fmt_h}
} , &fmt_li , &align_li } ;



Text o335 = { {
{"FastMutex",&fmt_h}
} , &fmt_li , &align_li } ;



Text o337 = { {
{"Sem",&fmt_h}
} , &fmt_li , &align_li } ;



Text o339 = { {
{"Event",&fmt_h}
} , &fmt_li , &align_li } ;



Text o341 = { {
{"MultiSem",&fmt_h}
} , &fmt_li , &align_li } ;



Text o343 = { {
{"MultiEvent",&fmt_h}
} , &fmt_li , &align_li } ;



Text o345 = { {
{"AntiSem",&fmt_h}
} , &fmt_li , &align_li } ;



Text o347 = { {
{"ResSem",&fmt_h}
} , &fmt_li , &align_li } ;



Text o349 = { {
{"HCore-specific"}
} , &fmt_li , &align_li } ;



TextList o350 = { {{"1.",{
{ &o351 , null , {0,0} , {0,0} }
}}
} };

Text o351 = { {
{"SlowSem",&fmt_h}
} , &fmt_li , &align_li } ;





Text o354 = { {
{"XCore-specific"}
} , &fmt_li , &align_li } ;



TextList o355 = { {{"1.",{
{ &o356 , null , {0,0} , {0,0} }
}}
,{"2.",{
{ &o358 , null , {0,0} , {0,0} }
}}
,{"3.",{
{ &o360 , null , {0,0} , {0,0} }
}}
,{"4.",{
{ &o362 , null , {0,0} , {0,0} }
}}
} };

Text o356 = { {
{"TickCount and TickJob",&fmt_h}
} , &fmt_li , &align_li } ;



Text o358 = { {
{"Ticker and TimedTrigger",&fmt_h}
} , &fmt_li , &align_li } ;



Text o360 = { {
{"ForcedTimeout",&fmt_h}
} , &fmt_li , &align_li } ;



Text o362 = { {
{"TaskMonitor",&fmt_h}
} , &fmt_li , &align_li } ;





Text o365 = { {
{"PerTask",&fmt_h}
} , &fmt_li , &align_li } ;



Text o367 = { {
{"TaskHeap",&fmt_h}
} , &fmt_li , &align_li } ;



Text o369 = { {
{"TaskMemStack",&fmt_h}
} , &fmt_li , &align_li } ;





Text o372 = { {
{"Console input",&fmt_h}
} , &fmt_li , &align_li } ;



TextList o373 = { {{"1.",{
{ &o374 , null , {0,0} , {0,0} }
}}
,{"2.",{
{ &o376 , null , {0,0} , {0,0} }
}}
,{"3.",{
{ &o378 , null , {0,0} , {0,0} }
}}
} };

Text o374 = { {
{"InputUtils",&fmt_h}
} , &fmt_li , &align_li } ;



Text o376 = { {
{"LineInput",&fmt_h}
} , &fmt_li , &align_li } ;



Text o378 = { {
{"CmdInput",&fmt_h}
} , &fmt_li , &align_li } ;





Text o381 = { {
{"Logging"}
} , &fmt_li , &align_li } ;



TextList o382 = { {{"1.",{
{ &o383 , null , {0,0} , {0,0} }
}}
,{"2.",{
{ &o385 , null , {0,0} , {0,0} }
}}
} };

Text o383 = { {
{"General",&fmt_h}
} , &fmt_li , &align_li } ;



Text o385 = { {
{"(XCore) SysLog",&fmt_h}
} , &fmt_li , &align_li } ;





Text o388 = { {
{"Event"}
,{"recording"}
} , &fmt_li , &align_li } ;



TextList o389 = { {{"1.",{
{ &o390 , null , {0,0} , {0,0} }
}}
,{"2.",{
{ &o392 , null , {0,0} , {0,0} }
}}
,{"3.",{
{ &o394 , null , {0,0} , {0,0} }
}}
,{"4.",{
{ &o396 , null , {0,0} , {0,0} }
}}
,{"5.",{
{ &o398 , null , {0,0} , {0,0} }
}}
} };

Text o390 = { {
{"General",&fmt_h}
} , &fmt_li , &align_li } ;



Text o392 = { {
{"(XCore) Task events",&fmt_h}
} , &fmt_li , &align_li } ;



Text o394 = { {
{"PTP CilentDevice events",&fmt_h}
} , &fmt_li , &align_li } ;



Text o396 = { {
{"PTP ServerDevice events",&fmt_h}
} , &fmt_li , &align_li } ;



Text o398 = { {
{"NanoIPDevice events",&fmt_h}
} , &fmt_li , &align_li } ;





Text o401 = { {
{"HCore"}
,{"files"}
,{"and"}
,{"file"}
,{"system"}
} , &fmt_li , &align_li } ;



TextList o402 = { {{"1.",{
{ &o403 , null , {0,0} , {0,0} }
}}
,{"2.",{
{ &o405 , null , {0,0} , {0,0} }
}}
,{"3.",{
{ &o407 , null , {0,0} , {0,0} }
}}
,{"4.",{
{ &o409 , null , {0,0} , {0,0} }
}}
,{"5.",{
{ &o411 , null , {0,0} , {0,0} }
}}
,{"6.",{
{ &o413 , null , {0,0} , {0,0} }
}}
,{"7.",{
{ &o415 , null , {0,0} , {0,0} }
}}
} };

Text o403 = { {
{"RawFileToRead",&fmt_h}
} , &fmt_li , &align_li } ;



Text o405 = { {
{"FileToMem",&fmt_h}
} , &fmt_li , &align_li } ;



Text o407 = { {
{"AsyncFileDevice",&fmt_h}
} , &fmt_li , &align_li } ;



Text o409 = { {
{"FileSystem",&fmt_h}
} , &fmt_li , &align_li } ;



Text o411 = { {
{"DirTreeRun",&fmt_h}
} , &fmt_li , &align_li } ;



Text o413 = { {
{"Binary",&fmt_h}
} , &fmt_li , &align_li } ;



Text o415 = { {
{"LaunchPath",&fmt_h}
} , &fmt_li , &align_li } ;





Text o418 = { {
{"XCore"}
,{"files"}
} , &fmt_li , &align_li } ;



TextList o419 = { {{"1.",{
{ &o420 , null , {0,0} , {0,0} }
}}
,{"2.",{
{ &o422 , null , {0,0} , {0,0} }
}}
,{"3.",{
{ &o424 , null , {0,0} , {0,0} }
}}
,{"4.",{
{ &o426 , null , {0,0} , {0,0} }
}}
} };

Text o420 = { {
{"DefaultFileDevice",&fmt_h}
} , &fmt_li , &align_li } ;



Text o422 = { {
{"RawFileToRead",&fmt_h}
} , &fmt_li , &align_li } ;



Text o424 = { {
{"FileToMem",&fmt_h}
} , &fmt_li , &align_li } ;



Text o426 = { {
{"Binary",&fmt_h}
} , &fmt_li , &align_li } ;





Text o429 = { {
{"Printing devices",&fmt_h}
} , &fmt_li , &align_li } ;



Text o431 = { {
{"Scanning devices",&fmt_h}
} , &fmt_li , &align_li } ;



Text o433 = { {
{"NanoPackets",&fmt_h}
} , &fmt_li , &align_li } ;



Text o435 = { {
{"XCore console",&fmt_h}
} , &fmt_li , &align_li } ;



Text o437 = { {
{"Packets"}
} , &fmt_li , &align_li } ;



TextList o438 = { {{"1.",{
{ &o439 , null , {0,0} , {0,0} }
}}
,{"2.",{
{ &o441 , null , {0,0} , {0,0} }
}}
,{"3.",{
{ &o443 , null , {0,0} , {0,0} }
}}
,{"4.",{
{ &o445 , null , {0,0} , {0,0} }
}}
,{"5.",{
{ &o447 , null , {0,0} , {0,0} }
}}
} };

Text o439 = { {
{"Packet",&fmt_h}
} , &fmt_li , &align_li } ;



Text o441 = { {
{"PacketPool",&fmt_h}
} , &fmt_li , &align_li } ;



Text o443 = { {
{"PacketSet",&fmt_h}
} , &fmt_li , &align_li } ;



Text o445 = { {
{"CancelPacketList",&fmt_h}
} , &fmt_li , &align_li } ;



Text o447 = { {
{"(XCore) CompletePacket",&fmt_h}
} , &fmt_li , &align_li } ;





Text o450 = { {
{"Math",&fmt_h}
} , &fmt_li , &align_li } ;



TextList o451 = { {{"1.",{
{ &o452 , null , {0,0} , {0,0} }
}}
,{"2.",{
{ &o454 , null , {0,0} , {0,0} }
}}
,{"3.",{
{ &o456 , null , {0,0} , {0,0} }
}}
,{"4.",{
{ &o458 , null , {0,0} , {0,0} }
}}
,{"5.",{
{ &o460 , null , {0,0} , {0,0} }
}}
,{"6.",{
{ &o462 , null , {0,0} , {0,0} }
}}
,{"7.",{
{ &o464 , null , {0,0} , {0,0} }
}}
,{"8.",{
{ &o466 , null , {0,0} , {0,0} }
}}
} };

Text o452 = { {
{"Integer",&fmt_h}
} , &fmt_li , &align_li } ;



Text o454 = { {
{"IntegerSlowAlgo",&fmt_h}
} , &fmt_li , &align_li } ;



Text o456 = { {
{"IntegerFastAlgo",&fmt_h}
} , &fmt_li , &align_li } ;



Text o458 = { {
{"IntegerOctetBuilder",&fmt_h}
} , &fmt_li , &align_li } ;



Text o460 = { {
{"SmallPrimes",&fmt_h}
} , &fmt_li , &align_li } ;



Text o462 = { {
{"ModEngine",&fmt_h}
} , &fmt_li , &align_li } ;



Text o464 = { {
{"NoPrimeTest",&fmt_h}
} , &fmt_li , &align_li } ;



Text o466 = { {
{"APRTest",&fmt_h}
} , &fmt_li , &align_li } ;





Text o469 = { {
{"Crypton",&fmt_h}
} , &fmt_li , &align_li } ;



TextList o470 = { {{"1.",{
{ &o471 , null , {0,0} , {0,0} }
}}
,{"2.",{
{ &o473 , null , {0,0} , {0,0} }
}}
,{"3.",{
{ &o475 , null , {0,0} , {0,0} }
}}
,{"4.",{
{ &o477 , null , {0,0} , {0,0} }
}}
,{"5.",{
{ &o479 , null , {0,0} , {0,0} }
}}
,{"6.",{
{ &o481 , null , {0,0} , {0,0} }
}}
,{"7.",{
{ &o483 , null , {0,0} , {0,0} }
}}
,{"8.",{
{ &o485 , null , {0,0} , {0,0} }
}}
} };

Text o471 = { {
{"BlockCipher",&fmt_h}
} , &fmt_li , &align_li } ;



Text o473 = { {
{"AES",&fmt_h}
} , &fmt_li , &align_li } ;



Text o475 = { {
{"HashFunction",&fmt_h}
} , &fmt_li , &align_li } ;



Text o477 = { {
{"SHA",&fmt_h}
} , &fmt_li , &align_li } ;



Text o479 = { {
{"MD5",&fmt_h}
} , &fmt_li , &align_li } ;



Text o481 = { {
{"Rot",&fmt_h}
} , &fmt_li , &align_li } ;



Text o483 = { {
{"Forget",&fmt_h}
} , &fmt_li , &align_li } ;



Text o485 = { {
{"DHExp",&fmt_h}
} , &fmt_li , &align_li } ;





Text o488 = { {
{"DDL"}
} , &fmt_li , &align_li } ;



TextList o489 = { {{"1.",{
{ &o490 , null , {0,0} , {0,0} }
}}
,{"2.",{
{ &o492 , null , {0,0} , {0,0} }
}}
} };

Text o490 = { {
{"DDL language (v.2)",&fmt_h}
} , &fmt_li , &align_li } ;



Text o492 = { {
{"DDL Engine",&fmt_h}
} , &fmt_li , &align_li } ;





Text o495 = { {
{"Net"}
} , &fmt_li , &align_li } ;



TextList o496 = { {{"1.",{
{ &o497 , null , {0,0} , {0,0} }
}}
,{"2.",{
{ &o499 , null , {0,0} , {0,0} }
}}
,{"3.",{
{ &o501 , null , {0,0} , {0,0} }
}}
,{"4.",{
{ &o503 , null , {0,0} , {0,0} }
}}
,{"5.",{
{ &o505 , null , {0,0} , {0,0} }
}}
,{"6.",{
{ &o507 , null , {0,0} , {0,0} }
}}
,{"7.",{
{ &o509 , null , {0,0} , {0,0} }
}}
,{"8.",{
{ &o511 , null , {0,0} , {0,0} }
}}
,{"9.",{
{ &o513 , null , {0,0} , {0,0} }
}}
,{"10.",{
{ &o515 , null , {0,0} , {0,0} }
}}
,{"11.",{
{ &o517 , null , {0,0} , {0,0} }
}}
,{"12.",{
{ &o519 , null , {0,0} , {0,0} }
}}
,{"13.",{
{ &o521 , null , {0,0} , {0,0} }
}}
,{"14.",{
{ &o523 , null , {0,0} , {0,0} }
}}
,{"15.",{
{ &o525 , null , {0,0} , {0,0} }
}}
,{"16.",{
{ &o527 , null , {0,0} , {0,0} }
}}
,{"17.",{
{ &o529 , null , {0,0} , {0,0} }
}}
,{"18.",{
{ &o531 , null , {0,0} , {0,0} }
}}
,{"19.",{
{ &o533 , null , {0,0} , {0,0} }
}}
,{"20.",{
{ &o535 , null , {0,0} , {0,0} }
}}
,{"21.",{
{ &o537 , null , {0,0} , {0,0} }
}}
,{"22.",{
{ &o539 , null , {0,0} , {0,0} }
}}
} };

Text o497 = { {
{"Packet endpoint",&fmt_h}
} , &fmt_li , &align_li } ;



Text o499 = { {
{"NetBase",&fmt_h}
} , &fmt_li , &align_li } ;



Text o501 = { {
{"UDPoint",&fmt_h}
} , &fmt_li , &align_li } ;



Text o503 = { {
{"CheckedData",&fmt_h}
} , &fmt_li , &align_li } ;



Text o505 = { {
{"EchoDevice",&fmt_h}
} , &fmt_li , &align_li } ;



Text o507 = { {
{"SingleEchoDevice",&fmt_h}
} , &fmt_li , &align_li } ;



Text o509 = { {
{"Bridge",&fmt_h}
} , &fmt_li , &align_li } ;



Text o511 = { {
{"SingleBridge",&fmt_h}
} , &fmt_li , &align_li } ;



Text o513 = { {
{"NetFork",&fmt_h}
} , &fmt_li , &align_li } ;



Text o515 = { {
{"(HCore) UDPDevice",&fmt_h}
} , &fmt_li , &align_li } ;



Text o517 = { {
{"(HCore) AsyncUDPDevice",&fmt_h}
} , &fmt_li , &align_li } ;



Text o519 = { {
{"PTP",&fmt_h}
} , &fmt_li , &align_li } ;



Text o521 = { {
{"PTP Service",&fmt_h}
} , &fmt_li , &align_li } ;



Text o523 = { {
{"PTP Support",&fmt_h}
} , &fmt_li , &align_li } ;



Text o525 = { {
{"PTP echo test",&fmt_h}
} , &fmt_li , &align_li } ;



Text o527 = { {
{"PTP Console",&fmt_h}
} , &fmt_li , &align_li } ;



Text o529 = { {
{"PTP Boot",&fmt_h}
} , &fmt_li , &align_li } ;



Text o531 = { {
{"HFS",&fmt_h}
} , &fmt_li , &align_li } ;



Text o533 = { {
{"PSec",&fmt_h}
} , &fmt_li , &align_li } ;



Text o535 = { {
{"PKE",&fmt_h}
} , &fmt_li , &align_li } ;



Text o537 = { {
{"EthDevice",&fmt_h}
} , &fmt_li , &align_li } ;



Text o539 = { {
{"NanoIPDevice",&fmt_h}
} , &fmt_li , &align_li } ;





Text o542 = { {
{"Video"}
} , &fmt_li , &align_li } ;



Text o544 = { {
{"Desktop"}
} , &fmt_li , &align_li } ;



Text o546 = { {
{"HCore targets",&fmt_h}
} , &fmt_li , &align_li } ;



TextList o547 = { {{"1.",{
{ &o548 , null , {0,0} , {0,0} }
}}
,{"2.",{
{ &o550 , null , {0,0} , {0,0} }
}}
,{"3.",{
{ &o552 , null , {0,0} , {0,0} }
}}
,{"4.",{
{ &o554 , null , {0,0} , {0,0} }
}}
,{"5.",{
{ &o556 , null , {0,0} , {0,0} }
}}
,{"6.",{
{ &o558 , null , {0,0} , {0,0} }
}}
,{"7.",{
{ &o560 , null , {0,0} , {0,0} }
}}
,{"8.",{
{ &o562 , null , {0,0} , {0,0} }
}}
,{"9.",{
{ &o564 , null , {0,0} , {0,0} }
}}
,{"10.",{
{ &o566 , null , {0,0} , {0,0} }
}}
,{"11.",{
{ &o568 , null , {0,0} , {0,0} }
}}
,{"12.",{
{ &o570 , null , {0,0} , {0,0} }
}}
,{"13.",{
{ &o572 , null , {0,0} , {0,0} }
}}
,{"14.",{
{ &o574 , null , {0,0} , {0,0} }
}}
,{"15.",{
{ &o576 , null , {0,0} , {0,0} }
}}
,{"16.",{
{ &o578 , null , {0,0} , {0,0} }
}}
,{"17.",{
{ &o580 , null , {0,0} , {0,0} }
}}
,{"18.",{
{ &o582 , null , {0,0} , {0,0} }
}}
,{"19.",{
{ &o584 , null , {0,0} , {0,0} }
}}
} };

Text o548 = { {
{"PlatformBase",&fmt_h}
} , &fmt_li , &align_li } ;



Text o550 = { {
{"Quick",&fmt_h}
} , &fmt_li , &align_li } ;



Text o552 = { {
{"SysAbort",&fmt_h}
} , &fmt_li , &align_li } ;



Text o554 = { {
{"SysAtomic",&fmt_h}
} , &fmt_li , &align_li } ;



Text o556 = { {
{"SysCon",&fmt_h}
} , &fmt_li , &align_li } ;



Text o558 = { {
{"SysError",&fmt_h}
} , &fmt_li , &align_li } ;



Text o560 = { {
{"SysFile",&fmt_h}
} , &fmt_li , &align_li } ;



Text o562 = { {
{"SysFileSystem",&fmt_h}
} , &fmt_li , &align_li } ;



Text o564 = { {
{"SysLaunchPath",&fmt_h}
} , &fmt_li , &align_li } ;



Text o566 = { {
{"SysMemPage",&fmt_h}
} , &fmt_li , &align_li } ;



Text o568 = { {
{"SysNet",&fmt_h}
} , &fmt_li , &align_li } ;



Text o570 = { {
{"SysPlanInit",&fmt_h}
} , &fmt_li , &align_li } ;



Text o572 = { {
{"SysProp",&fmt_h}
} , &fmt_li , &align_li } ;



Text o574 = { {
{"SysSem",&fmt_h}
} , &fmt_li , &align_li } ;



Text o576 = { {
{"SysTask",&fmt_h}
} , &fmt_li , &align_li } ;



Text o578 = { {
{"SysTime",&fmt_h}
} , &fmt_li , &align_li } ;



Text o580 = { {
{"SysTlsSlot",&fmt_h}
} , &fmt_li , &align_li } ;



Text o582 = { {
{"SysWait",&fmt_h}
} , &fmt_li , &align_li } ;



Text o584 = { {
{"PlanInit_CCore",&fmt_h}
} , &fmt_li , &align_li } ;





Text o587 = { {
{"XCore targets",&fmt_h}
} , &fmt_li , &align_li } ;



TextList o588 = { {{"1.",{
{ &o589 , null , {0,0} , {0,0} }
}}
,{"2.",{
{ &o591 , null , {0,0} , {0,0} }
}}
,{"3.",{
{ &o593 , null , {0,0} , {0,0} }
}}
,{"4.",{
{ &o595 , null , {0,0} , {0,0} }
}}
,{"5.",{
{ &o597 , null , {0,0} , {0,0} }
}}
,{"6.",{
{ &o599 , null , {0,0} , {0,0} }
}}
,{"7.",{
{ &o601 , null , {0,0} , {0,0} }
}}
,{"8.",{
{ &o603 , null , {0,0} , {0,0} }
}}
,{"9.",{
{ &o605 , null , {0,0} , {0,0} }
}}
,{"10.",{
{ &o607 , null , {0,0} , {0,0} }
}}
,{"11.",{
{ &o609 , null , {0,0} , {0,0} }
}}
,{"12.",{
{ &o611 , null , {0,0} , {0,0} }
}}
,{"13.",{
{ &o613 , null , {0,0} , {0,0} }
}}
,{"14.",{
{ &o615 , null , {0,0} , {0,0} }
}}
,{"15.",{
{ &o617 , null , {0,0} , {0,0} }
}}
,{"16.",{
{ &o619 , null , {0,0} , {0,0} }
}}
,{"17.",{
{ &o621 , null , {0,0} , {0,0} }
,{ &o622 , null , {0,0} , {0,0} }
}}
} };

Text o589 = { {
{"PlatformBase",&fmt_h}
} , &fmt_li , &align_li } ;



Text o591 = { {
{"Quick",&fmt_h}
} , &fmt_li , &align_li } ;



Text o593 = { {
{"SysAbort",&fmt_h}
} , &fmt_li , &align_li } ;



Text o595 = { {
{"SysAtomic",&fmt_h}
} , &fmt_li , &align_li } ;



Text o597 = { {
{"SysMemSpace",&fmt_h}
} , &fmt_li , &align_li } ;



Text o599 = { {
{"SysTime",&fmt_h}
} , &fmt_li , &align_li } ;



Text o601 = { {
{"SysCon",&fmt_h}
} , &fmt_li , &align_li } ;



Text o603 = { {
{"SysPlanInit",&fmt_h}
} , &fmt_li , &align_li } ;



Text o605 = { {
{"TaskContext",&fmt_h}
} , &fmt_li , &align_li } ;



Text o607 = { {
{"DevInt",&fmt_h}
} , &fmt_li , &align_li } ;



Text o609 = { {
{"DevTick",&fmt_h}
} , &fmt_li , &align_li } ;



Text o611 = { {
{"DevWaitForInterrupt",&fmt_h}
} , &fmt_li , &align_li } ;



Text o613 = { {
{"DevIntHandle",&fmt_h}
} , &fmt_li , &align_li } ;



Text o615 = { {
{"DevPlanInit",&fmt_h}
} , &fmt_li , &align_li } ;



Text o617 = { {
{"CBase",&fmt_h}
} , &fmt_li , &align_li } ;



Text o619 = { {
{"PlanInit_CCore",&fmt_h}
} , &fmt_li , &align_li } ;



Text o621 = { {
{"STD implementation",&fmt_h}
} , &fmt_li , &align_li } ;



TextList o622 = { {{"1.",{
{ &o623 , null , {0,0} , {0,0} }
}}
,{"2.",{
{ &o625 , null , {0,0} , {0,0} }
}}
,{"3.",{
{ &o627 , null , {0,0} , {0,0} }
}}
,{"4.",{
{ &o629 , null , {0,0} , {0,0} }
}}
} };

Text o623 = { {
{"atexit",&fmt_h}
} , &fmt_li , &align_li } ;



Text o625 = { {
{"__std_init",&fmt_h}
} , &fmt_li , &align_li } ;



Text o627 = { {
{"sysroot",&fmt_h}
} , &fmt_li , &align_li } ;



Text o629 = { {
{"binutils and gcc",&fmt_h}
} , &fmt_li , &align_li } ;







Text o633 = { {
{"Tools"}
} , &fmt_li , &align_li } ;



TextList o634 = { {{"1.",{
{ &o635 , null , {0,0} , {0,0} }
}}
,{"2.",{
{ &o637 , null , {0,0} , {0,0} }
}}
,{"3.",{
{ &o639 , null , {0,0} , {0,0} }
}}
,{"4.",{
{ &o641 , null , {0,0} , {0,0} }
}}
,{"5.",{
{ &o643 , null , {0,0} , {0,0} }
}}
,{"6.",{
{ &o645 , null , {0,0} , {0,0} }
}}
,{"7.",{
{ &o647 , null , {0,0} , {0,0} }
}}
,{"8.",{
{ &o649 , null , {0,0} , {0,0} }
}}
,{"9.",{
{ &o651 , null , {0,0} , {0,0} }
}}
,{"10.",{
{ &o653 , null , {0,0} , {0,0} }
}}
,{"11.",{
{ &o655 , null , {0,0} , {0,0} }
}}
,{"12.",{
{ &o657 , null , {0,0} , {0,0} }
}}
,{"13.",{
{ &o659 , null , {0,0} , {0,0} }
}}
,{"14.",{
{ &o661 , null , {0,0} , {0,0} }
}}
,{"15.",{
{ &o663 , null , {0,0} , {0,0} }
}}
} };

Text o635 = { {
{"MakeList",&fmt_h}
} , &fmt_li , &align_li } ;



Text o637 = { {
{"Keywords",&fmt_h}
} , &fmt_li , &align_li } ;



Text o639 = { {
{"CondLangLR1",&fmt_h}
} , &fmt_li , &align_li } ;



Text o641 = { {
{"ParserGen",&fmt_h}
} , &fmt_li , &align_li } ;



Text o643 = { {
{"DDLShow",&fmt_h}
} , &fmt_li , &align_li } ;



Text o645 = { {
{"DDLTypeSet",&fmt_h}
} , &fmt_li , &align_li } ;



Text o647 = { {
{"EllipticPi",&fmt_h}
} , &fmt_li , &align_li } ;



Text o649 = { {
{"EchoServer",&fmt_h}
} , &fmt_li , &align_li } ;



Text o651 = { {
{"PTPEchoServer",&fmt_h}
} , &fmt_li , &align_li } ;



Text o653 = { {
{"PTPServer",&fmt_h}
} , &fmt_li , &align_li } ;



Text o655 = { {
{"exectest",&fmt_h}
} , &fmt_li , &align_li } ;



Text o657 = { {
{"PSecEchoServer",&fmt_h}
} , &fmt_li , &align_li } ;



Text o659 = { {
{"Regen",&fmt_h}
} , &fmt_li , &align_li } ;



Text o661 = { {
{"PTPSecureServer",&fmt_h}
} , &fmt_li , &align_li } ;



Text o663 = { {
{"PTPSecureClient",&fmt_h}
} , &fmt_li , &align_li } ;







} // scope Pages

Book Data = { Pages#BookName , {&Pages#page1} , Pages#Back , Pages#Fore } ;

