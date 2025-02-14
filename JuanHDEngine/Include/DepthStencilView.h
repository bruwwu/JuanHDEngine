#pragma once
#include "PreRequisites.h"

class Device;
class DeviceContext;
class Texture;

class
	DepthStencilView {
public:
	DepthStencilView() = default;
	~DepthStencilView() = default;

	/** @brief Inicializa la vista de profundidad y stencil. */
	HRESULT
	init(Device& device,
		Texture& depthStencil,
		DXGI_FORMAT format);

	/** @brief Actualiza el estado de la vista de profundidad y stencil. */
	void
	update();

	/** @brief Renderiza utilizando la vista de profundidad y stencil. */
	void
	render(DeviceContext& deviceContext);

	/** @brief Libera los recursos de la vista de profundidad y stencil. */
	void
	destroy();

public:
	ID3D11DepthStencilView* m_depthStencilView = nullptr;
};
