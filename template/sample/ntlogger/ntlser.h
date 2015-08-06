/**
 * @file ntlser.h
 * @author Shinichiro Nakamura
 * @brief NT-Loggerシリアルの定義。
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

#ifndef NTLSER_H
#define NTLSER_H

/**
 * @brief シリアルポートを初期化する。
 *
 * @retval 0 成功。
 * @retval -1 失敗。
 */
int ntlser_init(void);

/**
 * @brief シリアルポートにデータを書き込む。
 *
 * @param buf 送信要求データ。
 * @param siz 送信要求バイト数。
 *
 * @return 実際に送信したバイト数。
 */
int ntlser_write(const unsigned char *buf, const int siz);

#endif

