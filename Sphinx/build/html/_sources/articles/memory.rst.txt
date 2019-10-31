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

The old **C** pair::

   void * malloc(size_t len);

   void free(void *mem);

The new **C++** pair::

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
 
   void MemFree(void *mem); // mem may == 0


First of all, no **size_t**, please. **ulen** is a much better name for the practicall programming, 
where the good name selection does matter.

Second, we need two allocation functions. One throws an exception, and another returns **null**.
An we need functions, not operators, clean and simple.

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

extend/shrink::

   bool MemExtend(void *mem,ulen len); // mem may == 0

   bool MemShrink(void *mem,ulen len); // mem may == 0

This two function can be used to extend or shrink an allocated block of memory *in-place*.

Why these functions are required?

Consider a dynamic array class, like **std::vector**.
This class allocates a memory block, then creates a range of elements withing.
When you append the array with a new element, it must find a memory behind the last element.
If there is no one, it must reallocate a bigger block of memory, then move elements there. 
This is expensive. So, why don't try to *extend* the memory block in-place? It may fall,
and in such case we do full reallocation.

Another case, if you have an array, you may have an extra memory, reserved behind the last element. 
But if you don't need to extend the array anymore, you may *shrink* the memory block to release the extra memory.

There is **C** function **realloc()**, I haven't mentioned before and for a reason. 
This function does some memory reallocation. 
But it does it in such a way, it cannot be used in **C++** with objects of non-trivial types.

So we need a simple and clean solution like presented above.

Both these functions are efficient.


Memory usage statistics
-----------------------

stats::

   struct MemStatData
    {
     ulen block_count; // the count of allocated memory blocks
     ulen len_count;   // the total allocated memory

     .... // some methods
    };

   struct MemStat : MemStatData
    {
     MemStat();
    };

   struct MemPeak : MemStatData
    {
     MemPeak();
    };

These set of functions (not a functions, ofc, but a *class-functions*) returns the heap statistic information.

What are they good for?

For information and for memory leak detection. It can help detect memory leaks during testing.

**MemStat** returns the current heap statistic.

**MemPeak** returns the peak heap statistic.

Both values are usefull.

Utilities
---------

utilities::

   ulen MemLen(const void *mem); // mem may == 0

   void MemLim(ulen limit);

   void GuardNoMem(ulen len);

And some utilities at last.

**MemLen()** determins the length of the memory block.

**MemLim()** limits the heap capacity. I's very useful for testing. 
You can easily simulate the situation of memory exhausted.

**GuardNoMem()** throws a *"no-memory"* exception. It is used by **MemAlloc()** to throw an exception, 
and can be used in custom situations to implement the similar behavior.


CCore memory management
=======================

When I've started development of **CCore**, the first prioryty task was to design the proper memory management subsystem, instead of standard.
Why? For several reasons.

For real-time systems we need a real-time heap. On bare-metal, heap lives in a predefine memory region and we can make it real-time.
On normal OS, heap makes system calls to get a huge memory regions and then split them on smaller ones. So it can be made quasi-real-time.

On bare-metal, we are limited in resources, so extend and shrink functions are a big plus.
Heap protection and statistic are also helpful in development of reliable software.


EOF
===

by Sergey Strukov

CCore brief: http://sergeystrukov.github.io/CCore-Sphinx-3-60/brief/brief.html

CCore: https://github.com/SergeyStrukov/CCore-3-xx

