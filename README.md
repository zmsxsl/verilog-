# verilog批量该变量名工具
用来骗过只考虑字符是否相同的查重

在LexicalAnalyser.cpp文件的LexicalAnalyser::ExchangeInList()函数中定义自己的规则，ID指变量，INTERFACE是接口。

举个粒子：
modude lizi
(input a);
则a是变量。

lizi LZ
(.a(A));
则.a是接口。

保留字可能没有加全，当前版本不识别双引号。

解释权著作权全部归@Noirebao。

祝广大受难朋友早日脱离苦海。
