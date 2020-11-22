#include"LexicalAnalyser.h"

void getFiles(string path, vector<string>& files)
{
	//�ļ����
	long   hFile = 0;
	//�ļ���Ϣ
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//�����Ŀ¼,����֮
			//�������,�����б�
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

	////��ȡ��·���µ������ļ�
	getFiles(filePath, files);

	int size = files.size();
	for (int i = 0;i < size;i++)
	{
		//FILE *fp;
		//
		//fp=fopen(files[i].c_str(), "r+");//��дģʽ�������ļ�������ڣ���֮ǰ�����ж�һ��

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

