#pragma once
#include "PreRequisites.h"

class
	DeviceContext {
public:
	DeviceContext() = default;
	~DeviceContext() = default;

	/** @brief Inicializa el contexto del dispositivo. */
	void
		init();

	/** @brief Actualiza el estado del dispositivo. */
	void
		update();

	/** @brief Renderiza la escena. */
	void
		render();

	/** @brief Libera los recursos del contexto del dispositivo. */
	void
		destroy();

	/** @brief Configura las viewport en el rasterizador. */
	void
	RSSetViewports(unsigned int NumViewports,
					const D3D11_VIEWPORT* pViewports);

	/** @brief Establece las texturas de recursos para el shader de píxeles. */
	void
	PSSetShaderResources(unsigned int StartSlot,
						unsigned int NumViews,
						ID3D11ShaderResourceView* const* ppShaderResourceViews);

	/** @brief Define el diseño de entrada para la etapa de ensamblado de entrada. */
	void
	IASetInputLayout(ID3D11InputLayout* pInputLayout);

	/** @brief Establece el shader de vértices actual. */
	void
	VSSetShader(ID3D11VertexShader* pVertexShader,
				ID3D11ClassInstance* const* ppClassInstances,
				unsigned int NumClassInstances);

	/** @brief Establece el shader de píxeles actual. */
	void
	PSSetShader(ID3D11PixelShader* pPixelShader,
				ID3D11ClassInstance* const* ppClassInstances,
				unsigned int NumClassInstances);

	/** @brief Actualiza una subrecurso de una textura o buffer. */
	void
	UpdateSubresource(ID3D11Resource* pDstResource,
					unsigned int DstSubresource,
					const D3D11_BOX* pDstBox,
					const void* pSrcData,
					unsigned int SrcRowPitch,
					unsigned int SrcDepthPitch);

	/** @brief Establece los buffers de vértices para la etapa de ensamblado de entrada. */
	void
	IASetVertexBuffers(unsigned int StartSlot,
					unsigned int NumBuffers,
					ID3D11Buffer* const* ppVertexBuffers,
					const unsigned int* pStrides,
					const unsigned int* pOffsets);

	/** @brief Establece el buffer de índices para la etapa de ensamblado de entrada. */
	void
	IASetIndexBuffer(ID3D11Buffer* pIndexBuffer,
					DXGI_FORMAT Format,
					unsigned int Offset);

	/** @brief Configura los estados de muestreo para el shader de píxeles. */
	void
	PSSetSamplers(unsigned int StartSlot,
				unsigned int NumSamplers,
				ID3D11SamplerState* const* ppSamplers);

	/** @brief Configura el estado del rasterizador. */
	void
	RSSetState(ID3D11RasterizerState* pRasterizerState);

	/** @brief Configura el estado de mezcla para la salida de mezcla. */
	void
	OMSetBlendState(ID3D11BlendState* pBlendState,
					const float BlendFactor[4],
					unsigned int SampleMask);

	/** @brief Configura los objetivos de renderizado y el buffer de profundidad. */
	void
	OMSetRenderTargets(unsigned int NumViews,
						ID3D11RenderTargetView* const* ppRenderTargetViews,
						ID3D11DepthStencilView* pDepthStencilView);

	/** @brief Configura la topología de la primitiva para el ensamblado de entrada. */
	void
	IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology);

	/** @brief Limpia el objetivo de renderizado con un color específico. */
	void
	ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView,
						const float ColorRGBA[4]);

	/** @brief Limpia el buffer de profundidad y plantilla. */
	void
	ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView,
						unsigned int ClearFlags,
						float Depth,
						UINT8 Stencil);

	/** @brief Configura los buffers constantes para el shader de vértices. */
	void
	VSSetConstantBuffers(unsigned int StartSlot,
						unsigned int NumBuffers,
						ID3D11Buffer* const* ppConstantBuffers);

	/** @brief Configura los buffers constantes para el shader de píxeles. */
	void
	PSSetConstantBuffers(unsigned int StartSlot,
						unsigned int NumBuffers,
						ID3D11Buffer* const* ppConstantBuffers);

	/** @brief Dibuja una lista de índices. */
	void
	DrawIndexed(unsigned int IndexCount,
				unsigned int StartIndexLocation,
				int BaseVertexLocation);
private:

public:
	ID3D11DeviceContext* m_deviceContext = nullptr;
};