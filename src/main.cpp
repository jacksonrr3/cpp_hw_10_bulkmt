#include "command.h"

int main(int, char* argv[]) {
	
	auto m_file2 = std::make_shared<metric>("File2");
	auto m_file1 = std::make_shared<metric>("File1");
	auto m_log = std::make_shared<metric>("log");
	auto m_main = std::make_shared<metric>( "main", true);
	
	Command command_log(std::atoi(argv[1]), m_main);
	command_log.subscribe(std::make_unique<FileObserver>(m_file1, m_file2));
	command_log.subscribe(std::make_unique<TerminalObserver>(m_log));
	command_log.add_command();
	
	
}
