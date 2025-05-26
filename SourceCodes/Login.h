#pragma once
#include "EntityObjects.h"
#include "LoginUI.h"

class LoginUI;

//로그인 기능을 구현하기 위한 Control Class
class Login {
private:
	//LoginUI Boundary object를 생성하고, Boundary object의 StartInterface()를 호출하기 위한 변수
	LoginUI* login_ui_;

	//UserCollection Entity Class의 함수를 호출하기 위한 변수
	UserCollection* user_collection_;

	//AccessManager Entity Class의 함수를 호출하기 위한 변수
	AccessManager* access_manager_;

public:
	//생성자
	Login(ifstream* input_stream, ofstream* output_stream, UserCollection* user_collection, AccessManager* access_manager);

	//이용자의 ID, 비밀번호를 입력받아 로그인이 성공했는지를 반환함.
	bool IsValid(string input_id, string input_password);

	//이용자가 입력한 비밀번호와 저장된 비밀번호가 일치하는지를 반환함.
	bool IsEqual(string input_password, string user_password);
};
