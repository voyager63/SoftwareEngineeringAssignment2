#include "LoginUI.h"

LoginUI::LoginUI(ifstream* input_stream, ofstream* output_stream, Login* login) {
	//파일로부터 입력받기 위해 사용될 변수를 초기화함.
	input_stream_ = input_stream;

	//파일에 출력하기 위해 사용될 변수를 초기화함.
	output_stream_ = output_stream;

	//Login Control object의 함수를 호출하기 위한 변수를 초기화함.
	login_ = login;
}

void LoginUI::StartInterface() {
	//로그인에 필요한 입력값을 입력받음.
	string user_id, user_password;
	*input_stream_ >> user_id >> user_password;

	//입력받은 값을 내부로 전달하기 위해 함수를 호출함.
	ClickLogin(user_id, user_password);
}

void LoginUI::ClickLogin(string user_id, string user_password) {
	//로그인에 성공했다면 로그인된 이용자의 ID를 출력함.
	if (login_->IsValid(user_id, user_password)) {
		*output_stream_ << "2.1. 로그인" << endl << "> " << user_id << ' ' << user_password << endl << endl;
	}
}