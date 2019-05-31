.. title:: Sphinx test page

Sphinx test
===========

This page is intended for testing sphinx capabilities.

*Italic text*.

**Bold text**.

1. List item 1.

  1. Inner list 1.1.
  2. Inner list 1.2.

2. List item 2.

.. math::

   Пусть\ a \in \mathbb{Z} ,\ p \nmid a . Положим   

   G\left(\frac{a}{p}\right):=\sum_{0 \leqslant x < p}^{} e^{ \displaystyle 2 \pi i \frac{a x^2}{p} } 

code::

    template <CursorType R,class T> requires ( CursorOverType<R,T> )
    class PrintSet : public PrintOptAdapter< Meta::UnConst<T> >
     {
       R range;
    
      private:
    
       template <class S>
       static const T & Cast(const S &obj) { return obj; }
    
      public:
    
       explicit PrintSet(const R &range_) : range(range_) {}
    
       void print(PrinterType &out) const
        {
         R r=range;
    
         if( +r )
           {
            Putobj(out,"{ "_c,Cast(*r));
    
            for(++r; +r ;++r) Putobj(out," , "_c,Cast(*r));
    
            Putobj(out," }"_c);
           }
         else
           {
            Putobj(out,"{ }"_c);
           }
        }
    
       void print(PrinterType &out,const AnyType &opt) const
        {
         R r=range;
    
         if( +r )
           {
            Putobj(out,"{ "_c,BindOpt(opt,Cast(*r)));
    
            for(++r; +r ;++r) Putobj(out," , "_c,BindOpt(opt,Cast(*r)));
    
            Putobj(out," }"_c);
           }
         else
           {
            Putobj(out,"{ }"_c);
           }
        }
     };

