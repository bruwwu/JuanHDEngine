#pragma once
#include "Prerequisites.h"
#include "Utilities/Vectors/Vector3.h"
#include "Component.h"

/**
 * @class Transform
 * @brief Componente que representa la posición, rotación y escala de un objeto en el mundo 3D.
 *
 * Esta clase administra la transformación espacial del objeto y forma parte del sistema ECS (Entity-Component-System).
 * Extiende de `Component` para integrarse en la arquitectura de entidades.
 */
class Transform : public Component {
public:
  /**
   * @brief Constructor por defecto de Transform.
   *
   * Inicializa posición, rotación y escala a sus valores por defecto (cero), y asigna su tipo como `TRANSFORM`.
   */
  Transform() : position(),
    rotation(),
    scale(),
    matrix(),
    Component(ComponentType::TRANSFORM) {}

  /**
   * @brief Inicializa el objeto Transform.
   *
   * Prepara el objeto para su uso en la escena.
   */
  void init();

  /**
   * @brief Actualiza el estado del objeto Transform basado en el tiempo transcurrido.
   *
   * @param deltaTime Tiempo transcurrido desde la última actualización.
   */
  void update(float deltaTime) override;

  /**
   * @brief Renderiza el objeto Transform.
   *
   * @param deviceContext Contexto del dispositivo de renderizado.
   */
  void render(DeviceContext& deviceContext) override {}

  /**
   * @brief Destruye el objeto Transform y libera recursos asociados.
   */
  void destroy() {}

  // **Métodos de acceso y modificación de posición**

  /**
   * @brief Obtiene la posición actual del objeto.
   * @return Referencia constante a la posición.
   */
  const EngineUtilities::Vector3& getPosition() const { return position; }

  /**
   * @brief Establece una nueva posición para el objeto.
   * @param newPos Nueva posición a asignar.
   */
  void setPosition(const EngineUtilities::Vector3& newPos) { position = newPos; }

  // **Métodos de acceso y modificación de rotación**

  /**
   * @brief Obtiene la rotación actual del objeto.
   * @return Referencia constante a la rotación.
   */
  const EngineUtilities::Vector3& getRotation() const { return rotation; }

  /**
   * @brief Establece una nueva rotación para el objeto.
   * @param newRot Nueva rotación a asignar.
   */
  void setRotation(const EngineUtilities::Vector3& newRot) { rotation = newRot; }

  // **Métodos de acceso y modificación de escala**

  /**
   * @brief Obtiene la escala actual del objeto.
   * @return Referencia constante a la escala.
   */
  const EngineUtilities::Vector3& getScale() const { return scale; }

  /**
   * @brief Establece una nueva escala para el objeto.
   * @param newScale Nueva escala a asignar.
   */
  void setScale(const EngineUtilities::Vector3& newScale) { scale = newScale; }

  /**
   * @brief Establece la posición, rotación y escala del objeto de forma conjunta.
   *
   * @param newPos Nueva posición.
   * @param newRot Nueva rotación.
   * @param newSca Nueva escala.
   */
  void setTransform(const EngineUtilities::Vector3& newPos,
    const EngineUtilities::Vector3& newRot,
    const EngineUtilities::Vector3& newSca);

  /**
   * @brief Aplica una traslación adicional al objeto.
   *
   * @param translation Vector de traslación a aplicar.
   */
  void translate(const EngineUtilities::Vector3& translation);

public:
  EngineUtilities::Vector3 position; ///< Posición del objeto en el mundo.
  EngineUtilities::Vector3 rotation; ///< Rotación del objeto en el mundo.
  EngineUtilities::Vector3 scale;    ///< Escala del objeto en el mundo.
  XMMATRIX matrix;                   ///< Matriz de transformación resultante.
};
