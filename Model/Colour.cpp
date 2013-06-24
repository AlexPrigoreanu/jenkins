#include "Colour.h"
#include<cmath>

Colour::Colour() : red(-1), green(-1), blue(-1), alpha(-1) {}

Colour::Colour(double r, double g, double b, double a) {
	setRed(r);
	setGreen(g);
	setBlue(b);
	setAlpha(a);
}

Colour::Colour(const Colour& c) : red(c.red), green(c.green), blue(c.blue), alpha(c.alpha) {}

Colour& Colour::operator= (const Colour& c){
    this->alpha=c.getAlpha();
    this->blue=c.getBlue();
    this->green=c.getGreen();
    this->red=c.getRed();
    return *this;
}

bool Colour::operator == (const Colour& other) const {
	return red == other.red && green == other.green && blue == other.blue && alpha == other.alpha;
}

bool Colour::operator != (const Colour& other) const{
	return red != other.red || green != other.green || blue != other.blue || alpha != other.alpha;
}

Colour& Colour::operator+=(const Colour& c) {
	setRed(red+c.red);
	setGreen(green+c.green);
	setBlue(blue+c.blue);
	setAlpha(alpha+c.alpha);
    return *this;
}
Colour& Colour::operator-=(const Colour& c) {
	setRed(red-c.red);
	setGreen(green-c.green);
	setBlue(blue-c.blue);
	setAlpha(alpha-c.alpha);
    return *this;
}
Colour& Colour::operator*=(const Colour& c) {
	setRed(red*c.red);
	setGreen(green*c.green);
	setBlue(blue*c.blue);
	setAlpha(alpha*c.alpha);
    return *this;
}

void Colour::setRed(double r) {
	if (r<0) {
		r = 0;
	}
	else {
        if (r>1) {
            r = 1;
		}
	}
	red = r;
	return;
}

void Colour::setGreen(double g) {
	if (g<0) {
		g = 0;
	}
	else {
        if (g>1) {
            g = 1;
		}
	}
	green = g;
	return;
}

void Colour::setBlue(double b) {
	if (b<0) {
		b = 0;
	}
	else {
        if (b>1) {
            b = 1;
		}
	}
	blue = b;
	return;
}

void Colour::setAlpha(double a) {
	if (a<0) {
		a = 0;
	}
	else {
		if (a>1) {
			a = 1;
		}
	}
	alpha = a;
	return;
}

double Colour::getRed() const {
	return red;
}

double Colour::getGreen() const {
	return green;
}

double Colour::getBlue() const {
	return blue;
}

double Colour::getAlpha() const {
	return alpha;
}
