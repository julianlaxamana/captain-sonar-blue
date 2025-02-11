#pragma once
#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio::ip;

tcp::iostream client_start(const std::string& host, int port) {
	tcp::iostream stream(host, std::to_string(port).c_str());

	if (!stream) {
		std::cerr << "Couldn't connect" << endl;
	} else {
		std::cout << "Successfully connected to " << host << ":" << port << endl;

		std::string response;
		getline(stream, response);

		std::cout << response;
		std::cout.flush();
	}

	return stream;
}
