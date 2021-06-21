#include<cassert>
#include<cstddef>
#include<iostream>
#include<map>
#include<ostream>
#include<string>
#include<set>
//#include"function.h"

using namespace std;

namespace oj
{
	struct String
	{
		std::string str;
		String(const std::string &);
		String(const String &);
		String& operator=(const String &);
	};

	std::ostream& operator<<(std::ostream &,const String &);

	void insert(std::map<int,String> &ma,int key,const std::string &str);
	void output(const std::map<int,String> &ma,int begin,int end);
	void erase(std::map<int,String> &ma,int begin,int end);

	std::ostream& operator<<(std::ostream &,const std::map<int,String> &);
}

namespace oj
{
	String::String(const std::string &str_)
		:str(str_){}

	String::String(const String &rhs)
		:str(rhs.str){}

	String& String::operator=(const String &rhs)
	{
		str=rhs.str;
		return *this;
	}

	std::ostream& operator<<(std::ostream &os,const String &str)
	{
		return os<<str.str;
	}
}

void oj::insert(map<int, String> &ma, int key, const string &str){
    auto tmp = ma.find(key);
    string new_str;

    if(tmp != ma.end()){
        new_str = str + tmp->second.str;
        ma.erase(tmp);
    }
    else
        new_str = str;

    ma.insert(pair<int, String>(key,string(new_str)));
}

void oj::output(const map<int, String> &ma, int begin, int end){
    for(auto &i:ma)
        if(i.first >= begin && i.first<= end)
            cout << i.second << ' ';
}

void oj::erase(map<int, String> &ma, int begin, int end){
    set<int> eraseKeys;
    for(auto &i:ma)
        if(i.first >= begin && i.first <= end)
            eraseKeys.insert(i.first);

    for(auto key:eraseKeys)
        ma.erase(key);
}

ostream& oj::operator<<(ostream &o, const map<int, String> &ma){
    for(auto &i:ma)
        o << i.second << ' ';
    return o;
}

int main()
{
	using namespace std;
	using namespace oj;
	map<int,String> ma;
	for(string cmd;cin>>cmd;)
	{
		if(cmd=="insert")
		{
			int key;
			cin>>key>>cmd;
			insert(ma,key,cmd);
		}
		else
			if(cmd=="range")
			{
				int begin,end;
				cin>>cmd>>begin>>end;
				if(cmd=="output")
					output(ma,begin,end);
				else
					if(cmd=="erase")
						erase(ma,begin,end);
					else
						assert(false);
			}
			else
				assert(false);
		cout<<ma<<endl;
	}
}
