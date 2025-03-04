#pragma once
#include "PreRequisites.h"
#include "Window.h"
#include "Prerequisites.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Swapchain.h"
#include "Texture.h"
#include "RenderTargetView.h"
#include "DepthStencilView.h"
#include "Viewport.h"
#include "ShaderProgram.h"
#include "Buffer.h"
#include "MeshComponent.h"
class
	BaseApp {
public:
	BaseApp() = default;
	~BaseApp() = default;

	HRESULT
	init();

	void
	update();

	void
	render();

	void
	destroy();


	/** @brief Ejecuta el bucle principal de la aplicación. */
	int
	run(HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPWSTR lpCmdLine,
		int nCmdShow,
		WNDPROC wndproc);


private:
	/** @brief Ventana principal de la aplicación. */
	Window m_window;
public:
	// Local Variables
	Window															g_window;
	Device															g_device;
	DeviceContext												g_deviceContext;
	SwapChain														g_swapchain;
	Texture															g_backBuffer;
	Texture															g_depthStencil;
	RenderTargetView										g_renderTargetView;
	DepthStencilView										g_depthStencilView;
	Viewport														g_viewport;
	ShaderProgram												g_shaderProgram;
	Buffer															g_vertexBuffer;
	Buffer															g_indexBuffer;
	Buffer															g_neverChanges;
	Buffer															g_changeOnResize;
	Buffer															g_changeEveryFrame;
	ID3D11SamplerState*									g_pSamplerLinear = nullptr;
	Texture															g_textureRV;

	XMMATRIX                            g_World;
	XMMATRIX                            g_View;
	XMMATRIX                            g_Projection;
	XMFLOAT4                            g_vMeshColor;

	CBChangesEveryFrame									cb;
	CBNeverChanges											cbNeverChanges;
	CBChangeOnResize										cbChangesOnResize; //olayonesi
};