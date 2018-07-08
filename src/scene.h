struct Vec
{
	float x;
	float y;
	float z;

	Vec();
	Vec(float, float, float);

	float dot(Vec other);
	float magnitude();
	Vec normalize();
	Vec operator+(Vec other);
	Vec operator-(Vec other);
	Vec operator*(Vec other);
	Vec operator/(Vec other);
};

struct Ray
{
	Vec origin;
	Vec dir;

	Ray(Vec, Vec);
};
