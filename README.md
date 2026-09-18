# pc98-iodata-ga-prcgs
PC9801のMS-DOSにIOデータのGA-1024Aシリーズを使ってPRCGSデータを表示する

# 動作確認環境
Neko Project 21/W 0.86-rev104(Window AcceleratorとしてGA-1280Aを有効に)
FreeDOS(98)

# 必要なコンパイラ、ライブラリ
Open Watcom C 2.0(hugeモデルを使っているので追加でインストールしてください)
IOデータ社提供 GA-1024A/1280A サポートソフト

# ビルド方法
MakefileのGAをサポートライブラリがインストールされているディレクトリに設定してください。<br>
あとはwmakeでlookga.exeが生成されます。

# 使用方法
LOOKGA PRCファイル名
ヘッダ情報を表示しながら読み込みを行い、読み込みが終わるとGA側に切り替えて画面表示します。<br>
なにかキーを押すとDOS画面に戻って終了します。<br>
