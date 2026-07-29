Create a .vscode folder. In it you will create two files:
c_cpp_properties.json AND tasks.json


Here is a sample code you will need for c_cpp_properties.json. Fill it in with your paths
**********************************
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**",
                "PATH OF glfw-3.4.bin.WIN64",
                "PATH OF glew-2.3.1",
                "PATH OF GLM"
            ],
            "defines": [
                "GLEW_STATIC"
            ],
            "compilerPath": "YOUR PATH FOR MSYS",
            "cStandard": "c17",
            "cppStandard": "c++17",
            "intelliSenseMode": "windows-gcc-x64"
        }
    ],
    "version": 4
}

****************
Here is the code for tasks.json, please fill it in with your paths
**************

{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Build OpenGL Project",
            "type": "shell",
            "command": "PATH g++.exe",
            "args": [
                "-g",
                "-std=c++17",
                "-DGLEW_STATIC",
                "-I", "PATH glfw-3.4.bin.WIN64",
                "-I", "PATH glew-2.3.1",
                "-I", "PATH GLM",
                "${workspaceFolder}/main.cpp",
                "${workspaceFolder}/VertexShader.cpp",
"${workspaceFolder}/FragmentShader.cpp",
"${workspaceFolder}/Pyramid.cpp",
                ADD OTHER CPP FILES HERE AS WELL WHEN YOU CREATE THEM
                
                "-o", "${workspaceFolder}/main.exe",
                "-L", "PATH glfw-3.4.bin.WIN64/lib-mingw-w64",
                "-L", "PATH glew-2.3.1/lib/Release/x64",
                "-lglew32s", "-lglfw3", "-lopengl32", "-lgdi32", "-luser32"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "problemMatcher": ["$gcc"],
            "detail": "Compiles main.cpp with GLFW, GLEW (static), and GLM"
        }
    ]
}