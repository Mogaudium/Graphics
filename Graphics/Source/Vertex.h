#pragma once

//Vertex functions implementation

class Vertex
{
public:
	Vertex();
	Vertex(float x, float y, float z);

	Vertex(const Vertex& v);//Copy vertex
	~Vertex();//Destructor

	void Dehomogenise();
	void Normalise();
	float Length();

	float GetX() const;
	void SetX(const float x);
	float GetY() const;
	void SetY(const float y);
	float GetZ() const;
	void SetZ(const float z);
	float GetW() const;
	void SetW(const float w);

	Vertex& operator= (const Vertex& rhs);//Operator
	bool operator== (const Vertex& rhs) const;

	const Vertex operator+ (const Vertex& rhs) const;//Vector addition
	const Vertex operator- (const Vertex& rhs) const;//Vector substraction

	float DotProduct(const Vertex& rhs) const;//Dot product
	Vertex CrossProduct(const Vertex& rhs) const;//Cross product

private:
	float _x;
	float _y;
	float _z;
	float _w;
};

