.. title:: CCore brief

.. ------------------------------------------------------------------------------------------------------------------

CCore brief
===========

Many years ago I had started this project ... :ref:`to_ab_ovo`

**CCore** uses an advanced memory manager ... :ref:`to_heap`

**CCore** provides `Printf()` print facility ... :ref:`to_printf`

**CCore** uses advanced exception handling pattern ... :ref:`to_exception`

One of the most useful invention, implemented in **CCore**, is **DDL** ... :ref:`to_DDL`

**CCore** provides advanced synchronization basis ... :ref:`to_sync`

**CCore** implements the **Packets** -- infrastructure for mass asynchonous request processing ... :ref:`to_packets`

and much more ...  

**CCore** source contains many advanced C++ tricks, based on the latest C++ language features. 
No way I can describe all of them in this *brief notes*.
So put your hands on ...  

.. ------------------------------------------------------------------------------------------------------------------

.. _to_ab_ovo:

Ab ovo
------

.. ------------------------------------------------------------------------------------------------------------------

.. _to_heap:

Heap
----

**CCore** heap has the following features:

1. Best fit.

      Heap selects a smallest available block of memory to satisfy an allocation request.

2. Fast, with real-time properties.

3. Integrity check.

      If you try to use an invalid pointer as a heap function argument, it will be higly likely detected and abort will be called.

4. Extended interface.

   Here is a list of heap functions::
   
       void * TryMemAlloc(ulen len) noexcept;
    
       void * MemAlloc(ulen len);
    
       ulen MemLen(const void *mem);       // mem may == 0
    
       bool MemExtend(void *mem,ulen len); // mem may == 0
    
       bool MemShrink(void *mem,ulen len); // mem may == 0
    
       void MemFree(void *mem);            // mem may == 0
    
       void MemLim(ulen limit);
       
   You can not only allocate and deallocate blocks of memory, but you can resize them in place (if possible).
   This is useful in the building of resizable arrays and other containers.
    
   You can also set a memory allocation limit. 
   This feature is useful for testing.
   
   Heap has also some statistic functions, this allow to watch over the memory usage.     

These features are highly valuable in any kind of software development.    

.. ------------------------------------------------------------------------------------------------------------------

.. _to_printf:

`Printf()`
----------

`Printf()` is similar to the **C** `printf()`.
It works as the following::

  int x = 12345 ;
    
  Printf(Con,"x = #;\n\n",x);

The first argument is a *printer* object. In this case it is the console.
The second is a format string. By tradition it is a null terminated string.
After the format string an arbitrary number of arguments of any *printable* types may follow.
They will be printed in places of format stems.
Each format stem is a sequence like `"#...;"`.
Between the starting `'#'` symbol and the ending `';'` symbol options my be specified::

  Printf(Con,"--- #10l; ---\n",12345);
  Printf(Con,"--- #10i; ---\n",12345);
  Printf(Con,"--- #10r; ---\n",12345);
  Printf(Con,"--- #+10.5l; ---\n",12345);
  Printf(Con,"--- #+10.hi; ---\n",12345);
  Printf(Con,"--- #10.hi; ---\n",-12345);

  Printf(Con,"--- #10.f2l; ---\n",12345);
  Printf(Con,"--- #10.f2i; ---\n",12345);
  Printf(Con,"--- #10.f2r; ---\n",12345);

  Printf(Con,"--- #10.f2l; ---\n",-12345);
  Printf(Con,"--- #10.f2i; ---\n",-12345);
  Printf(Con,"--- #10.f2r; ---\n",-12345);

  Printf(Con,"--- #10.f2l; ---\n",-12);
  Printf(Con,"--- #10.f2i; ---\n",-12);
  Printf(Con,"--- #10.f2r; ---\n",-12);

  Printf(Con,"--- #10.f4l; ---\n",12);
  Printf(Con,"--- #10.f4i; ---\n",12);
  Printf(Con,"--- #10.f4r; ---\n",12);

  Printf(Con,"--- #10.f2l; ---\n",0);
  Printf(Con,"--- #10.f2i; ---\n",0);
  Printf(Con,"--- #10.f2r; ---\n",0);
  
and the output is::  
  
    --- 12345      ---
    --- 0000012345 ---
    ---      12345 ---
    --- +343340    ---
    --- +00003039h ---
    --- -00003039h ---
    --- 123.45     ---
    --- 0000123.45 ---
    ---     123.45 ---
    --- -123.45    ---
    --- -000123.45 ---
    ---    -123.45 ---
    --- -0.12      ---
    --- -000000.12 ---
    ---      -0.12 ---
    --- 0.0012     ---
    --- 00000.0012 ---
    ---     0.0012 ---
    --- 0.00       ---
    --- 0000000.00 ---
    ---       0.00 ---  

`Printf()` ties together a printer object, a format string and printable objects.
You can easily develope these kind of objects to match your particular needs.

Printer class
*************

In general, to make a class a printer you have to define the following class elements::

  class PrintToSomething
   {
    public:
    
     using PrintOutType = PrintToSomething & ;

     PrintOutType printRef() { return *this; }
     
     void put(char ch);

     void put(char ch,ulen len);

     void put(const char *str,ulen len);

     void flush();
   };

In most cases, however, it's better to inherit from the following base class for printer types::

    class PrintBase : NoCopy
     {
       ....
       
       virtual PtrLen<char> do_provide(ulen hint_len)=0;
    
       virtual void do_flush(char *ptr,ulen len)=0;
    
      public:
    
       using PrintOutType = PrintBase & ;
    
       PrintOutType printRef() { return *this; }
    
       // constructors
    
       PrintBase();
    
       ~PrintBase();
    
       // methods

       ....    
     };

You have to implement two virtual functions in a derived class to output printed characters to whatever you want.

Printable types
***************

Making a type printable is simple like this::

    struct IntPoint
     {
      int x;
      int y;
      
      ....
      
      // print object
    
      void print(PrinterType &out) const
       {
        Printf(out,"(#;,#;)",x,y);
       } 
     };

OR, if you need a printing options, like this::

    struct PrintDumpOptType
     {
      ....
      
      void setDefault();
    
      PrintDumpOptType() { setDefault(); }
    
      PrintDumpOptType(const char *ptr,const char *lim);
    
      //
      // [width=0][.line_len=16]
      //
     };
     
    template <UIntType UInt>
    class PrintDump
     {
       PtrLen<const UInt> data;
    
      public:
    
       ....
    
       using PrintOptType = PrintDumpOptType ;
    
       void print(PrinterType &out,PrintOptType opt) const;
     };

.. ------------------------------------------------------------------------------------------------------------------

.. _to_exception:

Exceptions
----------

**CCore** uses the special pattern to throw and catch exceptions:

1. All exception are of type `CatchType`, which is an empty structure::

      try
        {
         ....
        }
      catch(CatchType)
        {
        }

2. To get exception notifications you have to define a special object::  

      try
        {
         ReportException report;
        
         ....
        }
      catch(CatchType)
        {
        }

3. To react on `no-exceptions` you have to call the special method `guard()`::

      try
        {
         ReportException report;
        
         {
          ....
         } 
         
         report.guard();
        }
      catch(CatchType)
        {
        }

4. To throw an exception use the function `Printf()`::

      Printf(Exception,"Shit happened"); 
      
        // exception will be thrown by this call 
      
   OR::    
   
      Printf(NoException,"Shit happened, but we continue ..."); 
      
        // no exception will be thrown by this call
      
5. Event if you don't throw an exception, `report` object gets the exception text ans sets an internal flag.
   So later, when you call `report.guard()` an exception will be eventually thown.       

Using this pattern you can safely handle exceptional situations in class destructors::

    PrintFile::~PrintFile()
     {
      if( isOpened() )
        {
         FileMultiError errout;
    
         soft_close(errout);
    
         if( +errout )
           {
            Printf(NoException,"CCore::PrintFile::~PrintFile() : #;",errout);
           }
        }
     }

No one glitch will be forgotten!

.. ------------------------------------------------------------------------------------------------------------------

.. _to_DDL:

DDL
---

**DDL** expands as "Data Definition Language". 
This is a textual language for representation of data.
**DDL** files looks like::

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

and like this::
 
    //include <FavData.ddl>
    
    FavData Data =
     {
    
      {
       { "CCore" , "" , True , True },
       { "CCore 3-xx" , "D:/active/home/C++/CCore-3-xx/book/CCore.book.vol" , False , True },
       { "Sample" , "" , True , False },
       { "CCore 3-xx" , "D:/active/home/C++/CCore-3-xx/book/sample/CCore.book.ddl" , False , False }
      },
    
      0,
      1
     };

You can find the complete description `here <https://github.com/SergeyStrukov/CCore-3-xx/blob/master/doc/DDL.pdf>`_.
**DDL** is

1. **C**-style,
2. typed,
3. commutative,
4. flexible,
5. polymorphe,
6. simple.

It can be conveniently used for representation of any kind of data with any level of internal connectivity.
For example, this types are used to reprersent context-free grammars and LR1 state machines::

    type AtomIndex = uint32 ;
    type SyntIndex = uint32 ;
    type KindIndex = uint32 ;
    type ElementIndex = uint32 ;
    type RuleIndex = uint32 ;
    type StateIndex = uint32 ;
    type FinalIndex = uint32 ;
    
    struct Lang
     {
      Atom[] atoms;
      Synt[] synts;
      Synt * [] lang;
      Element[] elements;
      Rule[] rules;
      TopRule[] top_rules;
      State[] states;
      Final[] finals;
     };
    
    struct Atom
     {
      AtomIndex index;
      text name;
      
      Element *element;
     };
    
    struct Synt
     {
      SyntIndex index;
      text name;
      
      Kind[] kinds;
      Rule * [] rules;
     };
    
    struct Kind
     {
      KindIndex kindex; // index among all kinds
      KindIndex index; // index in synt array
      text name;
    
      Synt *synt;
      
      Element *element;
      
      TopRule * [] rules;
     };
    
    struct Element
     {
      ElementIndex index;
      
      {Atom,Kind} * elem;
     };
    
    struct Rule
     {
      RuleIndex index;
      text name;
    
      Kind *result;
    
      type Arg = {Atom,Synt} * ;
    
      Arg[] args;
     };
     
    struct TopRule
     {
      RuleIndex index;
      text name;
      
      Rule *bottom;
    
      Kind *result;
    
      type Arg = {Atom,Kind} * ;
    
      Arg[] args;
     }; 
    
    struct State
     {
      StateIndex index;
      Final *final;
    
      struct Transition
       {
        Element *element;
        State *state;
       };
    
      Transition[] transitions;
     };
    
    struct Final
     {
      FinalIndex index;
    
      struct Action
       {
        Atom *atom; // null for (End)
        Rule *rule; // null for <- ( STOP if atom is (END) )
       };
    
      Action[] actions;
     };

And more samples::

    int a = 10 ;
    
    int * pa = &a ;
    
    text [a] B = { "b1" , "b2" } ;
    
    text [] C = { "c1" , "c2" } ;
    
    struct S
     {
      text name = "unnamed" ;
      int id = 0 ;
     };
    
    S record = { "" , 10 } ;

,::
    
    int a = 10 ;

    int * pa = &a ;
    
    int b = *pa ; // 10
    
    int[10] c = {0,1,2,3,4,5,6,7,8,9} ;
    
    int * pc = c+5 ;
    
    int d = *pc ; // 5
    int e = pc[2] ; // 7
    
    int l = pc - c ; // 5

,::

    type Ptr = {int,uint} * ; 
    
    int a = 1 ;
    
    uint b = 2 ;
    
    Ptr ptr_a = &a ; 
    
    Ptr ptr_b = &b ;

**DDL** is not intended for the manual data edition. 
Normally **DDL** files are generated by software and used by another software.
It is a *Soft-to-Soft* language. 
You can think about it as a "universal data assembler".
I am lovely using **DDL** for many years for different purposes:

1. configuration files,
2. complex data files, like shown above,
3. Book files, this is a latest GUI component, developed to represent formatted text:

.. image:: Book.png

So I advise everybody learn and use it in your projects.
You will be loving it too!
Printing **DDL** files is easy, you can do it using `Printf()`.
To load data from **DDL** files, however, you need a library.
**CCore** contains components and tools to do it, but you may develope your own, 
using **CCore** implementtaion as a reference design.    

.. ------------------------------------------------------------------------------------------------------------------

.. _to_sync:

Synchronization
---------------

.. ------------------------------------------------------------------------------------------------------------------

.. _to_packets:

Packets
-------

.. ------------------------------------------------------------------------------------------------------------------



