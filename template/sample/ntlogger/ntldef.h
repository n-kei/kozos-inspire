/**
 * @file ntldef.h
 * @author Shinichiro Nakamura
 * @brief NT-Logger共通の定義。
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

#ifndef NTLDEF_H
#define NTLDEF_H

/**
 * @brief 開始点を表現するタイプ番号。
 */
#define NTLDEF_TYPE_START   (1)

/**
 * @brief 終了点を表現するタイプ番号。
 */
#define NTLDEF_TYPE_END     (0)

/**
 * @brief パケットを生成する。
 *
 * @param TRACK トラック番号。
 * @param EVENT イベント番号。
 * @param TYPE  タイプ番号。
 *
 * @return パケット。
 */
#define NTLDEF_NTL_PACKET(TRACK, EVENT, TYPE) \
    ((((TRACK) & 0x0F) << 4) | (((EVENT) & 0x07) << 1) | (((TYPE) & 0x01) << 0))

/**
 * @brief パケットからトラック番号を得る。
 *
 * @param P パケット。
 *
 * @return トラック番号。
 */
#define NTLDEF_NTL_TRACK(P)    (((P) >> 4) & 0x0F)

/**
 * @brief パケットからイベント番号を得る。
 *
 * @param P パケット。
 *
 * @return イベント番号。
 */
#define NTLDEF_NTL_EVENT(P)    (((P) >> 1) & 0x07)

/**
 * @brief パケットからタイプ番号を得る。
 *
 * @param P パケット。
 *
 * @return タイプ番号。
 */
#define NTLDEF_NTL_TYPE(P)    (((P) >> 0) & 0x01)

#endif

