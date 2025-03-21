#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;

/**
 * @class SamplerState
 * @brief Gestiona los estados de muestreo de texturas en DirectX 11.
 *
 * Esta clase encapsula la creación y uso de un `ID3D11SamplerState`, que define cómo
 * se filtran y aplican las texturas en la renderización.
 */
class SamplerState {
public:
  /**
   * @brief Constructor por defecto de SamplerState.
   */
  SamplerState() = default;

  /**
   * @brief Destructor de SamplerState.
   *
   * Libera los recursos utilizados por el objeto `ID3D11SamplerState`.
   */
  ~SamplerState() = default;

  /**
   * @brief Inicializa el Sampler State con los parámetros de filtrado y dirección de texturas.
   *
   * @param device Referencia al objeto `Device` utilizado para la creación del Sampler State.
   * @return `S_OK` si la inicialización es exitosa, o un código de error de DirectX.
   */
  HRESULT init(Device& device);

  /**
   * @brief Actualiza los valores internos del Sampler State si es necesario.
   *
   * Este método permite realizar cambios dinámicos en los parámetros del Sampler.
   */
  void update();

  /**
   * @brief Asigna el Sampler State al contexto del dispositivo para su uso en los shaders.
   *
   * @param deviceContext Referencia al contexto del dispositivo (`DeviceContext`) donde se aplicará el Sampler.
   * @param StartSlot Índice de inicio del slot donde se vinculará el Sampler State.
   * @param NumSamplers Número de Samplers a establecer en la pipeline gráfica.
   */
  void render(DeviceContext& deviceContext,
    unsigned int StartSlot,
    unsigned int NumSamplers);

  /**
   * @brief Libera los recursos del Sampler State.
   *
   * Se encarga de liberar `m_sampler` para evitar fugas de memoria.
   */
  void destroy();

public:
  ID3D11SamplerState* m_sampler = nullptr; ///< Puntero al estado de muestreo de DirectX 11.
};
