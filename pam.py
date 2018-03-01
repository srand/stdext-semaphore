from build.model import *
from externals.googletest import googletest
from toolchains.pam import *


stdext_semaphore = cxx_project(
    name = "stdext-semaphore",
    incpaths = [("include", {"publish": True})]
)

stdext_semaphore_test = cxx_executable(
    name = "stdext-semaphore-test",
    sources = ["test/test.cpp"],
    dependencies = [stdext_semaphore, googletest],
    features = ["language-c++11"]
)
