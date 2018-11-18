#include <iostream>
#include <Windows.h>
#include <time.h>
#include <cstring>
using namespace std;

void gotoxy(int x, int y)		// 커서 이동 함수
{
	COORD Pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void Roading()		// 로딩 그림 그려주기
{
	int i;
	bool a = true;

	gotoxy(20, 10);
	
	for(i=0; i<6; i++)
	{
		if(a == true)
		{
			cout<<"●";
			a = false;
		}
		else
		{
			cout<<"○";
			a = true;
		}
		Sleep(200);
		system("cls");
	}
}
void Randdot()		// 랜덤시간(ex. 물건고르기, 봉투에담기)
{
	srand(time(NULL));
	int i = ( (rand() % 6) + 3 );	// 랜덤시간
	int j;
	
	for(j = 0; j < i; j++)
	{
		cout<<"…";
		Sleep(500);
	}
	cout<<endl;
}

char Start()		// 제일 첫 화면
{
	char c;

	cout<<"편의점 관리 프로그램에 접속하신 걸 환영합니다."<<endl;
	cout<<"직원을 생성하시겠습니까 ? (Y/N) : ";
	cin>>c;

	return c;
}
char* Create()		// 직원 생성 화면
{
	char name[30];

	cout<<"성함을 입력해 주세요 : ";
	cin>>name;

	system("cls");

	return name;
}

namespace 객체지향_7조		// 네임스페이스
{
	class POS	// 포스객체
	{
	private:
		int money;	// 포스기안에 금액
		int pro_money;	// 프로그램의 금액
		int select;		// 선택
		int safe_money;		// 금고 금액

		int sel_num;	// 고를 물건의 갯수
		int *one;	// 카테고리 고르기(과자, 음료, 아이스크림 등)
		int *two;	// 물품고르기(새우깡, 오렌지쥬스 등)

		char *(*item)[5];	// 과자들
		int (*price)[5];	// 가격들
		int (*cprice)[5];	// 원가
		int (*num)[5];		// 물품갯수

		char *name;		// 직원이름

		int send;		// 손님이 낼 금액
		int pro_imsi;	// 포스기 프로그램에 넣을 돈
		int change;		// 거슬러 줄돈

	public:
		static int day;		// 근무 일수 (공유 변수)
		static int gtime;	// 근무 시간 (공유 변수)
		void Showmoney();	// 잔고 출력
		void Menu();		// 메뉴 출력	
		void ComeGuest();		// 손님받을때 함수
		void Gowork();		// 출근
		void Set();			// 초기화(과자, 가격)
		void Sel();			// 손님이 물건고르는 것 랜덤
		void Setmoney();	// 포스기 초기금액 설정
		void Sending();		// 손님이 낼돈 랜덤
		void Search();		// 재고조사하기
		void MoneyChk();	// 시재점검하기
		void Refill();		// 물품 채우기

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
	int POS::day = 0;		// 초기화
	int POS::gtime = 0;		// 초기화

	void POS::Showmoney()
	{
		cout<<"현재 돈통의 잔액 : "<<money<<endl;
	}
	void POS::Menu()
	{
		while(true)
		{
			cout<<"편의점 관리 프로그램\t"<<day<<"일 째"<<endl;
			cout<<"1. 출근하기"<<endl;
			cout<<"2. 하루쉬기"<<endl;
			cout<<"3. 게임종료"<<endl;
			cout<<"선택 : ";
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
				cout<<"1~3까지 입력하세요"<<endl;
				return;
			}
			day++;
			system("cls");
		} // while 문 끝
	}
	
	void POS::Gowork()
	{
		while(true)
		{
			cout<<"1. 손님 받기"<<endl;
			cout<<"2. POS기 금액 조사"<<endl;
			cout<<"3. 재고 조사"<<endl;
			cout<<"4. 시재 점검"<<endl;
			cout<<"5. 물품채우기"<<endl;
			cout<<"6. 퇴근하기"<<endl;
			cout<<"선택 : ";
				
			cin>>select;
					
			switch(select)
			{
			case 1:				// 손님받기 선택
				ComeGuest();
				gtime++;		// gtime이 5가 되면 퇴근
				break;
			case 2:				// POS기 금액 조사 선택
				Showmoney();
				break;
			case 3:				// 재고 조사 선택
				Search();
				break;
			case 4:				// 시재 점검 선택
				MoneyChk();
				break;
			case 5:				// 물품 채우기 선택
				Refill();
				break;
			case 6:				// 퇴근하기 선택
				return;
			default:
				break;
			}
			Sleep(500);
			system("cls");
			if(gtime >= 5)		// 5번 일했으니 퇴근
			{
				gtime = 0;
				cout<<"밤이 되었습니다.."<<endl;
				cout<<"퇴근합니다~"<<endl;
					
				safe_money = money - 100000;	// 번돈 금고에 넣기
				money = pro_money = 100000;		// 금고에 넣었으니 10만으로 다시 초기화

				Sleep(400);
				system("cls");
				return;
			}
		} // while 문 끝
	}
	void POS::ComeGuest()		// 손님 받기
	{
		int i;
		
		pro_imsi = 0;

		cout<<"딸랑~"<<endl;
		cout<<"손님이 오셨습니다"<<endl;
		cout<<"손님이 물건 고르는 중"; //Randdot(); // 이거 다시 주석 풀어놓기
		POS::Sel();
		if(sel_num == 0)
		{
			cout<<"\n손님이 물건을 고르지 않고 그냥 나갔습니다."<<endl;
			return;
		}
		cout<<"손님이 고른 물품들"<<endl;
		for(i=0; i<sel_num; i++)
		{
			int j, k;
			j = one[i];		// 랜덤 숫자를 j에 넣음
			k = two[i];

			printf("%s             \t %4d원\n", item[j][k], price[j][k]);		// 물품들 출력
		}
		for(i=0; i< sel_num; i++)
		{
			pro_imsi += price[one[i]][two[i]];	// 임시 머니에 총 물품액 저장
			num[one[i]][two[i]] -= 1;		// 판매물품 재고 -1
		}
		pro_money += pro_imsi;				// 포스기 프로그램돈에 플러스

		Sending();		// 손님이 낼 금액 랜덤으로 정하기
		money += send;
		cout<<"손님이 "<<send<<"원 을 내셨습니다."<<endl;
		cout<<"거스름돈 : ";
		cin>>change;
		money -= change;

		cout<<"봉투에 담는 중"; //Randdot();
		cout<<"안녕히 가세요~"<<endl;
	}

	void POS::Sel()			// 손님이 물건고르는 것 랜덤
	{
		int i, j, k;
		srand(time(NULL));
		sel_num = (rand() % 7);		// 손님이 물품고를때 고를 갯수 랜덤
		
		one = new int [sel_num];	// num만큼 동적할당
		two = new int [sel_num];

		for(k=0; k<sel_num; k++)	// k로 카운트 해주면서 고를 갯수만큼만 one two에 숫자 넣기
		{											// 숫자 = 물픔번호
			i = (rand() % 5);		// i는 카데고리, j는 물품번호
			j = (rand() % 5);		// 0은 미지수.. 물품 받으면 입력해줘야함********************************************************
									// i와 j에 랜덤 넣기
			one[k] = i;
			two[k] = j;
		}
	}

	void POS::Setmoney()		// 포스기 기본금액 설정
	{
		money = 100000;
		pro_money = 100000;
		safe_money = 100000;
	}

	void POS::Sending()			// 손님이 낼 금액 랜덤
	{
		send = (rand() % (pro_imsi * 2)) + pro_imsi;
	}

	void POS::Search()
	{
		int i;
		int s_sel;

		cout<<"카데고리 선택"<<endl;
		cout<<"1. 과자류"<<endl;
		cout<<"2. 아이스크림류"<<endl;
		cout<<"3. 음료류"<<endl;
		cout<<"4. 담배류"<<endl;
		cout<<"5. 주류"<<endl;
		cout<<"선택 : "<<endl;
		cin>>s_sel;

		system("cls");

		if(s_sel == 1)
		{
			cout<<"과자류"<<endl;
			cout<<"-------------------------"<<endl;
			for(i=0; i<5; i++)
			{
				printf("%s     \t\t%3d개\n", item[0][i], num[0][i]);
			}
		}
		else if(s_sel == 2)
		{
			cout<<"아이스크림 류"<<endl;
			cout<<"-------------------------"<<endl;
			for(i=0; i<5; i++)
			{
				printf("%s     \t\t%3d개\n", item[1][i], num[1][i]);
			}
		}
		else if(s_sel == 3)
		{
			cout<<"음료 류"<<endl;
			cout<<"-------------------------"<<endl;
			for(i=0; i<5; i++)
			{
				printf("%s     \t\t%3d개\n", item[2][i], num[2][i]);
			}
		}
		else if(s_sel == 4)
		{
			cout<<"담배 류"<<endl;
			cout<<"-------------------------"<<endl;
			for(i=0; i<5; i++)
			{
				printf("%s     \t\t%3d개\n", item[3][i], num[3][i]);
			}
		}
		else if(s_sel == 5)
		{
			cout<<"주류"<<endl;
			cout<<"-------------------------"<<endl;
			for(i=0; i<5; i++)
			{
				printf("%s     \t\t%3d개\n", item[4][i], num[4][i]);
			}
		}
		else
		{
			cout<<"정확한 숫자를 입력하십시오"<<endl;
		}
		system("pause");
	}

	void POS::MoneyChk()		// 시재점검 하기
	{
		cout<<"시재 점검 중입니다.."<<endl;
		Sleep(300);
		cout<<"포스기 금액 : "<<pro_money<<endl;
		cout<<"돈통   금액 : "<<money<<endl;
		cout<<"시재   차이 : "<<money - pro_money<<endl;
		Sleep(500);
	}

	void POS::Refill()		// 물품 채우기
	{
		int i, j;
		int sel;
		int c_num;	// 구매갯수 입력받기
		char c_in;

		cout<<"현재 금고 잔액 : "<<safe_money<<"원"<<endl<<endl;

		cout<<"1. 과자"<<endl;
		cout<<"2. 아이스크림"<<endl;
		cout<<"3. 음료"<<endl;
		cout<<"4. 담배"<<endl;
		cout<<"5. 술"<<endl;
		cout<<"6. 돌아가기"<<endl;
		cout<<"카테고리 선택 : ";
		cin>>sel;

		switch(sel)
		{
		case 1:			// 과자
			cout<<"과자류"<<endl;
			cout<<"--------------------"<<endl;
			j = 0;		// 과자 배열번호로

			for(i=0; i<5; i++)
			{
				printf("%d. %s   \t\t %4d원\n", i, item[j][i], cprice[j][i]);
			}
			break;
		case 2:			// 아이스크림
			cout<<"아이스크림 류"<<endl;
			cout<<"--------------------"<<endl;
			j = 1;

			for(i=0; i<5; i++)
			{
				printf("%d. %s       \t %5d원\n", i, item[j][i], cprice[j][i]);
			}
			break;
		case 3:			// 음료
			cout<<"음료 류"<<endl;
			cout<<"--------------------"<<endl;
			j = 2;

			for(i=0; i<5; i++)
			{
				printf("%d. %s       \t %5d원\n", i, item[j][i], cprice[j][i]);
			}
			break;
		case 4:			// 담배
			cout<<"담배류"<<endl;
			cout<<"--------------------"<<endl;
			j = 3;

			for(i=0; i<5; i++)
			{
				printf("%d. %s          \t%4d원\n", i, item[j][i], cprice[j][i]);
			}
			break;
		case 5:			// 술
			cout<<"주 류"<<endl;
			cout<<"--------------------"<<endl;
			j = 4;

			for(i=0; i<5; i++)
			{
				printf("%d. %s          \t %4d원\n", i, item[j][i], cprice[j][i]);
			}
			break;
		case 6:
			return;
		default:
			cout<<"제대로된 숫자를 입력하세요"<<endl;
			return;
		}
		
		cout<<"물품 번호를 입력하세요 : ";
		cin>>i;
		if(i >= 5 || i <= -1)		// 물품번호 잘못 입력시
		{
			cout<<"물품 번호를 잘못 입력하셨습니다."<<endl;
			return;
		}

		cout<<item[j][i]<<"    개당 "<<cprice[j][i]<<"원 입니다"<<endl;

		cout<<"몇개를 구매 하시겠습니까? ";
		cin>>c_num;

		cout<<c_num<<"개 "<<c_num * cprice[j][i]<<"원 입니다"<<endl;
		cout<<"구매 하시겠습니까 (Y/N) ? ";
		cin>>c_in;

		if(c_in == 'y' || c_in == 'Y')
		{
			safe_money = safe_money - (c_num * cprice[j][i]);		// 금고 금액 차감
			num[j][i] = num[j][i] + c_num;		// 재고 플러스
			cout<<"구매 완료되었습니다"<<endl;
			Sleep(400);
		}
		else
		{
			cout<<"구매를 취소합니다"<<endl;
			return;
		}
	}
}

using namespace 객체지향_7조;

int main(void)
{
	int i, j;	// 카운트
	char c;
	char name[30];

	char * item[5][5] = { {"새우깡","콘칩","바나나킥","빼빼로","초코킥"},					// 상품배열 // 과자
						  {"죠스바","수박바","브라보콘","누가바","스크류바"},				// 아이스크림
						  {"비타민워터","코카콜라","레드불","칠성사이다","웰치스"},		// 음료
						  {"말보루레드","시가No.6","팔리아멘트","한라산","디스"},	// 담배
						  {"참이슬","카스","처음처럼","맥스","막걸리"}					// 술
						};
	
	int price[5][5] = {{1000, 1100, 900, 1000, 1200},			// 가격 배열
					   {800, 700, 1200, 600, 700},
				   	   {1200, 900, 1000, 800, 700},
					   {2500, 2500, 2500, 1500, 2000},
					   {1300, 1100, 1300, 1200, 1100}
					  };

	int cprice[5][5]={	{700,770,630,700,840},					// 원가
						{400,350,600,300,350},
						{960,720,800,640,560},
						{2250,2070,2700,1350,1800},
						{780,660,780,720,660}};

	int num[5][5];									// 물품갯수
	
	for(i=0; i<5; i++)					// 20으로 초기화
	{
		for(j=0; j<5; j++)
		{
			num[i][j] = 20;
		}
	}

	c = Start();
	
	if(c == 'N' || c == 'n')	// 직원 생성 안하면 종료
	{
		return 0;
	}
	else
	{
		strcpy(name, Create());
		cout<<"생성된 직원의 이름은 "<<name<<" 입니다."<<endl;
	}
	

	POS *a = new POS(name, item, price, cprice, num);
	a->Setmoney();	// 포스기 초기 금액 설정

	a->Menu();		// 프로그램 시작

	return 0;
}