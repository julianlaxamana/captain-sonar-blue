#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <Windows.h>


using boost::asio::ip::tcp;
static std::vector<tcp::iostream> connections(8);
static std::vector<std::thread> t(8);
static std::vector<std::string> buffer;
static std::vector<std::mutex> mutx;
static std::mutex bruh;



void fillBuffer(int i) {
	while (1) {
		std::string msg;
		char a;
		if (connections.at(i).peek() == 'c')
		{
			connections.at(i) >> a;
			getline(connections.at(i), msg);
		}
		if (!msg.empty())
		{
			const std::lock_guard<std::mutex> lock(bruh);
			buffer.push_back(msg);
		}
	}
}

void sendData() {
	while (1) {
		const std::lock_guard<std::mutex> lock(bruh);
		while (!buffer.empty()) {
			std::string str = buffer.back();
			buffer.pop_back();
			for (int i = 0; i < connections.size();i++) {
				connections.at(i) << 's' << str << "\n";
			}
		}
	}
}


tcp::iostream server_start(const std::string& host, int port) {
	boost::asio::io_context io_context;
	tcp::endpoint endpoint(boost::asio::ip::make_address(host), port);
	tcp::acceptor acceptor(io_context, endpoint);
	int index = 0;


	std::cout << "Server is listening on " << host << ":" << port << "..... Please wait for a client to connect" << std::endl;
	std::thread tgr(sendData);

	while (true) {
		
		boost::system::error_code error;
		acceptor.accept(connections.at(index).socket(), error);

		if (!error) {
				t.at(index) = std::thread(fillBuffer, index);
				std::cout << index << std::endl;
				index++;
		}
	}
}
