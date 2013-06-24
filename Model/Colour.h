#ifndef COLOUR_H
#define COLOUR_H

class Colour{
public:
	Colour();
    Colour(double r, double g, double b, double a = 1);
	Colour(const Colour& c);
	bool operator == (const Colour& other) const;
	bool operator != (const Colour& other) const;
	Colour& operator+=(const Colour& c);
	Colour& operator-=(const Colour& c);
	Colour& operator*=(const Colour& c);
    Colour& operator= (const Colour& c);
    void setRed(double r);
    void setGreen(double g);
    void setBlue(double b);
	void setAlpha(double a);
    double getRed() const;
    double getGreen() const;
    double getBlue() const;
	double getAlpha() const;
private:
    double red;
    double green;
    double blue;
	double alpha;
};

#endif // COLOUR_H
