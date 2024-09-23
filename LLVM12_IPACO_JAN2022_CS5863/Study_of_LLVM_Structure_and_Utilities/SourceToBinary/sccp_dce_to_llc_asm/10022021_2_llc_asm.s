	.text
	.file	"10022021_2.c"
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
	movabsq	$.L.str, %rdi                   # <MCInst #1772 MOV64ri
                                        #  <MCOperand Reg:53>
                                        #  <MCOperand Expr:(.L.str)>>
	movl	$620, %esi                      # <MCInst #1755 MOV32ri
                                        #  <MCOperand Reg:32>
                                        #  <MCOperand Imm:620>>
                                        # imm = 0x26C
	movb	$0, %al                         # <MCInst #1791 MOV8ri
                                        #  <MCOperand Reg:2>
                                        #  <MCOperand Imm:0>>
	callq	printf                          # <MCInst #662 CALL64pcrel32
                                        #  <MCOperand Expr:(printf)>>
	xorl	%eax, %eax                      # <MCInst #15371 XOR32rr
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:22>
                                        #  <MCOperand Reg:22>>
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
	.asciz	"%d"
	.size	.L.str, 3

	.ident	"clang version 12.0.1 (https://github.com/llvm/llvm-project.git fed41342a82f5a3a9201819a82bf7a48313e296b)"
	.section	".note.GNU-stack","",@progbits
