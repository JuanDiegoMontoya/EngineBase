#pragma once

class Frustum;

enum CameraType : int
{
	kPhysicsCam, // uses movement keys to affect velocity and acceleration
	kControlCam, // use movement keys to fly around
	kAffixedCam, // parented to some object
	kImmobileCam // cannot move
};

class Camera
{
public:
	Camera(CameraType type);
	void Update(float dt);
	const glm::mat4& GetView() const { return view_; }
	const glm::mat4& GetProj() const { return proj_; }
	const CameraType GetType() const { return type_; }
	const glm::vec3& GetPos() const { return worldpos_; }
	const glm::vec3& GetDir() const { return dir_; }
	const Frustum* GetFrustum() const { return frustum_; }
	float GetFov() const { return fov_; }
	float GetNear() const { return near_; }
	float GetFar() const { return far_; }
	glm::vec3 GetEuler() const { return { pitch_, yaw_, roll_ }; }

	void SetPos(const glm::vec3& v) { worldpos_ = v; }
	void SetType(CameraType t) { type_ = t; }
	void SetFar(float f) { far_ = f; GenProjection(); }
	void GenProjection(float fovDeg = 80.f)
	{
		proj_ = glm::perspective(glm::radians(fovDeg), 1920.f / 1080.f, near_, far_);
	}

	glm::vec3 up = glm::vec3(0, 1.f, 0);
	glm::vec3 front = glm::vec3(0, 0, -1.f);

	// physics (temp)
	glm::vec3 velocity_;
	glm::vec3 acceleration_;
	float maxspeed_ = 5.0f;
	glm::vec3 oldPos;
private:
	CameraType type_;
	glm::vec3 worldpos_ = glm::vec3(150, 50, 100);
	glm::vec3 dir_ = glm::vec3(-.22f, .22f, -.95f);
	glm::mat4 view_ = glm::mat4(1);
	glm::mat4 proj_;
	Frustum* frustum_;

	float speed_ = 3.5f;

	float pitch_ = 16;
	float yaw_ = 255;
	float roll_ = 0;
	float fov_ = 80.f;

	float near_ = .1f;
	float far_ = 300.f;
};