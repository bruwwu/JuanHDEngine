#pragma once
#include "Prerequisites.h"

/**
 * @class Window
 * @brief Encapsula la creación y gestión de la ventana principal de la aplicación.
 *
 * Esta clase se encarga de inicializar, actualizar, renderizar y destruir la ventana de
 * la aplicación utilizando la API Win32. Además, mantiene el tamaño y el handle
 * necesarios para el contexto gráfico.
 */
class Window {
public:
  /**
   * @brief Constructor por defecto de Window.
   */
  Window() = default;

  /**
   * @brief Destructor por defecto de Window.
   */
  ~Window() = default;

  /**
   * @brief Inicializa la ventana principal.
   *
   * @param hInstance Instancia de la aplicación.
   * @param nCmdShow Estado de visualización de la ventana (normal, minimizada, etc).
   * @param wndproc Puntero a la función de procedimiento de ventana (callback).
   * @return `S_OK` si la ventana fue creada correctamente, o un código de error.
   */
  HRESULT init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc);

  /**
   * @brief Actualiza el estado interno de la ventana (si aplica).
   */
  void update();

  /**
   * @brief Renderiza el contenido de la ventana (placeholder para compatibilidad).
   */
  void render();

  /**
   * @brief Destruye la ventana y libera sus recursos.
   */
  void destroy();

  /**
   * @brief Redimensiona internamente los valores de la ventana.
   *
   * Se utiliza normalmente al recibir eventos de `WM_SIZE`.
   */
  void ResizeWindow();

public:
  HWND m_hWnd = nullptr;          ///< Handle de la ventana principal.
  unsigned int m_width;           ///< Ancho de la ventana en píxeles.
  unsigned int m_height;          ///< Alto de la ventana en píxeles.

private:
  HINSTANCE m_hInst = nullptr;    ///< Instancia de la aplicación.
  RECT m_rect;                    ///< Rectángulo que define el área de la ventana.
  std::string m_windowName = "JuanHDEngine"; ///< Nombre por defecto de la ventana.
};
