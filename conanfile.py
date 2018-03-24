from conans import ConanFile, CMake, tools


class StdextsemaphoreConan(ConanFile):
    name = "stdext-semaphore"
    version = "1.0"
    license = "http://github.com/srand/stdext-semaphore/LICENSE"
    url = "http://github.com/srand/stdext-semaphore"
    description = "stdext::semaphore"
    settings = None
    exports_sources = "include/*"

    def package(self):
        self.copy("*.h", dst="include", src="include")

    def package_info(self):
        self.cpp_info.includedirs = ["include"]
