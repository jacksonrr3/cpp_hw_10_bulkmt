#include "command.h"

int main(int, char* argv[]) {


	//Command command_log(std::atoi(argv[1]));

	metric m_main{ "main", true };
	//auto m_log = new metric("log");
	//auto m_file1 = new metric("File1");
	//auto m_file2 = new metric("File2");

	Command command_log(3, m_main);
	command_log.subscribe(std::make_unique<FileObserver>(2));
	//command_log.subscribe(std::make_unique<FileObserver>());
	command_log.subscribe(std::make_unique<TerminalObserver>());
	command_log.add_command();
	
	//command_log.~Command();

	//m_main.~metric();
	//delete m_log
	//delete m_file1;
	//delete m_file2;

	return 0;
}
