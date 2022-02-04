#include <iostream>
#include <fstream>
#include <json/json.h>

bool case1()
{
	Json::Value epl_table;
	epl_table["team"] = "arsenal";
	epl_table["played"] = 21;
	epl_table["Won"] = 11;
	epl_table["Drawn"] = 3;
	epl_table["Lost"] = 7;

	//
	//	해당 방법은 여러가지가 있다.
	//
	Json::Value root;
	root["Manager"] = "Mikel Arteta";
	root["Captain"] = "N/A";
	root["Vice_Captain"] = "Alexandre Lacazette";
	epl_table["squad"] = root;

	//
	//	위 결과와 같다.
	//	코딩 스타일의 차이일까?
	//
	//epl_table["squad"]["Manager"] = "Mikel Arteta";
	//epl_table["squad"]["Captain"] = "N/A";
	//epl_table["squad"]["Vice_Captain"] = "Alexandre Lacazette";

	//
	//	list 형태 추가
	//
	epl_table["record"].append("2003-04");
	epl_table["record"].append("2001-02");
	epl_table["record"].append("1997-98");

	epl_table["test"] = "remove";

	//
	//	String 으로 변환
	//
	std::string json_to_str = epl_table.toStyledString();
	std::cout << json_to_str << std::endl;

	std::ofstream outfile("arsenal.json", std::ios::out);
	if (true != outfile.is_open())
	{
		std::cout << "File Opne Failed." << std::endl;
		return false;
	}

	// outfile << epl_table;
	outfile << json_to_str;
	outfile.close();

	return true;
}

bool case2()
{
	//
	//	Json File 읽기
	//
	std::ifstream infile("arsenal.json", std::ios::in);
	if (true != infile.is_open())
	{
		std::cout << "File Opne Failed." << std::endl;
		return false;
	}

	//
	//	File 내용을 Json 객체로 변환
	//
	Json::Value root;
	infile >> root;
	infile.close();

	//
	//	Json 객체 접근
	//
	std::cout << root["team"].asString() << std::endl;
	//
	//	키 접근 시, 에러방지를 위해 이렇게 접근하면 어떨까?
	//
	if (true == root.isMember("played"))
	{
		std::cout << root["played"].asInt() << std::endl;
	}
	if (true != root.isMember("supporters"))
	{
		std::cout << "supporters not exists" << std::endl;
	}

	//
	//	Json 객체 -> String으로 변환
	//
	std::string json_to_str = root.toStyledString();
	std::cout << json_to_str << std::endl;

	return true;
}

bool case3()
{
	//
	//	Json File 읽기
	//
	std::ifstream infile("arsenal.json", std::ios::in);
	if (true != infile.is_open())
	{
		std::cout << "File Opne Failed." << std::endl;
		return false;
	}

	//
	//	File 내용을 Json 객체로 변환
	//
	Json::Value root;
	infile >> root;
	infile.close();

	//
	//	Value 수정 및 추가
	//
	if (true == root.isMember("Lost"))
	{
		root["Lost"] = 0;
	}

	if (true == root.isMember("squad"))
	{
		if (true == root["squad"].isMember("Captain"))
		{
			root["squad"]["Captain"] = "Kieran Tierney";
		}
	}

	root["supporters"] = "Gunners";
	if (true == root.isMember("record"))
	{
		root["record"].append("2021-22");
	}

	//
	//	삭제
	//
	if (true == root.isMember("test"))
	{
		root.removeMember("test");
	}

	//
	//	Json 객체 -> String으로 변환
	//
	std::string json_to_str = root.toStyledString();
	std::cout << json_to_str << std::endl;

	//
	//	파일 저장
	//
	std::ofstream outfile("arsenal.json", std::ios::out);
	if (true != outfile.is_open())
	{
		std::cout << "File Opne Failed." << std::endl;
		return false;
	}

	// outfile << epl_table;
	outfile << json_to_str;
	outfile.close();

	return true;
}

int main(int argc, char* argv[])
{
	_CrtMemState memoryState = { 0 };
	_CrtMemCheckpoint(&memoryState);
	{
		_ASSERTE(true == case1());
		_ASSERTE(true == case2());
		_ASSERTE(true == case3());
	}
	_CrtMemDumpAllObjectsSince(&memoryState);

	return 0;
}