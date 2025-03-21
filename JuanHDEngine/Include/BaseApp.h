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
#include "UI.h"

/**
 * @class BaseApp
 * @brief Clase principal de la aplicación, encargada de la inicialización, actualización y renderizado.
 *
 * Esta clase maneja la lógica de la aplicación, incluyendo la creación de la ventana, la gestión de DirectX 11,
 * la actualización de la cámara, el control de la interfaz gráfica y el bucle principal del programa.
 */
class BaseApp {
public:
  /**
   * @brief Constructor por defecto de BaseApp.
   */
  BaseApp() = default;

  /**
   * @brief Destructor de BaseApp.
   */
  ~BaseApp() = default;

  /**
   * @brief Inicializa los recursos de la aplicación, incluyendo DirectX y la UI.
   * @return `S_OK` si la inicialización es exitosa, de lo contrario devuelve un código de error.
   */
  HRESULT init();

  /**
   * @brief Actualiza la lógica de la aplicación en cada frame.
   *
   * Maneja el tiempo, la entrada del usuario y la actualización de la cámara.
   */
  void update();

  /**
   * @brief Renderiza la escena y la interfaz gráfica.
   *
   * Este método se ejecuta en cada frame para dibujar la escena en la pantalla.
   */
  void render();

  /**
   * @brief Rota la cámara en base al movimiento del mouse.
   * @param mouseX Posición X del mouse.
   * @param mouseY Posición Y del mouse.
   */
  void rotateCamera(int mouseX, 
                    int mouseY);

  /**
   * @brief Actualiza la vista de la cámara en base a su posición y dirección.
   */
  void updateCamera();

  /**
   * @brief Libera los recursos utilizados por la aplicación antes de cerrarla.
   */
  void destroy();

  /**
   * @brief Redimensiona la ventana y ajusta los buffers de DirectX en consecuencia.
   * @param hWnd Handle de la ventana.
   * @param lParam Parámetro con las dimensiones de la nueva ventana.
   * @return `S_OK` si la operación fue exitosa, de lo contrario devuelve un código de error.
   */
  HRESULT resizeWindow(HWND hWnd, 
                       LPARAM lParam);

  /**
   * @brief Actualiza la posición de la cámara en base a la entrada del usuario.
   * @param deltaTime Tiempo transcurrido entre frames para un movimiento suave.
   */
  void updateTransalationbyKeys(float deltaTime);

  /**
   * @brief Ejecuta el bucle principal de la aplicación.
   *
   * Maneja los eventos del sistema y actualiza la aplicación en cada iteración.
   *
   * @param hInstance Instancia de la aplicación.
   * @param hPrevInstance Instancia anterior (no se usa en la mayoría de los casos).
   * @param lpCmdLine Línea de comandos.
   * @param nCmdShow Modo de visualización de la ventana.
   * @param wndproc Procedimiento de la ventana.
   * @return Código de salida de la aplicación.
   */
  int run(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR lpCmdLine,
    int nCmdShow,
    WNDPROC wndproc);

private:
  /** @brief Ventana principal de la aplicación. */
  Window                              m_window;

public:
  // **Objetos principales del motor**
  Window                              g_window;                  ///< Ventana de la aplicación.
  Device                              g_device;                  ///< Dispositivo Direct3D.
  DeviceContext                       g_deviceContext;     ///< Contexto del dispositivo.
  SwapChain                           g_swapchain;             ///< Swapchain para la presentación de la imagen.
  Texture                             g_backBuffer;              ///< BackBuffer para renderizado.
  Texture                             g_depthStencil;            ///< Textura de profundidad.
  RenderTargetView                    g_renderTargetView; ///< Vista del render target.
  DepthStencilView                    g_depthStencilView; ///< Vista del depth stencil.
  Viewport                            g_viewport;               ///< Viewport de la escena.
  ShaderProgram                       g_shaderProgram;     ///< Programa de shaders.

  // **Buffers de datos**
  Buffer                              g_vertexBuffer;             ///< Buffer de vértices.
  Buffer                              g_indexBuffer;              ///< Buffer de índices.
  Buffer                              g_neverChanges;             ///< Buffer para constantes inmutables.
  Buffer                              g_changeOnResize;           ///< Buffer para cambios al redimensionar.
  Buffer                              g_changeEveryFrame;         ///< Buffer para constantes que cambian cada frame.

  // **Texturas y Samplers**
  ID3D11SamplerState*               g_pSamplerLinear = nullptr; ///< Sampler para texturas.
  Texture                           g_textureRV;             ///< Recurso de textura.

  // **Interfaz gráfica**
  UI                                g_ui;                          ///< Controlador de la UI.

  // **Matrices de transformación**
  XMMATRIX                          g_modelMatrix;           ///< Matriz del modelo.
  XMMATRIX                          g_View;                  ///< Matriz de vista de la cámara.
  XMMATRIX                          g_Projection;            ///< Matriz de proyección.
  XMFLOAT4                          g_vMeshColor;            ///< Color del modelo.

  // **Transformaciones del objeto**
  XMFLOAT3                          position;                ///< Posición del objeto en la escena.
  XMFLOAT3                          rotation;                ///< Rotación del objeto en la escena.
  XMFLOAT3                          scale;                   ///< Escala del objeto en la escena.

  // **Buffers constantes**
  CBChangesEveryFrame               cb;           ///< Buffer de constantes que cambian cada frame.
  CBNeverChanges                    cbNeverChanges;    ///< Buffer de constantes inmutables.
  CBChangeOnResize                  cbChangesOnResize; ///< Buffer para cambios en la ventana.

  // **Entrada del usuario**
  bool keys[256] = { false };        ///< Estado de las teclas del teclado.
  Camera g_camera;                   ///< Cámara de la escena.
  bool mouseLeftDown = false;        ///< Estado del botón izquierdo del mouse.
  int lastY;                         ///< Última posición Y del mouse.
  int lastX;                         ///< Última p
  float sensitivity = 0.1f;          ///< Sensibilidad del mouse. 
};