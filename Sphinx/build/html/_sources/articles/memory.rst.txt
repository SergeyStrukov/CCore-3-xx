.. title:: WIMSL: advanced memory management. 

.. ------------------------------------------------------------------------------------------------------------------

Abstract
========

WIMSL: What I miss in the standard library.

Yes. I need the *memory mangement* and need it better, than the standard library provides.

Prologue
========

So, what's exactly SL gives us.
Two memory management functions sets.

The old C pair::

   void * malloc(size_t len);

   void free(void *mem);

The new C++ pair::

   void * operator new[] (size_t len); // for   char *mem=new char[len];

   void operator delete[] (void *mem); // for   delete[] mem;

In any sane implementation they are the same, except the **new** throws an exception, but **malloc** just returns 0.

What is missing
===============

Oh, a lot of things!

Basic
-----

Let's start with the basic functionality. We will discuss the global heap functions, 
but the same is relevant to heap class objects.

alloc/free::

   void * TryMemAlloc(ulen len) noexcept;

   void * MemAlloc(ulen len);
 
   void MemFree(void *mem);            // mem may == 0


First of all, no **size_t**, please. **ulen** is a much better name for the practicall programming, 
where the good name selection does matter.

Second, we need two allocation functions. One throws an exception, and another returns **null**.

Protection
----------

What if we pass a wrong argument to **MemFree()**? *Undefine behavior* ?
No, thanks. Heap must have a *defined* behavior in this case: print a diagnostic message and then call **abort()**.
Can we implement this? Yes, we can! 
Can we do it efficiently? Yes! We can do it too!
So it must be a **required property of the heap**::

   MemFree(mem) : if mem is not a valid argument, it prints a diagnostic message and then call abort()

Expand and shrink
-----------------

expand/shrink::

   bool MemExtend(void *mem,ulen len); // mem may == 0

   bool MemShrink(void *mem,ulen len); // mem may == 0

This two function can be used to extend or shrink an allocated block of memory *in-place*.

TODO
std::vector
realloc()

Memory usage statistics
-----------------------

TODO

Utilities
---------

TODO

CCore memory management
=======================

When I've started development of **CCore**, the first prioryty task was to design the proper memory management subsystem, instead of standard.
Why? For several reasons.

TODO

EOF
===

by Sergey Strukov

CCore brief: http://sergeystrukov.github.io/CCore-Sphinx-3-60/brief/brief.html

CCore: https://github.com/SergeyStrukov/CCore-3-xx

