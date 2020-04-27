#pragma once

namespace pmxy {

	template <typename T> void println(T a) {
		std::cout << a << std::endl;
	}


	template <typename T> double round3(T a) {
		return round(1000 * a) / 1000.0;
	}

}