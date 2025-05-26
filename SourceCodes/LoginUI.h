#pragma once
#include "EntityObjects.h"
#include "Login.h"

class Login;

//로그인 기능을 구현하기 위한 Boundary Class
class LoginUI {
private:
	//Login Control object의 함수를 호출하기 위한 변수
	Login* login_;

	//파일로부터 입력을 받기 위한 변수
	ifstream* input_stream_;

	//Control object로부터 반환받은 값을 파일에 출력하기 위한 변수
	ofstream* output_stream_;

public:
	//생성자
	LoginUI(ifstream* input_stream, ofstream* output_stream, Login* login);

	//이용자로부터 입력을 받음.
	void StartInterface();

	//이용자의 입력을 Control object에게 전달함.
	void ClickLogin(string user_id, string user_password);
};