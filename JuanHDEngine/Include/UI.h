#pragma once
#include "PreRequisites.h"

/**
 * @class UI
 * @brief Clase encargada de gestionar la interfaz de usuario.
 *
 * La clase UI se encarga de inicializar, actualizar y renderizar la interfaz gráfica
 * utilizando Dear ImGui. Además, proporciona métodos para configurar el estilo visual
 * y controlar elementos de la UI, como los paneles de transformación de objetos.
 */
class UI {
public:
  /**
   * @brief Constructor por defecto de la clase UI.
   */
  UI() = default;

  /**
   * @brief Destructor de la clase UI.
   */
  ~UI() = default;

  /**
   * @brief Inicializa la interfaz gráfica.
   *
   * @param window Puntero a la ventana de la aplicación.
   * @param device Puntero al dispositivo Direct3D 11.
   * @param deviceContext Puntero al contexto de dispositivo Direct3D 11.
   */
  void init(void* window, ID3D11Device* device, ID3D11DeviceContext* deviceContext);

  /**
   * @brief Actualiza el estado de la interfaz de usuario en cada frame.
   *
   * Este método se debe llamar antes de renderizar la UI para capturar eventos
   * y actualizar elementos interactivos.
   */
  void update();

  /**
   * @brief Renderiza la interfaz de usuario.
   *
   * Debe llamarse después de la fase de actualización y antes de presentar el frame
   * en pantalla.
   */
  void render();

  /**
   * @brief Destruye y libera los recursos utilizados por la UI.
   *
   * Este método debe ser llamado antes de cerrar la aplicación para evitar
   * pérdidas de memoria.
   */
  void destroy();

  /**
   * @brief Aplica un estilo visual a la interfaz gráfica.
   *
   * Define los colores, bordes y apariencia general de la UI según un esquema de diseño predefinido.
   */
  void baseStyleGUI();

  /**
   * @brief Renderiza una ventana simple en la UI.
   *
   * Este método se usa para dibujar un panel de control o herramientas dentro de la interfaz.
   */
  void renderWindow();

  /**
   * @brief Renderiza un panel de inspección de propiedades de objetos 3D.
   *
   * Permite modificar en tiempo real la posición, rotación y escala de los objetos en la escena.
   */
  void Inspector();

  /**
   * @brief Control personalizado para modificar valores de un vector de 3 dimensiones.
   *
   * @param label Nombre del control que se mostrará en la UI.
   * @param value Puntero al arreglo de valores (x, y, z).
   * @param resetValues Valor de reinicio por defecto (0.0f por defecto).
   * @param columnWidth Ancho de la columna para la disposición de los controles (100.0f por defecto).
   */
  void vec3Control(std::string label,
                    float* value, 
                    float resetValues = 0.0f, 
                    float columnWidth = 100.0f);
};
