#pragma once

// **Librerías estándar (STD)**
#include <string>
#include <sstream>
#include <vector>
#include <windows.h>
#include <xnamath.h>
#include <thread>

// **Librerías de DirectX**
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include "Resource.h"
#include "resource.h"

// **Librerías de ImGui**
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_internal.h>
#include "imgui_impl_win32.h"

// EngineUtilities
#include "Utilities/Memory/TSharedPointer.h"
#include "Utilities/Memory/TStaticPtr.h"
#include "Utilities/Memory/TWeakPointer.h"
#include "Utilities/Memory/TUniquePtr.h"

//Mathmamadams
#include "Utilities\Vectors\Vector3.h"
#include "Utilities\Matrix\Matrix4x4.h"

// **MACROS**
/**
 * @brief Libera de forma segura un recurso COM.
 *
 * Evita fugas de memoria asegurando que el recurso se libere y se establezca en `nullptr`.
 * @param x Puntero al recurso COM que se desea liberar.
 */
#define SAFE_RELEASE(x) if(x != nullptr) x->Release(); x = nullptr;

 /**
  * @brief Mensaje de depuración para la creación de recursos.
  *
  * Registra en la consola un mensaje indicando la creación de un recurso en DirectX.
  * @param classObj Nombre de la clase donde ocurre el evento.
  * @param method Método donde ocurre el evento.
  * @param state Estado del recurso creado.
  */
#define MESSAGE(classObj, method, state)   \
{                                          \
   std::wostringstream os_;                \
   os_ << classObj << "::" << method << " : " << "[CREATION OF RESOURCE " << ": " << state << "] \n"; \
   OutputDebugStringW(os_.str().c_str());  \
}

  /**
   * @brief Mensaje de error en la consola de depuración.
   *
   * Captura errores en la ejecución y los muestra en la consola para facilitar la depuración.
   * @param classObj Nombre de la clase donde ocurre el error.
   * @param method Método donde ocurre el error.
   * @param errorMSG Mensaje de error.
   */
#define ERROR(classObj, method, errorMSG)                      \
{                                                              \
    try {                                                      \
        std::wostringstream os_;                               \
        os_ << L"ERROR : " << classObj << L"::" << method      \
            << L" : " << errorMSG << L"\n";                    \
        OutputDebugStringW(os_.str().c_str());                 \
    } catch (...) {                                            \
        OutputDebugStringW(L"Failed to log error message.\n"); \
    }                                                          \
}

   // **Enumeraciones**
   /**
    * @enum ComponentType
    * @brief Define los tipos de componentes disponibles en la escena.
    */
enum
  ComponentType {
  NONE = 0,     ///< Tipo de componente no especificado.
  TRANSFORM = 1,///< Componente de transformación.
  MESH = 2,     ///< Componente de malla.
  MATERIAL = 3  ///< Componente de material.
};

// **Estructura de la Cámara**
/**
 * @struct Camera
 * @brief Representa la cámara en la escena 3D.
 */
struct Camera {
  XMFLOAT3 position;  ///< Posición de la cámara en el mundo.
  XMFLOAT3 target;    ///< Punto al que la cámara está mirando.
  XMFLOAT3 up;        ///< Vector que indica la dirección "arriba" de la cámara.
  XMFLOAT3 forward;   ///< Vector que indica la dirección hacia adelante.
  XMFLOAT3 right;     ///< Vector que indica la dirección hacia la derecha.

  float yaw;          ///< Rotación en el eje Y.
  float pitch;        ///< Rotación en el eje X.

  /**
   * @brief Constructor de la cámara, inicializa su posición y orientación por defecto.
   */
  Camera() {
    position = XMFLOAT3(0.0f, 1.6f, -5.0f);
    target = XMFLOAT3(0.0f, 1.6f, 0.0f);
    up = XMFLOAT3(0.0f, 1.0f, 0.0f);
    forward = XMFLOAT3(0.0f, 0.0f, 1.0f);
    right = XMFLOAT3(1.0f, 0.0f, 0.0f);
    yaw = 0.0f;
    pitch = 0.0f;
  }
};

// **Estructuras de Datos**
/**
 * @struct SimpleVertex
 * @brief Representa un vértice con posición y coordenadas de textura.
 */
struct SimpleVertex {
  XMFLOAT3 Pos;  ///< Posición del vértice en el espacio 3D.
  XMFLOAT2 Tex;  ///< Coordenadas de textura.
};

/**
 * @struct CBNeverChanges
 * @brief Buffer constante que no cambia durante la ejecución del programa.
 */
struct CBNeverChanges {
  XMMATRIX mView;  ///< Matriz de vista utilizada en la renderización.
};

/**
 * @struct CBChangeOnResize
 * @brief Buffer constante que cambia cuando la ventana se redimensiona.
 */
struct CBChangeOnResize {
  XMMATRIX mProjection; ///< Matriz de proyección utilizada en la renderización.
};

/**
 * @struct CBChangesEveryFrame
 * @brief Buffer constante que se actualiza en cada frame.
 */
struct CBChangesEveryFrame {
  XMMATRIX mWorld;   ///< Matriz de transformación del modelo.
  XMFLOAT4 vMeshColor; ///< Color del modelo.
};

// **Enumeraciones Adicionales**
/**
 * @enum ExtensionType
 * @brief Tipos de extensiones de texturas soportadas.
 */
enum ExtensionType {
  DDS = 0, ///< Formato de textura DDS.
  PNG = 1, ///< Formato de textura PNG.
  JPG = 2  ///< Formato de textura JPG.
};

/**
 * @enum ShaderType
 * @brief Tipos de shaders utilizados en la aplicación.
 */
enum ShaderType {
  VERTEX_SHADER = 0, ///< Shader de vértices.
  PIXEL_SHADER = 1   ///< Shader de píxeles.
};

struct LoadDataOBJ {
  std::string name; ///< Nombre del objeto.
  std::vector<SimpleVertex> vertex; ///< Vértices del objeto.
  std::vector<unsigned int> index; ///< Índices de los vértices.
  int numVertex = 0; ///< Número de vértices.
  int numIndex = 0; ///< Número de índices.
};