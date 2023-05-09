#include "renderer3D.h"

#include "nfd/nfd.h"

Kasumi::Renderer3D Kasumi::Renderer3D::DEFAULT_RENDERER = Kasumi::Renderer3D();

void Kasumi::Renderer3D::ui_menu()
{
	if (ImGui::BeginMenu("Scene"))
	{
		if (ImGui::MenuItem("Open Scene"))
		{
			char *path = nullptr;
			NFD_OpenDialog("json", nullptr, &path);
			if (path)
			{
				std::string spath(path);
				_scene->read_scene(spath);
				free(path);
			}
		}
		if (ImGui::MenuItem("Export Scene"))
		{
			char *path = nullptr;
			NFD_SaveDialog("json", nullptr, &path);
			if (path)
			{
				std::string spath(path);
				_scene->export_scene(spath);
				free(path);
			}
		}
		if (ImGui::MenuItem("Save Scene (Ctrl+s)")) { _scene->export_scene(); }
		ImGui::EndMenu();
	}

//	if (ImGui::BeginMenu("Edit"))
//	{
//		if (ImGui::MenuItem("Undo (Ctrl+z)")) {}
//		if (ImGui::MenuItem("Redo (Ctrl+y)")) {}
//		if (ImGui::MenuItem("Edit Debug Data (Ctrl+d)")) {}
//		if (ImGui::MenuItem("Settings")) {}
//		ImGui::EndMenu();
//	}
//
//	if (ImGui::BeginMenu("Pathtracer"))
//	{
//		if (ImGui::MenuItem("Load Pathtracer")) {}
//		ImGui::EndMenu();
//	}
}
