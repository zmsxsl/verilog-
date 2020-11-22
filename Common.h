#ifndef COMMON_H
#define COMMON_H
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <utility>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <cstdlib>
#include <cassert>
#include <functional>
#include<io.h>
using namespace std;

typedef enum //枚举类型，保存词素类型
{
	/* 结束标志和错误标志 */
	BLANK,TABLE, LBRACK, RBRACK,COLON,INPUT,OUTPUT,MODULE,SINGLEQUOTE,ENDMODULE,
	ENDFILE, ERROR,AT,ALWAYS,BEGIN,END, POINT, SHUXIAN, BINGQIE, BOLANG, WENHAO,MEIYUAN, JIANJIAO, BAIFENHAO,
	/* 保留字 */
	IF, ELSE, INT, RETURN, VOID, WHILE,PARAMETER,REG,
	/* 变量名和数字 */
	ID, NUM,
	/* 特殊字符 */
	/*  {       }    >=   <=   !=   ==    =    <   >    +      -     *     /     (        )     ;     ,   */
	LBRACE, RBRACE, GTE, LTE, NEQ, EQ, ASSIGN, LT, GT, PLUS, MINUS, MULT, DIV, LPAREN, RPAREN, SEMI, COMMA,
	/* 行注释  段注释 */
	LCOMMENT, PCOMMENT,
	/*换行符*/
	NEXTLINE, 
	/*接口*/
	INTERFACE,
	/*线*/
	WIRE, VERLOGASSIGN
} LexicalType;

typedef pair<LexicalType, string> Token;
void outputError(string err);


#endif // !COMMON_H
