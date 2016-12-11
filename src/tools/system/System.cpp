/***************************************************************
 * Name:      System.cpp
 * Purpose:   Code for wxTools
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2016-12-11
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "System.h"

#ifdef __WXMSW__
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <dirent.h>
    #include <windows.h>
    #include <shlobj.h>
    #include <shellapi.h>
#else
    #include <unistd.h>
#endif

using namespace tools::system;

System::System()
{
    //ctor
}

System::~System()
{
    //dtor
}

wxString System::getUnauthorizedCharacterFile()
{
    #ifdef __WXMSW__
    return "\\/:*?\"<>|";
    #endif // __WXMSW__
}

bool System::createShortcut(const wxString& shortcut, const wxString& filename)
{
    #ifdef __WXMSW__
    bool resultat = false;
    CoInitialize(NULL);
    IShellLink* pIShellLink = NULL;
    if (SUCCEEDED(CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID *)&pIShellLink)))
    {
        IPersistFile* pIPersistFile = NULL;
        wxString description = _T("Raccourci fichier .") + filename.AfterLast('.') + _T(" - Fu(X) 2.0");

        // Vérifier si le raccourci existe déjà:

        // Définir le chemin du raccourci et descrition:
        pIShellLink->SetPath(filename.c_str());
        pIShellLink->SetDescription(description.c_str());

        //Sauvegarde le raccourci de façon durable
        if (SUCCEEDED(pIShellLink->QueryInterface(IID_IPersistFile, (LPVOID *)&pIPersistFile)))
        {
            // Convertir le chemin en UNICODE:
            WCHAR *chaine = new WCHAR[shortcut.Length()+2];

            MultiByteToWideChar(CP_ACP, 0, shortcut.mb_str(), -1, (LPWSTR)chaine, shortcut.Length()+1);
            // Créer le raccourci:
            resultat = pIPersistFile->Save(chaine, 1);

            delete[] chaine;
            // Libérer l'interface IPersistFile:
            pIPersistFile->Release();
        }
     }
     // Libérer l'interface IShellLink:
     pIShellLink->Release();
     // Fermer la librairie COM:
     CoUninitialize();
     return !resultat;
    #else
    return !symlink(filename.c_str(), shortcut.c_str());
    #endif // __WXMSW__
}

