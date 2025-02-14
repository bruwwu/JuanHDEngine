#pragma once
#include "PreRequisites.h"

// Forward Declarations
class Device;
class DeviceContext;
class Texture;
class DepthStencilView;

class
	RenderTargetView {
public:
	RenderTargetView() = default;
	~RenderTargetView() = default;

	/** @brief Inicializa la vista de renderizado con un buffer de respaldo y un formato específico. */
	HRESULT
	init(Device& device, 
		Texture& backBuffer, 
		DXGI_FORMAT Format);

	/** @brief Actualiza el estado de la vista de renderizado. */
	void
	update();

	/** @brief Renderiza utilizando la vista de renderizado y el depth stencil. */
	void
	render(DeviceContext& deviceContext,
			DepthStencilView& depthStencilView,
			unsigned int numViews,
			const float ClearColor[4]);

	/** @brief Libera los recursos de la vista de renderizado. */
	void
	destroy();

public:
	ID3D11RenderTargetView* m_renderTargetView = nullptr;
};