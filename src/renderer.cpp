#include "renderer.hpp"

#include <algorithm>
#include <unordered_map>

Renderer::Renderer(GPU& gpu, const std::array<u32, regNum>& internalRegs, const std::array<u32, extRegNum>& externalRegs)
	: gpu(gpu), regs(internalRegs), externalRegs(externalRegs) {}
Renderer::~Renderer() {}

std::optional<RendererType> Renderer::typeFromString(std::string inString) {
	// Transform to lower-case to make the setting case-insensitive
	std::transform(inString.begin(), inString.end(), inString.begin(), [](unsigned char c) { return std::tolower(c); });

	// Huge table of possible names and misspellings
	// Please stop misspelling Vulkan as Vulcan
	static const std::unordered_map<std::string, RendererType> map = {
		{"null", RendererType::Null},         {"nil", RendererType::Null},      {"none", RendererType::Null},
		{"gl", RendererType::OpenGL},         {"ogl", RendererType::OpenGL},    {"opengl", RendererType::OpenGL},
		{"vk", RendererType::Vulkan},         {"vulkan", RendererType::Vulkan}, {"vulcan", RendererType::Vulkan},
		{"mtl", RendererType::Metal},         {"metal", RendererType::Metal},
		{"sw", RendererType::Software},       {"soft", RendererType::Software}, {"software", RendererType::Software},
		{"softrast", RendererType::Software},
	};

	if (auto search = map.find(inString); search != map.end()) {
		return search->second;
	}

	return std::nullopt;
}

const char* Renderer::typeToString(RendererType rendererType) {
	switch (rendererType) {
		case RendererType::Null: return "null";
		case RendererType::OpenGL: return "opengl";
		case RendererType::Vulkan: return "vulkan";
		case RendererType::Metal: return "metal";
		case RendererType::Software: return "software";
		default: return "Invalid";
	}
}
