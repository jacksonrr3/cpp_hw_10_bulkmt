#pragma once
#include <string>
#include <iostream>
#include <mutex>

std::mutex console_m;


class metric {
public:
	int _str_ch=0;
	int _cmd_ch=0;
	int _block_ch=0;
	std::string _name;
	const bool _is_main;
	
	metric( const std::string name, bool is_main = false):_is_main(is_main), _name(name) {}

	~metric() {
		
		std::cout << _name << " thread - ";
		if (_is_main) { 
			console_m.lock();
			std::cout << _str_ch << " string, " << _cmd_ch << " command, " <<
			_block_ch << " blok." << std::endl; 
			console_m.unlock();
		}
		else {
			console_m.lock();
			std::cout << _block_ch << " blok, " << _cmd_ch << " command." << std::endl;
			console_m.unlock();
		}
		
		
	}
};
