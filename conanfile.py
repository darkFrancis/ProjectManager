from conans import ConanFile, CMake, tools


class ProjectManagerConan(ConanFile):
    name = "ProjectManager"
    version = "1.2.2"
    license = "Copyright Dark Francis 2021"
    author = "Dark Francis dark.francis.dod@gmail.com"
    url = "https://github.com/darkFrancis/ProjectManager"
    description = "Project manager"
    
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"

    def source(self):
        self.run("git clone git@github.com:darkFrancis/ProjectManager.git")

    def build(self):
        cmake = CMake(self)
        cmake.definitions["DEFINED_VERSION"] = self.version
        cmake.definitions["DEFINED_APP_NAME"] = self.name
        cmake.configure(source_folder="ProjectManager")
        cmake.build()

    def package(self):
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)
        
    def imports(self):
        self.copy("*.dll")
        self.copy("*.so")
        self.copy("*.a")

    def requirements(self):
        self.requires("Logger/0.5@yggdrasil/stable")

