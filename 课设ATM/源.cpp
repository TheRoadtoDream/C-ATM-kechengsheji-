#include<iostream>
#include<string>
#include<algorithm>         //�㷨   find_if
//#include<functional>      //����
//#include<iterator>        //ģ����
#include<vector>            //����
#include<fstream>           //�ļ�



using namespace std;                               //std



enum Count_Type { First = 1, Second = 2 };        //����һ���µ��������� - ö����



class ATM                                          //ATM��
{
public:
	ATM() {}
	static double Get_RMB() { return RMB; }
	static void Set(double rm) { RMB += rm; }       //��
	static void Set_(double Rmb) { RMB -= Rmb; }    //ȡ
private:
	static double RMB;
};

class Count                                    //�˻�
{

public:

	Count_Type Get_Message()const { return this->s; }
	void Set() { this->s = First; } //����
	void Set_Second() { this->s = Second; }//����
private:
	Count_Type s;
};

class Card                                         //���п���
{
public:
	string Get_Id()const { return this->Card_Id; }      //id

	void Set_New_Password(const string& value) { this->PassWord = value; }      //�޸�


	int Get_Credit()const { return this->Credit; }      //���ö��
	string Get_Type()const { return this->s; }          //����
	void Set_Credit(int value = 10) { this->Credit += value; }   //���+10
	string Get_Password()const { return this->PassWord; }        //����

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
	string s; //��������
	vector<pair<Count, double>> money;
	int Credit; //���ö��
	string PassWord;//����
	string Card_Message;//������Ϣ

	double Surples;//���
};

class Staff                 //ְ����
{
public:
	static string Get_Root() { return Root; }
private:

	static string Root;
};




string Staff::Root = "admin";
//��ʼ ����
class Handle //������
{
public:
	Handle(const string& s)                                      //����
		:mess(s) {}
	string Get_Mess()const { return this->mess; }                //����mess
	void Set_Mess(const string& value) { this->mess = value; }   //�޸�
private:
	string mess;
};




void Show_Print(Card& card);                                    //��ӡ

vector<Card> card;                                              //����

void Out_Money(Card& outcard);                                  //

vector<pair<Card, Handle>> history;                             //��ʷ��¼

bool Set_New_Money(Card& outcard, const double outmoney);       //�ж�

void Find_History(const vector<pair<Card, Handle>> history);    //���Ҽ�¼



void Carry_One(Card& outcard)                     //ת�ˣ����������п�
{
	cout << "��������ת�˵Ŀ���: ";
	string s;
	cin >> s;
	auto iter = std::find_if(card.begin(), card.end(), [&s](const Card& card1) {return card1.Get_Id() == s; });//��ѯ�˻�
	if (iter != card.end())
	{
		cout << "����������ת����Ǯ: ";
		double outmoney;
		cin >> outmoney;

		if (Set_New_Money(outcard, outmoney))           //ת�˽��
		{
			iter->Set_Up_Surples(outmoney);             //һ���˻�ʧȥǮ����һ�����Ǯ
			cout << "ת�˳ɹ�" << endl;
		}
		else
			cout << "ת��ʧ�� ��������ɶ��ʲ�����" << endl;
	}
	else
	{
		cout << "�ÿ��Ų�����ת��ʧ��";
	}
	history.push_back(make_pair(outcard, Handle("ת��")));          //push

}



void Life_Cost(Card& outcard)                  //�ɷѣ�������outsomebody
{
	cout << "����������Ҫ��ʲô���нɷ�: ";
	string s;
	cin >> s;
	cout << "��������Ҫ�ɷѶ���Ǯ: ";
	double outsomemoney;                       //���
	cin >> outsomemoney;
	if (Set_New_Money(outcard, outsomemoney))     //bool�ͺ���
	{
		cout << "�ɷѳɹ�" << endl;
		history.push_back(make_pair(outcard, Handle("����ɷ�")));
	}
	else
		cout << "�����ܶ�������" << endl;
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
	else if (outcard.Get_Type() == "���ÿ�")
	{
		if ((count + outcard.Get_Credit()) >= outmoney)
		{
			outcard.Set_Surples(outmoney);
			return true;
		}
	}
	return false;
}



void Print(const vector<Card>& card)                //ÿ���˻�����ӡ
{
	for (auto p : card)
		cout << p;
	cout << endl;
}



void SET_ATM()                                        //*****************
{

}



void Save_Money(Card& outcard)                         //��Ǯ ����������getmoney
{
	cout << "��������������Ǯ: ";
	double getmoney;
	cin >> getmoney;


	cout << "��ѡ���Ǵ����(ѡ��1)   ����(ѡ��0): ";
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
	cout << "���ɹ�" << endl;
	if (outcard.Get_Type() == "���ÿ�" && getmoney >= 1000)
	{
		outcard.Set_Credit();
		cout << "���ö��+10" << endl;
	}
	outcard.Set_Up_Surples(getmoney);

	outcard.Set_Money(std::make_pair(c, getmoney));
	history.push_back(make_pair(outcard, Handle("���")));            //push
}




void Out_Money(Card& outcard)                                //ȡǮ
{
	cout << "����������ȡ����Ǯ: ";
	double outmoney;
	cin >> outmoney;
	if (outcard.Get_Type() == "���ÿ�")
	{
		if (outcard.Get_Credit() >= 0)
		{
			if (Set_New_Money(outcard, outmoney))
				cout << "ȡ��ɹ�" << endl;
			else
				cout << "����" << endl;
		}
		else
			cout << "���ö�̫���޷�ȡǮ" << endl;
	}
	else
	{
		if (Set_New_Money(outcard, outmoney))
			cout << "ȡ��ɹ�" << endl;
		else
			cout << "ȡ��ʧ�� ����" << endl;
	}
	history.push_back(make_pair(outcard, Handle("ȡ��")));

}



void E()                          //��ʽ����������
{
	cout << "\t\t\t\t\t";
}


void Root();                         //**************

void Deal(vector<Card>& card);       // ����


void Begin()                           //��ʼҳ�棬����¼
{
	std::fstream File("����.txt");
	Card test;

	while (File >> test)
	{
		card.push_back(test);
	}
	cout << endl;
	E(); cout << "��ӭ����ATMϵͳ" << endl;
	do
	{

		int Count{};

		cout << "�������ǹ˿ͻ�������ְԱ(1���˿� 2��ְԱ 0������): ";
		cin >> Count;
		if (Count == 0)
			break;
		if (Count == 1)
			Deal(card);
		if (Count == 2)
		{
			string s;
			cout << "����������: ";
			cin >> s;
			if (s == Staff::Get_Root())
				Root();
			else
				cout << "�������" << endl;

		}
	} while (1);

}



void Deal(vector<Card>& card)             //�������������п�����
{
	string cid, password;
	cout << "������������: ";
	cin >> cid;
	cout << "����������: ";
	cin >> password;
	auto iter = std::find_if(card.begin(), card.end(), [&cid, &password](const Card& card1)    //����������
		{return card1.Get_Id() == cid && card1.Get_Password() == password; });
	if (iter != card.end())                                      //����ҵ�
	{
		do
		{
			system("pause");
			system("cls");
			E(); cout << "1��ȡ��" << endl;
			E(); cout << "2�����" << endl;
			E(); cout << "3�����������" << endl;
			E(); cout << "4��ת��" << endl;
			E(); cout << "5���鿴ʹ�ü�¼" << endl;
			E(); cout << "6����ʾCard����Ϣ" << endl;
			E(); cout << "0���˳�" << endl;
			int Count{};
			cin >> Count;
			if (Count == 0)
				break;
			switch (Count)
			{
			case 1:
				Out_Money(*iter);        //ȡ
				break;
			case 2:
				Save_Money(*iter);       //��
				break;
			case 3:
				Life_Cost(*iter);        //�ɷ�
				break;
			case 4:
				Carry_One(*iter);        //ת��
				break;
			case 5:
				Find_History(history);   //��ʷ
				break;
			case 6:
				Show_Print(*iter);       //card��Ϣ
				break;
			default:
				cout << "����ʧ��" << endl;

			}
		} while (1);
	}
	else
		cout << "���Ų������˳�" << endl;
}




std::ostream& operator<<(ostream& out, const Card& card)
{
	out << "����: " << card.Card_Id << " ��������: " << card.s;
	if (card.s == "���ÿ�")
		out << " ���÷�: " << card.Credit;
	out << " ������Ϣ: " << card.Card_Message << " �������: " << card.Surples << endl;
	return out;
}   //����



std::istream& operator>>(istream& in, Card& card)
{
	in >> card.Card_Id >> card.s;
	if (card.s == "���ÿ�")
		in >> card.Credit;
	in >> card.PassWord >> card.Card_Message >> card.Surples;
	return in;
}      //����



void Root()            //����ְԱ�Ĳ���
{
	E(); cout << "����������ְԱ �����޸Ŀͻ���Ϣ" << endl;
	E(); cout << "1���޸�����" << endl;
	E(); cout << "2���޸Ŀ�����Ϣ" << endl;
	E(); cout << "3���鿴���п����" << endl;
	E(); cout << "4��װ���ֽ�" << endl;
	E(); cout << "5��ȡ���ֽ�" << endl;
	E(); cout << "6����ʾ��ǰ���" << endl;
	E(); cout << "0�����ز˵�" << endl;
	int Count{};
	do
	{
		cin >> Count;
		if (Count == 0)
			break;
		if (Count == 1)
		{
			cout << "�����뿨��: ";
			string s;
			cin >> s;
			auto iter = std::find_if(card.begin(), card.end(), [&s](const Card& card1) {return card1.Get_Id() == s; });
			if (iter != card.end())
			{
				cout << "�������µ�����: ";
				string password;                   //�޸�����
				cin >> password;
				iter->Set_New_Password(password);
				cout << "�޸ĳɹ�" << endl;
			}
			else
			{
				cout << "�����ڿ����޷��޸�" << endl;
			}
		}
		if (Count == 2)                                 //�޸Ŀ�Ƭ��Ϣ
		{
			cout << "�����뿨��: ";
			string s;
			cin >> s;
			auto iter = std::find_if(card.begin(), card.end(), [&s](const Card& card1) {return card1.Get_Id() == s; });
			if (iter != card.end())
			{
				cout << "�����뿨����Ϣ: ";
				string message;
				cin >> message;
				iter->Set_Card_Message(message);
				cout << "�޸ĳɹ�" << endl;
			}
			else
			{
				cout << "�����ڿ����޷��޸�" << endl;
			}
		}
		if (Count == 3)                           //�鿴���п����
		{
			cout << "�����뿨��: ";
			string s;
			cin >> s;
			auto iter = std::find_if(card.begin(), card.end(), [&s](const Card& card1) {return card1.Get_Id() == s; });
			if (iter != card.end())
			{
				cout << "���: " << iter->Get_Surples() << endl;
			}
			else
			{
				cout << "�����ڿ���" << endl;
			}

		}
		if (Count == 4)                        //װ���ֽ�
		{
			cout << "����װ�����: " << endl;
			double rm;
			cin >> rm;

			ATM::Set(rm);
			cout << "���: " << ATM::Get_RMB() << endl;
			cout << "ת��ɹ�" << endl;

		}
		if (Count == 5)                      //ȡ���ֽ�
		{
			cout << "����ȡ������: " << endl;
			double rm;
			cin >> rm;
			if (rm > ATM::Get_RMB())
			{
				cout << "ȡ���������ʧ��" << endl;
			}
			else
			{
				ATM::Set_(rm);
				cout << "ȡ���ɹ�" << endl;
			}
			cout << "���: " << ATM::Get_RMB() << endl;
		}
		if (Count == 6)                      //��ӡ���
		{
			cout << "��ǰ���: " << ATM::Get_RMB() << endl;
		}
		cout << "���������: ";
	} while (1);
}



void Find_History(const vector<pair<Card, Handle>> history)          //��ʷ��¼��ѯ
{
	cout << "����������Ҫ���ҵļ�¼�Ŀ��� ";
	string id;
	cin >> id;
	bool test = true;
	for (auto iter = history.begin(); iter != history.end(); ++iter)      //˳�����
	{
		if (iter->first.Get_Id() == id)
		{
			test = false;
			cout << iter->first << "����ҵ��: " << iter->second.Get_Mess() << endl;
		}
	}
	if (test)
		cout << "û��������" << endl;
}




double ATM::RMB = 100000000;             //�����ʼǮ��//



void Show_Print(Card& card)              //��ӡ
{
	cout << card << endl;

}


int main()
{
	Begin();

	return 0;
}