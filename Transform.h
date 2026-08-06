#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform {
public:
    static constexpr float TRANSLATION_DISTANCE = 0.01f;
    static constexpr float ROTATION_STEP_DEGREES = 30.0f;
    static constexpr float SCALE_FACTOR = 1.1f;

    //Added a getters for verifications some of them are not super visible, so the marker will help see the change
    float zScaleValue() const { return zScale_; }
    glm::vec3 translationValue() const { return translation_; }
    float rotationValue() const { return rotationDegrees_; }

    void translate(const glm::vec3& displacement) {
        translation_ += displacement;
    }

    void rotateAroundZ(float degrees) {
        rotationDegrees_ += degrees;
    }

    void scaleAlongZ(float factor) {
        if (factor > 0.0f) {
            zScale_ *= factor;
        }
    }

    glm::mat4 matrix() const {
        glm::mat4 result(1.0f);

        result = glm::translate(result, translation_);

        result = glm::rotate(
            result,
            glm::radians(rotationDegrees_),
            glm::vec3(0.0f, 0.0f, 1.0f)
        );

        result = glm::scale(
            result,
            glm::vec3(1.0f, 1.0f, zScale_)
        );

        return result;
    }


private:
    glm::vec3 translation_{0.0f, 0.0f, 0.0f};
    float rotationDegrees_{0.0f};
    float zScale_{1.0f};
};