#include <iostream>
#include "ucoro/awaitable.hpp"

/*

ucoro::awaitable<int> coro_compute_int(int value)
{
	auto ret = co_await callback_awaitable<int>([value](auto handle) {
		std::cout << value << " value\n";
		handle(value * 100);
	});

	co_return (value + ret);
}

ucoro::awaitable<void> coro_compute_exec(int value)
{
	auto x = co_await ucoro::local_storage;
	std::cout << "local storage: " << std::any_cast<std::string>(x) << std::endl;

	try
	{
		auto y = co_await ucoro::local_storage_t<std::string>();
		std::cout << "local storage: " << y << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}

	auto comput_promise = coro_compute_int(value);

	auto ret = co_await std::move(comput_promise);
	std::cout << "return: " << ret << std::endl;
	co_return;
}

ucoro::awaitable<void> coro_compute()
{
	for (auto i = 0; i < 100; i++)
	{
		co_await coro_compute_exec(i);
	}
}
*/

ucoro::awaitable<int> foo()
{
	throw std::runtime_error("test");
	co_return 1;
}

ucoro::awaitable<int> bar()
{
	int res;
	res = co_await foo();
	assert(false); // 不会执行，因为上一行会抛出异常。

	co_return res;
}

ucoro::awaitable<int> baz()
{
	co_return co_await bar();
}

ucoro::awaitable<int> coro_compute()
{
	co_return co_await bar();
// 	for (auto i = 0; i < 100; i++)
// 	{
// 		co_await coro_compute_exec(i);
// 	}
}

void normal() {
	try {
		std::string str = "hello";
		coro_start(coro_compute(), str);
	}
	catch (...) {
		// 我们可以在这里捕获到异常。
	}
}


int main(int argc, char **argv)
{
	normal();
	return 0;
}
