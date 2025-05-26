#include "SignUp.h"

SignUp::SignUp(ifstream* input_stream, ofstream* output_stream, UserCollection* user_collection) {
	//UserCollection Entity object의 함수를 호출하기 위한 변수를 초기화함.
	user_collection_ = user_collection;

	//SignUpUI Boundary object를 생성함.
	sign_up_ui_ = new SignUpUI(input_stream, output_stream, this);

	//Boundary object의 StartInterface() 함수를 호출함.
	sign_up_ui_->StartInterface();
}

UserInput SignUp::AddNewUser(UserInput user_input) {
	//함수를 호출함으로써 Entity object에게 값을 전달함.
	user_collection_->AddNewUser(user_input);

	//Boundary object에게 값을 반환함.
	return user_input;
}