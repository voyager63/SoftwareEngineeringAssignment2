#include "SharedBikeRentalSystem.h"
#include <stdio.h>
#include <string.h>
#include <fstream>

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

	while (!is_program_exit)
	{
		in_fp >> menu_level_1 >> menu_level_2;

		switch (menu_level_1)
		{
			case 1:
			{
				switch (menu_level_2)
				{
					case 1: //회원가입
					{


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

					}
					case 2: //로그아웃
					{

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


					}
				}
				break;
			}
			case 5:
			{
				switch (menu_level_2)
				{
					case 1: //대여 중인 자전거 정보 조회
					{


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
						is_program_exit = 1;
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