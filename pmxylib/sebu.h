#pragma once

#ifndef SEBU_H
#define SEBU_H
#endif

namespace sebu {

	template <typename T> void println(T a) {
		std::cout << a << std::endl;
	}

	class Vector {
	public:
		double x, y;
		Vector() {
			x = 0;
			y = 0;
		}
		Vector(double _x, double _y) {
			x = _x;
			y = _y;
		}

		void dump() {
			std::cout << "[ " << x << ", " << y << " ]" << std::endl;
		}

		void rotate(double ang) {
			
		}

		Vector operator+(const Vector& a) {
			return Vector(
				x + a.x,
				y + a.y
			);
		}

		void operator +=(const Vector& a) {
			x += a.x;
			y += a.y;
		}

	};


	template <typename T> double round3(T a) {
		return round(1000 * a) / 1000.0;
	}

}