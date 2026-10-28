/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright © 2026 The mipsx-sdk authors
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * setjmp and longjmp for MIPS-X (the ES3890).
 *
 * jmp_buf holds the registers a call preserves (mipsx-sdk docs/abi.md
 * §7.4, §13.7): r16-r22, r25-r27, sp (r29), fp (r30) and the return
 * address r31, a word address.  r23, r24 and r28 never change after
 * start-up, so they are not saved.  Arguments are in r4 and r5 and the
 * result in r2 (abi §7).  Every jump below has its two delay slots, and
 * no instruction reads a register loaded by the one before it (abi §9).
 */

#include <picolibc.h>

	.text

	.globl	setjmp
	.type	setjmp,@function
setjmp:
	st	0[r4],r16
	st	4[r4],r17
	st	8[r4],r18
	st	12[r4],r19
	st	16[r4],r20
	st	20[r4],r21
	st	24[r4],r22
	st	28[r4],r25
	st	32[r4],r26
	st	36[r4],r27
	st	40[r4],sp
	st	44[r4],fp
	st	48[r4],ra
	jspci	ra,#0,r0
	mov	r0,r2			/* delay slot 1: return 0 */
	nop				/* delay slot 2 */
	.size	setjmp, . - setjmp

	.globl	longjmp
	.type	longjmp,@function
longjmp:
	ld	0[r4],r16
	ld	4[r4],r17
	ld	8[r4],r18
	ld	12[r4],r19
	ld	16[r4],r20
	ld	20[r4],r21
	ld	24[r4],r22
	ld	28[r4],r25
	ld	32[r4],r26
	ld	36[r4],r27
	ld	40[r4],sp
	ld	44[r4],fp
	ld	48[r4],ra
	mov	r5,r2			/* return val, or 1 if val is 0 */
	bne	r2,r0,1f
	nop
	nop
	addi	r0,#1,r2
1:
	jspci	ra,#0,r0
	nop
	nop
	.size	longjmp, . - longjmp
