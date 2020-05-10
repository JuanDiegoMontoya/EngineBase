#include "../../stdafx.h"
#include "camera.h"
#include "input.h"
#include "Frustum.h"

// might add more to this constructor later
Camera::Camera(CameraType type) : type_(type) 
{
	frustum_ = new Frustum;
	GenProjection(fov_);
	glm::vec3 temp;
	temp.x = cos(glm::radians(pitch_)) * cos(glm::radians(yaw_));
	temp.y = sin(glm::radians(pitch_));
	temp.z = cos(glm::radians(pitch_)) * sin(glm::radians(yaw_));
	front = glm::normalize(temp);
	view_ = glm::lookAt(worldpos_, worldpos_ + front, up);
}

// update movement and generate view matrix
void Camera::Update(float dt)
{
	//view_ = glm::translate(glm::mat4(1.0f), worldpos_);
	float currSpeed = speed_ * dt;
	switch (type_)
	{
	case kPhysicsCam:
	{
		acceleration_ = glm::vec3(0, -25, 0); // "gravity"
		// "friction" (multiply dt by big num so the friction constant isn't stupidly small)
		velocity_.x *= glm::pow(.90f, dt * 100);
		velocity_.z *= glm::pow(.90f, dt * 100);
		if (Input::Keyboard().down[GLFW_KEY_W])
		{
			velocity_.x += 60 * cos(glm::radians(yaw_));
			velocity_.z += 60 * sin(glm::radians(yaw_));
		}
		if (Input::Keyboard().down[GLFW_KEY_S])
		{
			velocity_.x -= 60 * cos(glm::radians(yaw_));
			velocity_.z -= 60 * sin(glm::radians(yaw_));
		}
		if (Input::Keyboard().down[GLFW_KEY_A])
		{
			velocity_.x += 60 * cos(glm::radians(yaw_ - 90));
			velocity_.z += 60 * sin(glm::radians(yaw_ - 90));
		}
		if (Input::Keyboard().down[GLFW_KEY_D])
		{
			velocity_.x -= 60 * cos(glm::radians(yaw_ - 90));
			velocity_.z -= 60 * sin(glm::radians(yaw_ - 90));
		}

		// jump impulse
		if (Input::Keyboard().pressed[GLFW_KEY_SPACE])
		{
			velocity_.y = 8;
		}

		// cap xz speed, but not y speed
		float speed = glm::length(glm::vec2(velocity_.x, velocity_.z));
		if (speed > maxspeed_)
		{
			auto norm = glm::normalize(glm::vec2(velocity_.x, velocity_.z));
			velocity_.x = norm.x * maxspeed_;
			velocity_.z = norm.y * maxspeed_;

		}
		velocity_ += acceleration_ * dt;
		worldpos_ += velocity_ * dt;
		yaw_ += Input::Mouse().screenOffset.x;
		pitch_ += Input::Mouse().screenOffset.y;

		if (pitch_ > 89.f) pitch_ = 89.f;
		if (pitch_ < -89.f) pitch_ = -89.f;

		glm::vec3 temp;
		temp.x = cos(glm::radians(pitch_)) * cos(glm::radians(yaw_));
		temp.y = sin(glm::radians(pitch_));
		temp.z = cos(glm::radians(pitch_)) * sin(glm::radians(yaw_));
		front = glm::normalize(temp);
		dir_ = front;
		break;
	}
	case kControlCam:
		if (Input::Keyboard().down[GLFW_KEY_LEFT_SHIFT])
			currSpeed *= 10;
		if (Input::Keyboard().down[GLFW_KEY_LEFT_CONTROL])
			currSpeed /= 10;
		if (Input::Keyboard().down[GLFW_KEY_W])
			worldpos_ += currSpeed * front;
		if (Input::Keyboard().down[GLFW_KEY_S])
			worldpos_ -= currSpeed * front;
		if (Input::Keyboard().down[GLFW_KEY_A])
			worldpos_ -= glm::normalize(glm::cross(front, up)) * currSpeed;
		if (Input::Keyboard().down[GLFW_KEY_D])
			worldpos_ += glm::normalize(glm::cross(front, up)) * currSpeed;

		yaw_ += Input::Mouse().screenOffset.x;
		pitch_ += Input::Mouse().screenOffset.y;

		if (pitch_ > 89.f) pitch_ = 89.f;
		if (pitch_ < -89.f) pitch_ = -89.f;

		glm::vec3 temp;
		temp.x = cos(glm::radians(pitch_)) * cos(glm::radians(yaw_));
		temp.y = sin(glm::radians(pitch_));
		temp.z = cos(glm::radians(pitch_)) * sin(glm::radians(yaw_));
		front = glm::normalize(temp);
		dir_ = front;

		if (scrollMove)
			worldpos_ += 10 * Input::Mouse().scrollOffset.y * front;
		break;
	case kAffixedCam: // attached to an object, possibly follows directionality
		// TODO: add behavior to follow object
		break;
	case kImmobileCam: // do nothing
	default:
		break;
	}

	UpdateViewMat();
}

void Camera::UpdateViewMat()
{
	view_ = glm::lookAt(worldpos_, worldpos_ + front, up);
	frustum_->Transform(proj_, view_);
}
