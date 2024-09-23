	.text
	.file	"10022021_4.c"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbp                            # <MCInst #2422 PUSH64r
                                        #  <MCOperand Reg:50>>
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp                      # <MCInst #1775 MOV64rr
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Reg:58>>
	.cfi_def_cfa_register %rbp
	subq	$64, %rsp                       # <MCInst #2897 SUB64ri8
                                        #  <MCOperand Reg:58>
                                        #  <MCOperand Reg:58>
                                        #  <MCOperand Imm:64>>
	movq	.L__const.main.St_ar, %rax      # <MCInst #1774 MOV64rm
                                        #  <MCOperand Reg:49>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Expr:(.L__const.main.St_ar)>
                                        #  <MCOperand Reg:0>>
	movq	%rax, -32(%rbp)                 # <MCInst #1767 MOV64mr
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-32>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Reg:49>>
	movq	.L__const.main.St_ar+8, %rax    # <MCInst #1774 MOV64rm
                                        #  <MCOperand Reg:49>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Expr:(.L__const.main.St_ar+8)>
                                        #  <MCOperand Reg:0>>
	movq	%rax, -24(%rbp)                 # <MCInst #1767 MOV64mr
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-24>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Reg:49>>
	movl	.L__const.main.St_ar+16, %eax   # <MCInst #1757 MOV32rm
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Expr:(.L__const.main.St_ar+16)>
                                        #  <MCOperand Reg:0>>
	movl	%eax, -16(%rbp)                 # <MCInst #1749 MOV32mr
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-16>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Reg:22>>
	movl	$20, %edi                       # <MCInst #1755 MOV32ri
                                        #  <MCOperand Reg:26>
                                        #  <MCOperand Imm:20>>
	callq	malloc                          # <MCInst #662 CALL64pcrel32
                                        #  <MCOperand Expr:(malloc)>>
	movq	%rax, %rcx                      # <MCInst #1775 MOV64rr
                                        #  <MCOperand Reg:52>
                                        #  <MCOperand Reg:49>>
	movq	%rcx, -56(%rbp)                 # 8-byte Spill
                                        # <MCInst #1767 MOV64mr
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-56>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Reg:52>>
	movl	$10, (%rax)                     # <MCInst #1748 MOV32mi
                                        #  <MCOperand Reg:49>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:0>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:10>>
	movl	$20, 4(%rax)                    # <MCInst #1748 MOV32mi
                                        #  <MCOperand Reg:49>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:4>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:20>>
	movl	$30, 8(%rax)                    # <MCInst #1748 MOV32mi
                                        #  <MCOperand Reg:49>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:8>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:30>>
	movl	$40, 12(%rax)                   # <MCInst #1748 MOV32mi
                                        #  <MCOperand Reg:49>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:12>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:40>>
	movl	$50, 16(%rax)                   # <MCInst #1748 MOV32mi
                                        #  <MCOperand Reg:49>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:16>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:50>>
	movabsq	$.L.str, %rdi                   # <MCInst #1772 MOV64ri
                                        #  <MCOperand Reg:53>
                                        #  <MCOperand Expr:(.L.str)>>
	movl	$100, %ecx                      # <MCInst #1755 MOV32ri
                                        #  <MCOperand Reg:25>
                                        #  <MCOperand Imm:100>>
	movl	%ecx, %esi                      # <MCInst #1758 MOV32rr
                                        #  <MCOperand Reg:32>
                                        #  <MCOperand Reg:25>>
	movl	%ecx, %edx                      # <MCInst #1758 MOV32rr
                                        #  <MCOperand Reg:27>
                                        #  <MCOperand Reg:25>>
	movb	$0, %al                         # <MCInst #1791 MOV8ri
                                        #  <MCOperand Reg:2>
                                        #  <MCOperand Imm:0>>
	callq	printf                          # <MCInst #662 CALL64pcrel32
                                        #  <MCOperand Expr:(printf)>>
	xorl	%eax, %eax                      # <MCInst #15371 XOR32rr
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:22>>
	movl	%eax, -44(%rbp)                 # 4-byte Spill
                                        # <MCInst #1749 MOV32mr
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-44>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Reg:22>>
.LBB0_1:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	movl	-44(%rbp), %eax                 # 4-byte Reload
                                        # <MCInst #1757 MOV32rm
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-44>
                                        #  <MCOperand Reg:0>>
	movl	%eax, -60(%rbp)                 # 4-byte Spill
                                        # <MCInst #1749 MOV32mr
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-60>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Reg:22>>
	cmpl	$5, %eax                        # <MCInst #766 CMP32ri8
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Imm:5>>
	jge	.LBB0_4                         # <MCInst #1228 JCC_1
                                        #  <MCOperand Expr:(.LBB0_4)>
                                        #  <MCOperand Imm:13>>
# %bb.2:                                # %for.body
                                        #   in Loop: Header=BB0_1 Depth=1
	movq	-56(%rbp), %rax                 # 8-byte Reload
                                        # <MCInst #1774 MOV64rm
                                        #  <MCOperand Reg:49>
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-56>
                                        #  <MCOperand Reg:0>>
	movl	-60(%rbp), %ecx                 # 4-byte Reload
                                        # <MCInst #1757 MOV32rm
                                        #  <MCOperand Reg:25>
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-60>
                                        #  <MCOperand Reg:0>>
	movslq	%ecx, %rdx                      # <MCInst #1896 MOVSX64rr32
                                        #  <MCOperand Reg:54>
                                        #  <MCOperand Reg:25>>
	movl	-32(%rbp,%rdx,4), %esi          # <MCInst #1757 MOV32rm
                                        #  <MCOperand Reg:32>
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:4>
                                        #  <MCOperand Reg:54>
                                        #  <MCOperand Imm:-32>
                                        #  <MCOperand Reg:0>>
	movslq	%ecx, %rcx                      # <MCInst #1896 MOVSX64rr32
                                        #  <MCOperand Reg:52>
                                        #  <MCOperand Reg:25>>
	addl	(%rax,%rcx,4), %esi             # <MCInst #367 ADD32rm
                                        #  <MCOperand Reg:32>
                                        #  <MCOperand Reg:32>
                                        #  <MCOperand Reg:49>
                                        #  <MCOperand Imm:4>
                                        #  <MCOperand Reg:52>
                                        #  <MCOperand Imm:0>
                                        #  <MCOperand Reg:0>>
	movabsq	$.L.str.1, %rdi                 # <MCInst #1772 MOV64ri
                                        #  <MCOperand Reg:53>
                                        #  <MCOperand Expr:(.L.str.1)>>
	movb	$0, %al                         # <MCInst #1791 MOV8ri
                                        #  <MCOperand Reg:2>
                                        #  <MCOperand Imm:0>>
	callq	printf                          # <MCInst #662 CALL64pcrel32
                                        #  <MCOperand Expr:(printf)>>
# %bb.3:                                # %for.inc
                                        #   in Loop: Header=BB0_1 Depth=1
	movl	-60(%rbp), %eax                 # 4-byte Reload
                                        # <MCInst #1757 MOV32rm
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-60>
                                        #  <MCOperand Reg:0>>
	addl	$1, %eax                        # <MCInst #366 ADD32ri8
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Imm:1>>
	movl	%eax, -44(%rbp)                 # 4-byte Spill
                                        # <MCInst #1749 MOV32mr
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-44>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Reg:22>>
	jmp	.LBB0_1                         # <MCInst #1247 JMP_1
                                        #  <MCOperand Expr:(.LBB0_1)>>
.LBB0_4:                                # %for.end
	movl	$1000, -40(%rbp)                # <MCInst #1748 MOV32mi
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-40>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:1000>>
                                        # imm = 0x3E8
	movl	-40(%rbp), %esi                 # <MCInst #1757 MOV32rm
                                        #  <MCOperand Reg:32>
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-40>
                                        #  <MCOperand Reg:0>>
	movabsq	$.L.str.2, %rdi                 # <MCInst #1772 MOV64ri
                                        #  <MCOperand Reg:53>
                                        #  <MCOperand Expr:(.L.str.2)>>
	movb	$0, %al                         # <MCInst #1791 MOV8ri
                                        #  <MCOperand Reg:2>
                                        #  <MCOperand Imm:0>>
	callq	printf                          # <MCInst #662 CALL64pcrel32
                                        #  <MCOperand Expr:(printf)>>
	xorl	%eax, %eax                      # <MCInst #15371 XOR32rr
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:22>>
	addq	$64, %rsp                       # <MCInst #375 ADD64ri8
                                        #  <MCOperand Reg:58>
                                        #  <MCOperand Reg:58>
                                        #  <MCOperand Imm:64>>
	popq	%rbp                            # <MCInst #2278 POP64r
                                        #  <MCOperand Reg:50>>
	.cfi_def_cfa %rsp, 8
	retq                                    # <MCInst #2548 RETQ>
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	.L__const.main.St_ar,@object    # @__const.main.St_ar
	.section	.rodata,"a",@progbits
	.p2align	4
.L__const.main.St_ar:
	.long	1                               # 0x1
	.long	2                               # 0x2
	.long	3                               # 0x3
	.long	4                               # 0x4
	.long	5                               # 0x5
	.size	.L__const.main.St_ar, 20

	.type	.L.str,@object                  # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	" %d %d %d"
	.size	.L.str, 10

	.type	.L.str.1,@object                # @.str.1
.L.str.1:
	.asciz	"%d "
	.size	.L.str.1, 4

	.type	.L.str.2,@object                # @.str.2
.L.str.2:
	.asciz	"%d"
	.size	.L.str.2, 3

	.ident	"clang version 12.0.1 (https://github.com/llvm/llvm-project.git fed41342a82f5a3a9201819a82bf7a48313e296b)"
	.section	".note.GNU-stack","",@progbits
