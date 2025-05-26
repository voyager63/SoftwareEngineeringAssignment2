#pragma once
#include "EntityObjects.h"
#include "SignUp.h"

class SignUp;

//회원 가입 기능을 구현하기 위한 Boundary Class
class SignUpUI {
private:
	//SignUp Control object의 함수를 호출하기 위한 변수
	SignUp* sign_up_;

	//파일로부터 입력을 받기 위한 변수
	ifstream* input_stream_;

	//Control object로부터 반환받은 값을 파일에 출력하기 위한 변수
	ofstream* output_stream_;

public:
	//생성자
	SignUpUI(ifstream* input_stream, ofstream* output_stream, SignUp* sign_up);

	//사용자로부터 입력을 받음.
	void StartInterface();

	//사용자의 입력을 Control object에게 전달함.
	void CreateNewUser(UserInput user_input);
};