#include "UI.h"
#include "Prerequisites.h"
#include "BaseApp.h"

extern BaseApp g_app; //Antes de esto lo estaba haciendo sin el extern, por lo que entendí asi no creo una 
//nueva instancia de BaseApp, sino que uso la que ya tengo creada en BaseApp.cpp

void 
UI::init(void* window, ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;        // Enable Gamepad Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

  // Setup Dear ImGui style
  baseStyleGUI();

  // Setup Dear ImGui style
  ImGuiStyle& style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }



  // Setup Platform/Renderer bindings
  ImGui_ImplWin32_Init(window);
  ImGui_ImplDX11_Init(device, deviceContext);

  
    
}
void
UI::update()
{
  // Start the Dear ImGui frame
  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();
  ImGui::NewFrame();
}

void
UI::render()
{
  // Rendering
  ImGui::Render();
  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
  ImGuiIO& io = ImGui::GetIO();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
  }
} 

void
UI::destroy()
{
  // Cleanup
  ImGui_ImplDX11_Shutdown();
  ImGui_ImplWin32_Shutdown();
  ImGui::DestroyContext();
}

void UI::Inspector()
{
    static int selectedActorIndex = -1; // Índice del actor seleccionado

    ImGui::Begin("Actor Inspector");

    // — Lista jerárquica de actores —
    ImGui::Text("Actors in Scene:");
    for (int i = 0; i < (int)g_app.g_actors.size(); ++i) {
        auto& actor = g_app.g_actors[i];
        if (!actor) continue;
        bool isSelected = (selectedActorIndex == i);
        // Visible label: actor name; Internal ID: "##Actor_i"
        std::string label = actor->getName() + "##Actor_" + std::to_string(i);
        if (ImGui::Selectable(label.c_str(), isSelected)) {
            selectedActorIndex = i;
        }
    }

    ImGui::Separator();

    // — Inspector de transform del actor seleccionado —
    if (selectedActorIndex >= 0 && selectedActorIndex < (int)g_app.g_actors.size()) {
        auto& actor     = g_app.g_actors[selectedActorIndex];
        auto  transform = actor->getComponent<Transform>();
        if (transform) {
            ImGui::Text("Transform for %s", actor->getName().c_str());

            // Preparamos un buffer para las etiquetas con ID único
            char buf[64];

            // Position
            sprintf(buf, "Position##pos_%d", selectedActorIndex);
            ImGui::DragFloat3(buf, &transform->position.x, 0.1f);

            // Rotation
            sprintf(buf, "Rotation##rot_%d", selectedActorIndex);
            ImGui::DragFloat3(buf, &transform->rotation.x, 0.1f);

            // Scale
            sprintf(buf, "Scale##scl_%d", selectedActorIndex);
            ImGui::DragFloat3(buf, &transform->scale.x,    0.1f);
        }
        else {
            ImGui::TextColored(ImVec4(1,0,0,1), "No Transform component!");
        }
    }

    ImGui::End();
}



void UI::baseStyleGUI() {
  ImGuiStyle& style = ImGui::GetStyle();
  ImVec4* colors = style.Colors;

  colors[ImGuiCol_Text] = ImVec4(1.0f, 0.85f, 0.35f, 1.00f);            // Dorado para el texto
  colors[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);       // Fondo negro
  colors[ImGuiCol_Button] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);         // Botones negros opacos
  colors[ImGuiCol_ButtonHovered] = ImVec4(1.0f, 0.85f, 0.35f, 1.00f);   // Hover con dorado brillante
  colors[ImGuiCol_ButtonActive] = ImVec4(0.85f, 0.65f, 0.25f, 1.00f);   // Botones activos con dorado más tenue

  colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);        // Fondo del frame negro opaco
  colors[ImGuiCol_FrameBgHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f); // Fondo del frame al pasar el mouse gris oscuro
  colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);        // Fondo del título negro
  colors[ImGuiCol_TitleBgActive] = ImVec4(1.0f, 0.85f, 0.35f, 1.00f);   // Fondo del título activo dorado

  colors[ImGuiCol_Border] = ImVec4(0.85f, 0.65f, 0.25f, 1.00f);         // Bordes dorados
  colors[ImGuiCol_CheckMark] = ImVec4(1.0f, 0.85f, 0.35f, 1.00f);       // Checkmark dorado
  colors[ImGuiCol_SliderGrab] = ImVec4(0.85f, 0.65f, 0.25f, 1.00f);     // Slider dorado
  colors[ImGuiCol_SliderGrabActive] = ImVec4(1.0f, 0.85f, 0.35f, 1.00f);// Slider activo con dorado brillante
  colors[ImGuiCol_Separator] = ImVec4(0.85f, 0.65f, 0.25f, 1.00f);      // Separadores dorados

  colors[ImGuiCol_Tab] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);            // Pestañas negras opacas
  colors[ImGuiCol_TabHovered] = ImVec4(1.0f, 0.85f, 0.35f, 1.00f);      // Hover dorado
  colors[ImGuiCol_TabActive] = ImVec4(0.85f, 0.65f, 0.25f, 1.00f);      // Pestañas activas doradas
  colors[ImGuiCol_Header] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);         // Encabezados negros opacos
  colors[ImGuiCol_HeaderHovered] = ImVec4(1.0f, 0.85f, 0.35f, 1.00f);   // Encabezados al pasar el mouse dorados
  colors[ImGuiCol_HeaderActive] = ImVec4(0.85f, 0.65f, 0.25f, 1.00f);   // Encabezados activos dorados

  colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);        // Fondo de pop-ups negros

  // Ajustes de estilo general
  style.WindowRounding = 10.0f;   // Redondeo más pronunciado
  style.FrameRounding = 10.0f;    // Redondeo de los frames
  style.ScrollbarRounding = 10.0f;// Redondeo de los scrollbars
  style.GrabRounding = 10.0f;     // Redondeo de los sliders y botones de agarre
  style.FrameBorderSize = 2.0f;   // Bordes más prominentes en los cuadros
  style.WindowBorderSize = 2.0f;  // Grosor del borde de ventanas
  style.PopupBorderSize = 2.0f;   // Grosor del borde de pop-ups
}
