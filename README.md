# Feng-Rao-Decorder-for-AG-Code
Stichtenothらによる一般化エルミート曲線を使って幾何学的ゴッパ符号を構成し、それをFeng-Rao訂正アルゴリズムで復号しようという目的で作りました。
あわよくば多点生成AG符号にも挑戦してみたいです。
このテーマは私の学生時代からの宿敵であり、私の、ふぐりすみえのような、しつこい執念でいま解決されようとしているのです。
この符号を暗号に使うかどうかはまだ決めてません。
自分には数学を理解する才能がないので、こうして具体例を作ることで理解に近づくことができるのではないかと思っています。趣味としての生涯学習ですね。

C(x,y)=x^15y^2+x^14y^4+x^12y^8+x^8y+x^16　over GF(16)　#N=137

今のところこんな曲線がいくつも見つかっています。

20200103

これは既約じゃないので、x^8で割ってみます。すると、

c'(x,y)=x^7y^2+x^6y^4+x^4y^8+y+x^8　over　GF(16)　#N=121

しかしこれだと点の数が１２１に減ってしまいます。（当然ですが）

でもこれがどうやら正しい式のようです。
最後の項はあってもなくても点の数は変わりませんが、今度はyで割り切れてしまうので必要です。

論文通りにやってみると、曲線はこうなります。

C”(x,y)=y^2/x+y^4/x^2+y^8/x^4+y/x^8=1

すると今度は点の数が210個にもなり。増えてしまいます。０でわるんだから何だかインチキ臭い計算ですねｗ

論文１の例にあるような有理式だと、点の数がやたらと多くて例に乗っている点の数になりません。
そこで整式になおしてやると正しい点の数が出てきます。
なのでこれは、有限体では逆数が計算できるとはいえ、整式に直して考えるのが正しいかもしれないです。

これらの式は一般化された式から個別に計算しているだけなので規則性があります。
定義体の拡大次数によって変わるだけなので実に単純です。

20200105

曲線Cの規約性をsagemathで確認しました。既約です。すると次数は12もあるので、種数はg=(12-1)(12-2)/2=55もあるはずです。
しかし曲線の点は121個しかないわけで素直に喜べません。いくら既約性があったとしても、既存の符号のパラメータとしては絶望的です。
次元が１とかになってしまう。多分特異点があるんだと思うのですが、それもsagemathを使って確かめられるでしょうか・・・。

sage: x, y = AffineSpace(2, GF(2), 'xy').gens()

sage: C3 = Curve(x^7*y^2 + x^6*y^4 + x^4*y^8 + y + x^8)

sage: C3

Affine Plane Curve over Finite Field of size 2 defined by x^4*y^8 + x^6*y^4 + x^7*y^2 + x^8 + y

sage: C3.irreducible_components()

[

Closed subscheme of Affine Space of dimension 2 over Finite Field of size 2 defined by:

x^4*y^8 + x^6*y^4 + x^7*y^2 + x^8 + y

]



参考文献は以下のとおりです。

1.Multi-point Codes from Generalized Hermitian Curves arXiv 2015

2.Simplified Understanding and Efficient Decoding of a Class of Algebraic-Geometric Codes 1994 IEEE

3.A Simple Apploach for Construction of Algebraic-Geometric Codes from Affine Plane Curves 1994 IEEE

4.Construction and Decoding of a Class of Algebraic Geometry Codes 1989 IEEE
