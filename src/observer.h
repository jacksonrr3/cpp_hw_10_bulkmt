#pragma once
/**
\file
\brief Заголовочный файл с описанием классов
Данный файл содержит в себе определения классов, используемых в программе
*/

#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <thread>
#include <future>
#include <string>
#include <memory>
#include <condition_variable>
#include <chrono>
#include <atomic>
#include <tuple>
#include <functional>
#include "fibfac.h"
#include "metrics.h"

using commands = std::vector<std::string>;

class data_pack {
public:
	commands _command_pack;
	std::string _time;
};

void worker(std::function<void(const commands&, const std::string)> f, std::queue<data_pack>& q,
	std::condition_variable& cv, std::mutex& cv_m, std::atomic_bool& quit, std::shared_ptr<metric> m) {
	while (!quit) {
		std::unique_lock<std::mutex> lk(cv_m);
		cv.wait(lk, [&]() {return !q.empty() || quit; });
		if (!q.empty()) {
			commands a = q.front()._command_pack;
			std::string b = q.front()._time;
			m->_block_ch += 1;
			m->_cmd_ch += a.size();
			//std::tie(a, b) = std::move(q.front());
			q.pop();
			lk.unlock();
			f(a, b);
		}
	}
}

void print_to_terminal(const commands& comm, const std::string&) {
	console_m.lock();
	std::cout << "Bulk: ";
	bool first = true;
	for (auto& command : comm) {
		if (!first) { std::cout << ","; }
		std::cout << fac(std::stoi(command));
		first = false;
	}
	std::cout << std::endl;
	console_m.unlock();
}

void print_to_file(const commands& comm, const std::string& time) {
	static int file_id = 11;
	std::ofstream file;
	std::string path("bulk" + std::to_string(file_id) + time + ".log");
	++file_id;
	file.open(path);
	for (auto& command : comm) {
		file << fib(std::stoi(command)) << "\n";
	}
	file.close();
}


/**
* @brief базовый класс, для реализации классов вывода команд
*
*/

class Observers {
public:
	virtual void print(const commands&, const std::string&) = 0;
	virtual ~Observers() = default;

	std::condition_variable _cv;
	std::mutex _cv_m;
	std::atomic_bool _quit = false;
};


/**
* @brief класс реализующий функцию вывода команд в файл
*
*/

class FileObserver : public Observers {
public:
	FileObserver(std::shared_ptr<metric> file1, std::shared_ptr<metric> file2):_file1(file1), _file2(file2) {

		_vtr.emplace_back(std::thread(worker, std::function<void(const commands&, const std::string&)>(print_to_file),
				std::ref(_data),
				std::ref(_cv),
				std::ref(_cv_m),
				std::ref(_quit),
				_file1
		));
		_vtr.emplace_back(std::thread(worker, std::function<void(const commands&, const std::string&)>(print_to_file),
				std::ref(_data),
				std::ref(_cv),
				std::ref(_cv_m),
				std::ref(_quit),
				_file2
		));
	}

	~FileObserver() {
		_quit = true;
		_cv.notify_all();
		for (auto& v : _vtr) {
			if (v.joinable())
				v.join();
		}
	}

	virtual void print(const commands& comm, const std::string& time) {
		{
			std::lock_guard<std::mutex> lk(_cv_m);
			_data.emplace(data_pack{ comm, time });
		}
		_cv.notify_one();
	}

	std::vector<std::thread> _vtr;
	std::queue<data_pack> _data;
	std::shared_ptr<metric> _file1;
	std::shared_ptr<metric> _file2;
};


/**
* @brief класс реализующий функцию вывода команд в консоль
*
*/

class TerminalObserver : public Observers {
public:
	TerminalObserver(std::shared_ptr<metric> log):_log(log) {
		_vtr.emplace_back(std::thread(worker, std::function<void(const commands&, const std::string&)>(print_to_terminal),
			std::ref(_data),
			std::ref(_cv),
			std::ref(_cv_m),
			std::ref(_quit),
			log));
		
	}

	~TerminalObserver() {
		_quit = true;
		_cv.notify_all();
		for (auto& v : _vtr) {
			if (v.joinable())
				v.join();
		}
		
	}

	virtual void print(const commands& comm, const std::string& time) {
		{
			std::lock_guard<std::mutex> lk(_cv_m);
			_data.emplace(data_pack{ comm, time });
		}
		_cv.notify_one();
	}

	std::queue<data_pack> _data;
	std::vector<std::thread> _vtr;
	std::shared_ptr<metric> _log;
};


