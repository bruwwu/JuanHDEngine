#pragma once
#include "PreRequisites.h"
#include "Window.h"

class
	BaseApp {
public:
	BaseApp() = default;
	~BaseApp() = default;

	HRESULT
	init();

	void
	update();

	void
	render();

	void
	destroy();

	/** @brief Ejecuta el bucle principal de la aplicación. */
	int
	run(HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPWSTR lpCmdLine,
		int nCmdShow,
		WNDPROC wndproc);

private:
	/** @brief Ventana principal de la aplicación. */
	Window m_window;
};