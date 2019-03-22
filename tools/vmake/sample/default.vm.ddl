/* default.vm.ddl */

Rule r1 = {} ;

Dep dep1 = { {&a1} } ;

Target main = {} ;

Target a1 = { 'a1' } ;

Target a2 = { 'a2' } ;

Target a3 = { 'a3' } ;

type XXX = Dep ;

XXX dep2 = { {&a2} } ;

scope Inner {

Dep dep3 = { {&a3} } ;

}
