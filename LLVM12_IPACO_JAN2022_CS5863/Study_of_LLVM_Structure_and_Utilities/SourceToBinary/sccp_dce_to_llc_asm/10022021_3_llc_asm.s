	.text
	.file	"10022021_3.c"
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
	subq	$48, %rsp                       # <MCInst #2897 SUB64ri8
                                        #  <MCOperand Reg:58>
                                        #  <MCOperand Reg:58>
                                        #  <MCOperand Imm:48>>
	xorl	%eax, %eax                      # <MCInst #15371 XOR32rr
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:22>>
	movl	%eax, %ecx                      # <MCInst #1758 MOV32rr
                                        #  <MCOperand Reg:25>
                                        #  <MCOperand Reg:22>>
	movl	%ecx, -8(%rbp)                  # 4-byte Spill
                                        # <MCInst #1749 MOV32mr
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-8>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Reg:25>>
	movl	%eax, -4(%rbp)                  # 4-byte Spill
                                        # <MCInst #1749 MOV32mr
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-4>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Reg:22>>
	jmp	.LBB0_1                         # <MCInst #1247 JMP_1
                                        #  <MCOperand Expr:(.LBB0_1)>>
.LBB0_1:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	movl	-8(%rbp), %eax                  # 4-byte Reload
                                        # <MCInst #1757 MOV32rm
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-8>
                                        #  <MCOperand Reg:0>>
	movl	-4(%rbp), %ecx                  # 4-byte Reload
                                        # <MCInst #1757 MOV32rm
                                        #  <MCOperand Reg:25>
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-4>
                                        #  <MCOperand Reg:0>>
	movl	%ecx, -16(%rbp)                 # 4-byte Spill
                                        # <MCInst #1749 MOV32mr
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-16>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Reg:25>>
	movl	%eax, -12(%rbp)                 # 4-byte Spill
                                        # <MCInst #1749 MOV32mr
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-12>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Reg:22>>
	cmpl	$10, %eax                       # <MCInst #766 CMP32ri8
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Imm:10>>
	jge	.LBB0_4                         # <MCInst #1228 JCC_1
                                        #  <MCOperand Expr:(.LBB0_4)>
                                        #  <MCOperand Imm:13>>
# %bb.2:                                # %for.body
                                        #   in Loop: Header=BB0_1 Depth=1
	movl	-12(%rbp), %ecx                 # 4-byte Reload
                                        # <MCInst #1757 MOV32rm
                                        #  <MCOperand Reg:25>
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-12>
                                        #  <MCOperand Reg:0>>
	movl	-16(%rbp), %eax                 # 4-byte Reload
                                        # <MCInst #1757 MOV32rm
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-16>
                                        #  <MCOperand Reg:0>>
	addl	%ecx, %eax                      # <MCInst #368 ADD32rr
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:25>>
	movl	%eax, -20(%rbp)                 # 4-byte Spill
                                        # <MCInst #1749 MOV32mr
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-20>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Reg:22>>
# %bb.3:                                # %for.inc
                                        #   in Loop: Header=BB0_1 Depth=1
	movl	-20(%rbp), %eax                 # 4-byte Reload
                                        # <MCInst #1757 MOV32rm
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-20>
                                        #  <MCOperand Reg:0>>
	movl	-12(%rbp), %ecx                 # 4-byte Reload
                                        # <MCInst #1757 MOV32rm
                                        #  <MCOperand Reg:25>
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-12>
                                        #  <MCOperand Reg:0>>
	movl	%ecx, %edx                      # <MCInst #1758 MOV32rr
                                        #  <MCOperand Reg:27>
                                        #  <MCOperand Reg:25>>
	addl	$1, %edx                        # <MCInst #366 ADD32ri8
                                        #  <MCOperand Reg:27>
                                        #  <MCOperand Reg:27>
                                        #  <MCOperand Imm:1>>
	addl	%edx, %ecx                      # <MCInst #368 ADD32rr
                                        #  <MCOperand Reg:25>
                                        #  <MCOperand Reg:25>
                                        #  <MCOperand Reg:27>>
	movl	%ecx, -8(%rbp)                  # 4-byte Spill
                                        # <MCInst #1749 MOV32mr
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-8>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Reg:25>>
	movl	%eax, -4(%rbp)                  # 4-byte Spill
                                        # <MCInst #1749 MOV32mr
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-4>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Reg:22>>
	jmp	.LBB0_1                         # <MCInst #1247 JMP_1
                                        #  <MCOperand Expr:(.LBB0_1)>>
.LBB0_4:                                # %for.end
	movl	-16(%rbp), %esi                 # 4-byte Reload
                                        # <MCInst #1757 MOV32rm
                                        #  <MCOperand Reg:32>
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-16>
                                        #  <MCOperand Reg:0>>
	movabsq	$.L.str, %rdi                   # <MCInst #1772 MOV64ri
                                        #  <MCOperand Reg:53>
                                        #  <MCOperand Expr:(.L.str)>>
	movb	$0, %al                         # <MCInst #1791 MOV8ri
                                        #  <MCOperand Reg:2>
                                        #  <MCOperand Imm:0>>
	callq	printf                          # <MCInst #662 CALL64pcrel32
                                        #  <MCOperand Expr:(printf)>>
	xorl	%eax, %eax                      # <MCInst #15371 XOR32rr
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:22>>
	movl	%eax, -24(%rbp)                 # 4-byte Spill
                                        # <MCInst #1749 MOV32mr
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-24>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Reg:22>>
.LBB0_5:                                # %while.cond
                                        # =>This Inner Loop Header: Depth=1
	movl	-12(%rbp), %eax                 # 4-byte Reload
                                        # <MCInst #1757 MOV32rm
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-12>
                                        #  <MCOperand Reg:0>>
	movl	-24(%rbp), %ecx                 # 4-byte Reload
                                        # <MCInst #1757 MOV32rm
                                        #  <MCOperand Reg:25>
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-24>
                                        #  <MCOperand Reg:0>>
	movl	%ecx, -28(%rbp)                 # 4-byte Spill
                                        # <MCInst #1749 MOV32mr
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-28>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Reg:25>>
	cmpl	$10, %eax                       # <MCInst #766 CMP32ri8
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Imm:10>>
	jge	.LBB0_7                         # <MCInst #1228 JCC_1
                                        #  <MCOperand Expr:(.LBB0_7)>
                                        #  <MCOperand Imm:13>>
# %bb.6:                                # %while.body
                                        #   in Loop: Header=BB0_5 Depth=1
	movl	-28(%rbp), %eax                 # 4-byte Reload
                                        # <MCInst #1757 MOV32rm
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-28>
                                        #  <MCOperand Reg:0>>
	subl	$2, %eax                        # <MCInst #2888 SUB32ri8
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Imm:2>>
	movl	%eax, -24(%rbp)                 # 4-byte Spill
                                        # <MCInst #1749 MOV32mr
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-24>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Reg:22>>
	jmp	.LBB0_5                         # <MCInst #1247 JMP_1
                                        #  <MCOperand Expr:(.LBB0_5)>>
.LBB0_7:                                # %while.end
	movl	-28(%rbp), %esi                 # 4-byte Reload
                                        # <MCInst #1757 MOV32rm
                                        #  <MCOperand Reg:32>
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-28>
                                        #  <MCOperand Reg:0>>
	movabsq	$.L.str.1, %rdi                 # <MCInst #1772 MOV64ri
                                        #  <MCOperand Reg:53>
                                        #  <MCOperand Expr:(.L.str.1)>>
	movb	$0, %al                         # <MCInst #1791 MOV8ri
                                        #  <MCOperand Reg:2>
                                        #  <MCOperand Imm:0>>
	callq	printf                          # <MCInst #662 CALL64pcrel32
                                        #  <MCOperand Expr:(printf)>>
.LBB0_8:                                # %do.body
                                        # =>This Inner Loop Header: Depth=1
	jmp	.LBB0_9                         # <MCInst #1247 JMP_1
                                        #  <MCOperand Expr:(.LBB0_9)>>
.LBB0_9:                                # %do.cond
                                        #   in Loop: Header=BB0_8 Depth=1
	movl	-12(%rbp), %eax                 # 4-byte Reload
                                        # <MCInst #1757 MOV32rm
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-12>
                                        #  <MCOperand Reg:0>>
	cmpl	$10, %eax                       # <MCInst #766 CMP32ri8
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Imm:10>>
	jl	.LBB0_8                         # <MCInst #1228 JCC_1
                                        #  <MCOperand Expr:(.LBB0_8)>
                                        #  <MCOperand Imm:12>>
# %bb.10:                               # %do.end
	movabsq	$.L.str.2, %rdi                 # <MCInst #1772 MOV64ri
                                        #  <MCOperand Reg:53>
                                        #  <MCOperand Expr:(.L.str.2)>>
	xorl	%esi, %esi                      # <MCInst #15371 XOR32rr
                                        #  <MCOperand Reg:32>
                                        #  <MCOperand Reg:32>
                                        #  <MCOperand Reg:32>>
	movb	$0, %al                         # <MCInst #1791 MOV8ri
                                        #  <MCOperand Reg:2>
                                        #  <MCOperand Imm:0>>
	callq	printf                          # <MCInst #662 CALL64pcrel32
                                        #  <MCOperand Expr:(printf)>>
                                        # kill: def $ecx killed $eax
	movl	-12(%rbp), %eax                 # 4-byte Reload
                                        # <MCInst #1757 MOV32rm
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-12>
                                        #  <MCOperand Reg:0>>
	movl	%eax, -32(%rbp)                 # 4-byte Spill
                                        # <MCInst #1749 MOV32mr
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-32>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Reg:22>>
.LBB0_11:                               # %l1
                                        # =>This Inner Loop Header: Depth=1
	movl	-32(%rbp), %eax                 # 4-byte Reload
                                        # <MCInst #1757 MOV32rm
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-32>
                                        #  <MCOperand Reg:0>>
	movl	%eax, -36(%rbp)                 # 4-byte Spill
                                        # <MCInst #1749 MOV32mr
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-36>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Reg:22>>
	cmpl	$10, %eax                       # <MCInst #766 CMP32ri8
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Imm:10>>
	jge	.LBB0_13                        # <MCInst #1228 JCC_1
                                        #  <MCOperand Expr:(.LBB0_13)>
                                        #  <MCOperand Imm:13>>
# %bb.12:                               # %if.then
                                        #   in Loop: Header=BB0_11 Depth=1
	movl	-36(%rbp), %esi                 # 4-byte Reload
                                        # <MCInst #1757 MOV32rm
                                        #  <MCOperand Reg:32>
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-36>
                                        #  <MCOperand Reg:0>>
	movabsq	$.L.str.3, %rdi                 # <MCInst #1772 MOV64ri
                                        #  <MCOperand Reg:53>
                                        #  <MCOperand Expr:(.L.str.3)>>
	movb	$0, %al                         # <MCInst #1791 MOV8ri
                                        #  <MCOperand Reg:2>
                                        #  <MCOperand Imm:0>>
	callq	printf                          # <MCInst #662 CALL64pcrel32
                                        #  <MCOperand Expr:(printf)>>
                                        # kill: def $ecx killed $eax
	movl	-36(%rbp), %eax                 # 4-byte Reload
                                        # <MCInst #1757 MOV32rm
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-36>
                                        #  <MCOperand Reg:0>>
	addl	$2, %eax                        # <MCInst #366 ADD32ri8
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Imm:2>>
	movl	%eax, -40(%rbp)                 # 4-byte Spill
                                        # <MCInst #1749 MOV32mr
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-40>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Reg:22>>
	jmp	.LBB0_14                        # <MCInst #1247 JMP_1
                                        #  <MCOperand Expr:(.LBB0_14)>>
.LBB0_13:                               # %if.else
	jmp	.LBB0_15                        # <MCInst #1247 JMP_1
                                        #  <MCOperand Expr:(.LBB0_15)>>
.LBB0_14:                               # %if.end
                                        #   in Loop: Header=BB0_11 Depth=1
	movl	-40(%rbp), %eax                 # 4-byte Reload
                                        # <MCInst #1757 MOV32rm
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-40>
                                        #  <MCOperand Reg:0>>
	movl	%eax, -32(%rbp)                 # 4-byte Spill
                                        # <MCInst #1749 MOV32mr
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-32>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Reg:22>>
	jmp	.LBB0_11                        # <MCInst #1247 JMP_1
                                        #  <MCOperand Expr:(.LBB0_11)>>
.LBB0_15:                               # %l2
	xorl	%eax, %eax                      # <MCInst #15371 XOR32rr
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:22>>
	addq	$48, %rsp                       # <MCInst #375 ADD64ri8
                                        #  <MCOperand Reg:58>
                                        #  <MCOperand Reg:58>
                                        #  <MCOperand Imm:48>>
	popq	%rbp                            # <MCInst #2278 POP64r
                                        #  <MCOperand Reg:50>>
	.cfi_def_cfa %rsp, 8
	retq                                    # <MCInst #2548 RETQ>
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	.L.str,@object                  # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	" For loop work %d"
	.size	.L.str, 18

	.type	.L.str.1,@object                # @.str.1
.L.str.1:
	.asciz	" while loop work %d"
	.size	.L.str.1, 20

	.type	.L.str.2,@object                # @.str.2
.L.str.2:
	.asciz	" do-while loop work %d"
	.size	.L.str.2, 23

	.type	.L.str.3,@object                # @.str.3
.L.str.3:
	.asciz	" goto %d"
	.size	.L.str.3, 9

	.ident	"clang version 12.0.1 (https://github.com/llvm/llvm-project.git fed41342a82f5a3a9201819a82bf7a48313e296b)"
	.section	".note.GNU-stack","",@progbits
