#include <iostream>
#include <Windows.h>
#include <time.h>
#include <cstring>
using namespace std;

void gotoxy(int x, int y)		// Ŀ�� �̵� �Լ�
{
	COORD Pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void Roading()		// �ε� �׸� �׷��ֱ�
{
	int i;
	bool a = true;

	gotoxy(20, 10);
	
	for(i=0; i<6; i++)
	{
		if(a == true)
		{
			cout<<"��";
			a = false;
		}
		else
		{
			cout<<"��";
			a = true;
		}
		Sleep(200);
		system("cls");
	}
}
void Randdot()		// �����ð�(ex. ���ǰ���, ���������)
{
	srand(time(NULL));
	int i = ( (rand() % 6) + 3 );	// �����ð�
	int j;
	
	for(j = 0; j < i; j++)
	{
		cout<<"��";
		Sleep(500);
	}
	cout<<endl;
}

char Start()		// ���� ù ȭ��
{
	char c;

	cout<<"������ ���� ���α׷��� �����Ͻ� �� ȯ���մϴ�."<<endl;
	cout<<"������ �����Ͻðڽ��ϱ� ? (Y/N) : ";
	cin>>c;

	return c;
}
char* Create()		// ���� ���� ȭ��
{
	char name[30];

	cout<<"������ �Է��� �ּ��� : ";
	cin>>name;

	system("cls");

	return name;
}

namespace ��ü����_7��		// ���ӽ����̽�
{
	class POS	// ������ü
	{
	private:
		int money;	// ������ȿ� �ݾ�
		int pro_money;	// ���α׷��� �ݾ�
		int select;		// ����
		int safe_money;		// �ݰ� �ݾ�

		int sel_num;	// �� ������ ����
		int *one;	// ī�װ� ����(����, ����, ���̽�ũ�� ��)
		int *two;	// ��ǰ����(�����, �������꽺 ��)

		char *(*item)[5];	// ���ڵ�
		int (*price)[5];	// ���ݵ�
		int (*cprice)[5];	// ����
		int (*num)[5];		// ��ǰ����

		char *name;		// �����̸�

		int send;		// �մ��� �� �ݾ�
		int pro_imsi;	// ������ ���α׷��� ���� ��
		int change;		// �Ž��� �ٵ�

	public:
		static int day;		// �ٹ� �ϼ� (���� ����)
		static int gtime;	// �ٹ� �ð� (���� ����)
		void Showmoney();	// �ܰ� ���
		void Menu();		// �޴� ���	
		void ComeGuest();		// �մԹ����� �Լ�
		void Gowork();		// ���
		void Set();			// �ʱ�ȭ(����, ����)
		void Sel();			// �մ��� ���ǰ��� �� ����
		void Setmoney();	// ������ �ʱ�ݾ� ����
		void Sending();		// �մ��� ���� ����
		void Search();		// ��������ϱ�
		void MoneyChk();	// ���������ϱ�
		void Refill();		// ��ǰ ä���

		POS(char* name, char *item[5][5], int (*price)[5], int (*cprice)[5], int (*num)[5])
		{
			this->item = item;
			this->price = price;
			this->cprice = cprice;
			this->num = num;
		}
		~POS()
		{
			delete [] name;

			delete [] one;
			delete [] two;

			delete [] item;
			delete [] price;
			delete [] cprice;
			delete [] num;
		}
		
	};
	int POS::day = 0;		// �ʱ�ȭ
	int POS::gtime = 0;		// �ʱ�ȭ

	void POS::Showmoney()
	{
		cout<<"���� ������ �ܾ� : "<<money<<endl;
	}
	void POS::Menu()
	{
		while(true)
		{
			cout<<"������ ���� ���α׷�\t"<<day<<"�� °"<<endl;
			cout<<"1. ����ϱ�"<<endl;
			cout<<"2. �Ϸ罬��"<<endl;
			cout<<"3. ��������"<<endl;
			cout<<"���� : ";
			cin>>select;
			switch(select)
			{
			case 1:
				Roading();
				Gowork();
				break;
			case 2:
				Roading();
				break;
			case 3:
				exit(0);
			default:
				cout<<"1~3���� �Է��ϼ���"<<endl;
				return;
			}
			day++;
			system("cls");
		} // while �� ��
	}
	
	void POS::Gowork()
	{
		while(true)
		{
			cout<<"1. �մ� �ޱ�"<<endl;
			cout<<"2. POS�� �ݾ� ����"<<endl;
			cout<<"3. ��� ����"<<endl;
			cout<<"4. ���� ����"<<endl;
			cout<<"5. ��ǰä���"<<endl;
			cout<<"6. ����ϱ�"<<endl;
			cout<<"���� : ";
				
			cin>>select;
					
			switch(select)
			{
			case 1:				// �մԹޱ� ����
				ComeGuest();
				gtime++;		// gtime�� 5�� �Ǹ� ���
				break;
			case 2:				// POS�� �ݾ� ���� ����
				Showmoney();
				break;
			case 3:				// ��� ���� ����
				Search();
				break;
			case 4:				// ���� ���� ����
				MoneyChk();
				break;
			case 5:				// ��ǰ ä��� ����
				Refill();
				break;
			case 6:				// ����ϱ� ����
				return;
			default:
				break;
			}
			Sleep(500);
			system("cls");
			if(gtime >= 5)		// 5�� �������� ���
			{
				gtime = 0;
				cout<<"���� �Ǿ����ϴ�.."<<endl;
				cout<<"����մϴ�~"<<endl;
					
				safe_money = money - 100000;	// ���� �ݰ� �ֱ�
				money = pro_money = 100000;		// �ݰ� �־����� 10������ �ٽ� �ʱ�ȭ

				Sleep(400);
				system("cls");
				return;
			}
		} // while �� ��
	}
	void POS::ComeGuest()		// �մ� �ޱ�
	{
		int i;
		
		pro_imsi = 0;

		cout<<"����~"<<endl;
		cout<<"�մ��� ���̽��ϴ�"<<endl;
		cout<<"�մ��� ���� ���� ��"; //Randdot(); // �̰� �ٽ� �ּ� Ǯ�����
		POS::Sel();
		if(sel_num == 0)
		{
			cout<<"\n�մ��� ������ ���� �ʰ� �׳� �������ϴ�."<<endl;
			return;
		}
		cout<<"�մ��� �� ��ǰ��"<<endl;
		for(i=0; i<sel_num; i++)
		{
			int j, k;
			j = one[i];		// ���� ���ڸ� j�� ����
			k = two[i];

			printf("%s             \t %4d��\n", item[j][k], price[j][k]);		// ��ǰ�� ���
		}
		for(i=0; i< sel_num; i++)
		{
			pro_imsi += price[one[i]][two[i]];	// �ӽ� �ӴϿ� �� ��ǰ�� ����
			num[one[i]][two[i]] -= 1;		// �ǸŹ�ǰ ��� -1
		}
		pro_money += pro_imsi;				// ������ ���α׷����� �÷���

		Sending();		// �մ��� �� �ݾ� �������� ���ϱ�
		money += send;
		cout<<"�մ��� "<<send<<"�� �� ���̽��ϴ�."<<endl;
		cout<<"�Ž����� : ";
		cin>>change;
		money -= change;

		cout<<"������ ��� ��"; //Randdot();
		cout<<"�ȳ��� ������~"<<endl;
	}

	void POS::Sel()			// �մ��� ���ǰ��� �� ����
	{
		int i, j, k;
		srand(time(NULL));
		sel_num = (rand() % 7);		// �մ��� ��ǰ���� �� ���� ����
		
		one = new int [sel_num];	// num��ŭ �����Ҵ�
		two = new int [sel_num];

		for(k=0; k<sel_num; k++)	// k�� ī��Ʈ ���ָ鼭 �� ������ŭ�� one two�� ���� �ֱ�
		{											// ���� = ���Ĺ�ȣ
			i = (rand() % 5);		// i�� ī����, j�� ��ǰ��ȣ
			j = (rand() % 5);		// 0�� ������.. ��ǰ ������ �Է��������********************************************************
									// i�� j�� ���� �ֱ�
			one[k] = i;
			two[k] = j;
		}
	}

	void POS::Setmoney()		// ������ �⺻�ݾ� ����
	{
		money = 100000;
		pro_money = 100000;
		safe_money = 100000;
	}

	void POS::Sending()			// �մ��� �� �ݾ� ����
	{
		send = (rand() % (pro_imsi * 2)) + pro_imsi;
	}

	void POS::Search()
	{
		int i;
		int s_sel;

		cout<<"ī���� ����"<<endl;
		cout<<"1. ���ڷ�"<<endl;
		cout<<"2. ���̽�ũ����"<<endl;
		cout<<"3. �����"<<endl;
		cout<<"4. ����"<<endl;
		cout<<"5. �ַ�"<<endl;
		cout<<"���� : "<<endl;
		cin>>s_sel;

		system("cls");

		if(s_sel == 1)
		{
			cout<<"���ڷ�"<<endl;
			cout<<"-------------------------"<<endl;
			for(i=0; i<5; i++)
			{
				printf("%s     \t\t%3d��\n", item[0][i], num[0][i]);
			}
		}
		else if(s_sel == 2)
		{
			cout<<"���̽�ũ�� ��"<<endl;
			cout<<"-------------------------"<<endl;
			for(i=0; i<5; i++)
			{
				printf("%s     \t\t%3d��\n", item[1][i], num[1][i]);
			}
		}
		else if(s_sel == 3)
		{
			cout<<"���� ��"<<endl;
			cout<<"-------------------------"<<endl;
			for(i=0; i<5; i++)
			{
				printf("%s     \t\t%3d��\n", item[2][i], num[2][i]);
			}
		}
		else if(s_sel == 4)
		{
			cout<<"��� ��"<<endl;
			cout<<"-------------------------"<<endl;
			for(i=0; i<5; i++)
			{
				printf("%s     \t\t%3d��\n", item[3][i], num[3][i]);
			}
		}
		else if(s_sel == 5)
		{
			cout<<"�ַ�"<<endl;
			cout<<"-------------------------"<<endl;
			for(i=0; i<5; i++)
			{
				printf("%s     \t\t%3d��\n", item[4][i], num[4][i]);
			}
		}
		else
		{
			cout<<"��Ȯ�� ���ڸ� �Է��Ͻʽÿ�"<<endl;
		}
		system("pause");
	}

	void POS::MoneyChk()		// �������� �ϱ�
	{
		cout<<"���� ���� ���Դϴ�.."<<endl;
		Sleep(300);
		cout<<"������ �ݾ� : "<<pro_money<<endl;
		cout<<"����   �ݾ� : "<<money<<endl;
		cout<<"����   ���� : "<<money - pro_money<<endl;
		Sleep(500);
	}

	void POS::Refill()		// ��ǰ ä���
	{
		int i, j;
		int sel;
		int c_num;	// ���Ű��� �Է¹ޱ�
		char c_in;

		cout<<"���� �ݰ� �ܾ� : "<<safe_money<<"��"<<endl<<endl;

		cout<<"1. ����"<<endl;
		cout<<"2. ���̽�ũ��"<<endl;
		cout<<"3. ����"<<endl;
		cout<<"4. ���"<<endl;
		cout<<"5. ��"<<endl;
		cout<<"6. ���ư���"<<endl;
		cout<<"ī�װ� ���� : ";
		cin>>sel;

		switch(sel)
		{
		case 1:			// ����
			cout<<"���ڷ�"<<endl;
			cout<<"--------------------"<<endl;
			j = 0;		// ���� �迭��ȣ��

			for(i=0; i<5; i++)
			{
				printf("%d. %s   \t\t %4d��\n", i, item[j][i], cprice[j][i]);
			}
			break;
		case 2:			// ���̽�ũ��
			cout<<"���̽�ũ�� ��"<<endl;
			cout<<"--------------------"<<endl;
			j = 1;

			for(i=0; i<5; i++)
			{
				printf("%d. %s       \t %5d��\n", i, item[j][i], cprice[j][i]);
			}
			break;
		case 3:			// ����
			cout<<"���� ��"<<endl;
			cout<<"--------------------"<<endl;
			j = 2;

			for(i=0; i<5; i++)
			{
				printf("%d. %s       \t %5d��\n", i, item[j][i], cprice[j][i]);
			}
			break;
		case 4:			// ���
			cout<<"����"<<endl;
			cout<<"--------------------"<<endl;
			j = 3;

			for(i=0; i<5; i++)
			{
				printf("%d. %s          \t%4d��\n", i, item[j][i], cprice[j][i]);
			}
			break;
		case 5:			// ��
			cout<<"�� ��"<<endl;
			cout<<"--------------------"<<endl;
			j = 4;

			for(i=0; i<5; i++)
			{
				printf("%d. %s          \t %4d��\n", i, item[j][i], cprice[j][i]);
			}
			break;
		case 6:
			return;
		default:
			cout<<"����ε� ���ڸ� �Է��ϼ���"<<endl;
			return;
		}
		
		cout<<"��ǰ ��ȣ�� �Է��ϼ��� : ";
		cin>>i;
		if(i >= 5 || i <= -1)		// ��ǰ��ȣ �߸� �Է½�
		{
			cout<<"��ǰ ��ȣ�� �߸� �Է��ϼ̽��ϴ�."<<endl;
			return;
		}

		cout<<item[j][i]<<"    ���� "<<cprice[j][i]<<"�� �Դϴ�"<<endl;

		cout<<"��� ���� �Ͻðڽ��ϱ�? ";
		cin>>c_num;

		cout<<c_num<<"�� "<<c_num * cprice[j][i]<<"�� �Դϴ�"<<endl;
		cout<<"���� �Ͻðڽ��ϱ� (Y/N) ? ";
		cin>>c_in;

		if(c_in == 'y' || c_in == 'Y')
		{
			safe_money = safe_money - (c_num * cprice[j][i]);		// �ݰ� �ݾ� ����
			num[j][i] = num[j][i] + c_num;		// ��� �÷���
			cout<<"���� �Ϸ�Ǿ����ϴ�"<<endl;
			Sleep(400);
		}
		else
		{
			cout<<"���Ÿ� ����մϴ�"<<endl;
			return;
		}
	}
}

using namespace ��ü����_7��;

int main(void)
{
	int i, j;	// ī��Ʈ
	char c;
	char name[30];

	char * item[5][5] = { {"�����","��Ĩ","�ٳ���ű","������","����ű"},					// ��ǰ�迭 // ����
						  {"�ҽ���","���ڹ�","�����","������","��ũ����"},				// ���̽�ũ��
						  {"��Ÿ�ο���","��ī�ݶ�","�����","ĥ�����̴�","��ġ��"},		// ����
						  {"�����緹��","�ð�No.6","�ȸ��Ƹ�Ʈ","�Ѷ��","��"},	// ���
						  {"���̽�","ī��","ó��ó��","�ƽ�","���ɸ�"}					// ��
						};
	
	int price[5][5] = {{1000, 1100, 900, 1000, 1200},			// ���� �迭
					   {800, 700, 1200, 600, 700},
				   	   {1200, 900, 1000, 800, 700},
					   {2500, 2500, 2500, 1500, 2000},
					   {1300, 1100, 1300, 1200, 1100}
					  };

	int cprice[5][5]={	{700,770,630,700,840},					// ����
						{400,350,600,300,350},
						{960,720,800,640,560},
						{2250,2070,2700,1350,1800},
						{780,660,780,720,660}};

	int num[5][5];									// ��ǰ����
	
	for(i=0; i<5; i++)					// 20���� �ʱ�ȭ
	{
		for(j=0; j<5; j++)
		{
			num[i][j] = 20;
		}
	}

	c = Start();
	
	if(c == 'N' || c == 'n')	// ���� ���� ���ϸ� ����
	{
		return 0;
	}
	else
	{
		strcpy(name, Create());
		cout<<"������ ������ �̸��� "<<name<<" �Դϴ�."<<endl;
	}
	

	POS *a = new POS(name, item, price, cprice, num);
	a->Setmoney();	// ������ �ʱ� �ݾ� ����

	a->Menu();		// ���α׷� ����

	return 0;
}