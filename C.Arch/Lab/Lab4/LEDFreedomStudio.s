.data
L1: .word 100000    # Delay between ON and OFF

.text
.global main

main:
    lui s0, 0x10012
    addi s0, s0, 0x004    # s0 = 0x10012004
    sw x0, 0(s0)          # 0x00 @ s0
    addi t0, x0, 0x20
    sw t0, 4(s0)          # 0x20 @ s0+4
    
    addi t0, x0, 0x20     # 0x20 => ON
    addi t1, x0, 0x00     # 0x00 => OFF

    addi t2, x0, 100      # To maintain the number of blinks

    loop:
        lw t0, 8(s0)    # ON
        la x3, L1
        ON:
            addi x3, x3, -1
            bge x3, x0, ON
    
        lw t1, 8(s0)    # OFF
        la x3, L1
        OFF:
            addi x3, x3, -1
            bge x3, x0, OFF
    
        addi t2, t2, -1
        bge t2, x0, loop

