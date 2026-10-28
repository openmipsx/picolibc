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
 * The I/O page of mipsx-sim, the MIPS-X (ES3890) simulator in the
 * mipsx-sdk (docs/abi.md §13.5, sim/README.md).  The device has no such
 * page: this library is for the simulator only.
 */

#ifndef _MIPSX_SEMIHOST_H_
#define _MIPSX_SEMIHOST_H_

#include <stdint.h>

#define MIPSX_IO_PUTC    (*(volatile uint32_t *)0xffff0000) /* store: stdout */
#define MIPSX_IO_EXIT    (*(volatile uint32_t *)0xffff0004) /* store: exit */
#define MIPSX_IO_CYCLES  (*(volatile uint32_t *)0xffff0008) /* load: cycles, low */
#define MIPSX_IO_CYCLESH (*(volatile uint32_t *)0xffff000c) /* load: cycles, high */
#define MIPSX_IO_GETC    (*(volatile int32_t *)0xffff0010)  /* load: stdin or -1 */
#define MIPSX_IO_PUTERR  (*(volatile uint32_t *)0xffff0014) /* store: stderr */

#endif /* _MIPSX_SEMIHOST_H_ */
