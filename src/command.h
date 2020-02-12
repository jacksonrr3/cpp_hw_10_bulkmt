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
	observers _obs;
	commands _comm;

	int _block_size;
	int _comm_counter = 0;
	int _bracket_counter = 0;
	bool _is_reg = true;
	std::string _time;
	std::shared_ptr<Metric> _m_main = std::make_shared<Metric>("main", true);
		
public:
	Command(int N):_block_size(N){
		v_m.emplace_back(_m_main);
	}
	
	~Command() {
		if (_is_reg) {
			if (_comm_counter) {
				notify();
			}
		}
	}

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

	void add_command(const std::string& s) {
		if (std::cin.eof()) { return; }
		_m_main->_str_ch += 1;
		if (s[0] == '{') {
			if (_comm_counter) {
				notify();
				_comm_counter = 0;
			}

			++_bracket_counter;
			_is_reg = false;
			return;
		}
		else if (s[0] == '}') {
			--_bracket_counter;
			if (!_bracket_counter) {
				notify();
				_is_reg = true;
			}
		}

		else {
			if (_comm.empty()) { setTime(); }
			_comm.push_back(s);
			if (_is_reg) {
				++_comm_counter;
				if (_comm_counter == _block_size) {
					notify();
					_comm_counter = 0;
				}
			}
		}
	}

};
