#pragma once
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

tcp::iostream server_start(boost::asio::io_context& io_context, const std::string& host, int port) {
	tcp::endpoint endpoint(boost::asio::ip::make_address(host), port);
	tcp::acceptor acceptor(io_context, endpoint);

	std::cout << "Server is listening on " << host << ":" << port << "..... Please wait for a client to connect" << endl;

	while (true) {
		tcp::iostream stream;
		boost::system::error_code error;

		acceptor.accept(stream.socket(), error);

		if (!error) {
			stream << "Connected! Welcome!\n\n";
			return stream;
		}
	}
}
