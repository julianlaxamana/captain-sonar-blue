#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include <mutex>
#include <vector>

using namespace boost::asio::ip;

static std::string msg = "test";
static std::mutex mut;

std::vector<std::string> hist;

static tcp::iostream* ptr;

tcp::iostream client_start(const std::string& host, int port) {
	tcp::iostream stream(host, std::to_string(port).c_str());
	ptr = &stream;

	if (!stream) {
		std::cerr << "Couldn't connect" << std::endl;
	}
	else {
		std::cout << "Successfully connected to " << host << ":" << port << std::endl;

		while (1) {

			std::string buf;
			if (stream.peek() == 's')
			{
				char s;
				stream >> s;
				getline(stream, buf);
				hist.push_back(buf);
			}
		}
	}

	return stream;
}

void sendMessage(const std::string& bruh) {
	const std::lock_guard<std::mutex> lock(mut);
	msg = bruh;
	*ptr << 'c' << msg << std::endl;
	msg = "";
}