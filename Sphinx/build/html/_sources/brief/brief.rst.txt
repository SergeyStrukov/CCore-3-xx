.. title:: CCore brief

.. ------------------------------------------------------------------------------------------------------------------

CCore breif
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

.. ------------------------------------------------------------------------------------------------------------------

.. _to_exception:

Exceptions
----------

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



