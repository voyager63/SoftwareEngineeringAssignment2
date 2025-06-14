#include "SignUpUI.h"
#include "SignUp.h"
#include "LoginUI.h"
#include "Login.h"
#include "LogoutUI.h"
#include "Logout.h"
#include "RegisterBikeUI.h"
#include "RegisterBike.h"
#include "RentBikeUI.h"
#include "RentBike.h"
#include "CheckBikeRentalInformationUI.h"
#include "CheckBikeRentalInformation.h"
#include "ExitUI.h"
#include "Exit.h"


int main() {

	ifstream in_fp;
	ofstream out_fp;

	in_fp.open("input.txt");
	out_fp.open("output.txt");

	int menu_level_1 = 0, menu_level_2 = 0;
	int is_program_exit = 0;

	//이용자 컬렉션 생성. 관리자를 등록함.
	UserCollection user_collection("admin", "admin");

	//자전거 컬렉션 생성
	BikeCollection bike_collection;

	//AccessManager 생성
	AccessManager access_manager;

	while (!is_program_exit)
	{
		in_fp >> menu_level_1 >> menu_level_2;

		switch (menu_level_1)
		{
		case 1:
		{
			switch (menu_level_2)
			{
			case 1: //회원 가입
			{
				//Control object 생성
				SignUp sign_up(&in_fp, &out_fp, &user_collection);
				break;
			}
			}
			break;
		}
		case 2:
		{
			switch (menu_level_2)
			{
			case 1: //로그인
			{
				//Control object 생성
				Login login(&in_fp, &out_fp, &user_collection, &access_manager);
				break;
			}
			case 2: //로그아웃
			{
				//Control object 생성
				Logout logout(&in_fp, &out_fp, &access_manager);
				break;
			}
			}
			break;
		}
		case 3:
		{
			switch (menu_level_2)
			{
			case 1: //자전거 등록
			{
				//Control object 생성
				RegisterBike register_bike(&in_fp, &out_fp, &bike_collection, &access_manager);
				break;
			}
			}
			break;
		}
		case 4:
		{
			switch (menu_level_2)
			{
			case 1: //자전거 대여
			{
				//Control object 생성
				RentBike rent_bike(&in_fp, &out_fp, &bike_collection, &access_manager);
				break;
			}
			}
			break;
		}
		case 5:
		{
			switch (menu_level_2)
			{
			case 1: //대여 중인 자전거 조회
			{
				//Control object 생성
				CheckBikeRentalInformation check_bike_rental_information(&in_fp, &out_fp, &access_manager);
				break;
			}
			}
			break;
		}
		case 6:
		{
			switch (menu_level_2)
			{
			case 1: //종료
			{
				//Control object 생성
				Exit(&in_fp, &out_fp, &is_program_exit);
				break;
			}
			}
			break;
		}
		}
	}


	out_fp.close();
	in_fp.close();

	return 0;
}