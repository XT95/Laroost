#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.h"

Camera::Camera()
{
    m_proj = glm::perspective(70., 16./9., 0.01, 5000.);
    m_view = glm::translate(glm::mat4(1.f), glm::vec3(0.,-5.,5.));
}

Camera::~Camera()
{

}


void Camera::setViewMatrix( glm::mat4& mat)
{
    m_view = mat;
}

void Camera::setProjectionMatrix( glm::mat4& mat)
{
    m_proj = mat;
}

glm::mat4& Camera::getViewMatrix()
{
    return m_view;
}

glm::mat4& Camera::getProjectionMatrix()
{
    return m_proj;
}
