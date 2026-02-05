#include <iostream>
#include <d3d12.h>
#include <dxgi1_6.h>

// Varible pour stocker la fenetre
HWND hwnd = NULL;

// nom de la fenetre
LPCTSTR WindowName = L"Moteur 3D";
// titre de la fenetre
LPCTSTR WindowTitle = L"Moteur 3D - DirectX 12";

int width = 800;
int height = 800;

bool FullScreen = false;

// pointeur vers la fonction de gestion des messages
//PasFini
//wc.cbSize = sizeof(WNDCLASSEX); // taille de la structure
//wc.style = CS_HREDRAW | CS_VREDRAW; // style de la fenetre


void mainloop() {
	MSG msg; // structure pour stocker les messages
	ZeroMemory(&msg, sizeof(MSG)); // initialiser la structure a zero
	while (true) {
		// boucle infinie
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // si il y a un message a traiter
		{
			if (msg.message == WM_QUIT) // si le message est de quitter
			{
				TranslateMessage(&msg); // traduire le message
				DispatchMessage(&msg);
			}// envoyer le message a la fonction de gestion des messages
		}
	}
}

LRESULT CALLBACK WndProc(HWND hwnd,// la fentre concernee
	UINT msg, // type de message qui va etre envoye (genre un clic, une touche appuyee, etc)
	WPARAM wparam, // parametre supplementaire (varie selon le message envoye, genre une touche précise)
	LPARAM lparam) // parametre supplementaire (varie selon le message envoye, genre position de la souris)
{
	switch (msg) // selon le type de message envoye 
	{
	case WM_KEYDOWN:
		if (wparam == VK_ESCAPE) {
			if (MessageBox(0, L"Are you sure you want to exit?",
				L"Really?", MB_YESNO | MB_ICONQUESTION) == IDYES)
				DestroyWindow(hwnd); // detruire la fenetre
		}
		return 0;
	case WM_DESTROY: // si le message est de detruire la fenetre
		PostQuitMessage(0); // poster un message de fin d'application
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam); // procedure par defaut de gestion des messages
}


bool InitializeWindow(HINSTANCE hinstance, // instance de l'application
	int ShowWnd, //	mode d'affichage de la fenetre
	int width, int height, // taille de la fenetre
	bool FullScreen) // si la fenetre est en plein ecran ou pas
{
	if (FullScreen) {
		HMONITOR hmon = MonitorFromWindow(hwnd, // la fenetre concernee
			MONITOR_DEFAULTTONEAREST); // obtenir le moniteur le plus proche de la fenetre
		MONITORINFO mi = { sizeof(mi) }; // structure pour stocker les infos du moniteur

		GetMonitorInfo(hmon, &mi); // obtenir les infos de notre moniteur
		width = mi.rcMonitor.right - mi.rcMonitor.left; // largeur de l'ecran (rcMonitor est un RECT qui definit les dimensions du moniteur)
		height = mi.rcMonitor.bottom - mi.rcMonitor.top; // hauteur de l'ecran
	}

	WNDCLASSEX wc; // structure pour stocker les informations de la fenetre
	wc.cbSize = sizeof(WNDCLASSEX); // taille de la structure
	wc.style = CS_HREDRAW | CS_VREDRAW; // style de la fenetre
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = NULL; // espace memoire supplementaire pour la classe
	wc.cbWndExtra = NULL; // espace memoire supplementaire pour la fenetre
	wc.hInstance = hinstance; // instance de l'application
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // icone de la fenetre
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // curseur de la fenetre
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // couleur de fond de la fenetre
	wc.lpszMenuName = NULL; // pas de menu
	wc.lpszClassName = WindowName; // nom de la fenetre
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION); // petite icone de la fenetre

	if (!RegisterClassEx(&wc)) // enregistrer la classe de la fenetre
	{
		MessageBox(0, L"Registering Class Failed",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	hwnd = CreateWindowEx(NULL, // styles et extensions supplementaires
		WindowName, // nom de la fenetre
		WindowTitle, // titre de la fenetre
		WS_OVERLAPPEDWINDOW, // style de la fenetre (bordures, boutons, etc)
		CW_USEDEFAULT, CW_USEDEFAULT, // position initiale de la fenetre (x,y)
		width, height, // taille de la fenetre (largeur, hauteur)
		NULL, // fenetre parente
		NULL, // pas de menu
		hinstance, // instance de l'application
		NULL); // parametres supplementaires

	if (!hwnd) // si la creation de la fenetre a echoue
	{
		MessageBox(0, L"Creating Window Failed",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	if (FullScreen)
	{
		SetWindowLong(hwnd, GWL_STYLE, 0); // enlever les bordures et boutons de la fenetre
	}

	ShowWindow(hwnd, ShowWnd); // afficher la fenetre
	UpdateWindow(hwnd); // mettre a jour la fenetre
	return true; // fenetre initialisee avec succes
}


int WINAPI WinMain(HINSTANCE hinstance, // notre instance de l'application
	HINSTANCE hPreviousInstance, // instance precedente de l'application
	LPSTR lpCmdLine,
	int nShowCmd) // ligne de commande
{
	// initialisation de la fenetre
	if (!InitializeWindow(hinstance, nShowCmd, width, height, FullScreen))
	{
		MessageBox(0, L"Window Initialization - Failed",
			L"Error", MB_OK);
		return 0;
	}
	mainloop();
	return 0;
}

