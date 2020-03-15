#pragma once

class Camera;
class Shader;
class Pipeline
{
public:

	void SetShader(std::string shader);

	void AddCamera(Camera* cam)
	{
		cameras_.push_back(cam);
	}

	auto GetCamera(unsigned index)
	{
		return cameras_[index];
	}

	auto& GetAllCameras()
	{
		return cameras_;
	}

	void RemoveCamera(unsigned index)
	{
		cameras_.erase(cameras_.begin() + index);
	}

	glm::vec3 ClearColor = { 0, 0, 0 };
private:
	//std::unordered_map<std::string, Camera*> cameras_;
	std::vector<Camera*> cameras_; // view + projection matrices
	class Shader* activeShader_ = nullptr;
};