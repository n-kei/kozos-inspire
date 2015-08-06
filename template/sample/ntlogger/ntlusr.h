/**
 * @file ntluser.h
 * @author Shinichiro Nakamura
 * @brief NT-Loggerユーザの定義。
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

#ifndef NTLUSR_H
#define NTLUSR_H

/*
 * トラックの定義。
 */
#define NTLUSR_TRACK_AUDIO      (0)
#define NTLUSR_TRACK_DISPLAY    (1)
#define NTLUSR_TRACK_MENU       (2)
#define NTLUSR_TRACK_INPUT      (3)
#define NTLUSR_TRACK_COMMAND    (4)
#define NTLUSR_TRACK_FILEIO     (5)

/*
 * オーディオトラックのイベント。
 */
#define NTLUSR_EVENT_AUDIO_PLAY     (0)
#define NTLUSR_EVENT_AUDIO_CANCEL   (1)
#define NTLUSR_EVENT_AUDIO_VOLUME   (2)

/*
 * ディスプレイトラックのイベント。
 */
#define NTLUSR_EVENT_DISPLAY_CLEAR      (0)
#define NTLUSR_EVENT_DISPLAY_DRAWBOX    (1)
#define NTLUSR_EVENT_DISPLAY_DRAWLOGO   (2)
#define NTLUSR_EVENT_DISPLAY_DRAWTEXT   (3)
#define NTLUSR_EVENT_DISPLAY_DRAWPROG   (4)
#define NTLUSR_EVENT_DISPLAY_LEDON      (5)
#define NTLUSR_EVENT_DISPLAY_LEDOFF     (6)
#define NTLUSR_EVENT_DISPLAY_LEDTOGGLE  (7)

/*
 * メニュートラックのイベント。
 */
#define NTLUSR_EVENT_MENU_FILENAME  (0)
#define NTLUSR_EVENT_MENU_LOCATION  (1)
#define NTLUSR_EVENT_MENU_ROTARY    (2)
#define NTLUSR_EVENT_MENU_SWITCH    (3)
#define NTLUSR_EVENT_MENU_REMOTE    (4)

/*
 * インプットトラックのイベント。
 */

/*
 * コマンドトラックのイベント。
 */

/*
 * ファイルI/Oトラックのイベント。
 */
#define NTLUSR_EVENT_FILEIO_READING (0)
#define NTLUSR_EVENT_FILEIO_OTHERS  (1)

#endif

