#include "matrix.h"

Matrix::Matrix()
{
	LoadIdentity();
}

Matrix::Matrix(const GLfloat* matrix)
{
	std::copy(matrix, matrix + 16, matrix_);
}

const GLfloat* Matrix::GetMatrix() const
{
	return matrix_;
}

void Matrix::LoadIdentity()
{
	std::fill(matrix_, matrix_ + 16, 0.0f);
	matrix_[0] = matrix_[5] = matrix_[10] = matrix_[15] = 1.0f;
}

Matrix Matrix::Identity()
{
	Matrix matrix;
	matrix.LoadIdentity();
	return matrix;
}

Matrix Matrix::Translate(GLfloat x, GLfloat y, GLfloat z)
{
	Matrix matrix;
	matrix.LoadIdentity();
	matrix.matrix_[12] = x;
	matrix.matrix_[13] = y;
	matrix.matrix_[14] = z;
	return matrix;
}

Matrix Matrix::Scale(GLfloat x, GLfloat y, GLfloat z)
{
	Matrix matrix;
	matrix.Identity();
	matrix.matrix_[0] = x;
	matrix.matrix_[5] = y;
	matrix.matrix_[10] = z;

	return matrix;
}

Matrix Matrix::Rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
	Matrix matrix;
	matrix.LoadIdentity();

	const GLfloat d(sqrt(x * x + y * y + z * z));

	if (d > 0.0f)
	{
		const GLfloat l(x / d), m(y / d), n(z / d);
		const GLfloat l2(l * l), m2(m * m), n2(n * n);
		const GLfloat lm(l * m), mn(m * n), nl(n * l);
		const GLfloat c(cos(angle)), c1(1.0f - c), s(sin(angle));

		matrix.matrix_[0] = (1.0f - l2) * c + l2;
		matrix.matrix_[1] = lm * c1 + n * s;
		matrix.matrix_[2] = nl * c1 - m * s;
		matrix.matrix_[4] = lm * c1 - n * s;
		matrix.matrix_[5] = (1.0f - m2) * c + m2;
		matrix.matrix_[6] = mn * c1 + l * s;
		matrix.matrix_[8] = nl * c1 + m * s;
		matrix.matrix_[9] = mn * c1 - l * s;
		matrix.matrix_[10] = (1.0f - n2) * c + n2;
	}
	return matrix;
}

Matrix Matrix::LookAt(GLfloat ex, GLfloat ey, GLfloat ez, GLfloat gx, GLfloat gy, GLfloat gz, GLfloat ux, GLfloat uy, GLfloat uz)
{
	const Matrix tv(Translate(-ex, -ey, -ez));
	const GLfloat tx(ex - gx);
	const GLfloat ty(ey - gy);
	const GLfloat tz(ez - gz);

	const GLfloat rx(uy * tz - uz * ty);
	const GLfloat ry(uz * tx - ux * tz);
	const GLfloat rz(ux * ty - uy * tx);

	const GLfloat sx(ty * rz - tz * ry);
	const GLfloat sy(tz * rx - tx * rz);
	const GLfloat sz(tx * ry - ty * rx);

	const GLfloat sl(sx * sx + sy * sy + sz * sz);

	if (sl == 0.0f)
	{
		return tv;
	}

	Matrix rv;
	rv.LoadIdentity();

	const GLfloat r(sqrt(rx * rx + ry * ry + rz * rz));

	rv.matrix_[0] = rx / r;
	rv.matrix_[4] = ry / r;
	rv.matrix_[8] = rz / r;

	const GLfloat s(sqrt(sl));

	rv.matrix_[1] = sx / s;
	rv.matrix_[5] = sy / s;
	rv.matrix_[9] = sz / s;

	const GLfloat t(sqrt(tx * tx + ty * ty + tz * tz));

	rv.matrix_[2] = tx / t;
	rv.matrix_[6] = ty / t;
	rv.matrix_[10] = tz / t;

	return rv * tv;
}

Matrix Matrix::Orthogonal(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat z_near, GLfloat z_far)
{
	Matrix matrix;
	const GLfloat dx(right - left);
	const GLfloat dy(top - bottom);
	const GLfloat dz(z_far - z_near);

	if (dx != 0.0f && dy != 0.0f && dz != 0.0f)
	{
		matrix.LoadIdentity();
		matrix.matrix_[0] = 2.0f / dx;
		matrix.matrix_[5] = 2.0f / dy;
		matrix.matrix_[10] = -2.0f / dz;
		matrix.matrix_[12] = -(right + left) / dx;
		matrix.matrix_[13] = -(top + bottom) / dy;
		matrix.matrix_[14] = -(z_far + z_near) / dz;
	}

	return matrix;
}

Matrix Matrix::Frustum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat z_near, GLfloat z_far)
{
	Matrix matrix;
	const GLfloat dx(right - left);
	const GLfloat dy(top - bottom);
	const GLfloat dz(z_far - z_near);

	if (dx != 0.0f && dy != 0.0f && dz != 0.0f)
	{
		matrix.LoadIdentity();
		matrix.matrix_[0] = 2.0f * z_near / dx;
		matrix.matrix_[5] = 2.0f * z_near / dy;
		matrix.matrix_[8] = (right + left) / dx;
		matrix.matrix_[9] = (top + bottom) / dy;
		matrix.matrix_[10] = -(z_far + z_near) / dz;
		matrix.matrix_[11] = -1.0f;
		matrix.matrix_[14] = -2.0f * z_far * z_near / dz;
		matrix.matrix_[15] = 0.0f;
	}
	return matrix;
}

Matrix Matrix::Perspective(GLfloat fovy, GLfloat aspect, GLfloat z_near, GLfloat z_far)
{
	Matrix matrix;
	const GLfloat dz(z_far - z_near);

	if (dz != 0.0f)
	{
		matrix.LoadIdentity();
		matrix.matrix_[5] = 1.0f / tan(fovy * 0.5f);
		matrix.matrix_[0] = matrix.matrix_[5] / aspect;
		matrix.matrix_[10] = -(z_far + z_near) / dz;
		matrix.matrix_[11] = -1.0f;
		matrix.matrix_[14] = -2.0f * z_far * z_near / dz;
		matrix.matrix_[15] = 0.0f;
	}
	return matrix;
}

Matrix Matrix::operator*(const Matrix& m) const
{
	Matrix matrix;

	for (int i = 0; i < 16; ++i)
	{
		const int j(i & 3), k(i & ~3);
		matrix.matrix_[i] =
			matrix_[0 + j] * m.matrix_[k + 0] +
			matrix_[4 + j] * m.matrix_[k + 1] +
			matrix_[8 + j] * m.matrix_[k + 2] +
			matrix_[12 + j] * m.matrix_[k + 3];
	}
	return matrix;
}

