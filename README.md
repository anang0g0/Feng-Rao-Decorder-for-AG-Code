# Feng-Rao-Decorder-for-Class-of-AG-Codes 

参考文献

１． The Key Equation for One-Point Codes. M.E.O'Sullivan et al. 2008

２．Cryptanalysis of McEliece Cryptosystem Based on Algebraic Geometry Codes and their Subcodes. Alain Couvreur, Irene Márquez-Corbella, and Ruud Pellikaan

３．Explicit Construction of AG Codes from a curve in the tower of Bassa-Beelen-Garcia-Stichtenoth. C.Hu

４．Multi-point Codes from Generalized Hermitian Curves. C.Hu et,al.


# 20230324

BBGS曲線を拡大次数と基礎体をパラメータとして自動的に生成する関数を追加。
VG限界を軽やかに突破。
今までいちいち計算してたので自動化出来て嬉しい。

Classic Goppa Codesにも未解決な問題はあるんですが、リスト復号や補間と近似方式で性能が向上するのでしょうか？


# 20230323

引き続きbbgs曲線の一般化を行った。
bbgsは標数と拡大次数によって決まるので、いろんな拡大体で最大曲線になる。

また代数幾何符号に帰ってきそうな予感。
蛇足でプログラムなんかいじるから、余興のつもりがハマってしまった。
alone againの論文のおかげで一歩復号に近づいた。
本当はもっと先に片付けないといけない課題があるのですが、主にプログラミングの書き方ですね。
bbgs曲線がすごい。

もちろん成功したあとは暗号に応用させてもらいますｗ

# 20230322

BBGS曲線の、拡大次数3の場合の点数えを実装した。

BBGS曲線とは、3次拡大に特化すると、

$$\frac{y^q}{x}+\frac{y^{q^2}}{x^q}+\frac{y}{x^{q^2}}=1$$

となるような曲線である。

例えばGF(27)の場合、この曲線の有理点の数は235個になる。


# 20220403

https://arxiv.org/pdf/1505.03020.pdf

https://www.cs.utexas.edu/~danama/courses/codes/lec7-AG-codes.pdf

https://arxiv.org/pdf/2108.02758.pdf　
（これのおかげで謎が解けそう）

Klein曲線で実験してみる。アフィンの点は　#K=22 over GF(8)
なので、無限点P∞は別にある。

無限遠点P∞を使って符号長n=22の符号を作る物とする。  
このとき、関数x,yの無限遠点における位数を計算すると、  

C(x,y)=x^3y+y^3+x=0

x^3y=3x+y=max{y^3+x}=3y

3x+y=3y <=> 3x=2y

ord(x)=2 ord(y)=3

Klein曲線の種数はg=3なので、m>2g-2=2*3-2=4, m>4 である。  

m=11と置くと、  
L(11P∞)={1,x,y,x^2,xy,y^2,x^2y,xy^2,y^3,x^2y^2,xy^3}  
I={0,2,3,4,5,6,7,8,9,10,11}

このように基底が求められる。

k=m+1-g=12-3=9  
k'=2m+1-g=20

最小距離はまだわからない。

# 20220402

文献1より、
GF(64)で定義される以下のアフィン曲線の点の数は　#C=1009、エルミート曲線より長い符号を生成する。

C(x,y)=x^16y^15+xy^12+x^4+y^16;

a=16  
b=1  
c=15

故に文献3のタイプ2の曲線に相当する。

代数幾何より暗号の方がいいという意見を聞いたのでちょっとリスト復号に戻ります。
アディオス！ｗ

# 20220401

何だかBMAが世界を制覇しそうな感じなので、汎用的でなくてもいいからフェンラオを制覇したい。

そしてなぜフェンラオでは訂正できない符号の族が存在するのか、或いはできるのかを明らかにしたい。

フェンラオには多項式をいじる部分が全くないのが不思議だ。

天気が毎日変わるので体がついて行かないせいか眠い。

https://ci.nii.ac.jp/naid/110003197615  
「Feng-Rao復号法は任意の線型符号をO (n^3) のオーダの計算量である設計距離 (BCH符号ならBCH限界を下回らない値, Goppa符号ならGoppa限界を下回らない値) まで復号するアルゴリズムである.」

任意の線形符号とのことなので、僕は僕でいいんだ！

2点生成エルミートはBMAで復号できてしまう。
だから中国の論文は3点生成だったのだろうか？

まだまだフェンラオに関する調査は続く。

バグ取り。
点数え関数のバグをとる。
定数項の数え落としが原因。

昨日の続き。

曲線C: over GF(8)  
C(x,y)=x^4y^3+y^4+xy^2+x^2  
#C=29  
a=4, b=1, c=3  

これてっきりgcd(4,1)=4だと思っていたら、gcd(4,1)=1だったのですね。

これはフェンラオのタイプ2に当てはまりそうなので、復号できるかも知れないです。

# 20220331

フェンラオは万能じゃないらしい。

曲線の形が限られている。

これじゃ一般の場合を実装したことにならない。
例えば文献5の次のような曲線は複合できない。

C(x,y)=x^8*y^16 + x^12*y^8 + x^14*y^4 + x^15*y^2 + x^16 + y over GF(32)
#C=497

肩透かし。

でもちょっといい曲線を知っているのでそれでやってみる。

f1=x^3y+y^3+1  
f2=x^3y+y^3+y^2+1  
a=3  
b=2  
c=1

この2つの曲線は（確認してないが）非特異で、種数が3である。そして点の数はGF(64)上で112ある。
なのでセール限界式の上限を満たす。また、文献3のタイプBに当てはまる。

このとき関数x,yの位数はx=2,y=3である。
種数が3のとき、m>2g-2=6-2=4なので次元は少なくとも5以上ある。

m=6の場合、この符号の基底は

O={1,x,y,x^2,xy,y^2}  
I={0,2,3,4,5,6}

である。

多項式の規約性判定はすでに調査済みだが、特異点があるかどうかの判定法がわからない。  
有理点を計算して、その都度偏微分して特異点かどうか虱潰しに計算すればいいのかもしれないが、なんだか効率が悪い。

関数論を勉強しなければ。

文献1から見つけた曲線を、色々いじって見つけた。

C(x,y)=x^{q^2}y^{q^2-1}+xy^q+x^q+y^{q^2} over GF(q^3)

ここでｑは基礎体。q=2のとき、

f=x^4y^3+y^4+xy^2+x^2: #f=31 over GF(8)  

既約性を確かめてみた  
sage:  x, y = AffineSpace(2, GF(2), 'xy').gens()  
sage: f=x^4*y^3+y^4+x*y^2+x^2  
sage: C=Curve(f)  
sage: C.irreducible_components()  
[  
Closed subscheme of Affine Space of dimension 2 over Finite Field of size 2 defined by:  
  x^4*y^3 + y^4 + x*y^2 + x^2  
]  

GF(8)でも同様に既約であった。  

x=1,y=4,g=6なので、xとyの間の位数のとり方に気をつける。

つまりy/x=4-1=3  
として計算すると、位数が隙間なく並べることができる。

m>2*6-2=10

m=11とすると基底は

O={1,x,x^2,y/x,y,xy,x^2y,y^2/x,y^2,xy^2,x^2y^2}  
I={0,1,2,3,4,5,6,7,8,9,10}  

a=4
c=3
b=1

この曲線は式の形からフェンラオのタイプには当てはまらない。
いい曲線があったとしても、その曲線から作る符号を復号する方法がないという感じでしょうか。

復号アルゴリズムに汎用性を期待するのか、それとも性能を要求するのかの問題だが、自分としては汎用性を重視したい。
つまり基底とシンドロームさえ計算できれば復号できるような復号法だ。

ベーシックアルゴリズムでもなんでもいい。（もしあれば）
そのへんはまた明日調べよう。

# 20220330

文献3を読んでいます。

きちんと読めば技術者にもわかるように書いてあるので、時間をかけて理解したいです。  
ただ、フェンラオの論文はネットに落ちてないのですね。

最初にエルミート符号を実装したときは文献2しか読んでなかった。
どんな曲線でも復号できるなんて贅沢だと思っていた。
文献3を読むことでいろんな具体例に届きそうな気がする。
私のやりたいことはすべて文献3に書いてあるのかもしれない。

代数曲線論も知っておきたいので、フルトンの本をネットからDLして印刷した。
シカゴ大が公開している2008年バージョン。

sagenathで平面代数曲線のプロットをしたいのだが、なぜか3次元の表示になってしまい、使い方がよくわからない。

よくわからない数学ｗ

# 20220329

口に出すのもおぞましい研究者の競争を尻目に、やはりフェンラオしかないだろうと思いフェンラオをまた始めた。  
エルミート符号は復号できて、他の符号はダメというような理由があれば無謀だが、まだ調べていない。  
今までエルミート符号しかしてなかったけど、今回は一般の1点生成代数曲線符号に対してフェンラオを拡張できるかどうかをやってみる。  
BMAを使わずにやる予定。

https://tsujimotter.hatenablog.com/entry/curve-and-function-field-1

https://www2.meijo-u.ac.jp/~yonishi/research/pub/ss2007/02ogawa.pdf


やっと曲線上の関数の位数の計算方法がわかった。  
これで任意の曲線からできる符号のパラメーターが計算できるようになる。  
関数X,Yの無限遠点での極の位数は曲線の次数と関係しているようだが、どのような規則によってそうなっているのか勉強中。

そもそも極とか零点というのは複素関数論の概念で、勉強が身についていなかった自分に理解できるはずがなかったのだ。  
でも今ならわかるかもしれない。

そして多点生成のパラメーターもわかるだろうが、復号できなければ困るので、
無限遠の一点生成の時に任意の曲線から構成される符号を復号できるように頑張ろう。

多数決論理の精密化ができればいいけどできるのだろうか？

LDPCに比べればこの前世紀の遺物はすでに実用的な価値を失ってはいるが、それでも数学的な魅力にあふれている。

リーマンロッホの定理がこの符号に応用されていることがとても面白い。



参考文献は以下のとおりです。

1.Multi-point Codes from Generalized Hermitian Curves arXiv 2015

2.Simplified Understanding and Efficient Decoding of a Class of Algebraic-Geometric Codes 1994 IEEE

3.A Simple Apploach for Construction of Algebraic-Geometric Codes from Affine Plane Curves 1994 IEEE

4.Construction and Decoding of a Class of Algebraic Geometry Codes 1989 IEEE

5.Explicit Construction of AG Codes from Generalized Hermitian Curves 2015 arXiv

