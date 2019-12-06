#include "opengl_genderer.h"

void OpenGLRenderer::Initialize()
{
	model_view_uniform_location_ = glGetUniformLocation(program_, "modelview");
	projection_uniform_location_ = glGetUniformLocation(program_, "projection");
	texture_location_ = glGetUniformLocation(program_, "texture_2d");
	vertex_object_.Initialize(model_data_);
}

void OpenGLRenderer::Draw()
{
	glUseProgram(program_);	// �V�F�[�_�v���O�����̎g�p�J�n
	glBindTexture(GL_TEXTURE_2D, model_data_->texture_id_);
	const glm::mat4 translation_mat = glm::translate(glm::mat4(1.0f), transform_->position_);
	const glm::mat4 rotation_mat = glm::toMat4(transform_->GetRotation());
	const glm::mat4 scale_mat = glm::scale(glm::mat4(1.0f), transform_->scale_);
	const glm::mat4 model_view_mat(Camera::main_->Projection() * Camera::main_->LookAt() * translation_mat * rotation_mat * scale_mat);    // ���f���r���[�ϊ��s��

	// uniform�ϐ��ɒl��ݒ肷��
	glUniformMatrix4fv(model_view_uniform_location_, 1, GL_FALSE, &model_view_mat[0][0]);
	vertex_object_.Draw();

	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);    // �V�F�[�_�v���O�����̎g�p�I��
}

void OpenGLRenderer::Finalize()
{
	model_data_->Finalize();
	vertex_object_.Finalize();
	delete this;
}

void OpenGLRenderer::SetTransform(Transform* transform)
{
	transform_ = transform;
}

void OpenGLRenderer::LoadShader(const char* vertex_path, const char* fragment_path)
{
	program_ = LoadProgram(vertex_path, fragment_path);
}

void OpenGLRenderer::LoadModel(const char* model_path)
{
	model_data_ = FbxLoader::Load(model_path);
	model_data_->Initialize();
}

GLboolean OpenGLRenderer::PrintProgramInfoLog(GLuint program)
{
	// �����N���ʂ��擾����
	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);

	if (status == GL_FALSE)
	{
		std::cerr << "link error" << std::endl;
	}

	// �V�F�[�_�̃����N���̃��O�̒������擾����
	GLsizei buf_size;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &buf_size);

	if (buf_size > 1)
	{
		// �V�F�[�_�̃����N���̃��O�̓��e���擾����
		std::vector<GLchar> info_log(buf_size);
		GLsizei length;
		glGetProgramInfoLog(program, buf_size, &length, &info_log[0]);
		std::cerr << &info_log[0] << std::endl;
	}

	return static_cast<GLboolean>(status);
}

GLboolean OpenGLRenderer::PrintShaderInfoLog(GLuint shader, const char* str)
{
	// �R���p�C�����ʂ��擾����
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE) {
		std::cerr << "compile error in " << str << std::endl;
	}

	// �V�F�[�_�̃R���p�C�����̃��O�̒������擾����
	GLsizei buf_size;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &buf_size);

	if (buf_size > 1)
	{
		// �V�F�[�_�̃R���p�C�����̃��O�̓��e���擾����;
		std::vector<GLchar> info_log(buf_size);
		GLsizei length;
		glGetShaderInfoLog(shader, buf_size, &length, &info_log[0]);
		std::cerr << &info_log[0] << std::endl;
	}

	return static_cast<GLboolean>(status);
}

GLuint OpenGLRenderer::CreateProgram(const char* v_src, const char* f_src)
{
	const GLuint program(glCreateProgram());		// ��̃v���O�����I�u�W�F�N�g���쐬����

	if (v_src != nullptr) {
		// �o�[�e�b�N�X�V�F�[�_�̃V�F�[�_�I�u�W�F�N�g���쐬����
		const GLuint v_obj(glCreateShader(GL_VERTEX_SHADER));
		glShaderSource(v_obj, 1, &v_src, NULL);
		glCompileShader(v_obj);

		// �o�[�e�b�N�X�V�F�[�_�̃V�F�[�_�I�u�W�F�N�g���v���O�����I�u�W�F�N�g�ɑg�ݍ���
		if (PrintShaderInfoLog(v_obj, "vertex shader"))
		{
			glAttachShader(program, v_obj);
		}
		glDeleteShader(v_obj);
	}

	if (f_src != nullptr) {
		// �t���O�����g�V�F�[�_�̃V�F�[�_�I�u�W�F�N�g���쐬����
		const GLuint f_obj(glCreateShader(GL_FRAGMENT_SHADER));
		glShaderSource(f_obj, 1, &f_src, NULL);
		glCompileShader(f_obj);

		// �t���O�����g�V�F�[�_�̃V�F�[�_�I�u�W�F�N�g���v���O�����I�u�W�F�N�g�ɑg�ݍ���
		if (PrintShaderInfoLog(f_obj, "fragment shader"))
		{
			glAttachShader(program, f_obj);
		}
		glDeleteShader(f_obj);
	}

	// �v���O�����I�u�W�F�N�g�������N����
	glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "color");
	glBindAttribLocation(program, 2, "normal");
	glBindAttribLocation(program, 3, "uv");

	glBindFragDataLocation(program, 0, "fragment");
	glLinkProgram(program);

	// �쐬�����v���O�����I�u�W�F�N�g��Ԃ�
	if (PrintProgramInfoLog(program))
	{
		return program;
	}

	// �v���O�����I�u�W�F�N�g���쐬�ł��Ȃ���� 0 ��Ԃ�
	glDeleteProgram(program);

	return 0;
}

bool OpenGLRenderer::ReadShaderSource(const char* name, std::vector<GLchar>& buffer)
{
	if (name == nullptr)
	{
		return false;
	}

	std::ifstream file(name, std::ios::binary);    // �\�[�X�t�@�C�����J��

	if (file.fail())
	{
		std::cerr << "failed to open source file:" << name << std::endl;
		return false;
	}

	// �t�@�C���̖����Ɉړ������݈ʒu�i���t�@�C���T�C�Y�j�𓾂�
	file.seekg(0L, std::ios::end);
	GLsizei length = static_cast<GLsizei>(file.tellg());

	buffer.resize(length + 1);    // �t�@�C���T�C�Y�̃����������

	// �t�@�C����擪����ǂݍ���
	file.seekg(0L, std::ios::beg);
	file.read(buffer.data(), length);
	buffer[length] = '\0';

	if (file.fail())
	{
		// �ǂݍ��߂Ȃ�����
		std::cerr << "could not read source file:" << name << std::endl;
		file.close();
		return false;
	}

	// �ǂݍ��߂�
	file.close();
	return true;
}

GLuint OpenGLRenderer::LoadProgram(const char* vert, const char* frag)
{
	// �V�F�[�_�̃\�[�X�t�@�C����ǂݍ���
	std::vector<GLchar> v_src;
	std::vector<GLchar> f_src;
	const bool v_stat(ReadShaderSource(vert, v_src));
	const bool f_stat(ReadShaderSource(frag, f_src));

	return v_stat && f_stat ? CreateProgram(v_src.data(), f_src.data()) : 0;
}
