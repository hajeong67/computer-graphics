#include <iostream>
#include <cmath>

class VECTOR3D
{
public:
    VECTOR3D()
        : x(0.0f), y(0.0f), z(0.0f) {}

    VECTOR3D(float x, float y, float z)
        : x(x), y(y), z(z) {}

    float Magnitude();           
    float InnerProduct(VECTOR3D v); 
    VECTOR3D CrossProduct(VECTOR3D v);  
    VECTOR3D Normalize();               

    VECTOR3D operator+(VECTOR3D v);
    VECTOR3D operator-(VECTOR3D v);
    VECTOR3D operator*(float val);

    float x;
    float y;
    float z;
};


VECTOR3D VECTOR3D::operator+(VECTOR3D v)
{
    return VECTOR3D(x + v.x, y + v.y, z + v.z);
}

VECTOR3D VECTOR3D::operator-(VECTOR3D v)
{
    return VECTOR3D(x - v.x, y - v.y, z - v.z);
}

VECTOR3D VECTOR3D::operator*(float val)
{
    return VECTOR3D(x * val, y * val, z * val);
}

VECTOR3D VECTOR3D::Normalize()
{
    float mag = Magnitude();
    if (mag > 0.0f) {
        return VECTOR3D(x / mag, y / mag, z / mag);
    }
    return *this;
}

float VECTOR3D::Magnitude()
{
    return sqrt(x * x + y * y + z * z);
}

float VECTOR3D::InnerProduct(VECTOR3D v)
{
    return x * v.x + y * v.y + z * v.z;
}

VECTOR3D VECTOR3D::CrossProduct(VECTOR3D v)
{
    return VECTOR3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

int main() {
    float x1, y1, z1, x2, y2, z2;

    std::cout << "첫 번째 벡터의 x, y, z 좌표를 입력하세요: ";
    std::cin >> x1 >> y1 >> z1;

    std::cout << "두 번째 벡터의 x, y, z 좌표를 입력하세요: ";
    std::cin >> x2 >> y2 >> z2;

    VECTOR3D v1(x1, y1, z1);
    VECTOR3D v2(x2, y2, z2);

    VECTOR3D sum = v1 + v2;
    std::cout << "addition of a and b: (" << sum.x << ", " << sum.y << ", " << sum.z << ")" << std::endl;

    VECTOR3D sub = v1 - v2;
    std::cout << "substraction of a and b: (" << sub.x << ", " << sub.y << ", " << sub.z << ")" << std::endl;

    float scalar = 5.0f;
    VECTOR3D scalarMulti = v1 * scalar;
    std::cout << "scalar multiplication: " << scalar << "*a = (" << scalarMulti.x << ", " << scalarMulti.y << ", " << scalarMulti.z << ")" << std::endl;

    VECTOR3D normalizedVector = v1.Normalize();
    std::cout << "normalized vector a: (" << normalizedVector.x << ", " << normalizedVector.y << ", " << normalizedVector.z << ")" << std::endl;

    std::cout << "magnitude of vector a: " << v1.Magnitude() << std::endl;

    std::cout << "dot product of a and b: " << v1.InnerProduct(v2) << std::endl;

    VECTOR3D crossProduct = v1.CrossProduct(v2);
    std::cout << "cross product of a and b: (" << crossProduct.x << ", " << crossProduct.y << ", " << crossProduct.z << ")" << std::endl;

    return 0;
}