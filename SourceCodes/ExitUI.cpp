#include "ExitUI.h"


ExitUI::ExitUI(ifstream* input_stream, ofstream* output_stream, Exit* exit) {
	//파일로부터 입력받기 위해 사용될 변수를 초기화함.
	input_stream_ = input_stream;

	//파일에 출력하기 위해 사용될 변수를 초기화함.
	output_stream_ = output_stream;

	//Exit Control object의 함수를 호출하기 위한 변수를 초기화함.
	exit_ = exit;
}

void ExitUI::StartInterface() {
	//입력받은 값을 내부로 전달하기 위해 함수를 호출함.
	ExitSystem();
}

void ExitUI::ExitSystem() {
	//Control object의 함수를 호출함.
	exit_->ExitSystem();

	//시스템이 종료되었음을 화면에 출력함.
	*output_stream_ << "6.1. 종료";
}