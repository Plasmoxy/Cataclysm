#include "Shader.h"

Shader::Shader(const std::string& namePath): namePath(namePath) {
    const std::string vertexSource = tryReadFile(namePath + ".vert");
    const std::string fragmentSource = tryReadFile(namePath + ".frag");

    rendererId = createShaderProgram(vertexSource, fragmentSource);
}

Shader::~Shader() {
    glDeleteProgram(rendererId);
}

void Shader::bind() const {
    glUseProgram(rendererId);
}

void Shader::unbind() const {
    glUseProgram(0);
}

void Shader::setUniform4f(const std::string& name, float a,
						  float b, float c, float d) {
    glUniform4f(getUniformLocation(name), a, b, c, d);
}

GLint Shader::getUniformLocation(const std::string& uniformName) {

    // get from cache
    if (uniformLocationCache.find(uniformName) != uniformLocationCache.end()) {
        return uniformLocationCache[uniformName];
    }

    GLint loc = glGetUniformLocation(rendererId, uniformName.c_str());
    uniformLocationCache[uniformName] = loc;
	return loc;
}

std::string Shader::tryReadFile(const std::string& filepath) {
    std::stringstream ss;
    std::ifstream fs(filepath);
    if (!fs) {
        fmt::print("Error loading shader file: {}\n", filepath);
        return "";
    }
    ss << fs.rdbuf();
    return ss.str();
}

GLuint Shader::compileShader(unsigned int type, const std::string& source) {
    // create shader
    GLuint id = glCreateShader(type);
    const char* src = source.c_str();

    // specify shader source for created shader and compile it
    glShaderSource(id, 1, &src, nullptr); //length=NULL means source is null-terminated
    glCompileShader(id);

    // handle compilation errors
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result); // returns parameter from shader obj
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        char* message = new char[length];
        glGetShaderInfoLog(id, length, &length, message);

        fmt::print("Failed to compile {} shader:\n{}\n",
                   (type == GL_VERTEX_SHADER ? "vertex" : "fragment"),
                   message
        );

        glDeleteShader(id); // delete it
        delete[] message;
        return 0; // 0 = failure
    }

    return id;
}


GLuint Shader::createShaderProgram(const std::string& vertexSrc, const std::string& fragmentSrc) {

    GLuint program = glCreateProgram();
    GLuint vs = compileShader(GL_VERTEX_SHADER, vertexSrc);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);

    // attach and link shaders to the program
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    int valid;
    glGetProgramiv(program, GL_VALIDATE_STATUS, &valid);

    if (!valid) {
        fmt::print("Shader program is not valid!");
        return 0;
    }

    // they are linked to the program, we can delete them from memory
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}