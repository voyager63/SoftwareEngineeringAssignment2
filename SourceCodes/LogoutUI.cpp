#include "LogoutUI.h"

LogoutUI::LogoutUI(ifstream* input_stream, ofstream* output_stream, Logout* logout) {
	//파일로부터 입력받기 위해 사용될 변수를 초기화함.
	input_stream_ = input_stream;

	//파일에 출력하기 위해 사용될 변수를 초기화함.
	output_stream_ = output_stream;

	//Logout Control object의 함수를 호출하기 위한 변수를 초기화함.
	logout_ = logout;
}

void LogoutUI::StartInterface() {
	//입력받은 값을 내부로 전달하기 위해 함수를 호출함.
	ClickLogout();
}

void LogoutUI::ClickLogout() {
	//Control object의 함수를 호출하고, Control object로부터 반환받은 로그아웃된 이용자의 ID를 출력함.
	string current_user_id = logout_->ExitSystemAccess();
	*output_stream_ << "2.2. 로그아웃" << endl << "> " << current_user_id << endl << endl;
}