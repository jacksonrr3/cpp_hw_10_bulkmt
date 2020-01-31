#pragma once
/**
\file
\brief Заголовочный файл с описанием классов
Данный файл содержит в себе определения основного класса, используемого в программе
*/



#pragma once
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <ctime>
#include <sstream>
#include "observer.h"


using observers = std::vector<std::unique_ptr<Observers>>;
/**
* @brief Основной класс, реализующий функционал считывания команд из стандартного ввода и распределения на блоки команд
*
*/
class Command {
	std::shared_ptr<metric> _m_main;
	observers _obs;
	commands _comm;
	int _block_size;
	int _comm_counter = 0;
	std::string _time;
	
public:
	Command(int N, std::shared_ptr<metric> m_main):_block_size(N), _m_main(m_main){}

	void subscribe(std::unique_ptr<Observers>&& obs) {
		_obs.emplace_back(std::move(obs));
	}

	void setTime() {
		std::time_t temp_time = std::time(0);
		_time = std::to_string(temp_time);
	}

	void notify() {
		for (auto& u : _obs) {
			u->print(_comm, _time);
		}
		_m_main->_block_ch += 1;
		_m_main->_cmd_ch += _comm.size();
		_comm.clear();
		_time.clear();
	}

	void add_command_bracket() {
		int bracket_counter = 1;
		std::string s;
		while (std::getline(std::cin, s)) {
			if (std::cin.eof()) { return; }
			_m_main->_str_ch += 1;
			if (s[0] == '{') {
				++bracket_counter;
				continue;
			}

			else if (s[0] == '}') {
				--bracket_counter;
				if (!bracket_counter) {
					notify();
					return;
				}
			}
			
			else {
				if (_comm.empty()) { setTime(); }
				_comm.push_back(s);
			}
		}
	}

	void add_command() {
		std::string s;
		while (std::getline(std::cin, s)) {
			if (std::cin.eof()) {
				break;
			}
			_m_main->_str_ch += 1;
			if (s[0] == '{') {
				if (_comm_counter) {
					notify();
					_comm_counter = 0;
				}
				add_command_bracket();
			}
			else {
				if (_comm.empty()) { setTime(); }
				_comm.push_back(s);
				++_comm_counter;
				if (_comm_counter == _block_size) {
					notify();
					_comm_counter = 0;
				}
			}
		}
		if (_comm_counter) { notify(); }
	}
};
