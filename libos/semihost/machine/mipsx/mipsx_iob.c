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

#include <stdio.h>
#include "mipsx-semihost.h"

static int
mipsx_putc(char c, FILE *file)
{
    (void)file;
    MIPSX_IO_PUTC = (unsigned char)c;
    return (unsigned char)c;
}

static int
mipsx_putc_err(char c, FILE *file)
{
    (void)file;
    MIPSX_IO_PUTERR = (unsigned char)c;
    return (unsigned char)c;
}

static int
mipsx_getc(FILE *file)
{
    int c = MIPSX_IO_GETC;

    (void)file;
    if (c < 0)
        return EOF;
    return (unsigned char)c;
}

static FILE __stdio = FDEV_SETUP_STREAM(mipsx_putc, mipsx_getc, NULL, _FDEV_SETUP_RW);
static FILE __stderr = FDEV_SETUP_STREAM(mipsx_putc_err, NULL, NULL, _FDEV_SETUP_WRITE);

FILE * const stdin = &__stdio;
#ifdef __strong_reference
__strong_reference(stdin, stdout);
#else
FILE * const stdout = &__stdio;
#endif
FILE * const stderr = &__stderr;
