#pragma once
#include "PreRequisites.h"

// Forward Declarations - Declaraciones Directas
class Device;
class DeviceContext;
class Window;
class Texture;

class
	SwapChain {
public:
	SwapChain() = default;
	~SwapChain() = default;

	/** @brief Inicializa el SwapChain con el dispositivo, contexto y buffer de respaldo. */
	HRESULT
		init(Device& device,
			DeviceContext& deviceContext,
			Texture& backBuffer,
			Window window);

	/** @brief Actualiza el estado del SwapChain. */
	void
		update();

	/** @brief Renderiza utilizando el SwapChain. */
	void
		render();

	/** @brief Libera los recursos del SwapChain. */
	void
		destroy();

	/** @brief Presenta el contenido del buffer en pantalla. */
	void
		present();

public:
	IDXGISwapChain* m_swapchain = nullptr;
	D3D_DRIVER_TYPE m_driverType = D3D_DRIVER_TYPE_NULL;
private:
	D3D_FEATURE_LEVEL m_featureLevel = D3D_FEATURE_LEVEL_11_0;
	// MSAA Configuration
	/*
	 * Para evitar que los píxeles se vean con un efecto de "serrucho" (aliasing) en DirectX 11 con C++,
	 * se puede utilizar una técnica llamada anti-aliasing.
	 *
	 * Multisample Anti-Aliasing (MSAA)
	 * MSAA es una técnica que suaviza los bordes de los objetos al muestrear varios puntos por píxel.
	 * Para habilitar MSAA en DirectX 11:
	 *
	 */


	/** @brief Número de muestras para MSAA. */
	unsigned int m_sampleCount;  // Number of MSAA samples (4x MSAA)

	/** @brief Niveles de calidad para MSAA. */
	unsigned int m_qualityLevels;

	// Punteros a las interfaces DXGI
	IDXGIDevice* m_dxgiDevice = nullptr;
	IDXGIAdapter* m_dxgiAdapter = nullptr;
	IDXGIFactory* m_dxgiFactory = nullptr;
};
