    .section .reset, "ax"
    .global _start
_start:
.option push
.option norelax
    li gp,0x400000       #   Base address of memory-mapped IO
.option pop

    li   t0,524288  # Can't use IO_HW_CONFIG_RAM(gp) (too far away !)
    add  t0,t0,gp             # Read RAM size in hw config register and
    lw   sp,0(t0)             # initialize SP at end of RAM
    li   t0,0                 # reset t0 to 0

    la      t0, trap_handler
    csrw    mtvec, t0

    la      t0, _bss_start
    la      t1, _bss_end

_bss_clear:
    sw      zero,0(t0)
    addi    t0, t0, 4
    bltu    t0, t1, _bss_clear

    la      sp, _stack
    call    main
    tail    exit

    .section .text.trap, "ax"
    .align 4
trap_handler:
    csrr    t5, mepc
    addi    t5, t5, 4
    csrw    mepc, t5
    mret

