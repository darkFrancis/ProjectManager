from conans import ConanFile, CMake, tools


class ProjectManagerConan(ConanFile):
    name = "ProjectManager"
    version = "1.2.0"
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

    def build_requirements(self):
        self.build_requires("Logger/0.2@dark/francis")

