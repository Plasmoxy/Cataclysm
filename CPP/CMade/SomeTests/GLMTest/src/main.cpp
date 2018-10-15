#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>


int main() {
    glm::vec2 a(1, 2);
    glm::vec2 b(4, 2);

    glm::vec2 c = a + b;

    std::cout << glm::to_string(c) << std::endl;
}