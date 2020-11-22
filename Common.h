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

typedef enum //ö�����ͣ������������
{
	/* ������־�ʹ����־ */
	BLANK,TABLE, LBRACK, RBRACK,COLON,INPUT,OUTPUT,MODULE,SINGLEQUOTE,ENDMODULE,
	ENDFILE, ERROR,AT,ALWAYS,BEGIN,END, POINT, SHUXIAN, BINGQIE, BOLANG, WENHAO,MEIYUAN, JIANJIAO, BAIFENHAO,
	/* ������ */
	IF, ELSE, INT, RETURN, VOID, WHILE,PARAMETER,REG,
	/* ������������ */
	ID, NUM,
	/* �����ַ� */
	/*  {       }    >=   <=   !=   ==    =    <   >    +      -     *     /     (        )     ;     ,   */
	LBRACE, RBRACE, GTE, LTE, NEQ, EQ, ASSIGN, LT, GT, PLUS, MINUS, MULT, DIV, LPAREN, RPAREN, SEMI, COMMA,
	/* ��ע��  ��ע�� */
	LCOMMENT, PCOMMENT,
	/*���з�*/
	NEXTLINE, 
	/*�ӿ�*/
	INTERFACE,
	/*��*/
	WIRE, VERLOGASSIGN
} LexicalType;

typedef pair<LexicalType, string> Token;
void outputError(string err);


#endif // !COMMON_H
