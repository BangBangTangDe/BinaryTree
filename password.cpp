#include<string>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;


struct a_word {
	char ch;
	int count;
	a_word() { count = 0; };
};
a_word first[26];//统计字母个数的结构体数组
long long number = 0;//穷举法的个数统计
string password_str = "";//密文
int ans = 0;//统计有记录的字母个数
map<char, int> m;//回溯法的访问数组
map<char, char> key_mi;//密钥

bool cmp(a_word a, a_word b)
{
	return (a.count > b.count);
}
//大小写转换
string conform(string str)
{
	string s = "";
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			s += (char)str[i] + ('a' - 'A');
		}

	}
	return s;

}
//字符串替换函数
void replace_str(string & str, char a, char b)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i]== a)
		{
			str[i] = b;
		}
	}
}
//密钥和明文对应
string solve(string password)
{
	string line_str="";
	string mingwen = password;
	ifstream in("d:\\密码学文件\\keyword.txt");
	while (getline(in, line_str))
	{
		key_mi[line_str[0]+'a'-'A'] = line_str[3]-'A'+'a';
	}
	in.close();
	char tmp = '$';
	int count = 0;
	bool vis[26] = { 0 };
	for (char i='a'; i <='z'; i++)
	{
		if (key_mi[i] != i && vis[i-'a']==false && vis[key_mi[i]-'a']==false)
		{
			
			replace_str(mingwen, i, tmp);
			replace_str(mingwen, key_mi[i], i);
			replace_str(mingwen, tmp, key_mi[i]);
			vis[i - 'a'] = true;
			vis[key_mi[i] - 'a'] = true;
			count++;
		}
	}

	return mingwen;
}
//子特征字符串包含个数
int include_num(string str ,string sub)
{
	int len = sub.length();
	int count = 0;
	while (str.length() >= len && str.find(sub)>=0)
	{
		int pos = str.find(sub);
		str = str.substr(pos+len, str.length() - pos);
		count++;
	}
	return count;
	
}
//回溯实现全排列
void DFS(string result,int count)
{
	if (count == 26)
	{
		cout << result << endl;
		for (int i = 0; i < result.length(); i++)
		{
			key_mi['a' + i] = result[i];
		}
		string see_wen = solve(password_str);
		if (include_num(see_wen, "the") == 12 && include_num(see_wen, "and") == 10)
		{
			number++;
			cout << number << ":===>" << see_wen << endl;
		}
		key_mi.clear();
	}
	for (char c = 'a'; c <= 'z'; c++)
	{
		if (m[c] == 0)
		{
			string s = result + c;
			m[c] = 1;
			DFS(s, count + 1);
			m[c] = 0;
		}
	}

}
//穷举法
void Exhaustion(string password_str)
{
	string result = "";
	DFS(result, 0);
}
//统计频率
void count_hz(a_word a[], string s)
{
	
	for (int i = 0; i < s.length(); i++)
	{
		first[s[i]-'a'].count++;
		first[s[i] - 'a'].ch = s[i];
	}
	sort(first, first+26, cmp);
	cout << "字母  " << "  个数" << "    频率" << endl;
	for (int i = 0; i < 26; i++)
	{
		if (first[i].count != 0)
		{
			cout << first[i].ch << "\t" << first[i].count<<"\t"<< first[i].count*1.0/s.length() << endl;
			ans++;
		}
	}

	cout << "有记录的结果字母有" << ans << " 个" << endl;

}
//显示密钥
void print_key()
{
	string s = "";
	cout << "\t\t原字母\t对应字母" << endl;
	ifstream in("d:\\密码学文件\\keyword.txt");
	while (getline(in,s))
	{
		cout << "\t\t" << s[0] << "\t" << s[3] << endl;
	}
	in.close();

}

int main()
{
	ifstream in("d:\\密码学文件\\key.txt");
	char ch;
	int choice;
	while (in.get(ch))
	{
		password_str += ch;
	}
	in.close();
	//大写转换小写
	password_str = conform(password_str);
	cout << "\t小宝的密码破解" << endl;
	cout << "1.穷举法\n2.频率分析法\n3.其他键退出" << endl;
	while (1) {
		cin >> choice;
		switch (choice)
		{
		case 1:
			//穷举法
			cout << "====================穷举法================" << endl;
			cout << "正在破解。。。。。。。。。。。。。。。" << endl; 
			Exhaustion(password_str);
			break;
		case 2:
			cout << "=================频率统计===================" << endl;
			//统计频率
			count_hz(first, password_str);
			cout << endl;

			//破解结果
			cout << "=====================密文=====================" << endl;
			cout << password_str << endl;
			cout << endl;
			cout << "=======================明文=====================" << endl;
			cout << solve(password_str) << endl;
			cout << endl;
			cout << "======================密钥代换规则================" << endl;
			print_key();
			cout << endl;
			break;
		default:
			break;
		}
		if (choice != 1 || choice != 2)break;

		
	}
	system("pause");
	return 0;
}