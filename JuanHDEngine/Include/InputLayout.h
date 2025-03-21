#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;

/**
 * @class InputLayout
 * @brief Administra la disposición de entrada de vértices para la pipeline gráfica de DirectX 11.
 *
 * Esta clase encapsula la creación, actualización y uso de un `ID3D11InputLayout`,
 * el cual define cómo los datos de vértices son interpretados por el **Vertex Shader**.
 */
class InputLayout {
public:
  /**
   * @brief Constructor por defecto de InputLayout.
   */
  InputLayout() = default;

  /**
   * @brief Destructor de InputLayout.
   *
   * Se encarga de liberar los recursos de DirectX asociados a la disposición de entrada.
   */
  ~InputLayout() = default;

  /**
   * @brief Inicializa el Input Layout con una descripción de los elementos de entrada.
   *
   * @param device Referencia al objeto `Device` para crear el Input Layout.
   * @param Layout Vector que contiene la descripción de los elementos de entrada (`D3D11_INPUT_ELEMENT_DESC`).
   * @param VertexShaderData Puntero al blob del shader de vértices, necesario para validar el Input Layout.
   * @return `S_OK` si la inicialización fue exitosa, o un código de error de DirectX.
   */
  HRESULT init(Device& device,
              std::vector<D3D11_INPUT_ELEMENT_DESC>& Layout,
              ID3DBlob* VertexShaderData);

  /**
   * @brief Actualiza los valores internos del Input Layout (si es necesario).
   *
   * Este método puede ser útil si se requiere modificar dinámicamente el Input Layout.
   */
  void update();

  /**
   * @brief Configura el Input Layout en el contexto del dispositivo.
   *
   * @param deviceContext Referencia al contexto del dispositivo (`DeviceContext`) donde se aplicará el Input Layout.
   */
  void render(DeviceContext& deviceContext);

  /**
   * @brief Libera los recursos del Input Layout.
   *
   * Se encarga de liberar `m_inputLayout` para evitar fugas de memoria.
   */
  void destroy();

public:
  ID3D11InputLayout* m_inputLayout = nullptr; ///< Puntero al objeto de DirectX que define el Input Layout.
};
