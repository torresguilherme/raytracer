struct Vec
{
	float x;
	float y;
	float z;

	Vec();
	Vec(float, float, float);

	float dot(const Vec& other);
	Vec cross(const Vec& other);
	float magnitude();
	Vec normalize();

	Vec operator+(const Vec& other);
	Vec operator-(const Vec& other);
	Vec operator*(const Vec& other);
	Vec operator/(const Vec& other);
	Vec operator*(float scalar);
	Vec operator/(float scalar);
};

struct Ray
{
	Vec origin;
	Vec dir;

	Ray(Vec, Vec);
};

struct Camera
{
	Vec pos;
	Vec aim;
	Vec up;
	float abertura;

	Camera(Vec, Vec, Vec, float);
};

struct Light
{
	Vec pos;
	Vec color;
	float constAten;
	float propAten;
	float squarePropAten;

	Light(Vec, Vec, float, float, float);
};