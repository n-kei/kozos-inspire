/**
 * @file ntl.h
 * @author Shinichiro Nakamura
 * @brief NT-Loggerメインモジュールの定義。
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

#ifndef NTL_H
#define NTL_H

#define NTLEVT_START(TRACK,EVENT)   ntl_event_start(TRACK,EVENT)
#define NTLEVT_END(TRACK,EVENT)     ntl_event_end(TRACK,EVENT)

/**
 * @brief NT-Loggerを初期化する。
 *
 * @retval 0 成功。
 * @retval -1 失敗。
 */
int ntl_init(void);

/**
 * @brief イベント開始点を報告する。
 *
 * @param track トラック番号。
 * @param event イベント番号。
 *
 * @retval 0 成功。
 * @retval -1 失敗。
 */
int ntl_event_start(const int track, const int event);

/**
 * @brief イベント終了点を報告する。
 *
 * @param track トラック番号。
 * @param event イベント番号。
 *
 * @retval 0 成功。
 * @retval -1 失敗。
 */
int ntl_event_end(const int track, const int event);

#endif

