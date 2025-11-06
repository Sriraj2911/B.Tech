.text
.global main

main:
	fcvt.s.w ft11, x0	# The single precision zero is stored in ft11, and is used throughout the code
    	
    	# Store the two addresses in s0 and s1
    	lui s0, 0x10000
    	addi s1, s0, 0x200
    	
    	
    	# Save the function codes
    	addi s2, x0, 0
    	addi s3, x0, 1
    	addi s4, x0, 2
    	addi s5, x0, 3
    	addi s6, x0, 4
    	
    	lw t0, 0(s0)	# This register now contains the total number of values to be computed
    	bge x0, t0, N_error	# Jump to N-error if the number of values to be computed is <=0
    	addi s0, s0, 4
    	loop:
    		beq t0, x0, exit
    		lw t1, 0(s0)
    		flw fa0, 4(s0)
    		lw a0, 8(s0)
    		addi s0, s0, 12
    		
    		bge x0, a0, FC_error	# Jump to error if the number of terms is <=0 
    		
    		# Extend the stack and store t0
    		addi sp, sp, -4
    		sw t0, 0(sp)
    		
    		beq t1, s2, e
    		beq t1, s3, s
    		beq t1, s4, c
    		beq t1, s5, l
    		beq t1, s6, i
    		jal x0, FC_error	# Jump to error if function code is not valid
    		
    		e:
    			jal ra, exp
    			jal x0, iter
    		s:
    			jal ra, sin
    			jal x0, iter
    		c:
    			jal ra, cos
    			jal x0, iter
    		l:
    			jal ra, ln
    			jal x0, iter
    		i:
    			jal ra, inv
    			jal x0, iter
    		
    		iter:
    			# Load back t0 and restore the stack
    			lw t0, 0(sp)
    			addi sp, sp, 4
    			# Store the output of the function in 0(s1)
    			fsw fa0, 0(s1)
    			addi s1, s1, 4	# Increment s1 for future storing

    			addi t0, t0, -1
    			jal x0, iter
    		
    		FC_error:
			# put NaN (0x7FC00000) into fa0
		    	lui   t2, 0x7FC00      # use t2 as a scratch register
		    	fmv.w.x fa0, t2
		    	fsw fa0, 0(s1)           # store NaN
		    	addi s1, s1, 4           # advance output pointer
			
		    	addi t0, t0, -1
		    	jal x0, iter             # go back to main loop

    		
    	N_error:
   			# put NaN (0x7FC00000) into fa0
			lui   t2, 0x7FC00
			fmv.w.x fa0, t2
			fsw fa0, 0(s1)
			
			jal x0, exit

    	exit:
    		flw ft0, -12(s1)
    		flw ft1, -8(s1)
    		flw ft2, -4(s1)
    		ecall

# exp(x, n)
# Arguments are in fa0 and a0
exp:
	# Expand the stack and store the jalr x0, x1, 0urn address
	addi sp, sp, -4
	sw ra, 0(sp)
	
	fcvt.s.w ft0, x0	# ft0 = 0.0
	fcvt.s.w fs0, x0	# fs0 = 0.0 (The result of exp will be store in this register, and then copied to fa0 at the end)
	addi a0, a0, -1		# Because nth term uses (n-1) not n
	e_loop:
		blt a0, x0, e_exit
		
		# t0 = factorial(a0)
		addi sp, sp, -4		# Extend the stack
		sw a0, 0(sp)		
		jal ra, factorial
		addi t0, a0, 0		# Copy the factorial (stored in a0) in t0
		lw a0, 0(sp)		
		addi sp, sp, 4		# Restore the stack
		
		# ft1 = pow(fa0, a0)
		addi sp, sp, -8	# Extend the stack
		sw a0, 0(sp)		
		fsw fa0, 4(sp)	
		jal ra, pow
		fadd.s ft1, fa0, ft11	# Copy the result (stored in fa0) to ft1
		lw a0, 0(sp)
		flw fa0, 4(sp)	
		addi sp, sp, 8
		
		# ft2 = ft1/t0
		fcvt.s.w ft2, t0	# Convert the factorial to a single float
		fdiv.s ft2, ft1, ft2
		
		fadd.s fs0, fs0, ft2	# Add nth term to the result
		
		addi a0, a0, -1
		jal x0, e_loop
			
	e_exit:
		fadd.s fa0, fs0, ft11	# Copy the result to fa0
		# Load back the jalr x0, x1, 0urn address and restore the stack
		lw ra, 0(sp)
		addi sp, sp, 4
		jalr x0, x1, 0
#-------------------------------------------------------------------------------------------#
# sin(x, n)
# Arguments are in fa0 and a0
sin:
	addi sp, sp, -4
	sw ra, 0(sp)
	
	fadd.s fs0, ft11, ft11
	
	s_loop:
		beq a0, x0, s_exit
		
		# t1 = factorial(t0)
		addi sp, sp, -4		# Extend the stack
		sw a0, 0(sp)
		add a0, a0, a0		# Set a0 to 2*a0-1
		addi a0, a0, -1	
		jal ra, factorial
		addi t1, a0, 0		# Copy the factorial (stored in a0) to t1
		lw a0, 0(sp)		
		addi sp, sp, 4		# Restore the stack
		
		# ft1 = pow(fa0, t0)
		addi sp, sp, -8	# Extend the stack
		sw a0, 0(sp)		
		fsw fa0, 4(sp)
		add a0, a0, a0
		addi a0, a0, -1
		jal ra, pow
		fadd.s ft1, fa0, ft11	# Copy the result (stored in fa0) to ft1
		lw a0, 0(sp)
		flw fa0, 4(sp)	
		addi sp, sp, 8
		
		# ft2 = ft1/t1
		fcvt.s.w ft2, t1
		fdiv.s ft2, ft1, ft2
		
		addi t2, x0, 2	# t2 = 2
		rem t3, a0, t2
		beq t3, x0, s_sub	# Even term => Subtract from the result
		bne t3, x0, s_add	# Odd term => Add to the result
		
		s_add:
			fadd.s fs0, fs0, ft2
			addi a0, a0, -1
			jal x0, s_loop
		s_sub:
			fsub.s fs0, fs0, ft2
			addi a0, a0, -1
			jal x0, s_loop
	
	s_exit:
		fadd.s fa0, fs0, ft11
		lw ra, 0(sp)
		addi sp, sp, 4
		jalr x0, x1, 0
	
#-------------------------------------------------------------------------------------------#
# cos(x, n)
# Arguments are in fa0 and a0
cos:
	addi sp, sp, -4
	sw ra, 0(sp)
	
	fadd.s fs0, ft11, ft11
	
	c_loop:
		beq a0, x0, c_exit
		
		# t1 = factorial(t0)
		addi sp, sp, -4		# Extend the stack
		sw a0, 0(sp)
		add a0, a0, a0		# Set a0 to 2*a0-2
		addi a0, a0, -2	
		jal ra, factorial
		addi t1, a0, 0		# Copy the factorial (stored in a0) to t1
		lw a0, 0(sp)		
		addi sp, sp, 4		# Restore the stack
		
		# ft1 = pow(fa0, t0)
		addi sp, sp, -8	# Extend the stack
		sw a0, 0(sp)		
		fsw fa0, 4(sp)
		add a0, a0, a0		# Set a0 to 2*a0-2
		addi a0, a0, -2		
		jal ra, pow
		fadd.s ft1, fa0, ft11	# Copy the result (stored in fa0) to ft1
		lw a0, 0(sp)
		flw fa0, 4(sp)	
		addi sp, sp, 8
		
		# ft2 = ft1/t1
		fcvt.s.w ft2, t1
		fdiv.s ft2, ft1, ft2
		
		addi t2, x0, 2	# t2 = 2
		rem t3, a0, t2
		beq t3, x0, c_sub	# Even term => Subtract from the result
		bne t3, x0, c_add	# Odd term => Add to the result
		
		c_add:
			fadd.s fs0, fs0, ft2
			addi a0, a0, -1
			jal x0, c_loop
		c_sub:
			fsub.s fs0, fs0, ft2
			addi a0, a0, -1
			jal x0, c_loop
	
	c_exit:
		fadd.s fa0, fs0, ft11
		lw ra, 0(sp)
		addi sp, sp, 4
		jalr x0, x1, 0
#-------------------------------------------------------------------------------------------#
# ln(1+x, n)
# Arguments are in fa0 and a0
ln:
	fge.s t0, ft11, fa0	# Jump to the label which handles 'out of bound' values of x
	bne t0, x0, l_OOB
	
	addi sp, sp, -4
	sw ra, 0(sp)
	
	addi t0, x0, -1		# t0 = -1
	fcvt.s.w ft0, t0	# ft0 = -1.0
	fadd.s fa0, fa0, ft0	# fa0 = x-1, since the expansion is for ln(1+x)
	fsub.s fa0, ft11, fa0	# fa0 = -x
	fcvt.s.w fs0, x0	# The result of ln will be stored in this register and copied to fa0 at the end
	
	l_loop:
		beq a0, x0, l_exit
		# Extend the stack and store a0 and fa0 
		addi sp, sp, -8
		sw a0, 0(sp)
		fsw fa0, 4(sp)
		# ft0 = pow(fa0, a0)
		jal ra, pow
		fadd.s ft0, fa0, ft11	# Copy the output of pow to ft0
		# Load the values and restore the stack
		lw a0, 0(sp)
		flw fa0, 4(sp)
		addi sp, sp, 8
		
		# ft2 = ft0/a0
		fcvt.s.w ft2, a0
		fdiv.s ft2, ft0, ft2
		fadd.s fs0, fs0, ft2	# Add the term to the fs0
		
		addi a0, a0, -1
		jal x0, l_loop
	
	l_exit:
		fsub.s fa0, ft11, fs0	# Copy the result to fa0
		# Load back the jalr x0, x1, 0urn address and restore the stack
		lw ra, 0(sp)
		addi sp, sp, 4
		jalr x0, x1, 0
	
	l_OOB:
		lui t2, 0x7fc00
    		fmv.w.x fa0, t0
		jalr x0, x1, 0
	
	
#-------------------------------------------------------------------------------------------#
# inv(x, n)
# Arguments are in fa0 and a0
inv:
	# Output NaN if x is not in (0, 2)
	fge.s t0, ft11, fa0
	bne t0, x0, i_OOB
	addi t1, x0, 2
	fcvt.s.w ft0, t1	# ft0 = 2.0
	fge.s t0, fa0, ft0
	bne t0, x0, i_OOB
	
	addi t1, x0, 1
	fcvt.s.w ft0, t1	# ft0 = 1.0
	feq.s t0, fa0, ft0
	bne t0, x0, i_one
	
	addi sp, sp, -4
	sw ra, 0(sp)
	
	addi t0, x0, 1
	fcvt.s.w ft0, t0	# ft0 = 1.0
	fsub.s fa0, ft0, fa0	# x -> 1-x
	addi a0, a0, -1		# Since the nth term uses (n-1), not n
	
	fadd.s fs0, ft11, ft11 	# The result will be stored in fs0, which will later be copied to fa0
	
	i_loop:
		blt a0, x0, i_exit
		# Extend the stack and store a0 and fa0
		addi sp, sp, -8
		sw a0, 0(sp)
		fsw fa0, 4(sp)
		jal ra, pow
		fadd.s fs0, fs0, fa0	# Add the result of pow to the accumulator term
		# Load the values and restore the stack
		lw a0, 0(sp)
		flw fa0, 4(sp)
		addi sp, sp, 8
		
		addi a0, a0, -1
		jal x0, i_loop
		
	i_exit:
		fadd.s fa0, fs0, ft11
		lw ra, 0(sp)
		addi sp, sp, 4
		jalr x0, x1, 0
	
	i_one:
		jalr x0, x1, 0
	
	i_OOB:
		lui t2, 0x7fc00
    		fmv.w.x fa0, t0
		jalr x0, x1, 0
	

#-------------------------------------------------------------------------------------------#
# factorial(n)
# Argument in a0
factorial:
	addi t0, x0, 1		# t0 = 1 (accumulator)
	addi t1, x0, 2		# t1 = 2 (multiplier)
	f_loop:
		blt a0, t1, f_exit
		mul t0, t0, t1
		addi t1, t1, 1
		jal x0, f_loop
	f_exit:
		addi a0, t0, 0		# Copy the result to a0
		jalr x0, x1, 0

#-------------------------------------------------------------------------------------------#
# pow(a, b) = a^b
# Arguments are in fa0 and a0
pow:
	# Directly jump to the exit if a = 0.0
	fcvt.s.w ft0, x0	# ft0 = 0.0
	feq.s t5, fa0, ft0	# t5 = (fa0 == ft0) ? 1 : 0
	bne t5, x0, p_exit
	
	# Directly jump to the exit if a = 1.0
	addi t5, x0, 1
	fcvt.s.w ft0, t5	# ft0 = 1.0
	feq.s t5, fa0, ft0	# t5 = (fa0 == ft0) ? 1 : 0
	bne t5, x0, p_exit
	
	# Code for a != 0.0 and a != 1.0
	addi t6, x0, 1
	fcvt.s.w ft0, t6	# ft0 = 1.0
	
	p_loop:
		bge x0, a0, p_exit	# Exit the loop if a0 <= 0
		fmul.s ft0, ft0, fa0	# result *= a
		addi a0, a0, -1		# a0 -= 1
		jal x0, p_loop
			
	p_exit:
		fadd.s fa0, ft0, ft11	# Copy the result to fa0
		jalr x0, x1, 0



	
		
