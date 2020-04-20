#include<iostream>
#include<string>
#include<algorithm>         //算法   find_if
//#include<functional>      //函数
//#include<iterator>        //模板类
#include<vector>            //容器
#include<fstream>           //文件



using namespace std;                               //std



enum Count_Type { First = 1, Second = 2 };        //定义一种新的数据类型 - 枚举型



class ATM                                          //ATM类
{
public:
	ATM() {}
	static double Get_RMB() { return RMB; }
	static void Set(double rm) { RMB += rm; }       //存
	static void Set_(double Rmb) { RMB -= Rmb; }    //取
private:
	static double RMB;
};

class Count                                    //账户
{

public:

	Count_Type Get_Message()const { return this->s; }
	void Set() { this->s = First; } //活期
	void Set_Second() { this->s = Second; }//死期
private:
	Count_Type s;
};

class Card                                         //银行卡类
{
public:
	string Get_Id()const { return this->Card_Id; }      //id

	void Set_New_Password(const string& value) { this->PassWord = value; }      //修改


	int Get_Credit()const { return this->Credit; }      //信用额度
	string Get_Type()const { return this->s; }          //类型
	void Set_Credit(int value = 10) { this->Credit += value; }   //额度+10
	string Get_Password()const { return this->PassWord; }        //密码

	friend std::istream& operator>>(istream& in, Card& card);
	friend std::ostream& operator<<(ostream& out, const Card& card);
	auto Get_Money() { return this->money; }
	void Set_Money(const pair<Count, double>& value) { money.push_back(value); }
	double Get_Surples()const { return this->Surples; }
	void Set_Surples(const double value) { this->Surples -= value; }
	void Set_Up_Surples(const double value) { this->Surples += value; }
	void Set_Card_Message(const string& value) { this->Card_Message = value; }
private:
	string Card_Id;
	string s; //卡号类型
	vector<pair<Count, double>> money;
	int Credit; //信用额度
	string PassWord;//密码
	string Card_Message;//卡户信息

	double Surples;//余额
};

class Staff                 //职工类
{
public:
	static string Get_Root() { return Root; }
private:

	static string Root;
};




string Staff::Root = "admin";
//初始 密码
class Handle //操作类
{
public:
	Handle(const string& s)                                      //构造
		:mess(s) {}
	string Get_Mess()const { return this->mess; }                //返回mess
	void Set_Mess(const string& value) { this->mess = value; }   //修改
private:
	string mess;
};




void Show_Print(Card& card);                                    //打印

vector<Card> card;                                              //容器

void Out_Money(Card& outcard);                                  //

vector<pair<Card, Handle>> history;                             //历史记录

bool Set_New_Money(Card& outcard, const double outmoney);       //判断

void Find_History(const vector<pair<Card, Handle>> history);    //查找记录



void Carry_One(Card& outcard)                     //转账，，，，银行卡
{
	cout << "请问你想转账的卡号: ";
	string s;
	cin >> s;
	auto iter = std::find_if(card.begin(), card.end(), [&s](const Card& card1) {return card1.Get_Id() == s; });//查询账户
	if (iter != card.end())
	{
		cout << "请输入你想转多少钱: ";
		double outmoney;
		cin >> outmoney;

		if (Set_New_Money(outcard, outmoney))           //转账金额
		{
			iter->Set_Up_Surples(outmoney);             //一个账户失去钱，另一个获得钱
			cout << "转账成功" << endl;
		}
		else
			cout << "转账失败 可能余额或可动资产不足" << endl;
	}
	else
	{
		cout << "该卡号不存在转账失败";
	}
	history.push_back(make_pair(outcard, Handle("转账")));          //push

}



void Life_Cost(Card& outcard)                  //缴费，，参数outsomebody
{
	cout << "请输入你想要对什么进行缴费: ";
	string s;
	cin >> s;
	cout << "请输入需要缴费多少钱: ";
	double outsomemoney;                       //金额
	cin >> outsomemoney;
	if (Set_New_Money(outcard, outsomemoney))     //bool型函数
	{
		cout << "缴费成功" << endl;
		history.push_back(make_pair(outcard, Handle("生活缴费")));
	}
	else
		cout << "卡内能动的余额不足" << endl;
}



bool Set_New_Money(Card& outcard, const double outmoney)
{
	double count = outcard.Get_Surples();
	if (!outcard.Get_Money().empty())
	{
		auto iter = outcard.Get_Money();
		for (auto p = iter.begin(); p != iter.end(); ++p)
		{

			if (p->first.Get_Message() == Second)
				count -= p->second;
		}
	}
	if (count >= outmoney)
	{
		outcard.Set_Surples(outmoney);
		return true;
	}
	else if (outcard.Get_Type() == "信用卡")
	{
		if ((count + outcard.Get_Credit()) >= outmoney)
		{
			outcard.Set_Surples(outmoney);
			return true;
		}
	}
	return false;
}



void Print(const vector<Card>& card)                //每个账户卡打印
{
	for (auto p : card)
		cout << p;
	cout << endl;
}



void SET_ATM()                                        //*****************
{

}



void Save_Money(Card& outcard)                         //存钱 ，，，参数getmoney
{
	cout << "请问你想存入多少钱: ";
	double getmoney;
	cin >> getmoney;


	cout << "请选择是存活期(选择1)   死期(选择0): ";
	int p;
	cin >> p;
	Count c;

	if (p == 1)
	{
		c.Set();
	}
	else if (p == 0)
	{
		c.Set_Second();
	}
	cout << "存款成功" << endl;
	if (outcard.Get_Type() == "信用卡" && getmoney >= 1000)
	{
		outcard.Set_Credit();
		cout << "信用额度+10" << endl;
	}
	outcard.Set_Up_Surples(getmoney);

	outcard.Set_Money(std::make_pair(c, getmoney));
	history.push_back(make_pair(outcard, Handle("存款")));            //push
}




void Out_Money(Card& outcard)                                //取钱
{
	cout << "请输入您想取多少钱: ";
	double outmoney;
	cin >> outmoney;
	if (outcard.Get_Type() == "信用卡")
	{
		if (outcard.Get_Credit() >= 0)
		{
			if (Set_New_Money(outcard, outmoney))
				cout << "取款成功" << endl;
			else
				cout << "余额不足" << endl;
		}
		else
			cout << "信用度太低无法取钱" << endl;
	}
	else
	{
		if (Set_New_Money(outcard, outmoney))
			cout << "取款成功" << endl;
		else
			cout << "取款失败 余额不足" << endl;
	}
	history.push_back(make_pair(outcard, Handle("取款")));

}



void E()                          //格式，，，，，
{
	cout << "\t\t\t\t\t";
}


void Root();                         //**************

void Deal(vector<Card>& card);       // 容器


void Begin()                           //初始页面，，登录
{
	std::fstream File("卡号.txt");
	Card test;

	while (File >> test)
	{
		card.push_back(test);
	}
	cout << endl;
	E(); cout << "欢迎来到ATM系统" << endl;
	do
	{

		int Count{};

		cout << "请问您是顾客还是银行职员(1、顾客 2、职员 0、结束): ";
		cin >> Count;
		if (Count == 0)
			break;
		if (Count == 1)
			Deal(card);
		if (Count == 2)
		{
			string s;
			cout << "请输入密码: ";
			cin >> s;
			if (s == Staff::Get_Root())
				Root();
			else
				cout << "密码错误" << endl;

		}
	} while (1);

}



void Deal(vector<Card>& card)             //处理，，，，银行卡类型
{
	string cid, password;
	cout << "请输入您卡号: ";
	cin >> cid;
	cout << "请输入密码: ";
	cin >> password;
	auto iter = std::find_if(card.begin(), card.end(), [&cid, &password](const Card& card1)    //迭代，查找
		{return card1.Get_Id() == cid && card1.Get_Password() == password; });
	if (iter != card.end())                                      //如果找到
	{
		do
		{
			system("pause");
			system("cls");
			E(); cout << "1、取款" << endl;
			E(); cout << "2、存款" << endl;
			E(); cout << "3、缴纳生活费" << endl;
			E(); cout << "4、转账" << endl;
			E(); cout << "5、查看使用记录" << endl;
			E(); cout << "6、显示Card的信息" << endl;
			E(); cout << "0、退出" << endl;
			int Count{};
			cin >> Count;
			if (Count == 0)
				break;
			switch (Count)
			{
			case 1:
				Out_Money(*iter);        //取
				break;
			case 2:
				Save_Money(*iter);       //存
				break;
			case 3:
				Life_Cost(*iter);        //缴费
				break;
			case 4:
				Carry_One(*iter);        //转账
				break;
			case 5:
				Find_History(history);   //历史
				break;
			case 6:
				Show_Print(*iter);       //card信息
				break;
			default:
				cout << "输入失败" << endl;

			}
		} while (1);
	}
	else
		cout << "卡号不存在退出" << endl;
}




std::ostream& operator<<(ostream& out, const Card& card)
{
	out << "卡号: " << card.Card_Id << " 卡号类型: " << card.s;
	if (card.s == "信用卡")
		out << " 信用分: " << card.Credit;
	out << " 卡户信息: " << card.Card_Message << " 卡内余额: " << card.Surples << endl;
	return out;
}   //重载



std::istream& operator>>(istream& in, Card& card)
{
	in >> card.Card_Id >> card.s;
	if (card.s == "信用卡")
		in >> card.Credit;
	in >> card.PassWord >> card.Card_Message >> card.Surples;
	return in;
}      //重载



void Root()            //银行职员的操作
{
	E(); cout << "我们是银行职员 可以修改客户信息" << endl;
	E(); cout << "1、修改密码" << endl;
	E(); cout << "2、修改卡号信息" << endl;
	E(); cout << "3、查看银行卡余额" << endl;
	E(); cout << "4、装入现金" << endl;
	E(); cout << "5、取出现金" << endl;
	E(); cout << "6、显示当前余额" << endl;
	E(); cout << "0、返回菜单" << endl;
	int Count{};
	do
	{
		cin >> Count;
		if (Count == 0)
			break;
		if (Count == 1)
		{
			cout << "请输入卡号: ";
			string s;
			cin >> s;
			auto iter = std::find_if(card.begin(), card.end(), [&s](const Card& card1) {return card1.Get_Id() == s; });
			if (iter != card.end())
			{
				cout << "请输入新的密码: ";
				string password;                   //修改密码
				cin >> password;
				iter->Set_New_Password(password);
				cout << "修改成功" << endl;
			}
			else
			{
				cout << "不存在卡号无法修改" << endl;
			}
		}
		if (Count == 2)                                 //修改卡片信息
		{
			cout << "请输入卡号: ";
			string s;
			cin >> s;
			auto iter = std::find_if(card.begin(), card.end(), [&s](const Card& card1) {return card1.Get_Id() == s; });
			if (iter != card.end())
			{
				cout << "请输入卡户信息: ";
				string message;
				cin >> message;
				iter->Set_Card_Message(message);
				cout << "修改成功" << endl;
			}
			else
			{
				cout << "不存在卡号无法修改" << endl;
			}
		}
		if (Count == 3)                           //查看银行卡余额
		{
			cout << "请输入卡号: ";
			string s;
			cin >> s;
			auto iter = std::find_if(card.begin(), card.end(), [&s](const Card& card1) {return card1.Get_Id() == s; });
			if (iter != card.end())
			{
				cout << "余额: " << iter->Get_Surples() << endl;
			}
			else
			{
				cout << "不存在卡号" << endl;
			}

		}
		if (Count == 4)                        //装入现金
		{
			cout << "您想装入多少: " << endl;
			double rm;
			cin >> rm;

			ATM::Set(rm);
			cout << "余额: " << ATM::Get_RMB() << endl;
			cout << "转入成功" << endl;

		}
		if (Count == 5)                      //取出现金
		{
			cout << "您想取出多少: " << endl;
			double rm;
			cin >> rm;
			if (rm > ATM::Get_RMB())
			{
				cout << "取出超出额度失败" << endl;
			}
			else
			{
				ATM::Set_(rm);
				cout << "取出成功" << endl;
			}
			cout << "余额: " << ATM::Get_RMB() << endl;
		}
		if (Count == 6)                      //打印余额
		{
			cout << "当前余额: " << ATM::Get_RMB() << endl;
		}
		cout << "请继续输入: ";
	} while (1);
}



void Find_History(const vector<pair<Card, Handle>> history)          //历史记录查询
{
	cout << "请输入你想要查找的记录的卡号 ";
	string id;
	cin >> id;
	bool test = true;
	for (auto iter = history.begin(); iter != history.end(); ++iter)      //顺序查找
	{
		if (iter->first.Get_Id() == id)
		{
			test = false;
			cout << iter->first << "所做业务: " << iter->second.Get_Mess() << endl;
		}
	}
	if (test)
		cout << "没有这个编号" << endl;
}




double ATM::RMB = 100000000;             //定义初始钱数//



void Show_Print(Card& card)              //打印
{
	cout << card << endl;

}


int main()
{
	Begin();

	return 0;
}