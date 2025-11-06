lui s1, 0x10000 # Load the base address for inputs in s1
addi s2, s1, 512 # Load the base address for outputs in s2 (s2 = s1 + 0x200)

ld t0, 0(s1) # Load count_of_gcd in t0 from the base address
addi s1, s1, 8
   
count:
    # exit if count_of_gcd = 0
    beq t0, x0, exit
    # Load inputx1 in t1
    ld t1, 0(s1)
    addi s1, s1, 8
    # Load inputx2 in t2
    ld t2, 0(s1)
    addi s1, s1, 8
        
    # Extend the stack and store the temporaries
    addi sp, sp, -24
    sd t0, 0(sp)
    sd t1, 8(sp)
    sd t2, 16(sp)
        
    # Store the return address in x1 and jump to gcd
    jal x1, gcd
        
    # Store the result of the gcd funtion in s2
    sd x10, 0(s2)
    # Increment in s2 by 8 for suitable storing of the next gcd value
    addi s2, s2, 8
        
    # Load back the previously caller-stored values
    ld t0, 0(sp)
    ld t1, 8(sp)
    ld t2, 16(sp)
    addi sp, sp, 24
        
    # A counter for the number of gcd calls
    addi t0, t0, -1
    j count
    
exit:
    beq x0, x0, exit

gcd:
    # Copy inputx1 and inputx2 into the args
    addi a0, t1, 0
    addi a1, t2, 0
    
    # Return 0 if either of the arguments are 0
    beq a0, x0, zero
    beq a1, a0, zero
    # Directly return a0 if both the arguments are equal
    beq a0, a1, exit_gcd

    while:
        beq a1, x0, exit_gcd  # Exit if b = 0
        add t0, x0, a1        # temp = b
        # Store the return address in t1 and jump to remainder
        jal t1, remainder
        addi a1, a0, 0        # b = a%b
        addi a0, t0, 0        # a = b
        j while

    remainder:
        blt a0, a1, rem_exit
        sub a0, a0, a1
        j remainder
    rem_exit:
        jalr x0, t1, 0    # The remainder is stored in a0

    zero:
        # Set the result (x10) as 0
        add x10, x0, x0
        j exit_gcd

    exit_gcd:
        jalr x0, x1, 0