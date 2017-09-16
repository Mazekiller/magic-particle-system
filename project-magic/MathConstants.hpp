#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

const sf::FloatRect ShotBounds(60, 56, 770, 762);
const sf::Vector2i Bound(800, 800);

const float EPSILON = 0.0000001;            ///A number used to make difference operations between floats, since their precission is low.
const double D_EPSILON = 0.00000000000001;  ///A number used to make difference operations between doubles, since their precission is higher, but still not perfect.

const sf::Time MaxTime = sf::seconds(1296000); ///6 hours in seconds.

///Overrides the math trigonometry functions to avoid unnecessary conversions between radians and degrees.
///Thanks to Jan Haller for this code, I stole it!
template <typename T>
struct Math
{
};

template <>
struct Math<float>
{
    typedef float Type;

	static Type sin(Type deg)					{ return std::sin(degToRad(deg));			}
	static Type cos(Type deg)					{ return std::cos(degToRad(deg));			}
	static Type tan(Type deg)					{ return std::tan(degToRad(deg));			}
	static Type asin(Type value)				{ return radToDeg(std::asin(value));		}
	static Type acos(Type value)				{ return radToDeg(std::acos(value));		}
	static Type atan2(Type valY, Type valX)	    { return radToDeg(std::atan2(valY, valX));	}
	static Type sqrt(Type value)				{ return std::sqrt(value);					}

	static Type Pi()							{ return 3.141592653589793238462643383f;	}
	static Type TwoPi()                         { return Pi() * 2;                          }
	static Type radToDeg(Type rad)				{ return 180 / Pi() * rad;					}
	static Type degToRad(Type deg)				{ return Pi() / 180 * deg;					}


};

template <>
struct Math<double>
{
	typedef double Type;

	static Type sin(Type deg)					{ return std::sin(degToRad(deg));			}
	static Type cos(Type deg)					{ return std::cos(degToRad(deg));			}
	static Type tan(Type deg)					{ return std::tan(degToRad(deg));			}
	static Type asin(Type value)				{ return radToDeg(std::asin(value));		}
	static Type acos(Type value)				{ return radToDeg(std::acos(value));		}
	static Type atan2(Type valY, Type valX)	{ return radToDeg(std::atan2(valY, valX));	}
	static Type sqrt(Type value)				{ return std::sqrt(value);					}

	static Type Pi()							{ return 3.141592653589793238462643383;		}
	static Type TwoPi()                         { return Pi() * 2;                          }
	static Type radToDeg(Type rad)				{ return 180 / Pi() * rad;					}
	static Type degToRad(Type deg)				{ return Pi() / 180 * deg;					}
};

template <>
struct Math<long double>
{
	typedef long double Type;

	static Type sin(Type deg)					{ return std::sin(degToRad(deg));			}
	static Type cos(Type deg)					{ return std::cos(degToRad(deg));			}
	static Type tan(Type deg)					{ return std::tan(degToRad(deg));			}
	static Type asin(Type value)				{ return radToDeg(std::asin(value));		}
	static Type acos(Type value)				{ return radToDeg(std::acos(value));		}
	static Type atan2(Type valY, Type valX)	{ return radToDeg(std::atan2(valY, valX));	}
	static Type sqrt(Type value)				{ return std::sqrt(value);					}

	static Type Pi()							{ return 3.141592653589793238462643383l;	}
	static Type TwoPi()                         { return Pi() * 2;                          }
	static Type radToDeg(Type rad)				{ return 180 / Pi() * rad;					}
	static Type degToRad(Type deg)				{ return Pi() / 180 * deg;					}
};

///Function to turn Radians to Degrees.
template <typename T>
T toDegrees(T radian)
{ return Math<T>::radToDeg(radian); }

///Function to turn Degrees to Radians.
template <typename T>
T toRadians(T degree)
{ return Math<T>::degToRad(degree); }


