	.text
	.file	"10022021_1.c"
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
	subq	$16, %rsp                       # <MCInst #2897 SUB64ri8
                                        #  <MCOperand Reg:58>
                                        #  <MCOperand Reg:58>
                                        #  <MCOperand Imm:16>>
	xorl	%eax, %eax                      # <MCInst #15371 XOR32rr
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:22>>
                                        # kill: def $al killed $al killed $eax
	testb	$1, %al                         # <MCInst #3011 TEST8i8
                                        #  <MCOperand Imm:1>>
	jne	.LBB0_1                         # <MCInst #1228 JCC_1
                                        #  <MCOperand Expr:(.LBB0_1)>
                                        #  <MCOperand Imm:5>>
	jmp	.LBB0_2                         # <MCInst #1247 JMP_1
                                        #  <MCOperand Expr:(.LBB0_2)>>
.LBB0_1:                                # %if.then
	jmp	.LBB0_3                         # <MCInst #1247 JMP_1
                                        #  <MCOperand Expr:(.LBB0_3)>>
.LBB0_2:                                # %if.else
	jmp	.LBB0_3                         # <MCInst #1247 JMP_1
                                        #  <MCOperand Expr:(.LBB0_3)>>
.LBB0_3:                                # %if.end
	movl	$7, %eax                        # <MCInst #1755 MOV32ri
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Imm:7>>
	movl	%eax, -4(%rbp)                  # 4-byte Spill
                                        # <MCInst #1749 MOV32mr
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-4>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Reg:22>>
	xorl	%eax, %eax                      # <MCInst #15371 XOR32rr
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:22>>
                                        # kill: def $al killed $al killed $eax
	testb	%al, %al                        # <MCInst #3015 TEST8rr
                                        #  <MCOperand Reg:2>
                                        #  <MCOperand Reg:2>>
	jne	.LBB0_5                         # <MCInst #1228 JCC_1
                                        #  <MCOperand Expr:(.LBB0_5)>
                                        #  <MCOperand Imm:5>>
	jmp	.LBB0_8                         # <MCInst #1247 JMP_1
                                        #  <MCOperand Expr:(.LBB0_8)>>
.LBB0_8:                                # %if.end
	movl	-4(%rbp), %eax                  # 4-byte Reload
                                        # <MCInst #1757 MOV32rm
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:50>
                                        #  <MCOperand Imm:1>
                                        #  <MCOperand Reg:0>
                                        #  <MCOperand Imm:-4>
                                        #  <MCOperand Reg:0>>
	subl	$75, %eax                       # <MCInst #2888 SUB32ri8
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Imm:75>>
	jne	.LBB0_6                         # <MCInst #1228 JCC_1
                                        #  <MCOperand Expr:(.LBB0_6)>
                                        #  <MCOperand Imm:5>>
	jmp	.LBB0_4                         # <MCInst #1247 JMP_1
                                        #  <MCOperand Expr:(.LBB0_4)>>
.LBB0_4:                                # %sw.bb
	jmp	.LBB0_5                         # <MCInst #1247 JMP_1
                                        #  <MCOperand Expr:(.LBB0_5)>>
.LBB0_5:                                # %sw.bb3
	jmp	.LBB0_6                         # <MCInst #1247 JMP_1
                                        #  <MCOperand Expr:(.LBB0_6)>>
.LBB0_6:                                # %sw.default
	movabsq	$.L.str.2, %rdi                 # <MCInst #1772 MOV64ri
                                        #  <MCOperand Reg:53>
                                        #  <MCOperand Expr:(.L.str.2)>>
	movb	$0, %al                         # <MCInst #1791 MOV8ri
                                        #  <MCOperand Reg:2>
                                        #  <MCOperand Imm:0>>
	callq	printf                          # <MCInst #662 CALL64pcrel32
                                        #  <MCOperand Expr:(printf)>>
# %bb.7:                                # %sw.epilog
	xorl	%eax, %eax                      # <MCInst #15371 XOR32rr
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:22>>
	addq	$16, %rsp                       # <MCInst #375 ADD64ri8
                                        #  <MCOperand Reg:58>
                                        #  <MCOperand Reg:58>
                                        #  <MCOperand Imm:16>>
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
	.asciz	"a is %c and c is %d "
	.size	.L.str, 21

	.type	.L.str.1,@object                # @.str.1
.L.str.1:
	.asciz	"a is not %c c is %d "
	.size	.L.str.1, 21

	.type	.L.str.2,@object                # @.str.2
.L.str.2:
	.asciz	"oops"
	.size	.L.str.2, 5

	.ident	"clang version 12.0.1 (https://github.com/llvm/llvm-project.git fed41342a82f5a3a9201819a82bf7a48313e296b)"
	.section	".note.GNU-stack","",@progbits
