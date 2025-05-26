#include "SignUpUI.h"

SignUpUI::SignUpUI(ifstream* input_stream, ofstream* output_stream, SignUp* sign_up) {
	//파일로부터 입력받기 위해 사용될 변수를 초기화함.
	input_stream_ = input_stream;

	//파일에 출력하기 위해 사용될 변수를 초기화함.
	output_stream_ = output_stream;

	//SignUp Control object의 함수를 호출하기 위한 변수를 초기화함.
	sign_up_ = sign_up;
}

void SignUpUI::StartInterface()
{
	//회원 가입에 필요한 필수 입력 정보를 입력받음.
	UserInput user_input;
	user_input.user_type = 'M';
	*input_stream_ >> user_input.id >> user_input.password >> user_input.phone_number;

	//입력받은 값을 내부로 전달하기 위해 함수를 호출함.
	CreateNewUser(user_input);
}

void SignUpUI::CreateNewUser(UserInput user_input)
{
	//Control object의 함수를 호출하고, Control object로부터 반환받은 값을 출력함.
	UserInput registered_user = sign_up_->AddNewUser(user_input);
	*output_stream_ << "1.1. 회원가입" << endl << "> " << registered_user.id << ' ' << registered_user.password << ' ' << registered_user.phone_number << endl << endl;
}