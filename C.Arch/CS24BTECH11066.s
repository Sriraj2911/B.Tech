
.text
.globl _start

_start:
    # Set up base address for LED matrix (from your config: 0xf0000000)
    lui t0, 0xf0000        # t0 = base address upper 20 bits
    addi t0, t0, 0x000     # t0 = 0xf0000000
    
    # Reverting all the LEDs back to black
    sw x0, 0(t0)
    sw x0, 4(t0)
    sw x0, 8(t0)
    
    # Green => 0x00FF00
    # Red => 0xFF0000
    # Blue => 0x0000FF
    
    L:
        li t1, 0x00FF00        # Green
        sw t1, 0(t0)
        
        li t4, 1    # ON time
        loopON:
            addi t4, t4, -1
            bge t4, x0, loopON
    
        sw x0, 0(t0)
        
        li t5, 5    # OFF time
        loopOFF:
            addi t5, t5, -1
            bge t5, x0, loopOFF
        
        j L
