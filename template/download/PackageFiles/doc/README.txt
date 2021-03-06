
=============================================
 KOZOS H8/3069F Flash Writer.
 Copyright(C) 2011-2012 Shinichiro Nakamura
=============================================

KOZOS H8/3069F Flash WriterはKOZOS本を楽しむために
H8/3069Fを手にしたけど、有名なh8writeでは書き込みに
失敗するという方のために作られたフラッシュライタです。

Makefile            メイクファイル
README.txt          このファイル
kz_h8write.c        本体用ソースコード
kz_h8write.h        本体用ヘッダファイル
mot.c               motファイル読み込みモジュールの実装
mot.h               motファイル読み込みモジュールのインターフェース
motdump.c           motファイルダンププログラムの実装
serial_linux.c      シリアルポートライブラリの実装(Linux)
serial_windows.c    シリアルポートライブラリの実装(Windows)
serial.h            シリアルポートライブラリのインターフェース

=======================================
 使い方
=======================================
 motファイル名、ボードクロック[MHz]、シリアルポート名を与えて実行します。

 例) kz_h8write -3069 -f20 kzload.mot /dev/ttyUSB0  (Linux)
 例) kz_h8write -3069 -f20 kzload.mot COM5          (Windows)

 書き込みに成功した場合、実行表示の最後にComplete.と表示されます。

=======================================
 バージョン
=======================================
2011/05/26 Version 0.0.1
 初版

2011/05/28 Version 0.0.2
 メモリ消去コマンドに対する応答処理の不具合を修正。
 異常終了時にシェルに返すコードが正常時と区別できない不具合を修正。
 24ビットアドレスモード、32ビットアドレスモードの処理不具合を修正。
 シリアルポートをクローズして終了するように修正。
 メモリ消去時、書き込み時に進捗を示す表示を追加。

2011/05/31 Version 0.0.3
 Windowsに対応。
 バージョン番号を表示を追加。
 シリアルボーレート合わせ込みシーケンスに再試行処理を追加。
 付属プログラムmotdumpの表示処理のマイナーバグを修正。

2012/04/30 Version 0.1.0
 引数の指定方法を書籍で使っている範囲でh8writeと互換性をとるようにした。
 書籍では、-3069、-f20、MOTファイル名、シリアルデバイスが指定されている。

2012/12/18 Version 0.2.0
 書き込み対象motファイルサイズに依存して起きるバグを修正した。

2012/12/19 Version 0.2.1
 バージョン番号の更新漏れを修正した。
 書き込み最終アドレス計算のバグを修正した。

=======================================
 謝辞
=======================================
やまちゅうさん
 Version 0.0.1でおきる問題について詳細なレポートを頂きました。

蔵花たけしさん
 Version 0.1.0でおきる問題について詳細なレポートを頂きました。

