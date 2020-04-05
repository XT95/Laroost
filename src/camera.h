#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera
{
public:
    Camera();
    ~Camera();

    void setViewMatrix( glm::mat4& mat);
    void setProjectionMatrix( glm::mat4& mat);

    glm::mat4& getViewMatrix();
    glm::mat4& getProjectionMatrix();

protected:
    glm::mat4 m_view;
    glm::mat4 m_proj;
};

#endif // CAMERA_H
