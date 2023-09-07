project('foray', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'optimization=3',
                     # 'b_lto=true',
                     'b_lto_mode=thin',
                     'cpp_std=c++20'])

exe = executable('foray', 'src/foray.cpp', 'src/canvas.cpp', 'src/vec3.cpp',
                          'src/ray.cpp', 'src/scene.cpp', 'src/scene_object.cpp',
                 install : true)

test('basic', exe)
