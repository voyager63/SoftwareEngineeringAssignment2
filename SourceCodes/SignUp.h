#pragma once
#include "EntityObjects.h"
#include "SignUpUI.h"

class SignUpUI;

//회원 가입 기능을 구현하기 위한 Control Class
class SignUp {
private:
	//SignUpUI Boundary object를 생성하고, Boundary object의 StartInterface()를 호출하기 위한 변수
	SignUpUI* sign_up_ui_;

	//UserCollection Entity Class의 함수를 호출하기 위한 변수
	UserCollection* user_collection_;

public:
	//생성자
	SignUp(ifstream* input_stream, ofstream* output_stream, UserCollection* user_collection);

	//Boundary object로부터 받은 값을 Entity object에게 전달함.
	UserInput AddNewUser(UserInput user_input);
};