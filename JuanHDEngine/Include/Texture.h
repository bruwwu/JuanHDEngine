#pragma once
#include "PreRequisites.h"

class Device;
class DeviceContext;

class
	Texture {
public:
	Texture() = default;
	~Texture() = default;

	/** @brief Crea una textura a partir de una imagen (.dds) desde el ordenador. */
	HRESULT
	init(Device device,
		const std::string& textureName,
		ExtensionType extensionType);

	/** @brief Crea una textura 2D a partir de los datos proporcionados. */
	HRESULT
	init(Device device,
			unsigned int width,
			unsigned int height,
			DXGI_FORMAT Format,
			unsigned int BindFlags,
			unsigned int sampleCount = 1,
			unsigned int qualityLevels = 0);

	
	void
	update();

	/** @brief Renderiza la textura en pantalla si es necesario. */
	void
	render(DeviceContext& deviceContext, unsigned int StartSlot, unsigned int NumViews);

	void
	destroy();

public:
	/** @brief Maneja un recurso de textura como datos. */
	ID3D11Texture2D* m_texture = nullptr;
	/** @brief Maneja un recurso de textura como datos de imagen. */
	ID3D11ShaderResourceView* m_textureFromImg;
};
