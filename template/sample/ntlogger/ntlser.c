/**
 * @file ntlser.c
 * @author Shinichiro Nakamura
 * @brief NT-Logger$B%7%j%"%k$N<BAu!#(B
 */

/*
 * ===============================================================
 *  Natural Tiny Logger (NT-Logger)
 * ===============================================================
 * Copyright (c) 2010-2012 Shinichiro Nakamura
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 * ===============================================================
 */

#include "ntlser.h"
#include "lib.h"

#define NTL_ENABLED (0)

/**
 * @brief $B%7%j%"%k%]!<%H$r=i4|2=$9$k!#(B
 *
 * @retval 0 $B@.8y!#(B
 * @retval -1 $B<:GT!#(B
 */
int ntlser_init(void)
{
#if NTL_ENABLED
    /*
     * $B$3$N%]!<%H$G$O2?$b$7$J$$!#(B
     */
    return 0;
#else
    /*
     * $BL58z2=$5$l$F$$$k$N$G2?$b$7$J$$$G@.8y$7$?;v$K$9$k!#(B
     */
    return 0;
#endif
}

/**
 * @brief $B%7%j%"%k%]!<%H$K%G!<%?$r=q$-9~$`!#(B
 *
 * @param buf $BAw?.MW5a%G!<%?!#(B
 * @param siz $BAw?.MW5a%P%$%H?t!#(B
 *
 * @return $B<B:]$KAw?.$7$?%P%$%H?t!#(B
 */
int ntlser_write(const unsigned char *buf, const int siz)
{
#if NTL_ENABLED
    /*
     * $BAw?.$r<B9T$9$k!#(B
     */
    int i;
    for (i = 0; i < siz; i++) {
        putc(buf[i]);
    }
    return siz;
#else
    /*
     * $BL58z2=$5$l$F$$$k$N$G2?$b$7$J$$$G@.8y$7$?;v$K$9$k!#(B
     */
    return siz;
#endif
}

