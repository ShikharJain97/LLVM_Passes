	.text
	.file	"NameMangle.cpp"
	.section	.text.startup,"ax",@progbits
	.p2align	4, 0x90                         # -- Begin function __cxx_global_var_init
	.type	__cxx_global_var_init,@function
__cxx_global_var_init:                  # @__cxx_global_var_init
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	$_ZStL8__ioinit, %edi
	callq	_ZNSt8ios_base4InitC1Ev
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	movl	$_ZStL8__ioinit, %esi
	movl	$__dso_handle, %edx
	callq	__cxa_atexit
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end0:
	.size	__cxx_global_var_init, .Lfunc_end0-__cxx_global_var_init
	.cfi_endproc
                                        # -- End function
	.text
	.globl	_Z5func1ii                      # -- Begin function _Z5func1ii
	.p2align	4, 0x90
	.type	_Z5func1ii,@function
_Z5func1ii:                             # @_Z5func1ii
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	%edi, -8(%rbp)
	movl	%esi, -4(%rbp)
	movl	-8(%rbp), %eax
	addl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end1:
	.size	_Z5func1ii, .Lfunc_end1-_Z5func1ii
	.cfi_endproc
                                        # -- End function
	.globl	_Z5func1i                       # -- Begin function _Z5func1i
	.p2align	4, 0x90
	.type	_Z5func1i,@function
_Z5func1i:                              # @_Z5func1i
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	imull	-4(%rbp), %eax
	imull	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end2:
	.size	_Z5func1i, .Lfunc_end2-_Z5func1i
	.cfi_endproc
                                        # -- End function
	.globl	_Z5func1df                      # -- Begin function _Z5func1df
	.p2align	4, 0x90
	.type	_Z5func1df,@function
_Z5func1df:                             # @_Z5func1df
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movsd	%xmm0, -16(%rbp)
	movss	%xmm1, -4(%rbp)
	movsd	-16(%rbp), %xmm0                # xmm0 = mem[0],zero
	movss	-4(%rbp), %xmm1                 # xmm1 = mem[0],zero,zero,zero
	cvtss2sd	%xmm1, %xmm1
	subsd	%xmm1, %xmm0
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end3:
	.size	_Z5func1df, .Lfunc_end3-_Z5func1df
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst8,"aM",@progbits,8
	.p2align	3                               # -- Begin function main
.LCPI4_0:
	.quad	0x40562a9a02752546              # double 88.665649999999999
	.section	.rodata.cst4,"aM",@progbits,4
	.p2align	2
.LCPI4_1:
	.long	0x40d8f5c3                      # float 6.78000021
	.text
	.globl	main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset %rbx, -24
	movl	$10, -12(%rbp)
	movl	$20, -20(%rbp)
	movss	.LCPI4_1(%rip), %xmm0           # xmm0 = mem[0],zero,zero,zero
	movss	%xmm0, -16(%rbp)
	movsd	.LCPI4_0(%rip), %xmm0           # xmm0 = mem[0],zero
	movsd	%xmm0, -32(%rbp)
	movabsq	$_ZSt4cout, %rdi
	movabsq	$.L.str, %rsi
	callq	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rax, %rbx
	movl	-12(%rbp), %edi
	movl	-20(%rbp), %esi
	callq	_Z5func1ii
	movq	%rbx, %rdi
	movl	%eax, %esi
	callq	_ZNSolsEi
	movabsq	$.L.str.1, %rsi
	movq	%rax, %rdi
	callq	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movabsq	$_ZSt4cout, %rdi
	movabsq	$.L.str.2, %rsi
	callq	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rax, %rbx
	movl	-12(%rbp), %edi
	callq	_Z5func1i
	movq	%rbx, %rdi
	movl	%eax, %esi
	callq	_ZNSolsEi
	movabsq	$.L.str.1, %rsi
	movq	%rax, %rdi
	callq	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movabsq	$_ZSt4cout, %rdi
	movabsq	$.L.str.3, %rsi
	callq	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rax, %rbx
	movsd	-32(%rbp), %xmm0                # xmm0 = mem[0],zero
	movss	-16(%rbp), %xmm1                # xmm1 = mem[0],zero,zero,zero
	callq	_Z5func1df
	movq	%rbx, %rdi
	callq	_ZNSolsEd
	movabsq	$.L.str.1, %rsi
	movq	%rax, %rdi
	callq	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	xorl	%eax, %eax
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end4:
	.size	main, .Lfunc_end4-main
	.cfi_endproc
                                        # -- End function
	.section	.text.startup,"ax",@progbits
	.p2align	4, 0x90                         # -- Begin function _GLOBAL__sub_I_NameMangle.cpp
	.type	_GLOBAL__sub_I_NameMangle.cpp,@function
_GLOBAL__sub_I_NameMangle.cpp:          # @_GLOBAL__sub_I_NameMangle.cpp
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	callq	__cxx_global_var_init
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end5:
	.size	_GLOBAL__sub_I_NameMangle.cpp, .Lfunc_end5-_GLOBAL__sub_I_NameMangle.cpp
	.cfi_endproc
                                        # -- End function
	.type	_ZStL8__ioinit,@object          # @_ZStL8__ioinit
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.hidden	__dso_handle
	.type	.L.str,@object                  # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"This is func1(int a,int b) call "
	.size	.L.str, 33

	.type	.L.str.1,@object                # @.str.1
.L.str.1:
	.asciz	"\n"
	.size	.L.str.1, 2

	.type	.L.str.2,@object                # @.str.2
.L.str.2:
	.asciz	"This is func1(int a) call "
	.size	.L.str.2, 27

	.type	.L.str.3,@object                # @.str.3
.L.str.3:
	.asciz	"This is func1(double a, float b) call "
	.size	.L.str.3, 39

	.section	.init_array,"aw",@init_array
	.p2align	3
	.quad	_GLOBAL__sub_I_NameMangle.cpp
	.ident	"clang version 12.0.1 (https://github.com/llvm/llvm-project.git fed41342a82f5a3a9201819a82bf7a48313e296b)"
	.section	".note.GNU-stack","",@progbits
