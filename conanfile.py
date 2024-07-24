from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMake 

class SmoldbRecipe(ConanFile):
    name = "smoldb"
    version = "0.0.1"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"
    options = {
            "install_gtest": [True, False],
    }
    default_options = {
            "install_gtest": True,
    }

    def requirements(self):
        self.requires("gtest/1.14.0")

    def layout(self):
        cmake_layout(self)
