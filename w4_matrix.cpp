#include <iostream>
#include <cmath>

class VECTOR3D
{
public:
    VECTOR3D()
        : x(0.0f), y(0.0f), z(0.0f) {}

    VECTOR3D(float x, float y, float z)
        : x(x), y(y), z(z) {}

    float x;
    float y;
    float z;
};

class MATRIX
{
public:

    MATRIX()
    {
        // ����� �ʱⰪ�� ���� ��ķ� ����
        ele[0][0] = 1.0f;
        ele[0][1] = 0.0f;
        ele[0][2] = 0.0f;

        ele[1][0] = 0.0f;
        ele[1][1] = 1.0f;
        ele[1][2] = 0.0f;

        ele[2][0] = 0.0f;
        ele[2][1] = 0.0f;
        ele[2][2] = 1.0f;
    }

    MATRIX Transpose();
    MATRIX Inverse();
    float Determinant();

    MATRIX operator+(MATRIX m);
    MATRIX operator-(MATRIX m);
    MATRIX operator*(MATRIX m);
    MATRIX operator*(float val);
    VECTOR3D operator*(VECTOR3D v);

    float ele[3][3];
};

void InputMatrixElements(MATRIX& mat)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cin >> mat.ele[i][j];
        }
    }
}

MATRIX MATRIX::operator+(MATRIX m)
{
    MATRIX result;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            result.ele[i][j] = ele[i][j] + m.ele[i][j];

    return result;
}

MATRIX MATRIX::operator-(MATRIX m)
{
    MATRIX result;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            result.ele[i][j] = ele[i][j] - m.ele[i][j];

    return result;
}

MATRIX MATRIX::operator*(MATRIX m)
{
    MATRIX result;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            result.ele[i][j] = 0.0;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                result.ele[i][j] += ele[i][k] * m.ele[k][j];

    return result;
}

MATRIX MATRIX::operator*(float t)
{
    MATRIX result;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            result.ele[i][j] = ele[i][j] * t;

    return result;
}

VECTOR3D MATRIX::operator*(VECTOR3D v)
{
    VECTOR3D result;

    result.x = ele[0][0] * v.x + ele[0][1] * v.y + ele[0][2] * v.z;
    result.y = ele[1][0] * v.x + ele[1][1] * v.y + ele[1][2] * v.z;
    result.z = ele[2][0] * v.x + ele[2][1] * v.y + ele[2][2] * v.z;

    return result;
}

MATRIX MATRIX::Transpose()
{
    MATRIX result;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            result.ele[i][j] = ele[j][i];

    return result;
}

float MATRIX::Determinant()
{
    float a = ele[0][0];
    float b = ele[0][1];
    float c = ele[0][2];
    float d = ele[1][0];
    float e = ele[1][1];
    float f = ele[1][2];
    float g = ele[2][0];
    float h = ele[2][1];
    float i = ele[2][2];

    return a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
}

MATRIX MATRIX::Inverse()
{
    MATRIX result;

    float det = Determinant();
    if (det == 0)
    {
        std::cerr << "Matrix is singular, cannot compute inverse." << std::endl;
        return result;
    }

    float invDet = 1.0f / det;

    result.ele[0][0] = (ele[1][1] * ele[2][2] - ele[1][2] * ele[2][1]) * invDet;
    result.ele[0][1] = (ele[0][2] * ele[2][1] - ele[0][1] * ele[2][2]) * invDet;
    result.ele[0][2] = (ele[0][1] * ele[1][2] - ele[0][2] * ele[1][1]) * invDet;
    result.ele[1][0] = (ele[1][2] * ele[2][0] - ele[1][0] * ele[2][2]) * invDet;
    result.ele[1][1] = (ele[0][0] * ele[2][2] - ele[0][2] * ele[2][0]) * invDet;
    result.ele[1][2] = (ele[0][2] * ele[1][0] - ele[0][0] * ele[1][2]) * invDet;
    result.ele[2][0] = (ele[1][0] * ele[2][1] - ele[1][1] * ele[2][0]) * invDet;
    result.ele[2][1] = (ele[0][1] * ele[2][0] - ele[0][0] * ele[2][1]) * invDet;
    result.ele[2][2] = (ele[0][0] * ele[1][1] - ele[0][1] * ele[1][0]) * invDet;

    return result;
}

int main()
{
    MATRIX mat1;
    MATRIX mat2;
    float x, y, z, t;

    // ����� ����, ��Į��, ���� �Է� �ޱ�
    std::cout << "ù ��° ����� �Է��ϼ���:";
    InputMatrixElements(mat1);

    std::cout << "�� ��° ����� �Է��ϼ���:";
    InputMatrixElements(mat2);

    std::cout << "��Į�� �� t�� �Է��ϼ���: ";
    std::cin >> t;

    std::cout << "���� v�� x, y, z�� �Է��ϼ���: ";
    std::cin >> x >> y >> z;

    // ���� ����
    // ��� ����
    MATRIX sum = mat1 + mat2;
    std::cout << "matrix addition of a, b:" << std::endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << sum.ele[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // ��� ����
    MATRIX diff = mat1 - mat2;
    std::cout << "matrix subtraction of a, b:" << std::endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << diff.ele[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // ��Į�� t�� ��� a ����
    MATRIX scaledMat1 = mat1 * t;

    std::cout << "scalar t multiplication of a:" << std::endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << scaledMat1.ele[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // ��� a�� ���� v ����
    VECTOR3D resultVector = mat1 * VECTOR3D(x, y, z);
    std::cout << "matrix a & vector v multiplication:" << std::endl;
    std::cout << resultVector.x << " " << resultVector.y << " " << resultVector.z << " " << std::endl;

    // ��ġ ���
    MATRIX transposed = mat1.Transpose();
    std::cout << "matrix transpose of a:" << std::endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << transposed.ele[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // ��Ľ�
    float determinant = mat1.Determinant();
    std::cout << "matrix determinant of a: " << determinant << std::endl;

    // ��� �����
    MATRIX inverse = mat1.Inverse();
    std::cout << "matrix inverse of a:" << std::endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << inverse.ele[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}