#pragma once
#include "Prerequisites.h"
#include "InputLayout.h"

class Device;
class DeviceContext;

/**
 * @class ShaderProgram
 * @brief Encapsula la gestión de shaders y el input layout en DirectX 11.
 *
 * Esta clase permite compilar, crear, aplicar y destruir shaders de vértices y píxeles,
 * además de configurar el input layout correspondiente. Es fundamental para definir cómo
 * se procesan los vértices y los fragmentos en la GPU.
 */
class ShaderProgram {
public:
  /**
   * @brief Constructor por defecto del ShaderProgram.
   */
  ShaderProgram() = default;

  /**
   * @brief Destructor del ShaderProgram.
   */
  ~ShaderProgram() = default;

  /**
   * @brief Inicializa los shaders y el input layout desde un archivo `.fx` o `.hlsl`.
   *
   * @param device Referencia al dispositivo Direct3D.
   * @param fileName Ruta del archivo del shader.
   * @param Layout Estructura que describe los elementos del input layout.
   * @return `S_OK` si la inicialización fue exitosa, de lo contrario retorna un código de error.
   */
  HRESULT init(Device& device,
              const std::string& fileName,
              std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

  /**
   * @brief Método reservado para futuras actualizaciones del shader.
   */
  void update();

  /**
   * @brief Aplica el shader y el input layout en el contexto de renderizado.
   *
   * @param deviceContext Contexto del dispositivo donde se aplican los shaders.
   */
  void render(DeviceContext& deviceContext);

  /**
   * @brief Libera los recursos asignados a los shaders y al input layout.
   */
  void destroy();

  /**
   * @brief Crea el input layout que define cómo se interpretan los datos del vértice.
   *
   * @param device Dispositivo usado para crear el layout.
   * @param Layout Vector con la descripción de los elementos del vértice.
   * @return `S_OK` si se crea correctamente.
   */
  HRESULT CreateInputLayout(Device& device,
    std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

  /**
   * @brief Crea el shader correspondiente según su tipo (vértice o píxel).
   *
   * @param device Referencia al dispositivo Direct3D.
   * @param type Tipo de shader a crear (`VERTEX_SHADER` o `PIXEL_SHADER`).
   * @return `S_OK` si se crea correctamente.
   */
  HRESULT CreateShader(Device& device, ShaderType type);

  /**
   * @brief Compila un shader desde archivo fuente.
   *
   * @param szFileName Nombre del archivo del shader.
   * @param szEntryPoint Punto de entrada del shader.
   * @param szShaderModel Modelo de shader (`vs_5_0`, `ps_5_0`, etc).
   * @param ppBlobOut Referencia al blob donde se almacenará el resultado de la compilación.
   * @return `S_OK` si la compilación fue exitosa.
   */
  HRESULT CompileShaderFromFile(char* szFileName,
                                LPCSTR szEntryPoint,
                                LPCSTR szShaderModel,
                                ID3DBlob** ppBlobOut);

public:
  ID3D11VertexShader*                            m_VertexShader = nullptr; ///< Shader de vértices (Vertex Shader).
  ID3D11PixelShader*                             m_PixelShader = nullptr;   ///< Shader de píxeles (Pixel Shader).
  InputLayout                                    m_inputLayout;                   ///< Disposición de los atributos de entrada.

private:
  std::string                                    m_shaderFileName;                ///< Ruta del archivo de shader fuente.
  ID3DBlob*                                      m_vertexShaderData = nullptr;      ///< Datos compilados del shader de vértices.
  ID3DBlob*                                      m_pixelShaderData = nullptr;       ///< Datos compilados del shader de píxeles.
};
