@ DevWaitForInterrupt.s
@-----------------------------------------------------------------------------------------
@
@  Project: CCore 2.00
@
@  Tag: Target/BeagleBoneBlack
@
@  License: Boost Software License - Version 1.0 - August 17th, 2003
@
@            see http://www.boost.org/LICENSE_1_0.txt or the local copy
@
@  Copyright (c) 2016 Sergey Strukov. All rights reserved.
@
@-----------------------------------------------------------------------------------------

        .text
        .align 2

        .global _ZN5CCore3Dev16WaitForInterruptEv

_ZN5CCore3Dev16WaitForInterruptEv:               @ CCore::Dev::WaitForInterrupt

        wfi

        bx      lr

@-----------------------------------------------------------------------------------------

