#include "BaseApp.h"


HRESULT
BaseApp::init() {
	HRESULT hr = S_OK;

	// Create Swapchain and BackBuffer
	hr = g_swapchain.init(g_device, g_deviceContext, g_backBuffer, g_window);
	if (FAILED(hr)) {
		return hr;
	}

	// Create a render target view
	hr = g_renderTargetView.init(g_device,
		g_backBuffer,
		DXGI_FORMAT_R8G8B8A8_UNORM);

	if (FAILED(hr)) {
		return hr;
	}

	// Create a depth stencil
	hr = g_depthStencil.init(g_device,
		g_window.m_width,
		g_window.m_height,
		DXGI_FORMAT_D24_UNORM_S8_UINT,
		D3D11_BIND_DEPTH_STENCIL,
		4,
		0);
	if (FAILED(hr))
		return hr;

	// Create the depth stencil view
	hr = g_depthStencilView.init(g_device,
		g_depthStencil,
		DXGI_FORMAT_D24_UNORM_S8_UINT);

	if (FAILED(hr))
		return hr;


	// Setup the viewport
	hr = g_viewport.init(g_window);

	if (FAILED(hr))
		return hr;

	// Define the input layout
	std::vector<D3D11_INPUT_ELEMENT_DESC> Layout;

	D3D11_INPUT_ELEMENT_DESC position;
	position.SemanticName = "POSITION";
	position.SemanticIndex = 0;
	position.Format = DXGI_FORMAT_R32G32B32_FLOAT;
	position.InputSlot = 0;
	position.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT /*0*/;
	position.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	position.InstanceDataStepRate = 0;
	Layout.push_back(position);

	D3D11_INPUT_ELEMENT_DESC texcoord;
	texcoord.SemanticName = "TEXCOORD";
	texcoord.SemanticIndex = 0;
	texcoord.Format = DXGI_FORMAT_R32G32_FLOAT;
	texcoord.InputSlot = 0;
	texcoord.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT /*12*/;
	texcoord.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	texcoord.InstanceDataStepRate = 0;
	Layout.push_back(texcoord);

	// Create the Shader Program
	hr = g_shaderProgram.init(g_device, "JuanHDEngine.fx", Layout);
	if (FAILED(hr))
		return hr;


	// Create the constant buffers

	hr = g_neverChanges.init(g_device, sizeof(CBNeverChanges));
	if (FAILED(hr))
		return hr;

	hr = g_changeOnResize.init(g_device, sizeof(CBChangeOnResize));
	if (FAILED(hr))
		return hr;



	// Initialize the view matrix
	XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	g_View = XMMatrixLookAtLH(Eye, At, Up);

  g_ui.init(g_window.m_hWnd, g_device.m_device, g_deviceContext.m_deviceContext);


	// Set Wattson Actor
	AWattson = EngineUtilities::MakeShared<Actor>(g_device);
	if (!AWattson.isNull()) {
		// Init Actor Transform
		AWattson->getComponent<Transform>()->setTransform(
			EngineUtilities::Vector3(0.0f, 0.0f, 0.0f),
			EngineUtilities::Vector3(0.0f, 3.0f, 0.0f),
			EngineUtilities::Vector3(0.03f, 0.03f, 0.03f));

		// Load Model
		g_modelLoader.LoadFBXModel("models/Wattson.fbx");

		// Init Actor Mesh
		AWattson->setMesh(g_device, g_modelLoader.meshes);

		// Set Actor Name
		AWattson->setName(g_modelLoader.modelName);


		std::vector<Texture> wattsonTextures;
		Texture Wattson_Face;
		Wattson_Face.init(g_device, "Textures/Face_D.png", ExtensionType::PNG);

    Texture Wattson_Clothes;
    Wattson_Clothes.init(g_device, "Textures/Jacket_D.png", ExtensionType::PNG);

		Texture Wattson_Gear;
    Wattson_Gear.init(g_device, "Textures/Gear_D.png", ExtensionType::PNG);

    Texture Wattson_Hair;
    Wattson_Hair.init(g_device, "Textures/Hair_D.png", ExtensionType::PNG);

    Texture Wattson_JumpKit;
    Wattson_JumpKit.init(g_device, "Textures/Jumpkit_D.png", ExtensionType::PNG);

    Texture Wattson_Suit;
    Wattson_Suit.init(g_device, "Textures/Suit_D.png", ExtensionType::PNG);


		g_WattsonTXT.reserve(7);
		g_WattsonTXT.push_back(Wattson_Suit);
		g_WattsonTXT.push_back(Wattson_Gear);
		g_WattsonTXT.push_back(Wattson_Clothes);
		g_WattsonTXT.push_back(Wattson_Gear);
		g_WattsonTXT.push_back(Wattson_JumpKit);
		g_WattsonTXT.push_back(Wattson_Face);
		g_WattsonTXT.push_back(Wattson_Hair);
    // Set Actor Textures
    AWattson->setTextures(g_WattsonTXT);
	
		g_actors.clear();

		if (!AWattson.isNull()) {
			g_actors.push_back(AWattson);
		}
		std::string msg = AWattson->getName() + " - Actor accessed successfully.";
		MESSAGE("Actor", "Actor", msg.c_str());
	}
	else {
		MESSAGE("Actor", "Actor", "Actor resource not found.");
	}



	
  AMichi = EngineUtilities::MakeShared<Actor>(g_device);
	if (!AMichi.isNull()) {
		AMichi->getComponent<Transform>()->setTransform(
			{ 0.0, 0.0f, 4.0f },      // Posición
			{ XM_PI / 1.0f, 0.0f, XM_PI }, // Rotación (en radianes)
			{ 0.05f, 0.05f, 0.05f }      // Escala (muy pequeña)
		);

		g_modelLoader1.LoadOBJ_model("models/Simple.obj");
		// Se asignan las mallas procesadas desde el .OBJ al actor
		AMichi->setMesh(g_device, g_modelLoader1.meshes);
    
    AMichi->setName(g_modelLoader1.modelName);
		// Se asignan las texturas a cada submesh del actor
	
		

		std::vector<Texture> MichiTXT;

		Texture head;
		head.init(g_device, "Textures/head.png", ExtensionType::PNG);

		Texture q;
		q.init(g_device, "Textures/head.png", ExtensionType::PNG);

		Texture w;
		w.init(g_device, "Textures/head.png", ExtensionType::PNG);

		Texture e;
		e.init(g_device, "Textures/head.png", ExtensionType::PNG);
		

		Texture body;
		body.init(g_device, "Textures/body.png", ExtensionType::PNG);

		Texture a;
		a.init(g_device, "Textures/body.png", ExtensionType::PNG);

		Texture s;
		s.init(g_device, "Textures/body.png", ExtensionType::PNG);

		Texture all;
		all.init(g_device, "Textures/all.png", ExtensionType::PNG);


		

    MichiTXT.push_back(head);
    MichiTXT.push_back(q);
    MichiTXT.push_back(w);
    MichiTXT.push_back(e);
    MichiTXT.push_back(body);
    MichiTXT.push_back(a);
    MichiTXT.push_back(s);
    MichiTXT.push_back(all);

		AMichi->setTextures(MichiTXT);
		
		if (!AMichi.isNull()) {
			g_actors.push_back(AMichi);
		}
		MESSAGE("Actor", "AMichi", (AMichi->getName() + " - Actor accessed successfully.").c_str());
	}
	else {
		ERROR("Actor", "AMichi", "Failed to create actor.");
	}
	return S_OK;
}
	



void
BaseApp::update() {
	g_ui.update();
	// Actualizar tiempo y rotación
	static float t = 0.0f;
	if (g_swapchain.m_driverType == D3D_DRIVER_TYPE_REFERENCE) {
		t += (float)XM_PI * 0.0125f;
	}
	else {
		static DWORD dwTimeStart = 0;
		DWORD dwTimeCur = GetTickCount();
		if (dwTimeStart == 0)
			dwTimeStart = dwTimeCur;
		t = (dwTimeCur - dwTimeStart) / 1000.0f;
	}
	// Renderizar UI
	g_ui.Inspector();
	updateTransalationbyKeys(t);

	// Actualizar la matriz de proyecci�n
	float FOV = XMConvertToRadians(90.0F);
	g_Projection = XMMatrixPerspectiveFovLH(FOV, g_window.m_width / (float)g_window.m_height, 0.01f, 10000.0f);

	updateCamera();
	// Actualizar la proyección en el buffer constante
	cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);
	g_changeOnResize.update(g_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);

	// Actualizar info logica del mesh
	AWattson->update(0, g_deviceContext);
	
  AMichi->update(0, g_deviceContext);
}

void
BaseApp::updateCamera() {

	if (ImGui::GetIO().WantCaptureMouse){
    mouseLeftDown = false; //Si caprura el mouse, no se puede mover la camara, yi yi papá
	}
	// Convertir la dirección a vectores normalizados
	XMVECTOR pos = XMLoadFloat3(&g_camera.position);
	XMVECTOR dir = XMLoadFloat3(&g_camera.forward);
	XMVECTOR up = XMLoadFloat3(&g_camera.up);

	// Calcular la nueva vista
	g_View = XMMatrixLookAtLH(pos, pos + dir, up);

	// Transponer y actualizar el buffer de la vista
	cbNeverChanges.mView = XMMatrixTranspose(g_View);
	g_neverChanges.update(g_deviceContext, 0, nullptr, &cbNeverChanges, 0, 0);
}

void
BaseApp::updateTransalationbyKeys(float deltaTime) {
	float moveSpeed = 0.001f; // Velocidad de movimiento
	float moveSpeedCamera = 0.01f; // Velocidad de movimiento

	if (keys[VK_UP])    position.y += moveSpeed * deltaTime; // Mueve arriba
	if (keys[VK_DOWN])  position.y -= moveSpeed * deltaTime; // Mueve abajo
	if (keys[VK_LEFT])  position.x -= moveSpeed * deltaTime; // Mueve izquierda
	if (keys[VK_RIGHT]) position.x += moveSpeed * deltaTime; // Mueve derecha
	if (keys['E'])      position.z += moveSpeed * deltaTime; // Avanza en Z
	if (keys['Q'])      position.z -= moveSpeed * deltaTime; // Retrocede en Z

	XMVECTOR pos = XMLoadFloat3(&g_camera.position);
	XMVECTOR forward = XMLoadFloat3(&g_camera.forward);
	XMVECTOR right = XMLoadFloat3(&g_camera.right);

	if (keys['W']) pos += forward * moveSpeedCamera;
	if (keys['S']) pos -= forward * moveSpeedCamera;
	if (keys['A']) pos -= right * moveSpeedCamera;
	if (keys['D']) pos += right * moveSpeedCamera;

	XMStoreFloat3(&g_camera.position, pos);

}

void BaseApp::rotateCamera(int mouseX, int mouseY)
{
	float offsetX = (mouseX - lastX) * sensitivity;
	float offsetY = (mouseY - lastY) * sensitivity;
	lastX = mouseX;
	lastY = mouseY;

	g_camera.yaw += offsetX;
	g_camera.pitch += offsetY;

	// Limitar la inclinación de la cámara
	if (g_camera.pitch > 1.5f) g_camera.pitch = 1.5f;
	if (g_camera.pitch < -1.5f) g_camera.pitch = -1.5f;

	// Recalcular la dirección hacia adelante
	XMVECTOR forward = XMVectorSet(
		cosf(g_camera.yaw) * cosf(g_camera.pitch),
		sinf(g_camera.pitch),
		sinf(g_camera.yaw) * cosf(g_camera.pitch),
		0.0f
	);

	XMVECTOR right = XMVector3Cross(forward, XMLoadFloat3(&g_camera.up));

	XMStoreFloat3(&g_camera.forward, XMVector3Normalize(forward));
	XMStoreFloat3(&g_camera.right, XMVector3Normalize(right));
}

void
BaseApp::render() {
	// Clear the back buffer
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha

	// Set Viewport
	g_viewport.render(g_deviceContext);

	// Set Render Target View
	g_renderTargetView.render(g_deviceContext, g_depthStencilView, 1, ClearColor);

	// Set Depth Stencil View
	g_depthStencilView.render(g_deviceContext);

	// Render the cube
	g_shaderProgram.render(g_deviceContext);

	// Render the models
	AWattson->render(g_deviceContext);
  AMichi->render(g_deviceContext);
	//Awebitos->render(m_deviceContext);

	// Set Constant Buffers and asign Shaders
	g_neverChanges.render(g_deviceContext, 0, 1);
	g_changeOnResize.render(g_deviceContext, 1, 1);

	// Drawing
	//m_deviceContext.DrawIndexed(MC.m_index.size(), 0, 0);

	// Render the UI
  g_ui.render();

	// Present our back buffer to our front buffer
	g_swapchain.present();
}

void
BaseApp::destroy() {
	if (g_deviceContext.m_deviceContext) g_deviceContext.m_deviceContext->ClearState();
  //AWattson->destroy();
  //AMichi->destroy();	

	//g_textureRV.destroy();
	g_neverChanges.destroy();
	g_changeOnResize.destroy();
	//g_changeEveryFrame.destroy();
	//g_vertexBuffer.destroy();
	//g_indexBuffer.destroy();
	g_shaderProgram.destroy();

  g_ui.destroy();
	g_depthStencil.destroy();
	g_depthStencilView.destroy();
	g_renderTargetView.destroy();
	g_swapchain.destroy();
	g_deviceContext.destroy();
	g_device.destroy();
}





int
BaseApp::run(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow,
	WNDPROC wndproc) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	if (FAILED(g_window.init(hInstance, nCmdShow, wndproc)))
		return 0;

	if (FAILED(init())) {
		destroy();
		return 0;
	}

	// Main message loop
	MSG msg = { 0 };
	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			update();
			render();
		}
	}

	destroy();

	return (int)msg.wParam;
}

HRESULT
BaseApp::resizeWindow(HWND hWnd, LPARAM lParam) {

	if (g_swapchain.m_swapchain)
	{
    HRESULT hr = S_OK;

    // Liberar los valores anteriores del RTV, DS, DSV, Back Buffer
    g_renderTargetView.destroy();
    g_depthStencil.destroy();
    g_depthStencilView.destroy();
    g_backBuffer.destroy();

    // Redimensionar los datos del ancho y alto de la ventana
    g_window.m_width = LOWORD(lParam);
    g_window.m_height = HIWORD(lParam);


    // Redimensionar el buffer del swapchain
    hr = g_swapchain.m_swapchain->ResizeBuffers(0, g_window.m_width, g_window.m_height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
    if (FAILED(hr)){
      ERROR("SwapChain", "resizeWindow", "Failed to resize swapchain buffers");
      return hr;
		}

    // Recrear backbuffer, revisar Swapchain
		hr = g_swapchain.m_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&g_backBuffer.m_texture));
    if (FAILED(hr))
      return hr;

    // Recrear el RTV
    hr = g_renderTargetView.init(g_device, g_backBuffer, DXGI_FORMAT_R8G8B8A8_UNORM);
    if (FAILED(hr))
      return hr;

    // Recrear DS
    hr = g_depthStencil.init(g_device, g_window.m_width, g_window.m_height, DXGI_FORMAT_D24_UNORM_S8_UINT, D3D11_BIND_DEPTH_STENCIL, 4, 0);
    if (FAILED(hr))
      return hr;

    // Recrear DSV
    hr = g_depthStencilView.init(g_device, g_depthStencil, DXGI_FORMAT_D24_UNORM_S8_UINT);
    if (FAILED(hr))
      return hr;

    // Actualizar viewport
    hr = g_viewport.init(g_window);
    if (FAILED(hr))
      return hr;

    // Actualizar la proyección, o sea, ChangeOnResize
		g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, g_window.m_width / (float)g_window.m_height, 0.01f, 100.0f);
		cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);
		g_changeOnResize.update(g_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);

    return S_OK;
  }
	}

	/*
	1. Validar que existe el swapchain
	2. Destruir los valores anteriores del RTV, DS, DSV, Back Buffer
	3. Ya destruidos los valores, redimenzionar los datos del ancho y alto de la ventana
	4. Redimenzionar el buffer del swapchain
	5. Si algo falla se manda un error bien yon
	6. Recrear backbuffer, revisar Swapchain
	7. Recrear el RTV
	8. Recrear DS
	9. Recrear DSV
	10. Actualizar viewport
	11. Actualizar la proyección, o sea, ChangeOnResize*/