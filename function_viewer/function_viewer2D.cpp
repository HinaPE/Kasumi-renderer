#include "function_viewer2D.h"

Kasumi::FunctionViewer2D::FunctionViewer2D() { clean_mode(); }

void Kasumi::FunctionViewer2D::load(const std::function<real(real)> &f, real x_min, real x_max)
{
	ImGui::SetNextWindowPos({0.0f, 0.0f}, ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize({ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y}, ImGuiCond_FirstUseEver);
	ImGui::Begin("Monitor", nullptr, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize);

	static ImPlotAxisFlags flags = ImPlotAxisFlags_AutoFit | ImPlotAxisFlags_Opposite;
	ImPlot::SetupAxes(nullptr, nullptr, flags, flags);
	ImPlot::SetupAxisLimits(ImAxis_X1, x_min, x_max, ImGuiCond_Always);
	ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 1);

	ImGui::End();
}
