#include "LexicalAnalyser.h"

string token_to_string(Token t)
{
	const char* LexicalTypeStr[] =
	{
	"BLANK","TABLE","LBRACK","RBRACK","COLON","INPUT","OUTPUT","MODULE","SINGLEQUOTE","ENDMODULE",
	"ENDFILE", "ERROR","AT","ALWAYS","BEGIN","END","POINT","SHUXIAN","BINGQIE","BOLANG","WENHAO","MEIYUAN","JIANJIAO","BAIFENHAO"
	"IF", "ELSE", "INT", "RETURN", "VOID", "WHILE","PARAMETER","REG"
	"ID", "NUM",
	"LBRACE", "RBRACE", "GTE", "LTE", "NEQ", "EQ", "ASSIGN", "LT", "GT", "PLUS", "MINUS", "MULT", "DIV", "LPAREN", "RPAREN", "SEMI", "COMMA",
	"LCOMMENT", "PCOMMENT",
	"NEXTLINE",
	"INTERFACE","WIRE","VERLOGASSIGN"
	};

	string res;
	res += LexicalTypeStr[t.first];
	res += "  " + t.second;
	return res;
}

LexicalAnalyser::LexicalAnalyser(const char* path)
{
	lineCount = 0;
	openFile(path);

}

LexicalAnalyser::~LexicalAnalyser() {
	if (src.is_open()) {
		src.close();
	}
}

void LexicalAnalyser::openFile(const char* path) {
	src.open(path, ios::in);

	if (!src.is_open()) {
		cerr << "file " << path << " open error" << endl;
		exit(-1);
	}
}

//获取下一个字符
char LexicalAnalyser::getNextChar() {
	char c;
	c = src.get();
	if (c == '\n')
		lineCount++;
	if (src.eof())
		return 0;
	else
		return c;
}

Token LexicalAnalyser::getNextToken() {
	char c = getNextChar();
	switch (c) {
		case ' ':
			return Token(BLANK, " ");
			break;
		case '`':
			return Token(POINT, "`");
			break;
		case '@':
			return Token(AT, "@");
			break;
		case '\t':
			return Token(TABLE, "\t");
			break;
		case '|':
			return Token(SHUXIAN, "|");
			break;
		case '&':
			return Token(BINGQIE, "&");
			break;
		case '$':
			return Token(MEIYUAN, "$");
			break;
		case '~':
			return Token(BOLANG, "~");
			break;
		case '?':
			return Token(WENHAO, "?");
			break;
		case '\n':
			return Token(NEXTLINE, "\n");
			break;
		case '%':
			return Token(BAIFENHAO, "%");
			break;
		case ':':
			return Token(COLON, ":");
			break;
		case '\'':
			return Token(SINGLEQUOTE, "\'");
			break;
		case '(':
			return Token(LPAREN, "(");
			break;
		case ')':
			return Token(RPAREN, ")");
			break;
		case '[':
			return Token(LBRACK, "[");
			break;
		case ']':
			return Token(RBRACK, "]");
			break;
		case '^':
			return Token(JIANJIAO, "^");
			break;
		case '{':
			return Token(LBRACE, "{");
			break;
		case '}':
			return Token(RBRACE, "}");
			break;
		case '#':
			return Token(ENDFILE, "#");
			break;
		case '+':
			return Token(PLUS, "+");
			break;
		case '-':
			return Token(MINUS, "-");
			break;
		case '*':
			return Token(MULT, "*");
			break;
		case ',':
			return Token(COMMA, ",");
			break;
		case ';':
			return Token(SEMI, ";");
			break;
		case '=':
			if (src.peek() == '=') {
				src.get();
				return Token(EQ, "==");
			}
			else {
				return Token(ASSIGN, "=");
			}
			break;
		case '>':
			if (src.peek() == '=') {
				src.get();
				return Token(GTE, ">=");
			}
			else {
				return Token(GT, ">");
			}
			break;
		case '<':
			if (src.peek() == '=') {
				src.get();
				return Token(LTE, "<=");
			}
			else {
				return Token(LT, "<");
			}
			break;
		case '!':
			if (src.peek() == '=') {
				src.get();
				return Token(NEQ, "!=");
			}
			else {
				return Token(ERROR, string("词法分析第") + to_string(lineCount) + string("行：未识别的符号!"));
			}
			break;
		case '/':
			//行注释
			if (src.peek() == '/') {
				char buf[1024];
				src.getline(buf, 1024);
				return Token(LCOMMENT, string("/") + buf + '\n');
			}
			//段注释
			else if (src.peek() == '*') {
				src.get();
				string buf = "/*";
				while (src >> c) {
					buf += c;
					if (c == '*') {
						src >> c;
						buf += c;
						if (c == '/') {
							return Token(PCOMMENT, buf);
							break;
						}
					}
				}
				//读到最后都没找到*/，因不满足while循环条件退出
				if (src.eof()) {
					return Token(ERROR, string("词法分析第") + to_string(lineCount) + string("行：段注释没有匹配的*/"));
				}
			}
			//除法
			else {
				return Token(DIV, "/");
			}
			break;
		default:
			if (isdigit(c)) {
				string buf;
				buf.push_back(c);
				while (c = src.peek()) {
					if (isdigit(c)) {
						src >> c;
						buf += c;
					}
					else {
						break;
					}
				}
				return Token(NUM, buf);
			}
			else if (isalpha(c))
			{
				string buf;
				buf.push_back(c);
				while (c = src.peek())
				{
					if (isdigit(c) || isalpha(c))
					{
						src >> c;
						buf += c;
					}
					else if (c == '_')
					{
						src >> c;
						buf += c;
					}
					else
					{
						break;
					}
				}
				if (buf == "int")
				{
					return Token(INT, "int");
				}
				else if (buf == "wire")
				{
					return Token(WIRE, "wire");
				}
				else if (buf == "always")
				{
					return Token(ALWAYS, "always");
				}
				else if (buf == "begin")
				{
					return Token(BEGIN, "begin");
				}
				else if (buf == "end")
				{
					return Token(END, "end");
				}
				else if (buf == "assign")
				{
					return Token(VERLOGASSIGN, "assign");
				}
				else if (buf == "input")
				{
					return Token(INPUT, "input");
				}
				else if (buf == "output")
				{
					return Token(OUTPUT, "output");
				}
				else if (buf == "module")
				{
					return Token(MODULE, "module");
				}
				else if (buf == "reg")
				{
					return Token(REG, "reg");
				}
				else if (buf == "parameter")
				{
					return Token(PARAMETER, "parameter");
				}
				else if (buf == "endmodule")
				{
					return Token(ENDMODULE, "endmodule");
				}
				else if (buf == "void")
				{
					return Token(VOID, "void");
				}
				else if (buf == "if") {
					return Token(IF, "if");
				}
				else if (buf == "else") {
					return Token(ELSE, "else");
				}
				else if (buf == "while") {
					return Token(WHILE, "while");
				}
				else if (buf == "return") {
					return Token(RETURN, "return");
				}
				else
				{
					return Token(ID, buf);
				}
			}
			else if (c == '.')
			{
				string buf;
				buf.push_back(c);
				while (c = src.peek())
				{
					if (isdigit(c) || isalpha(c))
					{
						src >> c;
						buf += c;
					}
					else if (c == '_')
					{
						src >> c;
						buf += c;
					}
					else
					{
						break;
					}
				}
				return Token(INTERFACE, buf);
			}
			else {
				return Token(ERROR, string("词法分析第") + to_string(lineCount) + string("行：未识别的符号") + c);
			}
	}
	return Token(ERROR, "UNKOWN ERROR");
}

void LexicalAnalyser::analyse()
{
	while (1)
	{
		Token t = getNextToken();
		result.push_back(t);
		if (t.first == ERROR)
		{
			outputError(t.second);
		}
		else if (t.first == ENDFILE)
		{
			break;
		}
	}
}

void LexicalAnalyser::outputToStream(ostream&out)
{
	if (result.back().first == ERROR)
	{
		out << token_to_string(result.back()) << endl;
	}
	else {
		list<Token>::iterator iter;
		for (iter = result.begin(); iter != result.end(); iter++)
		{
			if ((*iter).first == ID)
				out << token_to_string(*iter) << endl;
		}
	}
}

void LexicalAnalyser::outputToScreen()
{
	outputToStream(cout);
}

void LexicalAnalyser::outputToFile(const char *fileName) {
	ofstream fout;
	fout.open(fileName, ios::out);
	if (!fout.is_open())
	{
		cerr << "file " << fileName << " open error" << endl;
		return;
	}
	outputToStream(fout);
	fout.close();
}

list<Token>&LexicalAnalyser::getResult()
{
	return result;
}

void LexicalAnalyser::ExchangeInList()
{
	list<Token>::iterator iter;
	for (iter = result.begin(); iter != result.end(); iter++)
	{
		if (iter->first == ID)
		{
			string s = iter->second;
			string temp;
			int flag = 0;


			for (int i = 0; i < s.size(); i++)
			{
				
				if (i == 0&&s[i]>='a'&&s[i]<='z')
					temp += s[i] + 'A' - 'a';
				else if (s[i] == '_'&&s[i+1] >= 'a'&&s[i+1] <= 'z')
				{
					i++;
					temp += '_';
					temp += +s[i] + 'A' - 'a';
				}
				else
					temp += s[i];
			}
			iter->second = temp;

		}

		if (iter->first == INTERFACE)
		{
			string s = iter->second;
			string temp;
			int flag = 0;


			for (int i = 0; i < s.size(); i++)
			{

				if (i == 1 && s[i] >= 'a'&&s[i] <= 'z')
					temp += s[i]+'A'-'a';
				else if (s[i] == '_'&&s[i + 1] >= 'a'&&s[i + 1] <= 'z')
				{
					i++;
					temp += '_';
					temp += s[i] + 'A' - 'a';
				}
				else
					temp += s[i];
			}
			iter->second = temp;


		}
	}
}

void LexicalAnalyser::GetCodefromList(const char *fileName)
{
	ofstream fout;
	fout.open(fileName, ios::out);
	if (!fout.is_open())
	{
		cerr << "file " << fileName << " open error" << endl;
		return;
	}
	list<Token>::iterator iter;
	for (iter = result.begin(); iter != --result.end(); iter++)

		fout << iter->second;
	fout.close();
}
