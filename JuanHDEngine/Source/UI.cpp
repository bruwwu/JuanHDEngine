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

void
UI::renderWindow() {
  ImGui::Begin("yonesi de fortnite");
  ImGui::Text("Inserte Textura");
  ImGui::End();
}

void 
UI::Inspector()
{
  // Crea una nueva ventana
  ImGui::Begin("Cube Transform");

  // Controles para la posición del cubo
  ImGui::Text("Position");
  ImGui::DragFloat3("Position", reinterpret_cast<float*>(&g_app.position), 0.1f);

  // Controles para la rotación del cubo
  ImGui::Text("Rotation");
  ImGui::DragFloat3("Rotation", reinterpret_cast<float*>(&g_app.rotation), 0.1f);

  // Controles para la escala del cubo
  ImGui::Text("Scale");
  ImGui::DragFloat3("Scale", reinterpret_cast<float*>(&g_app.scale), 0.1f);

  // Termina la ventana
  ImGui::End();
}

void
UI::baseStyleGUI() {
  ImGuiStyle& style = ImGui::GetStyle();
  ImVec4* colors = style.Colors;

  colors[ImGuiCol_Text] = ImVec4(0.80f, 0.70f, 0.60f, 1.00f);            // Color de texto (beige oscuro)
  colors[ImGuiCol_WindowBg] = ImVec4(0.20f, 0.15f, 0.10f, 1.00f);        // Fondo de ventana (marrón muy oscuro)
  colors[ImGuiCol_Button] = ImVec4(0.40f, 0.25f, 0.15f, 1.00f);          // Botones (marrón oscuro)
  colors[ImGuiCol_ButtonHovered] = ImVec4(0.55f, 0.35f, 0.20f, 1.00f);   // Botones al pasar el mouse (marrón menos oscuro)
  colors[ImGuiCol_ButtonActive] = ImVec4(0.60f, 0.30f, 0.20f, 1.00f);    // Botones activos (marrón rojizo oscuro)
  colors[ImGuiCol_FrameBg] = ImVec4(0.25f, 0.15f, 0.10f, 1.00f);         // Fondo de los frames (marrón muy oscuro)
  colors[ImGuiCol_FrameBgHovered] = ImVec4(0.35f, 0.20f, 0.15f, 1.00f);  // Fondo de los frames con hover (más claro)
  colors[ImGuiCol_TitleBg] = ImVec4(0.35f, 0.20f, 0.10f, 1.00f);         // Fondo del título (marrón oscuro)
  colors[ImGuiCol_TitleBgActive] = ImVec4(0.45f, 0.30f, 0.15f, 1.00f);   // Fondo del título activo (marrón menos oscuro)

  colors[ImGuiCol_Border] = ImVec4(0.20f, 0.10f, 0.05f, 1.00f);          // Bordes (marrón muy oscuro)
  colors[ImGuiCol_CheckMark] = ImVec4(0.70f, 0.35f, 0.20f, 1.00f);       // Checkmark (marrón rojizo)
  colors[ImGuiCol_SliderGrab] = ImVec4(0.50f, 0.25f, 0.15f, 1.00f);      // Slider (marrón oscuro)
  colors[ImGuiCol_SliderGrabActive] = ImVec4(0.60f, 0.35f, 0.20f, 1.00f);// Slider activo (marrón menos oscuro)
  colors[ImGuiCol_Separator] = ImVec4(0.30f, 0.15f, 0.10f, 1.00f);       // Separadores (marrón muy oscuro)

  colors[ImGuiCol_Tab] = ImVec4(0.35f, 0.20f, 0.10f, 1.00f);             // Pestañas (marrón muy oscuro)
  colors[ImGuiCol_TabHovered] = ImVec4(0.50f, 0.30f, 0.20f, 1.00f);      // Pestañas al pasar el mouse (marrón menos oscuro)
  colors[ImGuiCol_TabActive] = ImVec4(0.55f, 0.30f, 0.20f, 1.00f);       // Pestañas activas (marrón oscuro)
  colors[ImGuiCol_Header] = ImVec4(0.30f, 0.15f, 0.10f, 1.00f);          // Encabezado (marrón oscuro)
  colors[ImGuiCol_HeaderHovered] = ImVec4(0.40f, 0.25f, 0.15f, 1.00f);   // Encabezado al pasar el mouse (más claro)
  colors[ImGuiCol_HeaderActive] = ImVec4(0.50f, 0.30f, 0.20f, 1.00f);    // Encabezado activo (marrón cálido)

  colors[ImGuiCol_PopupBg] = ImVec4(0.20f, 0.15f, 0.10f, 1.00f);         // Fondo de pop-ups (marrón oscuro)

  // Ajustes de estilo general
  style.WindowRounding = 5.0f;   // Redondeo de bordes de ventanas
  style.FrameRounding = 5.0f;   // Redondeo de bordes de cuadros
  style.ScrollbarRounding = 5.0f;   // Redondeo de bordes de scrollbar
  style.GrabRounding = 5.0f;   // Redondeo de bordes de botones de agarrar
  style.FrameBorderSize = 1.0f;   // Grosor del borde de cuadros
  style.WindowBorderSize = 1.0f;   // Grosor del borde de ventanas
  style.PopupBorderSize = 1.0f;   // Grosor del borde de popups
}