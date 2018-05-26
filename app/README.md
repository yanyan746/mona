Copyright 2018, yanyan. All rights reserved

******************
git clone https://github.com/yanyan746/mona.git
sudo cp -r mysql-connector-c++-1.1.11/include/ /usr/local/include
sudo apt install libmysqlcppconn-dev
sudo apt install libcurl4-openssl-dev

// please adjust -L path in GNUmakefile
******************

名前：未定
目的：記事作成インセンティブの底上げ、対外向け自社紹介用
内容：作成者が自分以外の記事へmonacoinを投げ銭するシステム
設計：
　月曜日の朝９時に一定量のmonacoinを全員へ配布し、週末までに良記事作成者へ投げ銭を行う
　自分の記事への投げ銭は不可
　日曜日の深夜０時までに投げることのできなかったmonacoinはプールへと返金される
　プールに返金された分のmonacoinは月末に記事作成数に応じて全員に振り分けられる

table1:user
id, name, mona-pubkey, mona-seckey, password
CREATE table test.user (id int, password varchar(16), name varchar(16), mona double, pool double, count double, PubKey varchar(256), SecKey varchar(256));
INSERT INTO test.user (id, password, name, mona, pool, count, PubKey, SecKey) VALUES (1, "password", "yanyan", 100, 10, 5, "test", "test");


table2:article
date, title, writer, mona-count
CREATE table test.article (date varchar(16), title varchar(64), writer varchar(16), mona double);
INSERT INTO test.article (data, title, writer, mona) VALUES ("2018-5-23", "MONA token", "yanyan", 4.567);

* article.writerはuser.nameの中からしか選べない
* monacountはmonacoinがブロックに取り込まれてから１２ブロック後に反映される

【作成手順】
user tableの作成
　管理者のみユーザーの追加と削除を可能に
article tableの作成
　記事の登録と削除の実装
記事一覧とユーザー別記事の表示コマンド実装
Monacoin送金機能実装
週初めのMonacoin自動送金と、週終わりの回収、月末の配当実装
セキュリティ強化
API実装
　　
