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

  g_Wattson.LoadFBXModel("models/Wattson.fbx");

	// Create vertex buffer
	SimpleVertex
		vertices[] = {
				{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
				{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
				{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
				{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

				{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
				{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
				{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
				{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

				{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
				{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
				{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
				{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

				{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
				{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
				{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
				{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

				{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
				{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
				{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
				{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 1.0f) },

				{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
				{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },
				{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
				{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
	};

	/*D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 24;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;
	hr = g_device.CreateBuffer(&bd, &InitData, &g_pVertexBuffer);
	if (FAILED(hr))
		return hr;*/

		// Create vertex buffer
	unsigned int
		indices[] = {
				3,1,0,
				2,1,3,

				6,4,5,
				7,4,6,

				11,9,8,
				10,9,11,

				14,12,13,
				15,12,14,

				19,17,16,
				18,17,19,

				22,20,21,
				23,20,22
	};

	MeshComponent MC;
	for (SimpleVertex vertex : vertices) {
		MC.m_vertex.push_back(vertex);
	}

	for (unsigned int index : indices) {
		MC.m_index.push_back(index);
	}

	MC.m_numVertex = MC.m_vertex.size();
	MC.m_numIndex = MC.m_index.size();

	hr = g_vertexBuffer.init(g_device, MC, D3D11_BIND_VERTEX_BUFFER);

	if (FAILED(hr))
		return hr;

	hr = g_indexBuffer.init(g_device, MC, D3D11_BIND_INDEX_BUFFER);

	if (FAILED(hr))
		return hr;

	// Create the constant buffers

	hr = g_neverChanges.init(g_device, sizeof(CBNeverChanges));
	if (FAILED(hr))
		return hr;

	hr = g_changeOnResize.init(g_device, sizeof(CBChangeOnResize));
	if (FAILED(hr))
		return hr;

	hr = g_changeEveryFrame.init(g_device, sizeof(CBChangesEveryFrame));
	if (FAILED(hr))
		return hr;

	hr = g_textureRV.init(g_device, "seafloor.dds", DDS);
	if (FAILED(hr))
		return hr;

	//bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.ByteWidth = sizeof(WORD) * 36;
	//bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	//bd.CPUAccessFlags = 0;
	//InitData.pSysMem = indices;
	//hr = g_device.CreateBuffer(&bd, &InitData, &g_pIndexBuffer);
	//if (FAILED(hr))
	//	return hr;

	//// Create the constant buffers
	//bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.ByteWidth = sizeof(CBNeverChanges);
	//bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//bd.CPUAccessFlags = 0;
	//hr = g_device.CreateBuffer(&bd, nullptr, &g_pCBNeverChanges);
	//if (FAILED(hr))
	//	return hr;

	//bd.ByteWidth = sizeof(CBChangeOnResize);
	//hr = g_device.CreateBuffer(&bd, nullptr, &g_pCBChangeOnResize);
	//if (FAILED(hr))
	//	return hr;

	//bd.ByteWidth = sizeof(CBChangesEveryFrame);
	//hr = g_device.CreateBuffer(&bd, nullptr, &g_pCBChangesEveryFrame);
	//if (FAILED(hr))
	//	return hr;

	//// Load the Texture
	/*hr = D3DX11CreateShaderResourceViewFromFile(g_device.m_device, "seafloor.dds", nullptr, nullptr, &g_TextureRV, nullptr);*/



	//// Create the sample state
	//D3D11_SAMPLER_DESC sampDesc;
	//ZeroMemory(&sampDesc, sizeof(sampDesc));
	//sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	//sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	//sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	//sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	//sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	//sampDesc.MinLOD = 0;
	//sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	//hr = g_device.CreateSamplerState(&sampDesc, &g_pSamplerLinear);
	//if (FAILED(hr))
	//	return hr;
	/*Se movió esta partecita al SamplerState, que pro*/
	g_ui.init(g_window.m_hWnd, g_device.m_device, g_deviceContext.m_deviceContext);

	// Initialize the world matrices
	g_modelMatrix = XMMatrixIdentity();

	//Escala del objeto, 
  scale.x = 1.0f;
  scale.y = 1.0f;
  scale.z = 1.0f;

 

	// Initialize the view matrix
	XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	g_View = XMMatrixLookAtLH(Eye, At, Up);
	return S_OK;
}



void
BaseApp::update() {
	// Actualizar tiempo y rotaci�n
	g_ui.update();
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
  g_ui.renderWindow();
	updateTransalationbyKeys(t);
	

	// Actualizar la rotaci�n del objeto y el color
	g_modelMatrix = XMMatrixRotationY(t);
	g_vMeshColor = XMFLOAT4(
		(sinf(t * 1.0f) + 1.0f) * 0.5f,
		(cosf(t * 3.0f) + 1.0f) * 0.5f,
		(sinf(t * 5.0f) + 1.0f) * 0.5f,
		1.0f
	);

	//Rotacion del objeto
	rotation.y = t;

  XMMATRIX scaleMatrix = XMMatrixScaling(scale.x, scale.y, scale.z);
  XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
  XMMATRIX translationMatrix = XMMatrixTranslation(position.x, position.y, position.z);

	g_modelMatrix = scaleMatrix * rotationMatrix * translationMatrix;

	// Actualizar el buffer constante del frame
	cb.mWorld = XMMatrixTranspose(g_modelMatrix);
	g_vMeshColor = XMFLOAT4(
		(sinf(t * 1.0f) + 1.0f) * 0.5f,
		(cosf(t * 3.0f) + 1.0f) * 0.5f,
		(sinf(t * 5.0f) + 1.0f) * 0.5f,
		1.0f
	);
	cb.vMeshColor = g_vMeshColor;


	//g_deviceContext.UpdateSubresource(g_pCBChangesEveryFrame, 0, nullptr, &cb, 0, 0);
	g_changeEveryFrame.update(g_deviceContext, 0, nullptr, &cb, 0, 0);

	// Actualizar la matriz de proyecci�n
	float FOV = XMConvertToRadians(90.0F);
	g_Projection = XMMatrixPerspectiveFovLH(FOV, g_window.m_width / (float)g_window.m_height, 0.01f, 10000.0f);

	updateCamera();
	// Actualizar la proyecci�n en el buffer constante
	cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);
	//g_deviceContext.UpdateSubresource(g_pCBChangeOnResize, 0, nullptr, &cbChangesOnResize, 0, 0);
	g_changeOnResize.update(g_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);

	/*Nota
	Se arregló el error con el renderizado del cubito kawaii, el problema fue por tener un g_neverChanges
	en donde no era, todo bobomensotonto*/
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
	// Limpiar los buffers
	const float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha

	// Set Render Target View
	g_renderTargetView.render(g_deviceContext, g_depthStencilView, 1, ClearColor);

	// Set Viewport
	g_viewport.render(g_deviceContext);

	// Set Depth Stencil View
	g_depthStencilView.render(g_deviceContext);

	// Configurar los buffers y shaders para el pipeline
	g_shaderProgram.render(g_deviceContext);

	g_vertexBuffer.render(g_deviceContext, 0, 1);
	g_indexBuffer.render(g_deviceContext, 0, 1, false, DXGI_FORMAT_R32_UINT);
	g_deviceContext.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Asignar shaders y buffers constantes
	// Renderizar buffers constantes en el Vertex Shader
	g_neverChanges.render(g_deviceContext, 0, 1);
	g_changeOnResize.render(g_deviceContext, 1, 1);
	g_changeEveryFrame.render(g_deviceContext, 2, 1);

	// Renderizar buffers constantes en el Pixel Shader (si aplica)
	g_changeEveryFrame.render(g_deviceContext, 2, 1, true);

	g_textureRV.render(g_deviceContext, 0, 1);
	g_deviceContext.PSSetSamplers(0, 1, &g_pSamplerLinear);

	// Dibujar
	g_deviceContext.DrawIndexed(36, 0, 0);

  g_ui.render();
	// Presentar el frame en pantalla
	g_swapchain.present();
}

void
BaseApp::destroy() {
	if (g_deviceContext.m_deviceContext) g_deviceContext.m_deviceContext->ClearState();

	if (g_pSamplerLinear) g_pSamplerLinear->Release();

	g_textureRV.destroy();
	g_neverChanges.destroy();
	g_changeOnResize.destroy();
	g_changeEveryFrame.destroy();
	g_vertexBuffer.destroy();
	g_indexBuffer.destroy();
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