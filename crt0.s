.section .init, "ax"
.global _start
_start:
    .cfi_startproc
    .cfi_undefined ra
    .option push
    .option norelax
    la gp, __global_pointer$
    .option pop
    la sp, __stack_top
    add s0, sp, zero
    la  a5, _interrupt_handler
    csrw mtvec, a5
    jal ra, init
    csrsi mstatus, 0x8
    li a5, 0x888
    csrw mie, a5
    jal ra, main
end:
    j end
    .cfi_endproc
    .end
