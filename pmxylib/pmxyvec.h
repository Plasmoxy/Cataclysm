#pragma once

#include <pmxy.h>

#define _USE_MATH_DEFINES
#include <math.h>

namespace pmxy {
	class Vec {
	public:
		double x, y;
		Vec() {
			x = 0;
			y = 0;
		}
		Vec(double _x, double _y) {
			x = _x;
			y = _y;
		}

		void dump() {
			std::cout << "[ " << x << ", " << y << " ]" << std::endl;
		}

		void round() {
			x = round3(x);
			y = round3(y);
		}

		void rotate(Vec origin, double ang) {
			double dx = x - origin.x;
			double dy = y - origin.y;
			x = dx*cos(ang) - dy*sin(ang) + origin.x;
			y = dx*sin(ang) + dy*cos(ang) + origin.y;
		}

		Vec operator+(const Vec& a) {
			return Vec(
				x + a.x,
				y + a.y
			);
		}

		void operator +=(const Vec& a) {
			x += a.x;
			y += a.y;
		}

	};
}