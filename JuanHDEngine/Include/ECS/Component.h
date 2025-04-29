#pragma once

class DeviceContext;

/**
 * @class Component
 * @brief Clase base abstracta para todos los componentes del motor de juego.
 *
 * Define la interfaz básica que todos los componentes deben implementar,
 * permitiendo su actualización y renderizado. También maneja la identificación
 * de cada componente mediante un tipo específico.
 */
class Component {
public:
  /**
   * @brief Constructor por defecto de Component.
   */
  Component() = default;

  /**
   * @brief Constructor que inicializa el tipo de componente.
   * @param type Tipo del componente definido en la enumeración ComponentType.
   */
  Component(const ComponentType type) : m_type(type) {}

  /**
   * @brief Destructor virtual de Component.
   *
   * Permite la destrucción adecuada de objetos derivados.
   */
  virtual ~Component() = default;

  /**
   * @brief Actualiza la lógica del componente.
   *
   * Método virtual puro que debe ser implementado por las clases hijas.
   *
   * @param deltaTime Tiempo transcurrido desde la última actualización.
   */
  virtual void update(float deltaTime) = 0;

  /**
   * @brief Renderiza el componente.
   *
   * Método virtual puro que debe ser implementado por las clases hijas.
   *
   * @param deviceContext Contexto del dispositivo para renderizar operaciones gráficas.
   */
  virtual void render(DeviceContext& deviceContext) = 0;

  /**
   * @brief Obtiene el tipo del componente.
   * @return Tipo del componente (`ComponentType`).
   */
  ComponentType getType() const { return m_type; }

protected:
  ComponentType m_type; ///< Tipo del componente, definido en la enumeración ComponentType.
};
