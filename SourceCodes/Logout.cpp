#include "Logout.h"

Logout::Logout(ifstream* input_stream, ofstream* output_stream, AccessManager* access_manager) {
	//AccessManager Entity object의 함수를 호출하기 위한 변수를 초기화함.
	access_manager_ = access_manager;

	//LogoutUI Boundary object를 생성함.
	logout_ui_ = new LogoutUI(input_stream, output_stream, this);

	//Boundary object의 StartInterface() 함수를 호출함.
	logout_ui_->StartInterface();
}

string Logout::ExitSystemAccess() {
	//AccessManager Entity Class로부터 현재 로그인된 이용자를 받음.
	User* current_user = access_manager_->GetCurrentUser();

	//현재 로그인된 이용자의 ID를 받음.
	string current_user_id = current_user->GetId();

	//현재 로그인된 이용자를 로그아웃시킴.
	access_manager_->Disconnect();

	//로그아웃된 이용자의 ID를 반환함.
	return current_user_id;
}