# Quick.s
#-----------------------------------------------------------------------------------------
#
#  Project: CCore 2.00
#
#  Tag: Target/WIN64utf8
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2015 Sergey Strukov. All rights reserved.
#
#-----------------------------------------------------------------------------------------

        .text

        .global _ZN5CCore5Quick9ScanLSBitEm
        .global _ZN5CCore5Quick9ScanMSBitEm
        .global _ZN5CCore5Quick10ByteSwap16Et
        .global _ZN5CCore5Quick10ByteSwap32Ej
        .global _ZN5CCore5Quick10ByteSwap64Em

#-----------------------------------------------------------------------------------------

        .p2align 4,,15

_ZN5CCore5Quick9ScanLSBitEm:           # CCore::Quick::ScanLSBit

        bsfq    %rcx, %rax

        ret

#-----------------------------------------------------------------------------------------

        .p2align 4,,15

_ZN5CCore5Quick9ScanMSBitEm:           # CCore::Quick::ScanMSBit

        bsrq    %rcx, %rax

        ret

#-----------------------------------------------------------------------------------------

        .p2align 4,,15

_ZN5CCore5Quick10ByteSwap16Et:         # CCore::Quick::ByteSwap16

        movzwl  %cx, %eax
        xchgb   %al, %ah

        ret

#-----------------------------------------------------------------------------------------

        .p2align 4,,15

_ZN5CCore5Quick10ByteSwap32Ej:         # CCore::Quick::ByteSwap32

        movl    %ecx, %eax
        bswap   %eax

        ret

#-----------------------------------------------------------------------------------------

        .p2align 4,,15

_ZN5CCore5Quick10ByteSwap64Em:         # CCore::Quick::ByteSwap64

        movq    %rcx, %rax
        bswap   %rax

        ret

#-----------------------------------------------------------------------------------------

        .global _ZN5CCore5Quick11UIntMulFuncImE3MulC1Emm
        .global _ZN5CCore5Quick11UIntMulFuncImE3DivEmmm
        .global _ZN5CCore5Quick11UIntMulFuncImE3ModEmmm
        .global _ZN5CCore5Quick11UIntMulFuncImE6MulDivEmmm
        .global _ZN5CCore5Quick11UIntMulFuncImE6DivModC1Emmm
        .global _ZN5CCore5Quick11UIntMulFuncImE6ModMulEmmm
        .global _ZN5CCore5Quick11UIntMulFuncImE6ModMacEmmmm

#-----------------------------------------------------------------------------------------

        .p2align 4,,15

_ZN5CCore5Quick11UIntMulFuncImE3MulC1Emm:        # CCore::Quick::UIntMulFunc<uint64>::Mul::Mul

        movq    %rdx, %rax
        mulq    %r8

        movq    %rdx, (%rcx)
        movq    %rax, 8(%rcx)

        ret

#-----------------------------------------------------------------------------------------

        .p2align 4,,15

_ZN5CCore5Quick11UIntMulFuncImE3DivEmmm:         # CCore::Quick::UIntMulFunc<uint64>::Div

        movq    %rdx, %rax
        movq    %rcx, %rdx
        divq    %r8

        ret

#-----------------------------------------------------------------------------------------

        .p2align 4,,15

_ZN5CCore5Quick11UIntMulFuncImE3ModEmmm:         # CCore::Quick::UIntMulFunc<uint64>::Mod

        movq    %rdx, %rax
        movq    %rcx, %rdx
        divq    %r8

        movq    %rdx, %rax

        ret

#-----------------------------------------------------------------------------------------

        .p2align 4,,15

_ZN5CCore5Quick11UIntMulFuncImE6MulDivEmmm:      # CCore::Quick::UIntMulFunc<uint64>::MulDiv

        movq    %rcx, %rax
        mulq    %rdx
        divq    %r8

        ret

#-----------------------------------------------------------------------------------------

        .p2align 4,,15

_ZN5CCore5Quick11UIntMulFuncImE6DivModC1Emmm:    # CCore::Quick::UIntMulFunc<uint64>::DivMod::DivMod

        movq    %r8, %rax
        divq    %r9

        movq    %rax, (%rcx)
        movq    %rdx, 8(%rcx)

        ret

#-----------------------------------------------------------------------------------------

        .p2align 4,,15

_ZN5CCore5Quick11UIntMulFuncImE6ModMulEmmm:      # CCore::Quick::UIntMulFunc<uint64>::ModMul

        movq    %rdx, %rax
        mulq    %rcx
        divq    %r8

        movq    %rdx, %rax

        ret

#-----------------------------------------------------------------------------------------

        .p2align 4,,15

_ZN5CCore5Quick11UIntMulFuncImE6ModMacEmmmm:     # CCore::Quick::UIntMulFunc<uint64>::ModMac

        movq    %rdx, %rax
        mulq    %r8

        addq    %rcx, %rax
        adcq    $0, %rdx

        divq    %r9

        movq    %rdx, %rax

        ret

#-----------------------------------------------------------------------------------------

