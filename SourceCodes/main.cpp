#include "SharedBikeRentalSystem.h"

#define MAX_STRING 32
#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

ifstream in_fp;
ofstream out_fp;


int main(){
	in_fp.open(INPUT_FILE_NAME);
	out_fp.open(OUTPUT_FILE_NAME);

	int menu_level_1 = 0, menu_level_2 = 0;
	int is_program_exit = 0;

	//�̿��� �÷��� ����. �����ڸ� �����.
	UserCollection user_collection("admin", "admin");

	//������ �÷��� ����
	BikeCollection bike_collection;

	//AccessManager ����
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
					case 1: //ȸ�� ����
					{
						//Control object ����
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
					case 1: //�α���
					{
						//Control object ����
						Login login(&in_fp, &out_fp, &user_collection, &access_manager);
						break;
					}
					case 2: //�α׾ƿ�
					{
						//Control object ����
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
					case 1: //������ ���
					{
						//Control object ����
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
					case 1: //������ �뿩
					{
						//Control object ����
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
					case 1: //�뿩 ���� ������ ���� ��ȸ
					{
						//Control object ����
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
					case 1: //����
					{
						//Control object ����
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