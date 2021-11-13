# ProjectManager
> Outil de gestion de projet
<br/>V1.2.0

# Dependencies 
[Logger](https://github.com/darkFrancis/Logger)
Add Conan remote https://darkfrancis.jfrog.io/artifactory/api/conan/public-conan

# Build
```bash
cd path/to/ProjectManager
mkdir build
cd build
conan install ..
cmake ..
make
```

## Onglets
### Projets
Gestion de la liste de fichiers .pro correspondants aux sous projets à gérer.
### Doxygen
Réglage de la documentation générée.<br/>
Génération de templates de documentation.<br/>
Génération de la documentation.
### Git
Gestion des commandes git les plus utiles.
