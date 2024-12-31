# hello-mqtt

ESP-IDF で MQTT にチャレンジしよう！

## 概要

IoT関連でよく聞く MQTT(Message Queuing Telemetry Transport)、名前は知っていてもイマイチよくわからん。 我々捜査班はMQTTの謎に迫るべくリポジトリを作成した...。

## MQTT とは？

センサー（温度計とか）のデータをネット経由で送ったり、ボタンの動きを同期したりなどできる。複数のデバイスを同時に動かすなどもカンタンにできる。

## MQTT の仕組み

メッセージを発信できる(Publish)。購読してるマン(Subscribe)に全部届くような仕組み。届けるために中継のサーバーが必要。そのサーバーの事をブローカーと呼ぶ。

## ブローカー(サーバー)をローカルで動かす方法

クラウドサービス(Adafruit IO)などを使うとカンタン。ローカルで試したい場合はMacだとemqxがカンタン。

インストール方法
~~~
brew install emqx
~~~

起動方法
~~~
/opt/homebrew/opt/emqx/bin/emqx foreground
~~~


## クライアント

Macだとこの辺のGUIがある。

- https://github.com/emqx/MQTTX

## ESP-IDFでの使用法

- 設定
~~~
idf.py menuconfig
~~~

menuconfig で WifiのSSID と PASSWORD を設定

ソースコード内の```BROKER_URI``` と ```FEED``` を適当に書き換えてください。

- ビルド
~~~
idf.py build
~~~

- 実行
~~~
idf.py flash monitor
~~~

