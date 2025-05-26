#pragma once
#include "EntityObjects.h"
#include "Logout.h"

class Logout;

//로그아웃 기능을 구현하기 위한 Boundary Class
class LogoutUI {
private:
	//Logout Control object의 함수를 호출하기 위한 변수
	Logout* logout_;

	//파일로부터 입력을 받기 위한 변수
	ifstream* input_stream_;

	//Control object로부터 반환받은 값을 파일에 출력하기 위한 변수
	ofstream* output_stream_;

public:
	//생성자
	LogoutUI(ifstream* input_stream, ofstream* output_stream, Logout* logout);

	//이용자로부터 입력을 받음.
	void StartInterface();

	//이용자의 입력을 Control object에게 전달함.
	void ClickLogout();
};
