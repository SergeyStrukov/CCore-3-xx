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

.. ------------------------------------------------------------------------------------------------------------------

.. _to_sync:

Synchronization
---------------

.. ------------------------------------------------------------------------------------------------------------------

.. _to_packets:

Packets
-------

.. ------------------------------------------------------------------------------------------------------------------



