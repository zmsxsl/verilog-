#include"LexicalAnalyser.h"

void getFiles(string path, vector<string>& files)
{
	//文件句柄
	long   hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之
			//如果不是,加入列表
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}


int main() 
{
	string filePath = "E:\\try_for_54_cpu_static_pipeline\\source_decode2";

	vector<string> files;

	////获取该路径下的所有文件
	getFiles(filePath, files);

	int size = files.size();
	for (int i = 0;i < size;i++)
	{
		//FILE *fp;
		//
		//fp=fopen(files[i].c_str(), "r+");//读写模式，但是文件必须存在，用之前可以判断一下

		//fseek(fp,0, SEEK_END);
		//fprintf(fp, "#");
		//fclose(fp);



		string temp;
		cout << files[i].c_str() << endl;
		LexicalAnalyser lexicalAnalyser(files[i].c_str());
		lexicalAnalyser.analyse();
		lexicalAnalyser.ExchangeInList();
		//lexicalAnalyser.outputToScreen();
		
		temp = "E:\\try_for_54_cpu_static_pipeline\\source_final";
		
		int c=files[i].rfind("\\");

		temp += files[i].substr(c);

		cout << temp.c_str() << endl;
		lexicalAnalyser.GetCodefromList(temp.c_str());

	}
	cout << "OK"<<endl;
	return 0;
}

